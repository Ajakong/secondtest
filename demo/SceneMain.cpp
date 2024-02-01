#include<stdio.h>

#include "SceneMain.h"
#include"DxLib.h"
#include"Game.h"
#include"Object.h"
#include"Player.h"
#include"Map.h"
#include"Boss.h"
#include"EnemyBase.h"
#include"EnemyToPlayerDir.h"
#include"EneShot.h"
#include"Shot.h"
#include"Laser.h"
#include"CircleShot.h"
#include"ImageGroundManager.h"
#include"Pad.h"

SceneMain::SceneMain():
	m_screenMove(0),
	m_bgHandle(0),
	m_wipeFrame(0),
	m_enemyInterval(0),
	m_shakeFrame(0),
	m_gameScreenhandle(0),
	m_gameScreenHandle(0),
	bossZone (false)
{
	for (auto& shot : m_pShot)
	{
		shot = nullptr;
	}
	
	for (auto& shot : m_circleShot)
	{
		shot = nullptr;
	}
	for (auto& shot : m_eneShot)
	{
		shot = nullptr;
	}
	m_pPlayer = new Player{this};
	m_pMap = new Map{m_pPlayer};
	m_pBgManager = new ImageGroundManager;
	m_pBoss = new Boss{this};
	
	for (int i = 0; i < ENEMY_NUM; i++)m_pEnemy[i] = new EnemyBase;
	
	m_pLaser = nullptr;

	m_enePos[0] = Vec2(100, 50);
	m_enePos[1] = Vec2(850, 700);
	m_enePos[2] = Vec2(1500, 800);
	m_enePos[3] = Vec2(2400, 800);
	m_enePos[4] = Vec2(3200, 0);
	m_enePos[5] = Vec2(6000, 800);
	m_enePos[6] = Vec2(6500, 800);
	m_enePos[7] = Vec2(7100, 0);
	m_enePos[8] = Vec2(5000, 0);
	m_enePos[9] = Vec2(5500, 800);

	m_eneToPlayerPos[0] = Vec2(800, 0);
	m_eneToPlayerPos[1] = Vec2(850, 0);
	m_eneToPlayerPos[2] = Vec2(600, 0);
	m_eneToPlayerPos[3] = Vec2(1200, 0);
	m_eneToPlayerPos[4] = Vec2(1250, 0);
	m_eneToPlayerPos[5] = Vec2(1300, 0);
	m_eneToPlayerPos[6] = Vec2(1800, 0);
	m_eneToPlayerPos[7] = Vec2(2200, 0);
	m_eneToPlayerPos[8] = Vec2(2500, 0);
	m_eneToPlayerPos[9] = Vec2(2900, 0);
	m_eneToPlayerPos[10] = Vec2(3400, 500);
	m_eneToPlayerPos[11] = Vec2(3850, 500);
	m_eneToPlayerPos[12] = Vec2(3900, 0);
	m_eneToPlayerPos[13] = Vec2(4200, 0);
	m_eneToPlayerPos[14] = Vec2(4250, 500);
	m_eneToPlayerPos[15] = Vec2(5300, 0);
	m_eneToPlayerPos[16] = Vec2(5400, 0);
	m_eneToPlayerPos[17] = Vec2(5500, 500);
	m_eneToPlayerPos[18] = Vec2(5700, 0);
	m_eneToPlayerPos[19] = Vec2(6000, 0);

}

SceneMain::~SceneMain()
{
	for (auto& shot : m_pShot)
	{
		delete shot;
	}

	for (auto& shot : m_circleShot)
	{
		delete shot;
	}
	for (auto& shot : m_eneShot)
	{
		delete shot;
	}
	delete m_pPlayer ;
	delete m_pMap ;
	delete m_pBgManager ;
	for (int i = 0; i < ENEMY_NUM; i++)delete m_pEnemy[i] ;
	for (int e = 0; e < ENEMY_TO_PLAYER_NUM; e++)delete m_pEnemyToPlayer[e];
	delete m_pBoss;
	delete m_pLaser;
}

void SceneMain::Init()
{
	m_gameScreenHandle = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);
	m_pBgManager->Init();
	m_pPlayer->Init();
	m_pMap->Init();
	m_pBoss->Init();
	m_pBoss->GetSceneMain(this);
	for(int e=0;e<ENEMY_NUM;e++)
	{
		m_pEnemy[e]->Init(m_enePos[e]);
		m_pEnemy[e]->GetSceneMain(this);
		m_pEnemy[e]->WantPlayerPoint(m_pPlayer);
	}
	for (int e = 0; e < ENEMY_TO_PLAYER_NUM; e++)
	{
		CreateEnemy(m_eneToPlayerPos[e],e);
	}
	
}

void SceneMain::End()
{
}

void SceneMain::Update()
{
	//if (bossZone == false)
	{
		CollisionUpdate();

		m_wipeFrame++;

		m_pBgManager->Update();
		if (m_pPlayer != nullptr)
		{
			m_pPlayer->Update();
			m_pPlayer->GetPos(m_pPlayer->GetVelocity().x);
			if (m_pPlayer->GetPos().x > Game::kScreenWidth * 6 / 8)
			{
				m_pMap->GetScreenMove(3);
			}
		}
		/*if (m_pPlayer->GetPos().x > (Game::kScreenWidth * 0.675))
		{
			m_pMap->OnScreenMoveAdd();
			m_pPlayer->screenAdd();
		}*/
		/*if (m_pPlayer->GetPos().x < (Game::kScreenWidth * 0.375))
		{
			m_pMap->OnScreenMoveSub();
			if (m_pMap->GetScreenMove() <= 0)
			{
				m_pPlayer->screenSub();
			}
		}*/

		if (m_pMap != nullptr)
		{
			m_pMap->OnScreenMoveAdd(m_pPlayer->GetVelocity().x);
			m_pMap->Update();
			//if (!bossZone)
			{
				if (m_pMap->GetScreenMove() + m_pPlayer->GetPos().x > 6500)
				{
					m_screenMove = m_pMap->GetScreenMove();
					m_pMap->GetScreenMove(6750);
					m_pPlayer->GetPos(500);
					m_isClear = true;
				}
			}
		}
		if (m_toBoss)
		{
			m_frame++;
			if (m_frame >= 60)
			{
				bossZone = true;
				m_isClear = true;
			}
		}
		{
			for (int e = 0; e < ENEMY_TO_PLAYER_NUM; e++)
			{
				if (m_pEnemyToPlayer[e] != nullptr)
				{
					m_pEnemyToPlayer[e]->ScreenMove(m_pMap->GetScreenMove());
					m_pEnemyToPlayer[e]->Update();
				}
			}
		}
		{
			//m_pEnemy->GetScreenMove(m_pPlayer->GetVelocity().x);
			for (int e = 0; e < ENEMY_NUM; e++)
			{
				if (m_pEnemy[e] != nullptr)
				{
					m_pEnemy[e]->ScreenMove(m_pMap->GetScreenMove());
					m_pEnemy[e]->Update();

					if (m_pEnemy[e]->OnDie())m_pEnemy[e] = nullptr;
				}
			}
			for (int e = 0; e < ENEMY_TO_PLAYER_NUM; e++)
			{
				if (m_pEnemyToPlayer[e] != nullptr)
				{
					if (m_pEnemyToPlayer[e]->OnDie())
					{
						m_pEnemyToPlayer[e] = nullptr;
					}
				}
				
			}
			
		}

		if (m_pBoss != nullptr)
		{
			//m_pBoss->GetScreenMove(m_pPlayer->GetVelocity().x);
			m_pBoss->Update();
			if (m_pBoss->OnDie())m_pBoss = nullptr;
		}

		for (int i = 0; i < SHOT_NUM_LIMIT; i++)
		{
			if (m_pShot[i] != nullptr)
			{
				if(m_pMap!=nullptr)
				{
					if (m_pShot[i]->GetIsDestroy() == true)
					{
						m_pShot[i] = nullptr;
					}
				}
				
			}
		}
	}

	if (bossZone = true)
	{

	}
	Pad::Update();
}

void SceneMain::CollisionUpdate()
{
	//ToDoオブジェクトそれぞれのRectを配列でとってfor文のiで管理する
	if (m_pBoss != nullptr)
	{
		m_pBoss->Update();
	}
	for (int e = 0; e < ENEMY_NUM; e++)
	{//toEnemyのCollision
		if (m_pEnemy[e] != nullptr)
		{
			for (int i = 0; i < SHOT_NUM_LIMIT; i++)
			{
				if (m_pShot[i] != nullptr)
				{
					if (m_pShot[i]->GetShotColli(m_pEnemy[e]->GetCollRect()))
					{
						m_pEnemy[e]->OnHitShot();
					}
				}
			}

			for (int i = 0; i < SHOT_NUM_LIMIT; i++)
			{
				if (m_circleShot[i] != nullptr)
				{
					for (int e = 0; e < ENEMY_NUM; e++)
					{
						if (m_circleShot[i]->GetShotColli(m_pEnemy[e]->GetCollRect()))
						{
							m_pEnemy[e]->OnHitShot();
						}
						if (m_circleShot[i]->GetIsDestroy() == true)
						{
							m_circleShot[i] = nullptr;
						}
					}
				}
			}

			if (m_pLaser != nullptr)
			{
				for (int e = 0; e < ENEMY_NUM; e++)
				{
					if (m_pLaser->OnLaserCollision(m_pEnemy[e]->GetCollRect()))
					{
						int d = 0;
					}
				}
				if (m_pLaser->GetVisible())
				{
					m_pLaser = nullptr;
				}
			}
			for (int e = 0; e < ENEMY_TO_PLAYER_NUM; e++)
			{
				if(m_pEnemyToPlayer[e]!=nullptr)
				{
					if (m_pPlayer->OnCollision(m_pEnemyToPlayer[e]->GetCollRect()))
					{
						if (m_pPlayer->OnDamage())
						{
							m_pEnemyToPlayer[e]->OnPlayerHit();
						}
						//プレイヤーが敵にヒット
						m_pPlayer->OnDamage();
						
						
					}
				}
			}
		}
	}
	for (int e = 0; e < ENEMY_TO_PLAYER_NUM; e++)
	{
		if (m_pEnemyToPlayer[e] != nullptr)
		{
			for (int i = 0; i < SHOT_NUM_LIMIT; i++)
			{
				if (m_pShot[i] != nullptr)
				{
					if (m_pShot[i]->GetShotColli(m_pEnemyToPlayer[e]->GetCollRect()))
					{
						m_pEnemyToPlayer[e]->OnDamage(10);
						
					}
					
				}
			}
		}
	}
	
	//toPlayerのCollision
	if (m_pPlayer != nullptr)
	{
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (m_eneShot[i] != nullptr)
			{
				m_eneShot[i]->GetScreenMove(m_pMap->GetScreenMove());
;				if (m_pPlayer->OnCollision(m_eneShot[i]->GetColRect()))
				{
					m_eneShot[i]->OnHit();
					//Playerが攻撃を受けた処理	
					m_pPlayer->OnDamage();
				}
				if (m_eneShot[i]->GetIsDestroy() == false)
				{
					m_eneShot[i] = nullptr;
				}
				
			}

		}
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (m_pEnemyToPlayer[i] != nullptr)
			{
				if (m_pPlayer->OnCollision(m_pEnemyToPlayer[i]->GetCollRect()))
				{
					//Playerが攻撃を受けた処理	
					m_pPlayer->OnDamage();

				}
			}
		}
		//マップとの当たり判定
		if (m_pMap->IsPlayerCollision(m_pPlayer->GetRect(), m_pPlayer->GetColRadius(), m_pPlayer->GetVelocity()) == true)
		{
			m_pPlayer->OnMapCollision();
		}
		for (int i = 0; i < SHOT_NUM_LIMIT; i++)
		{
			if (m_pShot[i] != nullptr)
			{
				m_pShot[i]->GetScreenMove(m_pPlayer->GetVelocity().x);

				if (m_pMap->IsCollision(m_pShot[i]->GetPos(), m_pShot[i]->GetRadius())==true)
				{
					m_pShot[i]->OnMapCol();
				}
				if (m_pShot[i]->GetIsDestroy() == true)
				{
					m_pShot[i] = nullptr;
				}
			}
		}
		
		{
			for (int e = 0; e < ENEMY_TO_PLAYER_NUM; e++)
			{
				if (m_pEnemyToPlayer[e] != nullptr)
				{
					if (m_pMap->IsPlayerCollision(m_pEnemyToPlayer[e]->GetCollRect(), 20, m_pEnemyToPlayer[e]->GetVelocity())==true)
					{
						m_pEnemyToPlayer[e]->OnMapCol(m_pMap->GetCollisionVelocity());
					}
				}
			}

			for (int e = 0; e < ENEMY_NUM; e++)
			{
				if (m_eneShot[e] != nullptr)
				{
					if (m_pMap->IsCollision(m_eneShot[e]->GetPos(), 20))
					{
						m_eneShot[e]->OnCollision();
					}
				}
			}
		}
	}
}

void SceneMain::Draw() const
{

	//if (bossZone == false)
	{
		m_pBgManager->Draw();
		m_pPlayer->Draw();
		for (int e = 0; e < ENEMY_NUM; e++)
		{
			if (m_pEnemy[e] != nullptr)m_pEnemy[e]->Draw();
		}
		if (m_pBoss != nullptr)m_pBoss->Draw();

		for (int e = 0; e < ENEMY_TO_PLAYER_NUM; e++)
		{
			if (m_pEnemyToPlayer[e] != nullptr)
			{
				m_pEnemyToPlayer[e]->Draw();

			}
		}
		m_pMap->Draw();

		if (m_toBoss)
		{
			int alpha = static_cast<int>(255 * (static_cast<float>(m_frame) / 60.0f));
			SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
			DrawBox(0, 0, 2000, 1000, 0xffffff, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}

		if (m_pBoss != nullptr)
		{
			m_pBoss->Draw();
		}

		DrawFormatString(1200, 0, 0xffffff, "score:%d", m_score);
	}
}

void SceneMain::CreateEnemy(Vec2 pos,int enemyNumber)
{
	
	m_pEnemyToPlayer[enemyNumber] = new EnemyToPlayerDir{pos};
	m_pEnemyToPlayer[enemyNumber]->GetSceneMain(this);
	m_pEnemyToPlayer[enemyNumber]->Init( m_pPlayer);

}

void SceneMain::EnemyDelete()
{
	m_isPlayerDie = true;
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		m_pEnemy[i] = nullptr;
		delete m_pEnemy[i];
	}
	for (int e = 0; e < ENEMY_TO_PLAYER_NUM; e++)
	{
		m_pEnemyToPlayer[e] = nullptr;
		delete m_pEnemyToPlayer[e];
	}
}

void SceneMain::GameOver()
{
	m_isGameOver = true; 
}

float SceneMain::GetPlayerPos()
{
	
	if (m_pPlayer != nullptr)
	{
		return m_pPlayer->GetPos().x;
	}
}

void SceneMain::Clear()
{
	
	
}

void SceneMain::AddShot(std::shared_ptr<Shot> shot)
{
	for (int i = 0; i < SHOT_NUM_LIMIT; i++)
	{
		if(m_pShot[i]==nullptr)
		{
			m_pShot[i] = shot.get();
			break;
		}
	}
}

void SceneMain::AddLaser(std::shared_ptr<Laser> laser)
{
	if (m_pLaser == nullptr)
	{
		m_pLaser = laser.get();
	}
}

void SceneMain::AddCircleShot(std::shared_ptr<CircleShot> circleShot)
{
	for (int i = 0; i < 3; i++)
	{
		if (m_circleShot[i] == nullptr)
		{
			m_circleShot[i] = circleShot.get();
			break;
		}
	}
}

void SceneMain::AddEneShot(std::shared_ptr<EneShot> eneShot)
{
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (m_eneShot[i] == nullptr)
		{
			m_eneShot[i] = eneShot.get();
			break;
		}
	}
}
