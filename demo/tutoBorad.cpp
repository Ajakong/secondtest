#include"DxLib.h"
#include "tutoBorad.h"
#include"SceneMain.h"

tutoBorad::tutoBorad():
	m_pos(0,0),
	m_handle(0),
	m_screenMove(0)
{
	
}

tutoBorad::~tutoBorad()
{
}

void tutoBorad::Init()
{

}

void tutoBorad::Update(int screenMove)
{
	m_screenMove = screenMove;
	m_pos.x = 500;
	m_pos.y = 700;
}

void tutoBorad::Draw()
{
	DrawBox(m_pos.x-m_screenMove, m_pos.y, m_pos.x + 100, m_pos.y + 50, 0xdddd00, true);
}

bool tutoBorad::CollisionPlayer(Rect playerRect)
{
	if (m_pos.y <= playerRect.bottom && m_pos.y+50 >= playerRect.top)
	{
		if (m_pos.x + 100 >= playerRect.left && m_pos.x <= playerRect.right)
		{


			return true;
		}
	}
	else
	{
		return false;
	}
	return false;
}

