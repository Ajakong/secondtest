#include <DxLib.h>
#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Bg.h"

#include "Game.h"

namespace
{
	
}



Bg::Bg() :
	m_handle(-1)
{
	
}

Bg::~Bg()
{
}

void Bg::Init()
{
	GetGraphSize(m_handle,&m_graphX,&m_graphY);
	
}

void Bg::Update()
{
	
}

void Bg::Draw()
{
	for(int i=0;i<8;i++)
	{
		graphRateX = m_graphX*2 * i-1 ;
		DrawRectRotaGraph(m_graphX * 2 +graphRateX, 450, 0, 0, m_graphX, m_graphY, 4, 0, m_handle, true);
	}
}

