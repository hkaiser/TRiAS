# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=Stdcpp - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Stdcpp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Stdcpp - Win32 Release" && "$(CFG)" != "Stdcpp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Stdcpp4.mak" CFG="Stdcpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Stdcpp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Stdcpp - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "Stdcpp - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "Stdcpp - Win32 Release"

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
# Begin Custom Macros
TargetName=stdcppr
# End Custom Macros

ALL : "$(OUTDIR)\stdcppr.lib" "c:\trias\lib\stdcppr.lib"

CLEAN : 
	-@erase "$(INTDIR)\BADCAST.OBJ"
	-@erase "$(INTDIR)\EXCEPTIO.OBJ"
	-@erase "$(INTDIR)\fnamestr.obj"
	-@erase "$(INTDIR)\INVALIDA.OBJ"
	-@erase "$(INTDIR)\LENGTHER.OBJ"
	-@erase "$(INTDIR)\NEW.OBJ"
	-@erase "$(INTDIR)\OUTOFRAN.OBJ"
	-@erase "$(INTDIR)\OVERFLOW.OBJ"
	-@erase "$(INTDIR)\STRAPC.OBJ"
	-@erase "$(INTDIR)\STRAPS.OBJ"
	-@erase "$(INTDIR)\STRAPX.OBJ"
	-@erase "$(INTDIR)\STRASC.OBJ"
	-@erase "$(INTDIR)\STRASS.OBJ"
	-@erase "$(INTDIR)\STRASX.OBJ"
	-@erase "$(INTDIR)\STRCOC.OBJ"
	-@erase "$(INTDIR)\STRCOPY.OBJ"
	-@erase "$(INTDIR)\STRCOS.OBJ"
	-@erase "$(INTDIR)\STRCOX.OBJ"
	-@erase "$(INTDIR)\STRFFNS.OBJ"
	-@erase "$(INTDIR)\STRFFS.OBJ"
	-@erase "$(INTDIR)\STRFIS.OBJ"
	-@erase "$(INTDIR)\STRFLNS.OBJ"
	-@erase "$(INTDIR)\STRFLS.OBJ"
	-@erase "$(INTDIR)\STRGET.OBJ"
	-@erase "$(INTDIR)\strgline.obj"
	-@erase "$(INTDIR)\STRINC.OBJ"
	-@erase "$(INTDIR)\STRING.OBJ"
	-@erase "$(INTDIR)\STRINS.OBJ"
	-@erase "$(INTDIR)\STRINX.OBJ"
	-@erase "$(INTDIR)\STRPUT.OBJ"
	-@erase "$(INTDIR)\STRREC.OBJ"
	-@erase "$(INTDIR)\STRREM.OBJ"
	-@erase "$(INTDIR)\STRRES.OBJ"
	-@erase "$(INTDIR)\STRREX.OBJ"
	-@erase "$(INTDIR)\STRRFIS.OBJ"
	-@erase "$(INTDIR)\STRXSTR.OBJ"
	-@erase "$(INTDIR)\TERMINAT.OBJ"
	-@erase "$(INTDIR)\UNEXPECT.OBJ"
	-@erase "$(INTDIR)\XDOMAIN.OBJ"
	-@erase "$(INTDIR)\XLOGIC.OBJ"
	-@erase "$(INTDIR)\XRANGE.OBJ"
	-@erase "$(INTDIR)\XRUNTIME.OBJ"
	-@erase "$(OUTDIR)\stdcppr.lib"
	-@erase "c:\trias\lib\stdcppr.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/stdcpp.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /I "..\stdcpp.inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# SUBTRACT CPP /Z<none> /Fr
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /I "..\stdcpp.inc" /D "WIN32" /D "NDEBUG"\
 /D "_WINDOWS" /Fp"$(INTDIR)/Stdcpp4.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\stdcppr/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Stdcpp4.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"stdcppr\stdcppr.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/stdcppr.lib" 
LIB32_OBJS= \
	"$(INTDIR)\BADCAST.OBJ" \
	"$(INTDIR)\EXCEPTIO.OBJ" \
	"$(INTDIR)\fnamestr.obj" \
	"$(INTDIR)\INVALIDA.OBJ" \
	"$(INTDIR)\LENGTHER.OBJ" \
	"$(INTDIR)\NEW.OBJ" \
	"$(INTDIR)\OUTOFRAN.OBJ" \
	"$(INTDIR)\OVERFLOW.OBJ" \
	"$(INTDIR)\STRAPC.OBJ" \
	"$(INTDIR)\STRAPS.OBJ" \
	"$(INTDIR)\STRAPX.OBJ" \
	"$(INTDIR)\STRASC.OBJ" \
	"$(INTDIR)\STRASS.OBJ" \
	"$(INTDIR)\STRASX.OBJ" \
	"$(INTDIR)\STRCOC.OBJ" \
	"$(INTDIR)\STRCOPY.OBJ" \
	"$(INTDIR)\STRCOS.OBJ" \
	"$(INTDIR)\STRCOX.OBJ" \
	"$(INTDIR)\STRFFNS.OBJ" \
	"$(INTDIR)\STRFFS.OBJ" \
	"$(INTDIR)\STRFIS.OBJ" \
	"$(INTDIR)\STRFLNS.OBJ" \
	"$(INTDIR)\STRFLS.OBJ" \
	"$(INTDIR)\STRGET.OBJ" \
	"$(INTDIR)\strgline.obj" \
	"$(INTDIR)\STRINC.OBJ" \
	"$(INTDIR)\STRING.OBJ" \
	"$(INTDIR)\STRINS.OBJ" \
	"$(INTDIR)\STRINX.OBJ" \
	"$(INTDIR)\STRPUT.OBJ" \
	"$(INTDIR)\STRREC.OBJ" \
	"$(INTDIR)\STRREM.OBJ" \
	"$(INTDIR)\STRRES.OBJ" \
	"$(INTDIR)\STRREX.OBJ" \
	"$(INTDIR)\STRRFIS.OBJ" \
	"$(INTDIR)\STRXSTR.OBJ" \
	"$(INTDIR)\TERMINAT.OBJ" \
	"$(INTDIR)\UNEXPECT.OBJ" \
	"$(INTDIR)\XDOMAIN.OBJ" \
	"$(INTDIR)\XLOGIC.OBJ" \
	"$(INTDIR)\XRANGE.OBJ" \
	"$(INTDIR)\XRUNTIME.OBJ"

"$(OUTDIR)\stdcppr.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

# Begin Custom Build
TargetPath=.\stdcppr\stdcppr.lib
TargetName=stdcppr
InputPath=.\stdcppr\stdcppr.lib
SOURCE=$(InputPath)

"c:\trias\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   xcopy /F $(TargetPath) c:\trias\lib

# End Custom Build

!ELSEIF  "$(CFG)" == "Stdcpp - Win32 Debug"

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
# Begin Custom Macros
TargetName=stdcppd
# End Custom Macros

ALL : "$(OUTDIR)\stdcppd.lib" "c:\trias\lib\stdcppd.lib"

CLEAN : 
	-@erase "$(INTDIR)\BADCAST.OBJ"
	-@erase "$(INTDIR)\EXCEPTIO.OBJ"
	-@erase "$(INTDIR)\fnamestr.obj"
	-@erase "$(INTDIR)\INVALIDA.OBJ"
	-@erase "$(INTDIR)\LENGTHER.OBJ"
	-@erase "$(INTDIR)\NEW.OBJ"
	-@erase "$(INTDIR)\OUTOFRAN.OBJ"
	-@erase "$(INTDIR)\OVERFLOW.OBJ"
	-@erase "$(INTDIR)\Stdcppd.pdb"
	-@erase "$(INTDIR)\STRAPC.OBJ"
	-@erase "$(INTDIR)\STRAPS.OBJ"
	-@erase "$(INTDIR)\STRAPX.OBJ"
	-@erase "$(INTDIR)\STRASC.OBJ"
	-@erase "$(INTDIR)\STRASS.OBJ"
	-@erase "$(INTDIR)\STRASX.OBJ"
	-@erase "$(INTDIR)\STRCOC.OBJ"
	-@erase "$(INTDIR)\STRCOPY.OBJ"
	-@erase "$(INTDIR)\STRCOS.OBJ"
	-@erase "$(INTDIR)\STRCOX.OBJ"
	-@erase "$(INTDIR)\STRFFNS.OBJ"
	-@erase "$(INTDIR)\STRFFS.OBJ"
	-@erase "$(INTDIR)\STRFIS.OBJ"
	-@erase "$(INTDIR)\STRFLNS.OBJ"
	-@erase "$(INTDIR)\STRFLS.OBJ"
	-@erase "$(INTDIR)\STRGET.OBJ"
	-@erase "$(INTDIR)\strgline.obj"
	-@erase "$(INTDIR)\STRINC.OBJ"
	-@erase "$(INTDIR)\STRING.OBJ"
	-@erase "$(INTDIR)\STRINS.OBJ"
	-@erase "$(INTDIR)\STRINX.OBJ"
	-@erase "$(INTDIR)\STRPUT.OBJ"
	-@erase "$(INTDIR)\STRREC.OBJ"
	-@erase "$(INTDIR)\STRREM.OBJ"
	-@erase "$(INTDIR)\STRRES.OBJ"
	-@erase "$(INTDIR)\STRREX.OBJ"
	-@erase "$(INTDIR)\STRRFIS.OBJ"
	-@erase "$(INTDIR)\STRXSTR.OBJ"
	-@erase "$(INTDIR)\TERMINAT.OBJ"
	-@erase "$(INTDIR)\UNEXPECT.OBJ"
	-@erase "$(INTDIR)\XDOMAIN.OBJ"
	-@erase "$(INTDIR)\XLOGIC.OBJ"
	-@erase "$(INTDIR)\XRANGE.OBJ"
	-@erase "$(INTDIR)\XRUNTIME.OBJ"
	-@erase "$(OUTDIR)\stdcppd.lib"
	-@erase "c:\trias\lib\stdcppd.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/stdcpp.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /GX /Zi /Od /Ob1 /I "..\stdcpp.inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /Fd"stdcppd/Stdcppd.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /GX /Zi /Od /Ob1 /I "..\stdcpp.inc" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)/Stdcpp4.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/Stdcppd.pdb" /c 
CPP_OBJS=.\stdcppd/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Stdcpp4.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"stdcppd\stdcppd.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/stdcppd.lib" 
LIB32_OBJS= \
	"$(INTDIR)\BADCAST.OBJ" \
	"$(INTDIR)\EXCEPTIO.OBJ" \
	"$(INTDIR)\fnamestr.obj" \
	"$(INTDIR)\INVALIDA.OBJ" \
	"$(INTDIR)\LENGTHER.OBJ" \
	"$(INTDIR)\NEW.OBJ" \
	"$(INTDIR)\OUTOFRAN.OBJ" \
	"$(INTDIR)\OVERFLOW.OBJ" \
	"$(INTDIR)\STRAPC.OBJ" \
	"$(INTDIR)\STRAPS.OBJ" \
	"$(INTDIR)\STRAPX.OBJ" \
	"$(INTDIR)\STRASC.OBJ" \
	"$(INTDIR)\STRASS.OBJ" \
	"$(INTDIR)\STRASX.OBJ" \
	"$(INTDIR)\STRCOC.OBJ" \
	"$(INTDIR)\STRCOPY.OBJ" \
	"$(INTDIR)\STRCOS.OBJ" \
	"$(INTDIR)\STRCOX.OBJ" \
	"$(INTDIR)\STRFFNS.OBJ" \
	"$(INTDIR)\STRFFS.OBJ" \
	"$(INTDIR)\STRFIS.OBJ" \
	"$(INTDIR)\STRFLNS.OBJ" \
	"$(INTDIR)\STRFLS.OBJ" \
	"$(INTDIR)\STRGET.OBJ" \
	"$(INTDIR)\strgline.obj" \
	"$(INTDIR)\STRINC.OBJ" \
	"$(INTDIR)\STRING.OBJ" \
	"$(INTDIR)\STRINS.OBJ" \
	"$(INTDIR)\STRINX.OBJ" \
	"$(INTDIR)\STRPUT.OBJ" \
	"$(INTDIR)\STRREC.OBJ" \
	"$(INTDIR)\STRREM.OBJ" \
	"$(INTDIR)\STRRES.OBJ" \
	"$(INTDIR)\STRREX.OBJ" \
	"$(INTDIR)\STRRFIS.OBJ" \
	"$(INTDIR)\STRXSTR.OBJ" \
	"$(INTDIR)\TERMINAT.OBJ" \
	"$(INTDIR)\UNEXPECT.OBJ" \
	"$(INTDIR)\XDOMAIN.OBJ" \
	"$(INTDIR)\XLOGIC.OBJ" \
	"$(INTDIR)\XRANGE.OBJ" \
	"$(INTDIR)\XRUNTIME.OBJ"

"$(OUTDIR)\stdcppd.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

# Begin Custom Build
OutDir=.\stdcppd
TargetPath=.\stdcppd\stdcppd.lib
TargetName=stdcppd
InputPath=.\stdcppd\stdcppd.lib
SOURCE=$(InputPath)

"c:\trias\lib\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   xcopy /F "$(TargetPath)" c:\trias\lib
   xcopy /F "$(OutDir)\$(TargetName).pdb" c:\trias\lib

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

# Name "Stdcpp - Win32 Release"
# Name "Stdcpp - Win32 Debug"

!IF  "$(CFG)" == "Stdcpp - Win32 Release"

!ELSEIF  "$(CFG)" == "Stdcpp - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\OVERFLOW.CPP
DEP_CPP_OVERF=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\OVERFLOW.OBJ" : $(SOURCE) $(DEP_CPP_OVERF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\INVALIDA.CPP
DEP_CPP_INVAL=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\INVALIDA.OBJ" : $(SOURCE) $(DEP_CPP_INVAL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\XRANGE.CPP
DEP_CPP_XRANG=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\XRANGE.OBJ" : $(SOURCE) $(DEP_CPP_XRANG) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRCOPY.CPP
DEP_CPP_STRCO=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRCOPY.OBJ" : $(SOURCE) $(DEP_CPP_STRCO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\XDOMAIN.CPP
DEP_CPP_XDOMA=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\XDOMAIN.OBJ" : $(SOURCE) $(DEP_CPP_XDOMA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRCOX.CPP
DEP_CPP_STRCOX=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRCOX.OBJ" : $(SOURCE) $(DEP_CPP_STRCOX) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRFLS.CPP
DEP_CPP_STRFL=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRFLS.OBJ" : $(SOURCE) $(DEP_CPP_STRFL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRFIS.CPP
DEP_CPP_STRFI=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRFIS.OBJ" : $(SOURCE) $(DEP_CPP_STRFI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRCOS.CPP
DEP_CPP_STRCOS=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRCOS.OBJ" : $(SOURCE) $(DEP_CPP_STRCOS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRFFS.CPP
DEP_CPP_STRFF=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRFFS.OBJ" : $(SOURCE) $(DEP_CPP_STRFF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRASX.CPP
DEP_CPP_STRAS=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRASX.OBJ" : $(SOURCE) $(DEP_CPP_STRAS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRAPX.CPP
DEP_CPP_STRAP=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRAPX.OBJ" : $(SOURCE) $(DEP_CPP_STRAP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\NEW.CPP
DEP_CPP_NEW_C=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\new.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\NEW.OBJ" : $(SOURCE) $(DEP_CPP_NEW_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRASS.CPP
DEP_CPP_STRASS=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRASS.OBJ" : $(SOURCE) $(DEP_CPP_STRASS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRAPS.CPP
DEP_CPP_STRAPS=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRAPS.OBJ" : $(SOURCE) $(DEP_CPP_STRAPS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\LENGTHER.CPP
DEP_CPP_LENGT=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\LENGTHER.OBJ" : $(SOURCE) $(DEP_CPP_LENGT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRGET.CPP
DEP_CPP_STRGE=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRGET.OBJ" : $(SOURCE) $(DEP_CPP_STRGE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\XRUNTIME.CPP
DEP_CPP_XRUNT=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\XRUNTIME.OBJ" : $(SOURCE) $(DEP_CPP_XRUNT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRREX.CPP
DEP_CPP_STRRE=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRREX.OBJ" : $(SOURCE) $(DEP_CPP_STRRE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\BADCAST.CPP
DEP_CPP_BADCA=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\BADCAST.OBJ" : $(SOURCE) $(DEP_CPP_BADCA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRCOC.CPP
DEP_CPP_STRCOC=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRCOC.OBJ" : $(SOURCE) $(DEP_CPP_STRCOC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRRES.CPP
DEP_CPP_STRRES=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRRES.OBJ" : $(SOURCE) $(DEP_CPP_STRRES) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\EXCEPTIO.CPP
DEP_CPP_EXCEP=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\EXCEPTIO.OBJ" : $(SOURCE) $(DEP_CPP_EXCEP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRINX.CPP
DEP_CPP_STRIN=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRINX.OBJ" : $(SOURCE) $(DEP_CPP_STRIN) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRREM.CPP
DEP_CPP_STRREM=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRREM.OBJ" : $(SOURCE) $(DEP_CPP_STRREM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRINS.CPP
DEP_CPP_STRINS=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRINS.OBJ" : $(SOURCE) $(DEP_CPP_STRINS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRASC.CPP
DEP_CPP_STRASC=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRASC.OBJ" : $(SOURCE) $(DEP_CPP_STRASC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRAPC.CPP
DEP_CPP_STRAPC=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRAPC.OBJ" : $(SOURCE) $(DEP_CPP_STRAPC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRFLNS.CPP
DEP_CPP_STRFLN=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRFLNS.OBJ" : $(SOURCE) $(DEP_CPP_STRFLN) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRREC.CPP
DEP_CPP_STRREC=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRREC.OBJ" : $(SOURCE) $(DEP_CPP_STRREC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\OUTOFRAN.CPP
DEP_CPP_OUTOF=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\OUTOFRAN.OBJ" : $(SOURCE) $(DEP_CPP_OUTOF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRRFIS.CPP
DEP_CPP_STRRF=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRRFIS.OBJ" : $(SOURCE) $(DEP_CPP_STRRF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRING.CPP
DEP_CPP_STRING=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRING.OBJ" : $(SOURCE) $(DEP_CPP_STRING) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRINC.CPP
DEP_CPP_STRINC=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRINC.OBJ" : $(SOURCE) $(DEP_CPP_STRINC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRFFNS.CPP
DEP_CPP_STRFFN=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRFFNS.OBJ" : $(SOURCE) $(DEP_CPP_STRFFN) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\XLOGIC.CPP
DEP_CPP_XLOGI=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\XLOGIC.OBJ" : $(SOURCE) $(DEP_CPP_XLOGI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRPUT.CPP
DEP_CPP_STRPU=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRPUT.OBJ" : $(SOURCE) $(DEP_CPP_STRPU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TERMINAT.CPP
DEP_CPP_TERMI=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\TERMINAT.OBJ" : $(SOURCE) $(DEP_CPP_TERMI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\UNEXPECT.CPP
DEP_CPP_UNEXP=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\UNEXPECT.OBJ" : $(SOURCE) $(DEP_CPP_UNEXP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\fnamestr.cpp
DEP_CPP_FNAME=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\fnamestr.h"\
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
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\fnamestr.obj" : $(SOURCE) $(DEP_CPP_FNAME) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\STRXSTR.CPP
DEP_CPP_STRXS=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\STRXSTR.OBJ" : $(SOURCE) $(DEP_CPP_STRXS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\strgline.cpp
DEP_CPP_STRGL=\
	{$(INCLUDE)}"\bool.h"\
	{$(INCLUDE)}"\config\_compile.h"\
	{$(INCLUDE)}"\config\_platfrm.h"\
	{$(INCLUDE)}"\config\compiler.h"\
	{$(INCLUDE)}"\config\local.h"\
	{$(INCLUDE)}"\config\platform.h"\
	{$(INCLUDE)}"\defines.hpp"\
	{$(INCLUDE)}"\exceptio.hpp"\
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
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\yxvals.h"\
	

"$(INTDIR)\strgline.obj" : $(SOURCE) $(DEP_CPP_STRGL) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
