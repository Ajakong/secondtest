#pragma once
#include<iostream>
#include<memory>
#include<list>
#include"Vec2.h"
#include"Object.h"
#include"Rect.h"



using namespace std;

class Player;
class EneShot;
class SceneMain;
class EneShotEffect;

class EnemyBase
{
public:
	EnemyBase();
	//EnemyBase(Vec2 pos);マップが指定した位置に敵を誕生
	~EnemyBase();

	void Init(Vec2 pos);
	void CollisionUpdate();
	virtual void Update();
	void Draw();

	void OnDamage(int Atk) { m_Hp - Atk; }

	void OnHitShot();

	void WantPlayerPoint(Player* player);

	void ScreenMove(int screenmove) { m_screenMove=screenmove; };

	void GetScreenMove(float veloX);

	bool OnDie();

	void GetSceneMain(SceneMain* sceneMain) { m_WorldMana = sceneMain; }

	Rect GetCollRect()const { return m_colRect; }

	Vec2 GetEnePos() { return m_pos; }

private:
	int m_Hp=0;

	int m_handle=0;

	int m_attackFrame=0;

	int m_shotGraph=0;
	
	int m_distance=0;

	int m_screenMove=0;

	bool m_isShotCollFlag=false;

	bool m_isDeathFlag=false;

	Vec2 m_targetPos;
	Vec2 m_fireDir;//照準の方向

	Vec2 m_pos;
	Vec2 m_graphSize;

	Vec2 m_velocity;

	//アニメーションの管理
	Vec2 animFrameMana;

	Rect m_colRect;

	
	Player* m_player;

	//////////*Shot関連*///////////
	std::shared_ptr<EneShot> m_shot[10];
	std::shared_ptr<EneShotEffect>m_shotEffect[10];
	//弾の発射フラグ
	bool shotBulletFlag=false;

	///////////////////////////////


	SceneMain* m_WorldMana;

};

