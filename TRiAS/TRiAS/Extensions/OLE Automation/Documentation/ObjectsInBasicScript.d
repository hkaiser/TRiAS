// @doc LEVEL1
// @topic Objekte in BasicScript® |
// In BasicScript® sind neben den im Abschnitt <l Variablen in BasicScript®> beschriebenen einfachen
// Variablentypen zwei verschiedene Objekttypen verwendbar:
// <nl>1. <b Datenobjekte>, die programminternen Sachverhalten in <tr> selbst entsprechen und
// <nl>2. <b OLE Automationsobjekte>, die Sachverhalte in anderen, externen Anwendungen außerhalb 
// von <tr> widerspiegeln.<nl>Beide Objekttypen werden in BasicScript® syntaktisch gleichartig 
// behandelt.
//
// Neben den vordefinierten BasicScript® Datenobjekten sind <tr>-spezifische Datenobjekte 
// vorhanden, die dem thematischen Sachverhalt der Arbeit in einem Geo-Informationssystem entsprechen. 
// Eine entsprechende Übersicht finden Sie im Kapitel <l TRiAS® Datenobjekte>
//
// @xref <l Variablen in BasicScript®>
// Im vorliegenden Kapitel sind folgende Problemkreise beschrieben:
// @index | OBJECTSINBS
//

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECTSINBS
// @topic Was ist ein Objekt | 
// Ein Datenobjekt repräsentiert die Kapselung von spezifischen Daten und der Routinen, 
// die zur Verarbeitung dieser Daten notwendig sind. Sie haben damit den Effekt, daß die 
// durch das jeweilige Datenobjekt gekapselten Daten immer gemeinsam mit den zugehörigen 
// spezifischen Methoden für Manipulation dieser Daten verwaltet werden. 
// <nl>Es ist damit gewährleistet, daß Daten immer nur durch Routinen behandelt werden, die zu 
// diesen Daten gehören und eine 'Fehlnutzung' von fremden, nicht zu diesen Daten passenden 
// Routinen ausgeschlossen wird.
// 
// <nl>Datenobjekte stellen verschiedene Typen von Routinen zur Verfügung:
// <nl><b Properties>: konkreten Eigenschaften, zumeist Einzelwerte aus objektspezifischen 
// Wertebereichen oder andere Elementarinformationen. Properties können im allgemeinen 
// abgefragt (get) und verändert (set) werden.
// <nl><b Methoden>: Algorithmische Abläufe, die objektspezifische Aktionen realisieren. In 
// BasicScript® existieren zwei verschiedene Typen von Methoden: Funktionen (<blue Function>) 
// und Unterprogramme (<blue Sub>).
// @xref <l Objekte in BasicScript®>

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECTSINBS
// @topic Deklaration von Objektvariablen | 
// Um ein Datenobjekt verwenden zu können, muß dieses vorab deklariert werden, d.h. es 
// muß dem Basic-System gegenüber bekanntgemacht werden, daß ein (frei wählbarer) Name 
// im folgenenden ein Datenobjekt eines bestimmten Datentypes verkörpert.
// <nl>Eine Deklaration eines Datenobjektes erfolgt mit den BasicScript® Operatoren <blue Dim>, 
// <blue Public> oder <blue Private>. 
// @ex Eine Deklaration muß folgende Syntax besitzen |
// Dim ObjektName As ObjektTyp		oder
// Public ObjektName As ObjektTyp	oder
// Private ObjektName As ObjektTyp
// @normal 
// Der Operator <blue Dim> wird zur Deklaration von Datenobjekten innerhalb von 
// BasicScript® Routinen verwendet. Diese Datenobjekte behalten ihren Wert im allgemeinen 
// lediglich während der Bearbeitung der Routine ihren Wert, in der sie deklariert und 
// initialisiert wurden.
// 
// <nl>Der Operator <blue Public> wird zur Deklaration von Datenobjekten verwendet, die in allen 
// BasicScript® Routinen aller aktiven Scripte 'sichtbar' und verwendbar sein sollen. 
// Diese Datenobjekte behalten den ihnen einmal zugewiesenen Wert bei, bis <tr> beendet wird. 
// Dieser Operator wird sicher äußerst selten zum Einsatz kommen.
// 
// <nl>Der Operator <blue Private> wird zur Deklaration von Datenobjekten außerhalb von BasicScript® 
// Routinen verwendet. Diese Datenobjekte behalten ihren Wert während der Bearbeitung des 
// Scriptes bei, in dem sie deklarariert und initialisiert wurden.
// Nach der Deklaration wird dem neuen Datenobjekt der Wert '0' (Null) bzw. <blue Nothing> zugewiesen. 
// Bevor dieses Datenobjekt verwendet werden kann, muß ihm daher ein Wert zugewiesen werden (Initialisierung) .
// @xref <l Objekte in BasicScript®>

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECTSINBS
// @topic Zuweisen eines Wertes einer Objektvariablen | 
// Datenobjekte müssen vor ihrer Nutzung grundsätzlich initialisiert werden, d.h. ihnen 
// muß ein Wert zugewiesen werden. Durch eine Initialisierung legt man fest, welches konkrete 
// Objekt durch die deklarierte Variable repräsentiert wird. Diese Initialiserung erfolgt 
// mit dem BasicScript® Operator Set.
// @ex Beispiel einer Initialisierung |
//	Dim myDataObj As DataObjectType		'Datenobjekt
//
//		Set myDataObj = New DataObjectType	
//
// oder verkürzt:
//
//	Dim myDataObj As New DataObjectType 
//
// @normal 
// <tr> Datenobjekte werden selten mit dem BasicScript® Operator <blue New> initialisiert 
// werden, da keinerlei Kontextinformation vorgegeben werden kann, die jedoch durch die 
// ausgeprägte Objekthierarchie in <tr> unerlässlich ist. So muß beispielsweise ein 
// Datenobjekt von Typ <o GeoObject> bereits bei seiner Initialisierung einem <tr> Projekt 
// zugeordnet werden, ohne eine derartige Zuordnung ist keine Arbeit möglich und sinnvoll.
// 
// Die Initialisierung von <tr> Datenobjekten erfolgt daher im allgemeinen durch eine 
// Routine des jeweils übergeordneten Datenobjektes. Ein Datenobjekt vom Typ <o GeoObject> kann 
// so z.B. über das aktuelle <tr> Projekt (<o GeoDocument>) initialisiert werden:
// @ex Initialisierung eines datenobjekten vom Typ GeoObject |
//	Dim Doc As GeoDocument
//	Dim Obj As GeoObject
//
//		Set Doc = GetActiveDocument()
//		Set Obj = Doc.GetObject("Objektname des Objektes")
//
// @xref <l Objekte in BasicScript®>

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECTSINBS
// @topic Zugriff auf Eigenschaften eines Datenobjektes | 
// Sobald eine Objektvariable deklariert und initialisiert ist, können die Eigenschaften 
// (Properties) des zugehörigen Datenobjektes abgefragt und modifiziert werden. 
// Properties werden syntaktisch über den BasicScript® Operator '.' (Punkt) angesprochen. 
// Vor dem Punkt steht dabei das Bezugs- Datenobjekt, nach dem Punkt die angesprochene Eigenschaft:
// @ex Beispiele des Zugriffs auf eine Property |
//		Doc.Name = "NeuerName"	'Modifikation des Projektnamens
//		i% = Doc.GeoObjectCount	'Abfrage der Objektanzahl
//
// @normal
// Eigenschaften werden modifiziert, wenn sie links vom Zuweisungsoperator '=' stehen, 
// ihr Wert wird abgefragt, wenn sie rechts vom Zuweisungsoperator stehen.
//
// Eigenschaften können zusätzliche Parameter besitzen. Diese werden mit Klammern 
// umgeben nach dem Namen der Eigenschaft angegeben:
// @ex Beispiel einer Property mit zusätzlichen Parametern |
//		Object.Feature("Objektname") = "NeuerObjektname"
//
// @xref <l Objekte in BasicScript®>

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECTSINBS
// @topic Anwenden von Methoden auf ein Datenobjekt | 
// Ebenso wie die Eigenschaften (Properties) eines Datenobjektes, so werden auch 
// die Methoden, die zu einem Datenobjekt gehören über den BasicScript® 
// Operator '.' (Punkt) aufgerufen.
// <nl>Methoden, die keinen Wert liefern, verhalten sich in BasicScript® ebenso, 
// wie Unterprogramme (<blue Sub>). Die Argumente werden nicht mit Klammern umgeben.
// @ex Beispiel des Aufrufes einer Methode ohne Rückgabewert an einem Datenobjekt |
//		TRiAS.OpenDocument "c:\files\test.ris".
//
// @normal
// Methoden, die einen Rückgabewert liefern, verhalten sich in BasicScript® 
// wie Funktionen (<blue Function>). Die Argument müssen immer mit Klammern umgeben sein, 
// und der gelieferte Rückgabewert muß einer Variablen entsprechenden Typs zugewiesen werden.
// @ex Beispiel des Aufrufes einer Methode mit Rückgabewert an einem Datenobjekt |
//		NumDocs% = TRiAS.OpenDocument("c:\files\test.ris")
//
// @normal
// Sollen Methoden ohne Rückgabewert mit geklammerten Argumenten gerufen werden, so ist das 
// Schlüsselwort <blue Call> voranzustellen:
// @ex Beispiel des Aufrufes einer Methode mit 'Call' |
//		Call TRiAS.OpenDocument ("c:\files\test.ris").
//
// @normal
// Parameter müssen in der Reihenfolge angegeben werden, wie sie in dieser Hilfedatei beschrieben sind. 
// Bei Verwendung der Parameternamen mit dem Operator ':=' (hier 'FileName' und 'Mode') kann allerdings eine 
// beliebige Reihenfolge gegeben sein:
// @ex Beispiel der Verwendung von Parameternamen |
//		TRiAS.OpenDocument _
//			FileName:="c:\files\test.ris", _
//			Mode:=OPENMODE_ReadOnly
//
// @normal
// Viele der <tr>- spezifischen Methoden können sowohl als Unterprogramme, als auch als 
// Funktionen eingesetzt werden, je nach dem, ob der Rückgabewert benötigt wird, oder nicht.
// Syntaktisch gibt es keinen Unterschied zwischen dem Auffruf einer Funktion und dem Zugriff 
// auf eine Eigenschaft (Property) mit Parametern eines Datenobjektes.
// @ex Vergleich des Auffrufes einer Funktion mit einer Property |
//		Variable = Object.Property(arg1, arg2)
//		Variable = Object.Method(arg1, arg2)
//
// @xref <l Objekte in BasicScript®>

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECTSINBS
// @topic Vergleichen von Datenobjekten | 
// Der Wert eines Datenobjektes an sich ist bis auf folgende Ausnahmen ohne Bedeutung 
// für die Scriptabarbeitung.
// <nl>Datenobjeke können miteinander verglichen werden, solange sie den gleichen Datentyp 
// besitzen, um festzustellen, ob sie ein und das selbe Objekt repräsentieren.
// <nl>Datenobjekte können mit Nothing verglichen werden, um festzustellen, ob sie 
// überhaupt ein Objekt repräsentieren (initialisiert sind).
// <nl>Datenobjekte werden mit Hilfe des BasicScript® Operators Is bzw. Is Not verglichen:
// @ex Beispiele für den Vergleich von Datenobjekten an sich |
//	' Die Objekte a und b sind identisch
//		If a Is b Then MsgBox
//	' a ist nicht initialisiert.
//		If a Is Nothing	Then MsgBox
//	' b ist initialisiert
//		If b Is Not Nothing Then MsgBox 
//
// @xref <l Objekte in BasicScript®>

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECTSINBS
// @topic Datenobjektsammlungen | 
// Eine Datenobjektsammlung (Collection) repräsentiert eine (beliebige) Menge 
// zusammengehörender Datenobjekte gleichen Objekttyps. Ein Element einer Collection 
// wird als Member (Mitglied) bezeichnet und wird über einen Index, der als Parameter 
// übergeben wird, referenziert.
// @ex Beispiele der Referenzierung von Elementen einer Datensammlungen |
//		Toolbar.Buttons(0)
//		Toolbar.Buttons("Dienstag")
//
// @normal
// Zu beachten ist jedoch, das selbst in den Fällen, wenn ein numerischer Index Verwendung 
// findet, nicht garantiert ist, ob das erste Element den Index '0' (Null) oder '1' (Eins) hat. 
// Ferner ist nicht garantiert, daß der Index fortlaufend und stetig ist. 
// Datenobjektsammlungen von <tr> Objekten werden von '1' bis 'Count' (Anzahl der Objekte, 
// die in der Sammlung enthalten sind) referenziert. Häufig wird jedoch ein kontextabhängiger 
// nichtnumerischer Index verwendet.
// <nl>Jedes Element einer Datenobjektsammlung ist selbst ein Datenobjekt, wie in den folgenden 
// Beispielen gezeigt ist:
// @ex Beispiele mit Datensammlungen |
//	Dim Objs As GeoObjects
//
//		Set Objs = Doc.GetObjects()
//		MsgBox Objs(1).Name			'Name des ersten Objektes der Sammlung
//
// @normal
// Eine Datenobjektsammlung selbst verfügt über Eigenschaften und Methoden, über die 
// Informationen über dieses Objekt abgefragt und modifiziert werden können.
// @ex Beispiele von Eigenschaften von Datenobjektsammlungen |
//	Dim Bttn As ToolbarButton
//
//		NumButtons% = MyApp.Toolbar.Buttons.Count
//		MyApp.Toolbar.Buttons.MoveNext
//		MyApp.Toolbar.Buttons.FindNext "Save"
//
//		For Each Bttn In MyApp.Toolbar.Buttons
//			Bttn.Caption = "Copy"
//		Next Bttn
//
// <nl>Es existieren zwei Typen von Datenobjektsammlungen:
// 1. Datenobjektsammlungen, deren Elemente nicht außerhalb dieser existieren können und
// 2. Datenobjektsammlungen, deren Elemente auch außerhalb von derartigen Collections existieren
// können.
// <nl>Nähere Informationen finden Sie dazu im Abschnitt <l Typen von Datenobjektsammlungen>.
// @xref <l Objekte in BasicScript®>, <l Typen von Datenobjektsammlungen>


///////////////////////////////////////////////////////////////////////////////
// @doc OBJECTSINBS
// @topic Vordefinierte Objekte | 
// In BasicScript sind einige Objekte vordefiniert, d.h. diese Datenobjekte müssen 
// nicht deklariert bzw. initialisiert werden, bevor sie benutzt werden können. Diese 
// Datenobjekte beziehen sich im allgemeinen auf Sachverhalte, die außerhalb des aktuellen 
// Scriptes liegen bzw. Vorraussetzung für die Abarbeitung des Scriptes sind.
// @ex Beispiele vordefinierter Datenobjekte |
//		<b Clipboard>: repräsentiert die Windows-Zwischenablage
//		<b System>: repräsentiert das unterliegende Betriebssystem (z.B. Windows)
//		<b Desktop>: 
//		<b Net>: repräsentiert die aktuellen Netzwerkeigenschaften des Computers
//		<b Basic>: repräsentiert BasicScript® selbst
//		<b Screen>: repräsentiert den aktuellen Bildschirmtreiber (Bildauflösung etc.)
//		<b TRiAS>: repräsentiert das Programm <tr>.

///////////////////////////////////////////////////////////////////////////////
// @doc OBJECTSINBS
// @topic Typen von Datenobjektsammlungen |
// Je nach Kontext, in dem eine Objektmenge erzeugt wurde, können die enthaltenen Datenobjekte
// unabhängig von der Sammlung existieren oder nicht. 
// 
// Die Menge aller Objekte (<o GeoObjects>) eines Projektes z.B., welche durch die Methode 
// <om DDocument.GetObjects> geliefert wurde, enthält so grundsätzlich sämtliche im Projekt 
// enthaltenen Objekte (<o GeoObject>). Das Entfernen eines <o GeoObject> aus dieser Sammlung 
// (durch <om DTRiASCollection.Remove>) bewirkt demnach das physische Löschen des referenzierten 
// Objektes aus der entsprechenden Datenquelle. Ein Hinzufügen eines neuen Objektes zu dieser 
// Sammlung (durch <om DTRiASCollection.Add>) erzeugt also ein neues Objekt in der entsprechenden 
// Datenquelle.
// 
// Eine Menge von Objekten jedoch (<o GeoObjects>), die durch die Funktion <om DDocument.CreateGeoObjectsCollection>
// erzeugt wurde, belegt die Methoden <om DTRiASCollection.Remove> bzw. <om DTRiASCollection.Add> mit
// <b keinem> weiteren Kontext. D.h. die Verwendung dieser Methoden entfernt lediglich das betreffende
// <o GeoObject> aus der Sammlung bzw. fügt ein neues/existierendes <o GeoObject> hinzu.
// @xref <o GeoObjects>, <o GeoObject>
// @xref <om DTRiASCollection.Remove>, <om DTRiASCollection.Add>, <om DDocument.CreateGeoObjectsCollection>
