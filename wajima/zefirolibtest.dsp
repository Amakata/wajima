# Microsoft Developer Studio Project File - Name="zefirolibtest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=zefirolibtest - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "zefirolibtest.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "zefirolibtest.mak" CFG="zefirolibtest - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "zefirolibtest - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "zefirolibtest - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "zefirolibtest - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "build/lib/test/release"
# PROP Intermediate_Dir "build/lib/test/release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "include/lib/" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /i "include/lib" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 d3d8.lib dxerr8.lib zefirolib.lib cppunitd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /libpath:"lib"

!ELSEIF  "$(CFG)" == "zefirolibtest - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "build/lib/test/debug"
# PROP Intermediate_Dir "build/lib/test/debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "include/lib/" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /i "include/lib" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 d3d8.lib dxerr8.lib zefirolibd.lib cppunitd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"lib"

!ENDIF 

# Begin Target

# Name "zefirolibtest - Win32 Release"
# Name "zefirolibtest - Win32 Debug"
# Begin Group "resource"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\resource\lib\zefirolibtest.rc
# End Source File
# End Group
# Begin Group "graphics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\lib\graphics\sys\test\AdapterTest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\sys\test\AdapterTest.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\graphics\sys\test\D3D8Test.cpp
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\sys\test\D3D8Test.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\graphics\sys\test\DXExceptionTest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\sys\test\DXExceptionTest.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\graphics\sys\test\ModeTest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\sys\test\ModeTest.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\graphics\test\SpriteFactoryTest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\lib\graphics\test\SpriteFactoryTest.h
# End Source File
# End Group
# Begin Group "std"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\lib\std\test\AssertTest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\lib\std\test\AssertTest.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\std\test\ExceptionTest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\lib\std\test\ExceptionTest.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\std\test\NotEqualExceptionTest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\lib\std\test\NotEqualExceptionTest.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\std\test\UniqueNumberFactoryTest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\lib\std\test\UniqueNumberFactoryTest.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\std\sys\test\Win32AssertTest.cpp
# End Source File
# Begin Source File

SOURCE=.\include\lib\std\sys\test\Win32AssertTest.h
# End Source File
# End Group
# Begin Group "thread"

# PROP Default_Filter ""
# End Group
# Begin Group "system"

# PROP Default_Filter ""
# End Group
# Begin Group "input"

# PROP Default_Filter ""
# End Group
# Begin Group "main"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\lib\resource.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\Window.h
# End Source File
# Begin Source File

SOURCE=.\include\lib\WindowClass.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\WinMain.cpp
# End Source File
# End Group
# End Target
# End Project
