#pragma once

#include "Game.h"
enum BgKind
{
	//�Ŕw�ʂ�BG
	BG_KIND_BACK,
	//�w�ʂ���񖇖ڂ�BG
	BG_KIND_MIDDLE,
	//Bg�̖���
	BG_KIND_NUM
};
class Bg
{
public:
	Bg();
	~Bg();

	void Init();
	void Update();
	void Draw() ;

	int GetHandle()const{}

	// �O���t�B�b�N�̐ݒ�
	void SetHandle(int handle) { m_handle = handle; }


private:
	// �}�b�v�`�b�v�̏��
	static constexpr int kChipWidth = 32;
	static constexpr int kChipHeight = 32;

	// �`�b�v��u����
	static constexpr int kChipNumX = Game::kScreenWidth / kChipWidth;
	static constexpr int kChipNumY = Game::kScreenHeight / kChipHeight;

private:
	int m_handle=0;
	int m_graphX=0;
	int m_graphY=0;
	int graphRateX=0;


	// �O���t�B�b�N�Ɋ܂܂��}�b�v�`�b�v�̐�
	int m_graphChipNumX=0;
	int m_graphChipNumY=0;

	// �}�b�v�`�b�v�̔z�u���
	int m_chipData[kChipNumY][kChipNumX];
};



