/*************************************************************************
  @FileName: dm02_Decorator_zsq.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Sun 10 May 2020 08:16:19 PM CST
 ************************************************************************/
#include <my_head.h>
#include <iostream>
/*
 * 装饰器模式:通过一种对客户端透明的方式来扩展对象的功能是继承关系的一个替换方案
 *      把添加的附加功能分别放在单独的类中，并让这个类包含它要装饰的对象
 *
 * 适用于：
 *      装饰模式  动态的给一个对象添加一些额外的职责，就增加功能来说，
 *      此模式比生成子类更为灵活
 * */



class Car
{
public:
    virtual void show() = 0;
};

class RunCar : public Car
{
public:
    virtual void show()
    {
        cout << "可以跑" << endl;
    }
};


class SwimCarDirector : public Car
{
public:
    SwimCarDirector(Car * car)
        :car_(car)
    {

    }

    void swim()
    {
        cout << " 可以游泳" << endl;
    }

    virtual void show()
    {
        car_->show();
        swim();
    }
private:
    Car * car_; //需要装饰的对象。
};


class FlyCarDirector : public Car
{
public:
    FlyCarDirector(Car * car) : car_(car)
    {
        
    }

    void fly()
    {
        cout << " 可以飞" << endl;
    }

    virtual void show()
    {
        car_->show(); //执行原来的
        fly();   //执行新的功能
    }
private:
    Car  * car_;
};


int main()
{
    Car * myCar = NULL;

    myCar = new RunCar;
    myCar->show();

    cout << "0000000000" << endl;

    FlyCarDirector * flyCar = new FlyCarDirector(myCar);
    flyCar->show();
    cout << "1111111111111" << endl;

    SwimCarDirector * swimCar = new SwimCarDirector(flyCar);
    swimCar->show();
    cout << "2222222222222" << endl;

    delete  myCar;
    delete  flyCar;
    delete  swimCar;

    std::cout << "Hello world" << std::endl;
    return 0;
}

