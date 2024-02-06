#pragma once
#include "Item.h"

class Player;

class FullAutoGun :
    public Item
{
public:
    FullAutoGun(Vec2 pos, Vec2 velo, int itemGraph);
    virtual ~FullAutoGun();

    virtual void Init();
    virtual void Update();
    virtual void Draw();
    virtual void CollisionUpdate();


    int GetWeaponNum() { return 1; }
private:

};

