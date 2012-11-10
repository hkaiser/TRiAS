@echo Release build ...
set CL=/D_TRiAS_VER=%TRiAS_VER%
call "D:\Program Files\Microsoft Visual Studio\VC98\Bin\vcvars32.bat"
nmake -i -a -nologo -f Makefile.mak CONF=NDEBUG TRiAS_VER=%TRiAS_VER% TRiAS > Release.log
