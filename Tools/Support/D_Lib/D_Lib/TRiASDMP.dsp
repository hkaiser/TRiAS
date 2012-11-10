# Microsoft Developer Studio Project File - Name="TRiASDMP" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRiASDMP - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRiASDMP.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRiASDMP.mak" CFG="TRiASDMP - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRiASDMP - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASDMP - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRiASDMP - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TRiASDMP_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I "$(YACLPATH)" /I "$(TRIASINCLUDE)/d_lib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TRiASDMP_EXPORTS" /D "USE_3PARTY_YACL" /D "USE_DLIB" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 yaclbasr.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386
# Begin Custom Build
OutDir=.\Release
TargetPath=.\Release\TRiASDMP.dll
TargetName=TRiASDMP
InputPath=.\Release\TRiASDMP.dll
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) \
	xcopy /F "$(OutDir)/$(TargetName).pdb" $(TRIASDIR_R) \
	xcopy /F "$(OutDir)/$(TargetName).lib" $(TRIASLIB) \
	

"$(TRIASDIR_R)/$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASLIB)/$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASDMP - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TRiASDMP_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "$(YACLPATH)" /I "$(TRIASINCLUDE)/d_lib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TRiASDMP_EXPORTS" /D "USE_3PARTY_YACL" /D "USE_DLIB" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 yaclbasd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"Debug/TRiASDMD.dll"
# Begin Custom Build
OutDir=.\Debug
TargetPath=.\Debug\TRiASDMD.dll
TargetName=TRiASDMD
InputPath=.\Debug\TRiASDMD.dll
SOURCE="$(InputPath)"

BuildCmds= \
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) \
	xcopy /F "$(OutDir)/$(TargetName).pdb" $(TRIASDIR_D) \
	xcopy /F "$(OutDir)/$(TargetName).lib" $(TRIASLIB) \
	

"$(TRIASDIR_D)/$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASLIB)/$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# Begin Target

# Name "TRiASDMP - Win32 Release"
# Name "TRiASDMP - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\d_list_c.cpp
# End Source File
# Begin Source File

SOURCE=.\d_support_c.cpp
# End Source File
# Begin Source File

SOURCE=.\d_time_c.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASDMPd.def

!IF  "$(CFG)" == "TRiASDMP - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASDMP - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASDMPr.def

!IF  "$(CFG)" == "TRiASDMP - Win32 Release"

!ELSEIF  "$(CFG)" == "TRiASDMP - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\d_consts.h
# End Source File
# Begin Source File

SOURCE=.\d_levelinfo_c.h
# End Source File
# Begin Source File

SOURCE=.\d_list_c.h
# End Source File
# Begin Source File

SOURCE=.\d_macros.h
# End Source File
# Begin Source File

SOURCE=.\d_maskinfo_c.h
# End Source File
# Begin Source File

SOURCE=.\d_regexpr.h
# End Source File
# Begin Source File

SOURCE=.\d_stackname_c.h
# End Source File
# Begin Source File

SOURCE=.\d_string_c.h
# End Source File
# Begin Source File

SOURCE=.\d_support_c.h
# End Source File
# Begin Source File

SOURCE=.\d_time_c.h
# End Source File
# Begin Source File

SOURCE=.\TRiASDMP.h
# End Source File
# Begin Source File

SOURCE=.\TRiASDMP_dll.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\TRiASDMP.rc
# End Source File
# End Group
# Begin Group "Documentation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\README.TXT
# End Source File
# Begin Source File

SOURCE=.\TRiASDMP.txt
# End Source File
# End Group
# End Target
# End Project
