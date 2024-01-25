#pragma once
#include<iostream>
#include<memory>
#include"Vec2.h"
#include"Object.h"
#include"Rect.h"
#include"Sqhere.h"

class Player;
class EnemyBase;
class ShotEffect;


class Shot : public Object
{
public:
	Shot();
	virtual ~Shot();

	void Init();
	virtual void Update();
	void Draw();


	//Shotのプログラミング統括
	void ShotProgram(const Vec2& Spos, const Vec2& DirVec, const int& graph);

	bool GetIsDestroy()const { return m_isDestroy; }

	bool GetShotColli(const Rect& rect);


	void setShotBullet() { m_isVisible = false; }

	Vec2 GetPos() { return m_shotPos; }

	void GetScreenMove(int screenmove) { m_screenMove = screenmove; }

	void OnDestroy() { m_isDestroy = true; m_shotEffect = nullptr; }

	void OnMapCol();

	int GetRadius() { return m_radius; }

	Sqhere GetCollSqhere()const { return m_collider; }
private:
	//Shotの位置情報
	Vec2 m_shotPos;
	//Shotのベクトル
	Vec2 m_Velocity;
	//ベクトルの向き
	Vec2 m_DirVec;
	//Shotのグラフィックハンドル
	int m_handle=0;
	int m_graph=0;

	Sqhere m_collider;

	int m_radius=0;

	int m_screenMove=0;

	bool m_isVisible = true;

	bool m_isDestroy;

	bool effectFlag=false;

	bool m_isMapColFlag=false;

	Vec2 m_graphSize;

	Player* m_player;
	EnemyBase* m_enemy;


	std::shared_ptr<ShotEffect> m_shotEffect;
};
