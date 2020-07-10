/*************************************************************************
  @FileName: dm10_Template_Method_mb.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Wed 27 May 2020 11:40:08 PM CST
 ************************************************************************/
#include <iostream>
#include <string>
using namespace  std;

/*
 * 意图：定义一个操作中的算法骨架，而将一些步骤延迟到子类中，
 *       使得子类可以改变一个算法的结构即可重定义该算法的某些特定步骤。
 *
 *
 *  适用性：
 *      一次性实现一个算法的不变的部分，并将可变的行为留给子类来实现。
 *      各子类中公共的行为被提取出来
 *
 *      控制子类扩展，模板方法只在特点调用“hook” 操作  这样就只允许在这些点进行扩展
 *
 * */


class MakeCar
{
public:
    virtual void MakeHead() = 0;
    virtual void MakeBody() = 0;
    virtual void MakeTail() = 0;
public:
    void Make()
    {
        MakeHead();
        MakeBody();
        MakeTail();
    }
};

class Jeep : public MakeCar
{
public:
    virtual void MakeHead()
    {
        cout << " jeep head" << endl;
    }
    virtual void MakeBody()
    {
        cout << "jeep body" << endl;
    }
    virtual void MakeTail()
    {
        cout << "jeep tail" << endl;
    }
};


class Bus : public MakeCar
{
public:
    virtual void MakeHead()
    {
        cout << "Bus head" << endl;
    }
    virtual void MakeBody()
    {
        cout << "bus Body" << endl;
    }
    virtual void MakeTail()
    {
        cout << "Bus Tail" << endl;
    }
};




int main()
{

    MakeCar * pCar = new Bus;
    pCar->Make();
    delete pCar;

    MakeCar * pCarOne = new Jeep;
    pCarOne->Make();
    delete pCarOne;



    std::cout << "Hello world" << std::endl;
    return 0;
}

