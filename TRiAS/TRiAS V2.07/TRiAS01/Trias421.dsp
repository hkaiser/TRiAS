# Microsoft Developer Studio Project File - Name="Trias321" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
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
!MESSAGE "Trias321 - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Trias321 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""$/TRiAS/TRiAS/TRiAS01", BBBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /WX /GX /O1 /D "NDEBUG" /D "__CV__" /D "STRICT" /D "DLL" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "__TRIAS01DLL__" /D "OS_WIN_95" /D "OS_NO_WSTRING" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /Fp".\Release\Trias321.pch" /Yu"trias01p.hxx" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 tfrmwork.lib cont50r.lib ospace2r.lib kernel32.lib ole32.lib user32.lib gdi32.lib uuid.lib /nologo /dll /machine:I386 /out:".\Release\Trias321.dll" /stub:"rights.exe" /SUBSYSTEM:windows,4.0
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\.\Release
TargetPath=.\Release\Trias321.dll
TargetName=Trias321
InputPath=.\Release\Trias321.dll
SOURCE=$(InputPath)

BuildCmds= \
	copy $(TargetPath) c:\trias.mvc\trias300.rel \
	copy $(OutDir)\$(TargetName).lib e:\triasdev.mvc\lib50 \
	

"c:\trias.mvc\trias300.rel\$(TargetName).dll" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   $(BuildCmds)

"e:\triasdev.mvc\lib50\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
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
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /Zi /Od /Ob1 /D "_DEBUG" /D "__CV__" /D "STRICT" /D "DLL" /D "MSWIND" /D "WIN32" /D "_WINDOWS" /D "__XT" /D "__DEXPROCS" /D "__TRIAS01DLL__" /D "OS_WIN_95" /D "OS_STL_ASSERT" /D "OS_NO_WSTRING" /D "OS_MULTI_THREADED" /D "OS_NO_STREAM_SUPPORT" /FR /Fp".\Debug\trias321d.pch" /Yu"trias01p.hxx" /Fd".\Debug\trias321d.pdb" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 tfrm32d.lib cont50d.lib ospace5d.lib kernel32.lib ole32.lib user32.lib gdi32.lib uuid.lib /nologo /base:"0x6b0000" /dll /profile /debug /machine:I386 /out:".\Debug\trias31d.dll" /stub:"rights.exe" /SUBSYSTEM:windows,4.0
# Begin Custom Build - Copying Target to Destination ...
OutDir=.\.\Debug
TargetPath=.\Debug\trias31d.dll
TargetName=trias31d
InputPath=.\Debug\trias31d.dll
SOURCE=$(InputPath)

BuildCmds= \
	copy $(TargetPath) c:\trias.mvc\trias200 \
	copy $(OutDir)\$(TargetName).lib e:\triasdev.mvc\lib50 \
	copy $(OutDir)\$(TargetName).pdb e:\triasdev.mvc\lib50 \
	

"c:\trias.mvc\trias200\$(TargetName).dll" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"e:\triasdev.mvc\lib50\$(TargetName).lib" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"e:\triasdev.mvc\lib50\$(TargetName).pdb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
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

SOURCE=.\CRYPT.CXX
# End Source File
# Begin Source File

SOURCE=.\CUBE.CXX
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

SOURCE=.\FLEX.CXX
# End Source File
# Begin Source File

SOURCE=.\GENBACK.CXX
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

SOURCE=.\HTWINDOW.CXX
# End Source File
# Begin Source File

SOURCE=.\INITTAB.CXX
# End Source File
# Begin Source File

SOURCE=.\INSERT.CXX
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

SOURCE=.\OVERFL.CXX
# End Source File
# Begin Source File

SOURCE=.\PARENT.CXX
# End Source File
# Begin Source File

SOURCE=.\PGZERO.CXX
# End Source File
# Begin Source File

SOURCE=.\PUTINL.CXX
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

SOURCE=.\QTWINDOW.CXX
# End Source File
# Begin Source File

SOURCE=.\QUAD.CXX
# End Source File
# Begin Source File

SOURCE=.\REINDEX.CXX
# End Source File
# Begin Source File

SOURCE=.\RESOURCE.CXX
# End Source File
# Begin Source File

SOURCE=.\ROOTSP.CXX
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

SOURCE=.\obj32\Trias321.RC

!IF  "$(CFG)" == "Trias321 - Win32 Release"

# ADD BASE RSC /l 0x407 /i "obj32"
# ADD RSC /l 0x407 /i "obj32"

!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

# ADD BASE RSC /l 0x407 /i "obj32"
# ADD RSC /l 0x407 /i "obj32"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TZAPSLT.CXX
# End Source File
# Begin Source File

SOURCE=.\VERSION.CXX
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

SOURCE=.\ERRFKT.HXX
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\HeaderEntry.h
# End Source File
# Begin Source File

SOURCE=.\Syncdb.hxx
# End Source File
# Begin Source File

SOURCE=.\trias01p.hxx
# End Source File
# Begin Source File

SOURCE=.\TRIAS01R.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Versioning"

# PROP Default_Filter "*.tpl;*.mak"
# Begin Source File

SOURCE=.\RIGHTS.TPL
USERDEP__RIGHT="TRiAS161.Mak"	

!IF  "$(CFG)" == "Trias321 - Win32 Release"

# Begin Custom Build - Generating version strings ...
InputPath=.\RIGHTS.TPL

"Rights.exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f TRiAS161.Mak Rights.Exe

# End Custom Build

!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

# Begin Custom Build - Generating version strings ...
InputPath=.\RIGHTS.TPL

"Rights.exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f TRiAS161.Mak Rights.Exe

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TRiAS01v.Tpl
USERDEP__TRIAS="TRiAS161.Mak"	

!IF  "$(CFG)" == "Trias321 - Win32 Release"

# Begin Custom Build - Generating version strings ...
InputPath=.\TRiAS01v.Tpl

"TRiAS321.Rcv" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nmake -nologo -f TRiAS161.Mak TRiAS321.Rcv

# End Custom Build

!ELSEIF  "$(CFG)" == "Trias321 - Win32 Debug"

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
# End Target
# End Project
