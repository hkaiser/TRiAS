
# Microsoft Developer Studio Generated NMAKE File, Based on dcomperm.dsp
!IF "$(CFG)" == ""
CFG=dcomperm - Win64 Debug
!MESSAGE No configuration specified. Defaulting to dcomperm - Win64 Debug.
!ENDIF 

!IF "$(CFG)" != "dcomperm - Win64 Release" && "$(CFG)" != "dcomperm - Win64 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dcomperm64.mak" CFG="dcomperm - Win64 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dcomperm - Win64 Release" (based on "Win64 (IA64) Console Application")
!MESSAGE "dcomperm - Win64 Debug" (based on "Win64 (IA64) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dcomperm - Win64 Release"

OUTDIR=.\Release\IA64
INTDIR=.\Release\IA64
# Begin Custom Macros
OutDir=.\Release\IA64
# End Custom Macros

ALL : "$(OUTDIR)\dcomperm.exe"


CLEAN :
	-@erase "$(INTDIR)\ACLMGMT.OBJ"
	-@erase "$(INTDIR)\DCOMPERM.OBJ"
	-@erase "$(INTDIR)\LISTACL.OBJ"
	-@erase "$(INTDIR)\SDMGMT.OBJ"
	-@erase "$(INTDIR)\SRVCMGMT.OBJ"
	-@erase "$(INTDIR)\UTILS.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WRAPPERS.OBJ"
	-@erase "$(OUTDIR)\dcomperm.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /Wp64 /GX /O2 /D "NDEBUG" /D "WIN64" /D "WIN32"  /D "_CONSOLE" /D "_MBCS" /D "_WIN32_DCOM" /Fp"$(INTDIR)\dcomperm.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dcomperm.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\dcomperm.pdb" /machine:IA64 /out:"$(OUTDIR)\dcomperm.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ACLMGMT.OBJ" \
	"$(INTDIR)\DCOMPERM.OBJ" \
	"$(INTDIR)\LISTACL.OBJ" \
	"$(INTDIR)\SDMGMT.OBJ" \
	"$(INTDIR)\SRVCMGMT.OBJ" \
	"$(INTDIR)\UTILS.OBJ" \
	"$(INTDIR)\WRAPPERS.OBJ"

"$(OUTDIR)\dcomperm.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "dcomperm - Win64 Debug"

OUTDIR=.\Debug\IA64
INTDIR=.\Debug\IA64
# Begin Custom Macros
OutDir=.\Debug\IA64
# End Custom Macros

ALL : "$(OUTDIR)\dcomperm.exe"


CLEAN :
	-@erase "$(INTDIR)\ACLMGMT.OBJ"
	-@erase "$(INTDIR)\DCOMPERM.OBJ"
	-@erase "$(INTDIR)\LISTACL.OBJ"
	-@erase "$(INTDIR)\SDMGMT.OBJ"
	-@erase "$(INTDIR)\SRVCMGMT.OBJ"
	-@erase "$(INTDIR)\UTILS.OBJ"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WRAPPERS.OBJ"
	-@erase "$(OUTDIR)\dcomperm.exe"
	-@erase "$(OUTDIR)\dcomperm.ilk"
	-@erase "$(OUTDIR)\dcomperm.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Wp64 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN64" /D "WIN32"  /D "_CONSOLE" /D "_MBCS" /D "_WIN32_DCOM" /Fp"$(INTDIR)\dcomperm.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"   /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dcomperm.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib atl21asm.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\dcomperm.pdb" /debug /machine:IA64 /out:"$(OUTDIR)\dcomperm.exe"  
LINK32_OBJS= \
	"$(INTDIR)\ACLMGMT.OBJ" \
	"$(INTDIR)\DCOMPERM.OBJ" \
	"$(INTDIR)\LISTACL.OBJ" \
	"$(INTDIR)\SDMGMT.OBJ" \
	"$(INTDIR)\SRVCMGMT.OBJ" \
	"$(INTDIR)\UTILS.OBJ" \
	"$(INTDIR)\WRAPPERS.OBJ"

"$(OUTDIR)\dcomperm.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("dcomperm.dep")
!INCLUDE "dcomperm.dep"
!ELSE 
!MESSAGE Warning: cannot find "dcomperm.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "dcomperm - Win64 Release" || "$(CFG)" == "dcomperm - Win64 Debug"
SOURCE=.\ACLMGMT.CPP

"$(INTDIR)\ACLMGMT.OBJ" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DCOMPERM.CPP

"$(INTDIR)\DCOMPERM.OBJ" : $(SOURCE) "$(INTDIR)"


SOURCE=.\LISTACL.CPP

"$(INTDIR)\LISTACL.OBJ" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SDMGMT.CPP

"$(INTDIR)\SDMGMT.OBJ" : $(SOURCE) "$(INTDIR)"


SOURCE=.\SRVCMGMT.CPP

"$(INTDIR)\SRVCMGMT.OBJ" : $(SOURCE) "$(INTDIR)"


SOURCE=.\UTILS.CPP

"$(INTDIR)\UTILS.OBJ" : $(SOURCE) "$(INTDIR)"


SOURCE=.\WRAPPERS.CPP

"$(INTDIR)\WRAPPERS.OBJ" : $(SOURCE) "$(INTDIR)"



!ENDIF 
