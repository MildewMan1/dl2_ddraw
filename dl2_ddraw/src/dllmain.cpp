#include "framework.h"
#include "mem_addresses.h"

#include <cassert>

extern HWND __stdcall myCreateWindowExA(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
extern int __stdcall StartDirectDraw(HWND hWnd, BOOL exclusive, int w, int h, int depth);
extern int __stdcall FindCD(void);
extern void __stdcall TestCopyProtect(void);
extern void __stdcall GetWinCursorPos(int* x, int* y);
extern void __stdcall InitGameCursor(HWND hWnd);
extern int __stdcall AllocateDIBOffport(OFFPORT* offport, int width, int height, int depth);

#ifdef DL2_288
extern int __stdcall SaveUnderBitsDraw(OFFPORT* offport, RECT* rect);
extern int __stdcall AllocateNewCursorBits(int w, int h);
#endif

#ifdef DL2_DEMO
extern int __stdcall PlayStillPic(int id, int timeLimit, const char* text);
#endif

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());

        //Detour DL2's StartDirectDraw function
        DetourAttach(&(PVOID&)pStartDirectDraw, StartDirectDraw);

        DetourAttach(&(PVOID&)pFindCD, FindCD);
        DetourAttach(&(PVOID&)pTestCopyProtect, TestCopyProtect);
        DetourAttach(&(PVOID&)pGetWinCursorPos, GetWinCursorPos);
        DetourAttach(&(PVOID&)pInitGameCursor, InitGameCursor);
        DetourAttach(&(PVOID&)pAllocateDIBOffport, AllocateDIBOffport);

#ifdef DL2_288
        //These lines prevent mouse cursor from loading/showing.
        DetourAttach(&(PVOID&)pAllocateNewCursorBits, AllocateNewCursorBits);
        DetourAttach(&(PVOID&)pSaveUnderBitsDraw, SaveUnderBitsDraw);
#endif

#ifdef DL2_DEMO
        DetourAttach(&(PVOID&)pPlayStillPic, PlayStillPic);
#endif
        DetourAttach(&(PVOID&)pCreateWindowExA, myCreateWindowExA);

        DetourTransactionCommit();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());

        DetourDetach(&(PVOID&)pStartDirectDraw, StartDirectDraw);
        DetourDetach(&(PVOID&)pFindCD, FindCD);
        DetourDetach(&(PVOID&)pTestCopyProtect, TestCopyProtect);
        DetourDetach(&(PVOID&)pInitGameCursor, InitGameCursor);

#ifdef DL2_288
        DetourDetach(&(PVOID&)pAllocateNewCursorBits, AllocateNewCursorBits);
        DetourDetach(&(PVOID&)pSaveUnderBitsDraw, SaveUnderBitsDraw);
#endif

#ifdef DL2_DEMO
        DetourDetach(&(PVOID&)pPlayStillPic, PlayStillPic);
#endif

        DetourTransactionCommit();
    }
    return TRUE;
}




