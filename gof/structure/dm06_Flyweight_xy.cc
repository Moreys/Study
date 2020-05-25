/*************************************************************************
  @FileName: dm06_Flyweight_xy.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Wed 20 May 2020 03:17:19 PM CST
 ************************************************************************/
#include <iostream>
#include <map>
#include <string>
using  namespace std;

/*
 * 意图：运用共享技术有效地支持大量细粒度的对象
 * 适用性
 *      一个应用程序使用了大量的对象
 *      完全由于使用大量的对象，造成很大的存储开销
 *      对象的大多数状态都可变为外部状态
 *      如果删除对象的外部状态，那么可以用相对较少的共享对象取代很多对象
 *      应用程序不依赖于对象标识，由于Flyweight对象可以被共享，对概念上明显有别的对象，标识测试讲返回真值
 *
 * 
 *
 * */


class Person
{
public:
    Person(string name, int age)
        : name_(name)
        , age_(age)
    {}
    ~Person()
    {
        cout << "~Person" << endl;
    }
    virtual void printT()  = 0;
protected:
    string name_;
    int age_;
};

class Teacher : public Person
{
public:
    Teacher(string name, int age, string id)
        : Person(name, age)
        , id_(id)
    {}

    void printT()
    {
        cout << "name:" << name_ << " age:" << age_ << " id:" << id_ << endl;
    }

private:
    string id_;
};


class FlyWeightTeacherFactory
{
public:
    FlyWeightTeacherFactory()
    {
        map_.clear();
    }
    ~FlyWeightTeacherFactory()
    {
        while(! map_.empty())
        {
            Person * pTmp = NULL;
            auto iter = map_.begin();
            pTmp = iter->second;
            map_.erase(iter);
            delete pTmp;
        }
    }

    Person * GetTeacher(string id)
    {
        Person * ptmp = NULL;
        auto iter = map_.find(id);
        if(iter != map_.end())
        {
            ptmp =  iter->second;
        }
        else
        {
            string tmpName;
            int tmpAge;
            cout << "\n输入name";
            cin >> tmpName;

            cout << "\n输入age";
            cin >> tmpAge;
            ptmp = new Teacher(tmpName, tmpAge, id);
            map_.insert(make_pair(id, ptmp));
        }
        return ptmp;
    }
private:
    map<string, Person*> map_;
};

int main()
{
    Person * p1 = NULL;
    Person * p2 = NULL;
    FlyWeightTeacherFactory * pFwtf = new FlyWeightTeacherFactory;
    p1 = pFwtf->GetTeacher("001");
    p1->printT();

    p2 = pFwtf->GetTeacher("001");
    p2->printT();
    delete  pFwtf;
    std::cout << "Hello world" << std::endl;
    return 0;
}

