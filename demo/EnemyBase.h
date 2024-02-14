#pragma once
#include<iostream>
#include<vector>
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
class EneDeathEffect;

class Item;

class FullAutoGun;
class Spread;
class LaserItem;
class CircleItem;


class EnemyBase
{
public:
	EnemyBase(int sound, int fullAutoGunGraph, int spreadGraph, int laserItem, int CircleBulletItem, int handle);
	//EnemyBase(Vec2 pos);マップが指定した位置に敵を誕生
	~EnemyBase();

	void Init(Vec2 pos,int shotgraph);
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

	bool GetDeathFlag() { return m_isDeathFlag; }

	Rect GetCollRect()const { return m_colRect; }
	Vec2 GetEnePos() { return m_pos; }

	
private:
	int m_Hp=0;
	int m_handle=0;
	int m_attackFrame=0;
	int m_shotGraph=0;
	int m_distance=0;
	int m_screenMove=0;

	int m_deathSoundHandle = 0;

	int m_itemNumber = 0;

	int m_fullAutoGunGraph = 0;
	int m_spreadGraph = 0;
	int m_laserItemGraph = 0;
	int m_CircleItemGraph = 0;

	float m_addFrame=0;

	bool m_isShotCollFlag=false;
	bool m_isDeathFlag=false;

	bool m_shotIt=false;


	Vec2 m_targetPos;
	Vec2 m_fireDir;//照準の方向
	Vec2 m_pos;
	Vec2 m_graphSize;
	Vec2 m_velocity;
	Vec2 m_ItemThrowVel;

	//アニメーションの管理
	Vec2 animFrameMana;
	Rect m_colRect;
	Player* m_player;

	//////////*Shot関連*///////////
	std::vector<std::shared_ptr<EneShot>> m_shot;
	
	std::vector<std::shared_ptr<EneDeathEffect>> m_EneDeathEffect;

	std::shared_ptr<Item> m_item;

	//弾の発射フラグ
	bool shotBulletFlag=false;

	///////////////////////////////


	SceneMain* m_WorldMana;

};

