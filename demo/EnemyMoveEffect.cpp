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

void EnemyMoveEffect::Draw(int screenMove)
{
	//if (m_isExisFlag)
	{
		m_exisFrame++;

		m_offSetY--;
		if (m_exisFrame < 60)
		{
			m_effectFrameOffSet.x = GetRand(10);
			m_effectFrameOffSet.y = GetRand(50);
			DrawBox(m_pos.x - screenMove+m_firstScreenMove, m_pos.y + m_offSetY, m_pos.x + m_offSetX + 5-screenMove+m_firstScreenMove, m_pos.y + 5+m_offSetY, 0xffaa11, true);
			DrawBox(m_pos.x+m_effectFrameOffSet.x - screenMove+m_firstScreenMove, m_pos.y +m_effectFrameOffSet.y, m_pos.x + +m_effectFrameOffSet.x + 5 - screenMove+m_firstScreenMove, m_pos.y + 5 + +m_effectFrameOffSet.y, 0xffaa11, false);
		}
		else
		{
			m_isDestroy = true;
		}
	}
	
}

void EnemyMoveEffect::CreateEffect(Vec2 pos,float offSetX,float offSetY, int screenMove)
{
	m_pos = pos;
	m_offSetX = offSetX;
	m_offSetY = offSetY;
	m_firstScreenMove = screenMove;
	m_isExisFlag = true;
	
}
