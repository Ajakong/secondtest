#pragma once
#include "Vec2.h"
#include"Player.h"
#include<iostream>
#include<memory>
#include <vector>
#include <map>
#include"Particle.h"

namespace
{
	constexpr int ENEMY_NUM = 7;
	constexpr int ENEMY_TO_PLAYER_NUM = 30;
}

using namespace std;

class Player;
class ImageGroundManager;
class EnemyBase;
class EnemyBasePro;
class EnemyToPlayerDir;

class Boss;
class BossMain;

class EneShot;
class Shot;
class Laser;
class CircleShot;
class Particle;

class ShotEffect;

class Map;

class Item;

class SceneMain
{
public:
	//using Shot = std::shared_ptr < Shot > ;

	SceneMain();
	virtual ~SceneMain();

	void Init();
	void End();

	void Update();
	void CollisionUpdate();
	void EnemyToPlayerCollisionUpdate();
	void Draw() const;

	void CreateEnemy(Vec2 pos,int enemyNumber);

	void EnemyDelete();
	void GameOver();
	float GetPlayerPos();
	bool GetGameOverFlag() { return m_isGameOver; }

	void OnBossZorn();

	void Clear();
	bool GetClearFlag() { return m_isClear; }
	bool GetPlayerDie() { return m_isPlayerDie; }

	void AddShot(std::shared_ptr<Shot> shot);
	void AddLaser(std::shared_ptr<Laser> laser);
	void AddCircleShot(std::shared_ptr<CircleShot> circleShot);
	void AddEneShot(std::shared_ptr<EneShot> eneShot);
	void AddItem(std::shared_ptr<Item> item);

	void AddScore(int score) { m_score += score; }

	bool OnHitTitle() { return m_isHitTitle; }

	void NormalUpdate();
	void BossUpdate();

	//メンバ関数ポインタ
	using SceneState_t = void(SceneMain::*)();
	SceneState_t m_SceneUpdate;

	
private:
	// グラフィックのハンドル
	int m_gameScreenhandle=0;//ゲーム画面
	int m_frame=0;
	int m_gameScreenHandle=0;
	int m_eneShotHandle = 0;
	int m_enemyBaseHandle = 0;

	int m_itenNumber0Graph = 0;
	int m_itemNumber1Graph = 0;
	int m_itemNumber2Graph = 0;
	int m_itemNumber3Graph = 0;

	int m_playerShotSound = 0;
	int m_playerDamageSound = 0;
	int m_laserSound = 0;

	int m_eneDestroySound = 0;
	int m_enemyDeathSound = 0;


	int m_screenMove=0;
	int m_bgHandle=0;
	int m_enemyToPlayerHandle = 0;

	int m_enemyBornSound = 0;

	int m_hitShotToEnemyHandle = 0;
	int m_hitShotToEnemyBaseHandle = 0;

	int m_score = 0;

	bool m_isGameOver = false;
	
	bool m_toBoss = false;
	bool m_isClear = false;
	bool bossZone=false;
	bool m_isPlayerDie=false;

	bool m_isEnemyCreate[10];

	int m_BulletKindNum[5];

	bool m_enemyCreated[ENEMY_TO_PLAYER_NUM];

	bool m_isHitTitle = false;
	// プレイヤー
	Player* m_pPlayer;
	//マップ
	Map* m_pMap;
	// 背景
	ImageGroundManager* m_pBgManager;
	// 敵
	EnemyBase* m_pEnemy[ENEMY_NUM];
	EnemyToPlayerDir* m_pEnemyToPlayer[ENEMY_TO_PLAYER_NUM];

	Boss* m_pBoss;
	BossMain* m_bossMain;

	Shot* m_pShot[SHOT_NUM_LIMIT];
	Laser* m_pLaser;
	CircleShot* m_circleShot[SHOT_NUM_LIMIT];
	

	std::vector<std::shared_ptr<EneShot>> m_eneShot;

	std::map<int, Vec2> m_enePos;
	std::map<int, Vec2> m_eneToPlayerPos;

	std::vector < std::shared_ptr<Item>>m_item;

	//画面ワイプ処理
	int m_wipeFrame=0;
	// 敵の登場間隔
	int m_enemyInterval=0;
	//ダメージを受けた時の画面揺れ
	int m_shakeFrame=0;
};



