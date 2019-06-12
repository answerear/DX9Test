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

#ifndef __D3D_APPLICATION_H__
#define __D3D_APPLICATION_H__


#include "D3DPrerequisites.h"

class CD3DWindow;

class CD3DApplication
{
    friend class CD3DWindow;

public:
    /// Constructor.
	CD3DApplication();
    /// Destructor.
	virtual ~CD3DApplication();

public:
    /// Init application.
    virtual bool Init();
    /// Run application.
    virtual bool Run();
    /// Release application.
    virtual void Release();

    /// Retrieve application instance.
    HINSTANCE GetInstance() { return mInstance; }

    /// Retrieve IDirect3D9 object.
    IDirect3D9 *GetDirect3D9() { return mD3D; }

protected:
    /// Init D3D9 environment.
    virtual bool InitD3D();
    /// Poll windows events.
    virtual bool PollEvents();
    /// Render one frame.
    virtual bool RenderOneFrame();
    /// Cleanup D3D9 environment.
    virtual void ReleaseD3D();

public:
    /// Derived class must implement this interface to initialize their work.
    virtual void applicationDidFinishLaunching();
    /// Derived class should implement this interface to handle event when
    /// application enter background.
    virtual void applicationDidEnterBackground();
    /// Derived class should implement this interface to handle event when
    /// application turn back to foreground.
    virtual void applicationWillEnterForeground();
    /// Derived class should implement this interface to handle event when
    /// application will be terminated.
    virtual void applicationWillTerminate();
    /// Derived class should implement this interface to handle event when 
    /// application will have not enough memory.
    virtual void applicationLowMemory();

protected:
    HINSTANCE   mInstance;
    CD3DWindow  *mWindow;

    IDirect3D9  *mD3D;
};


#endif	/*__D3D_APPLICATION_H__*/
