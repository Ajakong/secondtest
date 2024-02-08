#include "EnemyMoveEffect.h"
#include"DxLib.h"

EnemyMoveEffect::EnemyMoveEffect()
{
}

EnemyMoveEffect::~EnemyMoveEffect()
{
}

void EnemyMoveEffect::Init()
{
}

void EnemyMoveEffect::Update()
{
}

void EnemyMoveEffect::Draw()
{
}

void EnemyMoveEffect::CreateEffect(Vec2 pos,float offSetX,float offSetY)
{
	DrawBox( pos.x, pos.y, pos.x + offSetX, pos.y +offSetY, 0xdddd11, true);
}
