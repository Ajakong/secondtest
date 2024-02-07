#include"Dxlib.h"
#include <iostream>
#include"Game.h"
#include"Object.h"
#include"Shot.h"
#include "EnemyBase.h"
#include "Boss.h"
#include"BossSphere.h"
#include"EneShot.h"
#include"Player.h"
#include"SceneMain.h"

Boss::Boss(SceneMain* mana) :
	m_isDeathFlag(false),
	m_Hp(1600),
	m_pos(8000.0f, 0.0f),
	m_velocity(0.0f, 0.0f),
	animFrameMana(0, 0),
	m_fireDir(1.0f, 0.0f),
	m_isShotCollFlag(false),
	m_attackFrame(0)	
{
	
	/*for (auto& shot : m_shot)
	{
		shot = nullptr;
	}*/

	m_bossSphere = std::make_shared<BossSphere>(this);

	m_colRect.top = m_pos.y;
	m_colRect.bottom = m_pos.y + 896;
	m_colRect.left = m_pos.x;
	m_colRect.right = m_pos.x + 500;

	/*m_shotGraph =  LoadGraph("data/image/eneShot.png") ;*/

	m_WorldMana = mana;
	//m_shot = nullptr;
}

Boss::~Boss()
{
}

void Boss::Init()
{
	m_bossSphere->Init();
}

void Boss::CollisionUpdate()
{
}

void Boss::Update()
{
	CollisionUpdate();
	MissilePoint.x = m_pos.x + 320;
	MissilePoint.y = m_pos.y + 420;

	m_attackFrame++;
	
	m_velocity.x = (m_targetPos.x - m_pos.x) * (m_targetPos.x - m_pos.x);
	m_velocity.y = (m_targetPos.y - m_pos.y) * (m_targetPos.y - m_pos.y);
	m_distance = sqrt(m_velocity.x + m_velocity.y);

	m_bossSphere->Update();
		if (m_distance < 1000)
		{
			m_fireDir = m_velocity;
			m_fireDir.Normalize();
			for (int i = 0; i < 10; i++)
			{
				if (m_attackFrame >= 60)
				{
					//if (m_shot[i] == nullptr)
					//{
					//	m_shot[i] = std::make_shared<EneShot>();

					//	//m_shot[i]->ShotProgram(m_pos, m_fireDir, m_shotGraph);
					//	m_WorldMana->AddEneShot(m_shot[i]);
					//	m_attackFrame = 0;
					//	break;

					//}
				}
			}
		}
}

void Boss::Draw()
{
	if (m_isDeathFlag == false)
	{
		//DrawBox(m_pos.x-m_screenMove, m_pos.y+300, m_pos.x + 500-m_screenMove, m_pos.y +896, 0xaaaaaa, true);
		//DrawBox(m_pos.x - 170- m_screenMove, m_pos.y + 450, m_pos.x- m_screenMove, m_pos.y + 470, 0x660066, true);//‰œ
		//DrawBox(m_pos.x+200- m_screenMove, m_pos.y+100, m_pos.x +320- m_screenMove, m_pos.y + 420, 0x00dddd, true);//Žè‘O
		//
		//DrawPixel(m_pos.x + 25- m_screenMove, m_pos.y + 25, 0x000000);
		
		//DrawRectRotaGraphF(m_pos.x, m_pos.y, 0 + animDisX * animFrameMana.x, 0 + animDisY * animFrameMana.y, 220, 170, 1, 0, m_handle, true);
	}

	////////////
	m_bossSphere->Draw();
}

void Boss::OnHitShot()
{
	m_Hp -= 10;
	if (m_Hp < 0)
	{
		m_isDeathFlag = true;
	}
}

void Boss::WantPlayerPoint(Player* player)
{
	m_player = player;
}



bool Boss::OnDie()
{
	return false;
}
