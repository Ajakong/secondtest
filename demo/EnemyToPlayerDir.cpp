#include"Dxlib.h"
#include<cmath>
#include <iostream>
#include"Game.h"
#include"Object.h"
#include "EnemyBase.h"
#include"HitEffect.h"
#include"EnemyMoveEffect.h"
#include"EnemyAttackEffect.h"
#include"EnemyBornEffect.h"
#include"Player.h"
#include"SceneMain.h"
#include "EnemyToPlayerDir.h"

namespace
{
	constexpr int animDisX = 288;
	constexpr int animDisY = 162;

	constexpr int collisionSizeX = 45;
	constexpr int collisionSizeY = 80;
}


EnemyToPlayerDir::EnemyToPlayerDir(Vec2 pos, int deathSound):
	m_isDeathFlag(false),
	m_Hp(24),
	m_pos(0.0f, 0.0f),
	m_velocity(0.0f, 0.0f),
	animFrameMana(0, 0),
	m_fireDir(1.0f, 0.0f),
	m_isShotCollFlag(false),
	m_attackFrame(0),
	m_isDesitionMyWay(false)
{
	m_enemyUpdate = &EnemyToPlayerDir::SpawnUpdate;
	m_hole = true;
	m_pos = pos;
	m_firstPos = pos;
	m_deathSound = deathSound;
	m_bornEffect = std::make_shared<EnemyBornEffect>();
	m_bornEffect->CreateEffect(m_pos, 0, 0, m_screenMove);
}

EnemyToPlayerDir::~EnemyToPlayerDir()
{
}

void EnemyToPlayerDir::Init(Player* player,int handle)
{
	m_handle = handle;
	
	m_player = player;
	m_velocity.y = 0;
}

void EnemyToPlayerDir::CollisionUpdate()
{
	m_colRect.top = m_pos.y;
	m_colRect.bottom = m_pos.y + collisionSizeY;
	m_colRect.left = m_pos.x-m_screenMove-20;
	m_colRect.right = m_pos.x +collisionSizeX-m_screenMove-20;
}

void EnemyToPlayerDir::Update()
{
	
	if (m_isRight)
	{
		m_dirX = -1;
	}
	else
	{
		m_dirX = 1;
	}
	(this->*m_enemyUpdate)();//状態遷移
	
	

	if (!m_moveEffect.empty())
	{
		for (int i = 0; i < m_moveEffect.size(); i++)
		{
			m_moveEffect[i]->Update();
		}
		auto it = remove_if(m_moveEffect.begin(), m_moveEffect.end(), [](const auto& a)//リターンされるものを避ける(1,2,3,4,5)で3,4をリターンしたら(1,2,5,3,4)になる
			{
				return a->GetDestroyFlag();
			});
		
		m_moveEffect.erase(it, m_moveEffect.end());//さっきの例をそのまま使うと(1,2,5,3,4)でitには5まで入ってるので取り除きたい3,4はitからend()までで指定できる
	}
	
	if (!m_HitEffect.empty())
	{
		for (int i = 0; i < m_HitEffect.size(); i++)
		{
			m_HitEffect[i]->Update();
		}
		auto it = remove_if(m_HitEffect.begin(), m_HitEffect.end(), [](const auto a)//リターンされるものを避ける(1,2,3,4,5)で3,4をリターンしたら(1,2,5,3,4)になる
			{
				return a->OnDestroy();
			});

		m_HitEffect.erase(it, m_HitEffect.end());//さっきの例をそのまま使うと(1,2,5,3,4)でitには5まで入ってるので取り除きたい3,4はitからend()までで指定できる
	}
	for (int i = 0; i < m_attackEffect.size(); i++)
	{
		m_attackEffect[i]->Update();
	}
	if (!m_attackEffect.empty())
	{
		auto it = remove_if(m_attackEffect.begin(), m_attackEffect.end(), [](const auto& a)//リターンされるものを避ける(1,2,3,4,5)で3,4をリターンしたら(1,2,5,3,4)になる
			{
				return a->GetDestroyFlag();
			});

		m_attackEffect.erase(it, m_attackEffect.end());//さっきの例をそのまま使うと(1,2,5,3,4)でitには5まで入ってるので取り除きたい3,4はitからend()までで指定できる
	}

	if (m_bornEffect != nullptr)
	{
		m_bornEffect->Update();
	}


}

void EnemyToPlayerDir::Draw()
{

	for (int i = 0; i < m_moveEffect.size();i++)
	{
		m_moveEffect[i]->Draw(m_screenMove);
	}

	if (m_isDeathFlag == false)
	{
		DrawRectRotaGraphF(m_pos.x - m_screenMove,m_pos.y, 30 + animDisX * animFrameMana.x,animDisY * animFrameMana.y, 220, 170, 1,0, m_handle, true, m_isRight,false);
	}
	for (int i = 0; i < m_HitEffect.size(); i++)
	{
		m_HitEffect[i]->Draw(m_screenMove);
	}
	for (int i = 0; i < m_attackEffect.size(); i++)
	{
		m_attackEffect[i]->Draw(m_screenMove);
	}
	if (m_bornEffect != nullptr)
	{
		m_bornEffect->Draw(m_screenMove);
	}

	DrawCircle(m_firstPos.x, m_firstPos.y-500,50, 0xaa1100,false,5);
	DrawCircle(m_firstPos.x, m_firstPos.y-500,40, 0xffbb00, false,5);
	DrawCircle(m_firstPos.x, m_firstPos.y-500,30, 0xffeeaa, false,5);
	DrawCircle(m_firstPos.x, m_firstPos.y-500,20, 0xffffaa, false,5);
	DrawCircle(m_firstPos.x, m_firstPos.y-500,10, 0xffffff, false,5);
	
	//DrawBox(m_colRect.left, m_colRect.bottom, m_colRect.right, m_colRect.top,0x00ff00,false);
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

void EnemyToPlayerDir::OnPlayerHit()
{
	m_HitEffect.push_back(std::make_shared<HitEffect>(m_pos.x - m_screenMove,m_pos.y,m_screenMove));
}

void EnemyToPlayerDir::SpawnUpdate()
{
	m_velocity.x = 0;
	m_velocity.y = 0.0f;
	m_velocity.y += 9.8f;

	CollisionUpdate();

	if (m_isMapCol)
	{
		m_enemyUpdate = &EnemyToPlayerDir::IdleUpdate;
	}

	m_pos += m_velocity;

}

void EnemyToPlayerDir::IdleUpdate()
{
	m_velocity.x = 0;
	m_velocity.y = 0.0f;
	m_velocity.y += 9.8f;
	m_playerPos.x = m_player->GetPos().x + m_screenMove;
	m_playerPos.y = m_player->GetPos().y;

	m_dis = sqrt((m_playerPos.x - m_pos.x) * (m_playerPos.x - m_pos.x) + (m_playerPos.y - m_pos.y) * (m_playerPos.y - m_pos.y));

	CollisionUpdate();
	
	if(m_idleMoveFrame>200)
	{
		m_moveNumber= GetRand(1);//0の時に徘徊、1の時待機
	}

	if (m_moveNumber == 0)
	{
		
		//m_enemyUpdate = &EnemyToPlayerDir::WanderingUpdate;
	}
	
	if (m_player != nullptr)
	{
		if (abs(m_dis) < 600&& (m_playerPos.y - m_pos.y)<300)
		{
			if (m_isDesitionMyWay == false)
			{
				m_velocity.x = m_player->GetPos().x + m_screenMove - m_pos.x;
				m_velocity.Normalize();
				m_isDesitionMyWay = true;
			}
		}

		if (m_isDesitionMyWay)
		{
			m_isAttack = true;
			if ((m_player->GetPos().x + m_screenMove - m_pos.x) < 0)
			{
				m_isRight = false;
			}
			else
			{
				m_isRight = true;
			}
			
			m_enemyUpdate = &EnemyToPlayerDir::NeutralUpdate;
		}
	}
	if (m_animInterval > 6)
	{
		animFrameMana.x++;
		m_animInterval = 0;
		if (animFrameMana.x > 5)
		{
			animFrameMana.x = 0;
		}
	}

	m_pos += m_velocity;
	m_animInterval++;

	if (m_Hp <= 0)
	{
		PlaySoundMem(m_deathSound, DX_PLAYTYPE_BACK);
		m_WorldMana->AddScore(20000);
		m_enemyUpdate = &EnemyToPlayerDir::DyingUpdate;
	}
	m_idleMoveFrame++;
}

void EnemyToPlayerDir::NeutralUpdate()
{

	m_velocity.y = 0.0f;
	m_velocity.y += 9.8f;
	CollisionUpdate();
	m_playerPos.x = m_player->GetPos().x + m_screenMove;
	m_playerPos.y = m_player->GetPos().y;

	m_dis = sqrt((m_playerPos.x - m_pos.x) * (m_playerPos.x - m_pos.x) + (m_playerPos.y - m_pos.y) * (m_playerPos.y - m_pos.y));
	
	if (abs(m_dis) < 40)
	{
		animFrameMana.x = 8;
		for (int i = 0; i < 8; i++)
		{
			m_attackEffect.push_back(std::make_shared<EnemyAttackEffect>(m_screenMove, GetRand(5) - 4, GetRand(6) - 12));
			for (int i = 0; i < m_attackEffect.size(); i++)
			{
				Vec2 effectPos(m_colRect.left - 10, m_colRect.bottom);
				m_attackEffect[i]->CreateEffect(effectPos, 0, 0, m_screenMove);
			}
		}
		m_enemyUpdate = &EnemyToPlayerDir::AttackUpdate;
	}
	else
	{
		if (m_player != nullptr)
		{
			m_isMapCol = false;
		}
		if (m_animInterval > 6)
		{
			animFrameMana.y = 1;
			animFrameMana.x++;
			m_animInterval = 0;
			if (animFrameMana.x > 11)
			{
				animFrameMana.x = 0;
			}
		}
		m_moveEffect.push_back(std::make_shared<EnemyMoveEffect>());
		for (int i = m_moveEffect.size() - 1; i < m_moveEffect.size(); i++)
		{
			m_enemyMoveEffectOffsetY = GetRand(50)+50;
			if (m_velocity.x > 0)
			{
				
			}
			if (m_velocity.x < 0)
			{

			}
			if (m_enemyWalkEffectFrame > 10)
			{
				m_moveEffect[i]->CreateEffect(m_footPos, 0, m_enemyMoveEffectOffsetY,m_screenMove);
				m_enemyWalkEffectFrame = 0;
			}
			
		}

		m_enemyWalkEffectFrame++;
		m_pos += m_velocity;
		m_footPos.x = m_colRect.right;
		m_footPos.y = m_pos.y;
		
	}

	/*for (int i = 0; i < m_HitEffect.size(); i++)
	{
		m_HitEffect[i]->Update();
		if (m_HitEffect[i]->OnDestroy())
		{
			m_HitEffect.erase(m_HitEffect.begin()+i);
		}
	}*/
	
	
	m_animInterval++;

	if (m_Hp <= 0)
	{
		PlaySoundMem(m_deathSound, DX_PLAYTYPE_BACK);
		m_WorldMana->AddScore(20000);
		m_enemyUpdate = &EnemyToPlayerDir::DyingUpdate;
	}
}

void EnemyToPlayerDir::AttackUpdate()
{
	m_playerPos.x = m_player->GetPos().x + m_screenMove;
	m_playerPos.y = m_player->GetPos().y;

	m_dis = sqrt((m_playerPos.x - m_pos.x) * (m_playerPos.x - m_pos.x) + (m_playerPos.y - m_pos.y) * (m_playerPos.y - m_pos.y));

	if (m_animInterval > 6)
	{
		animFrameMana.y = 2;
		animFrameMana.x++;
		m_animInterval = 0;
		if (animFrameMana.x > 14)
		{
			animFrameMana.x = 0;
			m_enemyUpdate = &EnemyToPlayerDir::NeutralUpdate;
		}
	}
	
	for (int i = 0; i < m_HitEffect.size(); i++)
	{
		m_HitEffect[i]->Update();
		if (m_HitEffect[i]->OnDestroy())
		{
			m_HitEffect.erase(m_HitEffect.begin()+i);
		}
	}

	m_animInterval++;

	if (m_Hp <= 0)
	{
		PlaySoundMem(m_deathSound, DX_PLAYTYPE_BACK);
		m_WorldMana->AddScore(20000);
		m_enemyUpdate = &EnemyToPlayerDir::DyingUpdate;
	}
}

void EnemyToPlayerDir::DyingUpdate()
{
	m_velocity.x = 0.0f;
	/*m_velocity.y = 0.0f;
	
	m_velocity.y += 9.8f;
	CollisionUpdate();*/
	m_colRect.top = -2000;
	m_colRect.bottom = -2000;
	m_colRect.left = -2000;
	m_colRect.right = -2000;
	if (m_animInterval > 6)
	{
		animFrameMana.y = 4;
		animFrameMana.x++;
		m_animInterval = 0;
		if (animFrameMana.x > 22)
		{
			m_isDeathFlag = true;
		}
	}
	
	m_animInterval++;
}

void EnemyToPlayerDir::WanderingUpdate()
{
	m_velocity.y = 0.0f;
	m_velocity.y += 9.8f;
	CollisionUpdate();
	
	if (m_wanderingInterval > 500)
	{
		m_moveNumber=GetRand(2);
	}

	
	if (m_player != nullptr)
	{
		m_isMapCol = false;
	}
	if (m_animInterval > 6)
	{
		animFrameMana.y = 1;
		animFrameMana.x++;
		m_animInterval = 0;
		if (animFrameMana.x > 11)
		{
			animFrameMana.x = 0;
		}
	}
	m_pos += m_velocity;


	m_wanderingInterval++;
	m_animInterval++;
}


