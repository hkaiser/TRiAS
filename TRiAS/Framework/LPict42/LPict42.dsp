# Microsoft Developer Studio Project File - Name="LPict42" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=LPICT42 - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "LPict42.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LPict42.mak" CFG="LPICT42 - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LPict42 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LPict42 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/LPict42", DFDAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LPict42 - Win32 Release"

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
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /I "..\lmfcx42" /I "D:\TRiASDev.MVC\FrameWrk\LEADTOOLS\Include\ClassLib" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /D "NDEBUG" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /i "$(TRIASINCLUDE)" /d "NDEBUG" /d "_AFXDLL" /d "_AFXEXT"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ltwvc_n.lib delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /libpath:"D:\TRiASDev.MVC\FrameWrk\LEADTOOLS\Lib" /delayload:ltwvc13n.dll
# SUBTRACT LINK32 /incremental:yes
# Begin Custom Build - Copy Target
OutDir=.\_Release
TargetName=LPict42
InputPath=.\_Release\LPict42.dll
SOURCE="$(InputPath)"

"$(WINDIR)\system32\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
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

!ELSEIF  "$(CFG)" == "LPict42 - Win32 Debug"

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
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "..\lmfcx42" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_AFXEXT" /D "_DEBUG" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL" /d "_AFXEXT"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o".\_Debug/LPict42D.bsc"
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ltwvc_n.lib delayimp.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\_Debug/LPict42D.dll" /delayload:ltwvc13n.dll /opt:noref
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copy Target
OutDir=.\_Debug
TargetName=LPict42D
InputPath=.\_Debug\LPict42D.dll
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

# Name "LPict42 - Win32 Release"
# Name "LPict42 - Win32 Debug"
# Begin Group "Picture"

# PROP Default_Filter ""
# Begin Group "PictureBase"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LeadToolsPicture.cpp
# End Source File
# Begin Source File

SOURCE=.\LPICT\LeadToolsPicture.h
# End Source File
# Begin Source File

SOURCE=.\PgrHolder.cpp
# End Source File
# Begin Source File

SOURCE=.\PgrHolder.h
# End Source File
# Begin Source File

SOURCE=.\PgrTile.cpp
# End Source File
# Begin Source File

SOURCE=.\PgrTile.h
# End Source File
# Begin Source File

SOURCE=.\pictbmp.cpp
# End Source File
# Begin Source File

SOURCE=.\lpict\PICTDEF.H
# End Source File
# Begin Source File

SOURCE=.\lpict\pictdlg.h
# End Source File
# Begin Source File

SOURCE=.\pictdraw.cpp
# End Source File
# Begin Source File

SOURCE=.\picthelpers.cpp
# End Source File
# Begin Source File

SOURCE=.\pictinl.cpp
# End Source File
# Begin Source File

SOURCE=.\lpict\PictProp.h
# End Source File
# Begin Source File

SOURCE=.\picttif.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\lpict\PICTURE.H
# End Source File
# Begin Source File

SOURCE=.\lpict\PICTURE.INL
# End Source File
# Begin Source File

SOURCE=.\PictureCache.h
# End Source File
# Begin Source File

SOURCE=.\lpict\PICTWIN.INL
# End Source File
# Begin Source File

SOURCE=.\PolyGISPicture.cpp
# End Source File
# Begin Source File

SOURCE=.\lpict\PolyGISPicture.h
# End Source File
# End Group
# Begin Group "Picture Filters"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\fltBitOr.cpp
# End Source File
# Begin Source File

SOURCE=.\fltCopy.cpp
# End Source File
# Begin Source File

SOURCE=.\fltcred.cpp
# End Source File
# Begin Source File

SOURCE=.\fltCTable.cpp
# End Source File
# Begin Source File

SOURCE=.\fltfclu.cpp
# End Source File
# Begin Source File

SOURCE=.\fltflip.cpp
# End Source File
# Begin Source File

SOURCE=.\flthist.cpp
# End Source File
# Begin Source File

SOURCE=.\fltpict.cpp
# End Source File
# Begin Source File

SOURCE=.\fltsamp.cpp
# End Source File
# Begin Source File

SOURCE=.\lpict\PICTFLT.H
# End Source File
# Begin Source File

SOURCE=.\lpict\PICTFLT.INL
# End Source File
# Begin Source File

SOURCE=.\pictinlf.cpp
# End Source File
# End Group
# Begin Group "Picture Codecs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Codec.cpp
# End Source File
# Begin Source File

SOURCE=.\CodFAX.cpp
# End Source File
# Begin Source File

SOURCE=.\CodFAXG3.cpp
# End Source File
# Begin Source File

SOURCE=.\CodFAXG4.cpp
# End Source File
# Begin Source File

SOURCE=.\CodFAXTables.cpp
# End Source File
# Begin Source File

SOURCE=.\CodLZWT.cpp
# End Source File
# Begin Source File

SOURCE=.\CodPBits.cpp
# End Source File
# Begin Source File

SOURCE=.\CodRLE4.cpp
# End Source File
# Begin Source File

SOURCE=.\CodRLE8.cpp
# End Source File
# Begin Source File

SOURCE=.\lpict\PictCod.h
# End Source File
# Begin Source File

SOURCE=.\lpict\PictCod.inl
# End Source File
# Begin Source File

SOURCE=.\pictinlc.cpp
# End Source File
# End Group
# Begin Group "Picture Support"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\pagepictprop.cpp
# End Source File
# Begin Source File

SOURCE=.\PictExcept.cpp
# End Source File
# Begin Source File

SOURCE=.\pictmem.cpp
# End Source File
# Begin Source File

SOURCE=.\SpatialTree.cpp
# End Source File
# Begin Source File

SOURCE=.\SpatialTree.h
# End Source File
# Begin Source File

SOURCE=.\TagMgr.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\console.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\pictpriv.h
# End Source File
# Begin Source File

SOURCE=.\ROP3.h
# End Source File
# Begin Source File

SOURCE=.\TabBitRev.cpp
# End Source File
# Begin Source File

SOURCE=.\TabOptrgb6.cpp
# End Source File
# Begin Source File

SOURCE=.\TabWeight.cpp
# End Source File
# End Group
# Begin Group "DLL Data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LPict42.cpp
# End Source File
# Begin Source File

SOURCE=.\LPict42.idl

!IF  "$(CFG)" == "LPict42 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\LPict42.idl
InputName=LPict42

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASTLB)\$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "LPict42 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\LPict42.idl
InputName=LPict42

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

SOURCE=.\LPictImpl.h
# End Source File
# Begin Source File

SOURCE=.\lpict\PICTVER_.H
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\Version.mak

!IF  "$(CFG)" == "LPict42 - Win32 Release"

!ELSEIF  "$(CFG)" == "LPict42 - Win32 Debug"

# Begin Custom Build - Generating Version Information
InputPath=.\Version.mak

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\LPict42.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\LPict42.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\LPict42.ver" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\LPict42.rc
# End Source File
# Begin Source File

SOURCE=.\res\msg00407.bin
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LPict42.def
# End Source File
# Begin Source File

SOURCE=.\LPict42.rcv
# End Source File
# Begin Source File

SOURCE=.\LPict42.ver
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\help\LPict42.d
# End Source File
# Begin Source File

SOURCE=.\LPict42.mc

!IF  "$(CFG)" == "LPict42 - Win32 Release"

# Begin Custom Build
InputPath=.\LPict42.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=NDEBUG

".\LPict42.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "LPict42 - Win32 Debug"

# Begin Custom Build
InputPath=.\LPict42.mc

BuildCmds= \
	nmake -nologo -f version.mak CFG=_DEBUG

".\LPict42.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\res\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Generated Files"

# PROP Default_Filter ""
# End Group
# End Target
# End Project
