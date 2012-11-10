Attribute VB_Name = "RetrieveObjects"
Option Explicit

' Abbruch-Fehlercode
Const E_ABORT As Long = &H80004004
Const E_FAIL As Long = &H80004005

' Die folgende Folge von GeoKomponenten besteht aus lediglich einem Objekt,
' welches Objekte aus einem OR-Fenster selektiert und als Ergebnismenge
' liefert.

Sub RetrieveObjects(ByVal App As TRiAS.DApplication)

' Hilfobjekt für Sequenz erzeugen
Dim PropSeqSvr As New TRiAS.GeoComponentSequenceService
  
' Geduldsanzeige initialisieren
Dim ProgressInd As New TRiAS.ProgressIndicator

  ProgressInd.InitNew 0, TRiAS.PIFLAGS_RESULT

' Auch wenn keine Objektmenge am Eingang der Folge von GeoKomponenten
' 'angelegt' werden soll, muß ein gültiges Objekt vom Typ 'TRiASDataObject'
' übergeben werden.
Dim DataOut As TRiAS.TRiASDataObject
Dim Objs As TRiAS.DGeoObjects

  On Error GoTo labelError
  Set DataOut = PropSeqSvr.RunActionSequenceFromFile( _
    0, "D:\TRiASDev.MVC\TRIAS03\VB\SelectObjectsFromORWindow.xml", _
    "TestPropertyActionCaption2", "SaveAsTestPropertyAction2", _
    ProgressInd, Nothing, True)

  Set Objs = DataOut.GetObjects   ' erzeugt ggf. E_FAIL

Dim ObjWin As DGeoObjectWin

  Set ObjWin = Objs.CreateGeoObjectWin
  ObjWin.Visible = True
  
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



