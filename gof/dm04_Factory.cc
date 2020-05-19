/*************************************************************************
  @FileName: md04_Factory.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Mon 13 Apr 2020 08:46:59 PM CST
 ************************************************************************/
#include <my_head.h>
#include <iostream>

class Fruit
{
public:
    virtual void CreateFactory() = 0;
};

class Apple : public Fruit
{
public:
    void CreateFactory()
    {
        cout << "Apple" << endl;
    }
};

class Banana : public Fruit
{
public:
    void CreateFactory()
    {
        cout << "Banana" << endl;
    }
};

class ABFactory //生产苹果和香蕉的工厂接口
{
public:
    virtual Fruit * CreateFactory() = 0;
};

class BananaFactory : public ABFactory //具体的生产香蕉的工厂
{
public:
    virtual Fruit * CreateFactory()
    {
        return new Banana;
    }
};

class AppleFactory : public ABFactory //具体的生产苹果的工厂 
{
public:
    virtual Fruit * CreateFactory()
    {
        return new Apple;
    }
};



//TODO 需要生产新水果
//
//创建具体的水果
class Pair : public Fruit
{
public:
    virtual void CreateFactory()
    {
        cout << "Pair" << endl;
    }
};

class PairFactory
{
public:
    virtual Fruit *  CreateFactory() = 0;
};

class PairFactoryB : public PairFactory
{
public:
    virtual Fruit * CreateFactory()
    {
        return new Pair;
    }
};

int main()
{
    //使用
    ABFactory   *pFactory = NULL;
    Fruit       *pFrut = NULL;

    pFactory = new BananaFactory;
    pFrut = pFactory->CreateFactory();
    pFrut->CreateFactory(); //指向具体的Banana

    delete pFrut;
    delete pFactory;

    pFactory = new AppleFactory;
    pFrut = pFactory->CreateFactory();
    pFrut->CreateFactory();

    delete pFrut;
    delete pFactory;

    PairFactory *pPairFac = NULL; //新工厂 
    pPairFac = new PairFactoryB; //
    pFrut = pPairFac->CreateFactory(); //基类工厂生产新工厂的产品
    pFrut->CreateFactory();

    std::cout << "Hello world" << std::endl;
    return 0;
}

