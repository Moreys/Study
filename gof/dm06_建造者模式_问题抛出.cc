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

class Build
{
public:
    Build()
    {
        house_ = new House;
    }
    ~Build()
    {
        if(NULL != house_)
        {
            delete house_;
        }
    }
    void makeBuild()
    {
        buildDoor(house_);
        buildWall(house_);
        buildWindow(house_);
    }

    void buildDoor(House * h)
    {
        h->setDoor("door");
    }

    void buildWall(House * h)
    {
        h->setWall("wall");
    }

    void buildWindow(House * h)
    {
        h->setWindow("window");
    }

    House * getHouse()
    {
        return house_;
    }
private:
    House * house_;
};

int main()
{

    //原来的，自己建造房子
    House *  pHouse = new House;
    pHouse->setDoor("door");
    pHouse->setWall("wall");
    pHouse->setWindow("window");
    delete pHouse;


    //请施工队
    House * ppHouse = NULL;
    Build * pBuild = new Build;
    pBuild->makeBuild();
    ppHouse = pBuild->getHouse();
    ppHouse->getDoor();
    ppHouse->getWall();
    ppHouse->getWindow();
    delete pBuild;
    std::cout << "Hello world" << std::endl;
    return 0;
}

