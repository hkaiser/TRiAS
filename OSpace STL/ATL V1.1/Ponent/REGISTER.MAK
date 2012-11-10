# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=register - Win32 DebugU
!MESSAGE No configuration specified.  Defaulting to register - Win32 DebugU.
!ENDIF 

!IF "$(CFG)" != "register - Win32 Release" && "$(CFG)" !=\
 "register - Win32 Debug" && "$(CFG)" != "register - Win32 DebugU" && "$(CFG)"\
 != "register - Win32 ReleaseU"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "REGISTER.MAK" CFG="register - Win32 DebugU"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "register - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "register - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "register - Win32 DebugU" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "register - Win32 ReleaseU" (based on\
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
# PROP Target_Last_Scanned "register - Win32 ReleaseU"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "register - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\REGISTER.dll" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\register.obj"
	-@erase "$(INTDIR)\REGISTER.pch"
	-@erase "$(INTDIR)\register.res"
	-@erase "$(INTDIR)\RegObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\REGISTER.dll"
	-@erase "$(OUTDIR)\REGISTER.exp"
	-@erase "$(OUTDIR)\REGISTER.lib"
	-@erase "$(OUTDIR)\REGISTER.map"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\register.h"
	-@erase ".\register.tlb"
	-@erase ".\register_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
# ADD BASE F90 /I "Release/"
# ADD F90 /I "Release/"
F90_OBJS=.\Release/
F90_PROJ=/I "Release/" /Fo"Release/" 

.for{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f90{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /O1 /D "NDEBUG" /D "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /O1 /D "NDEBUG" /D "_ATL_MIN_CRT" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_STATIC_REGISTRY"\
 /Fp"$(INTDIR)/REGISTER.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/register.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/REGISTER.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /entry:"DllMain" /subsystem:windows /dll /map /machine:I386
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /entry:"DllMain" /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/REGISTER.pdb" /map:"$(INTDIR)/REGISTER.map" /machine:I386\
 /def:".\register.def" /out:"$(OUTDIR)/REGISTER.dll"\
 /implib:"$(OUTDIR)/REGISTER.lib" 
DEF_FILE= \
	".\register.def"
LINK32_OBJS= \
	"$(INTDIR)\register.obj" \
	"$(INTDIR)\register.res" \
	"$(INTDIR)\RegObj.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\REGISTER.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# ADD BASE  /I "Release/"
# ADD  /I "Release/"
# Begin Custom Build - Registering OLE Server
OutDir=.\Release
TargetPath=.\Release\REGISTER.dll
InputPath=.\Release\REGISTER.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > $(OutDir)\regsvr32.trg

# End Custom Build

!ELSEIF  "$(CFG)" == "register - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\REGISTER.dll" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\register.obj"
	-@erase "$(INTDIR)\REGISTER.pch"
	-@erase "$(INTDIR)\register.res"
	-@erase "$(INTDIR)\RegObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\REGISTER.dll"
	-@erase "$(OUTDIR)\REGISTER.exp"
	-@erase "$(OUTDIR)\REGISTER.ilk"
	-@erase "$(OUTDIR)\REGISTER.lib"
	-@erase "$(OUTDIR)\REGISTER.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\register.h"
	-@erase ".\register.tlb"
	-@erase ".\register_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
# ADD BASE F90 /I "Debug/"
# ADD F90 /I "Debug/"
F90_OBJS=.\Debug/
F90_PROJ=/I "Release/" /Fo"Release/" 

.for{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f90{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)/REGISTER.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/register.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/REGISTER.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/REGISTER.pdb" /debug /machine:I386 /def:".\register.def"\
 /out:"$(OUTDIR)/REGISTER.dll" /implib:"$(OUTDIR)/REGISTER.lib" 
DEF_FILE= \
	".\register.def"
LINK32_OBJS= \
	"$(INTDIR)\register.obj" \
	"$(INTDIR)\register.res" \
	"$(INTDIR)\RegObj.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\REGISTER.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# ADD BASE  /I "Debug/"
# ADD  /I "Debug/"
# Begin Custom Build - Registering OLE Server
OutDir=.\Debug
TargetPath=.\Debug\REGISTER.dll
InputPath=.\Debug\REGISTER.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > $(OutDir)\regsvr32.trg

# End Custom Build

!ELSEIF  "$(CFG)" == "register - Win32 DebugU"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "register"
# PROP BASE Intermediate_Dir "register"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Target_Dir ""
OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\REGISTER.dll" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\register.obj"
	-@erase "$(INTDIR)\REGISTER.pch"
	-@erase "$(INTDIR)\register.res"
	-@erase "$(INTDIR)\RegObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\REGISTER.dll"
	-@erase "$(OUTDIR)\REGISTER.exp"
	-@erase "$(OUTDIR)\REGISTER.ilk"
	-@erase "$(OUTDIR)\REGISTER.lib"
	-@erase "$(OUTDIR)\REGISTER.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\register.h"
	-@erase ".\register.tlb"
	-@erase ".\register_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
# ADD BASE F90 /I "register/"
# ADD F90 /I "DebugU/"
F90_OBJS=.\DebugU/
F90_PROJ=/I "Release/" /Fo"Release/" 

.for{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f90{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_STATIC_REGISTRY"\
 /Fp"$(INTDIR)/REGISTER.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/register.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/REGISTER.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/REGISTER.pdb" /debug /machine:I386 /def:".\register.def"\
 /out:"$(OUTDIR)/REGISTER.dll" /implib:"$(OUTDIR)/REGISTER.lib" 
DEF_FILE= \
	".\register.def"
LINK32_OBJS= \
	"$(INTDIR)\register.obj" \
	"$(INTDIR)\register.res" \
	"$(INTDIR)\RegObj.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\REGISTER.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# ADD BASE  /I "register/"
# ADD  /I "DebugU/"
# Begin Custom Build - Registering OLE Server
OutDir=.\DebugU
TargetPath=.\DebugU\REGISTER.dll
InputPath=.\DebugU\REGISTER.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > $(OutDir)\regsvr32.trg

# End Custom Build

!ELSEIF  "$(CFG)" == "register - Win32 ReleaseU"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "registe0"
# PROP BASE Intermediate_Dir "registe0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Target_Dir ""
OUTDIR=.\ReleaseU
INTDIR=.\ReleaseU
# Begin Custom Macros
OutDir=.\ReleaseU
# End Custom Macros

ALL : "$(OUTDIR)\REGISTER.dll" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\register.obj"
	-@erase "$(INTDIR)\REGISTER.pch"
	-@erase "$(INTDIR)\register.res"
	-@erase "$(INTDIR)\RegObj.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\REGISTER.dll"
	-@erase "$(OUTDIR)\REGISTER.exp"
	-@erase "$(OUTDIR)\REGISTER.lib"
	-@erase "$(OUTDIR)\REGISTER.map"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\register.h"
	-@erase ".\register.tlb"
	-@erase ".\register_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
# ADD BASE F90 /I "registe0/"
# ADD F90 /I "ReleaseU/"
F90_OBJS=.\ReleaseU/
F90_PROJ=/I "Release/" /Fo"Release/" 

.for{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

.f90{$(F90_OBJS)}.obj:
   $(F90) $(F90_PROJ) $<  

# ADD BASE CPP /nologo /MT /W3 /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_ATL_MINCRT" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /O1 /D "_UNICODE" /D "NDEBUG" /D "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /O1 /D "_UNICODE" /D "NDEBUG" /D "_ATL_MIN_CRT" /D\
 "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_STATIC_REGISTRY"\
 /Fp"$(INTDIR)/REGISTER.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/register.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/REGISTER.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /entry:"DllMain" /subsystem:windows /dll /map /machine:I386
# SUBTRACT BASE LINK32 /verbose /pdb:none
# ADD LINK32 /nologo /entry:"DllMain" /subsystem:windows /dll /map /machine:I386
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=/nologo /entry:"DllMain" /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/REGISTER.pdb" /map:"$(INTDIR)/REGISTER.map" /machine:I386\
 /def:".\register.def" /out:"$(OUTDIR)/REGISTER.dll"\
 /implib:"$(OUTDIR)/REGISTER.lib" 
DEF_FILE= \
	".\register.def"
LINK32_OBJS= \
	"$(INTDIR)\register.obj" \
	"$(INTDIR)\register.res" \
	"$(INTDIR)\RegObj.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\REGISTER.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# ADD BASE  /I "registe0/"
# ADD  /I "ReleaseU/"
# Begin Custom Build - Registering OLE Server
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\REGISTER.dll
InputPath=.\ReleaseU\REGISTER.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > $(OutDir)\regsvr32.trg

# End Custom Build

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

# Name "register - Win32 Release"
# Name "register - Win32 Debug"
# Name "register - Win32 DebugU"
# Name "register - Win32 ReleaseU"

!IF  "$(CFG)" == "register - Win32 Release"

!ELSEIF  "$(CFG)" == "register - Win32 Debug"

!ELSEIF  "$(CFG)" == "register - Win32 DebugU"

!ELSEIF  "$(CFG)" == "register - Win32 ReleaseU"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\static\statreg.cpp"\
	".\static\statreg.h"\
	".\stdafx.h"\
	{$(INCLUDE)}"\atlimpl.cpp"\
	

!IF  "$(CFG)" == "register - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /O1 /D "NDEBUG" /D "_ATL_MIN_CRT" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_STATIC_REGISTRY"\
 /Fp"$(INTDIR)/REGISTER.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\REGISTER.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "register - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)/REGISTER.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\REGISTER.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "register - Win32 DebugU"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_STATIC_REGISTRY"\
 /Fp"$(INTDIR)/REGISTER.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\REGISTER.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "register - Win32 ReleaseU"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /O1 /D "_UNICODE" /D "NDEBUG" /D "_ATL_MIN_CRT" /D\
 "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_ATL_STATIC_REGISTRY"\
 /Fp"$(INTDIR)/REGISTER.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\REGISTER.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\register.cpp
DEP_CPP_REGIS=\
	".\register.h"\
	".\register_i.c"\
	".\regobj.h"\
	".\static\statreg.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "register - Win32 Release"


"$(INTDIR)\register.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\REGISTER.pch" ".\register.h" ".\register_i.c"


!ELSEIF  "$(CFG)" == "register - Win32 Debug"


"$(INTDIR)\register.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\REGISTER.pch" ".\register.h" ".\register_i.c"


!ELSEIF  "$(CFG)" == "register - Win32 DebugU"


"$(INTDIR)\register.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\REGISTER.pch" ".\register.h" ".\register_i.c"


!ELSEIF  "$(CFG)" == "register - Win32 ReleaseU"


"$(INTDIR)\register.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\REGISTER.pch" ".\register.h" ".\register_i.c"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\register.def

!IF  "$(CFG)" == "register - Win32 Release"

!ELSEIF  "$(CFG)" == "register - Win32 Debug"

!ELSEIF  "$(CFG)" == "register - Win32 DebugU"

!ELSEIF  "$(CFG)" == "register - Win32 ReleaseU"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\register.rc
DEP_RSC_REGIST=\
	".\register.reg"\
	".\register.tlb"\
	

!IF  "$(CFG)" == "register - Win32 Release"


"$(INTDIR)\register.res" : $(SOURCE) $(DEP_RSC_REGIST) "$(INTDIR)"\
 ".\register.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "register - Win32 Debug"


"$(INTDIR)\register.res" : $(SOURCE) $(DEP_RSC_REGIST) "$(INTDIR)"\
 ".\register.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "register - Win32 DebugU"


"$(INTDIR)\register.res" : $(SOURCE) $(DEP_RSC_REGIST) "$(INTDIR)"\
 ".\register.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "register - Win32 ReleaseU"


"$(INTDIR)\register.res" : $(SOURCE) $(DEP_RSC_REGIST) "$(INTDIR)"\
 ".\register.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\register.idl

!IF  "$(CFG)" == "register - Win32 Release"

# Begin Custom Build - Running MIDL
InputPath=.\register.idl

BuildCmds= \
	midl /old register.idl \
	

"register.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"register.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"register_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "register - Win32 Debug"

# Begin Custom Build - Running MIDL
InputPath=.\register.idl

BuildCmds= \
	midl /old register.idl \
	

"register.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"register.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"register_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "register - Win32 DebugU"

# Begin Custom Build - Running MIDL
InputPath=.\register.idl

BuildCmds= \
	midl /old register.idl \
	

"register.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"register.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"register_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "register - Win32 ReleaseU"

# Begin Custom Build - Running MIDL
InputPath=.\register.idl

BuildCmds= \
	midl /old register.idl \
	

"register.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"register.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"register_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RegObj.cpp
DEP_CPP_REGOB=\
	".\register.h"\
	".\regobj.h"\
	".\static\statreg.h"\
	".\stdafx.h"\
	

!IF  "$(CFG)" == "register - Win32 Release"


"$(INTDIR)\RegObj.obj" : $(SOURCE) $(DEP_CPP_REGOB) "$(INTDIR)"\
 "$(INTDIR)\REGISTER.pch" ".\register.h"


!ELSEIF  "$(CFG)" == "register - Win32 Debug"


"$(INTDIR)\RegObj.obj" : $(SOURCE) $(DEP_CPP_REGOB) "$(INTDIR)"\
 "$(INTDIR)\REGISTER.pch" ".\register.h"


!ELSEIF  "$(CFG)" == "register - Win32 DebugU"


"$(INTDIR)\RegObj.obj" : $(SOURCE) $(DEP_CPP_REGOB) "$(INTDIR)"\
 "$(INTDIR)\REGISTER.pch" ".\register.h"


!ELSEIF  "$(CFG)" == "register - Win32 ReleaseU"


"$(INTDIR)\RegObj.obj" : $(SOURCE) $(DEP_CPP_REGOB) "$(INTDIR)"\
 "$(INTDIR)\REGISTER.pch" ".\register.h"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
