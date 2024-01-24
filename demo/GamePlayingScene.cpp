#include <DxLib.h>
#include <cassert>
#include "Application.h"
#include "SceneManager.h"
#include "GamePlayingScene.h"
#include "GameOverScene.h"
#include"ClearScene.h"
#include"SceneMain.h"


GamePlayingScene::GamePlayingScene(SceneManager& manager) :
	Scene(manager)
{
	m_Scene = new SceneMain;
	m_Scene->Init();
	m_frame = 60;
	m_updateFunc = &GamePlayingScene::FadeInUpdate;
	m_drawFunc = &GamePlayingScene::FadeDraw;	
}

GamePlayingScene::~GamePlayingScene()
{
}

void GamePlayingScene::Update()
{
	m_Scene->Update();
	m_fps = GetFPS();
	(this->*m_updateFunc)();
}

void GamePlayingScene::Draw()
{
	m_Scene->Draw();
	(this->*m_drawFunc)();
}

void GamePlayingScene::FadeInUpdate()
{
	m_frame--;
	if (m_frame <= 0)
	{
		m_updateFunc = &GamePlayingScene::NormalUpdate;
		m_drawFunc = &GamePlayingScene::NormalDraw;
	}
}

void GamePlayingScene::NormalUpdate()
{
	if(m_Scene->GetGameOverFlag()||m_Scene->GetClearFlag())
	{
		m_updateFunc = &GamePlayingScene::FadeOutUpdate;
		m_drawFunc = &GamePlayingScene::FadeDraw;
	}
	m_fps = GetFPS();
	m_btnFrame++;
}

void GamePlayingScene::FadeOutUpdate()
{
	m_frame++;
	if (m_Scene->GetGameOverFlag())
	{
		if (60 <= m_frame)
		{
			m_manager.ChangeScene(std::make_shared<GameOverScene>(m_manager));
		}
	}
	if (m_Scene->GetClearFlag())
	{
		if (60 <= m_frame)
		{
			m_manager.ChangeScene(std::make_shared<ClearScene>(m_manager));
		}
	}
	
}

void GamePlayingScene::FadeDraw()
{
	DrawString(10, 100, "GamePlayingScene", 0xffffff);
	int alpha = static_cast<int>(255 * (static_cast<float>(m_frame) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1600, 900, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GamePlayingScene::NormalDraw()
{
	DrawString(10, 100, "GamePlayingScene", 0xffffff);
	DrawFormatString(10, 10, 0xffffff, "fps = %2.2f", m_fps);
	auto& app = Application::GetInstance();
	auto size = app.GetWindowSize();
	int idx = m_btnFrame / 10 % 3;
	constexpr int kButtonSize = 16;
	constexpr float kBtnScale = 3.0f;

}
