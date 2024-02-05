#include"Dxlib.h"
#include"Game.h"
#include"Object.h"
#include"ShotEffect.h"
#include "Shot.h"
#include"Player.h"
#include"EnemyBase.h"
#include<cmath>

Shot::Shot() :
	m_handle(-1),
	m_shotPos(0, 0),
	m_Velocity(0, 0),
	m_radius(15),
	m_isInVisible(false),
	m_isDestroy(false),
	effectFlag(false)
{
	
}

Shot::~Shot()
{
}

void Shot::Init()
{
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
}

void Shot::Update()
{
	//collision‚ÌXV
	m_collider.pos = m_shotPos; m_collider.radius = m_radius;

	if (!m_isInVisible)
	{
		if (m_shotPos.x >= Game::kScreenWidth)
		{
			m_isDestroy = true;
		}
		if (m_shotPos.x <= 0 - m_graphSize.x)
		{
			m_isDestroy = true;
		}
		if (m_shotPos.y >= Game::kScreenHeight)
		{
			m_isDestroy = true;
		}
		if (m_shotPos.y <= 0 - m_graphSize.y)
		{
			m_isDestroy = true;
		}
		/*m_enePos = m_enemy->GetEnePos();
		m_Velocity.x = (m_enePos.x-m_shotPos.x);
		m_Velocity.y = (m_enePos.y- m_shotPos.y);
		m_Velocity.Normalize();*/

		m_Velocity.Normalize();
		m_shotPos += m_Velocity * 20.0f;
	}
	if (effectFlag == true)
	{
		if (m_shotEffect != nullptr)
		{
			m_shotEffect->Update(m_screenMove);
		}
	}

}

void Shot::Draw()
{
	if (m_isInVisible == false)
	{
		DrawGraph(m_shotPos.x, m_shotPos.y, m_handle, true);
	}
	if (effectFlag == true)
	{
		if (m_shotEffect != nullptr)m_shotEffect->Draw();
	}
	m_screenMove=0;
}



void Shot::ShotProgram(const Vec2& Spos, const Vec2& DirVec, const int& graph)
{
	m_shotEffect= std::make_shared<ShotEffect>();;
	m_shotPos = Spos;
	m_Velocity = DirVec;
	m_handle = graph;
}

bool Shot::GetShotColli(const Rect& rect)
{
	if (m_isInVisible == false)
	{
		if (m_shotPos.y - m_radius <= rect.bottom && m_shotPos.y + m_radius >= rect.top)
		{
			if (m_shotPos.x + m_radius >= rect.left && m_shotPos.x - m_radius <= rect.right)
			{
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

void Shot::OnMapCol()
{
	if (m_isInVisible == false)
	{
		m_shotEffect = make_shared<ShotEffect>();
		m_shotEffect->WantHitPos(this, m_shotPos);
		effectFlag = true;
		m_isInVisible = true;
	}
	
	
}


