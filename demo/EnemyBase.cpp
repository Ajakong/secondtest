#include"Dxlib.h"
#include<vector>
#include <iostream>
#include"Game.h"
#include"Object.h"
#include "EnemyBase.h"
#include"EneShotEffect.h"
#include"EneShot.h"
#include"EneDeathEffect.h"
#include"Player.h"
#include"SceneMain.h"

namespace
{
	constexpr int animDisX = 288;
	constexpr int animDisY = 112;
}

EnemyBase::EnemyBase() :
	m_isDeathFlag(false),
	m_Hp(50),
	m_pos(500.0f,200.0f),
	m_velocity(0.0f,0.0f),
	animFrameMana(0,0),
	m_fireDir(1.0f,0.0f),
	m_isShotCollFlag(false),
	m_attackFrame(0)
{
	/*for (auto& shot : m_shot)
	{
		shot = nullptr;
	}*/
	
	m_colRect.top = m_pos.y;
	m_colRect.bottom = m_pos.y + 130;
	m_colRect.left = m_pos.x;
	m_colRect.right = m_pos.x + 75;
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init(Vec2 pos)
{
	m_handle = LoadGraph("data/image/Enemy/enemyDevilSlime.png");
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
	m_shotGraph = LoadGraph("data/image/eneShot.png");
	m_pos = pos;
}

void EnemyBase::CollisionUpdate()
{
	m_colRect.top = m_pos.y;
	m_colRect.bottom = m_pos.y + 50;
	m_colRect.left = m_pos.x-m_screenMove;
	m_colRect.right = m_pos.x + 50-m_screenMove;
}

void EnemyBase::Update()
{
	CollisionUpdate();
	m_attackFrame++;

	if (m_player != nullptr)
	{
		m_targetPos.x = m_player->GetRect().right+20;
		m_targetPos.y = m_player->GetRect().top + 50;
		m_velocity.x = (m_targetPos.x+40 - m_pos.x)* (m_targetPos.x+40 - m_pos.x);
		m_velocity.y = (m_targetPos.y - m_pos.y)* (m_targetPos.y - m_pos.y);
		m_distance = sqrt(m_velocity.x + m_velocity.y);

		if (m_distance < 1000)
		{
			m_fireDir = m_velocity;
			m_fireDir.Normalize();
			
			{
				if (m_attackFrame >= 60)
				{
					m_shot.push_back(std::make_shared<EneShot>(m_pos, m_fireDir, m_shotGraph,m_player));
					//for (int i = i < m_shot.size()-1; i < m_shot.size(); i++)
					{
						
						//if (!m_shotIt)
						{

							m_pos.x -= m_screenMove;
							m_shot.back()->ShotProgram();
							m_WorldMana->AddEneShot(m_shot.back());
							m_attackFrame = 0;
							m_pos.x += m_screenMove;
						
						
						}

						
					}
					
				}
			}
		}
		for (int i = 0; i < m_shot.size(); i++)
		{
			m_shot[i]->Update();
			if (m_shot[i]->GetIsDestroy())
			{
				m_shot[i].reset();
				
			}
		}

		for (int i = 0; i < m_EneDeathEffect.size(); i++)
		{
			m_EneDeathEffect[i]->Update();
			if (m_EneDeathEffect[i]->OnDestroy())
			{
				m_EneDeathEffect[i].reset();
				m_EneDeathEffect.erase(m_EneDeathEffect.begin());
			}
		}
	}
}

void EnemyBase::Draw()
{
	if(m_isDeathFlag==false)
	{
		DrawBox(m_colRect.left, m_colRect.top, m_colRect.right, m_colRect.bottom, 0xff0000, true);
		DrawPixel(m_pos.x-m_screenMove + 25, m_pos.y + 25, 0x000000);
		for (int i = 0; i < m_shot.size(); i++)
		{
			if (m_shot[i] != nullptr)
				m_shot[i]->Draw(m_screenMove);
		}
	}

	for (int i = 0; i < m_EneDeathEffect.size(); i++)
	{
		m_EneDeathEffect[i]->Draw(m_screenMove);
	}
}

void EnemyBase::OnHitShot()
{
	m_Hp -= 10;
	if(m_Hp<0)
	{
		m_EneDeathEffect.push_back(std::make_shared<EneDeathEffect>(m_pos.x - m_screenMove, m_pos.y));
		m_WorldMana->AddScore(10000000);
		m_isDeathFlag = true;
	}
}

void EnemyBase::WantPlayerPoint(Player* player)
{
	m_player = player;
}

void EnemyBase::GetScreenMove(float veloX)
{
}

bool EnemyBase::OnDie()
{
	for (int i = 0; i < m_EneDeathEffect.size(); i++)
	{
		if (m_EneDeathEffect[i]->GetOnDestroy())
		{
			return m_isDeathFlag;
		}
	}
	return false;
}
