# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=linver - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to linver - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "linver - Win32 Release" && "$(CFG)" != "linver - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "LINVER.MAK" CFG="linver - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "linver - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "linver - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "linver - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "linver - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release.207"
# PROP Intermediate_Dir "Release.207"
# PROP Target_Dir ""
OUTDIR=.\Release.207
INTDIR=.\Release.207

ALL : "$(OUTDIR)\maschblr.ext" "..\..\triasdev\include\Imaschen.h"

CLEAN : 
	-@erase "$(INTDIR)\Datahelp.obj"
	-@erase "$(INTDIR)\Doppgeop.obj"
	-@erase "$(INTDIR)\geoobjs.obj"
	-@erase "$(INTDIR)\imaschen.obj"
	-@erase "$(INTDIR)\linver.obj"
	-@erase "$(INTDIR)\LINVER.pch"
	-@erase "$(INTDIR)\Linver.res"
	-@erase "$(INTDIR)\Linvprp.obj"
	-@erase "$(INTDIR)\maschbil.obj"
	-@erase "$(INTDIR)\objkante.obj"
	-@erase "$(INTDIR)\objstat.obj"
	-@erase "$(INTDIR)\Objstatp.obj"
	-@erase "$(INTDIR)\Paramdlg.obj"
	-@erase "$(INTDIR)\Pheader.obj"
	-@erase "$(INTDIR)\Progress.obj"
	-@erase "$(INTDIR)\Propactb.obj"
	-@erase "$(INTDIR)\Strutil.obj"
	-@erase "$(INTDIR)\TOOLS.obj"
	-@erase "$(INTDIR)\Verparam.obj"
	-@erase "$(INTDIR)\Verschnt.obj"
	-@erase "$(OUTDIR)\maschblr.exp"
	-@erase "$(OUTDIR)\maschblr.ext"
	-@erase "$(OUTDIR)\maschblr.lib"
	-@erase "..\..\triasdev\include\Imaschen.h"
	-@erase ".\Imaschen.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Yu"pheader.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release.207/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Linver.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/LINVER.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtmar42.lib cont32r.lib stdcppr.lib ospace2r.lib largeint.lib triastlb.lib /nologo /subsystem:windows /dll /machine:I386 /stub:"rights.exe" /out:"Release.207/maschblr.ext"
LINK32_FLAGS=ixtmar42.lib cont32r.lib stdcppr.lib ospace2r.lib largeint.lib\
 triastlb.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/maschblr.pdb" /machine:I386 /def:".\Linver.def"\
 /stub:"rights.exe" /out:"$(OUTDIR)/maschblr.ext"\
 /implib:"$(OUTDIR)/maschblr.lib" 
DEF_FILE= \
	".\Linver.def"
LINK32_OBJS= \
	"$(INTDIR)\Datahelp.obj" \
	"$(INTDIR)\Doppgeop.obj" \
	"$(INTDIR)\geoobjs.obj" \
	"$(INTDIR)\imaschen.obj" \
	"$(INTDIR)\linver.obj" \
	"$(INTDIR)\Linver.res" \
	"$(INTDIR)\Linvprp.obj" \
	"$(INTDIR)\maschbil.obj" \
	"$(INTDIR)\objkante.obj" \
	"$(INTDIR)\objstat.obj" \
	"$(INTDIR)\Objstatp.obj" \
	"$(INTDIR)\Paramdlg.obj" \
	"$(INTDIR)\Pheader.obj" \
	"$(INTDIR)\Progress.obj" \
	"$(INTDIR)\Propactb.obj" \
	"$(INTDIR)\Strutil.obj" \
	"$(INTDIR)\TOOLS.obj" \
	"$(INTDIR)\Verparam.obj" \
	"$(INTDIR)\Verschnt.obj"

"$(OUTDIR)\maschblr.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug.207"
# PROP Intermediate_Dir "Debug.207"
# PROP Target_Dir ""
OUTDIR=.\Debug.207
INTDIR=.\Debug.207

ALL : "$(OUTDIR)\maschbld.ext" "$(OUTDIR)\LINVER.bsc"

CLEAN : 
	-@erase "$(INTDIR)\Datahelp.obj"
	-@erase "$(INTDIR)\Datahelp.sbr"
	-@erase "$(INTDIR)\Doppgeop.obj"
	-@erase "$(INTDIR)\Doppgeop.sbr"
	-@erase "$(INTDIR)\geoobjs.obj"
	-@erase "$(INTDIR)\geoobjs.sbr"
	-@erase "$(INTDIR)\imaschen.obj"
	-@erase "$(INTDIR)\imaschen.sbr"
	-@erase "$(INTDIR)\linver.obj"
	-@erase "$(INTDIR)\LINVER.pch"
	-@erase "$(INTDIR)\Linver.res"
	-@erase "$(INTDIR)\linver.sbr"
	-@erase "$(INTDIR)\Linvprp.obj"
	-@erase "$(INTDIR)\Linvprp.sbr"
	-@erase "$(INTDIR)\maschbil.obj"
	-@erase "$(INTDIR)\maschbil.sbr"
	-@erase "$(INTDIR)\objkante.obj"
	-@erase "$(INTDIR)\objkante.sbr"
	-@erase "$(INTDIR)\objstat.obj"
	-@erase "$(INTDIR)\objstat.sbr"
	-@erase "$(INTDIR)\Objstatp.obj"
	-@erase "$(INTDIR)\Objstatp.sbr"
	-@erase "$(INTDIR)\Paramdlg.obj"
	-@erase "$(INTDIR)\Paramdlg.sbr"
	-@erase "$(INTDIR)\Pheader.obj"
	-@erase "$(INTDIR)\Pheader.sbr"
	-@erase "$(INTDIR)\Progress.obj"
	-@erase "$(INTDIR)\Progress.sbr"
	-@erase "$(INTDIR)\Propactb.obj"
	-@erase "$(INTDIR)\Propactb.sbr"
	-@erase "$(INTDIR)\Strutil.obj"
	-@erase "$(INTDIR)\Strutil.sbr"
	-@erase "$(INTDIR)\TOOLS.obj"
	-@erase "$(INTDIR)\TOOLS.sbr"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Verparam.obj"
	-@erase "$(INTDIR)\Verparam.sbr"
	-@erase "$(INTDIR)\Verschnt.obj"
	-@erase "$(INTDIR)\Verschnt.sbr"
	-@erase "$(OUTDIR)\LINVER.bsc"
	-@erase "$(OUTDIR)\maschbld.exp"
	-@erase "$(OUTDIR)\maschbld.ext"
	-@erase "$(OUTDIR)\maschbld.ilk"
	-@erase "$(OUTDIR)\maschbld.lib"
	-@erase "$(OUTDIR)\maschbld.pdb"
	-@erase ".\Imaschen.h"
	-@erase ".\Imaschen.tlb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr /Yu"pheader.h" /c
CPP_PROJ=/nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug.207/
CPP_SBRS=.\Debug.207/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Linver.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/LINVER.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Datahelp.sbr" \
	"$(INTDIR)\Doppgeop.sbr" \
	"$(INTDIR)\geoobjs.sbr" \
	"$(INTDIR)\imaschen.sbr" \
	"$(INTDIR)\linver.sbr" \
	"$(INTDIR)\Linvprp.sbr" \
	"$(INTDIR)\maschbil.sbr" \
	"$(INTDIR)\objkante.sbr" \
	"$(INTDIR)\objstat.sbr" \
	"$(INTDIR)\Objstatp.sbr" \
	"$(INTDIR)\Paramdlg.sbr" \
	"$(INTDIR)\Pheader.sbr" \
	"$(INTDIR)\Progress.sbr" \
	"$(INTDIR)\Propactb.sbr" \
	"$(INTDIR)\Strutil.sbr" \
	"$(INTDIR)\TOOLS.sbr" \
	"$(INTDIR)\Verparam.sbr" \
	"$(INTDIR)\Verschnt.sbr"

"$(OUTDIR)\LINVER.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtmad42.lib cont32d.lib stdcppd.lib ospace2d.lib largeint.lib triastld.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug.207/maschbld.ext"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=ixtmad42.lib cont32d.lib stdcppd.lib ospace2d.lib largeint.lib\
 triastld.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/maschbld.pdb" /debug /machine:I386 /def:".\Linver.def"\
 /out:"$(OUTDIR)/maschbld.ext" /implib:"$(OUTDIR)/maschbld.lib" 
DEF_FILE= \
	".\Linver.def"
LINK32_OBJS= \
	"$(INTDIR)\Datahelp.obj" \
	"$(INTDIR)\Doppgeop.obj" \
	"$(INTDIR)\geoobjs.obj" \
	"$(INTDIR)\imaschen.obj" \
	"$(INTDIR)\linver.obj" \
	"$(INTDIR)\Linver.res" \
	"$(INTDIR)\Linvprp.obj" \
	"$(INTDIR)\maschbil.obj" \
	"$(INTDIR)\objkante.obj" \
	"$(INTDIR)\objstat.obj" \
	"$(INTDIR)\Objstatp.obj" \
	"$(INTDIR)\Paramdlg.obj" \
	"$(INTDIR)\Pheader.obj" \
	"$(INTDIR)\Progress.obj" \
	"$(INTDIR)\Propactb.obj" \
	"$(INTDIR)\Strutil.obj" \
	"$(INTDIR)\TOOLS.obj" \
	"$(INTDIR)\Verparam.obj" \
	"$(INTDIR)\Verschnt.obj"

"$(OUTDIR)\maschbld.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "linver - Win32 Release"
# Name "linver - Win32 Debug"

!IF  "$(CFG)" == "linver - Win32 Release"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\linver.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

DEP_CPP_LINVE=\
	".\DOPPGUID.H"\
	".\LINAGUID.H"\
	".\LINVER.HPP"\
	".\LinVerConfig.h"\
	".\LINVGUID.H"\
	".\PHEADER.H"\
	".\RSLTGUID.H"\
	".\VERGUID.H"\
	".\version.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\linver.obj" : $(SOURCE) $(DEP_CPP_LINVE) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

DEP_CPP_LINVE=\
	".\DOPPGUID.H"\
	".\LINAGUID.H"\
	".\LINVER.HPP"\
	".\LinVerConfig.h"\
	".\LINVGUID.H"\
	".\PHEADER.H"\
	".\RSLTGUID.H"\
	".\VERGUID.H"\
	".\version.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\REGISTRX.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
# ADD CPP /Yu"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\linver.obj" : $(SOURCE) $(DEP_CPP_LINVE) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

"$(INTDIR)\linver.sbr" : $(SOURCE) $(DEP_CPP_LINVE) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Pheader.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

DEP_CPP_PHEAD=\
	".\LinVerConfig.h"\
	".\PHEADER.H"\
	{$(INCLUDE)}"\ATLIMPL.CPP"\
	{$(INCLUDE)}"\Atlimpl11.h"\
	{$(INCLUDE)}"\BOOL.H"\
	
# ADD CPP /Yc"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yc"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Pheader.obj" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LINVER.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

DEP_CPP_PHEAD=\
	".\LinVerConfig.h"\
	".\PHEADER.H"\
	{$(INCLUDE)}"\ATLIMPL.CPP"\
	{$(INCLUDE)}"\Atlimpl11.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	
# ADD CPP /Yc"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yc"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Pheader.obj" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Pheader.sbr" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LINVER.pch" : $(SOURCE) $(DEP_CPP_PHEAD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Linver.def

!IF  "$(CFG)" == "linver - Win32 Release"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Linver.rc
DEP_RSC_LINVER=\
	".\Doppelt.rgs"\
	".\Imaschen.rgs"\
	".\Imaschen.tlb"\
	".\Linver.rcv"\
	".\Maschen.rgs"\
	".\Result.rgs"\
	".\Verschnt.rgs"\
	

"$(INTDIR)\Linver.res" : $(SOURCE) $(DEP_RSC_LINVER) "$(INTDIR)"\
 ".\Imaschen.tlb"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Strutil.cpp
DEP_CPP_STRUT=\
	".\PHEADER.H"\
	

!IF  "$(CFG)" == "linver - Win32 Release"

# ADD CPP /Yu"pheader.h"

"$(INTDIR)\Strutil.obj" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

# ADD CPP /Yu"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Strutil.obj" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

"$(INTDIR)\Strutil.sbr" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Propactb.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

DEP_CPP_PROPA=\
	".\LinVerConfig.h"\
	".\PHEADER.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\hpp\DATAHELP.HPP"\
	{$(INCLUDE)}"\hpp\PROPACTB.HPP"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\Propactb.obj" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

DEP_CPP_PROPA=\
	".\LinVerConfig.h"\
	".\PHEADER.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Helper.h"\
	{$(INCLUDE)}"\hpp\DATAHELP.HPP"\
	{$(INCLUDE)}"\hpp\PROPACTB.HPP"\
	{$(INCLUDE)}"\OCIDL.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	
# ADD CPP /Yu"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Propactb.obj" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

"$(INTDIR)\Propactb.sbr" : $(SOURCE) $(DEP_CPP_PROPA) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Linvprp.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

DEP_CPP_LINVP=\
	".\DOPPGEOP.HPP"\
	".\DOPPGUID.H"\
	".\GEOOBJS.HPP"\
	".\Imaschen.h"\
	".\IMASCHEN.HPP"\
	".\LINAGUID.H"\
	".\LINVER.HPP"\
	".\LinVerConfig.h"\
	".\LINVGUID.H"\
	".\LINVPRP.HPP"\
	".\OBJKANTE.HPP"\
	".\OBJSTATP.HPP"\
	".\PARAMDLG.HPP"\
	".\PHEADER.H"\
	".\RSLTGUID.H"\
	".\VERGUID.H"\
	".\VERSCHNT.HPP"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\hpp\DATAHELP.HPP"\
	{$(INCLUDE)}"\hpp\PROPACTB.HPP"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\INT64.H"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\Linvprp.obj" : $(SOURCE) $(DEP_CPP_LINVP) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

DEP_CPP_LINVP=\
	".\DOPPGEOP.HPP"\
	".\DOPPGUID.H"\
	".\GEOOBJS.HPP"\
	".\Imaschen.h"\
	".\IMASCHEN.HPP"\
	".\LINAGUID.H"\
	".\LINVER.HPP"\
	".\LinVerConfig.h"\
	".\LINVGUID.H"\
	".\LINVPRP.HPP"\
	".\OBJCONT.HPP"\
	".\OBJKANTE.HPP"\
	".\OBJSTATP.HPP"\
	".\PARAMDLG.HPP"\
	".\PHEADER.H"\
	".\RSLTGUID.H"\
	".\VERGUID.H"\
	".\VERSCHNT.HPP"\
	"C:\CV.MVC\INCLUDE.32\Gc.h"\
	"C:\MSDEV\ATL11\INCLUDE\ATLBASE.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOM.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOMX.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLUTIL.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\hpp\DATAHELP.HPP"\
	{$(INCLUDE)}"\hpp\ErrCodesOdbc.hxx"\
	{$(INCLUDE)}"\hpp\PROPACTB.HPP"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\INT64.H"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Linvprp.obj" : $(SOURCE) $(DEP_CPP_LINVP) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch" ".\Imaschen.h"
   $(BuildCmds)

"$(INTDIR)\Linvprp.sbr" : $(SOURCE) $(DEP_CPP_LINVP) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch" ".\Imaschen.h"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Paramdlg.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

DEP_CPP_PARAM=\
	"..\Z_HXX\ctfx.hxx"\
	".\LINAGUID.H"\
	".\LINVER.HPP"\
	".\LinVerConfig.h"\
	".\LINVGUID.H"\
	".\LINVPRP.HPP"\
	".\MASCHBIL.HPP"\
	".\OBJCONT.HPP"\
	".\OBJKANTE.HPP"\
	".\PARAMDLG.HPP"\
	".\PHEADER.H"\
	".\TOOLS.HPP"\
	"C:\CV.MVC\INCLUDE.32\Gc.h"\
	"C:\MSDEV\ATL11\INCLUDE\ATLBASE.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOM.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOMX.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLUTIL.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\CtfxMfc.h"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\hpp\ErrCodesOdbc.hxx"\
	{$(INCLUDE)}"\hpp\PROGRSST.HPP"\
	{$(INCLUDE)}"\hpp\PROPACTB.HPP"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\Paramdlg.obj" : $(SOURCE) $(DEP_CPP_PARAM) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

DEP_CPP_PARAM=\
	".\LINAGUID.H"\
	".\LINVER.HPP"\
	".\LINVGUID.H"\
	".\LINVPRP.HPP"\
	".\MASCHBIL.HPP"\
	".\OBJKANTE.HPP"\
	".\PARAMDLG.HPP"\
	".\PHEADER.H"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\CtfxMfc.h"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\hpp\PROGRSST.HPP"\
	{$(INCLUDE)}"\hpp\PROPACTB.HPP"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
# ADD CPP /Yu"pheader.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Paramdlg.obj" : $(SOURCE) $(DEP_CPP_PARAM) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

"$(INTDIR)\Paramdlg.sbr" : $(SOURCE) $(DEP_CPP_PARAM) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Datahelp.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

DEP_CPP_DATAH=\
	".\LinVerConfig.h"\
	".\PHEADER.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\hpp\DATAHELP.HPP"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\Datahelp.obj" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

DEP_CPP_DATAH=\
	".\LinVerConfig.h"\
	".\PHEADER.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\hpp\DATAHELP.HPP"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\propactn.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Datahelp.obj" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

"$(INTDIR)\Datahelp.sbr" : $(SOURCE) $(DEP_CPP_DATAH) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\objkante.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

DEP_CPP_OBJKA=\
	".\LinVerConfig.h"\
	".\OBJKANTE.HPP"\
	".\PHEADER.H"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\objkante.obj" : $(SOURCE) $(DEP_CPP_OBJKA) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

DEP_CPP_OBJKA=\
	".\LinVerConfig.h"\
	".\OBJCONT.HPP"\
	".\OBJKANTE.HPP"\
	".\PHEADER.H"\
	".\TOOLS.HPP"\
	"C:\CV.MVC\INCLUDE.32\Gc.h"\
	"C:\MSDEV\ATL11\INCLUDE\ATLBASE.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOM.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOMX.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLUTIL.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\hpp\ErrCodesOdbc.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\objkante.obj" : $(SOURCE) $(DEP_CPP_OBJKA) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

"$(INTDIR)\objkante.sbr" : $(SOURCE) $(DEP_CPP_OBJKA) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TOOLS.Cpp

!IF  "$(CFG)" == "linver - Win32 Release"

DEP_CPP_TOOLS=\
	".\LinVerConfig.h"\
	".\PHEADER.H"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\TOOLS.obj" : $(SOURCE) $(DEP_CPP_TOOLS) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

DEP_CPP_TOOLS=\
	".\LinVerConfig.h"\
	".\PHEADER.H"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Hdrentrx.hxx"\
	{$(INCLUDE)}"\iunredo.hxx"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\UNDOGUID.H"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\TOOLS.obj" : $(SOURCE) $(DEP_CPP_TOOLS) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

"$(INTDIR)\TOOLS.sbr" : $(SOURCE) $(DEP_CPP_TOOLS) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\maschbil.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

DEP_CPP_MASCH=\
	".\LinVerConfig.h"\
	".\MASCHBIL.HPP"\
	".\OBJKANTE.HPP"\
	".\PARAMDLG.HPP"\
	".\PHEADER.H"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\hpp\PROGRSST.HPP"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
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
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
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
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Reinguid.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\maschbil.obj" : $(SOURCE) $(DEP_CPP_MASCH) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

DEP_CPP_MASCH=\
	".\LinVerConfig.h"\
	".\MASCHBIL.HPP"\
	".\OBJCONT.HPP"\
	".\OBJKANTE.HPP"\
	".\PARAMDLG.HPP"\
	".\PHEADER.H"\
	".\TOOLS.HPP"\
	"C:\CV.MVC\INCLUDE.32\Gc.h"\
	"C:\MSDEV\ATL11\INCLUDE\ATLBASE.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOM.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOMX.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLUTIL.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\hpp\ErrCodesOdbc.hxx"\
	{$(INCLUDE)}"\hpp\PROGRSST.HPP"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
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
	{$(INCLUDE)}"\ospace\stl\map.cc"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
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
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stl\treeaux.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Reinguid.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\maschbil.obj" : $(SOURCE) $(DEP_CPP_MASCH) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

"$(INTDIR)\maschbil.sbr" : $(SOURCE) $(DEP_CPP_MASCH) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Progress.cpp
DEP_CPP_PROGR=\
	".\PHEADER.H"\
	{$(INCLUDE)}"\hpp\PROGRSST.HPP"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	

!IF  "$(CFG)" == "linver - Win32 Release"

# ADD CPP /Yu"pheader.h"

"$(INTDIR)\Progress.obj" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "linver - Win32 Debug"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Progress.obj" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

"$(INTDIR)\Progress.sbr" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\objstat.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

DEP_CPP_OBJST=\
	".\GEOOBJS.HPP"\
	".\LinVerConfig.h"\
	".\OBJSTAT.HPP"\
	".\PHEADER.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\Xtensnx.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\objstat.obj" : $(SOURCE) $(DEP_CPP_OBJST) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

DEP_CPP_OBJST=\
	".\GEOOBJS.HPP"\
	".\LinVerConfig.h"\
	".\OBJCONT.HPP"\
	".\OBJSTAT.HPP"\
	".\PHEADER.H"\
	"C:\CV.MVC\INCLUDE.32\Gc.h"\
	"C:\MSDEV\ATL11\INCLUDE\ATLBASE.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOM.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOMX.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLUTIL.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\hpp\ErrCodesOdbc.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\objstat.obj" : $(SOURCE) $(DEP_CPP_OBJST) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

"$(INTDIR)\objstat.sbr" : $(SOURCE) $(DEP_CPP_OBJST) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Objstatp.cpp
DEP_CPP_OBJSTA=\
	".\LinVerConfig.h"\
	".\OBJCONT.HPP"\
	".\OBJSTAT.HPP"\
	".\OBJSTATP.HPP"\
	".\PHEADER.H"\
	".\RSLTGUID.H"\
	"C:\CV.MVC\INCLUDE.32\Gc.h"\
	"C:\MSDEV\ATL11\INCLUDE\ATLBASE.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOM.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOMX.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLUTIL.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\hpp\DATAHELP.HPP"\
	{$(INCLUDE)}"\hpp\ErrCodesOdbc.hxx"\
	{$(INCLUDE)}"\hpp\PROPACTB.HPP"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\INT64.H"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	

!IF  "$(CFG)" == "linver - Win32 Release"

# ADD CPP /Yu"pheader.h"

"$(INTDIR)\Objstatp.obj" : $(SOURCE) $(DEP_CPP_OBJSTA) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "linver - Win32 Debug"


BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Objstatp.obj" : $(SOURCE) $(DEP_CPP_OBJSTA) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

"$(INTDIR)\Objstatp.sbr" : $(SOURCE) $(DEP_CPP_OBJSTA) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Doppgeop.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

DEP_CPP_DOPPG=\
	".\DOPPGEOP.HPP"\
	".\DOPPGUID.H"\
	".\GEOOBJS.HPP"\
	".\LinVerConfig.h"\
	".\PHEADER.H"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\hpp\DATAHELP.HPP"\
	{$(INCLUDE)}"\hpp\PROGRSST.HPP"\
	{$(INCLUDE)}"\hpp\PROPACTB.HPP"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\INT64.H"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\Doppgeop.obj" : $(SOURCE) $(DEP_CPP_DOPPG) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

DEP_CPP_DOPPG=\
	".\DOPPGEOP.HPP"\
	".\DOPPGUID.H"\
	".\GEOOBJS.HPP"\
	".\LinVerConfig.h"\
	".\OBJCONT.HPP"\
	".\PHEADER.H"\
	".\TOOLS.HPP"\
	"C:\CV.MVC\INCLUDE.32\Gc.h"\
	"C:\MSDEV\ATL11\INCLUDE\ATLBASE.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOM.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOMX.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLUTIL.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\hpp\DATAHELP.HPP"\
	{$(INCLUDE)}"\hpp\ErrCodesOdbc.hxx"\
	{$(INCLUDE)}"\hpp\PROGRSST.HPP"\
	{$(INCLUDE)}"\hpp\PROPACTB.HPP"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\INT64.H"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
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
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Doppgeop.obj" : $(SOURCE) $(DEP_CPP_DOPPG) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

"$(INTDIR)\Doppgeop.sbr" : $(SOURCE) $(DEP_CPP_DOPPG) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\geoobjs.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

DEP_CPP_GEOOB=\
	".\GEOOBJS.HPP"\
	".\LinVerConfig.h"\
	".\PHEADER.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\geoobjs.obj" : $(SOURCE) $(DEP_CPP_GEOOB) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

DEP_CPP_GEOOB=\
	".\GEOOBJS.HPP"\
	".\LinVerConfig.h"\
	".\OBJCONT.HPP"\
	".\PHEADER.H"\
	"C:\CV.MVC\INCLUDE.32\Gc.h"\
	"C:\MSDEV\ATL11\INCLUDE\ATLBASE.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOM.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOMX.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLUTIL.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\hpp\ErrCodesOdbc.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\geoobjs.obj" : $(SOURCE) $(DEP_CPP_GEOOB) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

"$(INTDIR)\geoobjs.sbr" : $(SOURCE) $(DEP_CPP_GEOOB) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Result.rgs

!IF  "$(CFG)" == "linver - Win32 Release"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Maschen.rgs

!IF  "$(CFG)" == "linver - Win32 Release"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Doppelt.rgs

!IF  "$(CFG)" == "linver - Win32 Release"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Verschnt.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

DEP_CPP_VERSC=\
	".\LinVerConfig.h"\
	".\PARAMDLG.HPP"\
	".\PHEADER.H"\
	".\VERGUID.H"\
	".\VERPARAM.HPP"\
	".\VERSCHNT.HPP"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\hpp\DATAHELP.HPP"\
	{$(INCLUDE)}"\hpp\PROPACTB.HPP"\
	{$(INCLUDE)}"\INT64.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\Verschnt.obj" : $(SOURCE) $(DEP_CPP_VERSC) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

DEP_CPP_VERSC=\
	".\LinVerConfig.h"\
	".\PARAMDLG.HPP"\
	".\PHEADER.H"\
	".\VERGUID.H"\
	".\VERPARAM.HPP"\
	".\VERSCHNT.HPP"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\hpp\DATAHELP.HPP"\
	{$(INCLUDE)}"\hpp\PROPACTB.HPP"\
	{$(INCLUDE)}"\INT64.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\xtsnguid.h"\
	

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Verschnt.obj" : $(SOURCE) $(DEP_CPP_VERSC) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

"$(INTDIR)\Verschnt.sbr" : $(SOURCE) $(DEP_CPP_VERSC) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Verparam.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

DEP_CPP_VERPA=\
	".\LinVerConfig.h"\
	".\OBJKANTE.HPP"\
	".\PARAMDLG.HPP"\
	".\PHEADER.H"\
	".\TOOLS.HPP"\
	".\VERGUID.H"\
	".\VERPARAM.HPP"\
	".\VERSCHNT.HPP"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\hpp\PROPACTB.HPP"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\xtsnguid.h"\
	
# ADD CPP /Yu"pheader.h"

"$(INTDIR)\Verparam.obj" : $(SOURCE) $(DEP_CPP_VERPA) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "__XT" /D "__MFC__" /D\
 "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS" /D "OS_WIN_95" /D\
 "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D "_ATL_NEW_CCOMSTRUCT" /D\
 "__ATL_11_USED__" /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

DEP_CPP_VERPA=\
	".\LinVerConfig.h"\
	".\OBJCONT.HPP"\
	".\OBJKANTE.HPP"\
	".\PARAMDLG.HPP"\
	".\PHEADER.H"\
	".\TOOLS.HPP"\
	".\VERGUID.H"\
	".\VERPARAM.HPP"\
	".\VERSCHNT.HPP"\
	"C:\CV.MVC\INCLUDE.32\Gc.h"\
	"C:\MSDEV\ATL11\INCLUDE\ATLBASE.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOM.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOMX.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLUTIL.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\hpp\ErrCodesOdbc.hxx"\
	{$(INCLUDE)}"\hpp\PROPACTB.HPP"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\OPERGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.h"\
	{$(INCLUDE)}"\ospace\COM\Iterenum.wobase.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\header.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\class.h"\
	{$(INCLUDE)}"\ospace\rtti\class.ipp"\
	{$(INCLUDE)}"\ospace\rtti\hmacros.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros1.h"\
	{$(INCLUDE)}"\ospace\rtti\hmacros3.h"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\std\typeinfo"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /I "e:\triasdev.mvc\inc.hpp" /D\
 "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D\
 "__XT" /D "__MFC__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__DEXPROCS"\
 /D "OS_WIN_95" /D "OS_NO_ALLOCATORS" /D "OS_ALTERNATIVE_STRING_NAMES" /D\
 "_ATL_NEW_CCOMSTRUCT" /D "__ATL_11_USED__" /Fr"$(INTDIR)/"\
 /Fp"$(INTDIR)/LINVER.pch" /Yu"pheader.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Verparam.obj" : $(SOURCE) $(DEP_CPP_VERPA) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

"$(INTDIR)\Verparam.sbr" : $(SOURCE) $(DEP_CPP_VERPA) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Verschnt.rgs

!IF  "$(CFG)" == "linver - Win32 Release"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\imaschen.cpp

!IF  "$(CFG)" == "linver - Win32 Release"

DEP_CPP_IMASC=\
	".\Imaschen.h"\
	".\IMASCHEN.HPP"\
	".\Imaschen_i.c"\
	".\LinVerConfig.h"\
	".\LINVGUID.H"\
	".\MASCHBIL.HPP"\
	".\OBJCONT.HPP"\
	".\OBJKANTE.HPP"\
	".\PARAMDLG.HPP"\
	".\PHEADER.H"\
	".\TOOLS.HPP"\
	"C:\CV.MVC\INCLUDE.32\Gc.h"\
	"C:\MSDEV\ATL11\INCLUDE\ATLBASE.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOM.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLCOMX.H"\
	"C:\MSDEV\ATL11\INCLUDE\ATLUTIL.H"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\hpp\ErrCodesOdbc.hxx"\
	{$(INCLUDE)}"\hpp\PROGRSST.HPP"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Ipropseq.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\except\config.h"\
	{$(INCLUDE)}"\ospace\except\except.h"\
	{$(INCLUDE)}"\ospace\except\stdex.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\iosfwd"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\std\string"\
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
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.cc"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.cc"\
	{$(INCLUDE)}"\ospace\stl\nodealoc.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
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
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	

"$(INTDIR)\imaschen.obj" : $(SOURCE) $(DEP_CPP_IMASC) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch"


!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

DEP_CPP_IMASC=\
	".\Imaschen.h"\
	".\IMASCHEN.HPP"\
	".\Imaschen_i.c"\
	".\LINVGUID.H"\
	".\MASCHBIL.HPP"\
	".\OBJKANTE.HPP"\
	".\PARAMDLG.HPP"\
	".\PHEADER.H"\
	".\TOOLS.HPP"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\hpp\PROGRSST.HPP"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\OBJGGUID.H"\
	{$(INCLUDE)}"\ospace\COM\ComErrorMacros.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Debug.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.h"\
	{$(INCLUDE)}"\ospace\COM\Smartif.Nodebug.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\internal\fmacros.h"\
	{$(INCLUDE)}"\ospace\std\algorithm"\
	{$(INCLUDE)}"\ospace\std\istream"\
	{$(INCLUDE)}"\ospace\std\list"\
	{$(INCLUDE)}"\ospace\std\map"\
	{$(INCLUDE)}"\ospace\std\ostream"\
	{$(INCLUDE)}"\ospace\stl\advalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\advalgo.h"\
	{$(INCLUDE)}"\ospace\stl\allocate.cc"\
	{$(INCLUDE)}"\ospace\stl\allocate.h"\
	{$(INCLUDE)}"\ospace\stl\allocimp.h"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\auxalgo.h"\
	{$(INCLUDE)}"\ospace\stl\basalgo.h"\
	{$(INCLUDE)}"\ospace\stl\common.h"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\function.h"\
	{$(INCLUDE)}"\ospace\stl\heap.cc"\
	{$(INCLUDE)}"\ospace\stl\heap.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.cc"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\stl\list.h"\
	{$(INCLUDE)}"\ospace\stl\map.h"\
	{$(INCLUDE)}"\ospace\stl\ops.h"\
	{$(INCLUDE)}"\ospace\stl\pair.h"\
	{$(INCLUDE)}"\ospace\stl\randgen.h"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.cc"\
	{$(INCLUDE)}"\ospace\stl\rawalgo.h"\
	{$(INCLUDE)}"\ospace\stl\rawiter.h"\
	{$(INCLUDE)}"\ospace\stl\sort.cc"\
	{$(INCLUDE)}"\ospace\stl\sort.h"\
	{$(INCLUDE)}"\ospace\stl\stlerror.h"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.cc"\
	{$(INCLUDE)}"\ospace\stl\tempbuf.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	

"$(INTDIR)\imaschen.obj" : $(SOURCE) $(DEP_CPP_IMASC) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch" ".\Imaschen.h"

"$(INTDIR)\imaschen.sbr" : $(SOURCE) $(DEP_CPP_IMASC) "$(INTDIR)"\
 "$(INTDIR)\LINVER.pch" ".\Imaschen.h"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Imaschen.idl

!IF  "$(CFG)" == "linver - Win32 Release"

# Begin Custom Build - create type library
InputPath=.\Imaschen.idl
InputName=Imaschen

BuildCmds= \
	midl $(InputName).idl /win32 /mktyplib203 /old /I d:\triasdev\include\idl /h\
                                                                                                   D:\triasdev\include\$(InputName).h   /ms_ext  /c_ext /tlb $(InputName).tlb \
	

"d:\triasdev\include\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

# Begin Custom Build - create type library
InputPath=.\Imaschen.idl
InputName=Imaschen

BuildCmds= \
	midl $(InputName).idl /win32 /mktyplib203  /old /h  $(InputName).h   /ms_ext\
                                                                     /c_ext /tlb $(InputName).tlb \
	

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Imaschen.rgs

!IF  "$(CFG)" == "linver - Win32 Release"

!ELSEIF  "$(CFG)" == "linver - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
