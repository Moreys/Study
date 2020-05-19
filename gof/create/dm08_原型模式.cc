/*************************************************************************
  @FileName: dm08_原型模式.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Mon 20 Apr 2020 10:37:59 PM CST
 ************************************************************************/
#include <my_head.h>
#include <iostream>

class Person
{
public:
    virtual Person * clone() = 0;
    virtual void printT() = 0;
};

class CPlusPlusProgrammer : public Person
{
public:
    CPlusPlusProgrammer()
    {
        name_ = "";
        age_ = 0;
        resume_ = NULL;
    }
    CPlusPlusProgrammer(string name, int age)
    {
        name_ = name;
        age_ = age;
        resume_ = NULL;
    }

    void setResume(char * p)
    {
        if(resume_ != NULL)
        {
            delete  resume_;
        }
        resume_ = new char[strlen(p) + 1];
        strcpy(resume_, p);
    }

    virtual void printT()
    {
        cout << "name:" << name_ << " age:" << age_ << " resume_:" << resume_ << endl;
        cout << endl;
    }

    virtual Person * clone()
    {
        CPlusPlusProgrammer * tmp = new CPlusPlusProgrammer;
        *tmp = *this; 
        return tmp;
    }

private:
    string name_;
    int age_;
    char * resume_;
};

int main()
{
    Person * c1 = new CPlusPlusProgrammer("张山", 21);
    c1->printT();

    Person * c2 = c1->clone();
    c2->printT();

    std::cout << "Hello world" << std::endl;
    return 0;
}

