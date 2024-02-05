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

	delr = m_radius + m_player->GetColRadius();

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
	if (m_isEffectFlag == true)
	{
		if (m_shotEffect != nullptr)
		{
			m_shotEffect->Update();
		}
	}
}

void EneShot::Draw(int screenMove)
{
	m_screenMove = screenMove;
	if (m_isInVisible == false)
	{
		DrawGraph(m_shotPos.x-m_screenMove, m_shotPos.y, m_handle, true);
		//DrawBox(m_shotPos.x - m_screenMove, m_shotPos.y, m_shotPos.x + m_radius*2 - m_screenMove, m_shotPos.y + m_radius*2,0xff0000,0);
		DrawFormatString(50, 50, 0xffffff, "%d", m_screenMove);
	}
	if (m_isEffectFlag == true)
	{
		if (m_shotEffect != nullptr)
		{
			m_shotEffect->Draw();
		}
	}
}

void EneShot::ShotProgram()
{
	
}

bool EneShot::GetShotColli()
{
	//プレイヤーと弾(自分)の距離を計算
	float  delx =(m_shotPos.x - m_screenMove - m_player->GetPos().x);//弾からプレイヤーへのベクトルを作成し、その大きさ
	float dely = m_shotPos.y - m_player->GetPos().y;

	float del = sqrt((delx * delx) + (dely * dely));
	//当たり判定
	if (del <= delr)
	{
		m_isDestroy = true;
		m_isEffectFlag = true;
		return true;
	}
	return false;
}

void EneShot::OnCollision()
{
	
	
}

void EneShot::OnDestroy()
{
	m_isDestroy = true;
}

void EneShot::CollisionUpdate()
{
	
}

void EneShot::OnHit()
{
	
	
}
