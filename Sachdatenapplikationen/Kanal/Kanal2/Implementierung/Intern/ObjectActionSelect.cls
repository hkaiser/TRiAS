VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "ObjectActionSelect"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements ObjectAction
Dim objs As DGeoObjects

Private Function ObjectAction_BeginAction() As Long
    Dim doc As GeoDocument
    Set doc = GetTRiASDocument
    
    Set objs = doc.CreateGeoObjectsCollection
    If objs Is Nothing Then
        ObjectAction_BeginAction = 1    ' Fehler
    Else
        ObjectAction_BeginAction = 0
    End If
End Function

Private Function ObjectAction_DoAction(obj As TRiAS.DGeoObject) As Long
    ObjectAction_DoAction = 1
    If obj Is Nothing Then
        Exit Function
    End If

    If objs.Add(obj) Is Nothing Then
        ' do nothing
    Else
        ObjectAction_DoAction = 0
    End If
End Function

Private Function ObjectAction_EndAction() As Long
    ' ORW erzeugen und aktivieren
    Dim win As DGeoObjectWin
    Set win = objs.CreateGeoObjectWin(CREATEOBJECTWIN_SortText)
    win.SetActive
End Function
