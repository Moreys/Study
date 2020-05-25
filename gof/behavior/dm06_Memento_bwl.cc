/*************************************************************************
  @FileName: dm06_Memento_bwl.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Mon 25 May 2020 05:34:56 PM CST
 ************************************************************************/
#include <iostream>
using namespace std;

/*
 * 意图：在不破坏封装的前提下， 捕获一个对象的内部状态，并在该对象之外保存这个状态
 *       这样以后就可将该对象恢复到原先保存的状态
 *
 *  适用性: 1、必须保存一个对象在某一个时刻的(部分)状态，这样以后需要时它才能恢复到先前的状态
 *          2、如果一个接口来让其他对象直接得到这些状态，将会暴露对象的实现细节并破坏对象的封装性
 * */


//Caretaker 管理者
//MememTo 备忘录


class MememTo
{
public:
    MememTo(string name, int age)
        : name_(name)
        , age_(age)
    {}

    string getName()
    {
        return  name_;
    }

    int getAge()
    {
        return age_;
    }

    void setName(string name)
    {
        name_ = name;
    }

    void setAge(int age)
    {
        age_ = age;
    }

private:
    string name_;
    int age_;
};


class Person
{
public:
    Person(string name, int age):name_(name),age_(age)
    {}

    string getName()
    {
        return name_;
    }
    int getAge()
    {
        return age_;
    }

    void setName(string name)
    {
        name_ = name;
    }

    void setAge(int age)
    {
        age_ = age;
    }

    MememTo * createMememTo()
    {
        return  new  MememTo(name_, age_);
    }

    void setMememTo(MememTo * pMemTo)
    {
        name_ = pMemTo->getName();
        age_ = pMemTo->getAge();
    }

    
    void printT()
    {
        cout << "name_:" << name_ << " age:" << age_ << endl;
    }
private:
    string name_;
    int age_;
};

class Caretaker
{
public:
    Caretaker(MememTo * pMemTo):pMemTo_(pMemTo)
    {}

    MememTo * getMememTo()
    {
        return pMemTo_;
    }

    void setMememTo(MememTo * pMemTo)
    {
        pMemTo_ = pMemTo;
    }

private:
    MememTo * pMemTo_;
};


void One()
{
    Caretaker * pCaretaker = NULL;

    Person * p = new Person("张珊", 32);
    p->printT();

    //创建 Person 对象的一个状态
    printf("1111111111111111\n");
    pCaretaker = new Caretaker(p->createMememTo());
    p->setAge(42);
    p->printT();

    printf("还原状态\n");
    p->setMememTo(pCaretaker->getMememTo());
    p->printT();
    delete pCaretaker;
    delete p;

}

void Two()
{
    MememTo * pMemTo = NULL;
    Person * p = new Person("张翰" , 32);
    p->printT();

    //创建 Person 对象的一个状态
    printf("1111111111\n");
    pMemTo = p->createMememTo();
    p->setAge(42);
    p->printT();

    printf("还原旧的状态\n");
    p->setMememTo(pMemTo);
    p->printT();

    delete  pMemTo;
    delete  p;
}

int main()
{
    //One();
    Two();
    std::cout << "Hello world" << std::endl;
    return 0;
}

