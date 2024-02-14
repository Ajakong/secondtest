#pragma once
#include "Scene.h"
#include <string>
#include <vector>
#include <map>

class SceneMain;

class GamePlayingScene : public Scene
{
public:
    GamePlayingScene(SceneManager& manager);
    ~GamePlayingScene();
    virtual void Update();
    virtual void Draw();

    void getSlectNumber(int a) { m_selectNum = a; }

private:
    
    int m_btnFrame = 0;
    int m_frame = 0;
    int m_lightingFrame=0;

    int m_holySoundHandle = 0;
    int m_stageBgm = 0;

    int m_backBlack = 0;
    

    float m_fps = 0.0f;

    float m_lightRange = 5;
    float LightingPos = 0;

    float m_punishmentRange = 0;
    float m_punishmentFrame = 0;
    float m_punishmentPos = 0;


    bool m_isEndRoll=false;
    bool m_toTitle = false;
   
    int m_selectNum=0;
    int m_DyingSound = 0;
    bool m_soundFlag = false;

    SceneMain* m_Scene;

    

    // メンバ関数ポインタの宣言
    using UpdateFunc_t = void (GamePlayingScene::*)();
    using DrawFunc_t = void (GamePlayingScene::*)();
    UpdateFunc_t m_updateFunc = nullptr;
    DrawFunc_t m_drawFunc = nullptr;



    // 更新関数
    void FadeInUpdate();
    void NormalUpdate();
    void FadeOutUpdate();

    void PlayerLightingUpdate();
    void PunishmentUpdate();

    // 描画関数
    void FadeDraw();
    void NormalDraw();
    void PlayerLightingDraw();
    void PunishmentDraw();
};

