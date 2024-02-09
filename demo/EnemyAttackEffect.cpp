#include "EnemyAttackEffect.h"
#include"Dxlib.h"

EnemyAttackEffect::EnemyAttackEffect(int screenMove, float velocityX)
{
	m_firstScreenMove = screenMove;
	m_velocity.y = -10;
	m_velocity.x = velocityX;
}

EnemyAttackEffect::~EnemyAttackEffect()
{
}

void EnemyAttackEffect::Init()
{
}

void EnemyAttackEffect::Update()
{
	m_velocity.y++;
	m_exisFrame++;
	if (m_exisFrame > 30)
	{
		m_isDestroy = true;
	}
	m_pos += m_velocity;
}

void EnemyAttackEffect::Draw(int screenMove)
{
	
	DrawBox(m_pos.x + m_offSetX+screenMove-m_firstScreenMove+m_randNumX, m_pos.y + m_offSetY, m_pos.x + m_offSetX+screenMove-m_firstScreenMove + m_randNumX, m_pos.y + m_offSetY, 0xffaa11, true);
	DrawBox(m_pos.x + m_offSetX+screenMove-m_firstScreenMove + m_randNumX, m_pos.y + m_offSetY, m_pos.x + m_offSetX + screenMove - m_firstScreenMove + m_randNumX, m_pos.y + m_offSetY, 0xffaa11, false);
}

void EnemyAttackEffect::CreateEffect(Vec2 pos, float offSetX, float offSetY, int screenMove)
{
	m_pos = pos;
	m_offSetX = offSetX;
	m_offSetY = offSetY;
	m_firstScreenMove = screenMove;
	m_isExisFlag = true;
}
