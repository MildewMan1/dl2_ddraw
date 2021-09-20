#pragma once
#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

#ifdef _UNICODE
#undef _UNICODE
#endif

#ifndef _MBCS //make sure project is multibyte and not unicode. This is what was used in DL2.
#define _MBCS
#endif

#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <ddraw.h> //included only for struct definitions.
#include <detours.h>

#pragma comment(lib, "detours.lib")







#endif
