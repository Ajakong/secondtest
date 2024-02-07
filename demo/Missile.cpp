#include"Dxlib.h"
#include "Missile.h"
#include <iostream>
#include"Game.h"
#include"Object.h"
#include"Shot.h"
#include "EnemyBase.h"
#include"EneShot.h"
#include"Player.h"
#include"SceneMain.h"


Missile::Missile():
	m_handle(-1),
	m_shotPos(0, 0),
	m_Velocity(0, 0),
	m_radius(50)
{
}

Missile::~Missile()
{
}

void Missile::Init()
{
}

void Missile::Update()
{
	if (m_player != nullptr)
	{
		if(m_lockOnFrame>120)
		{
			m_Velocity.x = (m_targetPos.x - m_shotPos.x) * (m_targetPos.x - m_shotPos.x);
			m_Velocity.y = (m_targetPos.y - m_shotPos.y) * (m_targetPos.y - m_shotPos.y);
			m_Velocity.Normalize();
		}
		else
		{
			m_Velocity.y = 1*-5;
			m_Velocity.x= m_player->GetPos().x;
		}
		
		m_shotPos += m_Velocity;
	
	}

}

void Missile::Draw()
{
	DrawCircle(m_shotPos.x, m_shotPos.y, m_radius, 0xdddddd, 1);
	DrawLine(m_shotPos.x, m_shotPos.y, m_shotPos.x, m_shotPos.y - m_Velocity.y * 10,0xdd0000,50);

}

void Missile::ShotProgram(const Vec2& Spos, const Vec2& DirVec, const int& graph,Player* player)
{
	m_shotPos = Spos;
	m_DirVec = DirVec;
	m_handle = graph;
	m_player = player;
}

bool Missile::GetShotColli(const Rect& rect)
{
	return false;
}

void Missile::OnMapCol()
{
}
