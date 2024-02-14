#include <DxLib.h>
#include <cassert>
#include "Application.h"
#include "SceneManager.h"
#include "Title.h"
#include "GamePlayingScene.h"
#include"Game.h"
#include"Pad.h"

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
	m_jammingSound = LoadSoundMem("SE/jamming.mp3");
	m_rightsHandle = LoadGraph("data/Rights.png");
	ChangeVolumeSoundMem(150, m_jammingSound);
	PlaySoundMem(m_bgmHandle,DX_PLAYTYPE_LOOP);

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

	Pad::Update();
}

void Title::Draw()
{
	m_particle->Draw();
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

void Title::FadeInStringUpdate()
{
	m_gameStartY -= 7;
	m_fadeFrame--;
	if (m_gameStartY < 0)
	{
		
	}
	m_rightsNotationY -= 7;
	if (0 >= m_fadeFrame)
	{
		m_updateFunc = &Title::NormalStringUpdate;
		m_drawFunc = &Title::NormalStringDraw;

	}
}

void Title::NormalStringUpdate()
{
	if (Pad::IsTrigger(PAD_INPUT_DOWN) && !m_isrightsNotation)
	{
		m_selectNumber--;
	}
	if (Pad::IsTrigger(PAD_INPUT_UP)&&!m_isrightsNotation)
	{
		m_selectNumber++;
	}
	if (Pad::IsTrigger(PAD_INPUT_1) && !m_isrightsNotation)
	{
		if (m_selectNumber % 2 == 0)
		{
			m_updateFunc = &Title::FadeOutStringUpdate;
			m_drawFunc = &Title::FadeOutStringDraw;
		}
		else
		{
			m_isrightsNotation = true;
		}
	}
	else if (Pad::IsTrigger(PAD_INPUT_1) && m_isrightsNotation)
	{
		m_isrightsNotation = false;
	}
}

void Title::NormalUpdate()
{
	m_jammingFrame++;
	if (m_jammingFrame % 400 == 0)
	{
		m_screenHandle = Application::GetInstance().GetScreenHandle();

		PlaySoundMem(m_jammingSound, DX_PLAYTYPE_BACK);
		m_updateFunc = &Title::JammingUpdate;
		m_drawFunc = &Title::JammingDraw;
	}
	if (GetJoypadInputState(DX_INPUT_KEY_PAD1) && !GetKeyState(KEY_INPUT_ESCAPE))
	{
		m_isSelectMode = true;
		//m_updateFunc = &Title::FadeOutStringUpdate;
		//m_drawFunc = &Title::FadeStringDraw;
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
		m_updateFunc = &Title::FadeInStringUpdate;
		m_drawFunc = &Title::FadeStringDraw;
		//m_manager.ChangeScene(std::make_shared<GamePlayingScene>(m_manager));
	}
}

void Title::FadeOutStringUpdate()
{
	m_pressAnyButtonY+=7;
	m_fadeFrame++;
	if (60 <= m_fadeFrame)
	{
		m_manager.ChangeScene(std::make_shared<GamePlayingScene>(m_manager));
	}
	
}

void Title::JammingUpdate()
{
	m_onJammingFrame++;
	a++;
	m_jammingPosY+=5+a;
	
	if (m_jammingPosY > 400)
	{
		a = 0;
		m_jammingPosY = 0;
		StopSoundMem(m_jammingSound);
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
	DrawBox(0, drawStringPosY, 2000, 2000, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(drawStringPosX, drawStringPosY, drawStringPosX+1000, drawStringPosY+20, 0xff0000, true);
	DrawBox(drawStringPosX, drawStringPosY+20, drawStringPosX + 1000, drawStringPosY + 35, 0x00ff00, true);
	DrawBox(drawStringPosX, drawStringPosY + 350, drawStringPosX + 1000, drawStringPosY + 35, 0x0000ff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Title::FadeStringDraw()
{
	m_particle->Draw();
	DrawRotaGraph(graphPosX, graphPosY, 0.8, 0, m_handle, true);
	
	//DrawRotaString(drawStringPosX, drawStringPosY + m_pressAnyButtonY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "Press any button");
	DrawRotaString(drawStringPosX+100, drawStringPosY + m_gameStartY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "GameStart");
	DrawRotaString(drawStringPosX+50, drawStringPosY + m_rightsNotationY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "RightsNotation");

	
	// フェード暗幕
	int alpha = static_cast<int>(255 * (static_cast<float>(m_fadeFrame) / 60.0f));

	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	//DrawRotaString(drawStringPosX, drawStringPosY + m_pressAnyButtonY, 3, 3, 0, 0, 0, 0x000000, 0, 0, "Press any button");
	DrawRotaString(drawStringPosX + 100, drawStringPosY + m_gameStartY, 3, 3, 0, 0, 0, 0x000000, 0, 0, "GameStart");
	DrawRotaString(drawStringPosX + 50, drawStringPosY + m_rightsNotationY, 3, 3, 0, 0, 0, 0x000000, 0, 0, "RightsNotation");

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, drawStringPosY,2000, 2000, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(drawStringPosX, drawStringPosY, drawStringPosX + 1000, drawStringPosY + 20, 0xff0000, true);
	DrawBox(drawStringPosX, drawStringPosY + 20, drawStringPosX + 1000, drawStringPosY + 35, 0x00ff00, true);
	DrawBox(drawStringPosX, drawStringPosY + 350, drawStringPosX + 1000, drawStringPosY + 35, 0x0000ff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Title::FadeOutStringDraw()
{
	m_particle->Draw();
	DrawRotaGraph(graphPosX, graphPosY, 0.8, 0, m_handle, true);

	//DrawRotaString(drawStringPosX, drawStringPosY + m_pressAnyButtonY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "Press any button");
	DrawRotaString(drawStringPosX + 100, drawStringPosY + m_gameStartY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "GameStart");
	DrawRotaString(drawStringPosX + 50, drawStringPosY + m_rightsNotationY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "RightsNotation");


	// フェード暗幕
	int alpha = static_cast<int>(255 * (static_cast<float>(m_fadeFrame) / 60.0f));

	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	//DrawRotaString(drawStringPosX, drawStringPosY + m_pressAnyButtonY, 3, 3, 0, 0, 0, 0x000000, 0, 0, "Press any button");
	DrawRotaString(drawStringPosX + 100, drawStringPosY + m_gameStartY, 3, 3, 0, 0, 0, 0x000000, 0, 0, "GameStart");
	DrawRotaString(drawStringPosX + 50, drawStringPosY + m_rightsNotationY, 3, 3, 0, 0, 0, 0x000000, 0, 0, "RightsNotation");

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 2000, 2000, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(drawStringPosX, drawStringPosY, drawStringPosX + 1000, drawStringPosY + 20, 0xff0000, true);
	DrawBox(drawStringPosX, drawStringPosY + 20, drawStringPosX + 1000, drawStringPosY + 35, 0x00ff00, true);
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
	DrawRotaString(drawStringPosX, drawStringPosY + m_pressAnyButtonY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "Press any button");
	DrawRotaString(drawStringPosX + 100, drawStringPosY + m_gameStartY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "GameStart");
	DrawRotaString(drawStringPosX + 50, drawStringPosY + m_rightsNotationY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "RightsNotation");
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

void Title::NormalStringDraw()
{
	m_particle->Draw();
	DrawRotaGraph(graphPosX, graphPosY, 0.8, 0, m_handle, true);

	//DrawRotaString(drawStringPosX, drawStringPosY + m_pressAnyButtonY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "Press any button");
	DrawRotaString(drawStringPosX + 100, drawStringPosY + m_gameStartY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "GameStart");
	DrawRotaString(drawStringPosX + 50, drawStringPosY + m_rightsNotationY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "RightsNotation");

	
	

	SetDrawBlendMode(DX_BLENDMODE_MULA, 255/4);
	DrawBox(drawStringPosX, drawStringPosY - 45 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY - 30 + m_stringColorPlusA, 0xffddff, true);
	DrawBox(drawStringPosX, drawStringPosY - 30 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY - 15 + m_stringColorPlusA, 0xddffff, true);
	DrawBox(drawStringPosX, drawStringPosY - 15 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY - 0 + m_stringColorPlusA, 0xffddff, true);
	DrawBox(drawStringPosX, drawStringPosY + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY + 15 + m_stringColorPlusA, 0xffdddd, true);
	DrawBox(drawStringPosX, drawStringPosY + 15 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY + 30 + m_stringColorPlusA, 0xddffdd, true);
	DrawBox(drawStringPosX, drawStringPosY + 30 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY + 45 + m_stringColorPlusA, 0xddddff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255 / 3);

	if (m_selectNumber % 2 == 0)
	{
		DrawBox(drawStringPosX + 100, drawStringPosY + m_gameStartY, drawStringPosX +350, drawStringPosY + m_gameStartY + 50, 0xffffff, true);
	}
	else
	{

		DrawBox(drawStringPosX + 50, drawStringPosY + m_rightsNotationY, drawStringPosX + 430, drawStringPosY + m_rightsNotationY + 50, 0xffffff, true);

	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (m_isrightsNotation)
	{
		DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 1, 0, m_rightsHandle, true);
	}
}

void Title::JammingDraw()
{
	SetDrawScreen(m_screenHandle);//レンダーターゲットの変更

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
	DrawRotaString(drawStringPosX, drawStringPosY + m_pressAnyButtonY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "Press any button");
	DrawRotaString(drawStringPosX + 100, drawStringPosY + m_gameStartY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "GameStart");
	DrawRotaString(drawStringPosX + 50, drawStringPosY + m_rightsNotationY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "RightsNotation");
	//DrawBox(0, 0, 2000, 2000, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	
	m_stringColorPlusA++;
	if (m_stringColorPlusA > 50)
	{
		m_stringColorPlusA = 0;
	}

	SetDrawScreen(DX_SCREEN_BACK);//BACKに書き込まないと画面に表示されないので描画先を戻す
	

	int a = GetRand(Game::kScreenHeight);//一個目のy分割
	int b = GetRand(Game::kScreenWidth);//一個目のx分割
	int c = a+GetRand(Game::kScreenHeight-a);//一個目のy分割終点

	DrawRectRotaGraph(Game::kScreenWidth / 2 ,a / 2, 0, 0, Game::kScreenWidth, a, 1, 0, m_screenHandle, 0);//自作レンダーターゲットに描画したものの画像を表示
	DrawRectRotaGraph(Game::kScreenWidth / 2 - b, (a + c) / 2, 0, a, b, c-a, 1, 0, m_screenHandle, 0);//自作レンダーターゲットに描画したものの画像を表示
	DrawRectRotaGraph(Game::kScreenWidth / 2 + b, (a + c) / 2 , b, a, Game::kScreenWidth, c-a, 1, 0, m_screenHandle, 0);//自作レンダーターゲットに描画したものの画像を表示
	DrawRectRotaGraph(Game::kScreenWidth / 2, (c+Game::kScreenHeight) / 2, 0, c, Game::kScreenWidth, Game::kScreenHeight-c, 1, 0, m_screenHandle, 0);//自作レンダーターゲットに描画したものの画像を表示

}
