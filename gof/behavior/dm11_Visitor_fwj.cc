/*************************************************************************
  @FileName: dm11_Visitor_fwj.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Thu 28 May 2020 12:11:25 AM CST
 ************************************************************************/
#include <iostream>
#include <list>
using namespace  std;

/*
 * 意图： 表示一个作用于某个对象结构中的个各个元素的操作。它使你可以在不改变
 *         各元素的类的前提下定义作用于这些元素的新操作
 *
 *  适用于：
 *      1、一个对象结构包含很多类对象，他们有不同的接口，而你想对这些对象实施一些依赖于其具体类的操作
 *      2、需要对一个对象结构中的对象进行很多不同的并且不相关的操作，而你想避免让这些操作“污染”这些对象的类，
 *        访问者模式使得你可以将相关的操作集中起来定义在一个类中
 *        当该对象结构被很多应用共享时，用visitor模式让每个应用包含需要用到的操作
 *      3、定义对象结构的类很少变化，但经常要在此结构上定义新的操作， 改变对象结构需要重定义对所有访问者的结构可能
 *        需要很大的代价，如果对象结构经常改变，那么可能还是在这些类中定义这些操作比较好
 * */

class ParkElement;

class Visitor
{
public:
    virtual void visit(ParkElement * pParkelement) = 0;
};

class ParkElement
{
public:
    virtual void accept(Visitor * pVisit) = 0;
};


class ParkA : public ParkElement
{
public:
    virtual void accept(Visitor * pV)
    {
        pV->visit(this);
    }
};

class ParkB : public ParkElement
{
public:
    virtual void accept(Visitor * pV)
    {
        pV->visit(this);
    }
};

class Park : public ParkElement
{
public:
    Park()
    {
        lists_.clear();
    }

    void setParkElement(ParkElement * pE)
    {
        lists_.push_back(pE);
    }
public:
    virtual void accept(Visitor * pV)
    {
        for(auto & iter : lists_)
        {
            iter->accept(pV);
        }
    }

private:
    list<ParkElement *> lists_;
};


class VisitorA : public Visitor
{
public:
    virtual void visit(ParkElement * pParkelement)
    {
        cout << "清洁工A 完成 公园A部分的打扫" << endl;
    }
};

class VisitorB : public Visitor
{
public:
    virtual void visit(ParkElement * pParkelement)
    {
        cout << "清洁工B 完成 公园b分的打扫" << endl;
    }
};


class ManagetVisitor : public Visitor
{
public:
    virtual void visit(ParkElement * pParkelement)
    {
       cout << "管理者访问公园的各个部分" << endl; 
    }
};

void One()
{
    //两个访问者  还可以进一步抽象 
    Visitor * pVA = new VisitorA;
    Visitor * pVB = new VisitorB;

    ParkA * pParkA = new ParkA;
    ParkB * pParkB = new ParkB;


    pParkA->accept(pVA);
    pParkB->accept(pVB);


    delete pVA;
    delete pVB;

    delete  pParkA;
    delete pParkB;
}

void Two()
{
    Visitor * pVM = new ManagetVisitor;
    
     Park * pPK  = new Park;

     ParkElement * pPE1 = new ParkA;
     ParkElement * pPE2 = new ParkB;

     pPK->setParkElement(pPE1);
     pPK->setParkElement(pPE2);

     pPK->accept(pVM);

     delete pPE1;
     delete pPE2;
     delete pPK;
     delete pVM;

}

int main()
{
    //通过一个访问者去访问具体的方法  把基类传递进去
    One();
    std::cout << "Hello world" << std::endl;
    return 0;
}

