#pragma once
#include<iostream>
#include<memory>
#include"Vec2.h"
#include"Object.h"
#include"Rect.h"



using namespace std;

class Player;
class EneShot;
class SceneMain;
class EneShotEffect;

class EnemyBasePro
{
public:
	EnemyBasePro();
	//EnemyBase(Vec2 pos);マップが指定した位置に敵を誕生
	~EnemyBasePro();

	void Init();
	void CollisionUpdate();
	virtual void Update();
	void Draw();

	void OnDamage(int Atk) { m_Hp - Atk; }

	void OnHitShot();

	void WantPlayerPoint(Player* player);

	void GetScreenMove(float veloX);

	bool OnDie();

	void GetSceneMain(SceneMain* sceneMain) { m_WorldMana = sceneMain; }

	Rect GetCollRect()const { return m_colRect; }

	Vec2 GetEnePos() { return m_pos; }

private:
	int m_Hp;

	int m_handle;

	int m_attackFrame;

	int m_shotGraph;

	int m_distance;

	int m_screenMove;

	bool m_isShotCollFlag;

	bool m_isDeathFlag;

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
	bool shotBulletFlag;

	///////////////////////////////


	SceneMain* m_WorldMana;

};

