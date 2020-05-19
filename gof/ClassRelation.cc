/*************************************************************************
  @FileName: ClassRelation.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Sun 12 Apr 2020 08:29:20 PM CST
 ************************************************************************/
#include <my_head.h>


/*
 * 依赖关系.....UML图为虚线连接
 * 一个类是另外一个类的成员函数参数或者成员函数返回值。
 * */
class Car;
class ClassOne
{
    public:
        void GoWork(Car * pCar)
        {

        }

        Car * finx()
        {

        }
};

class Car
{
    
public:

private:

};


/*关联关系：UML图使用实线连接
 * 表现形式：一个类是另外一个类的成员变量。
 *
 *
 *  两者的耦合性对比：
 *
 * */

class AdvClassTwo
{
public:
    void GoWork()
    {

    }
private:
    Car * m_car;
};



int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

