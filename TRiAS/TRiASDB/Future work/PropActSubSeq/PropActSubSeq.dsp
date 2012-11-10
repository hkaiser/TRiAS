# Microsoft Developer Studio Project File - Name="PropActSubSeq" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=PropActSubSeq - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PropActSubSeq.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PropActSubSeq.mak" CFG="PropActSubSeq - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PropActSubSeq - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PropActSubSeq - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PropActSubSeq - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "PropActSubSeq - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "PropActSubSeq - Win32 Release"
# Name "PropActSubSeq - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DeleteAttributes.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteAttributesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MergeTwoSources.cpp
# End Source File
# Begin Source File

SOURCE=.\MergeTwoSourcesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PropActSubSeq.cpp
# End Source File
# Begin Source File

SOURCE=.\PropActSubSeq.def
# End Source File
# Begin Source File

SOURCE=.\PropActSubSeq.idl

!IF  "$(CFG)" == "PropActSubSeq - Win32 Release"

!ELSEIF  "$(CFG)" == "PropActSubSeq - Win32 Debug"

# ADD MTL /h "PropActSubSeq.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PropActSubSeq.rc
# End Source File
# Begin Source File

SOURCE=.\PropActSubSeqExt.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DeleteAttributes.h
# End Source File
# Begin Source File

SOURCE=.\DeleteAttributesDlg.h
# End Source File
# Begin Source File

SOURCE=.\MergeTwoSources.h
# End Source File
# Begin Source File

SOURCE=.\MergeTwoSourcesDlg.h
# End Source File
# Begin Source File

SOURCE=.\PropActSubSeq.h
# End Source File
# Begin Source File

SOURCE=.\PropActSubSeqConfig.h
# End Source File
# Begin Source File

SOURCE=.\PropActSubSeqExt.h
# End Source File
# Begin Source File

SOURCE=.\PropActSubSeqUtil.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\DeleteAttributes.rgs
# End Source File
# Begin Source File

SOURCE=.\MergeTwoSources.rgs
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\PropActSubSeq.tpl

!IF  "$(CFG)" == "PropActSubSeq - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\PropActSubSeq.tpl

"PropActSubSeq.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak PropActSubSeq.def

# End Custom Build

!ELSEIF  "$(CFG)" == "PropActSubSeq - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\PropActSubSeq.tpl

"PropActSubSeq.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak PropActSubSeq.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PropActSubSeqv.tpl

!IF  "$(CFG)" == "PropActSubSeq - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\PropActSubSeqv.tpl

"PropActSubSeq.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak PropActSubSeq.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "PropActSubSeq - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\PropActSubSeqv.tpl

"PropActSubSeq.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak PropActSubSeq.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "PropActSubSeq - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "PropActSubSeq - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
# Section PropActSubSeq : {00000000-0000-0000-0000-800000800000}
# 	1:28:IDD_DELETEATTRIBUTES_OPTIONS:107
# 	1:32:IDS_DESCRIPTION_DELETEATTRIBUTES:106
# 	1:20:IDR_DELETEATTRIBUTES:105
# End Section
