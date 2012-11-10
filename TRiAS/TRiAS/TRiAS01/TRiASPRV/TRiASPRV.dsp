# Microsoft Developer Studio Project File - Name="TRiASPRV" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRiASPRV - Win32 Debug Intel
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TRiASPRV.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TRiASPRV.mak" CFG="TRiASPRV - Win32 Debug Intel"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TRiASPRV - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASPRV - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASPRV - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TRiASPRV - Win32 Debug Intel" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/TRiAS01/TRiASPRV", EWIBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TRiASPRV - Win32 Debug"

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
F90=fl32.exe
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"StdAfx.h" /Fd"Debug/TRiASPRVd.pdb" /FD /Zm200 /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 shfolder.lib shlwapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/TRiASPRVd.dll"
# Begin Custom Build - Copying target to destination ...
OutDir=.\Debug
TargetPath=.\Debug\TRiASPRVd.dll
TargetName=TRiASPRVd
InputPath=.\Debug\TRiASPRVd.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinSize"

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
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"StdAfx.h" /Fd"ReleaseMinSize/TRiASPRV.pdb" /FD /Zm200 /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 shfolder.lib shlwapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# Begin Custom Build - Copying target to destination ...
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\TRiASPRV.dll
TargetName=TRiASPRV
InputPath=.\ReleaseMinSize\TRiASPRV.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\TRiASPRV.dll
InputPath=.\ReleaseMinDependency\TRiASPRV.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Debug Intel"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "TRiASPRV___Win32_Debug_Intel"
# PROP BASE Intermediate_Dir "TRiASPRV___Win32_Debug_Intel"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "TRiASPRV___Win32_Debug_Intel"
# PROP Intermediate_Dir "TRiASPRV___Win32_Debug_Intel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"StdAfx.h" /Fd"Debug/TRiASPRVd.pdb" /FD /Zm200 /GZ /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USE_INTEL_COMPILER" /Yu"StdAfx.h" /Fd"TRiASPRV___Win32_Debug_Intel/TRiASPRVd.pdb" /FD /Zm200 /GZ -Qms -Qvc6 /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 shfolder.lib shlwapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/TRiASPRVd.dll"
# ADD LINK32 shfolder.lib shlwapi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"TRiASPRV___Win32_Debug_Intel/TRiASPRVd.dll"
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying target to destination ...
OutDir=.\TRiASPRV___Win32_Debug_Intel
TargetPath=.\TRiASPRV___Win32_Debug_Intel\TRiASPRVd.dll
TargetName=TRiASPRVd
InputPath=.\TRiASPRV___Win32_Debug_Intel\TRiASPRVd.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "TRiASPRV - Win32 Debug"
# Name "TRiASPRV - Win32 Release MinSize"
# Name "TRiASPRV - Win32 Release MinDependency"
# Name "TRiASPRV - Win32 Debug Intel"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "TRiASQL Source Files"

# PROP Default_Filter ""
# Begin Group "Interface declaration"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Include\Idl\TRiASExpression.idl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\TRiASQLCoClasses.idl

!IF  "$(CFG)" == "TRiASPRV - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinSize"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Debug Intel"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASQL\TRiASQLInterfaces.idl

!IF  "$(CFG)" == "TRiASPRV - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinSize"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Debug Intel"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "Function and Operator Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TRiASQL\AggregateFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\AritOperator.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\BoolOperator.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\CompareOperator.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\DateFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\GeometryFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\LiteralValue.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\MathFunction.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\NullExpression.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\SelectStarExpression.cpp
# End Source File
# End Group
# Begin Group "Statement Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TRiASQL\CreateTableStmt.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\DeleteStmt.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\DropStmt.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\InsertStmt.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\SelectStmt.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\UpdateStmt.cpp
# End Source File
# End Group
# Begin Group "Item List Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TRiASQL\ColumnIdent.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\ColumnIdentList.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\CreateTableItem.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\CreateTableItemList.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\GenericColl.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\GenericStack.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\GenericStackList.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\OrderByList.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\OrderByObj.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\TableIdent.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\TableIdentList.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\UpdateItem.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\UpdateItemList.cpp
# End Source File
# End Group
# Begin Group "TRiASQL Parser"

# PROP Default_Filter ""
# Begin Group "Generated Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TRiASQL\Parser\yyacc.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\Parser\yylex.cpp
# End Source File
# End Group
# Begin Group "Helper Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TRiASQL\Parser\bison.simple
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\Parser\flexlexer.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\TRiASQL\Parser\ParseTree.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\Parser\sql.l

!IF  "$(CFG)" == "TRiASPRV - Win32 Debug"

USERDEP__SQL_L="TRiASQL/parser/yyacc.h"	
# Begin Custom Build
InputPath=.\TRiASQL\Parser\sql.l

"TRiASQL/parser/yylex.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd TRiASQL\parser 
	triasql-flex -L -++ -oyylex.cpp -8 sql.l 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinSize"

USERDEP__SQL_L="TRiASQL/parser/yyacc.h"	
# Begin Custom Build
InputPath=.\TRiASQL\Parser\sql.l

"TRiASQL/parser/yylex.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd TRiASQL\parser 
	triasql-flex -L -++ -oyylex.cpp sql.l 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Debug Intel"

USERDEP__SQL_L="TRiASQL/parser/yyacc.h"	
# Begin Custom Build
InputPath=.\TRiASQL\Parser\sql.l

"TRiASQL/parser/yylex.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd TRiASQL\parser 
	triasql-flex -L -++ -oyylex.cpp -8 sql.l 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASQL\Parser\sql.y

!IF  "$(CFG)" == "TRiASPRV - Win32 Debug"

# Begin Custom Build
InputPath=.\TRiASQL\Parser\sql.y

BuildCmds= \
	cd TRiASQL\parser \
	triasql-bison --defines sql.y --output=yyacc.cpp.pre  --no-lines \
	sed -f sql.y.sed  yyacc.cpp.pre > yyacc.cpp \
	copy yyacc.cpp.pre.h yyacc.h \
	del yyacc.cpp.pre.h \
	del yyacc.cpp.pre \
	

"TRiASQL/parser/yyacc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"TRiASQL/parser/yyacc.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinSize"

# Begin Custom Build
InputPath=.\TRiASQL\Parser\sql.y

BuildCmds= \
	cd TRiASQL\parser \
	triasql-bison --define sql.y --output=yyacc.cpp --no-lines \
	copy yyacc.cpp.h yyacc.h \
	del yyacc.cpp.h \
	

"TRiASQL/parser/yyacc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"TRiASQL/parser/yyacc.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Debug Intel"

# Begin Custom Build
InputPath=.\TRiASQL\Parser\sql.y

BuildCmds= \
	cd TRiASQL\parser \
	triasql-bison --defines sql.y --output=yyacc.cpp.pre  --no-lines \
	sed -f sql.y.sed  yyacc.cpp.pre > yyacc.cpp \
	copy yyacc.cpp.pre.h yyacc.h \
	del yyacc.cpp.pre.h \
	del yyacc.cpp.pre \
	

"TRiASQL/parser/yyacc.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"TRiASQL/parser/yyacc.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\TRiASQL\cAtlObjectConverter.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\Parser.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\SHAlloc.cpp

!IF  "$(CFG)" == "TRiASPRV - Win32 Debug"

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinDependency"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Debug Intel"

!ENDIF 

# End Source File
# End Group
# Begin Group "TRiAS OleDB Object Source Files"

# PROP Default_Filter "*.cpp"
# Begin Group "Data Access Handler Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\HandleBookmark.cpp
# End Source File
# Begin Source File

SOURCE=.\HandleExpression.cpp
# End Source File
# Begin Source File

SOURCE=.\HandleGeometry.cpp
# End Source File
# Begin Source File

SOURCE=.\HandleNativeAttribute.cpp
# End Source File
# Begin Source File

SOURCE=.\HandleObjectGuid.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\GenerateColumnInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\GenerateObjectsCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBDataSource.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBErrorLookup.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBIndex.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBRowSet.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBSession.cpp
# End Source File
# End Group
# Begin Group "Helper Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\OleDBError.cpp
# End Source File
# Begin Source File

SOURCE=.\SQLExpression.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "TRiASPRV - Win32 Debug"

# ADD CPP /Yc"StdAfx.h"

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinSize"

# ADD CPP /Yc"StdAfx.h"

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Debug Intel"

# ADD BASE CPP /Yc"StdAfx.h"
# ADD CPP /Yc"StdAfx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDB.def
# End Source File
# Begin Source File

SOURCE=.\TRiASPRV.cpp
# End Source File
# Begin Source File

SOURCE=.\TRiASPRV.idl

!IF  "$(CFG)" == "TRiASPRV - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TRiASPRV.idl

"$(TRIASTLB)\TRiASPRV.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /tlb ".\TRiASPRV.tlb" /h "TRiASPRV.h" /iid "TRiASPRV_i.c" "$(InputPath)" 
	xcopy /F ".\TRiASPRV.tlb" $(TRIASTLB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinSize"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\TRiASPRV.idl

"$(TRIASTLB)\TRiASPRV.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl /Oicf /tlb ".\TRiASPRV.tlb" /h "TRiASPRV.h" /iid "TRiASPRV_i.c" "$(InputPath)" 
	xcopy /F ".\TRiASPRV.tlb" $(TRIASTLB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinDependency"

# ADD MTL /tlb ".\TRiASPRV.tlb" /h "TRiASPRV.h" /iid "TRiASPRV_i.c" /Oicf

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Debug Intel"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASPRV.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "TRiASQL Header Files"

# PROP Default_Filter ""
# Begin Group "Function and Operator Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TRiASQL\AggregateFunction.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\AritOperator.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\BoolOperator.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\CompareOperator.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\DateFunction.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\GeometryFunction.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\LiteralValue.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\MathFunction.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\NullExpression.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\SelectStarExpression.h
# End Source File
# End Group
# Begin Group "Statement Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TRiASQL\CreateTableStmt.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\DeleteStmt.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\DropStmt.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\InsertStmt.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\SelectStmt.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\UpdateStmt.h
# End Source File
# End Group
# Begin Group "Item List Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TRiASQL\ColumnIdent.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\ColumnIdentList.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\CreateTableItem.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\CreateTableItemList.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\GenericColl.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\GenericStack.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\GenericStackList.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\OrderByList.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\OrderByObj.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\TableIdent.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\TableIdentList.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\UpdateItem.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\UpdateItemList.h
# End Source File
# End Group
# Begin Group "TRiASQL Parser Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TRiASQL\Parser\ParseTree.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\Parser\yyacc.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\TRiASQL\cAtlObjectConverter.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\Parser.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\Resource.h
# End Source File
# Begin Source File

SOURCE=.\TRiASQL\shalloc.h
# End Source File
# End Group
# Begin Group "TRiAS OleDB Object Header Files"

# PROP Default_Filter "*.h"
# Begin Group "Sesson Rowset Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\SchemaRowsets.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBSessionColSchemaRowset.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBSessionIdxSchemaRowset.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBSessionPrimaryKeysSchemaRowset.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBSessionPTSchemaRowset.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBSessionSchemaOGISGeoColumns.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBSessionSchemaOGISTables.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBSessionSchemaSpatRef.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBSessionStatistSchemaRowset.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBSessionTISchemaRowset.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBSessionTRSchemaRowset.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBSessionVRSchemaRowset.h
# End Source File
# End Group
# Begin Group "Data Access Handler Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\HandleBookmark.h
# End Source File
# Begin Source File

SOURCE=.\HandleExpression.h
# End Source File
# Begin Source File

SOURCE=.\HandleGeometry.h
# End Source File
# Begin Source File

SOURCE=.\HandleNativeAttribute.h
# End Source File
# Begin Source File

SOURCE=.\HandleObjectGuid.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\GenerateColumnInfo.h
# End Source File
# Begin Source File

SOURCE=.\GenerateObjectsCollection.h
# End Source File
# Begin Source File

SOURCE=.\OleDBError.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBColumnDesc.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBCommand.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBDataSource.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBErrorLookup.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBGetDatasource.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBGetSession.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBIndex.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBRow.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBRowSet.h
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBSession.h
# End Source File
# End Group
# Begin Group "Helper Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\AliasMap.h
# End Source File
# Begin Source File

SOURCE=.\AtlColumnInfo.h
# End Source File
# Begin Source File

SOURCE=.\Expression.h
# End Source File
# Begin Source File

SOURCE=.\OrderByPredicates.h
# End Source File
# Begin Source File

SOURCE=.\SQLExpression.h
# End Source File
# Begin Source File

SOURCE=.\SQLVerification.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
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

SOURCE=.\TRiASOleDBConfig.h
# End Source File
# Begin Source File

SOURCE=.\Util.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\TRiASQL\Parser.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDB.rgs
# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBErrorLookup.rgs
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak,*.tpl"
# Begin Source File

SOURCE=.\TRiASOleDB.tpl

!IF  "$(CFG)" == "TRiASPRV - Win32 Debug"

USERDEP__TRIAS="Version.mak"	
# Begin Custom Build
InputPath=.\TRiASOleDB.tpl

"TRiASOleDB.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f Version.mak -nologo TRiASOleDB.def

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinSize"

USERDEP__TRIAS="Version.mak"	
# Begin Custom Build
InputPath=.\TRiASOleDB.tpl

"TRiASOleDB.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f Version.mak -nologo TRiASOleDB.def

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinDependency"

USERDEP__TRIAS="Version.mak"	
# Begin Custom Build
InputPath=.\TRiASOleDB.tpl

"TRiASOleDB.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f Version.mak -nologo TRiASOleDB.def

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Debug Intel"

USERDEP__TRIAS="Version.mak"	
# Begin Custom Build
InputPath=.\TRiASOleDB.tpl

"TRiASOleDB.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f Version.mak -nologo TRiASOleDB.def

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiASOleDBv.tpl

!IF  "$(CFG)" == "TRiASPRV - Win32 Debug"

USERDEP__TRIASO="Version.mak"	
# Begin Custom Build
InputPath=.\TRiASOleDBv.tpl

"TRiASOleDB.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f Version.mak -nologo TRiASOleDB.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinSize"

USERDEP__TRIASO="Version.mak"	
# Begin Custom Build
InputPath=.\TRiASOleDBv.tpl

"TRiASOleDB.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f Version.mak -nologo TRiASOleDB.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinDependency"

USERDEP__TRIASO="Version.mak"	
# Begin Custom Build
InputPath=.\TRiASOleDBv.tpl

"TRiASOleDB.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f Version.mak -nologo TRiASOleDB.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Debug Intel"

USERDEP__TRIASO="Version.mak"	
# Begin Custom Build
InputPath=.\TRiASOleDBv.tpl

"TRiASOleDB.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f Version.mak -nologo TRiASOleDB.rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Version.mak
# End Source File
# Begin Source File

SOURCE=.\Version.tpl

!IF  "$(CFG)" == "TRiASPRV - Win32 Debug"

USERDEP__VERSI="Version.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f Version.mak -nologo Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinSize"

USERDEP__VERSI="Version.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f Version.mak -nologo Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinDependency"

USERDEP__VERSI="Version.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f Version.mak -nologo Version.h

# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Debug Intel"

USERDEP__VERSI="Version.mak"	
# Begin Custom Build
InputPath=.\Version.tpl

"Version.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -f Version.mak -nologo Version.h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "MessageStrings"

# PROP Default_Filter "*.mc,*.hmc"
# Begin Source File

SOURCE=.\OleDbMsg.mc

!IF  "$(CFG)" == "TRiASPRV - Win32 Debug"

# Begin Custom Build
InputDir=.
OutDir=.\Debug
InputPath=.\OleDbMsg.mc
InputName=OleDbMsg

BuildCmds= \
	cl -nologo -TC -C -EP -D_DEBUG -u $(InputPath) > $(OutDir)\$(InputName).i \
	mc -e hmc -h $(InputDir) -r "$(OutDir)" "$(OutDir)\$(InputName).i " \
	del "$(OutDir)\$(InputName).i" > nul \
	xcopy /F $(InputName).hmc $(TRIASINCLUDE) \
	

"$(OutDir)\Msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\Msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"OleDBMsg.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASINCLUDE)\OleDBMsg.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinSize"

# Begin Custom Build
InputDir=.
OutDir=.\ReleaseMinSize
InputPath=.\OleDbMsg.mc
InputName=OleDbMsg

BuildCmds= \
	cl -nologo -TC -C -EP -D_DEBUG -u $(InputPath) > $(OutDir)\$(InputName).i \
	mc -e hmc -h $(InputDir) -r "$(OutDir)" "$(OutDir)\$(InputName).i " \
	del "$(OutDir)\$(InputName).i" > nul \
	xcopy /F $(InputName).hmc $(TRIASINCLUDE) \
	

"$(OutDir)\Msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\Msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"OleDBMsg.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASINCLUDE)\OleDBMsg.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Release MinDependency"

!ELSEIF  "$(CFG)" == "TRiASPRV - Win32 Debug Intel"

# Begin Custom Build
InputDir=.
OutDir=.\TRiASPRV___Win32_Debug_Intel
InputPath=.\OleDbMsg.mc
InputName=OleDbMsg

BuildCmds= \
	cl -nologo -TC -C -EP -D_DEBUG -u $(InputPath) > $(OutDir)\$(InputName).i \
	mc -e hmc -h $(InputDir) -r "$(OutDir)" "$(OutDir)\$(InputName).i " \
	del "$(OutDir)\$(InputName).i" > nul \
	xcopy /F $(InputName).hmc $(TRIASINCLUDE) \
	

"$(OutDir)\Msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(OutDir)\Msg00409.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"OleDBMsg.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASINCLUDE)\OleDBMsg.hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
# Section TRiASPRV : {00000104-0037-0000-3800-000010020000}
# 	1:26:IDS_DBPROP_LITERALIDENTITY:219
# 	1:30:IDS_DBPROP_INIT_PROVIDERSTRING:189
# 	1:28:IDS_DBPROP_ISupportErrorInfo:168
# 	1:24:IDS_DBPROP_IRowsetUpdate:167
# 	1:28:IDS_DBPROP_MAXTABLESINSELECT:150
# 	1:20:IDS_DBPROP_TABLETERM:126
# 	1:25:IDS_DBPROP_ROWTHREADMODEL:232
# 	1:18:IDS_DBPROP_MAXROWS:222
# 	1:23:IDS_DBPROP_IColumnsInfo:196
# 	1:30:IDS_DBPROP_AUTH_CACHE_AUTHINFO:172
# 	1:33:IDS_DBPROP_BLOCKINGSTORAGEOBJECTS:165
# 	1:30:IDS_DBPROP_NOTIFYROWUNDOINSERT:159
# 	1:29:IDS_DBPROP_CONCATNULLBEHAVIOR:109
# 	1:26:IDS_DBPROP_IRowsetIdentity:202
# 	1:25:IDS_DBPROP_IColumnsRowset:197
# 	1:27:IDS_DBPROP_TRANSACTEDOBJECT:192
# 	1:23:IDS_DBPROP_INIT_TIMEOUT:187
# 	1:32:IDS_DBPROP_AUTH_ENCRYPT_PASSWORD:173
# 	1:26:IDS_DBPROP_MULTIPLERESULTS:162
# 	1:33:IDS_DBPROP_ORDERBYCOLUMNSINSELECT:156
# 	1:26:IDS_DBPROP_NOTIFYCOLUMNSET:134
# 	1:27:IDS_DBPROP_ORDEREDBOOKMARKS:233
# 	1:22:IDS_DBPROP_ROWRESTRICT:231
# 	1:22:IDS_DBPROP_INIT_PROMPT:185
# 	1:24:IDS_DBPROP_INIT_LOCATION:183
# 	1:26:IDS_DBPROP_AUTH_INTEGRATED:174
# 	1:29:IDS_DBPROP_CHANGEINSERTEDROWS:169
# 	1:31:IDS_DBPROP_NOTIFYROWFIRSTCHANGE:136
# 	1:23:IDS_DBPROP_IMMOBILEROWS:217
# 	1:22:IDS_DBPROP_CANHOLDROWS:210
# 	1:23:IDS_DBPROP_SERVERCURSOR:191
# 	1:24:IDS_DBPROP_IRowsetScroll:166
# 	1:31:IDS_DBPROP_PREPAREABORTBEHAVIOR:158
# 	1:21:IDS_DBPROP_MAXROWSIZE:148
# 	1:30:IDS_DBPROP_NOTIFYROWUNDODELETE:142
# 	1:19:IDS_DBPROP_DBMSNAME:112
# 	1:25:IDS_DBPROP_COLUMNRESTRICT:213
# 	1:29:IDS_DBPROP_CANSCROLLBACKWARDS:212
# 	1:22:IDS_DBPROP_IRowsetInfo:203
# 	1:24:IDS_DBPROP_IRowsetChange:201
# 	1:18:IDS_DBPROP_IRowset:200
# 	1:36:IDS_DBPROP_IConnectionPointContainer:198
# 	1:23:IDS_DBPROP_UPDATABILITY:193
# 	1:23:IDS_DBPROP_IConvertType:171
# 	1:21:IDS_DBPROP_OLEOBJECTS:155
# 	1:28:IDS_DBPROP_STRUCTUREDSTORAGE:122
# 	1:24:IDS_DBPROP_PROCEDURETERM:114
# 	1:18:IDS_DBPROP_DBMSVER:113
# 	1:25:IDS_DBPROP_ACTIVESESSIONS:102
# 	1:23:IDS_DBPROP_QUICKRESTART:227
# 	1:35:IDS_DBPROP_INIT_IMPERSONATION_LEVEL:182
# 	1:14:IDR_TRIASOLEDB:101
# 	1:27:IDS_DBPROP_LITERALBOOKMARKS:218
# 	1:30:IDS_DBPROP_DELAYSTORAGEOBJECTS:216
# 	1:20:IDS_DBPROP_BOOKMARKS:206
# 	1:25:IDS_DBPROP_STRONGIDENTITY:194
# 	1:22:IDS_DBPROP_AUTH_USERID:179
# 	1:37:IDS_DBPROP_ROWSETCONVERSIONSONCOMMAND:161
# 	1:33:IDS_DBPROP_MAXROWSIZEINCLUDESBLOB:149
# 	1:25:IDS_DBPROP_IDENTIFIERCASE:145
# 	1:30:IDS_DBPROP_NOTIFYROWUNDOCHANGE:141
# 	1:26:IDS_DBPROP_NOTIFYROWINSERT:137
# 	1:28:IDS_DBPROP_MULTIPLEPARAMSETS:131
# 	1:19:IDS_DBPROP_USERNAME:127
# 	1:32:IDS_DBPROP_SUPPORTEDTXNISOLEVELS:124
# 	1:23:IDS_DBPROP_PROVIDERNAME:116
# 	1:22:IDS_DBPROP_MAXOPENROWS:220
# 	1:20:IDS_DBPROP_IAccessor:195
# 	1:31:IDS_DBPROP_RETURNPENDINGINSERTS:170
# 	1:26:IDS_DBPROP_NOTIFYROWUPDATE:160
# 	1:30:IDS_DBPROP_HETEROGENEOUSTABLES:144
# 	1:42:IDS_DBPROP_NOTIFYROWSETFETCHPOSITIONCHANGE:140
# 	1:22:IDS_DBPROP_PROVIDERVER:117
# 	1:25:IDS_DBPROP_MAXPENDINGROWS:221
# 	1:25:IDS_DBPROP_COMMANDTIMEOUT:214
# 	1:25:IDS_DBPROP_IRowsetResynch:205
# 	1:24:IDS_DBPROP_IRowsetLocate:204
# 	1:26:IDS_DBPROP_INIT_DATASOURCE:180
# 	1:25:IDS_DBPROP_DSOTHREADMODEL:130
# 	1:22:IDS_DBPROP_SCHEMAUSAGE:120
# 	1:26:IDS_DBPROP_REENTRANTEVENTS:228
# 	1:20:IDS_DBPROP_OWNINSERT:225
# 	1:20:IDS_DBPROP_INIT_LCID:188
# 	1:20:IDS_DBPROP_INIT_MODE:184
# 	1:20:IDS_DBPROP_LOCKMODES:146
# 	1:26:IDS_DBPROP_NOTIFYROWDELETE:135
# 	1:26:IDS_DBPROP_SUPPORTEDTXNDDL:128
# 	1:21:IDS_DBPROP_SQLSUPPORT:121
# 	1:27:IDS_DBPROP_PROVIDEROLEDBVER:115
# 	1:27:IDS_DBPROP_COLUMNDEFINITION:108
# 	1:23:IDS_DBPROP_CATALOGUSAGE:107
# 	1:22:IDS_DBPROP_CATALOGTERM:106
# 	1:22:IDS_DBPROP_OTHERINSERT:223
# 	1:25:IDS_DBPROP_COMMITPRESERVE:215
# 	1:23:IDS_DBPROP_BOOKMARKTYPE:208
# 	1:32:IDS_DBPROP_INIT_PROTECTION_LEVEL:186
# 	1:42:IDS_DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO:178
# 	1:24:IDS_DBPROP_NULLCOLLATION:154
# 	1:26:IDS_DBPROP_CATALOGLOCATION:105
# 	1:21:IDS_DBPROP_APPENDONLY:211
# 	1:20:IDS_DBPROP_INIT_HWND:181
# 	1:28:IDS_DBPROP_ISequentialStream:163
# 	1:29:IDS_DBPROP_NOTIFICATIONPHASES:153
# 	1:18:IDS_DBPROP_GROUPBY:143
# 	1:21:IDS_DBPROP_SUBQUERIES:123
# 	1:29:IDS_DBPROP_DATASOURCEREADONLY:111
# 	1:25:IDS_DBPROP_ASYNCTXNCOMMIT:103
# 	1:32:IDS_DBPROP_REPORTMULTIPLECHANGES:230
# 	1:26:IDS_DBPROP_BOOKMARKSKIPPED:207
# 	1:24:IDS_DBPROP_AUTH_PASSWORD:176
# 	1:24:IDS_DBPROP_ABORTPRESERVE:164
# 	1:21:IDS_DBPROP_SCHEMATERM:119
# 	1:25:IDS_DBPROP_BYREFACCESSORS:104
# 	1:24:IDS_DBPROP_REMOVEDELETED:229
# 	1:27:IDS_DBPROP_MULTITABLEUPDATE:152
# 	1:24:IDS_DBPROP_ASYNCTXNABORT:129
# 	1:32:IDS_DBPROP_SUPPORTEDTXNISORETAIN:125
# 	1:35:IDS_DBPROP_SESS_AUTOCOMMITISOLEVELS:190
# 	1:32:IDS_DBPROP_PREPARECOMMITBEHAVIOR:157
# 	1:33:IDS_DBPROP_MULTIPLESTORAGEOBJECTS:151
# 	1:23:IDS_DBPROP_MAXINDEXSIZE:147
# 	1:30:IDS_DBPROP_NOTIFYROWSETRELEASE:139
# 	1:31:IDS_DBPROP_QUOTEDIDENTIFIERCASE:118
# 	1:26:IDS_DBPROP_OWNUPDATEDELETE:226
# 	1:28:IDS_DBPROP_OTHERUPDATEDELETE:224
# 	1:28:IDS_DBPROP_CANFETCHBACKWARDS:209
# 	1:26:IDS_DBPROP_IProvideMoniker:199
# 	1:33:IDS_DBPROP_AUTH_PERSIST_ENCRYPTED:177
# 	1:29:IDS_DBPROP_AUTH_MASK_PASSWORD:175
# 	1:27:IDS_DBPROP_NOTIFYROWRESYNCH:138
# 	1:27:IDS_DBPROP_PERSISTENTIDTYPE:133
# 	1:38:IDS_DBPROP_OUTPUTPARAMETERAVAILABILITY:132
# 	1:25:IDS_DBPROP_DATASOURCENAME:110
# End Section
