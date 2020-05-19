/*************************************************************************
  @FileName: HttpMsg.cpp
  @Author:   morey
  @Email:    zymorey@gmail.com
  @Time:     Fri 20 Dec 2019 07:41:48 PM CST
 ************************************************************************/
#include "HttpMsg.hpp"

HttpMsg::HttpMsg()
    :httpBase_(NULL)
    ,blob_(NULL)
     , commu_(NULL)
{
    isFin_ = false;
    isDataOver_ = false;
    isPageOk_   =false;
    ackNum_ = 0;
    nextAckNum_ = 0;
    lastSeqNum_ = 0;
    dataLen_ = 0;
    cliIp_ = 0;
    cliPort_ = 0;
    headLen_ = 0;
    sendSumDataLen_ = 0;
    recvSumDataLen_ = 0;
    insertNum_ = 0;
    ipId_   = 2345;
    httpTime_ = time(NULL);
    lastHttpTime_ = time(NULL);
}

HttpMsg::~HttpMsg()
{
    if(sendSumDataLen_ > 0 && 0 < recvSumDataLen_)
    {
        int timeOut = (time(NULL) - lastHttpTime_ - 9);
        if(timeOut <= 0)
            return;
        int webkb = sendSumDataLen_ / (time(NULL) - lastHttpTime_ - 9) / 1024;
        //int httpkb = recvSumDataLen_ / (time(NULL) - lastHttpTime_ - 9) / 1024;
        httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg ~HttpMsg]flow:%d webDataLen:%d httpDataLen:%d webTime:%lds Web:%dkb/s\n", 
                                  flow_, sendSumDataLen_, recvSumDataLen_, time(NULL) - lastHttpTime_ - 9, webkb);
        printf("[HttpMsg ~HttpMsg]flow:%d webDataLen:%d httpDataLen:%d webTime:%lds Web:%dkb/s\n", 
                                  flow_, sendSumDataLen_, recvSumDataLen_, time(NULL) - lastHttpTime_ - 9, webkb);
        printf("blob>len%d\n", blob_->len);
    }
}

int HttpMsg::comPage(unsigned char * sendData/*out*/,char * dataBuf/*in*/, int dateLen)
{
    if(NULL == dataBuf)
    {
        httpBase_->log_.LOG_P_PID(LOG_DEBUG,"[ComTcp comPage]flow:%d组装数据包error ackNum:%x seqNum:%x nextAckNum:%x nextSeqNum:%x \n",
                                  flow_, ackNum_, seqNum_, nextAckNum_, nextSeqNum_);
        return -1;
    }
    DATA_HEADER * rspHead;
    struct iphead* ip;
    struct tcphead* tcp;
    rspHead = (DATA_HEADER *)sendData;
    ip = (struct iphead*)(sendData + sizeof(DATA_HEADER));
    tcp = (struct tcphead*)(sendData + sizeof(DATA_HEADER) + sizeof(struct iphead));

    //TVL头部
    rspHead->version = 1;
    rspHead->commandcode = REQ_AP_GW_BUSINESS;
    rspHead->tun_id = srcPort_;
    rspHead->host_ip = htonl(srcIp_);

    ip->ip_hl = 5;
    ip->ip_version = 4;
    ip->ip_tos = 0;
    ip->ip_len = 0; //总长度
    ip->ip_id = htons(ipId_++);
    ip->ip_off = htons(0x4000);
    ip->ip_ttl = 64;
    ip->ip_pro = IPPROTO_TCP;
    ip->ip_src = srcIp_;
    ip->ip_dst = webIp_;
    ip->ip_sum = 0; //后面再赋值。 //因为不知道长度

    tcp->tcp_sport = htons(srcPort_);
    tcp->tcp_dport = htons(webPort_);
    tcp->tcp_seq = htonl(nextSeqNum_);
    lastSeqNum_ = nextAckNum_;
    nextSeqNum_ += dateLen; //发送超过1500的包的时候Seq有问题。

#if DEBUG_NO
    httpBase_->log_.LOG_P_PID(LOG_DEBUG,"[ComTcp comPage(1,2)]flow:%d seq:%8x ack:%8x nextSeq:%8x nextAck:%8x lastSeq:%8x \n",
                              flow_, seqNum_, ackNum_, nextSeqNum_, nextAckNum_, lastSeqNum_);
#endif

    tcp->tcp_ack = ntohl(nextAckNum_); 
    tcp->tcp_len = 5;
    tcp->tcp_off = 0;
    tcp->tcp_flag = 0x18;
    tcp->tcp_win = htons(4096);
    tcp->tcp_urp = htons(0);
    tcp->tcp_sum = 0;

    struct psdhead psd;
    psd.saddr = srcIp_;
    psd.daddr = webIp_;
    psd.mbz = 0;
    psd.ptcl = 6;
    psd.tcpl = htons(20 + dateLen);
    char buffer[1480];
    memset(buffer, 0, sizeof(buffer));
    memcpy(buffer, &psd, sizeof(psd));
    memcpy(buffer + sizeof(psd), tcp, sizeof(struct tcphead));
    memcpy(buffer + sizeof(psd) + sizeof(struct tcphead), dataBuf, dateLen);//ck
    tcp->tcp_sum = inChksum((unsigned short *)buffer, sizeof(psd) + sizeof(struct tcphead) + dateLen); //TODO 

    unsigned short len = 40 + dateLen;
    ip->ip_len = htons(len); //TODO 网络序
    ip->ip_sum = inChksum((unsigned short *)sendData, 20); // 计算校验和也有问题。
    memcpy(sendData + 40 + sizeof(DATA_HEADER), dataBuf, dateLen);//如果位置还对其进行复制那么就会报错。
    return len + sizeof(DATA_HEADER);
}

int HttpMsg::conn()
{  
    unsigned char packet[MTU_MAX];
    memset(packet, 0, sizeof(packet));
    DATA_HEADER * rspHead;
    struct iphead* ip;
    struct tcphead* tcp;
    rspHead = (DATA_HEADER *)packet;
    ip = (struct iphead*)(packet + sizeof(DATA_HEADER));
    tcp = (struct tcphead*)(packet + sizeof(DATA_HEADER) + sizeof(struct iphead));

    //这是TVL头部
    rspHead->version = 1;
    rspHead->commandcode = REQ_AP_GW_BUSINESS;
    rspHead->tun_id = srcPort_;
    rspHead->host_ip =htonl(srcIp_);

    /*以下分别设置IP，和TCP的首部，然后发送SYN报文段*/
    /*设置IP首部*/
    ip->ip_hl = 5;
    ip->ip_version = 4;
    ip->ip_tos = 0;
    ip->ip_len = htons(sizeof(struct iphead) + sizeof(struct tcphead));
    ip->ip_id = htons(ipId_++); // random()
    ip->ip_off = htons(0x4000);
    ip->ip_ttl = 64;
    ip->ip_pro = IPPROTO_TCP;
    ip->ip_src = srcIp_;
    ip->ip_dst = webIp_;
    ip->ip_sum = inChksum((unsigned short *)packet, 20);  //计算IP首部的校验和，必须在其他字段都赋值后再赋值该字段，赋值前为0

    /*设置TCP首部*/
    tcp->tcp_sport = htons(srcPort_);
    tcp->tcp_dport = htons(webPort_);
    tcp->tcp_seq = htonl(seqNum_);
    nextSeqNum_++;
    tcp->tcp_ack = htonl(nextAckNum_);
    lastSeqNum_ = nextAckNum_;
    tcp->tcp_len = 5;  //发送SYN报文段时，设置TCP首部长度为20字节
    tcp->tcp_off = 0;
    tcp->tcp_flag = 0x02;  //SYN置位
    tcp->tcp_win = htons(4096);
    tcp->tcp_urp = htons(0);
    /*设置tcp伪首部，用于计算TCP报文段校验和*/
    struct psdhead psd;
    psd.saddr = srcIp_; //源IP地址
    psd.daddr = webIp_; //目的IP地址
    psd.mbz = 0;
    psd.ptcl = 6;  
    psd.tcpl = htons(20);
    unsigned char buffer[256]; //用于存储TCP伪首部和TCP报文，计算校验码
    memcpy(buffer, &psd, sizeof(psd));
    memcpy(buffer+sizeof(psd), tcp, sizeof(struct tcphead));
    tcp->tcp_sum = inChksum((unsigned short *)buffer, sizeof(psd) + sizeof(struct tcphead));  //计算检验码

    /*发送SYN报文段*/ //发送给客户端....
    int sendNum = sendto(workFd_, packet, htons(ip->ip_len) + sizeof(DATA_HEADER), 0,(struct sockaddr *)&cliAddr_, sizeof(cliAddr_));

#if DEBUG_YES
    httpBase_->log_.LOG_P_PID(LOG_DEBUG,
                              "[ComTcp    conn]flow:%d seq:%8x ack:%8x lastSeq:%8x nextSeq:%8x nextAck:%8x Len:%d\n",
                                               flow_, seqNum_, ackNum_, lastSeqNum_, nextSeqNum_, nextAckNum_, sendNum);
#endif

    if(sendNum < 0)
    {
        perror("sendto");
        httpBase_->log_.LOG_P_PID(LOG_DEBUG,"[ComTcp conn] sendto synOne error\n");
        return -1;
    }
    return 1;
}

int HttpMsg::sendFin()
{
    unsigned char packet[MTU_MAX];
    memset(packet, 0, sizeof(packet));
    DATA_HEADER * rspHead;
    struct iphead* ip;
    struct tcphead* tcp;
    rspHead = (DATA_HEADER *)packet;
    ip = (struct iphead*)(packet + sizeof(DATA_HEADER));
    tcp = (struct tcphead*)(packet + sizeof(DATA_HEADER) + sizeof(struct iphead));

    //设置TVL头
    rspHead->version = 1;
    rspHead->commandcode = REQ_AP_GW_BUSINESS;
    rspHead->tun_id = srcPort_;
    rspHead->host_ip =htonl(srcIp_);

    /*设置IP首部*/
    ip->ip_hl = 5;
    ip->ip_version = 4;
    ip->ip_tos = 0;
    ip->ip_len = htons(sizeof(struct iphead) + sizeof(struct tcphead));
    ip->ip_id = htons(13543); // random()
    ip->ip_off = htons(0x4000);
    ip->ip_ttl = 64;
    ip->ip_pro = IPPROTO_TCP;
    ip->ip_src = srcIp_;
    ip->ip_dst = webIp_;
    ip->ip_sum = inChksum((unsigned short *)packet + 8, 20); 

    //这里的seq和ACK都还是上一次发送的ACk和seq
    tcp->tcp_sport = htons(srcPort_);
    tcp->tcp_dport = htons(webPort_);

    tcp->tcp_seq = htonl(nextSeqNum_);
    tcp->tcp_ack = ntohl(nextAckNum_);
    nextSeqNum_++;
    tcp->tcp_len = 5;  //发送SYN报文段时，设置TCP首部长度为20字节
    tcp->tcp_off = 0;
    tcp->tcp_flag = 0x11;  //FIN标志位和ACK
    tcp->tcp_win = htons(32768);
    tcp->tcp_urp = htons(0);

    /*设置tcp伪首部，用于计算TCP报文段校验和*/
    struct psdhead psd;
    psd.saddr = srcPort_; //源IP地址
    psd.daddr = webPort_; //目的IP地址
    psd.mbz = 0;
    psd.ptcl = 6;  
    psd.tcpl = htons(20);

    unsigned char buffer[1000]; //用于存储TCP伪首部和TCP报文，计算校验码
    memcpy(buffer, &psd, sizeof(psd));
    memcpy(buffer+sizeof(psd), tcp, sizeof(struct tcphead));
    tcp->tcp_sum = inChksum((unsigned short *)buffer, sizeof(psd) + sizeof(struct tcphead));  //计算检验码
    int sendNum = sendto(workFd_, packet, htons(ip->ip_len) + sizeof(DATA_HEADER), 0,(struct sockaddr *)&cliAddr_, sizeof(cliAddr_));

#if DEBUG_YES
    httpBase_->log_.LOG_P_PID(LOG_DEBUG,
                              "[ComTcp sendFin]flow:%d sendNum:%d workFd:%d ackNum:%x seqNum:%x nextAckNum:%x  nextSeqNum:%x\n",
                              flow_, sendNum ,  workFd_, ackNum_, seqNum_, nextAckNum_, nextSeqNum_);
#endif

    if(sendNum < 0)
    {
        httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[ComTcp sendFin] sendNum:%d\n", sendNum);
        return -1;
    }
    return 1;
}

int HttpMsg::sendAck(int dataNum)
{
    nextAckNum_ += dataNum;
    //TODO 也需要组TVL包。
    unsigned char packet[sizeof(DATA_HEADER) + sizeof(struct iphead) + sizeof(struct tcphead)];
    memset(packet, 0, sizeof(packet));
    DATA_HEADER * rspHead;
    struct iphead* ip;
    struct tcphead* tcp;
    rspHead = (DATA_HEADER *)packet;
    ip = (struct iphead*)(packet + sizeof(DATA_HEADER));
    tcp = (struct tcphead*)(packet + sizeof(DATA_HEADER) + sizeof(struct iphead));

    rspHead->version = 1;
    rspHead->commandcode = REQ_AP_GW_BUSINESS;
    rspHead->tun_id = srcPort_;
    rspHead->host_ip = htonl(srcIp_);

    ip->ip_hl = 5;
    ip->ip_version = 4;
    ip->ip_tos = 0;
    ip->ip_len = htons(sizeof(struct iphead) + sizeof(struct tcphead));
    ip->ip_id = htons(ipId_); // random()
    ip->ip_off = htons(0x4000);
    ip->ip_ttl = 64;
    ip->ip_pro = IPPROTO_TCP;
    ip->ip_src = srcIp_;
    ip->ip_dst = webIp_;
    ip->ip_sum = inChksum((unsigned short *)packet, 20); 

    //这里的seq和ACK都还是上一次发送的ACk和seq
    tcp->tcp_sport = htons(srcPort_);
    tcp->tcp_dport = htons(webPort_);
    tcp->tcp_seq = htonl(nextSeqNum_);//每次在  发送数据的时候更新
    tcp->tcp_ack = ntohl(nextAckNum_);
    lastSeqNum_ = nextAckNum_;
    tcp->tcp_len = 5;  //发送SYN报文段时，设置TCP首部长度为20字节
    tcp->tcp_off = 0;
    tcp->tcp_flag = 0x10;  
    tcp->tcp_win = htons(32768);
    tcp->tcp_urp = htons(0);

    /*设置tcp伪首部，用于计算TCP报文段校验和*/
    struct psdhead psd;
    psd.saddr = srcIp_; //源IP地址
    psd.daddr = webIp_; //目的IP地址
    psd.mbz = 0;
    psd.ptcl = 6;  
    psd.tcpl = htons(20);

    unsigned char buffer[1000]; //用于存储TCP伪首部和TCP报文，计算校验码
    memcpy(buffer, &psd, sizeof(psd));
    memcpy(buffer+sizeof(psd), tcp, sizeof(struct tcphead));
    tcp->tcp_sum = inChksum((unsigned short *)buffer, sizeof(psd) + sizeof(struct tcphead));  //计算检验码
    int sendNum = sendto(workFd_, packet, htons(ip->ip_len) + sizeof(DATA_HEADER), 0,(struct sockaddr *)&cliAddr_, sizeof(cliAddr_));

#if DEBUG_NO
    httpBase_->log_.LOG_P_PID(LOG_DEBUG,
                              "[ComTcp sendAck()]flow:%d seq:%8x ack:%8x lastSeq:%8x nextSeq:%8x nextAck:%8x\n",
                                               flow_, seqNum_, ackNum_, lastSeqNum_, nextSeqNum_, nextAckNum_);
#endif

    if(sendNum < 0)
    {
        httpBase_->log_.LOG_P_PID(LOG_DEBUG,"[ComTcp sendAck] sendACK error sendNum:%d flow:%d\n", sendNum, flow_);
        return -1;
    }

    return 1;
}

int HttpMsg::sendAck(int seqNum, int ackNum)
{
    //TODO 也需要组TVL包。
    unsigned char packet[sizeof(DATA_HEADER) + sizeof(struct iphead) + sizeof(struct tcphead)];
    memset(packet, 0, sizeof(packet));
    DATA_HEADER * rspHead;
    struct iphead* ip;
    struct tcphead* tcp;
    rspHead = (DATA_HEADER *)packet;
    ip = (struct iphead*)(packet + sizeof(DATA_HEADER));
    tcp = (struct tcphead*)(packet + sizeof(DATA_HEADER) + sizeof(struct iphead));

    rspHead->version = 1;
    rspHead->commandcode = REQ_AP_GW_BUSINESS;
    rspHead->tun_id = srcPort_;
    rspHead->host_ip = htonl(srcIp_);

    ip->ip_hl = 5;
    ip->ip_version = 4;
    ip->ip_tos = 0;
    ip->ip_len = htons(sizeof(struct iphead) + sizeof(struct tcphead));
    ip->ip_id = htons(ipId_); // random()
    ip->ip_off = htons(0x4000);
    ip->ip_ttl = 64;
    ip->ip_pro = IPPROTO_TCP;
    ip->ip_src = srcIp_;
    ip->ip_dst = webIp_;
    ip->ip_sum = inChksum((unsigned short *)packet, 20); 

    //这里的seq和ACK都还是上一次发送的ACk和seq
    tcp->tcp_sport = htons(srcPort_);
    tcp->tcp_dport = htons(webPort_);
    tcp->tcp_seq = htonl(seqNum);//每次在  发送数据的时候更新
    tcp->tcp_ack = ntohl(ackNum);
    tcp->tcp_len = 5;  //发送SYN报文段时，设置TCP首部长度为20字节
    tcp->tcp_off = 0;
    tcp->tcp_flag = 0x10;  
    tcp->tcp_win = htons(32768);
    tcp->tcp_urp = htons(0);

    /*设置tcp伪首部，用于计算TCP报文段校验和*/
    struct psdhead psd;
    psd.saddr = srcIp_; //源IP地址
    psd.daddr = webIp_; //目的IP地址
    psd.mbz = 0;
    psd.ptcl = 6;  
    psd.tcpl = htons(20);

    unsigned char buffer[1000]; //用于存储TCP伪首部和TCP报文，计算校验码
    memcpy(buffer, &psd, sizeof(psd));
    memcpy(buffer+sizeof(psd), tcp, sizeof(struct tcphead));
    tcp->tcp_sum = inChksum((unsigned short *)buffer, sizeof(psd) + sizeof(struct tcphead));  //计算检验码
    int sendNum = sendto(workFd_, packet, htons(ip->ip_len) + sizeof(DATA_HEADER), 0,(struct sockaddr *)&cliAddr_, sizeof(cliAddr_));

#if DEBUG_NO
    httpBase_->log_.LOG_P_PID(LOG_DEBUG,
                              "[ComTcp sendAck(1,2)]flow:%d seq_:%8x ack_:%8x seq:%8x ack:%8x lastSeq:%8x nextSeq:%8x nextAck:%8x seq和lastSeq不同发送ACK\n",
                                               flow_, seqNum_, ackNum_, seqNum, ackNum, lastSeqNum_, nextSeqNum_, nextAckNum_);

//    printf("[ComTcp sendAck(1,2)]flow:%d seq_:%8x ack_:%8x seq:%8x ack:%8x lastSeq:%8x nextSeq:%8x nextAck:%8x seq和lastSeq不同发送ACK\n",
 //                                flow_, seqNum_, ackNum_, seqNum, ackNum, lastSeqNum_, nextSeqNum_, nextAckNum_);
#endif

    if(sendNum < 0)
    {
        httpBase_->log_.LOG_P_PID(LOG_DEBUG,"[ComTcp sendAck] sendACK error sendNum:%d flow:%d\n", sendNum, flow_);
        return -1;
    }
    return 1;
}

bool HttpMsg::ckPage(uint8_t * recvBuf)
{
    if(NULL == (recvBuf + 40))//recvBuf直接为ip头开始   buff为TLV + IP + TCP 头.
    {
        httpBase_->log_.LOG_P_PID(LOG_DEBUG,"[ComTcp ckPage(1)]数据包长度不对。\n");
        return false;
    }
    /*校验接收到的IP数据报，重新计算校验和，结果应为0*/
    unsigned char ipheadlen = recvBuf[0]; //取出IP数据包的长度
    ipheadlen = (ipheadlen & 0x0f);   //IP首部长度字段只占该字节后四位
    ipheadlen *= 4; //四个字节为单位
    uint16_t ipLen = ntohs(*((unsigned short *)(recvBuf+2))); //获取IP数据报长度
    unsigned char tcpheadlen = recvBuf[32];  //获取TCP报文长度                  
    tcpheadlen = tcpheadlen >> 4;  //因为TCP报文长度只占该字节的高四位，需要取出该四位的值
    tcpheadlen *= 4;   //以四个字节为单位
    headLen_ = ipheadlen + tcpheadlen;
    dataLen_ = ipLen - ipheadlen - tcpheadlen;//拿到的数据部分的长度 /下次发包的时候要用到。
    uint32_t ackNum = ntohl(*((signed int*)(recvBuf+ipheadlen+8))); //每次拿到服务器发过来的确认号

    if(ackNum != nextSeqNum_) 
        //判断一下是不是自己想要收到的确认号 该确认号=上次发送时的序列号+data部分长度
    { 
#if DEBUG_YES
        httpBase_->log_.LOG_P_PID(LOG_DEBUG,"[ComTcp ckPage(1)]ackNum和seqNum没有通过 _ipLen:%d ipheadlen:%d tcpheadlen:%d _dataLen:%d ackNum:%x _seqNum:%x\n",
                                  ipLen, ipheadlen, tcpheadlen, dataLen_, ackNum, seqNum_);
#endif
        return false;
    }
    else
    {
        seqNum_ = ntohl(*((signed int*)(recvBuf+ipheadlen+4))); //每次拿到服务器发过来的序列号
        //ackNum_ = ntohl(*((signed int*)(recvBuf+ipheadlen+8))); //每次拿到服务器发过来的确认号
        if(recvBuf[33] == 0x11) //0x11 表示FIN和ACK
        {
            nextAckNum_ = ntohl(*((unsigned int*)(recvBuf+ipheadlen+4))) + dataLen_ + 1; 
#if DEBUG_YES
            httpBase_->log_.LOG_P_PID(LOG_DEBUG,
                                      "[ComTcp ckPage]web FIN workFd:%d ackNum:%x seqNum:%x nextAckNum:%x  nextSeqNum:%x  dataLen:%d flow:%d\n",
                                      workFd_, ackNum_, seqNum_, nextAckNum_, nextSeqNum_, dataLen_, flow_);
#endif
        }
        else if(recvBuf[33] == 0x12) //0x12 表示SYN和ACK
        {
            nextAckNum_ = ntohl(*((unsigned int*)(recvBuf+ipheadlen+4))); 
#if DEBUG_YES
            httpBase_->log_.LOG_P_PID(LOG_DEBUG,
                                      "[ComTcp ckPage]web SYN workFd:%d ackNum:%x seqNum:%x nextAckNum:%x nextSeqNum:%x dataLen:%d flow:%d\n",
                                      workFd_, ackNum_, seqNum_, nextAckNum_, nextSeqNum_, dataLen_, flow_);
#endif
            sendAck(1);//对端的序列号 + 1

            //TODO  更新lastSeq
            lastSeqNum_ = nextAckNum_;  
            sendMsgToHttp();
        }
        else
        {
            nextAckNum_ = ntohl(*((unsigned int*)(recvBuf+ipheadlen+4))); //拿到的是对端发过来的系列号
            if(dataLen_ > 0)
            {
#if DEBUG_NO
                httpBase_->log_.LOG_P_PID(LOG_DEBUG,
                                          "[ComTcp    ckPage]seq:%8x ack:%8x lastAck:%8x nextSeq:%8x nextAck:%8x Len:%4d flow:%d\n",
                                           seqNum_, ackNum_, ackNum_, nextSeqNum_, nextAckNum_, dataLen_, flow_);
#endif
            }
#if DEBUG_NO
            httpBase_->log_.LOG_P_PID(LOG_DEBUG,"[ComTcp ckPage(1)] ipLen_:%d tcpheadlen:%d ipheadlen:%d headLen:%d dataLen_:%d\n",
                                      ipLen,  tcpheadlen, ipheadlen, headLen_, dataLen_);
            httpBase_->log_.LOG_P_PID(LOG_DEBUG,"[ComTcp ckPage(1)] srcIp:%lu srcPort:%u webIp:%lu, webPort:%d\n",
                                      srcIp, srcPort, webIp, webPort);
#endif
        }
        return true;
    }
}

int HttpMsg::tcpConn()
{
    if(conn() == -1)
    {
        printfMess();
        httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[ComTc tcpConn] 三次握手失败...\n");
        return -1;
    }
    return  1;
}

void HttpMsg::printfMess()
{
    printf("[ComTcp printfMes]seq:%8x ack:%x webip:%lu webPort:%5u srcIp:%lu srcPort:%5u cliIp:%lu cliPort:%5u _cliFd:%d cliID_:%ld flow:%d\n",
           seqNum_, ackNum_, webIp_, webPort_, srcIp_, srcPort_, cliIp_, cliPort_, workFd_, cliID_, flow_);
    httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[ComTcp printfMes]seq:%8x ack:%x webip:%lu webPort:%5u srcIp:%lu srcPort:%5u cliIp:%lu cliPort:%5u _cliFd:%u cliID:%ld flow:%d\n",
                              seqNum_, ackNum_, webIp_, webPort_, srcIp_, srcPort_, cliIp_, cliPort_, workFd_, cliID_, flow_);
}

#if 1 //send相关函数

int HttpMsg::sendMsgToCli()
{
    int tmpLen = blob_->len;
    int buffLen = 0;
    int sendLen = 0;
    int httpDataLen = 0;
    char * pDataPos = NULL; //记录发送的开始位置
    pDataPos = blob_->data;
    httpDataLen = MTUSIZE - 40 - sizeof(DATA_HEADER) - 48; //单次发送的最大数据长度.
    if(blob_->data == NULL || blob_->len < 0)
        return -1;
    if(httpDataLen  > tmpLen) //小数据包直接发走
    {
        memset(buff_, 0, sizeof buff_);
        buffLen = comPage(buff_, blob_->data, blob_->len);
        sendLen = ::sendto(workFd_, buff_, buffLen, 0, (struct sockaddr*)&cliAddr_, sizeof(cliAddr_)); 
        if(sendLen > 0)
        {
#if DEBUG_NO
            httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg sendMsgToCli]小数据包cliIp:%u cliPort:%u sendLen:%d flow:%d\n",
                                      cliIp_, cliPort_, sendLen, flow_);
#endif
            setHttpTime();
            recvSumDataLen_ += tmpLen;
            return sendLen;
        }
        else
        {
            perror("sendto");
            httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg sendMsgToCli]sendto client error  sendLen:%d flow:%d\n", sendLen, flow_);
            return  -1;
        }
    }
    else
    {
        int sendOverNum = 0;
        while(httpDataLen < tmpLen) //如果长度大于要发送的长度
        {
            memset(buff_, 0, sizeof buff_);
            buffLen = comPage(buff_, pDataPos, httpDataLen);
            sendLen = ::sendto(workFd_, buff_, buffLen, 0, (struct sockaddr*)&cliAddr_, sizeof(cliAddr_)); 
            if(sendLen > 0)
            {
#if DEBUG_NO
                httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg sendMsgToCli]连续发送数据给web cliIp:%u cliPort:%u sendLen:%d tmpLen:%d flow:%d\n",
                                          cliIp_, cliPort_, sendLen, tmpLen, flow_);
#endif
                tmpLen -= httpDataLen;
                pDataPos += httpDataLen; //更新发送的起止位置
                sendOverNum += httpDataLen;
                recvSumDataLen_ += httpDataLen;
                setHttpTime();
            }
            else
            {
                perror("sendto");
                httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg sendMsgToCli]sendto client error  sendLen:%d flow:%d\n", sendLen, flow_);
                return  -1;
            }
        }
        memset(buff_, 0, sizeof buff_);
        buffLen = comPage(buff_, pDataPos, tmpLen);
        sendLen = ::sendto(workFd_, buff_, buffLen, 0, (struct sockaddr*)&cliAddr_, sizeof(cliAddr_)); 
        if(sendLen > 0)
        {
            sendOverNum += tmpLen;
            recvSumDataLen_ += tmpLen;
#if DEBUG_NO
            httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg sendMsgToCli]连续发送完毕.. cliIp:%u cliPort:%u sendLen:%d sendOverNum:%d flow:%d\n",
                                      cliIp_, cliPort_, sendLen, sendOverNum, flow_);
#endif
            setHttpTime();
            return  sendOverNum;
        }
        else
        {
            perror("sendto");
            httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg sendMsgToCli]sendto client error  sendLen:%d flow:%d\n", sendLen, flow_);
            return  -1;
        }
    }
}

int HttpMsg::sendMsgToHttpErr()
{
    int ret = 0;
    blob_type release_cmd;
    char buff[10];
    bzero(&buff, sizeof(buff));
    buff[0] = 0x5;
    buff[1] = 0x4;
    buff[2] = 0x0;
    buff[3] = 0x1;
    memcpy(buff + 4,&srcIp_, 4); 
    memcpy(buff + 8,&srcPort_, 2);
    release_cmd.data = buff;
    release_cmd.len = sizeof(buff);
    ret = commu_->sendto(flow_, &release_cmd, (void*)httpBase_);
#if DEBUG_YES
    httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg sendMsgToHttpErr]socks5认证最后一个阶段失败 ret:%d flow:%d\n", ret, flow_);
#endif
    if(0 != ret)
    {
        httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg sendMsgToHttpErr]发送消息给flow错误, ret:%d flow:%d\n", ret, flow_);
        return ret;
    }
    return  ret;
}

int HttpMsg::sendMsgToHttp()
{
    int ret = 0;
    blob_type release_cmd;
    char buff[10];
    bzero(&buff, sizeof(buff));
    buff[0] = 0x5;
    buff[1] = 0x0;
    buff[2] = 0x0;
    buff[3] = 0x1;
    memcpy(buff + 4,&srcIp_, 4); 
    memcpy(buff + 8,&srcPort_, 2);
    release_cmd.data = buff;
    release_cmd.len = sizeof(buff);
    ret = commu_->sendto(flow_, &release_cmd, (void*)httpBase_);
#if DEBUG_YES
    httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg sendMsgToHttp]socks5认证最后一个阶段成功发送内容为:%x\n", buff);
#endif
    if(0 != ret)
    {
        httpBase_->log_.LOG_P_PID(LOG_DEBUG, "send response error, ret:%d flow:%d\n", ret, flow_);
        return ret;
    }
    return  ret;
}

int HttpMsg::sendDataToShmOver()
{
    if(dataList_.empty())
        return 0;
    blob_type sendShmData;
    int sendDataLen = 0;
    for(auto & iter : dataList_)
    {
        memset(&sendShmData, 0, sizeof(sendShmData));
        Node node = iter;
        sendShmData.data = (char*)node.data;
        sendShmData.len = node.dataLen_; // 长度 = 总长度 - TVL  - IP - TCP
        sendDataLen += sendShmData.len;
        commu_->sendto(flow_, &sendShmData,(void*)httpBase_);
    }
    httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg sendToDataListTwo]发送剩余的数据到Shm。tmpData:%d\n", sendDataLen);
    dataList_.clear();
    sendSumDataLen_ += sendDataLen;
    return sendDataLen;
}

int HttpMsg::sendMsgToShm()
{
    if(dataList_.empty())
        return -1;

    blob_type sendShmData;
    uint32_t sendDataLen = 0;
    //TODO 每次需要发送数据的时候都要检查看里面的数据对不对....只能发送连续的数据，不连续的就不能发送....
    //比如：1 2 3 4  5 五个包    收到的顺序是 2 4 5 1 3  那么收到 1 的时候只能发走1 2 三四留着... 等待 3 来了以后才发走....
    uint32_t nextSeq = 0; 
    uint16_t sendNum = 0;
    uint32_t nodeOneSeq = 0;
    auto tmpIter = dataList_.begin();
    nodeOneSeq = tmpIter->seqNum_; //
    for(auto & iter : dataList_) //发送前检查包的顺序和完整性  得到需要发送几个包有序的包
    {
        if(iter.seqNum_ == nodeOneSeq)
        {
            nextSeq = iter.seqNum_ + iter.dataLen_;//得到第二个seq的值。
            sendNum++; 
            continue;
        }
        if(nextSeq == iter.seqNum_) //判断上次存储的seq是不是等于本次的seq
        {
            sendNum++;  //得到需要发送多个到http
            nextSeq += iter.dataLen_; //更新下一个seq的值
            continue;
        }
        else
            break;
    }
    for(auto iter = dataList_.begin(); iter != dataList_.end();)
    {
        if(sendNum > 0) //发送符合顺序的数据//发走前面的几个...
        {
            memset(&sendShmData, 0, sizeof(sendShmData));
            Node node = *iter;
            sendShmData.data = (char*)node.data;
            sendShmData.len = node.dataLen_; // 长度 = 总长度 - TVL  - IP - TCP
            sendDataLen += node.dataLen_;
            commu_->sendto(flow_, &sendShmData,(void*)httpBase_);
            dataListSend_.insert(*iter);
            iter = dataList_.erase(iter); 
            sendNum--;
            continue;
        }
        break;
    }
    sendSumDataLen_ += sendDataLen;
#if DEBUG_NO
    httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg sendHttp]发送符合条件的数据到Shm。Len:%d flow:%d\n", sendDataLen, flow_);
#endif
    return  sendDataLen;
}

int HttpMsg::sendMsgToShmOne(uint8_t * buff, uint16_t len)
{
    blob_type sendShmData;
    sendShmData.data = (char*)buff;
    sendShmData.len = len;
    int ret = commu_->sendto(flow_, &sendShmData, (void*)httpBase_);
    sendSumDataLen_ += len;
    sendSumDataLen_ += len;
    if(ret < 0 )
        httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg sendMsgToShmOne]发送shm error ret:%d dataLen:%d flow:%d\n", ret, len, flow_);
#if DEBUG_NO
    httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg sendMsgToShmOne]flow:%d单次发送数据到Shm ret:%d dataLen:%d\n", flow_, ret, len);
#endif
    return  sendShmData.len;
}

void HttpMsg::sendMsgToShmOver()
{
    blob_type sendShmData;
    memset(&sendShmData, 0, sizeof(sendShmData));
    sendShmData.data = NULL;
    sendShmData.len = 0; 
    commu_->sendto(flow_, &sendShmData, (void*)httpBase_);
    httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg sendMsgToShmOver]让proxy断开http连接 flow:%d\n", flow_);
}

#endif

#if 1 //get相关内容

int HttpMsg::getDataListNum()
{
    return dataList_.size();
}

uint32_t HttpMsg::getNextSeq()
{
    return nextSeqNum_;
}

uint16_t HttpMsg::getDataLen()
{
    return dataLen_;
}

bool HttpMsg::getIsFin()
{
    return isFin_;
}

uint32_t HttpMsg::getFlow()
{
    return flow_;
}

CTCommu * HttpMsg::getCommu()
{
    return commu_;
}

CServerBase * HttpMsg::getBase()
{
    return httpBase_;
}

long HttpMsg::getHttpTime()
{
    return httpTime_;
}

int16_t HttpMsg::getHeadLen()
{
    return headLen_;
}


uint32_t HttpMsg::getAckNum()
{
    return ackNum_; //返回的是上一次的ACK
}

uint32_t HttpMsg::getLastSeqNum()
{
    return lastSeqNum_;
}

blob_type * HttpMsg::getBlobType()
{
    return blob_;
}

#endif

#if 1 //set相关的内容

void HttpMsg::setNextSeq(uint32_t nextSeq)
{
    nextSeqNum_ = nextSeq;
}

int HttpMsg::setComMsg(uint64_t webIp,
                       uint16_t webPort, 
                       uint64_t srcIp, 
                       uint16_t srcPort, 
                       uint32_t seqNum)
{
    webIp_ = webIp;
    webPort_ = webPort;
    srcPort_ = srcPort;
    srcIp_ = srcIp;
    seqNum_ = seqNum;
    nextSeqNum_ = seqNum;

#if DEBUG_NO
    httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg setFlowMsg] webIp:%ld webPort:%d srcIp:%ld srcPort:%d seqNum:%d\n",
                              webIp, webPort, srcIp, srcPort, seqNum);
#endif

    return 0;
}

void HttpMsg::setCliMsg(uint64_t cliIp, 
                        uint16_t cliPort,
                        uint32_t workFd,
                        uint64_t cliId)
{
    cliIp_ = cliIp;
    cliPort_ = cliPort;
    workFd_ = workFd;
    cliID_ = cliId;
    bzero(&cliAddr_, sizeof(cliAddr_));
    cliAddr_.sin_family = AF_INET;
    cliAddr_.sin_port = htons(cliPort_);
    cliAddr_.sin_addr.s_addr = cliIp_;

#if DEBUG_NO
    httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg setFlowMsg] cliIp:%ld cliPort:%d workFd:%d cliId:%ld\n",
                              cliIp, cliPort, workFd, cliId);
#endif
}

int HttpMsg::setFlowMsg(uint32_t flow, 
                        void * arg1, 
                        void * arg2)
{
    if(arg1 == NULL || arg2 == NULL)
        return -1;
    flow_ = flow;    
    blob_ = (blob_type *)arg1;
    commu_ = (CTCommu *)blob_->owner;
    httpBase_ = (CServerBase *)arg2;    

#if DEBUG_NO
    httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg setFlowMsg] flow:%d\n", flow);
#endif

    return 0;
}


void HttpMsg::setIsFin(bool isFin)
{
    isFin_ = isFin;
}

void HttpMsg::setHttpTime()
{
    httpTime_ = time(NULL);
}

uint16_t HttpMsg::inChksum(uint16_t * addr, int len)
{
    int nleft = len;
    uint32_t sum = 0;
    uint16_t *w = addr;
    uint16_t answer = 0;
    while(nleft > 1)
    {
        sum+= *w++;
        nleft -= 2;
    }
    if(nleft ==1)
    {
        *(unsigned char *)(&answer) = *(unsigned char *)w;
        sum += answer;
    }
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = ~sum;
    return answer;
}

void HttpMsg::pushData(uint8_t * buff, uint16_t len)
{
    Node node(len, buff, seqNum_);
    dataList_.insert(node);
}

void HttpMsg::setIsDataOver(bool isDataOver)
{
    isDataOver_= isDataOver;
}

void HttpMsg::setIsPageOk(bool isPageOk)
{
    isPageOk_ = isPageOk;
}

void HttpMsg::setAck(uint32_t ackNum)
{
    ackNum_ = ackNum;
}

void HttpMsg::setLastSeq(uint32_t seqNum)
{
    lastSeqNum_ = seqNum;
}

void HttpMsg::coutMsg()
{
    httpBase_->log_.LOG_P_PID(LOG_DEBUG, "[HttpMsg coutMsg]flow:%d 超时 seq:%8x ack:%8x nextSeq:%8x nextAck:%8x lastSeq:%8x\n",
                          flow_, seqNum_, ackNum_, nextSeqNum_, nextAckNum_, lastSeqNum_);
    printf("[HttpMsg coutMsg]flow:%d 超时 seq:%8x ack:%8x nextSeq:%8x nextAck:%8x lastSeq:%8x\n",
                          flow_, seqNum_, ackNum_, nextSeqNum_, nextAckNum_, lastSeqNum_);
}

#endif


