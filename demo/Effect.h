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

	bool GetDestroyFlag() { return m_isDestroy; }

	virtual void CreateEffect(Vec2 pos, float offSetX, float offSetY, int screenMove) = 0;

	void WantPos(Vec2 pos) { m_pos = pos; }
protected:
	Vec2 m_pos;

	float m_offSetX = 0;
	float m_offSetY = 0;

	int m_exisFrame = 0;

	bool m_isDestroy = false;
	bool m_isExisFlag = false;

};

