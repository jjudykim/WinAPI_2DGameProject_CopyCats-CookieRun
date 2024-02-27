#pragma once

#include <Windows.h>
#include <assert.h>

#include <vector>
using std::vector;

#include <list>
using std::list;

#include <map>
using std::map;

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