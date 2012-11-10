# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=FillMode - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to FillMode - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "FillMode - Win32 Release" && "$(CFG)" !=\
 "FillMode - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "FillMode.mak" CFG="FillMode - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FillMode - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "FillMode - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "FillMode - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FillMode - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
TargetName=FillMode
# End Custom Macros

ALL : "$(OUTDIR)\FillMode.vmd" "c:\trias.mvc\trias200.rel\FillMode.vmd"

CLEAN : 
	-@erase "$(INTDIR)\Cgobject.obj"
	-@erase "$(INTDIR)\FillArea.obj"
	-@erase "$(INTDIR)\FillMode.obj"
	-@erase "$(INTDIR)\FillMode.pch"
	-@erase "$(INTDIR)\FillMode.res"
	-@erase "$(INTDIR)\FillParm.obj"
	-@erase "$(INTDIR)\Fixupdc.obj"
	-@erase "$(INTDIR)\helper.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Regvism.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\FillMode.exp"
	-@erase "$(OUTDIR)\FillMode.lib"
	-@erase "$(OUTDIR)\FillMode.vmd"
	-@erase "c:\trias.mvc\trias200.rel\FillMode.vmd"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "STRICT" /D "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D "__MFC__" /D "__VMD_DLL_" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "STRICT" /D "MSWIND" /D\
 "__XT" /D "DLL" /D "__DEXPROCS" /D "__MFC__" /D "__VMD_DLL_"\
 /Fp"$(INTDIR)/FillMode.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/FillMode.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/FillMode.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 stdcppr.lib /nologo /subsystem:windows /dll /machine:I386 /stub:"rights.exe" /out:"Release/FillMode.vmd"
LINK32_FLAGS=stdcppr.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/FillMode.pdb" /machine:I386 /def:".\FillMode.def"\
 /stub:"rights.exe" /out:"$(OUTDIR)/FillMode.vmd"\
 /implib:"$(OUTDIR)/FillMode.lib" 
DEF_FILE= \
	".\FillMode.def"
LINK32_OBJS= \
	"$(INTDIR)\Cgobject.obj" \
	"$(INTDIR)\FillArea.obj" \
	"$(INTDIR)\FillMode.obj" \
	"$(INTDIR)\FillMode.res" \
	"$(INTDIR)\FillParm.obj" \
	"$(INTDIR)\Fixupdc.obj" \
	"$(INTDIR)\helper.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\Regvism.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\FillMode.vmd" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Release\FillMode.vmd
TargetName=FillMode
InputPath=.\Release\FillMode.vmd
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\$(TargetName).vmd" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy "$(TargetPath)" c:\trias.mvc\trias200.rel

# End Custom Build

!ELSEIF  "$(CFG)" == "FillMode - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
TargetName=FillMode
# End Custom Macros

ALL : "$(OUTDIR)\FillMode.vmd" "$(OUTDIR)\FillMode.bsc"\
 "c:\trias.mvc\trias200\FillMode.vmd"

CLEAN : 
	-@erase "$(INTDIR)\Cgobject.obj"
	-@erase "$(INTDIR)\Cgobject.sbr"
	-@erase "$(INTDIR)\FillArea.obj"
	-@erase "$(INTDIR)\FillArea.sbr"
	-@erase "$(INTDIR)\FillMode.obj"
	-@erase "$(INTDIR)\FillMode.pch"
	-@erase "$(INTDIR)\FillMode.res"
	-@erase "$(INTDIR)\FillMode.sbr"
	-@erase "$(INTDIR)\FillParm.obj"
	-@erase "$(INTDIR)\FillParm.sbr"
	-@erase "$(INTDIR)\Fixupdc.obj"
	-@erase "$(INTDIR)\Fixupdc.sbr"
	-@erase "$(INTDIR)\helper.obj"
	-@erase "$(INTDIR)\helper.sbr"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Registry.sbr"
	-@erase "$(INTDIR)\Regvism.obj"
	-@erase "$(INTDIR)\Regvism.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\FillMode.bsc"
	-@erase "$(OUTDIR)\FillMode.exp"
	-@erase "$(OUTDIR)\FillMode.ilk"
	-@erase "$(OUTDIR)\FillMode.lib"
	-@erase "$(OUTDIR)\FillMode.pdb"
	-@erase "$(OUTDIR)\FillMode.vmd"
	-@erase "c:\trias.mvc\trias200\FillMode.vmd"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "STRICT" /D "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D "__MFC__" /D "__VMD_DLL__" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "STRICT" /D\
 "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D "__MFC__" /D "__VMD_DLL__"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/FillMode.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/FillMode.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/FillMode.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Cgobject.sbr" \
	"$(INTDIR)\FillArea.sbr" \
	"$(INTDIR)\FillMode.sbr" \
	"$(INTDIR)\FillParm.sbr" \
	"$(INTDIR)\Fixupdc.sbr" \
	"$(INTDIR)\helper.sbr" \
	"$(INTDIR)\Registry.sbr" \
	"$(INTDIR)\Regvism.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\FillMode.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 stdcppd.lib /nologo /subsystem:windows /dll /debug /machine:I386 /stub:"rights.exe" /out:"Debug/FillMode.vmd"
LINK32_FLAGS=stdcppd.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/FillMode.pdb" /debug /machine:I386 /def:".\FillMode.def"\
 /stub:"rights.exe" /out:"$(OUTDIR)/FillMode.vmd"\
 /implib:"$(OUTDIR)/FillMode.lib" 
DEF_FILE= \
	".\FillMode.def"
LINK32_OBJS= \
	"$(INTDIR)\Cgobject.obj" \
	"$(INTDIR)\FillArea.obj" \
	"$(INTDIR)\FillMode.obj" \
	"$(INTDIR)\FillMode.res" \
	"$(INTDIR)\FillParm.obj" \
	"$(INTDIR)\Fixupdc.obj" \
	"$(INTDIR)\helper.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\Regvism.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\FillMode.vmd" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Debug\FillMode.vmd
TargetName=FillMode
InputPath=.\Debug\FillMode.vmd
SOURCE=$(InputPath)

"c:\trias.mvc\trias200\$(TargetName).vmd" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" c:\trias.mvc\trias200

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

# Name "FillMode - Win32 Release"
# Name "FillMode - Win32 Debug"

!IF  "$(CFG)" == "FillMode - Win32 Release"

!ELSEIF  "$(CFG)" == "FillMode - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\FillMode.cpp

!IF  "$(CFG)" == "FillMode - Win32 Release"

DEP_CPP_FILLM=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\registrx.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\vismguid.h"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\FillMode.obj" : $(SOURCE) $(DEP_CPP_FILLM) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"


!ELSEIF  "$(CFG)" == "FillMode - Win32 Debug"

DEP_CPP_FILLM=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\CERRNO"\
	{$(INCLUDE)}"\CFLOAT"\
	{$(INCLUDE)}"\CLIMITS"\
	{$(INCLUDE)}"\CSTDDEF"\
	{$(INCLUDE)}"\CSTDIO"\
	{$(INCLUDE)}"\CSTDLIB"\
	{$(INCLUDE)}"\CSTRING"\
	{$(INCLUDE)}"\CWCHAR"\
	{$(INCLUDE)}"\EXCEPTION"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\IOS"\
	{$(INCLUDE)}"\IOSFWD"\
	{$(INCLUDE)}"\ISTREAM"\
	{$(INCLUDE)}"\MEMORY"\
	{$(INCLUDE)}"\NEW"\
	{$(INCLUDE)}"\OSTREAM"\
	{$(INCLUDE)}"\registrx.hxx"\
	{$(INCLUDE)}"\STDEXCEPT"\
	{$(INCLUDE)}"\STREAMBUF"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\TYPEINFO"\
	{$(INCLUDE)}"\USE_ANSI.H"\
	{$(INCLUDE)}"\UTILITY"\
	{$(INCLUDE)}"\vismguid.h"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\XIOSBASE"\
	{$(INCLUDE)}"\XLOCALE"\
	{$(INCLUDE)}"\XLOCINFO"\
	{$(INCLUDE)}"\XLOCINFO.H"\
	{$(INCLUDE)}"\XLOCNUM"\
	{$(INCLUDE)}"\XMEMORY"\
	{$(INCLUDE)}"\XSTDDEF"\
	{$(INCLUDE)}"\XSTRING"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\XUTILITY"\
	{$(INCLUDE)}"\YVALS.H"\
	

"$(INTDIR)\FillMode.obj" : $(SOURCE) $(DEP_CPP_FILLM) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"

"$(INTDIR)\FillMode.sbr" : $(SOURCE) $(DEP_CPP_FILLM) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FillMode.def

!IF  "$(CFG)" == "FillMode - Win32 Release"

!ELSEIF  "$(CFG)" == "FillMode - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "FillMode - Win32 Release"

DEP_CPP_STDAF=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "STRICT" /D "MSWIND" /D\
 "__XT" /D "DLL" /D "__DEXPROCS" /D "__MFC__" /D "__VMD_DLL_"\
 /Fp"$(INTDIR)/FillMode.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\FillMode.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "FillMode - Win32 Debug"

DEP_CPP_STDAF=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "STRICT" /D\
 "MSWIND" /D "__XT" /D "DLL" /D "__DEXPROCS" /D "__MFC__" /D "__VMD_DLL__"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/FillMode.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\FillMode.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FillMode.rc

!IF  "$(CFG)" == "FillMode - Win32 Release"

DEP_RSC_FILLMO=\
	".\res\FillMode.rc2"\
	

"$(INTDIR)\FillMode.res" : $(SOURCE) $(DEP_RSC_FILLMO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "FillMode - Win32 Debug"

DEP_RSC_FILLMO=\
	".\FILLMODE.RCV"\
	".\res\FillMode.rc2"\
	

"$(INTDIR)\FillMode.res" : $(SOURCE) $(DEP_RSC_FILLMO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FillArea.cpp

!IF  "$(CFG)" == "FillMode - Win32 Release"

DEP_CPP_FILLA=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\fixupdc.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\vismguid.h"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\FillArea.obj" : $(SOURCE) $(DEP_CPP_FILLA) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"


!ELSEIF  "$(CFG)" == "FillMode - Win32 Debug"

DEP_CPP_FILLA=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\fixupdc.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\vismguid.h"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\FillArea.obj" : $(SOURCE) $(DEP_CPP_FILLA) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"

"$(INTDIR)\FillArea.sbr" : $(SOURCE) $(DEP_CPP_FILLA) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Regvism.cxx

!IF  "$(CFG)" == "FillMode - Win32 Release"

DEP_CPP_REGVI=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\Regvism.obj" : $(SOURCE) $(DEP_CPP_REGVI) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"


!ELSEIF  "$(CFG)" == "FillMode - Win32 Debug"

DEP_CPP_REGVI=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\Regvism.obj" : $(SOURCE) $(DEP_CPP_REGVI) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"

"$(INTDIR)\Regvism.sbr" : $(SOURCE) $(DEP_CPP_REGVI) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cgobject.cxx

!IF  "$(CFG)" == "FillMode - Win32 Release"

DEP_CPP_CGOBJ=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\Cgobject.obj" : $(SOURCE) $(DEP_CPP_CGOBJ) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"


!ELSEIF  "$(CFG)" == "FillMode - Win32 Debug"

DEP_CPP_CGOBJ=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\Cgobject.obj" : $(SOURCE) $(DEP_CPP_CGOBJ) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"

"$(INTDIR)\Cgobject.sbr" : $(SOURCE) $(DEP_CPP_CGOBJ) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\helper.cpp

!IF  "$(CFG)" == "FillMode - Win32 Release"

DEP_CPP_HELPE=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\helper.obj" : $(SOURCE) $(DEP_CPP_HELPE) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"


!ELSEIF  "$(CFG)" == "FillMode - Win32 Debug"

DEP_CPP_HELPE=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\helper.obj" : $(SOURCE) $(DEP_CPP_HELPE) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"

"$(INTDIR)\helper.sbr" : $(SOURCE) $(DEP_CPP_HELPE) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\FillParm.cpp

!IF  "$(CFG)" == "FillMode - Win32 Release"

DEP_CPP_FILLP=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\FillParm.obj" : $(SOURCE) $(DEP_CPP_FILLP) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"


!ELSEIF  "$(CFG)" == "FillMode - Win32 Debug"

DEP_CPP_FILLP=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\FillParm.obj" : $(SOURCE) $(DEP_CPP_FILLP) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"

"$(INTDIR)\FillParm.sbr" : $(SOURCE) $(DEP_CPP_FILLP) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Fixupdc.cpp

!IF  "$(CFG)" == "FillMode - Win32 Release"

DEP_CPP_FIXUP=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\fixupdc.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\Fixupdc.obj" : $(SOURCE) $(DEP_CPP_FIXUP) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"


!ELSEIF  "$(CFG)" == "FillMode - Win32 Debug"

DEP_CPP_FIXUP=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\fixupdc.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\Fixupdc.obj" : $(SOURCE) $(DEP_CPP_FIXUP) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"

"$(INTDIR)\Fixupdc.sbr" : $(SOURCE) $(DEP_CPP_FIXUP) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Registry.cxx

!IF  "$(CFG)" == "FillMode - Win32 Release"

DEP_CPP_REGIS=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\registrx.hxx"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\Registry.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"


!ELSEIF  "$(CFG)" == "FillMode - Win32 Debug"

DEP_CPP_REGIS=\
	".\Cgobject.h"\
	".\FillArea.h"\
	".\FillParm.h"\
	".\Helper.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Icustom.hxx"\
	{$(INCLUDE)}"\registrx.hxx"\
	{$(INCLUDE)}"\VMDM.HXX"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

"$(INTDIR)\Registry.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"

"$(INTDIR)\Registry.sbr" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\FillMode.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
