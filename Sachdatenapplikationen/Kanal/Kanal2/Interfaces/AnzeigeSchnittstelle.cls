VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Darstellung"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

' Hervorheben einer Menge von Objekten
'Public Function Hervorheben(ObjIDs() As String, Klassen() As String) As Long
'    Hervorheben = 0
'End Function

' Zoomen auf eine Menge von Objekten
Public Function Zoomen(ObjIDs() As String, Klassen() As String) As Long
    Zoomen = 0
End Function

' Einfärben mit einem RGB-wert
Public Function FarbeSetzen(ObjIDs() As String, Klassen() As String, RGB As Long) As Long
    FarbeSetzen = 0
End Function

' Auswählen einer Menge von Objekten
Public Function Auswaehlen(ObjIDs() As String, Klassen() As String) As Long
    Auswaehlen = 0
End Function


