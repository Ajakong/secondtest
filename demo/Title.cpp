#include <DxLib.h>
#include <cassert>
#include "Application.h"
#include "SceneManager.h"
#include "Title.h"
#include "GamePlayingScene.h"

// デバッグログ関係
#include <sstream>
#include <iomanip>

namespace
{
	constexpr int graphPosX = 800;
	constexpr int graphPosY = 400;

	constexpr int drawStringPosX = 550;
	constexpr int drawStringPosY = 700;
}

Title::Title(SceneManager& manager) :
	Scene(manager)
{
	m_fadeFrame = 60;
	m_updateFunc = &Title::FadeInUpdate;
	m_drawFunc = &Title::FadeDraw;
	m_handle = LoadGraph("data/logo/Title.png");
	// output string stream
	// Debugログの表示
	std::ostringstream oss;
	oss << "TitleScene handle=" << std::hex <<
		" , frame=" << std::dec << std::setw(4) << std::setfill('0') << m_fadeFrame <<
		" , FPS=" << std::fixed << std::setprecision(2) << GetFPS() << std::endl;
	OutputDebugStringA(oss.str().c_str());

	m_particle = new Particle;
}

Title::~Title()
{
	OutputDebugString("タイトルシーンがdeleteされました\n");
	m_particle = nullptr;
	delete m_particle;
}

void Title::Update()
{
	//m_particle->Update();
	(this->*m_updateFunc)();
	
}

void Title::Draw()
{
	(this->*m_drawFunc)();
	//m_particle->Draw();
}

void Title::FadeInUpdate()
{
	m_fadeFrame--;
	if (m_fadeFrame <= 0) // 遷移条件
	{
		// 次の遷移先
		m_updateFunc = &Title::NormalUpdate;
		m_fadeFrame = 60;
		m_drawFunc = &Title::NormalDraw;
	}
}

void Title::NormalUpdate()
{
	if(GetJoypadInputState(DX_INPUT_KEY_PAD1)&&!GetKeyState(KEY_INPUT_ESCAPE))
	{
		m_updateFunc = &Title::FadeOutUpdate;
		m_drawFunc = &Title::FadeDraw;
		m_fadeFrame = 0;
		m_fadeFrame = m_fadeFrame + 8;
		m_frame++;
	}
	
}

void Title::FadeOutUpdate()
{
	m_fadeFrame++;
	if (60 <= m_fadeFrame)
	{
		m_manager.ChangeScene(std::make_shared<GamePlayingScene>(m_manager));
	}
}

void Title::FadeDraw()
{
	
	DrawRotaGraph(graphPosX, graphPosY,0.8,0, m_handle, true);
	// 通常の描画
	DrawRotaString(drawStringPosX, drawStringPosY+m_fadeFrame,3,3,0,0,0, 0xffffbb,0,0, "Press any button");
	// フェード暗幕
	int alpha = static_cast<int>(255 * (static_cast<float>(m_fadeFrame) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 2000, 2000, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(drawStringPosX, drawStringPosY, drawStringPosX+1000, drawStringPosY+20, 0xff0000, true);
	DrawBox(drawStringPosX, drawStringPosY+20, drawStringPosX + 1000, drawStringPosY + 35, 0x00ff00, true);
	DrawBox(drawStringPosX, drawStringPosY + 350, drawStringPosX + 1000, drawStringPosY + 35, 0x0000ff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Title::NormalDraw()
{
	
	DrawRotaGraph(graphPosX, graphPosY, 0.8, 0, m_handle, true);
	m_fadeFrame+=a;
	if (m_fadeFrame > 60)
	{
		a = -1;
	}
	if (m_fadeFrame < 0)
	{
		a = 1;
	}
	
	int alpha = static_cast<int>(255 * (static_cast<float>(m_fadeFrame) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_ADD, alpha);
	DrawRotaString(drawStringPosX, drawStringPosY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "Press any button");
	//DrawBox(0, 0, 2000, 2000, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(drawStringPosX, drawStringPosY -45+m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY - 30 + m_stringColorPlusA, 0xffddff, true);
	DrawBox(drawStringPosX, drawStringPosY -30+m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY - 15 + m_stringColorPlusA, 0xddffff, true);
	DrawBox(drawStringPosX, drawStringPosY -15+m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY -  0 + m_stringColorPlusA, 0xffddff, true);
	DrawBox(drawStringPosX, drawStringPosY +   m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY + 15 + m_stringColorPlusA, 0xffdddd, true);
	DrawBox(drawStringPosX, drawStringPosY +15+m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY + 30 + m_stringColorPlusA, 0xddffdd, true);
	DrawBox(drawStringPosX, drawStringPosY +30+m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY + 45 + m_stringColorPlusA, 0xddddff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	m_stringColorPlusA++;
	if (m_stringColorPlusA > 50)
	{
		m_stringColorPlusA = 0;
	}
	/*int dx = abs((m_fadeFrame + 640) % (640 * 2) - 640);
	int num = 200;
	float dy = abs((m_fadeFrame + num) % (num * 2) - num) * 0.1f;
	dy = dy * dy;
	DrawCircle(dx, static_cast<int>(dy), 10, 0xffaaaa, true);
	auto& app = Application::GetInstance();
	auto size = app.GetWindowSize();
	int idx = m_frame / 10 % 3;
	constexpr int kButtonSize = 16;*/
	
}
