#pragma once
#include "Effect.h"
class EnemyBornEffect : public Effect
{
public:
	EnemyBornEffect();
	~EnemyBornEffect();

	virtual void Init();
	virtual void Update();
	virtual void Draw(int m_screenMove);

	virtual void CreateEffect(Vec2 pos, float offSetX, float offSetY, int screenMove);

private:
	int m_firstScreenMove = 0;
	int m_reductionFrame = 0;
};

