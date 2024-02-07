#pragma once
#include "Scene.h"
#include"Particle.h"

class Title : public Scene
{
public:
	Title(SceneManager& manager);
	~Title();
	virtual void Update();
	virtual void Draw();

private:
	
	int m_bottonFrame = 0;
	int m_frame = 0;
	int m_jammingFrame = 0;
	int m_onJammingFrame = 0;
	int a = -1;
	int m_stringColorPlusA=0;
	int m_fadeFrame = 60;
	int m_fadeSoundFrame = 0;
	int m_handle;
	int m_screenHandle = 0;

	int m_jammingPosY = 0;
	int m_windowHandle = 0;


	int m_bgmHandle = 0;
	int m_jammingSound = 0;
	Particle* m_particle;

	// �X�V�����o�֐��|�C���^
	void(Title::* m_updateFunc)();
	// �`�惁���o�֐��|�C���^
	using DrawFunc_t = void (Title::*)();
	DrawFunc_t m_drawFunc;

	// �X�V�֐�
	void FadeInUpdate();	// �t�F�[�h�C�����
	void NormalUpdate();	// �ʏ���
	void FadeOutUpdate();	// �t�F�[�h�A�E�g���
	void JammingUpdate();

	// �`��֐�
	void FadeDraw();	// �t�F�[�h���`��
	void NormalDraw();	// ��t�F�[�h�`��
	void JammingDraw();
};

