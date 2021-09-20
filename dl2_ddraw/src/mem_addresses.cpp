#include "framework.h"
#include "mem_addresses.h"

CreateWindowExA_TYPE pCreateWindowExA = CreateWindowExA;

//This file holds the memory addresses for functions and global variables 
//for Deadlock 2.

//Create compilation configurations for each type if desired, and define
//only ONE of these 3 in the preprocessor of the project settings.

//An alternative is to just define 1 of these 3 in the framework header depending
//on which version you want to play.

//Only use a dll with the version defined.

//Patch version 1.20
#if defined(DL2_288)
	int* pglPixFormat = (int*)0x65E5A4;
	int* pglPixDepth = (int*)0x65E590;
	int* pglUsePixDepth = (int*)0x65E5A8;
	int* pglUsePixFormat = (int*)0x65E5AC;
	int* pgWindowWidth = (int*)0x65E5B0;
	int* pgWindowHeight = (int*)0x65E5B4;
	HWND* GameHWnd = (HWND*)0x51B834;
	HWND* hMainWnd = (HWND*)0x58F1A4;
	int* dontAsk = (int*)0x4D5980;
	int* overrideCopyProtect = (int*)0x4D59C4;
	int* cdVerified = (int*)0x4D02BC;
	int* cdFound = (int*)0x4D59AC;
	char* cdPath = (char*)0x58F20C;
	int* sgBitDepth = (int*)0x;
	OFFPORT* GamelibOffport = (OFFPORT*)0x65E644;

	CopyProtect_TYPE* pCopyProtect = (CopyProtect_TYPE*)0x4D02B8;
	CopyProtect_TYPE pPassCopyProtect = (CopyProtect_TYPE)0x457AC0;

	StartDirectDraw_TYPE pStartDirectDraw = (StartDirectDraw_TYPE)0x48B623;
	AllocateOffport_TYPE pAllocateDIBOffport = (AllocateOffport_TYPE)0x48BC0D;
	AdjustMainOffportWindowLink_TYPE pAdjustMainOffportWindowLink = (AdjustMainOffportWindowLink_TYPE)0x48AFE3;
	SetDClip_TYPE pSetDClip = (SetDClip_TYPE)0x49A9E7;
	FindCD_TYPE pFindCD = (FindCD_TYPE)0x457864;
	TestCopyProtect_TYPE pTestCopyProtect = (TestCopyProtect_TYPE)0x457B3C;

	AllocateNewCursorBits_TYPE pAllocateNewCursorBits = (AllocateNewCursorBits_TYPE)0x494346;
	SaveUnderBitsDraw_TYPE pSaveUnderBitsDraw = (SaveUnderBitsDraw_TYPE)0x4943AB;
	InitGameCursor_TYPE pInitGameCursor = (InitGameCursor_TYPE)0x415274;
	GetWinCursorPos_TYPE pGetWinCursorPos = (GetWinCursorPos_TYPE)0x48E138;
#endif

//CD release version 1.0
#if defined(DL2_256)
	int* pglPixFormat = (int*)0x65A6A4;
	int* pglPixDepth = (int*)0x65A690;
	int* pglUsePixDepth = (int*)0x65A6A8;
	int* pglUsePixFormat = (int*)0x65A6AC;
	int* pgWindowWidth = (int*)0x65A6B0;
	int* pgWindowHeight = (int*)0x65A6B4;
	HWND* GameHWnd = (HWND*)0x517AAC;
	HWND* hMainWnd = (HWND*)0x58B43C;
	int* dontAsk = (int*)0x4D19B4;
	int* overrideCopyProtect = (int*)0x4D19F8;
	int* cdVerified = (int*)0x4CC304;
	int* cdFound = (int*)0x4D19E0;
	char* cdPath = (char*)0x58B4A4;
	int* sgBitDepth = (int*)0x4D1AC0;

	CopyProtect_TYPE* pCopyProtect = (CopyProtect_TYPE*)0x4CC300;
	CopyProtect_TYPE pPassCopyProtect = (CopyProtect_TYPE)0x4568A8;

	OFFPORT* GamelibOffport = (OFFPORT*)0x65A744;

	StartDirectDraw_TYPE pStartDirectDraw = (StartDirectDraw_TYPE)0x4898AC;
	AllocateOffport_TYPE pAllocateDIBOffport = (AllocateOffport_TYPE)0x489E72;
	AdjustMainOffportWindowLink_TYPE pAdjustMainOffportWindowLink = (AdjustMainOffportWindowLink_TYPE)0x48926C;
	SetDClip_TYPE pSetDClip = (SetDClip_TYPE)0x49716F;
	FindCD_TYPE pFindCD = (FindCD_TYPE)0x45664C;
	TestCopyProtect_TYPE pTestCopyProtect = (TestCopyProtect_TYPE)0x456924;

	InitGameCursor_TYPE pInitGameCursor = (InitGameCursor_TYPE)0x415DB0;
	GetWinCursorPos_TYPE pGetWinCursorPos = (GetWinCursorPos_TYPE)0x48BF38;
#endif

//Demo version
#if defined(DL2_DEMO)
	int* pglPixFormat = (int*)0x64D4FC;
	int* pglPixDepth = (int*)0x64D4E8;
	int* pglUsePixDepth = (int*)0x64D500;
	int* pglUsePixFormat = (int*)0x64D504;
	int* pgWindowWidth = (int*)0x64D508;
	int* pgWindowHeight = (int*)0x64D50C;
	HWND* GameHWnd = (HWND*)0x50E6F0;
	HWND* hMainWnd = (HWND*)0x57E288;
	int* overrideCopyProtect = (int*)0x4C696C;
	int* cdVerified = (int*)0x4C1350;
	int* cdFound = (int*)0x4C6954;
	char* cdPath = (char*)0x57E2F4;
	int* sgBitDepth = (int*)0x;

	CopyProtect_TYPE* pCopyProtect = (CopyProtect_TYPE*)0x4C12E4;
	CopyProtect_TYPE pPassCopyProtect = (CopyProtect_TYPE)0x44F0B9;

	OFFPORT* GamelibOffport = (OFFPORT*)0x64D59C;

	StartDirectDraw_TYPE pStartDirectDraw = (StartDirectDraw_TYPE)0x47DD90;
	AllocateOffport_TYPE pAllocateDIBOffport = (AllocateOffport_TYPE)0x47E382;
	AdjustMainOffportWindowLink_TYPE pAdjustMainOffportWindowLink = (AdjustMainOffportWindowLink_TYPE)0x47D750;
	SetDClip_TYPE pSetDClip = (SetDClip_TYPE)0x48B115;
	FindCD_TYPE pFindCD = (FindCD_TYPE)0x46146B;
	TestCopyProtect_TYPE pTestCopyProtect = (TestCopyProtect_TYPE)0x44F135;
	PlayStillPic_TYPE pPlayStillPic = (PlayStillPic_TYPE)0x47ABFE;
	InitGameCursor_TYPE pInitGameCursor = (InitGameCursor_TYPE)0x4612DC;
	GetWinCursorPos_TYPE pGetWinCursorPos = (GetWinCursorPos_TYPE)0x480274;
#endif