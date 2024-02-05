#include <DxLib.h>
#include <cassert>
#include "Application.h"
#include "SceneManager.h"
#include "GamePlayingScene.h"
#include "GameOverScene.h"
#include"ClearScene.h"
#include"SceneMain.h"
#include"Pad.h"
#include"PauseScene.h"
#include"Title.h"



GamePlayingScene::GamePlayingScene(SceneManager& manager) :
	Scene(manager)
{
	m_Scene = new SceneMain;
	m_Scene->Init();
	m_frame = 60;
	m_updateFunc = &GamePlayingScene::FadeInUpdate;
	m_drawFunc = &GamePlayingScene::FadeDraw;	
	m_holySoundHandle = LoadSoundMem("SE/HolyLight.mp3");
	m_stageBgm = LoadSoundMem("BGM/stageBgm.mp3");
	PlaySoundMem(m_stageBgm,DX_PLAYTYPE_BACK);
}

GamePlayingScene::~GamePlayingScene()
{
}

void GamePlayingScene::Update()
{
	m_backBlack++;
	if (m_backBlack > 100)
	{
		m_Scene->Update();
		m_fps = GetFPS();
		(this->*m_updateFunc)();
	}
	
}

void GamePlayingScene::Draw()
{
	if (!m_selectTitle)
	{
		m_Scene->Draw();
		(this->*m_drawFunc)();
	}
	
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
		LightingPos = m_Scene->GetPlayerPos();
		PlaySoundMem(m_holySoundHandle, DX_PLAYTYPE_BACK);
		
		m_updateFunc = &GamePlayingScene::PlayerLightingUpdate;
		m_drawFunc = &GamePlayingScene::PlayerLightingDraw;
	}
	m_fps = GetFPS();
	m_btnFrame++;

	if (Pad::IsPress(PAD_INPUT_R))//XBOXコントローラーのSTART
	{
		m_manager.PushScene(std::make_shared<PauseScene>(m_manager));
		
	}
}

void GamePlayingScene::FadeOutUpdate()
{
	m_frame++;
	
	if (m_Scene->GetClearFlag())
	{
		if (60 <= m_frame)
		{
			m_manager.ChangeScene(std::make_shared<ClearScene>(m_manager));
		}
	}
}

void GamePlayingScene::PlayerLightingUpdate()
{
	m_lightingFrame++;
	m_lightRange += 0.5f;
	if (m_Scene->GetGameOverFlag())
	{
		if (200 <= m_lightingFrame)
		{
			if (m_isEndRoll)
			{
				m_manager.ChangeScene(std::make_shared<Title>(m_manager));
				m_selectTitle=true;
			}
			if(!m_isEndRoll)
			{
				m_isEndRoll = true;
				m_manager.PushScene(std::make_shared<GameOverScene>(m_manager));
			}
		}
	}
	

}

void GamePlayingScene::PunishmentUpdate()
{
	m_punishmentFrame++;
	m_punishmentRange += 0.5f;
	if (m_Scene->GetClearFlag())
	{
		if (200 <= m_lightingFrame)
		{
			if (m_isEndRoll)
			{
				m_manager.ChangeScene(std::make_shared<Title>(m_manager));
				m_selectTitle = true;
			}
			if (!m_isEndRoll)
			{
				m_isEndRoll = true;
				m_manager.PushScene(std::make_shared<ClearScene>(m_manager));
			}
		}
	}
}

void GamePlayingScene::FadeDraw()
{
	m_Scene->Draw();
	DrawString(10, 100, "GamePlayingScene", 0xffffff);
	int alpha = static_cast<int>(255 * (static_cast<float>(m_frame) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 1600, 900, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GamePlayingScene::NormalDraw()
{
	m_Scene->Draw();
	DrawString(10, 100, "GamePlayingScene", 0xffffff);
	DrawFormatString(10, 10, 0xffffff, "fps = %2.2f", m_fps);
	auto& app = Application::GetInstance();
	auto size = app.GetWindowSize();
	int idx = m_btnFrame / 10 % 3;
	constexpr int kButtonSize = 16;
	constexpr float kBtnScale = 3.0f;
}

void GamePlayingScene::PlayerLightingDraw()
{
	int alpha = 255; //static_cast<int>(255 * (static_cast<float>(m_lightingFrame) / 60.0f));
	
	for (int i = 0; i < 200; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, alpha -= 1);
	}

	for (int i = 50; i < 2000; i++)
	{
		DrawLine(LightingPos - 25 - i / 5, i, LightingPos + 25 + i / 5, i, 0x222222, i / 100);
	}
	SetDrawBlendMode(DX_BLENDMODE_SUB, alpha);
	DrawBox(0, 0, 2000, 2000, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GamePlayingScene::PunishmentDraw()
{
	int alpha = 255; //static_cast<int>(255 * (static_cast<float>(m_lightingFrame) / 60.0f));

	for (int i = 0; i < 200; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, alpha -= 1);
	}

	for (int i = 50; i < 2000; i++)
	{
		DrawLine(m_punishmentPos - 25 - i / 5, i, m_punishmentPos + 25 + i / 5, i, 0xffffff, m_punishmentRange);
	}
	SetDrawBlendMode(DX_BLENDMODE_SUB, alpha);
	DrawBox(0, 0, 2000, 2000, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
