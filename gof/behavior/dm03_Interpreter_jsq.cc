/*************************************************************************
  @FileName: dm03_Interpreter_jsq.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Fri 22 May 2020 04:21:08 PM CST
 ************************************************************************/
#include <iostream>
using namespace std;

/*
 * 意图：给定一个语言，定义它的文法的一种表示，并定义一个解释权
 *       这个解释器使用该表示来解释语言中的句子。
 *
 * 适用性：
 *      当有一个语言需要解释执行，并且你可将语言中的句子表示为一个抽象语法树使，可使用解释器模式
 *
 * */

class Context
{
public:
    Context(int num):num_(num)
    {}

    int getNum()
    {
        return num_;
    }
    int getRes()
    {
        return res_;
    }

    void setNum(int num)
    {
        num_ = num;
    }

    void setRes(int res)
    {
        res_ = res;
    }
private:
    int num_;
    int res_;
};


class Expression
{
public:
    virtual void interpreter(Context * pContext) = 0;

private:
    Context * pContext_;
};

class PlusExpression : public Expression
{
public:
    PlusExpression()
    {
        pContext_ = NULL;
    }

    virtual void interpreter(Context * pContext)
    {
        int num = pContext->getNum();
        num ++;
        pContext->setNum(num);
        pContext->setRes(num);
    }
private:
    Context * pContext_;
};

class MinusExpression : public Expression
{
public:
    MinusExpression()
    {
        pContext_ = NULL;
    }

    virtual void interpreter(Context * pContext)
    {
        int num = pContext->getNum();
        num--;
        pContext->setNum(num);
        pContext->setRes(num);
    }
private:
    Context * pContext_;
};

int main()
{

    Expression  * pExpressionOne = NULL;
    Context * pContext = NULL;

    Expression  * pExpressionTwo = NULL;

    pContext = new Context(10);

    cout << pContext->getNum() << endl;

    pExpressionOne = new PlusExpression;
    pExpressionOne->interpreter(pContext);

    cout << pContext->getRes() << endl;



    pExpressionTwo = new MinusExpression;
    pExpressionTwo->interpreter(pContext);
    cout << pContext->getRes() << endl;

    std::cout << "Hello world" << std::endl;
    return 0;
}

