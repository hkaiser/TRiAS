# Microsoft Developer Studio Project File - Name="Trias322" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TRIAS322 - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Trias422.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Trias422.mak" CFG="TRIAS322 - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Trias322 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Trias322 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/TRiAS02", CWAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Trias322 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WinRel"
# PROP BASE Intermediate_Dir ".\WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "__XT" /D "__DEXPROCS" /D "__TRIAS02DLL__" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "DLL" /D "__CV__" /D "_KOORD_ISDOUBLE" /Yu"trias02p.hxx" /Fd".\Release/TRiAS322.pdb" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ospace5r.lib trias321.lib containr.lib tfrmlr.lib tfrmwork.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:".\Release\TRiAS322.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Release
TargetPath=.\Release\TRiAS322.dll
TargetName=TRiAS322
InputPath=.\Release\TRiAS322.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_R) 
	xcopy /F $(OutDir)\TRiAS322.pdb $(TRIASDIR_R) 
	xcopy /F "$(OutDir)\TRiAS322.lib" $(TRIASLIB) 
	xcopy /F $(OutDir)\TRiAS322.pdb $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug4"
# PROP Intermediate_Dir ".\Debug4"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "__XT" /D "__DEXPROCS" /D "__TRIAS02DLL__" /D "WIN32" /D "_WINDOWS" /D "MSWIND" /D "DLL" /D "__CV__" /D "_KOORD_ISDOUBLE" /Fp".\Debug4\trias322d.pch" /Yu"trias02p.hxx" /Fd".\Debug4\trias322d.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 ospace5d.lib trias31d.lib cont50d.lib tfrmld.lib tfrm32d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /pdb:".\Debug4/trias322d.pdb" /debug /machine:I386 /out:".\Debug4\trias32d.dll" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Debug4
TargetPath=.\Debug4\trias32d.dll
TargetName=trias32d
InputPath=.\Debug4\trias32d.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F "$(TargetPath)" $(TRIASDIR_D) 
	xcopy /F "$(OutDir)\$(TargetName).lib" $(TRIASLIB) 
	xcopy /F $(OutDir)\trias322d.pdb $(TRIASLIB) 
	xcopy /F $(OutDir)\trias322d.pdb $(TRIASDIR_D) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Trias322 - Win32 Release"
# Name "Trias322 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Group "Obsolete Sources"

# PROP Default_Filter "*.cxx"
# Begin Source File

SOURCE=.\ATTRIBS.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\COMMFIL.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\DEL.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\DELGI.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\DELGIF.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\DELGIL.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\DELGIP.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\DELID.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\DELKAN.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\DELKANF.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\DELLINK.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\DELMIN.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\DELREL.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\DELRELKO.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\FINDREL.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\FNDGI.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\FNDKA.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\FNDLI.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\FNDMA.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\FNDPU.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\FNDTXT.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\FNDTXTN.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\FREETEXT.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GERADE.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETAPU.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETDBLM.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETGI.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETGIF.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETGIL.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETGIP.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETKAN.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETLONGM.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETMERKL.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETMI.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETMIT.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETRCODE.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETREL.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETRIF.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETRIG.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETRIL.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETRIP.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETTEXT.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETTEXTL.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\GETTEXTN.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\HTFUNC.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\HTMANR.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\IGLAGE.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\IGPTNL.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ISALIKE.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\KOMPLEX.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\KONS.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\KONSOBJ.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\KONSSATZ.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\KONSUTIL.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MDELKI.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MDELKM.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MDELKR.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MERKINFO.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MERKMAL.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MFIND.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MGETKM.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MGETKR.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MGETKT.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MGETL.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MGETTX.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MGETWM.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MODID.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MPUTKI.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MPUTKM.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MPUTKR.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MPUTKT.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MPUTTX.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\OVLFOBJ.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\OVLLOBJ.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\OVLPOBJ.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PBD.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PBDIDS.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PBDTEMP.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PUINFL.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PUTFOBJ.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PUTIDENT.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PUTKOBJ.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PUTLINK.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PUTLOBJ.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PUTMIT.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PUTPKT.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PUTPOBJ.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PUTREL.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PUTTEMPL.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PUTTOBJ.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PUTTXTC.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\PUTTXTCN.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\QTFUNC.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\RELATIO.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\RIGIN.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\RIGINFO.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\RIGKP.CXX
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\STINFL.CXX
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=.\CTF.CXX
# End Source File
# Begin Source File

SOURCE=.\CTFService.cpp
# End Source File
# Begin Source File

SOURCE=.\DATETIME.CXX
# End Source File
# Begin Source File

SOURCE=.\DB.CXX
# End Source File
# Begin Source File

SOURCE=.\dbasrt02.cxx
# End Source File
# Begin Source File

SOURCE=.\DBGETGI.CXX
# End Source File
# Begin Source File

SOURCE=.\DLLBIND.CXX
# End Source File
# Begin Source File

SOURCE=.\DRAWRECT.CXX
# SUBTRACT CPP /D "__CV__" /Yu
# End Source File
# Begin Source File

SOURCE=.\EFONT.CXX
# End Source File
# Begin Source File

SOURCE=.\EPEN.CXX
# End Source File
# Begin Source File

SOURCE=.\EVALKOEF.CXX
# End Source File
# Begin Source File

SOURCE=.\FormatString.cpp
# End Source File
# Begin Source File

SOURCE=.\GEO_OBJ.CXX
# End Source File
# Begin Source File

SOURCE=.\GEO_OBJ1.CXX
# End Source File
# Begin Source File

SOURCE=.\GeoDBCom.cpp
# End Source File
# Begin Source File

SOURCE=.\GeoObjekt.cpp
# End Source File
# Begin Source File

SOURCE=.\GEOTEXT.CXX
# End Source File
# Begin Source File

SOURCE=.\GIWINDOW.CXX
# End Source File
# Begin Source File

SOURCE=.\GlobalVars.cpp
# End Source File
# Begin Source File

SOURCE=.\HDRENTRY.CXX
# End Source File
# Begin Source File

SOURCE=.\LIBMAIN2.CXX
# End Source File
# Begin Source File

SOURCE=.\ObjGuid.cpp
# End Source File
# Begin Source File

SOURCE=.\OBJMTREE.CXX
# End Source File
# Begin Source File

SOURCE=.\OLISTE.CXX
# End Source File
# Begin Source File

SOURCE=.\PALETTE.CXX
# End Source File
# Begin Source File

SOURCE=.\PROFDLL.CXX
# End Source File
# Begin Source File

SOURCE=.\RECT.CXX
# End Source File
# Begin Source File

SOURCE=.\REGISTRY.CXX
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\STRUTIL.CXX
# End Source File
# Begin Source File

SOURCE=.\TRIAS02P.CXX
# ADD CPP /Yc"trias02p.hxx"
# End Source File
# Begin Source File

SOURCE=.\obj32\Trias322.RC
# ADD BASE RSC /l 0x407 /i "obj32"
# ADD RSC /l 0x407 /i "obj32" /i ".\obj32"
# End Source File
# Begin Source File

SOURCE=.\Utils.cpp
# End Source File
# Begin Source File

SOURCE=.\VISERROR.CXX
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\Include\CSPoint.h
# End Source File
# Begin Source File

SOURCE=..\Include\CSRectGeom.h
# End Source File
# Begin Source File

SOURCE=.\FONTSEL.H
# End Source File
# Begin Source File

SOURCE=.\GETRCODE.HXX
# End Source File
# Begin Source File

SOURCE=.\MapCaches.h
# End Source File
# Begin Source File

SOURCE=.\MERKINFO.HXX
# End Source File
# Begin Source File

SOURCE=.\PALETTE.HXX
# End Source File
# Begin Source File

SOURCE=.\PBDIDS.HXX
# End Source File
# Begin Source File

SOURCE=.\PROTOCOL.HXX
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# Begin Source File

SOURCE=.\TRIAS02.H
# End Source File
# Begin Source File

SOURCE=.\trias02p.hxx
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\obj32\RES\Deinstal.ico
# End Source File
# Begin Source File

SOURCE=.\obj32\MSG00407.bin
# End Source File
# End Group
# Begin Group "MessagingStrings"

# PROP Default_Filter "*.mc"
# Begin Source File

SOURCE=.\TRiAS02.MC

!IF  "$(CFG)" == "Trias322 - Win32 Release"

# Begin Custom Build - Generating message tables ...
InputDir=.
InputPath=.\TRiAS02.MC
InputName=TRiAS02

BuildCmds= \
	mc -e hmc -h $(InputDir) $(InputPath)

"$(InputName).rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"

# Begin Custom Build - Generating message tables ...
InputDir=.
InputPath=.\TRiAS02.MC
InputName=TRiAS02

BuildCmds= \
	mc -e hmc -h $(InputDir) $(InputPath)

"$(InputName).rc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).hmc" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.mak;*.tpl"
# Begin Source File

SOURCE=.\AutoBuildCount.h
# End Source File
# Begin Source File

SOURCE=.\obj32\TRIAS162.MAK
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\obj32\TRIAS32V.tpl

!IF  "$(CFG)" == "Trias322 - Win32 Release"

USERDEP__TRIAS="obj32\trias162.mak"	
# Begin Custom Build - Generating Version information ...
InputPath=.\obj32\TRIAS32V.tpl

"obj32\trias322.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f obj32\trias162.mak obj32\trias322.rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Trias322 - Win32 Debug"

USERDEP__TRIAS="obj32\trias162.mak"	
# Begin Custom Build - Generating Version information ...
InputPath=.\obj32\TRIAS32V.tpl

"obj32\trias322.rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f obj32\trias162.mak obj32\trias322.rcv

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
