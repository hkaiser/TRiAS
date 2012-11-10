# Microsoft Developer Studio Project File - Name="OPTemplate" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Generic Project" 0x010a

CFG=OPTemplate - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OPTemplate.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OPTemplate.mak" CFG="OPTemplate - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OPTemplate - Win32 Debug" (based on "Win32 (x86) Generic Project")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
MTL=midl.exe
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
# Begin Target

# Name "OPTemplate - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ObjectProperty.cpp
# Begin Custom Build
InputPath=.\ObjectProperty.cpp
InputName=ObjectProperty

"$(MSDEV6)\Common\MsDev98\Template\Atl\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(MSDEV6)\Common\MsDev98\Template\Atl

# End Custom Build
# End Source File
# Begin Source File

SOURCE=.\ObjectProperty.ctl
# Begin Custom Build
InputPath=.\ObjectProperty.ctl
InputName=ObjectProperty

"$(MSDEV6)\Common\MsDev98\Template\Atl\$(InputName).ctl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(MSDEV6)\Common\MsDev98\Template\Atl

# End Custom Build
# End Source File
# Begin Source File

SOURCE=.\ObjectProperty.reg
# Begin Custom Build
InputPath=.\ObjectProperty.reg
InputName=ObjectProperty

"$(MSDEV6)\Common\MsDev98\Template\Atl\$(InputName).reg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(MSDEV6)\Common\MsDev98\Template\Atl

# End Custom Build
# End Source File
# Begin Source File

SOURCE=.\ObjectPropertyBase.cpp
# Begin Custom Build
InputPath=.\ObjectPropertyBase.cpp
InputName=ObjectPropertyBase

"$(TRIASINCLUDE)\Com\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\Com

# End Custom Build
# End Source File
# Begin Source File

SOURCE=.\ObjectPropertyCo.idl
# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\ObjectPropertyCo.idl
InputName=ObjectPropertyCo

"$(MSDEV6)\Common\MsDev98\Template\Atl\$(InputName).idl" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(MSDEV6)\Common\MsDev98\Template\Atl

# End Custom Build
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ObjectProperty.h
# Begin Custom Build
InputPath=.\ObjectProperty.h
InputName=ObjectProperty

"$(MSDEV6)\Common\MsDev98\Template\Atl\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(MSDEV6)\Common\MsDev98\Template\Atl

# End Custom Build
# End Source File
# Begin Source File

SOURCE=.\ObjectPropertyBase.h
# Begin Custom Build
InputPath=.\ObjectPropertyBase.h
InputName=ObjectPropertyBase

"$(TRIASINCLUDE)\Com\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(TRIASINCLUDE)\Com

# End Custom Build
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\ObjectProperty.ico
# Begin Custom Build
InputPath=.\ObjectProperty.ico
InputName=ObjectProperty

"$(MSDEV6)\Common\MsDev98\Template\Atl\$(InputName).ico" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(MSDEV6)\Common\MsDev98\Template\Atl

# End Custom Build
# End Source File
# Begin Source File

SOURCE=.\ObjectProperty.rgs
# Begin Custom Build
InputPath=.\ObjectProperty.rgs
InputName=ObjectProperty

"$(MSDEV6)\Common\MsDev98\Template\Atl\$(InputName).rgs" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(InputPath) $(MSDEV6)\Common\MsDev98\Template\Atl

# End Custom Build
# End Source File
# End Group
# End Target
# End Project
