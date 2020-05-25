/*************************************************************************
  @FileName: dm04_Decorator_zs.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Wed 20 May 2020 11:33:51 AM CST
 ************************************************************************/
#include <iostream>
using namespace std;

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
        cout << "can run" << endl;
    }
};

class SwimCarDirector : public Car
{
public:
    SwimCarDirector(Car * pCar):pCar_(pCar)
    {}

    void swin()
    {
        cout << " cam swin" << endl;
    }
    virtual void show()
    {
        pCar_->show(); //本来可以跑  
        swin();   //现在添加了可以游的功能
    }

private:
    Car * pCar_;
};

class FlyCarDirector : public Car
{
public:
    FlyCarDirector(Car * pCar):pCar_(pCar)
    {}

    void fly()
    {
        cout << "can fly" << endl;
    }

    virtual void show()
    {
        pCar_->show(); //本来可以跑
        fly();//现在添加飞的功能
    }

private:
    Car * pCar_;
};

int main()
{

    Car * pCar = NULL;  //基类汽车
    pCar = new RunCar(); //子类基础可以跑的汽车
    pCar->show();

    printf("111111\n");

    //在跑的基础上添加飞 
    FlyCarDirector * pFlyCar = new FlyCarDirector(pCar);
    pFlyCar->show();
    printf("222222222222\n");

    //在飞的基础上再次添加游
    SwimCarDirector * pSwimCar = new SwimCarDirector(pFlyCar);
    pSwimCar->show();

    /*
     * 都通过基类调用，
     * 每个功能的子类中都有基类的指针。
     * */

    delete pSwimCar;
    delete pFlyCar;
    delete pCar;
    std::cout << "Hello world" << std::endl;
    return 0;
}

