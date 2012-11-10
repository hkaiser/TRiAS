@echo off

rem
rem Standardmäßig alles 'Release' bauen
rem Fr 'Debug' mit 'MakeTRiAS trias3deb' rufen
rem
set TARGET=%1
IF __%1 == __ SET TARGET=trias3rel

rem 
rem Umgebungsvariablen initialisierem
rem
set GEOMEDIA=D:\TRiASDev.MVC\Include\GMObjects\tlb
set INCLUDE=D:\TRiASDev.MVC\Include
set PREBUILDLIB="D:\TRiASDev.MVC\PreBuildLibs"

rem
rem Allgemeine Optionen
rem
set T3LOGDIR=D:\MAKE\RELEASE\LOG
if __%1 == __trias3deb set T3LOGDIR=D:\MAKE\DEBUG\LOG
set T3MAKEOPTIONS=/A /NOLOGO
rem SET T3MAKEOPTIONS=/I /NOLOGO

rem
rem Zusätzliche Optionen für MsDev
rem
rem set T3BUILDOPTIONS=/REBUILD /NORECURSE
set T3BUILDOPTIONS=/NORECURSE

rem
rem Pfade, wo die Tools zu finden sind
rem
set T3MSDEV="D:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\msdev.exe"
set T3VSS="D:\Program Files\Microsoft Visual Studio\Common\VSS\win32\SS.EXE"

rem
rem Alte Logfiles löschen
rem
del %T3LOGDIR%\*.log > nul

rem
rem Alle Makefiles an ihren Platzkopieren
rem
call StoreMakefiles.cmd

rem
rem Hier gehts los ...
rem
nmake %T3MAKEOPTIONS% /D /F MAKEFILE.mak %TARGET%

goto nmake_el%errorlevel%

goto :nmake_end

:nmake_el0
echo === nmake abgearbeitet ==========================================
echo Kein Fehler
goto :nmake_end

:nmake_el1
echo === nmake abgearbeitet ==========================================
echo Unvollständiger Build
goto :nmake_end

:nmake_el2
echo === nmake abgearbeitet ==========================================
echo Programmfehler
goto :nmake_end

:nmake_el4
echo === nmake abgearbeitet ==========================================
echo Systemfehler
goto :nmake_end

:nmake_el255
echo === nmake abgearbeitet ==========================================
echo Ziel ist nicht aktuell
goto :nmake_end

:nmake_end

