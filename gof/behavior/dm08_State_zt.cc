/*************************************************************************
  @FileName: dm08_State_zt.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Mon 25 May 2020 07:29:30 PM CST
 ************************************************************************/
#include <iostream>
using namespace std;

/*
 * 意图： 允许一个对象在其内部状态改变时改变它的行为，对象看起来似乎改变了它的类
 *
 * 适用性: 1、一个对象的行为取决于它的状态，并且它必须在运行时刻根据状态改变它的行为
 *         2、一个操作中含有庞大的多分支的条件语句，且这些分支依赖于该对象的状态，这个状态通常用一个或多个枚举
 *         常量独立的类中，这使得你可以根据对象的自身的情况将对象的状态作为一个对象，这一对象可以不依赖于其他的对象而独立变化
 * */

class Worker;

class State
{
public:
    virtual void doSomeThing(Worker * pw) = 0;
};

class Worker
{
public:
    Worker();
    int getHour()
    {
        return hour_;
    }

    void setHour(int hour)
    {
        hour_ = hour;
    }

    State * getCurrentState()
    {
        return currstate_;
    }

    void setCurrentState(State * pC)
    {
        currstate_ = pC;
    }

    void doSomeThing()
    {
        currstate_->doSomeThing(this);
    }
private:
    int hour_;
    State * currstate_;
};

class StateOne : public State
{
public:
    void doSomeThing(Worker * w);
};

class StateTwo : public State
{
public:
    void doSomeThing(Worker * w);
};

void StateOne::doSomeThing(Worker * w)
{
    if(w->getHour() == 7 || w->getHour() == 8)
    {
        cout << "吃早饭" << endl;
    }
    else
    {
        delete w->getCurrentState();  //状态1 不满足 要转到状态2
        w->setCurrentState(new StateTwo);
        w->getCurrentState()->doSomeThing(w);
    }
}

void StateTwo::doSomeThing(Worker * w)
{
    if(w->getHour() == 9 || w->getHour() == 10)
    {
        cout << "worker" << endl;
    }
    else
    {
        delete w->getCurrentState();  
        //状态2 不满足  要转到状态3  或者恢复到初始状态
        w->setCurrentState(new StateOne);
        cout << "当前时间：" << w->getHour() << endl;
    }
}

Worker::Worker()
{
    currstate_ = new StateOne;
}

int main()
{
    Worker * pw1 = new Worker;
    pw1->setHour(7);
    pw1->doSomeThing();

    pw1->setHour(9);
    pw1->doSomeThing();

    delete pw1;

    std::cout << "Hello world" << std::endl;
    return 0;
}

