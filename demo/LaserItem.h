#pragma once
#include "Item.h"
class LaserItem :
    public Item
{
public:
    LaserItem(Vec2 pos, Vec2 velo, int itemGraph);
    virtual ~LaserItem();

    virtual void Init();
    virtual void Update();
    virtual void Draw();
    virtual void CollisionUpdate();


    int GetWeaponNum() { return 3; }
};

