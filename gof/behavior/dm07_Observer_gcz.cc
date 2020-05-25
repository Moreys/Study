/*************************************************************************
  @FileName: dm07_Observer_gcz.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Mon 25 May 2020 06:22:52 PM CST
 ************************************************************************/
#include <iostream>
#include <string>
#include <list>
using namespace std;

/*
 * 意图：定义对象的一种一对多的依赖关系，当一个对象的状态发生改变时，
 *       所有依赖于它的对象得到通知并被自动更新。
 *
 * 适用性: 1、当一个抽象模型有两个方面，其中一个方面依赖于另一个方面，
 *            将二者封装在独立的对象中以使他们可以各自独立地改变和复用
 *        2、当一个对象的改变需要同时改变其他对象，而不知道具体有多少对象有待改变
 *        3、当一个对象必须通知其他对象，而它又不能假定其他对象是谁，换言之，你不希望这些对象是紧密耦合的
 * */


class Secretary;


//观察者
class PlayserObserver
{
public:
    PlayserObserver(Secretary * pSecretary):pSecretary_(pSecretary)
    {}

    void update(string action)
    {
        cout << "action:" << action << endl;
        cout << "老板来了，我很害怕" << endl;
    }
private:
    Secretary * pSecretary_;
};

class Secretary
{
public:
    Secretary()
    {
        lists_.clear();
    }
    void Notify(string info)
    {
        //给所有的观察者发送情报
        for(auto & iter : lists_)
        {
            iter->update(info);
        }
    }

    void setPlayserObserver(PlayserObserver * po)
    {
        lists_.push_back(po);
    }
private:
    list<PlayserObserver*> lists_;
};

int main()
{
    Secretary * pSecretary = NULL;
    PlayserObserver * po1 = NULL;
    PlayserObserver * po2 = nullptr;

    pSecretary = new Secretary;
    po1 = new PlayserObserver(pSecretary);
    po2 = new PlayserObserver(pSecretary);

    pSecretary->setPlayserObserver(po1);
    pSecretary->setPlayserObserver(po2);


    pSecretary->Notify("老板来了");
    pSecretary->Notify("老板走了");
    delete pSecretary;
    delete po1;
    delete po2;

    std::cout << "Hello world" << std::endl;
    return 0;
}

