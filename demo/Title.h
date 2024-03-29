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


	int m_selectNumber = 0;
	int m_pressAnyButtonY = 0;
	int m_gameStartY = 430;
	int m_rightsNotationY = 500;

	bool m_isSelectMode = false;
	Particle* m_particle;

	// 更新メンバ関数ポインタ
	void(Title::* m_updateFunc)();
	// 描画メンバ関数ポインタ
	using DrawFunc_t = void (Title::*)();
	DrawFunc_t m_drawFunc;

	// 更新関数
	void FadeInUpdate();	// フェードイン状態
	void FadeInStringUpdate();
	void NormalUpdate();	// 通常状態
	void FadeOutUpdate();	// フェードアウト状態
	void FadeOutStringUpdate();
	void JammingUpdate();

	// 描画関数
	void FadeDraw();	// フェード中描画
	void FadeStringDraw();
	void NormalDraw();	// 非フェード描画
	void JammingDraw();
};

