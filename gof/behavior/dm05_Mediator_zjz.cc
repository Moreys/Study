/*************************************************************************
  @FileName: dm05_Mediator_zjz.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Mon 25 May 2020 04:59:37 PM CST
 ************************************************************************/
#include <iostream>
#include <string>
using namespace  std;

/*
 * 意图：用一个中介者来封装一系列的对象交互 中介者使各个对象
 *       不需要显式地相互引用，从而使其耦合松散，而且可以独立的改变他们之间的交互
 *
 *  适用性： 一组对象以定义良好但是复杂的方式进行通信产生的相互依赖关系结构混乱且难以理解
 *  想定一个对象引用其他对象并且直接与这些对象通信，导致难以复用该对象
 *  想定制一个分布在多个类中的行为，而又不想生成太多的子类
 *
 * */

namespace  One
{

class Person
{
public:
    Person(string name, int sex, int condi)
        : name_(name)
        , sex_(sex)
        , condi_(condi)
    {

    }

    string getName()
    {
        return name_;
    }

    int getSex()
    {
        return sex_;
    }

    int getCondi()
    {
        return condi_;
    }

    virtual void getParter(Person * p) = 0;

protected:
    string name_;
    int sex_;
    int condi_;
};

class Woman : public Person
{
public:
    Woman(string name, int sex, int condi)
        : Person(name, sex, condi)
    {

    }

    virtual void getParter(Person *p)
    {
        if(sex_ == p->getSex())
        {
            cout << "我不是同性恋" << endl;
        }
        if(getCondi() == p->getCondi())
        {
            cout << getName() << " 和 " << p->getName() << "绝配" << endl;
        }
        else
        {
            cout << getName() << " 和 " << p->getName() << "不配" << endl;
        }
    }

private:

};


class Man : public Person
{
public:
    Man(string name, int sex, int condi)
        : Person(name, sex, condi)
    {}

    virtual void getParter(Person * p)
    {
        if(sex_ == p->getSex())
        {
            cout << "我不是同性恋" << endl;
        }
        if(getCondi() == p->getCondi())
        {
            cout << getName() << " 和 " << p->getName() << "绝配" << endl;
        }
        else
        {
            cout << getName() << " 和 " << p->getName() << "不配" << endl;
        }
    }
};

}//end of namespace One

namespace  Two
{

class Mediator;

class Person
{
public:
    Person(string name, int sex, int condi, Mediator * pm)
        : name_(name)
        , sex_(sex)
        , condi_(condi)
        , pMediator_(pm)
    {

    }

    string getName()
    {
        return name_;
    }

    int getSex()
    {
        return sex_;
    }

    int getCondi()
    {
        return condi_;
    }

    virtual void getParter(Person * p) = 0;

protected:
    string name_;
    int sex_;
    int condi_;
    Mediator * pMediator_;
};

class Mediator
{
public:
    void setMan(Person * pMan)
    {
        pMan_ = pMan;
    }

    void setWoman(Person * pWoman)
    {
        pWoman_ = pWoman;
    }

    virtual void getParter()
    {
        if(pWoman_->getSex() == pMan_->getSex())
            cout << "我不是同性恋" << endl;
        if(pWoman_->getCondi() == pMan_->getCondi())
            cout << pWoman_->getName() << " 和 " << pMan_->getName() << "绝配" << endl;
        else
            cout << pWoman_->getName() << " 和 " << pMan_->getName() << "不配" << endl;

    }
private:
    Person * pMan_;
    Person * pWoman_;
};

class Woman : public Person
{
public:
    Woman(string name, int sex, int condi, Mediator * p)
        : Person(name, sex, condi, p)
    {

    }

    virtual void getParter(Person *p)
    {
        pMediator_->setMan(p);
        pMediator_->setWoman(this);
        pMediator_->getParter(); //找对象
    }
private:

};


class Man : public Person
{
public:
    Man(string name, int sex, int condi, Mediator * p)
        : Person(name, sex, condi, p)
    {}

    virtual void getParter(Person * p)
    {
        pMediator_->setMan(this);
        pMediator_->setWoman(p);
        pMediator_->getParter();
    }
};

}//end of namespace Two

using  namespace Two;
int main()
{


    //通过传递给中间的人去进行比对

    Mediator * pM = new Mediator;
    Person * xf = new Woman("小芳", 2, 5, pM);

    Person * pZS = new Man("张山", 1, 4, pM);

    Person * pLS = new Man("李四", 1, 5, pM);

    xf->getParter(pZS);

    xf->getParter(pLS);



    pZS->getParter(pLS);
    std::cout << "Hello world" << std::endl;
    return 0;
}

