#include<Dxlib.h>
#include"Boss.h"
#include "BossSphere.h"

BossSphere::BossSphere(Boss* master)
{
	m_pMaster = master;
}

BossSphere::~BossSphere()
{
}

void BossSphere::Init()
{
}

void BossSphere::Update()
{
	m_center = m_pMaster->GetEnePos();
	m_center.x += 1;
	m_center.y += 1;
}

void BossSphere::Draw()
{
	for (int i = -100; i < 100; i++)
	{
		DrawLine(m_center.x + i, m_center.y - abs(100 - abs(i)), m_center.x + i, m_center.y + abs(100 - abs(i)), 0xdd00dd);
	}

}
