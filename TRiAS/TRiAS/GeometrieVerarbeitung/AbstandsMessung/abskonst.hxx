// Konstanten für Abstandsbestimmung
// File: ABSKONST.HXX
// W. Mörtl

#if !defined(_ABSKONST_HXX)
#define _ABSKONST_HXX


// ********************************************************************************************
// Konstantendefinitionen
const long lSpGr = 4096;// Größe des Speichers, in dem Meßergebnisse zwischengespeichert werden
const double dVer = 20;	// ist der Mittelpunktsabstand mindestens dVer-mal größer als die
						// größte Seite des ein Objekt umschließenden Rechtecks, dann wir
						// dieses Objekt automatisch auf den Rechteckmittelpunkt reduziert und
						// für die Abstandsberechnung nicht die Stützpunkte im einzelnen
						// hinzugezogen
const int iOff = 5;	// Abstand für Textobjekt von dem dazugehörigen Kilometrierungspunkt
						// (in BS-Pixel)

#endif  // _ABSKONST_HXX
