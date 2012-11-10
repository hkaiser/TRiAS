# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Colors - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Colors - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Colors - Win32 Release" && "$(CFG)" != "Colors - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Colors.mak" CFG="Colors - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Colors - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Colors - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Colors - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Colors - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
TargetName=Colors
# End Custom Macros

ALL : "$(OUTDIR)\Colors.ebn" "c:\trias.mvc\trias200.rel\Colors.ebn"

CLEAN : 
	-@erase "$(INTDIR)\ColorLookUp.obj"
	-@erase "$(INTDIR)\Colors.obj"
	-@erase "$(INTDIR)\Colors.pch"
	-@erase "$(INTDIR)\Colors.res"
	-@erase "$(INTDIR)\ColorsExt.obj"
	-@erase "$(INTDIR)\DoubleColor.obj"
	-@erase "$(INTDIR)\Jumptab.obj"
	-@erase "$(INTDIR)\rgb_hsb2.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\Colors.ebn"
	-@erase "$(OUTDIR)\Colors.exp"
	-@erase "$(OUTDIR)\Colors.lib"
	-@erase ".\Colors.h"
	-@erase ".\Colors.tlb"
	-@erase ".\Colors_i.c"
	-@erase "c:\trias.mvc\trias200.rel\Colors.ebn"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "EBWIN32" /D "QI_EXCEPTION" /D "OS_NO_STREAM_SUPPORT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_ALLOCATORS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "EBWIN32" /D "QI_EXCEPTION"\
 /D "OS_NO_STREAM_SUPPORT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING"\
 /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_ALLOCATORS"\
 /Fp"$(INTDIR)/Colors.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Colors.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Colors.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ebn.lib ospace2r.lib /nologo /dll /machine:I386 /stub:"rights.exe" /out:"Release/Colors.ebn" /subsystem:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=ebn.lib ospace2r.lib /nologo /dll /incremental:no\
 /pdb:"$(OUTDIR)/Colors.pdb" /machine:I386 /def:".\Colors.def"\
 /stub:"rights.exe" /out:"$(OUTDIR)/Colors.ebn" /implib:"$(OUTDIR)/Colors.lib"\
 /subsystem:windows,4.0 
DEF_FILE= \
	".\Colors.def"
LINK32_OBJS= \
	"$(INTDIR)\ColorLookUp.obj" \
	"$(INTDIR)\Colors.obj" \
	"$(INTDIR)\Colors.res" \
	"$(INTDIR)\ColorsExt.obj" \
	"$(INTDIR)\DoubleColor.obj" \
	"$(INTDIR)\Jumptab.obj" \
	"$(INTDIR)\rgb_hsb2.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Colors.ebn" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying target to destination ...
TargetPath=.\Release\Colors.ebn
TargetName=Colors
InputPath=.\Release\Colors.ebn
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\$(TargetName).ebn" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy $(TargetPath) c:\trias.mvc\trias200.rel

# End Custom Build

!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
TargetName=Colorsd
# End Custom Macros

ALL : "$(OUTDIR)\Colorsd.ebn" "$(OUTDIR)\Colors.bsc"\
 "c:\trias.mvc\trias200\Colorsd.ebn"

CLEAN : 
	-@erase "$(INTDIR)\ColorLookUp.obj"
	-@erase "$(INTDIR)\ColorLookUp.sbr"
	-@erase "$(INTDIR)\Colors.obj"
	-@erase "$(INTDIR)\Colors.pch"
	-@erase "$(INTDIR)\Colors.res"
	-@erase "$(INTDIR)\Colors.sbr"
	-@erase "$(INTDIR)\ColorsExt.obj"
	-@erase "$(INTDIR)\ColorsExt.sbr"
	-@erase "$(INTDIR)\DoubleColor.obj"
	-@erase "$(INTDIR)\DoubleColor.sbr"
	-@erase "$(INTDIR)\Jumptab.obj"
	-@erase "$(INTDIR)\Jumptab.sbr"
	-@erase "$(INTDIR)\rgb_hsb2.obj"
	-@erase "$(INTDIR)\rgb_hsb2.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Colors.bsc"
	-@erase "$(OUTDIR)\Colorsd.ebn"
	-@erase "$(OUTDIR)\Colorsd.exp"
	-@erase "$(OUTDIR)\Colorsd.ilk"
	-@erase "$(OUTDIR)\Colorsd.lib"
	-@erase "$(OUTDIR)\Colorsd.pdb"
	-@erase ".\Colors.h"
	-@erase ".\Colors.tlb"
	-@erase ".\Colors_i.c"
	-@erase "c:\trias.mvc\trias200\Colorsd.ebn"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "EBWIN32" /D "QI_EXCEPTION" /D "OS_NO_STREAM_SUPPORT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_ALLOCATORS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "EBWIN32" /D\
 "QI_EXCEPTION" /D "OS_NO_STREAM_SUPPORT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D\
 "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_ALLOCATORS"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/Colors.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Colors.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Colors.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ColorLookUp.sbr" \
	"$(INTDIR)\Colors.sbr" \
	"$(INTDIR)\ColorsExt.sbr" \
	"$(INTDIR)\DoubleColor.sbr" \
	"$(INTDIR)\Jumptab.sbr" \
	"$(INTDIR)\rgb_hsb2.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Colors.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ebn.lib ospace2d.lib /nologo /dll /debug /machine:I386 /stub:"rights.exe" /out:"Debug/Colorsd.ebn" /subsystem:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=ebn.lib ospace2d.lib /nologo /dll /incremental:yes\
 /pdb:"$(OUTDIR)/Colorsd.pdb" /debug /machine:I386 /def:".\Colors.def"\
 /stub:"rights.exe" /out:"$(OUTDIR)/Colorsd.ebn" /implib:"$(OUTDIR)/Colorsd.lib"\
 /subsystem:windows,4.0 
DEF_FILE= \
	".\Colors.def"
LINK32_OBJS= \
	"$(INTDIR)\ColorLookUp.obj" \
	"$(INTDIR)\Colors.obj" \
	"$(INTDIR)\Colors.res" \
	"$(INTDIR)\ColorsExt.obj" \
	"$(INTDIR)\DoubleColor.obj" \
	"$(INTDIR)\Jumptab.obj" \
	"$(INTDIR)\rgb_hsb2.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\Colorsd.ebn" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying target to destination ...
TargetPath=.\Debug\Colorsd.ebn
TargetName=Colorsd
InputPath=.\Debug\Colorsd.ebn
SOURCE=$(InputPath)

"c:\trias.mvc\trias200\$(TargetName).ebn" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy $(TargetPath) c:\trias.mvc\trias200

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

# Name "Colors - Win32 Release"
# Name "Colors - Win32 Debug"

!IF  "$(CFG)" == "Colors - Win32 Release"

!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Colors - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "EBWIN32" /D "QI_EXCEPTION"\
 /D "OS_NO_STREAM_SUPPORT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING"\
 /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_ALLOCATORS"\
 /Fp"$(INTDIR)/Colors.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Colors.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "EBWIN32" /D\
 "QI_EXCEPTION" /D "OS_NO_STREAM_SUPPORT" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D\
 "OS_NO_WSTRING" /D "OS_ALTERNATIVE_STRING_NAMES" /D "OS_NO_ALLOCATORS"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/Colors.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Colors.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Colors.cpp
DEP_CPP_COLOR=\
	".\ColorLookUp.h"\
	".\Colors.h"\
	".\Colors_i.c"\
	".\DoubleColor.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Colors - Win32 Release"


"$(INTDIR)\Colors.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch" ".\Colors.h" ".\Colors_i.c"


!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"


"$(INTDIR)\Colors.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch" ".\Colors.h" ".\Colors_i.c"

"$(INTDIR)\Colors.sbr" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch" ".\Colors.h" ".\Colors_i.c"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Colors.def

!IF  "$(CFG)" == "Colors - Win32 Release"

!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Colors.rc
DEP_RSC_COLORS=\
	".\Colors.tlb"\
	".\Res\ColorLookUp.rgs"\
	".\res\Colors.rc2"\
	".\res\Colors.rcv"\
	".\Res\DoubleColor.rgs"\
	

"$(INTDIR)\Colors.res" : $(SOURCE) $(DEP_RSC_COLORS) "$(INTDIR)" ".\Colors.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Colors.idl

!IF  "$(CFG)" == "Colors - Win32 Release"

# Begin Custom Build
InputPath=.\Colors.idl

BuildCmds= \
	midl Colors.idl \
	

"Colors.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Colors.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Colors_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"

# Begin Custom Build
InputPath=.\Colors.idl

BuildCmds= \
	midl /old Colors.idl \
	

"Colors.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Colors.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"Colors_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ColorLookUp.cpp
DEP_CPP_COLORL=\
	".\ColorLookUp.h"\
	".\Colors.h"\
	".\DoubleColor.h"\
	".\rgb_hsb2.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Colors - Win32 Release"


"$(INTDIR)\ColorLookUp.obj" : $(SOURCE) $(DEP_CPP_COLORL) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch" ".\Colors.h"


!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"


"$(INTDIR)\ColorLookUp.obj" : $(SOURCE) $(DEP_CPP_COLORL) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch" ".\Colors.h"

"$(INTDIR)\ColorLookUp.sbr" : $(SOURCE) $(DEP_CPP_COLORL) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch" ".\Colors.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Res\DoubleColor.rgs

!IF  "$(CFG)" == "Colors - Win32 Release"

!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Res\ColorLookUp.rgs

!IF  "$(CFG)" == "Colors - Win32 Release"

!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DoubleColor.cpp
DEP_CPP_DOUBL=\
	".\Colors.h"\
	".\DoubleColor.h"\
	".\rgb_hsb2.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Colors - Win32 Release"


"$(INTDIR)\DoubleColor.obj" : $(SOURCE) $(DEP_CPP_DOUBL) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch" ".\Colors.h"


!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"


"$(INTDIR)\DoubleColor.obj" : $(SOURCE) $(DEP_CPP_DOUBL) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch" ".\Colors.h"

"$(INTDIR)\DoubleColor.sbr" : $(SOURCE) $(DEP_CPP_DOUBL) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch" ".\Colors.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\rgb_hsb2.cpp
DEP_CPP_RGB_H=\
	".\rgb_hsb2.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Colors - Win32 Release"


"$(INTDIR)\rgb_hsb2.obj" : $(SOURCE) $(DEP_CPP_RGB_H) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch"


!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"


"$(INTDIR)\rgb_hsb2.obj" : $(SOURCE) $(DEP_CPP_RGB_H) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch"

"$(INTDIR)\rgb_hsb2.sbr" : $(SOURCE) $(DEP_CPP_RGB_H) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jumptab.cpp
DEP_CPP_JUMPT=\
	".\ColorsExt.h"\
	".\jumptab.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Colors - Win32 Release"

# PROP Exclude_From_Build 0

"$(INTDIR)\Jumptab.obj" : $(SOURCE) $(DEP_CPP_JUMPT) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch"


!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"

# PROP Exclude_From_Build 0

"$(INTDIR)\Jumptab.obj" : $(SOURCE) $(DEP_CPP_JUMPT) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch"

"$(INTDIR)\Jumptab.sbr" : $(SOURCE) $(DEP_CPP_JUMPT) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ColorsExt.cpp
DEP_CPP_COLORSE=\
	".\Colors.h"\
	".\jumptab.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\bscrerr.h"\
	{$(INCLUDE)}"\Trace.h"\
	

!IF  "$(CFG)" == "Colors - Win32 Release"

# PROP Exclude_From_Build 0

"$(INTDIR)\ColorsExt.obj" : $(SOURCE) $(DEP_CPP_COLORSE) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch" ".\Colors.h"


!ELSEIF  "$(CFG)" == "Colors - Win32 Debug"

# PROP Exclude_From_Build 0

"$(INTDIR)\ColorsExt.obj" : $(SOURCE) $(DEP_CPP_COLORSE) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch" ".\Colors.h"

"$(INTDIR)\ColorsExt.sbr" : $(SOURCE) $(DEP_CPP_COLORSE) "$(INTDIR)"\
 "$(INTDIR)\Colors.pch" ".\Colors.h"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
