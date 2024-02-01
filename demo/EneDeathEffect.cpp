#include"DxLib.h"
#include "EneDeathEffect.h"

EneDeathEffect::EneDeathEffect(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
	m_count = 0;
}

EneDeathEffect::~EneDeathEffect()
{
}

void EneDeathEffect::Init()
{
}

void EneDeathEffect::Update()
{
	m_count++;
	m_radius++;
	if (m_count > 30)
	{
		m_isDestroy = true;
	}
}

void EneDeathEffect::Draw()
{
	for (int i = 0; i < 20; i++)
	{
		m_PlusUltra.x = GetRand(m_pos.x * 2) - m_pos.x;
		m_PlusUltra.y = GetRand(1080) - 540;
		m_PlusUltra.Normalize();
		m_PlusUltra = m_PlusUltra * 20;
		DrawLine(m_pos.x+10, m_pos.y + 25, m_pos.x + m_PlusUltra.x+10, m_pos.y + 25 + m_PlusUltra.y, 0xffdddd);
	}
	DrawCircle(m_pos.x+10, m_pos.y+20, m_radius, 0xffddff, false, 2);
	DrawCircle(m_pos.x + 10, m_pos.y + 20, m_radius-5, 0xff8822, true, 2);
}
