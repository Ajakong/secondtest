#pragma once
#include"Vec2.h"
class HitEffect
{
public:
	HitEffect(float x,float y,int screenmove);
	~HitEffect();

	void Init();
	void Update();
	void Draw(int screenMove);

	bool OnDestroy() { return m_isDestroy; }
private:
	Vec2 m_pos;
	
	bool m_isDestroy = false;

	int m_size;
	int m_count;

	Vec2 m_PlusUltra;

	int m_firstScreenMove=0;
	
};

