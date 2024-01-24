#pragma once
#include"Rect.h"
#include"Vec2.h"

class CollisionMaster
{
	CollisionMaster();
	virtual ~CollisionMaster();

	
	bool Collision(Rect object1Rect, Rect object2Rect);
	bool Collision(Rect object1Rect, Vec2 object2Pos,int object2Radius);
	bool Collision(Vec2 object1Pos, int object1Radius,Vec2 object2Pos, int object2Radius);
	

};

