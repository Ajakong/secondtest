#include "Spread.h"

Spread::Spread(Vec2 pos, Vec2 velo, int itemGraph) :Item(pos, velo, itemGraph)
{
}

Spread::~Spread()
{
}

void Spread::Init()
{
	Item::Init();
}

void Spread::Update()
{
	Item::Update();
}

void Spread::Draw()
{
	Item::Update();
}

void Spread::CollisionUpdate()
{
	Item::CollisionUpdate();
}



