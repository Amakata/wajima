# Microsoft Developer Studio Project File - Name="graphics" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=graphics - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "graphics.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "graphics.mak" CFG="graphics - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "graphics - Win32 Release" ("Win32 (x86) Static Library" 用)
!MESSAGE "graphics - Win32 Debug" ("Win32 (x86) Static Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "graphics - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "build/lib/graphics/release"
# PROP Intermediate_Dir "build/lib/graphics/release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "src/lib/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\graphics.lib"

!ELSEIF  "$(CFG)" == "graphics - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "build/lib/graphics/debug"
# PROP Intermediate_Dir "build/lib/graphics/debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "src/lib/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\graphicsd.lib"

!ENDIF 

# Begin Target

# Name "graphics - Win32 Release"
# Name "graphics - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
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
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\src\lib\include\graphics\sys\Adapter.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\include\graphics\BaseSprite.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\include\graphics\BaseSpriteImp.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\include\graphics\sys\D3D8.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\include\graphics\sys\DXAssert.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\include\graphics\ImageSpriteImp.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\include\graphics\sys\Mode.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\include\graphics\Sprite.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\include\graphics\SpriteFactory.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\include\graphics\Sprites.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\include\graphics\TextSpriteImp.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\include\graphics\sys\Win32ImageSpriteImp.h
# End Source File
# Begin Source File

SOURCE=.\src\lib\include\graphics\sys\Win32SpriteFactory.h
# End Source File
# End Group
# End Target
# End Project
