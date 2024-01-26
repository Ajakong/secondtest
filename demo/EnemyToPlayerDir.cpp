#include"Dxlib.h"
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
	constexpr int animDisY = 112;

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
	m_attackFrame(0)
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
	m_velocity.x = m_player->GetPos().x - m_pos.x;
	
	m_velocity.x = m_velocity.x * 3;
	m_velocity.Normalize();
		
}

void EnemyToPlayerDir::CollisionUpdate()
{
	m_colRect.top = m_pos.y;
	m_colRect.bottom = m_pos.y + collisionSizeY;
	m_colRect.left = m_pos.x;
	m_colRect.right = m_pos.x +collisionSizeX;
}

void EnemyToPlayerDir::Update()
{
	m_velocity.y = 0;
	
	CollisionUpdate();
	if (m_player != nullptr)
	{
		if (m_isMapCol)
		{
			m_velocity.y = 0;
			
		}
		if (!m_isMapCol)
		{
			m_velocity.y += 9.8f;
			m_pos += m_velocity;
		}
		m_isMapCol = false;
	}
	if (m_pos.y > Game::kScreenHeight - 130)
	{
		m_pos.y = Game::kScreenHeight - 130;

	}
	if (m_pos.x > Game::kScreenWidth - 75)
	{
		m_pos.x = Game::kScreenWidth - 75;

	}
	if (m_pos.y < 0)
	{
		m_pos.y = 0.0f;
	}
	if (m_pos.x < 0)
	{
		m_pos.x = 0.0f;
	}
}

void EnemyToPlayerDir::Draw()
{
	if (m_isDeathFlag == false)
	{
		DrawRectRotaGraphF(m_pos.x - m_screenMove, m_pos.y, 0 + animDisX * animFrameMana.x, 0 + animDisY * animFrameMana.y, 220, 170, 1, 0, m_handle, true);
		DrawFormatString(50, 50, 0xffffff, "%d", m_screenMove);
	}
}

void EnemyToPlayerDir::WantPlayerPoint(Player* player)
{
	m_player = player;
}

void EnemyToPlayerDir::OnHitShot()
{
}

void EnemyToPlayerDir::OnMapCol(Vec2 colRange)
{
	m_isMapCol = true;
	m_pos += colRange;
}

bool EnemyToPlayerDir::OnDie()
{
	return false;
}
