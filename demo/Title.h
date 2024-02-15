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
	
	int m_gameIntroduceHandle[6];

	int m_jammingPosY = 0;
	int m_windowHandle = 0;


	int m_bgmHandle = 0;
	int m_jammingSound = 0;


	int m_selectNumber = 0;
	int m_pressAnyButtonY = 0;
	int m_gameStartY = 430;
	int m_rightsNotationY = 550;
	int m_gameIntroduceY = 500;
	int m_gameIntroduceNum = 0;
	int m_rightsHandle = 0;

	bool m_isSelectMode = false;
	bool m_isrightsNotation = false;
	bool m_isGameIntroduce = false;
	Particle* m_particle;

	// 更新メンバ関数ポインタ
	void(Title::* m_updateFunc)();
	// 描画メンバ関数ポインタ
	using DrawFunc_t = void (Title::*)();
	DrawFunc_t m_drawFunc;

	// 更新関数
	void FadeInUpdate();	// フェードイン状態
	void FadeInStringUpdate();
	void NormalStringUpdate();	// 通常状態
	void NormalUpdate();	// 通常状態
	void FadeOutUpdate();	// フェードアウト状態
	void FadeOutStringUpdate();
	

	void JammingUpdate();

	// 描画関数
	void FadeDraw();	// フェード中描画
	void FadeStringDraw();
	void FadeOutStringDraw();
	void NormalDraw();	// 非フェード描画
	void NormalStringDraw();	// 非フェード描画
	void JammingDraw();
};

