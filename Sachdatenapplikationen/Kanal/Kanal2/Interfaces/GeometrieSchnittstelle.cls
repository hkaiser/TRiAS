VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Geometrie"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

' for future releases
' Public Event ErzeugeObjekt(Klasse As String, ByRef bWillHandle)
Public Event AendereObjekt(x() As Double, y() As Double, ObjID As String, klasse As String)
Public Event LoescheObjekt(ObjID As String, klasse As String)
Public Event ZeigeObjekt(ObjID As String, klasse As String)

Public Enum KANAL_Symboltyp
    KANAL_SymbolPfeil = 1
End Enum

Public Enum KANAL_TextBezugspunkt
    KANAL_TextBezugLinks = 0
    KANAL_TextBezugMittig = 1
    KANAL_TextBezugRechts = 2
End Enum

' Erzeugen einer Linie mit den angegebenen Stützpunkten
' Der externe Schlüssel des Objektes ist ObjID, es gehört (intern und extern) zur Klasse Klasse
' Der Rückkehrwert 0 zeigt an, daß die Aktion ohne Fehler ausgeführt werden konnte
Public Function ErzeugeLinie(x() As Double, y() As Double, ObjID As String, klasse As String) As Long
    ErzeugeLinie = 0
End Function

' Erzeugen eines Kreises mit dem angegebenen Mittelpunkt und Durchmesser
' Der externe Schlüssel des Objektes ist ObjID, es gehört (inbtern und extern) zur Klasse Klasse
' Der Rückkehrwert 0 zeigt an, daß die Aktion ohne Fehler ausgeführt werden konnte
Public Function ErzeugeKreis(x As Double, y As Double, Durchmesser As Double, ObjID As String, klasse As String) As Long
    ErzeugeKreis = 0
End Function

' Erzeugen eines Symboles des angegebenen Types mit dem angegebenen Mittelpunkt und Durchmesser
' Der externe Schlüssel des Objektes ist ObjID, es gehört (inbtern und extern) zur Klasse Klasse
' Der Rückkehrwert 0 zeigt an, daß die Aktion ohne Fehler ausgeführt werden konnte
Public Function ErzeugeSymbol(x As Double, y As Double, Symbol As Long, sizex As Double, sizey As Double, rotation As Double, ObjID As String, klasse As String) As Long
    ErzeugeSymbol = 0
End Function

' Erzeugen eines Textes an dem angegebenen Punkt mit der in Bezugspunkt vorgegebenen Ausrichtung und dem vorgegebenen Drehwinkel
' Der externe Schlüssel des Objektes ist ObjID, es gehört (inbtern und extern) zur Klasse Klasse
' Der Rückkehrwert 0 zeigt an, daß die Aktion ohne Fehler ausgeführt werden konnte
Public Function ErzeugeText(x As Double, y As Double, Bezugspunkt As KANAL_TextBezugspunkt, Drehwinkel As Double, VisText As String, ObjID As String, klasse As String) As Long
    ErzeugeText = 0
End Function

' Löschen des angegebenen Objektes
Public Function Loesche(ObjID As String, klasse As String) As Long
    Loesche = 0
End Function
