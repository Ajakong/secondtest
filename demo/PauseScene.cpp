#include "PauseScene.h"
#include <DxLib.h>
#include"Pad.h"
#include "Application.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include"GamePlayingScene.h"
#include"Title.h"
#include"Game.h"

namespace
{
	constexpr int kAppeaInterval = 60;
	constexpr int kMenuMargin = 50;
}

PauseScene::PauseScene(SceneManager& mgr) : Scene(mgr) 
{

	m_updateFunc = &PauseScene::AppearUpdate;
	m_drawFunc = &PauseScene::ExpandDraw;
	m_tutoHandle=LoadGraph("data/image/tuto/controller_format.png");
}

void PauseScene::Update()
{
	(this->*m_updateFunc)();

	Pad::Update();
}

void PauseScene::Draw()
{
	(this->*m_drawFunc)();
}

void PauseScene::AppearUpdate()
{
	m_frame++;
	if (kAppeaInterval <= m_frame)
	{
		m_updateFunc = &PauseScene::NormalUpdate;
		m_drawFunc = &PauseScene::NormalDraw;
	}
}

void PauseScene::NormalUpdate()
{
	if (!m_tutoFlag)
	{
		if (Pad::IsTrigger(PAD_INPUT_R))
		{
			m_updateFunc = &PauseScene::DisappearUpdate;
			m_drawFunc = &PauseScene::ExpandDraw;

		}
		if (Pad::IsTrigger(PAD_INPUT_DOWN))
		{
			m_select++;
		}
		if (Pad::IsTrigger(PAD_INPUT_UP))
		{
			m_select--;
		}
	}
	
	if (Pad::IsTrigger(PAD_INPUT_2))
	{
		if (m_select % 3 == 0)
		{
			m_updateFunc = &PauseScene::DisappearUpdate;
			m_drawFunc = &PauseScene::ExpandDraw;
		}
		
		
		if(m_select % 3 == 1|| m_select % 3 == -2)
		{
			if (m_tutoFlag)
			{
				m_tutoFlag = false;
			}
			else
			{
				m_tutoFlag = true;

			}
			
		}
		if (m_select % 3 == 2 || m_select % 3 == -1)
		{
			m_updateFunc = &PauseScene::DisappearUpdate;
			m_drawFunc = &PauseScene::ExpandDraw;
		}
	}
	
}

void PauseScene::DisappearUpdate()
{
	m_frame--;
	if (m_frame == 0)
	{
		m_manager.PopScene();
	}
}

void PauseScene::ExpandDraw()
{
	Application& app = Application::GetInstance();
	const auto& size = app.GetWindowSize();

	int halfHeight = (size.h - 100) / 2;
	int centerY = size.h / 2;

	float rate = static_cast<float>(m_frame) / kAppeaInterval;	// åªç›ÇÃéûä‘ÇÃäÑçá(0.0Å`1.0)
	int currentHalfHeight = static_cast<int>(rate * halfHeight);

	SetDrawBlendMode(DX_BLENDMODE_MUL, 255);
	// ÇøÇÂÇ¡Ç∆à√Ç¢ãÈå`Çï`âÊ
	DrawBox(kMenuMargin, centerY - currentHalfHeight, size.w - kMenuMargin, centerY + currentHalfHeight,
		0x888888, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(kMenuMargin, centerY - currentHalfHeight, size.w - kMenuMargin, centerY + currentHalfHeight,
		0xffffff, false);
}

void PauseScene::NormalDraw()
{
	Application& app = Application::GetInstance();
	const auto& size = app.GetWindowSize();
	SetDrawBlendMode(DX_BLENDMODE_MUL, 255);
	// ÇøÇÂÇ¡Ç∆à√Ç¢ãÈå`Çï`âÊ
	DrawBox(kMenuMargin, kMenuMargin, size.w - kMenuMargin, size.h - kMenuMargin,
		0x888888, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawRotaString(650, 300, 6, 6, 0, 0, 0, 0xffffbb, 0, 0, "Pause");

	DrawString(750, 500, "ÉQÅ[ÉÄÇ…ñﬂÇÈ", 0xffffff);
	DrawString(770, 600, "ëÄçÏê‡ñæ", 0xffffff);
	//DrawString(810, 700, "É^ÉCÉgÉãÇ÷", 0xffffff);

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255 / 3);
	if (m_select % 3 == 0)
	{
		DrawBox(700, 480, 900, 550, 0xffffff, true);
	}
	if (m_select % 3 == 1 || m_select % 3 == -2)
	{
		DrawBox(700, 580, 900, 650, 0xffffff, true);
	}
	if (m_select % 3 == 2 || m_select % 3 == -1)
	{
		DrawBox(700, 680, 900, 750, 0xffffff, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	if (m_tutoFlag)
	{
		DrawRotaGraph(Game::kScreenWidth/2, Game::kScreenHeight/2,0.8f,0, m_tutoHandle, false);

	}
	
	DrawBox(kMenuMargin, kMenuMargin, size.w - kMenuMargin, size.h - kMenuMargin,
		0xffffff, false);
	
}
