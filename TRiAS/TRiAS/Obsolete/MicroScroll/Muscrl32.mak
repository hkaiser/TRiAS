# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Muscrl32 - Win32 (80x86) Debug
!MESSAGE No configuration specified.  Defaulting to Muscrl32 - Win32 (80x86)\
 Debug.
!ENDIF 

!IF "$(CFG)" != "Muscrl32 - Win32 (80x86) Release" && "$(CFG)" !=\
 "Muscrl32 - Win32 (80x86) Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Muscrl32.mak" CFG="Muscrl32 - Win32 (80x86) Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Muscrl32 - Win32 (80x86) Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Muscrl32 - Win32 (80x86) Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Muscrl32 - Win32 (80x86) Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Muscrl32 - Win32 (80x86) Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "$(OUTDIR)\muscrl32.dll" "$(OUTDIR)\muscrl32.bsc"

CLEAN : 
	-@erase "$(INTDIR)\INIT.OBJ"
	-@erase "$(INTDIR)\INIT.SBR"
	-@erase "$(INTDIR)\MSAPI.OBJ"
	-@erase "$(INTDIR)\MSAPI.SBR"
	-@erase "$(INTDIR)\MUSCRL32.OBJ"
	-@erase "$(INTDIR)\MUSCRL32.res"
	-@erase "$(INTDIR)\MUSCRL32.SBR"
	-@erase "$(INTDIR)\PAINT.OBJ"
	-@erase "$(INTDIR)\PAINT.SBR"
	-@erase "$(OUTDIR)\muscrl32.bsc"
	-@erase "$(OUTDIR)\muscrl32.dll"
	-@erase ".\MUSCRL32.exp"
	-@erase ".\MUSCRL32.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "WIN32" /FR /YX"mscrdll.h" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D\
 "WIN32" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Muscrl32.pch" /YX"mscrdll.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\WinRel/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MUSCRL32.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BASE BSC32 /Iu
# ADD BSC32 /nologo
# SUBTRACT BSC32 /Iu
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Muscrl32.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\INIT.SBR" \
	"$(INTDIR)\MSAPI.SBR" \
	"$(INTDIR)\MUSCRL32.SBR" \
	"$(INTDIR)\PAINT.SBR"

"$(OUTDIR)\muscrl32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib mfc30.lib mfco30.lib mfcd30.lib mfcuia32.lib mfcans32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /implib:"MUSCRL32.lib"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Muscrl32.pdb" /machine:I386 /def:".\MUSCRL32.DEF"\
 /out:"$(OUTDIR)/Muscrl32.dll" /implib:"MUSCRL32.lib" 
DEF_FILE= \
	".\MUSCRL32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\INIT.OBJ" \
	"$(INTDIR)\MSAPI.OBJ" \
	"$(INTDIR)\MUSCRL32.OBJ" \
	"$(INTDIR)\MUSCRL32.res" \
	"$(INTDIR)\PAINT.OBJ"

"$(OUTDIR)\muscrl32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Muscrl32 - Win32 (80x86) Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "$(OUTDIR)\muscrl32.dll" "$(OUTDIR)\muscrl32.bsc"

CLEAN : 
	-@erase "$(INTDIR)\INIT.OBJ"
	-@erase "$(INTDIR)\INIT.SBR"
	-@erase "$(INTDIR)\MSAPI.OBJ"
	-@erase "$(INTDIR)\MSAPI.SBR"
	-@erase "$(INTDIR)\MUSCRL32.OBJ"
	-@erase "$(INTDIR)\MUSCRL32.res"
	-@erase "$(INTDIR)\MUSCRL32.SBR"
	-@erase "$(INTDIR)\PAINT.OBJ"
	-@erase "$(INTDIR)\PAINT.SBR"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\muscrl32.bsc"
	-@erase "$(OUTDIR)\muscrl32.dll"
	-@erase "$(OUTDIR)\Muscrl32.ilk"
	-@erase "$(OUTDIR)\Muscrl32.pdb"
	-@erase ".\MUSCRL32.exp"
	-@erase ".\MUSCRL32.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "WIN32" /FR /YX"mscrdll.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_WINDOWS" /D "_MBCS"\
 /D "WIN32" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Muscrl32.pch" /YX"mscrdll.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MUSCRL32.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# SUBTRACT BASE BSC32 /Iu
# ADD BSC32 /nologo
# SUBTRACT BSC32 /Iu
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Muscrl32.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\INIT.SBR" \
	"$(INTDIR)\MSAPI.SBR" \
	"$(INTDIR)\MUSCRL32.SBR" \
	"$(INTDIR)\PAINT.SBR"

"$(OUTDIR)\muscrl32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib mfc30d.lib mfco30d.lib mfcd30d.lib mfcuia32.lib mfcans32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /implib:"MUSCRL32.lib"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/Muscrl32.pdb" /debug /machine:I386 /def:".\MUSCRL32.DEF"\
 /out:"$(OUTDIR)/Muscrl32.dll" /implib:"MUSCRL32.lib" 
DEF_FILE= \
	".\MUSCRL32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\INIT.OBJ" \
	"$(INTDIR)\MSAPI.OBJ" \
	"$(INTDIR)\MUSCRL32.OBJ" \
	"$(INTDIR)\MUSCRL32.res" \
	"$(INTDIR)\PAINT.OBJ"

"$(OUTDIR)\muscrl32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Muscrl32 - Win32 (80x86) Release"
# Name "Muscrl32 - Win32 (80x86) Debug"

!IF  "$(CFG)" == "Muscrl32 - Win32 (80x86) Release"

!ELSEIF  "$(CFG)" == "Muscrl32 - Win32 (80x86) Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\MUSCRL32.C
DEP_CPP_MUSCR=\
	".\Mscrdll.h"\
	".\Muscrl32.h"\
	

"$(INTDIR)\MUSCRL32.OBJ" : $(SOURCE) $(DEP_CPP_MUSCR) "$(INTDIR)"

"$(INTDIR)\MUSCRL32.SBR" : $(SOURCE) $(DEP_CPP_MUSCR) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MUSCRL32.RC

"$(INTDIR)\MUSCRL32.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\INIT.C
DEP_CPP_INIT_=\
	".\Mscrdll.h"\
	".\Muscrl32.h"\
	

"$(INTDIR)\INIT.OBJ" : $(SOURCE) $(DEP_CPP_INIT_) "$(INTDIR)"

"$(INTDIR)\INIT.SBR" : $(SOURCE) $(DEP_CPP_INIT_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MSAPI.C
DEP_CPP_MSAPI=\
	".\Mscrdll.h"\
	".\Muscrl32.h"\
	

"$(INTDIR)\MSAPI.OBJ" : $(SOURCE) $(DEP_CPP_MSAPI) "$(INTDIR)"

"$(INTDIR)\MSAPI.SBR" : $(SOURCE) $(DEP_CPP_MSAPI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PAINT.C
DEP_CPP_PAINT=\
	".\Mscrdll.h"\
	".\Muscrl32.h"\
	

"$(INTDIR)\PAINT.OBJ" : $(SOURCE) $(DEP_CPP_PAINT) "$(INTDIR)"

"$(INTDIR)\PAINT.SBR" : $(SOURCE) $(DEP_CPP_PAINT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MUSCRL32.DEF

!IF  "$(CFG)" == "Muscrl32 - Win32 (80x86) Release"

!ELSEIF  "$(CFG)" == "Muscrl32 - Win32 (80x86) Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
