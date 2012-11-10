.SILENT:
###############################################################################
# @doc VERSION TRIAS
# @topic Standard-Versionskontrolle für TRiAS-Erweiterungen / COM-Objekte / DLL's usw.
# @normal TRiASVerEx.mak stellt Mechanismen zur standardisierten
#	Versionskontrolle von TRiAS-Modulen (Erweiterungen, COM-Objekte usw.)
#	bereit.

###############################################################################
# Das sind unsere Templates

TPL_VER			= $(TRIASINCLUDE)\TRiAS.ver.tpl
TPL_RCV			= $(TRIASINCLUDE)\TRiAS.rcv.tpl
TPL_DEF			= $(TRIASINCLUDE)\TRiAS.def.tpl
REPLACE			= ersetz
TRIASVERFILE	= $(TRIASINCLUDE)\TRiASVer.mak		# die eigentlichen Versionsnummern
THIS_FILE		= $(TRIASINCLUDE)\TRiASVerEx.mak
COPY			= xcopy /F

###############################################################################
# das ist die TRiAS-Version (kompatibel mit alten Makefiles)

!include	<TRiASVER.mak>

!if !defined(TRIAS_PNAME)
!error "Makro TRIAS_PNAME nicht definiert (siehe TRiASVER.mak)"
!endif

!if !defined(TRIAS_PADDRESS)
!error "Makro TRIAS_PADDRESS nicht definiert (siehe TRiASVER.mak)"
!endif

!if !defined(COMPANYNAME)
!error "Makro COMPANYNAME nicht definiert (siehe TRiASVER.mak)"
!endif

###############################################################################
# wir gucken mal, ob der Aufrufer auch alles angegeben hat...

!if !defined(APP_COMPANY) || "$(APP_COMPANY)" == ""
APP_COMPANY = $(COMPANYNAME)
!endif

!if !defined(APP_SHORT)
!error "Makro APP_SHORT nicht definiert (gibt den DLL-Namen des Moduls an)"
!endif

!if !defined(APP_LONG) || "$(APP_LONG)" == ""
!error "Makro APP_LONG nicht definiert (gibt eine etwas längere Beschreibung des Moduls an)"
!endif

!if !defined(APP_YEAR) || "$(APP_YEAR)" == ""
!error "Makro APP_YEAR nicht definiert (gibt den Bearbeitungszeitraum des Moduls an)"
!endif

!if !defined(APP_COPYRIGHT) || "$(APP_COPYRIGHT)" == ""
!error "Makro APP_COPYRIGHT nicht definiert (gibt das Copyright des Moduls an)"
!endif

!if !defined(APP_VERSION) || "$(APP_VERSION)" == ""
!error "Makro APP_VERSION nicht definiert (gibt die Versionsnummer des Moduls an)"
!endif

!if !defined(APP_RELEASE) || "$(APP_RELEASE)" == ""
!error "Makro APP_RELEASE nicht definiert (gibt den Release-Level des Moduls an)"
!endif

!if !defined(APP_BUILD) || "$(APP_BUILD)" == ""
!error "Makro APP_BUILD nicht definiert (gibt den Build des Moduls an)"
!endif

!if !defined(APP_TLB_MINOR) || "$(APP_TLB_MINOR)" == ""
!error "Makro APP_TLB_MINOR nicht definiert (gibt die Minor-Version der Typelibrary des Moduls an)"
!endif

!if !defined(APP_TLB_MAJOR) || "$(APP_TLB_MAJOR)" == ""
!error "Makro APP_TLB_MINOR nicht definiert (gibt die Major-Version der Typelibrary des Moduls an)"
!endif

!if !defined(TRIASDOC) || "$(TRIASDOC)" == ""
!error "Umgebungsvariable TRIASDOC nicht definiert (gibt den Standort der zu erzeugenden Dokumentation an)"
!endif

!if !defined(TRIASTLB) || "$(TRIASTLB)" == ""
!error "Umgebungsvariable TRIASTLB nicht definiert (gibt den Standort der zu erzeugenden Typelibrary an)"
!endif

!if !defined(TRIAS_LANGUAGE) || "$(TRIAS_LANGUAGE)" == ""
!error "Umgebungsvariable TRIAS_LANGUAGE nicht definiert (gibt die aktuell zu erzeugende Sprachversion an)"
!endif

#Creating command line "rc.exe /l 0x407 /fo"_Debug/TRiASMDS.res" /d "_DEBUG" "E:\Entwickl\TRiASDB\TRiASMDS\TRiASMDS.rc"" 
###############################################################################
# CFG=... in der Aufrufzeile ist wegen der folgenden Definitionen notwendig:

!if defined(RC_DEFINES)
RC_DEFINES = /d $(RC_DEFINES)
!endif

!if "$(CFG)" == "_DEBUG" || "$(CFG)" == "_DEBUGMT"
RC=rc.exe /l $(TRIAS_LANGUAGE) /d "LANGUAGE_$(TRIAS_LANGUAGE)" /d "_DEBUG" $(RC_DEFINES)
!else if "$(CFG)" == "NDEBUG" || "$(CFG)" == "NDEBUGMT"
RC=rc.exe /l $(TRIAS_LANGUAGE) /d "LANGUAGE_$(TRIAS_LANGUAGE)" /d "NDEBUG" $(RC_DEFINES)
!else
!error "Bitte _DEBUG oder NDEBUG definieren! (z.B.: 'nmake -nologo -f Version.mak CFG=_DEBUG')"
!endif

###############################################################################
# SOURCE_FILES=... kann definiert werden um generelle Abhängigkeiten für
# Version.mak zu schaffen. 
# ==> Ist nichts angegeben, Standard definieren.

!if !defined(SOURCE_FILES) || "$(SOURCE_FILES)" == ""
SOURCE_FILES = *.cpp *.rc *.rgs
!endif

###############################################################################
# Die Dokumentation ist generell abhängig von .\help\$(APP_SHORT).d
# Mit DOC_FILES können zusätzliche Abhängigkeiten angegeben werden

!if !defined(DOC_FILES) || "$(DOC_FILES)" == ""
DOC_FILES =
!endif

###############################################################################
# Mit IDL_FILES können zusätzliche Abhängigkeiten für die $(APP_SHORT).idl 
# Datei angegeben werden

!if !defined(IDL_FILES) || "$(IDL_FILES)" == ""
IDL_FILES =
!endif

###############################################################################
# Die Standard-Targets für ein COM-Objekt

_APP_VERSION	= $(APP_SHORT).rcv $(APP_SHORT).def $(APP_SHORT).ver
_APP_TYPELIB	= $(TRIASTLB)\$(APP_SHORT).tlb
_APP_DOC		= $(TRIASDOC)\$(APP_SHORT).hlp
_APP_RESOURCE	= $(OUTDIR)\$(APP_SHORT).res
_APP_MESSAGES	= .\$(APP_SHORT).hmc

###############################################################################
# Kompatibilität mit älteren Modulen die keine Doku/TLB kennen

!if defined(NO_DOCUMENTATION)
_APP_DOC		= 
!endif
!if defined(NO_TYPELIBRARY)
_APP_TYPELIB	=
!endif
!if defined(NO_HELPMESSAGES)
_APP_MESSAGES	=
!endif

###############################################################################
# VERDIR wird intern gebraucht

VERDIR		=_Version

###############################################################################
# Die Wurzel allen Übels...

default:	$(_APP_VERSION) $(_APP_TYPELIB) $(APP_SHORT).tlb $(_APP_MESSAGES) $(_APP_DOC)

# ...und jetzt die Einzelheiten:
###############################################################################

###############################################################################
# (1) Typelibrary
# nur dann neu erzeugen, wenn sich wirklich was (nicht nur Kommentare) geändert hat

$(_APP_TYPELIB):	$(VERDIR) $(VERDIR)\$(APP_SHORT).tlb
	if not exist $@ nmake -nologo -f Version.mak __COPY_TYPELIBRARY_OUT__
#	nmake -nologo -f Version.mak __COPY_TYPELIBRARY_OUT__

$(APP_SHORT).tlb:	$(VERDIR) $(VERDIR)\$(APP_SHORT).tlb
	nmake -nologo -f Version.mak __COPY_TYPELIBRARY_INTERNAL__

$(VERDIR)\$(APP_SHORT).tlb:	$(VERDIR)\$(APP_SHORT).idy $(VERDIR)\$(APP_SHORT).idz

$(VERDIR)\$(APP_SHORT).idy:	$(APP_SHORT).idl $(IDL_FILES)
	if not exist $(VERDIR)\$(APP_SHORT).idz nmake -nologo -f Version.mak __FORCE_TYPELIBRARY__
	cl -nologo -E $(APP_SHORT).idl > $(VERDIR)\$(APP_SHORT).idy
	IsDifferent $(VERDIR)\$(APP_SHORT).idy $(VERDIR)\$(APP_SHORT).idz "nmake -nologo -f Version.mak __FORCE_TYPELIBRARY__"

$(VERDIR)\$(APP_SHORT).idz:	$(VERDIR)\$(APP_SHORT).idy
	copy $(VERDIR)\$(APP_SHORT).idy $@

__FORCE_TYPELIBRARY__:
	IncVer Version.mak
	cl -nologo -E $(APP_SHORT).idl > $(VERDIR)\$(APP_SHORT).idz
	nmake -nologo -f Version.mak __BUILD_TYPELIBRARY__
	nmake -nologo -f Version.mak __COPY_TYPELIBRARY_OUT__

__BUILD_TYPELIBRARY__:
	nmake -nologo -f Version.mak $(_APP_VERSION)
	midl /nologo /Oicf /tlb "$(VERDIR)\$(APP_SHORT).tlb" /h "$(VERDIR)\$(APP_SHORT).h" "$(APP_SHORT).idl"
	nmake -nologo -f Version.mak __COPY_TYPELIBRARY_INTERNAL__

__COPY_TYPELIBRARY_INTERNAL__:
	BinCat $(VERDIR)\$(APP_SHORT).h > $(APP_SHORT).h
	BinCat $(VERDIR)\$(APP_SHORT).tlb > $(APP_SHORT).tlb
	nmake -nologo -f Version.mak __BUILD_RESOURCES__

__COPY_TYPELIBRARY_OUT__:
	@echo $(THIS_FILE): Generating external typelibrary $(TRIASTLB)\$(APP_SHORT).tlb
	BinCat "$(VERDIR)\$(APP_SHORT).tlb" > $(TRIASTLB)\$(APP_SHORT).tlb

__BUILD_RESOURCES__:	$(_APP_VERSION) .\$(APP_SHORT).hmc
	@echo $(THIS_FILE): Compiling Resources with LANGUAGE_$(TRIAS_LANGUAGE)
	$(RC) /fo"$(_APP_RESOURCE)" "$(APP_SHORT).rc"

###############################################################################
# (1a) Versionsverzeichnis für Typelibrarycheck
$(VERDIR):
	if not exist $(VERDIR)\NUL mkdir $(VERDIR)\

###############################################################################
# (2) Versionsnummer (inkl. Buildnummer)
# ist abhängig von Änderungen in den Quelldateien...

VERSION:	Version.mak $(TRIASVERFILE)
	nmake -nologo -f Version.mak MTCFG=$(MTCFG) clean
	nmake -nologo -f Version.mak $(_APP_VERSION)
	nmake -nologo -f Version.mak __BUILD_RESOURCES__

Version.mak: $(SOURCE_FILES)
	nmake -nologo -f Version.mak __INC_VERSION__

__INC_VERSION__:
	@echo $(THIS_FILE): Incrementing Build Number
	IncVer Version.mak
	
###############################################################################
# Dokumentation

__DOCFILES__ = .\help\$(APP_SHORT).d $(DOC_FILES)

$(_APP_DOC):	$(__DOCFILES__)
	@echo $(THIS_FILE): Generating Documentation
	if not exist .\Help mkdir .\Help
	m4 help\$(APP_SHORT).d > help/contents.cpp 
	autoduck /s $(TRIASINCLUDE)\help\TRiASDB.Fmt /rh /t4 /o .\help\$(APP_SHORT).rtf /L .\help\contents.log .\help\contents.cpp 
	hcrtf /a /o .\help\$(APP_SHORT).hlp /xn .\help\$(APP_SHORT).hpj 
	$(COPY) .\help\$(APP_SHORT).hlp $(TRIASINCLUDE)\help\

###############################################################################
# Message-Tabellen

.\$(APP_SHORT).hmc:	$(APP_SHORT).mc
	@echo $(THIS_FILE): Generating Message Files
	if not exist .\Help mkdir .\Help
	m4 -I%TRIASINCLUDE%\help $(APP_SHORT).mc > .\help\$(APP_SHORT).i  
	cl -nologo -EP -C .\help\$(APP_SHORT).i > .\help\$(APP_SHORT).ii  
	mc -e hmc -r "res" ".\help\$(APP_SHORT).ii"  
	-erase .\help\$(APP_SHORT).i
	-erase .\help\$(APP_SHORT).ii

###############################################################################
# ein kleiner Helfer ;-))

clean:
	-erase $(APP_SHORT).rcv
	-erase $(APP_SHORT).def
	-erase $(APP_SHORT).ver

A_=$(APP_VERSION)
B_=$(APP_RELEASE)
C_=$(APP_BUILD)
D_=$(APP_TLB_MAJOR)
E_=$(APP_TLB_MINOR)
F_=$(APP_COPYRIGHT)
G_=$(TRIAS_PNAME)
H_=$(TRIAS_PADDRESS)
I_=$(TRIAS_VERSION)
J_=$(TRIAS_RELEASE)
K_=$(APP_COMPANY)
L_=$(APP_SHORT)
M_=$(APP_LONG)
N_=$(APP_YEAR)
O_=$(TRIAS_VERSION)
P_=$(TRIAS_RELEASE)
Q_=$(TRIAS_BUILD)

###############################################################################
# G_ => TRIAS_PNAME, H_ => TRIAS_PADDRESS, K_ => APP_COMPANY kommen aus TRiASVer.mak,
# sind dort gequoted und dürfen hier nicht nochmal gequoted werden

REPLACEARGS="$(A_)" "$(B_)" "$(C_)" "$(D_)" \
			"$(E_)" "$(F_)" $(G_) $(H_) \
			"$(I_)" "$(J_)" $(K_) "$(L_)" \
			"$(M_)" "$(N_)" "$(O_)" "$(P_)" \
			"$(Q_)" "$(R_)" "$(S_)" "$(T_)" 

###############################################################################
# Versionsresource

$(APP_SHORT).rcv:	$(VERFILES) $(TPL_RCV)
	@echo $(THIS_FILE): Generating $@ $(APP_VERSION).$(APP_RELEASE).$(APP_BUILD) / $(TRIAS_LANGUAGE)
	@$(REPLACE) $(REPLACEARGS) $(TPL_RCV) $@

###############################################################################
# .def-File

$(APP_SHORT).def:	$(VERFILES) $(TPL_DEF)
	@echo $(THIS_FILE): Generating $@ $(APP_VERSION).$(APP_RELEASE).$(APP_BUILD) / $(TRIAS_LANGUAGE)
	@$(REPLACE) $(REPLACEARGS) $(TPL_DEF) $@

###############################################################################
# Versionsinclude

$(APP_SHORT).ver:	$(VERFILES) $(TPL_VER)
	@echo $(THIS_FILE): Generating $@ $(APP_VERSION).$(APP_RELEASE).$(APP_BUILD) / $(TRIAS_LANGUAGE)
	@$(REPLACE) $(REPLACEARGS) $(TPL_VER) $@
