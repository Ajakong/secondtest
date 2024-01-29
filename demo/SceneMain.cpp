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
	for (int e = 0; e < ENEMY_NUM; e++)
	{
		m_pEnemyToPlayer[e] = new EnemyToPlayerDir;
	}
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

	m_eneToPlayerPos[0] = Vec2(500, 0);
	m_eneToPlayerPos[1] = Vec2(550, 0);
	m_eneToPlayerPos[2] = Vec2(600, 0);
	m_eneToPlayerPos[3] = Vec2(1200, 0);
	m_eneToPlayerPos[4] = Vec2(1250, 0);
	m_eneToPlayerPos[5] = Vec2(1300, 0);
	m_eneToPlayerPos[6] = Vec2(1800, 0);
	m_eneToPlayerPos[7] = Vec2(2200, 0);
	m_eneToPlayerPos[8] = Vec2(2500, 0);
	m_eneToPlayerPos[9] = Vec2(2900, 0);
	

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
	for (int e = 0; e < ENEMY_NUM; e++)delete m_pEnemyToPlayer[e];
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
	for (int e = 0; e < ENEMY_NUM ; e++)
	{
		m_pEnemyToPlayer[e]->GetSceneMain(this);
		m_pEnemyToPlayer[e]->Init(m_eneToPlayerPos[e],m_pPlayer);
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
			if (!bossZone)
			{
				if (m_pMap->GetScreenMove() + m_pPlayer->GetPos().x > 6500)
				{
					m_screenMove = m_pMap->GetScreenMove();
					m_pMap->GetScreenMove(6750);
					m_pPlayer->GetPos(500);
					m_toBoss = true;
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
			for (int e = 0; e < ENEMY_NUM; e++)
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
				if (m_pShot[i]->GetIsDestroy() == true)
				{
					m_pShot[i] = nullptr;
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
			for (int e = 0; e < ENEMY_NUM; e++)
			{
				if(m_pEnemy[e]!=nullptr)
				{
					if (m_pPlayer->OnCollision(m_pEnemyToPlayer[e]->GetCollRect()))
					{
						//プレイヤーが敵にヒット
						//m_pPlayer->OnDamage();
					}
				}
			}
		}
	}
	for (int e = 0; e < ENEMY_NUM; e++)
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
				if (m_eneShot[i]->GetShotColli(m_pPlayer->GetRect()))
				{
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
			for (int e = 0; e < ENEMY_NUM; e++)
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

	//ゲーム画面をバックバッファに描画する
	int screenX = 0;
	int screenY = 0;
	
	if (m_shakeFrame > 0)
	{
		//画面揺れ
		screenX = GetRand(8) - 4;
		screenY = GetRand(8) - 4;
	}

	//m_wipeFrameから描画する範囲を計算する
	//m_wipeFrameゲーム開始時に0,
	//毎フレーム加算されてkWipeFrame(30)まで変化する
	//wipeRateはm_wipeFrameの変化に合わせて0.0->1.0に変化する
	float wipeRate = static_cast<float>(m_wipeFrame) / static_cast<float>(30);
	int wipeHeight = Game::kScreenHeight * wipeRate;

	/*DrawRectGraph(screenX,screenY,
	0,0,Game::kScreenWidth, wipeHeight,
	m_gameScreenHandle, true, false);*/

	//offsetの値をwipeの進行に合わせて320->0に変化させたい

	//0->320に変化させるのはわかりやすい  320*wipeRate

	int offset = 320 * (1.0f - wipeRate);

	//画面の上から1ラインずつ描画を行っている

	//if (bossZone == false)
	{
		for (int y = 0; y < Game::kScreenHeight; y++)
		{
			int x = sinf(y * 0.05f) * offset;
			DrawRectGraph(x, y,
				0, y, Game::kScreenWidth, 1,
				m_gameScreenHandle, true, false);
		}
		m_pBgManager->Draw();
		m_pPlayer->Draw();
		for (int e = 0; e < ENEMY_NUM; e++)
		{
			if (m_pEnemy[e] != nullptr)m_pEnemy[e]->Draw();
		}
		if (m_pBoss != nullptr)m_pBoss->Draw();

		{
			for (int e = 0; e < ENEMY_NUM; e++)
			{
				if (m_pEnemyToPlayer != nullptr)m_pEnemyToPlayer[e]->Draw();
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
