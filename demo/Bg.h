#pragma once

#include "Game.h"
enum BgKind
{
	//最背面のBG
	BG_KIND_BACK,
	//背面から二枚目のBG
	BG_KIND_MIDDLE,
	//Bgの枚数
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

	// グラフィックの設定
	void SetHandle(int handle) { m_handle = handle; }


private:
	// マップチップの情報
	static constexpr int kChipWidth = 32;
	static constexpr int kChipHeight = 32;

	// チップを置く数
	static constexpr int kChipNumX = Game::kScreenWidth / kChipWidth;
	static constexpr int kChipNumY = Game::kScreenHeight / kChipHeight;

private:
	int m_handle=0;
	int m_graphX=0;
	int m_graphY=0;
	int graphRateX=0;


	// グラフィックに含まれるマップチップの数
	int m_graphChipNumX=0;
	int m_graphChipNumY=0;

	// マップチップの配置情報
	int m_chipData[kChipNumY][kChipNumX];
};



