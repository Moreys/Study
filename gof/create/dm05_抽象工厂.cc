/*************************************************************************
  @FileName: dm05_抽象工厂.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Mon 13 Apr 2020 10:19:16 PM CST
 ************************************************************************/
#include <my_head.h>
#include <iostream>

class Fruit
{
public:
    virtual void SayName() = 0;
};

class AbstractFactory
{
public:
    virtual Fruit * CreateBanana() = 0;//创建香蕉的抽象接口
    virtual Fruit * CreateApple() = 0; //创建苹果的抽象接口
};

class NorthApple : public Fruit
{
    virtual void SayName()
    {
        cout << "NorthApple" << endl;
    }
};

class NorthBanana : public Fruit
{
public:
    virtual void SayName()
    {
        cout << "NorthBanana" << endl;
    }
};

class SourthBanana : public Fruit
{
public:
    virtual void SayName()
    {
        cout << "SourthBanana" << endl;
    }
};

class SourthApple : public Fruit
{
public:
    virtual void SayName()
    {
        cout << "SourthApple" << endl;
    }
};

class NorthFacorty : public AbstractFactory //专门生产南方水果的工厂
{
    virtual Fruit * CreateBanana()
    {
        return new NorthBanana;
    }
    virtual Fruit * CreateApple()
    {
        return new NorthApple;
    }
};

class SourthFacorty : public AbstractFactory
{
    virtual Fruit * CreateBanana()
    {
        return  new SourthBanana;
    }
    virtual Fruit * CreateApple()
    {
        return  new SourthApple;
    }
};


int main()
{
    Fruit   * pFruit = NULL; //父类指针 
    AbstractFactory  * af = NULL; //工厂基类

    af = new SourthFacorty;  //工厂生产子类对象
    pFruit = af->CreateApple(); //间接指向子类对象 通过创建苹果的方法 创建了一个属于南方的苹果
    pFruit->SayName();
    delete pFruit;
    pFruit = af->CreateBanana();
    pFruit->SayName();
    delete pFruit;

    af = new NorthFacorty;
    pFruit = af->CreateApple();
    pFruit->SayName();
    delete pFruit;
    pFruit = af->CreateBanana();
    pFruit->SayName();
    delete pFruit;


    std::cout << "Hello world" << std::endl;
    return 0;
}

