# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Release" && "$(CFG)" != "Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRIAS323.MAK" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Debug"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 Release"

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

ALL : .\WinRel\TRIAS323.dll .\WinRel\TRIAS323.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__TRIAS03DLL__" /D "__CV__" /D "MSCC8" /Yu"trias03p.hxx" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__TRIAS03DLL__" /D\
 "__CV__" /D "MSCC8" /Fp$(OUTDIR)/"TRIAS323.pch" /Yu"trias03p.hxx" /Fo$(INTDIR)/\
 /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
RSC_PROJ=/l 0x407 /fo$(INTDIR)/"TRIAS323.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_SBRS= \
	
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"TRIAS323.bsc" 

.\WinRel\TRIAS323.bsc : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /MACHINE:I386
# ADD LINK32 trias322.lib trias321.lib tfrm32.lib cont32r.lib muscrl32.lib stdcppr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /DLL /MACHINE:I386 /STUB:"\triasdev.mvc\trias03\obj32\rights.exe" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /PDB:none
LINK32_FLAGS=trias322.lib trias321.lib tfrm32.lib cont32r.lib muscrl32.lib\
 stdcppr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /DLL\
 /INCREMENTAL:no /PDB:$(OUTDIR)/"TRIAS323.pdb" /MACHINE:I386\
 /DEF:".\TRIAS323.DEF" /STUB:"\triasdev.mvc\trias03\obj32\rights.exe"\
 /OUT:$(OUTDIR)/"TRIAS323.dll" /IMPLIB:$(OUTDIR)/"TRIAS323.lib"\
 /SUBSYSTEM:windows,4.0  
DEF_FILE=.\TRIAS323.DEF
LINK32_OBJS= \
	.\WinRel\LIBMAIN3.OBJ \
	.\WinRel\TRIAS323.res \
	.\WinRel\trias03p.obj \
	.\WinRel\DATATRAN.OBJ \
	\CV.MVC\LIB\TFRM32.LIB \
	C:\MSVC20\LIB\STDCPPR.LIB \
	\CV.MVC\LIB\CONT32R.LIB \
	\TRIASDEV.MVC\LIB\TRIAS321.LIB \
	\TRIASDEV.MVC\LIB\TRIAS322.LIB \
	.\WinRel\undocf.obj \
	.\WinRel\undodelo.obj \
	.\WinRel\undodelr.obj \
	.\WinRel\undodelt.obj \
	.\WinRel\undofeat.obj \
	.\WinRel\undohelp.obj \
	.\WinRel\undohwnd.obj \
	.\WinRel\undomodo.obj \
	.\WinRel\undomodr.obj \
	.\WinRel\undoredo.obj \
	.\WinRel\undotext.obj \
	.\WinRel\enumundo.obj \
	.\WinRel\undopbd.obj \
	.\WinRel\DATAOBJ.OBJ \
	.\WinRel\IDATAOBJ.OBJ \
	.\WinRel\IENUMFE.OBJ \
	.\WinRel\checklst.obj \
	.\WinRel\DBLNUMED.OBJ \
	.\WinRel\HELPTEXT.OBJ \
	.\WinRel\MUSCROLL.OBJ \
	.\WinRel\NUMEDIT.OBJ \
	.\WinRel\OWNCOMBO.OBJ \
	.\WinRel\OWNLIST.OBJ \
	.\WinRel\OWNLISTE.OBJ \
	.\WinRel\SELIDLST.OBJ \
	.\WinRel\SPINCTRL.OBJ \
	.\WinRel\dblcoord.obj \
	.\WinRel\PRNTPARS.OBJ \
	.\WinRel\ROTATE.OBJ \
	.\WinRel\JUSTIFY.OBJ \
	.\WinRel\opropcf.obj \
	.\WinRel\INTOPROP.OBJ \
	.\WinRel\queryfld.obj \
	.\WinRel\oprpfeat.obj \
	.\WinRel\statimpl.obj \
	.\WinRel\STATUS.OBJ

.\WinRel\TRIAS323.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

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

ALL : .\WinDebug\trias33d.dll .\WinDebug\TRIAS323.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__TRIAS03DLL__" /D "__CV__" /D "MSCC8" /Fp"WinDebug/trias323d.pch" /Yu"trias03p.hxx" /Fd"WinDebug/trias323d.pdb" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D\
 "__TRIAS03DLL__" /D "__CV__" /D "MSCC8" /Fp"WinDebug/trias323d.pch"\
 /Yu"trias03p.hxx" /Fo$(INTDIR)/ /Fd"WinDebug/trias323d.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
RSC_PROJ=/l 0x407 /fo$(INTDIR)/"TRIAS323.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_SBRS= \
	
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"TRIAS323.bsc" 

.\WinDebug\TRIAS323.bsc : $(OUTDIR)  $(BSC32_SBRS)
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DEBUG /MACHINE:I386
# ADD LINK32 trias32d.lib trias31d.lib tfrm32d.lib cont32d.lib muscrl32.lib stdcppd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib /NOLOGO /BASE:0x60000 /DLL /DEBUG /MACHINE:I386 /STUB:"\triasdev.mvc\trias03\obj32\rights.exe" /OUT:"WinDebug/trias33d.dll" /IMPLIB:"WinDebug/trias33d.lib" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /PROFILE /INCREMENTAL:no
LINK32_FLAGS=trias32d.lib trias31d.lib tfrm32d.lib cont32d.lib muscrl32.lib\
 stdcppd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib winmm.lib /NOLOGO\
 /BASE:0x60000 /DLL /INCREMENTAL:yes /PDB:$(OUTDIR)/"TRIAS323.pdb" /DEBUG\
 /MACHINE:I386 /DEF:".\TRIAS323.DEF"\
 /STUB:"\triasdev.mvc\trias03\obj32\rights.exe" /OUT:"WinDebug/trias33d.dll"\
 /IMPLIB:"WinDebug/trias33d.lib" /SUBSYSTEM:windows,4.0  
DEF_FILE=.\TRIAS323.DEF
LINK32_OBJS= \
	.\WinDebug\LIBMAIN3.OBJ \
	.\WinDebug\TRIAS323.res \
	.\WinDebug\trias03p.obj \
	.\WinDebug\DATATRAN.OBJ \
	.\WinDebug\undocf.obj \
	.\WinDebug\undodelo.obj \
	.\WinDebug\undodelr.obj \
	.\WinDebug\undodelt.obj \
	.\WinDebug\undofeat.obj \
	.\WinDebug\undohelp.obj \
	.\WinDebug\undohwnd.obj \
	.\WinDebug\undomodo.obj \
	.\WinDebug\undomodr.obj \
	.\WinDebug\undoredo.obj \
	.\WinDebug\undotext.obj \
	.\WinDebug\enumundo.obj \
	.\WinDebug\undopbd.obj \
	.\WinDebug\DATAOBJ.OBJ \
	.\WinDebug\IDATAOBJ.OBJ \
	.\WinDebug\IENUMFE.OBJ \
	.\WinDebug\checklst.obj \
	.\WinDebug\DBLNUMED.OBJ \
	.\WinDebug\HELPTEXT.OBJ \
	.\WinDebug\MUSCROLL.OBJ \
	.\WinDebug\NUMEDIT.OBJ \
	.\WinDebug\OWNCOMBO.OBJ \
	.\WinDebug\OWNLIST.OBJ \
	.\WinDebug\OWNLISTE.OBJ \
	.\WinDebug\SELIDLST.OBJ \
	.\WinDebug\SPINCTRL.OBJ \
	.\WinDebug\dblcoord.obj \
	.\WinDebug\PRNTPARS.OBJ \
	.\WinDebug\ROTATE.OBJ \
	.\WinDebug\JUSTIFY.OBJ \
	.\WinDebug\opropcf.obj \
	.\WinDebug\INTOPROP.OBJ \
	.\WinDebug\queryfld.obj \
	.\WinDebug\oprpfeat.obj \
	.\WinDebug\statimpl.obj \
	.\WinDebug\STATUS.OBJ

.\WinDebug\trias33d.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

################################################################################
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\LIBMAIN3.CXX
DEP_LIBMA=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\LIBMAIN3.OBJ :  $(SOURCE)  $(DEP_LIBMA) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\LIBMAIN3.OBJ :  $(SOURCE)  $(DEP_LIBMA) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TRIAS323.RC
DEP_TRIAS=\
	.\TRIAS323.RCV

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\TRIAS323.res :  $(SOURCE)  $(DEP_TRIAS) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\TRIAS323.res :  $(SOURCE)  $(DEP_TRIAS) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\trias03p.cxx
DEP_TRIAS0=\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\trias02m.hxx\
	\TRIASDEV.MVC\INCLUDE\TRIAS03M.HXX\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

# ADD CPP /Yc"trias03p.hxx"

.\WinRel\trias03p.obj :  $(SOURCE)  $(DEP_TRIAS0) $(INTDIR)
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__XT" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D "__TRIAS03DLL__" /D\
 "__CV__" /D "MSCC8" /Fp$(OUTDIR)/"TRIAS323.pch" /Yc"trias03p.hxx" /Fo$(INTDIR)/\
 /c  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

# ADD CPP /Yc"trias03p.hxx"

.\WinDebug\trias03p.obj :  $(SOURCE)  $(DEP_TRIAS0) $(INTDIR)
   $(CPP) /nologo /MD /W3 /WX /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "STRICT" /D "MSWIND" /D "DLL" /D\
 "__TRIAS03DLL__" /D "__CV__" /D "MSCC8" /Fp"WinDebug/trias323d.pch"\
 /Yc"trias03p.hxx" /Fo$(INTDIR)/ /Fd"WinDebug/trias323d.pdb" /c  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TRIAS323.DEF
# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\DATATRAN.CXX
DEP_DATAT=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\TRIAS03\DATAOBJ.HXX\
	\TRIASDEV.MVC\TRIAS03\DATATRAN.HXX\
	\TRIASDEV.MVC\INCLUDE\statguid.h\
	\TRIASDEV.MVC\INCLUDE\undoguid.h\
	\TRIASDEV.MVC\INCLUDE\xtsnguid.h\
	\TRIASDEV.MVC\INCLUDE\oprpguid.h\
	\TRIASDEV.MVC\TRIAS03\undocf.hxx\
	\TRIASDEV.MVC\TRIAS03\opropcf.hxx\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\TRIASDEV.MVC\INCLUDE\EONRGUID.H\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\DATATRAN.OBJ :  $(SOURCE)  $(DEP_DATAT) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\DATATRAN.OBJ :  $(SOURCE)  $(DEP_DATAT) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
# End Group
################################################################################
# Begin Group "Release Libraries"

################################################################################
# Begin Source File

SOURCE=\CV.MVC\LIB\TFRM32.LIB

!IF  "$(CFG)" == "Win32 Release"

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=C:\MSVC20\LIB\STDCPPR.LIB

!IF  "$(CFG)" == "Win32 Release"

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\CV.MVC\LIB\CONT32R.LIB

!IF  "$(CFG)" == "Win32 Release"

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\LIB\TRIAS321.LIB

!IF  "$(CFG)" == "Win32 Release"

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\LIB\TRIAS322.LIB

!IF  "$(CFG)" == "Win32 Release"

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
################################################################################
# Begin Group "Undo and Redo"

################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\undocf.cxx
DEP_UNDOC=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\INCLUDE\funcs03.h\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\undoguid.h\
	\TRIASDEV.MVC\INCLUDE\iunredo.hxx\
	\TRIASDEV.MVC\INCLUDE\ENUMUNDO.HXX\
	\TRIASDEV.MVC\INCLUDE\undoredo.hxx\
	\TRIASDEV.MVC\TRIAS03\undocf.hxx\
	\TRIASDEV.MVC\TRIAS03\UNDOFEAT.HXX\
	\TRIASDEV.MVC\TRIAS03\UNDODELR.HXX\
	\TRIASDEV.MVC\TRIAS03\UNDOMODR.HXX\
	\TRIASDEV.MVC\TRIAS03\UNDODELT.HXX\
	\TRIASDEV.MVC\TRIAS03\UNDOTEXT.HXX\
	\TRIASDEV.MVC\TRIAS03\UNDOHWND.HXX\
	\TRIASDEV.MVC\TRIAS03\undodelo.hxx\
	\TRIASDEV.MVC\TRIAS03\undomodo.hxx\
	\TRIASDEV.MVC\TRIAS03\undopbd.hxx\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\TRIASDEV.MVC\INCLUDE\ROTATE.HXX\
	\TRIASDEV.MVC\INCLUDE\JUSTIFY.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\undocf.obj :  $(SOURCE)  $(DEP_UNDOC) $(INTDIR) .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\undocf.obj :  $(SOURCE)  $(DEP_UNDOC) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\undodelo.cxx
DEP_UNDOD=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\TRIAS03\TRIAS03.H\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\undoguid.h\
	\TRIASDEV.MVC\INCLUDE\iunredo.hxx\
	\TRIASDEV.MVC\INCLUDE\ENUMUNDO.HXX\
	\TRIASDEV.MVC\INCLUDE\undoredo.hxx\
	\TRIASDEV.MVC\TRIAS03\undodelo.hxx\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\undodelo.obj :  $(SOURCE)  $(DEP_UNDOD) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\undodelo.obj :  $(SOURCE)  $(DEP_UNDOD) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\undodelr.cxx
DEP_UNDODE=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\TRIAS03\TRIAS03.H\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\undoguid.h\
	\TRIASDEV.MVC\INCLUDE\iunredo.hxx\
	\TRIASDEV.MVC\INCLUDE\ENUMUNDO.HXX\
	\TRIASDEV.MVC\INCLUDE\undoredo.hxx\
	\TRIASDEV.MVC\TRIAS03\UNDODELR.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\undodelr.obj :  $(SOURCE)  $(DEP_UNDODE) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\undodelr.obj :  $(SOURCE)  $(DEP_UNDODE) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\undodelt.cxx
DEP_UNDODEL=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\TRIAS03\TRIAS03.H\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\undoguid.h\
	\TRIASDEV.MVC\INCLUDE\iunredo.hxx\
	\TRIASDEV.MVC\INCLUDE\ENUMUNDO.HXX\
	\TRIASDEV.MVC\INCLUDE\undoredo.hxx\
	\TRIASDEV.MVC\TRIAS03\UNDODELT.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\undodelt.obj :  $(SOURCE)  $(DEP_UNDODEL) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\undodelt.obj :  $(SOURCE)  $(DEP_UNDODEL) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\undofeat.cxx
DEP_UNDOF=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\TRIAS03\TRIAS03.H\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\undoguid.h\
	\TRIASDEV.MVC\INCLUDE\iunredo.hxx\
	\TRIASDEV.MVC\INCLUDE\ENUMUNDO.HXX\
	\TRIASDEV.MVC\INCLUDE\undoredo.hxx\
	\TRIASDEV.MVC\TRIAS03\UNDOFEAT.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\undofeat.obj :  $(SOURCE)  $(DEP_UNDOF) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\undofeat.obj :  $(SOURCE)  $(DEP_UNDOF) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\undohelp.cxx
DEP_UNDOH=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\TRIAS03\TRIAS03.H\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\undoguid.h\
	\TRIASDEV.MVC\INCLUDE\iunredo.hxx\
	\TRIASDEV.MVC\INCLUDE\ENUMUNDO.HXX\
	\TRIASDEV.MVC\INCLUDE\undoredo.hxx\
	\TRIASDEV.MVC\INCLUDE\undohelp.hxx\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\undohelp.obj :  $(SOURCE)  $(DEP_UNDOH) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\undohelp.obj :  $(SOURCE)  $(DEP_UNDOH) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\undohwnd.cxx
DEP_UNDOHW=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\TRIAS03\TRIAS03.H\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\undoguid.h\
	\TRIASDEV.MVC\INCLUDE\iunredo.hxx\
	\TRIASDEV.MVC\INCLUDE\ENUMUNDO.HXX\
	\TRIASDEV.MVC\INCLUDE\undoredo.hxx\
	\TRIASDEV.MVC\TRIAS03\UNDOHWND.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\undohwnd.obj :  $(SOURCE)  $(DEP_UNDOHW) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\undohwnd.obj :  $(SOURCE)  $(DEP_UNDOHW) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\undomodo.cxx
DEP_UNDOM=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\TRIAS03\TRIAS03.H\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\undoguid.h\
	\TRIASDEV.MVC\INCLUDE\iunredo.hxx\
	\TRIASDEV.MVC\INCLUDE\ENUMUNDO.HXX\
	\TRIASDEV.MVC\INCLUDE\undoredo.hxx\
	\TRIASDEV.MVC\TRIAS03\undomodo.hxx\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\undomodo.obj :  $(SOURCE)  $(DEP_UNDOM) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\undomodo.obj :  $(SOURCE)  $(DEP_UNDOM) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\undomodr.cxx
DEP_UNDOMO=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\TRIAS03\TRIAS03.H\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\undoguid.h\
	\TRIASDEV.MVC\INCLUDE\iunredo.hxx\
	\TRIASDEV.MVC\INCLUDE\ENUMUNDO.HXX\
	\TRIASDEV.MVC\INCLUDE\undoredo.hxx\
	\TRIASDEV.MVC\TRIAS03\UNDOMODR.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\undomodr.obj :  $(SOURCE)  $(DEP_UNDOMO) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\undomodr.obj :  $(SOURCE)  $(DEP_UNDOMO) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\undoredo.cxx
DEP_UNDOR=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\undoguid.h\
	\TRIASDEV.MVC\INCLUDE\iunredo.hxx\
	\TRIASDEV.MVC\INCLUDE\ENUMUNDO.HXX\
	\TRIASDEV.MVC\INCLUDE\undoredo.hxx\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\undoredo.obj :  $(SOURCE)  $(DEP_UNDOR) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\undoredo.obj :  $(SOURCE)  $(DEP_UNDOR) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\undotext.cxx
DEP_UNDOT=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\TRIAS03\TRIAS03.H\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\undoguid.h\
	\TRIASDEV.MVC\INCLUDE\iunredo.hxx\
	\TRIASDEV.MVC\INCLUDE\ENUMUNDO.HXX\
	\TRIASDEV.MVC\INCLUDE\undoredo.hxx\
	\TRIASDEV.MVC\TRIAS03\UNDOTEXT.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\undotext.obj :  $(SOURCE)  $(DEP_UNDOT) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\undotext.obj :  $(SOURCE)  $(DEP_UNDOT) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\enumundo.cxx
DEP_ENUMU=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\ENUMUNDO.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\enumundo.obj :  $(SOURCE)  $(DEP_ENUMU) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\enumundo.obj :  $(SOURCE)  $(DEP_ENUMU) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\undopbd.cxx
DEP_UNDOP=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\TRIAS03\TRIAS03.H\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRINST.HXX\
	\TRIASDEV.MVC\INCLUDE\XTENSNN.H\
	\TRIASDEV.MVC\INCLUDE\undoguid.h\
	\TRIASDEV.MVC\INCLUDE\iunredo.hxx\
	\TRIASDEV.MVC\INCLUDE\ENUMUNDO.HXX\
	\TRIASDEV.MVC\INCLUDE\undoredo.hxx\
	\TRIASDEV.MVC\TRIAS03\undopbd.hxx\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\undopbd.obj :  $(SOURCE)  $(DEP_UNDOP) $(INTDIR) .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\undopbd.obj :  $(SOURCE)  $(DEP_UNDOP) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
# End Group
################################################################################
# Begin Group "Debug Libraries"

################################################################################
# Begin Source File

SOURCE=\CV.MVC\LIB\CONT32D.LIB
# PROP Exclude_From_Build 1
# End Source File
################################################################################
# Begin Source File

SOURCE=C:\MSVC20\LIB\STDCPPD.LIB
# PROP Exclude_From_Build 1
# End Source File
################################################################################
# Begin Source File

SOURCE=\CV.MVC\LIB\TFRM32D.LIB
# PROP Exclude_From_Build 1
# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\LIB\TRIAS31D.LIB
# PROP Exclude_From_Build 1
# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\LIB\TRIAS32D.LIB
# PROP Exclude_From_Build 1
# End Source File
# End Group
################################################################################
# Begin Group "DataObject"

################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\DATAOBJ.CXX
DEP_DATAO=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\TRIAS03\DATAOBJ.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\DATAOBJ.OBJ :  $(SOURCE)  $(DEP_DATAO) $(INTDIR) .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\DATAOBJ.OBJ :  $(SOURCE)  $(DEP_DATAO) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\IDATAOBJ.CXX
DEP_IDATA=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\TRIAS03\DATAOBJ.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\IDATAOBJ.OBJ :  $(SOURCE)  $(DEP_IDATA) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\IDATAOBJ.OBJ :  $(SOURCE)  $(DEP_IDATA) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\IENUMFE.CXX
DEP_IENUM=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\INCLUDE\DIRISOLE.H\
	\TRIASDEV.MVC\TRIAS03\DATAOBJ.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\IENUMFE.OBJ :  $(SOURCE)  $(DEP_IENUM) $(INTDIR) .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\IENUMFE.OBJ :  $(SOURCE)  $(DEP_IENUM) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
# End Group
################################################################################
# Begin Group "Control Extensions"

################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\checklst.cxx
DEP_CHECK=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\checklst.hxx\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\checklst.obj :  $(SOURCE)  $(DEP_CHECK) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\checklst.obj :  $(SOURCE)  $(DEP_CHECK) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\DBLNUMED.CXX
DEP_DBLNU=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\INCLUDE\ZPROTOS.H\
	\TRIASDEV.MVC\INCLUDE\NUMEDIT.HXX\
	\TRIASDEV.MVC\INCLUDE\DBLNUMED.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\TRIASDEV.MVC\INCLUDE\trias02m.hxx\
	\TRIASDEV.MVC\INCLUDE\FPROTOS.H\
	\TRIASDEV.MVC\INCLUDE\MPROTOS.H\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\DBLNUMED.OBJ :  $(SOURCE)  $(DEP_DBLNU) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\DBLNUMED.OBJ :  $(SOURCE)  $(DEP_DBLNU) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\HELPTEXT.CXX
DEP_HELPT=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\INCLUDE\HELPTEXT.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\HELPTEXT.OBJ :  $(SOURCE)  $(DEP_HELPT) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\HELPTEXT.OBJ :  $(SOURCE)  $(DEP_HELPT) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\MUSCROLL.CXX
DEP_MUSCR=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	d:\msvc20\include\muscroll.h\
	d:\msvc20\include\muscrl32.h\
	\TRIASDEV.MVC\INCLUDE\MUSCROLL.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\MUSCROLL.OBJ :  $(SOURCE)  $(DEP_MUSCR) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\MUSCROLL.OBJ :  $(SOURCE)  $(DEP_MUSCR) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\NUMEDIT.CXX
DEP_NUMED=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\INCLUDE\NUMEDIT.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\NUMEDIT.OBJ :  $(SOURCE)  $(DEP_NUMED) $(INTDIR) .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\NUMEDIT.OBJ :  $(SOURCE)  $(DEP_NUMED) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\OWNCOMBO.CXX
DEP_OWNCO=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\OWNCOMBO.OBJ :  $(SOURCE)  $(DEP_OWNCO) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\OWNCOMBO.OBJ :  $(SOURCE)  $(DEP_OWNCO) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\OWNLIST.CXX
DEP_OWNLI=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\INCLUDE\OWNLIST.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\OWNLIST.OBJ :  $(SOURCE)  $(DEP_OWNLI) $(INTDIR) .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\OWNLIST.OBJ :  $(SOURCE)  $(DEP_OWNLI) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\OWNLISTE.CXX
DEP_OWNLIS=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\INCLUDE\OWNLIST.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNLISTE.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\OWNLISTE.OBJ :  $(SOURCE)  $(DEP_OWNLIS) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\OWNLISTE.OBJ :  $(SOURCE)  $(DEP_OWNLIS) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\SELIDLST.CXX
DEP_SELID=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\INCLUDE\SELIDLST.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\SELIDLST.OBJ :  $(SOURCE)  $(DEP_SELID) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\SELIDLST.OBJ :  $(SOURCE)  $(DEP_SELID) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\SPINCTRL.CXX
DEP_SPINC=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\INCLUDE\MUSCROLL.HXX\
	\TRIASDEV.MVC\INCLUDE\NUMEDIT.HXX\
	\TRIASDEV.MVC\INCLUDE\SPINCTRL.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\SPINCTRL.OBJ :  $(SOURCE)  $(DEP_SPINC) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\SPINCTRL.OBJ :  $(SOURCE)  $(DEP_SPINC) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\dblcoord.cxx
DEP_DBLCO=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\INCLUDE\dblcoord.hxx\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\TRIASDEV.MVC\INCLUDE\NUMEDIT.HXX\
	\TRIASDEV.MVC\INCLUDE\DBLNUMED.HXX\
	\TRIASDEV.MVC\INCLUDE\DLLBIND.HXX\
	\TRIASDEV.MVC\INCLUDE\CTF.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	\TRIASDEV.MVC\INCLUDE\CTF.H\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	\TRIASDEV.MVC\INCLUDE\ctfm.hxx\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\dblcoord.obj :  $(SOURCE)  $(DEP_DBLCO) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\dblcoord.obj :  $(SOURCE)  $(DEP_DBLCO) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
# End Group
################################################################################
# Begin Group "Aux Helper"

################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\PRNTPARS.CXX
DEP_PRNTP=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\INCLUDE\DBLPAIR.HXX\
	\TRIASDEV.MVC\INCLUDE\prntpars.hxx\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\PRNTPARS.OBJ :  $(SOURCE)  $(DEP_PRNTP) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\PRNTPARS.OBJ :  $(SOURCE)  $(DEP_PRNTP) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\ROTATE.CXX
DEP_ROTAT=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\funcs03.h\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	\TRIASDEV.MVC\INCLUDE\ROTATE.HXX\
	\TRIASDEV.MVC\INCLUDE\JUSTIFY.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\ROTATE.OBJ :  $(SOURCE)  $(DEP_ROTAT) $(INTDIR) .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\ROTATE.OBJ :  $(SOURCE)  $(DEP_ROTAT) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\JUSTIFY.CXX
DEP_JUSTI=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\INCLUDE\funcs03.h\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\TRIASDEV.MVC\INCLUDE\ROTATE.HXX\
	\TRIASDEV.MVC\INCLUDE\JUSTIFY.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\JUSTIFY.OBJ :  $(SOURCE)  $(DEP_JUSTI) $(INTDIR) .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\JUSTIFY.OBJ :  $(SOURCE)  $(DEP_JUSTI) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
# End Group
################################################################################
# Begin Group "Objekteigenschaften"

################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\opropcf.cxx
DEP_OPROP=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\INCLUDE\funcs03.h\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\undoguid.h\
	\TRIASDEV.MVC\INCLUDE\oprpguid.h\
	\TRIASDEV.MVC\INCLUDE\IXTENSN.HXX\
	\TRIASDEV.MVC\INCLUDE\iunredo.hxx\
	\TRIASDEV.MVC\INCLUDE\ioprpini.hxx\
	\TRIASDEV.MVC\INCLUDE\ENUMUNDO.HXX\
	\TRIASDEV.MVC\INCLUDE\undoredo.hxx\
	\TRIASDEV.MVC\TRIAS03\opropcf.hxx\
	\TRIASDEV.MVC\TRIAS03\INTOPROP.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\TRIASDEV.MVC\INCLUDE\ROTATE.HXX\
	\TRIASDEV.MVC\INCLUDE\JUSTIFY.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	\TRIASDEV.MVC\INCLUDE\IENUMOBJ.HXX\
	\TRIASDEV.MVC\INCLUDE\istatus.h\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\opropcf.obj :  $(SOURCE)  $(DEP_OPROP) $(INTDIR) .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\opropcf.obj :  $(SOURCE)  $(DEP_OPROP) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\INTOPROP.CXX
DEP_INTOP=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\TRIAS03\TRIAS03.H\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\IXTENSN.HXX\
	\TRIASDEV.MVC\INCLUDE\ioprpini.hxx\
	\TRIASDEV.MVC\INCLUDE\xtsnguid.h\
	\TRIASDEV.MVC\INCLUDE\oprpguid.h\
	\TRIASDEV.MVC\INCLUDE\ERRINST.HXX\
	\TRIASDEV.MVC\TRIAS03\INTOPROP.HXX\
	\TRIASDEV.MVC\TRIAS03\QUERYFLD.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	\TRIASDEV.MVC\INCLUDE\IENUMOBJ.HXX\
	\TRIASDEV.MVC\INCLUDE\istatus.h\
	\TRIASDEV.MVC\INCLUDE\EONRGUID.H\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\INTOPROP.OBJ :  $(SOURCE)  $(DEP_INTOP) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\INTOPROP.OBJ :  $(SOURCE)  $(DEP_INTOP) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\queryfld.cxx
DEP_QUERY=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\TRIAS03\TRIAS03.H\
	\TRIASDEV.MVC\TRIAS03\QUERYFLD.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\queryfld.obj :  $(SOURCE)  $(DEP_QUERY) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\queryfld.obj :  $(SOURCE)  $(DEP_QUERY) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\oprpfeat.cxx
DEP_OPRPF=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\TRIAS03\TRIAS03.H\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\IXTENSN.HXX\
	\TRIASDEV.MVC\INCLUDE\ioprpini.hxx\
	\TRIASDEV.MVC\INCLUDE\xtsnguid.h\
	\TRIASDEV.MVC\INCLUDE\oprpguid.h\
	\TRIASDEV.MVC\INCLUDE\ERRINST.HXX\
	\TRIASDEV.MVC\TRIAS03\INTOPROP.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	\TRIASDEV.MVC\INCLUDE\IENUMOBJ.HXX\
	\TRIASDEV.MVC\INCLUDE\istatus.h\
	\TRIASDEV.MVC\INCLUDE\EONRGUID.H\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\oprpfeat.obj :  $(SOURCE)  $(DEP_OPRPF) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\oprpfeat.obj :  $(SOURCE)  $(DEP_OPRPF) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
# End Group
################################################################################
# Begin Group "Progress Indicator"

################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\statimpl.cxx
DEP_STATI=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\TRIASDEV.MVC\TRIAS03\TRIAS03.H\
	\TRIASDEV.MVC\INCLUDE\statguid.h\
	\TRIASDEV.MVC\INCLUDE\statimpl.hxx\
	\TRIASDEV.MVC\TRIAS03\STATUS.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\TRIASDEV.MVC\INCLUDE\istatus.h\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\statimpl.obj :  $(SOURCE)  $(DEP_STATI) $(INTDIR)\
 .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\statimpl.obj :  $(SOURCE)  $(DEP_STATI) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\TRIASDEV.MVC\TRIAS03\STATUS.CPP
DEP_STATU=\
	\TRIASDEV.MVC\TRIAS03\trias03p.hxx\
	\CV.MVC\TFRMWORK.INC\CONTAINR.HXX\
	\TRIASDEV.MVC\INCLUDE\istatus.h\
	\TRIASDEV.MVC\TRIAS03\TRIAS03.H\
	\TRIASDEV.MVC\TRIAS03\STATUS.HXX\
	d:\msvc20\stdcpp.inc\string\
	\TRIASDEV.MVC\INCLUDE\PROTOS.H\
	\TRIASDEV.MVC\INCLUDE\XTENSION.H\
	\TRIASDEV.MVC\INCLUDE\XTENSNX.H\
	\TRIASDEV.MVC\INCLUDE\RESSTRG.H\
	\CV.MVC\TFRMWORK.INC\COMMONVU.HXX\
	\TRIASDEV.MVC\INCLUDE\RISTYPES.HXX\
	\TRIASDEV.MVC\INCLUDE\ERRCODES.HXX\
	\TRIASDEV.MVC\INCLUDE\ODDLGWIN.HXX\
	\TRIASDEV.MVC\INCLUDE\OWNCOMBO.HXX\
	\CV.MVC\TFRMWORK.INC\CTRTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\FREESTOR.HXX\
	\CV.MVC\TFRMWORK.INC\TASSERT.HXX\
	\CV.MVC\TFRMWORK.INC\SYNCTHRD.HXX\
	\CV.MVC\TFRMWORK.INC\CTRLINES.HXX\
	d:\msvc20\stdcpp.inc\string.hpp\
	\TRIASDEV.MVC\INCLUDE\trias01m.hxx\
	\TRIASDEV.MVC\INCLUDE\xtensnm.hxx\
	d:\msvc20\include\print.h\
	\CV.MVC\TFRMWORK.INC\CXXTYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_TYPES.HXX\
	\CV.MVC\TFRMWORK.INC\CV_DEFS.H\
	\CV.MVC\TFRMWORK.INC\CVINLINE.HXX\
	\TRIASDEV.MVC\INCLUDE\PALCHEVT.HXX\
	d:\msvc20\stdcpp.inc\defines.hpp\
	d:\msvc20\stdcpp.inc\exceptio.hpp\
	d:\msvc20\stdcpp.inc\yxvals.h

!IF  "$(CFG)" == "Win32 Release"

.\WinRel\STATUS.OBJ :  $(SOURCE)  $(DEP_STATU) $(INTDIR) .\WinRel\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\STATUS.OBJ :  $(SOURCE)  $(DEP_STATU) $(INTDIR)\
 .\WinDebug\trias03p.obj
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
