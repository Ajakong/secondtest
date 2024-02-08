#pragma once
#include"Vec2.h"
#include"Rect.h"
class Effect
{
public:
	Effect();
	virtual ~Effect();

	void Init();
	void Update();
	void Draw();

	virtual void CreateEffect() = 0;

	void WantPos(Vec2 pos) { m_pos = pos; }
protected:
	Vec2 m_pos;

	float m_offSetX = 0;
	float m_offSetY = 0;
};

