########################################################################################
#	Kontrolle und Verwaltung versionsabhängiger Informationen für TRiAS-Projekte
#
#	(1) Targets
#
#		----- allgemeine Versionsdatei -----
#			$(PROJECTDIR)/$(APP_SHORT).ver
#				aus $(PROJECTDIR)/Version.mak und $(TRIASINCLUDE)/TRiAS.ver.tpl
#
#		----- Versionsresource -----
#			$(PROJECTDIR)/$(APP_SHORT).rcv
#				aus $(PROJECTDIR)/Version.mak und $(TRIASINCLUDE)/TRiAS.rcv.tpl
#
#		----- Definitionsdatei für Linker -----
#			$(PROJECTDIR)/$(APP_SHORT).def
#				aus $(PROJECTDIR)/Version.mak und $(TRIASINCLUDE)/TRiAS.def.tpl
#
#		----- Message-Strings -----
#			$(PROJECTDIR)/$(APP_SHORT).hmc
#				aus $(PROJECTDIR)/$(APP_SHORT).mc
#
#		----- Typelibrary -----
#			$(PROJECTDIR)/$(APP_SHORT).tlb
#			$(TRIASTLB)/$(APP_SHORT).tlb
#				aus $(PROJECTDIR)/$(APP_SHORT).idl
#
#		----- Hilfedatei -----
#			$(PROJECTDIR)/help/$(APP_SHORT).hlp
#			$(TRIASDOC)/$(APP_SHORT).hlp
#				aus $(PROJECTDIR)/help/$(APP_SHORT).d
#
#	(2) Benutzte Umgebungsvariablen
#
#		TRIASINCLUDE	- Include-Verzeichnis für TRiAS - Header
#		TRIASLIB		- Verzeichnis für TRiAS - Bibliotheken
#		TRIASTLB		- Verzeichnis für erzeugte Typelibraries
#		TRIASDOC		- Verzeichnis für erzeugte Hilfedateien
#		TRIASDIR_R		- Verzeichnis für Release-Build
#		TRIASDIR_D		- Verzeichnis für Debug-Build
#
#	(3) Benötige Binaries (unter Source-Safe, 'Required Binaries')
#
#		Ersetz.exe		- Ersetzen von Variablen
#		IncVer.exe		- Erhöhen der Buildnummer in Version.mak
#		m4.exe			- eben der geniale m4 ;-)
#		mc.exe			- Message-Compiler
#		IsDifferent.exe	- Überprüfen ob zwei IDL-Dateien Unterschiede aufweisen
#		BinCat.exe		- Binäres kopieren von Dateien
#
#	(4) Hinweise
#
#		- Version.mak resp. TRiASVerEx.mak arbeiten nur sinnvoll wenn im Projekt
#		  bestimmte Abhängigkeiten eingetragen sind. Diese Abhängigkeiten
#		  können mit dem Makro 'TRiASVerEx.dsm' erzeugt werden.
#		  - Voraussetzungen:
#			o Existenz der folgenden Konfigurationen:
#				Release
#				Debug
#			o Existenz der folgenden Dateien:
#				$(PROJECTDIR)/Version.mak
#				$(PROJECTDIR)/$(APP_SHORT).mc
#				$(PROJECTDIR)/$(APP_SHORT).idl
#				$(PROJECTDIR)/help/$(APP_SHORT).d
#		  - Eine Abhängigkeit muß im 'Pre-Link-Step' von Hand eingetragen werden:
#				nmake -nologo -f Version.mak CFG=_DEBUG VERSION		# für Debug
#				nmake -nologo -f Version.mak CFG=NDEBUG VERSION		# für Release
#		- Die Versionsresource '$(APP_SHORT).rcv' sollte als 'Include' in die
#		  Resourcendatei eingebunden werden (im DevStudio: View->Resource Includes).
#
########################################################################################
!include <TRiASVerLang.mak>
########################################################################################
# Hier die Kurzbezeichnung für das Projekt eintragen
APP_SHORT		= PolygisPMF
########################################################################################
# Hier die Langbezeichnung für das Projekt eintragen
!if "0x0407" == "$(TRIAS_LANGUAGE)"
APP_LONG		= Exportfilter - PolyGIS - PMF
!else if "0x0409" == "$(TRIAS_LANGUAGE)"
APP_LONG		= Exportfilter - PolyGIS - PMF
!else
!error "Undefined Build-Language"
!endif
########################################################################################
# Hier eintragen welches Jahr / welche Jahre an dem Projekt gearbeitet wurde
APP_YEAR		= 1999-2003
########################################################################################
# Wer ist denn derjenige, der dieses Projekt verzapft hat?
APP_COPYRIGHT	= KK040510
########################################################################################
# Die Major-Versionsnummer des Projektes
APP_VERSION		= 1
########################################################################################
# Die Minor-Versionsnummer des Projektes
APP_RELEASE		= 0
########################################################################################
# Die aktuelle Build-Nummer des Projektes; diese Nummer wird automatisch hochgezählt
APP_BUILD	= 191
########################################################################################
# Die Major-Versionsnummer der Typelibrary
APP_TLB_MAJOR	= 1
########################################################################################
# Die Minor-Versionsnummer der Typelibrary
APP_TLB_MINOR	= 0
########################################################################################
# welche Dateien sollen dafür zuständig sein bei Änderungen eine Erhöhung der 
# Build-Nummer zu veranlassen?
SOURCE_FILES = *.cpp *.rc *.rgs
########################################################################################
# welche Dateien sollen dafür zuständig sein bei Änderungen eine Neugenerierung der
# Hilfedatei zu veranlassen?
DOC_FILES		=
########################################################################################
# Und der hier ist eigentlich für die Versionskontrolle zuständig...
!include <triasverEx.mak>
