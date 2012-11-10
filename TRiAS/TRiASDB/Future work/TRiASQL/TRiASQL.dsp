# Microsoft Developer Studio Project File - Name="TRiASQL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRiASQL - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRiASQL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRiASQL.mak" CFG="TRiASQL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRiASQL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASQL - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Products/TRiASQL", JKAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRiASQL - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /Fp"Debug/TRiASQLD.pch" /Yu"stdafx.h" /Fd"Debug/TRiASQLD.pdb" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ospace5d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/TRiASQLD.dll"
# Begin Custom Build - Performing registration
TargetDir=.\Debug
TargetPath=.\Debug\TRiASQLD.dll
TargetName=TRiASQLD
InputPath=.\Debug\TRiASQLD.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASQL - Win32 Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Yu"stdafx.h" /Fd"ReleaseMinSize/TRiASQL.pdb" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ospace5r.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Performing registration
TargetDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\TRiASQL.dll
TargetName=TRiASQL
InputPath=.\ReleaseMinSize\TRiASQL.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F "$(TargetDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "TRiASQL - Win32 Debug"
# Name "TRiASQL - Win32 Release MinSize"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Interface declaration"

# PROP Default_Filter "*.idl"
# Begin Source File

SOURCE=.\TRiASQL.idl
# ADD MTL /tlb ".\TRiASQL.tlb" /h "TRiASQL.h" /iid "TRiASQL_i.c" /Oicf
# End Source File
# End Group
# Begin Group "Function and Operator Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\AggregateFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\AritOperator.cpp
# End Source File
# Begin Source File

SOURCE=.\BoolOperator.cpp
# End Source File
# Begin Source File

SOURCE=.\CompareOperator.cpp
# End Source File
# Begin Source File

SOURCE=.\DateFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\LiteralValue.cpp
# End Source File
# Begin Source File

SOURCE=.\MathFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\NullExpression.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectStarExpression.cpp
# End Source File
# End Group
# Begin Group "Statement Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\CreateTableStmt.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteStmt.cpp
# End Source File
# Begin Source File

SOURCE=.\DropStmt.cpp
# End Source File
# Begin Source File

SOURCE=.\InsertStmt.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectStmt.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateStmt.cpp
# End Source File
# End Group
# Begin Group "Item List Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\ColumnIdent.cpp
# End Source File
# Begin Source File

SOURCE=.\ColumnIdentList.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateTableItem.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateTableItemList.cpp
# End Source File
# Begin Source File

SOURCE=.\GenericColl.cpp
# End Source File
# Begin Source File

SOURCE=.\GenericStack.cpp
# End Source File
# Begin Source File

SOURCE=.\GenericStackList.cpp
# End Source File
# Begin Source File

SOURCE=.\OrderByList.cpp
# End Source File
# Begin Source File

SOURCE=.\OrderByObj.cpp
# End Source File
# Begin Source File

SOURCE=.\TableIdent.cpp
# End Source File
# Begin Source File

SOURCE=.\TableIdentList.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateItem.cpp
# End Source File
# Begin Source File

SOURCE=.\UpdateItemList.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\cAtlObjectConverter.cpp
# End Source File
# Begin Source File

SOURCE=.\Parser.cpp
# End Source File
# Begin Source File

SOURCE=.\SHAlloc.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TRiASQL.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Function and Operator Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\AggregateFunction.h
# End Source File
# Begin Source File

SOURCE=.\AritOperator.h
# End Source File
# Begin Source File

SOURCE=.\BoolOperator.h
# End Source File
# Begin Source File

SOURCE=.\CompareOperator.h
# End Source File
# Begin Source File

SOURCE=.\DateFunction.h
# End Source File
# Begin Source File

SOURCE=.\LiteralValue.h
# End Source File
# Begin Source File

SOURCE=.\MathFunction.h
# End Source File
# Begin Source File

SOURCE=.\NullExpression.h
# End Source File
# Begin Source File

SOURCE=.\SelectStarExpression.h
# End Source File
# End Group
# Begin Group "Statement Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\CreateTableStmt.h
# End Source File
# Begin Source File

SOURCE=.\DeleteStmt.h
# End Source File
# Begin Source File

SOURCE=.\DropStmt.h
# End Source File
# Begin Source File

SOURCE=.\InsertStmt.h
# End Source File
# Begin Source File

SOURCE=.\SelectStmt.h
# End Source File
# Begin Source File

SOURCE=.\UpdateStmt.h
# End Source File
# End Group
# Begin Group "Item List Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\ColumnIdent.h
# End Source File
# Begin Source File

SOURCE=.\ColumnIdentList.h
# End Source File
# Begin Source File

SOURCE=.\CreateTableItem.h
# End Source File
# Begin Source File

SOURCE=.\CreateTableItemList.h
# End Source File
# Begin Source File

SOURCE=.\GenericColl.h
# End Source File
# Begin Source File

SOURCE=.\GenericStack.h
# End Source File
# Begin Source File

SOURCE=.\GenericStackList.h
# End Source File
# Begin Source File

SOURCE=.\OrderByList.h
# End Source File
# Begin Source File

SOURCE=.\OrderByObj.h
# End Source File
# Begin Source File

SOURCE=.\TableIdent.h
# End Source File
# Begin Source File

SOURCE=.\TableIdentList.h
# End Source File
# Begin Source File

SOURCE=.\UpdateItem.h
# End Source File
# Begin Source File

SOURCE=.\UpdateItemList.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\cAtlObjectConverter.h
# End Source File
# Begin Source File

SOURCE=.\Parser.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\shalloc.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQLConfig.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Parser.rgs
# End Source File
# End Group
# Begin Group "TRiASQL Parser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Parser\bison.simple
# End Source File
# Begin Source File

SOURCE=.\Parser\flexlexer.h
# End Source File
# Begin Source File

SOURCE=.\Parser\ParseTree.cpp
# End Source File
# Begin Source File

SOURCE=.\Parser\ParseTree.h
# End Source File
# Begin Source File

SOURCE=.\Parser\SmartPointers.h
# End Source File
# Begin Source File

SOURCE=.\Parser\sql.l

!IF  "$(CFG)" == "TRiASQL - Win32 Debug"

# Begin Custom Build
InputPath=.\Parser\sql.l

"parser/yylex.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd parser 
	triasql-flex -L -++ -oyylex.cpp sql.l 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASQL - Win32 Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Parser\sql.y

!IF  "$(CFG)" == "TRiASQL - Win32 Debug"

# Begin Custom Build
InputPath=.\Parser\sql.y

"parser/yyacc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd parser 
	triasql-bison --define sql.y --output=yyacc.cpp --no-lines 
	copy yyacc.cpp.h yyacc.h 
	del yyacc.cpp.h 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASQL - Win32 Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Parser\StdString.cpp
# End Source File
# Begin Source File

SOURCE=.\Parser\StdString.h
# End Source File
# Begin Source File

SOURCE=.\Parser\yyacc.cpp
# End Source File
# Begin Source File

SOURCE=.\Parser\yyacc.h
# End Source File
# Begin Source File

SOURCE=.\Parser\yylex.cpp
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak;*.tpl"
# Begin Source File

SOURCE=.\TRiASQL.tpl

!IF  "$(CFG)" == "TRiASQL - Win32 Debug"

USERDEP__TRIAS="version.mak"	
# Begin Custom Build
InputPath=.\TRiASQL.tpl

"TRiASQL.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASQL.def

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASQL - Win32 Release MinSize"

USERDEP__TRIAS="version.mak"	
# Begin Custom Build
InputPath=.\TRiASQL.tpl

"TRiASQL.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASQL.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASQLv.tpl

!IF  "$(CFG)" == "TRiASQL - Win32 Debug"

USERDEP__TRIASQ="version.mak"	
# Begin Custom Build
InputPath=.\TRiASQLv.tpl

"TRiASQL.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASQL.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASQL - Win32 Release MinSize"

USERDEP__TRIASQ="version.mak"	
# Begin Custom Build
InputPath=.\TRiASQLv.tpl

"TRiASQL.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak TRiASQL.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "TRiASQL - Win32 Debug"

USERDEP__VERSI="version.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASQL - Win32 Release MinSize"

USERDEP__VERSI="version.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f version.mak version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "General purpose files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\dlldatax.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\dlldatax.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL.def
# End Source File
# Begin Source File

SOURCE=.\TRiASQL.rc
# End Source File
# End Group
# End Target
# End Project
