# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Raumzugriff - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Raumzugriff - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Raumzugriff - Win32 Release" && "$(CFG)" !=\
 "Raumzugriff - Win32 Debug" && "$(CFG)" !=\
 "Raumzugriff - Win32 Unicode Release" && "$(CFG)" !=\
 "Raumzugriff - Win32 Unicode Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Raumzugriff.mak" CFG="Raumzugriff - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Raumzugriff - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Raumzugriff - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Raumzugriff - Win32 Unicode Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Raumzugriff - Win32 Unicode Debug" (based on\
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
# PROP Target_Last_Scanned "Raumzugriff - Win32 Release"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Raumzugriff - Win32 Release"

# PROP BASE Use_MFC 1
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

ALL : "$(OUTDIR)\Raumzugriff.dll" "$(OUTDIR)\Raumzugriff.bsc"\
 "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\EnumUnknown.obj"
	-@erase "$(INTDIR)\EnumUnknown.sbr"
	-@erase "$(INTDIR)\Hilfsfunktionen.obj"
	-@erase "$(INTDIR)\Hilfsfunktionen.sbr"
	-@erase "$(INTDIR)\objdispatch.obj"
	-@erase "$(INTDIR)\objdispatch.sbr"
	-@erase "$(INTDIR)\Raumzugriff.obj"
	-@erase "$(INTDIR)\Raumzugriff.pch"
	-@erase "$(INTDIR)\Raumzugriff.res"
	-@erase "$(INTDIR)\Raumzugriff.sbr"
	-@erase "$(INTDIR)\SpatialTree.obj"
	-@erase "$(INTDIR)\SpatialTree.sbr"
	-@erase "$(INTDIR)\SpatialTreeQuery.obj"
	-@erase "$(INTDIR)\SpatialTreeQuery.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\testobjekt.obj"
	-@erase "$(INTDIR)\testobjekt.sbr"
	-@erase "$(OUTDIR)\Raumzugriff.bsc"
	-@erase "$(OUTDIR)\Raumzugriff.dll"
	-@erase "$(OUTDIR)\Raumzugriff.exp"
	-@erase "$(OUTDIR)\Raumzugriff.lib"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\Raumzugriff.h"
	-@erase ".\Raumzugriff.tlb"
	-@erase ".\Raumzugriff_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_ALLOCATORS" /D "_ATL_NEW_CCOMSTRUCT" /D "QI_EXCEPTION" /D "_WINDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_USRDLL" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_ALLOCATORS" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "QI_EXCEPTION" /D "_WINDLL" /D "_MBCS" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Raumzugriff.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Raumzugriff.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Raumzugriff.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\EnumUnknown.sbr" \
	"$(INTDIR)\Hilfsfunktionen.sbr" \
	"$(INTDIR)\objdispatch.sbr" \
	"$(INTDIR)\Raumzugriff.sbr" \
	"$(INTDIR)\SpatialTree.sbr" \
	"$(INTDIR)\SpatialTreeQuery.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\testobjekt.sbr"

"$(OUTDIR)\Raumzugriff.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 f:\toolkit\ospace\ospace\debug\ospace2d.lib /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT LINK32 /incremental:yes
LINK32_FLAGS=f:\toolkit\ospace\ospace\debug\ospace2d.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)/Raumzugriff.pdb"\
 /machine:I386 /def:".\Raumzugriff.def" /out:"$(OUTDIR)/Raumzugriff.dll"\
 /implib:"$(OUTDIR)/Raumzugriff.lib" 
DEF_FILE= \
	".\Raumzugriff.def"
LINK32_OBJS= \
	"$(INTDIR)\EnumUnknown.obj" \
	"$(INTDIR)\Hilfsfunktionen.obj" \
	"$(INTDIR)\objdispatch.obj" \
	"$(INTDIR)\Raumzugriff.obj" \
	"$(INTDIR)\Raumzugriff.res" \
	"$(INTDIR)\SpatialTree.obj" \
	"$(INTDIR)\SpatialTreeQuery.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\testobjekt.obj"

"$(OUTDIR)\Raumzugriff.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\Release
TargetPath=.\Release\Raumzugriff.dll
InputPath=.\Release\Raumzugriff.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Debug"

# PROP BASE Use_MFC 1
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

ALL : "$(OUTDIR)\Raumzugriff.dll" "$(OUTDIR)\Raumzugriff.bsc"

CLEAN : 
	-@erase "$(INTDIR)\EnumUnknown.obj"
	-@erase "$(INTDIR)\EnumUnknown.sbr"
	-@erase "$(INTDIR)\Hilfsfunktionen.obj"
	-@erase "$(INTDIR)\Hilfsfunktionen.sbr"
	-@erase "$(INTDIR)\objdispatch.obj"
	-@erase "$(INTDIR)\objdispatch.sbr"
	-@erase "$(INTDIR)\Raumzugriff.obj"
	-@erase "$(INTDIR)\Raumzugriff.pch"
	-@erase "$(INTDIR)\Raumzugriff.res"
	-@erase "$(INTDIR)\Raumzugriff.sbr"
	-@erase "$(INTDIR)\SpatialTree.obj"
	-@erase "$(INTDIR)\SpatialTree.sbr"
	-@erase "$(INTDIR)\SpatialTreeQuery.obj"
	-@erase "$(INTDIR)\SpatialTreeQuery.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\testobjekt.obj"
	-@erase "$(INTDIR)\testobjekt.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Raumzugriff.bsc"
	-@erase "$(OUTDIR)\Raumzugriff.dll"
	-@erase "$(OUTDIR)\Raumzugriff.exp"
	-@erase "$(OUTDIR)\Raumzugriff.ilk"
	-@erase "$(OUTDIR)\Raumzugriff.lib"
	-@erase "$(OUTDIR)\Raumzugriff.pdb"
	-@erase ".\Raumzugriff.h"
	-@erase ".\Raumzugriff.tlb"
	-@erase ".\Raumzugriff_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_ALLOCATORS" /D "_ATL_NEW_CCOMSTRUCT" /D "QI_EXCEPTION" /D "_WINDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_USRDLL" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_ALLOCATORS" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "QI_EXCEPTION" /D "_WINDLL" /D "_MBCS" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Raumzugriff.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Raumzugriff.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Raumzugriff.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\EnumUnknown.sbr" \
	"$(INTDIR)\Hilfsfunktionen.sbr" \
	"$(INTDIR)\objdispatch.sbr" \
	"$(INTDIR)\Raumzugriff.sbr" \
	"$(INTDIR)\SpatialTree.sbr" \
	"$(INTDIR)\SpatialTreeQuery.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\testobjekt.sbr"

"$(OUTDIR)\Raumzugriff.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 f:\toolkit\ospace\ospace\debug\ospace2d.lib /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=f:\toolkit\ospace\ospace\debug\ospace2d.lib /nologo\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/Raumzugriff.pdb"\
 /debug /machine:I386 /def:".\Raumzugriff.def" /out:"$(OUTDIR)/Raumzugriff.dll"\
 /implib:"$(OUTDIR)/Raumzugriff.lib" 
DEF_FILE= \
	".\Raumzugriff.def"
LINK32_OBJS= \
	"$(INTDIR)\EnumUnknown.obj" \
	"$(INTDIR)\Hilfsfunktionen.obj" \
	"$(INTDIR)\objdispatch.obj" \
	"$(INTDIR)\Raumzugriff.obj" \
	"$(INTDIR)\Raumzugriff.res" \
	"$(INTDIR)\SpatialTree.obj" \
	"$(INTDIR)\SpatialTreeQuery.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\testobjekt.obj"

"$(OUTDIR)\Raumzugriff.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\Raumzugriff.dll
InputPath=.\Debug\Raumzugriff.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Unicode Release"
# PROP BASE Intermediate_Dir "Unicode Release"
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

ALL : "$(OUTDIR)\Raumzugriff.dll" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\EnumUnknown.obj"
	-@erase "$(INTDIR)\Hilfsfunktionen.obj"
	-@erase "$(INTDIR)\objdispatch.obj"
	-@erase "$(INTDIR)\Raumzugriff.obj"
	-@erase "$(INTDIR)\Raumzugriff.pch"
	-@erase "$(INTDIR)\Raumzugriff.res"
	-@erase "$(INTDIR)\SpatialTree.obj"
	-@erase "$(INTDIR)\SpatialTreeQuery.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\testobjekt.obj"
	-@erase "$(OUTDIR)\Raumzugriff.dll"
	-@erase "$(OUTDIR)\Raumzugriff.exp"
	-@erase "$(OUTDIR)\Raumzugriff.lib"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\Raumzugriff.h"
	-@erase ".\Raumzugriff.tlb"
	-@erase ".\Raumzugriff_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "_UNICODE" /D "IN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "OS_WIN95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMESOS_NO_ALLOCATOR" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "_UNICODE" /D "IN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "OS_WIN95" /D\
 "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMESOS_NO_ALLOCATOR" /Fp"$(INTDIR)/Raumzugriff.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\ReleaseU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Raumzugriff.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Raumzugriff.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/Raumzugriff.pdb" /machine:I386 /def:".\Raumzugriff.def"\
 /out:"$(OUTDIR)/Raumzugriff.dll" /implib:"$(OUTDIR)/Raumzugriff.lib" 
DEF_FILE= \
	".\Raumzugriff.def"
LINK32_OBJS= \
	"$(INTDIR)\EnumUnknown.obj" \
	"$(INTDIR)\Hilfsfunktionen.obj" \
	"$(INTDIR)\objdispatch.obj" \
	"$(INTDIR)\Raumzugriff.obj" \
	"$(INTDIR)\Raumzugriff.res" \
	"$(INTDIR)\SpatialTree.obj" \
	"$(INTDIR)\SpatialTreeQuery.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\testobjekt.obj"

"$(OUTDIR)\Raumzugriff.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\Raumzugriff.dll
InputPath=.\ReleaseU\Raumzugriff.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

# End Custom Build

!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Unicode Debug"
# PROP BASE Intermediate_Dir "Unicode Debug"
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

ALL : "$(OUTDIR)\Raumzugriff.dll" "$(OUTDIR)\regsvr32.trg"

CLEAN : 
	-@erase "$(INTDIR)\EnumUnknown.obj"
	-@erase "$(INTDIR)\Hilfsfunktionen.obj"
	-@erase "$(INTDIR)\objdispatch.obj"
	-@erase "$(INTDIR)\Raumzugriff.obj"
	-@erase "$(INTDIR)\Raumzugriff.pch"
	-@erase "$(INTDIR)\Raumzugriff.res"
	-@erase "$(INTDIR)\SpatialTree.obj"
	-@erase "$(INTDIR)\SpatialTreeQuery.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\testobjekt.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Raumzugriff.dll"
	-@erase "$(OUTDIR)\Raumzugriff.exp"
	-@erase "$(OUTDIR)\Raumzugriff.ilk"
	-@erase "$(OUTDIR)\Raumzugriff.lib"
	-@erase "$(OUTDIR)\Raumzugriff.pdb"
	-@erase "$(OUTDIR)\regsvr32.trg"
	-@erase ".\Raumzugriff.h"
	-@erase ".\Raumzugriff.tlb"
	-@erase ".\Raumzugriff_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "IN32" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "OS_WIN95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMESOS_NO_ALLOCATOR" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "IN32"\
 /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "OS_WIN95" /D\
 "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMESOS_NO_ALLOCATOR" /Fp"$(INTDIR)/Raumzugriff.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\DebugU/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Raumzugriff.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Raumzugriff.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/Raumzugriff.pdb" /debug /machine:I386 /def:".\Raumzugriff.def"\
 /out:"$(OUTDIR)/Raumzugriff.dll" /implib:"$(OUTDIR)/Raumzugriff.lib" 
DEF_FILE= \
	".\Raumzugriff.def"
LINK32_OBJS= \
	"$(INTDIR)\EnumUnknown.obj" \
	"$(INTDIR)\Hilfsfunktionen.obj" \
	"$(INTDIR)\objdispatch.obj" \
	"$(INTDIR)\Raumzugriff.obj" \
	"$(INTDIR)\Raumzugriff.res" \
	"$(INTDIR)\SpatialTree.obj" \
	"$(INTDIR)\SpatialTreeQuery.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\testobjekt.obj"

"$(OUTDIR)\Raumzugriff.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
OutDir=.\DebugU
TargetPath=.\DebugU\Raumzugriff.dll
InputPath=.\DebugU\Raumzugriff.dll
SOURCE=$(InputPath)

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   regsvr32 /s /c "$(TargetPath)"
   echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg"

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

# Name "Raumzugriff - Win32 Release"
# Name "Raumzugriff - Win32 Debug"
# Name "Raumzugriff - Win32 Unicode Release"
# Name "Raumzugriff - Win32 Unicode Debug"

!IF  "$(CFG)" == "Raumzugriff - Win32 Release"

!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Debug"

!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Atlimpl.cpp"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

!IF  "$(CFG)" == "Raumzugriff - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_USRDLL" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_ALLOCATORS" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "QI_EXCEPTION" /D "_WINDLL" /D "_MBCS" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Raumzugriff.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Raumzugriff.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_USRDLL" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_ALLOCATORS" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "QI_EXCEPTION" /D "_WINDLL" /D "_MBCS" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/Raumzugriff.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Raumzugriff.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Release"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "_UNICODE" /D "IN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "OS_WIN95" /D\
 "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMESOS_NO_ALLOCATOR" /Fp"$(INTDIR)/Raumzugriff.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Raumzugriff.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "_UNICODE" /D "IN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_MBCS" /D "_USRDLL" /D "OS_WIN95" /D\
 "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D\
 "OS_ALTERNATIVE_STRING_NAMESOS_NO_ALLOCATOR" /Fp"$(INTDIR)/Raumzugriff.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Raumzugriff.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Raumzugriff.cpp

!IF  "$(CFG)" == "Raumzugriff - Win32 Release"

DEP_CPP_RAUMZ=\
	".\Raumguid.h"\
	".\Raumzugriff.h"\
	".\Raumzugriff_i.c"\
	".\SpatialTree.h"\
	".\SpatialTreeQuery.h"\
	".\StdAfx.h"\
	".\TestObjekt.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\Raumzugriff.obj" : $(SOURCE) $(DEP_CPP_RAUMZ) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h" ".\Raumzugriff_i.c"

"$(INTDIR)\Raumzugriff.sbr" : $(SOURCE) $(DEP_CPP_RAUMZ) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h" ".\Raumzugriff_i.c"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Debug"

DEP_CPP_RAUMZ=\
	".\Raumguid.h"\
	".\Raumzugriff.h"\
	".\Raumzugriff_i.c"\
	".\SpatialTree.h"\
	".\SpatialTreeQuery.h"\
	".\StdAfx.h"\
	".\TestObjekt.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\Raumzugriff.obj" : $(SOURCE) $(DEP_CPP_RAUMZ) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h" ".\Raumzugriff_i.c"

"$(INTDIR)\Raumzugriff.sbr" : $(SOURCE) $(DEP_CPP_RAUMZ) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h" ".\Raumzugriff_i.c"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Release"

DEP_CPP_RAUMZ=\
	".\Raumguid.h"\
	".\Raumzugriff.h"\
	".\Raumzugriff_i.c"\
	".\SpatialTree.h"\
	".\SpatialTreeQuery.h"\
	".\StdAfx.h"\
	".\TestObjekt.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	

"$(INTDIR)\Raumzugriff.obj" : $(SOURCE) $(DEP_CPP_RAUMZ) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h" ".\Raumzugriff_i.c"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Debug"

DEP_CPP_RAUMZ=\
	".\Raumguid.h"\
	".\Raumzugriff.h"\
	".\Raumzugriff_i.c"\
	".\SpatialTree.h"\
	".\SpatialTreeQuery.h"\
	".\StdAfx.h"\
	".\TestObjekt.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\Raumzugriff.obj" : $(SOURCE) $(DEP_CPP_RAUMZ) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h" ".\Raumzugriff_i.c"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Raumzugriff.def

!IF  "$(CFG)" == "Raumzugriff - Win32 Release"

!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Debug"

!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Release"

!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Raumzugriff.rc
DEP_RSC_RAUMZU=\
	".\question.rgs"\
	".\Raumzugriff.tlb"\
	".\testobjekt.rgs"\
	".\tree.rgs"\
	

!IF  "$(CFG)" == "Raumzugriff - Win32 Release"


"$(INTDIR)\Raumzugriff.res" : $(SOURCE) $(DEP_RSC_RAUMZU) "$(INTDIR)"\
 ".\Raumzugriff.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Debug"


"$(INTDIR)\Raumzugriff.res" : $(SOURCE) $(DEP_RSC_RAUMZU) "$(INTDIR)"\
 ".\Raumzugriff.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Release"


"$(INTDIR)\Raumzugriff.res" : $(SOURCE) $(DEP_RSC_RAUMZU) "$(INTDIR)"\
 ".\Raumzugriff.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Debug"


"$(INTDIR)\Raumzugriff.res" : $(SOURCE) $(DEP_RSC_RAUMZU) "$(INTDIR)"\
 ".\Raumzugriff.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Raumzugriff.idl

!IF  "$(CFG)" == "Raumzugriff - Win32 Release"

# Begin Custom Build
InputPath=.\Raumzugriff.idl

BuildCmds= \
	midl /old Raumzugriff.idl \
	

"Raumzugriff.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Raumzugriff.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Raumzugriff_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Debug"

# Begin Custom Build
InputPath=.\Raumzugriff.idl

BuildCmds= \
	midl /old Raumzugriff.idl \
	

"Raumzugriff.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Raumzugriff.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Raumzugriff_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Release"

# Begin Custom Build
InputPath=.\Raumzugriff.idl

BuildCmds= \
	midl Raumzugriff.idl \
	

"Raumzugriff.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Raumzugriff.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Raumzugriff_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Debug"

# Begin Custom Build
InputPath=.\Raumzugriff.idl

BuildCmds= \
	midl Raumzugriff.idl \
	

"Raumzugriff.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Raumzugriff.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Raumzugriff_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SpatialTreeQuery.cpp

!IF  "$(CFG)" == "Raumzugriff - Win32 Release"

DEP_CPP_SPATI=\
	".\Hilfsfunktionen.h"\
	".\Raumzugriff.h"\
	".\SpatialTreeQuery.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\SpatialTreeQuery.obj" : $(SOURCE) $(DEP_CPP_SPATI) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"

"$(INTDIR)\SpatialTreeQuery.sbr" : $(SOURCE) $(DEP_CPP_SPATI) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Debug"

DEP_CPP_SPATI=\
	".\Hilfsfunktionen.h"\
	".\Raumzugriff.h"\
	".\SpatialTreeQuery.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\SpatialTreeQuery.obj" : $(SOURCE) $(DEP_CPP_SPATI) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"

"$(INTDIR)\SpatialTreeQuery.sbr" : $(SOURCE) $(DEP_CPP_SPATI) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Release"

DEP_CPP_SPATI=\
	".\Hilfsfunktionen.h"\
	".\Raumzugriff.h"\
	".\SpatialTreeQuery.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\vector"\
	

"$(INTDIR)\SpatialTreeQuery.obj" : $(SOURCE) $(DEP_CPP_SPATI) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Debug"

DEP_CPP_SPATI=\
	".\Hilfsfunktionen.h"\
	".\Raumzugriff.h"\
	".\SpatialTreeQuery.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\SpatialTreeQuery.obj" : $(SOURCE) $(DEP_CPP_SPATI) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SpatialTree.cpp

!IF  "$(CFG)" == "Raumzugriff - Win32 Release"

DEP_CPP_SPATIA=\
	".\EnumUnknown.h"\
	".\Hilfsfunktionen.h"\
	".\objdispatch.h"\
	".\Raumguid.h"\
	".\Raumzugriff.h"\
	".\SpatialTree.h"\
	".\SpatialTreeQuery.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\vector"\
	

"$(INTDIR)\SpatialTree.obj" : $(SOURCE) $(DEP_CPP_SPATIA) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"

"$(INTDIR)\SpatialTree.sbr" : $(SOURCE) $(DEP_CPP_SPATIA) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Debug"

DEP_CPP_SPATIA=\
	".\EnumUnknown.h"\
	".\Hilfsfunktionen.h"\
	".\objdispatch.h"\
	".\Raumguid.h"\
	".\Raumzugriff.h"\
	".\SpatialTree.h"\
	".\SpatialTreeQuery.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\deque"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\deque.cc"\
	{$(INCLUDE)}"\ospace\stl\deque.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\SpatialTree.obj" : $(SOURCE) $(DEP_CPP_SPATIA) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"

"$(INTDIR)\SpatialTree.sbr" : $(SOURCE) $(DEP_CPP_SPATIA) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Release"

DEP_CPP_SPATIA=\
	".\EnumUnknown.h"\
	".\Hilfsfunktionen.h"\
	".\objdispatch.h"\
	".\Raumguid.h"\
	".\Raumzugriff.h"\
	".\SpatialTree.h"\
	".\SpatialTreeQuery.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\deque"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\deque.cc"\
	{$(INCLUDE)}"\ospace\stl\deque.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\SpatialTree.obj" : $(SOURCE) $(DEP_CPP_SPATIA) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Debug"

DEP_CPP_SPATIA=\
	".\EnumUnknown.h"\
	".\Hilfsfunktionen.h"\
	".\objdispatch.h"\
	".\Raumguid.h"\
	".\Raumzugriff.h"\
	".\SpatialTree.h"\
	".\SpatialTreeQuery.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\deque"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\deque.cc"\
	{$(INCLUDE)}"\ospace\stl\deque.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\SpatialTree.obj" : $(SOURCE) $(DEP_CPP_SPATIA) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\testobjekt.cpp

!IF  "$(CFG)" == "Raumzugriff - Win32 Release"

DEP_CPP_TESTO=\
	".\Raumzugriff.h"\
	".\StdAfx.h"\
	".\TestObjekt.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\vector"\
	

"$(INTDIR)\testobjekt.obj" : $(SOURCE) $(DEP_CPP_TESTO) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"

"$(INTDIR)\testobjekt.sbr" : $(SOURCE) $(DEP_CPP_TESTO) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Debug"

DEP_CPP_TESTO=\
	".\Raumzugriff.h"\
	".\StdAfx.h"\
	".\TestObjekt.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\deque"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\deque.cc"\
	{$(INCLUDE)}"\ospace\stl\deque.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\testobjekt.obj" : $(SOURCE) $(DEP_CPP_TESTO) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"

"$(INTDIR)\testobjekt.sbr" : $(SOURCE) $(DEP_CPP_TESTO) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Release"

DEP_CPP_TESTO=\
	".\Raumzugriff.h"\
	".\StdAfx.h"\
	".\TestObjekt.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\deque"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\deque.cc"\
	{$(INCLUDE)}"\ospace\stl\deque.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\testobjekt.obj" : $(SOURCE) $(DEP_CPP_TESTO) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Debug"

DEP_CPP_TESTO=\
	".\Raumzugriff.h"\
	".\StdAfx.h"\
	".\TestObjekt.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\deque"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\deque.cc"\
	{$(INCLUDE)}"\ospace\stl\deque.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\testobjekt.obj" : $(SOURCE) $(DEP_CPP_TESTO) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch" ".\Raumzugriff.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Hilfsfunktionen.cpp

!IF  "$(CFG)" == "Raumzugriff - Win32 Release"

DEP_CPP_HILFS=\
	".\Hilfsfunktionen.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\Hilfsfunktionen.obj" : $(SOURCE) $(DEP_CPP_HILFS) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"

"$(INTDIR)\Hilfsfunktionen.sbr" : $(SOURCE) $(DEP_CPP_HILFS) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Debug"

DEP_CPP_HILFS=\
	".\Hilfsfunktionen.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\Hilfsfunktionen.obj" : $(SOURCE) $(DEP_CPP_HILFS) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"

"$(INTDIR)\Hilfsfunktionen.sbr" : $(SOURCE) $(DEP_CPP_HILFS) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Release"

DEP_CPP_HILFS=\
	".\Hilfsfunktionen.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	

"$(INTDIR)\Hilfsfunktionen.obj" : $(SOURCE) $(DEP_CPP_HILFS) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Debug"

DEP_CPP_HILFS=\
	".\Hilfsfunktionen.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\Hilfsfunktionen.obj" : $(SOURCE) $(DEP_CPP_HILFS) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\objdispatch.cpp

!IF  "$(CFG)" == "Raumzugriff - Win32 Release"

DEP_CPP_OBJDI=\
	".\objdispatch.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\objdispatch.obj" : $(SOURCE) $(DEP_CPP_OBJDI) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"

"$(INTDIR)\objdispatch.sbr" : $(SOURCE) $(DEP_CPP_OBJDI) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Debug"

DEP_CPP_OBJDI=\
	".\objdispatch.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\objdispatch.obj" : $(SOURCE) $(DEP_CPP_OBJDI) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"

"$(INTDIR)\objdispatch.sbr" : $(SOURCE) $(DEP_CPP_OBJDI) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Release"

DEP_CPP_OBJDI=\
	".\objdispatch.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\objdispatch.obj" : $(SOURCE) $(DEP_CPP_OBJDI) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Debug"

DEP_CPP_OBJDI=\
	".\objdispatch.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\objdispatch.obj" : $(SOURCE) $(DEP_CPP_OBJDI) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EnumUnknown.cpp

!IF  "$(CFG)" == "Raumzugriff - Win32 Release"

DEP_CPP_ENUMU=\
	".\EnumUnknown.h"\
	".\Raumguid.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\EnumUnknown.obj" : $(SOURCE) $(DEP_CPP_ENUMU) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"

"$(INTDIR)\EnumUnknown.sbr" : $(SOURCE) $(DEP_CPP_ENUMU) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Debug"

DEP_CPP_ENUMU=\
	".\EnumUnknown.h"\
	".\Raumguid.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\EnumUnknown.obj" : $(SOURCE) $(DEP_CPP_ENUMU) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"

"$(INTDIR)\EnumUnknown.sbr" : $(SOURCE) $(DEP_CPP_ENUMU) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Release"

DEP_CPP_ENUMU=\
	".\EnumUnknown.h"\
	".\Raumguid.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	

"$(INTDIR)\EnumUnknown.obj" : $(SOURCE) $(DEP_CPP_ENUMU) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"


!ELSEIF  "$(CFG)" == "Raumzugriff - Win32 Unicode Debug"

DEP_CPP_ENUMU=\
	".\EnumUnknown.h"\
	".\Raumguid.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\Com\Iterenum.h"\
	{$(INCLUDE)}"\ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\except\stream.h"\
	{$(INCLUDE)}"\ospace\except\stream.ipp"\
	{$(INCLUDE)}"\ospace\except\toolkit.h"\
	{$(INCLUDE)}"\ospace\except\toolkit.ipp"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\io\adapter.h"\
	{$(INCLUDE)}"\ospace\io\adapter.ipp"\
	{$(INCLUDE)}"\ospace\io\device.h"\
	{$(INCLUDE)}"\ospace\io\device.ipp"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\fstream"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\iostream"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\set"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\std\vector"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\internal.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\rbtree.cc"\
	{$(INCLUDE)}"\ospace\stl\rbtree.h"\
	{$(INCLUDE)}"\ospace\stl\set.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
	{$(INCLUDE)}"\ospace\stl\vector.cc"\
	{$(INCLUDE)}"\ospace\stl\vector.h"\
	{$(INCLUDE)}"\ospace\stream.h"\
	{$(INCLUDE)}"\ospace\stream\_startup.h"\
	{$(INCLUDE)}"\ospace\stream\ascii.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.h"\
	{$(INCLUDE)}"\ospace\stream\bstream.ipp"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\fstrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\istrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndr.h"\
	{$(INCLUDE)}"\ospace\stream\ndr.ipp"\
	{$(INCLUDE)}"\ospace\stream\ndrtypes.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.h"\
	{$(INCLUDE)}"\ospace\stream\ostrmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\protocol.h"\
	{$(INCLUDE)}"\ospace\stream\protocol.ipp"\
	{$(INCLUDE)}"\ospace\stream\strbuf.h"\
	{$(INCLUDE)}"\ospace\stream\strbuf.ipp"\
	{$(INCLUDE)}"\ospace\stream\strmdev.h"\
	{$(INCLUDE)}"\ospace\stream\strmdev.ipp"\
	{$(INCLUDE)}"\ospace\stream\tstream.h"\
	{$(INCLUDE)}"\ospace\stream\tstream.ipp"\
	{$(INCLUDE)}"\ospace\string\basic.cc"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\basic.ipp"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\search.cc"\
	{$(INCLUDE)}"\ospace\string\search.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\type\types.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	

"$(INTDIR)\EnumUnknown.obj" : $(SOURCE) $(DEP_CPP_ENUMU) "$(INTDIR)"\
 "$(INTDIR)\Raumzugriff.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
