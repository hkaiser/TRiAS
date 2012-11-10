@ECHO off
REM
REM
REM  Example Build sequence
REM
REM  "build" builds static, GUI and CONSOLE libs and DLLs, and builds the exe's
REM          with the static libraries
REM
REM  "build GUI" builds only the GUI libs, DLL, and links the exe's with them. 
REM
REM  "build CON" builds only the CON libs, DLL, and links the exe's with them. 
REM
REM
REM

echo.
echo You must have run install.bat before running this file.
echo If you did not, exit now with ctl-C and run install.
echo.
pause

if "%1"=="GUI" goto gui
if "%1"=="CON" goto console

REM else, build all and link with statics.
echo.
echo Building all libs and DLLs. Linking exe's with the static library.
echo Press ctl-C to cancel.
echo.
pause

cd ..\libtiff
call mktifvc.bat ALL

cd ..\libgeotiff
call mkgeovc.bat ALL

cd bin
call mkexevc.bat

goto done




:gui 
REM build GUI and link exes.
echo.
echo Building GUI libs and DLLs. Linking exe's with the GUI DLL.
echo Press ctl-C to cancel.
echo.
pause

cd ..\libtiff
call mktifvc.bat GUI

cd ..\libgeotiff
call mkgeovc.bat GUI

cd bin
call mkexevc.bat GUI
echo.
echo Remember to copy the DLLs to the bin directory, or in the path
echo before trying to run.
echo.

goto done



:console
REM build CON and link exes.
echo.
echo Building CON libs and DLLs. Linking exe's with the CON DLL.
echo Press ctl-C to cancel.
echo.
pause

cd ..\libtiff
call mktifvc.bat CON

cd ..\libgeotiff
call mkgeovc.bat CON

cd bin
call mkexevc.bat CON
echo.
echo Remember to copy the DLLs to the bin directory, or in the path
echo before trying to run.
echo.



:done

echo.
echo Done. Press any key to exit.
echo.

pause

