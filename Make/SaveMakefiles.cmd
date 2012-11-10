@echo off
rem
rem Makefiles aus den Projektverzeichnisse zusammenstellen
rem 
xcopy /Q D:\TRiASDev.MVC\Makefile.ma* D:\Make\Makefiles\TRiASDev.MVC /s
xcopy /Q D:\VCPP\Makefile.ma* D:\Make\Makefiles\VCPP /s
xcopy /Q D:\Toolkit\Makefile.ma* D:\Make\Makefiles\Toolkit /s
