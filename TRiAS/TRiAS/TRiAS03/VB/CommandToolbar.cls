VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CommandToolbar"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

' wir nicht nur eine Toolbar, sondern auch ein UIOwner
Implements ToolBarLib.DToolBarUIOwner

Dim TRiASApp As TRiAS.Application
Dim Toolbar As ToolBarLib.DControlToolBar
Dim BttnRetrieve As ToolBarLib.DControlToolBarButton
Dim BttnShow As ToolBarLib.DControlToolBarButton

Private Sub Class_Initialize()

  Set TRiASApp = Nothing
End Sub

Private Sub Class_Terminate()

  TRiASApp.RemoveToolBar "VBPropertySequence"
  
  Set BttnRetrieve = Nothing
  Set BttnShow = Nothing
  Set Toolbar = Nothing
  Set TRiASApp = Nothing
End Sub

Public Sub Init(App As TRiAS.Application)

  Set TRiASApp = App
  Set Toolbar = TRiASApp.AddToolBar("VBPropertySequence")
  
  Set BttnRetrieve = Toolbar.AddButton(0, Me)
  Set BttnShow = Toolbar.AddButton(1, Me)
  
  Toolbar.Visible = True
  
End Sub

Private Sub DToolBarUIOwner_FireCommand(ByVal uiID As Long, ByVal nCode As Long)

  If (nCode <> 0) Then
    Exit Sub      ' kein Command
  End If
  
  If (uiID = BttnRetrieve.CmdID) Then
    RetrieveObjects.RetrieveObjects TRiASApp   ' Objekte geben lassen
  ElseIf (uiID = BttnShow.CmdID) Then
    ShowObjects.ShowObjects TRiASApp           ' Objekte in OR-Fenster anzeigen
  End If
  
End Sub

Private Function DToolBarUIOwner_GetDescription(ByVal uiID As Long) As String

  If (uiID = BttnRetrieve.CmdID) Then
    DToolBarUIOwner_GetDescription = "RetrieveObjects" + Chr(10) + "RetrieveObjects"
  ElseIf (uiID = BttnShow.CmdID) Then
    DToolBarUIOwner_GetDescription = "ShowObjects" + Chr(10) + "ShowObjects"
  End If

End Function

Private Sub DToolBarUIOwner_SetToolBarUIOwnerSite(ByVal uiID As Long, ByVal pIToolBar As ToolBarLib.DControlToolBar)

End Sub

Private Sub DToolBarUIOwner_UpdateUI(ByVal pICmdUI As ToolBarLib.DTRiASCmdUI)

' Knöpfchen nur aktiv machen, wenn Projekt geöffnet ist
  If (TRiASApp.ActiveDocument Is Nothing) Then
    pICmdUI.IsEnabled = False
  Else
    pICmdUI.IsEnabled = True
  End If
End Sub
