#include "Application.h"
#include "SceneManager.h"
#include "Title.h"
#include "FileManager.h"
#include <DxLib.h>
#include <cassert>

namespace
{
    constexpr int kScreenWidth =1600;
    constexpr int kScreenHeight = 900;
}

int MyLoadGraph(const TCHAR* path)
{
    int handle = LoadGraph(path);
    assert(handle != -1);
    return handle;
}

Application::Application()
{
    m_windowSize = Size{ kScreenWidth, kScreenHeight };
}

void Application::Terminate()
{
    DxLib_End();
}

float Application::GetGravity() const
{
    return 0.5f;
}

bool Application::Init()
{
    ChangeWindowMode(true); // ウィンドウモードにします
    SetGraphMode(m_windowSize.w, m_windowSize.h, 1);
    SetWindowSizeChangeEnableFlag(TRUE, TRUE);
    SetChangeScreenModeGraphicsSystemResetFlag(false);

    SetGraphMode(1600, 900, 32);
    SetWindowSize(1600, 900);
    //SetWindowSizeExtendRate(1.2f,1.2f);
    void* CallBack();

    DxLib_Init();
   
    SetUseASyncChangeWindowModeFunction(TRUE,NULL, NULL);

    SetWindowText("スーパーサイヤング7");
    if (DxLib_Init() == -1)
    {
        return false;
    }
    SetDrawScreen(DX_SCREEN_BACK);

    return true;
}

void Application::Run()
{
    {// スコープを強制的に作っている
        
        SceneManager sceneManager;
        sceneManager.ChangeScene(std::make_shared<Title>(sceneManager));
        

        LONGLONG time;
        while (ProcessMessage() != -1)
        {
            // FPSの固定ように開始時の時間を取得
            time = GetNowHiPerformanceCount();

            ClearDrawScreen();
            if (CheckHitKey(KEY_INPUT_ESCAPE))
            {
                ChangeWindowMode(true);
            }
            sceneManager.Update();
            sceneManager.Draw();
            ScreenFlip();

            // 60FPSに固定
            while (16667 > GetNowHiPerformanceCount() - time) {};
        }
    }
    //Terminate();
}

const Size& Application::GetWindowSize() const
{
    return m_windowSize;
}
