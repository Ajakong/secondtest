#pragma once
#include"Rect.h"
#include"Vec2.h"
class Boss;

class BossMain
{
public:
	BossMain();
	~BossMain();

	void Init();
	void Update();
	void Draw();

	bool BossMapColl(Rect colRect);
private:
};

