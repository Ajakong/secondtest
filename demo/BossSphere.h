#pragma once
#include"Vec2.h"
#include"Boss.h"

class BossSphere
{
public:
	BossSphere(Boss* master);
	~BossSphere();

	void Init();
	void Update();
	void Draw();
	void GetBossPos(Boss* master) { m_bossPos = master->GetEnePos(); }

	//状態別関数
	void IdleUpdate();
	void BossAt1Update();
	

	//メンバ関数ポインタ
	using sphereMove = void(BossSphere::*)();
	sphereMove m_sphereUpdate;
private:
	Vec2 m_bossPos;
	Vec2 m_center;
	Boss* m_pMaster;
	int z;
};

