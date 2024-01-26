#pragma once
#include "Shot.h"

class EneShotEffect;

class EneShot 
{
public:
	EneShot();
	virtual ~EneShot();

	void Init();
	virtual void Update();
	void Draw();


	//Shotのプログラミング統括
	void ShotProgram(const Vec2& Spos, const Vec2& DirVec, const int& graph, std::shared_ptr<EneShotEffect> eneShotEffect);

	bool GetIsDestroy()const { return m_isVisible; }

	bool GetShotColli(const Rect& rect);
	void OnCollision();

	void setShotBullet() { m_isVisible = false; }

	void OnDestroy() { m_isDestroy = true; m_shotEffect = nullptr; }

	Vec2 GetPos() { return m_shotPos; }

	Sqhere GetCollSqhere()const { return m_collider; }
private:
	//Shotの位置情報
	Vec2 m_shotPos;
	//Shotのベクトル
	Vec2 m_Velocity;
	//ベクトルの向き
	Vec2 m_DirVec;
	//Shotのグラフィックハンドル
	int m_handle;
	int m_graph;

	Sqhere m_collider;

	int m_radius;

	bool m_isVisible = true;

	bool m_isEffectFlag = false;

	bool m_isDestroy=false;

	Vec2 m_graphSize;

	Player* m_player;
	EnemyBase* m_enemy;

	std::shared_ptr<EneShotEffect> m_shotEffect;
};

