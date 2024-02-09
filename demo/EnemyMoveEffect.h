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
    void Draw(int screenMove);

    virtual void CreateEffect(Vec2 pos, float offSetX, float offSetY,int screenMove);
private:
   
    int m_firstScreenMove = 0;

    Vec2 m_effectFrameOffSet;

};

