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
	constexpr int ENEMY_NUM = 10;
	constexpr int ENEMY_TO_PLAYER_NUM = 20;
}

using namespace std;

class Player;
class ImageGroundManager;
class EnemyBase;
class EnemyBasePro;
class EnemyToPlayerDir;
class Boss;
class EneShot;
class Shot;
class Laser;
class CircleShot;
class Particle;

class ShotEffect;

class Map;

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
	void Draw() const;

	void CreateEnemy(Vec2 pos,int enemyNumber);

	void EnemyDelete();
	void GameOver();
	float GetPlayerPos();
	bool GetGameOverFlag() { return m_isGameOver; }

	void Clear();
	bool GetClearFlag() { return m_isClear; }
	bool GetPlayerDie() { return m_isPlayerDie; }

	void AddShot(std::shared_ptr<Shot> shot);
	void AddLaser(std::shared_ptr<Laser> laser);
	void AddCircleShot(std::shared_ptr<CircleShot> circleShot);
	void AddEneShot(std::shared_ptr<EneShot> eneShot);

	void AddScore(int score) { m_score += score; }
	
private:
	// グラフィックのハンドル
	int m_gameScreenhandle=0;//ゲーム画面
	int m_frame=0;
	int m_gameScreenHandle=0;

	int m_screenMove=0;
	int m_bgHandle=0;

	int m_score = 0;

	bool m_isGameOver = false;
	bool m_isCreateEnemyFlag;//  ToDo:特定の場所にプレイヤーが来たときtrueにし、敵を生成後すぐにfalse
	bool m_toBoss = false;
	bool m_isClear = false;
	bool bossZone=false;
	bool m_isPlayerDie=false;
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
	Shot* m_pShot[SHOT_NUM_LIMIT];
	//ShotEffect* m_pShotEffect[SHOT_NUM_LIMIT];
	Laser* m_pLaser;
	CircleShot* m_circleShot[SHOT_NUM_LIMIT];
	EneShot* m_eneShot[ENEMY_NUM];

	std::map<int, Vec2> m_enePos;
	std::map<int, Vec2> m_eneToPlayerPos;

	//画面ワイプ処理
	int m_wipeFrame;
	// 敵の登場間隔
	int m_enemyInterval;
	//ダメージを受けた時の画面揺れ
	int m_shakeFrame;
};



