# Microsoft Developer Studio Project File - Name="TRiASUI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRiASUI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRiASUI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRiASUI.mak" CFG="TRiASUI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRiASUI - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASUI - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiASDB/TRiASUI", PVQAAAAA"
# PROP Scc_LocalPath "."
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRiASUI - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_SECDLL" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ospace5d.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/TRiASUId.dll" /pdbtype:sept
# Begin Custom Build - Copying target to destination ...
TargetDir=.\Debug
TargetPath=.\Debug\TRiASUId.dll
TargetName=TRiASUId
InputPath=.\Debug\TRiASUId.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F $(TargetDir)\$(TargetName).pdb $(TRIASDIR_D) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASUI - Win32 Release MinSize"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_SECDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_AFXDLL" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ospace5r.lib /nologo /subsystem:windows /dll /debug /machine:I386
# Begin Custom Build - Copying target to destination ...
TargetDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\TRiASUI.dll
TargetName=TRiASUI
InputPath=.\ReleaseMinSize\TRiASUI.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "TRiASUI - Win32 Debug"
# Name "TRiASUI - Win32 Release MinSize"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Interface definition"

# PROP Default_Filter "*.idl"
# Begin Source File

SOURCE=.\TRiASUI.idl

!IF  "$(CFG)" == "TRiASUI - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\TRiASUI.idl

BuildCmds= \
	midl /win32 /Oicf /h "TRiASUI.h" /iid "TRiASUI_i.c" "TRiASUI.idl" \
	xcopy /F TRiASUI.tlb $(TRIASTLB) \
	

".\TRiASUI.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASUI.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASUI_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASUI - Win32 Release MinSize"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\TRiASUI.idl

BuildCmds= \
	midl /Oicf /h "TRiASUI.h" /iid "TRiASUI_i.c" "TRiASUI.idl" \
	xcopy /F TRiASUI.tlb $(TRIASTLB) \
	

".\TRiASUI.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASUI.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\TRiASUI_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "TRiASOptionDlg Source Files"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\COMHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\COMTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=.\CoolBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\PopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\StdCtrlDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOptionDlg.cpp
# End Source File
# End Group
# Begin Group "PropertyPages"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\EditFeatureDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditFeatureParamDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EditRO.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASUI.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "TRiASOptionDlg Header Files"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\COMHelper.h
# End Source File
# Begin Source File

SOURCE=.\COMTreeItem.h
# End Source File
# Begin Source File

SOURCE=.\CoolBtn.h
# End Source File
# Begin Source File

SOURCE=.\CPTRiASOptionDlgCallback.h
# End Source File
# Begin Source File

SOURCE=.\PopupMenu.h
# End Source File
# Begin Source File

SOURCE=.\StdCtrlDlg.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOptionDlg.h
# End Source File
# Begin Source File

SOURCE=.\TRiASUIConfig.h
# End Source File
# End Group
# Begin Group "PropertyPages Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\editfeaturedlg.h
# End Source File
# Begin Source File

SOURCE=.\EditFeatureParamDlg.h
# End Source File
# Begin Source File

SOURCE=.\EditRO.h
# End Source File
# Begin Source File

SOURCE=.\MfcAtlPropertyPage.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\MfcHelper.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# Begin Source File

SOURCE=.\UIUtil.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\actions.bmp
# End Source File
# Begin Source File

SOURCE=.\res\horzdrag.cur
# End Source File
# Begin Source File

SOURCE=.\Debug\MSG00407.bin
# End Source File
# Begin Source File

SOURCE=.\res\nopic.bmp
# End Source File
# Begin Source File

SOURCE=.\TRiASUI.rc
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak;*.tpl"
# Begin Source File

SOURCE=.\TRiASUI.tpl

!IF  "$(CFG)" == "TRiASUI - Win32 Debug"

USERDEP__TRIAS="version.mak"	
# Begin Custom Build - Generating TRiASUI.Def ...
InputPath=.\TRiASUI.tpl

"TRiASUI.Def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASUI.Def

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASUI - Win32 Release MinSize"

USERDEP__TRIAS="version.mak"	
# Begin Custom Build - Generating TRiASUI.Def ...
InputPath=.\TRiASUI.tpl

"TRiASUI.Def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASUI.Def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASUIv.Tpl

!IF  "$(CFG)" == "TRiASUI - Win32 Debug"

USERDEP__TRIASU="version.mak"	
# Begin Custom Build - Generating TRiASUI.Rcv ...
InputPath=.\TRiASUIv.Tpl

"TRiASUI.Rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASUI.Rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASUI - Win32 Release MinSize"

USERDEP__TRIASU="version.mak"	
# Begin Custom Build - Generating TRiASUI.Rcv ...
InputPath=.\TRiASUIv.Tpl

"TRiASUI.Rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASUI.Rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "TRiASUI - Win32 Debug"

USERDEP__VERSI="version.mak"	
# Begin Custom Build - Generating Version.h ...
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASUI - Win32 Release MinSize"

USERDEP__VERSI="version.mak"	
# Begin Custom Build - Generating Version.h ...
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\EditFeatureDlg.rgs
# End Source File
# Begin Source File

SOURCE=.\EditFeatureParamDlg.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASOptionDlg.rgs
# End Source File
# End Group
# Begin Group "General Purpose Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# ADD CPP /D "_MERGE_PROXYSTUB"
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\TRiASUI.def
# End Source File
# End Group
# Begin Group "MessageStrings"

# PROP Default_Filter "*.mc"
# Begin Source File

SOURCE=.\UIMSG.MC

!IF  "$(CFG)" == "TRiASUI - Win32 Debug"

# Begin Custom Build - Generating message tables ...
InputDir=.
OutDir=.\Debug
InputPath=.\UIMSG.MC
InputName=UIMSG

BuildCmds= \
	cl -nologo -TC -C -EP -D_DEBUG -u $(InputPath) > $(OutDir)\$(InputName).i \
	mc -e hmc -h $(InputDir) -r "$(OutDir)" "$(OutDir)\$(InputName).i " \
	mc2const -h .\Help  $(OutDir)\$(InputName).i \
	del "$(OutDir)\$(InputName).i" > nul \
	

".\help\UIMsg.d" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASUI - Win32 Release MinSize"

!ENDIF 

# End Source File
# End Group
# Begin Group "Testing support"

# PROP Default_Filter "*.vb*;*.frm"
# Begin Source File

SOURCE=.\VB\Client.frm
# End Source File
# Begin Source File

SOURCE=.\VB\StdDlgClient.vbp
# End Source File
# Begin Source File

SOURCE=.\VB\StdDlgClient.vbw
# End Source File
# End Group
# End Target
# End Project
