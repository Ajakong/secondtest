#pragma once
#include "Item.h"
class Spread : public Item
{
public:
    Spread(Vec2 pos, Vec2 velo, int itemGraph);
    virtual ~Spread();

    virtual void Init();
    virtual void Update();
    virtual void Draw();
    virtual void CollisionUpdate();


    int GetWeaponNum() { return 2; }
};

