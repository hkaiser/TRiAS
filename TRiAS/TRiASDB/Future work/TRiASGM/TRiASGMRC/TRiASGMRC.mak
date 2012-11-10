# Microsoft Developer Studio Generated NMAKE File, Based on TRiASGMRC.dsp
!IF "$(CFG)" == ""
CFG=TRiASGMRC - Win32 Release
!MESSAGE No configuration specified. Defaulting to TRiASGMRC - Win32\
 Release.
!ENDIF 

!IF "$(CFG)" != "TRiASGMRC - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRiASGMRC.mak" CFG="TRiASGMRC - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRiASGMRC - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : "..\bin\resdlls\0009\TRiASGM1.drx"

!ELSE 

ALL : "..\bin\resdlls\0009\TRiASGM1.drx"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\TRiASGM1.res"
	-@erase "$(OUTDIR)\TRiASGM1.exp"
	-@erase "$(OUTDIR)\TRiASGM1.lib"
	-@erase "..\bin\resdlls\0009\TRiASGM1.drx"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TRiASGMRC.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\TRiASGM1.pdb" /machine:I386\
 /out:"..\bin\resdlls\0009\TRiASGM1.drx"\
 /implib:"$(OUTDIR)\TRiASGM1.lib" /NOENTRY 
LINK32_OBJS= \
	"$(INTDIR)\TRiASGM1.res"

"..\bin\resdlls\0009\TRiASGM1.drx" : "$(OUTDIR)" $(DEF_FILE)\
 $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\TRiASGMRC.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TRiASGM1.res" /d "NDEBUG" 

!IF "$(CFG)" == "TRiASGMRC - Win32 Release"
SOURCE=..\include\TRiASGM.rc

"$(INTDIR)\TRiASGM1.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\TRiASGM1.res" /i\
 "\Implementation\TRiASGM\include" /d "NDEBUG" $(SOURCE)



!ENDIF 

