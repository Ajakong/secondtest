#include <DxLib.h>
#include <cassert>
#include "Application.h"
#include "SceneManager.h"
#include "GameOverScene.h"
#include"GamePlayingScene.h"
#include "Title.h"
#include"Pad.h"


GameOverScene::GameOverScene(SceneManager& mgr) :
	Scene(mgr),
	m_fadeSoundFrame(200)
{
	m_frame = 60;
	m_updateFunc = &GameOverScene::FadeInUpdate;
	m_drawFunc = &GameOverScene::FadeDraw;
	m_DyingSound = LoadSoundMem("BGM/Patrasche.mp3");
	PlaySoundMem(m_DyingSound, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(m_fadeSoundFrame, m_DyingSound);
	
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Update()
{
	(this->*m_updateFunc)();

	Pad::Update();
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
	if(GetJoypadInputState(DX_INPUT_KEY_PAD1))
	{
		m_updateFunc = &GameOverScene::FadeOutUpdate;
		m_drawFunc = &GameOverScene::FadeDraw;
	}
	if (Pad::IsTrigger(PAD_INPUT_DOWN))
	{
		m_selectNumber++;
	}
	if (Pad::IsTrigger(PAD_INPUT_UP))
	{
		m_selectNumber--;
	}

}

void GameOverScene::FadeOutUpdate()
{
	m_frame++;
	m_fadeSoundFrame-=3;
	ChangeVolumeSoundMem(m_fadeSoundFrame, m_DyingSound);
	StopSoundMem(m_DyingSound);
	if (60 <= m_frame)
	{
		
		
		if (m_selectNumber % 2 == 0)
		{
			
			m_manager.PushScene(std::make_shared<GamePlayingScene>(m_manager));

		}
		if (m_selectNumber % 2 == 1)
		{
			
			m_manager.PushScene(std::make_shared<Title>(m_manager));

		}
		m_manager.PopScene();
	}
}

void GameOverScene::FadeDraw()
{
	int alpha = static_cast<int>(255 * (static_cast<float>(m_frame) / 60.0f));


	DrawString(1000, 500, "Continue", 0xffffff);
	DrawString(1000, 600, "To Title", 0xffffff);

	SetDrawBlendMode(DX_BLENDMODE_ADD, alpha/3);
	if (m_selectNumber % 2 == 0)
	{
		DrawBox(950, 470, 1200, 530, 0xffffff, true);
	}
	if (m_selectNumber % 2 == 1)
	{
		DrawBox(950, 570, 1200, 630, 0xffffff, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawString(1000, 500, "Continue", 0x000000);
	DrawString(1000, 600, "To Title", 0x000000);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameOverScene::NormalDraw()
{
	DrawString(1000, 500, "Continue", 0xffffff);
	DrawString(1000, 600, "To Title", 0xffffff);
	SetDrawBlendMode(DX_BLENDMODE_MULA, 255 / 3);
	if (m_selectNumber % 2 == 0)
	{
		DrawBox(950, 470, 1200, 530, 0xffffff, true);
	}
	if (m_selectNumber % 2 == 1)
	{
		DrawBox(950, 570, 1200, 630, 0xffffff, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	auto& app = Application::GetInstance();
	auto size = app.GetWindowSize();
	int idx = m_btnFrame / 10 % 3;
	constexpr int kButtonSize = 16;
	constexpr float kBtnScale = 3.0f;
	
}
