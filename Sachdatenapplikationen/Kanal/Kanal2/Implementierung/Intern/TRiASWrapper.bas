Attribute VB_Name = "TRiASWrapper"
Option Explicit

' Zugriffscode auf TRiAS
' wird evtl. später durch die Routinen von Manfred Wendt ersetzt
Private triasapp As TRiAS.Application
Private triasdoc As TRiAS.GeoDocument

' Funktion : Speichern einer Geometrie am vorgegebenem GeoObjekt
Function PutGeometry(obj As DGeoObject, OBJTYPE As OBJECTTYPE, x() As Double, y() As Double) As Boolean
#If DEBUGVERSION Then
  If (UBound(x, 1) - LBound(x, 1) <> UBound(y, 1) - LBound(y, 1)) Then
    ErzeugeFehler ErrorIDInvalidArrayDimension
  End If
#End If

  ' die Arraygröße bestimmen
  Dim size As Long
  size = UBound(x, 1) - LBound(x, 1)
  
  ' eine einfache Kontur erzeugen
  Dim Conture() As Long
  ReDim Conture(1)
  Conture(0) = size
  
  PutGeometry = obj.PutGeometry(OBJTYPE, x, y, Conture, MODGEOMETRY_ModObject + MODGEOMETRY_NoMemoryObject)
End Function

' Funktion : löschen des angegebenem GeoObjektes aus der GeoDatenbank
Function RemoveObject(obj As DGeoObject) As Boolean
  Set obj = triasdoc.GetObject(obj, GEOOBJECTMODE_Remove)
  RemoveObject = True
End Function

' bla
Function GetClass(klasse As String, connection As String) As DGeoClass
    Err.Clear
    On Error Resume Next
    Set GetClass = triasdoc.GetClassEx(klasse, connection, GEOCLASSMODE_Get)
    Err.Clear
End Function

' Funktion : eine per Kurznamen angegebene GeoKlasse holen (oder erzeugen (future releases)
Function GetOrCreateClass(klasse As String, connection As String) As DGeoClass
  Err.Clear
  On Error Resume Next
  Set GetOrCreateClass = GetClass(klasse, connection)
  Err.Clear
  
  If (GetOrCreateClass Is Nothing) Then
    Set GetOrCreateClass = triasdoc.GetClassEx(klasse, connection, GEOCLASSMODE_Add)
    Err.Clear
  End If
  
End Function

Function GetObject(ObjID As String, klasse As String, connection As String) As DGeoObject
    ' Wir haben kein Ergebnis
    Set GetObject = Nothing
    
    ' Klasse bestimmen
    Dim Class As DGeoClass
    Set Class = GetClass(klasse, connection)
    If Class Is Nothing Then
        Exit Function
    End If
    
    ' Object bestimmen
    On Error Resume Next
    Set GetObject = Class.GetObject(ObjID, GEOOBJECTMODE_Get)
    Err.Clear
End Function

Function CreateObject(ObjID As String, klasse As String, connection As String) As DGeoObject
  Dim Class As DGeoClass
  Dim obj As DGeoObject
  
  ' Ergebnis initialisieren
  Set CreateObject = Nothing
  
  ' Testen ob das Objekt schon vorhanden ist
  If (Not GetObject(ObjID, klasse, connection) Is Nothing) Then
    Exit Function
  End If
  
  ' Klasse bestimmen
  On Error Resume Next
  Set Class = GetOrCreateClass(klasse, connection)
  
  ' Tja sorry Jungs, ein Satz mit x
  If (Class Is Nothing) Then
    ErzeugeFehler ErrorIDCouldntCreateClass, klasse
  End If
  
  Set obj = triasdoc.AddObject(ObjID, Class)
  ' Tja sorry Jungs, ein Satz mit x
  If (obj Is Nothing) Then
    ErzeugeFehler ErrorIDCouldntCreateObj, klasse
  End If
  
  ' wieder mal eine Testimpl
  Set CreateObject = obj
End Function

Public Function StarteTRiAS() As Boolean
    StarteTRiAS = False
    
    If (triasapp Is Nothing) Then
        Set triasapp = New TRiAS.Application
    End If
    
    ' Schluß mit lustig
    If (triasapp Is Nothing) Then
        Exit Function
    End If
    
    ' Anzeigen den Scheiß
'    triasapp.Visible = True    dafür gibts jetzt 'ne externe Funktion
    
    If (triasdoc Is Nothing) Then
        Set triasdoc = triasapp.OpenDocument(GetTRiASDoc)
    End If
    
    ' Schluß mit lustig
    If (triasdoc Is Nothing) Then
        Exit Function
    End If
    
'    triasdoc.PreventRepaint = True
    
    StarteTRiAS = True
End Function

Public Function SchliesseTRiAS() As Boolean
'    triasdoc.PreventRepaint = False
    SchliesseTRiAS = False
    
    If (Not triasapp Is Nothing) Then
        triasapp.Quit True
    End If
    
    Set triasapp = Nothing
    SchliesseTRiAS = True
End Function

Public Function GetTRiASDocument() As TRiAS.GeoDocument
    Set GetTRiASDocument = triasdoc
End Function

Public Function GetTRiASApp() As TRiAS.Application
    Set GetTRiASApp = triasapp
End Function

Public Function SchreibeVisInfo(obj As DGeoObject, vi As DVisInfo)
    SchreibeVisInfo = 1
    
    Dim views As DViews
    Set views = GetTRiASDocument.GetViews
    
    Dim view As DView
    For Each view In views
        obj.SetVisInfo vi, view  ' GetViewName
    Next
    
    SchreibeVisInfo = 0
End Function

Public Function SetTextVis(obj As DGeoObject, Bezugspunkt As KanalSchnittstellen.KANAL_TextBezugspunkt, Drehwinkel As Double, VisText As String, Optional fontname As String = vbNullString) As Long
    On Error Resume Next
    SetTextVis = 1

    If obj Is Nothing Then
        Exit Function
    End If

    ' ist das denn ein Text
    Dim vi As TextVisInfo
    Set vi = obj.GetVisInfo
    Err.Clear
    
    If vi Is Nothing Then
        Exit Function
    End If
    
    ' alle notwendigen Werte eintragen
    vi.ALIGNSTYLE = Bezugspunkt
    vi.Rotate = Drehwinkel * 10
    obj.PutText VisText
'    vi.VisString = VisText
    ' den Font rausschreiben
    If (vbNullString <> fontname) Then
        vi.Name = fontname
    End If
    
    SetTextVis = SchreibeVisInfo(obj, vi)
End Function

Public Function SetVisFont(obj As DGeoObject, font As String) As Long
    On Error Resume Next
    SetVisFont = 1

'    If obj Is Nothing Then
'        Exit Function
'    End If
'
'    ' ist das denn ein Text
'    Dim vi As TextVisInfo
'    Set vi = obj.GetVisInfo
'    Err.Clear
'
'    If vi Is Nothing Then
'        Exit Function
'    End If
'
'    ' alle notwendigen Werte eintragen
'    Dim visstr As String
'    visstr = vi.VisString
'
'    Dim posdelimiter1 As Long
'    posdelimiter1 = InStr(visstr, """") + 1 ' die Startposition des Klassennamens
'    Dim posdelimiter2 As Long
'    posdelimiter2 = InStr(posdelimiter1, visstr, """")
'    Dim rechteseite As Long
'    rechteseite = Len(visstr) - posdelimiter2 + 1
'
'    vi.VisString = Left(visstr, posdelimiter1 - 1) & font & Right(visstr, rechteseite)
'
'    SetVisFont = SchreibeVisInfo(obj, vi)
End Function

Public Sub TRiASZoom(xmin As Double, ymin As Double, xmax As Double, ymax As Double)
    ' jetzt auf das bestimmte Rechteck zoomen
    Dim doc As TRiAS.GeoDocument
    Set doc = GetTRiASDocument
    
    Dim view As DView
    Set view = doc.GetView(doc.ActiveViewName)
    
    Dim txmin As Double
    Dim txmax As Double
    Dim tymin As Double
    Dim tymax As Double
'    Dim t1, t2, t3, t4, t5, t6, txmax2, tymax2  ' Variablen für den Test
    
'    view.GetActRect txmin, tymin, txmax, tymax

    Dim xmax2
    xmax2 = xmax
    Dim ymax2
    ymax2 = ymax
    
    
'    view.SetConstraintRect xmin, ymin, xmax2, ymax2
    On Error Resume Next
'    view.SetActRect txmin, tymin ' , xmax2, ymax2
     
    view.SetActRect xmin, ymin, xmax2, ymax2
    
'    Dim doc As GeoDocument
'    Set doc = GetTRiASDocument
    doc.PreventRepaint = False
    doc.RePaint
    Err.Clear
'    .SetViewRect xmin, ymin, xmax, ymax
End Sub


