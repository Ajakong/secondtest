#pragma once
#include "Game.h"
#include"Vec2.h"
#include"Rect.h"
#include <iostream>
#include <vector>
#include <algorithm>

//namespace
//{
//	constexpr int ENEMY_NUM = 30;
//}

class Player;

class Map
{
public:
	Map(Player* player);
	~Map();

	void Init();
	void Update();
	void Draw();

	int GetScreenVelocity() { return screenVelocityX; }

	bool IsPlayerCollision(Rect& rect,int colRadius, Vec2 velo);
	bool IsPlayerCollision(Rect& rect,Rect& bottomRay,Rect& topRay, int colRadius, Vec2 velo);
	bool IsCollision(Rect& rect, Vec2 velo);
	bool IsCollision(Vec2 pos, int radius);
	bool RectCollision(Rect& rect);

	bool ObjectCollision(const Rect& rect);

	Vec2 GetCollisionVelocity(){ return m_collisionVelocity; }
	
	//Vec2 GetEnePos() { return m_enemyPos; }
	
	int GetScreenMove() { return screenMove; }
	int GetScreenMove(int move) { screenMove = move; return screenMove; }

	void OnScreenMoveAdd(float veloX) { m_isScreenMoveAddFlag = true; screenMove += veloX;}
	Vec2 GetCollisionPos() { return m_collisionPos; }
	


private:
	
	int screenVelocityX=0;//スクリーンのx軸移動量(フレーム単位)
	int screenMove=0;//スクリーンのx軸移動量(合計)

	bool m_isScreenMoveAddFlag=false;
	bool m_isScreenMoveSubFlag=true;


	Player* m_player;

	Vec2 m_playerPos;

	Vec2 m_collisionVelocity;

	Vec2 m_collisionPos;

	
};

