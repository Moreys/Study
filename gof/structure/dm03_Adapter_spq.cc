/*************************************************************************
  @FileName: dm03_Adapter_spq.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Sun 10 May 2020 08:31:54 PM CST
 ************************************************************************/
#include <my_head.h>
#include <iostream>
/*
 *适配器模式
        可以改变已有类（或外部类) 的接口形式

    适用于：
            将一个类的接口转化成客户端希望的另一个接口
            使得原本由于接口不兼容而不能一起工作的哪些类可以一起工作

            虚线
    Client------->Target(客户所期待的接口，可以是具体的抽象类，也可以是接口)
                   / \
                    |
                    |   实线
                Adapter------->Adsptee(需要适配的类)
        (内部包装一个Adaptee对象 把源接口转换成目标接口)

 * */



// Current18
// Current220
// Adapter
//
class Current18v
{
public:
    virtual void useCurrent18v() = 0;
};

class Current220v
{
public:
    void useCurrent220v()
    {
        cout << "I a 220v " << endl;
    }
};

class Adapter : public Current18v //让18v去适配220v
{
public:
    Adapter(Current220v * current):current_(current)
    {

    }

    virtual void useCurrent18v()
    {
        cout << "适配器  适配  220v" << endl;
        current_->useCurrent220v();
    }

private:
    Current220v * current_;
};

int main()
{
    Current220v * pCurrent220v = NULL;
    Adapter * pAdapter = NULL;

    pCurrent220v = new Current220v;

    pAdapter = new Adapter(pCurrent220v);
    pAdapter->useCurrent18v();


    delete pCurrent220v;
    delete  pAdapter;

    std::cout << "Hello world" << std::endl;
    return 0;
}

