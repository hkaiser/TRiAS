# Microsoft Developer Studio Project File - Name="Mitab" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Mitab - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Mitab.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Mitab.mak" CFG="Mitab - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Mitab - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Mitab - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "Mitab - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /Gm /GX /Zi /O1 /I ".\CPL" /I ".\OGR" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "CPL_DISABLE_DLL" /D "MITAB_DISABLE_DLL" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Mitab - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I ".\CPL" /I ".\OGR" /D "_DEBUG" /D "DEBUG" /D "WIN32" /D "_WINDOWS" /D "CPL_DISABLE_DLL" /D "MITAB_DISABLE_DLL" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\Mitabd.lib"

!ENDIF 

# Begin Target

# Name "Mitab - Win32 Release"
# Name "Mitab - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "MiTab Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=.\mitab\mitab_bounds.cpp
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_capi.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_coordsys.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_datfile.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_feature.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_feature_mif.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_geometry.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_idfile.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_imapinfofile.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_indfile.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_mapcoordblock.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_mapfile.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_mapheaderblock.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_mapindexblock.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_mapobjectblock.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_maptoolblock.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_middatafile.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_miffile.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_ogr_datasource.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_ogr_driver.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_rawbinblock.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_spatialref.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_tabfile.cpp"
# End Source File
# Begin Source File

SOURCE=.\mitab\mitab_tabseamless.cpp
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_tabview.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_tooldef.cpp"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_utils.cpp"
# End Source File
# End Group
# Begin Group "OGR Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=".\ogr\ogr_fromepsg.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogr_srs_proj4.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogr_srsnode.cpp"
# End Source File
# Begin Source File

SOURCE=.\ogr\ogrct.cpp
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrcurve.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrdatasource.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrfeature.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrfeaturedefn.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrfeaturestyle.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrfielddefn.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrgeometry.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrgeometrycollection.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrgeometryfactory.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrlayer.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrlinearring.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrlinestring.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrmultilinestring.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrmultipoint.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrmultipolygon.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrpoint.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrpolygon.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrsfdriver.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrsfdriverregistrar.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrspatialreference.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrsurface.cpp"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrutils.cpp"
# End Source File
# End Group
# Begin Group "CPL Sources"

# PROP Default_Filter "*.cpp"
# Begin Source File

SOURCE=".\cpl\cpl_conv.cpp"
# End Source File
# Begin Source File

SOURCE=".\cpl\cpl_csv.cpp"
# End Source File
# Begin Source File

SOURCE=".\cpl\cpl_dir.cpp"
# End Source File
# Begin Source File

SOURCE=".\cpl\cpl_error.cpp"
# End Source File
# Begin Source File

SOURCE=".\cpl\cpl_findfile.cpp"
# End Source File
# Begin Source File

SOURCE=".\cpl\cpl_path.cpp"
# End Source File
# Begin Source File

SOURCE=".\cpl\cpl_string.cpp"
# End Source File
# Begin Source File

SOURCE=".\cpl\cpl_vsisimple.cpp"
# End Source File
# Begin Source File

SOURCE=".\cpl\cplgetsymbol.cpp"
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "MiTab Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=".\mitab\mitab.h"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_capi.h"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_geometry.h"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_ogr_driver.h"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_priv.h"
# End Source File
# Begin Source File

SOURCE=".\mitab\mitab_utils.h"
# End Source File
# End Group
# Begin Group "OGR headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=".\ogr\ogr_core.h"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogr_feature.h"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogr_featurestyle.h"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogr_geometry.h"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogr_p.h"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogr_spatialref.h"
# End Source File
# Begin Source File

SOURCE=".\ogr\ogrsf_frmts.h"
# End Source File
# End Group
# Begin Group "CPL Headers"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=".\cpl\cpl_config.h"
# End Source File
# Begin Source File

SOURCE=".\cpl\cpl_conv.h"
# End Source File
# Begin Source File

SOURCE=".\cpl\cpl_csv.h"
# End Source File
# Begin Source File

SOURCE=".\cpl\cpl_error.h"
# End Source File
# Begin Source File

SOURCE=".\cpl\cpl_port.h"
# End Source File
# Begin Source File

SOURCE=".\cpl\cpl_string.h"
# End Source File
# Begin Source File

SOURCE=".\cpl\cpl_vsi.h"
# End Source File
# End Group
# End Group
# End Target
# End Project
