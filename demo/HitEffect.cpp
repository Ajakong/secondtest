#include"DxLib.h"
#include "HitEffect.h"

HitEffect::HitEffect(float x,float y,int screenMove)
{
	m_pos.x = x;
	m_pos.y = y;
	m_count = 0;
	m_firstScreenMove = screenMove;
}

HitEffect::~HitEffect()
{
}

void HitEffect::Init()
{
}

void HitEffect::Update()
{
	m_count++;
	if (m_count > 6)
	{
		m_isDestroy = true;
	}
}

void HitEffect::Draw(int screenMove)
{
	int a = screenMove - m_firstScreenMove;
	for(int i=0;i<8;i++)
	{
		m_PlusUltra.x = GetRand(m_pos.x*2) - m_pos.x;
		m_PlusUltra.y = GetRand(m_pos.y*2) - m_pos.y;
		m_PlusUltra.Normalize();
		m_PlusUltra = m_PlusUltra * 15;
		DrawLine(m_pos.x-a, m_pos.y+30, m_pos.x + m_PlusUltra.x-a, m_pos.y+30 + m_PlusUltra.y, 0xffffdd);
		DrawLine(m_pos.x+2-a, m_pos.y + 30+2, m_pos.x + m_PlusUltra.x+2-a, m_pos.y + 30 + m_PlusUltra.y+2, 0xffaa00);
	}
}
