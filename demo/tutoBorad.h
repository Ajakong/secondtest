#pragma once
#include"Vec2.h"
#include"Rect.h"

class SceneMain;

class tutoBorad
{
public:
	tutoBorad();
	~tutoBorad();

	void Init();
	void Update(int screenMove);
	void Draw();
	bool CollisionPlayer(Rect playerRect);//ƒvƒŒƒCƒ„[‚ªˆê’è‹——£‚É‹ß‚Ã‚¢‚½‚ç
private:
	int m_handle=0;
	int m_screenMove=0;

	bool m_isCollision = false;

	Vec2 m_pos;
	SceneMain* m_WorldMana;
};

