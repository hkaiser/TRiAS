# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Buffer - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Buffer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Buffer - Win32 Release" && "$(CFG)" != "Buffer - Win32 Debug"\
 && "$(CFG)" != "Buffer - Win32 ReleaseDebug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Buffer.mak" CFG="Buffer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Buffer - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Buffer - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Buffer - Win32 ReleaseDebug" (based on\
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
# PROP Target_Last_Scanned "Buffer - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Buffer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel
# Begin Custom Macros
TargetName=buffer
# End Custom Macros

ALL : "$(OUTDIR)\buffer.ext" "..\..\TRIAS\TRIAS32R\buffer.ext"

CLEAN : 
	-@erase "$(INTDIR)\BUFF_EIN.OBJ"
	-@erase "$(INTDIR)\BUFFER.OBJ"
	-@erase "$(INTDIR)\Buffer.pch"
	-@erase "$(INTDIR)\Buffer.res"
	-@erase "$(INTDIR)\Buffering.obj"
	-@erase "$(INTDIR)\BUFFERP.OBJ"
	-@erase "$(INTDIR)\Buffext.obj"
	-@erase "$(OUTDIR)\buffer.exp"
	-@erase "$(OUTDIR)\buffer.ext"
	-@erase "$(OUTDIR)\buffer.lib"
	-@erase "..\..\TRIAS\TRIAS32R\buffer.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /I "..\z_hxx" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_11_USED__" /Yu"bufferp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /I "..\z_hxx" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D\
 "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /Fp"$(INTDIR)/Buffer.pch" /Yu"bufferp.hxx"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i "..\z_hxx" /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Buffer.res" /i "..\z_hxx" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Buffer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 geometr.lib ixtatr42.lib stdcppr.lib tfrmwork.lib cont32r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib triastlb.lib /nologo /dll /machine:I386 /out:"WinRel/buffer.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=geometr.lib ixtatr42.lib stdcppr.lib tfrmwork.lib cont32r.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib\
 triastlb.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)/buffer.pdb"\
 /machine:I386 /def:".\BUFFER.DEF" /out:"$(OUTDIR)/buffer.ext"\
 /implib:"$(OUTDIR)/buffer.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\BUFFER.DEF"
LINK32_OBJS= \
	"$(INTDIR)\BUFF_EIN.OBJ" \
	"$(INTDIR)\BUFFER.OBJ" \
	"$(INTDIR)\Buffer.res" \
	"$(INTDIR)\Buffering.obj" \
	"$(INTDIR)\BUFFERP.OBJ" \
	"$(INTDIR)\Buffext.obj"

"$(OUTDIR)\buffer.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinRel\buffer.ext
TargetName=buffer
InputPath=.\WinRel\buffer.ext
SOURCE=$(InputPath)

"D:\TRIAS\TRIAS32R\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" D:\TRIAS\TRIAS32R

# End Custom Build

!ELSEIF  "$(CFG)" == "Buffer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug
# Begin Custom Macros
TargetName=bufferd
# End Custom Macros

ALL : "$(OUTDIR)\bufferd.ext" "$(OUTDIR)\Buffer.bsc"\
 "..\..\TRIAS\TRIAS32D\bufferd.ext"

CLEAN : 
	-@erase "$(INTDIR)\BUFF_EIN.OBJ"
	-@erase "$(INTDIR)\BUFF_EIN.SBR"
	-@erase "$(INTDIR)\BUFFER.OBJ"
	-@erase "$(INTDIR)\Buffer.res"
	-@erase "$(INTDIR)\BUFFER.SBR"
	-@erase "$(INTDIR)\BUFFERD.idb"
	-@erase "$(INTDIR)\BUFFERD.pch"
	-@erase "$(INTDIR)\BUFFERD.pdb"
	-@erase "$(INTDIR)\Buffering.obj"
	-@erase "$(INTDIR)\Buffering.sbr"
	-@erase "$(INTDIR)\BUFFERP.OBJ"
	-@erase "$(INTDIR)\BUFFERP.SBR"
	-@erase "$(INTDIR)\Buffext.obj"
	-@erase "$(INTDIR)\Buffext.sbr"
	-@erase "$(OUTDIR)\Buffer.bsc"
	-@erase "$(OUTDIR)\bufferd.exp"
	-@erase "$(OUTDIR)\bufferd.ext"
	-@erase "$(OUTDIR)\bufferd.ilk"
	-@erase "$(OUTDIR)\bufferd.lib"
	-@erase "..\..\TRIAS\TRIAS32D\bufferd.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

.\WinDebug\BUFFER.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_11_USED__" /Fr /Fp"WinDebug/BUFFERD.pch" /Yu"bufferp.hxx" /Fd"WinDebug/BUFFERD.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D\
 "MSWIND" /D "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/BUFFERD.pch"\
 /Yu"bufferp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/BUFFERD.pdb" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i "..\z_hxx" /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Buffer.res" /i "..\z_hxx" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Buffer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BUFF_EIN.SBR" \
	"$(INTDIR)\BUFFER.SBR" \
	"$(INTDIR)\Buffering.sbr" \
	"$(INTDIR)\BUFFERP.SBR" \
	"$(INTDIR)\Buffext.sbr"

"$(OUTDIR)\Buffer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 geometd.lib ixtatd42.lib stdcppd.lib tfrm32d.lib cont32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib triastld.lib /nologo /dll /debug /machine:I386 /out:"WinDebug\bufferd.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=geometd.lib ixtatd42.lib stdcppd.lib tfrm32d.lib cont32d.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib\
 triastld.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)/bufferd.pdb" /debug\
 /machine:I386 /def:".\BUFFER.DEF" /out:"$(OUTDIR)/bufferd.ext"\
 /implib:"$(OUTDIR)/bufferd.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\BUFFER.DEF"
LINK32_OBJS= \
	"$(INTDIR)\BUFF_EIN.OBJ" \
	"$(INTDIR)\BUFFER.OBJ" \
	"$(INTDIR)\Buffer.res" \
	"$(INTDIR)\Buffering.obj" \
	"$(INTDIR)\BUFFERP.OBJ" \
	"$(INTDIR)\Buffext.obj"

"$(OUTDIR)\bufferd.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinDebug\bufferd.ext
TargetName=bufferd
InputPath=.\WinDebug\bufferd.ext
SOURCE=$(InputPath)

"D:\TRIAS\TRIAS32D\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" D:\TRIAS\TRIAS32D

# End Custom Build

!ELSEIF  "$(CFG)" == "Buffer - Win32 ReleaseDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Buffer__"
# PROP BASE Intermediate_Dir "Buffer__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRelDebug"
# PROP Intermediate_Dir "WinRelDebug"
# PROP Target_Dir ""
OUTDIR=.\WinRelDebug
INTDIR=.\WinRelDebug
# Begin Custom Macros
TargetName=buffer
# End Custom Macros

ALL : "$(OUTDIR)\buffer.ext" "C:\TRIAS\TRIAS32R\buffer.ext"

CLEAN : 
	-@erase "$(INTDIR)\BUFF_EIN.OBJ"
	-@erase "$(INTDIR)\BUFFER.OBJ"
	-@erase "$(INTDIR)\Buffer.pch"
	-@erase "$(INTDIR)\Buffer.res"
	-@erase "$(INTDIR)\Buffering.obj"
	-@erase "$(INTDIR)\BUFFERP.OBJ"
	-@erase "$(INTDIR)\Buffext.obj"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\buffer.exp"
	-@erase "$(OUTDIR)\buffer.ext"
	-@erase "$(OUTDIR)\buffer.lib"
	-@erase "$(OUTDIR)\buffer.pdb"
	-@erase "C:\TRIAS\TRIAS32R\buffer.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\z_hxx" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_11_USED__" /Yu"bufferp.hxx" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /I "..\z_hxx" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "QI_EXCEPTION" /D "__ATL_11_USED__" /Yu"bufferp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /GX /Zi /O1 /I "..\z_hxx" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D\
 "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /Fp"$(INTDIR)/Buffer.pch" /Yu"bufferp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinRelDebug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /i "..\z_hxx" /d "NDEBUG"
# ADD RSC /l 0x407 /i "..\z_hxx" /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/Buffer.res" /i "..\z_hxx" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Buffer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 geometr.lib ixtatr42.lib stdcppr.lib tfrmwork.lib cont32r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib triastlb.lib /nologo /dll /machine:I386 /out:"WinRel/buffer.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 geometr.lib ixtatr42.lib stdcppr.lib tfrmwork.lib cont32r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib triastlb.lib /nologo /dll /debug /machine:I386 /out:"WinRelDebug/buffer.ext" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=geometr.lib ixtatr42.lib stdcppr.lib tfrmwork.lib cont32r.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib\
 triastlb.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)/buffer.pdb" /debug\
 /machine:I386 /def:".\BUFFER.DEF" /out:"$(OUTDIR)/buffer.ext"\
 /implib:"$(OUTDIR)/buffer.lib" /SUBSYSTEM:windows,4.0 
DEF_FILE= \
	".\BUFFER.DEF"
LINK32_OBJS= \
	"$(INTDIR)\BUFF_EIN.OBJ" \
	"$(INTDIR)\BUFFER.OBJ" \
	"$(INTDIR)\Buffer.res" \
	"$(INTDIR)\Buffering.obj" \
	"$(INTDIR)\BUFFERP.OBJ" \
	"$(INTDIR)\Buffext.obj"

"$(OUTDIR)\buffer.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\WinRelDebug\buffer.ext
TargetName=buffer
InputPath=.\WinRelDebug\buffer.ext
SOURCE=$(InputPath)

"C:\TRIAS\TRIAS32R\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" C:\TRIAS\TRIAS32R

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

# Name "Buffer - Win32 Release"
# Name "Buffer - Win32 Debug"
# Name "Buffer - Win32 ReleaseDebug"

!IF  "$(CFG)" == "Buffer - Win32 Release"

!ELSEIF  "$(CFG)" == "Buffer - Win32 Debug"

!ELSEIF  "$(CFG)" == "Buffer - Win32 ReleaseDebug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\BUFFERP.CXX
DEP_CPP_BUFFE=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\identlst.hxx"\
	"..\z_hxx\objgext.hxx"\
	".\Buff_ein.hxx"\
	".\BufferConfig.h"\
	".\BUFFERM.HXX"\
	".\Bufferp.hxx"\
	".\Bufkonst.hxx"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLIMPL.CPP"\
	{$(INCLUDE)}"\Atlimpl11.h"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	

!IF  "$(CFG)" == "Buffer - Win32 Release"

# ADD CPP /Yc"bufferp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /I "..\z_hxx" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D\
 "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /Fp"$(INTDIR)/Buffer.pch" /Yc"bufferp.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\BUFFERP.OBJ" : $(SOURCE) $(DEP_CPP_BUFFE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Buffer.pch" : $(SOURCE) $(DEP_CPP_BUFFE) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Buffer - Win32 Debug"

# ADD CPP /Yc"bufferp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /I "..\z_hxx" /D "_DEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D\
 "MSWIND" /D "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/BUFFERD.pch"\
 /Yc"bufferp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/BUFFERD.pdb" /c $(SOURCE) \
	

"$(INTDIR)\BUFFERP.OBJ" : $(SOURCE) $(DEP_CPP_BUFFE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\BUFFERP.SBR" : $(SOURCE) $(DEP_CPP_BUFFE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\BUFFERD.pch" : $(SOURCE) $(DEP_CPP_BUFFE) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Buffer - Win32 ReleaseDebug"

# ADD BASE CPP /Yc"bufferp.hxx"
# ADD CPP /Yc"bufferp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /Zi /O1 /I "..\z_hxx" /D "NDEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "STRICT" /D "DLL" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D\
 "MSCC8" /D "__CV__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D\
 "QI_EXCEPTION" /D "__ATL_11_USED__" /Fp"$(INTDIR)/Buffer.pch" /Yc"bufferp.hxx"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\BUFFERP.OBJ" : $(SOURCE) $(DEP_CPP_BUFFE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Buffer.pch" : $(SOURCE) $(DEP_CPP_BUFFE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BUFFER.CXX

!IF  "$(CFG)" == "Buffer - Win32 Release"

DEP_CPP_BUFFER=\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\GeomDLL.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\progstat.h"\
	".\..\..\..\Triasdev.Mvc\INCLUDE\RESSTRG.H"\
	".\Buffer.hxx"\
	".\BufferConfig.h"\
	".\Bufferp.hxx"\
	".\version.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
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
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\BUFFER.OBJ" : $(SOURCE) $(DEP_CPP_BUFFER) "$(INTDIR)"\
 "$(INTDIR)\Buffer.pch"


!ELSEIF  "$(CFG)" == "Buffer - Win32 Debug"

DEP_CPP_BUFFER=\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\GeomDLL.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgguid.h"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\reinguid.h"\
	".\..\..\..\Triasdev.Mvc\INCLUDE\RESSTRG.H"\
	".\Buffer.hxx"\
	".\BufferConfig.h"\
	".\Bufferp.hxx"\
	".\Buffguid.h"\
	".\SmartInterfaces.h"\
	".\version.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
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
	

"$(INTDIR)\BUFFER.OBJ" : $(SOURCE) $(DEP_CPP_BUFFER) "$(INTDIR)"\
 "$(INTDIR)\BUFFERD.pch"

"$(INTDIR)\BUFFER.SBR" : $(SOURCE) $(DEP_CPP_BUFFER) "$(INTDIR)"\
 "$(INTDIR)\BUFFERD.pch"


!ELSEIF  "$(CFG)" == "Buffer - Win32 ReleaseDebug"

DEP_CPP_BUFFER=\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\GeomDLL.hxx"\
	"..\z_hxx\geotrias.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgguid.h"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\reinguid.h"\
	".\..\..\..\Triasdev.Mvc\INCLUDE\RESSTRG.H"\
	".\Buffer.hxx"\
	".\BufferConfig.h"\
	".\Bufferp.hxx"\
	".\Buffguid.h"\
	".\SmartInterfaces.h"\
	".\version.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
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
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stream\hmacros.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\BUFFER.OBJ" : $(SOURCE) $(DEP_CPP_BUFFER) "$(INTDIR)"\
 "$(INTDIR)\Buffer.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BUFF_EIN.CXX

!IF  "$(CFG)" == "Buffer - Win32 Release"

DEP_CPP_BUFF_=\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgguid.h"\
	"..\z_hxx\reinguid.h"\
	".\BufferConfig.h"\
	".\Bufferp.hxx"\
	".\Buffguid.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\BUFF_EIN.OBJ" : $(SOURCE) $(DEP_CPP_BUFF_) "$(INTDIR)"\
 "$(INTDIR)\Buffer.pch"


!ELSEIF  "$(CFG)" == "Buffer - Win32 Debug"

DEP_CPP_BUFF_=\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgguid.h"\
	"..\z_hxx\reinguid.h"\
	".\BufferConfig.h"\
	".\Bufferp.hxx"\
	".\Buffguid.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\BUFF_EIN.OBJ" : $(SOURCE) $(DEP_CPP_BUFF_) "$(INTDIR)"\
 "$(INTDIR)\BUFFERD.pch"

"$(INTDIR)\BUFF_EIN.SBR" : $(SOURCE) $(DEP_CPP_BUFF_) "$(INTDIR)"\
 "$(INTDIR)\BUFFERD.pch"


!ELSEIF  "$(CFG)" == "Buffer - Win32 ReleaseDebug"

DEP_CPP_BUFF_=\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgguid.h"\
	"..\z_hxx\reinguid.h"\
	".\BufferConfig.h"\
	".\Bufferp.hxx"\
	".\Buffguid.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\BUFF_EIN.OBJ" : $(SOURCE) $(DEP_CPP_BUFF_) "$(INTDIR)"\
 "$(INTDIR)\Buffer.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Buffext.cxx

!IF  "$(CFG)" == "Buffer - Win32 Release"

DEP_CPP_BUFFEX=\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\objgext.hxx"\
	"..\z_hxx\objgguid.h"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\reinguid.h"\
	".\..\..\..\Triasdev.Mvc\INCLUDE\RESSTRG.H"\
	".\Buffer.hxx"\
	".\BufferConfig.h"\
	".\Bufferp.hxx"\
	".\Buffguid.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\Buffext.obj" : $(SOURCE) $(DEP_CPP_BUFFEX) "$(INTDIR)"\
 "$(INTDIR)\Buffer.pch"


!ELSEIF  "$(CFG)" == "Buffer - Win32 Debug"

DEP_CPP_BUFFEX=\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\objgext.hxx"\
	".\..\..\..\Triasdev.Mvc\INCLUDE\RESSTRG.H"\
	".\Buffer.hxx"\
	".\Bufferp.hxx"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	

"$(INTDIR)\Buffext.obj" : $(SOURCE) $(DEP_CPP_BUFFEX) "$(INTDIR)"\
 "$(INTDIR)\BUFFERD.pch"

"$(INTDIR)\Buffext.sbr" : $(SOURCE) $(DEP_CPP_BUFFEX) "$(INTDIR)"\
 "$(INTDIR)\BUFFERD.pch"


!ELSEIF  "$(CFG)" == "Buffer - Win32 ReleaseDebug"

DEP_CPP_BUFFEX=\
	"..\z_hxx\ctfx.hxx"\
	"..\z_hxx\ctfxmfc.h"\
	"..\z_hxx\datbank.hxx"\
	"..\z_hxx\errcodes.hxx"\
	"..\z_hxx\FormatString.hxx"\
	"..\z_hxx\geo_obj.hxx"\
	"..\z_hxx\geokonst.hxx"\
	"..\z_hxx\GeometrM.hxx"\
	"..\z_hxx\identlst.hxx"\
	"..\z_hxx\objgext.hxx"\
	"..\z_hxx\objgguid.h"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\reinguid.h"\
	".\..\..\..\Triasdev.Mvc\INCLUDE\RESSTRG.H"\
	".\Buff_ein.hxx"\
	".\Buffer.hxx"\
	".\BufferConfig.h"\
	".\BUFFERM.HXX"\
	".\Bufferp.hxx"\
	".\Buffguid.h"\
	".\Bufkonst.hxx"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\ATL11.H"\
	{$(INCLUDE)}"\ATLBASE.H"\
	{$(INCLUDE)}"\ATLCOM.H"\
	{$(INCLUDE)}"\ATLCOMX.H"\
	{$(INCLUDE)}"\ATLUTIL.H"\
	{$(INCLUDE)}"\Basetsd.h"\
	{$(INCLUDE)}"\BOOL.H"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\COPTTREE.HXX"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\ctfm.hxx"\
	{$(INCLUDE)}"\CTRLINES.HXX"\
	{$(INCLUDE)}"\CTRTYPES.HXX"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\dblnumex.hxx"\
	{$(INCLUDE)}"\DBLPAIR.HXX"\
	{$(INCLUDE)}"\DEFINES.HPP"\
	{$(INCLUDE)}"\dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\ERRINSTX.HXX"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\FREESTOR.HXX"\
	{$(INCLUDE)}"\Gc.h"\
	{$(INCLUDE)}"\GC_CPP.H"\
	{$(INCLUDE)}"\GEO_INL.HXX"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\numeditx.hxx"\
	{$(INCLUDE)}"\OBJCONTX.HXX"\
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
	{$(INCLUDE)}"\PRINT.H"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\TASSERT.HXX"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	{$(INCLUDE)}"\TSTRING.HPP"\
	{$(INCLUDE)}"\xtencatl.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\xtsnaux.hxx"\
	{$(INCLUDE)}"\xtsnguid.h"\
	{$(INCLUDE)}"\YXVALS.H"\
	

"$(INTDIR)\Buffext.obj" : $(SOURCE) $(DEP_CPP_BUFFEX) "$(INTDIR)"\
 "$(INTDIR)\Buffer.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Buffering.cxx

!IF  "$(CFG)" == "Buffer - Win32 Release"

DEP_CPP_BUFFERI=\
	"..\z_hxx\BasicFunctions.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgguid.h"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\reinguid.h"\
	"..\z_hxx\strecke.hxx"\
	".\Buffer.hxx"\
	".\BufferConfig.h"\
	".\Bufferp.hxx"\
	".\Buffguid.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\Buffering.obj" : $(SOURCE) $(DEP_CPP_BUFFERI) "$(INTDIR)"\
 "$(INTDIR)\Buffer.pch"


!ELSEIF  "$(CFG)" == "Buffer - Win32 Debug"

DEP_CPP_BUFFERI=\
	"..\z_hxx\BasicFunctions.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgguid.h"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\reinguid.h"\
	"..\z_hxx\strecke.hxx"\
	".\Buffer.hxx"\
	".\BufferConfig.h"\
	".\Bufferp.hxx"\
	".\Buffguid.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\stl\iterator.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\Buffering.obj" : $(SOURCE) $(DEP_CPP_BUFFERI) "$(INTDIR)"\
 "$(INTDIR)\BUFFERD.pch"

"$(INTDIR)\Buffering.sbr" : $(SOURCE) $(DEP_CPP_BUFFERI) "$(INTDIR)"\
 "$(INTDIR)\BUFFERD.pch"


!ELSEIF  "$(CFG)" == "Buffer - Win32 ReleaseDebug"

DEP_CPP_BUFFERI=\
	"..\z_hxx\BasicFunctions.hxx"\
	"..\z_hxx\ErrorCorrection.hxx"\
	"..\z_hxx\koord.hxx"\
	"..\z_hxx\objgguid.h"\
	"..\z_hxx\ProgressProxy.h"\
	"..\z_hxx\progstat.h"\
	"..\z_hxx\reinguid.h"\
	"..\z_hxx\strecke.hxx"\
	".\Buffer.hxx"\
	".\BufferConfig.h"\
	".\Bufferp.hxx"\
	".\Buffguid.h"\
	".\SmartInterfaces.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\ospace\config.h"\
	{$(INCLUDE)}"\ospace\std\string"\
	{$(INCLUDE)}"\ospace\stl\config.h"\
	{$(INCLUDE)}"\ospace\string\basic.h"\
	{$(INCLUDE)}"\ospace\string\config.h"\
	{$(INCLUDE)}"\ospace\string\string.h"\
	{$(INCLUDE)}"\ospace\string\traits.cc"\
	{$(INCLUDE)}"\ospace\string\traits.h"\
	{$(INCLUDE)}"\ospace\type\prim.h"\
	{$(INCLUDE)}"\ospace\utility\memory.h"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TSTRING"\
	

"$(INTDIR)\Buffering.obj" : $(SOURCE) $(DEP_CPP_BUFFERI) "$(INTDIR)"\
 "$(INTDIR)\Buffer.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BUFFER.DEF

!IF  "$(CFG)" == "Buffer - Win32 Release"

!ELSEIF  "$(CFG)" == "Buffer - Win32 Debug"

!ELSEIF  "$(CFG)" == "Buffer - Win32 ReleaseDebug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Buffer.rc
DEP_RSC_BUFFER_=\
	".\..\..\..\Triasdev.Mvc\INCLUDE\RESSTRG.H"\
	".\BUFFER.RCV"\
	

!IF  "$(CFG)" == "Buffer - Win32 Release"


"$(INTDIR)\Buffer.res" : $(SOURCE) $(DEP_RSC_BUFFER_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Buffer - Win32 Debug"


"$(INTDIR)\Buffer.res" : $(SOURCE) $(DEP_RSC_BUFFER_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Buffer - Win32 ReleaseDebug"


"$(INTDIR)\Buffer.res" : $(SOURCE) $(DEP_RSC_BUFFER_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
