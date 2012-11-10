VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "GeoCompWithoutUI"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

' Wir sind eine GeoKomponente
Implements TRiAS.IGeoComponent

Dim Callback As TRiAS.IGeoComponentCallback
Dim ObjsIn As TRiAS.DGeoObjects

' Callback zur gesamten Sequenz speichern (wird evtl. noch gebraucht)
' dies ist die erste Funktion die gerufen wird (Not RHS Is Nothing) und
' gleichzeitig auch die letzte (RHS Is Nothing)
Private Property Set IGeoComponent_Callback(ByVal RHS As TRiAS.IGeoComponentCallback)
  
  Set Callback = RHS
  If (RHS Is Nothing) Then
  ' hier kann aufgeräumt werden
  ' ...
  End If
  
End Property

' Da diese Geokomponente kein eigenes Nutzerinterface hat, muß die
' Eigenschaft PageCount = 0 sein. In diesem Fall werden auch die
' Eigenschaften PageProgId und ConnectUI nicht gerufen, müssen hier
' also auch nicht (sinnvoll) implementiert werden.
Private Property Get IGeoComponent_PageCount() As Long

  IGeoComponent_PageCount = 0
End Property

Private Property Get IGeoComponent_PageProgId(ByVal Index As Long) As String

  ' never called, da PageCount = 0
End Property

Private Property Set IGeoComponent_ConnectUI(ByVal Index As Long, ByVal RHS As Object)

  ' never called, da PageCount = 0
End Property

' PreConfigAction wird so ziemlich am Anfang gerufen und übergibt
' die TRiAS Applikation, das aktuelle TRiAS Dokument und die Datenmenge,
' die am Eingang der ersten Geokomponente dieser Sequenz übergeben werden
' soll
Private Sub IGeoComponent_PreConfigAction(ByVal App As TRiAS.DApplication, _
  ByVal Doc As TRiAS.DDocument, ByVal DataIn As TRiAS.ITRiASDataObject)

End Sub

' BeginAction wird einmal zu Beginn der eigentlichen Abarbeitung gerufen. Der
' übergebene ProgressIndicator kann während der Abarbeitung der Methode
' 'EndAction' dazu verwendet werden, eine Gedultsanzeige zu erzeugen
Private Sub IGeoComponent_BeginAction(ByVal Indicator As TRiAS.IProgressIndicator2)

End Sub

' DoAction wird gerufen, um die Datenmengen abzuliefern, die die vorhergehende
' Geokomponente abgegeben hat. Diese Methode wird genau sooft gerufen wie die
' vorhergehende Geokomponente Datenmengen erzeugt.
' Entsprechend der allgemeinen Konvention sollte diese Methode die Eingabemengen
' lediglich zwischenspeichern und die eigentliche Verarbeitung erst während der
' Abarbeitung der Methode 'EndAction' erledigen.
Private Sub IGeoComponent_DoAction(ByVal DataIn As TRiAS.ITRiASDataObject)

  If (ObjsIn Is Nothing) Then
  ' der erste Aufruf, also Objektmenge lediglich speichern
    Set ObjsIn = DataIn.GetObjects
  Else
  ' alle weiteren Objektmengen hier einfach zu unserer Objektmenge
  ' hinzufügen
  Dim Objs As TRiAS.DGeoObjects
  
    Set Objs = DataIn.GetObjects
    Set ObjsIn = ObjsIn.Union(Objs)
  End If
  
End Sub

' EndAction wird gerufen, wenn die vorgehende Geokomponente keine Datenmengen
' mehr abzugeben hat und nachdem unsere Methode DoAction für die letzte dort
' abgegebene Datenmenge gerufen wurde. Die Methode EndAction wird solange
' gerufen werden, bis unsere Eigenschaft HasDataOut = True ist. Bei jedem dieser
' Aufrufe muß EndAction eine Datenmenge liefern.
' Eine Ausnahme bildet der erste Aufruf von EndAction. Wenn überhaupt keine
' Datenmenge geliefert werden soll, dann darf der Rückgabewert Nothing sein.
' Unbedingt ist zu unterscheiden zwischen 'keine Objektmenge abzugeben' und
' 'keine Datenmenge abzugeben'. Wenn diese Geokomponente keine Datenmenge
' abgeben soll (z.B. weil die Eingabedatenmenge lediglich in einem Recherchefenster
' angezeigt und keine nachfolgende Geokomponente erwartet wird), dann liefert
' diese Methode Nothing (beim ersten Aufruf).
' Wenn normalerweise jedoch Objekte abgegeben werden sollen, in einer konkreten
' Situation jedoch keine passenden Objekte vorhanden sind (z.B. keine
' entsprechenden Rechercheergebnisse), dann muß diese Methode eine Datenmenge
' zurückliefern, die eine leere Objektmenge enthält.
' Generell gilt, wenn eine Datenmenge geliefert wird, dann muß diese eine
' (notfalls leere) Objektmenge enthalten.
' Übrigens werden die Datenmengen, die hier geliefert werden an die Funktion
' DoAction der nachfolgenden Geokomponente übergeben.
Private Function IGeoComponent_EndAction() As TRiAS.ITRiASDataObject

  Set IGeoComponent_EndAction = Nothing
  On Error GoTo labelError
  
Dim DataOut As New TRiAS.TRiASDataObject

  DataOut.SetObjects ObjsIn
  Set ObjsIn = Nothing
  Set IGeoComponent_EndAction = DataOut
  Exit Function
  
labelError:
  Set ObjsIn = Nothing
  Exit Function

End Function

' HasDataOut wird unmittelbar nach jedem Aufruf von EndAction getestet. Wenn
' HasDataOut = True ist, dann wird davon ausgegangen, das weitere Objektmengen
' abgegeben werden sollen. Anderenfalls, wird EndAction nicht mehr gerufen.
Private Property Get IGeoComponent_HasDataOut() As Boolean

  IGeoComponent_HasDataOut = False  ' wir haben nur eine Objektmenge
End Property

Private Sub IGeoComponent_ReadProperties(ByVal PropBag As TRiAS.ITRiASPropertyBag)

End Sub

Private Sub IGeoComponent_WriteProperties(ByVal PropBag As TRiAS.ITRiASPropertyBag)

End Sub

Private Sub IGeoComponent_InitFromData(ByVal PropBag As TRiAS.ITRiASPropertyBag)

Dim TestItem1 As String
Dim TestItem3 As String

  TestItem1 = PropBag.ReadProperty("TestItem1")
  TestItem3 = PropBag.ReadProperty("TestItem3", "DefaultValue3")
  
  MsgBox "TestItem1: " + TestItem1 + Chr(10) + "TestItem3: " + TestItem3
  
End Sub




