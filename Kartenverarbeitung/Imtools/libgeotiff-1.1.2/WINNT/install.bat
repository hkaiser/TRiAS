@ECHO OFF
REM
REM
REM This file copies makefiles, batch files, and source code patches to the
REM appropriate directories to build libtiff, libgeotiff, and the sample 
REM geotiff executables with either static linked version, console or
REM gui DLLs. 
REM
REM

if not exist ..\\libtiff goto wrongdir
if not exist ..\\libgeotiff goto wrongdir 

echo To get to this point, you must have read enough of 
echo the README.TXT file to put this distribution in the 
echo proper place.
echo.
echo.
echo.
echo The first thing I need to do is to copy the NT specific
echo makefiles to the proper directories.  Hit ctl-C to abort
echo.
pause

@echo on
copy Maketif.vc ..\\libtiff
copy Makegeo.vc ..\\libgeotiff
copy Makeexe.vc ..\\libgeotiff\\bin
@echo off

echo.
echo Now I am going to copy the NT batch files to the
echo proper directories.  Hit ctl-C to abort
echo.
pause

@echo on
copy mktifvc.bat ..\\libtiff
copy mkgeovc.bat ..\\libgeotiff
copy mkexevc.bat ..\\libgeotiff\\bin
@echo off


echo.
echo Now I am going to copy the DLL definition files to the
echo proper directories.  Hit ctl-C to abort
echo.
pause

@echo on
copy libctif.def ..\\libtiff
copy libgtif.def ..\\libtiff
copy libgeoc.def ..\\libgeotiff
copy libgeog.def ..\\libgeotiff
@echo off

echo.

if exist ..\\libtiff\\tif_win32.bak goto isthere

echo Now I am going to copy tif_win32.c to tif_win32.bak
echo and replace it with a file from the distribution.
echo Hit ctl-C to abort
echo.
pause

@echo on
copy ..\\libtiff\\tif_win32.c ..\\libtiff\\tif_win32.bak
copy tif_win32.c ..\\libtiff
@echo off

goto notthere

:isthere
echo I found a copy of tif_win32.bak already in the libtiff directory.
echo You need to make sure that libtiff\tif_win32.c corresponds to the 
echo one in the NT distribution and not the default tiff distribution
echo before trying to build.
echo.
pause

:notthere



echo.
echo Ok, we are done.
echo.
echo Now follow the instructions in the README2.TXT for building
echo the DLLS, libraries, and executables. (note: readme"2".txt)
echo.
echo Since most folks try to skip this step, I am scrolling 
echo it here for you. Press "space" to move forward each page
echo.
pause

type README2.TXT | more
pause
cls

echo Ok, If you need to refer back to that information, just
echo use notepad to view the file
echo.
pause


REM skip over error message.
goto done


REM errors, print out helpful message
:wrongdir
echo.
echo This installation seems to be in the wrong place.  I can't find
echo either ..\libtiff or ..\libgeotiff (or both).
echo.
echo Please move this installation directory to the proper place as
echo described in the README.TXT. Press "space" to move forward each page.
echo.
pause
type README.TXT | more
pause
cls

:done

