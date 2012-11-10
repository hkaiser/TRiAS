VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "ObjectActionSetColor"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Dim m_Color As TRIASCOLOR

Implements ObjectAction

Private Function ObjectAction_BeginAction() As Long
    ObjectAction_BeginAction = 0
End Function

Private Function ObjectAction_DoAction(obj As TRiAS.DGeoObject) As Long
    If obj Is Nothing Then
        ObjectAction_DoAction = 1
        Exit Function
    End If
    
    ' die eigentliche Aktion
    On Error Resume Next
    Dim vi As TRiAS.DVisInfo
    Set vi = obj.GetVisInfo
    vi.MainColor = m_Color
    SchreibeVisInfo obj, vi
    
'    obj.Hilight m_Color
    
    ObjectAction_DoAction = 0
End Function

Private Function ObjectAction_EndAction() As Long
    ObjectAction_EndAction = 0
End Function

Public Property Get Color() As TRIASCOLOR
    Color = m_Color
End Property

Public Property Let Color(ByVal vNewValue As TRIASCOLOR)
    m_Color = vNewValue
End Property

