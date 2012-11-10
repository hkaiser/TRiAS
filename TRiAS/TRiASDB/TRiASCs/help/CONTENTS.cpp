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
// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.09.2000 11:11:50 
//
// @doc
// @module TRiASCs.idl | Definitionen und Konstanten für TRiAS - Koordinatensysteme

import "wtypes.idl";
import "oaidl.idl";
import "ocidl.idl";

import "SpatialReference.idl";

#include <idl/Collection.idl>

#include "TRiASCS.ver"
#include <TRiASCs.hh>


#define TYPELIB_TRiASCS_HELPFILE_NAME "TRiASCs.hlp"

///////////////////////////////////////////////////////////////////////////////
// forward decls only
interface ITRiASCSSet;
interface ITRiASCSDatumTransformation;
interface ITRiASCSPCS;
interface ITRiASCSGCS;
interface ITRiASCS;
interface ITRiASCSTransform;

interface ITRiASCSEvents;

interface ITRiASRawCoordTransform;

//interface ITRiASCSStorageManager;

interface ITRiASCSUIService;
interface ITRiASCSTransformService;
#if defined(_USE_WKTSERVICE)
interface ITRiASCSWktService;
#endif // defined(_USE_WKTSERVICE)

///////////////////////////////////////////////////////////////////////////////
//     Geographic_CS              =  Angular_Unit + Geodetic_Datum + Prime_Meridian
//     Projected_CS               =  Geographic_CS + Projection
//     Projection                 =  Linear Unit + Coord_Transf_Method + Coord_Transform_Parameters 
//     Coord_Transform_Method     = { TransverseMercator | LambertCC | ...}
//     Coord_Transform_Parameters = { OriginLatitude + StandardParallel + ...}
///////////////////////////////////////////////////////////////////////////////

typedef [public, v1_enum] enum CODETYPE {
	tcsCType_Undefined = -1,
	tcsCType_Storage = 0,		// Koordinatensystemtyp (Projected, Geografic ...)
	tcsCType_Ellipsoid = 21,	// Bezugsellipsoid (Bessel, Krassovsky ...)
	tcsCType_GD = 23,			// geod. Datum (DHDN, Pulkovo42 ...)
	tcsCType_PM = 25,
	tcsCType_UOA = 41,
	tcsCType_UOL = 43,
	tcsCType_PA = 3310,
	tcsCType_DT = 3320,
	tcsCType_EllipsOfGD = 32769,
} CODETYPE;

typedef [public, v1_enum] enum TCS_REGISTRYROOT {
	TCS_HKCR = 1,
	TCS_HKLM = 2,
	TCS_HKCU = 3,
	TCS_HKCC = 4,
	TCS_HKU = 5,
} TCS_REGISTRYROOT;

cpp_quote("#define	TCS_PARAMETER_INRANGE(idx) ((idx) >= 0 && (idx) < tcsPP_SizeOfParameterSet)")
cpp_quote("#include	\"TRiASCS.hmc\"")

///////////////////////////////////////////////////////////////////////////////
// @doc INTERFACE TRIASCS
// @interface ITRiASCSDistanceService | Über dieses Interface sind diverse Berechnungen
// verfügbar, die sich auf die Berechnung des Abstandes zwischen 2 Koordinatenpunkten
// zurückführen lassen.
// @group Eigenschaften von <i ITRiASCSDistanceService>
// @index | ITRIASCSDISTANCESERVICE & PROPERTY
// @group Methoden von <i ITRiASCSDistanceService>
// @index | ITRIASCSDISTANCESERVICE & METHOD
// @doc ITRIASCSDISTANCESERVICE
[
	object,
	uuid(F6081608-368A-4F75-AB99-4DC4823D2E4B),
	dual,
	helpstring("ITRiASCSDistanceService Interface"),
	pointer_default(unique),
	helpcontext(ITRiASCSDistanceService_int)
]
interface ITRiASCSDistanceService : IDispatch
{
cpp_quote("#if !defined(_ACCURACY_DEFINED)")
cpp_quote("#define _ACCURACY_DEFINED")
// @doc ACCURACYENUMS 
// @enum DIST_ACCURACY | Die Genauigkeitsgrundlage auf der die Berechnungen über das Objekt
// <o TRiASCsDistanceService> durchgeführt werden.
// @xref <i ITRiASCSDistanceService>, <om ITRiASCSDistanceService.GetDistancePts>
	typedef [
		public, 
		v1_enum, 
		helpstring("Genauigkeitsgrundlage der Entfernungsberechnungen"),
		helpcontext(ACCURACY_enum)
	]
	enum _tagACCURACY {
		[helpstring("Die Genauigkeit der Berechnungen ist nicht definiert"), helpcontext(ACCURACY_enum)]
			ACCURACY_Unknown = 0,		// Die Genauigkeit der Berechnungen ist nicht definiert.
		[helpstring("Die Berechnungen werden in der Ebene durchgeführt"), helpcontext(ACCURACY_enum)]
			ACCURACY_Planar = 10,		// @emem Die Berechnungen werden in der Ebene durchgeführt.

		[hidden, restricted, helpstring("Die Berechnungen werden auf die Kugel bezogen (große Halbachse)")]
			ACCURACY_SphericMajorAxis = 20,		// Die Berechnungen werden auf die Kugel bezogen, deren 
				// Radius identisch mit der großen Halbachse des Bezugsellipsoides ist.
		[hidden, restricted, helpstring("Die Berechnungen werden auf die Kugel bezogen (arithmetischer Mittelwert der Halbachsen)")]
			ACCURACY_SphericArithMean = 21,		// Die Berechnungen werden auf die Kugel bezogen, deren 
				// Radius sich aus dem arithmetischen Mittelwert der großen und kleinen Halbachsen des Bezugsellipsoides
				// berechnet.
		[hidden, restricted, helpstring("Die Berechnungen werden auf die Kugel bezogen (geometrischer Mittelwert der Halbachsen)")]
			ACCURACY_SphericGeomMean = 22,		// Die Berechnungen werden auf die Kugel bezogen, deren 
				// Radius sich aus dem geometrischen Mittelwert der großen und kleinen Halbachsen des Bezugsellipsoides
				// berechnet.
		[hidden, restricted, helpstring("Die Berechnungen werden auf die Kugel bezogen (harmonischer Mittelwert der Halbachsen)")]
			ACCURACY_SphericHarmMean = 23,		// Die Berechnungen werden auf die Kugel bezogen, deren 
				// Radius sich aus dem harmonischen Mittelwert der großen und kleinen Halbachsen des Bezugsellipsoides
				// berechnet.
		[hidden, restricted, helpstring("Die Berechnungen werden auf die Kugel bezogen (Kugel mit identischem Volumen wie Ellipsoid)")]
			ACCURACY_SphericVolume = 24,		// Die Berechnungen werden auf die Kugel bezogen, deren 
				// Volumen identisch zu dem Volumen des durch die große und kleine Halbachsen gebildeten Bezugsellipsoiden
				// ist.
		[hidden, restricted, helpstring("Die Berechnungen werden auf die Kugel bezogen (Kugel mit identischem Volumen wie Ellipsoid)")]
			ACCURACY_SphericArea = 25,			// Die Berechnungen werden auf die Kugel bezogen, deren 
				// Oberfläche identisch zu der Oberfläche des durch die große und kleine Halbachsen gebildeten Bezugsellipsoiden
				// ist.
		[hidden, restricted, helpstring("Die Berechnungen werden auf die Kugel bezogen (gemetrischer Mittelwert der Krümmungsradien)")]
			ACCURACY_SphericGeomMeanCurvatureRadii = 26,			// Die Berechnungen werden auf die Kugel bezogen, deren 
				// Radius sich aus dem geometrischen Mittel des Meridiankrümmungsradiuses und des 
				// Querkrümmungsradiuses berechnet.

		[helpstring("Die Berechnungen werden auf die Kugel bezogen"), helpcontext(ACCURACY_enum)]
			ACCURACY_Spheric = ACCURACY_SphericGeomMeanCurvatureRadii,		// @emem Die Berechnungen werden auf die Kugel bezogen, deren 
				// Radius sich aus dem Mittelwert der großen und kleinen Halbachsen des Bezugsellipsoides
				// der Koordinaten berechnet.

		[hidden, restricted, helpstring("Die Berechnungen werden auf dem Bezugsellipsoiden durchgeführt (Algorithmus 1)")]
			ACCURACY_Ellipsoidal1 = 30,	// Die Berechnungen werden auf dem Bezugsellipsoiden
				// durchgeführt, auf welches die Koordinaten bezogen sind (forward/inverse).
		[hidden, restricted, helpstring("Die Berechnungen werden auf dem Bezugsellipsoiden durchgeführt (Algorithmus 2)")]
			ACCURACY_Ellipsoidal2 = 31,	// Die Berechnungen werden auf dem Bezugsellipsoiden
				// durchgeführt, auf welches die Koordinaten bezogen sind (proj.4).
		[helpstring("Die Berechnungen werden auf dem Bezugsellipsoiden durchgeführt"), helpcontext(ACCURACY_enum)]
			ACCURACY_Ellipsoidal = ACCURACY_Ellipsoidal1,	// @emem Die Berechnungen werden auf dem Bezugsellipsoiden
				// durchgeführt, auf welches die Koordinaten bezogen sind.
	} DIST_ACCURACY;
cpp_quote("#endif // _ACCURACY_DEFINED")

cpp_quote("#if !defined(_DISTTYPE_DEFINED)")
cpp_quote("#define _DISTTYPE_DEFINED")
// @doc DISTTYPEENUMS 
// @enum DIST_TYPE | Die verwendbaren Formen der Abstandsbestimmung zwischen zwei Geometrien.
// @xref <i ITRiASCSDistanceService>, <om ITRiASCSDistanceService.GetDistance>
	typedef [
		public, 
		v1_enum, 
		helpstring("Verwendbare Formen der Abstandsbestimmung."),
		helpcontext(DISTTYPE_enum)
	]
	enum _tagDISTTYPE {
		[helpstring("Das zu verwendende Form der Abstandsbestimmung ist nicht definiert"), helpcontext(DISTTYPE_enum)]
			DISTTYPE_Unknown = 0,		// Das zu verwendende Form der Abstandsbestimmung ist nicht definiert.

		[helpstring("Automatische Entscheidung über die Form der Abstandsbestimmung"), helpcontext(DISTTYPE_enum)]
			DISTTYPE_Auto = 1,			// Automatische Entscheidung über die Form der Abstandsbestimmung.
	} DIST_TYPE;
cpp_quote("#endif // _DISTTYPE_DEFINED")

// @doc ITRIASCSDISTANCESERVICE | PROPERTY
// @property <t DIST_ACCURACY> | ITRiASCSDistanceService | Accuracy | Die Eigenschaft <op .Accuracy> setzt 
// bzw. liefert die Genauigkeitsgrundlage, auf der basierend alle Berechnungen durchgeführt werden.
// @comm Wenn keine Genauigkeit vorgegeben wird, so erfolgen alle Berechnungen, als ob <e DIST_ACCURACY.ACCURACY_Spheric>
// vorgegeben worden wäre.
// @supby <o TRiASCSDistanceService>
// @xref <i ITRiASCSDistanceService>
	[propput, id(1), helpstring("Setzt die Genauigkeitsgrundlage, mit der sämtliche Berechnungen durchgeführt werden."), helpcontext(ITRiASCSDistanceService_Accuracy_prop)] HRESULT Accuracy ([in] DIST_ACCURACY newVal);
	[propget, id(1), helpstring("Liest die Genauigkeitsgrundlage, mit der sämtliche Berechnungen durchgeführt werden."), helpcontext(ITRiASCSDistanceService_Accuracy_prop)] HRESULT Accuracy ([out, retval] DIST_ACCURACY *pVal);

// @doc ITRIASCSDISTANCESERVICE | PROPERTY
// @property <i ITRiASCSTransform> | ITRiASCSDistanceService | TransformPipe | Die Eigenschaft <op .TransformPipe>
// setzt bzw. liefert das Transformationsobjekt, welches den Berechnungen zugrunde liegt.
// @comm Das Transformationsobjekt wird verwendet, um alle Koordinaten in ein einheitliches 
// Bezugskoordinatensystem umzusetzen, d.h. das im Transformationsobjekt eingestellte Ausgangskoordinatensystem 
// legt fest, auf welcher Grundlage die Berechnungen erfolgen. 
// @comm Die Eigenschaft <op .TransformPipe> muß nicht gesetzt werden. In diesem Fall wird als 
// Bezugskoordinatensysstem WGS84 (UTM Projektion 9°/6°, Längenmaßeinheit Meter) verwendet.
// @comm Das Transformationsobjekt bietet die Möglichkeit einer Optimierung, sowohl von vornherein sämtliche 
// auftretenden Koordinatensysteme als Eingangskoordinatensysteme (s. <om ITRiASCSTransform.AddInputCS>)
// zu registrieren, als auch u.U. das Ausgangskoordinatensystem auf das sowieso verwendete
// Koordinatensystem der zu verarbeitetenden Koordinatenpunkte zu initialisieren. In diesem Fall wären intern
// keine weiteren Transformationen notwendig, was die Verarbeitungszeit positiv beeinflußt.
// @supby <o TRiASCSDistanceService>
// @xref <i ITRiASCSDistanceService>, <i ITRiASCSTransform>
	[propputref, id(2), helpstring("Setzt das Transformationsobjekt, welches den Berechnungen zugrunde liegt."), helpcontext(ITRiASCSDistanceService_TransformPipe_prop)] HRESULT TransformPipe ([in] ITRiASCSTransform *newVal);
	[propget, id(2), helpstring("Liest das Transformationsobjekt, welches den Berechnungen zugrunde liegt."), helpcontext(ITRiASCSDistanceService_TransformPipe_prop)] HRESULT TransformPipe ([out, retval] ITRiASCSTransform **pVal);

// @doc ITRIASCSDISTANCESERVICE | PROPERTY
// @property double | ITRiASCSDistanceService | LastTime | Die Eigenschaft <op .LastTime> 
// liefert die für die zuletzt ausgeführte  Berechnung benötigte Zeit in [ms].
// @comm Die <op .LastTime> -Eigenschaft kann nicht gesetzt werden.
// @supby <o TRiASCSDistanceService>
// @xref <i ITRiASCSDistanceService>
	[propget, id(3), helpstring("Liefert die für die zuletzt ausgeführte Berechnung benötigte Zeit in [ms]."), helpcontext(ITRiASCSDistanceService_LastTime_prop)] HRESULT LastTime ([out, retval] double *pVal);

// @doc ITRIASCSDISTANCESERVICE | METHOD
// @method double | ITRiASCSDistanceService | GetDistancePts | Die Methode <om .GetDistancePts>
// berechnet den Abstand zwischen den beiden gegebenen Koordinaten.
// @parm VARIANT | CS1 | Der Parameter <p CS1> definiert das Koordinatensystem des ersten 
// Koordinatenpunktes (s. Parameter <p Pts1>). 
// @parm VARIANT | Pts1 | Der Parameter <p Pts1> enthält die Koordinaten des ersten Punktes in Form eines
// Zahlen-Tripels (X, Y, Z).
// @parm VARIANT | CS2 | Der Parameter <p CS2> definiert das Koordinatensystem des ersten 
// Koordinatenpunktes (s. Parameter <p Pts2>). 
// @parm VARIANT | Pts2 | Der Parameter <p Pts2> enthält die Koordinaten des zweiten Punktes in Form eines
// Zahlen-Tripels (X, Y, Z).
// @comm Als Maßeinheit wird die im Ausgangssystem des Transformationsobjektes eingestellte 
// Längenmaßeinheit (<op ITRiASCSPS.UnitOfLength>) verwendet. Ist im Ausgangssystem keine Projektion
// definiert, dann wird [Meter] angenommen.
// @comm Die Koordinatensysteme (s. Parameter <p CS1> bzw. <p CS2>) können sowohl direkt in Form eines
// <i ITRiASCS> -Interfaces oder aber indirekt über einen GUID eines Koordinatensystemes gegeben sein (s <op ITRiASCS.GUID>). 
// Wenn der GUID als Zeichenkette gegeben wird, dann muß das betreffende Koordinatensystem am Transformationsobjekt
// als Einganssystem registriert sein (s. <om ITRiASCSTransform.AddInputCS>)
// @comm Obwohl sämtliche Koordinatenangaben als Zahlen-Tripel (X, Y, Z) - bzw. (Rechtwert, Hochwert, Höhe)
// gegeben sein müssen, werden z.Zt. lediglich der Rechtswert und der Hochwert ausgewertet. Die Höhe wird
// in jedem Fall ignoriert und sollte daher auf den Wert Null vorinitialisiert werden.
// @ex Berechnung des Abstandes zwischen zwei Punkten |
//	Option Base 0
//	Sub Main()
//	' Erzeugen des Koordinatensystemes
//	Dim cs As New TRiASCs.TRiASCS		' WGS84, geodätisch, Sekunden
//
//	' Initialisierung des ersten Punktes (12°, 52°30')
//  Dim pt1() As Double: ReDim pt1(0 To 2)
//
//		pt1(0) = 12# * 3600
//		pt1(1) = 52# * 3600 + 30# * 60#
//		pt1(2) = 0
//
//	' Initialisierung des zweiten Punktes (11°59'54.51", 52°29'54.87")
//  Dim pt2() As Double: ReDim pt2(0 To 2)
//
//		pt2(0) = 11# * 3600# + 59# * 60# + 54.51
//		pt2(1) = 52# * 3600# + 29# * 60# + 54.87
//		pt2(2) = 0
//
//	' Berechnen der Entfernung
//	Dim DistService As New TRiASCs.TRiASCsDistanceService
//
//		MsgBox "Entfernung:", Str$(DistService.GetDistancePts(cs, pt1, cs, pt2))
//
//	End Sub
// @xref <i ITRiASCSDistanceService>, <i TRiASCS>, <i ITRiASCSPS>, <i ITRiASCSTransform>
	[id(100), helpstring("Berechnet den Abstand zwischen den beiden gegebenen Koordinaten."), helpcontext(ITRiASCSDistanceService_GetDistancePts_meth), hidden, restricted] HRESULT GetDistancePts([in] VARIANT CS1, [in] VARIANT Pts1, [in] VARIANT CS2, [in] VARIANT Pts2, [out, retval] double *pVal);
};

///////////////////////////////////////////////////////////////////////////////
// @doc INTERFACE TRIASCS
// @interface ITRIASCSSet | Eine Sammlung von Koordinatensystemen
// @group Methoden und Eigenschaften von <i ITRIASCSSet>
// @index | ITRIASCSSet
// @normal ITRiASCSSet stellt eine einfache Möglichkeit dar Sammlungen von 
//		Koordinatensystemen anzulegen, Elemente hinzuzufügen, Elemente daraus 
//		zu löschen, Elemente zu suchen sowie den gesamten Satz zu speichern und
//		zu lesen. 
// @comm Siehe auch <l Speichern / Lesen von Koordinatensystemen>
[
	object,
	uuid(2FB28CB5-89D8-11D2-9894-0060085FC1CE),
	dual,
	helpstring("ITRIASCSSet Interface"),
	pointer_default(unique)
] 
interface ITRiASCSSet : IDispatch 
{
	[id(DISPID_NEWENUM), helpstring("method _NewEnum")] HRESULT _NewEnum([out,retval] IUnknown **ppIEnum);

// @doc METHOD TRIASCS ITRIASCSSet
// @method HRESULT | ITRIASCSSet | Add | 
//		fügt der Sammlung ein Koordinatensystem hinzu
	[id(1), helpstring("method Add")] HRESULT Add([in] VARIANT Item);

// @doc METHOD TRIASCS ITRIASCSSet
// @method HRESULT | ITRIASCSSet | Remove | 
//		entfernt ein Koordinatensystem aus der Sammlung
// @comm siehe auch <om .Find>.
	[id(2), helpstring("method Remove")] HRESULT Remove([in] VARIANT Item);

// @doc METHOD TRIASCS ITRIASCSSet
// @method HRESULT | ITRIASCSSet | Find |
//		Sucht ein Koordinatensystem in der Sammlung.
// @normal Der anzugebende VARIANT wird wie folgt interpretiert:
// @normal VT_I1, VT_I2, VT_I4, VT_UI1, VT_UI2, VT_UI4 - es wird das System mit dem entsprechenden
//		Index zurückgegeben
// @normal VT_BSTR - es wird das System mit dem entsprechenden Namen zurückgegeben
	[id(3), helpstring("method Find")] HRESULT Find([in] VARIANT Item, [out,retval] IDispatch **ppCS);
	[propget, id(4), helpstring("property Count")] HRESULT Count([out, retval] long *pVal);

// @doc METHOD TRIASCS ITRIASCSSet
// @method HRESULT | ITRIASCSSet | SaveToFile |
// @normal Speichert die Sammlung unter dem angegebenen Dateinamen ab.
	[id(5), helpstring("method SaveToFile")] HRESULT SaveToFile([in] BSTR strFile);

// @doc METHOD TRIASCS ITRIASCSSet
// @method HRESULT | ITRIASCSSet | LoadFromFile |
// @normal Lädt eine Koordinatensystemsammlung aus der gegebenen Datei.
	[id(6), helpstring("method LoadFromFile")] HRESULT LoadFromFile([in] BSTR strFileName);

// @doc METHOD TRIASCS ITRIASCSSet
// @method HRESULT | ITRIASCSSet | SaveToRegistry |
// @normal Speichert die Sammlung unter dem angegebenen Registrierungsschlüssel ab.
// @comm Als arument wird nur der Registrierungsschlüssel angegeben. Die Daten Werden als Binärdaten
//		unter der dem Wert 'InstalledSystems' abgelegt.
	[id(7), helpstring("method SaveToRegistry")] HRESULT SaveToRegistry([in] TCS_REGISTRYROOT root, [in] BSTR strRegKey, [in, optional] VARIANT strComputername);

// @doc METHOD TRIASCS ITRIASCSSet
// @method HRESULT | ITRIASCSSet | LoadFromRegistry |
// @normal Lädt eine Sammlung aus dem angegebenen Registrierungsschlüssel.
	[id(8), helpstring("method LoadFromRegistry")] HRESULT LoadFromRegistry([in] TCS_REGISTRYROOT root, [in] BSTR strRegKey, [in, optional] VARIANT strComputername);
};

#if defined(_USE_WKTSERVICE)
[
	object,
	uuid(C689F443-3E59-4308-AD8E-94A948283101),
	dual,
	helpstring("ITRiASCSWktService Interface"),
	pointer_default(unique),
	helpcontext(ITRiASCSWktService_int)
]
interface ITRiASCSWktService : IDispatch
{
	typedef [
		public, v1_enum, 
		helpstring("Gibt das verwendete Textformat vor."),
		helpcontext(WKTFORMAT_enum)
	]
	enum _tagWKTFORMAT {
		WKTFORMAT_Unknown = 0,
		WKTFORMAT_OgcWkt = 1,
	} WKTFORMAT;

	[id(100), helpstring("method CreateFromWkt"), helpcontext(ITRiASCSWktService_CreateFromWkt_meth)] HRESULT CreateFromWkt([in] WKTFORMAT Format, [in] BSTR WktCS, [out, retval] ITRiASCS **CS);
	[id(101), helpstring("method ExportAsWkt"), helpcontext(ITRiASCSWktService_ExportAsWkt_meth)] HRESULT ExportAsWkt([in] WKTFORMAT Format, [in] ITRiASCS *CS, [out, retval] BSTR *WktCS);
};
#endif // defined(_USE_WKTSERVICE)

///////////////////////////////////////////////////////////////////////////////
// @doc INTERFACE TRIASCS INTERNAL
// @interface ITRiASCSUIHelper | Das <i ITRiASCSUIHelper> -interface dient der 
// Bereitstellung verschiedener Funktionen, die für die Koordinatendarstellung und
// -Eingabe in einer Nutzerschnittstelle nützlich sind.
// @group Eigenschaften von <i ITRiASCSUIHelper>
// @index | ITRiASCSUIHelper & PROPERTY
// @group Methoden von <i ITRiASCSUIHelper>
// @index | ITRiASCSUIHelper & METHOD
// @doc ITRiASCSUIHelper
[ 
	object, 
	uuid(7A268E3E-C155-411F-AF39-AAEC957F0B2B), 
	dual, 
	helpstring("ITRiASCSUIHelper Interface"),
	pointer_default(unique) 
]
interface ITRiASCSUIHelper : IDispatch
{
cpp_quote("#if !defined(_COORDELEMENT_DEFINED)")
cpp_quote("#define _COORDELEMENT_DEFINED")
// @doc COORDELEMENTENUMS 
// @enum COORDELEMENT | Entscheidet welcher der Werte eines Koordinatentripels untersucht bzw. 
// verwendet werden soll.
// @xref <i ITRiASCSUIHelper>
typedef [
	public, v1_enum, 
	helpstring("Entscheidet welcher der Werte eines Koordinatentripels untersucht bzw. verwendet werden soll"),
	helpcontext(COORDELEMENT_enum)
]
enum _tagCOORDELEMENT {
	[helpstring("Es wird der X-Wert eines Koordinatentripels untersucht bzw. ausgewertet"), helpcontext(COORDELEMENT_enum)]
		COORDELEMENT_X = 0,		// @emem Es wird der X-Wert eines Koordinatentripels untersucht bzw. ausgewertet.
	[helpstring("Es wird der Y-Wert eines Koordinatentripels untersucht bzw. ausgewertet"), helpcontext(COORDELEMENT_enum)]
		COORDELEMENT_Y = 1,		// @emem Es wird der Y-Wert eines Koordinatentripels untersucht bzw. ausgewertet.
	[helpstring("Es wird der Z-Wert eines Koordinatentripels untersucht bzw. ausgewertet"), helpcontext(COORDELEMENT_enum)]
		COORDELEMENT_Z = 2,		// @emem Es wird der Z-Wert eines Koordinatentripels untersucht bzw. ausgewertet.
} COORDELEMENT;
cpp_quote("#endif // _COORDELEMENT_DEFINED")

// @doc ITRiASCSUIHelper | PROPERTY INTERNAL
// @property String | ITRiASCSUIHelper | InputMask | Die Eigenschaft <op .InputMask>
// liefert die für die Koordinateneingabe eines Wertes zu verwendende Eingabemaske.
// @parm COORDELEMENT | Element | Der Parameter <p Element> entscheidet, für welchen der Werte des 
// Koordinatentripels die Eingabemaske geliefert wird.
// @comm Die Eigenschaft <op .InputMask> kann nicht gesetzt werden.
// @devnote Die Eingabemaske ist für das Control 'MsMskEdit.Ocx' formatiert und kann dort
// für sowohl für die .Mask -Eigenschaft als auch für die .Format -Eigenschaft verwendet werden.
// @xref <i ITRiASCSUIHelper>
	[propget, id(1), helpstring("Liefert die für die Koordinateneingabe zu verwendende Eingabemaske."), helpcontext(ITRiASCSUIHelper_InputMask_prop)] HRESULT InputMask ([in] COORDELEMENT Element, [out, retval] BSTR *UIMask);

// @doc ITRiASCSUIHelper | PROPERTY INTERNAL
// @property Long | ITRiASCSUIHelper | Precision | Die Eigenschaft <op .Precision> liefert bzw.
// setzt die Anzahl der auszuwertenden bzw. anzuzeigenden Nachkommastellen.
// @xref <i ITRiASCSUIHelper>
	[propget, id(2), helpstring("Liefert die Anzahl der auszuwertenden Nachkommastellen."), helpcontext(ITRiASCSUIHelper_Presision_prop)]  HRESULT Precision ([out, retval] long *Prec);
	[propput, id(2), helpstring("Liefert die Anzahl der auszuwertenden Nachkommastellen."), helpcontext(ITRiASCSUIHelper_Presision_prop)]  HRESULT Precision ([in] long Prec);

// @doc ITRiASCSUIHelper | METHOD INTERNAL
// @method String | ITRiASCSUIHelper | Format | Die Methode <om .Format>
// konvertiert einen Wert einer Koordinate in eine Zeichenkette.
// @parm COORDELEMENT | Element | Der Parameter <p Element> entscheidet, welcher der Werte des 
// Koordinatentripels in eine Zeichenkette konvertiert wird.
// @parm Double | Value | Der Parameter <p Value> enthält den zu konvertierenden Koordinatenwert
// der auf das zugehörige Koordinatensystem bezogen ist. 
// @rvalue String | Der Rückgabewert enthält den aktuellen Einstellungen des zugehörigen Koordinatensystemes 
// formatierten Koordinatenwert.
// @xref <i ITRiASCSUIHelper>
	[id(3), helpstring("Konvertiert einen Wert einer Koordinate in eine Zeichenkette."), helpcontext(ITRiASCSUIHelper_Format_meth)] HRESULT Format ([in] COORDELEMENT Element, [in] double Value, [out, retval] BSTR *FormattedElement);

// @doc ITRiASCSUIHelper | METHOD INTERNAL
// @method Double | ITRiASCSUIHelper | Convert | Die Methode <om .Convert>
// konvertiert eine Zeichenkette in einen Wert einer Koordinate.
// @parm COORDELEMENT | Element | Der Parameter <p Element> entscheidet, welcher der Werte des 
// Koordinatentripels in eine Zeichenkette konvertiert wird.
// @parm String | Formatted | Der Parameter <p Formatted> enthält eine entsprechend der Eingabemaske
// formierte Zeichenkette
// @rvalue Double | Der Rückgabewert enthält den konvertierten Koordinatenwert, der auf das zugehörige
// Koordinatensystem bezogen ist
// @xref <i ITRiASCSUIHelper>
	[id(4), helpstring("Konvertiert eine Zeichenkette in einen Wert einer Koordinate."), helpcontext(ITRiASCSUIHelper_Convert_meth)] HRESULT Convert ([in] COORDELEMENT Element, [in] BSTR Formatted, [out, retval] double *Value);
};

///////////////////////////////////////////////////////////////////////////////
// @doc INTERFACE TRIASCS
[ 
	object,
	uuid(04D103F3-592A-11d2-8FCA-0060085FC1CE),
	dual,
	helpstring("ITRiASCSEvents Interface"),
	pointer_default(unique)
] 
interface ITRiASCSEvents : IDispatch 
{
	[id(1), helpstring("")] HRESULT ChangingCS([in] ITRiASCS* pCS, [in,out] VARIANT_BOOL *canChange);
	[id(2), helpstring("")] HRESULT CSToChange([in] ITRiASCS* pCS );
	[id(3), helpstring("")] HRESULT CSChanged([in] ITRiASCS* pCS );
};
	
///////////////////////////////////////////////////////////////////////////////
// @doc INTERFACE ITRIASCSUISERVICE
// @interface ITRiASCSUIService | Das <i ITRiASCSUIService> -interface dient der 
// Bereitstellung verschiedener Funktionen, die für die Koordinatendarstellung und
// -Eingabe in einer Nutzerschnittstelle nützlich sind.
// @group Eigenschaften von <i ITRiASCSUIService>
// @index | ITRIASCSUISERVICE & PROPERTY
// @group Methoden von <i ITRiASCSUIService>
// @index | ITRiASCSUIService & METHOD
// @doc ITRIASCSUISERVICE
[ 
	object, 
	uuid(0A899448-E4F2-480F-B794-7F10D519C396),
	dual, 
	oleautomation, 
	pointer_default(unique),
	helpcontext(ITRiASCSUIService_int)
]
interface ITRiASCSUIService : IDispatch
{
// @doc ITRIASCSUISERVICE | PROPERTY
// @property String | ITRiASCSUIService | InputMask | Die Eigenschaft <op .InputMask>
// liefert die für die Koordinateneingabe eines Wertes zu verwendende Eingabemaske.
// @parm COORDELEMENT | Element | Der Parameter <p Element> entscheidet, für welchen der Werte des 
// Koordinatentripels die Eingabemaske geliefert wird.
// @comm Die Eigenschaft <op .InputMask> kann nicht gesetzt werden.
// @devnote Die Eingabemaske ist für das Control formatiert, welches durch die Eigenschaft <om .InputMaskControl>
// geliefert wird und kann dort sowohl für die .Mask -Eigenschaft als auch für die .Format -Eigenschaft 
// verwendet werden.
// @xref <i ITRiASCSUIService>
	[propget, id(1), helpstring("Liefert die für die Koordinateneingabe zu verwendende Eingabemaske."), helpcontext(ITRiASCSUIHelper_InputMask_prop)] HRESULT InputMask ([in] ITRiASCS *CoordSys, [in] COORDELEMENT Element, [out, retval] BSTR *UIMask);

// @doc ITRIASCSUISERVICE | PROPERTY
// @property Long | ITRiASCSUIService | Precision | Die Eigenschaft <op .Precision> liefert bzw.
// setzt die Anzahl der auszuwertenden bzw. anzuzeigenden Nachkommastellen.
// @xref <i ITRiASCSUIService>
	[propget, id(2), helpstring("Liefert die Anzahl der auszuwertenden Nachkommastellen."), helpcontext(ITRiASCSUIHelper_Presision_prop)]  HRESULT Precision ([in] ITRiASCS *CoordSys, [out, retval] long *Prec);
	[propput, id(2), helpstring("Liefert die Anzahl der auszuwertenden Nachkommastellen."), helpcontext(ITRiASCSUIHelper_Presision_prop)]  HRESULT Precision ([in] ITRiASCS *CoordSys, [in] long Prec);

// @doc ITRIASCSUISERVICE | METHOD
// @method String | ITRiASCSUIHelper | Format | Die Methode <om .Format>
// konvertiert einen Wert einer Koordinate in eine Zeichenkette.
// @parm COORDELEMENT | Element | Der Parameter <p Element> entscheidet, welcher der Werte des 
// Koordinatentripels in eine Zeichenkette konvertiert wird.
// @parm Double | Value | Der Parameter <p Value> enthält den zu konvertierenden Koordinatenwert
// der auf das zugehörige Koordinatensystem bezogen ist. 
// @rvalue String | Der Rückgabewert enthält den aktuellen Einstellungen des zugehörigen Koordinatensystemes 
// formatierten Koordinatenwert.
// @xref <i ITRiASCSUIService>
	[id(3), helpstring("Konvertiert einen Wert einer Koordinate in eine Zeichenkette."), helpcontext(ITRiASCSUIHelper_Format_meth)] HRESULT Format ([in] ITRiASCS *CoordSys, [in] COORDELEMENT Element, [in] double Value, [out, retval] BSTR *FormattedElement);

// @doc ITRIASCSUISERVICE | METHOD
// @method Double | ITRiASCSUIService | Convert | Die Methode <om .Convert>
// konvertiert eine Zeichenkette in einen Wert einer Koordinate.
// @parm COORDELEMENT | Element | Der Parameter <p Element> entscheidet, welcher der Werte des 
// Koordinatentripels in eine Zeichenkette konvertiert wird.
// @parm String | Formatted | Der Parameter <p Formatted> enthält eine entsprechend der Eingabemaske
// formierte Zeichenkette
// @rvalue Double | Der Rückgabewert enthält den konvertierten Koordinatenwert, der auf das zugehörige
// Koordinatensystem bezogen ist
// @xref <i ITRiASCSUIService>
	[id(4), helpstring("Konvertiert eine Zeichenkette in einen Wert einer Koordinate."), helpcontext(ITRiASCSUIHelper_Convert_meth)] HRESULT Convert ([in] ITRiASCS *CoordSys, [in] COORDELEMENT Element, [in] BSTR Formatted, [out, retval] double *Value);

// @doc ITRIASCSUISERVICE | PROPERTY
// @property String | ITRiASCSUIService | InputMaskControl | Die Eigenschaft <op .InputMaskControl>
// liefert das Control, für welches die Eingabemaske für die Koordinateneingabe eines Wertes verwendet 
// werden sollte.
// @comm Die Eigenschaft <op .InputMaskControl> kann nicht gesetzt werden.
// @xref <i ITRiASCSUIService>
	[propget, id(5), helpstring("Liefert das für die Koordinateneingabe zu verwendende Eingabecontrol."), helpcontext(ITRiASCSUIHelper_InputMaskControl_prop)] HRESULT InputMaskControl ([out, retval] BSTR *UIGuid);
};

///////////////////////////////////////////////////////////////////////////////
// @doc INTERFACE ITRIASCSTRANSFORMSERVICE
[
	object,
	uuid(C913AAB2-781E-4D71-9834-BCF00D78BDF0),
	dual,
	helpstring("IEnumCoordSystemnames Interface"),
	pointer_default(unique)
]
interface IEnumCoordSystemNames : IStaticCollection
{
};

///////////////////////////////////////////////////////////////////////////////
// @doc INTERFACE ITRIASCSTRANSFORMSERVICE
// @interface ITRiASCSTransformService | Das <i ITRiASCSTransformService> -interface dstellt 
// Funktionen zur Verfügung, die es VB-Clients ermöglichen, Geometrieobjekte direkt durch eine
// Koordinatentransformationspipe verarbeiten zu lassen.
// @group Eigenschaften von <i ITRiASCSTransformService>
// @index | ITRIASCSTRANSFORMSERVICE & PROPERTY
// @group Methoden von <i ITRiASCSTransformService>
// @index | ITRIASCSTRANSFORMSERVICE & METHOD
// @doc ITRIASCSUISERVICE
[ 
	object, 
	uuid(3FD138FF-221D-4D2E-AB5F-1510450B3872), 
	dual, 
	helpstring("ITRiASCSTransformService Interface"),	
	pointer_default(unique) 
]
interface ITRiASCSTransformService : IDispatch
{
// @doc ITRIASCSTRANSFORMSERVICE METHOD 
// @method HRESULT | ITRiASCSTransformService | Transform | Transformiert ein Geometrieobjekt
// in das Ausgangssystem der Transformationspipe
// @parm [in] Object | Geometry | Der Parameter <p Geometry> definiert das zu transformierende 
// Geometrieobjekt
// @parm [in] String | CoordSysGuid | Der Parameter <p CoordSysGuid> definiert das zu 
// verwendende Eingangskoordinatensystem
// @parm [in] <l ITRiASCSTransform> | CTF | Der Parameter <p CTF> definiert das zu 
// verwendende Transformationsobjekt
// @xref <i ITRiASCSTransformService>, <om ITRiASCSTransformService.TransformInversePts>
	[id(100), helpstring("Transformiert die Koordinaten eines Geometrieobjekt ins Ausgangssystem der gegebenen Transformationspipe."), helpcontext(ITRiASCSTransformService_Transform_meth)] HRESULT Transform([in] IDispatch *Geometry, [in] BSTR CoordSysGuid, [in] ITRiASCSTransform *CTF);

// @doc ITRIASCSTRANSFORMSERVICE METHOD 
// @method HRESULT | ITRiASCSTransformService | TransformInverse | Transformiert ein Geometrieobjekt
// aus dem Ausgangssystem der Transformationspipe in das angegebene Eingangssystem (gesetzt mit 
// <om ITRiASCSTransform.AddInputCS>)
// @parm [in] Object | Geometry | Der Parameter <p Geometry> definiert das zu transformierende 
// Geometrieobjekt
// @parm [in] String | CoordSysGuid | Der Parameter <p CoordSysGuid> definiert das zu 
// verwendende Eingangskoordinatensystem
// @parm [in] <l ITRiASCSTransform> | CTF | Der Parameter <p CTF> definiert das zu 
// verwendende Transformationsobjekt
// @xref <i ITRiASCSTransformService>, <om ITRiASCSTransformService.TransformPts>
	[id(101), helpstring("Transformiert die Koordinaten eines Geometrieobjekt in eines der Eingangssysteme der gegebenen Transformationspipe."), helpcontext(ITRiASCSTransformService_TransformInverse_meth)] HRESULT TransformInverse([in] IDispatch *Geometry, [in] BSTR CoordSysGuid, [in] ITRiASCSTransform *CTF);

// @doc METHOD TRIASCS ITRIASCSTRANSFORMSERVICE
// @method Variant | ITRiASCSTransformService | TransformPts | Die Methode <om .TransformPts> transformiert ein Feld 
// von Koordinaten vom angegebenen Eingangssystem des Transformationsobjektes (gesetzt mit 
// <om .AddInputCS>) in das Ausgangssystem des Transformationsobjektes.
// @parm [in] String | CoordSysGuid | Der Parameter <p CoordSysGuid> definiert das zu verwendende 
// Eingangskoordinatensystem.
// @parm [in] <l ITRiASCSTransform> | CTF | Das zu verwendende Transformationsobjekt
// @parm [in] Double() | InPoints | Der Parameter <p InPoints> enthält die zu transformierenden 
// Koordinaten. Das übergebene Feld muß durch eine 'ReDim'- Anweisung eine Größe zugewiesen
// bekommen haben, die durch 3 teilbar ist. Es wird davon ausgegangen, daß jeweils 3 aufeinanderfolgende
// Elemente dieses Feldes ein Koordinaten-Tripel (X, Y, Z) enthalten.
// @rdesc Die Methode <om .TransformPts> liefert ein Feld, in dem die transformierten Koordinaten 
// abgelegt sind. Das Format des gelieferten Feldes entspricht dem des Parameters <p InPoints>. Die
// Elemente des Feldes sind vom Typ Double.
// @except:(INTERNAL)
// <nl><cv E_INVALIDARG> Zeiger auf Quellkoordinaten ist ungültig (NULL)
// <nl><cv E_POINTER> Zeiger auf Zielkoordinaten ist ungültig (NULL)
// <nl><cv CST_E_COORDSYSTEMNOTFOUND> Es wurde kein Koordinatensystem gefunden, welches dem übergebenen
// GUID zugeordnet ist.
// <nl><cv CST_E_INVALIDCOORDCOUNT> Die Anzahl der Werte im Parameter <p InPoints> ist nicht durch 3 teilbar.
// <nl><cv CST_E_INPUTTRANSFORMATIONFAILED>
// <nl><cv CST_E_OUTPUTTRANSFORMATIONFAILED>
// <nl><cv CST_E_INVALIDSOURCECOORDSYSTEM> Das Eingangskoordinatensystem ist ungültig.
// <nl><cv CST_E_INVALIDDESTINATIONCOORDSYSTEM> Das Ausgangskoordinatensystem ist ungültig.
// @xref <i ITRiASCSTransformService>, <om ITRiASCSTransformService.TransformInverse>
	[id(102), helpstring("Koordinatentransformation von einem der Einganssysteme zum Ausgangssystem."), helpcontext(ITRiASCSTransformService_TransformPts_meth)] HRESULT TransformPts([in] BSTR CoordSysGuid, [in] ITRiASCSTransform *CTF, [in] VARIANT InPoints, [out, retval] VARIANT *OutPoints);

// @doc METHOD TRIASCS ITRIASCSTRANSFORMSERVICE
// @method Variant | ITRiASCSTransformService | TransformInversePts | Die Methode <om .TransformInversPts>
// transformiert ein Feld von Koordinaten aus dem Ausgangssystem des Transformators in das
// angegebene Eingangssystem des Transformationsobjektes (gesetzt mit <om ITRiASCSTransform.AddInputCS>).
// @parm [in] String | CoordSysGuid | Der Parameter <p CoordSysGuid> definiert das zu verwendende 
// Eingangskoordinatensystem.
// @parm [in] <l ITRiASCSTransform> | CTF | Das zu verwendende Transformationsobjekt
// @parm [in] Double() | InPoints | Der Parameter <p InPoints> enthält die zu transformierenden 
// Koordinaten. Das übergebene Feld muß durch eine 'ReDim'- Anweisung eine Größe zugewiesen
// bekommen haben, die durch 3 teilbar ist. Es wird davon ausgegangen, daß jeweils 3 aufeinanderfolgende
// Elemente dieses Feldes ein Koordinaten-Tripel (X, Y, Z) enthalten.
// @rdesc Die Methode <om .TransformInversePts> liefert ein Feld, in dem die transformierten Koordinaten 
// abgelegt sind. Das Format des gelieferten Feldes entspricht dem des Parameters <p InPoints>. Die
// Elemente des Feldes sind vom Typ Double.
// @rdesc Die Methode <om .TransformInversPts> liefert ein Feld, in dem die transformierten Koordinaten 
// abgelegt sind. Das Format des gelieferten Feldes entspricht dem des Parameters <p InPoints>. Die
// Elemente des Feldes sind vom Typ Double.
// @except:(INTERNAL)
// <nl><cv E_INVALIDARG> Zeiger auf Quellkoordinaten ist ungültig (NULL)
// <nl><cv E_POINTER> Zeiger auf Zielkoordinaten ist ungültig (NULL)
// <nl><cv CST_E_COORDSYSTEMNOTFOUND> Es wurde kein Koordinatensystem gefunden, welches dem übergebenen
// GUID zugeordnet ist.
// <nl><cv CST_E_INVALIDCOORDCOUNT> Die Anzahl der Werte im Parameter <p InPoints> ist nicht durch 3 teilbar.
// <nl><cv CST_E_INPUTTRANSFORMATIONFAILED>
// <nl><cv CST_E_OUTPUTTRANSFORMATIONFAILED>
// <nl><cv CST_E_INVALIDSOURCECOORDSYSTEM>
// <nl><cv CST_E_INVALIDDESTINATIONCOORDSYSTEM>
// @xref <i ITRiASCSTransformService>, <om ITRiASCSTransformService.Transform>
	[id(103), helpstring("Koordinatentransformation vom Ausgangssystem zu einem der Einganssysteme."), helpcontext(ITRiASCSTransformService_TransformInversePts_meth)] HRESULT TransformInversePts([in] BSTR CoordSysGuid, [in] ITRiASCSTransform *CTF, [in] VARIANT InPoints, [out, retval] VARIANT *OutPoints);

// @doc METHOD TRIASCS ITRIASCSTRANSFORMSERVICE
// @method Variant | ITRiASCSTransformService | EnumCoordSystemNames | Die Methode <om .EnumCoordSystemNames>
// liefert einen Enumerator, der die Menge aller bekannten Koordinatensysteme enthält.
// @rdesc Die Methode <om .EnumCoordSystemNames> liefert ein Enumeratorobjekt (<i IEnumCoordSystemNames>)
// welches alle Namen der direkt verfügbaren Koordinatensysteme enthält.
// @xref <i ITRiASCSTransformService>
	[id(104), helpstring("Liefert die Namen der verfügbaren Koordinatensysteme."), helpcontext(ITRiASCSTransformService_EnumCoordSystemNames_meth)] HRESULT EnumCoordSystemNames ([out, retval] IEnumCoordSystemNames **ppIEnum);
};

///////////////////////////////////////////////////////////////////////////////
// Die eigentliche Type-Library ...
[
	uuid(2DF06A03-E3EF-11D1-8F3E-0060085FC1CE),
	version(TYPELIB_TRiASCS_VERSION),
	helpstring(TYPELIB_TRiASCS_HELPSTRING),
	helpfile(TYPELIB_TRiASCS_HELPFILE_NAME)
]
library TRIASCS 
{
	importlib("stdole32.tlb");
	importlib("stdole2.tlb");

	enum TRIASCS_VERSIONS 
	{
		TYPELIB_TRIASCS_VERSION_MAJOR = TYPELIB_TRiASCS_VERSION_MAJOR,
		TYPELIB_TRIASCS_VERSION_MINOR = TYPELIB_TRiASCS_VERSION_MINOR,
	};

///////////////////////////////////////////////////////////////////////////////
// Diese Koordinatensystemtypen gibt es:
// @doc ENUM TRIASCS
// @enum TRIASCSTYPE | legt den Typ des verwendeten Koordinatensystems fest
	typedef [public, v1_enum] enum TRIASCSTYPE {
		tcsCS_Undefined = -1,	// @emem undefiniertes Koordinatensystem
		tcsCS_Projected = 1,	// @emem projektives Koordinatensystem
		tcsCS_Geographic = 2,	// @emem geographisches Koordinatensystem
		tcsCS_Geocentric = 3,	// @emem geozentrisches Kooordinatensystem
	} TRIASCSTYPE;

///////////////////////////////////////////////////////////////////////////////
// ...und hier wird jetzt alles andere definiert 
#include "EPSG.h"
 
///////////////////////////////////////////////////////////////////////////////
// @doc STRUCT TRIASCS
// @struct CSCOORD | Ein Koordinaten-Tripel (X, Y, Z)
// @index | CSCOORD
	typedef struct CSCOORD {
		double	X;			// @field Rechtswert der Koordinate in projektiven Systemen,
			// in geodätischen Systemen die geographische Länge.
		double	Y;			// @field Hochwert der Koordinate in projektiven Systemen,
			// in geodätischen Systemen die geographische Breite.
		double	Z;			// @field Höhe über Normalnull.
	} CSCOORD;

///////////////////////////////////////////////////////////////////////////////
// @doc STRUCT TRIASCS
// @struct CSREFPOINT | Ein Referenzpunkt World zu Map
// @index | CSREFPOINT
	typedef struct CSREFPOINT {
		CSCOORD	ptInWorld;	// @field Punkt in der Welt
		CSCOORD	ptInMap;	// @field Punkt in der Karte
	} CSREFPOINT;

///////////////////////////////////////////////////////////////////////////////
// @doc STRUCT TRIASCS
// @struct CSID | Unsere 'eigene' GUID - Deklaration
// @devnote CSID ist genau dasselbe wie ein GUID; nur mit einem anderen Namen
// ohne diesen zweiten Namen würde das '#import' - Statement
// nur Fehler produzieren...
// @index | CSID
	typedef struct CSID {
		DWORD Data1;
		WORD  Data2;
		WORD  Data3;
		BYTE  Data4[8];
	} CSID;

#include <olectl.h>

///////////////////////////////////////////////////////////////////////////////
// @doc INTERFACE TRIASCS
// @interface ITRiASCSDatumTransformation | TRiAS Koordinatensysteme; Datumstransformation
// @group Methoden und Eigenschaften von <i ITRiASCSDatumTransformation>
// @index | ITRiASCSDatumTransformation
// @doc ITRiASCSDatumTransformation
	[ 
		object,
		uuid(E5AC8733-0769-11D2-8F5E-0060085FC1CE),
		dual,
		helpstring("ITRiASCSDatumTransformation Interface"),
		pointer_default(unique)
	] 
	interface ITRiASCSDatumTransformation : IDispatch 
	{
	// @doc PROPERTY TRIASCS ITRiASCSDatumTransformation
	// @property <t TRIASCSDTRANSALGORITHM> | ITRiASCSDatumTransformation | TransformationAlgorithm | 
	//		setzt / liest den Transformationsalgorithmus für die Datumstransformation
	// @except:(INTERNAL)
	//	<cv DTT_E_INAVLIDDATUMTRANSFORMATION>
		[propget, id(1), helpstring("property TransformationAlgorithm")] HRESULT TransformationAlgorithm([out, retval] TRIASCSDTRANSALGORITHM *pVal);
		[propput, id(1), helpstring("property TransformationAlgorithm")] HRESULT TransformationAlgorithm([in] TRIASCSDTRANSALGORITHM newVal);

	// @doc PROPERTY TRIASCS ITRiASCSDatumTransformation
	// @property <t TRIASCSDTRANSPARAMETER> | ITRiASCSDatumTransformation | Parameter | 
	//		setzt / liest einen Parameter für die Datumstransformation
	//	@head3 siehe auch |
	//		<l Setzen / Lesen von Parametern>
	// @except:(INTERNAL)
	//	<cv TCS_E_INVALIDPARAMETERINDEX>
		[propget, id(2), helpstring("property Parameter")] HRESULT Parameter([in] TRIASCSDTRANSPARAMETER par, [out, retval] double *pVal);
		[propput, id(2), helpstring("property Parameter")] HRESULT Parameter([in] TRIASCSDTRANSPARAMETER par, [in] double newVal);

	// @doc PROPERTY TRIASCS ITRiASCSDatumTransformation
	// @property VARIANT * | ITRiASCSDatumTransformation | Parameters |
	//		setzt / liest ein Parameterfeld für die Datumstransformation
	//	@head3 siehe auch |
	//		<l Setzen / Lesen von Parametern>
	// @except:(INTERNAL)
	//	<cv TCS_E_INVALIDPARAMETERCOUNT>
		[propget, id(4), helpstring("property Parameters")] HRESULT Parameters([out, retval] VARIANT *pVal);
		[propput, id(4), helpstring("property Parameters")] HRESULT Parameters([in] VARIANT newVal);

	// @doc PROPERTY TRIASCS ITRiASCSDatumTransformation
	// @property <t TRIASCSGEODETICDATUM> | ITRiASCSDatumTransformation | GeodeticDatum |
	//		setzt / liest das geodätische Datum des Transformators
	// @except:(INTERNAL)
	//	<cv DTT_E_INAVLIDGEODETICDATUM>
		[propget, id(8), helpstring("property GeodeticDatum")] HRESULT GeodeticDatum([out, retval] TRIASCSGEODETICDATUM *pVal);
		[propput, id(8), helpstring("property GeodeticDatum")] HRESULT GeodeticDatum([in] TRIASCSGEODETICDATUM newVal);
	};

///////////////////////////////////////////////////////////////////////////////
// @doc INTERFACE TRIASCS
// @interface ITRiASCSPCS | TRiAS Koordinatensysteme; projektives Koordinatensystem
// @group Methoden und Eigenschaften von <i ITRiASCSPCS>
// @index | ITRiASCSPCS
// @doc ITRiASCSPCS
	[
		object,
		uuid(4E1A7103-E993-11D1-8F48-0060085FC1CE),
		dual,
		helpstring("ITRiASCSPCS Interface"),
		pointer_default(unique),
	] 
	interface ITRiASCSPCS : IDispatch 
	{
	// @doc PROPERTY TRIASCS ITRiASCSPCS
	// @property <t TRIASCSPROJECTIONALGORITHM> | ITRiASCSPCS | ProjectionAlgorithm | 
	//		setzt / liest den Projektionsalgorithmus
	// @except:(INTERNAL)
	//	<cv PCS_E_INAVLIDPROJECTIONALGORITHM>
		[propget, id(1), helpstring("property ProjectionAlgorithm")] HRESULT ProjectionAlgorithm([out, retval] TRIASCSPROJECTIONALGORITHM *pVal);
		[propput, id(1), helpstring("property ProjectionAlgorithm")] HRESULT ProjectionAlgorithm([in] TRIASCSPROJECTIONALGORITHM newVal);

	// @doc PROPERTY TRIASCS ITRiASCSPCS
	// @property <t TRIASCSUNITOFLENGTH> | ITRiASCSPCS | UnitOfLength | 
	//		setzt / liest den Projektionsalgorithmus
	// @except:(INTERNAL)
	//	<cv PCS_E_INAVLIDUNITOFLENGTH>
		[propget, id(2), helpstring("property UnitOfLength")] HRESULT UnitOfLength([out, retval] TRIASCSUNITOFLENGTH *pVal);
		[propput, id(2), helpstring("property UnitOfLength")] HRESULT UnitOfLength([in] TRIASCSUNITOFLENGTH newVal);

	// @doc PROPERTY TRIASCS ITRiASCSPCS
	// @property VARIANT * | ITRiASCSPCS | ProjectionParameters |
	//		setzt / liest ein Parameterfeld für den Projektionsalgorithmus
	//	@head3 siehe auch |
	//		<l Setzen / Lesen von Parametern>
	// @except:(INTERNAL)
	//	<cv TCS_E_INVALIDPARAMETERCOUNT>
		[propget, id(3), helpstring("property ProjectionParameters")] HRESULT ProjectionParameters([out, retval] VARIANT *pVal);
		[propput, id(3), helpstring("property ProjectionParameters")] HRESULT ProjectionParameters([in] VARIANT newVal);

	// @doc PROPERTY TRIASCS ITRiASCSPCS
	// @property <t TRIASCSPROJECTIONPARAMETER> | ITRiASCSPCS | ProjectionParameter | 
	//		setzt / liest einen Parameter für den Projektionsalgorithmus 
	//	@head3 siehe auch |
	//		<l Setzen / Lesen von Parametern>
	// @except:(INTERNAL)
	//	<nl><cv TCS_E_INVALIDPARAMETERINDEX>
		[propget, id(4), helpstring("property ProjectionParameter")] HRESULT ProjectionParameter(TRIASCSPROJECTIONPARAMETER par, [out, retval] double *pVal);
		[propput, id(4), helpstring("property ProjectionParameter")] HRESULT ProjectionParameter(TRIASCSPROJECTIONPARAMETER par, [in] double newVal);
	};

///////////////////////////////////////////////////////////////////////////////
// @doc INTERFACE TRIASCS
// @interface ITRiASCSGCS | TRiAS Koordinatensysteme; geodätische Grundlage
// @group Methoden und Eigenschaften von <i ITRiASCSGCS>
// @index | ITRiASCSGCS 
// @doc ITRiASCSGCS
	[	
		object,
		uuid(73372653-E66A-11D1-8F40-0060085FC1CE),
		dual,
		helpstring("ITRiASCSGCS Interface"),
		pointer_default(unique)
	] 
	interface ITRiASCSGCS : IDispatch 
	{
	// @doc PROPERTY TRIASCS ITRiASCSGCS
	// @property <t TRIASCSUNITOFANGLE> | ITRiASCSGCS | UnitOfAngle | 
	//		setzt / liest die Maßeinheit für Winkelangaben
	// @except:(INTERNAL)
	//	<cv GCS_E_INVALIDUNITOFANGLE>
		[propget, id(1), helpstring("property UnitOfAngle")] HRESULT UnitOfAngle([out, retval] TRIASCSUNITOFANGLE *pVal);
		[propput, id(1), helpstring("property UnitOfAngle")] HRESULT UnitOfAngle([in] TRIASCSUNITOFANGLE newVal);

	// @doc PROPERTY TRIASCS ITRiASCSGCS
	// @property <t TRIASCSGEODETICDATUM> | ITRiASCSGCS | GeodeticDatum | 
	//		setzt / liest das Geodätische Datum
	// @except:(INTERNAL)
	//	<cv GCS_E_INVALIDGEODETICDATUM>
		[propget, id(2), helpstring("property GeodeticDatum")] HRESULT GeodeticDatum([out, retval] TRIASCSGEODETICDATUM *pVal);
		[propput, id(2), helpstring("property GeodeticDatum")] HRESULT GeodeticDatum([in] TRIASCSGEODETICDATUM newVal);

	// @doc PROPERTY TRIASCS ITRiASCSGCS
	// @property <t TRIASCSPRIMEMERIDIAN> | ITRiASCSGCS |  PrimeMeridian | 
	//		setzt / liest den 'PrimeMeridian'
	// @except:(INTERNAL)
	//	<cv GCS_E_INVALIDPRIMEMERIDIAN>
		[propget, id(3), helpstring("property PrimeMeridian")] HRESULT PrimeMeridian([out, retval] TRIASCSPRIMEMERIDIAN *pVal);
		[propput, id(3), helpstring("property PrimeMeridian")] HRESULT PrimeMeridian([in] TRIASCSPRIMEMERIDIAN newVal);

	// @doc PROPERTY TRIASCS ITRiASCSGCS
	// @property double | ITRiASCSGCS |  SemiMajorAxis | 
	//		setzt / liest die große Halbachse des Ellipsoids
	// @comm Diese Eigenschaft ist nur schreibbar, wenn das geodätische Datum
	//		auf <e TRIASCSGEODETICDATUM.tcsGD_UserDefined> und das Ellipsoid
	//		auf <e TRIASCSELLIPSOID.tcsEL_UserDefined> gesetzt ist.
	// @except:(INTERNAL)
	//	<cv TCS_E_CANNOTWRITEDATA>
		[propget, id(4), helpstring("property SemiMajorAxis")] HRESULT SemiMajorAxis([out, retval] double *pVal);
		[propput, id(4), helpstring("property SemiMajorAxis")] HRESULT SemiMajorAxis([in] double newVal);

	// @doc PROPERTY TRIASCS ITRiASCSGCS
	// @property double | ITRiASCSGCS | Flattening |
	//		setzt / liest die Ablattung des Ellipsoids
	// @comm Diese Eigenschaft ist nur schreibbar, wenn das geodätische Datum
	//		auf <e TRIASCSGEODETICDATUM.tcsGD_UserDefined> und das Ellipsoid
	//		auf <e TRIASCSELLIPSOID.tcsEL_UserDefined> gesetzt ist.
	// @except:(INTERNAL)
	//	<cv TCS_E_CANNOTWRITEDATA>
		[propget, id(5), helpstring("property Flattening")] HRESULT Flattening([out, retval] double *pVal);
		[propput, id(5), helpstring("property Flattening")] HRESULT Flattening([in] double newVal);

	// @doc PROPERTY TRIASCS ITRiASCSGCS
	// @property double | ITRiASCSGCS |  SemiMinorAxis | 
	//		liest die klein Halbachse des Ellipsoids
	// @comm Diese Eigenschaft wird aus den Parametern <op .SemiMajorAxis> und <op .Flattening> berechnet.
		[propget, id(6), helpstring("property SemiMinorAxis")] HRESULT SemiMinorAxis([out, retval] double *pVal);

	// @doc PROPERTY TRIASCS ITRiASCSGCS
	// @property <t TRIASCSELLIPSOID> | ITRiASCSGCS | Ellipsoid | 
	//		setzt / liest das dem Datum zugrundeliegende Ellipsoid
	// @comm Diese Eigenschaft ist nur schreibbar, wenn das geodätische Datum
	//		auf <e TRIASCSGEODETICDATUM.tcsGD_UserDefined> gesetzt ist.
	// @except:(INTERNAL)
	//	<cv TCS_E_CANNOTWRITEDATA>
	//	<nl><cv GCS_E_INVALIDELLIPSOID>
		[propget, id(7), helpstring("property Ellipsoid")] HRESULT Ellipsoid([out, retval] TRIASCSELLIPSOID *pVal);
		[propput, id(7), helpstring("property Ellipsoid")] HRESULT Ellipsoid([in] TRIASCSELLIPSOID newVal);
	};

///////////////////////////////////////////////////////////////////////////////
// @doc INTERFACE TRIASCS
// @interface ITRiASCS | TRiAS Koordinatensysteme; eigentliches Koordinatensystem
// @group Methoden und Eigenschaften von <i ITRiASCS>
// @index | ITRiASCS
// @doc ITRiASCS
	[
		object,
		uuid(AC3B1896-E585-11D1-8F3E-0060085FC1CE),
		dual,
		helpstring("ITRiASCS Interface"),
		pointer_default(unique)
	] 
	interface ITRiASCS : IDispatch 
	{
	// @doc PROPERTY TRIASCS ITRiASCS
	// @property <t TRIASCSTYPE> | ITRiASCS | CoordSystemType | setzt / liest den Typ des Koordinatensystems
	// @except:(INTERNAL)
	//	<cv CS_E_INVALIDCOORDSYSTEMTYPE>
		[propget, id(1), helpstring("Gets the Identifier for the spatial Model")] HRESULT CoordSystemType([out, retval] TRIASCSTYPE *pVal);
		[propput, id(1), helpstring("Sets the Identifier for the spatial Model")] HRESULT CoordSystemType([in] TRIASCSTYPE newVal);

	// @doc PROPERTY TRIASCS ITRiASCS
	// @property BSTR | ITRiASCS | GUID | setzt / liest den GUID des Koordinatensystems
	// @comm Diese Eigenschaft sollte, nachdem das Koordinatensystem einem Transformator
	//		als Eingangskoordinatensystem bekannt gemacht wurde <om ITRiASCSTransform.AddInputCS> ), <b nicht> mehr angwendet
	//		werden.
		[propget, id(2), helpstring("Gets the GUID for this CoordSystem Object")] HRESULT GUID([out, retval] BSTR* pVal);
		[propput, id(2), helpstring("Sets the GUID for this CoordSystem Object")] HRESULT GUID([in] BSTR pVal);

	// @doc PROPERTY TRIASCS ITRiASCS
	// @property <i ITRiASCSGCS> | ITRiASCS | GeographicCS | liefert die geodätische Grundlage des Koordinatensystems
		[propget, id(3), helpstring("property GeographicCS")] HRESULT GeographicCS([out, retval] ITRiASCSGCS **GCS);

	// @doc PROPERTY TRIASCS ITRiASCS
	// @property <i ITRiASCSPCS> | ITRiASCS | ProjectedCS | liefert die Projektion des Koordinatensystems
		[propget, id(4), helpstring("property ProjectedCS")] HRESULT ProjectedCS([out, retval] ITRiASCSPCS **PCS);

	// @doc PROPERTY TRIASCS ITRiASCS
	// @property <i ITRiASCSDatumTransformation> | ITRiASCS | DatumTransformation | liefert die Datumstransformation des Koordinatensystems
		[propget, id(5), helpstring("property DatumTransformation")] HRESULT DatumTransformation([out, retval] ITRiASCSDatumTransformation **pVal);

	// @doc METHOD TRIASCS ITRiASCS
	// @method HRESULT | ITRiASCS | ChangeGUID | 
	//		erzeugt einen neuen GUID für dieses Koordinatensystem. Der GUID kann mit <om .GUID> ausgelesen werden.
	// @rdesc
	//	<cv S_OK>
		[id(6), helpstring("Generates a new GUID for this CoordSystem Object")] HRESULT ChangeGUID();

	// @doc METHOD TRIASCS ITRiASCS
	// @method HRESULT | ITRiASCS | Recompute | 
	//		Wird gerufen nachdem alle Änderungen am Koordinatensystem vorgenommen wurden.
	// @rdesc
	//	<cv S_OK>
		[id(7), helpstring("Recomputes the Coordsystem")] HRESULT Recompute();

	// @doc PROPERTY TRIASCS ITRiASCS
	// @property BSTR | ITRiASCS | Description | setzt / liest eine Beschreibung des Koordinatensystems
		[propget, id(8), helpstring("property Description")] HRESULT Description([out, retval] BSTR *pVal);
		[propput, id(8), helpstring("property Description")] HRESULT Description([in] BSTR newVal);

	// @doc PROPERTY TRIASCS ITRiASCS
	// @property BSTR | ITRiASCS | Category | setzt / liest eine Beschreibung für eine Kategorie
	// @comm Die Eigenschaft Kategorie kann verwendet werden um eine Menge von Koordinatensystemen
	//		logisch zusammenzufassen. Im folgenden Beispiel werden in Koordinatensystemen
	//		mit Backslash getrennte Beschreibungen gesetzt. Diese Beschreibungen können anderweitig
	//		ausgelesen und damit das jeweilige Koordinatensystem (z.B. in einen Baum) eingeordnet werden.
	// @ex Beispiel für Category: |
	//	option base 0
	//	sub main()
	//		dim cs() as TRiASCS : redim cs(1 to 7)
	//		cs(0).Category = "Geodätisch"			: cs(0).Description = "WGS84"
	//		cs(1).Category = "Projektiv\Bessel"		: cs(1).Description = "9° / 3°"
	//		cs(2).Category = "Projektiv\Bessel"		: cs(2).Description = "12° / 3°"
	//		cs(3).Category = "Projektiv\Bessel"		: cs(3).Description = "15° / 3°"
	//		cs(4).Category = "Projektiv\Krassovski" : cs(4).Description = "3° / 6°"
	//		cs(5).Category = "Projektiv\Krassovski" : cs(5).Description = "9° / 6°"
	//		cs(6).Category = "Projektiv\Krassovski" : cs(6).Description = "15° / 6°"
	//	end sub
		[propget, id(9), helpstring("property Category")] HRESULT Category([out, retval] BSTR *pVal);
		[propput, id(9), helpstring("property Category")] HRESULT Category([in] BSTR newVal);

	// @doc METHOD TRIASCS ITRiASCS
	// @method HRESULT | ITRiASCS | SaveToFile | Koordinatensystem in Datei ablegen.
	// @normal Speichert das Koordinatensystem unter dem angegebenen Dateinamen ab.
		[id(10), helpstring("method SaveToFile")] HRESULT SaveToFile([in] BSTR strFile);

	// @doc METHOD TRIASCS ITRiASCS
	// @method HRESULT | ITRiASCS | LoadFromFile | Koordinatensystem aus Datei einlesen.
	// @normal Lädt das Koordinatensystem aus der gegebenen Datei.
		[id(11), helpstring("method LoadFromFile")] HRESULT LoadFromFile([in] BSTR strFileName);

	// @doc METHOD TRIASCS ITRiASCS
	// @method HRESULT | ITRiASCS | SaveToRegistry | Koordinatensystem in Registry ablegen
	// @normal Speichert das Koordinatensystem unter dem angegebenen Registrierungsschlüssel ab.
	// @comm Als arument wird nur der Registrierungsschlüssel angegeben. Die Daten Werden als Binärdaten
	//		unter der dem Wert 'InstalledSystems' abgelegt.
		[id(12), helpstring("method SaveToRegistry")] HRESULT SaveToRegistry([in] TCS_REGISTRYROOT root, [in] BSTR strRegKey, [in, optional] VARIANT strComputername);

	// @doc METHOD TRIASCS ITRiASCS
	// @method HRESULT | ITRiASCS | LoadFromRegistry | Koordinatensystem aus Registry lesen
	// @normal Lädt das Koordinatensystem aus dem angegebenen Registrierungsschlüssel.
		[id(13), helpstring("method LoadFromRegistry")] HRESULT LoadFromRegistry([in] TCS_REGISTRYROOT root, [in] BSTR strRegKey, [in, optional] VARIANT strComputername);

	// @doc METHOD TRIASCS ITRiASCS
	// @method HRESULT | ITRiASCS | IsEqual | Koordinatensystem mit anderem Koordinatensystem
	// vergleichen
	// @normal Vergleicht das Koordinatensystem mit dem als Parameter übergebenen.
		[id(14), helpstring("Koordinatensystem mit Anderem vergleichen")] HRESULT IsEqual([in] ITRiASCS *pIOther, [out, retval] VARIANT_BOOL *pfEqual);

	// @doc PROPERTY TRIASCS ITRiASCS
	// @property BSTR | ITRiASCS | Name | setzt / liest den Kurzbezeichner des Koordinatensystemes
		[propget, id(15), helpstring("property Name")] HRESULT Name([out, retval] BSTR *pVal);
		[propput, id(15), helpstring("property Name")] HRESULT Name([in] BSTR newVal);
	};

///////////////////////////////////////////////////////////////////////////////
// öffentliche, nicht Automation-fähige Interfaces
// Diese Interfaces werden durch TRiASCSTransform bereitgestellt

///////////////////////////////////////////////////////////////////////////////
// @doc INTERFACE TRIASCS
// @interface ITRiASRawCoordTransform | TRiAS Koordinatensysteme; direkte Koordinatentransformation
// @devnote Das Interfce <b ITRiASRawCoordTransform> ist <b nicht> OLE-Automation-kompatibel und
//		daher nicht von Visual-Basic aus anzusprechen.
// @group Methoden und Eigenschaften von <i ITRiASRawCoordTransform>
// @index | ITRiASRawCoordTransform
// @doc ITRiASRawCoordTransform
	[
		object,
		uuid(792D9030-F412-11d1-8F50-0060085FC1CE),
		helpstring("direkte Transformation von Koordinatenfeldern")
	] 
	interface ITRiASRawCoordTransform : IUnknown 
	{
	// @doc TRIASCS METHOD ITRiASRawCoordTransform
	// @method HRESULT | ITRiASRawCoordTransform | Transform | 
	//		transformiert ein Feld von Koordinaten in das Ausgangssystem des Transformators
	// @parm [in] <l CSGUID> | csGUID | 
	//		definiert das zu verwendende Eingangskoordinatensystem
	// @parm [in] long | nCoords | 
	//		Anzahl der zu transformierenden Koordinaten
	// @parm [in,size_is(3*nCoords)] double* | pInPoints | 
	//		Zeiger auf die zu transformierenden Koordinaten
	// @parm [in,out] double* | pOutPoints | 
	//		Zeiger auf Bereich, in dem die transformierten Koordinaten abzulegen sind
	// @rdesc
	//	siehe <om ITRiASCSTransform.Transform>
		HRESULT	Transform( [in] struct CSID csUID, [in] long nCoords, [in,size_is(nCoords)] CSCOORD* pInPoints, [in,out,size_is(nCoords)] CSCOORD* pOutPoints );

	// @doc TRIASCS METHOD ITRiASRawCoordTransform
	// @method HRESULT | ITRiASRawCoordTransform | TransformInverse | 
	//		transformiert ein Feld von Koordinaten aus dem Ausgangssystem des Transformators in das
	//		angegebene Eingangssystem (gesetzt mit <om ITRiASCSTransform.AddInputCS>)
	// @parm [in] <l CSGUID> | csGUID | 
	//		definiert das zu verwendende Eingangskoordinatensystem
	// @parm [in] long | nCoords | 
	//		Anzahl der zu transformierenden Koordinaten
	// @parm [in,size_is(3*nCoords)] double* | pInPoints | 
	//		Zeiger auf die zu transformierenden Koordinaten
	// @parm [in,out] double* | pOutPoints | 
	//		Zeiger auf Bereich, in dem die transformierten Koordinaten abzulegen sind
	// @rdesc
	//	siehe <om ITRiASCSTransform.TransformInverse>
		HRESULT	TransformInverse( [in] struct CSID csUID, [in] long nCoords, [in,size_is(nCoords)] CSCOORD* pInPoints, [in,out,size_is(nCoords)] CSCOORD* pOutPoints );
	}

///////////////////////////////////////////////////////////////////////////////
// @doc INTERFACE TRIASCS
// @interface ITRiASCSTransform | TRiAS Koordinatensysteme; Koordinatentransformation
// @group Eigenschaften von <i ITRiASCSTransform>
// @index | ITRIASCSTRANSFORM & PROPERTY
// @group Methoden von <i ITRiASCSTransform>
// @index | ITRIASCSTRANSFORM & METHOD
// @doc ITRIASCSTRANSFORM
	[ 
		object,
		uuid(24069B53-F3B9-11D1-8F50-0060085FC1CE),
		dual,
		helpstring("ITRiASCSTransform Interface (obsolete)"),
		pointer_default(unique),
		helpcontext(ITRiASCSTransform_int)
	] 
	interface ITRiASCSTransform0 : IDispatch 
	{
	// @doc PROPERTY TRIASCS ITRIASCSTRANSFORM
	// @property <i ITRiASCS> | ITRiASCSTransform | OutputCS | Die Eigenschaft <op .OutputCS> setzt bzw.
	// liest das Ausgangskoordinatensystem des Transformationsobjektes.
	// @except:(INTERNAL) 
	// <nl><cv E_POINTER> Das Koordinatensystem ist nicht gegeben (NULL).
	// @comm Das Ausgangskoordinatensystem ist im allgemeinen das Koordinatensystem, welches im aktuellen
	// <tr>- Projekt verwendet wird. Im Gegensatz dazu sind die Eingansgskoordinatensystem des 
	// Transformationsobjektes im allgemeinen den einzelnen Datenquellen des aktuellen Projektes zugeordnet.
	// @xref <i ITRiASCSTransform>, <om .AddInputCS>
		[propget, id(1), helpstring("Liest das Ausgangskoordinatensystem des Transformationsobjektes."), helpcontext(ITRiASCSTransform_OutputCS_prop)] HRESULT OutputCS([out, retval] ITRiASCS **TRiASCS);
		[propputref, id(1), helpstring("Setzt das Ausgangskoordinatensystem des Transformationsobjektes."), helpcontext(ITRiASCSTransform_OutputCS_prop)] HRESULT OutputCS([in] ITRiASCS *TRiASCS);

	// @doc METHOD TRIASCS ITRIASCSTRANSFORM
	// @method Sub | ITRiASCSTransform | AddInputCS | Die Methode <om .AddInputCS> fügt zu dem 
	// Transformationsobjekt ein weiteres Eingangskoordinatensystem hinzu.
	// @parm [in] <i ITRiASCS> | CS | Der Parameter <p CS> enthält das vorinitialisierte Koordinatensystem, 
	// welches zum Transformationsobjekt hinzugefügt werden soll.
	// @except:(INTERNAL) 
	// <nl><cv E_POINTER> Das Koordinatensystem ist nicht gegeben (NULL).
	// <nl><cv CST_E_INVALIDSOURCECOORDSYSTEM> Das übergebene Koordinatensystem ist ungültig.
	// <nl><cv CST_E_COORDSYSTEMALREADYPRESENT> Das zu registrierende Koordinatensystem ist bereits registriert.
	// @comm Ein Eingangskoordinatensystem wird häufig einer Datenquelle des aktuellen <tr>- Projektes 
	// zugeordnet. Im Gegensatzsatz dazu entspricht das Ausgangskoordinatensystem im allgemeinen dem 
	// <tr>- Projekt selbst.
	// @xref <i ITRiASCSTransform>, <op .OutputCS>
		[id(2), helpstring("Fügt ein Koordinatensystem zu dem Transformationsobjekt hinzu."), helpcontext(ITRiASCSTransform_AddInputCS_meth)] HRESULT AddInputCS([in] ITRiASCS *CS);

	// @doc METHOD TRIASCS ITRIASCSTRANSFORM
	// @method Sub | ITRiASCSTransform | RemoveInputCS | Die Methode <om .RemoveInputCS> entfernt das 
	// angegebene Eingangskoordinatensystem aus dem Transformationsobjekt.
	// @parm [in] String | strGUID | Der Parameter <p strGUID> enthält den GUID des aus dem
	// Transformationsobjekt zu entfernenden Koordinatensystems.
	// @except:(INTERNAL) 
	// <nl><cv E_INVALIDARG> Die übergebene Zeichenkette ist kein Guid im Format '{xxxx-xxxx-....}'
	// <nl><cv CST_E_COORDSYSTEMNOTFOUND> Es wurde kein Koordinatensystem gefunden, welches dem übergebenen
	// GUID zugeordnet ist.
	// @xref <i ITRiASCSTransform>
		[id(3), helpstring("Entfernt ein Eingangskoordinatensystem aus dem Transformationsobjekt."), helpcontext(ITRiASCSTransform_RemoveInputCS_meth)] HRESULT RemoveInputCS([in] BSTR strGUID);

	// @doc PROPERTY TRIASCS ITRIASCSTRANSFORM
	// @property Boolean | ITRiASCSTransform | IsValid | Die Eigenschaft <op .IsValid> überprüft, ob die 
	// Transformation vom gegebenen Eingangssystem zum Ausgangssystem möglich ist.
	// @parm [in] String | strGUID | Der Parameter <p strGUID> enthält den der GUID des zu testenden 
	// Eingangssystems.
	// @except:(INTERNAL)  
	// <nl><cv CST_E_COORDSYSTEMNOTFOUND> Es wurde kein Koordinatensystem gefunden, welches dem übergebenen
	// GUID zugeordnet ist.
	// <nl><cv CST_E_INVALIDSOURCECOORDSYSTEM> Das Eingangskoordinatensystem ist ungültig.
	// <nl><cv CST_E_INVALIDDESTINATIONCOORDSYSTEM> Das Ausgangskoordinatensystem ist ungültig.
	// @xref <i ITRiASCSTransform>
		[propget, id(4), helpstring("Überprüfen, ob die Transformation vom gegebenen Eingangssystem zum Ausgangssystem möglich ist."), helpcontext(ITRiASCSTransform_IsValid_prop)] HRESULT IsValid([in] BSTR strGUID, [out, retval] VARIANT_BOOL *pVal);

	// @doc METHOD TRIASCS ITRIASCSTRANSFORM
	// @method Sub | ITRiASCSTransform | RecomputeTransformations | Die Methode <om .RecomputeTransformations>
	// berechnet alle internen Transformationspfade neu.
	// @devnote Die Methode <om .RecomputeTransformations> ist veraltet und darf nicht mehr benutzt werden.
	// Zur Neuberechnung der Transformationspfade muß die Methode <om ITRiACS.Recompute> für eines der am
	// Transformationsobjekt registrierten Koordinatensystem (Ausgangskoordinatensystem oder 
	// Einganskoordinatensystem) gerufen werden.
	// @xref <i ITRiASCSTransform>
		[id(5), helpstring("Berechnet alle internen Transformationspfade neu (varaltet)."), hidden] HRESULT RecomputeTransformations();

	// @doc METHOD TRIASCS ITRIASCSTRANSFORM
	// @method Variant | ITRiASCSTransform | Transform | Die Methode <om .Transform> transformiert ein Feld 
	// von Koordinaten vom angegebenen Eingangssystem des Transformationsobjektes (gesetzt mit 
	// <om .AddInputCS>) in das Ausgangssystem des Transformationsobjektes.
	// @parm [in] String | strGUID | Der Parameter <p strGUID> definiert das zu verwendende 
	// Eingangskoordinatensystem.
	// @parm [in] Double() | InPoints | Der Parameter <p InPoints> enthält die zu transformierenden 
	// Koordinaten. Das übergebene Feld muß durch eine 'ReDim'- Anweisung eine Größe zugewiesen
	// bekommen haben, die durch 3 teilbar ist. Es wird davon ausgegangen, daß jeweils 3 aufeinanderfolgende
	// Elemente dieses Feldes ein Koordinaten-Tripel (X, Y, Z) enthalten.
	// @rdesc Die Methode <om .Transform> liefert ein Feld, in dem die transformierten Koordinaten 
	// abgelegt sind. Das Format des gelieferten Feldes entspricht dem des Parameters <p InPoints>. Die
	// Elemente des Feldes sind vom Typ Double.
	// @except:(INTERNAL)
	// <nl><cv E_INVALIDARG> Zeiger auf Quellkoordinaten ist ungültig (NULL)
	// <nl><cv E_POINTER> Zeiger auf Zielkoordinaten ist ungültig (NULL)
	// <nl><cv CST_E_COORDSYSTEMNOTFOUND> Es wurde kein Koordinatensystem gefunden, welches dem übergebenen
	// GUID zugeordnet ist.
	// <nl><cv CST_E_INVALIDCOORDCOUNT> Die Anzahl der Werte im Parameter <p InPoints> ist nicht durch 3 teilbar.
	// <nl><cv CST_E_INPUTTRANSFORMATIONFAILED>
	// <nl><cv CST_E_OUTPUTTRANSFORMATIONFAILED>
	// <nl><cv CST_E_INVALIDSOURCECOORDSYSTEM> Das Eingangskoordinatensystem ist ungültig.
	// <nl><cv CST_E_INVALIDDESTINATIONCOORDSYSTEM> Das Ausgangskoordinatensystem ist ungültig.
	// @xref <i ITRiASCSTransform>, <om .TransformInverse>
		[id(6), helpstring("Koordinatentransformation von einem der Einganssysteme zum Ausgangssystem."), helpcontext(ITRiASCSTransform_Transform_meth)] HRESULT Transform([in] BSTR strGUID, [in] VARIANT InPoints, [out, retval] VARIANT *OutPoints);

	// @doc METHOD TRIASCS ITRIASCSTRANSFORM
	// @method Variant | ITRiASCSTransform | TransformInverse | Die Methode <om .TransformInvers>
	// transformiert ein Feld von Koordinaten aus dem Ausgangssystem des Transformators in das
	// angegebene Eingangssystem des Transformationsobjektes (gesetzt mit <om ITRiASCSTransform.AddInputCS>).
	// @parm [in] String | strGUID | Der Parameter <p strGUID> definiert das zu verwendende 
	// Eingangskoordinatensystem.
	// @parm [in] Double() | InPoints | Der Parameter <p InPoints> enthält die zu transformierenden 
	// Koordinaten. Das übergebene Feld muß durch eine 'ReDim'- Anweisung eine Größe zugewiesen
	// bekommen haben, die durch 3 teilbar ist. Es wird davon ausgegangen, daß jeweils 3 aufeinanderfolgende
	// Elemente dieses Feldes ein Koordinaten-Tripel (X, Y, Z) enthalten.
	// @rdesc Die Methode <om .Transform> liefert ein Feld, in dem die transformierten Koordinaten 
	// abgelegt sind. Das Format des gelieferten Feldes entspricht dem des Parameters <p InPoints>. Die
	// Elemente des Feldes sind vom Typ Double.
	// @rdesc Die Methode <om .TransformInvers> liefert ein Feld, in dem die transformierten Koordinaten 
	// abgelegt sind. Das Format des gelieferten Feldes entspricht dem des Parameters <p InPoints>. Die
	// Elemente des Feldes sind vom Typ Double.
	// @except:(INTERNAL)
	// <nl><cv E_INVALIDARG> Zeiger auf Quellkoordinaten ist ungültig (NULL)
	// <nl><cv E_POINTER> Zeiger auf Zielkoordinaten ist ungültig (NULL)
	// <nl><cv CST_E_COORDSYSTEMNOTFOUND> Es wurde kein Koordinatensystem gefunden, welches dem übergebenen
	// GUID zugeordnet ist.
	// <nl><cv CST_E_INVALIDCOORDCOUNT> Die Anzahl der Werte im Parameter <p InPoints> ist nicht durch 3 teilbar.
	// <nl><cv CST_E_INPUTTRANSFORMATIONFAILED>
	// <nl><cv CST_E_OUTPUTTRANSFORMATIONFAILED>
	// <nl><cv CST_E_INVALIDSOURCECOORDSYSTEM>
	// <nl><cv CST_E_INVALIDDESTINATIONCOORDSYSTEM>
	// @xref <i ITRiASCSTransform>, <om .Transform>
		[id(7), helpstring("Koordinatentransformation vom Ausgangssystem zu einem der Einganssysteme."), helpcontext(ITRiASCSTransform_TransformInverse_meth)] HRESULT TransformInverse([in] BSTR strGUID, [in] VARIANT InPoints, [out, retval] VARIANT *OutPoints);

	// @doc METHOD TRIASCS ITRIASCSTRANSFORM
	// @method HRESULT | ITRiASCSTransform | ShutDown | Gibt sämtliche durch diesen Transformator
	// intern benötigten Resourcen sowie sämtliche enthaltenen Koordinatensysteme frei.
	// @devnote Die Methode <om .ShutDown> muß unbedingt vor dem entgültigen Freigeben des 
	// Transformators gerufen werden, da ansonsten die internen Resourcen nicht freigegeben werden 
	// können.
	// @xref <i ITRiASCSTransform>
		[id(8), helpstring("Freigeben sämtlicher Koordinatensystem und Resourcen."), helpcontext(ITRiASCSTransform_ShutDown_meth)] HRESULT ShutDown();

	// @doc METHOD TRIASCS ITRIASCSTRANSFORM
	// @method HRESULT | ITRiASCSTransform | GetGoodEnvelope | 
	//		Liefert einen (hoffentlich) gut passenden Container für das Koordinatensystem. Dieser
	//		Container bezieht sich immer auf das festegelegte Ausgangskoordinatensystem.
	//		Wurde bisher noch kein passender Container definiert werden Standardwerte aus
	//		[HKCR\Software\{Company}\{Product}\Config\DefaultEnvelope] entnommen. Als Standard ist 
	//		voreingestellt:
	// @ex Beispiel für einen Registrierungseintrag |
	// [HKEY_CURRENT_USER\Software\{Company}\{Product}\CoordTransform\DefaultEnvelope]
	// \@="Deutschland gesamt, WGS84 Dezimalgrad"
	// "XMin"="6"
	// "XMax"="15"
	// "YMin"="40"
	// "YMax"="55"
	// @rdesc
	//	<cv S_OK>
	// @xref <i ITRiASCSTransform>
		[id(9)] HRESULT GetGoodEnvelope([in,out] double *lowerLeftX, [in,out] double *lowerLeftY, [in,out] double *upperRightX, [in,out] double *upperRightY );

	// @doc METHOD TRIASCS ITRIASCSTRANSFORM
	// @method HRESULT | ITRiASCSTransform | SetGoodEnvelope | 
	//		Setzt für das Koordinatensystem einen gut passenden Container
	// @rdesc
	//	<cv S_OK>
	// @xref <i ITRiASCSTransform>
		[id(10)] HRESULT SetGoodEnvelope([in] double lowerLeftX, [in] double lowerLeftY, [in] double upperRightX, [in] double upperRightY );
	};

///////////////////////////////////////////////////////////////////////////////
// @doc INTERFACE TRIASCS
	[
		object,
		uuid(0D9D0690-3AA1-11d3-99A1-0060085FC1CE),
		dual,
		helpstring("ITRiASCSTransform Interface"),
		pointer_default(unique)
	] 
	interface ITRiASCSTransform : ITRiASCSTransform0 
	{
	// @doc METHOD TRIASCS ITRiASCSTransform
	// @method HRESULT | ITRiASCSTransform | Count | Liefert die Anzahl der registrierten Eingangskoordinatensysteme
	// @rdesc
	//	<cv S_OK>
		[propget] HRESULT Count([out, retval] long* lpCount);

	// @doc METHOD TRIASCS ITRiASCSTransform
	// @method HRESULT | ITRiASCSTransform | Item | 
	//		liefert das Eingangskoordinatensystem welches unter einem bestimmten GUID registriert
	//		ist
	// @rdesc
	//	<cv S_OK>
		[propget, id(DISPID_VALUE)] HRESULT Item([in] VARIANT vIndex, [out, retval] VARIANT* pTRiASCS);

	// @doc METHOD TRIASCS ITRiASCSTransform
	// @method HRESULT | ITRiASCSTransform | _NewEnum | 
	//		liefert einen Enumerator über alle Eingangskoordinatensysteme; der Enumerator ist
	//		vom Typ IEnumUnknown.
	// @rdesc
	//	<cv S_OK>
		[propget, id(DISPID_NEWENUM), restricted] HRESULT _NewEnum([out,retval] IUnknown ** ppEnum);

	// @doc METHOD TRIASCS ITRiASCSTransform
	// @method HRESULT | ITRiASCSTransform | Add | Fügt ein Eingangskoordinatensystem hinzu
	// @rdesc
	//	<cv S_OK>
		HRESULT Add([in] VARIANT vCS);

	// @doc METHOD TRIASCS ITRiASCSTransform
	// @method HRESULT | ITRiASCSTransform | Remove | Entfernt ein Eingangskoordinatensystem
	// @rdesc
	//	<cv S_OK>
		HRESULT Remove([in] VARIANT CS);
	};

///////////////////////////////////////////////////////////////////////////////
// @doc INTERFACE TRIASCS
// @interface ITRiASTransformGeometry | TRiAS Koordinatensysteme
//		ein allgemeines Interface um Koordinaten zu transformieren.
//		Dieses Interface wird von den Koordinatenservices selbst nicht genutzt.
//		Ein Geometrieobjekt kann allerdings dieses Interface bereitstellen
//		um 'sich selbst' zu transformieren.
// @group Methoden und Eigenschaften von <i ITRiASCSTransform>
// @index | ITRiASTransformGeometry
// @doc ITRiASTransformGeometry
	[
		object,
		uuid(6FABC490-4904-11d2-8FB8-0060085FC1CE),
		helpstring("ITRiASTransformGeometry Interface"),
		pointer_default(unique)
	] 
	interface ITRiASTransformGeometry : IUnknown {
	// @doc TRIASCS METHOD ITRiASTransformGeometry
	// @method HRESULT | ITRiASTransformGeometry | Transform | 
	//		transformiert ein Feld von Koordinaten in das Ausgangssystem des Transformators
	// @parm [in] <l CSGUID> | csGUID | 
	//		das zu verwendende Eingangskoordinatensystem
	// @parm [in] <l ITRiASCSTransform> | *pCSTransform | 
	//		das zu verwendende Transformationsobjekt
	// @rdesc
	//	siehe <om ITRiASCSTransform.Transform>
		HRESULT Transform( [in] struct CSID coordsysGUID, [in] ITRiASCSTransform *pCSTransform );

	// @doc TRIASCS METHOD ITRiASTransformGeometry
	// @method HRESULT | ITRiASTransformGeometry | TransformInverse | 
	//		transformiert ein Feld von Koordinaten aus dem Ausgangssystem des Transformators in das
	//		angegebene Eingangssystem (gesetzt mit <om ITRiASCSTransform.AddInputCS>)
	// @parm [in] <l CSGUID> | csGUID | 
	//		definiert das zu verwendende Eingangskoordinatensystem
	// @parm [in] <l ITRiASCSTransform> | *pCSTransform | 
	//		das zu verwendende Transformationsobjekt
	// @rdesc
	//	siehe <om ITRiASCSTransform.TransformInverse>
		HRESULT TransformInverse( [in] struct CSID coordsysGUID, [in] ITRiASCSTransform *pCSTransform );
	};

// @doc
	[ 
		object,
		uuid(AE998A03-1127-11D2-8F75-0060085FC1CE),
		helpstring("ITRiASCSUI Interface"),
		pointer_default(unique)
	] 
	interface ITRiASCSUI : IDispatch {
		[propputref, id(DISPID_FONT)]
		HRESULT Font([in]IFontDisp* pFont);
		[propput, id(DISPID_FONT)]
		HRESULT Font([in]IFontDisp* pFont);
		[propget, id(DISPID_FONT)]
		HRESULT Font([out, retval]IFontDisp** ppFont);
	};
	
///////////////////////////////////////////////////////////////////////////////
// Coclasses

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECT TRIASCS
// @object TRiASCS | TRiAS Koordinatensysteme; Koordinatensystem
// @head3 Interfaces |
// <i ITRiASCS>
// @head3 Konstanten |
// <t TRIASCSTYPE>
	[
		uuid(AC3B1897-E585-11D1-8F3E-0060085FC1CE),
		helpstring("TRiAS Coordinate System"),
		helpcontext(TRiASCS_obj)
	] 
	coclass TRiASCS 
	{
		[default] interface ITRiASCS;
		interface ISpatialReferenceInfo;
	};

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECT TRIASCS
// @object TRiASCSGCS | TRiAS Koordinatensysteme; geodätische Grundlage
// @head3 Interfaces |
// <i ITRiASCSGCS>
// @head3 Konstanten |
// <t TRIASCSGEODETICDATUM>
// <nl><t TRIASCSELLIPSOID>
	[
		uuid(73372654-E66A-11D1-8F40-0060085FC1CE),
		helpstring("TRiAS Geographic spatial Model"),
		helpcontext(TRiASCSGCS_obj)
	] 
	coclass TRiASCSGCS 
	{
		[default] interface ITRiASCSGCS;
		interface ISpatialReferenceInfo;
	};

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECT TRIASCS
// @object TRiASCSPCS | TRiAS Koordinatensysteme; projektives Koordinatensystem
// @head3 Interfaces |
// <i ITRiASCSPCS>
// @head3 Konstanten |
// <t TRIASCSPROJECTIONALGORITHM>
// <nl><t TRIASCSPROJECTIONPARAMETER>
	[
		uuid(4E1A7104-E993-11D1-8F48-0060085FC1CE),
		helpstring("TRiAS Projected spatial Model"),
		helpcontext(TRiASCSPCS_obj)
	] 
	coclass TRiASCSPCS 
	{
		[default] interface ITRiASCSPCS;
		interface ISpatialReferenceInfo;
	};

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECT TRIASCS
// @object TRiASCSTransform | TRiAS Koordinatensysteme; Koordinatentransformator
// @head3 Interfaces |
// <i ITRiASCSTransform>
// <nl><i ITRiASRawCoordTransform>
	[
		uuid(24069B54-F3B9-11D1-8F50-0060085FC1CE),
		helpstring("TRiAS geographic CoordTransform"),
		helpcontext(TRiASCSTransform_obj)
	] 
	coclass TRiASCSTransform 
	{
		[default] interface ITRiASCSTransform;
		interface ITRiASRawCoordTransform;
	};

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECT TRIASCS
// @object TRiASCSDatumTransformation | TRiAS Koordinatensysteme; Datumstransformation
// @head3 Interfaces |
// <i ITRiASCSDatumTransformation>
// @head3 Konstanten |
// <t TRIASCSDTRANSALGORITHM>
// <nl><t TRIASCSDTRANSPARAMETER>
	[
		uuid(E5AC8734-0769-11D2-8F5E-0060085FC1CE),
		helpstring("TRiASCSDatumTransformation")
	] 
	coclass TRiASCSDatumTransformation 
	{
		[default] interface ITRiASCSDatumTransformation;
	};

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECT TRIASCS
// @object TRIASCSSet | TRiAS Koordinatensysteme; Sammlung von Koordinatensystemen
// @head3 Interfaces |
// <i ITRIASCSSet>
// @head3 Konstanten |
	[ 
		uuid(2FB28CB6-89D8-11D2-9894-0060085FC1CE),
		helpstring("TRiASCSSet"),
		helpcontext(TRiASCSSet_obj)
	] 
	coclass TRiASCSSet 
	{
		[default] interface ITRiASCSSet;
	};
	
///////////////////////////////////////////////////////////////////////////////
// @doc
	[	
		uuid(AE998A04-1127-11D2-8F75-0060085FC1CE),
		helpstring("TRiASCSUI Class"),
	] 
	coclass TRiASCSUI 
	{
		[default] interface ITRiASCSUI;
	};
	
	[ uuid(F2FF1AF3-0FF1-11D2-8F6D-0060085FC1CE),
		helpstring("TRiASCSPropertyPage")
	] coclass TRiASCSPpg {
		interface IUnknown;
	};
	
	[ uuid(B1C41973-11C4-11D2-8F75-0060085FC1CE),
		helpstring("TRiASGCSPpg Class")
	] coclass TRiASGCSPpg {
		interface IUnknown;
	};
	
	[ uuid(59E3C095-13F7-11D2-8F77-0060085FC1CE),
		helpstring("TRiASPCSPpg Class")
	] coclass TRiASPCSPpg {
		interface IUnknown;
	};

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECT TRIASCS
// @object TRiASCSUIService | Ein Datenobjekt vom Typ <o TRiASCSUIService> stellt verschiedene
// Methoden zur Verfügung, mit deren Hilfe sich Eingabe- bzw. Ausgabeoperationen für Koordinatenwerte
// in einer Oberfläche besser realisieren lassen.
// @supint <i ITRiASCSUIHelper> | Über das Interface <i ITRiASCSUIHelper> sind sämtliche Eigenschaften
// und Methoden des Objektes <o TRiASCSUIService> verfügbar. 
// @comm Die Berechnungen erfolgen auf der Grundlage der Koordinatensysteme, in denen die einzelnen
// Koordinatenwerte gegeben sind.
	[ 
		uuid(D7BF4727-14CB-474E-AAFD-C1202E3EC3C8),
		helpstring("TRiASCSUIService Class") 
	]
	coclass TRiASCSUIService
	{
		[default] interface ITRiASCSUIService;
	};

#if defined(_USE_WKTSERVICE)
///////////////////////////////////////////////////////////////////////////////
// @doc OBJECT TRIASCS
// @object TRiASCSWktService | Ein Datenobjekt vom Typ <o TRiASCSWktService> stellt 
// verschiedene Funktionen zur Verfügung, mit deren Hilfe ein <o TRiASCS> -Objekt
// in eine textliche Repräsentation (wkt steht 'well known text') bzw. eine textliche
// Repräsentation eines Koordinatensystemes in ein <o TRiASCS> -Objekt umgewandelt werden
// können.
// @supint <i ITRiASCSWktService> | Über das Interface <i ITRiASCSWktService> sind sämtliche
// Eigenschaften und Methoden des Objektes <o TRiASCSWktService> verfügbar.
// @comm Die textliche Repräsentation, die durch das <o TRiASCSWktService> -Objekt erzeugt bzw.
// interpretiert werden kann, entspricht dem durch das OGC standardisierten WKT-Format
// für Koordinatensysteme (s. OpenGIS® Simple Feature Specification For SQL, Open GIS Consortium, Inc.
// Revision 1.0, 13. March 1998, pp. 3-28, 3-29, Chapter 3.4 Well-known Text
// Representation of Spatial Reference Systems).
// @xref <o TRiASCS>, <i ITRiASCSWktService>
	[
		uuid(EF402E92-99D1-4B83-981C-7F53C7F6243E),
		helpstring("TRiASCSWktService Class"),
		helpcontext(TRiASCSWktService_obj)
	]
	coclass TRiASCSWktService
	{
		[default] interface ITRiASCSWktService;
	};
#endif // defined(_USE_WKTSERVICE)

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECT TRIASCS
// @object TRiASCSDistanceService | Ein Datenobjekt vom Typ <o TRiASCSDistanceService> stellt
// verschiedenen Methoden zur Verfügung, mit deren Hilfe sich Abstände, Längen bzw. Flächeninhalte
// berechnen lassen. 
// @supint <i ITRiASCSDistanceService> | Über das Interface <i ITRiASCSDistanceService> sind
// sämtliche Eigenschaften und Methoden eines Objektes vom Typ <o TRiASCSDistanceService> verfügbar.
// @comm Die Berechnungen erfolgen auf der Grundlage der Koordinatensysteme, in denen die einzelnen
// Koordinaten gegeben sind.
// @xref <i ITRiASCSDistanceService>
	[
		uuid(4F4DF03D-3863-4808-8606-4F7513033066),
		helpstring("TRiASCSDistanceService Class"),
		helpcontext(TRiASCSDistanceService_obj)
	]
	coclass TRiASCSDistanceService
	{
		[default] interface ITRiASCSDistanceService;
	};

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECT TRIASCS
// @object TRiASCSTransformService | Ein Datenobjekt vom Typ <o TRiASCSTransformService> stellt 
// Funktionen zur Verfügung, die es VB-Clients ermöglichen, Geometrieobjekte direkt durch eine
// Koordinatentransformationspipe verarbeiten zu lassen
// @xref <i ITRiASCSTransformService>
	[ 
		uuid(71B8F28B-10AE-406E-9679-796A63805801), 
		helpstring("TRiASCSTransformService Object") 
	]
	coclass TRiASCSTransformService
	{
		[default] interface ITRiASCSTransformService;
	};
};

///////////////////////////////////////////////////////////////////////////////
// internes Interface für CTRiASCS, CTRiASPCS und CDatumTransformation
[
	object
	, uuid(2E02D030-F707-11d1-8F51-0060085FC1CE)
]
interface ITRiASCSTransformData : IUnknown {
	[helpstring("Transformation LLH zu PCS")] HRESULT Transform( [in] long nCoords, [in,out,size_is(nCoords)] CSCOORD* pCoords /*, [in,defaultvalue(FALSE)] BOOL bTransformDatum*/ );
	[helpstring("Transformation PCS zu LLH")] HRESULT TransformInverse( [in] long nCoords, [in,out,size_is(nCoords)] CSCOORD* pCoords /*, [in,defaultvalue(FALSE)] BOOL bTransformDatum */);
}

[
	object
	, uuid(3B94F3B0-48CF-11d2-8FB8-0060085FC1CE)
]
interface ITRiASCSValidate : IUnknown {
	[helpstring("Interne Überprüfung des Koordinatensystems")] HRESULT IsValid( );
	[helpstring("interne Neuberechnung der Transformation")] HRESULT RecomputeTransformation([in,defaultvalue(0)] ITRiASCSGCS *pGCS );
}

[
	object
	, uuid(0132E710-4E41-11d2-8FC0-0060085FC1CE)
]
interface ITRiASCSValidateDatum : ITRiASCSValidate {
	[helpstring("Konsolidieren der Datumstransformation")] HRESULT RecomputeDatumTransformation([in] ITRiASCSGCS *pSrcGCS, [in] ITRiASCSGCS *pDstGCS, [in] ITRiASCSDatumTransformation *pDstDTrans );
}

[
	object
	, uuid(9BCD9BF2-1712-11d2-8F79-0060085FC1CE)
]
interface ITRiASCSTransformInfo : IUnknown {
	[helpstring("method CanTransform")] HRESULT CanTransform([in] LONG typeOfTransformation);
}


/***********************************************************************
// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 25.09.2000 11:27:37 
//
// @doc
// @module EPSG.h | Declaration of the <c CEPSG> class

#if !defined(_EPSG_H__AE14AAAB_D399_427C_8F3C_5CEA6E5900C1__INCLUDED_)
#define _EPSG_H__AE14AAAB_D399_427C_8F3C_5CEA6E5900C1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

cpp_quote("typedef struct { long code; LPCTSTR name; } CODENAME;")
cpp_quote("typedef struct { long code; long param; } CODEPARAM;")

cpp_quote("#if defined(__cplusplus)")
cpp_quote("typedef const CODENAME const *LPCCODENAME;")
cpp_quote("typedef const CODEPARAM const *LPCCODEPARAM;")
cpp_quote("const short tcsPP_SizeOfParameterSet = 35;")
cpp_quote("#else")
cpp_quote("typedef CODENAME const *LPCCODENAME;")
cpp_quote("typedef CODEPARAM const *LPCCODEPARAM;")
cpp_quote("#define tcsPP_SizeOfParameterSet 35")
cpp_quote("#endif // defined(__cplusplus)")

cpp_quote("typedef struct PARAMETERSET { double p[tcsPP_SizeOfParameterSet];} PARAMETERSET;")

cpp_quote("#if defined(__cplusplus)")
cpp_quote("typedef const PARAMETERSET const *LPCPARAMETERSET;")
cpp_quote("typedef struct { long code; PARAMETERSET p; } CODEPARAMSET;")
cpp_quote("typedef const CODEPARAMSET const *LPCCODEPARAMSET;")
cpp_quote("#else")
cpp_quote("typedef PARAMETERSET const *LPCPARAMETERSET;")
cpp_quote("typedef struct { long code; PARAMETERSET p; } CODEPARAMSET;")
cpp_quote("typedef CODEPARAMSET const *LPCCODEPARAMSET;")
cpp_quote("#endif // defined(__cplusplus)")

cpp_quote("extern CODENAME _CT_TRIASCSUNITOFANGLE[];")

// @doc ENUM TRIASCS
// @enum TRIASCSUNITOFANGLE | TRIASCSUNITOFANGLE
typedef enum TRIASCSUNITOFANGLE {
	tcsUOA_Undefined = -1,		// @emem Wert ist nicht definiert
	tcsUOA_Radian = 9101,		// @emem radian
	tcsUOA_Degree = 9102,		// @emem degree
	tcsUOA_ArcMinute = 9103,	// @emem arc-minute
	tcsUOA_ArcSecond = 9104,	// @emem arc-second
	tcsUOA_Grad = 9105,			// @emem grad
	tcsUOA_Gon = 9106,			// @emem gon
	tcsUOA_DMS = 9107,			// @emem DMS
	tcsUOA_DMSH = 9108,			// @emem DMSH
	tcsUOA_Microradian = 9109,	// @emem microradian
	tcsUOA_DDDMMSSsss = 9110,	// @emem DDD.MMSSsss
	tcsUOA_Second = 32769,		// @emem Second
} TRIASCSUNITOFANGLE;
cpp_quote("extern CODENAME _CT_TRIASCSDTRANSALGORITHM[];")

// @doc ENUM TRIASCS
// @enum TRIASCSDTRANSALGORITHM | TRIASCSDTRANSALGORITHM
typedef enum TRIASCSDTRANSALGORITHM {
	tcsDTA_Undefined = -1, // @emem Wert ist nicht definiert
	tcsDTA_LongitudeRotation = 9601, // @emem Longitude rotation
	tcsDTA_GeodeticGeocentricConversions = 9602, // @emem Geodetic/geocentric conversions
	tcsDTA_GeocentricTranslations = 9603, // @emem Geocentric translations
	tcsDTA_Molodenski = 9604, // @emem Molodenski
	tcsDTA_AbridgedMolodenski = 9605, // @emem Abridged Molodenski
	tcsDTA_PositionVector7ParamTransformation = 9606, // @emem Position Vector 7-param. transformation
	tcsDTA_CoordinateFrame7ParamTransformation = 9607, // @emem Coordinate Frame 7-param. transformation
	tcsDTA_SimilarityTransform = 9608, // @emem Similarity transform
	tcsDTA_2DimensionalAffineTransformation = 9609, // @emem 2-dimensional Affine transformation
	tcsDTA_2ndOrderPolynomialFunction = 9610, // @emem 2nd-order Polynomial function
	tcsDTA_3rdOrderPolynomialFunction = 9611, // @emem 3rd-order Polynomial function
	tcsDTA_4thOrderPolynomialFunction = 9612, // @emem 4th-order Polynomial function
	tcsDTA_NADCON = 9613, // @emem NADCON
	tcsDTA_CanadaNTv1 = 9614, // @emem Canada NTv1
	tcsDTA_CanadaNTv2 = 9615, // @emem Canada NTv2
	tcsDTA_VerticalOffset = 9616, // @emem Vertical Offset
} TRIASCSDTRANSALGORITHM;
cpp_quote("extern CODENAME _CT_TRIASCSELLIPSOID[];")

// @doc ENUM TRIASCS
// @enum TRIASCSELLIPSOID | TRIASCSELLIPSOID
typedef enum TRIASCSELLIPSOID {
	tcsEL_Undefined = -1, // @emem Wert ist nicht definiert
	tcsEL_Airy1830 = 7001, // @emem Airy 1830
	tcsEL_AiryModified1849 = 7002, // @emem Airy Modified 1849
	tcsEL_AustralianNationalSpheroid = 7003, // @emem Australian National Spheroid
	tcsEL_Bessel1841 = 7004, // @emem Bessel 1841
	tcsEL_BesselModified = 7005, // @emem Bessel Modified
	tcsEL_BesselNamibia = 7006, // @emem Bessel Namibia
	tcsEL_Clarke1858 = 7007, // @emem Clarke 1858
	tcsEL_Clarke1866 = 7008, // @emem Clarke 1866
	tcsEL_Clarke1866Michigan = 7009, // @emem Clarke 1866 Michigan
	tcsEL_Clarke1880Benoit = 7010, // @emem Clarke 1880 (Benoit)
	tcsEL_Clarke1880IGN = 7011, // @emem Clarke 1880 (IGN)
	tcsEL_Clarke1880RGS = 7012, // @emem Clarke 1880 (RGS)
	tcsEL_Clarke1880Arc = 7013, // @emem Clarke 1880 (Arc)
	tcsEL_Clarke1880SGA1922 = 7014, // @emem Clarke 1880 (SGA 1922)
	tcsEL_Everest18301937Adjustment = 7015, // @emem Everest 1830 (1937 Adjustment)
	tcsEL_Everest18301967Definition = 7016, // @emem Everest 1830 (1967 Definition)
	tcsEL_Everest18301975Definition = 7017, // @emem Everest 1830 (1975 Definition)
	tcsEL_Everest1830Modified = 7018, // @emem Everest 1830 Modified
	tcsEL_GRS1980 = 7019, // @emem GRS 1980
	tcsEL_Helmert1906 = 7020, // @emem Helmert 1906
	tcsEL_IndonesianNationalSpheroid = 7021, // @emem Indonesian National Spheroid
	tcsEL_International1924 = 7022, // @emem International 1924
	tcsEL_Krassowsky1940 = 7024, // @emem Krassowsky 1940
	tcsEL_NWL9D = 7025, // @emem NWL 9D
	tcsEL_NWL10D = 7026, // @emem NWL 10D
	tcsEL_Plessis1817 = 7027, // @emem Plessis 1817
	tcsEL_Struve1860 = 7028, // @emem Struve 1860
	tcsEL_WarOffice = 7029, // @emem War Office
	tcsEL_WGS84 = 7030, // @emem WGS 84
	tcsEL_GEM10C = 7031, // @emem GEM 10C
	tcsEL_OSU86F = 7032, // @emem OSU86F
	tcsEL_OSU91A = 7033, // @emem OSU91A
	tcsEL_Clarke1880 = 7034, // @emem Clarke 1880
	tcsEL_Sphere = 7035, // @emem Sphere
	tcsEL_GRS1967 = 7036, // @emem GRS 1967
	tcsEL_AverageTerrestrialSystem1977 = 7041, // @emem Average Terrestrial System 1977
	tcsEL_UserDefined = 32769,  // @emem User Defined
} TRIASCSELLIPSOID;
cpp_quote("extern CODENAME _CT_TRIASCSGEODETICDATUM[];")

// @doc ENUM TRIASCS
// @enum TRIASCSGEODETICDATUM | TRIASCSGEODETICDATUM
typedef enum TRIASCSGEODETICDATUM {
	tcsGD_Undefined = -1, // @emem Wert ist nicht definiert
	tcsGD_NotSpecifiedBasedOnEllipsoid7001 = 6001, // @emem Not specified (based on ellipsoid 7001)
	tcsGD_NotSpecifiedBasedOnEllipsoid7002 = 6002, // @emem Not specified (based on ellipsoid 7002)
	tcsGD_NotSpecifiedBasedOnEllipsoid7003 = 6003, // @emem Not specified (based on ellipsoid 7003)
	tcsGD_NotSpecifiedBasedOnEllipsoid7004 = 6004, // @emem Not specified (based on ellipsoid 7004)
	tcsGD_NotSpecifiedBasedOnEllipsoid7005 = 6005, // @emem Not specified (based on ellipsoid 7005)
	tcsGD_NotSpecifiedBasedOnEllipsoid7006 = 6006, // @emem Not specified (based on ellipsoid 7006)
	tcsGD_NotSpecifiedBasedOnEllipsoid7007 = 6007, // @emem Not specified (based on ellipsoid 7007)
	tcsGD_NotSpecifiedBasedOnEllipsoid7008 = 6008, // @emem Not specified (based on ellipsoid 7008)
	tcsGD_NotSpecifiedBasedOnEllipsoid7009 = 6009, // @emem Not specified (based on ellipsoid 7009)
	tcsGD_NotSpecifiedBasedOnEllipsoid7010 = 6010, // @emem Not specified (based on ellipsoid 7010)
	tcsGD_NotSpecifiedBasedOnEllipsoid7011 = 6011, // @emem Not specified (based on ellipsoid 7011)
	tcsGD_NotSpecifiedBasedOnEllipsoid7012 = 6012, // @emem Not specified (based on ellipsoid 7012)
	tcsGD_NotSpecifiedBasedOnEllipsoid7013 = 6013, // @emem Not specified (based on ellipsoid 7013)
	tcsGD_NotSpecifiedBasedOnEllipsoid7014 = 6014, // @emem Not specified (based on ellipsoid 7014)
	tcsGD_NotSpecifiedBasedOnEllipsoid7015 = 6015, // @emem Not specified (based on ellipsoid 7015)
	tcsGD_NotSpecifiedBasedOnEllipsoid7016 = 6016, // @emem Not specified (based on ellipsoid 7016)
	tcsGD_NotSpecifiedBasedOnEllipsoid7017 = 6017, // @emem Not specified (based on ellipsoid 7017)
	tcsGD_NotSpecifiedBasedOnEllipsoid7018 = 6018, // @emem Not specified (based on ellipsoid 7018)
	tcsGD_NotSpecifiedBasedOnEllipsoid7019 = 6019, // @emem Not specified (based on ellipsoid 7019)
	tcsGD_NotSpecifiedBasedOnEllipsoid7020 = 6020, // @emem Not specified (based on ellipsoid 7020)
	tcsGD_NotSpecifiedBasedOnEllipsoid7021 = 6021, // @emem Not specified (based on ellipsoid 7021)
	tcsGD_NotSpecifiedBasedOnEllipsoid7022 = 6022, // @emem Not specified (based on ellipsoid 7022)
	tcsGD_NotSpecifiedBasedOnEllipsoid7024 = 6024, // @emem Not specified (based on ellipsoid 7024)
	tcsGD_NotSpecifiedBasedOnEllipsoid7025 = 6025, // @emem Not specified (based on ellipsoid 7025)
	tcsGD_NotSpecifiedBasedOnEllipsoid7026 = 6026, // @emem Not specified (based on ellipsoid 7026)
	tcsGD_NotSpecifiedBasedOnEllipsoid7027 = 6027, // @emem Not specified (based on ellipsoid 7027)
	tcsGD_NotSpecifiedBasedOnEllipsoid7028 = 6028, // @emem Not specified (based on ellipsoid 7028)
	tcsGD_NotSpecifiedBasedOnEllipsoid7029 = 6029, // @emem Not specified (based on ellipsoid 7029)
	tcsGD_NotSpecifiedBasedOnEllipsoid7030 = 6030, // @emem Not specified (based on ellipsoid 7030)
	tcsGD_NotSpecifiedBasedOnEllipsoid7031 = 6031, // @emem Not specified (based on ellipsoid 7031)
	tcsGD_NotSpecifiedBasedOnEllipsoid7032 = 6032, // @emem Not specified (based on ellipsoid 7032)
	tcsGD_NotSpecifiedBasedOnEllipsoid7033 = 6033, // @emem Not specified (based on ellipsoid 7033)
	tcsGD_NotSpecifiedBasedOnEllipsoid7034 = 6034, // @emem Not specified (based on ellipsoid 7034)
	tcsGD_NotSpecifiedBasedOnEllipsoid7035 = 6035, // @emem Not specified (based on ellipsoid 7035)
	tcsGD_NotSpecifiedBasedOnEllipsoid7036 = 6036, // @emem Not specified (based on ellipsoid 7036)
	tcsGD_Greek = 6120, // @emem Greek
	tcsGD_GreekGeodeticReferenceSystem1987 = 6121, // @emem Greek Geodetic Reference System 1987
	tcsGD_AverageTerrestrialSystem1977 = 6122, // @emem Average Terrestrial System 1977
	tcsGD_Kartastokoordinaattijarjestelma = 6123, // @emem Kartastokoordinaattijarjestelma
	tcsGD_RiketsKoordinatsystem1990 = 6124, // @emem Rikets koordinatsystem 1990
	tcsGD_Samboja = 6125, // @emem Samboja
	tcsGD_Lithuania1994ETRS89 = 6126, // @emem Lithuania 1994 (ETRS89)
	tcsGD_Pulkovo1995 = 6200, // @emem Pulkovo 1995
	tcsGD_Adindan = 6201, // @emem Adindan
	tcsGD_AustralianGeodeticDatum1966 = 6202, // @emem Australian Geodetic Datum 1966
	tcsGD_AustralianGeodeticDatum1984 = 6203, // @emem Australian Geodetic Datum 1984
	tcsGD_AinElAbd1970 = 6204, // @emem Ain el Abd 1970
	tcsGD_Afgooye = 6205, // @emem Afgooye
	tcsGD_Agadez = 6206, // @emem Agadez
	tcsGD_Lisbon = 6207, // @emem Lisbon
	tcsGD_Aratu = 6208, // @emem Aratu
	tcsGD_Arc1950 = 6209, // @emem Arc 1950
	tcsGD_Arc1960 = 6210, // @emem Arc 1960
	tcsGD_Batavia = 6211, // @emem Batavia
	tcsGD_Barbados = 6212, // @emem Barbados
	tcsGD_Beduaram = 6213, // @emem Beduaram
	tcsGD_Beijing1954 = 6214, // @emem Beijing 1954
	tcsGD_ReseauNationalBelge1950 = 6215, // @emem Reseau National Belge 1950
	tcsGD_Bermuda1957 = 6216, // @emem Bermuda 1957
	tcsGD_Bern1898 = 6217, // @emem Bern 1898
	tcsGD_Bogota = 6218, // @emem Bogota
	tcsGD_BukitRimpah = 6219, // @emem Bukit Rimpah
	tcsGD_Camacupa = 6220, // @emem Camacupa
	tcsGD_CampoInchauspe = 6221, // @emem Campo Inchauspe
	tcsGD_Cape = 6222, // @emem Cape
	tcsGD_Carthage = 6223, // @emem Carthage
	tcsGD_Chua = 6224, // @emem Chua
	tcsGD_CorregoAlegre = 6225, // @emem Corrego Alegre
	tcsGD_CoteDIvoire = 6226, // @emem Cote d'Ivoire
	tcsGD_DeirEzZor = 6227, // @emem Deir ez Zor
	tcsGD_Douala = 6228, // @emem Douala
	tcsGD_Egypt1907 = 6229, // @emem Egypt 1907
	tcsGD_EuropeanDatum1950 = 6230, // @emem European Datum 1950
	tcsGD_EuropeanDatum1987 = 6231, // @emem European Datum 1987
	tcsGD_Fahud = 6232, // @emem Fahud
	tcsGD_Gandajika1970 = 6233, // @emem Gandajika 1970
	tcsGD_Garoua = 6234, // @emem Garoua
	tcsGD_GuyaneFrancaise = 6235, // @emem Guyane Francaise
	tcsGD_HuTzuShan = 6236, // @emem Hu Tzu Shan
	tcsGD_HungarianDatum1972 = 6237, // @emem Hungarian Datum 1972
	tcsGD_IndonesianDatum1974 = 6238, // @emem Indonesian Datum 1974
	tcsGD_Indian1954 = 6239, // @emem Indian 1954
	tcsGD_Indian1975 = 6240, // @emem Indian 1975
	tcsGD_Jamaica1875 = 6241, // @emem Jamaica 1875
	tcsGD_Jamaica1969 = 6242, // @emem Jamaica 1969
	tcsGD_Kalianpur = 6243, // @emem Kalianpur
	tcsGD_Kandawala = 6244, // @emem Kandawala
	tcsGD_Kertau = 6245, // @emem Kertau
	tcsGD_KuwaitOilCompany = 6246, // @emem Kuwait Oil Company
	tcsGD_LaCanoa = 6247, // @emem La Canoa
	tcsGD_ProvisionalSouthAmericanDatum1956 = 6248, // @emem Provisional South American Datum 1956
	tcsGD_Lake = 6249, // @emem Lake
	tcsGD_Leigon = 6250, // @emem Leigon
	tcsGD_Liberia1964 = 6251, // @emem Liberia 1964
	tcsGD_Lome = 6252, // @emem Lome
	tcsGD_Luzon1911 = 6253, // @emem Luzon 1911
	tcsGD_HitoXVIII1963 = 6254, // @emem Hito XVIII 1963
	tcsGD_HeratNorth = 6255, // @emem Herat North
	tcsGD_Mahe1971 = 6256, // @emem Mahe 1971
	tcsGD_Makassar = 6257, // @emem Makassar
	tcsGD_EuropeanTerrestrialReferenceSystem89 = 6258, // @emem European Terrestrial Reference System 89
	tcsGD_Malongo1987 = 6259, // @emem Malongo 1987
	tcsGD_Manoca = 6260, // @emem Manoca
	tcsGD_Merchich = 6261, // @emem Merchich
	tcsGD_Massawa = 6262, // @emem Massawa
	tcsGD_Minna = 6263, // @emem Minna
	tcsGD_Mhast = 6264, // @emem Mhast
	tcsGD_MonteMario = 6265, // @emem Monte Mario
	tcsGD_MPoraloko = 6266, // @emem M'poraloko
	tcsGD_NorthAmericanDatum1927 = 6267, // @emem North American Datum 1927
	tcsGD_NADMichigan = 6268, // @emem NAD Michigan
	tcsGD_NorthAmericanDatum1983 = 6269, // @emem North American Datum 1983
	tcsGD_Nahrwan1967 = 6270, // @emem Nahrwan 1967
	tcsGD_Naparima1972 = 6271, // @emem Naparima 1972
	tcsGD_NewZealandGeodeticDatum1949 = 6272, // @emem New Zealand Geodetic Datum 1949
	tcsGD_NGO1948 = 6273, // @emem NGO 1948
	tcsGD_Datum73 = 6274, // @emem Datum 73
	tcsGD_NouvelleTriangulationFrancaise = 6275, // @emem Nouvelle Triangulation Francaise
	tcsGD_NSWC9Z2 = 6276, // @emem NSWC 9Z-2
	tcsGD_OSGB1936 = 6277, // @emem OSGB 1936
	tcsGD_OSGB1970SN = 6278, // @emem OSGB 1970 (SN)
	tcsGD_OSSN1980 = 6279, // @emem OS (SN) 1980
	tcsGD_Padang1884 = 6280, // @emem Padang 1884
	tcsGD_Palestine1923 = 6281, // @emem Palestine 1923
	tcsGD_PointeNoire = 6282, // @emem Pointe Noire
	tcsGD_GeocentricDatumOfAustralia1994 = 6283, // @emem Geocentric Datum of Australia 1994
	tcsGD_Pulkovo1942 = 6284, // @emem Pulkovo 1942
	tcsGD_Qatar = 6285, // @emem Qatar
	tcsGD_Qatar1948 = 6286, // @emem Qatar 1948
	tcsGD_Qornoq = 6287, // @emem Qornoq
	tcsGD_LomaQuintana = 6288, // @emem Loma Quintana
	tcsGD_Amersfoort = 6289, // @emem Amersfoort
	tcsGD_SouthAmericanDatum1969 = 6291, // @emem South American Datum 1969
	tcsGD_SapperHill1943 = 6292, // @emem Sapper Hill 1943
	tcsGD_Schwarzeck = 6293, // @emem Schwarzeck
	tcsGD_Segora = 6294, // @emem Segora
	tcsGD_Serindung = 6295, // @emem Serindung
	tcsGD_Sudan = 6296, // @emem Sudan
	tcsGD_Tananarive1925 = 6297, // @emem Tananarive 1925
	tcsGD_Timbalai1948 = 6298, // @emem Timbalai 1948
	tcsGD_TM65 = 6299, // @emem TM65
	tcsGD_TM75 = 6300, // @emem TM75
	tcsGD_Tokyo = 6301, // @emem Tokyo
	tcsGD_Trinidad1903 = 6302, // @emem Trinidad 1903
	tcsGD_TrucialCoast1948 = 6303, // @emem Trucial Coast 1948
	tcsGD_Voirol1875 = 6304, // @emem Voirol 1875
	tcsGD_VoirolUnifie1960 = 6305, // @emem Voirol Unifie 1960
	tcsGD_Bern1938 = 6306, // @emem Bern 1938
	tcsGD_NordSahara1959 = 6307, // @emem Nord Sahara 1959
	tcsGD_Stockholm1938 = 6308, // @emem Stockholm 1938
	tcsGD_Yacare = 6309, // @emem Yacare
	tcsGD_Yoff = 6310, // @emem Yoff
	tcsGD_Zanderij = 6311, // @emem Zanderij
	tcsGD_MilitarGeographischeInstitut = 6312, // @emem Militar-Geographische Institut
	tcsGD_ReseauNationalBelge1972 = 6313, // @emem Reseau National Belge 1972
	tcsGD_DeutscheHauptdreiecksnetz = 6314, // @emem Deutsche Hauptdreiecksnetz
	tcsGD_Conakry1905 = 6315, // @emem Conakry 1905
	tcsGD_DealulPiscului1933 = 6316, // @emem Dealul Piscului 1933
	tcsGD_DealulPiscului1970 = 6317, // @emem Dealul Piscului 1970
	tcsGD_NationalGeodeticNetwork = 6318, // @emem National Geodetic Network
	tcsGD_KuwaitUtility = 6319, // @emem Kuwait Utility
	tcsGD_WorldGeodeticSystem1972 = 6322, // @emem World Geodetic System 1972
	tcsGD_WGS72TransitBroadcastEphemeris = 6324, // @emem WGS 72 Transit Broadcast Ephemeris
	tcsGD_WorldGeodeticSystem1984 = 6326, // @emem World Geodetic System 1984
	tcsGD_AncienneTriangulationFrancaise = 6901, // @emem Ancienne Triangulation Francaise
	tcsGD_NordDeGuerre = 6902, // @emem Nord de Guerre

// #HK020228
// Dreiteilung des Festpunktnetzes (alte Bundesländer)
	tcsGD_DeutscheHauptdreiecksnetzAblN = 6903, // @emem Deutsche Hauptdreiecksnetz, alte Bundesländer Nord (55°-52°20')
	tcsGD_DeutscheHauptdreiecksnetzAblM = 6904, // @emem Deutsche Hauptdreiecksnetz, alte Bundesländer Mitte (52°20'-50°20')
	tcsGD_DeutscheHauptdreiecksnetzAblS = 6905, // @emem Deutsche Hauptdreiecksnetz, alte Bundesländer Süd (50°20'-47°)

// Neue Bundesländer
	tcsGD_DeutscheHauptdreiecksnetzRd83 = 6906, // @emem Deutsche Hauptdreiecksnetz, neue Bundesländer 
	tcsGD_DeutscheHauptdreiecksnetzPd83 = 6907, // @emem Deutsche Hauptdreiecksnetz, Thüringen

// #HK020419
// Alle Festpunkte berücksichtigt
	tcsGD_DeutscheHauptdreiecksnetzRd83DHDN = 6908, // @emem Deutsche Hauptdreiecksnetz RD83 (neu)

// Zweiteilung des Festpunktnetzes (alte Bundesländer)
	tcsGD_DeutscheHauptdreiecksnetzAblN2 = 6909, // @emem Deutsche Hauptdreiecksnetz, alte Bundesländer Nord (zweigeteilt) (55°-51°)
	tcsGD_DeutscheHauptdreiecksnetzAblS2 = 6910, // @emem Deutsche Hauptdreiecksnetz, alte Bundesländer Süd (zweigeteilt) (51°-47°)

// Alte Bundesländer Gesamt
	tcsGD_DeutscheHauptdreiecksnetzDHDN = 6911, // @emem Alte Bundesländer gesamt RD83 (neu)

// Überbreite Zone für Deutschland (GeoStar)
	tcsGD_DeutscheHauptdreiecksnetzBesD = 6912, // @emem Überbreite Zone für Deutschland (GeoStar)

	tcsGD_UserDefined = 32769,  // @emem User Defined
} TRIASCSGEODETICDATUM;
cpp_quote("extern CODENAME _CT_TRIASCSUNITOFLENGTH[];")

// @doc ENUM TRIASCS
// @enum TRIASCSUNITOFLENGTH | TRIASCSUNITOFLENGTH
typedef enum TRIASCSUNITOFLENGTH {
	tcsUOL_Undefined = -1, // @emem Wert ist nicht definiert
	tcsUOL_Metre = 9001, // @emem metre
	tcsUOL_MilliMetre = 90011, // @emem metre
	tcsUOL_KiloMetre = 90012, // @emem metre
	tcsUOL_Foot = 9002, // @emem foot
	tcsUOL_USSurveyFoot = 9003, // @emem US survey foot
	tcsUOL_ModifiedAmericanFoot = 9004, // @emem modified American foot
	tcsUOL_ClarkeSFoot = 9005, // @emem Clarke's foot
	tcsUOL_IndianFootClarke = 9006, // @emem Indian foot (Clarke)
	tcsUOL_Link = 9007, // @emem link
	tcsUOL_LinkBenoit = 9008, // @emem link (Benoit)
	tcsUOL_LinkSears = 9009, // @emem link (Sears)
	tcsUOL_ChainBenoit = 9010, // @emem chain (Benoit)
	tcsUOL_ChainSears = 9011, // @emem chain (Sears)
	tcsUOL_YardSears = 9012, // @emem yard (Sears)
	tcsUOL_IndianYard = 9013, // @emem Indian yard
	tcsUOL_Fathom = 9014, // @emem fathom
	tcsUOL_NauticalMile = 9030, // @emem nautical mile
	tcsUOL_GermanLegalMetre = 9031, // @emem German legal metre
	tcsUOL_FootSears = 9032, // @emem foot (Sears)
	tcsUOL_USSurveyChain = 9033, // @emem US survey chain
	tcsUOL_USSurveyLink = 9034, // @emem US survey link
	tcsUOL_USSurveyMile = 9035, // @emem US survey mile
	tcsUOL_Inch = 90013,	// @emem inch
	tcsUOL_CentiMetre = 90014, // @emem centimetre
} TRIASCSUNITOFLENGTH;
cpp_quote("extern CODENAME _CT_TRIASCSPRIMEMERIDIAN[];")

// @doc ENUM TRIASCS
// @enum TRIASCSPRIMEMERIDIAN | TRIASCSPRIMEMERIDIAN
typedef enum TRIASCSPRIMEMERIDIAN {
	tcsPM_Undefined = -1, // @emem Wert ist nicht definiert
	tcsPM_Greenwich = 8901, // @emem Greenwich
	tcsPM_Lisbon = 8902, // @emem Lisbon
	tcsPM_Paris = 8903, // @emem Paris
	tcsPM_Bogota = 8904, // @emem Bogota
	tcsPM_Madrid = 8905, // @emem Madrid
	tcsPM_Rome = 8906, // @emem Rome
	tcsPM_Bern = 8907, // @emem Bern
	tcsPM_Jakarta = 8908, // @emem Jakarta
	tcsPM_Ferro = 8909, // @emem Ferro
	tcsPM_Brussels = 8910, // @emem Brussels
	tcsPM_Stockholm = 8911, // @emem Stockholm
	tcsPM_Athens = 8912, // @emem Athens
} TRIASCSPRIMEMERIDIAN;
cpp_quote("extern CODENAME _CT_TRIASCSPROJECTIONALGORITHM[];")

// @doc ENUM TRIASCS
// @enum TRIASCSPROJECTIONALGORITHM | TRIASCSPROJECTIONALGORITHM
typedef enum TRIASCSPROJECTIONALGORITHM {
	tcsPA_Undefined = -1, // @emem Wert ist nicht definiert
	tcsPA_LambertConicConformal1SP = 9801, // @emem Lambert Conic Conformal (1SP)
	tcsPA_LambertConicConformal2SP = 9802, // @emem Lambert Conic Conformal (2SP)
	tcsPA_LambertConicConformal2SPBelgium = 9803, // @emem Lambert Conic Conformal (2SP Belgium)
	tcsPA_Mercator1SP = 9804, // @emem Mercator (1SP)
	tcsPA_Mercator2SP = 9805, // @emem Mercator (2SP)
	tcsPA_CassiniSoldner = 9806, // @emem Cassini-Soldner
	tcsPA_TransverseMercator = 9807, // @emem Transverse Mercator
	tcsPA_TransverseMercatorSouthOrientated = 9808, // @emem Transverse Mercator (South Orientated)
	tcsPA_ObliqueStereographic = 9809, // @emem Oblique Stereographic
	tcsPA_PolarStereographic = 9810, // @emem Polar Stereographic
	tcsPA_NewZealandMapGrid = 9811, // @emem New Zealand Map Grid
	tcsPA_HotineObliqueMercator = 9812, // @emem Hotine Oblique Mercator
	tcsPA_LabordeObliqueMercator = 9813, // @emem Laborde Oblique Mercator
	tcsPA_SwissObliqueCylindrical = 9814, // @emem Swiss Oblique Cylindrical
	tcsPA_ObliqueMercator = 9815, // @emem Oblique Mercator
	tcsPA_AffineTransformation = 32770,  // @emem Affine Transformation
	tcsPA_GaussKrueger = 32769,  // @emem Gauss Krüger
	tcsPA_CylindricEquirectangular = 32771,  // @emem Cylindric Equirectangular
} TRIASCSPROJECTIONALGORITHM;

// @doc ENUM TRIASCS
// @enum TRIASCSPROJECTIONPARAMETER | TRIASCSPROJECTIONPARAMETER
typedef enum TRIASCSPROJECTIONPARAMETER {
	tcsPP_Undefined = -1, // @emem Wert ist nicht definiert
// @xref <l Cassini-Soldner>
	tcsPP_CassiniSoldner_LatitudeOfNaturalOrigin = 0, // @emem Latitude of natural origin <l Cassini-Soldner>
	tcsPP_CassiniSoldner_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l Cassini-Soldner>
	tcsPP_CassiniSoldner_FalseEasting = 5, // @emem False easting <l Cassini-Soldner>
	tcsPP_CassiniSoldner_FalseNorthing = 6, // @emem False northing <l Cassini-Soldner>
// @xref <l Hotine Oblique Mercator>
	tcsPP_HotineObliqueMercator_LatitudeOfProjectionCentre = 0, // @emem Latitude of projection centre <l Hotine Oblique Mercator>
	tcsPP_HotineObliqueMercator_LongitudeOfProjectionCentre = 1, // @emem Longitude of projection centre <l Hotine Oblique Mercator>
	tcsPP_HotineObliqueMercator_AzimuthOfInitialLine = 2, // @emem Azimuth of initial line <l Hotine Oblique Mercator>
	tcsPP_HotineObliqueMercator_AngleFromRectifiedToSkewGrid = 3, // @emem Angle from Rectified to Skew Grid <l Hotine Oblique Mercator>
	tcsPP_HotineObliqueMercator_ScaleFactorOnInitialLine = 4, // @emem Scale factor on initial line <l Hotine Oblique Mercator>
	tcsPP_HotineObliqueMercator_FalseEasting = 5, // @emem False easting <l Hotine Oblique Mercator>
	tcsPP_HotineObliqueMercator_FalseNorthing = 6, // @emem False northing <l Hotine Oblique Mercator>
// @xref <l Laborde Oblique Mercator>
	tcsPP_LabordeObliqueMercator_LatitudeOfProjectionCentre = 0, // @emem Latitude of projection centre <l Laborde Oblique Mercator>
	tcsPP_LabordeObliqueMercator_LongitudeOfProjectionCentre = 1, // @emem Longitude of projection centre <l Laborde Oblique Mercator>
	tcsPP_LabordeObliqueMercator_AzimuthOfInitialLine = 2, // @emem Azimuth of initial line <l Laborde Oblique Mercator>
	tcsPP_LabordeObliqueMercator_ScaleFactorOnInitialLine = 4, // @emem Scale factor on initial line <l Laborde Oblique Mercator>
	tcsPP_LabordeObliqueMercator_FalseEasting = 5, // @emem False easting <l Laborde Oblique Mercator>
	tcsPP_LabordeObliqueMercator_FalseNorthing = 6, // @emem False northing <l Laborde Oblique Mercator>
// @xref <l Lambert Conic Conformal (1SP)>
	tcsPP_LambertConicConformal1SP_LatitudeOfNaturalOrigin = 0, // @emem Latitude of natural origin <l Lambert Conic Conformal (1SP)>
	tcsPP_LambertConicConformal1SP_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l Lambert Conic Conformal (1SP)>
	tcsPP_LambertConicConformal1SP_ScaleFactorAtNaturalOrigin = 4, // @emem Scale factor at natural origin <l Lambert Conic Conformal (1SP)>
	tcsPP_LambertConicConformal1SP_FalseEasting = 5, // @emem False easting <l Lambert Conic Conformal (1SP)>
	tcsPP_LambertConicConformal1SP_FalseNorthing = 6, // @emem False northing <l Lambert Conic Conformal (1SP)>
// @xref <l Lambert Conic Conformal (2SP)>
	tcsPP_LambertConicConformal2SP_LatitudeOfFirstStandardParallel = 0, // @emem Latitude of first standard parallel <l Lambert Conic Conformal (2SP)>
	tcsPP_LambertConicConformal2SP_LatitudeOfSecondStandardParallel = 1, // @emem Latitude of second standard parallel <l Lambert Conic Conformal (2SP)>
	tcsPP_LambertConicConformal2SP_LatitudeOfFalseOrigin = 2, // @emem Latitude of false origin <l Lambert Conic Conformal (2SP)>
	tcsPP_LambertConicConformal2SP_LongitudeOfFalseOrigin = 3, // @emem Longitude of false origin <l Lambert Conic Conformal (2SP)>
	tcsPP_LambertConicConformal2SP_EastingAtFalseOrigin = 5, // @emem Easting at false origin <l Lambert Conic Conformal (2SP)>
	tcsPP_LambertConicConformal2SP_NorthingAtFalseOrigin = 6, // @emem Northing at false origin <l Lambert Conic Conformal (2SP)>
// @xref <l Lambert Conic Conformal (2SP Belgium)>
	tcsPP_LambertConicConformal2SPBelgium_LatitudeOfFirstStandardParallel = 0, // @emem Latitude of first standard parallel <l Lambert Conic Conformal (2SP Belgium)>
	tcsPP_LambertConicConformal2SPBelgium_LatitudeOfSecondStandardParallel = 1, // @emem Latitude of second standard parallel <l Lambert Conic Conformal (2SP Belgium)>
	tcsPP_LambertConicConformal2SPBelgium_LatitudeOfFalseOrigin = 2, // @emem Latitude of false origin <l Lambert Conic Conformal (2SP Belgium)>
	tcsPP_LambertConicConformal2SPBelgium_LongitudeOfFalseOrigin = 3, // @emem Longitude of false origin <l Lambert Conic Conformal (2SP Belgium)>
	tcsPP_LambertConicConformal2SPBelgium_EastingAtFalseOrigin = 5, // @emem Easting at false origin <l Lambert Conic Conformal (2SP Belgium)>
	tcsPP_LambertConicConformal2SPBelgium_NorthingAtFalseOrigin = 6, // @emem Northing at false origin <l Lambert Conic Conformal (2SP Belgium)>
// @xref <l Mercator (1SP)>
	tcsPP_Mercator1SP_LatitudeOfNaturalOrigin = 0, // @emem Latitude of natural origin <l Mercator (1SP)>
	tcsPP_Mercator1SP_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l Mercator (1SP)>
	tcsPP_Mercator1SP_ScaleFactorAtNaturalOrigin = 4, // @emem Scale factor at natural origin <l Mercator (1SP)>
	tcsPP_Mercator1SP_FalseEasting = 5, // @emem False easting <l Mercator (1SP)>
	tcsPP_Mercator1SP_FalseNorthing = 6, // @emem False northing <l Mercator (1SP)>
// @xref <l Mercator (2SP)>
	tcsPP_Mercator2SP_LatitudeOfFirstStandardParallel = 0, // @emem Latitude of first standard parallel <l Mercator (2SP)>
	tcsPP_Mercator2SP_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l Mercator (2SP)>
	tcsPP_Mercator2SP_FalseEasting = 5, // @emem False easting <l Mercator (2SP)>
	tcsPP_Mercator2SP_FalseNorthing = 6, // @emem False northing <l Mercator (2SP)>
// @xref <l New Zealand Map Grid>
	tcsPP_NewZealandMapGrid_LatitudeOfNaturalOrigin = 0, // @emem Latitude of natural origin <l New Zealand Map Grid>
	tcsPP_NewZealandMapGrid_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l New Zealand Map Grid>
	tcsPP_NewZealandMapGrid_FalseEasting = 5, // @emem False easting <l New Zealand Map Grid>
	tcsPP_NewZealandMapGrid_FalseNorthing = 6, // @emem False northing <l New Zealand Map Grid>
// @xref <l Oblique Stereographic>
	tcsPP_ObliqueStereographic_LatitudeOfNaturalOrigin = 0, // @emem Latitude of natural origin <l Oblique Stereographic>
	tcsPP_ObliqueStereographic_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l Oblique Stereographic>
	tcsPP_ObliqueStereographic_ScaleFactorAtNaturalOrigin = 4, // @emem Scale factor at natural origin <l Oblique Stereographic>
	tcsPP_ObliqueStereographic_FalseEasting = 5, // @emem False easting <l Oblique Stereographic>
	tcsPP_ObliqueStereographic_FalseNorthing = 6, // @emem False northing <l Oblique Stereographic>
// @xref <l Polar Stereographic>
	tcsPP_PolarStereographic_LatitudeOfNaturalOrigin = 0, // @emem Latitude of natural origin <l Polar Stereographic>
	tcsPP_PolarStereographic_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l Polar Stereographic>
	tcsPP_PolarStereographic_ScaleFactorAtNaturalOrigin = 4, // @emem Scale factor at natural origin <l Polar Stereographic>
	tcsPP_PolarStereographic_FalseEasting = 5, // @emem False easting <l Polar Stereographic>
	tcsPP_PolarStereographic_FalseNorthing = 6, // @emem False northing <l Polar Stereographic>
// @xref <l Swiss Oblique Cylindrical>
	tcsPP_SwissObliqueCylindrical_LatitudeOfProjectionCentre = 0, // @emem Latitude of projection centre <l Swiss Oblique Cylindrical>
	tcsPP_SwissObliqueCylindrical_LongitudeOfProjectionCentre = 1, // @emem Longitude of projection centre <l Swiss Oblique Cylindrical>
	tcsPP_SwissObliqueCylindrical_EastingAtProjectionCentre = 5, // @emem Easting at projection centre <l Swiss Oblique Cylindrical>
	tcsPP_SwissObliqueCylindrical_NorthingAtProjectionCentre = 6, // @emem Northing at projection centre <l Swiss Oblique Cylindrical>
// @xref <l Transverse Mercator>
	tcsPP_TransverseMercator_LatitudeOfNaturalOrigin = 0, // @emem Latitude of natural origin <l Transverse Mercator>
	tcsPP_TransverseMercator_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l Transverse Mercator>
	tcsPP_TransverseMercator_ScaleFactorAtNaturalOrigin = 4, // @emem Scale factor at natural origin <l Transverse Mercator>
	tcsPP_TransverseMercator_FalseEasting = 5, // @emem False easting <l Transverse Mercator>
	tcsPP_TransverseMercator_FalseNorthing = 6, // @emem False northing <l Transverse Mercator>
	tcsPP_TransverseMercator_ZoneWidth = 7, // @emem Automatically calculate correct origin based on this zone width <l Transverse Mercator>
// @xref <l Transverse Mercator (South Orientated)>
	tcsPP_TransverseMercatorSouthOrientated_LatitudeOfNaturalOrigin = 0, // @emem Latitude of natural origin <l Transverse Mercator (South Orientated)>
	tcsPP_TransverseMercatorSouthOrientated_LongitudeOfNaturalOrigin = 1, // @emem Longitude of natural origin <l Transverse Mercator (South Orientated)>
	tcsPP_TransverseMercatorSouthOrientated_ScaleFactorAtNaturalOrigin = 4, // @emem Scale factor at natural origin <l Transverse Mercator (South Orientated)>
	tcsPP_TransverseMercatorSouthOrientated_FalseEasting = 5, // @emem False easting <l Transverse Mercator (South Orientated)>
	tcsPP_TransverseMercatorSouthOrientated_FalseNorthing = 6, // @emem False northing <l Transverse Mercator (South Orientated)>
// @xref <l Oblique Mercator>
	tcsPP_ObliqueMercator_LatitudeOfProjectionCentre = 0, // @emem Latitude of projection centre <l Oblique Mercator>
	tcsPP_ObliqueMercator_LongitudeOfProjectionCentre = 1, // @emem Longitude of projection centre <l Oblique Mercator>
	tcsPP_ObliqueMercator_AzimuthOfInitialLine = 2, // @emem Azimuth of initial line <l Oblique Mercator>
	tcsPP_ObliqueMercator_AngleFromRectifiedToSkewGrid = 3, // @emem Angle from Rectified to Skew Grid <l Oblique Mercator>
	tcsPP_ObliqueMercator_ScaleFactorOnInitialLine = 4, // @emem Scale factor on initial line <l Oblique Mercator>
	tcsPP_ObliqueMercator_EastingAtProjectionCentre = 5, // @emem Easting at projection centre <l Oblique Mercator>
	tcsPP_ObliqueMercator_NorthingAtProjectionCentre = 6, // @emem Northing at projection centre <l Oblique Mercator>
// @xref <l Affine Transformation>
	tcsPP_AffineTransformation_OffsetX = 15, // @emem OffsetX <l Affine Transformation>
	tcsPP_AffineTransformation_OffsetY = 16, // @emem OffsetY <l Affine Transformation>
	tcsPP_AffineTransformation_RotatePhi = 3, // @emem RotatePhi <l Affine Transformation>
	tcsPP_AffineTransformation_ScaleX = 0, // @emem ScaleX <l Affine Transformation>
	tcsPP_AffineTransformation_ScaleY = 1, // @emem ScaleY <l Affine Transformation>
// @xref <l Gauss Krüger>
	tcsPP_GaussKrueger_FalseEasting = tcsPP_TransverseMercator_FalseEasting, // @emem False easting <l Gauss Krüger>
	tcsPP_GaussKrueger_FalseNorthing = tcsPP_TransverseMercator_FalseNorthing, // @emem False northing <l Gauss Krüger>
	tcsPP_GaussKrueger_LatitudeOfNaturalOrigin = tcsPP_TransverseMercator_LatitudeOfNaturalOrigin, // @emem Latitude of natural origin <l Gauss Krüger>
	tcsPP_GaussKrueger_LongitudeOfNaturalOrigin = tcsPP_TransverseMercator_LongitudeOfNaturalOrigin, // @emem Longitude of natural origin <l Gauss Krüger>
	tcsPP_GaussKrueger_ScaleFactorAtNaturalOrigin = tcsPP_TransverseMercator_ScaleFactorAtNaturalOrigin, // @emem Scale factor at natural origin <l Gauss Krüger>
	tcsPP_GaussKrueger_ZoneWidth = tcsPP_TransverseMercator_ZoneWidth, // @emem Automatically calculate correct origin based on this zone width <l Gauss Krüger>
// @xref <l Cylindric Equirectangular>
	tcsPP_CylindricEquirectangular_FalseEasting = tcsPP_TransverseMercator_FalseEasting, // @emem False easting <l Cylindric Equirectangular>
	tcsPP_CylindricEquirectangular_FalseNorthing = tcsPP_TransverseMercator_FalseNorthing, // @emem False northing <l Cylindric Equirectangular>
	tcsPP_CylindricEquirectangular_LatitudeOfNaturalOrigin = tcsPP_TransverseMercator_LatitudeOfNaturalOrigin, // @emem Latitude of natural origin <l Cylindric Equirectangular>
	tcsPP_CylindricEquirectangular_LongitudeOfNaturalOrigin = tcsPP_TransverseMercator_LongitudeOfNaturalOrigin, // @emem Longitude of natural origin <l Cylindric Equirectangular>
} TRIASCSPROJECTIONPARAMETER;

// @doc ENUM TRIASCS
// @enum TRIASCSDTRANSPARAMETER | TRIASCSDTRANSPARAMETER
typedef enum TRIASCSDTRANSPARAMETER {
	tcsDTP_Undefined = -1, // @emem Wert ist nicht definiert
// @xref <l Longitude rotation>
	tcsDTP_LongitudeRotation_LongitudeRotation = 0, // @emem Longitude rotation <l Longitude rotation>
// @xref <l Geodetic/geocentric conversions>
// @xref <l Geocentric translations>
	tcsDTP_GeocentricTranslations_XAxisTranslation = 0, // @emem X-axis translation <l Geocentric translations>
	tcsDTP_GeocentricTranslations_YAxisTranslation = 1, // @emem Y-axis translation <l Geocentric translations>
	tcsDTP_GeocentricTranslations_ZAxisTranslation = 2, // @emem Z-axis translation <l Geocentric translations>
// @xref <l Molodenski>
	tcsDTP_Molodenski_XAxisTranslation = 0, // @emem X-axis translation <l Molodenski>
	tcsDTP_Molodenski_YAxisTranslation = 1, // @emem Y-axis translation <l Molodenski>
	tcsDTP_Molodenski_ZAxisTranslation = 2, // @emem Z-axis translation <l Molodenski>
	tcsDTP_Molodenski_SemiMajorAxisLengthDifference = 3, // @emem Semi-major axis length difference <l Molodenski>
	tcsDTP_Molodenski_FlatteningDifference = 4, // @emem Flattening difference <l Molodenski>
// @xref <l Abridged Molodenski>
	tcsDTP_AbridgedMolodenski_XAxisTranslation = 0, // @emem X-axis translation <l Abridged Molodenski>
	tcsDTP_AbridgedMolodenski_YAxisTranslation = 1, // @emem Y-axis translation <l Abridged Molodenski>
	tcsDTP_AbridgedMolodenski_ZAxisTranslation = 2, // @emem Z-axis translation <l Abridged Molodenski>
	tcsDTP_AbridgedMolodenski_SemiMajorAxisLengthDifference = 3, // @emem Semi-major axis length difference <l Abridged Molodenski>
	tcsDTP_AbridgedMolodenski_FlatteningDifference = 4, // @emem Flattening difference <l Abridged Molodenski>
// @xref <l Position Vector 7-param transformation>
	tcsDTP_PositionVector7ParamTransformation_XAxisTranslation = 0, // @emem X-axis translation <l Position Vector 7-param transformation>
	tcsDTP_PositionVector7ParamTransformation_YAxisTranslation = 1, // @emem Y-axis translation <l Position Vector 7-param transformation>
	tcsDTP_PositionVector7ParamTransformation_ZAxisTranslation = 2, // @emem Z-axis translation <l Position Vector 7-param transformation>
	tcsDTP_PositionVector7ParamTransformation_XAxisRotation = 3, // @emem X-axis rotation <l Position Vector 7-param transformation>
	tcsDTP_PositionVector7ParamTransformation_YAxisRotation = 4, // @emem Y-axis rotation <l Position Vector 7-param transformation>
	tcsDTP_PositionVector7ParamTransformation_ZAxisRotation = 5, // @emem Z-axis rotation <l Position Vector 7-param transformation>
	tcsDTP_PositionVector7ParamTransformation_ScaleDifference = 6, // @emem Scale difference <l Position Vector 7-param transformation>
// @xref <l Coordinate Frame 7-param transformation>
	tcsDTP_CoordinateFrame7ParamTransformation_XAxisTranslation = 0, // @emem X-axis translation <l Coordinate Frame 7-param transformation>
	tcsDTP_CoordinateFrame7ParamTransformation_YAxisTranslation = 1, // @emem Y-axis translation <l Coordinate Frame 7-param transformation>
	tcsDTP_CoordinateFrame7ParamTransformation_ZAxisTranslation = 2, // @emem Z-axis translation <l Coordinate Frame 7-param transformation>
	tcsDTP_CoordinateFrame7ParamTransformation_XAxisRotation = 3, // @emem X-axis rotation <l Coordinate Frame 7-param transformation>
	tcsDTP_CoordinateFrame7ParamTransformation_YAxisRotation = 4, // @emem Y-axis rotation <l Coordinate Frame 7-param transformation>
	tcsDTP_CoordinateFrame7ParamTransformation_ZAxisRotation = 5, // @emem Z-axis rotation <l Coordinate Frame 7-param transformation>
	tcsDTP_CoordinateFrame7ParamTransformation_ScaleDifference = 6, // @emem Scale difference <l Coordinate Frame 7-param transformation>
// @xref <l Similarity transform>
	tcsDTP_SimilarityTransform_A1 = 0, // @emem A1 <l Similarity transform>
	tcsDTP_SimilarityTransform_A2M = 1, // @emem A2 * m <l Similarity transform>
	tcsDTP_SimilarityTransform_A3N = 2, // @emem A3 * n <l Similarity transform>
	tcsDTP_SimilarityTransform_B1 = 3, // @emem B1 <l Similarity transform>
	tcsDTP_SimilarityTransform_B2M = 4, // @emem B2 * m <l Similarity transform>
	tcsDTP_SimilarityTransform_B3N = 5, // @emem B3 * n <l Similarity transform>
// @xref <l 2-dimensional Affine transformation>
	tcsDTP_2DimensionalAffineTransformation_A1 = 0, // @emem A1 <l 2-dimensional Affine transformation>
	tcsDTP_2DimensionalAffineTransformation_A2M = 1, // @emem A2 * m <l 2-dimensional Affine transformation>
	tcsDTP_2DimensionalAffineTransformation_A3N = 2, // @emem A3 * n <l 2-dimensional Affine transformation>
	tcsDTP_2DimensionalAffineTransformation_B1 = 3, // @emem B1 <l 2-dimensional Affine transformation>
	tcsDTP_2DimensionalAffineTransformation_B2M = 4, // @emem B2 * m <l 2-dimensional Affine transformation>
	tcsDTP_2DimensionalAffineTransformation_B3N = 5, // @emem B3 * n <l 2-dimensional Affine transformation>
// @xref <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_A6Nn = 9, // @emem A6 * nn <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_Ordinate1OfSourceEvaluationPoint = 0, // @emem Ordinate 1 of source evaluation point <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_B1 = 10, // @emem B1 <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_Ordinate2OfSourceEvaluationPoint = 1, // @emem Ordinate 2 of source evaluation point <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_B2M = 11, // @emem B2 * m <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_Ordinate1OfTargetEvaluationPoint = 2, // @emem Ordinate 1 of target evaluation point <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_B3N = 12, // @emem B3 * n <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_Ordinate2OfTargetEvaluationPoint = 3, // @emem Ordinate 2 of target evaluation point <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_B4Mm = 13, // @emem B4 * mm <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_A1 = 4, // @emem A1 <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_B5Mn = 14, // @emem B5 * mn <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_A2M = 5, // @emem A2 * m <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_B6Nn = 15, // @emem B6 * nn <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_A3N = 6, // @emem A3 * n <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_A4Mm = 7, // @emem A4 * mm <l 2nd-order Polynomial function>
	tcsDTP_2ndOrderPolynomialFunction_A5Mn = 8, // @emem A5 * mn <l 2nd-order Polynomial function>
// @xref <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A6Nn = 9, // @emem A6 * nn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B6Nn = 19, // @emem B6 * nn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A7Mmm = 10, // @emem A7 * mmm <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A8Mmn = 11, // @emem A8 * mmn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B7Mmm = 20, // @emem B7 * mmm <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B8Mmn = 21, // @emem B8 * mmn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A9Mnn = 12, // @emem A9 * mnn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A10Nnn = 13, // @emem A10 * nnn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B9Mnn = 22, // @emem B9 * mnn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B10Nnn = 23, // @emem B10 * nnn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B1 = 14, // @emem B1 <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B2M = 15, // @emem B2 * m <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B3N = 16, // @emem B3 * n <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B4Mm = 17, // @emem B4 * mm <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_B5Mn = 18, // @emem B5 * mn <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_Ordinate1OfSourceEvaluationPoint = 0, // @emem Ordinate 1 of source evaluation point <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_Ordinate2OfSourceEvaluationPoint = 1, // @emem Ordinate 2 of source evaluation point <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_Ordinate1OfTargetEvaluationPoint = 2, // @emem Ordinate 1 of target evaluation point <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_Ordinate2OfTargetEvaluationPoint = 3, // @emem Ordinate 2 of target evaluation point <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A1 = 4, // @emem A1 <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A2M = 5, // @emem A2 * m <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A3N = 6, // @emem A3 * n <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A4Mm = 7, // @emem A4 * mm <l 3rd-order Polynomial function>
	tcsDTP_3rdOrderPolynomialFunction_A5Mn = 8, // @emem A5 * mn <l 3rd-order Polynomial function>
// @xref <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A6Nn = 9, // @emem A6 * nn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B1 = 19, // @emem B1 <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A7Mmm = 10, // @emem A7 * mmm <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B11Mmmm = 29, // @emem B11 * mmmm <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A8Mmn = 11, // @emem A8 * mmn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B2M = 20, // @emem B2 * m <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B3N = 21, // @emem B3 * n <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B12Mmmn = 30, // @emem B12 * mmmn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A9Mnn = 12, // @emem A9 * mnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B13Mmnn = 31, // @emem B13 * mmnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A10Nnn = 13, // @emem A10 * nnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B4Mm = 22, // @emem B4 * mm <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B5Mn = 23, // @emem B5 * mn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B14Mnnn = 32, // @emem B14 * mnnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A11Mmmm = 14, // @emem A11 * mmmm <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B15Nnnn = 33, // @emem B15 * nnnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A12Mmmn = 15, // @emem A12 * mmmn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B6Nn = 24, // @emem B6 * nn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B7Mmm = 25, // @emem B7 * mmm <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A13Mmnn = 16, // @emem A13 * mmnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A14Mnnn = 17, // @emem A14 * mnnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B8Mmn = 26, // @emem B8 * mmn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B9Mnn = 27, // @emem B9 * mnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A15Nnnn = 18, // @emem A15 * nnnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_B10Nnn = 28, // @emem B10 * nnn <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_Ordinate1OfSourceEvaluationPoint = 0, // @emem Ordinate 1 of source evaluation point <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_Ordinate2OfSourceEvaluationPoint = 1, // @emem Ordinate 2 of source evaluation point <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_Ordinate1OfTargetEvaluationPoint = 2, // @emem Ordinate 1 of target evaluation point <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_Ordinate2OfTargetEvaluationPoint = 3, // @emem Ordinate 2 of target evaluation point <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A1 = 4, // @emem A1 <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A2M = 5, // @emem A2 * m <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A3N = 6, // @emem A3 * n <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A4Mm = 7, // @emem A4 * mm <l 4th-order Polynomial function>
	tcsDTP_4thOrderPolynomialFunction_A5Mn = 8, // @emem A5 * mn <l 4th-order Polynomial function>
// @xref <l NADCON>
// @xref <l Vertical Offset>
	tcsDTP_VerticalOffset_VerticalOffset = 0, // @emem Vertical offset <l Vertical Offset>
// @xref <l Canada NTv1>
// @xref <l Canada NTv2>
} TRIASCSDTRANSPARAMETER;

cpp_quote("extern CODEPARAM _PT_ELLIPSFROMGD[];")
cpp_quote("extern CODEPARAMSET _PT_ELLIPSPARAM[];")
cpp_quote("typedef struct PA_ATTRIBUTESET { TRIASCSPROJECTIONALGORITHM pa; TRIASCSPROJECTIONPARAMETER pp; LPCTSTR value; } PA_ATTRIBUTESET;")
cpp_quote("typedef struct DT_ATTRIBUTESET { TRIASCSDTRANSALGORITHM ta; TRIASCSDTRANSPARAMETER tp; LPCTSTR value; } DT_ATTRIBUTESET;")

cpp_quote("#if defined(__cplusplus)")
cpp_quote("typedef const PA_ATTRIBUTESET const *LPCPA_ATTRIBUTESET;")
cpp_quote("typedef const DT_ATTRIBUTESET const *LPCDT_ATTRIBUTESET;")
cpp_quote("#else")
cpp_quote("typedef PA_ATTRIBUTESET const *LPCPA_ATTRIBUTESET;")
cpp_quote("typedef DT_ATTRIBUTESET const *LPCDT_ATTRIBUTESET;")
cpp_quote("#endif // defined(__cplusplus)")

cpp_quote("extern DT_ATTRIBUTESET _DT_ATTRIBUTES[];")
cpp_quote("extern PA_ATTRIBUTESET _PA_ATTRIBUTES[];")

#endif // !defined(_EPSG_H__AE14AAAB_D399_427C_8F3C_5CEA6E5900C1__INCLUDED_)

///////////////////////////////////////////////////////////////////////////////
// @doc
// @module TRiASCoordSystems.mc | Message Constants for TRiASCoordSystems

#if !defined(_TRiASCoordSystems_H_46419BC0_4999_11d2_8FB8_0060085FC1CE)
#define _TRiASCoordSystems_H_46419BC0_4999_11d2_8FB8_0060085FC1CE

#if 1200 >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// allgemeine Fehler
//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_TCS                     0x1
#define FACILITY_STM                     0x7
#define FACILITY_RCS                     0x8
#define FACILITY_PCS                     0x4
#define FACILITY_GCS                     0x3
#define FACILITY_DTT                     0x6
#define FACILITY_CST                     0x5
#define FACILITY_CS                      0x2


//
// Define the severity codes
//
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: TCS_E_COMMON
//
// MessageText:
//
//  Allgemeiner Fehler.
//
#define TCS_E_COMMON                     ((HRESULT)0xC0011000L)

// @constv HRESULT | TCS_E_COMMON | 0xc0011000 |
// Allgemeiner Fehler.
// @doc
//
// MessageId: TCS_E_INVALIDPARAMETERINDEX
//
// MessageText:
//
//  Fehlerhafter Parameterindex.
//
#define TCS_E_INVALIDPARAMETERINDEX      ((HRESULT)0xC0011001L)

// @constv HRESULT | TCS_E_INVALIDPARAMETERINDEX | 0xc0011001 |
// Fehlerhafter Parameterindex.
// @doc
//
// MessageId: TCS_E_INVALIDPARAMETERCOUNT
//
// MessageText:
//
//  Fehlerhafte Parameteranzahl.
//
#define TCS_E_INVALIDPARAMETERCOUNT      ((HRESULT)0xC0011002L)

// @constv HRESULT | TCS_E_INVALIDPARAMETERCOUNT | 0xc0011002 |
// Fehlerhafte Parameteranzahl.
// @doc
//
// MessageId: TCS_E_INVALIDPARAMETER
//
// MessageText:
//
//  Fehlerhafter Parameter.
//
#define TCS_E_INVALIDPARAMETER           ((HRESULT)0xC0011003L)

// @constv HRESULT | TCS_E_INVALIDPARAMETER | 0xc0011003 |
// Fehlerhafter Parameter.
// @doc
//
// MessageId: TCS_E_CANNOTWRITEDATA
//
// MessageText:
//
//  Daten können nicht geschrieben werden.
//
#define TCS_E_CANNOTWRITEDATA            ((HRESULT)0xC0011004L)

// @constv HRESULT | TCS_E_CANNOTWRITEDATA | 0xc0011004 |
// Daten k÷nnen nicht geschrieben werden.
// @doc
//
// MessageId: TCS_E_INVALIDDATAFORMAT
//
// MessageText:
//
//  Fehlerhaftes Datenformat.
//
#define TCS_E_INVALIDDATAFORMAT          ((HRESULT)0xC0011005L)

// @constv HRESULT | TCS_E_INVALIDDATAFORMAT | 0xc0011005 |
// Fehlerhaftes Datenformat.
// @doc
//
// MessageId: TCS_E_CANNOTREADDATA
//
// MessageText:
//
//  Daten können nicht gelesen werden.
//
#define TCS_E_CANNOTREADDATA             ((HRESULT)0xC0011006L)

// @constv HRESULT | TCS_E_CANNOTREADDATA | 0xc0011006 |
// Daten k÷nnen nicht gelesen werden.
// @doc
//
// MessageId: TCS_E_ACCESS_DENIED
//
// MessageText:
//
//  Zugriff nicht möglich.
//
#define TCS_E_ACCESS_DENIED              ((HRESULT)0xC0011007L)

// @constv HRESULT | TCS_E_ACCESS_DENIED | 0xc0011007 |
// Zugriff nicht m÷glich.
// @doc
///////////////////////////////////////////////////////////////////////////////
// Fehler im Koordinatensystem
//
// MessageId: CS_E_INVALIDCOORDSYSTEMTYPE
//
// MessageText:
//
//  Fehlerhafter Koordinatensystemtyp.
//
#define CS_E_INVALIDCOORDSYSTEMTYPE      ((HRESULT)0xC0022001L)

// @constv HRESULT | CS_E_INVALIDCOORDSYSTEMTYPE | 0xc0022001 |
// Fehlerhafter Koordinatensystemtyp.
// @doc
//
// MessageId: CS_E_INVALIDCOORDSYSTEM
//
// MessageText:
//
//  Fehler im Koordinatensystem.
//
#define CS_E_INVALIDCOORDSYSTEM          ((HRESULT)0xC0022002L)

// @constv HRESULT | CS_E_INVALIDCOORDSYSTEM | 0xc0022002 |
// Fehler im Koordinatensystem.
// @doc
//
// MessageId: CS_E_UNKNOWNCOORDSYSTEM
//
// MessageText:
//
//  Unbekanntes Koordinatensystem.
//
#define CS_E_UNKNOWNCOORDSYSTEM          ((HRESULT)0xC0022003L)

// @constv HRESULT | CS_E_UNKNOWNCOORDSYSTEM | 0xc0022003 |
// Unbekanntes Koordinatensystem.
// @doc
//
// MessageId: CS_E_INVALIDGEOGRAPHICSYSTEM
//
// MessageText:
//
//  Fehlerhaftes geographisches System.
//
#define CS_E_INVALIDGEOGRAPHICSYSTEM     ((HRESULT)0xC0022004L)

// @constv HRESULT | CS_E_INVALIDGEOGRAPHICSYSTEM | 0xc0022004 |
// Fehlerhaftes geographisches System.
// @doc
//
// MessageId: CS_E_INVALIDPROJECTEDSYSTEM
//
// MessageText:
//
//  Fehlerhaftes projektives System.
//
#define CS_E_INVALIDPROJECTEDSYSTEM      ((HRESULT)0xC0022005L)

// @constv HRESULT | CS_E_INVALIDPROJECTEDSYSTEM | 0xc0022005 |
// Fehlerhaftes projektives System.
// @doc
//
// MessageId: CS_E_INVALIDDATUMTRANSFORMATION
//
// MessageText:
//
//  Fehlerhafte Datumstransformation.
//
#define CS_E_INVALIDDATUMTRANSFORMATION  ((HRESULT)0xC0022006L)

// @constv HRESULT | CS_E_INVALIDDATUMTRANSFORMATION | 0xc0022006 |
// Fehlerhafte Datumstransformation.
// @doc
//
// MessageId: CS_E_FILENOTFOUND
//
// MessageText:
//
//  Die angegebene Datei kann nicht gefunden werden.
//
#define CS_E_FILENOTFOUND                ((HRESULT)0xC0022010L)

// @constv HRESULT | CS_E_FILENOTFOUND | 0xc0022010 |
// Die angegebene Datei kann nicht gefunden werden.
// @doc
//
// MessageId: CS_E_FILECORRUPTED
//
// MessageText:
//
//  Die angegebene Datei ist keine gültige Koordinatensystemdatei.
//
#define CS_E_FILECORRUPTED               ((HRESULT)0xC0022011L)

// @constv HRESULT | CS_E_FILECORRUPTED | 0xc0022011 |
// Die angegebene Datei ist keine g³ltige Koordinatensystemdatei.
// @doc
//
// MessageId: CS_W_NEWEROBJECT
//
// MessageText:
//
//  Format des zu ladenden Objektes zu neu.
//
#define CS_W_NEWEROBJECT                 ((HRESULT)0x80022012L)

// @constv HRESULT | CS_W_NEWEROBJECT | 0x80022012 |
// Format des zu ladenden Objektes zu neu.
// @doc
///////////////////////////////////////////////////////////////////////////////
// Fehler im geodõtischen Koordinatensystem
//
// MessageId: GCS_E_INVALIDGEODETICDATUM
//
// MessageText:
//
//  Fehlerhaftes geodätisches Datum.
//
#define GCS_E_INVALIDGEODETICDATUM       ((HRESULT)0xC0033001L)

// @constv HRESULT | GCS_E_INVALIDGEODETICDATUM | 0xc0033001 |
// Fehlerhaftes geodõtisches Datum.
// @doc
//
// MessageId: GCS_E_INVALIDPRIMEMERIDIAN
//
// MessageText:
//
//  Fehlerhafte Zentralmeridian.
//
#define GCS_E_INVALIDPRIMEMERIDIAN       ((HRESULT)0xC0033002L)

// @constv HRESULT | GCS_E_INVALIDPRIMEMERIDIAN | 0xc0033002 |
// Fehlerhafte Zentralmeridian.
// @doc
//
// MessageId: GCS_E_INVALIDELLIPSOID
//
// MessageText:
//
//  Fehlerhaftes Ellipsoid.
//
#define GCS_E_INVALIDELLIPSOID           ((HRESULT)0xC0033003L)

// @constv HRESULT | GCS_E_INVALIDELLIPSOID | 0xc0033003 |
// Fehlerhaftes Ellipsoid.
// @doc
//
// MessageId: GCS_E_INVALIDUNITOFANGLE
//
// MessageText:
//
//  Fehlerhafte Winkeleinheit.
//
#define GCS_E_INVALIDUNITOFANGLE         ((HRESULT)0xC0033009L)

// @constv HRESULT | GCS_E_INVALIDUNITOFANGLE | 0xc0033009 |
// Fehlerhafte Winkeleinheit.
// @doc
///////////////////////////////////////////////////////////////////////////////
// Fehler im projektiven Koordinatensystem
//
// MessageId: PCS_E_INAVLIDPROJECTIONALGORITHM
//
// MessageText:
//
//  Ungültiger Projektionsalgorithmus.
//
#define PCS_E_INAVLIDPROJECTIONALGORITHM ((HRESULT)0xC0044001L)

// @constv HRESULT | PCS_E_INAVLIDPROJECTIONALGORITHM | 0xc0044001 |
// Ung³ltiger Projektionsalgorithmus.
// @doc
//
// MessageId: PCS_E_INAVLIDUNITOFLENGTH
//
// MessageText:
//
//  Ungültige Längeneinheit.
//
#define PCS_E_INAVLIDUNITOFLENGTH        ((HRESULT)0xC0044002L)

// @constv HRESULT | PCS_E_INAVLIDUNITOFLENGTH | 0xc0044002 |
// Ung³ltige Lõngeneinheit.
// @doc
//
// MessageId: PCS_E_INAVLIDTRANSFORMATION
//
// MessageText:
//
//  Fehler im Projektionskern.
//
#define PCS_E_INAVLIDTRANSFORMATION      ((HRESULT)0xC0044003L)

// @constv HRESULT | PCS_E_INAVLIDTRANSFORMATION | 0xc0044003 |
// Fehler im Projektionskern.
// @doc
//
// MessageId: PCS_E_INAVLIDPARAMETER
//
// MessageText:
//
//  Fehlerhafte(r) Parameter im projektiven System.
//
#define PCS_E_INAVLIDPARAMETER           ((HRESULT)0xC0044004L)

// @constv HRESULT | PCS_E_INAVLIDPARAMETER | 0xc0044004 |
// Fehlerhafte(r) Parameter im projektiven System.
// @doc
//
// MessageId: PCS_E_TRANSFORMATIONFAILED
//
// MessageText:
//
//  Transformation fehlgeschlagen.
//
#define PCS_E_TRANSFORMATIONFAILED       ((HRESULT)0xC0044010L)

// @constv HRESULT | PCS_E_TRANSFORMATIONFAILED | 0xc0044010 |
// Transformation fehlgeschlagen.
// @doc
///////////////////////////////////////////////////////////////////////////////
// Fehler im Datumstransformator
//
// MessageId: DTT_E_INAVLIDDATUMTRANSFORMATION
//
// MessageText:
//
//  Ungültiger Algorithmus für die Datumstransformation.
//
#define DTT_E_INAVLIDDATUMTRANSFORMATION ((HRESULT)0xC0065001L)

// @constv HRESULT | DTT_E_INAVLIDDATUMTRANSFORMATION | 0xc0065001 |
// Ung³ltiger Algorithmus f³r die Datumstransformation.
// @doc
//
// MessageId: DTT_E_INAVLIDGEODETICDATUM
//
// MessageText:
//
//  Ungültiges geodätisches Datum.
//
#define DTT_E_INAVLIDGEODETICDATUM       ((HRESULT)0xC0065002L)

// @constv HRESULT | DTT_E_INAVLIDGEODETICDATUM | 0xc0065002 |
// Ung³ltiges geodõtisches Datum.
// @doc
//
// MessageId: DTT_E_INCOMPATIBLEDATUMTRANSFORMATION
//
// MessageText:
//
//  Das Datumstransformationsverfahren im Quell und Zielsystem ist nicht kompatibel.
//
#define DTT_E_INCOMPATIBLEDATUMTRANSFORMATION ((HRESULT)0xC0065003L)

// @constv HRESULT | DTT_E_INCOMPATIBLEDATUMTRANSFORMATION  | 0xc0065003 |
// Das Datumstransformationsverfahren im Quell und Zielsystem ist nicht kompatibel.
// @doc
//
// MessageId: DTT_E_INAVLIDPARAMETER
//
// MessageText:
//
//  Fehlerhafte(r) Parameter im Datumstransformator.
//
#define DTT_E_INAVLIDPARAMETER           ((HRESULT)0xC0065004L)

// @constv HRESULT | DTT_E_INAVLIDPARAMETER | 0xc0065004 |
// Fehlerhafte(r) Parameter im Datumstransformator.
// @doc
//
// MessageId: DTT_E_TRANSFORMATIONFAILED
//
// MessageText:
//
//  Transformation fehlgeschlagen.
//
#define DTT_E_TRANSFORMATIONFAILED       ((HRESULT)0xC0065010L)

// @constv HRESULT | DTT_E_TRANSFORMATIONFAILED | 0xc0065010 |
// Transformation fehlgeschlagen.
// @doc
///////////////////////////////////////////////////////////////////////////////
// Fehler im Koordinatentransformator
//
// MessageId: CST_E_INVALIDCOORDSYSTEM
//
// MessageText:
//
//  Ungültiges Koordinatensystem.
//
#define CST_E_INVALIDCOORDSYSTEM         ((HRESULT)0xC0056001L)

// @constv HRESULT | CST_E_INVALIDCOORDSYSTEM | 0xc0056001 |
// Ung³ltiges Koordinatensystem.
// @doc
//
// MessageId: CST_E_INVALIDSOURCECOORDSYSTEM
//
// MessageText:
//
//  Ungültiges Eingangskoordinatensystem.
//
#define CST_E_INVALIDSOURCECOORDSYSTEM   ((HRESULT)0xC0056002L)

// @constv HRESULT | CST_E_INVALIDSOURCECOORDSYSTEM | 0xc0056002 |
// Ung³ltiges Eingangskoordinatensystem.
// @doc
//
// MessageId: CST_E_INVALIDDESTINATIONCOORDSYSTEM
//
// MessageText:
//
//  Ungültiges Ausgangskoordinatensystem.
//
#define CST_E_INVALIDDESTINATIONCOORDSYSTEM ((HRESULT)0xC0056003L)

// @constv HRESULT | CST_E_INVALIDDESTINATIONCOORDSYSTEM | 0xc0056003 |
// Ung³ltiges Ausgangskoordinatensystem.
// @doc
//
// MessageId: CST_E_COORDSYSTEMNOTFOUND
//
// MessageText:
//
//  Das angegebene Koordinatensystem kann nicht gefunden werden.
//
#define CST_E_COORDSYSTEMNOTFOUND        ((HRESULT)0xC0056004L)

// @constv HRESULT | CST_E_COORDSYSTEMNOTFOUND | 0xc0056004 |
// Das angegebene Koordinatensystem kann nicht gefunden werden.
// @doc
//
// MessageId: CST_E_COORDSYSTEMALREADYPRESENT
//
// MessageText:
//
//  Ein Koordinatensystem ist unter diesen GUID bereits eingetragen.
//
#define CST_E_COORDSYSTEMALREADYPRESENT  ((HRESULT)0xC0056005L)

// @constv HRESULT | CST_E_COORDSYSTEMALREADYPRESENT | 0xc0056005 |
// Ein Koordinatensystem ist unter diesen GUID bereits eingetragen.
// @doc
//
// MessageId: CST_E_INCOMPATIBLEDATUMTRANSFORMATION
//
// MessageText:
//
//  Inkompatible Datumstransformation.
//
#define CST_E_INCOMPATIBLEDATUMTRANSFORMATION ((HRESULT)0xC0056006L)

// @constv HRESULT | CST_E_INCOMPATIBLEDATUMTRANSFORMATION | 0xc0056006 |
// Inkompatible Datumstransformation.
// @doc
//
// MessageId: CST_E_INVALIDCOORDCOUNT
//
// MessageText:
//
//  Koordinatenanzahl fehlerhaft (keine {X,Y,Z} Tripel).
//
#define CST_E_INVALIDCOORDCOUNT          ((HRESULT)0xC0056011L)

// @constv HRESULT | CST_E_INVALIDCOORDCOUNT | 0xc0056011 |
// Koordinatenanzahl fehlerhaft (keine {X,Y,Z} Tripel).
// @doc
//
// MessageId: CST_E_INPUTTRANSFORMATIONFAILED
//
// MessageText:
//
//  Transformation aus dem Quellsystem fehlgeschlagen.
//
#define CST_E_INPUTTRANSFORMATIONFAILED  ((HRESULT)0xC0056012L)

// @constv HRESULT | CST_E_INPUTTRANSFORMATIONFAILED | 0xc0056012 |
// Transformation aus dem Quellsystem fehlgeschlagen.
// @doc
//
// MessageId: CST_E_OUTPUTTRANSFORMATIONFAILED
//
// MessageText:
//
//  Transformation in das Zielsystem fehlgeschlagen.
//
#define CST_E_OUTPUTTRANSFORMATIONFAILED ((HRESULT)0xC0056013L)

// @constv HRESULT | CST_E_OUTPUTTRANSFORMATIONFAILED | 0xc0056013 |
// Transformation in das Zielsystem fehlgeschlagen.
// @doc
///////////////////////////////////////////////////////////////////////////////
// Fehler im StorageManager
//
// MessageId: STM_E_COORDSYSTEMNOTFOUND
//
// MessageText:
//
//  Das angegebene Koordinatensystem kann nicht gefunden werden.
//
#define STM_E_COORDSYSTEMNOTFOUND        ((HRESULT)0xC0076004L)

// @constv HRESULT | STM_E_COORDSYSTEMNOTFOUND | 0xc0076004 |
// Das angegebene Koordinatensystem kann nicht gefunden werden.
// @doc
///////////////////////////////////////////////////////////////////////////////
// Fehler im Raw-Transformator
//
// MessageId: RCS_E_COMMON
//
// MessageText:
//
//  Allgemeiner Fehler in der Transformationbibliothek.
//
#define RCS_E_COMMON                     ((HRESULT)0xC0087001L)

// @constv HRESULT | RCS_E_COMMON | 0xc0087001 |
// Allgemeiner Fehler in der Transformationbibliothek.
// @doc
//
// MessageId: RCS_E_HA_NULL
//
// MessageText:
//
//  Große Halbachse ist null.
//
#define RCS_E_HA_NULL                    ((HRESULT)0xC0087002L)

// @constv HRESULT | RCS_E_HA_NULL | 0xc0087002 |
// Gro¯e Halbachse ist null.
// @doc
//
// MessageId: RCS_E_F_NULL
//
// MessageText:
//
//  Abplattung ist null.
//
#define RCS_E_F_NULL                     ((HRESULT)0xC0087003L)

// @constv HRESULT | RCS_E_F_NULL | 0xc0087003 |
// Abplattung ist null.
// @doc
//
// MessageId: RCS_E_SCALE_NULL
//
// MessageText:
//
//  Skalierungsfaktor ist null.
//
#define RCS_E_SCALE_NULL                 ((HRESULT)0xC0087004L)

// @constv HRESULT | RCS_E_SCALE_NULL | 0xc0087004 |
// Skalierungsfaktor ist null.
// @doc
//
// MessageId: RCS_E_MODELPARAMETERS
//
// MessageText:
//
//  Fehlerhafte Modellparameter.
//
#define RCS_E_MODELPARAMETERS            ((HRESULT)0xC0087011L)

// @constv HRESULT | RCS_E_MODELPARAMETERS | 0xc0087011 |
// Fehlerhafte Modellparameter.
// @doc
//
// MessageId: RCS_E_SINGULAR
//
// MessageText:
//
//  Singuläre Matrix.
//
#define RCS_E_SINGULAR                   ((HRESULT)0xC0087101L)

// @constv HRESULT | RCS_E_SINGULAR | 0xc0087101 |
// Singulõre Matrix.
// @doc
//
// MessageId: RCS_E_BADPARALLEL
//
// MessageText:
//
//  Equal Latitiudes for Standard Parallels on opposite sides of equator.
//
#define RCS_E_BADPARALLEL                ((HRESULT)0xC0087102L)

// @constv HRESULT | RCS_E_BADPARALLEL | 0xc0087102 |
// Equal Latitiudes for Standard Parallels on opposite sides of equator.
// @doc
//
// MessageId: RCS_E_NOCONVERGENCE
//
// MessageText:
//
//  Konvergenzfehler.
//
#define RCS_E_NOCONVERGENCE              ((HRESULT)0xC0087103L)

// @constv HRESULT | RCS_E_NOCONVERGENCE | 0xc0087103 |
// Konvergenzfehler.
// @doc
//
// MessageId: RCS_E_CANTPROJECTPOINT
//
// MessageText:
//
//  Punkt kann nicht projeziert werden.
//
#define RCS_E_CANTPROJECTPOINT           ((HRESULT)0xC0087104L)

// @constv HRESULT | RCS_E_CANTPROJECTPOINT | 0xc0087104 |
// Punkt kann nicht projeziert werden.
// @doc
///////////////////////////////////////////////////////////////////////////////
// Fehler im DistanceService
//
// MessageId: CS_E_INVALIDACCURACYTYPE
//
// MessageText:
//
//  Fehlerhafte Genauigkeitsgrundlage für Berechnungen.
//
#define CS_E_INVALIDACCURACYTYPE         ((HRESULT)0xC0028001L)

// @constv HRESULT | CS_E_INVALIDACCURACYTYPE | 0xc0028001 |
// Fehlerhafte Genauigkeitsgrundlage f³r Berechnungen.
// @doc
#endif


***********************************************************************
@doc EXAMPLES 
@topic Koordinatentransformation - Geodätisch zu Gauß-Krüger | 
@ex Koordinatentransformation - Geodätisch zu Gauß-Krüger | Attribute VB_Name = "GeoZuGau"
Option Explicit
Option Base 0
Const dX = 606.069176231606
Const dY = 22.9985051548215
Const dZ = 413.04801358317

'------------------------------------------------------------
' Transformation von geodätischen zu Gauß-Krüger Koordinaten

Sub TestGeoZuGau()
    Dim CTF As New TRiASCSTransform
    Dim CS1 As New TRiASCS
    Dim CS2 As New TRiASCS
    On Error GoTo errHandler
    
    CS1.CoordSystemType = tcsCS_Geographic
    With CS1.GeographicCS
        .GeodeticDatum = tcsGD_DeutscheHauptdreiecksnetz
        .PrimeMeridian = tcsPM_Greenwich
    End With
    With CS1.ProjectedCS
        .ProjectionAlgorithm = tcsPA_GaussKrueger
        .ProjectionParameter(tcsPP_GaussKrueger_FalseEasting) = 4500000#
        .ProjectionParameter(tcsPP_GaussKrueger_FalseNorthing) = 0#
        .ProjectionParameter(tcsPP_GaussKrueger_LongitudeOfNaturalOrigin) = 12#
        .ProjectionParameter(tcsPP_GaussKrueger_LatitudeOfNaturalOrigin) = 0#
    End With
    With CS1.DatumTransformation
        .TransformationAlgorithm = tcsDTA_GeocentricTranslations
        .Parameter(tcsDTP_GeocentricTranslations_XAxisTranslation) = dX
        .Parameter(tcsDTP_GeocentricTranslations_YAxisTranslation) = dY
        .Parameter(tcsDTP_GeocentricTranslations_ZAxisTranslation) = dZ
    End With
    
    CS2.CoordSystemType = tcsCS_Geographic
    With CS2.GeographicCS
        .GeodeticDatum = tcsGD_WorldGeodeticSystem1984
        .PrimeMeridian = tcsPM_Greenwich
    End With
    With CS2.ProjectedCS
        .ProjectionAlgorithm = tcsPA_GaussKrueger
        .ProjectionParameter(tcsPP_GaussKrueger_FalseEasting) = 4500000#
        .ProjectionParameter(tcsPP_GaussKrueger_FalseNorthing) = 0#
        .ProjectionParameter(tcsPP_GaussKrueger_LongitudeOfNaturalOrigin) = 12#
        .ProjectionParameter(tcsPP_GaussKrueger_LatitudeOfNaturalOrigin) = 0#
    End With
    With CS2.DatumTransformation
        .TransformationAlgorithm = tcsDTA_GeocentricTranslations
        .Parameter(tcsDTP_GeocentricTranslations_XAxisTranslation) = 0
        .Parameter(tcsDTP_GeocentricTranslations_YAxisTranslation) = 0
        .Parameter(tcsDTP_GeocentricTranslations_ZAxisTranslation) = 0
    End With
    
    '/////////////////////////////////////////////////////////////////////////////////////
    '// der Transformator...
    Dim csIn As TRiASCS, csOut As TRiASCS
    Set csIn = CS1
    Set csOut = CS2
    With csIn
        .CoordSystemType = tcsCS_Geographic
        .GeographicCS.UnitOfAngle = tcsUOA_Second
    End With
    With csOut
        .CoordSystemType = tcsCS_Projected
        .GeographicCS.UnitOfAngle = tcsUOA_Degree
        .ProjectedCS.UnitOfLength = tcsUOL_Metre
    End With
    
    CTF.AddInputCS csIn
    CTF.OutputCS = csOut
    CTF.OutputCS.Recompute
    
    '/////////////////////////////////////////////////////////////////////////////////////
    '// die Koordinate
    Dim ptsIn() As Double: ReDim ptsIn(0 To 2)
    ptsIn(0) = 12# * 3600                       '11# * 3600# + 59# * 60# + 54.5128311
    ptsIn(1) = 52# * 3600 + 30# * 60#           '52# * 3600# + 29# * 60# + 54.8759844
    ptsIn(2) = 0
    '/////////////////////////////////////////////////////////////////////////////////////
    '// ...transformieren
    Dim ptsOut As Variant
    ptsOut = CTF.Transform(strguid:=csIn.Guid, inpoints:=ptsIn)
    CTF.ShutDown
    ptsOut(0) = ptsOut(0) - 4499896.48687
    ptsOut(1) = ptsOut(1) - 5818821.21615
errHandler:
End Sub

@topic Speichern / Lesen von Koordinatensystemen | 
@ex Speichern / Lesen von Koordinatensystemen | Attribute VB_Name = "CSSet"
Option Explicit
Option Base 0

Sub TestCSSet()
    Dim csSet1 As New TRiASCSSet
    Dim csSet2 As New TRiASCSSet
    Dim csSet3 As New TRiASCSSet
    
    Dim cs As TRiASCS, cs2 As TRiASCS, i%, s$
    
    For i% = 0 To 10
        Set cs = New TRiASCS
        If 8 = i% Then Set cs2 = cs
        If 0 = i Mod 3 Then
            cs.CoordSystemType = tcsCS_Projected
            cs.Category = "Gauß-Krüger Koordinatensysteme"
        End If
        If 1 = i Mod 3 Then
            cs.CoordSystemType = tcsCS_Geographic
            cs.Category = "Geodätische Koordinatensysteme"
        End If
        If 2 = i Mod 3 Then
            cs.CoordSystemType = tcsCS_Projected
            cs.Category = "Allgemeine Koordinatensysteme"
        End If
        cs.Description = "Koordinatensystem " & i%
        csSet1.Add cs
    Next
    For Each cs In csSet1
        s$ = cs.Description
    Next
    i% = csSet1.Count
    Set cs = csSet1.Find(5)
    Set cs = csSet1.Find("CS 7")
    Set cs = csSet1.Find(cs2)
    csSet1.Remove ("CS 3")
    Set cs = csSet1.Find(5)
    csSet1.SaveToFile ("c:\tmp\csset.dat")
    csSet1.SaveToRegistry TCS_HKCU, "Software\FEZ\TRiAS\CoordinateSystems"
    
    csSet2.LoadFromFile ("c:\tmp\csset.dat")
    csSet2.LoadFromRegistry TCS_HKCU, "Software\FEZ\TRiAS\CoordinateSystems"
    csSet2.SaveToFile ("c:\tmp\csset2.dat")
End Sub

@topic Ermitteln eines guten Containers | 
@ex Ermitteln eines guten Containers | Attribute VB_Name = "ModTestGoodEnvelope"
Option Explicit

Sub TestGoodEnvelope()
    Dim csOut As New TRiASCS, csTrans As New TRiASCSTransform
    Dim x0#, y0#, x1#, y1#
    '----------------------------------------------------------------
    ' OutputSystem muß gegeben sein; csOut ist per Default als
    ' WGS84/Cyl-Equi initialisiert
    csTrans.OutputCS = csOut
    csTrans.GetGoodEnvelope x0, y0, x1, y1
    
    csOut.CoordSystemType = tcsCS_Geographic
    csOut.GeographicCS.UnitOfAngle = tcsUOA_Degree
    csOut.Recompute
    csTrans.GetGoodEnvelope x0, y0, x1, y1
    csTrans.ShutDown
End Sub

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

// @doc
// @topic Koordinatentransformationen - eine Einführung |
// Eine Koordinatentransformation dient der Umrechnung eines oder mehrerer Koordinatenpunkte
// aus einem Koordinatensystem in ein anderes. Das ist zum Beispiel dann notwendig, wenn Daten 
// verschiedener Datenquellen, die in verschiedenen Koordinatensystemen vorliegen, gleichzeitig
// angezeigt oder ausgewertet werden sollen.
//
// Das zentrale Objekt einer Koordinatentransformation in <tr> ist daher das <o TRiASCSTransform> Objekt,
// welches es ermöglicht, Koordinaten verschiedener Eingangs-Koordinatensystem in ein vorgebbares
// Ausgangskoordinatensystem zu konvertieren (bzw. umgekehrt). Das Koordinatensystem am Ausgang des 
// Transformators ist im allgemeinen das Koordinatensystem des <tr>- Projektes, die Koordinatensysteme 
// am Eingang des Transformators entsprechen im allgemeienen den Koordinatensystemen, in denen die Daten 
// der einzelnen Datenquellen vorliegen.
// 
// Zu weiteren Informationen zu Koordinatensystemen siehe <l Koordinatensysteme - eine Einführung>
// Das Koordinatensystem am Ausgang des Transformators wird mit der <op ITRiASCSTransform.OutputCS>
// gesetzt bzw. gelesen. 
//
// @xref <l Koordinatensysteme - eine Einführung>, <l Definition von Koordinatentransformationen>,
// <o TRiASCSTransform>
// @end

///////////////////////////////////////////////////////////////////////////////
// @topic Definition von Koordinatentransformationen |
// @xref <o TRiASCSTransform>
// @end

///////////////////////////////////////////////////////////////////////////////
// @topic Koordinatensysteme - eine Einführung |
// Ein Koordinatensystem in <tr> wird durch das <o TRiASCS>- Objekt repräsentiert und definiert das 
// Bezugssystem, in welchem die Koordinaten einzelner Punkte
// abgebildet werden. Im allgemeinen werden 2 dimensionale und 3 dimensionale Koordinatensysteme 
// unterschieden. Obwohl sämtliche Funktionen in <tr>, die mit Koordinaten zu tun haben, davon ausgehen, 
// daß die Koordinaten als Punkte-Tripel (X, Y, Z) gegeben sind, so werden z.Zt. jedoch nur die 
// Werte X und Y ausgewertet, der Z-Wert (Höhe über Normalnull) wird derzeit in <tr> grundsätzlich 
// ignoriert.
//
// Zentrale Bedeutung bei der Beschreibung eines Koordinatensystemes kommt dem sogenannten 
// <b geodätischen Datum> zu, welches die Gesamtheit der beschreibenden Parameter des dem Koordinatensystem 
// zu Grunde liegenden Erdmodelles beinhaltet. Ein geodätisches Datum kann horizontal, vertikal oder 
// vollständig sein, je nach dem, ob es in erster Linie 2 dimensionale Zusammenhänge auf der Erdoberfläche, 
// Höhen zu einer Bezugsebene oder beide gleichzeitig beschreibt.
// Beispiele für ein geodätisches Datum sind 'Deutsches Hauptdreiecksnetz', 'Pulkovo 1942' oder 'WGS 1984'.
//
// Da die Koordinaten von Punkten der Erdoberfläche in den seltensten Fällen als Punkte in einer Ebene 
// angenommen werden können, liegen den meisten erdbezogenen Koordinatensystemen ellipsoidale Modelle
// zu Grunde, die besonders bei größeren Entfernungen zwischen zwei Punkten erheblich bessere Genauigkeiten
// liefern. Diese ellipsoidalen Modelle gehen von Rotationsellipsoiden aus, die durch eine Äquatorial- und 
// einen Polarradius definiert sind. Diese Radien bezeichnet man als <b große Halbachse> (Äquatorialradius) 
// bzw. <b kleine Halbachse> (Polarradius) und den sich daraus ergebenden Ellispoiden als 
// <b Referenzellipsoid> des Koordinatensystemes. Andere Parameter des Referenzellipsoides wie Abflachung 
// oder Exzentrizität lassen sich aus den beiden Halbachsen berechnen.
// Beispiele für Referenzellipsoide sind 'Bessel 1841', 'Krassovky 1940' oder 'WGS 84'.
//
// Je nach konkret verwendetem Koordinatensystem unterscheidet man nach der Koordinatenprojektion, die 
// die Punktkoordinaten der Karte erzeugt. Die wohl bekanntesten Projektionen in Deutschland sind
// die Gauß-Krüger Projektion (eine UTM- Projektion, UTM steht für <b u>niversal <b t>ransvers <b m>ercator)
// oder die Lambert- Projektion (eine Kegelprojektion). Projektionen werden verwendet, um Koordinatensysteme 
// zu erhalten, welche, je nach Anwendungsfall, z.B. längen-, winkel- oder flächentreu sind. Das ist 
// notwendig, da die unmittelbar auf den Ellipsoid bezogenen Koordinatensysteme diese Eigenschaften nicht 
// besitzen und daher schlecht für den täglichen Gebrauch z.B. zur Erstellung von thematischen Karten 
// geeignet sind.
//
// @xref <l Definition von Koordinatensystemen>, <o TRiASCS>
// @end

///////////////////////////////////////////////////////////////////////////////
// @topic Definition von Koordinatensystemen |
// 
// @xref <o TRiASCS>
// @end

