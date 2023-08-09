﻿// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H
#define GRAVITY 10.0f
// Debug Memory Leak
//#define _CRTDBG_MAP_ALLOC
//#endif
//#define _CRTDBG_MAP_ALLOC
// 여기에 미리 컴파일하려는 헤더 추가

#include <crtdbg.h>
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// 여기에 미리 컴파일하려는 헤더 추가
#include <d2d1.h>
#include <d2d1_1.h>
#include <wincodec.h>
#include <comdef.h>
#include <d2d1_1helper.h>
#include <dwrite.h>
#include <sysinfoapi.h>
#include <string>
#include <cassert>
#include <vector>
#include <map>
#include <dcommon.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <cmath>
#include <type_traits>
#include "struct.h"
#include "Time.h"

using namespace std;
#endif //PCH_H
