@SET VSINSTALLDIR=C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\IDE
@SET VCINSTALLDIR=C:\Program Files\Microsoft Visual Studio .NET 2003
@SET FrameworkDir=C:\WINDOWS\Microsoft.NET\Framework
@SET FrameworkVersion=v1.1.4322
@SET FrameworkSDKDir=C:\Program Files\Microsoft Visual Studio .NET 2003\SDK\v1.1
@rem Root of Visual Studio common files.

@if "%VSINSTALLDIR%"=="" goto Usage
@if "%VCINSTALLDIR%"=="" set VCINSTALLDIR=%VSINSTALLDIR%

@rem
@rem Root of Visual Studio ide installed files.
@rem
@set DevEnvDir=%VSINSTALLDIR%

@rem
@rem Root of Visual C++ installed files.
@rem
@set MSVCDir=%VCINSTALLDIR%\VC7

@rem
@echo Setting environment for using Microsoft Visual Studio .NET 2003 tools.
@echo (If you have another version of Visual Studio or Visual C++ installed and wish
@echo to use its tools from the command line, run vcvars32.bat for that version.)
@rem

@REM %VCINSTALLDIR%\Common7\Tools dir is added only for real setup.

@set PATH=%DevEnvDir%;%MSVCDir%\BIN;%VCINSTALLDIR%\Common7\Tools;%VCINSTALLDIR%\Common7\Tools\bin\prerelease;%VCINSTALLDIR%\Common7\Tools\bin;%FrameworkSDKDir%\bin;%FrameworkDir%\%FrameworkVersion%;%PATH%;
@set INCLUDE=%MSVCDir%\ATLMFC\INCLUDE;%MSVCDir%\INCLUDE;%MSVCDir%\PlatformSDK\include\prerelease;%MSVCDir%\PlatformSDK\include;%FrameworkSDKDir%\include;%INCLUDE%
@set LIB=%MSVCDir%\ATLMFC\LIB;%MSVCDir%\LIB;%MSVCDir%\PlatformSDK\lib\prerelease;%MSVCDir%\PlatformSDK\lib;%FrameworkSDKDir%\lib;%LIB%

@goto end

:Usage

@echo. VSINSTALLDIR variable is not set. 
@echo.
@echo SYNTAX: %0
@goto end

:end
bjam -sTOOLS=vc7.1 --prefix=..\..\ install
exit /B0