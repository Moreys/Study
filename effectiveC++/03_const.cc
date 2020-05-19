/*************************************************************************
  @FileName: 03_const.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Wed 29 Apr 2020 01:05:18 PM CST
 ************************************************************************/
#include <my_head.h>
#include <iostream>


void prinT(const char * buff, int len)
{
    //buff[3] = 0x5;//error  //不能改变指向的值

    for(int i = 0; i < len; ++i)
    {
        //buff[i] = i; //error
        printf("%d\n",buff[i]);
    }
}

void setBuff(char *  buff, int len)
{
    for(int i = 0; i < len; ++i)
    {
        buff[i] = i;
    }
}


int main()
{
    char buff[12] = {0};
    strcpy(buff, "fkasdjkl");
    prinT(buff, sizeof(buff));
    setBuff(buff, 12);
    cout << "--------------" << endl;
    prinT(buff, sizeof(buff));


    std::cout << "Hello world" << std::endl;
    return 0;
}

