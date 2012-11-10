# Microsoft Developer Studio Project File - Name="Idntdb32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Idntdb32 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Idntdb32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Idntdb32.mak" CFG="Idntdb32 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Idntdb32 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Idntdb32 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/Extensions/Beschreibungsdaten", YVEAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Idntdb32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "_WINDLL" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "DLL" /D "EXTVIS" /Yu"idntsdbp.hxx" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i ".." /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ixtnsr50.lib lol.lib tfrmwork.lib containr.lib ospace5r.lib delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\Release\Identsdb.ext" /delayload:ole32.dll /delayload:oleaut32.dll /delayload:advapi32.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Release
TargetPath=.\Release\Identsdb.ext
TargetName=Identsdb
InputPath=.\Release\Identsdb.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Idntdb32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /D "_DEBUG" /D "_WINDLL" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "DLL" /D "EXTVIS" /Yu"idntsdbp.hxx" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i ".." /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ixtnsd50.lib lol50d.lib tfrm32d.lib cont50d.lib ospace5d.lib delayimp.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:".\Debug\Identdbd.ext" /delayload:ole32.dll /delayload:oleaut32.dll /delayload:advapi32.dll
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
TargetDir=.\Debug
TargetPath=.\Debug\Identdbd.ext
TargetName=Identdbd
InputPath=.\Debug\Identdbd.ext
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).ext" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Idntdb32 - Win32 Release"
# Name "Idntdb32 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\AuxUIOwnerIdDB.cpp
# End Source File
# Begin Source File

SOURCE=.\Bmpbox.cxx
# End Source File
# Begin Source File

SOURCE=.\Defident.cxx
# End Source File
# Begin Source File

SOURCE=.\DEFIDERR.CXX
# End Source File
# Begin Source File

SOURCE=.\Defmerkm.cxx
# End Source File
# Begin Source File

SOURCE=.\DEFMKERR.CXX
# End Source File
# Begin Source File

SOURCE=.\Expcodes.cxx
# End Source File
# Begin Source File

SOURCE=.\ExportAsXml.cpp
# End Source File
# Begin Source File

SOURCE=.\FormatString.cpp
# End Source File
# Begin Source File

SOURCE=.\Identsdb.cxx
# End Source File
# Begin Source File

SOURCE=.\Idignore.cxx
# End Source File
# Begin Source File

SOURCE=.\obj32\IDNTDB32.DEF
# End Source File
# Begin Source File

SOURCE=.\obj32\idntdb32.RC
# ADD BASE RSC /l 0x407 /i "obj32"
# SUBTRACT BASE RSC /i ".."
# ADD RSC /l 0x407 /i "obj32" /i ".\obj32"
# SUBTRACT RSC /i ".."
# End Source File
# Begin Source File

SOURCE=.\idntmenu.cxx
# End Source File
# Begin Source File

SOURCE=.\idntsdbl.cxx
# End Source File
# Begin Source File

SOURCE=.\Idntsdbm.cxx
# End Source File
# Begin Source File

SOURCE=.\Idntsdbm.yxx

!IF  "$(CFG)" == "Idntdb32 - Win32 Release"

!ELSEIF  "$(CFG)" == "Idntdb32 - Win32 Debug"

# Begin Custom Build - Generating lexer and parser sources ...
InputPath=.\Idntsdbm.yxx

BuildCmds= \
	yxx -ns -nl -mph idntsdbp.hxx $(InputPath) \
	sed -e s/yy_export//g idntsdby.hxx > tmp \
	del idntsdby.hxx \
	ren tmp idntsdby.hxx \
	sed -e s/yy_export//g idntsdbl.hxx > tmp \
	del idntsdbl.hxx \
	ren tmp idntsdbl.hxx \
	sed -e s/yy_export//g yy_myref.h > tmp \
	del yy_myref.h \
	ren tmp yy_myref.h \
	

"idntsdby.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"idntsdby.hxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"idntsdbl.cxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"idntsdbl.hxx" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\idntsdbp.cxx

!IF  "$(CFG)" == "Idntdb32 - Win32 Release"

# ADD CPP /Yc"idntsdbp.hxx"

!ELSEIF  "$(CFG)" == "Idntdb32 - Win32 Debug"

# ADD CPP /Ob0 /Yc"idntsdbp.hxx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\idntsdby.cxx
# End Source File
# Begin Source File

SOURCE=.\impcodes.cxx
# End Source File
# Begin Source File

SOURCE=.\ImportFromXml.cpp
# End Source File
# Begin Source File

SOURCE=.\JumpTable.cpp
# End Source File
# Begin Source File

SOURCE=.\Mkignore.cxx
# End Source File
# Begin Source File

SOURCE=.\Newident.cxx
# End Source File
# Begin Source File

SOURCE=.\Newmcode.cxx
# End Source File
# Begin Source File

SOURCE=.\Pbderr.cxx
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\AuxUIOwner.h
# End Source File
# Begin Source File

SOURCE=.\defabout.h
# End Source File
# Begin Source File

SOURCE=.\defabout.hxx
# End Source File
# Begin Source File

SOURCE=.\defident.h
# End Source File
# Begin Source File

SOURCE=.\defident.hxx
# End Source File
# Begin Source File

SOURCE=.\defiderr.h
# End Source File
# Begin Source File

SOURCE=.\defiderr.hxx
# End Source File
# Begin Source File

SOURCE=.\defmerkm.hxx
# End Source File
# Begin Source File

SOURCE=.\defmkerr.hxx
# End Source File
# Begin Source File

SOURCE=.\defrelat.hxx
# End Source File
# Begin Source File

SOURCE=.\defrkerr.hxx
# End Source File
# Begin Source File

SOURCE=.\identres.h
# End Source File
# Begin Source File

SOURCE=.\identsdb.h
# End Source File
# Begin Source File

SOURCE=.\identsdb.hxx
# End Source File
# Begin Source File

SOURCE=.\idignore.hxx
# End Source File
# Begin Source File

SOURCE=.\idntguid.h
# End Source File
# Begin Source File

SOURCE=.\idntsdba.hxx
# End Source File
# Begin Source File

SOURCE=.\idntsdbl.hxx
# End Source File
# Begin Source File

SOURCE=.\idntsdbm.hxx
# End Source File
# Begin Source File

SOURCE=.\idntsdbp.hxx
# End Source File
# Begin Source File

SOURCE=.\idntsdby.hxx
# End Source File
# Begin Source File

SOURCE=.\impdialg.hxx
# End Source File
# Begin Source File

SOURCE=.\JumpTable.h
# End Source File
# Begin Source File

SOURCE=.\mkignore.hxx
# End Source File
# Begin Source File

SOURCE=.\newident.h
# End Source File
# Begin Source File

SOURCE=.\newident.hxx
# End Source File
# Begin Source File

SOURCE=.\newmcode.h
# End Source File
# Begin Source File

SOURCE=.\newmcode.hxx
# End Source File
# Begin Source File

SOURCE=.\newrcode.h
# End Source File
# Begin Source File

SOURCE=.\newrcode.hxx
# End Source File
# Begin Source File

SOURCE=.\pbderr.h
# End Source File
# Begin Source File

SOURCE=.\pbderr.hxx
# End Source File
# Begin Source File

SOURCE=.\rkignore.hxx
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# Begin Source File

SOURCE=.\version.h
# End Source File
# Begin Source File

SOURCE=.\yy_myref.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\obj32\IERROR.BMP
# End Source File
# Begin Source File

SOURCE=.\obj32\LUPE.ICO
# End Source File
# Begin Source File

SOURCE=.\obj32\metadata.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\RERROR.BMP
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\obj32\IDNTDB16.MAK
# End Source File
# Begin Source File

SOURCE=.\obj32\IDNTDB32.TPL

!IF  "$(CFG)" == "Idntdb32 - Win32 Release"

USERDEP__IDNTD="obj32\idntdb16.mak"	
# Begin Custom Build
InputPath=.\obj32\IDNTDB32.TPL

"obj32\idntdb32.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f "obj32\idntdb16.mak" -nologo obj32\idntdb32.def

# End Custom Build

!ELSEIF  "$(CFG)" == "Idntdb32 - Win32 Debug"

USERDEP__IDNTD="obj32\idntdb16.mak"	
# Begin Custom Build
InputPath=.\obj32\IDNTDB32.TPL

"obj32\idntdb32.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f "obj32\idntdb16.mak" -nologo obj32\idntdb32.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\obj32\IDNTDB3V.TPL

!IF  "$(CFG)" == "Idntdb32 - Win32 Release"

USERDEP__IDNTDB="obj32\idntdb16.mak"	
# Begin Custom Build
InputPath=.\obj32\IDNTDB3V.TPL

"obj32\idntdb32.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f "obj32\idntdb16.mak" -nologo obj32\idntdb32.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Idntdb32 - Win32 Debug"

USERDEP__IDNTDB="obj32\idntdb16.mak"	
# Begin Custom Build
InputPath=.\obj32\IDNTDB3V.TPL

"obj32\idntdb32.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f "obj32\idntdb16.mak" -nologo obj32\idntdb32.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\obj32\VERSIO32.TPL

!IF  "$(CFG)" == "Idntdb32 - Win32 Release"

USERDEP__VERSI="obj32\idntdb16.mak"	
# Begin Custom Build
InputPath=.\obj32\VERSIO32.TPL

"obj32\versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f "obj32\idntdb16.mak" -nologo obj32\versio32.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Idntdb32 - Win32 Debug"

USERDEP__VERSI="obj32\idntdb16.mak"	
# Begin Custom Build
InputPath=.\obj32\VERSIO32.TPL

"obj32\versio32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f "obj32\idntdb16.mak" -nologo obj32\versio32.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
