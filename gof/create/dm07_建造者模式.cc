/*************************************************************************
  @FileName: dm06_建造者模式_问题抛出.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Wed 15 Apr 2020 10:31:16 PM CST
 ************************************************************************/
#include <my_head.h>
#include <iostream>

class House
{
public:
    void setDoor(string door)
    {
        door_ = door;
    }

    ~House()
    {
        cout <<"~House" << endl;
    }

    void setWall(string wall)
    {
        wall_ = wall;
    }

    void setWindow(string window)
    {
        window_ = window;
    }

    string getDoor()
    {
        cout << door_ << endl;
        return door_;
    }

    string getWall()
    {
        cout << wall_ << endl;
        return wall_;
    }

    string getWindow()
    {
        cout<< window_ << endl;
        return window_;
    }

private:
    string door_;
    string wall_;
    string window_;
};

class Builder //建造者基类
{
public:
    virtual void buildWall() = 0;
    virtual void buildDoor() = 0;
    virtual void buildWindow() = 0;
    virtual House * getHouse() = 0;
};

//后续的不同施工队进行不同的施工
class FlatBuilder : public Builder
{

public:
    FlatBuilder()
    {
        house_ = new House;
    }

    virtual void buildDoor() override
    {
        house_->setDoor("flat door");
    }

     virtual void buildWall() override
     {
        house_->setWall("flat wall");
     }

     virtual void buildWindow() override
     {
         house_->setWindow("flat window");
     }
     virtual House * getHouse() override{
         return house_;
     }

private:
    House * house_;
};


class VillaBuilder : public Builder
{
public:
    VillaBuilder()
    {
        house_ = new House;
    }
    virtual ~VillaBuilder()
    {
        delete house_;
    }

    virtual void buildDoor()
    {
        house_->setDoor("vill door");
    }

    virtual void buildWall()
    {
        house_->setWall("vill wall");
    }
    virtual void buildWindow()
    {
        house_->setWindow("vill window");
    }

    virtual House * getHouse() override
    {
        return house_;
    }
        
private:
    House * house_;
};


//设计师  指挥者  负责建造逻辑
//建筑队  干具体的活
class Director
{
public:
    Director(Builder * builder)
    {
        build_ = builder;
    }

    void Construct()
    {
        build_->buildDoor();
        build_->buildWall();
        build_->buildWindow();
    }
private:
    Builder * build_;

};

int main()
{

    House       * pHouse = NULL;
    Builder     * pBuilder = NULL;
    Director    * pDirector = NULL;

    //请一个建筑别墅的施工队
    pBuilder = new VillaBuilder;

    //设计师  指挥施工队 干活
    pDirector = new Director(pBuilder);
    pDirector->Construct();
    pHouse = pBuilder->getHouse();
    pHouse->getWindow();
    pHouse->getDoor();

    delete pHouse;
    delete pBuilder;

    pBuilder = new FlatBuilder;
    pDirector = new Director(pBuilder);
    pDirector->Construct();
    pHouse->getDoor();
    pHouse->getWall();
    delete pHouse;
    delete pBuilder;



    delete  pDirector;
    std::cout << "Hello world" << std::endl;
    return 0;
}

