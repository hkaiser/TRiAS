# Microsoft Developer Studio Project File - Name="imcopy" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=imcopy - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "imcopy.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "imcopy.mak" CFG="imcopy - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "imcopy - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "imcopy - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Imtools/imcopy", ZOBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "imcopy - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /Ob2 /I "..\include" /I "..\..\include" /I "..\..\libsdsc\include" /I "..\..\libim\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "__STDC__" /D "MSWIND" /D "STRICT" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 binmode.obj kernel32.lib user32.lib gdi32.lib /nologo /subsystem:console /debug /machine:I386
# SUBTRACT LINK32 /verbose /nodefaultlib /force
# Begin Custom Build
TargetPath=.\Release\imcopy.exe
InputPath=.\Release\imcopy.exe
InputName=imcopy
SOURCE="$(InputPath)"

"$(IMTOOLS_ROOT)\$(InputName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(IMTOOLS_ROOT)

# End Custom Build

!ELSEIF  "$(CFG)" == "imcopy - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "imcopy___Win32_Debug"
# PROP BASE Intermediate_Dir "imcopy___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Zi /Od /I "$(UWINBASE)\usr\include" /I "..\include" /I "..\..\libsdsc\include" /I "..\..\libim\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_POSIX_" /D __STDC__=1 /D _X86_=1 /D "unix" /D "MSWIND" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /I "..\include" /I "..\..\include" /I "..\..\libsdsc\include" /I "..\..\libim\include" /D "__STDC__" /D "MSWIND" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "STRICT" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ast.lib posix.lib libjpeg.lib kernel32.lib gdi32.lib user32.lib libc.lib /nologo /entry:"WinMainCRTStartup" /subsystem:console /debug /machine:I386 /nodefaultlib /include:"_init_libposix" /include:"_free" /include:"_fopen" /include:"_fclose" /include:"_fseek" /include:"_fread" /include:"_fwrite" /include:"_realloc" /include:"_calloc" /include:"_fflush" /force /libpath:"$(UWINBASE)\usr\lib" /libpath:"..\..\jpeg-6b"
# SUBTRACT BASE LINK32 /verbose
# ADD LINK32 binmode.obj kernel32.lib user32.lib gdi32.lib /nologo /subsystem:console /incremental:yes /debug /machine:I386 /out:"Debug/imcopyd.exe"
# SUBTRACT LINK32 /verbose /nodefaultlib /force
# Begin Custom Build
TargetPath=.\Debug\imcopyd.exe
TargetName=imcopyd
InputPath=.\Debug\imcopyd.exe
SOURCE="$(InputPath)"

"$(IMTOOLS_ROOT_DEBUG)\$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	xcopy /F $(TargetPath) $(IMTOOLS_ROOT_DEBUG)

# End Custom Build

!ENDIF 

# Begin Target

# Name "imcopy - Win32 Release"
# Name "imcopy - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\imcopy.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
