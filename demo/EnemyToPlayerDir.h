#pragma once
#include"Vec2.h"
#include "EnemyBase.h"

class HitEffect;
class EnemyMoveEffect;
class EnemyAttackEffect;

class EnemyToPlayerDir
{
public:
    EnemyToPlayerDir(Vec2 pos,int deathSound);
    virtual ~EnemyToPlayerDir();

    virtual void Init( Player* player,int handle) ;
	void CollisionUpdate();
    virtual void Update();
    virtual void Draw();

	void WantPlayerPoint(Player* player);

	void OnDamage(int Atk = 0);

	void ScreenMove(int screenmove) { m_screenMove = screenmove; };

	void OnHitShot();

	void OnMapCol(Vec2 colRange);

	void OnPlayerHit();

	void IdleUpdate();
	void NeutralUpdate();
	void AttackUpdate();
	void DyingUpdate();
	void WanderingUpdate();

	float GetDirX() { return m_dirX; }

	using EnemyState_t = void(EnemyToPlayerDir::*)();
	EnemyState_t m_enemyUpdate;

	bool OnDie() { return m_isDeathFlag; }

	Rect& GetCollRect() { return m_colRect; }

	Vec2 GetEnePos() { return m_pos; }

	Vec2 GetVelocity() { return m_velocity; }

	void GetSceneMain(SceneMain* sceneMain) { m_WorldMana = sceneMain; }
private:
    int m_Hp=0;

    int m_handle=0;

    int m_attackFrame=0;
	int m_shotGraph=0;

	Vec2 m_playerPos;

	int m_dis=0;

	int m_animInterval=0;

	int m_screenMove=0;
	int m_deathSound = 0;

	int m_idleMoveFrame = 0;
	int m_wanderingInterval = 0;
	int m_enemyMoveEffectOffsetX = 0;
	int m_enemyMoveEffectOffsetY = 0;

	int m_enemyWalkEffectFrame = 5;

	int m_moveNumber = 0;

	Vec2 m_colRange;

	bool m_isShotCollFlag=false;

	bool m_isDeathFlag=false;

	bool m_isDesitionMyWay = false;

	bool m_isMapCol = false;

	bool m_isAttack = false;

	bool m_isRight = false;

	bool m_hole = false;

	Vec2 m_firstPos;

	Vec2 m_targetPos;

	Vec2 m_fireDir;//照準の方向

	Vec2 m_pos;
	Vec2 m_footPos;
	Vec2 m_graphSize;

	Vec2 m_velocity;

	//アニメーションの管理
	Vec2 animFrameMana;

	Rect m_colRect;

	std::vector<std::shared_ptr<EnemyMoveEffect>> m_moveEffect;
	std::vector<std::shared_ptr<EnemyAttackEffect>> m_attackEffect;

	Player* m_player;

	float m_dirX;

	std::vector<std::shared_ptr<HitEffect>> m_HitEffect;

	//弾の発射フラグ
	bool shotBulletFlag=false;

	///////////////////////////////


	SceneMain* m_WorldMana;

};

