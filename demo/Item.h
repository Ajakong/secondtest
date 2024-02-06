#pragma once
#include"Vec2.h"
#include"Rect.h"

class Item
{
public:
	Item(Vec2 pos, Vec2 velo,int itemGraph);
	~Item();

	void Init();
	void Update();
	void Draw(int screenMove);

	Rect& GetColRect() { return m_rect; }

	void CollisionUpdate();
	void OnCollision();

	virtual int GetWeaponNum() = 0;

	void OnMapCol(Vec2 colRange);

	Vec2 GetVelocity() { return m_velocity; }

	bool GetDestroy() { return m_isDestroy; }

protected:
	Vec2 m_pos;
	Vec2 m_velocity;
	Rect m_rect;

	Vec2 m_excessVec;

	int m_handle = 0;
	int m_screenMove = 0;

	bool m_isDestroy = false;

	bool m_isCollision = false;
};

