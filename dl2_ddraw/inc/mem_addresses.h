#pragma once
#ifndef __MEM_ADDRESSES_H__
#define __MEM_ADDRESSES_H__

#include "main.h"

extern int* pglPixFormat;
extern int* pglPixDepth;
extern int* pglUsePixDepth;
extern int* pglUsePixFormat;
extern int* pgWindowWidth;
extern int* pgWindowHeight;
extern HWND* GameHWnd;
extern HWND* hMainWnd;
extern int* overrideCopyProtect;
extern int* cdVerified;
extern int* cdFound;
extern char* cdPath;
extern int* sgBitDepth;

#ifndef DL2_DEMO
extern int* dontAsk;
#else
extern PlayStillPic_TYPE pPlayStillPic;
#endif

extern CopyProtect_TYPE* pCopyProtect;
extern CopyProtect_TYPE pPassCopyProtect;

extern OFFPORT* GamelibOffport;

extern StartDirectDraw_TYPE pStartDirectDraw;
extern AllocateOffport_TYPE pAllocateDIBOffport;
extern AdjustMainOffportWindowLink_TYPE pAdjustMainOffportWindowLink;
extern SetDClip_TYPE pSetDClip;
extern FindCD_TYPE pFindCD;
extern TestCopyProtect_TYPE pTestCopyProtect;
extern GetWinCursorPos_TYPE pGetWinCursorPos;
extern InitGameCursor_TYPE pInitGameCursor;

#ifdef DL2_288
extern AllocateNewCursorBits_TYPE pAllocateNewCursorBits;
extern SaveUnderBitsDraw_TYPE pSaveUnderBitsDraw;
#endif

extern CreateWindowExA_TYPE pCreateWindowExA;

#endif
