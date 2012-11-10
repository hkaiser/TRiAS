#############################################################################
# Makefile zur Erstellung von TRiAS5
#	1999.07.14	=> Alle Module in's Makefile eingebaut; TRiAS kann jetzt
#				   komplett mit diesem gebaut werden.
#	1999.07.07	=> Umbau dergestalt, daß auch diejenigen Module die ein
#				   'Makefile.mak' in ihrem Projektverzeichnis haben,
#				   mit gebastelt werden können. Notwendig ist jedoch
#				   leider, daß die Targets explizit gelöscht werden
#				   (wegen Fehler in der Konstruktion von 'Makefile.mak').
#				=> für Module die sich an die folgenden Konventionen halten,
#				   ist 'Makefile.mak' *nicht* mehr nötig:
#				   (1) Name des Projekworkspace entspricht Modulname:
#							Export.ext => Export => Export.dsp
#				   (2) Debug-Konfiguration wie folgt:
#							"$(PROJECTNAME) - Win32 Debug"
#				   (3) Release-Konfiguration wie folgt:
#							"$(PROJECTNAME) - Win32 Release"
#	1999.06.17	=> Feinarbeit; über das steuernde CMD-File können jetzt
#				einzelne Targets angesprungen werden;
#				Beispiel: MakeTRiAS -D _TRiASGDO erstellt *nur* GDO als Debug
#				=> neben nur Debug / Release ist jetzt auch ein zielgerichtetes
#					Clean / Rebuild möglich; nötige Optionen siehe MakeTRiAS.cmd
#					die Optionen funktionieren mit allen Einzel / Sammeltargets
#				=> T3BUILDOPTIONS gibt es nicht mehr; ist jetzt in T3MAKEOPTIONS
#					(war Schwachsinn; zwei Optionen für denselben Zweck)
#	1999.05.04	=> Umgebungsvariablen aus MakeTRiAS.cmd in's Makefile
#				=> Konfiguration, Defaulteinstellung, Pfadeinstellung usw.
#				=> alle Buildaktivtäten im Makefile (als Targets)
#				=> modulspezifische Makefiles können dieses makefile
#				   zum eigentlichen Build nutzen
#				Beispiel (LibVMD):	=> CD C:\TRiASDev.mvc\Xtension\Visobj\Libvmd
#									=> nmake $(T3MAKEOPTIONS) /F makefile.mak FINALTARGET
#				Modulmakefile:		=> T3PROJECT=LibVMD
#									=> !INCLUDE $(MASTERMAKE)
#							=> $(MASTERMAKE)::FINALTARGET wird abgearbeitet
#	1999.??.??	Initial Version
#############################################################################

#############################################################################
# Umgebungsvariablen initialisieren

GEOMEDIA=D:\TRiASDev.MVC\Include\GMObjects\tlb
INCLUDE = $(INCLUDE);D:\TRiASDev.MVC\Include
PREBUILDLIBS=D:\TRiASDev.MVC\PreBuildLibs

MASTERMAKE=D:\Make\MakeNew\Makefile.mak		# dieses Makefile hier

T3SRCBASE=D:\TRiASDev.mvc

#############################################################################
# Sprache setzen

!include <TRiASVerLang.mak>

TRIASDIR_R=D:\TRiAS\TRiAS\V_4_0_0\$(TRIAS_LANGUAGE)
TRIASDIR_D=D:\TRiAS\TRiASDeb\V_4_0_0\$(TRIAS_LANGUAGE)

#############################################################################
# Allgemeine Optionen

T3MAKEOPTIONS=/A /NOLOGO /NORECURSE /n

#############################################################################
# Pfade, wo die Tools zu finden sind

T3MSDEV="D:\Program Files\Microsoft Visual Studio\Common\MSDev98\Bin\msdev.exe"
T3VSS="D:\Program Files\Microsoft Visual Studio\Common\VSS\win32\SS.EXE"

XCOPY=@xcopy /F

#.SILENT:

#############################################################################
# Defaultkonfiguration ist Debug

!if !defined(CONF) || "$(CONF)" == ""
CONF=_DEBUG
!message ================== No Configuration specified; using <<$(CONF)>>
!endif

#############################################################################
# Konfigurationsabhängige Definitionen

!if "$(CONF)" == "NDEBUG" || "$(CONF)" == "NDEBUGCLEAN" || "$(CONF)" == "NDEBUGREBUILD"
CONFIGURATION=Release
!else if "$(CONF)" == "_DEBUG" || "$(CONF)" == "_DEBUGCLEAN" || "$(CONF)" == "_DEBUGREBUILD"
CONFIGURATION=Debug
!else
!error ================== Invalid Configuration <<$(CONF)>> specified
!endif

#############################################################################
# soll etwa ein CLEAN / REBUILD ausgeführt werden?

!if "$(CONF)" == "NDEBUGCLEAN" || "$(CONF)" == "_DEBUGCLEAN"
T3ADD=/CLEAN
!else if "$(CONF)" == "NDEBUGREBUILD" || "$(CONF)" == "_DEBUGREBUILD"
T3ADD=/REBUILD
!endif

#############################################################################
# ggf. Standardkonfiguration für MSDEV bauen

!if defined(T3PROJECT) && !defined(T3CONFIG)
T3CONFIG=$(T3PROJECT) - Win32 $(CONFIGURATION)
!endif

#############################################################################
# jetzt die endgültigen Variablen

T3LOGDIR=D:\MAKE\$(CONFIGURATION)\LOG
T3MAKEOPTIONS=$(T3MAKEOPTIONS) $(T3ADD)
T3GETLOGDIR=$(T3LOGDIR)\GET
T3HTMLOG=$(T3LOGDIR)\__$(CONFIGURATION).html
T3MAINLOG=$(T3LOGDIR)\__$(CONFIGURATION).log

#############################################################################
#!message $(CONF) => $(CONFIGURATION) => $(T3ADD)
#!message $(T3PROJECT)
#!message $(T3CONFIG)
#############################################################################

#############################################################################
# dieses Makro wird in den Einzeltargets aufgelöst; spart uns dort 'ne
# Menge Schreibarbeit

MAKECMD=nmake /nologo /F $(MASTERMAKE)

#############################################################################
# Wenn Verzeichnis angegeben ist in dem formake gemacht werden soll, 
# dann geht's hier rein (ist bei allen Modulen von Wolfgang so).

!if defined(FORMAKEDIR) && "" != "$(FORMAKEDIR)"
__FORMAKE:
	@CD $(FORMAKEDIR)
	@-echo {{FORMAKE $(FORMAKEDIR) >> $(T3MAINLOG)
	@-nmake /nologo /F Makefile new formake 2>> $(T3MAINLOG)
	@-echo }}FORMAKE >> $(T3MAINLOG)
!endif

#############################################################################
# Hier geht's rein für diejenigen Targets die mit 'Makefile.mak' in ihrem
# Projektverzeichnis arbeiten. Das Target muß jedoch erst gelöscht werden
# um einen Build zu erzwingen.

!if defined(OLDMAKEDIR) && "" != "$(OLDMAKEDIR)"
__MAKEINOLDDIR: SETUPENV
	@echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	@echo !!! Please correct Workspace for: $(OLDMAKEDIR)
	@echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	@-del $(FINALTARGET)
	@-CD $(OLDMAKEDIR)
	@-echo {{TARGET $(FINALTARGET) >> $(T3MAINLOG)
	@-nmake /nologo T3BUILDOPTIONS="$(T3MAKEOPTIONS)" /F Makefile.mak $(FINALTARGET) 2>> $(T3MAINLOG)
	@-echo }}TARGET >> $(T3MAINLOG)
#	@type $(OLDMAKEDIR)\*.plg >> $(T3HTMLOG) 2> NUL
!endif

#############################################################################
# Wenn Verzeichnis angegeben ist in dem gearbeitet werden soll, dann:

!if defined(DOMAKEDIR) && "" != "$(DOMAKEDIR)"
__MAKEINDIR:
	@CD $(DOMAKEDIR)
	@-echo {{TARGET $(T3PROJECT) >> $(T3MAINLOG)
	@-nmake /nologo T3PROJECT=$(T3PROJECT) /F $(MASTERMAKE) FINALTARGET  2>> $(T3MAINLOG)
	@-echo }}TARGET >> $(T3MAINLOG)
#	@type $(DOMAKEDIR)\*.plg >> $(T3LOGDIR)\__$(CONFIGURATION).html 2> NUL
!endif

#############################################################################
# wenn kein Target gegeben, dann dieses hier, das ist der Build des gesamten
# TRiAS
# das eigentliche Target wird weiter unten definiert

default:
	@-del $(T3HTMLOG)
	@-del $(T3MAINLOG)
	@-nmake -nologo -I -f Makefile.mak CONF=$(CONF) TRiAS

#############################################################################
# Ein virtuelles Target welches zum Erzwingen des Builds für diejenigen
# Module benötigt wird, die mit 'Makefile.mak' in ihrem Verzeichnis
# arbeiten.

_ForceBuild:

#############################################################################
# Environment setzen (damit der externe Aufruf des alten externen
# Makefiles korrekt funktioniert)

SETUPENV:
	@SET T3MSDEV=$(T3MSDEV)
	@SET T3VSS=$(T3VSS)
	@SET T3LOGDIR=$(T3LOGDIR)
	@SET T3MAKEOPTIONS=$(T3MAKEOPTIONS)
!if "$(TRiAS_VER)" != ""
	@SET CL=-D_TRiAS_VER=$(TRiAS_VER)
!endif

############################################################################
# Logfiles l”schen

cleanlog:
	@echo === Removing Logfiles
	@DEL $(T3LOGDIR)\*.log > NUL 2> NUL

#############################################################################
# explizites Löschen der .res - Dateien

cleanres:
	@del /S $(T3SRCBASE)\*.res

#############################################################################
# Makefiles kopieren
# ACHTUNG! Makefiles immer erst **nach** dem auschecken (trias3get) kopieren!!

makefiles:
	@echo === Copying Makefiles
	@xcopy /F /R /D /S D:\Make\Makefiles\Makefile.ma* D:\ > NUL

#############################################################################
# SourceSafe Auschecken

trias3get:	t3getBase t3getTDB t3getAndy makefiles

t3getBase:
	@if not exist $(T3GETLOGDIR)\NUL mkdir $(T3GETLOGDIR)
	@set ssdir=\\SpaceShuttle\Sccs\TRiAS
	@echo === Checking out from %%ssdir%%
	@$(T3VSS) GET $$\*.* -GF -GTM -R -W+ -O$(T3GETLOGDIR)\ssget_trias.log

t3getTDB:
	@if not exist $(T3GETLOGDIR)\NUL mkdir $(T3GETLOGDIR)
	@set ssdir=\\SpaceShuttle\Sccs\TRiASDB
	@echo === Checking out from %%ssdir%%
	@$(T3VSS) GET $$\*.* -GF -GTM -R -W+ -O$(T3GETLOGDIR)\ssget_triasdb.log

t3getAndy:
	@if not exist $(T3GETLOGDIR)\NUL mkdir $(T3GETLOGDIR)
	@set ssdir=\\SpaceShuttle\Sccs\TRiASVMD_Andy
	@echo === Checking out from %%ssdir%%
	@$(T3VSS) GET $$\FrameWrk\*.* -GF -GTM -R -W+ -O$(T3GETLOGDIR)\ssget_lmfcx.log
	@$(T3VSS) GET $$\Xtension\VisObj\*.* -GF -GTM -R -W+ -O$(T3GETLOGDIR)\ssget_triasvmd.log
	
#############################################################################
# das große Finale...
# hier kommen wir an wenn das targetspezifische Makefile abgearbeitet wird
# und als Target "FINALTARGET" angegeben wurde.
# Beispiel siehe unter "Einzeltargets ==> lmfcx / lpict"

FINALTARGET:
#	@ECHO === MAKE WITH MSDEV "$(T3PROJECT).dsp" /OUT $(T3LOGDIR)\$(T3PROJECT).log /MAKE "$(T3CONFIG)" $(T3MAKEOPTIONS)
	@$(T3MSDEV) "$(T3PROJECT).dsp" /OUT "$(T3LOGDIR)\$(T3PROJECT).log" /MAKE "$(T3CONFIG)" $(T3MAKEOPTIONS)

#############################################################################
# TRiAS - Komponenten; jeweils Debug / Release

#############################################################################
# Bibliotheken

D_TRIASLIB		= \
	$(TRIASDIR_D)\lol50d.dll \
	$(TRIASDIR_D)\Objmand.dll \
	$(TRIASLIB)\muscrl32.lib \
	$(TRIASLIB)\GMObjectsD.lib

R_TRIASLIB		= \
	$(TRIASDIR_R)\lol.dll \
	$(TRIASDIR_R)\Objman.dll \
	$(TRIASLIB)\muscrl32.lib \
	$(TRIASLIB)\GMObjects.lib

#############################################################################
# Core-Komponenten

D_TRIASCORE		= \
	$(TRIASDIR_D)\trias32d.exe	\
	$(TRIASDIR_D)\UnRegTRiASd.exe	\
	$(TRIASDIR_D)\containd.dll \
	$(TRIASDIR_D)\trias31d.dll \
	$(TRIASDIR_D)\trias32d.dll \
	$(TRIASDIR_D)\trias33d.dll \
	$(TRIASDIR_D)\Tfrm32d.dll \
	$(TRIASLIB)\tfrmld.lib \
	$(TRIASDIR_D)\TRiASUId.dll \
	$(TRIASDIR_D)\TRiASICN.dll \
	$(TRIASDIR_D)\colorsd.ebn \
	$(TRIASDIR_D)\daolayed.ebn

R_TRIASCORE		= \
	$(TRIASDIR_R)\trias32.exe	\
	$(TRIASDIR_R)\UnRegTRiAS.exe	\
	$(TRIASDIR_R)\containr.dll \
	$(TRIASDIR_R)\trias321.dll \
	$(TRIASDIR_R)\trias322.dll \
	$(TRIASDIR_R)\trias323.dll \
	$(TRIASDIR_R)\Tfrmwork.dll \
	$(TRIASLIB)\tfrmlr.lib \
	$(TRIASDIR_R)\TRiASUI.dll \
	$(TRIASDIR_R)\TRiASICN.dll \
	$(TRIASDIR_R)\colors.ebn \
	$(TRIASDIR_R)\daolayer.ebn

!if "Debug" == "$(CONFIGURATION)"
B_TRIASCORE = $(D_TRIASCORE)
!else if "Release" == "$(CONFIGURATION)"
B_TRIASCORE = $(R_TRIASCORE)
!endif

#############################################################################
# Geometrie

D_TRIASGEOM		= \
	$(TRIASDIR_D)\geometd.dll \
	$(TRIASDIR_D)\objoperd.ext \
	$(TRIASDIR_D)\geoeditd.ext \
	$(TRIASDIR_D)\abstandd.ext \
	$(TRIASDIR_D)\gitterd.ext \
	$(TRIASDIR_D)\bufferd.ext \
	$(TRIASDIR_D)\toporeld.ext \
	$(TRIASDIR_D)\georeind.ext

R_TRIASGEOM		= \
	$(TRIASDIR_R)\geometr.dll \
	$(TRIASDIR_R)\objoper.ext \
	$(TRIASDIR_R)\geoedit.ext \
	$(TRIASDIR_R)\abstand.ext \
	$(TRIASDIR_R)\gitter.ext \
	$(TRIASDIR_R)\buffer.ext \
	$(TRIASDIR_R)\toporel.ext \
	$(TRIASDIR_R)\georein.ext

!if "Debug" == "$(CONFIGURATION)"
B_TRIASGEOM = $(D_TRIASGEOM)
!else if "Release" == "$(CONFIGURATION)"
B_TRIASGEOM = $(R_TRIASGEOM)
!endif

#############################################################################
# Koordinaten

D_TRIASCOORD	= \
	$(TRIASDIR_D)\DefCtfsd.css	\
	$(TRIASDIR_D)\GeodCtfd.css	\
	$(TRIASDIR_D)\GKCtfsd.css

R_TRIASCOORD	= \
	$(TRIASDIR_R)\DefCtfs.css	\
	$(TRIASDIR_R)\GeodCtfs.css	\
	$(TRIASDIR_R)\GKCtfs.css

!if "Debug" == "$(CONFIGURATION)"
B_TRIASCOORD = $(D_TRIASCOORD)
!else if "Release" == "$(CONFIGURATION)"
B_TRIASCOORD = $(R_TRIASCOORD)
!endif

#############################################################################
# Exportmodule

D_TRIASEXPORT	= \
	$(TRIASDIR_D)\ExportD.ext \
	$(TRIASDIR_D)\DirisASCD.flt \
	$(TRIASDIR_D)\TRiASARCD.flt \
	$(TRIASDIR_D)\AcadDXFD.flt \
	$(TRIASDIR_D)\AtlasBNAD.flt \
	$(TRIASDIR_D)\ArcViewD.flt \
	$(TRIASDIR_D)\PolyGISPMFD.flt \
	$(TRIASDIR_D)\PolyGISDATD.flt

R_TRIASEXPORT	= \
	$(TRIASDIR_R)\Export.ext \
	$(TRIASDIR_R)\DirisASC.flt \
	$(TRIASDIR_R)\TRiASARC.flt \
	$(TRIASDIR_R)\AcadDXF.flt \
	$(TRIASDIR_R)\AtlasBNA.flt \
	$(TRIASDIR_R)\ArcView.flt \
	$(TRIASDIR_R)\PolyGISPMF.flt \
	$(TRIASDIR_R)\PolyGISDAT.flt

!if "Debug" == "$(CONFIGURATION)"
B_TRIASEXPORT = $(D_TRIASEXPORT)
!else if "Release" == "$(CONFIGURATION)"
B_TRIASEXPORT = $(R_TRIASEXPORT)
!endif

#############################################################################
# Importmodule

D_TRIASIMPORT	= \
	$(TRIASDIR_D)\arctriad.ext \
	$(TRIASDIR_D)\ascimpd.ext \
	$(TRIASDIR_D)\dxfimpd.ext \
	$(TRIASDIR_D)\edbsimpd.ext \
	$(TRIASDIR_D)\edbsalkd.ext \
	$(TRIASDIR_D)\bnaimpd.ext

R_TRIASIMPORT	= \
	$(TRIASDIR_R)\arctrias.ext \
	$(TRIASDIR_R)\ascimp.ext \
	$(TRIASDIR_R)\dxfimp.ext \
	$(TRIASDIR_R)\edbsimp.ext \
	$(TRIASDIR_R)\edbsalk.ext \
	$(TRIASDIR_R)\bnaimp.ext

!if "Debug" == "$(CONFIGURATION)"
B_TRIASIMPORT = $(D_TRIASIMPORT)
!else if "Release" == "$(CONFIGURATION)"
B_TRIASIMPORT = $(R_TRIASIMPORT)
!endif
	
#############################################################################
# Extensions

D_TRIASXTENSION		= \
	$(TRIASDIR_D)\Oleautod.ext \
	$(TRIASDIR_D)\bilderd.ext \
	$(TRIASDIR_D)\maschbld.ext \
	$(TRIASDIR_D)\Identdbd.ext \
	$(TRIASDIR_D)\fakemfcd.ext \
	$(TRIASDIR_D)\geostatd.ext \
	$(TRIASDIR_D)\odbcextd.ext \
	$(TRIASDIR_D)\bscriptd.ext \
	$(TRIASDIR_D)\TRiASIGM.ext \
	$(TRIASDIR_D)\Tprojecd.ext \
	$(TRIASDIR_D)\TRSABiSd.ext \
	$(TRIASDIR_D)\LineToold.ext \
	$(TRIASDIR_D)\LoadableCommandsd.ext \
	$(TRIASDIR_D)\Statistd.ext

#	$(TRIASDIR_D)\Splittid.ext \

R_TRIASXTENSION		= \
	$(TRIASDIR_R)\Oleauto.ext \
	$(TRIASDIR_R)\bilder.ext \
	$(TRIASDIR_R)\maschblr.ext \
	$(TRIASDIR_R)\Identsdb.ext \
	$(TRIASDIR_R)\fakemfc.ext \
	$(TRIASDIR_R)\geostat.ext \
	$(TRIASDIR_R)\odbcext.ext \
	$(TRIASDIR_R)\bscript.ext \
	$(TRIASDIR_R)\TRiASIGM.ext \
	$(TRIASDIR_R)\Tproject.ext \
	$(TRIASDIR_R)\TRSABiS.ext \
	$(TRIASDIR_R)\LineTools.ext \
	$(TRIASDIR_R)\LoadableCommands.ext \
	$(TRIASDIR_R)\Statist.ext \

#	$(TRIASDIR_R)\Splitting.ext \

!if "Debug" == "$(CONFIGURATION)"
B_TRIASXTENSION = $(D_TRIASXTENSION)
!else if "Release" == "$(CONFIGURATION)"
B_TRIASXTENSION = $(R_TRIASXTENSION)
!endif

#############################################################################
# Visualisierungsmodule

D_TRIASVISMOD		= \
	$(TRIASDIR_D)\KartenD.vmd \
	$(TRIASDIR_D)\LinesigD.vmd \
	$(TRIASDIR_D)\TortenD.vmd \
	$(TRIASDIR_D)\TxtRotl.vmd 

R_TRIASVISMOD		= \
	$(TRIASDIR_R)\Karten.vmd \
	$(TRIASDIR_R)\Linesig.vmd \
	$(TRIASDIR_R)\Torten.vmd \
	$(TRIASDIR_R)\TxtRotl.vmd

!if "Debug" == "$(CONFIGURATION)"
B_TRIASVISMOD = $(D_TRIASVISMOD)
!else if "Release" == "$(CONFIGURATION)"
B_TRIASVISMOD = $(R_TRIASVISMOD)
!endif

#############################################################################
# TRiASDBBase; TRiASDB Basismodule

D_TRIASDBBASE	= \
	$(TRIASDIR_D)\TRiASMDSD.dll \
	$(TRIASDIR_D)\TErrTrkD.dll \
	$(TRIASDIR_D)\TDBGEOd.dll \
	$(TRIASDIR_D)\Helperd.dll \
	$(TRIASDIR_D)\TRiASCsD.dll

R_TRIASDBBASE	= \
	$(TRIASDIR_R)\TRiASMDS.dll \
	$(TRIASDIR_R)\TErrTrk.dll \
	$(TRIASDIR_R)\TDBGEO.dll \
	$(TRIASDIR_R)\Helper.dll \
	$(TRIASDIR_R)\TRiASCs.dll

!if "Debug" == "$(CONFIGURATION)"
B_TRIASDBBASE = $(D_TRIASDBBASE)
!else if "Release" == "$(CONFIGURATION)"
B_TRIASDBBASE = $(R_TRIASDBBASE)
!endif

#############################################################################
# TRiASDB; TRiASDB selbst

D_TRIASDB		= \
	$(TRIASDIR_D)\TRiASDBD.dll

R_TRIASDB		= \
	$(TRIASDIR_R)\TRiASDB.dll

!if "Debug" == "$(CONFIGURATION)"
B_TRIASDB = $(D_TRIASDB)
!else if "Release" == "$(CONFIGURATION)"
B_TRIASDB = $(R_TRIASDB)
!endif

#############################################################################
# TRiASCFG: XML Konfiguration

D_TRIASCFG		= \
	$(TRIASDIR_D)\TRiASCFGD.dll

R_TRIASCFG		= \
	$(TRIASDIR_R)\TRiASCFG.dll

!if "Debug" == "$(CONFIGURATION)"
B_TRIASCFG = $(D_TRIASCFG)
!else if "Release" == "$(CONFIGURATION)"
B_TRIASCFG = $(R_TRIASCFG)
!endif

#############################################################################
# TRiASHP; ArcView Dataserver

D_TRIASHP		= \
	$(TRIASDIR_D)\TRiASHPD.dll

R_TRIASHP		= \
	$(TRIASDIR_R)\TRiASHP.dll

!if "Debug" == "$(CONFIGURATION)"
B_TRIASHP = $(D_TRIASHP)
!else if "Release" == "$(CONFIGURATION)"
B_TRIASHP = $(R_TRIASHP)
!endif

#############################################################################
# MMMODULES; Kartenimportmodule et.al.

D_MMMODULES		= \
	$(TRIASDIR_D)\MMARCINFD.dll \
	$(TRIASDIR_D)\MMGEOPUNKTDLKD.dll \
	$(TRIASDIR_D)\MMPOLYGISD.dll 

R_MMMODULES		= \
	$(TRIASDIR_R)\MMARCINF.dll \
	$(TRIASDIR_R)\MMGEOPUNKTDLK.dll \
	$(TRIASDIR_R)\MMPOLYGIS.dll 

!if "Debug" == "$(CONFIGURATION)"
B_MMMODULES = $(D_MMMODULES)
!else if "Release" == "$(CONFIGURATION)"
B_MMMODULES = $(R_MMMODULES)
!endif

#############################################################################
# MAPMGR; Kartenimport et.al.

D_MAPMGR_ETAL		= \
	$(TRIASDIR_D)\UICTRLD.dll \
	$(TRIASDIR_D)\MAPMGRD.ext \
	$(D_MMMODULES)

R_MAPMGR_ETAL		= \
	$(TRIASDIR_R)\UICTRL.dll \
	$(TRIASDIR_R)\MAPMGR.ext \
	$(R_MMMODULES)

!if "Debug" == "$(CONFIGURATION)"
B_MAPMGR_ETAL = $(D_MAPMGR_ETAL)
!else if "Release" == "$(CONFIGURATION)"
B_MAPMGR_ETAL = $(R_MAPMGR_ETAL)
!endif

#############################################################################
# TRiASGDO; TRIASGDO

D_TRIASGDO		= \
	$(TRIASDIR_D)\TRiASGDOD.dll

R_TRIASGDO		= \
	$(TRIASDIR_R)\TRiASGDO.dll

!if "Debug" == "$(CONFIGURATION)"
B_TRIASGDO = $(D_TRIASGDO)
!else if "Release" == "$(CONFIGURATION)"
B_TRIASGDO = $(R_TRIASGDO)
!endif

#############################################################################
# alles schön zusammengefaßt

D_TRIAS = \
	$(D_TRIASLIB) \
	$(D_TRIASCORE) \
	$(D_TRIASXTENSION) \
	$(D_TRIASGEOM) \
	$(D_TRIASCOORD) \
	$(D_TRIASVISMOD) \
	$(D_TRIASDB) \
	$(D_TRIASHP) \
	$(D_TRIASGDO) \
	$(D_TRIASEXPORT) \
	$(D_MAPMGR_ETAL) \
	$(D_TRIASIMPORT)

R_TRIAS = \
	$(R_TRIASLIB) \
	$(R_TRIASCORE) \
	$(R_TRIASXTENSION) \
	$(R_TRIASGEOM) \
	$(R_TRIASCOORD) \
	$(R_TRIASVISMOD) \
	$(R_TRIASDB) \
	$(R_TRIASHP) \
	$(R_TRIASGDO) \
	$(R_TRIASEXPORT) \
	$(R_MAPMGR_ETAL) \
	$(R_TRIASIMPORT)

!if "Debug" == "$(CONFIGURATION)"
B_T3FILES=$(D_TRIAS)
!else if "Release" == "$(CONFIGURATION)"
B_T3FILES=$(R_TRIAS)
!endif

#############################################################################
# und jetzt die eigentlichen Targets um die es in dem ganzen Makefile geht...

TRiAS:			SETUPENV makefiles $(B_T3FILES)

TRiASCore:		SETUPENV makefiles $(B_TRIASCORE)

TRiASDBBase:	SETUPENV makefiles $(B_TRIASDBBASE)

TRiASDB:		SETUPENV makefiles $(B_TRIASDBBASE) $(B_TRIASDB) $(B_TRIASHP)

TRiASGDO:		SETUPENV makefiles $(B_TRIASDBBASE) $(B_TRIASDB) $(B_TRIASHP) $(B_TRIASGDO)

TRiASExport:	SETUPENV makefiles $(B_TRIASEXPORT)

TRiASImport:	SETUPENV makefiles $(B_TRIASIMPORT)

TRiASVismod:	SETUPENV makefiles $(B_TRIASVISMOD)

TRiASGeometry:	SETUPENV makefiles $(B_TRIASGEOM)

TRiASCoords:	SETUPENV makefiles $(B_TRIASCOORD)

TRiASXtensions:	SETUPENV makefiles $(B_TRIASXTENSION)

wolfgang:	SETUPENV makefiles TRiASGeometry

MapMgr:		SETUPENV makefiles $(B_MAPMGR_ETAL)

#############################################################################
# ...die hier zum Testen....

!if "Debug" == "$(CONFIGURATION)"
test:	SETUPENV makefiles 	$(TRIASDIR_D)\trias32d.exe
!else if "Release" == "$(CONFIGURATION)"
test:	SETUPENV makefiles $(TRIASDIR_R)\Torten.vmd
!endif

#############################################################################
# Die folgenden Targets arbeiten mit 'OLDMAKEDIR', meist aufgrund
# von inkonsistenten Workspacenamen. Sie sind hier zusammengefaßt
# und sollten angelegentlich korrigiert werden. Die einzelnen Targets
# können im Makefile über die folgende Marke gefunden werden (CTRL-F3):
#OLDMAKEDIR

!if "Debug" == "$(CONFIGURATION)"
_lol:		$(TRIASDIR_D)\lol50d.dll $(TRIASLIB)\lol50d.lib
_Visobj:	$(TRIASDIR_D)\visobjd.ext			# Visobj42.dsp (sollte Visobj.dsp sein)
_Torten:	$(TRIASDIR_D)\TortenD.vmd			# Torten4.dsp (sollte Torten.dsp sein)
_TxtRotl:	$(TRIASDIR_D)\TxtRotl.vmd			# TxtRotl4.dsp (sollte TxtRotl.dsp sein)
_BScript:	$(TRIASDIR_D)\bscriptd.ext			# Verzeichnis, BScript4.dsp (sollte BScript.dsp sein)
_OleAuto:	$(TRIASDIR_D)\OleAutoD.ext			# OleAuto4.dsp (sollte OleAuto.dsp sein)
_Identsdb:	$(TRIASDIR_D)\Identdbd.ext			# Idntdb32.dsp (sollte Identsdb.dsp sein)
_Bilder:	$(TRIASDIR_D)\bilderd.ext			# Bilder4.dsp (sollte Bilder.dsp sein)
_GeoStat:	$(TRIASDIR_D)\geostatd.ext			# Stat32.dsp (sollte Geostat.dsp sein)
_MaschBld:	$(TRIASDIR_D)\Maschbld.ext			# Verzeicnis, Linver.dsp (sollte MaschBld.dsp sein)
_FakeMFC:	$(TRIASDIR_D)\fakemfcd.ext			# Konfiguration ("fakemfc - Win32 Debug with OT")
_AscImp:	$(TRIASDIR_D)\ascimpd.ext
_DefCtfs:	$(TRIASDIR_D)\DefCtfsd.css
_GeodCtfs:	$(TRIASDIR_D)\GeodCtfd.css
_GKCtfs:	$(TRIASDIR_D)\GKCtfsd.css
_TRiAS01:	$(TRIASDIR_D)\trias31d.dll			# $(TRIASLIB)\trias31d.lib
_TRiAS02:	$(TRIASDIR_D)\trias32d.dll			# $(TRIASLIB)\trias32d.lib
_TRiAS03:	$(TRIASDIR_D)\trias33d.dll			# $(TRIASLIB)\trias33d.lib
_TRiAS:		$(TRIASDIR_D)\trias32d.exe
_Kompias:	$(TRIASDIR_D)\TRiASIGM.ext
_Tproject:	$(TRIASDIR_D)\Tprojecd.ext
_IXtension:	$(TRIASLIB)\ixtnsd50.lib
_IXtsnMFC:	$(TRIASLIB)\ixtmfd50.lib
_IXtsnATLBase:	$(TRIASLIB)\ixtatd50.lib
_IXtsnATL:	$(TRIASLIB)\Ixtmad50.lib
_IXtsnWTL:	$(TRIASLIB)\Ixtwtld.lib
_EDBSAlk:	$(TRIASDIR_D)\EdbsAlkd.ext
_Statist:	$(TRIASDIR_D)\Statistd.ext

!else if "Release" == "$(CONFIGURATION)"
_lol:		$(TRIASDIR_R)\lol.dll $(TRIASLIB)\lol.lib
_Visobj:	$(TRIASDIR_R)\visobj.ext
_Torten:	$(TRIASDIR_R)\Torten.vmd
_TxtRotl:	$(TRIASDIR_R)\TxtRotl.vmd
_BScript:	$(TRIASDIR_R)\bscript.ext
_OleAuto:	$(TRIASDIR_R)\OleAuto.ext
_Identsdb:	$(TRIASDIR_R)\Identsdb.ext
_Bilder:	$(TRIASDIR_R)\bilder.ext
_GeoStat:	$(TRIASDIR_R)\geostat.ext
_MaschBld:	$(TRIASDIR_R)\Maschblr.ext
_FakeMFC:	$(TRIASDIR_R)\fakemfc.ext
_AscImp:	$(TRIASDIR_R)\ascimp.ext
_DefCtfs:	$(TRIASDIR_R)\DefCtfs.css
_GeodCtfs:	$(TRIASDIR_R)\GeodCtfs.css
_GKCtfs:	$(TRIASDIR_R)\GKCtfs.css
_TRiAS01:	$(TRIASDIR_R)\trias321.dll			# $(TRIASLIB)\trias321.lib
_TRiAS02:	$(TRIASDIR_R)\trias322.dll			# $(TRIASLIB)\trias322.lib
_TRiAS03:	$(TRIASDIR_R)\trias323.dll			# $(TRIASLIB)\trias323.lib
_TRiAS:		$(TRIASDIR_R)\TRiAS32.exe
_Kompias:	$(TRIASDIR_R)\TRiASIGM.ext
_Tproject:	$(TRIASDIR_R)\Tproject.ext
_IXtension:	$(TRIASLIB)\ixtnsr50.lib
_IXtsnMFC:	$(TRIASLIB)\ixtmfr50.lib
_IXtsnATLBase:	$(TRIASLIB)\ixtatr50.lib
_IXtsnATL:	$(TRIASLIB)\Ixtmar50.lib
_IXtsnWTL:	$(TRIASLIB)\Ixtwtlr.lib
_EDBSAlk:	$(TRIASDIR_R)\EdbsAlk.ext
_Statist:	$(TRIASDIR_R)\Statist.ext
!endif

#############################################################################
# (1) Bibliotheken

#############################################################################
# LMFCX

$(TRIASDIR_D)\LMfcx42D.dll:	_LMFCX42 Ospace_
$(TRIASDIR_R)\LMfcx42.dll:	_LMFCX42 Ospace_

_LMFCX42:
	$(MAKECMD) T3PROJECT=LMfcx42 DOMAKEDIR=$(T3SRCBASE)\FrameWrk\LMfcx42

#############################################################################
# LPict

$(TRIASDIR_D)\LPict42D.dll:	_LibCtrlExt _LPICT42 Ospace_
$(TRIASDIR_R)\LPict42.dll:	_LibCtrlExt _LPICT42 Ospace_

_LPICT42:
	$(MAKECMD) T3PROJECT=LPict42 DOMAKEDIR=$(T3SRCBASE)\FrameWrk\LPict42

#############################################################################
# LibVMD

$(TRIASLIB)\LibvmdD.lib:	_LIBVMD
$(TRIASLIB)\Libvmd.lib:		_LIBVMD

_LIBVMD:
	$(MAKECMD) T3PROJECT=LibVMD DOMAKEDIR=$(T3SRCBASE)\Xtension\Visobj\Libvmd

#############################################################################
# LibTopoMap

$(TRIASLIB)\LibTopoMapD.lib:	_LIBTopoMap
$(TRIASLIB)\LibTopoMap.lib:		_LIBTopoMap

_LIBTopoMap:
	$(MAKECMD) T3PROJECT=LibTopoMap DOMAKEDIR=$(T3SRCBASE)\FrameWrk\LibTopoMap

#############################################################################
# LibCtrlExt

$(TRIASLIB)\LibCtrlExtD.lib:	_LibCtrlExt
$(TRIASLIB)\LibCtrlExt.lib:		_LibCtrlExt

_LibCtrlExt:
	$(MAKECMD) T3PROJECT=LibCtrlExt DOMAKEDIR=$(T3SRCBASE)\LibCtrlExt

#############################################################################
# libGiST

$(TRIASLIB)\libGiSTD.lib:	_libGiST
$(TRIASLIB)\libGiST.lib:	_libGiST

_libGiST:
	$(MAKECMD) T3PROJECT=libGiST DOMAKEDIR=$(T3SRCBASE)\FrameWrk\GiST\libGiST

#############################################################################
# Am meisten benutzte Basisabhängigkeiten; diese sind i.a. fertige
# Bibliotheken die nur noch kopiert werden müssen. Die Targets heißen
# immer gleich, haben jedoch je nach Debug / Release jeweils andere
# Abhängigkeiten.

!if "Debug" == "$(CONFIGURATION)"
lol_:			$(TRIASDIR_D)\lol50d.dll $(TRIASLIB)\lol50d.lib
OleAuto_:		$(TRIASDIR_D)\OleAutoD.ext
FakeMFC_:		$(TRIASDIR_D)\FakeMFCD.ext
TRiASTLB_:		$(TRIASLIB)\TriasTld.lib $(TRIASLIB)\TRiAStld.pdb
Container_:		$(TRIASDIR_D)\containd.dll
Ospace_:		$(TRIASDIR_D)\Ospace5d.dll
OspaceUSS_:		$(TRIASLIB)\StdStr5d.lib
TFramework_:		$(TRIASDIR_D)\Tfrm32d.dll $(TRIASLIB)\tfrmld.lib
IXtension_:		$(TRIASLIB)\ixtnsd50.lib
IXtsnATLBase_:		$(TRIASLIB)\ixtatd50.lib
IXtsnWTLBase_:		$(TRIASLIB)\ixtwtld.lib
IXtsnATL_:		$(TRIASLIB)\Ixtmad50.lib
IXtsnMFC_:		$(TRIASLIB)\ixtmfd50.lib
!else if "Release" == "$(CONFIGURATION)"
lol_:			$(TRIASDIR_R)\lol.dll $(TRIASLIB)\lol.lib
OleAuto_:		$(TRIASDIR_R)\OleAuto.ext
FakeMFC_:		$(TRIASDIR_R)\FakeMFC.ext
TRiASTLB_:		$(TRIASLIB)\TriasTlb.lib $(TRIASLIB)\TriasTlb.pdb
Container_:		$(TRIASDIR_R)\containr.dll
Ospace_:		$(TRIASDIR_R)\Ospace.dll
OspaceUSS_:		$(TRIASLIB)\StdStr5r.lib
TFramework_:		$(TRIASDIR_R)\Tfrmwork.dll $(TRIASLIB)\tfrmlr.lib
IXtension_:		$(TRIASLIB)\ixtnsr50.lib
IXtsnATLBase_:		$(TRIASLIB)\ixtatr50.lib
IXtsnWTLBase_:		$(TRIASLIB)\ixtwtlr.lib
IXtsnATL_:		$(TRIASLIB)\Ixtmar50.lib
IXtsnMFC_:		$(TRIASLIB)\ixtmfr50.lib
!endif

IProp_:			$(TRIASLIB)\iprop.lib
MuScroll_:		$(TRIASLIB)\muscrl32.lib

#############################################################################
# TRiASTlb

$(TRIASLIB)\TriasTld.lib: $(PREBUILDLIBS)\TriasTld.lib
	$(XCOPY) $(PREBUILDLIBS)\TriasTld.lib $(TRIASLIB)\\

$(TRIASLIB)\TRiAStld.pdb: $(PREBUILDLIBS)\TRiAStld.pdb
	$(XCOPY) $(PREBUILDLIBS)\TRiAStld.pdb $(TRIASLIB)\\

$(TRIASLIB)\TriasTlb.lib : $(PREBUILDLIBS)\TriasTlb.lib
	$(XCOPY) $(PREBUILDLIBS)\TriasTlb.lib $(TRIASLIB)\\

$(TRIASLIB)\TRiAStlb.pdb: $(PREBUILDLIBS)\TRiAStlb.pdb
	$(XCOPY) $(PREBUILDLIBS)\TRiAStlb.pdb $(TRIASLIB)\\

#############################################################################
# Iprop
$(TRIASLIB)\iprop.lib : $(PREBUILDLIBS)\iprop.lib
	$(XCOPY) $(PREBUILDLIBS)\iprop.lib $(TRIASLIB)\\

#############################################################################
# Muscroll

$(TRIASLIB)\muscrl32.lib : $(PREBUILDLIBS)\muscrl32.lib
	$(XCOPY) $(PREBUILDLIBS)\muscrl32.lib $(TRIASLIB)\\

#############################################################################
# GMObjects

$(TRIASLIB)\GMObjectsD.lib : $(PREBUILDLIBS)\GMObjectsD.lib
	$(XCOPY) $(PREBUILDLIBS)\GMObjectsD.lib $(TRIASLIB)
# \GMObjectsD.lib	

$(TRIASLIB)\GMObjects.lib : $(PREBUILDLIBS)\GMObjects.lib
	$(XCOPY) $(PREBUILDLIBS)\GMObjects.lib $(TRIASLIB)
# \GMObjects.lib	

#############################################################################
# Container

$(TRIASDIR_D)\containd.dll:
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\FrameWrk\Containr FINALTARGET=$@

#$(TRIASLIB)\cont50d.lib:
#	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\FrameWrk\Containr FINALTARGET=$@

$(TRIASDIR_R)\containr.dll:
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\FrameWrk\Containr FINALTARGET=$@

#$(TRIASLIB)\containr.lib:
#	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\FrameWrk\Containr FINALTARGET=$@

#############################################################################
# Ospace

$(TRIASDIR_D)\Ospace5d.dll:
	$(MAKECMD) OLDMAKEDIR=D:\Toolkit\Ospace\Ospace FINALTARGET=$@

#$(TRIASLIB)\Ospace5d.lib:
#	$(MAKECMD) OLDMAKEDIR=D:\Toolkit\Ospace\Ospace FINALTARGET=$@

$(TRIASDIR_R)\Ospace.dll:
	$(MAKECMD) OLDMAKEDIR=D:\Toolkit\Ospace\Ospace FINALTARGET=$@

#$(TRIASLIB)\Ospace5r.lib:
#	$(MAKECMD) OLDMAKEDIR=D:\Toolkit\Ospace\Ospace FINALTARGET=$@

$(TRIASLIB)\StdStr5d.lib:
	$(MAKECMD) OLDMAKEDIR=D:\Toolkit\Ospace\Ospace FINALTARGET=$@

$(TRIASLIB)\StdStr5r.lib : 
	$(MAKECMD) OLDMAKEDIR=D:\Toolkit\Ospace\Ospace FINALTARGET=$@

#############################################################################
# Common View

COMMONVIEWBASEDEP = Ospace_

$(TRIASDIR_D)\Tfrm32d.dll:	$(COMMONVIEWBASEDEP)
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\FrameWrk\CV FINALTARGET=$@

#$(TRIASLIB)\tfrm32d.lib:	$(COMMONVIEWBASEDEP)
#	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\FrameWrk\CV FINALTARGET=$@

$(TRIASDIR_R)\Tfrmwork.dll:	$(COMMONVIEWBASEDEP)
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\FrameWrk\CV FINALTARGET=$@

#$(TRIASLIB)\tfrmwork.lib:	$(COMMONVIEWBASEDEP)
#	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\FrameWrk\CV FINALTARGET=$@

$(TRIASLIB)\tfrmld.lib:
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\FrameWrk\CV FINALTARGET=$@

$(TRIASLIB)\tfrmlr.lib:
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\FrameWrk\CV FINALTARGET=$@

#############################################################################
# ZLib

$(TRIASLIB)\Zlibd.lib:	_ZLib
$(TRIASLIB)\ZLib.lib:	_ZLib

_ZLib:
	$(MAKECMD) T3PROJECT=ZLib DOMAKEDIR=$(T3SRCBASE)\TRiASDB\ZLib 

#############################################################################
# ShapeLib

$(TRIASLIB)\Shapelibd.lib:	_ShapeLib
$(TRIASLIB)\Shapelib.lib:	_ShapeLib

_ShapeLib:
	$(MAKECMD) T3PROJECT=Shapelib DOMAKEDIR=$(T3SRCBASE)\TRiASHP\Shapelib

#############################################################################
# Esnecil

$(TRIASLIB)\Esnecild.lib:	_Esnecil
$(TRIASLIB)\Esnecil.lib:	_Esnecil

_Esnecil:
	$(MAKECMD) T3PROJECT=Esnecil DOMAKEDIR=$(T3SRCBASE)\Esnecil

#############################################################################
# (2) Basismodule; diese Module sind von nichts anderem abhängig

#############################################################################
# TErrTrk

$(TRIASDIR_D)\TErrTrkD.dll:	_TErrTrk
$(TRIASDIR_R)\TErrTrk.dll:	_TErrTrk

_TErrTrk:
	$(MAKECMD) T3PROJECT=TErrTrk DOMAKEDIR=$(T3SRCBASE)\TErrTrk

#############################################################################
# TRiASCS

$(TRIASDIR_D)\TRiASCsD.dll: \
		$(TRIASDIR_D)\TErrTrkD.dll \
		_TRiASCS

$(TRIASDIR_R)\TRiASCs.dll: \
		$(TRIASDIR_R)\TErrTrk.dll \
		_TRiASCS

_TRiASCS:
	$(MAKECMD) T3PROJECT=TRiASCS DOMAKEDIR=$(T3SRCBASE)\TRiASCs

#############################################################################
# TRiASMDS

$(TRIASDIR_D)\TRiASMDSD.dll:	_TRiASMDS
$(TRIASDIR_R)\TRiASMDS.dll:		_TRiASMDS

_TRiASMDS:
	$(MAKECMD) T3PROJECT=TRiASMDS DOMAKEDIR=$(T3SRCBASE)\TRiASMDS

#############################################################################
# TRiASUI

$(TRIASDIR_D)\TRiASUId.dll:		_TRiASUI
$(TRIASDIR_R)\TRiASUI.dll:		_TRiASUI

_TRiASUI:
	$(MAKECMD) T3PROJECT=TRiASUI DOMAKEDIR=$(T3SRCBASE)\TRiASUI

#############################################################################
# Objman

$(TRIASDIR_D)\Objmand.dll:		_ObjMan
$(TRIASDIR_R)\Objman.dll:		_ObjMan

_ObjMan:
	$(MAKECMD) T3PROJECT=Objman DOMAKEDIR=$(T3SRCBASE)\XTension\Objman

#############################################################################
# Helper

$(TRIASDIR_D)\Helperd.dll:		_Helper
$(TRIASDIR_R)\Helper.dll:		_Helper

_Helper:
	$(MAKECMD) T3PROJECT=Helper DOMAKEDIR=$(T3SRCBASE)\Xtension\oleauto\helper

#############################################################################
# TRiASICN

$(TRIASDIR_D)\TRiASICN.dll:	_TRiASICN
$(TRIASDIR_R)\TRiASICN.dll:		_TRiASICN

_TRiASICN:
	$(MAKECMD) T3PROJECT=TRiASICN DOMAKEDIR=$(T3SRCBASE)\TRiASICN

#############################################################################
# (3) wieder Basismodule, hier aber schon Abhängigkeiten

#############################################################################
# TDBGEO

$(TRIASDIR_D)\TDBGEOd.dll : \
	$(TRIASDIR_D)\TRiASCSD.dll \
	$(TRIASDIR_D)\TErrTrkd.dll \
	$(TRIASLIB)\GMObjectsd.lib \
	_TDBGeo

$(TRIASDIR_R)\TDBGEO.dll : \
	$(TRIASDIR_R)\TRiASCS.dll \
	$(TRIASDIR_R)\TErrTrk.dll \
	$(TRIASLIB)\GMObjects.lib \
	_TDBGeo

_TDBGeo:
	$(MAKECMD) T3PROJECT=TDBGeo DOMAKEDIR=$(T3SRCBASE)\TDBGeo

#############################################################################
# LOL

LOLBASEDEP = Ospace_

$(TRIASDIR_D)\lol50d.dll:	$(LOLBASEDEP)
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\FrameWrk\lol\lib.c8\Lol32 FINALTARGET=$@

$(TRIASLIB)\lol50d.lib:		$(LOLBASEDEP)
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\FrameWrk\lol\lib.c8\Lol32 FINALTARGET=$@

$(TRIASDIR_R)\lol.dll:		$(LOLBASEDEP)
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\FrameWrk\lol\lib.c8\Lol32 FINALTARGET=$@

$(TRIASLIB)\lol.lib:		$(LOLBASEDEP)
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\FrameWrk\lol\lib.c8\Lol32 FINALTARGET=$@

#############################################################################
# Colors

$(TRIASDIR_D)\Colorsd.ebn:		Ospace_ _Colors
$(TRIASDIR_R)\Colors.ebn:		Ospace_ _Colors

_Colors:
	$(MAKECMD) T3PROJECT=Colors DOMAKEDIR=$(T3SRCBASE)\Xtension\Colors

#############################################################################
# (4) Koordinatentransformationen (alt)

#############################################################################
# DefCtfs

D_COORDSBASEDEP	= Ospace_ $(TRIASDIR_D)\TDBGeoD.dll		# $(TRIASDIR_D)\TRiASDBD.dll
R_COORDSBASEDEP	= Ospace_ $(TRIASDIR_R)\TDBGeo.dll		# $(TRIASDIR_R)\TRiASDB.dll

$(TRIASDIR_D)\DefCtfsd.css:	$(D_COORDSBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Coords\Default FINALTARGET=$@

$(TRIASDIR_R)\DefCtfs.css:	$(R_COORDSBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Coords\Default FINALTARGET=$@

#############################################################################
# GeodCtfs

$(TRIASDIR_D)\GeodCtfd.css:	$(D_COORDSBASEDEP) $(TRIASDIR_D)\DefCtfsd.css \
		_ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Coords\GeodCTF FINALTARGET=$@

$(TRIASDIR_R)\GeodCtfs.css:	$(D_COORDSBASEDEP) $(TRIASDIR_R)\DefCtfs.css \
		_ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Coords\GeodCTF FINALTARGET=$@

#############################################################################
# GKCtfs

$(TRIASDIR_D)\GKCtfsd.css:	$(D_COORDSBASEDEP) $(TRIASDIR_D)\DefCtfsd.css \
		_ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Coords\GKCTF FINALTARGET=$@

$(TRIASDIR_R)\GKCtfs.css:	$(D_COORDSBASEDEP) $(TRIASDIR_R)\DefCtfs.css \
		_ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Coords\GKCTF FINALTARGET=$@

#############################################################################
# Ixtensn
#OLDMAKEDIR

D_IXTENSNBASEDEP = \
		$(TRIASDIR_D)\DefCtfsD.css 	#	$(TRIASDIR_D)\TRiASDBD.dll

R_IXTENSNBASEDEP = \
		$(TRIASDIR_R)\DefCtfs.css 	#	$(TRIASDIR_R)\TRiASDB.dll

$(TRIASLIB)\Ixtmad50.lib:	$(D_IXTENSNBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Ixtensn FINALTARGET=$@
		         	
$(TRIASLIB)\Ixtmar50.lib:	$(R_IXTENSNBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Ixtensn FINALTARGET=$@

$(TRIASLIB)\ixtmfd50.lib:	$(D_IXTENSNBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Ixtensn FINALTARGET=$@

$(TRIASLIB)\ixtmfr50.lib:	$(R_IXTENSNBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Ixtensn FINALTARGET=$@

$(TRIASLIB)\ixtnsd50.lib:	$(D_IXTENSNBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Ixtensn FINALTARGET=$@

$(TRIASLIB)\ixtnsr50.lib:	$(R_IXTENSNBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Ixtensn FINALTARGET=$@

$(TRIASLIB)\ixtatd50.lib:	$(D_IXTENSNBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Ixtensn FINALTARGET=$@

$(TRIASLIB)\ixtatr50.lib:	$(R_IXTENSNBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Ixtensn FINALTARGET=$@

$(TRIASLIB)\ixtwtld.lib:	$(D_IXTENSNBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Ixtensn FINALTARGET=$@

$(TRIASLIB)\ixtwtlr.lib:	$(R_IXTENSNBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Ixtensn FINALTARGET=$@

#############################################################################
# (5) TRiAS Basis-DLL's und EXE

#############################################################################
# TRiAS01
#OLDMAKEDIR

TRIAS01BASEDEP = Container_

D_TRIAS01BASEDEP = $(TRIAS01BASEDEP) \
		$(TRIASDIR_D)\TRiASMDSD.dll \
		$(TRIASDIR_D)\TDBGeoD.dll \
		$(TRIASDIR_D)\VisObjd.ext \
		_libGiST \
		_ZLib

R_TRIAS01BASEDEP = $(TRIAS01BASEDEP) \
		$(TRIASDIR_R)\TRiASMDS.dll \
		$(TRIASDIR_R)\TDBGeo.dll \
		$(TRIASDIR_R)\VisObj.ext \
		_libGiST \
		_ZLib

$(TRIASDIR_D)\trias31d.dll:	$(D_TRIAS01BASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\TRiAS01 FINALTARGET=$@

#$(TRIASLIB)\trias31d.lib:	$(D_TRIAS01BASEDEP) _ForceBuild
#		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\TRiAS01 FINALTARGET=$@

$(TRIASDIR_R)\trias321.dll:	$(R_TRIAS01BASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\TRiAS01 FINALTARGET=$@

#$(TRIASLIB)\trias321.lib:	$(R_TRIAS01BASEDEP) _ForceBuild
#		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\TRiAS01 FINALTARGET=$@

#############################################################################
# TRiAS02
#OLDMAKEDIR

TRIAS02BASEDEP = Ospace_ Container_ TFramework_

D_TRIAS02BASEDEP = $(TRIAS02BASEDEP) \
	$(TRIASDIR_D)\triasdbd.dll \
	$(TRIASDIR_D)\trias31d.dll

R_TRIAS02BASEDEP = $(TRIAS02BASEDEP) \
	$(TRIASDIR_R)\triasdb.dll \
	$(TRIASDIR_R)\trias321.dll

$(TRIASDIR_D)\trias32d.dll:	$(D_TRIAS02BASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\TRiAS02 FINALTARGET=$@

#$(TRIASLIB)\trias32d.lib:		$(D_TRIAS02BASEDEP) _ForceBuild
#		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\TRiAS02 FINALTARGET=$@

$(TRIASDIR_R)\trias322.dll:		$(R_TRIAS02BASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\TRiAS02 FINALTARGET=$@

#$(TRIASLIB)\trias322.lib:		$(R_TRIAS02BASEDEP) _ForceBuild
#		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\TRiAS02 FINALTARGET=$@

#############################################################################
# TRiAS03
#OLDMAKEDIR

TRIAS03BASEDEP = Ospace_ Container_ TFramework_ MuScroll_

D_TRIAS03BASEDEP = $(TRIAS03BASEDEP) \
	$(TRIASDIR_D)\triasdbd.dll \
	$(TRIASDIR_D)\TRiASCFGd.dll \
	$(TRIASDIR_D)\trias32d.dll

R_TRIAS03BASEDEP = $(TRIAS03BASEDEP) \
	$(TRIASDIR_R)\triasdb.dll \
	$(TRIASDIR_R)\TRiASCFG.dll \
	$(TRIASDIR_R)\trias322.dll

$(TRIASDIR_D)\trias33d.dll:		$(D_TRIAS03BASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\TRiAS03 FINALTARGET=$@

#$(TRIASLIB)\trias33d.lib:		$(D_TRIAS03BASEDEP) _ForceBuild
#		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\TRiAS03 FINALTARGET=$@

$(TRIASDIR_R)\trias323.dll:		$(R_TRIAS03BASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\TRiAS03 FINALTARGET=$@

#$(TRIASLIB)\trias323.lib:		$(R_TRIAS03BASEDEP) _ForceBuild
#		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\TRiAS03 FINALTARGET=$@

#############################################################################
# TRiAS
#OLDMAKEDIR

TRIASEXEBASEDEP = Ospace_ Container_ TFramework_ lol_ OleAuto_

D_TRIASEXEBASEDEP = $(TRIASEXEBASEDEP) \
		$(TRIASDIR_D)\trias31d.dll \
		$(TRIASDIR_D)\trias32d.dll \
		$(TRIASDIR_D)\trias33d.dll \
		$(TRIASDIR_D)\triasdbd.dll \
		$(TRIASDIR_D)\fakemfcd.ext \
		$(TRIASLIB)\tfrmld.lib \
		$(TRIASLIB)\Esnecild.lib

R_TRIASEXEBASEDEP = $(TRIASEXEBASEDEP) \
		$(TRIASDIR_R)\trias321.dll \
		$(TRIASDIR_R)\trias322.dll \
		$(TRIASDIR_R)\trias323.dll \
		$(TRIASDIR_R)\triasdb.dll \
		$(TRIASDIR_R)\fakemfc.ext \
		$(TRIASLIB)\tfrmlr.lib \
		$(TRIASLIB)\Esnecil.lib

$(TRIASDIR_D)\trias32d.exe:	$(D_TRIASEXEBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\TRiAS FINALTARGET=$@

$(TRIASDIR_R)\TRiAS32.exe:	$(R_TRIASEXEBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\TRiAS FINALTARGET=$@

#############################################################################
# (6) Geometrieverarbeitung

#############################################################################
# GeoMetr

$(TRIASDIR_D)\geometd.dll:	$(TRIASDIR_D)\trias33d.dll _Geometr

$(TRIASLIB)\geometd.lib:	$(TRIASDIR_D)\trias33d.dll _Geometr

$(TRIASDIR_R)\geometr.dll:	$(TRIASDIR_R)\trias323.dll _Geometr

$(TRIASLIB)\geometr.lib:	$(TRIASDIR_R)\trias323.dll _Geometr

_Geometr:
	$(MAKECMD) T3PROJECT=Geometr FORMAKEDIR=D:\VCPP\Geometr
	$(MAKECMD) T3PROJECT=Geometr DOMAKEDIR=D:\VCPP\GeoMetr

#############################################################################
# Basisabhängigkeiten für alle Geometriemodule

GEOMBASEDEP = IXtsnATLBase_ TFramework_ Ospace_

D_GEOMBASEDEP = $(GEOMBASEDEP) $(TRIASLIB)\geometd.lib $(TRIASDIR_D)\TDBGeoD.dll
R_GEOMBASEDEP = $(GEOMBASEDEP) $(TRIASLIB)\geometr.lib $(TRIASDIR_R)\TDBGeo.dll

#############################################################################
# Georein

$(TRIASDIR_D)\georeind.ext:		$(D_GEOMBASEDEP) _GeoRein
$(TRIASDIR_R)\georein.ext :		$(R_GEOMBASEDEP) _GeoRein

_GeoRein:
	$(MAKECMD) T3PROJECT=GeoRein FORMAKEDIR=D:\VCPP\GeoRein
	$(MAKECMD) T3PROJECT=GeoRein DOMAKEDIR=D:\VCPP\GeoRein

#############################################################################
# Objoper

D_OBJOPERBASEDEP = $(D_GEOMBASEDEP) \
		$(TRIASDIR_D)\Helperd.dll \
		$(TRIASDIR_D)\Maschbld.ext

R_OBJOPERBASEDEP = $(R_GEOMBASEDEP) \
		$(TRIASDIR_R)\Helper.dll \
		$(TRIASDIR_R)\Maschblr.ext

$(TRIASDIR_D)\objoperd.ext:		$(D_OBJOPERBASEDEP) _ObjOper
$(TRIASDIR_R)\objoper.ext:		$(R_OBJOPERBASEDEP) _ObjOper

_ObjOper:
	$(MAKECMD) T3PROJECT=ObjOper FORMAKEDIR=D:\VCPP\ObjOper
	$(MAKECMD) T3PROJECT=ObjOper DOMAKEDIR=D:\VCPP\ObjOper

#############################################################################
# GeoEdit

$(TRIASDIR_D)\geoeditd.ext:		$(D_GEOMBASEDEP) _GeoEdit
$(TRIASDIR_R)\geoedit.ext:		$(R_GEOMBASEDEP) _GeoEdit

_GeoEdit:
	$(MAKECMD) T3PROJECT=GeoEdit FORMAKEDIR=D:\VCPP\GeoEdit
	$(MAKECMD) T3PROJECT=GeoEdit DOMAKEDIR=D:\VCPP\GeoEdit

#############################################################################
# Abstand

$(TRIASDIR_D)\abstandd.ext:		$(D_GEOMBASEDEP) _Abstand
$(TRIASDIR_R)\abstand.ext:		$(R_GEOMBASEDEP) _Abstand

_Abstand:
	$(MAKECMD) T3PROJECT=Abstand FORMAKEDIR=D:\VCPP\Abstand
	$(MAKECMD) T3PROJECT=Abstand DOMAKEDIR=D:\VCPP\Abstand

#############################################################################
# Gitter

$(TRIASDIR_D)\gitterd.ext:		$(D_GEOMBASEDEP) _Gitter
$(TRIASDIR_R)\gitter.ext:		$(R_GEOMBASEDEP) _Gitter

_Gitter:
	$(MAKECMD) T3PROJECT=Raster FORMAKEDIR=D:\VCPP\Gitter
	$(MAKECMD) T3PROJECT=Raster DOMAKEDIR=D:\VCPP\Gitter

#############################################################################
# Buffer

$(TRIASDIR_D)\bufferd.ext:		$(D_GEOMBASEDEP) _Buffer
$(TRIASDIR_R)\buffer.ext:		$(R_GEOMBASEDEP) _Buffer

_Buffer:
	$(MAKECMD) T3PROJECT=Buffer FORMAKEDIR=D:\VCPP\Buffer
	$(MAKECMD) T3PROJECT=Buffer DOMAKEDIR=D:\VCPP\Buffer

#############################################################################
# Toporel

$(TRIASDIR_D)\toporeld.ext:		$(D_GEOMBASEDEP) _Toporel
$(TRIASDIR_R)\toporel.ext:		$(R_GEOMBASEDEP) _Toporel

_Toporel:
	$(MAKECMD) T3PROJECT=Toporel FORMAKEDIR=D:\VCPP\Toporel
	$(MAKECMD) T3PROJECT=Toporel DOMAKEDIR=D:\VCPP\Toporel

#############################################################################
# (7) Die eigentlichen Erweiterungen

#############################################################################
# TRiAS-Datenserver

#############################################################################
# TRiASGDO

D_TRIASGDOBASEDEP = \
		$(TRIASLIB)\GMObjectsD.lib \
		$(TRIASDIR_D)\TRiASMDSD.dll \
		$(TRIASDIR_D)\TErrTrkD.dll \
		$(TRIASDIR_D)\TRiASCsD.dll

R_TRIASGDOBASEDEP = \
		$(TRIASLIB)\GMObjects.lib \
		$(TRIASDIR_R)\TRiASMDS.dll \
		$(TRIASDIR_R)\TErrTrk.dll \
		$(TRIASDIR_R)\TRiASCs.dll

$(TRIASDIR_D)\TRiASGDOD.dll:	$(D_TRIASGDOBASEDEP) _TRiASGDO
$(TRIASDIR_R)\TRiASGDO.dll:		$(R_TRIASGDOBASEDEP) _TRiASGDO

_TRiASGDO:
	$(MAKECMD) T3PROJECT=TRiASGDO DOMAKEDIR=$(T3SRCBASE)\TRiASGDO

#############################################################################
# TRiASDB

TRIASDBBASEDEP = IProp_

D_TRIASDBBASEDEP = $(TRIASDBBASEDEP) \
		$(TRIASDIR_D)\trias31d.dll \
		$(TRIASDIR_D)\Helperd.dll \
		$(TRIASDIR_D)\TDBGEOd.dll \
		$(TRIASDIR_D)\TRiASCsD.dll \
		$(TRIASDIR_D)\TRiASUId.dll \
		$(TRIASDIR_D)\visobjd.ext \
		$(TRIASDIR_D)\objmand.dll \
		_ZLib

R_TRIASDBBASEDEP = $(TRIASDBBASEDEP) \
		$(TRIASDIR_R)\trias321.dll \
		$(TRIASDIR_R)\Helper.dll \
		$(TRIASDIR_R)\TDBGEO.dll \
		$(TRIASDIR_R)\TRiASCs.dll \
		$(TRIASDIR_R)\TRiASUI.dll \
		$(TRIASDIR_R)\visobj.ext \
		$(TRIASDIR_R)\objman.dll \
		_ZLib

$(TRIASDIR_D)\TRiASDBD.dll:		$(D_TRIASDBBASEDEP) _TRiASDB
$(TRIASDIR_R)\TRiASDB.dll:		$(R_TRIASDBBASEDEP) _TRiASDB

_TRiASDB:
	$(MAKECMD) T3PROJECT=TRiASDB DOMAKEDIR=$(T3SRCBASE)\TRiASDB

#############################################################################
# TRiASCFG

D_TRIASCFGBASEDEP = \
		$(TRIASDIR_D)\Helperd.dll 

R_TRIASCFGBASEDEP = \
		$(TRIASDIR_R)\Helper.dll 

$(TRIASDIR_D)\TRiASCFGD.dll:		$(D_TRIASCFGBASEDEP) _TRiASCFG
$(TRIASDIR_R)\TRiASCFG.dll:		$(R_TRIASCFGBASEDEP) _TRiASCFG

_TRiASCFG:
	$(MAKECMD) T3PROJECT=TRiASCFG DOMAKEDIR=$(T3SRCBASE)\TRiASCFG

#############################################################################
# TRiASHP

TRIASHPBASEDEP = _ShapeLib

D_TRIASHPBASEDEP = $(TRIASHPBASEDEP) \
		$(TRIASDIR_D)\Helperd.dll \
		$(TRIASDIR_D)\TDBGEOd.dll \
		$(TRIASDIR_D)\TRiASCsD.dll \
		$(TRIASDIR_D)\TRiASMDSD.dll \
		$(TRIASDIR_D)\TRiASDBD.dll 

R_TRIASHPBASEDEP = $(TRIASHPBASEDEP) \
		$(TRIASDIR_R)\Helper.dll \
		$(TRIASDIR_R)\TDBGEO.dll \
		$(TRIASDIR_R)\TRiASCs.dll \
		$(TRIASDIR_R)\TRiASMDS.dll \
		$(TRIASDIR_R)\TRiASDB.dll


$(TRIASDIR_D)\TRiASHPD.dll:		$(D_TRIASHPBASEDEP) _TRiASHP
$(TRIASDIR_R)\TRiASHP.dll:		$(R_TRIASHPBASEDEP) _TRiASHP

_TRiASHP:
	$(MAKECMD) T3PROJECT=TRiASHP DOMAKEDIR=$(T3SRCBASE)\TRiASHP

#############################################################################
# Visobj
#OLDMAKEDIR

VISOBJBASEDEP = IXtsnATLBase_ TRiASTLB_ TFramework_ Ospace_ Container_ 

D_VISOBJBASEDEP = $(VISOBJBASEDEP) $(TRIASDIR_D)\colorsd.ebn # $(TRIASDIR_D)\Oleautod.ext
R_VISOBJBASEDEP = $(VISOBJBASEDEP) $(TRIASDIR_R)\colors.ebn  # $(TRIASDIR_R)\Oleauto.ext

$(TRIASDIR_D)\visobjd.ext:	$(D_VISOBJBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\VisObj FINALTARGET=$@

$(TRIASDIR_R)\visobj.ext:	$(R_VISOBJBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\VisObj FINALTARGET=$@

#############################################################################
# Basisabhängigkeiten für Visualisierungsmodule

D_VISMODBASEDEP = \
		$(TRIASDIR_D)\LMfcx42D.dll \
		$(TRIASDIR_D)\LPict42D.dll \
		$(TRIASLIB)\LibvmdD.lib

R_VISMODBASEDEP = \
		$(TRIASDIR_R)\LMfcx42.dll \
		$(TRIASDIR_R)\LPict42.dll \
		$(TRIASLIB)\Libvmd.lib

#############################################################################
# Karten

$(TRIASDIR_D)\KartenD.vmd:	$(D_VISMODBASEDEP) _Karten
$(TRIASDIR_R)\Karten.vmd:	$(R_VISMODBASEDEP) _Karten

_Karten:
	$(MAKECMD) T3PROJECT=Karten DOMAKEDIR=$(T3SRCBASE)\Xtension\VisObj\Karten

#############################################################################
# Basisabhängigkeiten für Kartenimport

D_MAPMGRBASEDEP = \
		$(TRIASTLB)\MapCtrl.tlb \
		$(TRIASLIB)\LibTopoMapD.lib \
		$(TRIASLIB)\LibCtrlExtD.lib \
		$(TRIASDIR_D)\UICtrlD.dll \
		$(TRIASDIR_D)\VisObjd.ext

R_MAPMGRBASEDEP = \
		$(TRIASTLB)\MapCtrl.tlb \
		$(TRIASLIB)\LibTopoMap.lib \
		$(TRIASLIB)\LibCtrlExt.lib \
		$(TRIASDIR_R)\UICtrl.dll \
		$(TRIASDIR_R)\VisObj.ext

#############################################################################
# UICtrl

$(TRIASDIR_D)\UICtrlD.dll:	_UICtrl
$(TRIASDIR_R)\UICtrl.dll:	_UICtrl

_UICtrl:
	$(MAKECMD) T3PROJECT=UICtrl DOMAKEDIR=$(T3SRCBASE)\Xtension\MapMgr\UICtrl

#############################################################################
# MapCtrl

$(TRIASTLB)\MapCtrl.tlb:	_MapCtrl

_MapCtrl:
	$(MAKECMD) T3PROJECT=MapCtrl DOMAKEDIR=$(T3SRCBASE)\Xtension\MapMgr\MapCtrl

#############################################################################
# MapMgr

$(TRIASDIR_D)\MapMgrD.ext: \
		$(D_VISMODBASEDEP) \
		$(D_MAPMGRBASEDEP) \
		IXtsnATL_ \
		_MapMgr

$(TRIASDIR_R)\MapMgr.ext: \
		$(R_VISMODBASEDEP) \
		$(R_MAPMGRBASEDEP) \
		IXtsnATL_  \
		_MapMgr

_MapMgr:
	$(MAKECMD) T3PROJECT=MapMgr DOMAKEDIR=$(T3SRCBASE)\Xtension\MapMgr

#############################################################################
# MMArcInf

$(TRIASDIR_D)\MMArcInfD.dll: \
		$(D_VISMODBASEDEP) \
		$(D_MAPMGRBASEDEP) \
		_MMArcInf

$(TRIASDIR_R)\MMArcInf.dll: \
		$(R_VISMODBASEDEP) \
		$(R_MAPMGRBASEDEP) \
		_MMArcInf

_MMArcInf:
	$(MAKECMD) T3PROJECT=MMArcInf DOMAKEDIR=$(T3SRCBASE)\Xtension\MapMgr\MapCtrl\MMArcInf

#############################################################################
# MMGeoPunktDLK

$(TRIASDIR_D)\MMGeoPunktDLKD.dll: \
		$(D_VISMODBASEDEP) \
		$(D_MAPMGRBASEDEP) \
		_MMGeoPunktDLK

$(TRIASDIR_R)\MMGeoPunktDLK.dll: \
		$(R_VISMODBASEDEP) \
		$(R_MAPMGRBASEDEP) \
		_MMGeoPunktDLK

_MMGeoPunktDLK:
	$(MAKECMD) T3PROJECT=MMGeoPunktDLK DOMAKEDIR=$(T3SRCBASE)\Xtension\MapMgr\MapCtrl\MMGeoPunktDLK

#############################################################################
# MMPolyGIS

$(TRIASDIR_D)\MMPolyGISD.dll: \
		$(D_VISMODBASEDEP) \
		$(D_MAPMGRBASEDEP) \
		_MMPolyGIS

$(TRIASDIR_R)\MMPolyGIS.dll: \
		$(R_VISMODBASEDEP) \
		$(R_MAPMGRBASEDEP) \
		_MMPolyGIS

_MMPolyGIS:
	$(MAKECMD) T3PROJECT=MMPolyGIS DOMAKEDIR=$(T3SRCBASE)\Xtension\MapMgr\MapCtrl\MMPolyGIS

#############################################################################
# Linesig

$(TRIASDIR_D)\LinesigD.vmd:	$(D_VISMODBASEDEP) _Linesig
$(TRIASDIR_R)\Linesig.vmd:	$(R_VISMODBASEDEP) _Linesig

_Linesig:
	$(MAKECMD) T3PROJECT=Linesig DOMAKEDIR=$(T3SRCBASE)\Xtension\VisObj\Linesig

#############################################################################
# Torten
#OLDMAKEDIR

TORTENBASEDEP = TFramework_ Ospace_ Container_ TRiASTLB_

D_TORTENBASEDEP = $(TORTENBASEDEP)
R_TORTENBASEDEP = $(TORTENBASEDEP)
	
$(TRIASDIR_D)\TortenD.vmd:	$(D_TORTENBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\VisObj\Torten FINALTARGET=$@

$(TRIASDIR_R)\Torten.vmd:	$(R_TORTENBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\VisObj\Torten FINALTARGET=$@

#############################################################################
# TxtRotl
#OLDMAKEDIR

TXTROTLBASEDEP = TFramework_ Ospace_ Container_ TRiASTLB_

D_TXTROTLBASEDEP = $(TXTROTLBASEDEP)
R_TXTROTLBASEDEP = $(TXTROTLBASEDEP)
	
$(TRIASDIR_D)\TxtRotl.vmd:	$(D_TXTROTLBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\VisObj\TxtRotl FINALTARGET=$@

$(TRIASDIR_R)\TxtRotl.vmd:	$(R_TXTROTLBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\VisObj\TxtRotl FINALTARGET=$@

#############################################################################
# Exportdefinitionen

$(TRIASINCLUDE)\tlb\ExportDef.tlb:	_ExportDef

_ExportDef:
	$(MAKECMD) T3PROJECT=ExportDef DOMAKEDIR=$(T3SRCBASE)\Export\ExportDef

#############################################################################
# Basisabhängigkeiten für Exportmodule

D_EXPORTBASEDEP = \
		$(TRIASINCLUDE)\tlb\ExportDef.tlb

R_EXPORTBASEDEP = \
		$(TRIASINCLUDE)\tlb\ExportDef.tlb

#############################################################################
# Export

$(TRIASDIR_D)\ExportD.ext:		$(D_EXPORTBASEDEP) _Export
$(TRIASDIR_R)\Export.ext:		$(R_EXPORTBASEDEP) _Export

_Export:
	$(MAKECMD) T3PROJECT=Export DOMAKEDIR=$(T3SRCBASE)\Export\Export

#############################################################################
# Diris-ASC

$(TRIASDIR_D)\DirisASCD.flt:	$(D_EXPORTBASEDEP) _DirisASC
$(TRIASDIR_R)\DirisASC.flt:		$(R_EXPORTBASEDEP) _DirisASC

_DirisASC:
	$(MAKECMD) T3PROJECT=DirisASC DOMAKEDIR=$(T3SRCBASE)\Export\DirisASC

#############################################################################
# Atlas-BNA

$(TRIASDIR_D)\AtlasBNAD.flt:	$(D_EXPORTBASEDEP) _AtlasBNA
$(TRIASDIR_R)\AtlasBNA.flt:		$(R_EXPORTBASEDEP) _AtlasBNA

_AtlasBNA:
	$(MAKECMD) T3PROJECT=AtlasBNA DOMAKEDIR=$(T3SRCBASE)\Export\AtlasBNA

#############################################################################
# Shape-Export

$(TRIASDIR_D)\ArcViewD.flt:		$(D_EXPORTBASEDEP) _ArcView
$(TRIASDIR_R)\ArcView.flt:		$(R_EXPORTBASEDEP) _ArcView

_ArcView:
	$(MAKECMD) T3PROJECT=ArcView DOMAKEDIR=$(T3SRCBASE)\Export\ArcView

#############################################################################
# ArcInfo-E00

$(TRIASDIR_D)\TRiASARCD.flt:	$(D_EXPORTBASEDEP) _TRiASARC
$(TRIASDIR_R)\TRiASARC.flt:		$(R_EXPORTBASEDEP) _TRiASARC

_TRiASARC:
	$(MAKECMD) T3PROJECT=TRiASARC DOMAKEDIR=$(T3SRCBASE)\Export\TRiASARC

#############################################################################
# Autocad-DXF

$(TRIASDIR_D)\AcadDXFD.flt:		$(D_EXPORTBASEDEP) _AcadDXF
$(TRIASDIR_R)\AcadDXF.flt:		$(R_EXPORTBASEDEP) _AcadDXF

_AcadDXF:
	$(MAKECMD) T3PROJECT=AcadDXF DOMAKEDIR=$(T3SRCBASE)\Export\AcadDXF

#############################################################################
# PolyGIS-PMF

$(TRIASDIR_D)\PolyGISPMFD.flt:		$(D_EXPORTBASEDEP) _PolyGISPMF
$(TRIASDIR_R)\PolyGISPMF.flt:		$(R_EXPORTBASEDEP) _PolyGISPMF

_PolyGISPMF:
	$(MAKECMD) T3PROJECT=PolygisPMF DOMAKEDIR=$(T3SRCBASE)\Export\PolyGISPMF

#############################################################################
# PolyGIS-DAT

$(TRIASDIR_D)\PolyGISDATD.flt:		$(D_EXPORTBASEDEP) _PolyGISDAT
$(TRIASDIR_R)\PolyGISDAT.flt:		$(R_EXPORTBASEDEP) _PolyGISDAT

_PolyGISDAT:
	$(MAKECMD) T3PROJECT=PolygisDAT DOMAKEDIR=$(T3SRCBASE)\Export\PolyGISDAT

#############################################################################
# BScript
#OLDMAKEDIR

BSCRIPTBASEDEP = IXtsnATL_ Container_ Ospace_ OspaceUSS_ 

D_BSCRIPTBASEDEP = $(BSCRIPTBASEDEP) \
	$(TRIASDIR_D)\daolayed.ebn \
	$(TRIASLIB)\Esnecild.lib \
	$(TRIASDIR_D)\objmand.dll

R_BSCRIPTBASEDEP = $(BSCRIPTBASEDEP) \
	$(TRIASDIR_R)\daolayer.ebn \
	$(TRIASLIB)\Esnecil.lib \
	$(TRIASDIR_R)\objman.dll 

$(TRIASDIR_D)\bscriptd.ext:	$(D_BSCRIPTBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\BS FINALTARGET=$@

$(TRIASDIR_R)\bscript.ext:	$(R_BSCRIPTBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\BS FINALTARGET=$@

#############################################################################
# Kompias
#OLDMAKEDIR

KOMPIASBASEDEP = IXtension_ Container_ Ospace_ OspaceUSS_ 

D_KOMPIASBASEDEP = $(KOMPIASBASEDEP) \
	$(TRIASLIB)\Esnecild.lib 

R_KOMPIASBASEDEP = $(KOMPIASBASEDEP) \
	$(TRIASLIB)\Esnecil.lib 

$(TRIASDIR_D)\TRiASIGM.ext:	$(D_KOMPIASBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\IGM\komp32 FINALTARGET=$@

$(TRIASDIR_R)\TRiASIGM.ext:	$(R_KOMPIASBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\IGM\komp32 FINALTARGET=$@

#############################################################################
# Tproject
#OLDMAKEDIR

TPROJECTBASEDEP = IXtension_ Container_ Ospace_ OspaceUSS_ 

D_TPROJECTBASEDEP = $(TPROJECTBASEDEP) 

R_KOMPIASBASEDEP = $(TPROJECTBASEDEP) 

$(TRIASDIR_D)\Tprojecd.ext:	$(D_TPROJECTBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Tproject\Tproj32 FINALTARGET=$@

$(TRIASDIR_R)\Tproject.ext:	$(R_TPROJECTBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Tproject\Tproj32 FINALTARGET=$@

#############################################################################
# Oleauto
#OLDMAKEDIR

D_OLEAUTOBASEDEP = \
	$(TRIASDIR_D)\bscriptd.ext \
	$(TRIASDIR_D)\visobjd.ext \
	$(TRIASDIR_D)\trias33d.dll \
	$(TRIASDIR_D)\Colorsd.ebn

R_OLEAUTOBASEDEP = \
	$(TRIASDIR_R)\bscript.ext \
	$(TRIASDIR_R)\visobj.ext \
	$(TRIASDIR_R)\trias323.dll \
	$(TRIASDIR_R)\Colors.ebn

$(TRIASDIR_D)\Oleautod.ext:	$(D_OLEAUTOBASEDEP) _ForceBuild 
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\OleAuto FINALTARGET=$@

$(TRIASDIR_R)\Oleauto.ext:	$(R_OLEAUTOBASEDEP) _ForceBuild 
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\OleAuto FINALTARGET=$@


#############################################################################
# ODBCExt

ODBCEXTBASEDEP = IXtsnATL_ Container_ Ospace_

D_ODBCEXTBASEDEP = $(ODBCEXTBASEDEP)
R_ODBCEXTBASEDEP = $(ODBCEXTBASEDEP)

$(TRIASDIR_D)\odbcextd.ext:		$(D_ODBCEXTBASEDEP) _ODBCExt
$(TRIASDIR_R)\odbcext.ext:		$(R_ODBCEXTBASEDEP) _ODBCExt

_ODBCExt:
	$(MAKECMD) T3PROJECT=ODBCExt DOMAKEDIR=$(T3SRCBASE)\XTension\ODBCExt

#############################################################################
# Identsdb
#OLDMAKEDIR

IDENTSDBBASEDEP = IXtension_ Ospace_ TFramework_ Container_ lol_ OleAuto_

D_IDENTSDBBASEDEP = $(IDENTSDBBASEDEP)
R_IDENTSDBBASEDEP = $(IDENTSDBBASEDEP)

$(TRIASDIR_D)\Identdbd.ext:	$(D_IDENTSDBBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Identsdb FINALTARGET=$@

$(TRIASDIR_R)\Identsdb.ext:	$(R_IDENTSDBBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Identsdb FINALTARGET=$@

#############################################################################
# Bilder
#OLDMAKEDIR

BILDERBASEDEP = IXtension_ Ospace_ TFramework_ Container_

D_BILDERBASEDEP = $(BILDERBASEDEP)
R_BILDERBASEDEP = $(BILDERBASEDEP)

$(TRIASDIR_D)\bilderd.ext:	$(D_BILDERBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Bilder FINALTARGET=$@

$(TRIASDIR_R)\bilder.ext:	$(R_BILDERBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Bilder FINALTARGET=$@

#############################################################################
# GeoStat
#OLDMAKEDIR

GEOSTATBASEDEP = IXtension_ Ospace_ TFramework_ Container_ OleAuto_

$(TRIASDIR_D)\geostatd.ext:	$(GEOSTATBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\GeoStat FINALTARGET=$@

$(TRIASDIR_R)\geostat.ext:	$(GEOSTATBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\GeoStat FINALTARGET=$@

#############################################################################
# Statist
#OLDMAKEDIR

STATISTBASEDEP = IXtsnWTLBase_ Ospace_ Container_ OleAuto_ FakeMFC_ 

$(TRIASDIR_D)\Statistd.ext:	$(STATISTBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Statist FINALTARGET=$@

$(TRIASDIR_R)\Statist.ext:	$(STATISTBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Statist FINALTARGET=$@

#############################################################################
# Maschbld
#OLDMAKEDIR

MASCBLDBASEDEP = IXtsnATL_ Ospace_ Container_

D_MASCBLDBASEDEP = $(MASCBLDBASEDEP) $(TRIASDIR_D)\Helperd.dll $(TRIASLIB)\triastld.lib
R_MASCBLDBASEDEP = $(MASCBLDBASEDEP) $(TRIASDIR_R)\Helper.dll $(TRIASLIB)\triastlb.lib

$(TRIASDIR_D)\Maschbld.ext:	$(D_MASCBLDBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\LinVer FINALTARGET=$@

$(TRIASDIR_R)\Maschblr.ext:	$(R_MASCBLDBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\LinVer FINALTARGET=$@

#############################################################################
# FakeMFC
#OLDMAKEDIR

FAKEMFCBASEDEP = Ospace_ OleAuto_

D_FAKEMFCBASEDEP = $(FAKEMFCBASEDEP) \
		$(TRIASDIR_D)\triasdbd.dll \
		$(TRIASLIB)\triastld.lib \
		$(TRIASLIB)\Esnecild.lib

R_FAKEMFCBASEDEP = $(FAKEMFCBASEDEP) \
		$(TRIASDIR_R)\triasdb.dll \
		$(TRIASLIB)\triastlb.lib \
		$(TRIASLIB)\Esnecil.lib

$(TRIASDIR_D)\fakemfcd.ext:		$(D_FAKEMFCBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\FakeMFC FINALTARGET=$@

$(TRIASDIR_R)\fakemfc.ext:		$(R_FAKEMFCBASEDEP) _ForceBuild
		$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\FakeMFC FINALTARGET=$@

#############################################################################
# DaoLayer

$(TRIASDIR_D)\Daolayed.ebn:		_DAOLayer
$(TRIASDIR_R)\Daolayer.ebn:		_DAOLayer

_DAOLayer:
	$(MAKECMD) T3PROJECT=DAOLayer DOMAKEDIR=$(T3SRCBASE)\XTension\DAOLayer

#############################################################################
# ArcTrias

ARCTRIASBASEDEP = _ArcTRiAS IXtension_ Container_ Ospace_ TFramework_

$(TRIASDIR_D)\arctriad.ext:	$(ARCTRIASBASEDEP)
$(TRIASDIR_R)\arctrias.ext:	$(ARCTRIASBASEDEP)

_ArcTRiAS:
	$(MAKECMD) T3PROJECT=ArcTRiAS DOMAKEDIR=$(T3SRCBASE)\XTension\ArcTRiAS

#############################################################################
# ASCimp
#OLDMAKEFILE

ASCIMPBASEDEP = IXtsnATLBase_

$(TRIASDIR_D)\ascimpd.ext:	$(ASCIMPBASEDEP) _ForceBuild 
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\XTension\ASCimp FINALTARGET=$@

$(TRIASDIR_R)\ascimp.ext:	$(ASCIMPBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\XTension\ASCimp FINALTARGET=$@

#############################################################################
# bnaimp
#OLDMAKEFILE

BNAIMPBASEDEP = IXtsnATLBase_

$(TRIASDIR_D)\bnaimpd.ext:	$(BNAIMPBASEDEP) _ForceBuild 
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\XTension\bnaimp FINALTARGET=$@

$(TRIASDIR_R)\bnaimp.ext:	$(BNAIMPBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\XTension\bnaimp FINALTARGET=$@

#############################################################################
# EDBSimp

EDBSIMPBASEDEP = IXtsnMFC_

$(TRIASDIR_D)\edbsimpd.ext:	$(EDBSIMPBASEDEP) _EDBSImp
$(TRIASDIR_R)\edbsimp.ext:	$(EDBSIMPBASEDEP) _EDBSImp

_EDBSImp:
	$(MAKECMD) T3PROJECT=EDBSImp DOMAKEDIR=$(T3SRCBASE)\XTension\EDBSImp

#############################################################################
# EDBSALk
#OLDMAKEFILE

EDBSALKBASEDEP = IXtsnMFC_

$(TRIASDIR_D)\edbsalkd.ext:	$(EDBSALKBASEDEP) 
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\XTension\EDBSAlk FINALTARGET=$@

$(TRIASDIR_R)\edbsalk.ext:	$(EDBSALKBASEDEP) 
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\XTension\EDBSAlk FINALTARGET=$@

#############################################################################
# DXFimp
#OLDMAKEFILE

DXFIMPBASEDEP = IXtension_

$(TRIASDIR_D)\dxfimpd.ext:	$(DXFIMPBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\DxfImp FINALTARGET=$@

$(TRIASDIR_R)\dxfimp.ext:	$(DXFIMPBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\DxfImp FINALTARGET=$@

#_DXFImp:	_ForceBuild
#	$(MAKECMD) T3PROJECT=DXFimp DOMAKEDIR=$(T3SRCBASE)\XTension\DXFimp

#############################################################################
# UnRegTRiAS

UNREGTRIASBASEDEP = TFramework_

$(TRIASDIR_D)\UnRegTRiASd.exe:		_UnRegTRiAS 
$(TRIASDIR_R)\UnRegTRiAS.exe:		_UnRegTRiAS

_UnRegTRiAS:	$(UNREGTRIASBASEDEP)
	$(MAKECMD) T3PROJECT=UnRegTRiAS DOMAKEDIR=$(T3SRCBASE)\TRiAS\UnRegTRiAS

#############################################################################
# TRSABiS

$(TRIASDIR_D)\TRSABiSd.ext:		_TRSABiS 
$(TRIASDIR_R)\TRSABiS.ext:		_TRSABiS

_TRSABiS:	$(TRSABISBASEDEP)
	$(MAKECMD) T3PROJECT=TRSABIS DOMAKEDIR=$(T3SRCBASE)\TRiAS\Xtension\TRSABiS

#############################################################################
# Splitting
#OLDMAKEFILE

SPLITTINGBASEDEP = IXtsnATLBase_

$(TRIASDIR_D)\splittid.ext:	$(SPLITTINGBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Splitting FINALTARGET=$@

$(TRIASDIR_R)\Splitting.ext:	$(SPLITTINGBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\Splitting FINALTARGET=$@

#############################################################################
# LineTools
#OLDMAKEFILE

LINETOOLSBASEDEP = IXtsnATLBase_

$(TRIASDIR_D)\LineToold.ext:	$(LINETOOLSBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\LineTools FINALTARGET=$@

$(TRIASDIR_R)\LineTools.ext:	$(LINETOOLSBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\LineTools FINALTARGET=$@


#############################################################################
# LoadableCommands
#OLDMAKEFILE

LOADABLECOMMANDSBASEDEP = IXtsnWTLBase_

$(TRIASDIR_D)\LoadableCommandsd.ext:	$(LOADABLECOMMANDSBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\LoadableCommands FINALTARGET=$@

$(TRIASDIR_R)\LoadableCommands.ext:	$(LOADABLECOMMANDSBASEDEP) _ForceBuild
	$(MAKECMD) OLDMAKEDIR=$(T3SRCBASE)\Xtension\LoadableCommands FINALTARGET=$@

