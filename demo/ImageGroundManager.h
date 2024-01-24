#pragma once
#include"Bg.h"

class Bg;
class ForeGround;

class ImageGroundManager
{
public:
	ImageGroundManager();

	void Init();
	void Update();
	void Draw();
private:
	Bg* m_bg[BG_KIND_NUM];
	ForeGround* m_foreGround;
};

