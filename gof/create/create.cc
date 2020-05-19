/*************************************************************************
  @FileName: create.cc
  @Author:   morey
  @Email:    zymorey@gmail.com
  @GitHub:   https://github.com/Moreys
  @Time:     Tue 12 May 2020 07:28:48 PM CST
 ************************************************************************/
#include <my_head.h>
#include <iostream>

class MapSite
{
public:
    virtual void Enter() = 0;
};

enum Direction
{
    North,
    South,
    East,
    West
};

class Room : public MapSite
{
public:
    Room(int roomNo);

    MapSite * GetSide(Direction)const;
    void SetSide(Direction, MapSite*);
    
    virtual void Enter();

private:
    MapSite * _sides[4];
    int roomNumber_;
};


class Wall : public MapSite
{
public:
    Wall();
    virtual void Enter();
private:
};

class Door : public MapSite
{
public:
    Door(Room * = NULL, Room * = NULL);

    virtual void Enter();
    Room * OtherSideFrom(Room*);

private:
    Room * room1_;
    Room * room2_;
    bool   isOpen_;
};


class Maze
{
public:
    Maze();
    void AddRoom(Room *);
    Room * RoomNo(int)const;
private:
    //
};


class MazeFactory
{
public:
    MazeFactory();
    virtual Maze * MakeMaze()const
    {
        return new Maze;
    }
    virtual Wall * MakeWall()const
    {
        return new Wall;
    }

    virtual Room * MakeRoom(int n)const
    {
        return new Room(n);
    }

    virtual Door * MakeDoor(Room * r1, Room * r2)const
    {
        return new Door(r1, r2);
    }


private:
};

class Spell;

class RoomWithABomb : public Room
{
public:
    RoomWithABomb(int = 0, bool bombed = false);
    RoomWithABomb(const RoomWithABomb&);
    bool HasBomb();
private:
        bool bomb_;
};

class BombedWall : public Wall
{
public:
    BombedWall(bool bombed = false);
    BombedWall(const BombedWall&);

    virtual Wall * Clone() const;

    void Intialize(bool);

    virtual void Enter();
private:
    bool bomb_;
};

class EnchantedRoom : public Room
{
public:
    EnchantedRoom(int, Spell * = NULL);
    EnchantedRoom(const EnchantedRoom&);

    bool HasSpell();
    Spell PickUpSpell();
private:
        Spell * spell_;
};

class DoorNeedingSpell : public Door
{
public:
    DoorNeedingSpell(Room*, Room*);
    DoorNeedingSpell(const DoorNeedingSpell&);
    bool TrySpell(Spell);
private:
};

//有魔法的迷宫
class EnchanteMazeFactory : public MazeFactory
{
public:
    virtual Room * MakeRoom(int n) const
    {
        return new EnchantedRoom(n, CastSpell());
    }

    virtual Door * MakeDoor(Room * r1, Room * r2)const
    {
        return new DoorNeedingSpell(r1, r2);
    }
private:
    Spell * CastSpell()const;
};



class BombedMazeFactory :public MazeFactory
{
public:
    BombedMazeFactory();
    virtual Wall * MakeWall() const 
    {
        return new BombedWall;
    }

    virtual Room * MakeRoom(int n) const
    {
        return new RoomWithABomb(n);
    }
};

class MazeGame
{
public:

private:
};


int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

