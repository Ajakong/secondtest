#include"Dxlib.h"
#include<cmath>
#include <iostream>
#include"Game.h"
#include"Object.h"
#include "EnemyBase.h"
#include"Player.h"
#include"SceneMain.h"
#include "EnemyToPlayerDir.h"

namespace
{
	constexpr int animDisX = 288;
	constexpr int animDisY = 162;

	constexpr int collisionSizeX = 75;
	constexpr int collisionSizeY = 80;
}


EnemyToPlayerDir::EnemyToPlayerDir():
	m_isDeathFlag(false),
	m_Hp(50),
	m_pos(0.0f, 0.0f),
	m_velocity(0.0f, 0.0f),
	animFrameMana(0, 0),
	m_fireDir(1.0f, 0.0f),
	m_isShotCollFlag(false),
	m_attackFrame(0),
	m_isDesitionMyWay(false)
{
}

EnemyToPlayerDir::~EnemyToPlayerDir()
{
}

void EnemyToPlayerDir::Init(Vec2 pos,Player* player)
{
	m_handle = LoadGraph("data/image/Enemy/enemyDevilSlime.png");
	m_pos = pos;
	m_player = player;
	m_velocity.y = 0;
}

void EnemyToPlayerDir::CollisionUpdate()
{
	m_colRect.top = m_pos.y;
	m_colRect.bottom = m_pos.y + collisionSizeY;
	m_colRect.left = m_pos.x-m_screenMove;
	m_colRect.right = m_pos.x +collisionSizeX-m_screenMove;
}

void EnemyToPlayerDir::Update()
{
	m_velocity.y =0.0f;
	m_velocity.y += 9.8f;
	CollisionUpdate();
	
	if (m_player != nullptr)
	{
		//if (abs(m_player->GetPos().x - m_pos.x) < 300)
		{
			if (m_isDesitionMyWay == false)
			{
				m_velocity.x = m_player->GetPos().x - m_pos.x;
				m_velocity.Normalize();
				m_isDesitionMyWay = true;
			}
		}


		if (abs(m_player->GetPos().x - m_pos.x) < 50)
		{
			m_isAttack = true;
			if ((m_player->GetPos().x - m_pos.x) < 0)
			{
				m_isRight = false;
			}
			else
			{
				m_isRight = true;
			}
		}
	}

	if(m_isDesitionMyWay)
	{
		
		if (m_player != nullptr)
		{
			
			m_isMapCol = false;
		}
		if (m_animInterval > 6)
		{
			animFrameMana.y = 2;
			animFrameMana.x++;
			m_animInterval = 0;
			if (animFrameMana.x > 11)
			{
				animFrameMana.x = 0;
			}
		}
		
	}
	if (!m_isDesitionMyWay)
	{
		if (m_animInterval > 6)
		{
			animFrameMana.x++;
			m_animInterval = 0;
			if (animFrameMana.x > 5)
			{
				animFrameMana.x = 0;
			}
		}
	}
	
	if (m_Hp <= 0)
	{
		m_isDeathFlag = true;
	}
	
	m_pos += m_velocity;
	m_animInterval++;
}

void EnemyToPlayerDir::Draw()
{
	if (m_isDeathFlag == false)
	{
		DrawRectRotaGraphF(m_pos.x - m_screenMove, m_pos.y, 0 + animDisX * animFrameMana.x, 0 + animDisY * animFrameMana.y, 220, 170, 1, m_isRight, m_handle, true);
		
	}
}

void EnemyToPlayerDir::WantPlayerPoint(Player* player)
{
	m_player = player;
}

void EnemyToPlayerDir::OnDamage(int Atk)
{
	m_Hp -= Atk;
}

void EnemyToPlayerDir::OnHitShot()
{
}

void EnemyToPlayerDir::OnMapCol(Vec2 colRange)
{
	m_isMapCol = true;
	m_pos.y = m_colRect.bottom - 80;
	m_pos += colRange;
}


