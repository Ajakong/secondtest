#include <DxLib.h>
#include <cassert>
#include "Application.h"
#include "SceneManager.h"
#include "GameOverScene.h"
#include "Title.h"


GameOverScene::GameOverScene(SceneManager& mgr) :
	Scene(mgr)
{
	m_frame = 60;
	m_updateFunc = &GameOverScene::FadeInUpdate;
	m_drawFunc = &GameOverScene::FadeDraw;
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Update()
{
	(this->*m_updateFunc)();
}

void GameOverScene::Draw()
{
	(this->*m_drawFunc)();
}

void GameOverScene::FadeInUpdate()
{
	m_frame--;
	if (m_frame <= 0)
	{
		m_updateFunc = &GameOverScene::NormalUpdate;
		m_drawFunc = &GameOverScene::NormalDraw;
	}
}

void GameOverScene::NormalUpdate()
{
	m_btnFrame++;
	m_updateFunc = &GameOverScene::FadeOutUpdate;
	m_drawFunc = &GameOverScene::FadeDraw;
}

void GameOverScene::FadeOutUpdate()
{
	m_frame++;
	if (60 <= m_frame)
	{
		m_manager.ChangeScene(std::make_shared<Title>(m_manager));
	}
}

void GameOverScene::FadeDraw()
{
	DrawString(10, 100, "GameOverScene", 0xffffff);
	int alpha = static_cast<int>(255 * (static_cast<float>(m_frame) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 640, 480, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameOverScene::NormalDraw()
{
	DrawString(10, 100, "GameOverScene", 0xffffff);
	auto& app = Application::GetInstance();
	auto size = app.GetWindowSize();
	int idx = m_btnFrame / 10 % 3;
	constexpr int kButtonSize = 16;
	constexpr float kBtnScale = 3.0f;
	
}
