/*
@doc
@contents1 Inhaltsverzeichnis | Um eine Liste der Kapitel nach
ihrer Kategorie anzuzeigen, müssen Sie auf einen der folgenden Kapiteleinträge
klicken. Um eine alphabetische Liste der Kapitel anzuzeigen, wählen Sie die Index - 
Schaltfläche.

@head3 Übersichten |

@subindex Übersichten

@head3 COM Elemente |

@subindex Objekte
@subindex Objektinterfaces

@head3 Sonstiges |

@subindex Datenstrukturen
@subindex Enumerationen
@subindex Konstanten
@subindex Beispiele
@subindex Objekteigenschaften
@subindex Objektmethoden

@normal Diese Hilfedatei wurde erzeugt am: <date>

@subindex Über diese Hilfedatei

***********************************************************************
@contents2 Übersichten |
@index topic |

***********************************************************************
@contents2 Objekte |
@normal <tr>- Koordinatensystemobjekte
@index object | (OBJECT & TRIASCS)

***********************************************************************
@contents2 Objektinterfaces |
@normal Interfaces der <tr>- Koordinatensystemobjekte
@index interface | (INTERFACE & TRIASCS)

***********************************************************************
@contents2 Objektmethoden |
@normal Alle Methoden auf einen Blick
@index method | (METHOD & TRIASCS)

***********************************************************************
@contents2 Objekteigenschaften |
@normal Alle Properties auf einen Blick
@index property | (PROPERTY & TRIASCS)

***********************************************************************
@contents2 Datenstrukturen |
@normal Datenstrukturen
@index struct | (STRUCT & TRIASCS)

***********************************************************************
@contents2 Enumerationen |
@normal Aufzählungstypen
@index enum | (ENUM & TRIASCS)

***********************************************************************
@contents2 Konstanten |
@normal Konstanten
@index constv | 

***********************************************************************
@contents2 Beispiele |
@index | EXAMPLES

***********************************************************************
@topic Setzen / Lesen von Parametern |
kann man auch machen...

***********************************************************************
@contents2 Über diese Hilfedatei | 

Copyright<csign> 1991-2000 <company>, #<copyright> V<version>
<nl>For more information about TRiASCs, contact Hartmut Kaiser (H.Kaiser@intertrias.com)

<nl>The sources for this Help file were generated
by Autoduck, the source code documentation tool that generates Print or
Help files from tagged comments in C, C++, Assembly, and Basic source
files.
<nl>For more information about Autoduck, contact Eric Artzt (erica@microsoft.com).

***********************************************************************/
include(`TRiASCS.idl')

/***********************************************************************
include(`epsg.h')
include(`triascs.hmc')

***********************************************************************
@doc EXAMPLES 
@topic Koordinatentransformation - Geodätisch zu Gauß-Krüger | 
@ex Koordinatentransformation - Geodätisch zu Gauß-Krüger | include(`vb/GeoZuGau.bas')
@topic Speichern / Lesen von Koordinatensystemen | 
@ex Speichern / Lesen von Koordinatensystemen | include(`vb/CSSet.bas')
@topic Ermitteln eines guten Containers | 
@ex Ermitteln eines guten Containers | include(`vb/ModTestGoodEnvelope.bas')
@head2 Hinweise: |
@head3 Per Rechner definierte Geometrie |
@normal
<nl>[HKEY_LOCAL_MACHINE\SOFTWARE\FEZ\TRiAS\3.0\CoordinateSystems\DefaultEnvelope]
<nl>@="Deutschland gesamt, WGS84, Dezimalgrad"
<nl>"XMin"="6"
<nl>"XMax"="15"
<nl>"YMin"="40"
<nl>"YMax"="55"
@head3 Per Nutzer definierte Geometrie |
@normal
<nl>[HKEY_CURRENT_USER\Software\FEZ\TRiAS\CoordinateSystems\DefaultEnvelope]
<nl>@="Deutschland gesamt, WGS84, Dezimalgrad"
<nl>"XMin"="6"
<nl>"XMax"="15"
<nl>"YMin"="40"
<nl>"YMax"="55"
@normal Sofern unter HKCR... keine Geometrie eingetragen ist wird diese aus HKLM...
	übernommen. Somit wird gesichert daß GetGoodEnvelope auf jeden Fall sinnvolle Werte
	liefert. Außerdem ist eine nutzerspezifische Anpassung möglich indem unter HKCU... z.B. 
	der eigene Landkreis eingetragen wird.
***********************************************************************/

include(`Help/Koordinatentransformation.d')
