// @doc
// @topic Recherchen in TRiAS® |
// Die Recherche in <tr> ist auf der Grundlage folgender Regeln implementiert.
//
// Sämtliche Recherchen erfolgen über das <i ITRiASSearchObjects> -Interface.
// 
// Recherchen erfolgen der Reihe nach in allen betroffenen Datenquellen. 
// Die dabei gefundenen Objekte werden in der Resultats-Objektmenge durch
// eine ODER-Operation zusammengefaßt.
// 
// Für jede betroffene Datenquelle wird für das zugehörige Datenbank-Objekt
// getestet, ob für dieses das <i ITRiASSearchObjects> -Interface implementiert ist.
// Wenn dies der Fall ist, wird die Methode <om ITRiASSearchObjects.ConsiderSearch>
// gerufen. Wenn diese Methode <cv S_OK> liefert, wird davon ausgegangen, daß die
// Recherche <b vollständig> durch das Datenbank-Objekt durchgeführt werden kann.
// daher wird am Datenbank-Objekt die Methode <om ITRiASSearchObjects.SearchObjects> 
// gerufen, welche die eigentliche Recherche durchführt und sämtliche Objekte liefert, 
// die das gegebene Suchkriterium erfüllen.
// <nl>Liefert <om ITRiASSearchObjects.ConsiderSearch> dagegegen <cv TRIASDB_S_SEARCH_NOT_SUPPORTED>,
// oder <cv TRIASDB_S_SEARCH_NOT_RECOMMENDED>, dann wird davon ausgegangen, daß die 
// Recherche durch andere Objekte durchgeführt werden kann (s.u.)
// 
// Der nächste Kandidat für die Recherche ist das ObjectsCollection-Objekt.
// Die Reihenfolge der Aufrufe ist identisch.
// <nl>Durch das ObjectsCollection-Objekt werden zuerst die betroffenen Objekteigenschafts-Objekte
// in identischer Form getestet, ob durch diese die Recherche durchgeführt werden kann.
// Schlägt die Recherche durch die Objekteigenschafts-Objekte fehl, dann werden sequentiell 
// alle Objektklassen-Objekte untersucht.
// 
// Jedes der jetzt untersuchten Objektklassen-Objekte testet sequentiell das 
// Recherchekriterium für jedes Objekt der Objektklasse und fügen die entsprechend 
// gefundenen Objekte zur Resultatobjektmenge hinzu.
//
// <nnl>-> Nach erfolgreichem Abschluß der Recherche bis zu diesem Punkt wird die
// Ergebnisobjektmenge ggf. mit den Objektklassen der aktuellen Ansicht abgeglichen, 
// so daß in diesem Fall keine Objekte in der Resultatmenge enthalten sind, die
// nicht ebenfalls zur aktuellen Ansicht gehören. Dieser Abgleich erfolgt durch die
// Methode <om ITRiASSearchObjects.ConstraintObjects> des ObjectsCollection-Objektes 
// der zu untersuchenden Ansicht.
// 
// <nnl>In einem Datenserver-Modul können selbst eigene Recherchefunktionalitäten 
// implementiert werden, wenn diese evtl. schneller Ergebnisse liefern, als der 
// in TRiAS als 'Notanker' vorgesehene sequentielle Suchalgorithmus. 
//
// Um die beschriebene Abfolge der Recherche zu modifizieren, kann an jedem der 
// genannten Objekte das <i ITRiASSearchObjects> -Interface implementiert werden, 
// durch welches die gewünschte Recherchefunktionalität implementiert werden kann.
//
// @xref <i ITRiASSearchObjects>
