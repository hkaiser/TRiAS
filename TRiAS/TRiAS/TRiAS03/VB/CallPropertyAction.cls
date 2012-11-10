VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "VBExtension"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

' unsere Toolbar
Dim Toolbar As CommandToolbar

' wir sind eine TRiAS Erweiterung
Implements TRiAS.DTRiASExtension

Private Sub DTRiASExtension_LoadExtension(ByVal App As TRiAS.DApplication, Optional ByVal vDocDisp As Variant)

  Set Toolbar = New CommandToolbar
  Toolbar.Init App
  
End Sub

Private Sub DTRiASExtension_UnloadExtension()

  Set Toolbar = Nothing
End Sub

Private Function DTRiASExtension_UnloadingExtension(ByVal fMayDeny As Boolean) As Boolean

  DTRiASExtension_UnloadingExtension = True
End Function

