#include"Dxlib.h"
#include"Game.h"
#include"Object.h"
#include"Player.h"
#include"EnemyBase.h"
#include<cmath>
#include "EneShot.h"
#include"EneShotEffect.h"

EneShot::EneShot():
	m_handle(-1),
	m_shotPos(0, 0),
	m_isVisible(false),
	m_Velocity(0, 0),
	m_radius(15),
	m_isDestroy(false)
{
}

EneShot::~EneShot()
{
}

void EneShot::Init()
{
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
}

void EneShot::Update()
{
	
	if (m_screenMove > 0)
	{
		int b = 0;
	}
	//collision‚ÌXV
	m_collider.pos = m_shotPos; m_collider.radius = m_radius;

	if (m_isVisible == false)
	{
		if (m_shotPos.x >= Game::kScreenWidth)
			m_isVisible = true;
		if (m_shotPos.x <= 0 - 15)
			m_isVisible = true;
		if (m_shotPos.y >= Game::kScreenHeight)
			m_isVisible = true;
		if (m_shotPos.y <= 0 - 15)
			m_isVisible = true;

		/*m_enePos = m_enemy->GetEnePos();
		m_Velocity.x = (m_enePos.x-m_shotPos.x);
		m_Velocity.y = (m_enePos.y- m_shotPos.y);
		m_Velocity.Normalize();*/

		m_Velocity.Normalize();
		m_shotPos += m_Velocity * 10.0f;
	}
	if (m_isEffectFlag == true)
	{
		if (m_shotEffect != nullptr)
		{
			m_shotEffect->Update();
		}
	}
	
}

void EneShot::Draw()
{
	if (m_isVisible == false)
	{
		DrawGraph(m_shotPos.x-m_screenMove, m_shotPos.y, m_handle, true);
		DrawBox(m_shotPos.x - m_screenMove, m_shotPos.y, m_shotPos.x + m_radius*2 - m_screenMove, m_shotPos.y + m_radius*2,0xff0000,0);
		DrawFormatString(50, 50, 0xffffff, "%d", m_screenMove);
	}

	if (m_isEffectFlag == true)
	{
		if (m_shotEffect != nullptr)m_shotEffect->Draw();
	}
}

void EneShot::ShotProgram(const Vec2& Spos, const Vec2& DirVec, const int& graph, std::shared_ptr<EneShotEffect> eneShotEffect, std::shared_ptr<EneShot>shotPointer)
{
	m_isVisible = false;
	m_shotPos = Spos;
	m_Velocity = DirVec;
	m_myPointer = shotPointer;
	m_handle = graph;
	m_shotEffect = eneShotEffect;
}



bool EneShot::GetShotColli(const Rect& rect)
{
	if (m_isVisible == false)
	{
		if (m_shotPos.y <= rect.bottom && m_shotPos.y + m_radius*2 >= rect.top)
		{
			if (m_shotPos.x + m_radius*2 >= rect.left && m_shotPos.x <= rect.right)
			{
				m_isVisible = true;
				m_isEffectFlag = true;
				m_shotEffect->WantHitPos(m_myPointer, m_shotPos);
				return true;
			}
		}
	}
	return false;
}

void EneShot::OnCollision()
{
	m_isVisible = true;
	m_isEffectFlag = true;
	m_shotEffect->WantHitPos(m_myPointer, m_shotPos);
}
