#pragma once
#include "EnemyBase.h"

class Missile;
class BossSphere;

class Boss 
{
public:
	Boss(SceneMain* mana);
	~Boss();

	void Init();
	void CollisionUpdate();
	virtual void Update();
	void Draw();

	

	void OnDamage(int Atk) { m_Hp - Atk; }

	void OnHitShot();

	void WantPlayerPoint(Player* player);

	void ScreenMove(int screenMove) { m_screenMove = screenMove; };

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

	Vec2 MissilePoint;

	//アニメーションの管理
	Vec2 animFrameMana;

	Rect m_colRect;


	Player* m_player;

	//////////*Shot関連*///////////
	/*std::shared_ptr<EneShot> m_shot[10];*/
	std::shared_ptr<BossSphere> m_bossSphere;

	//弾の発射フラグ
	bool shotBulletFlag;

	///////////////////////////////


	SceneMain* m_WorldMana;

};

