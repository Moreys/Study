/*************************************************************************
  @FileName: dm02_Bridge_qj.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Wed 20 May 2020 11:19:44 AM CST
 ************************************************************************/
#include <iostream>
using namespace std;

class Engine
{
public:
    virtual void InstallEngine() = 0;
};

class Engine4400cc : public Engine
{
public:
    virtual void InstallEngine()
    {
        cout << "I m 4400cc I m ok" << endl;
    }
};

class Engine4500cc : public Engine
{
public:
    virtual void InstallEngine()
    {
        cout << "I m 4500cc I m OK" << endl;
    }
};

class Car
{
public:
    Car(Engine * pEngine)
        :pEngine_(pEngine)
    {

    }
    virtual void installEngine() = 0;
protected:
    Engine * pEngine_;
};

class WBM5 : public Car 
{
public:
    WBM5(Engine * pEngine)
        : Car(pEngine)
    {

    }
    virtual void installEngine()
    {
        cout << "I m WBM5" << endl;
        pEngine_->InstallEngine();
    }
private:
};

class WBM6 : public Car 
{
public:
    WBM6(Engine * pEngine)
        : Car(pEngine)
    {

    }
    virtual void installEngine()
    {
        cout << "I m WBM6" << endl;
        pEngine_->InstallEngine();
    }
private:
};

int main()
{
    Engine * pEngine = NULL;
    WBM6 * pWbm6 = NULL;
    pEngine = new Engine4400cc;
    pWbm6 = new WBM6(pEngine);
    pWbm6->installEngine();
    delete pEngine;

    //动态改变发动机型号
    pEngine = new Engine4500cc;
    pWbm6->installEngine(); 

    delete pEngine;
    delete pWbm6;
    std::cout << "Hello world" << std::endl;
    return 0;
}

