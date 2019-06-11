
#ifndef __UTILITY_H__
#define __UTILITY_H__

#define WIN32_LEAN_AND_MEAN
#define INITGUID

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Math/T3DMath.h"
#include "Math/T3DMatrix4.h"
#include "Math/T3DQuaternion.h"
#include "Math/T3DMatrix3.h"
#include "Math/T3DVector3.h"
#include "Math/T3DTransform.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")

#include "D3DApplication.h"


#define SAFE_DELETE(p)	\
	{					\
		delete (p);		\
		(p) = NULL;		\
	}

#define SAFE_DELETE_ARRAY(p)	\
	{							\
		delete [](p);			\
		(p) = NULL;				\
	}

#define SAFE_RELEASE(p)		\
	{						\
		if (NULL != (p))	\
		{					\
			(p)->Release();	\
			(p) = NULL;		\
		}					\
	}


#define DEF_WNDCLASSNAME		_T("D3DAppClass")
#define DEF_WNDTITLENAME		_T("D3DApplication")

#define DEF_SCREENWIDTH			640
#define DEF_SCREENHEIGHT		480

const D3DXCOLOR      WHITE = D3DCOLOR_XRGB(255, 255, 255);
const D3DXCOLOR      BLACK = D3DCOLOR_XRGB(  0,   0,   0);
const D3DXCOLOR        RED = D3DCOLOR_XRGB(255,   0,   0);
const D3DXCOLOR      GREEN = D3DCOLOR_XRGB(  0, 255,   0);
const D3DXCOLOR       BLUE = D3DCOLOR_XRGB(  0,   0, 255);
const D3DXCOLOR     YELLOW = D3DCOLOR_XRGB(255, 255,   0);
const D3DXCOLOR       CYAN = D3DCOLOR_XRGB(  0, 255, 255);
const D3DXCOLOR    MAGENTA = D3DCOLOR_XRGB(255,   0, 255);

#pragma warning(disable : 4996)

using namespace Tiny3D;

D3DMATRIX toD3DMatrix(const Matrix4 &mat);

Matrix4 toT3DMatrix(const D3DMATRIX &mat);

Matrix4 lookAt(const Vector3 &pos, const Vector3 &obj, const Vector3 &up);
Matrix4 perpective(const Radian &rkFovY, Real aspect, Real nearDist, Real farDist);
Matrix4 ortho(const Radian &rkFovY, Real ratio, Real nearDist, Real farDist);

#endif	/*__UTILITY_H__*/
