/*************************************************************************
  @FileName: dm09_Strategy_cl.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Tue 26 May 2020 05:39:24 PM CST
 ************************************************************************/
#include <iostream>
#include <string>
using namespace std;

/* 意图：定义一系列的算法，把他们一个个封装起来，并且使他们可相互替换
 *       本模式使得算法可独立于使用他的客户而变化...STL的算法
 *
 *  适用性：1、许多相关的类仅仅是行为有不同，“策略”提供了一种多个行为中的一个行为配置一个类的方法
 *          2、需要使用一个算法的不同变体，例如，你可能会定义一些反映不同的空间/时间权衡的
 *              算法，当这些变体实现为一个算法的类层次时，可以使用策略模式
 *          3、算法使用客户端不应该知道的数据，可使策略模式避免暴露复杂的，与算法的数据结构
 *          4、一个类定义了多种行为，并且这些行为在类的操作中以多个条件语句的形式出现
 *              将相关的条件分支移入他们各自的Strategy类中以替代这些条件。
 *
 * */


//对称加密  速度快  加密大数据块文件 
//非对称加密   加密速度慢  加密强度高   安全性高

class Strategy
{
public:
    virtual void crypt() = 0;
};


class AES : public Strategy
{
public:
    virtual void crypt()
    {
        cout << "AES加密算法" << endl;
    }
};


class DES : public Strategy 
{
public:
    virtual void crypt()
    {
        cout << "DES加密算法" << endl;
    }
};

class Context
{
public:
    void setStrategy(Strategy * pStrategy) 
    {
        pStrategy_ = pStrategy;
    }

    void myOperator()
    {
        pStrategy_->crypt();
    }
private:
    Strategy *  pStrategy_;
};

int main()
{
    Strategy * pStrategy = NULL;

    pStrategy = new AES;
    Context * pContext = new Context; //在他的内部实现  
    pContext->setStrategy(pStrategy);
    pContext->myOperator();

    delete pStrategy;
    delete pContext;

    std::cout << "Hello world" << std::endl;
    return 0;
}

