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
	int m_handle;
	int m_graphX;
	int m_graphY;
	int graphRateX;


	// グラフィックに含まれるマップチップの数
	int m_graphChipNumX;
	int m_graphChipNumY;

	// マップチップの配置情報
	int m_chipData[kChipNumY][kChipNumX];
};



