#include"DxLib.h"

#include"ForeGround.h"
#include "ImageGroundManager.h"


ImageGroundManager::ImageGroundManager()
{
	for (auto& bg : m_bg)
	{
		bg = new Bg;
	}
	m_foreGround = new ForeGround;
}

void ImageGroundManager::Init()
{
	m_bg[BG_KIND_BACK]->SetHandle(LoadGraph("data/image/BgLayer/night-town-background-sky.png"));
	m_bg[BG_KIND_BACK]->Init();
	m_bg[BG_KIND_MIDDLE]->SetHandle(LoadGraph("data/image/BgLayer/night-town-background-mountains-lights.png"));
	m_bg[BG_KIND_MIDDLE]->Init();
	m_foreGround->SetHandle(LoadGraph("data/image/BgLayer/night-town-background-clouds.png"));
	m_foreGround->Init();
}

void ImageGroundManager::Update()
{
	m_bg[BG_KIND_BACK]->Update();
	m_bg[BG_KIND_MIDDLE]->Update();
	m_foreGround->Update();
}

void ImageGroundManager::Draw()
{
	m_bg[BG_KIND_BACK]->Draw();
	m_bg[BG_KIND_MIDDLE]->Draw();
	m_foreGround->Draw();
}
