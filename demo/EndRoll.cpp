#include "EndRoll.h"
#include"Game.h"
#include"DxLib.h"
// デバッグログ関係
#include <sstream>
#include <iomanip>

EndRoll::EndRoll():
	m_MainScrollPos(Game::kScreenWidth-500,Game::kScreenHeight)
{
	m_titleLogo = LoadGraph("data/logo/Title.png");
}

EndRoll::~EndRoll()
{
}

void EndRoll::Init()
{
}

void EndRoll::Update()
{
	m_MainScrollPos.y--;
}

void EndRoll::Draw()
{
	DrawRotaGraph(m_MainScrollPos.x, m_MainScrollPos.y, 0.5f, 0, m_titleLogo, 0);
	DrawString(m_MainScrollPos.x, m_MainScrollPos.y+500, "starring : Cthulu", 0xffffff);
	DrawString(m_MainScrollPos.x, m_MainScrollPos.y+800, "starring : Cthulu", 0xffffff);
	DrawString(m_MainScrollPos.x, m_MainScrollPos.y+900, "starring : Cthulu", 0xffffff);
	DrawString(m_MainScrollPos.x, m_MainScrollPos.y+1000, "starring : Cthulu", 0xffffff);
	DrawString(m_MainScrollPos.x, m_MainScrollPos.y+1100, "starring : Cthulu", 0xffffff);
	DrawString(m_MainScrollPos.x, m_MainScrollPos.y+1200, "starring : Cthulu", 0xffffff);
	DrawString(m_MainScrollPos.x, m_MainScrollPos.y+1300, "starring : Cthulu", 0xffffff);
	DrawString(m_MainScrollPos.x, m_MainScrollPos.y+1400, "starring : Cthulu", 0xffffff);
	DrawString(m_MainScrollPos.x, m_MainScrollPos.y+1500, "starring : Cthulu", 0xffffff);
}
