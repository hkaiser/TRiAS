# Microsoft Developer Studio Project File - Name="lmfcx42" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=lmfcx42 - Win32 Release
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "lmfcx42.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "lmfcx42.mak" CFG="lmfcx42 - Win32 Release"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "lmfcx42 - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "lmfcx42 - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/lmfcx42", PCDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "lmfcx42 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "_Release"
# PROP Intermediate_Dir "_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /D "NDEBUG" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL" /d "_AFXEXT"
# SUBTRACT RSC /x
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# SUBTRACT LINK32 /incremental:yes /map
# Begin Custom Build - Copy Target
OutDir=.\_Release
TargetName=lmfcx42
InputPath=.\_Release\lmfcx42.dll
SOURCE="$(InputPath)"

"$(WINDIR)\system32\$(TARGETNAME).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(OutDir)\$(TargetName).dll $(WINDIR)\system32 
	xcopy /F $(OutDir)\$(TargetName).pdb $(WINDIR)\system32 
	xcopy /F $(OutDir)\$(TargetName).dll $(TRIASDIR_R) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASDIR_R) 
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB) 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=NDEBUG VERSION
# End Special Build Tool

!ELSEIF  "$(CFG)" == "lmfcx42 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "_Debug"
# PROP Intermediate_Dir "_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I ".\lmfcx" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /D "_DEBUG" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL" /d "_AFXEXT"
# SUBTRACT RSC /x
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o".\_Debug/lmfcx42D.bsc"
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\_Debug/lmfcx42D.dll"
# SUBTRACT LINK32 /incremental:no /map
# Begin Custom Build - Copy Target
OutDir=.\_Debug
TargetName=lmfcx42D
InputPath=.\_Debug\lmfcx42D.dll
SOURCE="$(InputPath)"

"$(WINDIR)\system32\$(TARGETNAME).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(OutDir)\$(TargetName).dll $(WINDIR)\system32 
	xcopy /F $(OutDir)\$(TargetName).pdb $(WINDIR)\system32 
	xcopy /F $(OutDir)\$(TargetName).dll $(TRIASDIR_D) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASDIR_D) 
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB) 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Cmds=nmake -nologo -f Version.mak CFG=_DEBUG VERSION
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "lmfcx42 - Win32 Release"
# Name "lmfcx42 - Win32 Debug"
# Begin Group "Lmfcx42"

# PROP Default_Filter ""
# Begin Group "Redist"

# PROP Default_Filter ""
# Begin Group "Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lmfcx\LAFX.H
# End Source File
# Begin Source File

SOURCE=.\lmfcx\LAFX_DOS.H
# End Source File
# Begin Source File

SOURCE=.\lmfcx\LAFXCOLL.H
# End Source File
# Begin Source File

SOURCE=.\LafxPriv.h
# End Source File
# Begin Source File

SOURCE=.\lmfcx\LAFXVER_.H
# End Source File
# Begin Source File

SOURCE=.\lmfcx\LAFXWIN.H
# End Source File
# End Group
# Begin Group "Inline"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lmfcx\LAFX.INL
# End Source File
# Begin Source File

SOURCE=.\lmfcx\LAFXCOLL.INL
# End Source File
# Begin Source File

SOURCE=.\lmfcx\LAFXWIN.INL
# End Source File
# End Group
# End Group
# Begin Group "Lmfcx Base"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\array_db.cpp
# End Source File
# Begin Source File

SOURCE=.\array_pl.cpp
# End Source File
# Begin Source File

SOURCE=.\array_pt.cpp
# End Source File
# Begin Source File

SOURCE=.\Constnts.cpp
# End Source File
# Begin Source File

SOURCE=.\cpath.cpp
# End Source File
# Begin Source File

SOURCE=.\euklid1.cpp
# End Source File
# Begin Source File

SOURCE=.\euklid2.cpp
# End Source File
# Begin Source File

SOURCE=.\extstrg.cpp
# End Source File
# Begin Source File

SOURCE=.\getopt.cpp
# End Source File
# Begin Source File

SOURCE=.\map_dwo.cpp
# End Source File
# Begin Source File

SOURCE=.\mk_matrx.cpp
# End Source File
# Begin Source File

SOURCE=.\mk_vectr.cpp
# End Source File
# Begin Source File

SOURCE=.\rexpstr.cpp
# End Source File
# Begin Source File

SOURCE=.\tree.cpp
# End Source File
# End Group
# Begin Group "Lmfcx Win"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BmpBtn.CPP
# End Source File
# Begin Source File

SOURCE=.\cdcex.cpp
# End Source File
# Begin Source File

SOURCE=.\coordbg.cpp
# End Source File
# Begin Source File

SOURCE=.\dirselec.cpp
# End Source File
# Begin Source File

SOURCE=.\listupdn.cpp
# End Source File
# End Group
# Begin Group "Lmfcx Support"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lafxinl1.cpp
# End Source File
# Begin Source File

SOURCE=.\lafxinl2.cpp
# End Source File
# End Group
# End Group
# Begin Group "DLL Data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lmfcx42.cpp
# End Source File
# Begin Source File

SOURCE=.\lmfcx42.idl

!IF  "$(CFG)" == "lmfcx42 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\lmfcx42.idl
InputName=lmfcx42

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "lmfcx42 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\lmfcx42.idl
InputName=lmfcx42

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\STDAFX.CPP
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\STDAFX.H
# End Source File
# Begin Source File

SOURCE=.\Version.mak

!IF  "$(CFG)" == "lmfcx42 - Win32 Release"

# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\LMFCX42.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\LMFCX42.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\LMFCX42.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "lmfcx42 - Win32 Debug"

# Begin Custom Build
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\LMFCX42.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\LMFCX42.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\LMFCX42.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LMFCX42.def
# End Source File
# Begin Source File

SOURCE=.\LMFCX42.rcv
# End Source File
# Begin Source File

SOURCE=.\LMFCX42.ver
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\help\lmfcx42.d
# End Source File
# Begin Source File

SOURCE=.\lmfcx42.mc

!IF  "$(CFG)" == "lmfcx42 - Win32 Release"

# Begin Custom Build
InputPath=.\lmfcx42.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\lmfcx42.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "lmfcx42 - Win32 Debug"

# Begin Custom Build
InputPath=.\lmfcx42.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\lmfcx42.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter ""
# Begin Group "lmfcx"

# PROP Default_Filter ""
# Begin Group "res"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\lmfcx\res\BTNADD_D.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\BTNADD_F.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\BTNADD_U.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\BTNADD_X.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\BTNDEL_D.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\BTNDEL_F.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\BTNDEL_U.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\BTNDEL_X.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\BTNDN_D.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\BTNDN_F.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\BTNDN_U.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\BTNDN_X.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\BTNUP_D.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\BTNUP_F.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\BTNUP_U.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\BTNUP_X.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\MSOL_CLO.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\MSOL_LEA.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\MSOL_MIN.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\MSOL_OPN.BMP
# End Source File
# Begin Source File

SOURCE=.\lmfcx\res\MSOL_PLU.BMP
# End Source File
# End Group
# Begin Source File

SOURCE=.\lmfcx\lmfcx42Res.h
# End Source File
# Begin Source File

SOURCE=.\lmfcx\lmfcx42Res.rc
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=.\lmfcx42.rc

!IF  "$(CFG)" == "lmfcx42 - Win32 Release"

# ADD BASE RSC /l 0x407
# ADD RSC /l 0x407

!ELSEIF  "$(CFG)" == "lmfcx42 - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res\msg00407.bin
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# End Target
# End Project
