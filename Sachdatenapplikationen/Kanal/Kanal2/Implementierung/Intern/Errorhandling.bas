Attribute VB_Name = "Errorhandling"
Option Explicit

Private Const UserdefinedErrorStart = 1000000
Enum ErrorID
ErrorIDNoError = 0
ErrorIDCouldntCreateClass = 1
ErrorIDCouldntCreateObj = 2
ErrorIDOpenTRiAS = 3
ErrorIDOpenProject = 4
ErrorIDInvalidArrayDimension = 5
End Enum


Sub ErzeugeFehler(errID As ErrorID, Optional additionalDesc As String)
  Dim desc As String
  Select Case errID
    Case ErrorIDNoError:
      Exit Sub
    Case ErrorIDCouldntCreateClass:
      desc = "Klasse " & additionalDesc & " konnte nicht erzeugt werden"
    Case ErrorIDCouldntCreateObj:
      desc = "Objekt " & additionalDesc & " konnte nicht erzeugt werden"
    Case ErrorIDOpenTRiAS:
      desc = "TRiAS konnte nicht gestartet werden"
    Case ErrorIDOpenProject:
      desc = "Das Projekt " & additionalDesc & " konnte nicht geöffnet werden"
    Case ErrorIDInvalidArrayDimension:
      desc = "Fehler bei der Dimensionierung der dynamischen Arrays"
    Case Else:
      desc = ""
  End Select
                          
  Err.Raise errID + UserdefinedErrorStart, "TRiASWrapper", desc
 Exit Sub
End Sub

