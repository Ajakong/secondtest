#pragma once
#include "Effect.h"
class EnemyMoveEffect :
    public Effect
{
public:
    EnemyMoveEffect();
    ~EnemyMoveEffect();

    void Init();
    void Update();
    void Draw();

    virtual void CreateEffect(Vec2 pos, float offSetX, float offSetY);
private:
    s

};

