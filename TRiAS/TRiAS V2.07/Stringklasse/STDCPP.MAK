# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Release" && "$(CFG)" != "Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "stdcpp.mak" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "stdcppr"
# PROP Intermediate_Dir "stdcppr"
OUTDIR=.\stdcppr
INTDIR=.\stdcppr

ALL : $(OUTDIR)/stdcppr.lib $(OUTDIR)/stdcpp.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W3 /WX /GX /YX /O2 /I "..\stdcpp.inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /YX /O2 /I "..\stdcpp.inc" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /Fp$(OUTDIR)/"stdcpp.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\stdcppr/
BSC32=bscmake.exe
BSC32_SBRS= \
	
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"stdcpp.bsc" 

$(OUTDIR)/stdcpp.bsc : $(OUTDIR)  $(BSC32_SBRS)
LIB32=lib.exe
# ADD BASE LIB32 /NOLOGO
# ADD LIB32 /NOLOGO /OUT:"stdcppr\stdcppr.lib"
LIB32_FLAGS=/NOLOGO /OUT:"stdcppr\stdcppr.lib" 
DEF_FLAGS=
DEF_FILE=
LIB32_OBJS= \
	$(INTDIR)/OVERFLOW.OBJ \
	$(INTDIR)/INVALIDA.OBJ \
	$(INTDIR)/XRANGE.OBJ \
	$(INTDIR)/STRCOPY.OBJ \
	$(INTDIR)/XDOMAIN.OBJ \
	$(INTDIR)/STRCOX.OBJ \
	$(INTDIR)/STRFLS.OBJ \
	$(INTDIR)/STRFIS.OBJ \
	$(INTDIR)/STRCOS.OBJ \
	$(INTDIR)/STRFFS.OBJ \
	$(INTDIR)/STRASX.OBJ \
	$(INTDIR)/STRAPX.OBJ \
	$(INTDIR)/NEW.OBJ \
	$(INTDIR)/STRASS.OBJ \
	$(INTDIR)/STRAPS.OBJ \
	$(INTDIR)/LENGTHER.OBJ \
	$(INTDIR)/STRGET.OBJ \
	$(INTDIR)/XRUNTIME.OBJ \
	$(INTDIR)/STRREX.OBJ \
	$(INTDIR)/BADCAST.OBJ \
	$(INTDIR)/STRCOC.OBJ \
	$(INTDIR)/STRRES.OBJ \
	$(INTDIR)/EXCEPTIO.OBJ \
	$(INTDIR)/STRINX.OBJ \
	$(INTDIR)/STRREM.OBJ \
	$(INTDIR)/STRINS.OBJ \
	$(INTDIR)/STRASC.OBJ \
	$(INTDIR)/STRAPC.OBJ \
	$(INTDIR)/STRFLNS.OBJ \
	$(INTDIR)/STRREC.OBJ \
	$(INTDIR)/OUTOFRAN.OBJ \
	$(INTDIR)/STRRFIS.OBJ \
	$(INTDIR)/STRING.OBJ \
	$(INTDIR)/STRINC.OBJ \
	$(INTDIR)/STRFFNS.OBJ \
	$(INTDIR)/XLOGIC.OBJ \
	$(INTDIR)/STRPUT.OBJ \
	$(INTDIR)/TERMINAT.OBJ \
	$(INTDIR)/UNEXPECT.OBJ \
	$(INTDIR)/fnamestr.obj \
	$(INTDIR)/STRXSTR.OBJ \
	$(INTDIR)/strgline.obj

$(OUTDIR)/stdcppr.lib : $(OUTDIR)  $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "stdcppd"
# PROP Intermediate_Dir "stdcppd"
OUTDIR=.\stdcppd
INTDIR=.\stdcppd

ALL : $(OUTDIR)/stdcppd.lib $(OUTDIR)/stdcpp.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE CPP /nologo /W3 /GX /Z7 /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /MD /W3 /WX /GX /Z7 /YX /Od /Ob1 /I "..\stdcpp.inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /Z7 /YX /Od /Ob1 /I "..\stdcpp.inc" /D "WIN32"\
 /D "_DEBUG" /D "_WINDOWS" /Fp$(OUTDIR)/"stdcpp.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\stdcppd/
BSC32=bscmake.exe
BSC32_SBRS= \
	
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"stdcpp.bsc" 

$(OUTDIR)/stdcpp.bsc : $(OUTDIR)  $(BSC32_SBRS)
LIB32=lib.exe
# ADD BASE LIB32 /NOLOGO
# ADD LIB32 /NOLOGO /OUT:"stdcppd\stdcppd.lib"
LIB32_FLAGS=/NOLOGO /OUT:"stdcppd\stdcppd.lib" 
DEF_FLAGS=
DEF_FILE=
LIB32_OBJS= \
	$(INTDIR)/OVERFLOW.OBJ \
	$(INTDIR)/INVALIDA.OBJ \
	$(INTDIR)/XRANGE.OBJ \
	$(INTDIR)/STRCOPY.OBJ \
	$(INTDIR)/XDOMAIN.OBJ \
	$(INTDIR)/STRCOX.OBJ \
	$(INTDIR)/STRFLS.OBJ \
	$(INTDIR)/STRFIS.OBJ \
	$(INTDIR)/STRCOS.OBJ \
	$(INTDIR)/STRFFS.OBJ \
	$(INTDIR)/STRASX.OBJ \
	$(INTDIR)/STRAPX.OBJ \
	$(INTDIR)/NEW.OBJ \
	$(INTDIR)/STRASS.OBJ \
	$(INTDIR)/STRAPS.OBJ \
	$(INTDIR)/LENGTHER.OBJ \
	$(INTDIR)/STRGET.OBJ \
	$(INTDIR)/XRUNTIME.OBJ \
	$(INTDIR)/STRREX.OBJ \
	$(INTDIR)/BADCAST.OBJ \
	$(INTDIR)/STRCOC.OBJ \
	$(INTDIR)/STRRES.OBJ \
	$(INTDIR)/EXCEPTIO.OBJ \
	$(INTDIR)/STRINX.OBJ \
	$(INTDIR)/STRREM.OBJ \
	$(INTDIR)/STRINS.OBJ \
	$(INTDIR)/STRASC.OBJ \
	$(INTDIR)/STRAPC.OBJ \
	$(INTDIR)/STRFLNS.OBJ \
	$(INTDIR)/STRREC.OBJ \
	$(INTDIR)/OUTOFRAN.OBJ \
	$(INTDIR)/STRRFIS.OBJ \
	$(INTDIR)/STRING.OBJ \
	$(INTDIR)/STRINC.OBJ \
	$(INTDIR)/STRFFNS.OBJ \
	$(INTDIR)/XLOGIC.OBJ \
	$(INTDIR)/STRPUT.OBJ \
	$(INTDIR)/TERMINAT.OBJ \
	$(INTDIR)/UNEXPECT.OBJ \
	$(INTDIR)/fnamestr.obj \
	$(INTDIR)/STRXSTR.OBJ \
	$(INTDIR)/strgline.obj

$(OUTDIR)/stdcppd.lib : $(OUTDIR)  $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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

SOURCE=.\OVERFLOW.CPP
DEP_OVERF=\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/OVERFLOW.OBJ :  $(SOURCE)  $(DEP_OVERF) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\INVALIDA.CPP
DEP_INVAL=\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/INVALIDA.OBJ :  $(SOURCE)  $(DEP_INVAL) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\XRANGE.CPP
DEP_XRANG=\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/XRANGE.OBJ :  $(SOURCE)  $(DEP_XRANG) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRCOPY.CPP
DEP_STRCO=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRCOPY.OBJ :  $(SOURCE)  $(DEP_STRCO) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\XDOMAIN.CPP
DEP_XDOMA=\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/XDOMAIN.OBJ :  $(SOURCE)  $(DEP_XDOMA) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRCOX.CPP
DEP_STRCOX=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRCOX.OBJ :  $(SOURCE)  $(DEP_STRCOX) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRFLS.CPP
DEP_STRFL=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRFLS.OBJ :  $(SOURCE)  $(DEP_STRFL) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRFIS.CPP
DEP_STRFI=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRFIS.OBJ :  $(SOURCE)  $(DEP_STRFI) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRCOS.CPP
DEP_STRCOS=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRCOS.OBJ :  $(SOURCE)  $(DEP_STRCOS) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRFFS.CPP
DEP_STRFF=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRFFS.OBJ :  $(SOURCE)  $(DEP_STRFF) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRASX.CPP
DEP_STRAS=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRASX.OBJ :  $(SOURCE)  $(DEP_STRAS) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRAPX.CPP
DEP_STRAP=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRAPX.OBJ :  $(SOURCE)  $(DEP_STRAP) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NEW.CPP
DEP_NEW_C=\
	\MSVC20\STDCPP.INC\NEW.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/NEW.OBJ :  $(SOURCE)  $(DEP_NEW_C) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRASS.CPP
DEP_STRASS=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRASS.OBJ :  $(SOURCE)  $(DEP_STRASS) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRAPS.CPP
DEP_STRAPS=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRAPS.OBJ :  $(SOURCE)  $(DEP_STRAPS) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LENGTHER.CPP
DEP_LENGT=\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/LENGTHER.OBJ :  $(SOURCE)  $(DEP_LENGT) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRGET.CPP
DEP_STRGE=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRGET.OBJ :  $(SOURCE)  $(DEP_STRGE) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\XRUNTIME.CPP
DEP_XRUNT=\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/XRUNTIME.OBJ :  $(SOURCE)  $(DEP_XRUNT) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRREX.CPP
DEP_STRRE=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRREX.OBJ :  $(SOURCE)  $(DEP_STRRE) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BADCAST.CPP
DEP_BADCA=\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/BADCAST.OBJ :  $(SOURCE)  $(DEP_BADCA) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRCOC.CPP
DEP_STRCOC=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRCOC.OBJ :  $(SOURCE)  $(DEP_STRCOC) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRRES.CPP
DEP_STRRES=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRRES.OBJ :  $(SOURCE)  $(DEP_STRRES) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EXCEPTIO.CPP
DEP_EXCEP=\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/EXCEPTIO.OBJ :  $(SOURCE)  $(DEP_EXCEP) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRINX.CPP
DEP_STRIN=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRINX.OBJ :  $(SOURCE)  $(DEP_STRIN) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRREM.CPP
DEP_STRREM=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRREM.OBJ :  $(SOURCE)  $(DEP_STRREM) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRINS.CPP
DEP_STRINS=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRINS.OBJ :  $(SOURCE)  $(DEP_STRINS) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRASC.CPP
DEP_STRASC=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRASC.OBJ :  $(SOURCE)  $(DEP_STRASC) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRAPC.CPP
DEP_STRAPC=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRAPC.OBJ :  $(SOURCE)  $(DEP_STRAPC) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRFLNS.CPP
DEP_STRFLN=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRFLNS.OBJ :  $(SOURCE)  $(DEP_STRFLN) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRREC.CPP
DEP_STRREC=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRREC.OBJ :  $(SOURCE)  $(DEP_STRREC) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OUTOFRAN.CPP
DEP_OUTOF=\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/OUTOFRAN.OBJ :  $(SOURCE)  $(DEP_OUTOF) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRRFIS.CPP
DEP_STRRF=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRRFIS.OBJ :  $(SOURCE)  $(DEP_STRRF) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRING.CPP
DEP_STRING=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRING.OBJ :  $(SOURCE)  $(DEP_STRING) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRINC.CPP
DEP_STRINC=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRINC.OBJ :  $(SOURCE)  $(DEP_STRINC) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRFFNS.CPP
DEP_STRFFN=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRFFNS.OBJ :  $(SOURCE)  $(DEP_STRFFN) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\XLOGIC.CPP
DEP_XLOGI=\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/XLOGIC.OBJ :  $(SOURCE)  $(DEP_XLOGI) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRPUT.CPP
DEP_STRPU=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRPUT.OBJ :  $(SOURCE)  $(DEP_STRPU) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TERMINAT.CPP
DEP_TERMI=\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/TERMINAT.OBJ :  $(SOURCE)  $(DEP_TERMI) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\UNEXPECT.CPP
DEP_UNEXP=\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/UNEXPECT.OBJ :  $(SOURCE)  $(DEP_UNEXP) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\fnamestr.cpp
DEP_FNAME=\
	\msvc20\stdcpp.inc\string\
	\msvc20\stdcpp.inc\fnamestr.h\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/fnamestr.obj :  $(SOURCE)  $(DEP_FNAME) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRXSTR.CPP
DEP_STRXS=\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/STRXSTR.OBJ :  $(SOURCE)  $(DEP_STRXS) $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\strgline.cpp
DEP_STRGL=\
	\msvc20\stdcpp.inc\string\
	\MSVC20\STDCPP.INC\STRING.HPP\
	\MSVC20\STDCPP.INC\DEFINES.HPP\
	\MSVC20\STDCPP.INC\EXCEPTIO.HPP\
	\MSVC20\STDCPP.INC\YXVALS.H

$(INTDIR)/strgline.obj :  $(SOURCE)  $(DEP_STRGL) $(INTDIR)

# End Source File
# End Group
# End Project
################################################################################
