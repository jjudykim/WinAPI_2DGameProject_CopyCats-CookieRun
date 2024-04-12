#pragma once

#include <Windows.h>
#include <assert.h>

#include <algorithm>
#include <vector>
using std::vector;

#include <list>
using std::list;

#include <map>
using std::map;
using std::make_pair;

#include <iostream>
#include <string>
using std::string;
using std::wstring;

// TransparentBlt
#pragma comment(lib, "Msimg32.lib")

#include "define.h"
#include "enum.h"
#include "struct.h"
#include "func.h"

#include "CSelectObj.h"

// PNG
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "GdiPlus.lib")
using namespace Gdiplus;

// File Path -> Name
#include <shlwapi.h> 
#pragma comment(lib, "shlwapi.lib") 

// MFC, Common Controls
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

// Sound
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

// Loading
#define WM_CUSTOM_LOAD_COMPLETE (WM_USER + 1)
