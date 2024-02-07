#include"Dxlib.h"
#include"Game.h"
#include"Object.h"
#include "Shot.h"
#include"Player.h"
#include"EnemyBase.h"
#include<cmath>
#include "CircleShot.h"
#include"ShotEffect.h"


CircleShot::CircleShot():
	m_handle(-1),
	m_shotPos(0, 0),

	m_Velocity(0, 0),
	m_radius(15)
{
}

CircleShot::~CircleShot()
{
}

void CircleShot::Init()
{
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
}

void CircleShot::Update()
{
	//collision‚ÌXV
	m_collider.pos = m_shotPos; m_collider.radius = m_radius;

	if (m_isInVisible == false)
	{
		if (m_shotPos.x >= Game::kScreenWidth)
			m_isInVisible = true;
		if (m_shotPos.x <= 0 - m_graphSize.x)
			m_isInVisible = true;
		if (m_shotPos.y >= Game::kScreenHeight)
			m_isInVisible = true;
		if (m_shotPos.y <= 0 - m_graphSize.y)
			m_isInVisible = true;



		/*m_enePos = m_enemy->GetEnePos();
		m_Velocity.x = (m_enePos.x-m_shotPos.x);
		m_Velocity.y = (m_enePos.y- m_shotPos.y);
		m_Velocity.Normalize();*/

		

		m_Velocity.Normalize();
		m_rotateCenter += m_Velocity * 20.0f;

		rotatePos.x = (m_shotPos.x-m_rotateCenter.x)*cos(3.14 / 2)- (m_shotPos.y - m_rotateCenter.y) * sin(3.14 / 2);
		rotatePos.y = (m_shotPos.x - m_rotateCenter.x) * sin(3.14 / 2) + (m_shotPos.y - m_rotateCenter.y) * cos(3.14 / 2);

		

		/*m_shotPos.x = ;
		m_shotPos.y = rotatePos.y * sin(3.14 / 30) + rotatePos.x * cos(3.14 / 15) ;*/

		m_shotPos = rotatePos+m_rotateCenter;
		

	}

	if (effectFlag == true)
	{
		if (m_shotEffect != nullptr)
		{
			m_shotEffect->Update(m_screenMove);
		}
	}


}

void CircleShot::Draw()
{
	if (m_isInVisible == false)
	{

		DrawGraph(m_shotPos.x, m_shotPos.y, m_handle, true);
	}
	if (effectFlag == true)
	{
		if (m_shotEffect != nullptr)m_shotEffect->Draw();
	}
}

void CircleShot::ShotProgram(const Vec2& Spos,const Vec2& DirVec,const int& graph)
{
	
	m_isInVisible = false;
	m_rotateCenter = Spos;
	m_Velocity = DirVec;
	m_shotPos.x = Spos.x + 5;
	m_shotPos.y = Spos.y + 2;
	m_handle = graph;
}

bool CircleShot::GetShotColli(const Rect rect)
{
	if (m_isInVisible == false)
	{
		if (m_shotPos.y - m_radius <= rect.bottom && m_shotPos.y + m_radius >= rect.top)
		{
			if (m_shotPos.x + m_radius >= rect.left && m_shotPos.x - m_radius <= rect.right)
			{
				m_shotEffect->WantHitPos(this, m_shotPos);

				m_shotEffect = make_shared<ShotEffect>();
				m_shotEffect->WantHitPos(this, m_shotPos);
				effectFlag = true;
				m_isInVisible = true;
				return true;
			}
		}
	}



	return false;
}
