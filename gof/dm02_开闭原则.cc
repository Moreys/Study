/*************************************************************************
  @FileName: dm02_开闭原则.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Sun 12 Apr 2020 08:54:59 PM CST
 ************************************************************************/
#include <my_head.h>
#include <iostream>

class BankWorker
{
public:
    void save()
    {
        cout << "存款" << endl;
    }
    void moveM()
    {
        cout << "转账" << endl;
    }
    
    void panl()
    {
        cout << "支付" << endl;
    }
private:

};

class AbBankWord //框架
{
public:
    virtual void doThing() = 0;
};


class SaveBanker : public AbBankWord
{
public:
    virtual void doThing() //实现接口
    {
        cout << "SaveBanker 存款" << endl;
    }
};

class MoveBanker : public AbBankWord
{
public:
    virtual void doThing()
    {
        cout << "MoveBanker 转账" << endl; 
    }
};

class AdvMoveBanker : public MoveBanker
{
public:
    virtual void doThing()
    {
        cout << "AdvMoveBanker 批量转账" << endl;
    }
};

class AdvAdvMoveBanker : public MoveBanker
{
public:
    virtual void doThing()
    {
        cout << "自动化 批量转账" << endl;
    }
};

int mainOne() //正常使用
{
    BankWorker * pBw = new BankWorker;
    pBw->panl();
    pBw->moveM();
    pBw->save();
    delete pBw;
    std::cout << "Hello world" << std::endl;
    return 0;
}





void howDo(AbBankWord * pBw)
{
    pBw->doThing(); //有多态发送   哪个子类调用属于哪个子类专属的方法
}

int mainTwo() //正常使用
{
    AbBankWord * pBw = NULL; //接口给类  属于父类
    pBw = new MoveBanker;  //实现接口  并且继承接口
    pBw->doThing(); //父类指针指向子类对象
    delete pBw;

    pBw = new SaveBanker; //  另外一个子类对象  也继承父类
    pBw->doThing();     //
    delete pBw;


    //同一个父类指针   指向不同的子类对象  实现的是不同子类对象的方法 同一个函数
    std::cout << "Hello world" << std::endl;
    return 0;
}



int main() //正常使用
{
    AbBankWord * pBw = NULL; //接口给类  属于父类
    pBw = new MoveBanker;  //实现接口  并且继承接口
    howDo(pBw);
    delete pBw;

    pBw = new SaveBanker; //  另外一个子类对象  也继承父类
    howDo(pBw);
    delete pBw;

    pBw = new AdvMoveBanker;
    howDo(pBw);
    delete pBw;

    pBw = new AdvAdvMoveBanker; //这个类是后来的需求添加上来的.....但是框架依然能够调用
    howDo(pBw);  //可扩展   调用后来人写的代码.
    delete pBw;

    //同一个父类指针   指向不同的子类对象  实现的是不同子类对象的方法 同一个函数
    std::cout << "Hello world" << std::endl;
    return 0;
}
