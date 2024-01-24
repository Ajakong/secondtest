#include <DxLib.h>
#include <cassert>
#include "Application.h"
#include "SceneManager.h"
#include "ClearScene.h"
#include "Title.h"


ClearScene::ClearScene(SceneManager& mgr) :
	Scene(mgr)
{
	m_frame = 60;
	m_updateFunc = &ClearScene::FadeInUpdate;
	m_drawFunc = &ClearScene::FadeDraw;
}

ClearScene::~ClearScene()
{
}

void ClearScene::Update()
{
	(this->*m_updateFunc)();
}

void ClearScene::Draw()
{
	(this->*m_drawFunc)();
}

void ClearScene::FadeInUpdate()
{
	m_frame--;
	if (m_frame <= 0)
	{
		m_updateFunc = &ClearScene::NormalUpdate;
		m_drawFunc = &ClearScene::NormalDraw;
	}
}

void ClearScene::NormalUpdate()
{
	m_btnFrame++;
	m_updateFunc = &ClearScene::FadeOutUpdate;
	m_drawFunc = &ClearScene::FadeDraw;
}

void ClearScene::FadeOutUpdate()
{
	m_frame++;
	if (60 <= m_frame)
	{
		m_manager.ChangeScene(std::make_shared<Title>(m_manager));
	}
}

void ClearScene::FadeDraw()
{
	DrawString(10, 100, "ClearScene", 0xffffff);
	int alpha = static_cast<int>(255 * (static_cast<float>(m_frame) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 640, 480, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ClearScene::NormalDraw()
{
	DrawString(10, 100, "ClearScene", 0xffffff);
	auto& app = Application::GetInstance();
	auto size = app.GetWindowSize();
	int idx = m_btnFrame / 10 % 3;
	constexpr int kButtonSize = 16;
	constexpr float kBtnScale = 3.0f;

}
