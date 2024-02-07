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
	Vec2 m_MainScrollPos;//エンドロールの主軸になるポジション<-これからの相対位置で文字の位置を決める
	int m_titleLogo = 0;


};

