#pragma once
#include"Vec2.h"
#include "EnemyBase.h"

class EnemyToPlayerDir :
    public EnemyBase
{
public:
    EnemyToPlayerDir();
    virtual ~EnemyToPlayerDir();

    virtual void Init(Vec2 pos, Player* player) ;
	void CollisionUpdate();
    virtual void Update() override;
    virtual void Draw();

	void WantPlayerPoint(Player* player);

	void OnDamage(int Atk) { m_Hp - Atk; }

	void ScreenMove(int screenmove) { m_screenMove = screenmove; };

	void OnHitShot();

	void OnMapCol(Vec2 colRange);

	bool OnDie();

	Rect& GetCollRect() { return m_colRect; }

	Vec2 GetEnePos() { return m_pos; }

	Vec2 GetVelocity() { return m_velocity; }

	void GetSceneMain(SceneMain* sceneMain) { m_WorldMana = sceneMain; }
private:
    int m_Hp;

    int m_handle;

    int m_attackFrame;
	int m_shotGraph;

	int m_screenMove;
	Vec2 m_colRange;

	bool m_isShotCollFlag;

	bool m_isDeathFlag;

	bool m_isMapCol = false;

	Vec2 m_targetPos;

	Vec2 m_fireDir;//照準の方向

	Vec2 m_pos;
	Vec2 m_graphSize;

	Vec2 m_velocity;

	//アニメーションの管理
	Vec2 animFrameMana;

	Rect m_colRect;


	Player* m_player;

	

	//弾の発射フラグ
	bool shotBulletFlag;

	///////////////////////////////


	SceneMain* m_WorldMana;

};

