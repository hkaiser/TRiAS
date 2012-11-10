@echo off

set T3LOGDIR=D:\MAKE\GET\LOG

rem Pfade, wo die Tools zu finden sind
set T3MSDEV="D:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\msdev.exe"
set T3VSS="D:\Program Files\Microsoft Visual Studio\Common\VSS\win32\SS.EXE"

nmake /F Makefile.mak trias3get /A
goto nmake_el%errorlevel%

goto :nmake_end

:nmake_el0
echo ">>> nmake abgearbeitet >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
echo Kein Fehler
goto :nmake_end
:nmake_el1
echo ">>> nmake abgearbeitet >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
echo Unvollständiger Build
goto :nmake_end
:nmake_el2
echo ">>> nmake abgearbeitet >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
echo Programmfehler
goto :nmake_end
:nmake_el4
echo ">>> nmake abgearbeitet >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
echo Systemfehler
goto :nmake_end
:nmake_el255
echo ">>> nmake abgearbeitet >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
echo Ziel ist nicht aktuell
goto :nmake_end

:nmake_end

