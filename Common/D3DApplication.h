
#ifndef __D3D_APPLICATION_H__
#define __D3D_APPLICATION_H__


class CD3DApplication
{
public:
	CD3DApplication();
	virtual ~CD3DApplication();

public:
	BOOL InitInstance(HINSTANCE hInstance);
	int Run();
	int ExitInstance();

protected:
	virtual void PreInitInstance();
	virtual BOOL InitD3D()		{ return TRUE; }
	virtual BOOL RenderD3D(DWORD dwDeltaTime)	{ return TRUE; }
	virtual BOOL ReleaseD3D()	{ return TRUE; }

	virtual LRESULT MessageProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)	
	{
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	HWND GetSafeHwnd()	
	{ 
		if (::IsWindow(m_hWnd)) 
			return m_hWnd; 
		return NULL; 
	}

	HINSTANCE GetInstance()	
	{ 
		return m_hInstance; 
	}

private:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;

protected:
	TCHAR		*m_lpszClassName;
	TCHAR		*m_lpszWindowName;

	int			m_nWndXPos;
	int			m_nWndYPos;
	int			m_nWndWidth;
	int			m_nWndHeight;

	DWORD		m_dwStyle;
	DWORD		m_dwExStyle;

	UINT		m_uIconID;
	UINT		m_uMenuID;

	HMENU		m_hMenu;
};


#endif	/*__D3D_APPLICATION_H__*/
