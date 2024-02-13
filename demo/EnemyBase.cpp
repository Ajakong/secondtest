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

#include"FullAutoGun.h"
#include"Spread.h"
#include"LaserItem.h"
#include"CircleBulletItem.h"


namespace
{
	constexpr int animDisX = 288;
	constexpr int animDisY = 112;
}

EnemyBase::EnemyBase(int sound,int fullAutoGunGraph,int spreadGraph,int laserItem,int CircleBulletItem,int handle) :
	m_isDeathFlag(false),
	m_Hp(20),
	m_pos(500.0f,200.0f),
	m_velocity(0.0f,0.0f),
	animFrameMana(0,0),
	m_fireDir(1.0f,0.0f),
	m_isShotCollFlag(false),
	m_attackFrame(0),
	m_fullAutoGunGraph(fullAutoGunGraph),
	m_spreadGraph(spreadGraph),
	m_laserItemGraph(laserItem),
	m_CircleItemGraph(CircleBulletItem)
{
	/*for (auto& shot : m_shot)
	{
		shot = nullptr;
	}*/
	
	m_colRect.top = m_pos.y;
	m_colRect.bottom = m_pos.y + 130;
	m_colRect.left = m_pos.x;
	m_colRect.right = m_pos.x + 75;

	m_deathSoundHandle = sound;

	m_itemNumber = GetRand(4) % 4;
	
	m_handle = handle;
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init(Vec2 pos,int shotgraph)
{
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
	m_shotGraph = shotgraph;
	m_pos = pos;
}

void EnemyBase::CollisionUpdate()
{
	m_colRect.top = m_pos.y;
	m_colRect.bottom = m_pos.y +75;
	m_colRect.left = m_pos.x-m_screenMove;
	m_colRect.right = m_pos.x + 75-m_screenMove;
}

void EnemyBase::Update()
{
	CollisionUpdate();
	m_attackFrame++;
	if (m_attackFrame > 120)
	{
		m_attackFrame = 120;
	}

	if (m_player != nullptr)
	{
		m_targetPos.x = m_player->GetRect().right+20;
		m_targetPos.y = m_player->GetRect().top;
		/*
		m_velocity.x = (m_targetPos.x+40 - m_pos.x)* (m_targetPos.x+40 - m_pos.x);
		m_velocity.y = (m_targetPos.y - m_pos.y)* (m_targetPos.y - m_pos.y);
		m_distance = sqrt(m_velocity.x + m_velocity.y);*/

		float  delx = m_player->GetPos().x-(m_pos.x - m_screenMove) ;
		m_velocity.x = delx;
		float dely = m_player->GetPos().y-m_pos.y ;
		m_velocity.y = dely;
		float del = sqrt((delx * delx) + (dely * dely));

		m_distance = del;
		if (m_distance < 710)
		{
			m_fireDir.x = m_velocity.x;
			m_fireDir.y = m_velocity.y;
			m_fireDir.Normalize();
			if (m_attackFrame >= 120)
			{
				m_shot.push_back(std::make_shared<EneShot>(m_pos, m_fireDir, m_shotGraph,m_player));
				for (int i = m_shot.size()-1; i < m_shot.size(); i++)
				{
					
					m_pos.x -= m_screenMove;
					m_shot.back()->ShotProgram();
					m_WorldMana->AddEneShot(m_shot.back());
					m_attackFrame = 0;
					m_pos.x += m_screenMove;
				}
			}
			
		}
		for (int i = 0; i < m_shot.size(); i++)
		{
 			m_shot[i]->Update();
			if (m_shot[i]->GetIsDestroy())
			{
				m_shot.erase(m_shot.begin() + i);
			}
		}

		for (int i = 0; i < m_EneDeathEffect.size(); i++)
		{
			m_EneDeathEffect[i]->Update();
			if (m_EneDeathEffect[i]->OnDestroy())
			{
				m_EneDeathEffect.erase(m_EneDeathEffect.begin()+i);
			}
		}
	}

	m_addFrame+=0.04f;
}

void EnemyBase::Draw()
{
	if(m_isDeathFlag==false)
	{
		DrawBox(m_colRect.left, m_colRect.top, m_colRect.right, m_colRect.bottom, 0xff0000, true);
		SetDrawBlendMode(DX_BLENDMODE_ADD, sin(m_addFrame) * 255);
		DrawBox(m_colRect.left, m_colRect.top, m_colRect.right, m_colRect.bottom, 0xdddd11, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawGraph(m_colRect.left, m_colRect.top, m_handle, true);
		
		/*SetDrawBlendMode(DX_BLENDMODE_ADD,m_attackFrame * 2);
		DrawCircle(m_colRect.left + 37.5f, m_colRect.top+37.5f,m_attackFrame/10, 0xffaa11);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);*/
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
		if (!m_isDeathFlag)
		{
			m_ItemThrowVel.x = 4;
			m_ItemThrowVel.y = -5;

			if (m_itemNumber == 0)
			{
				m_item = make_shared<FullAutoGun>(m_pos, m_ItemThrowVel, m_fullAutoGunGraph);
			}
			if (m_itemNumber == 1)
			{
				m_item = make_shared<Spread>(m_pos, m_ItemThrowVel, m_spreadGraph);
			}
			if (m_itemNumber == 2)
			{
				m_item = make_shared<LaserItem>(m_pos, m_ItemThrowVel, m_laserItemGraph);
			}
			if (m_itemNumber == 3)
			{
				m_item = make_shared<CircleBulletItem>(m_pos, m_ItemThrowVel, m_CircleItemGraph);
			}

			PlaySoundMem(m_deathSoundHandle, DX_PLAYTYPE_BACK);
			m_EneDeathEffect.push_back(std::make_shared<EneDeathEffect>(m_pos.x - m_screenMove + 20, m_pos.y + 25));
			m_WorldMana->AddScore(2000000);
			m_WorldMana->AddItem(m_item);
			m_isDeathFlag = true;
		}
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
