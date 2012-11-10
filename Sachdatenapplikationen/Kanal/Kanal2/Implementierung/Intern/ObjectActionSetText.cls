VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "ObjectActionSetText"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements ObjectAction
Public m_Text As String

Private Function ObjectAction_BeginAction() As Long
    ObjectAction_BeginAction = 0
End Function

Private Function ObjectAction_DoAction(obj As TRiAS.DGeoObject) As Long
    ObjectAction_DoAction = 1
    If obj Is Nothing Then
        Exit Function
    End If

    Dim tempval As Variant
    tempval = m_Text
    
    Dim prop As DTRiASProperty
    Set prop = Nothing
    On Error Resume Next
    Err.Clear
'    Set prop = obj.Properties("KanalInfo")
'
'    If prop Is Nothing Then
'        Err.Clear
'        Set prop = obj.Properties.Add("KanalInfo")
'    End If
    
    For Each prop In obj.Properties
        If prop.Name = "KanalInfo" Then
            prop.Value = m_Text
        End If
    Next
'    obj.Properties ("KanalInfo")
'    prop.Value = m_Text

ende:
    Err.Clear
End Function

Private Function ObjectAction_EndAction() As Long
    ObjectAction_EndAction = 0
End Function

