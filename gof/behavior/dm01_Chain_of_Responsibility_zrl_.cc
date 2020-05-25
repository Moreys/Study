/*************************************************************************
  @FileName: dm01_Chain_of_Responsibility_zrl_.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Wed 20 May 2020 03:59:51 PM CST
 ************************************************************************/
#include <iostream>
using  namespace std;

/*
 * 意图： 使多个对象都有机会处理请求，从而避免请求的发送者和接收者
 *        之间的耦合关系，将这些对象连成一条链，并沿着这条链传递该请求
 *        直到有一个对象处理它为止
 * 
 * 适用性
 *      有对个的对象可以处理一个请求，那个对象处理该请求运行时刻自动确定
 *      你想在不明确指定接收者的情况下，向多个对象中的一个提交哦一个请求
 *      可以处理一个请求的对象集合应该被动态指定
 *        * */

namespace zrlwt
{

class CarHandle
{
public:
    virtual void HandleCar() = 0;
};

class HeadCarHandle : public CarHandle
{
public:
    virtual void HandleCar()
    {
        cout << "车头" << endl;
    }
private:
};


class BodyCarHandle : public CarHandle
{
public:
    virtual void HandleCar()
    {
        cout << "车身" << endl;
    }
};

class TailCarHandle : public CarHandle
{
public:
    virtual void HandleCar()
    {
        cout << "车尾" << endl;
    }
};

}//end of namespace zrlwt

namespace  okzrl
{
/*
 * 意图：使用多个对象都有机会处理请求，从而避免请求的发送者和接收者的耦合关系
 * 将这些对象连成一条链，并沿着这条链传递该请求，直到有一个对象处理它为止.
 *
 * 适用性：有多个的对象可以处理一个请求，那个对象处理该请求运行时刻自动确定
 * 你想在不明确指定接收者的情况下，向多个对象中的一个提交一个请求
 * 可处理一个请求的对象集合应被动态指定
 * */
class CarHandle
{
public:
    virtual void HandleCar() = 0;

    CarHandle * setNextHandle(CarHandle * pHandle)
    {
        pHandle_ = pHandle;
        return pHandle_;
    }

protected:
    CarHandle * pHandle_;  //下一个处理单元
};

class HeadCarHandle : public CarHandle
{
public:
    virtual void HandleCar()
    {
        cout << "车头" << endl;

        //造完 车头以后把任务传递给下一个处理者
        if(pHandle_ != NULL)
        {
            pHandle_->HandleCar();
        }
    }
};

class BodyCarHandle : public CarHandle
{
public:
    virtual void HandleCar()
    {
        cout << "车身" << endl;
        if(pHandle_ != NULL)
        {
            pHandle_->HandleCar();
        }
    }
};

class TailCarHandle : public CarHandle
{
public:
    virtual void HandleCar()
    {
        cout << " 车尾" << endl;
        if(pHandle_ != NULL)
        {
            pHandle_->HandleCar();
        }
    }
};

}//end of namespace okzrl


//using namespace zrlwt;
using namespace okzrl;

int main()
{
    CarHandle * headHandle = new HeadCarHandle;
    CarHandle * bodyHandle = new BodyCarHandle;
    CarHandle * tailHandle = new TailCarHandle;

    //业务逻辑写死在客户端了
    /*
    headHandle->HandleCar();
    bodyHandle->HandleCar();
    tailHandle->HandleCar();
    */

    headHandle->setNextHandle(tailHandle);
    tailHandle->setNextHandle(bodyHandle);
    bodyHandle->setNextHandle(NULL);//如果需要后续还可以进行传递
    headHandle->HandleCar();
    
    delete headHandle;
    delete bodyHandle;
    delete tailHandle;
    std::cout << "Hello world" << std::endl;
    return 0;
}

