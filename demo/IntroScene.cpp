#include "IntroScene.h"
#include <DxLib.h>
#include"Pad.h"
#include "Application.h"
#include "SceneManager.h"
#include "IntroScene.h"
#include"Title.h"

namespace
{
	constexpr int kAppeaInterval = 60;
	constexpr int kMenuMargin = 50;
}

IntroScene::IntroScene(SceneManager& mgr) : Scene(mgr)
{
	m_updateFunc = &IntroScene::AppearUpdate;
	m_drawFunc = &IntroScene::ExpandDraw;
}

void IntroScene::Update()
{
	(this->*m_updateFunc)();
}

void IntroScene::Draw()
{
	(this->*m_drawFunc)();
}

void IntroScene::AppearUpdate()
{
	m_frame++;
	if (kAppeaInterval <= m_frame)
	{
		m_updateFunc = &IntroScene::NormalUpdate;
		m_drawFunc = &IntroScene::NormalDraw;
	}
}

void IntroScene::NormalUpdate()
{
	if (Pad::IsPress(PAD_INPUT_R))
	{
		m_updateFunc = &IntroScene::DisappearUpdate;
		m_drawFunc = &IntroScene::ExpandDraw;

	}
	if (Pad::IsPress(PAD_INPUT_DOWN))
	{
		m_select++;
	}
	if (Pad::IsPress(PAD_INPUT_UP))
	{
		m_select--;
	}
	if (Pad::IsPress(PAD_INPUT_2))
	{
		if (m_select % 2 == 0)
		{
			m_updateFunc = &IntroScene::DisappearUpdate;
			m_drawFunc = &IntroScene::ExpandDraw;
		}
		else
		{
			m_manager.ChangeScene(std::make_shared<Title>(m_manager));
		}

	}

}

void IntroScene::DisappearUpdate()
{
	m_frame--;
	if (m_frame == 0)
	{
		m_manager.PopScene();
	}
}

void IntroScene::ExpandDraw()
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

void IntroScene::NormalDraw()
{
	Application& app = Application::GetInstance();
	const auto& size = app.GetWindowSize();
	SetDrawBlendMode(DX_BLENDMODE_MUL, 255);
	// ÇøÇÂÇ¡Ç∆à√Ç¢ãÈå`Çï`âÊ
	DrawBox(kMenuMargin, kMenuMargin, size.w - kMenuMargin, size.h - kMenuMargin,
		0x888888, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(100, 100, "Pause Scene", 0xffffff);

	DrawBox(kMenuMargin, kMenuMargin, size.w - kMenuMargin, size.h - kMenuMargin,
		0xffffff, false);
}
