#pragma once
#include"Vec2.h"

class BossSphere
{
public:
	BossSphere(Boss* master);
	~BossSphere();

	void Init();
	void Update();
	void Draw();
private:
	
	Vec2 m_center;
	Boss* m_pMaster;
	int z;
};

