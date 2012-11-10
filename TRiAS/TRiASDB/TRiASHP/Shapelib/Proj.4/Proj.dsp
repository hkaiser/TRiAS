# Microsoft Developer Studio Project File - Name="Proj" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Proj - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Proj.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Proj.mak" CFG="Proj - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Proj - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Proj - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TRiAS/TRiASDB/TRiASHP/Shapelib", FRDBAAAA"
# PROP Scc_LocalPath ".."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Proj - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Proj - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Proj - Win32 Release"
# Name "Proj - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\aasincos.c
# End Source File
# Begin Source File

SOURCE=.\src\adjlon.c
# End Source File
# Begin Source File

SOURCE=.\src\bch2bps.c
# End Source File
# Begin Source File

SOURCE=.\src\bchgen.c
# End Source File
# Begin Source File

SOURCE=.\src\biveval.c
# End Source File
# Begin Source File

SOURCE=.\src\dmstor.c
# End Source File
# Begin Source File

SOURCE=.\src\emess.c
# End Source File
# Begin Source File

SOURCE=.\src\gen_cheb.c
# End Source File
# Begin Source File

SOURCE=.\src\hypot.c
# End Source File
# Begin Source File

SOURCE=.\src\mk_cheby.c
# End Source File
# Begin Source File

SOURCE=.\src\p_series.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_aea.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_aeqd.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_airy.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_aitoff.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_august.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_auth.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_bacon.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_bipc.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_boggs.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_bonne.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_cass.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_cc.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_cea.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_chamb.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_collg.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_crast.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_denoy.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_deriv.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_eck1.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_eck2.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_eck3.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_eck4.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_eck5.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_ell_set.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_ellps.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_eqc.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_eqdc.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_errno.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_factors.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_fahey.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_fouc_s.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_fwd.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_gall.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_gins8.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_gn_sinu.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_gnom.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_goode.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_hammer.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_hatano.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_imw_p.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_init.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_inv.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_labrd.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_laea.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_lagrng.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_larr.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_lask.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_lcc.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_list.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_loxim.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_lsat.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_malloc.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_mbt_fps.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_mbtfpp.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_mbtfpq.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_merc.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_mill.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_mlfn.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_mod_ster.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_moll.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_mpoly.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_msfn.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_nell.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_nell_h.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_nocol.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_nsper.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_nzmg.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_ob_tran.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_ocea.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_oea.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_omerc.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_open_lib.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_ortho.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_param.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_phi2.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_poly.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_pr_list.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_putp2.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_putp3.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_putp4p.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_putp5.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_putp6.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_qsfn.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_release.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_robin.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_rpoly.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_sconics.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_somerc.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_stere.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_strerrno.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_sts.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_tcc.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_tcea.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_tmerc.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_tpeqd.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_tsfn.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_units.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_urm5.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_urmfps.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_vandg.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_vandg2.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_vandg4.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_wag2.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_wag3.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_wag7.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_wink1.c
# End Source File
# Begin Source File

SOURCE=.\src\PJ_wink2.c
# End Source File
# Begin Source File

SOURCE=.\src\pj_zpoly1.c
# End Source File
# Begin Source File

SOURCE=.\src\proj.c
# End Source File
# Begin Source File

SOURCE=.\src\rtodms.c
# End Source File
# Begin Source File

SOURCE=.\src\strtod.c
# End Source File
# Begin Source File

SOURCE=.\src\vector1.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\src\emess.h
# End Source File
# Begin Source File

SOURCE=.\src\geodesic.h
# End Source File
# Begin Source File

SOURCE=.\src\nad_list.h
# End Source File
# Begin Source File

SOURCE=.\src\pj_list.h
# End Source File
# Begin Source File

SOURCE=.\src\projects.h
# End Source File
# End Group
# End Target
# End Project
