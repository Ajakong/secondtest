#pragma once
#include "Scene.h"

class Input;
class SceneManager;
/// <summary>
/// �|�[�Y���̃V�[���N���X
/// </summary>
class PauseScene : public Scene
{
public:
	PauseScene(SceneManager& mgr);

	void Update();
	void Draw();

	static bool getSelectTitle() { return m_chouseTitle; }
private:
	int m_frame = 0;
	int m_select = 0;

	int m_tutoHandle = 0;

	bool m_tutoFlag=false;
	static bool m_chouseTitle;

	// �X�V�����o�֐��|�C���^
	using UpdateFunc_t = void(PauseScene::*)();
	UpdateFunc_t  m_updateFunc;
	// �`�惁���o�֐��|�C���^
	using DrawFunc_t = void (PauseScene::*)();
	DrawFunc_t m_drawFunc;

	// �X�V�֐�
	void AppearUpdate();	// �o����
	void NormalUpdate();		// �ʏ���
	void DisappearUpdate();	// �ޏ���

	// �`��֐�
	void ExpandDraw();	// �g���k���`��
	void NormalDraw();	// ��t�F�[�h�`��
};

