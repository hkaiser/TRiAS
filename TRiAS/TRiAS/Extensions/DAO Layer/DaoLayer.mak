# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=DaoLayer - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to DaoLayer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DaoLayer - Win32 Release" && "$(CFG)" !=\
 "DaoLayer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DaoLayer.mak" CFG="DaoLayer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DaoLayer - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DaoLayer - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "DaoLayer - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "DaoLayer - Win32 Release"

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
TargetName=DaoLayer
# End Custom Macros

ALL : "$(OUTDIR)\DaoLayer.ebn" "c:\trias.mvc\trias200.rel\DaoLayer.ebn"

CLEAN : 
	-@erase "$(INTDIR)\Daoextf.obj"
	-@erase "$(INTDIR)\DaoLayer.obj"
	-@erase "$(INTDIR)\DaoLayer.pch"
	-@erase "$(INTDIR)\DaoLayer.res"
	-@erase "$(INTDIR)\Dbdao.obj"
	-@erase "$(INTDIR)\jumptab.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\strcvrt.obj"
	-@erase "$(INTDIR)\WinVersn.obj"
	-@erase "$(OUTDIR)\DaoLayer.ebn"
	-@erase "$(OUTDIR)\DaoLayer.exp"
	-@erase "$(OUTDIR)\DaoLayer.lib"
	-@erase "c:\trias.mvc\trias200.rel\DaoLayer.ebn"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "EBWIN32" /D DLLEXPORT=__declspec(dllexport) /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "EBWIN32" /D\
 DLLEXPORT=__declspec(dllexport) /Fp"$(INTDIR)/DaoLayer.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL" /d "_USE_DEFAULT_PROPERTYGET"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/DaoLayer.res" /d "NDEBUG" /d "_AFXDLL" /d\
 "_USE_DEFAULT_PROPERTYGET" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DaoLayer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ebn.lib /nologo /subsystem:windows /dll /machine:I386 /stub:"rights.exe" /out:"Release/DaoLayer.ebn"
LINK32_FLAGS=ebn.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/DaoLayer.pdb" /machine:I386 /def:".\DaoLayer.def"\
 /stub:"rights.exe" /out:"$(OUTDIR)/DaoLayer.ebn"\
 /implib:"$(OUTDIR)/DaoLayer.lib" 
DEF_FILE= \
	".\DaoLayer.def"
LINK32_OBJS= \
	"$(INTDIR)\Daoextf.obj" \
	"$(INTDIR)\DaoLayer.obj" \
	"$(INTDIR)\DaoLayer.res" \
	"$(INTDIR)\Dbdao.obj" \
	"$(INTDIR)\jumptab.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\strcvrt.obj" \
	"$(INTDIR)\WinVersn.obj"

"$(OUTDIR)\DaoLayer.ebn" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Release\DaoLayer.ebn
TargetName=DaoLayer
InputPath=.\Release\DaoLayer.ebn
SOURCE=$(InputPath)

"c:\trias.mvc\trias200.rel\$(TargetName).ebn" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   copy "$(TargetPath)" c:\trias.mvc\trias200.rel

# End Custom Build

!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"

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
TargetName=DaoLayed
# End Custom Macros

ALL : "$(OUTDIR)\DaoLayed.ebn" "$(OUTDIR)\DaoLayer.bsc"\
 "c:\trias.mvc\trias200\DaoLayed.ebn"

CLEAN : 
	-@erase "$(INTDIR)\Daoextf.obj"
	-@erase "$(INTDIR)\Daoextf.sbr"
	-@erase "$(INTDIR)\DaoLayer.obj"
	-@erase "$(INTDIR)\DaoLayer.pch"
	-@erase "$(INTDIR)\DaoLayer.res"
	-@erase "$(INTDIR)\DaoLayer.sbr"
	-@erase "$(INTDIR)\Dbdao.obj"
	-@erase "$(INTDIR)\Dbdao.sbr"
	-@erase "$(INTDIR)\jumptab.obj"
	-@erase "$(INTDIR)\jumptab.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\strcvrt.obj"
	-@erase "$(INTDIR)\strcvrt.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\WinVersn.obj"
	-@erase "$(INTDIR)\WinVersn.sbr"
	-@erase "$(OUTDIR)\DaoLayed.ebn"
	-@erase "$(OUTDIR)\DaoLayed.exp"
	-@erase "$(OUTDIR)\DaoLayed.ilk"
	-@erase "$(OUTDIR)\DaoLayed.lib"
	-@erase "$(OUTDIR)\DaoLayed.pdb"
	-@erase "$(OUTDIR)\DaoLayer.bsc"
	-@erase "c:\trias.mvc\trias200\DaoLayed.ebn"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "EBWIN32" /D DLLEXPORT=__declspec(dllexport) /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "EBWIN32" /D\
 DLLEXPORT=__declspec(dllexport) /FR"$(INTDIR)/" /Fp"$(INTDIR)/DaoLayer.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL" /d "_USE_DEFAULT_PROPERTYGET"
RSC_PROJ=/l 0x407 /fo"$(INTDIR)/DaoLayer.res" /d "_DEBUG" /d "_AFXDLL" /d\
 "_USE_DEFAULT_PROPERTYGET" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DaoLayer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Daoextf.sbr" \
	"$(INTDIR)\DaoLayer.sbr" \
	"$(INTDIR)\Dbdao.sbr" \
	"$(INTDIR)\jumptab.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\strcvrt.sbr" \
	"$(INTDIR)\WinVersn.sbr"

"$(OUTDIR)\DaoLayer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ebn.lib /nologo /subsystem:windows /dll /debug /machine:I386 /stub:"rights.exe" /out:"Debug/DaoLayed.ebn"
LINK32_FLAGS=ebn.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/DaoLayed.pdb" /debug /machine:I386 /def:".\Daolayed.def"\
 /stub:"rights.exe" /out:"$(OUTDIR)/DaoLayed.ebn"\
 /implib:"$(OUTDIR)/DaoLayed.lib" 
DEF_FILE= \
	".\Daolayed.def"
LINK32_OBJS= \
	"$(INTDIR)\Daoextf.obj" \
	"$(INTDIR)\DaoLayer.obj" \
	"$(INTDIR)\DaoLayer.res" \
	"$(INTDIR)\Dbdao.obj" \
	"$(INTDIR)\jumptab.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\strcvrt.obj" \
	"$(INTDIR)\WinVersn.obj"

"$(OUTDIR)\DaoLayed.ebn" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build - Copying Target to Destination ...
TargetPath=.\Debug\DaoLayed.ebn
TargetName=DaoLayed
InputPath=.\Debug\DaoLayed.ebn
SOURCE=$(InputPath)

"c:\trias.mvc\trias200\$(TargetName).ebn" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
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

# Name "DaoLayer - Win32 Release"
# Name "DaoLayer - Win32 Debug"

!IF  "$(CFG)" == "DaoLayer - Win32 Release"

!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "DaoLayer - Win32 Release"

!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DaoLayer.cpp
DEP_CPP_DAOLA=\
	".\DaoLayer.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DaoLayer - Win32 Release"


"$(INTDIR)\DaoLayer.obj" : $(SOURCE) $(DEP_CPP_DAOLA) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"


!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"


"$(INTDIR)\DaoLayer.obj" : $(SOURCE) $(DEP_CPP_DAOLA) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"

"$(INTDIR)\DaoLayer.sbr" : $(SOURCE) $(DEP_CPP_DAOLA) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DaoLayer.def

!IF  "$(CFG)" == "DaoLayer - Win32 Release"

!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DaoLayer - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "EBWIN32" /D\
 DLLEXPORT=__declspec(dllexport) /Fp"$(INTDIR)/DaoLayer.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DaoLayer.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "EBWIN32" /D\
 DLLEXPORT=__declspec(dllexport) /FR"$(INTDIR)/" /Fp"$(INTDIR)/DaoLayer.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DaoLayer.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Daoextf.cpp
DEP_CPP_DAOEX=\
	".\Daoextf.h"\
	".\ebargs.h"\
	".\jumptab.h"\
	".\StdAfx.h"\
	".\strcvrt.h"\
	".\WinVersn.h"\
	

!IF  "$(CFG)" == "DaoLayer - Win32 Release"


"$(INTDIR)\Daoextf.obj" : $(SOURCE) $(DEP_CPP_DAOEX) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"
   $(CPP) /nologo /MD /W3 /WX /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "EBWIN32" /D\
 DLLEXPORT=__declspec(dllexport) /Fp"$(INTDIR)/DaoLayer.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE)


!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"

# ADD CPP /Gi

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D\
 "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "EBWIN32" /D\
 DLLEXPORT=__declspec(dllexport) /FR"$(INTDIR)/" /Fp"$(INTDIR)/DaoLayer.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\Daoextf.obj" : $(SOURCE) $(DEP_CPP_DAOEX) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"
   $(BuildCmds)

"$(INTDIR)\Daoextf.sbr" : $(SOURCE) $(DEP_CPP_DAOEX) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\res\Daoextp.rc
# PROP Exclude_From_Build 1
# End Source File
################################################################################
# Begin Source File

SOURCE=.\jumptab.cpp
DEP_CPP_JUMPT=\
	".\Daoextf.h"\
	".\jumptab.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DaoLayer - Win32 Release"


"$(INTDIR)\jumptab.obj" : $(SOURCE) $(DEP_CPP_JUMPT) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"


!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"


"$(INTDIR)\jumptab.obj" : $(SOURCE) $(DEP_CPP_JUMPT) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"

"$(INTDIR)\jumptab.sbr" : $(SOURCE) $(DEP_CPP_JUMPT) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\strcvrt.cpp
DEP_CPP_STRCV=\
	".\StdAfx.h"\
	".\strcvrt.h"\
	

!IF  "$(CFG)" == "DaoLayer - Win32 Release"


"$(INTDIR)\strcvrt.obj" : $(SOURCE) $(DEP_CPP_STRCV) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"


!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"


"$(INTDIR)\strcvrt.obj" : $(SOURCE) $(DEP_CPP_STRCV) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"

"$(INTDIR)\strcvrt.sbr" : $(SOURCE) $(DEP_CPP_STRCV) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Dbdao.cpp
DEP_CPP_DBDAO=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "DaoLayer - Win32 Release"


"$(INTDIR)\Dbdao.obj" : $(SOURCE) $(DEP_CPP_DBDAO) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"


!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"


"$(INTDIR)\Dbdao.obj" : $(SOURCE) $(DEP_CPP_DBDAO) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"

"$(INTDIR)\Dbdao.sbr" : $(SOURCE) $(DEP_CPP_DBDAO) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DaoLayer.rc
DEP_RSC_DAOLAY=\
	".\daolayer.rcv"\
	".\res\daoextf.rc"\
	

"$(INTDIR)\DaoLayer.res" : $(SOURCE) $(DEP_RSC_DAOLAY) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\WinVersn.cpp
DEP_CPP_WINVE=\
	".\StdAfx.h"\
	".\WinVersn.h"\
	

!IF  "$(CFG)" == "DaoLayer - Win32 Release"


"$(INTDIR)\WinVersn.obj" : $(SOURCE) $(DEP_CPP_WINVE) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"


!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"


"$(INTDIR)\WinVersn.obj" : $(SOURCE) $(DEP_CPP_WINVE) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"

"$(INTDIR)\WinVersn.sbr" : $(SOURCE) $(DEP_CPP_WINVE) "$(INTDIR)"\
 "$(INTDIR)\DaoLayer.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Daolayed.def

!IF  "$(CFG)" == "DaoLayer - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "DaoLayer - Win32 Debug"

# PROP Exclude_From_Build 0

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
