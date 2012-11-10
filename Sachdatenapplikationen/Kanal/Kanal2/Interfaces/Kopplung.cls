VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Kopplung"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Private m_GISDatabase As String

' Starten der Kopplung
Public Function StarteKopplung() As Long
    StarteKopplung = 1
End Function

Public Function BeendeKopplung() As Long
    BeendeKopplung = 1
End Function

' eine Beispiel Kopplungseigenschaft
Public Property Get GISDatabase() As String
    GISDatabase = m_GISDatabase
End Property

Public Property Let GISDatabase(ByVal vNewValue As String)
    m_GISDatabase = GISDatabase
End Property

