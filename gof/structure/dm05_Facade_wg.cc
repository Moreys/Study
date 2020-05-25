/*************************************************************************
  @FileName: dm05_Facade_wg.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Wed 20 May 2020 11:48:17 AM CST
 ************************************************************************/
#include <iostream>
using namespace std;

class SubSystemA
{
public:
    void doThing()
    {
        cout << "SubSystemA run" << endl;
    }
};

class SubSystemB
{
public:
    void doThing()
    {
        cout << "SubSystemB run" << endl;
    }
};

class SubSystemC
{
public:
    void doThing()
    {
        cout << "SubSystemC run" << endl;
    }
};

class Facade
{
public:
    Facade()
    {
        pSysA_ = new SubSystemA;
        pSysB_ = new SubSystemB;
        pSysC_ = new SubSystemC;
    }
    ~Facade()
    {
        delete pSysA_;
        delete pSysB_;
        delete pSysC_;
    }

    void doThing()
    {
        pSysA_->doThing();
        pSysB_->doThing();
        pSysC_->doThing();
    }
private:
    SubSystemA * pSysA_;
    SubSystemB * pSysB_;
    SubSystemC * pSysC_;
};



//以前的使用方式
void former()
{
    SubSystemA * pSysA_;
    SubSystemB * pSysB_;
    SubSystemC * pSysC_;

    pSysA_->doThing();
    pSysB_->doThing();
    pSysC_->doThing();
    delete pSysA_;
    delete pSysB_;
    delete pSysC_;
}

void newFormer()
{
    Facade * pF = new Facade;
    pF->doThing();
    delete pF;
}

int main()
{
    //former();
    newFormer();

    std::cout << "Hello world" << std::endl;
    return 0;
}

