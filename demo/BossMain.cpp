#include "BossMain.h"
#include"Game.h"
#include"Dxlib.h"

BossMain::BossMain()
{
}

BossMain::~BossMain()
{
}

void BossMain::Init()
{
}

void BossMain::Update()
{
	
}

void BossMain::Draw()
{
	DrawBox(0, Game::kScreenHeight - 200, Game::kScreenWidth, Game::kScreenHeight, 0xdd11dd,true);
}

bool BossMain::BossMapColl(Rect colRect)
{
	if (colRect.bottom >= Game::kScreenHeight - 200)
	{
		return true;
	}
	return false;
}
