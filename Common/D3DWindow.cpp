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

#include "D3DWindow.h"
#include "D3DApplication.h"

extern CD3DApplication *g_pApp;

//------------------------------------------------------------------------------

CD3DWindow::CD3DWindow()
    : mSDLWindow(nullptr)
{

}

//------------------------------------------------------------------------------

CD3DWindow::~CD3DWindow()
{

}

//------------------------------------------------------------------------------

bool CD3DWindow::Create(const char *title, int32_t x, int32_t y,
    int32_t w, int32_t h, uint32_t flags)
{
    bool ret = false;

    do 
    {
        if (SDL_WasInit(SDL_INIT_VIDEO) != SDL_INIT_VIDEO)
        {
            break;
        }

        mSDLWindow = SDL_CreateWindow(title, x, y, w, h, flags);
        if (mSDLWindow == nullptr)
        {
            break;
        }

        SDL_SysWMinfo sdlInfo;
        SDL_VERSION(&sdlInfo.version);
        if (!SDL_GetWindowWMInfo(mSDLWindow, &sdlInfo))
        {
            break;
        }

        g_pApp->mInstance = sdlInfo.info.win.hinstance;
        mHWnd = sdlInfo.info.win.window;

        if (!CreateD3DDevice())
        {
            break;
        }

        ret = true;
    } while (0);

    if (!ret)
    {
        if (mSDLWindow != nullptr)
        {
            SDL_DestroyWindow(mSDLWindow);
            mSDLWindow = nullptr;
        }
    }

    return ret;
}

//------------------------------------------------------------------------------

void CD3DWindow::Destroy()
{
    if (mSDLWindow != nullptr)
    {
        SDL_DestroyWindow(mSDLWindow);
        mSDLWindow = nullptr;
    }
}

//------------------------------------------------------------------------------

bool CD3DWindow::Render()
{
    bool ret = false;

    do 
    {
        if (mD3DDevice == nullptr)
        {
            break;
        }

        if (!Clear())
        {
            break;
        }

        HRESULT hr = mD3DDevice->BeginScene();
        if (FAILED(hr))
        {
            break;
        }

        if (!RenderD3D())
        {
            break;
        }

        hr = mD3DDevice->EndScene();
        if (FAILED(hr))
        {
            break;
        }

        hr = mD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
        if (FAILED(hr))
        {
            break;
        }

        ret = true;
    } while (0);

    return ret;
}

//------------------------------------------------------------------------------

bool CD3DWindow::Clear()
{
    bool ret = false;

    do 
    {
        if (mD3DDevice == nullptr)
        {
            break;
        }

        HRESULT hr;
        hr = mD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_TARGET, 0, 1.0f, 0);
        if (FAILED(hr))
        {
            break;
        }

        ret = true;
    } while (0);

    return ret;
}

//------------------------------------------------------------------------------

bool CD3DWindow::Update()
{
    return true;
}

//------------------------------------------------------------------------------

bool CD3DWindow::RenderD3D()
{
    return true;
}

//------------------------------------------------------------------------------

bool CD3DWindow::CreateD3DDevice(uint32_t quality, bool fullscreen, bool vsync)
{
    bool ret = false;

    do 
    {
        LPDIRECT3D9 pD3D = g_pApp->GetDirect3D9();
        UINT uAdapter = 0;
        D3DADAPTER_IDENTIFIER9 d3dai;
        D3DDISPLAYMODE d3ddm;
        pD3D->GetAdapterIdentifier(uAdapter, 0, &d3dai);
        pD3D->GetAdapterDisplayMode(uAdapter, &d3ddm);

        D3DPRESENT_PARAMETERS d3dpp;
        memset(&d3dpp, 0, sizeof(d3dpp));

        D3DDEVTYPE devType = D3DDEVTYPE_HAL;

        d3dpp.BackBufferCount = 1;
        d3dpp.EnableAutoDepthStencil = TRUE;

        if (vsync)
            d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
        else
            d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

        d3dpp.Windowed = !fullscreen;
        d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

        int32_t width, height;
        SDL_GetWindowSize(mSDLWindow, &width, &height);

        uint32_t format = SDL_GetWindowPixelFormat(mSDLWindow);
        uint32_t bpp = SDL_BYTESPERPIXEL(format);
        uint32_t colordepth = (bpp << 3);

        if (fullscreen)
        {
            d3dpp.BackBufferWidth = width;
            d3dpp.BackBufferHeight = height;
            d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

            if (colordepth > 16)
                d3dpp.BackBufferFormat = D3DFMT_X8B8G8R8;
            else
                d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
        }
        else
        {
            d3dpp.BackBufferWidth = width;
            d3dpp.BackBufferHeight = height;
            d3dpp.BackBufferFormat = d3ddm.Format;
        }

        if (colordepth > 16)
        {
            // Try to create a 32-bit depth, 8-bit stencil
            if (FAILED(pD3D->CheckDeviceFormat(uAdapter,
                devType, d3dpp.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL,
                D3DRTYPE_SURFACE, D3DFMT_D24S8)))
            {
                // Bugger, no 8-bit hardware stencil, just try 32-bit zbuffer 
                if (FAILED(pD3D->CheckDeviceFormat(uAdapter,
                    devType, d3dpp.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL,
                    D3DRTYPE_SURFACE, D3DFMT_D32)))
                {
                    // Jeez, what a naff card. Fall back on 16-bit depth buffering
                    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
                }
                else
                    d3dpp.AutoDepthStencilFormat = D3DFMT_D32;
            }
            else
            {
                // Woohoo!
                if (SUCCEEDED(pD3D->CheckDepthStencilMatch(uAdapter,
                    devType, d3dpp.BackBufferFormat,
                    d3dpp.BackBufferFormat, D3DFMT_D24X8)))
                {
                    d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;
                }
                else
                    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
            }
        }
        else
        {
            // 16-bit depth, software stencil
            d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
        }

        DWORD dwMultiSampleQuality = quality;
        if (dwMultiSampleQuality < 2) // NONE
            dwMultiSampleQuality = 0;
        if (dwMultiSampleQuality > 16) // MAX
            dwMultiSampleQuality = 16;

        if (dwMultiSampleQuality &&
            checkMultiSampleQuality(
                pD3D,
                D3DMULTISAMPLE_NONMASKABLE,
                &dwMultiSampleQuality,
                d3dpp.BackBufferFormat,
                d3dpp.AutoDepthStencilFormat,
                uAdapter,
                devType,
                fullscreen))
        {
            d3dpp.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
            d3dpp.MultiSampleQuality
                = dwMultiSampleQuality ? dwMultiSampleQuality - 1 : NULL;
        }
        else
        {
            d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
            d3dpp.MultiSampleQuality = NULL;
        }

        HRESULT hr = pD3D->CreateDevice(uAdapter, devType, mHWnd,
            D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &mD3DDevice);
        if (SUCCEEDED(hr))
        {
            //             mD3DDevice->GetRenderTarget(0, &mpRenderSurface);
            //             mD3DDevice->GetDepthStencilSurface( &mpRenderZBuffer );
        }
        else
        {
            hr = pD3D->CreateDevice(uAdapter, devType, mHWnd,
                D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &mD3DDevice);
            if (SUCCEEDED(hr))
            {
                //                 mpD3DDevice->GetRenderTarget( 0, &mpRenderSurface );
                //                 mpD3DDevice->GetDepthStencilSurface( &mpRenderZBuffer );
            }
            else
            {
                hr = pD3D->CreateDevice(uAdapter, devType, mHWnd,
                    D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &mD3DDevice);
                if (SUCCEEDED(hr))
                {
                    //                     mpD3DDevice->GetRenderTarget( 0, &mpRenderSurface );
                    //                     mpD3DDevice->GetDepthStencilSurface( &mpRenderZBuffer );
                }
            }
        }

        ret = true;
    } while (0);

    return ret;
}

//--------------------------------------------------------------------------

bool CD3DWindow::checkMultiSampleQuality(LPDIRECT3D9 pD3D,
    D3DMULTISAMPLE_TYPE type, DWORD *outQuality, D3DFORMAT fBack,
    D3DFORMAT fDepth, UINT adapterNum, D3DDEVTYPE deviceType,
    BOOL fullScreen)
{
    if (SUCCEEDED(pD3D->CheckDeviceMultiSampleType(
        adapterNum,
        deviceType, fBack,
        fullScreen, type, outQuality)))
        return true;

    return false;
}
