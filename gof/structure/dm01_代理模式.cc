/*************************************************************************
  @FileName: dm09_代理模式.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Mon 20 Apr 2020 11:56:11 PM CST
 ************************************************************************/
#include <my_head.h>
#include <iostream>


//抽象主题角色
//真实主题与代理主题共同的接口  从这里进入
class Subject
{
public:
    virtual void saibook() = 0;
};


//真实意图    定义了代理角色所代表的真实对象
class RealSubjectBook : public Subject
{
public :
    virtual void saibook()
    {
        cout << "read book" << endl;
    }
};

//对真实主题角色的引用    代理角色在将客户端调用传递给真的主题对象之前  或者  之后执行某些操作
//而不是单纯返回真实的对象。
class DDProxy : public Subject
{
public:
    virtual void saibook()
    {
        RealSubjectBook * rsb = new RealSubjectBook;
        dazhe();
        rsb->saibook();
        dazhe();
    }
    void dazhe()
    {
        cout << "suanshiyidaze" << endl;
    }
private:
    Subject * pSuject_;
};

int main()
{
    Subject * pS = new DDProxy;
    pS->saibook();
    delete pS;
    std::cout << "Hello world" << std::endl;
    return 0;
}

