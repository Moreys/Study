/*************************************************************************
  @FileName: md3_依赖倒置原则.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Sun 12 Apr 2020 10:07:29 PM CST
 ************************************************************************/
#include <my_head.h>
#include <iostream>


//各种零部件接口
class HardDisk
{
public:
    virtual void work() = 0;
};

class Memorey
{
public:
    virtual void work() = 0;
};

class Cpu
{
public:
    virtual void work() = 0;
};

class Computer   //电脑框架
{
public:
    Computer(HardDisk * phandDisk, Memorey * pMemorey, Cpu * pCpu)
    {
        pHandDisk_ = phandDisk;
        pMemorey_ = pMemorey;
        pCpu_ = pCpu;
    }

public:
    void work()
    {
        pHandDisk_->work();
        pMemorey_->work();
        pCpu_->work();
    }

private:
    HardDisk * pHandDisk_;
    Memorey *  pMemorey_;
    Cpu     *  pCpu_;
};


class InterCpu : public Cpu
{
public:
    void work()
    {
        cout << "I'm InterCpu work good" << endl;
    }
};

class DzMem : public Memorey
{
public:
    void work()
    {
        cout << "I'm DzMem work good" << endl;
    }
};

class DzDisk : public HardDisk
{
public:
    void work()
    {
        cout << "I'm DzDisk work good" << endl;
    }
};




int main()
{
    HardDisk * pHardDisk = NULL;
    Memorey * pMemorey = NULL;
    Cpu     * pCpu = NULL;

    pHardDisk = new DzDisk;
    pMemorey = new DzMem;
    pCpu = new InterCpu;
    
    Computer * pComputer = new Computer(pHardDisk, pMemorey, pCpu);

    pComputer->work();

    delete  pHardDisk;
    delete  pMemorey;
    delete pCpu;
    delete pComputer;





    std::cout << "Hello world" << std::endl;
    return 0;
}

