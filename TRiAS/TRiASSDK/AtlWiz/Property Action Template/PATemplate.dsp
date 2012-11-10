# Microsoft Developer Studio Project File - Name="PATemplate" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PATemplate - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PATemplate.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PATemplate.mak" CFG="PATemplate - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PATemplate - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# Begin Target

# Name "PATemplate - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\PersistPropertyAction.cpp
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\PersistPropertyAction.cpp
InputName=PersistPropertyAction

"$(TRIASINCLUDE)\Com\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\Com

# End Custom Build
# End Source File
# Begin Source File

SOURCE=.\PropertyActionBase.cpp
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\PropertyActionBase.cpp
InputName=PropertyActionBase

"$(TRIASINCLUDE)\Com\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\Com

# End Custom Build
# End Source File
# Begin Source File

SOURCE=.\PropertyActionBaseDataImpl.cpp
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\PropertyActionBaseDataImpl.cpp
InputName=PropertyActionBaseDataImpl

"$(TRIASINCLUDE)\Com\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\Com

# End Custom Build
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\PropertyActionBase.h
# Begin Custom Build
InputPath=.\PropertyActionBase.h
InputName=PropertyActionBase

"$(TRIASINCLUDE)\Com\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\Com

# End Custom Build
# End Source File
# Begin Source File

SOURCE=.\PropertyActionBaseData.h
# Begin Custom Build
InputPath=.\PropertyActionBaseData.h
InputName=PropertyActionBaseData

"$(TRIASINCLUDE)\Com\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\Com

# End Custom Build
# End Source File
# End Group
# Begin Group "Documentation"

# PROP Default_Filter "*.htm"
# Begin Source File

SOURCE=C:\MsDev6\Common\MSDev98\Template\ATL\TEMPLATE.htm
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1
# End Source File
# End Group
# Begin Group "Template Files"

# PROP Default_Filter ""
# Begin Group "Template Source Files"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\PropertyAction.cpp
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\PropertyAction.cpp
InputName=PropertyAction

"$(MSDEV6)\Common\MsDev98\Template\Atl\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(MSDEV6)\Common\MsDev98\Template\Atl

# End Custom Build
# End Source File
# Begin Source File

SOURCE=.\PropertyAction.h
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\PropertyAction.h
InputName=PropertyAction

"$(MSDEV6)\Common\MsDev98\Template\Atl\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(MSDEV6)\Common\MsDev98\Template\Atl

# End Custom Build
# End Source File
# Begin Source File

SOURCE=.\PropertyActionDlg.cpp
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\PropertyActionDlg.cpp
InputName=PropertyActionDlg

"$(MSDEV6)\Common\MsDev98\Template\Atl\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(MSDEV6)\Common\MsDev98\Template\Atl

# End Custom Build
# End Source File
# Begin Source File

SOURCE=.\PropertyActionDlg.h
# Begin Custom Build
InputPath=.\PropertyActionDlg.h
InputName=PropertyActionDlg

"$(MSDEV6)\Common\MsDev98\Template\Atl\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(MSDEV6)\Common\MsDev98\Template\Atl

# End Custom Build
# End Source File
# End Group
# Begin Group "Template Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\PropertyAction.ico
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\PropertyAction.ico
InputName=PropertyAction

"$(MSDEV6)\Common\MsDev98\Template\Atl\$(InputName).ico" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(MSDEV6)\Common\MsDev98\Template\Atl

# End Custom Build
# End Source File
# Begin Source File

SOURCE=.\PropertyAction.rgs
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\PropertyAction.rgs
InputName=PropertyAction

"$(MSDEV6)\Common\MsDev98\Template\Atl\$(InputName).rgs" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(MSDEV6)\Common\MsDev98\Template\Atl

# End Custom Build
# End Source File
# End Group
# Begin Source File

SOURCE=.\PropertyAction.ctl
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\PropertyAction.ctl
InputName=PropertyAction

"$(MSDEV6)\Common\MsDev98\Template\Atl\$(InputName).ctl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(MSDEV6)\Common\MsDev98\Template\Atl

# End Custom Build
# End Source File
# Begin Source File

SOURCE=.\PropertyAction.rc
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\PropertyAction.rc
InputName=PropertyAction

"$(MSDEV6)\Common\MsDev98\Template\Atl\$(InputName).rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(MSDEV6)\Common\MsDev98\Template\Atl

# End Custom Build
# End Source File
# Begin Source File

SOURCE=.\PropertyAction.reg
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\PropertyAction.reg
InputName=PropertyAction

"$(MSDEV6)\Common\MsDev98\Template\Atl\$(InputName).reg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(MSDEV6)\Common\MsDev98\Template\Atl

# End Custom Build
# End Source File
# Begin Source File

SOURCE=.\PropertyActionCo.idl
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\PropertyActionCo.idl
InputName=PropertyActionCo

"$(MSDEV6)\Common\MsDev98\Template\Atl\$(InputName).idl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(MSDEV6)\Common\MsDev98\Template\Atl

# End Custom Build
# End Source File
# End Group
# End Target
# End Project
