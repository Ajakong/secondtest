#include "EnemyAttackEffect.h"
#include"Dxlib.h"

EnemyAttackEffect::EnemyAttackEffect(int screenMove)
{
	m
}

EnemyAttackEffect::~EnemyAttackEffect()
{
}

void EnemyAttackEffect::Init()
{
}

void EnemyAttackEffect::Update()
{
}

void EnemyAttackEffect::Draw(int screenMove)
{
	DrawBox(m_pos.x + m_offSetX, m_pos.y + m_offSetY, m_pos.x + m_offSetX, m_pos.y + m_offSetY, 0xffaa11, true);
	DrawBox(m_pos.x + m_offSetX, m_pos.y + m_offSetY, m_pos.x + m_offSetX, m_pos.y + m_offSetY, 0xffaa11, false);
}
