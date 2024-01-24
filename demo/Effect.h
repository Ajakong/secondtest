#pragma once
#include"Vec2.h"
#include"Rect.h"
class Effect
{
public:
	Effect();
	~Effect();

	void Init();
	void Update();
	void Draw();

	void WantPos(Vec2 pos) { m_pos = pos; }
private:
	Vec2 m_pos;
};

