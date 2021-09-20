#pragma once
#ifndef __MAIN_H__
#define __MAIN_H__

#include <ddraw.h> //included for the struct definitions.

struct OFFPORT;
struct OFFPORT2;

enum OFFPORT_TYPES
{
    DDSURFACE_OFFPORT,
    BITMAP_OFFPORT,
    MEMORY_OFFPORT1,
    MEMORY_OFFPORT2,
};

enum PICT_TYPES
{
    NULL_PICT,
    TARGA_PICT,
    IFF_PICT,
    LBM_PICT,
    FLIC_PICT,
    PCX_PICT,
    SMACK_PICT,
};

enum GLMOVIE_STATES
{
    NOT_INITIALIZED,
    STOPPED,
    PAUSED,
    PLAYING,
};

enum PIXEL_DEPTHS
{
    _4_BIT = 4,
    _8_BIT = 8,
    _16_BIT = 16,
    _24_BIT = 24,
    _32_BIT = 32,
};

enum PIXEL_FORMATS
{
    RGB8 = 1,
    RGB555,
    RGB565,
    RGB24,
    HSV,
};

struct myBITMAPINFO
{
    BITMAPINFOHEADER bmi;
    RGBQUAD pal[256];
};

#pragma pack(push, 1) //pack the struct to prevent padding.
struct FLIC_HEADER
{
    DWORD filesize;
    WORD type;
    short frames;
    short width;
    short height;
    WORD depth;
    WORD flags;
    DWORD speed;
    WORD reserved1;
    DWORD created;
    DWORD creator;
    DWORD updated;
    DWORD updater;
    WORD aspect_dx;
    WORD aspect_dy;
    WORD ext_flags;
    WORD keyframes;
    WORD totalframes;
    DWORD req_memory;
    WORD max_regions;
    WORD transp_num;
    BYTE reserved2[24];
    DWORD oframe1;
    DWORD oframe2;
    BYTE reserved3[40];
};

struct GLFILE_HANDLE
{
    HANDLE hFile;
    int numBytesRead_Or_LastErrorNumber;
    int ptrType;
    DWORD offset;
    LONG distanceToMove;
    DWORD filePointer;
    char* pMem;
    char* pMem2;
};

struct SMACK_HANDLE
{
    void* hSmack; //smacker handle.
    int x;
    int y;
    HANDLE hFile;
};

struct GLMOVIE
{
    GLFILE_HANDLE* glFile;
    GLMOVIE_STATES state;
    int* ptr;
    int smackHeight;
    int smackWidth;
    int flags;
    OFFPORT2* offport;
    SMACK_HANDLE* smackHandle;
    void(__stdcall* Close)(GLMOVIE*);
    BOOL(__stdcall* CanPlay)(GLMOVIE*);
    BOOL(__stdcall* CanStop)(GLMOVIE*);
    BOOL(__stdcall* CanPause)(GLMOVIE*);
    BOOL(__stdcall* IsInitialized)(GLMOVIE*);
    BOOL(__stdcall* GetSize)(GLMOVIE*, int* w, int* h);
    void(__stdcall* ChangeStateTo)(GLMOVIE*, GLMOVIE_STATES state);
    void(__stdcall* DeleteData)(GLMOVIE*);
    BOOL(__stdcall* Position)(GLMOVIE*, int x, int y, int w, int h);
    BOOL(__stdcall* IsPlaying)(GLMOVIE*);
    BOOL(__stdcall* AbortStop)(GLMOVIE*);
    BOOL(__stdcall* Stop)(GLMOVIE*);
    BOOL(__stdcall* Play)(GLMOVIE*, BOOL loop);
    BOOL(__stdcall* Pause)(GLMOVIE*);
    BOOL(__stdcall* Show)(GLMOVIE*, BOOL visible);
    BOOL(__stdcall* Poll)(GLMOVIE*);
    BOOL(__stdcall* DrawFrame)(GLMOVIE*);
};

struct FLIC
{
    GLFILE_HANDLE* glFile;
    int currFrameNum;
    FLIC_HEADER hdr;
};
#pragma pack(pop)

//auto FlicHdrSize = sizeof(FLIC_HEADER); //should be 128 bytes.

struct OFFPORT
{
    char* surfacePtr;
    int w;
    int h;
    int depth;
    int rowBytes;
    int windowLinkX;
    int windowLinkY;
    int dword28;
    int dword32;
    short lockCount;
    short pixelFormat;
    short flags;
    short objectType;
    RECT rect;
    HGLOBAL cyPalette;
    union
    {
        LPDIRECTDRAWSURFACE lpDDSurface;
        HBITMAP hBmp;
    };
    DDSURFACEDESC ddsd;
};


//auto offportSize = sizeof(OFFPORT); //should be 176 bytes.

struct OFFPORT2
{
    OFFPORT op;
    PICT_TYPES pictType;
    BOOL bIsStreamed;
    union
    {
        GLMOVIE* glMovie;
        FLIC* pFlic;
    };
    int int188; //unknown what is stored in this.
};

//auto offport2Size = sizeof(OFFPORT2); //should be 192 bytes.

using StartDirectDraw_TYPE = int (__stdcall*)(HWND hwnd, BOOL exclusive, int width, int height, int depth);
using AllocateOffport_TYPE = int (__stdcall*)(OFFPORT* offport, int w, int h, int depth);
using AdjustMainOffportWindowLink_TYPE = void (__stdcall*)(HWND hwnd, int x, int y);
using SetDClip_TYPE = BOOL(__stdcall*)(RECT* rect);
using CopyProtect_TYPE = BOOL(__stdcall*)(int);
using FindCD_TYPE = int(__stdcall*)(void);
using TestCopyProtect_TYPE = void(__stdcall*)(void);
using AllocateNewCursorBits_TYPE = int (__stdcall*)(int w, int h);
using SaveUnderBitsDraw_TYPE = int (__stdcall*)(OFFPORT* offport, RECT* rect);
using GLCursorActivate_TYPE = int (__stdcall*)(OFFPORT* offport, BOOL init);
using InitCursorThread_TYPE = int(__stdcall*)(void);
using CursorCallbackProc_TYPE = BOOL (__stdcall*)(HWND hWnd, int msg, WPARAM iParam, LPARAM lParam);
using InitGameCursor_TYPE = void (__stdcall*)(HWND hwnd);
using PlayStillPic_TYPE = int (__stdcall*)(int id, int timeLimit, const char* text);
using GetWinCursorPos_TYPE = void (__stdcall*)(int* x, int* y);
using CreateWindowExA_TYPE = HWND(__stdcall*)(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
#endif
