@echo off

SET CONF=NOTHING

if "-D" == "%1%" SET CONF=_DEBUG && shift
if "-R" == "%1%" SET CONF=NDEBUG && shift
if "-DC" == "%1%" SET CONF=_DEBUGCLEAN && shift
if "-RC" == "%1%" SET CONF=NDEBUGCLEAN && shift
if "-DR" == "%1%" SET CONF=_DEBUGREBUILD && shift
if "-RR" == "%1%" SET CONF=NDEBUGREBUILD && shift
if "NOTHING" == "%CONF%" goto :usage

nmake -nologo -f Makefile.mak CONF=%CONF% %1%

goto nmake_el%errorlevel%
goto :nmake_end

:nmake_el0
echo === nmake abgearbeitet ==========================================
echo Kein Fehler - oder vielleicht doch? ;) 
echo bitte je nach Build __Release.log bzw. __Debug.log ÅberprÅfen!
goto :nmake_end

:nmake_el1
echo === nmake abgearbeitet ==========================================
echo Unvollst‰ndiger Build
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

:usage
echo Aufruf: MakeTRiAS -R [Target]
echo    fÅr Release - Build
echo Aufruf: MakeTRiAS -D [Target]
echo    fÅr Debug - Build
echo mîgliche Werte fÅr Target - siehe MAKEFILE.mak

:nmake_end
SET CONF=
