
#include "Utility.h"

CD3DApplication *g_pApp;

CD3DApplication::CD3DApplication()
: m_hInstance(NULL)
, m_hWnd(NULL)
, m_lpszClassName(NULL)
, m_lpszWindowName(NULL)
, m_nWndXPos(0)
, m_nWndYPos(0)
, m_nWndWidth(0)
, m_nWndHeight(480)
, m_dwStyle(0)
, m_dwExStyle(0)
, m_uIconID(0)
, m_uMenuID(0)
, m_hMenu(NULL)
{
	g_pApp = this;
}

CD3DApplication::~CD3DApplication()
{
	SAFE_DELETE_ARRAY(m_lpszClassName);
	SAFE_DELETE_ARRAY(m_lpszWindowName);
}

BOOL CD3DApplication::InitInstance(HINSTANCE hInstance)
{
	PreInitInstance();

	m_hInstance = hInstance;

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_DBLCLKS|CS_VREDRAW|CS_HREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= m_hInstance;
	if(m_uIconID)
		wcex.hIcon		= ::LoadIcon(m_hInstance, MAKEINTRESOURCE(m_uIconID));
	else
		wcex.hIcon		= ::LoadIcon(NULL, (LPCTSTR)IDI_APPLICATION);
	wcex.hCursor		= ::LoadCursor(m_hInstance,IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= m_lpszClassName;
	wcex.hIconSm		= NULL;

	if (!::RegisterClassEx(&wcex))
		return FALSE;

	m_hWnd = ::CreateWindowEx(
		m_dwExStyle, 
		m_lpszClassName, 
		m_lpszWindowName,
		m_dwStyle, 
		m_nWndXPos, 
		m_nWndYPos, 
		m_nWndWidth, 
		m_nWndHeight, 
		NULL, 
		NULL, 
		m_hInstance, 
		NULL);

	if (NULL == m_hWnd)
		return FALSE;

	if (0 != m_uMenuID)
	{
		m_hMenu = ::LoadMenu(m_hInstance, MAKEINTRESOURCE(m_uMenuID));
		if (NULL == m_hMenu)
			return FALSE;
	}

	::ShowWindow(m_hWnd, SW_SHOWNORMAL);
	::UpdateWindow(m_hWnd);

	if (!InitD3D())
		return FALSE;

	return TRUE;
}

int CD3DApplication::Run()
{
	MSG msg;

	static DWORD dwLastTime = timeGetTime();
	while (1)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!::GetMessage(&msg, NULL, 0, 0))
				break;

			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			DWORD dwCurTime = timeGetTime();
			DWORD delta =  dwCurTime - dwLastTime;
			if (!RenderD3D(delta))
				break;
			dwLastTime = dwCurTime;
		}
	}

	return 0;
}

int CD3DApplication::ExitInstance()
{
	ReleaseD3D();
	return 0;
}

void CD3DApplication::PreInitInstance()
{
	int nLength = _tcslen(DEF_WNDCLASSNAME);
	m_lpszClassName = new TCHAR[nLength+1];
	memset(m_lpszClassName, 0, sizeof(TCHAR)*(nLength+1));
	_tcsncpy(m_lpszClassName, DEF_WNDCLASSNAME, nLength);

	nLength = _tcslen(DEF_WNDTITLENAME);
	m_lpszWindowName = new TCHAR[nLength+1];
	memset(m_lpszWindowName, 0, sizeof(TCHAR)*(nLength+1));
	_tcsncpy(m_lpszWindowName, DEF_WNDTITLENAME, nLength);

	m_nWndXPos = CW_USEDEFAULT;
	m_nWndYPos = CW_USEDEFAULT;
	m_nWndWidth = DEF_SCREENWIDTH;
	m_nWndHeight = DEF_SCREENHEIGHT;

	m_dwStyle = WS_VISIBLE|WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU|WS_CAPTION;
	m_dwExStyle = 0;

	m_uIconID = 0;
	m_uMenuID = 0;
}

LRESULT CALLBACK CD3DApplication::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	default:
		return g_pApp->MessageProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}