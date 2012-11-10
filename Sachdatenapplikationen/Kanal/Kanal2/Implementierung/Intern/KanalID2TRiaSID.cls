VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "KanalID2TRiaSID"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private Const KANALBasisID = "KANAL"
Private Const KANALDelimiter = "_"


Public Function GetTRiASIDfromKanalID(ObjID As String, klasse As String) As String
    ' wir bekommen nur einen eindeutigen SachdatenID runtergereicht
    GetTRiASIDfromKanalID = KANALBasisID & KANALDelimiter & _
                                            klasse & KANALDelimiter & _
                                            ObjID
End Function

' liefert vbNullString, wenn der TRiAS ID kein eindeutiger KanalID ist
Public Sub GetKANALIDFromTRiASID(TRiASID As String, ByRef ObjID As String, ByRef Class As String)
    
    Class = vbNullString
    ObjID = vbNullString
    
    
    Dim startKanalBasisID As Long
    startKanalBasisID = 1
    Dim lenKanalBasisID As Long
    lenKanalBasisID = Len(KANALBasisID)
    
    ' unsere Kennung prüfen
    If (Mid$(TRiASID, startKanalBasisID, lenKanalBasisID) <> KANALBasisID) Then
        Exit Sub
    End If
        
    ' jetzt
    Dim posdelimiter1 As Long
    posdelimiter1 = InStr(TRiASID, KANALDelimiter) + 1 ' die Startposition des Klassennamens
    
    ' Achtung posdelimiter1 ist bereits eins weitergesetzt
    Dim posdelimiter2 As Long
    posdelimiter2 = InStr(posdelimiter1, TRiASID, KANALDelimiter)  ' die Startposition des ID's
    
    ' Fehler
    If (posdelimiter2 <= lenKanalBasisID) Then
        Exit Sub
    End If
    
    ' korrekt
    Class = Mid$(TRiASID, posdelimiter1, posdelimiter2 - posdelimiter1)
    
    Dim charsinid As Long
    charsinid = Len(TRiASID) - posdelimiter2
    ObjID = Right(TRiASID, charsinid)
End Sub

