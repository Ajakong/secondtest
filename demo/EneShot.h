#pragma once
#include "Shot.h"
#include<vector>

class EneShotEffect;

class EneShot 
{
public:
	EneShot(const Vec2& Spos, const Vec2& DirVec, const int& graph, const Player* p_player);
	virtual ~EneShot();

	void Init();
	void Update();
	void Draw(int screenMove);


	//Shotのプログラミング統括
	void ShotProgram();

	bool GetIsDestroy()const { return m_isDestroy; }

	bool GetShotColli();
	void OnCollision();

	void setShotBullet() { m_isVisible = false; }

	void OnDestroy();

	void CollisionUpdate();

	void OnHit();


	Vec2 GetPos() { return m_shotPos; }

private:
	//Shotの位置情報
	Vec2 m_shotPos;
	//Shotの速度ベクトル
	Vec2 m_Velocity;
	
	Vec2 m_dis;

	//Shotのグラフィックハンドル
	int m_handle=0;

	int m_radius=0;//半径

	int m_screenMove = 0;

	bool m_isVisible = true;

	bool m_isEffectFlag = false;

	bool m_isDestroy=false;

	const Player* m_player;

	//std::vector<std::shared_ptr<EneShotEffect>> m_shotEffect;
};

