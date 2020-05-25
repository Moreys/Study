/*************************************************************************
  @FileName: dm02_Command_ml.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Fri 22 May 2020 03:42:54 PM CST
 ************************************************************************/
#include <iostream>

#include <list>
using  namespace std;

/*
 * 意图：讲一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数化
 *       对请求排队或记录请求日志，以及支持可撤销的操作
 *
 * 适用性：
 *      抽象出待执行的动作以参数化某对象，你可用过程语言中的回调 函数表达这种参数化机制
 *
 *      回调函数：是指函数先在某处注册，而它将在稍后某个需要的时候被调用
 *      Command模式是回调机制的一个面向对象的替代品
 *
 *
 * */

namespace One
{

class Doctor
{
public:
    void treat_eye()
    {
        cout << "医生 治疗眼科" << endl;
    }
    void treat_nose()
    {
        cout << "医生 治疗鼻科" << endl;
    }
};

class CommandTreatEye
{
public:
    CommandTreatEye(Doctor * pDoctor):pDoctor_(pDoctor)
    {

    }

    void treat()
    {
        pDoctor_->treat_eye();
    }
private:
    Doctor * pDoctor_;
    
};

class CommandTreatNose
{
public:
    CommandTreatNose(Doctor * pDoctor):pDoctor_(pDoctor)
    {}

    void treat()
    {
        pDoctor_->treat_nose();
    }
private:
    Doctor * pDoctor_;
};

}//end of namespace One

namespace Two
{

class Doctor
{
public:
    void treat_eye()
    {
        cout << "医生 治疗眼科" << endl;
    }
    void treat_nose()
    {
        cout << "医生 治疗鼻科" << endl;
    }
};

class Command
{
public:
virtual void treat() = 0;
};

class CommandTreatEye : public Command
{
public:
    CommandTreatEye(Doctor * pDoctor):pDoctor_(pDoctor)
    {

    }

    virtual void treat()
    {
        pDoctor_->treat_eye();
    }
private:
    Doctor * pDoctor_;
    
};

class CommandTreatNose : public Command
{
public:
    CommandTreatNose(Doctor * pDoctor):pDoctor_(pDoctor)
    {}

     virtual void treat()
    {
        pDoctor_->treat_nose();
    }
private:
    Doctor * pDoctor_;
};

class BeautyNurse
{
public:
    BeautyNurse(Command * pCommand):pCommand_(pCommand)
    {}

    void SubmittedCase() //提交病例  下单命令
    {
        pCommand_->treat();
    }
private:
    Command * pCommand_;
};


class HeadNurse//
{
public:
    HeadNurse()
    {
        commList_.clear();
    }

    void setCommand(Command * pCommand)
    {
        commList_.push_back(pCommand);
    }

    void SubmittedCase()
    {
        for(auto it = commList_.begin(); it != commList_.end(); it++)
        {
            (*it)->treat();
        }
    }

private:
    list<Command *> commList_;
};

}//end of namespace One

//using namespace One;
using namespace Two;
int main01()
{
    /*
    //1、医生直接看病
    Doctor * pDoctor = new Doctor;
    pDoctor->treat_eye();
    pDoctor->treat_nose();
    */

    //2、医生通过一个命令 治疗
    Doctor * pDoctor = new Doctor;
    CommandTreatEye * pCommandTreatEye = new CommandTreatEye(pDoctor);
    pCommandTreatEye->treat();
    delete pCommandTreatEye;
    delete pDoctor;
    std::cout << "Hello world" << std::endl;
    return 0;
}

int main02()
{
    BeautyNurse * pBeautyNurse = NULL;//护士
    Doctor      * pDoctor = NULL;//医生
    Command * pCommand = 0;//命令

    pDoctor = new Doctor;

    pCommand = new CommandTreatNose(pDoctor);//治疗的一个命令 pDoctor是具体命令的产生着
    pBeautyNurse = new BeautyNurse(pCommand); // 存储命令 
    pBeautyNurse->SubmittedCase(); //命令的执行者
    
    delete pBeautyNurse;
    delete pDoctor;
    delete pCommand;
    return 0;

}

int main03()
{
    HeadNurse * pHeadNurse = NULL;
    Doctor * pDoctor = NULL;
    Command * pCommandOne = NULL;
    Command * pCommandTwo = NULL;

    pDoctor = new Doctor;

    pCommandOne = new CommandTreatEye(pDoctor);
    pCommandTwo = new CommandTreatNose(pDoctor);

    pHeadNurse = new HeadNurse();
    pHeadNurse->setCommand(pCommandOne);
    pHeadNurse->setCommand(pCommandTwo);

    pHeadNurse->SubmittedCase();

    delete pDoctor;
    delete pHeadNurse;
    delete pCommandOne;
    delete pCommandTwo;

    return 0;
}


int main()
{
    //main02();
    main03();
    cout << "hell" <<endl;
    return 0;
}
