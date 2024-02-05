#include"Dxlib.h"
#include"Game.h"
#include"Object.h"
#include"Player.h"
#include"EnemyBase.h"
#include<cmath>
#include "EneShot.h"
#include"EneShotEffect.h"

EneShot::EneShot(const Vec2& Spos, const Vec2& DirVec, const int& graph,const Player* p_player):
	m_handle(-1),
	m_shotPos(0, 0),
	m_isInVisible(false),
	m_Velocity(0, 0),
	m_radius(15),
	m_isDestroy(false),
	m_player(p_player)
{
	m_isInVisible = false;
	m_shotPos = Spos;
	m_Velocity = DirVec;
	m_handle = graph;
	m_Velocity.Normalize();
}

EneShot::~EneShot()
{
}

void EneShot::Init()
{
	CollisionUpdate();
	
}

void EneShot::Update()
{
	
	CollisionUpdate();
	if (m_screenMove > 0)
	{
		int b = 0;
	}
	////collisionの更新
	//m_collider.pos = m_shotPos; m_collider.radius = m_radius;

	if (m_isInVisible == false)
	{
	/*	m_enePos = m_enemy->GetEnePos();
		m_Velocity.x = (m_enePos.x-m_shotPos.x);
		m_Velocity.y = (m_enePos.y- m_shotPos.y);
		m_Velocity.Normalize();*/

		
		m_shotPos += m_Velocity * 10.0f;
	}
	/*if (m_isEffectFlag == true)
	{
		if (m_shotEffect[0] != nullptr)
		{
			m_shotEffect[0]->Update();
		}
	}*/
}

void EneShot::Draw(int screenMove)
{
	m_screenMove = screenMove;
	if (m_isInVisible == false)
	{
		DrawGraph(m_shotPos.x-m_screenMove, m_shotPos.y, m_handle, true);
		DrawBox(m_shotPos.x - m_screenMove, m_shotPos.y, m_shotPos.x + m_radius*2 - m_screenMove, m_shotPos.y + m_radius*2,0xff0000,0);
		DrawFormatString(50, 50, 0xffffff, "%d", m_screenMove);
	}
	/*for (int i = 0; i < m_shotEffect.size(); i++)
	{
		if (m_isEffectFlag == true)
		{
			for (int i = 0; i < m_shotEffect.size(); i++)
			{
				if (m_shotEffect[i] != nullptr)
				{
					m_shotEffect[i]->Draw();

				}

			}
		}
	}*/
	
}

void EneShot::ShotProgram()
{
	
}

bool EneShot::GetShotColli()
{
	

	//プレイヤーと弾(自分)の距離を計算
	int  del = (int)(m_shotPos - m_player->GetPos()).Length();//弾からプレイヤーへのベクトルを作成し、その大きさ
	int delr = m_radius + 20;
	//当たり判定
	if (del < delr)
	{
		return true;
	}
	return false;
}

void EneShot::OnCollision()
{
	m_isInVisible = true;
	m_isEffectFlag = true;
	//m_shotEffect[0]->WantHitPos( m_shotPos);
}

void EneShot::OnDestroy()
{
	/*for(int i=0;i<m_shotEffect.size();i++)
	{
		m_shotEffect[i] = nullptr;
	}*/
	m_isDestroy = true;
}

void EneShot::CollisionUpdate()
{
	
}

void EneShot::OnHit()
{
	m_isInVisible = true;
	m_isEffectFlag = true;
	//m_shotEffect[0]->WantHitPos( m_shotPos);
}
