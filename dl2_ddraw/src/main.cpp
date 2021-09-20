#include "framework.h"

#include <string>

#include "mem_addresses.h"
#include "main.h"

//Must export this function because it is imported by DL2.
extern "C"
HRESULT __stdcall DirectDrawCreate(GUID * lpGUID, LPDIRECTDRAW * lplpDD, IUnknown * pUnkOuter)
{
	return S_OK;
}

//Hook the real CreateWindowExA Windows function to make game have system menu.
HWND __stdcall myCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	const std::string mainWndClassName("XenoMainWnd");
	const std::string strMainWindowTitle("Deadlock 2: Shrine Wars");

	size_t sz1 = mainWndClassName.find(lpClassName);
	size_t sz2 = strMainWindowTitle.find(lpWindowName);

	if (sz1 != std::string::npos && sz2 != std::string::npos)
	{
		nWidth += GetSystemMetrics(SM_CXFRAME);
		nHeight += GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION);

		return pCreateWindowExA(0, lpClassName, lpWindowName, (WS_CAPTION | WS_SYSMENU), 0, 0, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}

	return pCreateWindowExA(0, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

void __stdcall SetupDIBPixelFormat(void)
{
	auto hdcScreen = GetDC(nullptr);
	auto hMemBmp = CreateCompatibleBitmap(hdcScreen, 1, 1);
	if (hMemBmp)
	{
		myBITMAPINFO dib;
		dib.bmi.biSize = sizeof(dib.bmi);
		dib.bmi.biBitCount = 0;
		GetDIBits(hdcScreen, hMemBmp, 0, 0, nullptr, (LPBITMAPINFO)&dib, DIB_RGB_COLORS);
		*pglPixDepth = dib.bmi.biBitCount;

		switch (dib.bmi.biBitCount)
		{
		case _32_BIT: [[fallthrough]];
		case _24_BIT: [[fallthrough]];
		case _16_BIT:
		{
			dib.bmi.biSize = sizeof(dib.bmi);
			dib.bmi.biWidth = 1;
			dib.bmi.biHeight = 1;
			dib.bmi.biPlanes = 1;
			dib.bmi.biCompression = 3;
			char* bits;
			GetDIBits(hdcScreen, hMemBmp, 1, 1, (void**)&bits, (LPBITMAPINFO)&dib, DIB_RGB_COLORS);

			if (*(int*)dib.pal != 0x7C00L
				|| *(int*)&dib.pal[1] != 0x3E0L
				|| *(int*)&dib.pal[2] != 0x1FL)
			{
				*pglPixFormat = RGB565;
			}
			else
				*pglPixFormat = RGB555;

			break;
		}
		default:
			*pglPixFormat = RGB8;
			*pglPixDepth = _8_BIT;
			break;
		}

		DeleteObject(hMemBmp);
	}
	ReleaseDC(nullptr, hdcScreen);
}

void __stdcall SetupPixFormat(void)
{
	SetupDIBPixelFormat();
	*pglUsePixDepth = *pglPixDepth;
	*pglUsePixFormat = *pglPixFormat;
}

int __stdcall DIBRowBytes(myBITMAPINFO* dib)
{
	auto imageSize = dib->bmi.biBitCount * dib->bmi.biWidth * dib->bmi.biPlanes + 31;
	if (imageSize < 0)
		imageSize = dib->bmi.biBitCount * dib->bmi.biWidth * dib->bmi.biPlanes + 62;
	return 4 * (imageSize >> 5);
}

void __stdcall SetOffportClip(OFFPORT* offport, RECT* rect)
{
	if (offport)
	{
		if (rect)
			memcpy(&offport->rect, rect, sizeof(offport->rect));
		else
		{
			offport->rect.top = 0;
			offport->rect.left = 0;
			offport->rect.right = offport->w;
			offport->rect.bottom = offport->h;
		}
	}
}

//This function is detoured from Deadlock 2.
int __stdcall AllocateDIBOffport(OFFPORT* offport, int width, int height, int depth)
{
	if (!depth)
		depth = *pglUsePixDepth;

	auto hdcScreen = GetDC(nullptr);
	myBITMAPINFO dib;

	for (auto i = 0; i < 256; i++)
	{
		dib.pal[i].rgbBlue = i;
		dib.pal[i].rgbRed = i;
		dib.pal[i].rgbGreen = i;
	}

	dib.bmi.biSize = sizeof(dib.bmi);
	dib.bmi.biWidth = width;
	dib.bmi.biHeight = -height;
	dib.bmi.biPlanes = 1;
	dib.bmi.biBitCount = depth;
	dib.bmi.biCompression = 0;

	int format;

	switch (depth)
	{
	case _24_BIT: [[fallthrough]];
	case _32_BIT:
		format = RGB24;
		break;
	case _16_BIT:
		dib.bmi.biCompression = 3;
		if (_16_BIT == *pglUsePixDepth)
			format = *pglUsePixFormat;
		else
			format = RGB555;
		if (format == RGB555)
		{
			*(int*)&dib.pal[0] = 0x7C00L;
			*(int*)&dib.pal[1] = 0x3E0L;
		}
		else
		{
			*(int*)&dib.pal[0] = 0xF800L;
			*(int*)&dib.pal[1] = 0x7E0L;
		}
		*(int*)&dib.pal[2] = 0x1FL;
		break;
	default:
		format = RGB8;
		break;
	}

	dib.bmi.biSizeImage = 0;
	dib.bmi.biXPelsPerMeter = 1;
	dib.bmi.biYPelsPerMeter = 1;
	dib.bmi.biClrUsed = 0;

	if (depth < _24_BIT)
		dib.bmi.biClrUsed = depth ^ 2;
	dib.bmi.biClrImportant = 0;

	char* bits;
	auto hbmp = CreateDIBSection(hdcScreen, (LPBITMAPINFO)&dib, 0, (void**)&bits, nullptr, DIB_RGB_COLORS);
	memset(offport, 0, sizeof(OFFPORT));

	offport->w = width;
	offport->h = height;
	offport->surfacePtr = bits;
	offport->depth = depth;
	offport->flags = 0;
	offport->lockCount = 0;
	offport->rowBytes = DIBRowBytes(&dib);
	offport->objectType = BITMAP_OFFPORT;
	offport->hBmp = hbmp;
	offport->cyPalette = nullptr;
	offport->pixelFormat = format;
	SetOffportClip(offport, nullptr);

	ReleaseDC(nullptr, hdcScreen);
	return 1;
}

//This function is detoured from Deadlock 2.
int __stdcall StartDirectDraw(HWND hWnd, BOOL exclusive, int w, int h, int depth)
{
	*GameHWnd = hWnd; //store hWnd in DL2's global variable.

	SetupPixFormat();

	*pgWindowWidth = w; //store w in DL2 global variable.
	*pgWindowHeight = h; //store h in DL2 global variable.

	pAllocateDIBOffport(GamelibOffport, w, h, depth);
	GamelibOffport->flags = 6; //game uses this flag to distinguish the primary offport.

	RECT rect;
	GetWindowRect(hWnd, &rect);

	if (!exclusive)
	{
		rect.top += GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION);
		rect.left += GetSystemMetrics(SM_CXFRAME);
	}

	pAdjustMainOffportWindowLink(hWnd, rect.left, rect.top);

	pSetDClip(&GamelibOffport->rect);

	return TRUE;
}

void __stdcall GetWinCursorPos(int* x, int* y)
{
	POINT pt;

	GetCursorPos(&pt);

	ScreenToClient(*hMainWnd, &pt);

	*y = pt.y;
	*x = pt.x;
}

void __stdcall TestCopyProtect(void)
{
	return;
}

int __stdcall FindCD(void)
{
	//First call the real FindCD function to check if CD is inserted.
	//If real function returns 1, return 1.
	if (pFindCD())
		return TRUE;

#ifndef DL2_DEMO
	*dontAsk = TRUE;
#endif
	*overrideCopyProtect = TRUE;

	*cdVerified = TRUE;
	*cdFound = TRUE;

	*pCopyProtect = pPassCopyProtect;

	memset(cdPath, 0, sizeof(char) * 16);

	return TRUE;
}

void __stdcall InitGameCursor(HWND hWnd)
{
	return;
}

#ifdef DL2_288
int __stdcall AllocateNewCursorBits(int w, int h)
{
	return 0;
}

int __stdcall SaveUnderBitsDraw(OFFPORT* offport, RECT* rect)
{
	return 0;
}

#endif

#ifdef DL2_DEMO
int __stdcall PlayStillPic(int id, int timeLimit, const char* text)
{
	//The 3 demo screens that are shown when exiting game have a timelimit of 25000.
	//No other still pics have this time limit.
	if (timeLimit == 25000)
	{
		return 0; //return 0 always to never show a still pic when opening or closing game.
	}

	return pPlayStillPic(id, timeLimit, text);
}
#endif