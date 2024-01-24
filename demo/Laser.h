#pragma once
#include "Shot.h"

class ColllisionMaster;

class Laser :
    public Shot
{
public:
    Laser();
    
    virtual ~Laser();


    virtual void Update();

    virtual void Draw();

    virtual void ShotProgram(Vec2 Spos, Vec2 DirVec);

    bool GetVisible()const { return m_isVisible; }

    bool LineCollider(float x1,float y1,float x2,float y2);

    Vec2 GetLaserPos() { return m_laserHead; };
    
    bool OnLaserCollision(Rect rect);

    float toEquation(float& pos1X,float& pos1Y, float& pos2X,float& pos2Y);//一次方程式化して切片を返す


private:
    Rect m_rect;

    Vec2 m_laserHead;//レーザーの先頭
    Vec2 m_laserTail;//レーザーの尾

    Vec2 m_dirVec;//レーザーの先頭
    Vec2 m_startPos;//レーザーの尾

    Vec2 m_expLine;//レーザーの1次関数
    int b = 0;//切片

    bool m_isVisible;

    int m_limitTime;
};

