// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>


// TODO:  在此处引用程序需要的其他头文件

#include <d2d1.h>
#include <d2d1helper.h>
#include <dinput.h>
#include <dwrite.h>
#include <wincodec.h>

#pragma comment(lib, "dinput8.lib") 
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib,"dxguid.lib")
  

template <class Interface>
inline void SafeRelease(
	Interface** ppInterfaceToRelease
) {
	if (*ppInterfaceToRelease != NULL) {
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}

template <class Interface>
inline void SafeUnacquire(
	Interface** ppInterfaceToRelease
) {
	if (*ppInterfaceToRelease != NULL) {
		(*ppInterfaceToRelease)->Unacquire();

		(*ppInterfaceToRelease) = NULL;
	}
}



#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif
