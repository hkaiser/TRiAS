VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Koppelmodul"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

'Implements Darstellung
'Implements kopplung
'Implements Geometrie

Private KreisGen As New Kreisgenerator  ' macht was der Name schon sagt (allerdings nur die Geometrien)
Private idmapper As New KanalID2TRiaSID
Private WithEvents msgsink As MessageSink
Attribute msgsink.VB_VarHelpID = -1

Private cookie As Long
' Private idmapper As New KanalID2TRiaSID
Private bHandling As Boolean
Private m_SelObjID As String
Private m_SelKlasse As String
Private font As String


Public Event OnQueryShow(ObjID As String, klasse As String, ByRef retval As Boolean)   ' retval
Public Event OnShow(ObjID As String, klasse As String)
Public Event OnReShow(ObjID As String, klasse As String)

Public Event OnQueryChange(ObjID As String, klasse As String, ByRef retval As Boolean) ' retval
Public Event OnChanged(ObjID As String, klasse As String, x As Variant, y As Variant, z As Variant) ' Koordinaten

Public Event OnQueryDelete(ObjID As String, klasse As String, ByRef retval As Boolean) 'retval
Public Event OnDeleted(ObjID As String, klasse As String)

Public Event OnQueryCreate(klasse As String, x As Variant, y As Variant, z As Variant, ByRef retval As Boolean) ' Koordinaten , retval

' for future releases
' Public Event ErzeugeObjekt(Klasse As String, ByRef bWillHandle)
'Public Event OnAendereObjekt(Aktion As KANAL_ObjGeometrieEvent, ObjID As String, Klasse As String, para1 As Variant, para2 As Variant, para3 As Variant, ByRef retval As Variant)
'Public Event OnLoescheObjekt(ObjID As String, Klasse As String)
'Public Event OnZeigeObjekt(ObjID As String, Klasse As String)

Private Sub Class_Initialize()
    cookie = 0

    m_SelObjID = vbNullString
    m_SelKlasse = vbNullString
    font = "Arial"
    
    bHandling = False
End Sub

Private Sub Class_Terminate()
    Kopplung_BeendeKopplung
   Set msgsink = Nothing
End Sub

' Darstellung
Private Function Darstellung_Auswaehlen(ObjIDs() As String, Klassen() As String) As Long
    Dim action As New ObjectActionSelect
'    action.Color = 0                            ' Schwarz
    Darstellung_Auswaehlen = DoActionOnObjects(ObjIDs, Klassen, action)
End Function

Private Function Darstellung_FarbeSetzen(ObjIDs() As String, Klassen() As String, RGB As Long) As Long
    Dim action As New ObjectActionSetColor
    action.Color = RGB
    Darstellung_FarbeSetzen = DoActionOnObjects(ObjIDs, Klassen, action)
End Function

'Private Function Darstellung_Hervorheben(ObjIDs() As String, Klassen() As String) As Long
'    Dim action As New ObjectActionSelect
'    action.Color = 0
'    Darstellung_Auswaehlen = DoActionOnObjects(ObjIDs, Klassen, action)
'End Function

Private Function Darstellung_Zoomen(ObjIDs() As String, Klassen() As String) As Long
    Dim action As New ObjectActionZoom
    Darstellung_Zoomen = DoActionOnObjects(ObjIDs, Klassen, action)
End Function


' Geometrie
Private Function Geometrie_ErzeugeKreis(x As Double, y As Double, durchmesser As Double, ObjID As String, klasse As String) As Long
    On Error GoTo ende

    Geometrie_ErzeugeKreis = 1
    Dim ax() As Double  ' Speicher für die eigentliche Geometrie
    Dim ay() As Double
    
    KreisGen.GenerateKreis x, y, durchmesser, ax, ay
    
    ' TRiASId generieren
    Dim TRiASID As String
    TRiASID = idmapper.GetTRiASIDfromKanalID(ObjID, klasse)
    
    ' Objekt erzeugen
    Dim obj As DGeoObject
    Set obj = CreateObject(TRiASID, klasse, GetDataSource())
    If (obj Is Nothing) Then
        Exit Function
    End If
    
    ' Geometrie schreiben
    If (PutGeometry(obj, OBJECTTYPE_Line, ax, ay)) Then
        ' ready
        Geometrie_ErzeugeKreis = 0
    End If
ende:
    Err.Clear
End Function

Private Function Geometrie_ErzeugeLinie(x() As Double, y() As Double, ObjID As String, klasse As String) As Long
    On Error GoTo ende
    
    ' kein Erfolg
    Geometrie_ErzeugeLinie = 1
    
    ' TRiASId generieren
    Dim TRiASID As String
    TRiASID = idmapper.GetTRiASIDfromKanalID(ObjID, klasse)
    
    ' Objekt erzeugen
    Dim obj As DGeoObject
    Set obj = CreateObject(TRiASID, klasse, GetDataSource())
    If (obj Is Nothing) Then
        Exit Function
    End If
    
    ' Geometrie schreiben
    If (PutGeometry(obj, OBJECTTYPE_Line, x, y)) Then
        ' ready
        Geometrie_ErzeugeLinie = 0
    End If
    
ende:
    Err.Clear
End Function


Private Function Geometrie_ErzeugeSymbol(x As Double, y As Double, Symbol As String, size As Double, rotation As Double, ObjID As String, klasse As String) As Long
    On Error GoTo ende
    ' kein Erfolg
    Geometrie_ErzeugeSymbol = 1

    ' TRiASId generieren
    Dim TRiASID As String
    TRiASID = idmapper.GetTRiASIDfromKanalID(ObjID, klasse)

    ' Objekt erzeugen
    Dim obj As DGeoObject
    Set obj = CreateObject(TRiASID, klasse, GetDataSource())
    If (obj Is Nothing) Then
        Exit Function
    End If

    ' Geometriearrays generieren
    Dim ax() As Double
    ReDim ax(0)
    ax(0) = x

    Dim ay() As Double
    ReDim ay(0)
    ay(0) = y

    ' Geometrie schreiben
    If False = PutGeometry(obj, OBJECTTYPE_Text, ax, ay) Then
        ' ready
        Exit Function
    End If

    ' Jetzt noch Visinfo schreiben
    Geometrie_ErzeugeSymbol = SetTextVis(obj, KANAL_TextBezugMittig, rotation, Symbol, font)
'    Geometrie_ErzeugeSymbol = Geometrie_ErzeugeSymbol Or SetVisFont(Obj, font)
ende:
    Err.Clear
End Function

Private Function Geometrie_ErzeugeText(x As Double, y As Double, Bezugspunkt As KanalSchnittstellen.KANAL_TextBezugspunkt, Drehwinkel As Double, VisText As String, ObjID As String, klasse As String) As Long
    On Error GoTo ende
    ' kein Erfolg
    Geometrie_ErzeugeText = 1

    ' TRiASId generieren
    Dim TRiASID As String
    TRiASID = idmapper.GetTRiASIDfromKanalID(ObjID, klasse)

    ' Objekt erzeugen
    Dim obj As DGeoObject
    Set obj = CreateObject(TRiASID, klasse, GetDataSource())
    If (obj Is Nothing) Then
        Exit Function
    End If

    ' Geometriearrays generieren
    Dim ax() As Double
    ReDim ax(0)
    ax(0) = x

    Dim ay() As Double
    ReDim ay(0)
    ay(0) = y

    ' Geometrie schreiben
    If False = PutGeometry(obj, OBJECTTYPE_Text, ax, ay) Then
        ' ready
        Exit Function
    End If

    ' Jetzt noch Visinfo schreiben
    Geometrie_ErzeugeText = SetTextVis(obj, Bezugspunkt, Drehwinkel, VisText)
ende:
    Err.Clear
End Function

Private Function Geometrie_Loesche(ObjID As String, klasse As String) As Long
    Geometrie_Loesche = 1
    Dim obj As DGeoObject
    Set obj = GetObjectFromKanalID(ObjID, klasse)
    
    If obj Is Nothing Then
        Exit Function
    End If
    
    If RemoveObject(obj) Then
        Geometrie_Loesche = 0
    End If
End Function

' Kopplung
Private Property Let Kopplung_GISDatabase(ByVal RHS As String)

End Property

Private Property Get Kopplung_GISDatabase() As String

End Property

Private Function Kopplung_BeendeKopplung() As Long
    Kopplung_BeendeKopplung = 1

    Dim app As DApplication
    Set app = GetTRiASApp
    If app Is Nothing Then
        Exit Function
    End If

    app.Unadvise cookie
    Set msgsink = Nothing
    
    If SchliesseTRiAS() Then
        Kopplung_BeendeKopplung = 0 ' juchhu
    End If
    
End Function

Private Function Kopplung_StarteKopplung() As Long
    Kopplung_StarteKopplung = 1
    If Not StarteTRiAS Then
        Exit Function
    End If
    
    Dim app As DApplication
    Set app = GetTRiASApp
    If app Is Nothing Then
        Exit Function
    End If
    
    
    Set msgsink = New MessageSink
    cookie = app.Advise(msgsink)
    
    ' juchhu, wir haben's gestartet
    Kopplung_StarteKopplung = 0
End Function

Private Function GetObjectFromKanalID(ObjID As String, klasse As String) As DGeoObject
    Set GetObjectFromKanalID = Nothing

    ' TRiASId generieren
    Dim TRiASID As String
    Dim idmapper As New KanalID2TRiaSID
    TRiASID = idmapper.GetTRiASIDfromKanalID(ObjID, klasse)
    
    ' Objekt holen
    Set GetObjectFromKanalID = GetObject(TRiASID, klasse, GetDataSource())
End Function

Private Function DoActionOnObjects(ByRef ObjIDs() As String, ByRef Klassen() As String, action As ObjectAction) As Long
    DoActionOnObjects = 1
    
    ' something is wrong ...
    If (TesteDimensions(ObjIDs, Klassen) = False) Then
        Exit Function
    End If
        
    Dim lowerbound As Long
    lowerbound = LBound(ObjIDs) ' es ist jetzt egal wessen dimension wir nehmen
    
    Dim upperbound As Long
    upperbound = UBound(ObjIDs)
    
    Dim i As Long ' Laufvar
    Dim obj As DGeoObject
    ' bis jetzt kein Fehler
    DoActionOnObjects = action.BeginAction
    
    If DoActionOnObjects <> 0 Then
        Exit Function
    End If
    
    For i = lowerbound To upperbound
        Set obj = GetObjectFromKanalID(ObjIDs(i), Klassen(i))
        DoActionOnObjects = action.DoAction(obj) Or DoActionOnObjects   ' Fehler wenn ein Fehler
    Next
    
    DoActionOnObjects = action.EndAction Or DoActionOnObjects
End Function

' Funktionen aus der Überwachung von TRiAS
Private Sub msgsink_AendereObjektInt(x() As Double, y() As Double, ObjID As String, klasse As String)
'   RaiseEvent AendereObjekt(x, y, ObjID, Klasse)
End Sub

Private Sub msgsink_LoescheObjektInt(ObjID As String, klasse As String)
'    RaiseEvent LoescheObjekt(ObjID, Klasse)
End Sub

Private Sub msgsink_ZeigeObjektInt(ObjID As String, klasse As String)
'    RaiseEvent ZeigeObjekt(ObjID, Klasse)
End Sub


' noch einmal die Funktionen für EIN Interface
Public Function Zoomen(ObjIDs As Variant, Klassen As Variant) As Long
    Dim tObjIDs() As String
    tObjIDs = ObjIDs
    Dim tKlassen() As String
    tKlassen = Klassen

    Zoomen = Darstellung_Zoomen(tObjIDs, tKlassen)
End Function

' Einfärben mit einem RGB-wert
Public Function FarbeSetzen(ObjIDs As Variant, Klassen As Variant, RGB As Long) As Long
    Dim tObjIDs() As String
    tObjIDs = ObjIDs
    Dim tKlassen() As String
    tKlassen = Klassen

    FarbeSetzen = Darstellung_FarbeSetzen(tObjIDs, tKlassen, RGB)
End Function

' Auswählen einer Menge von Objekten
Public Function Auswaehlen(ObjIDs As Variant, Klassen As Variant) As Long
    Dim tObjIDs() As String
    tObjIDs = ObjIDs
    Dim tKlassen() As String
    tKlassen = Klassen

    Auswaehlen = Darstellung_Auswaehlen(tObjIDs, tKlassen)
End Function

Public Function ErzeugeLinie(x As Variant, y As Variant, z As Variant, ObjID As String, klasse As String) As Long
    Dim tx() As Double
    tx = x
    Dim ty() As Double
    ty = y
    ErzeugeLinie = Geometrie_ErzeugeLinie(tx, ty, ObjID, klasse)
End Function

' Erzeugen eines Kreises mit dem angegebenen Mittelpunkt und Durchmesser
' Der externe Schlüssel des Objektes ist ObjID, es gehört (inbtern und extern) zur Klasse Klasse
' Der Rückkehrwert 0 zeigt an, daß die Aktion ohne Fehler ausgeführt werden konnte
Public Function ErzeugeKreis(x As Double, y As Double, z As Double, durchmesser As Double, ObjID As String, klasse As String) As Long
    ErzeugeKreis = Geometrie_ErzeugeKreis(x, y, durchmesser, ObjID, klasse)
End Function

' Erzeugen eines Symboles des angegebenen Types mit dem angegebenen Mittelpunkt und Durchmesser
' Der externe Schlüssel des Objektes ist ObjID, es gehört (inbtern und extern) zur Klasse Klasse
' Der Rückkehrwert 0 zeigt an, daß die Aktion ohne Fehler ausgeführt werden konnte
Public Function ErzeugeSymbol(x As Double, y As Double, z As Double, Symbol As String, size As Double, rotation As Double, ObjID As String, klasse As String) As Long
    ErzeugeSymbol = Geometrie_ErzeugeSymbol(x, y, Symbol, size, rotation, ObjID, klasse)
End Function

' Erzeugen eines Textes an dem angegebenen Punkt mit der in Bezugspunkt vorgegebenen Ausrichtung und dem vorgegebenen Drehwinkel
' Der externe Schlüssel des Objektes ist ObjID, es gehört (inbtern und extern) zur Klasse Klasse
' Der Rückkehrwert 0 zeigt an, daß die Aktion ohne Fehler ausgeführt werden konnte
Public Function ErzeugeText(x As Double, y As Double, z As Double, Bezugspunkt As Long, Drehwinkel As Double, VisText As String, ObjID As String, klasse As String) As Long
    ErzeugeText = Geometrie_ErzeugeText(x, y, Bezugspunkt, Drehwinkel, VisText, ObjID, klasse)
End Function

' Löschen des angegebenen Objektes
Public Function Loesche(ObjID As String, klasse As String) As Long
    Loesche = Geometrie_Loesche(ObjID, klasse)
End Function

' Starten der Kopplung
Public Function StarteKopplung() As Long
    StarteKopplung = Kopplung_StarteKopplung
End Function

Public Function BeendeKopplung() As Long
    BeendeKopplung = Kopplung_BeendeKopplung
End Function

Public Sub StartGeometryTransaction(redraweach As Long)
    Dim doc As GeoDocument
    Set doc = GetTRiASDocument
    doc.PreventRepaint = True
End Sub

Public Function EndGeometryTransaction()
    Dim doc As GeoDocument
    Set doc = GetTRiASDocument
    doc.PreventRepaint = False
    doc.RePaint
End Function

Public Sub ZeigeTRiAS(show As Boolean)
    Dim app As Application
    Set app = GetTRiASApp
    app.Visible = show
End Sub

Public Function Zoom(xmin As Double, ymin As Double, xmax As Double, ymax As Double) As Long
    Zoom = 1
    TRiASZoom xmin, ymin, xmax, ymax
    Zoom = 1
End Function

' eine Beispiel Kopplungseigenschaft
'Public Property Get GISDatabase() As String
'    GISDatabase = Kopplung_GISDatabase
'End Property
'
'Public Property Let GISDatabase(ByVal vNewValue As String)
'    Kopplung_GISDatabase = GISDatabase
'End Property

'Public Event OnToShow(ObjID As String, klasse As String, ByRef retval As Boolean)   ' retval
'Public Event OnShow(ObjID As String, klasse As String)
'Public Event OnReShow(ObjID As String, klasse As String)
'Public Event OnToChange(ObjID As String, klasse As String, ByRef retval As Boolean) ' retval
'Public Event OnChanging(ObjID As String, klasse As String, x As Variant, y As Variant, z As Variant) ' Koordinaten
'Public Event OnToDelete(ObjID As String, klasse As String, ByRef retval As Boolean) 'retval
'Public Event OnDelete(ObjID As String, klasse As String)
'Public Event OnCreate(klasse As String, x As Variant, y As Variant, z As Variant, ByRef retval As Boolean) ' Koordinaten , retval

'Public Event OnAendereObjekt(Aktion As KANAL_ObjGeometrieEvent, ObjID As String, klasse As String, para1 As Variant, para2 As Variant, para3 As Variant, ByRef retval As Variant)
'Public Event OnLoescheObjektInt(ObjID As String, klasse As String)
'Public Event OnZeigeObjektInt(ObjID As String, klasse As String)


'Private Function GeoObjectEvent(ByVal hPrj As Long, ByVal oe As Long, ByVal lOnr As Long) As Long
'    GeoObjectEvent = 0
'
'    ' keine rekursiven Aufrufe
'    If bHandling Then
'        Exit Function
'    End If
'    bHandling = True
'
'    On Error GoTo ende
'
'    Dim kanalklasse As String
'    kanalklasse = vbNullString
'
'    Dim kanalid As String
'    kanalid = vbNullString
'
'    Dim retval As Boolean
'    Dim dx() As Double
'    Dim dy() As Double
'    Dim dz() As Double
'    Dim x As Variant
'    Dim y As Variant
'    Dim z As Variant
'    Dim obj As DGeoObject
'    Dim nPoints As Long
'    Dim i As Long
'
'    Select Case oe
'        ' Auswählen
'      Case GEOOBJECTEVT_ObjectSelected  ' vielleicht vorher noch nachfragen
'
'            If GetObjekt(lOnr, kanalid, kanalklasse) Then
'                RaiseEvent OnShow(kanalid, kanalklasse)
'            End If
'            m_SelObjID = kanalid
'            m_SelKlasse = kanalklasse
'
'        ' Undo Auswahl
'      Case GEOOBJECTEVT_ObjectUnSelected
'            If GetObjekt(lOnr, kanalid, kanalklasse) Then
'                RaiseEvent OnReShow(kanalid, kanalklasse)
'            End If
'            m_SelObjID = vbNullString
'            m_SelKlasse = vbNullString
'
'        ' will ändern
'      Case GEOOBJECTEVT_ChangingGeometry
'            If GetObjekt(lOnr, kanalid, kanalklasse) Then
'                retval = True   ' Default : ich darf ändern
'                RaiseEvent OnToChange(kanalid, kanalklasse, retval)
'
'                If retval = False Then  ' doch nichts ändern
'                    GeoObjectEvent = 1
'                End If
'            End If
'
'        ' ändere
'      Case GEOOBJECTEVT_GeometryChanged
'             If GetObjekt(lOnr, kanalid, kanalklasse) Then
'                Set obj = GetGeoObject(lOnr)
'                If obj Is Nothing Then
'                    Exit Function
'                End If
'
'                obj.GetGeometry nPoints
'
'                nPoints = nPoints - 1
'                ReDim dx(nPoints)
'                ReDim dy(nPoints)
'                ReDim dz(nPoints)
'
'                ' z gibts nicht, also generieren
'                For i = 0 To nPoints
'                    dx(i) = 0
'                Next
'                obj.GetGeometry nPoints, dx, dy
'
'                x = dx
'                y = dy
'                z = dz
'
'                RaiseEvent OnChanging(kanalid, kanalklasse, x, y, z)    ' Koordinaten
''                RaiseEvent OnDelete(kanalid, kanalklasse, retval, x, y, z)
'            End If
'
'        ' will löschen
'      Case GEOOBJECTEVT_ObjectToDelete
'             If GetObjekt(lOnr, kanalid, kanalklasse) Then
'                retval = True   ' Default : ich darf löschen
'                RaiseEvent OnToDelete(kanalid, kanalklasse, retval)
'
'                If retval = False Then  ' es wurde irgendwas geändert
'                    GeoObjectEvent = 1
'                End If
'            End If
'
'      ' lösche
'      Case GEOOBJECTEVT_DeletingObject
'            If GetObjekt(lOnr, kanalid, kanalklasse) Then
'                RaiseEvent OnDelete(kanalid, kanalklasse)
'            End If
'
'      ' neuanlegen
'      Case GEOOBJECTEVT_ObjectCreated
'                Set obj = GetGeoObject(lOnr)
'                If obj Is Nothing Then
'                    Exit Function
'                End If
'
'                obj.GetGeometry nPoints
'
'                nPoints = nPoints - 1
'                ReDim dx(nPoints)
'                ReDim dy(nPoints)
'                ReDim dz(nPoints)
'
'                ' z gibts nicht, also generieren
'                For i = 0 To nPoints
'                    dx(i) = 0
'                Next
'                obj.GetGeometry nPoints, dx, dy
'
'                ' retyping
'                x = dx
'                y = dy
'                z = dz
'
'                kanalklasse = obj.ObjClass.Name
'
'                retval = False   ' Default : Objekt wird nicht von Erweiterung verwaltet
'                RaiseEvent OnCreate(kanalklasse, x, y, z, retval)    ' Koordinaten
'                If True = retval Then   ' das Objekt wird von irgendjemandem verwaltet also wieder löschen
'                    RemoveObject obj
'                End If
'
'      Case GEOOBJECTEVT_ObjectActivated
'      Case GEOOBJECTEVT_ObjectDeActivated
'    End Select
'
'    GeoObjectEvent = 0
'ende:
'    bHandling = False
'
'End Function

Private Function GetObjekt(lOnr As Long, kanalid As String, kanalklasse As String) As Boolean
    On Error GoTo ende
    GetObjekt = False

    ' das Objekt extrahieren
    Dim obj As DGeoObject
    Set obj = GetGeoObject(lOnr)
    
    If obj Is Nothing Then
        Exit Function
    End If
    
    ' den KanlId bestimmen
    idmapper.GetKANALIDFromTRiASID obj.Name, kanalid, kanalklasse
    If kanalid = vbNullString Then
        Exit Function
    End If
    
    GetObjekt = True
ende:
End Function

Private Function GetGeoObject(lOnr As Long) As DGeoObject
    Set GetGeoObject = Nothing
    
    ' aktuelles Document holen
    Dim doc As GeoDocument
    Set doc = GetTRiASDocument
    
    If doc Is Nothing Then
        Exit Function
    End If
        
    ' das Objekt extrahieren
    Set GetGeoObject = doc.GetObject(lOnr)
End Function

Public Sub GetSelektedObjekt(ByRef ObjID As String, ByRef klasse As String)
    ObjID = m_SelObjID
    klasse = m_SelKlasse
End Sub

Private Function Darstellung_SetKanalText(ObjIDs() As String, Klassen() As String, text As String) As Long
    Dim action As New ObjectActionSetText
    action.m_Text = text
    Darstellung_SetKanalText = DoActionOnObjects(ObjIDs, Klassen, action)
End Function

Public Function SetKanalText(ObjIDs As Variant, klasses As Variant, text As String) As Long
    Dim tObjIDs() As String
    tObjIDs = ObjIDs
    Dim tKlassen() As String
    tKlassen = klasses

    SetKanalText = Darstellung_SetKanalText(tObjIDs, tKlassen, text)
End Function

Public Function SetzeSymbolFont(fontname As String)
    font = fontname
End Function

'Public Event OnQueryShow(ObjID As String, klasse As String, ByRef retval As Boolean)   ' retval
Private Sub msgsink_OnQueryShow(ObjID As String, klasse As String, retval As Boolean)
    RaiseEvent OnQueryShow(ObjID, klasse, retval)
End Sub


'Public Event OnShow(ObjID As String, klasse As String)
Private Sub msgsink_OnShow(ObjID As String, klasse As String)
    m_SelObjID = ObjID
    m_SelKlasse = klasse
    RaiseEvent OnShow(ObjID, klasse)
End Sub

'Public Event OnReShow(ObjID As String, klasse As String)
Private Sub msgsink_OnReShow(ObjID As String, klasse As String)
    m_SelObjID = vbNullString
    m_SelKlasse = vbNullString
    RaiseEvent OnReShow(ObjID, klasse)
End Sub

'Public Event OnQueryChange(ObjID As String, klasse As String, ByRef retval As Boolean) ' retval
Private Sub msgsink_OnQueryChange(ObjID As String, klasse As String, retval As Boolean)
    RaiseEvent OnQueryChange(ObjID, klasse, retval)
End Sub

'Public Event OnChanged(ObjID As String, klasse As String, x As Variant, y As Variant, z As Variant) ' Koordinaten
Private Sub msgsink_OnChanged(ObjID As String, klasse As String, x As Variant, y As Variant, z As Variant)
    RaiseEvent OnChanged(ObjID, klasse, x, y, z)
End Sub


'Public Event OnQueryDelete(ObjID As String, klasse As String, ByRef retval As Boolean) 'retval
Private Sub msgsink_OnQueryDelete(ObjID As String, klasse As String, retval As Boolean)
    RaiseEvent OnQueryDelete(ObjID, klasse, retval)
End Sub


'Public Event OnDeleted(ObjID As String, klasse As String)
Private Sub msgsink_OnDeleted(ObjID As String, klasse As String)
    RaiseEvent OnDeleted(ObjID, klasse)
End Sub

'Public Event OnQueryCreate(klasse As String, x As Variant, y As Variant, z As Variant, ByRef retval As Boolean) ' Koordinaten , retval
Private Sub msgsink_OnQueryCreate(klasse As String, x As Variant, y As Variant, z As Variant, retval As Boolean)
    RaiseEvent OnQueryCreate(klasse, x, y, z, retval)
End Sub






