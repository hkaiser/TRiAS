@echo off

SET T3LOGDIR=D:\MAKE\GET\LOG
SET T3VSS="C:\Programme\Microsoft Visual Studio\Common\VSS\win32\SS.EXE"

set ssdir=\\SpaceShuttle\Sccs\TRiASDB
%T3VSS% GET $\*.* -GF -GTM -R -W+ -O%T3LOGDIR%\ssget_triasdb.log
