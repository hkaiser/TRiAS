# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Attr32 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Attr32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Attr32 - Win32 Release" && "$(CFG)" != "Attr32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Attr32.mak" CFG="Attr32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Attr32 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Attr32 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "Attr32 - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Attr32 - Win32 Release"

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
TargetName=Attribut
# End Custom Macros

ALL : "$(OUTDIR)\Attribut.ext" "c:\trias\trias200\trias\Attribut.ext"

CLEAN : 
	-@erase "$(INTDIR)\Asorge.obj"
	-@erase "$(INTDIR)\ATTINFO.OBJ"
	-@erase "$(INTDIR)\Attr32.pch"
	-@erase "$(INTDIR)\ATTR32.res"
	-@erase "$(INTDIR)\ATTRIBP.OBJ"
	-@erase "$(INTDIR)\ATTRIBUT.OBJ"
	-@erase "$(INTDIR)\Attrifce.obj"
	-@erase "$(INTDIR)\AUSWAHL.OBJ"
	-@erase "$(INTDIR)\BILDEN.OBJ"
	-@erase "$(INTDIR)\Clstree.obj"
	-@erase "$(INTDIR)\ERBEN.OBJ"
	-@erase "$(INTDIR)\IDKEY.OBJ"
	-@erase "$(INTDIR)\MWERTE.OBJ"
	-@erase "$(INTDIR)\OBJKEY.OBJ"
	-@erase "$(INTDIR)\Osorge.obj"
	-@erase "$(INTDIR)\STOHWND.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\TXTEDIT.OBJ"
	-@erase "$(OUTDIR)\Attribut.exp"
	-@erase "$(OUTDIR)\Attribut.ext"
	-@erase "$(OUTDIR)\Attribut.ilk"
	-@erase "$(OUTDIR)\Attribut.lib"
	-@erase "c:\trias\trias200\trias\Attribut.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /Yu"attribp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32"\
 /Fp"$(INTDIR)/Attr32.pch" /Yu"attribp.hxx" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/ATTR32.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Attr32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtnsr42.lib cont32r.lib tfrmwork.lib stdcppr.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /machine:I386 /out:"WinRel/Attribut.ext"
LINK32_FLAGS=ixtnsr42.lib cont32r.lib tfrmwork.lib stdcppr.lib winmm.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/Attribut.pdb"\
 /machine:I386 /def:".\ATTR32.DEF" /out:"$(OUTDIR)/Attribut.ext"\
 /implib:"$(OUTDIR)/Attribut.lib" 
DEF_FILE= \
	".\ATTR32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\Asorge.obj" \
	"$(INTDIR)\ATTINFO.OBJ" \
	"$(INTDIR)\ATTR32.res" \
	"$(INTDIR)\ATTRIBP.OBJ" \
	"$(INTDIR)\ATTRIBUT.OBJ" \
	"$(INTDIR)\Attrifce.obj" \
	"$(INTDIR)\AUSWAHL.OBJ" \
	"$(INTDIR)\BILDEN.OBJ" \
	"$(INTDIR)\Clstree.obj" \
	"$(INTDIR)\ERBEN.OBJ" \
	"$(INTDIR)\IDKEY.OBJ" \
	"$(INTDIR)\MWERTE.OBJ" \
	"$(INTDIR)\OBJKEY.OBJ" \
	"$(INTDIR)\Osorge.obj" \
	"$(INTDIR)\STOHWND.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\TXTEDIT.OBJ"

"$(OUTDIR)\Attribut.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copyint Target to Destination...
TargetPath=.\WinRel\Attribut.ext
TargetName=Attribut
InputPath=.\WinRel\Attribut.ext
SOURCE=$(InputPath)

"c:\trias\trias200\trias\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" c:\trias\trias200\trias

# End Custom Build

!ELSEIF  "$(CFG)" == "Attr32 - Win32 Debug"

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
TargetName=attribud
# End Custom Macros

ALL : "$(OUTDIR)\attribud.ext" "..\..\..\..\trias\trias200\attribud.ext"

CLEAN : 
	-@erase "$(INTDIR)\Asorge.obj"
	-@erase "$(INTDIR)\ATTINFO.OBJ"
	-@erase "$(INTDIR)\Attr32.pch"
	-@erase "$(INTDIR)\ATTR32.res"
	-@erase "$(INTDIR)\ATTRIBP.OBJ"
	-@erase "$(INTDIR)\ATTRIBUT.OBJ"
	-@erase "$(INTDIR)\Attrifce.obj"
	-@erase "$(INTDIR)\AUSWAHL.OBJ"
	-@erase "$(INTDIR)\BILDEN.OBJ"
	-@erase "$(INTDIR)\Clstree.obj"
	-@erase "$(INTDIR)\ERBEN.OBJ"
	-@erase "$(INTDIR)\IDKEY.OBJ"
	-@erase "$(INTDIR)\MWERTE.OBJ"
	-@erase "$(INTDIR)\OBJKEY.OBJ"
	-@erase "$(INTDIR)\Osorge.obj"
	-@erase "$(INTDIR)\STOHWND.OBJ"
	-@erase "$(INTDIR)\STRUTIL.OBJ"
	-@erase "$(INTDIR)\TXTEDIT.OBJ"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\attribud.exp"
	-@erase "$(OUTDIR)\attribud.ext"
	-@erase "$(OUTDIR)\attribud.ilk"
	-@erase "$(OUTDIR)\attribud.lib"
	-@erase "$(OUTDIR)\attribud.pdb"
	-@erase "..\..\..\..\trias\trias200\attribud.ext"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /GX /Zi /Od /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32" /Yu"attribp.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W3 /WX /GX /Zi /Od /D "WIN32" /D "_WINDOWS" /D "STRICT"\
 /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__"\
 /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32"\
 /Fp"$(INTDIR)/Attr32.pch" /Yu"attribp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i ".." /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/ATTR32.res" /i ".." /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Attr32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtnsd42.lib cont32d.lib tfrm32d.lib stdcppd.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"WinDebug/attribud.ext"
LINK32_FLAGS=ixtnsd42.lib cont32d.lib tfrm32d.lib stdcppd.lib winmm.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)/attribud.pdb" /debug\
 /machine:I386 /def:".\ATTR32.DEF" /out:"$(OUTDIR)/attribud.ext"\
 /implib:"$(OUTDIR)/attribud.lib" 
DEF_FILE= \
	".\ATTR32.DEF"
LINK32_OBJS= \
	"$(INTDIR)\Asorge.obj" \
	"$(INTDIR)\ATTINFO.OBJ" \
	"$(INTDIR)\ATTR32.res" \
	"$(INTDIR)\ATTRIBP.OBJ" \
	"$(INTDIR)\ATTRIBUT.OBJ" \
	"$(INTDIR)\Attrifce.obj" \
	"$(INTDIR)\AUSWAHL.OBJ" \
	"$(INTDIR)\BILDEN.OBJ" \
	"$(INTDIR)\Clstree.obj" \
	"$(INTDIR)\ERBEN.OBJ" \
	"$(INTDIR)\IDKEY.OBJ" \
	"$(INTDIR)\MWERTE.OBJ" \
	"$(INTDIR)\OBJKEY.OBJ" \
	"$(INTDIR)\Osorge.obj" \
	"$(INTDIR)\STOHWND.OBJ" \
	"$(INTDIR)\STRUTIL.OBJ" \
	"$(INTDIR)\TXTEDIT.OBJ"

"$(OUTDIR)\attribud.ext" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copyint Target to Destination...
TargetPath=.\WinDebug\attribud.ext
TargetName=attribud
InputPath=.\WinDebug\attribud.ext
SOURCE=$(InputPath)

"d:\trias\trias200\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   copy "$(TargetPath)" d:\trias\trias200

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

# Name "Attr32 - Win32 Release"
# Name "Attr32 - Win32 Debug"

!IF  "$(CFG)" == "Attr32 - Win32 Release"

!ELSEIF  "$(CFG)" == "Attr32 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.CXX
DEP_CPP_ATTRI=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTINFO.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRGUID.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\AUSWAHL.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\BILDEN.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\DEFINE.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ERBEN.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\IDKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\MWERTE.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\OBJKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\STOHWND.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\TXTEDIT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\VERSIO16.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\VERSION.H"\
	".\..\clstree.hxx"\
	".\Versio32.h"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bscrguid.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eb.h"\
	{$(INCLUDE)}"\Eboem.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Oleguid.h"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trelguid.h"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\TRiASHelper.h"\
	{$(INCLUDE)}"\TRiASHelper_i.c"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnaux.hxx"\
	{$(INCLUDE)}"\Xtsnguid.h"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_ATTRI=\
	"..\..\..\INCLUDE\dc.h"\
	

"$(INTDIR)\ATTRIBUT.OBJ" : $(SOURCE) $(DEP_CPP_ATTRI) "$(INTDIR)"\
 "$(INTDIR)\Attr32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTINFO.CXX
DEP_CPP_ATTIN=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTINFO.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\DEFINE.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\IDKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\OBJKEY.HXX"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\ATTINFO.OBJ" : $(SOURCE) $(DEP_CPP_ATTIN) "$(INTDIR)"\
 "$(INTDIR)\Attr32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\ATTRIBUT\TXTEDIT.CXX
DEP_CPP_TXTED=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\DEFINE.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\TXTEDIT.HXX"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\TXTEDIT.OBJ" : $(SOURCE) $(DEP_CPP_TXTED) "$(INTDIR)"\
 "$(INTDIR)\Attr32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\ATTRIBUT\OBJKEY.CXX
DEP_CPP_OBJKE=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\DEFINE.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\IDKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\OBJKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\STOHWND.HXX"\
	".\..\clstree.hxx"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bscrguid.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eb.h"\
	{$(INCLUDE)}"\Eboem.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Oleguid.h"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnaux.hxx"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_OBJKE=\
	"..\..\..\INCLUDE\dc.h"\
	

"$(INTDIR)\OBJKEY.OBJ" : $(SOURCE) $(DEP_CPP_OBJKE) "$(INTDIR)"\
 "$(INTDIR)\Attr32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\ATTRIBUT\STOHWND.CXX
DEP_CPP_STOHW=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\DEFINE.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\IDKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\OBJKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\STOHWND.HXX"\
	".\..\clstree.hxx"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bscrguid.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eb.h"\
	{$(INCLUDE)}"\Eboem.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_STOHW=\
	"..\..\..\INCLUDE\dc.h"\
	

"$(INTDIR)\STOHWND.OBJ" : $(SOURCE) $(DEP_CPP_STOHW) "$(INTDIR)"\
 "$(INTDIR)\Attr32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\ATTRIBUT\AUSWAHL.CXX
DEP_CPP_AUSWA=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\AUSWAHL.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\DEFINE.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\IDKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\OBJKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\STOHWND.HXX"\
	".\..\clstree.hxx"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bscrguid.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eb.h"\
	{$(INCLUDE)}"\Eboem.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_AUSWA=\
	"..\..\..\INCLUDE\dc.h"\
	

"$(INTDIR)\AUSWAHL.OBJ" : $(SOURCE) $(DEP_CPP_AUSWA) "$(INTDIR)"\
 "$(INTDIR)\Attr32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\ATTRIBUT\BILDEN.CXX
DEP_CPP_BILDE=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\BILDEN.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\DEFINE.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\IDKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\OBJKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\STOHWND.HXX"\
	".\..\clstree.hxx"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bscrguid.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eb.h"\
	{$(INCLUDE)}"\Eboem.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Oleguid.h"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnaux.hxx"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_BILDE=\
	"..\..\..\INCLUDE\dc.h"\
	

"$(INTDIR)\BILDEN.OBJ" : $(SOURCE) $(DEP_CPP_BILDE) "$(INTDIR)"\
 "$(INTDIR)\Attr32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\ATTRIBUT\STRUTIL.CXX
DEP_CPP_STRUT=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.H"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	

"$(INTDIR)\STRUTIL.OBJ" : $(SOURCE) $(DEP_CPP_STRUT) "$(INTDIR)"\
 "$(INTDIR)\Attr32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\ATTRIBUT\ERBEN.CXX
DEP_CPP_ERBEN=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\DEFINE.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ERBEN.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\IDKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\OBJKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\STOHWND.HXX"\
	".\..\clstree.hxx"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bscrguid.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eb.h"\
	{$(INCLUDE)}"\Eboem.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Oleguid.h"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnaux.hxx"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_ERBEN=\
	"..\..\..\INCLUDE\dc.h"\
	

"$(INTDIR)\ERBEN.OBJ" : $(SOURCE) $(DEP_CPP_ERBEN) "$(INTDIR)"\
 "$(INTDIR)\Attr32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\ATTRIBUT\IDKEY.CXX
DEP_CPP_IDKEY=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\DEFINE.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\IDKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\OBJKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\STOHWND.HXX"\
	".\..\clstree.hxx"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bscrguid.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eb.h"\
	{$(INCLUDE)}"\Eboem.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_IDKEY=\
	"..\..\..\INCLUDE\dc.h"\
	

"$(INTDIR)\IDKEY.OBJ" : $(SOURCE) $(DEP_CPP_IDKEY) "$(INTDIR)"\
 "$(INTDIR)\Attr32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.CXX

!IF  "$(CFG)" == "Attr32 - Win32 Release"

DEP_CPP_ATTRIB=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlimpl.cpp"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Atlimpl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
# ADD CPP /Yc"attribp.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D\
 "__XTENSNDLL__" /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32"\
 /Fp"$(INTDIR)/Attr32.pch" /Yc"attribp.hxx" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\ATTRIBP.OBJ" : $(SOURCE) $(DEP_CPP_ATTRIB) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Attr32.pch" : $(SOURCE) $(DEP_CPP_ATTRIB) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Attr32 - Win32 Debug"

DEP_CPP_ATTRIB=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlimpl.cpp"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Atlimpl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
# ADD CPP /W3 /Yc"attribp.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /GX /Zi /Od /D "WIN32" /D "_WINDOWS" /D "STRICT"\
 /D "DLL" /D "MSWIND" /D "__CV__" /D "__XT" /D "__DEXPROCS" /D "__XTENSNDLL__"\
 /D "__ATL_USED__" /D "OS_NO_STREAM_SUPPORT" /D "EBWIN32"\
 /Fp"$(INTDIR)/Attr32.pch" /Yc"attribp.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\ATTRIBP.OBJ" : $(SOURCE) $(DEP_CPP_ATTRIB) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Attr32.pch" : $(SOURCE) $(DEP_CPP_ATTRIB) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\XTENSION\ATTRIBUT\MWERTE.CXX
DEP_CPP_MWERT=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\DEFINE.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ERBEN.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\IDKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\MWERTE.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\OBJKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\STOHWND.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\TXTEDIT.HXX"\
	".\..\clstree.hxx"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bscrguid.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eb.h"\
	{$(INCLUDE)}"\Eboem.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Oleguid.h"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnaux.hxx"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_MWERT=\
	"..\..\..\INCLUDE\dc.h"\
	

"$(INTDIR)\MWERTE.OBJ" : $(SOURCE) $(DEP_CPP_MWERT) "$(INTDIR)"\
 "$(INTDIR)\Attr32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ATTR32.RC
DEP_RSC_ATTR3=\
	".\about.h"\
	".\ABOUT.SRC"\
	".\ATTR32.RCV"\
	".\attribut.h"\
	".\LUPE.ICO"\
	{$(INCLUDE)}"\RESSTRG.H"\
	

"$(INTDIR)\ATTR32.res" : $(SOURCE) $(DEP_RSC_ATTR3) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ATTR32.DEF

!IF  "$(CFG)" == "Attr32 - Win32 Release"

!ELSEIF  "$(CFG)" == "Attr32 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Attribut\Clstree.cxx
DEP_CPP_CLSTR=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\DEFINE.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\IDKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\OBJKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\STOHWND.HXX"\
	".\..\clstree.hxx"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bscrguid.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eb.h"\
	{$(INCLUDE)}"\Eboem.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_CLSTR=\
	"..\..\..\INCLUDE\dc.h"\
	

"$(INTDIR)\Clstree.obj" : $(SOURCE) $(DEP_CPP_CLSTR) "$(INTDIR)"\
 "$(INTDIR)\Attr32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Attribut\Asorge.cxx
DEP_CPP_ASORG=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTINFO.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\AUSWAHL.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\BILDEN.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\DEFINE.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ERBEN.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\IDKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\MWERTE.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\OBJKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\STOHWND.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\TXTEDIT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\VERSIO16.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\VERSION.H"\
	".\..\clstree.hxx"\
	".\Versio32.h"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bscrguid.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eb.h"\
	{$(INCLUDE)}"\Eboem.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Oleguid.h"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnaux.hxx"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_ASORG=\
	"..\..\..\INCLUDE\dc.h"\
	

"$(INTDIR)\Asorge.obj" : $(SOURCE) $(DEP_CPP_ASORG) "$(INTDIR)"\
 "$(INTDIR)\Attr32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Attribut\Osorge.cxx
DEP_CPP_OSORG=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTINFO.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\AUSWAHL.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\BILDEN.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\DEFINE.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ERBEN.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\IDKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\MWERTE.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\OBJKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\STOHWND.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\TXTEDIT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\VERSIO16.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\VERSION.H"\
	".\..\clstree.hxx"\
	".\Versio32.h"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bscrguid.h"\
	{$(INCLUDE)}"\Clipbrd.hxx"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eb.h"\
	{$(INCLUDE)}"\Eboem.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Itriasap.h"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_OSORG=\
	"..\..\..\INCLUDE\dc.h"\
	

"$(INTDIR)\Osorge.obj" : $(SOURCE) $(DEP_CPP_OSORG) "$(INTDIR)"\
 "$(INTDIR)\Attr32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Triasdev.mvc\Xtension\Attribut\Attrifce.cxx

!IF  "$(CFG)" == "Attr32 - Win32 Release"

DEP_CPP_ATTRIF=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTINFO.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\AUSWAHL.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\BILDEN.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\DEFINE.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ERBEN.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\IDKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\MWERTE.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\OBJKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\STOHWND.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\TXTEDIT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\VERSIO16.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\VERSION.H"\
	".\..\clstree.hxx"\
	".\Versio32.h"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bscrguid.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eb.h"\
	{$(INCLUDE)}"\Eboem.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Itriasap.h"\
	{$(INCLUDE)}"\Iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Oleguid.h"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trelguid.h"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Undoguid.h"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnguid.h"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_ATTRIF=\
	"..\..\..\INCLUDE\dc.h"\
	

"$(INTDIR)\Attrifce.obj" : $(SOURCE) $(DEP_CPP_ATTRIF) "$(INTDIR)"\
 "$(INTDIR)\Attr32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Attr32 - Win32 Debug"

DEP_CPP_ATTRIF=\
	"..\..\..\..\Cv32.mvc\Include\Gc.h"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ABOUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTINFO.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBP.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ATTRIBUT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\AUSWAHL.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\BILDEN.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\DEFINE.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\ERBEN.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\IDKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\MWERTE.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\OBJKEY.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\STOHWND.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\TXTEDIT.HXX"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\VERSIO16.H"\
	".\..\..\..\..\TRIASDEV.MVC\XTENSION\ATTRIBUT\VERSION.H"\
	".\..\clstree.hxx"\
	".\Versio32.h"\
	"C:\Msdev\Atl11\Include\Atlbase.h"\
	"C:\Msdev\Atl11\Include\Atlcom.h"\
	"C:\Msdev\Atl11\Include\Atlcomx.h"\
	"C:\Msdev\Atl11\Include\Atlutil.h"\
	{$(INCLUDE)}"\Atl11.h"\
	{$(INCLUDE)}"\Bool.h"\
	{$(INCLUDE)}"\Bscrguid.h"\
	{$(INCLUDE)}"\Commonvu.hxx"\
	{$(INCLUDE)}"\Containr.hxx"\
	{$(INCLUDE)}"\Ctf.h"\
	{$(INCLUDE)}"\Ctfm.hxx"\
	{$(INCLUDE)}"\Ctfx.hxx"\
	{$(INCLUDE)}"\Ctrlines.hxx"\
	{$(INCLUDE)}"\Ctrtypes.hxx"\
	{$(INCLUDE)}"\Cv_defs.h"\
	{$(INCLUDE)}"\Cv_types.hxx"\
	{$(INCLUDE)}"\Cvinline.hxx"\
	{$(INCLUDE)}"\Cxxtypes.hxx"\
	{$(INCLUDE)}"\Dblnumex.hxx"\
	{$(INCLUDE)}"\Dblpair.hxx"\
	{$(INCLUDE)}"\Defines.hpp"\
	{$(INCLUDE)}"\Dirisole.h"\
	{$(INCLUDE)}"\Dllbindx.hxx"\
	{$(INCLUDE)}"\Eb.h"\
	{$(INCLUDE)}"\Eboem.h"\
	{$(INCLUDE)}"\Eieruhr.hxx"\
	{$(INCLUDE)}"\Eonrguid.h"\
	{$(INCLUDE)}"\Errcodes.hxx"\
	{$(INCLUDE)}"\Errinstx.hxx"\
	{$(INCLUDE)}"\Exceptio.hpp"\
	{$(INCLUDE)}"\Freestor.hxx"\
	{$(INCLUDE)}"\Gc_cpp.h"\
	{$(INCLUDE)}"\Helptxtx.hxx"\
	{$(INCLUDE)}"\Ibscript.hxx"\
	{$(INCLUDE)}"\Ienumobj.hxx"\
	{$(INCLUDE)}"\Igeometr.hxx"\
	{$(INCLUDE)}"\Istatus.h"\
	{$(INCLUDE)}"\Itriasap.h"\
	{$(INCLUDE)}"\Iunredo.hxx"\
	{$(INCLUDE)}"\Ixtensn.hxx"\
	{$(INCLUDE)}"\Numeditx.hxx"\
	{$(INCLUDE)}"\Objcontx.hxx"\
	{$(INCLUDE)}"\Oleguid.h"\
	{$(INCLUDE)}"\Ospace\Com\Atl.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlbase.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcom.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlcomx.h"\
	{$(INCLUDE)}"\Ospace\Com\Atlutil.h"\
	{$(INCLUDE)}"\Ospace\Com\Smartif.h"\
	{$(INCLUDE)}"\Protos.h"\
	{$(INCLUDE)}"\Registrx.hxx"\
	{$(INCLUDE)}"\Ristypes.hxx"\
	{$(INCLUDE)}"\Smartif.h"\
	{$(INCLUDE)}"\Stddlg.hxx"\
	{$(INCLUDE)}"\String.hpp"\
	{$(INCLUDE)}"\Syncthrd.hxx"\
	{$(INCLUDE)}"\Tassert.hxx"\
	{$(INCLUDE)}"\Trelguid.h"\
	{$(INCLUDE)}"\Trias01m.hxx"\
	{$(INCLUDE)}"\Triastlb.h"\
	{$(INCLUDE)}"\Triastlb_i.c"\
	{$(INCLUDE)}"\Tstring"\
	{$(INCLUDE)}"\Undoguid.h"\
	{$(INCLUDE)}"\Versions.h"\
	{$(INCLUDE)}"\Xtencunk.hxx"\
	{$(INCLUDE)}"\Xtension.h"\
	{$(INCLUDE)}"\Xtensnm.hxx"\
	{$(INCLUDE)}"\Xtensnn.h"\
	{$(INCLUDE)}"\Xtensnx.h"\
	{$(INCLUDE)}"\Xtensnxx.h"\
	{$(INCLUDE)}"\Xtsnguid.h"\
	{$(INCLUDE)}"\Xtsnprop.hxx"\
	{$(INCLUDE)}"\Yxvals.h"\
	
NODEP_CPP_ATTRIF=\
	"..\..\..\INCLUDE\dc.h"\
	

"$(INTDIR)\Attrifce.obj" : $(SOURCE) $(DEP_CPP_ATTRIF) "$(INTDIR)"\
 "$(INTDIR)\Attr32.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
