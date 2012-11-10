VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "ObjectActionZoom"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements ObjectAction

Private xmin As Double
Private xmax As Double
Private ymin As Double
Private ymax As Double
Private initialized As Boolean

Private Sub Class_Initialize()
    initialized = False
End Sub

Private Function ObjectAction_BeginAction() As Long
    
End Function

Private Function ObjectAction_DoAction(obj As TRiAS.DGeoObject) As Long
    ObjectAction_DoAction = 1
    If obj Is Nothing Then
        Exit Function
    End If
    
    ObjectAction_DoAction = 0
    If initialized Then
    '   Testweise einfach nur auf das erst beste Objekt zoomen
        Dim txmin As Double
        Dim txmax As Double
        Dim tymin As Double
        Dim tymax As Double
        obj.GetGeometryRect txmin, tymin, txmax, tymax

        ' jetzt die Größen vergleichen
        If txmin < xmin Then
            xmin = txmin
        End If

        If txmax > xmax Then
            xmax = txmax
        End If

        If tymin < ymin Then
            ymin = tymin
        End If

        If tymax > ymax Then
            ymax = tymax
        End If
    Else    ' nicht initialisiert
        ' Gesamtcontainer = Objektcontainer
        obj.GetGeometryRect xmin, ymin, xmax, ymax
        initialized = True
    End If
       
End Function

Private Function ObjectAction_EndAction() As Long
    ' evtl sollte man das ganze noch anpassen, evtl den Kontext besser anzeigen
    ObjectAction_EndAction = 1
    TRiASZoom xmin, ymin, xmax, ymax
    ObjectAction_EndAction = 0
End Function

