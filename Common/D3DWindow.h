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


#ifndef __D3D_WINDOW_H__
#define __D3D_WINDOW_H__


#include "D3DPrerequisites.h"


class CD3DWindow
{
public:
    /// Constructor.
    CD3DWindow();
    /// Destructor.
    virtual ~CD3DWindow();

    /// Create window.
    bool Create(const char *title, int32_t x, int32_t y, 
        int32_t w, int32_t h, uint32_t flags);
    /// Destroy window.
    void Destroy();
    /// Render window.
    bool Render();

    virtual bool Clear();

    /// Update per frame.
    virtual bool Update();
    /// Render with Direct3D 9 per frame.
    virtual bool RenderD3D();

    /// Retrieve handle to the window.
    HWND GetHWnd() { return mHWnd; }

protected:
    /// Create IDirect3D9Device object.
    virtual bool CreateD3DDevice(uint32_t quality = 8, bool fullscreen = false, 
        bool vsync = true);

    bool checkMultiSampleQuality(LPDIRECT3D9 pD3D, D3DMULTISAMPLE_TYPE type,
        DWORD *outQuality, D3DFORMAT fBack, D3DFORMAT fDepth,
        UINT adapterNum, D3DDEVTYPE deviceType, BOOL fullScreen);

    SDL_Window          *mSDLWindow;
    HWND                mHWnd;
    IDirect3DDevice9    *mD3DDevice;
};


#endif	/*__D3D_WINDOW_H__*/
