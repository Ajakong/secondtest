#include "LaserItem.h"

LaserItem::LaserItem(Vec2 pos, Vec2 velo, int itemGraph) :Item(pos, velo, itemGraph)
{
}

LaserItem::~LaserItem()
{
}

void LaserItem::Init()
{
	Item::Init();
}

void LaserItem::Update()
{
	Item::Update();
}

void LaserItem::Draw()
{
	Item::Update();
}

void LaserItem::CollisionUpdate()
{
	Item::CollisionUpdate();
}


#include "LaserItem.h"
