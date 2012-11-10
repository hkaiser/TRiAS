VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "MessageSink"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Public Event OnQueryShow(ObjID As String, klasse As String, ByRef retval As Boolean)   ' retval
Public Event OnShow(ObjID As String, klasse As String)
Public Event OnReShow(ObjID As String, klasse As String)

Public Event OnQueryChange(ObjID As String, klasse As String, ByRef retval As Boolean) ' retval
Public Event OnChanged(ObjID As String, klasse As String, x As Variant, y As Variant, z As Variant) ' Koordinaten

Public Event OnQueryDelete(ObjID As String, klasse As String, ByRef retval As Boolean) 'retval
Public Event OnDeleted(ObjID As String, klasse As String)

Public Event OnQueryCreate(klasse As String, x As Variant, y As Variant, z As Variant, ByRef retval As Boolean) ' Koordinaten , retval

' Private cookie As Long
Private idmapper As New KanalID2TRiaSID
Private bHandling As Boolean

Private Sub Class_Initialize()
'    bHandling = False
'
'    Dim app As DApplication
'    Set app = GetTRiASApp
'    If app Is Nothing Then
'        Exit Sub
'    End If
'
'    cookie = app.Advise(Me)
End Sub

Private Sub Class_Terminate()
'    Dim app As DApplication
'    Set app = GetTRiASApp
'    If app Is Nothing Then
'        Exit Sub
'    End If
'
'    app.UnAdvise cookie
End Sub

Public Function GeoObjectEvent(ByVal hPrj As Long, ByVal oe As Long, ByVal lOnr As Long) As Long
    GeoObjectEvent = 0
    
    ' keine rekursiven Aufrufe
    If bHandling Then
        Exit Function
    End If
    bHandling = True
    
    On Error GoTo ende

    Dim kanalklasse As String
    kanalklasse = vbNullString
    Dim kanalid As String
    kanalid = vbNullString
    Dim retval As Boolean
    Dim dx() As Double
    Dim dy() As Double
    Dim dz() As Double
    Dim x As Variant
    Dim y As Variant
    Dim z As Variant
    Dim obj As DGeoObject
    Dim nPoints As Long
    Dim i As Long
    

    Select Case oe
        ' Auswählen
'    GEOOBJECTEVT_ObjectSelected,
      Case GEOOBJECTEVT_ObjectActivated  ' vielleicht vorher noch nachfragen
            GetObjekt lOnr, kanalid, kanalklasse
            RaiseEvent OnShow(kanalid, kanalklasse)
            
        ' Undo Auswahl
'        GEOOBJECTEVT_ObjectUnSelected
      Case GEOOBJECTEVT_ObjectDeActivated
            GetObjekt lOnr, kanalid, kanalklasse
            RaiseEvent OnReShow(kanalid, kanalklasse)
            
        ' will ändern
      Case GEOOBJECTEVT_ChangingGeometry
            If GetObjekt(lOnr, kanalid, kanalklasse) Then
                retval = True   ' Default : ich darf ändern
                RaiseEvent OnQueryChange(kanalid, kanalklasse, retval)
                
                If retval = False Then  ' doch nichts ändern
                    GeoObjectEvent = 1
                End If
            End If
            
        ' ändere
      Case GEOOBJECTEVT_GeometryChanged
             If GetObjekt(lOnr, kanalid, kanalklasse) Then
                Set obj = GetGeoObject(lOnr)
                If obj Is Nothing Then
                    Exit Function
                End If
                
                obj.GetGeometry nPoints
                
                nPoints = nPoints - 1
                ReDim dx(nPoints)
                ReDim dy(nPoints)
                ReDim dz(nPoints)
                                                
                ' z gibts nicht, also generieren
                For i = 0 To nPoints
                    dx(i) = 0
                Next
                obj.GetGeometry nPoints, dx, dy
                
                x = dx
                y = dy
                z = dz
                
                RaiseEvent OnChanged(kanalid, kanalklasse, x, y, z)    ' Koordinaten
            End If
      
        ' will löschen
      Case GEOOBJECTEVT_DeletingObject
             If GetObjekt(lOnr, kanalid, kanalklasse) Then
                retval = True   ' Default : ich darf löschen
                RaiseEvent OnQueryDelete(kanalid, kanalklasse, retval)
                
                If retval = False Then  ' es wurde irgendwas geändert
                    GeoObjectEvent = 1
                End If
            End If
      
      ' lösche
      Case GEOOBJECTEVT_ObjectToDelete
            If GetObjekt(lOnr, kanalid, kanalklasse) Then
                RaiseEvent OnDeleted(kanalid, kanalklasse)
            End If
      
      ' neuanlegen
      Case GEOOBJECTEVT_ObjectCreated
                Set obj = GetGeoObject(lOnr)
                If obj Is Nothing Then
                    Exit Function
                End If
                
                obj.GetGeometry nPoints
                
                nPoints = nPoints - 1
                ReDim dx(nPoints)
                ReDim dy(nPoints)
                ReDim dz(nPoints)
                                                
                ' z gibts nicht, also generieren
                For i = 0 To nPoints
                    dx(i) = 0
                Next
                obj.GetGeometry nPoints, dx, dy
                
                ' retyping
                x = dx
                y = dy
                z = dz
                
                kanalklasse = obj.ObjClass.Name
                
                retval = False   ' Default : Objekt wird nicht von Erweiterung verwaltet
                RaiseEvent OnQueryCreate(kanalklasse, x, y, z, retval)    ' Koordinaten
                If True = retval Then   ' das Objekt wird von irgendjemandem verwaltet also wieder löschen
                    RemoveObject obj
                End If
    End Select
    
'    GeoObjectEvent = 0 ' auf gar keinen Fall, sonst wird ja das Ergebnis wieder gelöscht
ende:
    bHandling = False

End Function

Function GetObjekt(lOnr As Long, kanalid As String, kanalklasse As String) As Boolean
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

Function GetGeoObject(lOnr As Long) As DGeoObject
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
