@echo off
rem Kopieren diverser Dateien, welche fÅr Bootstrapping der BasicScripte 
rem benîtigt werden

SET LANG=NOTHING
if "ENU" == "%1%" SET LANG=0x0409
if "GER" == "%1%" SET LANG=0x0407
if "NOTHING" == "%LANG%" goto :usage

set quelle="d:\trias\triasdeb\v_4_0_0\%LANG%"
set target="d:\trias\triasdeb\v_4_0_0\Target"

echo SPRACHVERSION    : %LANG%
echo QUELLVERZEICHNIS : %quelle%

xcopy %quelle%\bscriptd.ext %target%
xcopy %quelle%\containd.dll %target%
xcopy %quelle%\oleautod.ext %target%
xcopy %quelle%\ospace5d.dll %target%
xcopy %quelle%\sumncm22.dll %target%
xcopy %quelle%\sumncx22.dll %target%
xcopy %quelle%\sumndc22.dll %target%
xcopy %quelle%\sumndd22.dll %target%
xcopy %quelle%\sumndg22.dll %target%
xcopy %quelle%\sumnol22.dll %target%
xcopy %quelle%\sumnpb22.dll %target%
xcopy %quelle%\sumnrn22.dll %target%
xcopy %quelle%\triasdmd.dll %target%
xcopy %quelle%\daolayed.ebn %target%

goto :end_of_script

:usage
echo Aufruf: TRiASCopy LANGUAGE
echo         wobei Language [ENU,GER] sein kann.

:end_of_script

set quelle=
set target=
