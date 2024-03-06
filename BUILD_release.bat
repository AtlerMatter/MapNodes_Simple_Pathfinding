@echo off
setlocal EnableDelayedExpansion
goto Setup

:Compile
cl.exe /EHsc /MT /fp:precise /sdl /O2 /GL /Ob2 /MP /Iinclude /Isrc\\vendor /Fedebug\\%CurrDir%_debug.exe /Fodebug\\ /Fddebug\\ %file% /link /MACHINE:X64 lib\\*.lib gdi32.lib user32.lib kernel32.lib shell32.lib

::Commented out compiler options
:: /Zi
:: /nologo 

::pause
exit


:Setup
for /f "delims=" %%a in ('dir /s /b /a-d src\\*.cpp') do set "file=!file! "%%a""
set file=%file:~1%

for %%I in (.) do set CurrDir=%%~nI%%~xI

goto set_msvc
exit


:set_msvc
call :check_msvc "%PROGRAMFILES%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
call :check_msvc "%PROGRAMFILES(x86)%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
call :check_msvc "%PROGRAMFILES%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
call :check_msvc "%PROGRAMFILES(x86)%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

echo "Couldn't find MSVC. Please ensure you have Visual Studio installed."
pause
exit


:check_msvc
IF EXIST %1 (
	::set msvc=%1
	call %1
	goto Compile
)