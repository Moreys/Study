/*************************************************************************
  @FileName: dm04_Iterator_ddq.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Fri 22 May 2020 04:38:45 PM CST
 ************************************************************************/
#include <iostream>

#define  SIZE 10

const int SiZe = 10;
/*
 * 意图： 提供一种方法顺序访问一个聚合对象中各个元素，而又不暴露该对象的内部表示
 *
 * 适用性： 
 *      访问一个聚合对象的内容而无需暴露它的内部表示
 *      支持对聚合对象的多种遍历
 *      为遍历不同的聚合结构提供一个统一的接口（即，支持多态迭代）
 * */

class MyIterator
{
public:
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() = 0;
    virtual int CurrentItem() = 0;
};

class Aggregate
{
public:
    virtual MyIterator * CreateIterator() = 0;
    virtual int getItem(int index) = 0;
    virtual int getSize() = 0;
};


class ConntreteIterator : public MyIterator
{
public:
     ConntreteIterator(Aggregate * ag)
         : ag_(ag)
     {
         current_index_ = 0;
     }

     virtual void First()
     {
         current_index_ = 0;
     }

     virtual void Next()
     {
         if(current_index_ < ag_->getSize())
         {
             current_index_++;
         }
     }

     virtual  bool IsDone()
     {
         return (current_index_ == ag_->getSize());
     }

     virtual int CurrentItem()
     {
         return  ag_->getItem(current_index_);
     }

     
private:
    int current_index_;
    Aggregate * ag_;
};


class ConntreteAggreagte : public Aggregate
{
public:
    ConntreteAggreagte()
    {
        for(int i = 0; i < SIZE; ++i)
        {
            objects_[i] = i + 100;
        }
    }

    virtual MyIterator * CreateIterator()
    {
        return new ConntreteIterator(this); //让迭代器 持有一个 集合的 引用
    }

    virtual int getItem(int index)
    {
        return objects_[index];
    }

    virtual int getSize()
    {
        return SIZE;
    }
private:
    int objects_[SIZE];
};

int main()
{
    Aggregate * pAg = new ConntreteAggreagte;

    MyIterator * pIt = pAg->CreateIterator();

    for(; !(pIt->IsDone()); pIt->Next())
    {
        std::cout << pIt->CurrentItem() << " "; 
    }
    std::cout << "Hello world" << std::endl;
    return 0;
}

