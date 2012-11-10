@ECHO OFF
REM
REM Configuration Section
REM
REM 
REM


REM Keeps environment variables set in this file from propogating
REM back into the command windows environment
SETLOCAL

REM This is ok as is unless you are on MIPS or ALPHA platform
set CPU=i386

REM Set this to point to your msvc directory
set MSTOOLS=d:\msvc20



REM Uncomment for Winnt 3.51
REM Comment for all others
set TARGETOS=WINNT
set APPVER=3.51

REM Uncomment for Win95
REM Comment for all others
REM set TARGETOS=WIN95
REM set APPVER=4.0

REM If you are debugging you need to unset this and change some
REM of the compiler flags.  More work needed here.
set NODEBUG=1

set MAKEOPTS=-n -p
set MAKEOPTS=


REM ##########################################################################
REM
REM DO NOT Edit Below this line
REM
REM #########################################################################

REM Clean out everything
nmake -f makegeo.vc clean

set DLLOPTS=
set DLLDEFS=
set DLLLINK=

if "%1"=="CON" goto console
if "%1"=="GUI" goto gui

REM else it is ALL or STATIC

REM For ALL or STATIC, begin by building static library
REM Build static library
nmake %MAKEOPTS% -f makegeo.vc DLL=
if "%1"=="" goto done

:console
set DLLOPTS=$(cvarsdll)
set DLLDEFS=-DCONSOLE_BUILD
set DLLLINK=$(dlllflags) -DEF:libgeoc.def
if "%1"=="ALL" nmake -f makegeo.vc clean_objs
nmake %MAKEOPTS% -f makegeo.vc libgeoc.dll "DLL=CON"
if "%1"=="CON" goto done


:gui
set DLLOPTS=$(cvarsdll)
set DLLDEFS=
set DLLLINK=$(dlllflags) -DEF:libgeog.def
if "%1"=="ALL" nmake -f makegeo.vc clean_objs
nmake %MAKEOPTS% -f makegeo.vc libgeog.dll "DLL=GUI"
if "%1"=="GUI" goto done


:done
ENDLOCAL
