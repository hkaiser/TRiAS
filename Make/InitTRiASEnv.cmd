@echo off
echo Setting TRiAS build environment variables ...
rem
cmd /c setx TRIASDEV_BASE "D:\TRiASDev.MVC"
cmd /c setx TRIAS_LANGUAGE "0x0407"
rem
cmd /c setx TRIASINCLUDE "%%TRIASDEV_BASE%%\Include"
cmd /c setx TRIASLIB "%%TRIASDEV_BASE%%\Lib"
cmd /c setx TRIASTLB "%%TRIASDEV_BASE%%\Include\Tlb"
cmd /c setx TRIASDOC "%%TRIASDEV_BASE%%\Include\Help"
cmd /c setx YXX "%%TRIASDEV_BASE%%\Framewrk\Lol"
rem
cmd /c setx TRIASDIR_D "D:\TRiAS\TRiASDEB\V_4_0_0\%%TRIAS_LANGUAGE%%"
cmd /c setx TRIASDIR_R "D:\TRiAS\TRiAS\V_4_0_0\%%TRIAS_LANGUAGE%%"
rem
cmd /c setx VCPP "D:\VCPP"
