@echo off
@echo Binding binaries ...

SET LANG=NOTHING
if "ENU" == "%1%" SET LANG=0x0409
if "GER" == "%1%" SET LANG=0x0407
if "NOTHING" == "%LANG%" goto :usage

echo .
echo SPRACHVERSION    : %LANG%
echo .

if exist trias32.bas del trias32.bas > nul
"C:\Programme\Microsoft SDK\bin\rebase.exe" -v -d -a -p -x ..\v_4_0_0\%LANG% -u ..\v_4_0_0\%LANG% -b 68000000 -C trias32.bas -R D:\TRiAS\TRiAS\v_4_0_0\%LANG% -G trias32.fil -G coords.fil -O exports.fil -O import.fil -O mapmgr.fil -N Leave.fil
rem xcopy /F ..\v_4_0_0\%LANG%\*.dbg ..\v_4_0_0\%LANG%.dbg

goto :end_of_script

:usage
echo Aufruf: TRiASBase LANGUAGE
echo         wobei Language [ENU,GER] sein kann.

:end_of_script
