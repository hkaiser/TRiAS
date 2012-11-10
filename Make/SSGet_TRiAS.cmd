@echo off

SET T3LOGDIR=D:\MAKE\GET\LOG
SET VSS="D:\Program Files\Microsoft Visual Studio\Common\VSS\win32\SS.EXE"

rem set ssdir=\\Mercury\Sccs\TRiAS
rem set ssdir=D:\Sccs\TRiAS

set ssdir=%SCCS_SOURCE%
%VSS% GET $\*.* -GF -GTM -R -W+ -O%T3LOGDIR%\ssget_trias.log -Y%SSUSER%,%SSPASSWORD% %VSSLABEL%

rem %VSS% LABEL $ -L"%SCCS_LABEL%" -O%T3LOGDIR%\sslabel_trias.log -Y%SSUSER%,%SSPASSWORD%
rem xcopy /F D:\TRiASDev.MVC\Xtension\oleauto\DEBUG\Triastlb.tlb %TRIASTLB%
rem xcopy /F bsl.ini E:\TRiASDev.MVC\Bin\Bsl