/*************************************************************************
  @FileName: dm07_Proxy_dl.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Wed 20 May 2020 03:42:43 PM CST
 ************************************************************************/
#include <iostream>
using namespace std;

/*
 * 意图 ： 为其他对象提供一种代理以控制对这个对象的访问。
 *
 * 适用性
 *      远程代理：为一个对象在不同的地址空间提供局部代表 
 *      虚代理： 根据需要创建开销很大的对象
 *      保护代理： 控制对原始对象的访问，保护代理用于对象应该有不同的访问权限的时候
 *      只能指引：取代了简单的指针，它在访问对象时执行一些附加操作
 *          对指向实际对象的引用计数，这样当该对象没有引用时，可以自动释放它
 *          当第一次引用一个持久化对象，将它装入内存
 *          在访问一个实际对象钱 检查是否已经锁定了它 以确保其他对象不能改变它 
 * */


class Subject
{
public:
    virtual void saibook() = 0;
};


class RealSubjectBook : public Subject
{
public:
    virtual void saibook()
    {
        cout << "读书" << endl;
    }
};

class dangdangProxy : public Subject
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
        cout << "双十一打折" << endl;
    }
private:
    Subject * subject_;
};

int main()
{
    Subject * s = new dangdangProxy;
    s->saibook();
    delete s;
    std::cout << "Hello world" << std::endl;
    return 0;
}

