#pragma once
#include "Scene.h"
class IntroScene :
    public Scene
{
public:
	IntroScene(SceneManager& mgr);

	void Update();
	void Draw();

private:
	int m_frame = 0;
	int m_select = 0;

	// 更新メンバ関数ポインタ
	using UpdateFunc_t = void(IntroScene::*)();
	UpdateFunc_t  m_updateFunc;
	// 描画メンバ関数ポインタ
	using DrawFunc_t = void (IntroScene::*)();
	DrawFunc_t m_drawFunc;

	// 更新関数
	void AppearUpdate();	// 登場状態
	void NormalUpdate();		// 通常状態
	void DisappearUpdate();	// 退場状態

	// 描画関数
	void ExpandDraw();	// 拡張縮張描画
	void NormalDraw();	// 非フェード描画

};

