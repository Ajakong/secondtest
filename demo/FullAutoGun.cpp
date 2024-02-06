#include "FullAutoGun.h"

FullAutoGun::FullAutoGun(Vec2 pos, Vec2 velo, int itemGraph):Item(pos,velo,itemGraph)
{
}

FullAutoGun::~FullAutoGun()
{
}

void FullAutoGun::Init()
{
	Item::Init();
}

void FullAutoGun::Update()
{
	Item::Update();
}

void FullAutoGun::Draw()
{
	Item::Update();
}

void FullAutoGun::CollisionUpdate()
{
	Item::CollisionUpdate();
}


