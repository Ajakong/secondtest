#include "CircleBulletItem.h"

CircleBulletItem::CircleBulletItem(Vec2 pos, Vec2 velo, int itemGraph) :Item(pos, velo, itemGraph)
{
}

CircleBulletItem::~CircleBulletItem()
{
}

void CircleBulletItem::Init()
{
	Item::Init();
}

void CircleBulletItem::Update()
{
	Item::Update();
}

void CircleBulletItem::Draw()
{
	Item::Update();
}

void CircleBulletItem::CollisionUpdate()
{
	Item::CollisionUpdate();
}

