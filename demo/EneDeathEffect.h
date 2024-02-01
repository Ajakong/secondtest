#pragma once
#include"Vec2.h"
class EneDeathEffect
{
public:
	EneDeathEffect(float x, float y);
	~EneDeathEffect();

	void Init();
	void Update();
	void Draw(int screenMove);

	bool GetOnDestroy() { return m_isDestroy; }

	bool OnDestroy() { return m_isDestroy; }
private:
	Vec2 m_pos;

	bool m_isDestroy = false;

	int m_size=0;
	int m_count=0;
	int m_radius = 0;
	int m_frame;

	Vec2 m_PlusUltra;

};

