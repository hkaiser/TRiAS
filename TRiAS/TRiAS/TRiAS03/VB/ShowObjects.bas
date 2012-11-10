Attribute VB_Name = "ShowObjects"
Option Explicit

' Abbruch-Fehlercode
Const E_ABORT As Long = &H80004004
Const E_FAIL As Long = &H80004005

' Die folgende Folge von GeoKomponenten besteht aus lediglich einem Objekt,
' welches alle Objekte der Eingabeobjektmenge in einem ORFenster anzeigt

Sub ShowObjects(ByVal App As TRiAS.DApplication)

' Hilfobjekt für Sequenz erzeugen
Dim PropSeqSvr As New TRiAS.GeoComponentSequenceService
  
' Geduldsanzeige initialisieren
Dim ProgressInd As New TRiAS.ProgressIndicator

  ProgressInd.InitNew 0, TRiAS.PIFLAGS_RESULT

' Eingabedatenmenge, wird hier mit allen Objekten der Objektklasse
' 'Wald' gefüllt
Dim DataIn As TRiAS.TRiASDataObject

Dim Doc As TRiAS.GeoDocument
Dim Wald As TRiAS.DGeoClass
Dim Objs As TRiAS.DGeoObjects

  Set Doc = App.ActiveDocument()
  Set Wald = Doc.GetClass("Wald")
  Set Objs = Wald.GetObjects()

  Set DataIn = New TRiAS.TRiASDataObject
  DataIn.SetObjects Objs
  
  On Error GoTo labelError
  Call PropSeqSvr.RunActionSequenceFromFile( _
    0, "D:\TRiASDev.MVC\TRIAS03\VB\SelectObjectsInORWindow.xml", _
    "TestPropertyActionCaption1", "SaveAsTestPropertyAction1", _
    ProgressInd, DataIn, True)

  Exit Sub
  
labelError:
' Wenn der Nutzer 'Abbrechen' drückt landen wir hier
  If (Err.Number = E_ABORT) Then
    MsgBox "Nutzer hat abgebrochen"
  ElseIf (Err.Number = E_FAIL) Then
    MsgBox "Datenmenge enthält keine Objektmenge"
  Else
    MsgBox "Fehler: " + Str$(Err.Number) + " (" + Err.Description + ")"
  End If

End Sub



