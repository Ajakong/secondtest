#include <DxLib.h>
#include <cassert>
#include "Application.h"
#include "SceneManager.h"
#include "Title.h"
#include "GamePlayingScene.h"
#include"Game.h"

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

	m_bgmHandle = LoadSoundMem("BGM/titleBgm.mp3");
	PlaySoundMem(m_bgmHandle,DX_PLAYTYPE_BACK);

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
	m_particle->Update();
	(this->*m_updateFunc)();
}

void Title::Draw()
{
	(this->*m_drawFunc)();
}

void Title::FadeInUpdate()
{
	m_fadeFrame--;
	m_fadeSoundFrame++;
	ChangeVolumeSoundMem(m_fadeSoundFrame*2, m_bgmHandle);
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
	m_jammingFrame ++;
	if (m_jammingFrame % 200 == 0)
	{
		m_screenHandle = Application::GetInstance().GetScreenHandle();
		m_windowHandle = GetDrawScreenGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight,m_handle, true);
		m_updateFunc = &Title::JammingUpdate;
		m_drawFunc = &Title::JammingDraw;
	}
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
	m_fadeSoundFrame--;
	ChangeVolumeSoundMem(m_fadeSoundFrame*2, m_bgmHandle);
	if (60 <= m_fadeFrame)
	{
		StopSoundMem(m_bgmHandle);
		m_manager.ChangeScene(std::make_shared<GamePlayingScene>(m_manager));
	}
}

void Title::JammingUpdate()
{
	m_onJammingFrame++;
	a++;
	m_jammingPosY+=5+a;
	
	if (m_jammingPosY > 2400)
	{
		DeleteGraph(m_screenHandle);
		a = 0;
		m_jammingPosY = 0;
		m_updateFunc = &Title::NormalUpdate;
		m_drawFunc = &Title::NormalDraw;
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) && !GetKeyState(KEY_INPUT_ESCAPE))
	{
		m_updateFunc = &Title::FadeOutUpdate;
		m_drawFunc = &Title::FadeDraw;
		m_fadeFrame = 0;
		m_fadeFrame = m_fadeFrame + 8;
		m_frame++;
	}
}

void Title::FadeDraw()
{
	m_particle->Draw();
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
	m_particle->Draw();
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
	DrawBox(drawStringPosX, drawStringPosY - 45 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY - 30 + m_stringColorPlusA, 0xffddff, true);
	DrawBox(drawStringPosX, drawStringPosY - 30 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY - 15 + m_stringColorPlusA, 0xddffff, true);
	DrawBox(drawStringPosX, drawStringPosY - 15 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY - 0 + m_stringColorPlusA, 0xffddff, true);
	DrawBox(drawStringPosX, drawStringPosY + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY + 15 + m_stringColorPlusA, 0xffdddd, true);
	DrawBox(drawStringPosX, drawStringPosY + 15 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY + 30 + m_stringColorPlusA, 0xddffdd, true);
	DrawBox(drawStringPosX, drawStringPosY + 30 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY + 45 + m_stringColorPlusA, 0xddddff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	m_stringColorPlusA++;
	if (m_stringColorPlusA > 50)
	{
		m_stringColorPlusA = 0;
	}
	
}

void Title::JammingDraw()
{
	m_particle->Draw();
	DrawRotaGraph(graphPosX, graphPosY, 0.8, 0, m_handle, true);
	m_fadeFrame += a;
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
	DrawBox(drawStringPosX, drawStringPosY - 45 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY - 30 + m_stringColorPlusA, 0xffddff, true);
	DrawBox(drawStringPosX, drawStringPosY - 30 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY - 15 + m_stringColorPlusA, 0xddffff, true);
	DrawBox(drawStringPosX, drawStringPosY - 15 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY - 0 + m_stringColorPlusA, 0xffddff, true);
	DrawBox(drawStringPosX, drawStringPosY + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY + 15 + m_stringColorPlusA, 0xffdddd, true);
	DrawBox(drawStringPosX, drawStringPosY + 15 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY + 30 + m_stringColorPlusA, 0xddffdd, true);
	DrawBox(drawStringPosX, drawStringPosY + 30 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY + 45 + m_stringColorPlusA, 0xddddff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	////ジャミング処理
	//SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	//DrawBox(0, m_jammingPosY-1350, 2000, m_jammingPosY-1400, 0x111111, true);
	//DrawBox(0, m_jammingPosY-850, 2000, m_jammingPosY-1300, 0x111111, true);
	//DrawBox(0, m_jammingPosY-800, 2000, m_jammingPosY - 830, 0x110000, true);
	//DrawBox(0, m_jammingPosY-450, 2000, m_jammingPosY-500, 0x110000, true);
	//DrawBox(0, m_jammingPosY-200, 2000, m_jammingPosY-400, 0x110000, true);
	//DrawBox(0, m_jammingPosY-50, 2000, m_jammingPosY-100, 0x110000, true);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	m_stringColorPlusA++;
	if (m_stringColorPlusA > 50)
	{
		m_stringColorPlusA = 0;
	}

	//DrawRectRotaGraph(0, 0, 0, 0, 2000, 1080, 1, 0, m_screenHandle, 0);
}
