// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#define WIN32_LEAN_AND_MEAN		// Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル :
#include <windows.h>
#include <mmsystem.h>
// C RunTime ヘッダー ファイル
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
// C++ ヘッダー ファイル
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
// TODO: プログラムに必要な追加ヘッダーをここで参照してください。

#define DISPLAY_WIDTH	800
#define DISPLAY_HEIGHT	600

#include "d3d.h"
#include "device.h"
#include "vertex.h"

#define WM_RENDER	WM_USER
