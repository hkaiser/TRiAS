@echo off

SET T3LOGDIR=H:\MAKE\GET\LOG
SET T3VSS="C:\Programme\Microsoft Visual Studio\Common\VSS\win32\SS.EXE"

set ssdir=\\SpaceShuttle\Sccs\LOCALE
%T3VSS% GET $\Sprachversionen\Englisch\*.* -I-Y -GF -GTM -R -W+ -O%T3LOGDIR%\ssget_english.log

