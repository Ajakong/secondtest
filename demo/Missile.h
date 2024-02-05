#pragma once
#include<iostream>
#include<memory>
#include"Vec2.h"
#include"Object.h"
#include"Rect.h"
#include"Sqhere.h"

class Player;

class Missile
{
public:
	Missile();
	~Missile();
	void Init();
	virtual void Update();
	void Draw();


	//Shotのプログラミング統括
	void ShotProgram(const Vec2& Spos, const Vec2& DirVec, const int& graph,Player* player);

	bool GetIsDestroy()const { return m_isDestroy; }

	bool GetShotColli(const Rect& rect);


	void setShotBullet() { m_isInVisible = false; }

	Vec2 GetPos() { return m_shotPos; }

	void OnDestroy() { m_isDestroy = true; }

	void OnMapCol();

	int GetRadius() { return m_radius; }

	Sqhere GetCollSqhere()const { return m_collider; }
private:
	//Shotの位置情報
	Vec2 m_shotPos;

	Vec2 m_missileEndPos;

	Vec2 m_targetPos;
	//Shotのベクトル
	Vec2 m_Velocity;
	//ベクトルの向き
	Vec2 m_DirVec;
	//Shotのグラフィックハンドル
	int m_handle;
	int m_graph;

	Sqhere m_collider;

	int m_radius;

	int m_lockOnFrame=0;

	bool m_isInVisible = true;

	bool m_isDestroy = false;

	bool effectFlag = false;

	bool m_isMapColFlag = false;

	Vec2 m_graphSize;

	Player* m_player;
	
};

