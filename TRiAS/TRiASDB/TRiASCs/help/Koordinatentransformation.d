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
