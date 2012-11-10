# Microsoft Developer Studio Project File - Name="Trias323" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Trias323 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Trias423.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Trias423.mak" CFG="Trias323 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Trias323 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Trias323 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""$/TRiAS/TRiAS/TRiAS03", DWAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Trias323 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /Fp".\Release\Trias323.pch" /Yu"trias03p.hxx" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /i ".\obj32" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 trias322.lib trias321.lib tfrmwork.lib containr.lib ospace.lib largeint.lib TriasTlb.lib comctl32.lib muscrl32.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /debug /machine:I386 /out:".\Release\TRiAS323.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\.\Release
TargetPath=.\Release\TRiAS323.dll
TargetName=TRiAS323
InputPath=.\Release\TRiAS323.dll
SOURCE=$(InputPath)

BuildCmds= \
	copy "$(TargetPath)" $(TRIASDIR_R) \
	copy "$(OutDir)\$(TargetName).lib" $(TRIASLIB) \
	

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug4"
# PROP Intermediate_Dir ".\Debug4"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /Gi /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /FR /Fp".\Debug4\trias323d.pch" /Yu"trias03p.hxx" /Fd".\Debug4\trias323d.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /i ".\obj32" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 trias32d.lib trias31d.lib tfrm32d.lib cont50d.lib ospace5d.lib largeint.lib TriasTld.lib comctl32.lib muscrl32.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /dll /debug /machine:I386 /out:".\Debug4\trias33d.dll" /stub:"./obj32\rights.exe" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\.\Debug4
TargetPath=.\Debug4\trias33d.dll
TargetName=trias33d
InputPath=.\Debug4\trias33d.dll
SOURCE=$(InputPath)

BuildCmds= \
	copy "$(TargetPath)" $(TRIASDIR_D) \
	copy "$(OutDir)\$(TargetName).lib" $(TRIASLIB) \
	copy "$(OutDir)\$(TargetName).pdb" $(TRIASLIB) \
	copy "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_D) \
	

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASLIB)\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(TRIASLIB)\$(TargetName).pdb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# Begin Target

# Name "Trias323 - Win32 Release"
# Name "Trias323 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\bmpbtn.cxx
# End Source File
# Begin Source File

SOURCE=.\cextreg.cxx
# End Source File
# Begin Source File

SOURCE=.\CheckTreeView.cpp
# End Source File
# Begin Source File

SOURCE=.\CLSFYPRP.CXX
# End Source File
# Begin Source File

SOURCE=.\CoDelegator.cpp
# End Source File
# Begin Source File

SOURCE=.\Datahelp.cxx
# End Source File
# Begin Source File

SOURCE=.\Dataobj.cxx
# End Source File
# Begin Source File

SOURCE=.\DATATRAN.CXX
# End Source File
# Begin Source File

SOURCE=.\dblcoord.cxx
# End Source File
# Begin Source File

SOURCE=.\DBLNUMED.CXX
# End Source File
# Begin Source File

SOURCE=.\Delegator.cpp
# End Source File
# Begin Source File

SOURCE=.\DelegatorSvc.cpp
# End Source File
# Begin Source File

SOURCE=.\DelObPrp.cxx
# End Source File
# Begin Source File

SOURCE=.\DLLDATAX.C

!IF  "$(CFG)" == "Trias323 - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DstObDlg.cxx
# End Source File
# Begin Source File

SOURCE=.\DstObWnd.cxx
# End Source File
# Begin Source File

SOURCE=.\Enumonr.cxx
# End Source File
# Begin Source File

SOURCE=.\enumundo.cxx
# End Source File
# Begin Source File

SOURCE=.\GenTextDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GenTextPropAct.cpp
# End Source File
# Begin Source File

SOURCE=.\HELPTEXT.CXX
# End Source File
# Begin Source File

SOURCE=.\Idataobj.cxx
# End Source File
# Begin Source File

SOURCE=.\Ienumfe.cxx
# End Source File
# Begin Source File

SOURCE=.\ImportDataDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportProp.cpp
# End Source File
# Begin Source File

SOURCE=.\InPlaceCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\INTOPROP.CXX
# End Source File
# Begin Source File

SOURCE=.\JUSTIFY.CXX
# End Source File
# Begin Source File

SOURCE=.\LIBMAIN3.CXX
# End Source File
# Begin Source File

SOURCE=.\LISTHSCR.CPP
# End Source File
# Begin Source File

SOURCE=.\MatchingObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\Modident.cxx
# End Source File
# Begin Source File

SOURCE=.\Modidprp.cxx
# End Source File
# Begin Source File

SOURCE=.\MultiPI.cpp
# End Source File
# Begin Source File

SOURCE=.\MUSCROLL.CXX
# End Source File
# Begin Source File

SOURCE=.\NUMEDIT.CXX
# End Source File
# Begin Source File

SOURCE=.\ObjekteDoppeln.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjekteVereinigen.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjGeomW.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjPropFeature.cpp
# End Source File
# Begin Source File

SOURCE=.\opropcf.cxx
# End Source File
# Begin Source File

SOURCE=.\OWNCOMBO.CXX
# End Source File
# Begin Source File

SOURCE=.\OWNLIST.CXX
# End Source File
# Begin Source File

SOURCE=.\OWNLISTE.CXX
# End Source File
# Begin Source File

SOURCE=.\PRNTPARS.CXX
# End Source File
# Begin Source File

SOURCE=.\Propactb.cxx
# End Source File
# Begin Source File

SOURCE=.\Propname.cxx
# End Source File
# Begin Source File

SOURCE=.\Propseq.cxx
# End Source File
# Begin Source File

SOURCE=.\queryfld.cxx
# End Source File
# Begin Source File

SOURCE=.\REGISTER.CPP
# End Source File
# Begin Source File

SOURCE=.\RegisterExt.cpp
# End Source File
# Begin Source File

SOURCE=.\REGOBJ.CPP
# End Source File
# Begin Source File

SOURCE=.\regprop.cxx
# End Source File
# Begin Source File

SOURCE=.\Resource.cpp
# End Source File
# Begin Source File

SOURCE=.\ROTATE.CXX
# End Source File
# Begin Source File

SOURCE=.\ScriptPropAct.cpp
# End Source File
# Begin Source File

SOURCE=.\Selident.cxx
# End Source File
# Begin Source File

SOURCE=.\SELIDLST.CXX
# End Source File
# Begin Source File

SOURCE=.\selidlvc.cxx
# End Source File
# Begin Source File

SOURCE=.\Selidprp.cxx
# End Source File
# Begin Source File

SOURCE=.\Selobdlg.cxx
# End Source File
# Begin Source File

SOURCE=.\SelObjProp.cpp
# End Source File
# Begin Source File

SOURCE=.\SelObjPropDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Selobwnd.cxx
# End Source File
# Begin Source File

SOURCE=.\SelOProp.cpp
# End Source File
# Begin Source File

SOURCE=.\SelOPrpTree.cpp
# End Source File
# Begin Source File

SOURCE=.\SPINCTRL.CXX
# End Source File
# Begin Source File

SOURCE=.\statimpl.cxx
# End Source File
# Begin Source File

SOURCE=.\STATUS.CPP
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\TextSearchEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\trias03p.cxx
# ADD CPP /Yc"trias03p.hxx"
# End Source File
# Begin Source File

SOURCE=.\obj32\Trias323.RC
# ADD BASE RSC /l 0x407 /i "obj32"
# SUBTRACT BASE RSC /i ".\obj32"
# ADD RSC /l 0x407 /i "obj32"
# SUBTRACT RSC /i ".\obj32"
# End Source File
# Begin Source File

SOURCE=.\obj32\TRIAS33D.DEF
# End Source File
# Begin Source File

SOURCE=.\TRiASHelper.IDL

!IF  "$(CFG)" == "Trias323 - Win32 Release"

# Begin Custom Build - Running MIDL ...
InputDir=.
InputPath=.\TRiASHelper.IDL
InputName=TRiASHelper

BuildCmds= \
	midl /Oicf /win32 /tlb $(InputDir)/Release/$(InputName).tlb /D __ATL_20_USED__\
                                             $(InputPath)

"$(InputDir)/Release/$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"dlldata.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_p.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

# Begin Custom Build - Running MIDL ...
InputDir=.
InputPath=.\TRiASHelper.IDL
InputName=TRiASHelper

BuildCmds= \
	midl /Oicf /win32 /tlb $(InputDir)/Debug4/$(InputName).tlb /D __ATL_20_USED__\
                                             $(InputPath) \
	copy $(InputName).h \triasdev.mvc\include \
	copy $(InputName)_i.c \triasdev.mvc\include \
	

"$(InputDir)/Debug4/$(InputName).tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"dlldata.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName)_p.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TriASTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\txtsrchd.cpp
# End Source File
# Begin Source File

SOURCE=.\undocf.cxx
# End Source File
# Begin Source File

SOURCE=.\UndoCreo.cpp
# End Source File
# Begin Source File

SOURCE=.\undodelo.cxx
# End Source File
# Begin Source File

SOURCE=.\undodelr.cxx
# End Source File
# Begin Source File

SOURCE=.\undodelt.cxx
# End Source File
# Begin Source File

SOURCE=.\undofeat.cxx
# End Source File
# Begin Source File

SOURCE=.\undohelp.cxx
# End Source File
# Begin Source File

SOURCE=.\undohwnd.cxx
# End Source File
# Begin Source File

SOURCE=.\undomodi.cxx
# End Source File
# Begin Source File

SOURCE=.\undomodo.cxx
# End Source File
# Begin Source File

SOURCE=.\undomodr.cxx
# End Source File
# Begin Source File

SOURCE=.\undomodv.cxx
# End Source File
# Begin Source File

SOURCE=.\undopbd.cxx
# End Source File
# Begin Source File

SOURCE=.\undoredo.cxx
# End Source File
# Begin Source File

SOURCE=.\undotext.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\CLSFYPRP.HXX
# End Source File
# Begin Source File

SOURCE=.\CoDelegator.h
# End Source File
# Begin Source File

SOURCE=.\DataHelp.h
# End Source File
# Begin Source File

SOURCE=.\DATATRAN.HXX
# End Source File
# Begin Source File

SOURCE=.\Delegator.h
# End Source File
# Begin Source File

SOURCE=.\DelObPrp.hxx
# End Source File
# Begin Source File

SOURCE=.\DLLDATAX.H
# End Source File
# Begin Source File

SOURCE=.\DstObDlg.hxx
# End Source File
# Begin Source File

SOURCE=.\DstObWnd.hxx
# End Source File
# Begin Source File

SOURCE=.\Enumonr.hxx
# End Source File
# Begin Source File

SOURCE=.\GenTextDlg.h
# End Source File
# Begin Source File

SOURCE=.\GenTextPropAct.h
# End Source File
# Begin Source File

SOURCE=.\ImportDataDlg.h
# End Source File
# Begin Source File

SOURCE=.\ImportProp.h
# End Source File
# Begin Source File

SOURCE=.\Intoprop.hxx
# End Source File
# Begin Source File

SOURCE=.\MatchingObjects.h
# End Source File
# Begin Source File

SOURCE=.\Modident.hxx
# End Source File
# Begin Source File

SOURCE=.\Modidprp.hxx
# End Source File
# Begin Source File

SOURCE=.\MultiPI.h
# End Source File
# Begin Source File

SOURCE=.\ObjekteDoppeln.h
# End Source File
# Begin Source File

SOURCE=.\ObjekteVereinigen.h
# End Source File
# Begin Source File

SOURCE=.\ObjGeomW.h
# End Source File
# Begin Source File

SOURCE=.\Propactb.hxx
# End Source File
# Begin Source File

SOURCE=.\Propseq.hxx
# End Source File
# Begin Source File

SOURCE=.\QUERYFLD.HXX
# End Source File
# Begin Source File

SOURCE=.\RegisterExt.h
# End Source File
# Begin Source File

SOURCE=.\REGOBJ.H
# End Source File
# Begin Source File

SOURCE=.\ScriptPropAct.h
# End Source File
# Begin Source File

SOURCE=.\Selident.hxx
# End Source File
# Begin Source File

SOURCE=.\Selidprp.hxx
# End Source File
# Begin Source File

SOURCE=.\Selobdlg.hxx
# End Source File
# Begin Source File

SOURCE=.\SelObjProp.h
# End Source File
# Begin Source File

SOURCE=.\SelObjPropDlg.h
# End Source File
# Begin Source File

SOURCE=.\Selobwnd.hxx
# End Source File
# Begin Source File

SOURCE=.\SelOPrpTree.h
# End Source File
# Begin Source File

SOURCE=.\statimpl.hxx
# End Source File
# Begin Source File

SOURCE=.\STATUS.HXX
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# Begin Source File

SOURCE=.\TextSearchEngine.h
# End Source File
# Begin Source File

SOURCE=.\TRIAS03.H
# End Source File
# Begin Source File

SOURCE=.\TRiAS03Config.h
# End Source File
# Begin Source File

SOURCE=.\Trias03p.hxx
# End Source File
# Begin Source File

SOURCE=.\TriASTrans.h
# End Source File
# Begin Source File

SOURCE=.\txtsrchd.h
# End Source File
# Begin Source File

SOURCE=.\UNDOCF.HXX
# End Source File
# Begin Source File

SOURCE=.\UndoCreo.hxx
# End Source File
# Begin Source File

SOURCE=.\UNDODELO.HXX
# End Source File
# Begin Source File

SOURCE=.\UNDODELR.HXX
# End Source File
# Begin Source File

SOURCE=.\UNDODELT.HXX
# End Source File
# Begin Source File

SOURCE=.\UNDOFEAT.HXX
# End Source File
# Begin Source File

SOURCE=.\UNDOHWND.HXX
# End Source File
# Begin Source File

SOURCE=.\UNDOMODI.HXX
# End Source File
# Begin Source File

SOURCE=.\UNDOMODO.HXX
# End Source File
# Begin Source File

SOURCE=.\UNDOMODR.HXX
# End Source File
# Begin Source File

SOURCE=.\UNDOMODV.HXX
# End Source File
# Begin Source File

SOURCE=.\UNDOPBD.HXX
# End Source File
# Begin Source File

SOURCE=.\UNDOTEXT.HXX
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\obj32\res\Chckmark.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\res\checkmar.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\res\Copy.avi
# End Source File
# Begin Source File

SOURCE=.\obj32\res\CopyObjectsd.ebc
# End Source File
# Begin Source File

SOURCE=.\obj32\res\CopyObjectsr.ebc
# End Source File
# Begin Source File

SOURCE=.\obj32\res\Delete.avi
# End Source File
# Begin Source File

SOURCE=.\obj32\res\down.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\res\downdis.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\res\downfoc.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\res\downsel.bmp
# End Source File
# Begin Source File

SOURCE=.\headerst.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\res\headerst.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\res\Move.avi
# End Source File
# Begin Source File

SOURCE=.\obj32\res\MultiPI.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\ObjekteVereinigend.ebc
# End Source File
# Begin Source File

SOURCE=.\obj32\res\ObjekteVereinigenr.ebc
# End Source File
# Begin Source File

SOURCE=.\obj32\res\plft.bmp
# End Source File
# Begin Source File

SOURCE=.\obj32\res\plft_lar.bmp
# End Source File
# Begin Source File

SOURCE=.\Debug4\TRiASHelper.tlb
# End Source File
# Begin Source File

SOURCE=.\Release\TRiASHelper.tlb
# End Source File
# End Group
# Begin Group "Registry Scripts"

# PROP Default_Filter "*.rgs"
# Begin Source File

SOURCE=.\obj32\res\DelObPrp.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\DstObWnd.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\EnumONr.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\FakeTRiASLockFeature.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\GenTextPropAct.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\ImportData.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\ModIdPrp.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\ObjekteDoppeln.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\ObjekteVereinigen.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\PropSeq.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\Register.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\RegisterExt.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\ScriptPropAct.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\SelIdPrp.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\SelObjPrp.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\SelObWnd.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\StatImpl.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\TextSearchEngine.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\TRiAS03.rgs
# End Source File
# Begin Source File

SOURCE=.\obj32\res\TxtObPrp.rgs
# End Source File
# End Group
# Begin Group "Basic Scripts"

# PROP Default_Filter "*.ebf;*.ebs"
# Begin Source File

SOURCE=.\obj32\res\CopyObjects.ebs

!IF  "$(CFG)" == "Trias323 - Win32 Release"

# Begin Custom Build - Compiling basic script ...
InputDir=.\obj32\res
InputPath=.\obj32\res\CopyObjects.ebs
InputName=CopyObjects

"$(InputDir)\$(InputName)r.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o $(InputDir)\$(InputName)r.ebc -DNDEBUG $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

# Begin Custom Build - Compiling basic script ...
InputDir=.\obj32\res
InputPath=.\obj32\res\CopyObjects.ebs
InputName=CopyObjects

"$(InputDir)\$(InputName)d.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -n -o $(InputDir)\$(InputName)d.ebc -DDEBUG $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\obj32\res\ObjekteVereinigen.ebs

!IF  "$(CFG)" == "Trias323 - Win32 Release"

# Begin Custom Build - Compiling basic script ...
InputDir=.\obj32\res
InputPath=.\obj32\res\ObjekteVereinigen.ebs
InputName=ObjekteVereinigen

"$(InputDir)\$(InputName)r.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -c -n -o $(InputDir)\$(InputName)r.ebc -DNDEBUG $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "Trias323 - Win32 Debug"

# Begin Custom Build - Compiling basic script ...
InputDir=.\obj32\res
InputPath=.\obj32\res\ObjekteVereinigen.ebs
InputName=ObjekteVereinigen

"$(InputDir)\$(InputName)d.ebc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	bsl -n -o $(InputDir)\$(InputName)d.ebc -DDEBUG $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
