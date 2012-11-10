// @doc LEVEL1
// @topic TRiAS® Datenobjekte |
// Sämtliche TRiAS® Datenobjekte sind hierarchisch miteinander verbunden. Sie besitzen 
// einen der vordefinierten Datentypen <t RTTI>.
//
// An der Spitze dieser Hierachie steht das vordefinierte DatenObjekt 'TRiAS', vom 
// Typ <o Application>, welches das Programm <tr> als Ganzes repräsentiert. 
//
// Alle <tr> Datenobjekte haben folgende allgemeine Eigenschaften:
// <nl><op DTRiASBaseClass.isA>
// <nl><op DTRiASBaseClass.Parent>
// <nl><op DTRiASBaseClass.Application>
//
// In der <b internen Macrosprache> haben sämtliche Datenobjekte zusätzlich
// die folgende allgemeine Eigenschaft:
// <nl><op DTRiASBaseClass.IDispatch>

// @doc DTRIASBASECLASS | BSPROPERTY
// @property IDispatch * | DTRiASBaseClass | IDispatch | Die Eigenschaft <op DTRiASBaseClass.IDispatch> liefert das 
// zugehörige OLE-Dispatch Interface, welches an externe Programme (z.B. VisualBasic) übergeben werden 
// kann.
// @comm Die Eigenschaft <op DTRiASBaseClass.IDispatch> kann nicht gesetzt werden.
// @xref <i DTRiASBaseClass>
// @ex Beispiel für die Nutzung der Eigenschaft <op DTRiASBaseClass.IDispatch> |
//	' Das vordefinierte Datenobjekt 'TRiAS' 
//	' soll an eine externe Routine übergeben werden
//	Dim Obj As Object	
//
//		Set Obj = TRiAS.IDispatch
//		SetExternalObject Obj
//

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECTSINBS
// @topic Typen von TRiAS® Datenobjekten |
// Ein TRiAS® Datenobjekt kann einen der folgenden Typen besitzen:
//
// <o Application>: das Programm <tr>
// <nl><o GeoDocument>: ein <tr> Projekt,
// <nl><o GeoClass>: eine <tr> Objektklasse,
// <nl><o GeoView>: eine Ansicht in einem <tr> Projekt,
// <nl><o GeoObject>: ein einzelnes <tr> Objekt (Punkt-, Linien-, Flächen- oder Textobjekt),
// <nl><o GeoFeature>: eine <tr> Objekteigenschaft,
// <nl><o GeoObjectWin>: ein Objektrecherchefenster,
// <nl><b Visualisierungsobjekte>: Objekte, über die die Darstellungsparameter von Einzelobjekten 
// oder von Objektklassen beeinflußt werden können,
// <nl><b Symbolleistenobjekte>: Objekte, die Symbolleisten bzw. einzelne Symbolleisten-Knöpfe 
// repräsentieren,
// <nl><o ProgressIndicator>: ein Objekt, welches lange Operationen durch die Anzeige eines
// Fensters mit Statusanzeige für den Nutzer transparent machen kann.
//
// Die meisten dieser Datentypen existieren sowohl als Einzeldatenobjekt als auch als Sammlung 
// gleichartiger Einzeldatenobjekte, sogenannter Collection-Objekte. Collection-Objekttypen bilden 
// sich jeweils aus der Mehrzahl des zugehörigen Einzeldatenobjekttyps:
//
// <o GeoDocument> - <o GeoDocuments>
// <nl><o GeoClass> - <o GeoClasses>
// <nl><o GeoView> - <o GeoViews>
// <nl><o GeoObject> - <o GeoObjects>
// <nl><o GeoFeature> - <o GeoFeatures>
// <nl><o GeoObjectWin> - <o GeoObjectWins>
//
// Sammlungen von Datenobjekten finden überall dort Anwendung, wo mehrere Datenobjekte eines 
// Datentypes gleichzeitig bzw. gleichartig behandelt werden sollen.
// <nl>Es existieren zwei Typen von Datenobjektsammlungen:
// 1. Datenobjektsammlungen, deren Elemente nicht außerhalb dieser existieren können und
// 2. Datenobjektsammlungen, deren Elemente auch außerhalb von derartigen Collections existieren
// können.
// <nl>Nähere Informationen finden Sie dazu im Abschnitt <l Typen von Datenobjektsammlungen>.
//
// Alle <tr> Datenobjektsammlungen haben folgende allgemeine Eigenschaften und Methoden:
// <nl><op DTRiASCollection.Count>
// <nl><om DTRiASCollection.Add>
// <nl><om DTRiASCollection.Item>
// <nl><om DTRiASCollection.Refresh>
// <nl><om DTRiASCollection.Remove>
//
// Der Typ <t RTTI> eines TRiAS® Datenobjektes kann über die Eigenschaft <op DTRiASBaseClass.isA> abgefragt 
// werden.
// @xref <l Typen von Datenobjektsammlungen>

