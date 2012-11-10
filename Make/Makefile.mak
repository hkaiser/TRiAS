# Makefile zur Erstellung von TRiAS3

#########################################################################
# Sprache setzen

!include <TRiASVerLang.mak>

TRIASDIR_R=g:\TRiAS\TRiAS\V_3_0_0\$(TRIAS_LANGUAGE)
TRIASDIR_D=g:\TRiAS\TRiASDeb\V_3_0_0\$(TRIAS_LANGUAGE)

all : trias3get trias3deb trias3rel

trias3get :
	set ssdir=\\SpaceShuttle\Sccs\TRiAS
	%T3VSS% GET $$\*.* -GF -GTM -R -W+ -O%T3LOGDIR%\ssget_trias.log
	set ssdir=\\SpaceShuttle\Sccs\TRiASDB
	%T3VSS% GET $$\*.* -GF -GTM -R -W+ -O%T3LOGDIR%\ssget_triasdb.log
#	set ssdir=\\SpaceShuttle\Sccs\TRiASVMD_Andy
#	%T3VSS% GET $$\*.* -GF -GTM -R -W+ -O%T3LOGDIR%\ssget_triasvmd.log
	

#=== Debug Build ========================================================
trias3deb :: $(TRIASDIR_D)\trias32d.exe
trias3deb :: $(TRIASDIR_D)\TRiASDBD.dll
trias3deb :: $(TRIASDIR_D)\containd.dll			#ok
#trias3deb :: $(TRIASLIB)\LibCtrlExtD.lib		#ok
trias3deb :: $(TRIASDIR_D)\TErrTrkD.dll			#ok
trias3deb :: $(TRIASDIR_D)\DefCtfsd.css		
trias3deb :: $(TRIASDIR_D)\GeodCtfd.css			#ok
trias3deb :: $(TRIASDIR_D)\GKCtfsd.css			#ok
# obsolete trias3deb :: $(TRIASDIR_D)\TDBHashd.dll			#ok
trias3deb :: $(TRIASDIR_D)\TRiASMDSD.dll		#ok
trias3deb :: $(TRIASDIR_D)\TRiASGDOD.dll

trias3deb :: $(TRIASDIR_D)\TRiASCsD.dll			#ok

trias3deb :: $(TRIASDIR_D)\Oleautod.ext
trias3deb :: $(TRIASDIR_D)\trias31d.dll
trias3deb :: $(TRIASDIR_D)\trias32d.dll
trias3deb :: $(TRIASDIR_D)\trias33d.dll

trias3deb :: $(TRIASDIR_D)\Tfrm32d.dll
trias3deb :: $(TRIASLIB)\tfrmld.lib
trias3deb :: $(TRIASDIR_D)\lol50d.dll
trias3deb :: $(TRIASDIR_D)\TDBGEOd.dll			#ok
trias3deb :: $(TRIASDIR_D)\TRiASUId.dll			#ok
trias3deb :: $(TRIASDIR_D)\TRiASICN.dll			#ok
trias3deb :: $(TRIASDIR_D)\Helperd.dll			#ok
trias3deb :: $(TRIASDIR_D)\Objmand.dll			#ok
trias3deb :: $(TRIASDIR_D)\visobjd.ext
trias3deb :: $(TRIASDIR_D)\arctriad.ext
trias3deb :: $(TRIASDIR_D)\Tortend.vmd
trias3deb :: $(TRIASDIR_D)\bilderd.ext
trias3deb :: $(TRIASDIR_D)\maschbld.ext
trias3deb :: $(TRIASDIR_D)\Identdbd.ext
trias3deb :: $(TRIASDIR_D)\fakemfcd.ext
trias3deb :: $(TRIASDIR_D)\geostatd.ext
trias3deb :: $(TRIASDIR_D)\odbcextd.ext
trias3deb :: $(TRIASDIR_D)\bscriptd.ext

trias3deb :: $(TRIASDIR_D)\ascimpd.ext
trias3deb :: $(TRIASDIR_D)\dxfimpd.ext
trias3deb :: $(TRIASDIR_D)\edbsimpd.ext

trias3deb :: $(TRIASDIR_D)\colorsd.ebn
trias3deb :: $(TRIASDIR_D)\daolayed.ebn

#=== Debug Build Wolfgang ================================================
trias3deb :: $(TRIASDIR_D)\abstandd.ext
trias3deb :: $(TRIASDIR_D)\bufferd.ext
trias3deb :: $(TRIASDIR_D)\geoeditd.ext
trias3deb :: $(TRIASDIR_D)\geometd.dll
trias3deb :: $(TRIASDIR_D)\georeind.ext
trias3deb :: $(TRIASDIR_D)\gitterd.ext
trias3deb :: $(TRIASDIR_D)\objoperd.ext
trias3deb :: $(TRIASDIR_D)\toporeld.ext

trias3deb :: $(TRIASLIB)\muscrl32.lib

#=== Debug Build zurückgestellt =========================================
#trias3deb :: $(TRIASLIB)\GMObjectsD.lib		#ok

#=== Release Build ========================================================
trias3rel :: $(TRIASDIR_R)\trias32.exe
trias3rel :: $(TRIASDIR_R)\TRiASDB.dll
trias3rel :: $(TRIASDIR_R)\containr.dll
#trias3rel :: $(TRIASLIB)\LibCtrlExt.lib
trias3rel :: $(TRIASDIR_R)\TErrTrk.dll
trias3rel :: $(TRIASDIR_R)\DefCtfs.css
trias3rel :: $(TRIASDIR_R)\GeodCtfs.css
trias3rel :: $(TRIASDIR_R)\GKCtfs.css
# obsolete trias3rel :: $(TRIASDIR_R)\TDBHash.dll
trias3rel :: $(TRIASDIR_R)\TRiASMDS.dll
trias3rel :: $(TRIASDIR_R)\TRiASGDO.dll

trias3rel :: $(TRIASDIR_R)\TRiASCs.dll

trias3rel :: $(TRIASDIR_R)\Oleauto.ext
trias3rel :: $(TRIASDIR_R)\trias321.dll
trias3rel :: $(TRIASDIR_R)\trias322.dll
trias3rel :: $(TRIASDIR_R)\trias323.dll

trias3rel :: $(TRIASDIR_R)\Tfrmwork.dll
trias3rel :: $(TRIASLIB)\tfrmlr.lib
trias3rel :: $(TRIASDIR_R)\lol.dll
trias3rel :: $(TRIASDIR_R)\TDBGEO.dll
trias3rel :: $(TRIASDIR_R)\TRiASUI.dll
trias3rel :: $(TRIASDIR_R)\TRiASICN.dll
trias3rel :: $(TRIASDIR_R)\Helper.dll
trias3rel :: $(TRIASDIR_R)\Objman.dll
trias3rel :: $(TRIASDIR_R)\visobj.ext
trias3rel :: $(TRIASDIR_R)\Torten.vmd
trias3rel :: $(TRIASDIR_R)\arctrias.ext
trias3rel :: $(TRIASDIR_R)\bilder.ext
trias3rel :: $(TRIASDIR_R)\maschblr.ext
trias3rel :: $(TRIASDIR_R)\Identsdb.ext
trias3rel :: $(TRIASDIR_R)\fakemfc.ext
trias3rel :: $(TRIASDIR_R)\geostat.ext
trias3rel :: $(TRIASDIR_R)\odbcext.ext
trias3rel :: $(TRIASDIR_R)\bscript.ext

trias3rel :: $(TRIASDIR_R)\ascimp.ext
trias3rel :: $(TRIASDIR_R)\dxfimp.ext
trias3rel :: $(TRIASDIR_R)\edbsimp.ext

trias3rel :: $(TRIASDIR_R)\colors.ebn
trias3rel :: $(TRIASDIR_R)\daolayer.ebn

#=== Release Build Wolfgang ===============================================
trias3rel :: $(TRIASDIR_R)\abstand.ext
trias3rel :: $(TRIASDIR_R)\buffer.ext
trias3rel :: $(TRIASDIR_R)\geoedit.ext
trias3rel :: $(TRIASDIR_R)\geometr.dll
trias3rel :: $(TRIASDIR_R)\georein.ext
trias3rel :: $(TRIASDIR_R)\gitter.ext
trias3rel :: $(TRIASDIR_R)\objoper.ext
trias3rel :: $(TRIASDIR_R)\toporel.ext
trias3rel :: $(TRIASDIR_R)\arctrias.ext

trias3rel :: $(TRIASLIB)\muscrl32.lib

#trias3rel :: $(TRIASLIB)\GMObjects.lib

#=== PreBuild =============================================================
#=== GMObjects
$(TRIASLIB)\GMObjectsD.lib : $(PREBUILDLIBS)\GMObjectsD.lib
	copy $(PREBUILDLIBS)\GMObjectsD.lib $(TRIASLIB)\GMObjectsD.lib	

$(TRIASLIB)\GMObjects.lib : $(PREBUILDLIBS)\GMObjects.lib
	copy $(PREBUILDLIBS)\GMObjects.lib $(TRIASLIB)\GMObjects.lib	

#=== Iprop
$(TRIASLIB)\iprop.lib : $(PREBUILDLIBS)\iprop.lib
	copy $(PREBUILDLIBS)\iprop.lib $(TRIASLIB)\iprop.lib	

#=== Iprop
$(TRIASLIB)\muscrl32.lib : $(PREBUILDLIBS)\muscrl32.lib
	copy $(PREBUILDLIBS)\muscrl32.lib $(TRIASLIB)\muscrl32.lib	

#=== TRiASTlb
$(TRIASLIB)\TriasTld.lib : $(PREBUILDLIBS)\TriasTld.lib
	copy $(PREBUILDLIBS)\TriasTld.lib $(TRIASLIB)\TriasTld.lib	
	copy $(PREBUILDLIBS)\vc40.pdb $(TRIASLIB)\vc40.pdb	

$(TRIASLIB)\TriasTlb.lib : $(PREBUILDLIBS)\TriasTlb.lib
	copy $(PREBUILDLIBS)\TriasTlb.lib $(TRIASLIB)\TriasTlb.lib	

#=== Ospace ===============================================================
$(TRIASDIR_D)\Ospace5d.dll $(TRIASLIB)\Ospace5d.lib: 
	@ECHO === $@
	CD C:\Toolkit\Ospace\Ospace
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\Ospace.dll $(TRIASLIB)\Ospace5r.lib : 
	@ECHO === $@
	CD C:\Toolkit\Ospace\Ospace
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== OspaceUss ============================================================
$(TRIASLIB)\StdStr5d.lib: 
	@ECHO === $@
	CD C:\Toolkit\Ospace\Ospace
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASLIB)\StdStr5r.lib : 
	@ECHO === $@
	CD C:\Toolkit\Ospace\Ospace
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== TRiASDB ==============================================================
$(TRIASDIR_D)\TRiASDBD.dll : \
		$(TRIASLIB)\trias31d.lib \
		$(TRIASDIR_D)\visobjd.ext \
		$(TRIASDIR_D)\TRiASUId.dll \
		$(TRIASDIR_D)\Helperd.dll \
		$(TRIASDIR_D)\objmand.dll \
		$(TRIASLIB)\iprop.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiASDB
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\TRiASDB.dll : \
		$(TRIASLIB)\trias321.lib \
		$(TRIASDIR_R)\visobj.ext \
		$(TRIASDIR_R)\TRiASUI.dll \
		$(TRIASDIR_R)\Helper.dll \
		$(TRIASDIR_R)\objman.dll \
		$(TRIASLIB)\iprop.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiASDB
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Ixtensn ==============================================================
$(TRIASLIB)\Ixtmad50.lib : \
		$(TRIASDIR_D)\DefCtfsD.css
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\Ixtensn
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASLIB)\Ixtmar50.lib : \
		$(TRIASDIR_R)\DefCtfs.css
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\Ixtensn
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASLIB)\ixtmfd50.lib : \
		$(TRIASDIR_D)\DefCtfsD.css
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\Ixtensn
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASLIB)\ixtmfr50.lib : \
		$(TRIASDIR_R)\DefCtfs.css
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\Ixtensn
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASLIB)\ixtnsd50.lib : \
		$(TRIASDIR_D)\DefCtfsD.css
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\Ixtensn
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASLIB)\ixtnsr50.lib : \
		$(TRIASDIR_R)\DefCtfs.css
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\Ixtensn
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASLIB)\ixtatd50.lib : \
		$(TRIASDIR_D)\DefCtfsD.css
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\Ixtensn
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASLIB)\ixtatr50.lib : \
		$(TRIASDIR_R)\DefCtfs.css
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\Ixtensn
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== LOL ==============================================================
$(TRIASDIR_D)\lol50d.dll $(TRIASLIB)\lol50d.lib : \
		$(TRIASLIB)\ospace5d.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\FrameWrk\lol\lib.c8\Lol32
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\lol.dll $(TRIASLIB)\lol.lib : \
		$(TRIASLIB)\ospace5r.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\FrameWrk\lol\lib.c8\Lol32
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Container ==============================================================
$(TRIASDIR_D)\containd.dll $(TRIASLIB)\cont50d.lib : 
	@ECHO === $@
	CD C:\TRiASDev.MVC\FrameWrk\Containr
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\containr.dll $(TRIASLIB)\containr.lib : 
	@ECHO === $@
	CD C:\TRiASDev.MVC\FrameWrk\Containr
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== LibCtrlExt ==============================================================
#$(TRIASLIB)\LibCtrlExtD.lib $(TRIASLIB)\LibCtrlExt.lib :
#	@ECHO === $@
#	CD C:\TRiASDev.MVC\LibCtrlExt
#	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== TErrTrk ==============================================================
$(TRIASDIR_D)\TErrTrkD.dll : 
	@ECHO === $@
	CD C:\TRiASDev.MVC\TErrTrk
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\TErrTrk.dll : 
	@ECHO === $@
	CD C:\TRiASDev.MVC\TErrTrk
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== GeodCtfs ==============================================================
$(TRIASDIR_D)\GeodCtfd.css : \
		$(TRIASDIR_D)\DefCtfsd.css \
		$(TRIASLIB)\ospace5d.lib 
	@ECHO === $@
	CD C:\TRiASDev.MVC\Coords\GeodCTF
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\GeodCtfs.css : \
		$(TRIASDIR_R)\DefCtfs.css \
		$(TRIASLIB)\ospace5r.lib 
	@ECHO === $@
	CD C:\TRiASDev.MVC\Coords\GeodCTF
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== GKCtfs ==============================================================
$(TRIASDIR_D)\GKCtfsd.css : \
		$(TRIASDIR_D)\DefCtfsd.css \
		$(TRIASLIB)\ospace5d.lib 
	@ECHO === $@
	CD C:\TRiASDev.MVC\Coords\GKCTF
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\GKCtfs.css : \
		$(TRIASDIR_R)\DefCtfs.css \
		$(TRIASLIB)\ospace5r.lib 
	@ECHO === $@
	CD C:\TRiASDev.MVC\Coords\GKCTF
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Common View ==============================================================
$(TRIASDIR_D)\Tfrm32d.dll $(TRIASLIB)\tfrm32d.lib : \
		$(TRIASLIB)\ospace5d.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\FrameWrk\CV
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASLIB)\tfrmld.lib :
	@ECHO === $@
	CD C:\TRiASDev.MVC\FrameWrk\CV
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\Tfrmwork.dll $(TRIASLIB)\tfrmwork.lib : \
		$(TRIASLIB)\ospace5r.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\FrameWrk\CV
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASLIB)\tfrmlr.lib :
	@ECHO === $@
	CD C:\TRiASDev.MVC\FrameWrk\CV
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== TDBGEO ==============================================================
$(TRIASDIR_D)\TDBGEOd.dll : \
		$(TRIASDIR_D)\TRiASCSD.dll \
		$(TRIASDIR_D)\TErrTrkd.dll \
		$(TRIASLIB)\GMObjectsd.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\TDBGeo
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\TDBGEO.dll : \
		$(TRIASDIR_R)\TRiASCS.dll \
		$(TRIASDIR_R)\TErrTrk.dll \
		$(TRIASLIB)\GMObjects.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\TDBGeo
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== GMObjects ==============================================================
#$(TRIASLIB)\GMObjectsD.lib $(TRIASLIB)\GMObjects.lib :
#	@ECHO === $@
#	CD C:\TRiASDev.MVC\GMObjects
#	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Maschbld ==============================================================
$(TRIASDIR_D)\Maschbld.ext : \
		$(TRIASLIB)\ixtmad50.lib \
		$(TRIASLIB)\cont50d.lib \
		$(TRIASLIB)\triastld.lib \
		$(TRIASDIR_D)\Helperd.dll \
		$(TRIASLIB)\ospace5d.lib 
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\LinVer
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\Maschblr.ext : \
		$(TRIASLIB)\ixtmar50.lib \
		$(TRIASLIB)\containr.lib \
		$(TRIASLIB)\triastlb.lib \
		$(TRIASDIR_R)\Helper.dll \
		$(TRIASLIB)\ospace5r.lib 
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\LinVer
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Abstand ==============================================================
$(TRIASDIR_D)\abstandd.ext : \
		$(TRIASLIB)\geometd.lib \
		$(TRIASDIR_D)\TDBGeoD.dll \
		$(TRIASLIB)\ixtatd50.lib \
		$(TRIASLIB)\ospace5d.lib \
		$(TRIASLIB)\tfrm32d.lib \
		$(TRIASLIB)\cont50d.lib
	@ECHO === $@
	CD C:\VCPP\Abstand
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\abstand.ext : \
		$(TRIASLIB)\geometr.lib \
		$(TRIASDIR_R)\TDBGeo.dll \
		$(TRIASLIB)\ixtatd50.lib \
		$(TRIASLIB)\ospace5r.lib \
		$(TRIASLIB)\tfrmwork.lib \
		$(TRIASLIB)\containr.lib
	@ECHO === $@
	CD C:\VCPP\Abstand
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Buffer ==============================================================
$(TRIASDIR_D)\bufferd.ext : \
		$(TRIASLIB)\geometd.lib \
		$(TRIASDIR_D)\TDBGeoD.dll \
		$(TRIASLIB)\ixtatd50.lib \
		$(TRIASLIB)\ospace5d.lib \
		$(TRIASLIB)\tfrm32d.lib \
		$(TRIASLIB)\cont50d.lib
	@ECHO === $@
	CD C:\VCPP\Buffer
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\buffer.ext : \
		$(TRIASLIB)\geometr.lib \
		$(TRIASDIR_R)\TDBGeo.dll \
		$(TRIASLIB)\ixtatd50.lib \
		$(TRIASLIB)\ospace5r.lib \
		$(TRIASLIB)\tfrmwork.lib \
		$(TRIASLIB)\containr.lib
	@ECHO === $@
	CD C:\VCPP\Buffer
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== GeoEdit ==============================================================
$(TRIASDIR_D)\geoeditd.ext : \
		$(TRIASLIB)\geometd.lib \
		$(TRIASDIR_D)\TDBGeoD.dll \
		$(TRIASLIB)\ixtatd50.lib \
		$(TRIASLIB)\ospace5d.lib \
		$(TRIASLIB)\tfrm32d.lib \
		$(TRIASLIB)\cont50d.lib
	@ECHO === $@
	CD C:\VCPP\GeoEdit
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\geoedit.ext : \
		$(TRIASLIB)\geometr.lib \
		$(TRIASDIR_R)\TDBGeo.dll \
		$(TRIASLIB)\ixtatd50.lib \
		$(TRIASLIB)\ospace5r.lib \
		$(TRIASLIB)\tfrmwork.lib \
		$(TRIASLIB)\containr.lib
	@ECHO === $@
	CD C:\VCPP\GeoEdit
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== GeoMetr ==============================================================
$(TRIASDIR_D)\geometd.dll $(TRIASLIB)\geometd.lib : \
		$(TRIASLIB)\tfrm32d.lib \
		$(TRIASLIB)\ospace5d.lib \
		$(TRIASLIB)\cont50d.lib \
		$(TRIASDIR_D)\trias33d.dll
	@ECHO === $@
	CD C:\VCPP\GeoMetr
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\geometr.dll $(TRIASLIB)\geometr.lib : \
		$(TRIASLIB)\tfrmwork.lib \
		$(TRIASLIB)\ospace5r.lib \
		$(TRIASLIB)\containr.lib \
		$(TRIASDIR_R)\trias323.dll
	@ECHO === $@
	CD C:\VCPP\GeoMetr
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Georein ==============================================================
$(TRIASDIR_D)\georeind.ext : \
		$(TRIASLIB)\geometd.lib \
		$(TRIASDIR_D)\TDBGeoD.dll \
		$(TRIASLIB)\ixtatd50.lib \
		$(TRIASLIB)\ospace5d.lib \
		$(TRIASLIB)\tfrm32d.lib \
		$(TRIASLIB)\cont50d.lib
	@ECHO === $@
	CD C:\VCPP\Georein
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\georein.ext : \
		$(TRIASLIB)\geometr.lib \
		$(TRIASDIR_R)\TDBGeo.dll \
		$(TRIASLIB)\ixtatd50.lib \
		$(TRIASLIB)\ospace5r.lib \
		$(TRIASLIB)\tfrmwork.lib \
		$(TRIASLIB)\containr.lib
	@ECHO === $@
	CD C:\VCPP\Georein
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Gitter ==============================================================
$(TRIASDIR_D)\gitterd.ext : \
		$(TRIASLIB)\geometd.lib \
		$(TRIASDIR_D)\TDBGeoD.dll \
		$(TRIASLIB)\ixtatd50.lib \
		$(TRIASLIB)\ospace5d.lib \
		$(TRIASLIB)\tfrm32d.lib \
		$(TRIASLIB)\cont50d.lib
	@ECHO === $@
	CD C:\VCPP\Gitter
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\gitter.ext : \
		$(TRIASLIB)\geometr.lib \
		$(TRIASDIR_R)\TDBGeo.dll \
		$(TRIASLIB)\ixtatd50.lib \
		$(TRIASLIB)\ospace5r.lib \
		$(TRIASLIB)\tfrmwork.lib \
		$(TRIASLIB)\containr.lib
	@ECHO === $@
	CD C:\VCPP\Gitter
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Objoper ==============================================================
$(TRIASDIR_D)\objoperd.ext : \
		$(TRIASDIR_D)\Helperd.dll \
		$(TRIASDIR_D)\Maschbld.ext \
		$(TRIASLIB)\geometd.lib \
		$(TRIASDIR_D)\TDBGeoD.dll \
		$(TRIASLIB)\ixtatd50.lib \
		$(TRIASLIB)\ospace5d.lib \
		$(TRIASLIB)\tfrm32d.lib \
		$(TRIASLIB)\cont50d.lib
	@ECHO === $@
	CD C:\VCPP\Objoper
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\objoper.ext : \
		$(TRIASDIR_R)\Helper.dll \
		$(TRIASDIR_R)\Maschblr.ext \
		$(TRIASLIB)\geometr.lib \
		$(TRIASDIR_R)\TDBGeo.dll \
		$(TRIASLIB)\ixtatd50.lib \
		$(TRIASLIB)\ospace5r.lib \
		$(TRIASLIB)\tfrmwork.lib \
		$(TRIASLIB)\containr.lib
	@ECHO === $@
	CD C:\VCPP\Objoper
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Toporel ==============================================================
$(TRIASDIR_D)\toporeld.ext : \
		$(TRIASLIB)\geometd.lib \
		$(TRIASDIR_D)\TDBGeoD.dll \
		$(TRIASLIB)\ixtatd50.lib \
		$(TRIASLIB)\ospace5d.lib \
		$(TRIASLIB)\tfrm32d.lib \
		$(TRIASLIB)\cont50d.lib
	@ECHO === $@
	CD C:\VCPP\Toporel
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\toporel.ext : \
		$(TRIASLIB)\geometr.lib \
		$(TRIASDIR_R)\TDBGeo.dll \
		$(TRIASLIB)\ixtatd50.lib \
		$(TRIASLIB)\ospace5r.lib \
		$(TRIASLIB)\tfrmwork.lib \
		$(TRIASLIB)\containr.lib
	@ECHO === $@
	CD C:\VCPP\Toporel
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Identsdb =============================================================
$(TRIASDIR_D)\Identdbd.ext : \
		$(TRIASLIB)\ixtnsd50.lib \
		$(TRIASLIB)\ospace5d.lib \
		$(TRIASLIB)\tfrm32d.lib \
		$(TRIASLIB)\cont50d.lib \
		$(TRIASDIR_D)\lol50d.dll
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\Identsdb
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\Identsdb.ext : \
		$(TRIASLIB)\ixtnsr50.lib \
		$(TRIASLIB)\ospace5r.lib \
		$(TRIASLIB)\tfrmwork.lib \
		$(TRIASLIB)\containr.lib \
		$(TRIASDIR_R)\lol.dll
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\Identsdb
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== FakeMFC ==============================================================
$(TRIASDIR_D)\fakemfcd.ext : \
		$(TRIASDIR_D)\triasdbd.dll \
		$(TRIASLIB)\triastld.lib \
		$(TRIASLIB)\ospace5d.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\FakeMFC
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\fakemfc.ext : \
		$(TRIASDIR_R)\triasdb.dll \
		$(TRIASLIB)\triastlb.lib \
		$(TRIASLIB)\ospace5r.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\FakeMFC
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Statistik ==============================================================
$(TRIASDIR_D)\geostatd.ext : \
		$(TRIASLIB)\ixtnsd50.lib \
		$(TRIASLIB)\cont50d.lib \
		$(TRIASLIB)\tfrm32d.lib \
		$(TRIASLIB)\ospace5d.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\GeoStat
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\geostat.ext : \
		$(TRIASLIB)\ixtnsr50.lib \
		$(TRIASLIB)\containr.lib \
		$(TRIASLIB)\tfrmwork.lib \
		$(TRIASLIB)\ospace5r.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\GeoStat
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== ODBC-Anbindung ==============================================================
$(TRIASDIR_D)\odbcextd.ext : \
		$(TRIASLIB)\ixtmad50.lib \
		$(TRIASLIB)\cont50d.lib \
		$(TRIASLIB)\ospace5d.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\ODBCext
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\odbcext.ext : \
		$(TRIASLIB)\ixtmar50.lib \
		$(TRIASLIB)\containr.lib \
		$(TRIASLIB)\ospace5r.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\ODBCext
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@


#=== Coords ==============================================================
$(TRIASDIR_D)\DefCtfsd.css : \
		$(TRIASDIR_D)\TDBGeoD.dll \
		$(TRIASLIB)\ospace5d.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Coords\Default
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\DefCtfs.css : \
		$(TRIASDIR_R)\TDBGeo.dll \
		$(TRIASLIB)\ospace5r.lib 
	@ECHO === $@
	CD C:\TRiASDev.MVC\Coords\Default
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@


#=== TRiASUI ==============================================================
$(TRIASDIR_D)\TRiASUId.dll $(TRIASDIR_R)\TRiASUI.dll : 
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiASUI
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== TRiASICN ==============================================================
$(TRIASDIR_D)\TRiASICN.dll $(TRIASDIR_R)\TRiASICN.dll :
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiASICN
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Helper ==============================================================
$(TRIASDIR_D)\Helperd.dll $(TRIASDIR_R)\Helper.dll :
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\oleauto\helper
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Oleauto ==============================================================
$(TRIASDIR_D)\Oleautod.ext : \
		$(TRIASDIR_D)\trias33d.dll \
		$(TRIASDIR_D)\bscriptd.ext \
		$(TRIASDIR_D)\visobjd.ext \
		$(TRIASDIR_D)\Colorsd.ebn
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\oleauto
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\Oleauto.ext : \
		$(TRIASDIR_R)\trias323.dll \
		$(TRIASDIR_R)\bscript.ext \
		$(TRIASDIR_R)\visobj.ext \
		$(TRIASDIR_R)\Colors.ebn
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\oleauto
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Objman ==============================================================
$(TRIASDIR_D)\Objmand.dll $(TRIASDIR_R)\Objman.dll :
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\ObjMan
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== VisObj ==============================================================
$(TRIASDIR_D)\visobjd.ext : \
		$(TRIASDIR_D)\colorsd.ebn \
		$(TRIASLIB)\tfrm32d.lib \
		$(TRIASLIB)\ixtatd50.lib \
		$(TRIASLIB)\cont50d.lib \
		$(TRIASLIB)\ospace5d.lib \
		$(TRIASLIB)\TRiASTld.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\VisObj
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\visobj.ext : \
		$(TRIASDIR_R)\colors.ebn \
		$(TRIASLIB)\tfrmwork.lib \
		$(TRIASLIB)\containr.lib \
		$(TRIASLIB)\ixtatr50.lib \
		$(TRIASLIB)\ospace5r.lib \
		$(TRIASLIB)\TRiASTlb.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\VisObj
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Torten ==============================================================
$(TRIASDIR_D)\Torten.vmd : \
		$(TRIASLIB)\tfrm32d.lib \
		$(TRIASLIB)\cont50d.lib \
		$(TRIASLIB)\ospace5d.lib \
		$(TRIASLIB)\TRiASTld.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\VisObj\Torten
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\Torten.vmd : \
		$(TRIASLIB)\tfrmwork.lib \
		$(TRIASLIB)\containr.lib \
		$(TRIASLIB)\ospace5r.lib \
		$(TRIASLIB)\TRiASTlb.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\VisObj\Torten
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== ArcTrias ==============================================================
$(TRIASDIR_D)\arctriad.ext : \
		$(TRIASLIB)\tfrm32d.lib \
		$(TRIASLIB)\ixtnsd50.lib \
		$(TRIASLIB)\cont50d.lib \
		$(TRIASLIB)\ospace5d.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\ArcTrias
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\arctrias.ext : \
		$(TRIASLIB)\tfrmwork.lib \
		$(TRIASLIB)\containr.lib \
		$(TRIASLIB)\ixtnsr50.lib \
		$(TRIASLIB)\ospace5r.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\ArcTrias
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== ASCimp ==============================================================
$(TRIASDIR_D)\ascimpd.ext : \
		$(TRIASLIB)\ixtatd50.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\ASCimp
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\ascimp.ext : \
		$(TRIASLIB)\ixtatr50.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\ASCimp
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== EDBSimp ==============================================================
$(TRIASDIR_D)\edbsimpd.ext : \
		$(TRIASLIB)\ixtmfd50.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\EDBSimp
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\edbsimp.ext : \
		$(TRIASLIB)\ixtmfr50.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\EDBSimp
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== DXFimp ==============================================================
$(TRIASDIR_D)\dxfimpd.ext : \
		$(TRIASLIB)\ixtnsd50.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\DXFimp
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\dxfimp.ext : \
		$(TRIASLIB)\ixtnsr50.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\DXFimp
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== TRiASCs ==============================================================
$(TRIASDIR_D)\TRiASCsD.dll :: \
		$(TRIASDIR_D)\TErrTrkD.dll \
		$(TRIASLIB)\GMObjectsd.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiASCs
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\TRiASCs.dll :: \
		$(TRIASDIR_R)\TErrTrk.dll \
		$(TRIASLIB)\GMObjects.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiASCs
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== TDBHash ==============================================================
#$(TRIASDIR_D)\TDBHashd.dll :
#	@ECHO === $@
#	CD C:\TRiASDev.MVC\TDBHash
#	nmake $(T3MAKEOPTIONS) /F makefile.mak $@
#
#$(TRIASDIR_R)\TDBHash.dll :
#	@ECHO === $@
#	CD C:\TRiASDev.MVC\TDBHash
#	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== TRiASMDS ==============================================================
$(TRIASDIR_D)\TRiASMDSD.dll :
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiASMDS
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\TRiASMDS.dll :
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiASMDS
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== TRiASGDO ==============================================================
$(TRIASDIR_D)\TRiASGDOD.dll : \
		$(TRIASLIB)\GMObjectsD.lib \
		$(TRIASDIR_D)\TRiASMDSD.dll \
		$(TRIASDIR_D)\TRiASDBD.dll \
		$(TRIASDIR_D)\TDBGEOD.dll \
		$(TRIASDIR_D)\TErrTrkD.dll \
		$(TRIASDIR_D)\TRiASMDSD.dll 
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiASGDO
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\TRiASGDO.dll : \
		$(TRIASLIB)\GMObjects.lib \
		$(TRIASDIR_R)\TRiASMDS.dll \
		$(TRIASDIR_R)\TRiASDB.dll \
		$(TRIASDIR_R)\TDBGEO.dll \
		$(TRIASDIR_R)\TErrTrk.dll \
		$(TRIASDIR_R)\TRiASCs.dll
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiASGDO
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Bilder ==============================================================
$(TRIASDIR_D)\bilderd.ext : \
		$(TRIASLIB)\ixtnsd50.lib \
		$(TRIASLIB)\ospace5d.lib \
		$(TRIASLIB)\tfrm32d.lib \
		$(TRIASLIB)\cont50d.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\Bilder
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\bilder.ext : \
		$(TRIASLIB)\ixtnsr50.lib \
		$(TRIASLIB)\tfrmwork.lib \
		$(TRIASLIB)\containr.lib \
		$(TRIASLIB)\ospace5r.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\Bilder
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== BScript ==============================================================
$(TRIASDIR_D)\bscriptd.ext : \
		$(TRIASDIR_D)\objmand.dll \
		$(TRIASDIR_D)\daolayed.ebn \
		$(TRIASLIB)\ixtmad50.lib \
		$(TRIASLIB)\ospace5d.lib \
		$(TRIASLIB)\cont50d.lib \
		$(TRIASLIB)\StdStr5d.lib 
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\BS
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\bscript.ext : \
		$(TRIASDIR_R)\objman.dll \
		$(TRIASDIR_R)\daolayer.ebn \
		$(TRIASLIB)\ixtmar50.lib \
		$(TRIASLIB)\containr.lib \
		$(TRIASLIB)\StdStr5r.lib \
		$(TRIASLIB)\ospace5r.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\BS
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Colors ==============================================================
$(TRIASDIR_D)\Colorsd.ebn : \
		$(TRIASLIB)\ospace5d.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\Colors
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\Colors.ebn : \
		$(TRIASLIB)\ospace5r.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\Colors
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== DaoLayer =============================================================
$(TRIASDIR_D)\Daolayed.ebn : 
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\Daolayer
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

$(TRIASDIR_R)\Daolayer.ebn : 
	@ECHO === $@
	CD C:\TRiASDev.MVC\Xtension\Daolayer
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== TRiAS01 ==============================================================
$(TRIASDIR_D)\trias31d.dll $(TRIASLIB)\trias31d.lib : \
		$(TRIASLIB)\cont50d.lib \
		$(TRIASLIB)\TFrm32d.lib \
		$(TRIASDIR_D)\TDBGeoD.dll \
		$(TRIASDIR_D)\VisObjd.ext
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiAS01
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@
	
$(TRIASDIR_R)\trias321.dll $(TRIASLIB)\trias321.lib : \
		$(TRIASLIB)\containr.lib \
		$(TRIASLIB)\TFrmwork.lib \
		$(TRIASDIR_R)\TDBGeo.dll \
		$(TRIASDIR_R)\VisObj.ext
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiAS01
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== TRiAS02 ==============================================================
$(TRIASDIR_D)\trias32d.dll $(TRIASLIB)\trias32d.lib : \
		$(TRIASDIR_D)\triasdbd.dll \
		$(TRIASLIB)\trias31d.lib \
		$(TRIASLIB)\tfrm32d.lib \
		$(TRIASLIB)\cont50d.lib \
		$(TRIASLIB)\ospace5d.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiAS02
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@
	
$(TRIASDIR_R)\trias322.dll $(TRIASLIB)\trias322.lib : \
		$(TRIASDIR_R)\triasdb.dll \
		$(TRIASLIB)\containr.lib \
		$(TRIASLIB)\TFrmwork.lib \
		$(TRIASLIB)\trias321.lib \
		$(TRIASLIB)\ospace5r.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiAS02
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== TRiAS03 ==============================================================
$(TRIASDIR_D)\trias33d.dll $(TRIASLIB)\trias33d.lib : \
		$(TRIASDIR_D)\triasdbd.dll \
		$(TRIASLIB)\cont50d.lib \
		$(TRIASLIB)\TFrm32d.lib \
		$(TRIASLIB)\trias32d.lib \
		$(TRIASLIB)\ospace5d.lib \
		$(TRIASLIB)\muscrl32.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiAS03
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@
	
$(TRIASDIR_R)\trias323.dll $(TRIASLIB)\trias323.lib : \
		$(TRIASDIR_R)\triasdb.dll \
		$(TRIASLIB)\containr.lib \
		$(TRIASLIB)\tfrmwork.lib \
		$(TRIASLIB)\ospace5r.lib \
		$(TRIASLIB)\trias322.lib \
		$(TRIASLIB)\muscrl32.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiAS03
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== TRiAS ==============================================================
$(TRIASDIR_D)\trias32d.exe : \
		$(TRIASDIR_D)\triasdbd.dll \
		$(TRIASDIR_D)\fakemfcd.ext \
		$(TRIASLIB)\tfrmld.lib \
		$(TRIASDIR_D)\lol50d.dll \
		$(TRIASLIB)\trias33d.lib \
		$(TRIASLIB)\trias32d.lib \
		$(TRIASLIB)\trias31d.lib \
		$(TRIASLIB)\tfrm32d.lib \
		$(TRIASLIB)\cont50d.lib \
		$(TRIASLIB)\ospace5d.lib 
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiAS
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@
	
$(TRIASDIR_R)\TRiAS32.exe : \
		$(TRIASDIR_R)\triasdb.dll \
		$(TRIASDIR_R)\fakemfc.ext \
		$(TRIASLIB)\tfrmlr.lib \
		$(TRIASLIB)\lol.lib \
		$(TRIASLIB)\trias323.lib \
		$(TRIASLIB)\trias322.lib \
		$(TRIASLIB)\trias321.lib \
		$(TRIASLIB)\tfrmwork.lib \
		$(TRIASLIB)\containr.lib \
		$(TRIASLIB)\ospace5r.lib
	@ECHO === $@
	CD C:\TRiASDev.MVC\TRiAS
	nmake $(T3MAKEOPTIONS) /F makefile.mak $@

#=== Sonstige Bibliotheken ==================================================

