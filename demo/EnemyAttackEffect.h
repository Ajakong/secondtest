#pragma once
#include "Effect.h"
class EnemyAttackEffect : public Effect
{
public:
	EnemyAttackEffect(int screenMove,float velocityX);
	~EnemyAttackEffect();

	virtual void Init();
	virtual void Update();
	virtual void Draw(int screenMove);

	virtual void CreateEffect(Vec2 pos, float offSetX, float offSetY, int screenMove);
private:
	int m_firstScreenMove = 0;

	int m_randNumX = 0;
};

