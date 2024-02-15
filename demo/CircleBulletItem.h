#pragma once
#include "Item.h"
class CircleBulletItem :
    public Item
{
public:
    CircleBulletItem(Vec2 pos, Vec2 velo, int itemGraph);
    virtual ~CircleBulletItem();

    virtual void Init();
    virtual void Update();
    virtual void Draw();
    virtual void CollisionUpdate();


    int GetWeaponNum() { return 4; }
};

