VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Kreisgenerator"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Const PI = 3.1415
Const m_maxSector = 64
Private m_gx() As Double
Private m_gy() As Double
Private m_bInitialized As Boolean


Public Sub GenerateKreis(x As Double, y As Double, durchmesser As Double, ByRef ax() As Double, ByRef ay() As Double)
    InitBasisGeometrie
    
    ' Platz schaffen
    ReDim ax(0 To m_maxSector + 1)
    ReDim ay(0 To m_maxSector + 1)
    
    Dim i As Long ' Laufvar.
    For i = 0 To m_maxSector
        ay(i) = m_gy(i) * durchmesser + y   ' mit Durchmesser skalieren und Offset draufgeben
        ax(i) = m_gx(i) * durchmesser + x
    Next
    
    ' explicit die Kontur schlieﬂen
    ax(m_maxSector + 1) = ax(0)
    ay(m_maxSector + 1) = ay(0)
End Sub

Private Sub InitBasisGeometrie()
    If m_bInitialized Then
        Exit Sub
    End If
    
    ' Platz schaffen (evtl hier noch einen mehr)
    ReDim m_gx(0 To m_maxSector)
    ReDim m_gy(0 To m_maxSector)
    
    Dim i As Long ' Laufvar.
    Dim arc As Double ' Winkel
    
    For i = 0 To m_maxSector
        arc = (i * PI * 2) / (m_maxSector + 1)
        m_gx(i) = Sin(arc) / 2
        m_gy(i) = Cos(arc) / 2
    Next
End Sub

