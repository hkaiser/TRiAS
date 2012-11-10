# Microsoft Developer Studio Project File - Name="Trias321" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Trias321 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Trias421.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Trias421.mak" CFG="Trias321 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Trias321 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Trias321 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiAS/TRiAS01", BBBAAAAA"
# PROP Scc_LocalPath "."
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Trias321 - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /WX /GX /Zi /O1 /D "NDEBUG" /D "__TRIAS01DLL__" /D "_ERROR_MESSAGERESOURCE" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__CV__" /D "_KOORD_ISDOUBLE" /D "_USE_LEGACY_CODE" /Fp".\Release\Trias321.pch" /Yu"trias01p.hxx" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 libGiST.lib containr.lib ospace5r.lib kernel32.lib ole32.lib user32.lib gdi32.lib uuid.lib delayimp.lib /nologo /dll /debug /machine:I386 /out:".\Release\TRiAS321.dll" /delayload:ole32.dll /delayload:advapi32.dll /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Release
TargetPath=.\Release\TRiAS321.dll
TargetName=TRiAS321
InputPath=.\Release\TRiAS321.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_R)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_R) 
	xcopy /F "$(OutDir)\$(TargetName).pdb" $(TRIASDIR_R) 
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB) 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WinDebug"
# PROP BASE Intermediate_Dir ".\WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /D "_DEBUG" /D "__TRIAS01DLL__" /D "_ERROR_MESSAGERESOURCE" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "MSWIND" /D "DLL" /D "__CV__" /D "_KOORD_ISDOUBLE" /D "_USE_LEGACY_CODE" /Fp".\Debug\trias321d.pch" /Yu"trias01p.hxx" /Fd".\Debug\trias321d.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 libGiSTd.lib cont50d.lib ospace5d.lib kernel32.lib ole32.lib user32.lib gdi32.lib uuid.lib delayimp.lib /nologo /dll /debug /machine:I386 /out:".\Debug\trias31d.dll" /delayload:ole32.dll /delayload:advapi32.dll /SUBSYSTEM:windows,4.0
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\Debug
TargetPath=.\Debug\trias31d.dll
TargetName=trias31d
InputPath=.\Debug\trias31d.dll
SOURCE="$(InputPath)"

"$(TRIASDIR_D)\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(TRIASDIR_D) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASDIR_D) 
	xcopy /F $(OutDir)\$(TargetName).lib $(TRIASLIB) 
	xcopy /F $(OutDir)\$(TargetName).pdb $(TRIASLIB) 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "Trias321 - Win32 Release"
# Name "Trias321 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\ACTIVATE.CXX
# End Source File
# Begin Source File

SOURCE=.\ASMBUF.CXX
# End Source File
# Begin Source File

SOURCE=.\BAKKEY.CXX
# End Source File
# Begin Source File

SOURCE=.\BITS.CXX
# End Source File
# Begin Source File

SOURCE=.\COMBIN.CXX
# End Source File
# Begin Source File

SOURCE=.\CompressedStream.cpp
# End Source File
# Begin Source File

SOURCE=.\CRYPT.CXX
# End Source File
# Begin Source File

SOURCE=.\CSSGuidHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\CUBE.CXX
# End Source File
# Begin Source File

SOURCE=.\DateTime.cpp
# End Source File
# Begin Source File

SOURCE=.\DB_IO.CXX
# End Source File
# Begin Source File

SOURCE=.\DBCLOSE.CXX
# End Source File
# Begin Source File

SOURCE=.\DBCODB.CXX
# End Source File
# Begin Source File

SOURCE=.\DBD.CXX
# End Source File
# Begin Source File

SOURCE=.\DBINITC.CXX
# End Source File
# Begin Source File

SOURCE=.\DBOPEN.CXX
# End Source File
# Begin Source File

SOURCE=.\DELETE.CXX
# End Source File
# Begin Source File

SOURCE=.\DeleteTextMerkmal.cpp
# End Source File
# Begin Source File

SOURCE=.\DIO_INIT.CXX
# End Source File
# Begin Source File

SOURCE=.\eexterr.cxx
# End Source File
# Begin Source File

SOURCE=.\EINVADDR.CXX
# End Source File
# Begin Source File

SOURCE=.\enfnderr.cxx
# End Source File
# Begin Source File

SOURCE=.\ENOMEM.CXX
# End Source File
# Begin Source File

SOURCE=.\enospac.cxx
# End Source File
# Begin Source File

SOURCE=.\ERRFKT.CXX
# End Source File
# Begin Source File

SOURCE=.\EVISERR.CXX
# End Source File
# Begin Source File

SOURCE=.\FDBCLOSE.CXX
# End Source File
# Begin Source File

SOURCE=.\FDBOPEN.CXX
# End Source File
# Begin Source File

SOURCE=.\FindTextMerkmal.cpp
# End Source File
# Begin Source File

SOURCE=.\FLEX.CXX
# End Source File
# Begin Source File

SOURCE=.\GENBACK.CXX
# End Source File
# Begin Source File

SOURCE=.\GeometryBlob.cpp
# End Source File
# Begin Source File

SOURCE=.\GeometryGuid.cpp
# End Source File
# Begin Source File

SOURCE=.\GeometryWKT.cpp
# End Source File
# Begin Source File

SOURCE=.\GETDWENT.CXX
# ADD CPP /D "COMPRESS_PWD"
# End Source File
# Begin Source File

SOURCE=.\GETDWNAM.CXX
# End Source File
# Begin Source File

SOURCE=.\GETDWUID.CXX
# End Source File
# Begin Source File

SOURCE=.\GETPATH.CXX
# End Source File
# Begin Source File

SOURCE=.\GetText.cpp
# End Source File
# Begin Source File

SOURCE=.\GetTextMerkmal.cpp
# End Source File
# Begin Source File

SOURCE=.\HeaderEntry.cpp
# End Source File
# Begin Source File

SOURCE=.\HTCONT.CXX
# End Source File
# Begin Source File

SOURCE=.\HTDEL.CXX
# End Source File
# Begin Source File

SOURCE=.\HTINS.CXX
# End Source File
# Begin Source File

SOURCE=.\HTPREP.CXX
# End Source File
# Begin Source File

SOURCE=.\HTSEARCH.CXX
# End Source File
# Begin Source File

SOURCE=.\HTSHRINK.CXX
# End Source File
# Begin Source File

SOURCE=.\HTSPLIT.CXX
# End Source File
# Begin Source File

SOURCE=.\HTWIND_F.CXX
# End Source File
# Begin Source File

SOURCE=.\HtWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\IdentBaseHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\INITTAB.CXX
# End Source File
# Begin Source File

SOURCE=.\INSERT.CXX
# End Source File
# Begin Source File

SOURCE=.\IsAlike.cpp
# End Source File
# Begin Source File

SOURCE=.\KEY_IO.CXX
# End Source File
# Begin Source File

SOURCE=.\KEYCAT.CXX
# End Source File
# Begin Source File

SOURCE=.\KEYCMP.CXX
# End Source File
# Begin Source File

SOURCE=.\KEYDEL.CXX
# End Source File
# Begin Source File

SOURCE=.\KEYFRST.CXX
# End Source File
# Begin Source File

SOURCE=.\KEYINI.CXX
# End Source File
# Begin Source File

SOURCE=.\KEYINS.CXX
# End Source File
# Begin Source File

SOURCE=.\KEYLAST.CXX
# End Source File
# Begin Source File

SOURCE=.\KEYLOC.CXX
# End Source File
# Begin Source File

SOURCE=.\KEYNEXT.CXX
# End Source File
# Begin Source File

SOURCE=.\KEYPREV.CXX
# End Source File
# Begin Source File

SOURCE=.\KEYREAD.CXX
# End Source File
# Begin Source File

SOURCE=.\KEYUTIL.CXX
# End Source File
# Begin Source File

SOURCE=.\LADRC.CXX
# End Source File
# Begin Source File

SOURCE=.\LIBMAIN1.CXX

!IF  "$(CFG)" == "Trias321 - Win32 Release"

!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

# ADD CPP /WX /Od

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LISTEN.CXX
# End Source File
# Begin Source File

SOURCE=.\LOCATE.CXX
# End Source File
# Begin Source File

SOURCE=.\LOCFRST.CXX
# End Source File
# Begin Source File

SOURCE=.\LOCLAST.CXX
# End Source File
# Begin Source File

SOURCE=.\LOCSLT.CXX
# End Source File
# Begin Source File

SOURCE=.\MYCRYPT.CXX
# End Source File
# Begin Source File

SOURCE=.\NativeConnectionFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\NativeGeometry.cpp
# End Source File
# Begin Source File

SOURCE=.\NativeGeometrySearch.cpp
# End Source File
# Begin Source File

SOURCE=.\NativeIdent.cpp
# End Source File
# Begin Source File

SOURCE=.\NativeMerkmal.cpp
# End Source File
# Begin Source File

SOURCE=.\NativeObject.cpp
# End Source File
# Begin Source File

SOURCE=.\NativePbd.cpp
# End Source File
# Begin Source File

SOURCE=.\NativeRelation.cpp
# End Source File
# Begin Source File

SOURCE=.\NativeView.cpp
# End Source File
# Begin Source File

SOURCE=.\NEWFILE.CXX
# End Source File
# Begin Source File

SOURCE=.\NGMC.CXX
# End Source File
# Begin Source File

SOURCE=.\NODEXP.CXX
# End Source File
# Begin Source File

SOURCE=.\NODFIL.CXX
# End Source File
# Begin Source File

SOURCE=.\NODSPL.CXX
# End Source File
# Begin Source File

SOURCE=.\NULLCMP.CXX
# ADD CPP /D "NULLCMP"
# End Source File
# Begin Source File

SOURCE=.\ObjectGiST.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjGuidHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\OKSHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\OVERFL.CXX
# End Source File
# Begin Source File

SOURCE=.\PARENT.CXX
# End Source File
# Begin Source File

SOURCE=.\PerfCounters.cpp
# End Source File
# Begin Source File

SOURCE=.\PGZERO.CXX
# End Source File
# Begin Source File

SOURCE=.\PUTINL.CXX
# End Source File
# Begin Source File

SOURCE=.\PutText.cpp
# End Source File
# Begin Source File

SOURCE=.\PutTextMerkmal.cpp
# End Source File
# Begin Source File

SOURCE=.\QTCONT.CXX
# End Source File
# Begin Source File

SOURCE=.\QTDEL.CXX
# End Source File
# Begin Source File

SOURCE=.\QTINS.CXX
# End Source File
# Begin Source File

SOURCE=.\QTPREP.CXX
# End Source File
# Begin Source File

SOURCE=.\QTSEARCH.CXX
# End Source File
# Begin Source File

SOURCE=.\QTSHRINK.CXX
# End Source File
# Begin Source File

SOURCE=.\QTSPLIT.CXX
# End Source File
# Begin Source File

SOURCE=.\QTWIND_F.CXX
# End Source File
# Begin Source File

SOURCE=.\QtWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\QUAD.CXX
# End Source File
# Begin Source File

SOURCE=.\REINDEX.CXX
# End Source File
# Begin Source File

SOURCE=.\ResString.cpp
# End Source File
# Begin Source File

SOURCE=.\ROOTSP.CXX
# End Source File
# Begin Source File

SOURCE=.\ScaleHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\SETERR.CXX
# End Source File
# Begin Source File

SOURCE=.\SHRINK.CXX
# End Source File
# Begin Source File

SOURCE=.\STATIST.CXX
# End Source File
# Begin Source File

SOURCE=.\STRFCNS.CXX
# End Source File
# Begin Source File

SOURCE=.\Strings.cpp
# End Source File
# Begin Source File

SOURCE=.\STRNCHR.CXX
# End Source File
# Begin Source File

SOURCE=.\SWITCHKC.CXX
# End Source File
# Begin Source File

SOURCE=.\TARGETFI.CXX
# End Source File
# Begin Source File

SOURCE=.\TLOCSLT.CXX
# End Source File
# Begin Source File

SOURCE=.\TPUTINL.CXX
# End Source File
# Begin Source File

SOURCE=.\TRIAS01P.CXX
# ADD CPP /Yc"trias01p.hxx"
# End Source File
# Begin Source File

SOURCE=.\trias31d.def
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\TRIAS321.DEF
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\obj32\Trias321.RC
# ADD BASE RSC /l 0x407 /i "obj32"
# ADD RSC /l 0x407 /i "obj32"
# End Source File
# Begin Source File

SOURCE=.\TZAPSLT.CXX
# End Source File
# Begin Source File

SOURCE=.\UniqueHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\VERSION.CXX
# End Source File
# Begin Source File

SOURCE=.\ViewPropHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\ZACCESS.CXX
# End Source File
# Begin Source File

SOURCE=.\ZACTIV.CXX
# End Source File
# Begin Source File

SOURCE=.\ZAPSLT.CXX
# End Source File
# Begin Source File

SOURCE=.\ZDISPOSE.CXX
# End Source File
# Begin Source File

SOURCE=.\ZFILLNEW.CXX
# End Source File
# Begin Source File

SOURCE=.\ZKEYFIND.CXX
# End Source File
# Begin Source File

SOURCE=.\ZKEYFRST.CXX
# End Source File
# Begin Source File

SOURCE=.\ZKEYLAST.CXX
# End Source File
# Begin Source File

SOURCE=.\ZKEYNEXT.CXX
# End Source File
# Begin Source File

SOURCE=.\ZKEYPREV.CXX
# End Source File
# Begin Source File

SOURCE=.\ZKEYREAD.CXX
# End Source File
# Begin Source File

SOURCE=.\ZREADREC.CXX
# End Source File
# Begin Source File

SOURCE=.\ZRESTOR.CXX
# End Source File
# Begin Source File

SOURCE=.\ZSETFILE.CXX
# End Source File
# Begin Source File

SOURCE=.\ZSETPAGE.CXX
# End Source File
# Begin Source File

SOURCE=.\ZTOUCH.CXX
# End Source File
# Begin Source File

SOURCE=.\ZWRITREC.CXX
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\CompressedStream.h
# End Source File
# Begin Source File

SOURCE=.\ConnectFilterWrappers.h
# End Source File
# Begin Source File

SOURCE=.\ERRFKT.HXX
# End Source File
# Begin Source File

SOURCE=.\FreeMapForCompressedStream.h
# End Source File
# Begin Source File

SOURCE=..\Include\GeometryBlob.h
# End Source File
# Begin Source File

SOURCE=..\Include\GeometryWKT.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\HeaderEntry.h
# End Source File
# Begin Source File

SOURCE=..\Include\com\MapOffsetsForCompressedStream.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\NativeIdent.h
# End Source File
# Begin Source File

SOURCE=..\Include\NativeMerkmal.h
# End Source File
# Begin Source File

SOURCE=..\Include\NativeMerkmalsListe.h
# End Source File
# Begin Source File

SOURCE=..\Include\NativeObject.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\NativeView.h
# End Source File
# Begin Source File

SOURCE=.\ObjectGiST.h
# End Source File
# Begin Source File

SOURCE=..\Include\ObjGuidHeader.h
# End Source File
# Begin Source File

SOURCE=.\PerfCounters.h
# End Source File
# Begin Source File

SOURCE=.\Strings.h
# End Source File
# Begin Source File

SOURCE=.\Syncdb.hxx
# End Source File
# Begin Source File

SOURCE=.\TRiAS01Config.h
# End Source File
# Begin Source File

SOURCE=.\trias01p.hxx
# End Source File
# Begin Source File

SOURCE=.\TRIAS01R.H
# End Source File
# Begin Source File

SOURCE=..\Include\ViewPropHeader.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Debug\MSG00407.bin
# End Source File
# Begin Source File

SOURCE=.\Release\Msg00407.bin
# End Source File
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=.\DbmsVersion.tpl

!IF  "$(CFG)" == "Trias321 - Win32 Release"

USERDEP__DBMSV="TRiAS161.Mak"	
# Begin Custom Build
InputPath=.\DbmsVersion.tpl

"DbmsVersion.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f TRiAS161.Mak DbmsVersion.h

# End Custom Build

!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

USERDEP__DBMSV="TRiAS161.Mak"	
# Begin Custom Build
InputPath=.\DbmsVersion.tpl

"DbmsVersion.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f TRiAS161.Mak DbmsVersion.h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DESC.TPL
# End Source File
# Begin Source File

SOURCE=.\RIGHTS.TPL

!IF  "$(CFG)" == "Trias321 - Win32 Release"

USERDEP__RIGHT="trias161.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\RIGHTS.TPL

"Rights.exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f TRiAS161.Mak Rights.Exe

# End Custom Build

!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

USERDEP__RIGHT="trias161.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\RIGHTS.TPL

"Rights.exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f TRiAS161.Mak Rights.Exe

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiAS01v.Tpl

!IF  "$(CFG)" == "Trias321 - Win32 Release"

USERDEP__TRIAS="trias161.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\TRiAS01v.Tpl

"TRiAS321.Rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f TRiAS161.Mak TRiAS321.Rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

USERDEP__TRIAS="trias161.mak"	
# Begin Custom Build - Generating version strings ...
InputPath=.\TRiAS01v.Tpl

"TRiAS321.Rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f TRiAS161.Mak TRiAS321.Rcv

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRIAS161.MAK
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\TRIAS31D.TPL
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\TRIAS321.TPL
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Obsolete Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat"
# Begin Source File

SOURCE=.\DELHD_F.CXX
# End Source File
# Begin Source File

SOURCE=.\GETHD_F.CXX
# End Source File
# Begin Source File

SOURCE=.\GETHDLEN.CXX
# End Source File
# Begin Source File

SOURCE=.\Puthd_f.cxx
# End Source File
# End Group
# Begin Group "MessageStrings"

# PROP Default_Filter "*.mc"
# Begin Source File

SOURCE=.\TRIAS01.MC

!IF  "$(CFG)" == "Trias321 - Win32 Release"

# Begin Custom Build - Generating message resource ...
InputDir=.
OutDir=.\Release
InputPath=.\TRIAS01.MC
InputName=TRIAS01

"$(OutDir)\Msg407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cl -nologo -TC -C -EP -DNDEBUG -u $(InputPath) > $(OutDir)\$(InputName).i 
	mc -e hmc -h $(InputDir) -r "$(OutDir)" "$(OutDir)\$(InputName).i " 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

# Begin Custom Build - Generating message resource ...
InputDir=.
OutDir=.\Debug
InputPath=.\TRIAS01.MC
InputName=TRIAS01

"$(OutDir)\Msg00407.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cl -nologo -TC -C -EP -D_DEBUG -u $(InputPath) > $(OutDir)\$(InputName).i 
	mc -e hmc -h $(InputDir) -r "$(OutDir)" "$(OutDir)\$(InputName).i" 
	
# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
