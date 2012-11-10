# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=Tfrm32l - Win32 Framework LIB Debug
!MESSAGE No configuration specified.  Defaulting to Tfrm32l - Win32 Framework\
 LIB Debug.
!ENDIF 

!IF "$(CFG)" != "Tfrm32l - Win32 Framework LIB Release" && "$(CFG)" !=\
 "Tfrm32l - Win32 Framework LIB Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tfrm4l.mak" CFG="Tfrm32l - Win32 Framework LIB Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tfrm32l - Win32 Framework LIB Release" (based on\
 "Win32 (x86) Static Library")
!MESSAGE "Tfrm32l - Win32 Framework LIB Debug" (based on\
 "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "Tfrm32l - Win32 Framework LIB Debug"
CPP=cl.exe

!IF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Tfrmwrkl.lib"

CLEAN : 
	-@erase "$(INTDIR)\APPIDLE.OBJ"
	-@erase "$(INTDIR)\APPINIT.OBJ"
	-@erase "$(INTDIR)\APPSTART.OBJ"
	-@erase "$(INTDIR)\APPSTRT2.OBJ"
	-@erase "$(INTDIR)\COMMONVU.OBJ"
	-@erase "$(INTDIR)\TFRMLIB.OBJ"
	-@erase "$(INTDIR)\tfrmlib.pch"
	-@erase "$(OUTDIR)\Tfrmwrkl.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/TFRM32L.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "__TFLIB__" /Fp"Release/tfrmlib.pch" /Yu"tfrmpre.hxx" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "__TFLIB__" /Fp"$(INTDIR)/tfrmlib.pch" /Yu"tfrmpre.hxx"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Tfrm4l.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Release\Tfrmwrkl.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/Tfrmwrkl.lib" 
LIB32_OBJS= \
	"$(INTDIR)\APPIDLE.OBJ" \
	"$(INTDIR)\APPINIT.OBJ" \
	"$(INTDIR)\APPSTART.OBJ" \
	"$(INTDIR)\APPSTRT2.OBJ" \
	"$(INTDIR)\COMMONVU.OBJ" \
	"$(INTDIR)\TFRMLIB.OBJ"

"$(OUTDIR)\Tfrmwrkl.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug4"
# PROP Intermediate_Dir "Debug4"
OUTDIR=.\Debug4
INTDIR=.\Debug4

ALL : "$(OUTDIR)\tfrm32ld.lib"

CLEAN : 
	-@erase "$(INTDIR)\APPIDLE.OBJ"
	-@erase "$(INTDIR)\APPINIT.OBJ"
	-@erase "$(INTDIR)\APPSTART.OBJ"
	-@erase "$(INTDIR)\APPSTRT2.OBJ"
	-@erase "$(INTDIR)\COMMONVU.OBJ"
	-@erase "$(INTDIR)\tfrm32ld.idb"
	-@erase "$(INTDIR)\tfrm32ld.pdb"
	-@erase "$(INTDIR)\TFRMLIB.OBJ"
	-@erase "$(INTDIR)\tfrmlib.pch"
	-@erase "$(OUTDIR)\tfrm32ld.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/TFRM32L.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "__CV__" /D "STRICT" /D "__TFLIB__" /Fp"Debug4/tfrmlib.pch" /Yu"tfrmpre.hxx" /Fd"Debug4/tfrm32ld.pdb" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "__TFLIB__" /Fp"$(INTDIR)/tfrmlib.pch"\
 /Yu"tfrmpre.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/tfrm32ld.pdb" /c 
CPP_OBJS=.\Debug4/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Tfrm4l.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug4\tfrm32ld.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/tfrm32ld.lib" 
LIB32_OBJS= \
	"$(INTDIR)\APPIDLE.OBJ" \
	"$(INTDIR)\APPINIT.OBJ" \
	"$(INTDIR)\APPSTART.OBJ" \
	"$(INTDIR)\APPSTRT2.OBJ" \
	"$(INTDIR)\COMMONVU.OBJ" \
	"$(INTDIR)\TFRMLIB.OBJ"

"$(OUTDIR)\tfrm32ld.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Tfrm32l - Win32 Framework LIB Release"
# Name "Tfrm32l - Win32 Framework LIB Debug"

!IF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Release"

!ELSEIF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\APPIDLE.CXX

!IF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Release"

DEP_CPP_APPID=\
	".\TFRMLIB.HXX"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	
# ADD CPP /Yu"tfrmlib.hxx"

"$(INTDIR)\APPIDLE.OBJ" : $(SOURCE) $(DEP_CPP_APPID) "$(INTDIR)"\
 "$(INTDIR)\tfrmlib.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "__TFLIB__" /Fp"$(INTDIR)/tfrmlib.pch" /Yu"tfrmlib.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Debug"

DEP_CPP_APPID=\
	"..\TFRMWORK.INC\_runtime.hxx"\
	".\TFRMLIB.HXX"\
	{$(INCLUDE)}"\_comonvu.hxx"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocinfo"\
	{$(INCLUDE)}"\xlocinfo.h"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xmemory"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	
# ADD CPP /Yu"tfrmlib.hxx"

"$(INTDIR)\APPIDLE.OBJ" : $(SOURCE) $(DEP_CPP_APPID) "$(INTDIR)"\
 "$(INTDIR)\tfrmlib.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "__TFLIB__" /Fp"$(INTDIR)/tfrmlib.pch"\
 /Yu"tfrmlib.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/tfrm32ld.pdb" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\COMMONVU.CXX

!IF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Release"

DEP_CPP_COMMO=\
	".\TFRMLIB.HXX"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	
# ADD CPP /Yu"tfrmlib.hxx"

"$(INTDIR)\COMMONVU.OBJ" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"\
 "$(INTDIR)\tfrmlib.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "__TFLIB__" /Fp"$(INTDIR)/tfrmlib.pch" /Yu"tfrmlib.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Debug"

DEP_CPP_COMMO=\
	"..\TFRMWORK.INC\_runtime.hxx"\
	".\TFRMLIB.HXX"\
	{$(INCLUDE)}"\_comonvu.hxx"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocinfo"\
	{$(INCLUDE)}"\xlocinfo.h"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xmemory"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	
# ADD CPP /Yu"tfrmlib.hxx"

"$(INTDIR)\COMMONVU.OBJ" : $(SOURCE) $(DEP_CPP_COMMO) "$(INTDIR)"\
 "$(INTDIR)\tfrmlib.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "__TFLIB__" /Fp"$(INTDIR)/tfrmlib.pch"\
 /Yu"tfrmlib.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/tfrm32ld.pdb" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\APPINIT.CXX

!IF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Release"

DEP_CPP_APPIN=\
	".\TFRMLIB.HXX"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	
# ADD CPP /Yu"tfrmlib.hxx"

"$(INTDIR)\APPINIT.OBJ" : $(SOURCE) $(DEP_CPP_APPIN) "$(INTDIR)"\
 "$(INTDIR)\tfrmlib.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "__TFLIB__" /Fp"$(INTDIR)/tfrmlib.pch" /Yu"tfrmlib.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Debug"

DEP_CPP_APPIN=\
	"..\TFRMWORK.INC\_runtime.hxx"\
	".\TFRMLIB.HXX"\
	{$(INCLUDE)}"\_comonvu.hxx"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocinfo"\
	{$(INCLUDE)}"\xlocinfo.h"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xmemory"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	
# ADD CPP /Yu"tfrmlib.hxx"

"$(INTDIR)\APPINIT.OBJ" : $(SOURCE) $(DEP_CPP_APPIN) "$(INTDIR)"\
 "$(INTDIR)\tfrmlib.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "__TFLIB__" /Fp"$(INTDIR)/tfrmlib.pch"\
 /Yu"tfrmlib.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/tfrm32ld.pdb" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\APPSTART.CXX

!IF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Release"

DEP_CPP_APPST=\
	".\TFRMLIB.HXX"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	
# ADD CPP /Yu"tfrmlib.hxx"

"$(INTDIR)\APPSTART.OBJ" : $(SOURCE) $(DEP_CPP_APPST) "$(INTDIR)"\
 "$(INTDIR)\tfrmlib.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "__TFLIB__" /Fp"$(INTDIR)/tfrmlib.pch" /Yu"tfrmlib.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Debug"

DEP_CPP_APPST=\
	"..\TFRMWORK.INC\_runtime.hxx"\
	".\TFRMLIB.HXX"\
	{$(INCLUDE)}"\_comonvu.hxx"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocinfo"\
	{$(INCLUDE)}"\xlocinfo.h"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xmemory"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	
# ADD CPP /Yu"tfrmlib.hxx"

"$(INTDIR)\APPSTART.OBJ" : $(SOURCE) $(DEP_CPP_APPST) "$(INTDIR)"\
 "$(INTDIR)\tfrmlib.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "__TFLIB__" /Fp"$(INTDIR)/tfrmlib.pch"\
 /Yu"tfrmlib.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/tfrm32ld.pdb" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\APPSTRT2.CXX

!IF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Release"

DEP_CPP_APPSTR=\
	".\TFRMLIB.HXX"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\use_ansi.h"\
	
# ADD CPP /Yu"tfrmlib.hxx"

"$(INTDIR)\APPSTRT2.OBJ" : $(SOURCE) $(DEP_CPP_APPSTR) "$(INTDIR)"\
 "$(INTDIR)\tfrmlib.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "__TFLIB__" /Fp"$(INTDIR)/tfrmlib.pch" /Yu"tfrmlib.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Debug"

DEP_CPP_APPSTR=\
	"..\TFRMWORK.INC\_runtime.hxx"\
	".\TFRMLIB.HXX"\
	{$(INCLUDE)}"\_comonvu.hxx"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\cerrno"\
	{$(INCLUDE)}"\cfloat"\
	{$(INCLUDE)}"\climits"\
	{$(INCLUDE)}"\cstddef"\
	{$(INCLUDE)}"\cstdio"\
	{$(INCLUDE)}"\cstdlib"\
	{$(INCLUDE)}"\cstring"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\cwchar"\
	{$(INCLUDE)}"\exception"\
	{$(INCLUDE)}"\ios"\
	{$(INCLUDE)}"\iosfwd"\
	{$(INCLUDE)}"\istream"\
	{$(INCLUDE)}"\memory"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\new"\
	{$(INCLUDE)}"\ostream"\
	{$(INCLUDE)}"\stdexcept"\
	{$(INCLUDE)}"\streambuf"\
	{$(INCLUDE)}"\STRING"\
	{$(INCLUDE)}"\typeinfo"\
	{$(INCLUDE)}"\use_ansi.h"\
	{$(INCLUDE)}"\utility"\
	{$(INCLUDE)}"\Winfns.h"\
	{$(INCLUDE)}"\xiosbase"\
	{$(INCLUDE)}"\xlocale"\
	{$(INCLUDE)}"\xlocinfo"\
	{$(INCLUDE)}"\xlocinfo.h"\
	{$(INCLUDE)}"\xlocnum"\
	{$(INCLUDE)}"\xmemory"\
	{$(INCLUDE)}"\xstddef"\
	{$(INCLUDE)}"\xstring"\
	{$(INCLUDE)}"\xutility"\
	{$(INCLUDE)}"\yvals.h"\
	
# ADD CPP /Yu"tfrmlib.hxx"

"$(INTDIR)\APPSTRT2.OBJ" : $(SOURCE) $(DEP_CPP_APPSTR) "$(INTDIR)"\
 "$(INTDIR)\tfrmlib.pch"
   $(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "__TFLIB__" /Fp"$(INTDIR)/tfrmlib.pch"\
 /Yu"tfrmlib.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/tfrm32ld.pdb" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TFRMLIB.CXX

!IF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Release"

DEP_CPP_TFRML=\
	"..\TFRMWORK.INC\_runtime.hxx"\
	".\TFRMLIB.HXX"\
	{$(INCLUDE)}"\_comonvu.hxx"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Winfns.h"\
	
# ADD CPP /Yc"tfrmlib.hxx"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "__CV__" /D "STRICT" /D "__TFLIB__" /Fp"$(INTDIR)/tfrmlib.pch" /Yc"tfrmlib.hxx"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\TFRMLIB.OBJ" : $(SOURCE) $(DEP_CPP_TFRML) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\tfrmlib.pch" : $(SOURCE) $(DEP_CPP_TFRML) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tfrm32l - Win32 Framework LIB Debug"

DEP_CPP_TFRML=\
	"..\TFRMWORK.INC\_runtime.hxx"\
	".\TFRMLIB.HXX"\
	{$(INCLUDE)}"\_comonvu.hxx"\
	{$(INCLUDE)}"\_DSFIX.HXX"\
	{$(INCLUDE)}"\_link.hxx"\
	{$(INCLUDE)}"\Cv_imp.hxx"\
	{$(INCLUDE)}"\Cv_impi.hxx"\
	{$(INCLUDE)}"\Cvd.hxx"\
	{$(INCLUDE)}"\CVRESID.H"\
	{$(INCLUDE)}"\MESSAGES.H"\
	{$(INCLUDE)}"\tstring"\
	{$(INCLUDE)}"\tstring.hpp"\
	{$(INCLUDE)}"\Winfns.h"\
	
# ADD CPP /Yc"tfrmlib.hxx"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "__CV__" /D "STRICT" /D "__TFLIB__" /Fp"$(INTDIR)/tfrmlib.pch"\
 /Yc"tfrmlib.hxx" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/tfrm32ld.pdb" /c $(SOURCE) \
	

"$(INTDIR)\TFRMLIB.OBJ" : $(SOURCE) $(DEP_CPP_TFRML) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\tfrmlib.pch" : $(SOURCE) $(DEP_CPP_TFRML) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
