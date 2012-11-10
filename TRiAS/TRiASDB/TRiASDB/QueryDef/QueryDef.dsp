# Microsoft Developer Studio Project File - Name="QueryDef" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=QueryDef - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "QueryDef.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "QueryDef.mak" CFG="QueryDef - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "QueryDef - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "QueryDef - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "QueryDef - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 iprop.lib /nologo /subsystem:windows /dll /debug /machine:I386
# Begin Custom Build
OutDir=.\Release
TargetPath=.\Release\QueryDef.dll
TargetName=QueryDef
InputPath=.\Release\QueryDef.dll
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F $(TargetPath) $(TRIASDIR_R) \
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASDIR_R) \
	

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASDIR_R)\$(TargetName).pdb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "QueryDef - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /Oicf /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 iprop.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/QueryDefd.dll" /pdbtype:sept
# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\QueryDefd.dll
TargetName=QueryDefd
InputPath=.\Debug\QueryDefd.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "QueryDef - Win32 Release"
# Name "QueryDef - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Extension"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\JumpTable.cpp
# End Source File
# Begin Source File

SOURCE=.\Notifications.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryDef.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryDefExt.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryDefMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\QueryDefUtil.cpp
# End Source File
# End Group
# Begin Group "QueryDef Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\RemoveFromObjectClass.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASCollectObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\UndoRedoAddObjToClass.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\QueryDef.def
# End Source File
# Begin Source File

SOURCE=.\QueryDef.idl

!IF  "$(CFG)" == "QueryDef - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\QueryDef.idl

"QueryDef.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /win32 /Oicf /h "QueryDef.h" /iid "QueryDef_i.c"  "QueryDef.idl" 
	xcopy /F "QueryDef.tlb" $(TRIASTLB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "QueryDef - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\QueryDef.idl

"QueryDef.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /win32 /Oicf /h "QueryDef.h" /iid "QueryDef_i.c"  "QueryDef.idl" 
	xcopy /F "QueryDef.tlb" $(TRIASTLB) 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\QueryDef.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Extension Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\DexCommands.h
# End Source File
# Begin Source File

SOURCE=.\JumpTable.h
# End Source File
# Begin Source File

SOURCE=.\QueryDef.h
# End Source File
# Begin Source File

SOURCE=.\QueryDefExt.h
# End Source File
# End Group
# Begin Group "Util Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\QueryDefConfig.h
# End Source File
# Begin Source File

SOURCE=.\QueryDefUtil.h
# End Source File
# End Group
# Begin Group "QueryDef Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\RemoveFromObjectClass.h
# End Source File
# Begin Source File

SOURCE=.\TRiASCollectObjects.h
# End Source File
# Begin Source File

SOURCE=.\UndoRedoAddObjToClass.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\UndoRedoAddObjToClass.rgs
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=.\QueryDef.tpl

!IF  "$(CFG)" == "QueryDef - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__QUERY="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\QueryDef.tpl

"QueryDef.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak QueryDef.def

# End Custom Build

!ELSEIF  "$(CFG)" == "QueryDef - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__QUERY="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\QueryDef.tpl

"QueryDef.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak QueryDef.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\QueryDefv.tpl

!IF  "$(CFG)" == "QueryDef - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__QUERYD="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\QueryDefv.tpl

"QueryDef.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak QueryDef.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "QueryDef - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__QUERYD="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\QueryDefv.tpl

"QueryDef.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak QueryDef.rcv

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

!IF  "$(CFG)" == "QueryDef - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__VERSI="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "QueryDef - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__VERSI="version.mak"	
# Begin Custom Build - Performing Custom Build Step on $(InputPath)
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

SOURCE=.\RemoveFromObjectClass.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASCollectObjects.rgs
# End Source File
# End Group
# End Target
# End Project
# Section QueryDef : {00000000-0000-0000-0000-800000800000}
# 	1:37:IDS_DESCRIPTION_REMOVEFROMOBJECTCLASS:113
# 	1:25:IDR_REMOVEFROMOBJECTCLASS:112
# 	1:33:IDD_REMOVEFROMOBJECTCLASS_OPTIONS:114
# End Section
