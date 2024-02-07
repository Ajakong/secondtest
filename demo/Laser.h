#pragma once
#include "Shot.h"

class ColllisionMaster;

class Laser 
{
public:
    Laser();
    
    virtual ~Laser();


    virtual void Update();

    virtual void Draw();

    virtual void ShotProgram(Vec2 Spos, Vec2 DirVec);

    bool GetVisible()const { return m_isInVisible; }

    bool LineCollider(float x1,float y1,float x2,float y2);

    Vec2 GetLaserPos() { return m_laserHead; };
    
    bool OnLaserCollision(Rect rect);

    float toEquation(float& pos1X,float& pos1Y, float& pos2X,float& pos2Y);//�ꎟ�����������ĐؕЂ�Ԃ�

    void GetScreenMove(int screenMove) { m_screenMove = screenMove; }

private:
    

    Vec2 m_laserHead;//���[�U�[�̐擪
    Vec2 m_laserTail;//���[�U�[�̔�

    Vec2 m_dirVec;//���[�U�[�̐擪
    Vec2 m_startPos;//���[�U�[�̔�

    Vec2 m_expLine;//���[�U�[��1���֐�
    int b = 0;//�ؕ�

    bool m_isInVisible=false;

    int m_limitTime=0;

    int m_screenMove=0;

    int m_laserSound = 0;
};

