# Microsoft Developer Studio Project File - Name="zefirolib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=zefirolib - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "zefirolib.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "zefirolib.mak" CFG="zefirolib - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "zefirolib - Win32 Release" ("Win32 (x86) Static Library" 用)
!MESSAGE "zefirolib - Win32 Debug" ("Win32 (x86) Static Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "zefirolib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "build/zefirolib/release"
# PROP Intermediate_Dir "build/zefirolib/release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "include/lib/" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/zefirolib.lib"

!ELSEIF  "$(CFG)" == "zefirolib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "build/zefirolib/debug"
# PROP Intermediate_Dir "build/zefirolib/debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "include/lib/" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/zefirolibd.lib"

!ENDIF 

# Begin Target

# Name "zefirolib - Win32 Release"
# Name "zefirolib - Win32 Debug"
# Begin Group "std src"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\src\lib\std\Assert.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\std\Asserter.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\std\Exception.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\std\InvalidArgument.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\std\Logger.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\std\NotEqualException.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\std\SourceLine.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\std\UniqueNumberBadAlloc.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\std\UniqueNumberFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\std\sys\Win32Assert.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\std\sys\Win32Exception.cpp
# End Source File
# End Group
# Begin Group "graphics src"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\src\lib\graphics\sys\Adapter.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\graphics\BaseSprite.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\graphics\BaseSpriteImp.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\graphics\sys\D3D8.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\graphics\sys\DXAssert.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\graphics\sys\DXException.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\graphics\sys\DXInvalidArgument.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\graphics\ImageSpriteImp.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\graphics\sys\Mode.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\graphics\Sprite.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\graphics\SpriteFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\graphics\Sprites.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\graphics\sys\Win32ImageSpriteImp.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\graphics\sys\Win32SpriteFactory.cpp
# End Source File
# End Group
# Begin Group "system src"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\src\lib\system\IllegalThreadStateException.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\system\Mutex.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\system\Process.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\system\SyncObject.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\system\Thread.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\system\TimeOutException.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lib\system\sys\Win32Event.cpp
# End Source File
# End Group
# Begin Group "input src"

# PROP Default_Filter "cpp"
# End Group
# Begin Group "graphics header"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\include\lib\graphics\sys\Adapter.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\BaseSprite.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\BaseSpriteImp.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\sys\D3D8.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\sys\DXAssert.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\sys\DXException.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\sys\DXInvalidArgument.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\ImageSpriteImp.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\sys\Mode.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\Sprite.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\SpriteFactory.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\Sprites.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\TextSpriteImp.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\sys\Win32ImageSpriteImp.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\sys\Win32SpriteFactory.h
# End Source File
# End Group
# Begin Group "system header"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\include\lib\system\IllegalThreadStateException.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\system\Mutex.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\system\Process.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\system\Runnable.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\system\SyncObject.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\system\Thread.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\system\TimeOutException.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\system\sys\Win32Event.h
# End Source File
# End Group
# Begin Group "input header"

# PROP Default_Filter "h"
# End Group
# Begin Group "std header"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\include\lib\std\Assert.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\std\Asserter.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\std\countptr.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\std\Exception.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\std\InvalidArgument.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\std\Logger.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\std\NotEqualException.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\std\SourceLine.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\std\UniqueNumberBadAlloc.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\std\UniqueNumberFactory.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\std\sys\Win32Assert.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\std\sys\Win32Exception.h
# End Source File
# End Group
# End Target
# End Project
