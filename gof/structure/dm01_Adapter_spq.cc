/*************************************************************************
  @FileName: dm01_Adapter_spq.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Wed 20 May 2020 11:13:13 AM CST
 ************************************************************************/
#include <iostream>
using namespace std;

class Current18v
{
public:
    virtual void userCurrent18v() = 0;
};

class Current220v
{
public:
    void userCurrent220v()
    {
        cout << "I am 220v" << endl;
    }
};


class Adapter : public Current18v
{
public:
    Adapter(Current220v * pCurrent)
    : pCurrent_(pCurrent)
    {

    }
    virtual void userCurrent18v()
    {
        cout << "I m Adapter 220v" << endl;
        pCurrent_->userCurrent220v();
    }
private:
    Current220v * pCurrent_;
};

int main()
{
    Current220v * pCurrent220v = NULL;
    Adapter * pAdapter = NULL;

    pCurrent220v = new Current220v;
    pAdapter = new Adapter(pCurrent220v);

    pAdapter->userCurrent18v();


    delete pCurrent220v;
    delete pAdapter;
    std::cout << "Hello world" << std::endl;
    return 0;
}

