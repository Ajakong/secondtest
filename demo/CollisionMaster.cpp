#include "CollisionMaster.h"
#include"cmath"

CollisionMaster::~CollisionMaster()
{
}

bool CollisionMaster::Collision(Rect object1Rect, Rect object2Rect)
{
	if (object1Rect.top <= object2Rect.bottom && object1Rect.bottom >= object2Rect.top)
	{
		if (object1Rect.right >= object2Rect.left && object1Rect.left <= object2Rect.right)
		{


			return true;
		}
	}
	else
	{
		return false;
	}
	
}

bool CollisionMaster::Collision(Rect object1Rect, Vec2 object2Pos, int object2Radius)
{
	if (object2Pos.y - object2Radius <= object1Rect.bottom && object2Pos.y + object2Radius >= object1Rect.top)
	{
		if (object2Pos.x + object2Radius >= object1Rect.left && object2Pos.x - object2Radius <= object1Rect.right)
		{
			
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool CollisionMaster::Collision(Vec2 object1Pos, int object1Radius, Vec2 object2Pos, int object2Radius)
{
	if (object1Radius + object2Radius <= sqrtf((object1Pos.y - object2Pos.y) * (object1Pos.y - object2Pos.y) + (object1Pos.x - object2Pos.x) * (object1Pos.x - object2Pos.x)))
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
