#pragma once
#include"Vec2.h"
class EndRoll
{
public:
	EndRoll();
	~EndRoll();

	void Init();
	void Update();
	void Draw();
	
private:
	int m_scrollSpeed = 0;
	Vec2 m_MainScrollPos;//�G���h���[���̎厲�ɂȂ�|�W�V����<-���ꂩ��̑��Έʒu�ŕ����̈ʒu�����߂�
	int m_titleLogo = 0;


};

