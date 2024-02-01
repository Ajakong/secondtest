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
	bool CollisionPlayer(Rect playerRect);//�v���C���[����苗���ɋ߂Â�����
private:
	int m_handle=0;
	int m_screenMove=0;

	bool m_isCollision = false;

	Vec2 m_pos;
	SceneMain* m_WorldMana;
};

