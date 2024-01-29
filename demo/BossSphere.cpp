#include<Dxlib.h>
#include"Boss.h"
#include "BossSphere.h"

BossSphere::BossSphere(Boss* master)
{
	m_pMaster = master;
	m_sphereUpdate = &BossSphere::IdleUpdate;
}

BossSphere::~BossSphere()
{
}

void BossSphere::Init()
{
}

void BossSphere::Update()
{
	

	
}

void BossSphere::Draw()
{
	for (int i = -100; i < 100; i++)
	{
		DrawLine(m_center.x + i, m_center.y - abs(100 - abs(i)), m_center.x + i, m_center.y + abs(100 - abs(i)), 0xdd00dd);
	}
}

void BossSphere::IdleUpdate()
{
	GetBossPos(m_pMaster);
	m_center = m_bossPos;

}

void BossSphere::BossAt1Update()
{
}
