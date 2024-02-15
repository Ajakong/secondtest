#pragma once
#include "Shot.h"
#include"CollisionMaster.h"


class CircleShot :
    public Shot
{
public:
	CircleShot();
	virtual ~CircleShot();

	void Init();
	virtual void Update();
	void Draw();


	//Shotのプログラミング統括
	void ShotProgram(const Vec2& Spos, const Vec2& DirVec,const int& graph);

	bool GetIsDestroy()const { return m_isDestroy; }

	bool GetShotColli(const Rect& rect);

	void setShotBullet() { m_isInVisible = false; }

	float GetPosX() { return m_shotPos.x; }

	virtual void OnMapCol() { Shot::OnMapCol(); }


	Sqhere GetCollSqhere()const { return m_collider; }
private:
	//Shotの位置情報
	Vec2 m_shotPos;
	//Shotのベクトル
	Vec2 m_Velocity;
	//ベクトルの向き
	Vec2 m_DirVec;

	Vec2 m_rotateCenter;

	Vec2 rotatePos;

	Vec2 rotatePos2;
	//Shotのグラフィックハンドル
	int m_handle=0;
	int m_graph=0;

	Sqhere m_collider;

	int m_radius=0;

	bool m_isInVisible = true;

	bool m_isDestroy = false;

	bool effectFlag = false;

	bool m_isMapColFlag = false;

	Vec2 m_graphSize;

	Player* m_player;
	EnemyBase* m_enemy;
	CollisionMaster* m_collosionMaster;

	std::shared_ptr<ShotEffect> m_shotEffect;
};

