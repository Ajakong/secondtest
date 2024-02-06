#include"Dxlib.h"
#include "Item.h"

Item::Item(Vec2 pos,Vec2 velo,int itemGraph):
	m_pos(pos),
	m_velocity(velo),
	m_handle(itemGraph)
{
	CollisionUpdate();
	
}

Item::~Item()
{
}

void Item::Init()
{
}

void Item::Update()
{
	CollisionUpdate();
	if (m_isCollision)
	{
		m_velocity.y = 0;
		m_velocity.x = 0;
	}
	else
	{
		m_velocity.y += 9.8f / 60.0f;

		m_pos += m_velocity;

	}
	
}

void Item::Draw(int screenMove)
{
	m_screenMove = screenMove;
	DrawGraph(m_pos.x-screenMove, m_pos.y, m_handle, true);
	//DrawBox(m_rect.left, m_rect.top, m_rect.right, m_rect.bottom,0x00ff00,false);
}

void Item::CollisionUpdate()
{
	m_rect.left = m_pos.x-m_screenMove;
	m_rect.right = m_pos.x + 50-m_screenMove;
	m_rect.top = m_pos.y;
	m_rect.bottom = m_pos.y + 50;
}

void Item::OnCollision()
{
	m_isDestroy = true;
}

void Item::OnMapCol(Vec2 colRange)
{
	m_pos.y = colRange.y-50;
	m_isCollision = true;
}
