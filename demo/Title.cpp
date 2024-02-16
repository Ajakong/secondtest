#include <DxLib.h>
#include <cassert>
#include "Application.h"
#include "SceneManager.h"
#include "Title.h"
#include "GamePlayingScene.h"
#include"Game.h"
#include"Pad.h"

// �f�o�b�O���O�֌W
#include <sstream>
#include <iomanip>

namespace
{
	constexpr int graphPosX = 800;
	constexpr int graphPosY = 400;

	constexpr int drawStringPosX = 600;
	constexpr int drawStringPosY = 700;
}

Title::Title(SceneManager& manager) :
	Scene(manager)
{
	m_fadeFrame = 60;
	m_updateFunc = &Title::FadeInUpdate;
	m_drawFunc = &Title::FadeDraw;
	m_handle = LoadGraph("data/logo/Title.png");

	m_gameIntroduceHandle[1] = LoadGraph("data/image/tuto/gameIntroduce.png");
	m_gameIntroduceHandle[2] = LoadGraph("data/image/tuto/gameIntroduce2.png");
	m_gameIntroduceHandle[3] = LoadGraph("data/image/tuto/gameIntroduce3.png");
	m_gameIntroduceHandle[4] = LoadGraph("data/image/tuto/gameIntroduce4.png");
	m_gameIntroduceHandle[5] = LoadGraph("data/image/tuto/gameIntroduce5.png");
	m_gameIntroduceHandle[0] = LoadGraph("data/image/tuto/controller_format.png");

	
	
	
	// output string stream
	// Debug���O�̕\��
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
	OutputDebugString("�^�C�g���V�[����delete����܂���\n");
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
	if (m_fadeFrame <= 0) // �J�ڏ���
	{
		// ���̑J�ڐ�
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
	m_gameIntroduceY -= 7;
	if (0 >= m_fadeFrame)
	{
		m_updateFunc = &Title::NormalStringUpdate;
		m_drawFunc = &Title::NormalStringDraw;

	}
}

void Title::NormalStringUpdate()
{
	if (Pad::IsTrigger(PAD_INPUT_UP) && !m_isrightsNotation&&!m_isGameIntroduce)
	{
		m_selectNumber--;
	}
	if (Pad::IsTrigger(PAD_INPUT_DOWN)&&!m_isrightsNotation&&!m_isGameIntroduce)
	{
		m_selectNumber++;
	}
	if (Pad::IsTrigger(PAD_INPUT_1) && !m_isrightsNotation && !m_isGameIntroduce)
	{
		if (m_selectNumber % 3 == 0)
		{
			m_updateFunc = &Title::FadeOutStringUpdate;
			m_drawFunc = &Title::FadeOutStringDraw;
		}
		if (m_selectNumber % 3 == 1 || m_selectNumber % 3 == -2)
		{
			m_isGameIntroduce = true;
		}
		if(m_selectNumber%3==2||m_selectNumber%3==-1)
		{
			m_isrightsNotation = true;
		}
	}
	else if (Pad::IsTrigger(PAD_INPUT_1) && m_isrightsNotation)
	{
		m_isrightsNotation = false;
	}
	if (m_isGameIntroduce)
	{
		if (Pad::IsTrigger(PAD_INPUT_RIGHT))
		{
			if (m_gameIntroduceNum < 5)
			{
				m_gameIntroduceNum++;
			}
		}
		if (Pad::IsTrigger(PAD_INPUT_LEFT))
		{
			if (m_gameIntroduceNum > 0)
			{
				m_gameIntroduceNum--;
			}
		}
		if (Pad::IsTrigger(PAD_INPUT_1)&&m_gameIntroduceNum==5)
		{
			m_isGameIntroduce = false;
			m_gameIntroduceNum = 0;
		}
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
	
	
	if (60 <= m_fadeFrame)
	{
		StopSoundMem(m_jammingSound);
		
		m_updateFunc = &Title::FadeInStringUpdate;
		m_drawFunc = &Title::FadeStringDraw;
		//m_manager.ChangeScene(std::make_shared<GamePlayingScene>(m_manager));
	}
}

void Title::FadeOutStringUpdate()
{
	m_pressAnyButtonY+=7;
	m_fadeFrame++;
	m_fadeSoundFrame--;
	ChangeVolumeSoundMem(m_fadeSoundFrame * 2, m_bgmHandle);
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
	
	if (m_jammingPosY > 400)
	{
		a = 0;
		m_jammingPosY = 0;
		StopSoundMem(m_jammingSound);
		m_updateFunc = &Title::NormalUpdate;
		m_drawFunc = &Title::NormalDraw;
	}
	/*if (GetJoypadInputState(DX_INPUT_KEY_PAD1) && !GetKeyState(KEY_INPUT_ESCAPE))
	{
		m_updateFunc = &Title::FadeInStringUpdate;
		m_drawFunc = &Title::FadeStringDraw;
		m_fadeFrame = 0;
		m_fadeFrame = m_fadeFrame + 8;
		m_frame++;
	}*/
}

void Title::FadeDraw()
{
	m_particle->Draw();
	DrawRotaGraph(graphPosX, graphPosY,0.8,0, m_handle, true);
	// �ʏ�̕`��
	DrawRotaString(drawStringPosX, drawStringPosY+m_fadeFrame,3,3,0,0,0, 0xffffbb,0,0, "Press any button");
	// �t�F�[�h�Ö�
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
	DrawRotaString(drawStringPosX + 100, drawStringPosY + m_gameStartY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "GameStart");
	DrawRotaString(drawStringPosX + 140, drawStringPosY + m_gameIntroduceY + 10, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "�Q�[���Љ�");
	DrawRotaString(drawStringPosX + 100, drawStringPosY + m_rightsNotationY + 10, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "RightsNotation");
	DrawRotaString(1420, 800, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "A�Ō���");

	// �t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * (static_cast<float>(m_fadeFrame) / 60.0f));

	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	//DrawRotaString(drawStringPosX, drawStringPosY + m_pressAnyButtonY, 3, 3, 0, 0, 0, 0x000000, 0, 0, "Press any button");
	DrawRotaString(drawStringPosX + 100, drawStringPosY + m_gameStartY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "GameStart");
	DrawRotaString(drawStringPosX + 140, drawStringPosY + m_gameIntroduceY + 10, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "�Q�[���Љ�");
	DrawRotaString(drawStringPosX + 100, drawStringPosY + m_rightsNotationY + 10, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "RightsNotation");
	DrawRotaString(1420, 800, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "A�Ō���");
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
	DrawRotaString(drawStringPosX + 140, drawStringPosY + m_gameIntroduceY + 10, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "�Q�[���Љ�");
	DrawRotaString(drawStringPosX + 100, drawStringPosY + m_rightsNotationY + 10, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "RightsNotation");
	DrawRotaString(1420, 800, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "A�Ō���");


	// �t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * (static_cast<float>(m_fadeFrame) / 60.0f));

	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	//DrawRotaString(drawStringPosX, drawStringPosY + m_pressAnyButtonY, 3, 3, 0, 0, 0, 0x000000, 0, 0, "Press any button");
	DrawRotaString(drawStringPosX + 100, drawStringPosY + m_gameStartY, 3, 3, 0, 0, 0, 0xffffbb, 0, 0, "GameStart");
	DrawRotaString(drawStringPosX + 140, drawStringPosY + m_gameIntroduceY + 10, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "�Q�[���Љ�");
	DrawRotaString(drawStringPosX + 100, drawStringPosY + m_rightsNotationY + 10, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "RightsNotation");
	DrawRotaString(1420,800, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "A�Ō���");


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
	DrawRotaString(drawStringPosX + 140, drawStringPosY + m_gameIntroduceY + 10, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "�Q�[���Љ�");
	DrawRotaString(drawStringPosX + 100, drawStringPosY + m_rightsNotationY + 10, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "RightsNotation");
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
	DrawRotaString(drawStringPosX+140 , drawStringPosY + m_gameIntroduceY+10, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "�Q�[���Љ�");
	DrawRotaString(drawStringPosX + 100, drawStringPosY + m_rightsNotationY+10, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "RightsNotation");
	DrawRotaString(1420, 800, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "A�Ō���");

	SetDrawBlendMode(DX_BLENDMODE_MULA, 255/4);
	DrawBox(drawStringPosX, drawStringPosY - 45 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY - 30 + m_stringColorPlusA, 0xffddff, true);
	DrawBox(drawStringPosX, drawStringPosY - 30 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY - 15 + m_stringColorPlusA, 0xddffff, true);
	DrawBox(drawStringPosX, drawStringPosY - 15 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY - 0 + m_stringColorPlusA, 0xffddff, true);
	DrawBox(drawStringPosX, drawStringPosY + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY + 15 + m_stringColorPlusA, 0xffdddd, true);
	DrawBox(drawStringPosX, drawStringPosY + 15 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY + 30 + m_stringColorPlusA, 0xddffdd, true);
	DrawBox(drawStringPosX, drawStringPosY + 30 + m_stringColorPlusA, drawStringPosX + 1000, drawStringPosY + 45 + m_stringColorPlusA, 0xddddff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255 / 3);

	if (m_selectNumber % 3 == 0)
	{
		DrawBox(drawStringPosX + 100, drawStringPosY + m_gameStartY, drawStringPosX +350, drawStringPosY + m_gameStartY + 50, 0xffffff, true);
	}
	else if (m_selectNumber % 3 == 1 || m_selectNumber % 3 == -2)
	{

		DrawBox(drawStringPosX + 100, drawStringPosY + m_gameIntroduceY, drawStringPosX + 350, drawStringPosY + m_gameIntroduceY + 50, 0xffffff, true);

	}
	else if (m_selectNumber % 3 == 2 || m_selectNumber % 3 == -1)
	{

		DrawBox(drawStringPosX + 50, drawStringPosY + m_rightsNotationY, drawStringPosX + 430, drawStringPosY + m_rightsNotationY +50, 0xffffff, true);

	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (m_isrightsNotation)
	{
		DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 1, 0, m_rightsHandle, true);
	}
	if (m_isGameIntroduce)
	{
		SetDrawBlendMode(DX_BLENDMODE_MULA, 255 / 2);
		DrawBox(0, 0, 2000, 1000, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if (m_gameIntroduceNum != 0)
		{
			DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 1, 0, m_gameIntroduceHandle[m_gameIntroduceNum], true);
		}
		else
		{
			DrawRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 0.7f, 0, m_gameIntroduceHandle[m_gameIntroduceNum], true);
		}
		DrawFormatString(800, 50,  0xffffbb, "%d/6",m_gameIntroduceNum+1);
		DrawFormatString(900, 50, 0x00ffdd, "�X�e�B�b�N���͂ŉ摜�؂�ւ�");
	}
}

void Title::JammingDraw()
{
	SetDrawScreen(m_screenHandle);//�����_�[�^�[�Q�b�g�̕ύX

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
	DrawRotaString(drawStringPosX + 140, drawStringPosY + m_gameIntroduceY + 10, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "�Q�[���Љ�");
	DrawRotaString(drawStringPosX + 100, drawStringPosY + m_rightsNotationY + 10, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "RightsNotation");
	DrawRotaString(1420, 800, 2, 2, 0, 0, 0, 0xffffbb, 0, 0, "A�Ō���");
	//DrawBox(0, 0, 2000, 2000, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	
	m_stringColorPlusA++;
	if (m_stringColorPlusA > 50)
	{
		m_stringColorPlusA = 0;
	}

	SetDrawScreen(DX_SCREEN_BACK);//BACK�ɏ������܂Ȃ��Ɖ�ʂɕ\������Ȃ��̂ŕ`����߂�
	

	int a = GetRand(Game::kScreenHeight);//��ڂ�y����
	int b = GetRand(Game::kScreenWidth);//��ڂ�x����
	int c = a+GetRand(Game::kScreenHeight-a);//��ڂ�y�����I�_

	DrawRectRotaGraph(Game::kScreenWidth / 2 ,a / 2, 0, 0, Game::kScreenWidth, a, 1, 0, m_screenHandle, 0);//���샌���_�[�^�[�Q�b�g�ɕ`�悵�����̂̉摜��\��
	DrawRectRotaGraph(Game::kScreenWidth / 2 - b, (a + c) / 2, 0, a, b, c-a, 1, 0, m_screenHandle, 0);//���샌���_�[�^�[�Q�b�g�ɕ`�悵�����̂̉摜��\��
	DrawRectRotaGraph(Game::kScreenWidth / 2 + b, (a + c) / 2 , b, a, Game::kScreenWidth, c-a, 1, 0, m_screenHandle, 0);//���샌���_�[�^�[�Q�b�g�ɕ`�悵�����̂̉摜��\��
	DrawRectRotaGraph(Game::kScreenWidth / 2, (c+Game::kScreenHeight) / 2, 0, c, Game::kScreenWidth, Game::kScreenHeight-c, 1, 0, m_screenHandle, 0);//���샌���_�[�^�[�Q�b�g�ɕ`�悵�����̂̉摜��\��

}
