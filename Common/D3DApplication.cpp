/*******************************************************************************
 * MIT License
 *
 * Copyright(c) 2019 Aaron Wang
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ******************************************************************************/

#include "D3DApplication.h"
#include "D3DWindow.h"


//------------------------------------------------------------------------------

CD3DApplication *g_pApp = nullptr;

//------------------------------------------------------------------------------

static int AppEventWatcher(void *userdata, SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_APP_DIDENTERBACKGROUND:
        {
            g_pApp->applicationDidEnterBackground();
        }
        break;
    case SDL_APP_WILLENTERFOREGROUND:
        {
            g_pApp->applicationWillEnterForeground();
        }
        break;
    case SDL_APP_TERMINATING:
        {
            g_pApp->applicationWillTerminate();
        }
        break;
    case SDL_APP_LOWMEMORY:
        {
            g_pApp->applicationLowMemory();
        }
        break;
    }

    return 0;
}

//------------------------------------------------------------------------------

CD3DApplication::CD3DApplication()
    : mWindow(nullptr)
{
    g_pApp = this;
}

//------------------------------------------------------------------------------

CD3DApplication::~CD3DApplication()
{
    g_pApp = nullptr;
}

//------------------------------------------------------------------------------

bool CD3DApplication::Init()
{
    bool ret = false;

    do
    {
        if (SDL_Init(0) != 0)
        {
            const char *error = SDL_GetError();
            break;
        }

        if (SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) 
            != 0)
        {
            const char *error = SDL_GetError();
            break;
        }

        SDL_AddEventWatch(AppEventWatcher, nullptr);

        if (!InitD3D())
        {
            break;
        }

        ret = true;
    } while (0);

	return ret;
}

//------------------------------------------------------------------------------

bool CD3DApplication::Run()
{
    applicationDidFinishLaunching();

    bool isRunning = true;

    while (isRunning)
    {
        // Poll events.
        isRunning = PollEvents();

        if (!isRunning)
            break;

        // Render one frame.
        RenderOneFrame();
    }

    applicationWillTerminate();

    return true;
}

//------------------------------------------------------------------------------

void CD3DApplication::Release()
{
    SDL_Quit();
}

//------------------------------------------------------------------------------

bool CD3DApplication::InitD3D()
{
    bool ret = false;

    do 
    {
        // 创建D3D9对象
        mD3D = ::Direct3DCreate9(D3D_SDK_VERSION);
        if (nullptr == mD3D)
        {
            break;
        }

        // 输出设备信息
        UINT uAdapter = 0;
        for (uAdapter = 0; uAdapter < mD3D->GetAdapterCount(); ++uAdapter)
        {
            D3DADAPTER_IDENTIFIER9 d3dai;
            D3DDISPLAYMODE d3ddm;
            mD3D->GetAdapterIdentifier(uAdapter, 0, &d3dai);
            mD3D->GetAdapterDisplayMode(uAdapter, &d3ddm);
        }

        ret = true;
    } while (0);

    return ret;
}

//------------------------------------------------------------------------------

bool CD3DApplication::PollEvents()
{
    bool ret = true;
    SDL_Event ev;

    while (SDL_PollEvent(&ev) != 0)
    {
        switch (ev.type)
        {
        case SDL_QUIT:
        {
            ret = false;
        }
        break;
        }
    }

    return ret;
}

//------------------------------------------------------------------------------

bool CD3DApplication::RenderOneFrame()
{
    bool ret = false;

    do 
    {
        if (mWindow == nullptr)
        {
            break;
        }

        mWindow->Update();

        mWindow->Render();

        ret = true;
    } while (0);

    return ret;
}

//------------------------------------------------------------------------------

void CD3DApplication::ReleaseD3D()
{
    SAFE_RELEASE(mD3D);
}

//------------------------------------------------------------------------------

void CD3DApplication::applicationDidFinishLaunching()
{
    mWindow = new CD3DWindow();
    mWindow->Create("D3D9 Samples", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 667, 375, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
}

//------------------------------------------------------------------------------

void CD3DApplication::applicationDidEnterBackground()
{

}

//------------------------------------------------------------------------------

void CD3DApplication::applicationWillEnterForeground()
{

}

//------------------------------------------------------------------------------

void CD3DApplication::applicationWillTerminate()
{
    if (mWindow != nullptr)
    {
        mWindow->Destroy();
        SAFE_DELETE(mWindow);
    }
}

//------------------------------------------------------------------------------

void CD3DApplication::applicationLowMemory()
{

}
