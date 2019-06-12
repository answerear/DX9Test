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


#ifndef __D3D_PREREQUISITES_H__
#define __D3D_PREREQUISITES_H__


#include <SDL.h>
#include <SDL_main.h>
#include <SDL_syswm.h>
#include <d3d9.h>
#include <d3dx9.h>

typedef signed char         char_t;
typedef unsigned char       uchar_t;
typedef signed short        short_t;
typedef unsigned short      ushort_t;
typedef signed int          int_t;
typedef unsigned int        uint_t;

typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef signed short        int16_t;
typedef unsigned short      uint16_t;
typedef signed int          int32_t;
typedef unsigned int        uint32_t;

typedef signed long long    int64_t;
typedef unsigned long long  uint64_t;


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


#endif	/*__D3D_PREREQUISITES_H__*/
