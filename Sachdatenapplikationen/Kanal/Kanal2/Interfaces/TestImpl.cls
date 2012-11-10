VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TestImpl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Implements GeometrieSchnittstelle
Public Event bla()


Private Function GeometrieSchnittstelle_ErzeugeKreis(x As Double, y As Double, Durchmesser As Double, ObjID As String, Klasse As String) As Long
    
End Function

Private Function GeometrieSchnittstelle_ErzeugeLinie(x() As Double, y() As Double, ObjID As String, Klasse As String) As Long

End Function

Private Function GeometrieSchnittstelle_ErzeugeSymbol(x As Double, y As Double, Symboltyp As KANAL_Symboltyp, ObjID As String, Klasse As String) As Long

End Function

Private Function GeometrieSchnittstelle_ErzeugeText(x As Double, y As Double, Bezugspunkt As KANAL_TextBezugspunkt, Drehwinkel As Double, ObjID As String, Klasse As String) As Long

End Function

Private Function GeometrieSchnittstelle_Loesche(ObjID As String, Klasse As String) As Long
    
End Function
