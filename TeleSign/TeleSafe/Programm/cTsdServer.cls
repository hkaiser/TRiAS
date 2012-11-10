VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "TsdServer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

Public Property Get Major() As Integer
    Major = App.Major
End Property

Public Property Get Minor() As Integer
    Minor = App.Minor
End Property

Public Property Get Revision() As Integer
    Revision = App.Minor
End Property

Public Property Get Version() As String
    Version = App.Major & "." & App.Minor & "." & App.Revision
End Property

Public Function Quit() As Long
    Unload fMainForm
End Function

Public Function OpenFile(strFileName As String) As Long
    
    If Len(strFileName) = 0 Then
        OpenFile = -1
        Exit Function
    End If
    
    fMainForm.ReadDokument strFileName
    fMainForm.RefreshListe
    OpenFile = 0
End Function

Public Function SaveFileAs(strFileName As String, lMode As Long) As Long
    gNode.SaveToTSD strFileName, False
    SaveFileAs = 0
End Function

Public Function AddDocument(strFileNameOrPath As String) As Long
On Error GoTo Err_AddDocument
 Dim dok As cNode
 Dim pages As cNode
 Dim hResult As Long
    If DateiExist(strFileNameOrPath) And ("DAT" = UCase(right(strFileNameOrPath, 3))) Then
        Set dok = gNode.SubNodes.Add("Dokument")
        If dok Is Nothing Then
            hResult = -1001
        Else
            dok.Caption = "Neues Dokument"
            Set pages = dok.SubNodes.Add("Visualisierung")
            pages.Caption = "Visualisierung"
            pages.LoadPrinterData strFileNameOrPath
        End If
        fMainForm.RefreshListe
    ElseIf right(strFileNameOrPath, 1) = "." Then
       If DateiExist(strFileNameOrPath & "001") Then
            Set dok = gNode.SubNodes.Add("Dokument")
            If Not dok Is Nothing Then
                dok.Caption = "Neues Dokument"
                Set pages = dok.SubNodes.Add("Visualisierung")
                pages.Caption = "Visualisierung"
                pages.LoadPrinterBitmaps strFileNameOrPath
            End If
        End If
        fMainForm.RefreshListe
    Else
        hResult = -1
    End If
    AddDocument = hResult
Exit Function

Err_AddDocument:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Function

Public Function AddEnclosure(strFileNameOrPath As String) As Long
On Error GoTo Err_AddEnclosure
 Dim oElement As cNode

    If vbDirectory = (GetAttr(strFileNameOrPath) And vbDirectory) Then
        Set oElement = gNode.SubNodes.Add("Verzeichnis")
        If Not oElement Is Nothing Then
            oElement.LoadFromPath strFileNameOrPath
            oElement.Caption = oElement.FileName
            Set oElement = Nothing
        End If
    Else
        Set oElement = gNode.SubNodes.Add("Anlage")
        If Not oElement Is Nothing Then
            oElement.LoadFromFile strFileNameOrPath
            oElement.Caption = oElement.FileName
            Set oElement = Nothing
        End If
    End If
        
    fMainForm.RefreshListe
    
    AddEnclosure = 0
Exit Function

Err_AddEnclosure:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Function
Public Function ShowDocument(ix As Integer, px As Integer) As Long
On Error GoTo Err_ShowDocument
 Dim iNumPages As Integer
 Dim strKey As String
 Dim nx As Integer
    If ix < 1 Or ix > gNode.SubNodes.Count Then
        ShowDocument = -1
    Else
        Set gCurElement = Nothing
        If gNode.SubNodes.Item(ix).Class = "Dokument" Then
            strKey = gNode.SubNodes.Item(ix).Visualisation(1).UniqueKey
            For nx = 1 To fMainForm.tvTreeView.Nodes.Count
                If fMainForm.tvTreeView.Nodes.Item(nx).Key = strKey Then
                    fMainForm.SetSelectedNode fMainForm.tvTreeView.Nodes.Item(nx)
                    Exit For
                End If
            Next nx
        Else
            ShowDocument = -2
        End If
        If gCurElement Is Nothing Then
            ShowDocument = -3
        Else
            iNumPages = gCurElement.ZahlSeiten
            If px < 1 Or px > iNumPages Then
                ShowDocument = -4
            Else
                gAktSeite = px
                fMainForm.ShowDetails
                fMainForm.ZeigeDetailBild "Details"
            End If
        End If
    End If
Exit Function

Err_ShowDocument:
    ShowDocument = -99
    Exit Function

End Function
Public Function SignElement(ix As Integer) As Long
On Error GoTo Err_SvrSignElement
 Dim iNumSignatures1 As Integer
 Dim iNumSignatures2 As Integer
 Dim strKey As String
 Dim nx As Integer
    If ix < 1 Or ix > gNode.SubNodes.Count Then
        SignElement = -1
    Else
        If gNode.SubNodes.Item(ix).Class = "Dokument" Then
            strKey = gNode.SubNodes.Item(ix).Visualisation(1).UniqueKey
        Else
            strKey = gNode.SubNodes.Item(ix).UniqueKey
        End If
        Set gCurElement = Nothing
        For nx = 1 To fMainForm.tvTreeView.Nodes.Count
            If fMainForm.tvTreeView.Nodes.Item(nx).Key = strKey Then
                fMainForm.SetSelectedNode fMainForm.tvTreeView.Nodes.Item(nx)
                Exit For
            End If
        Next nx
        If gCurElement Is Nothing Then
            SignElement = -2
        Else
            iNumSignatures1 = gNode.SubNodes.Item(ix).ZahlSignaturen()
            fMainForm.SignElement
            iNumSignatures2 = gNode.SubNodes.Item(ix).ZahlSignaturen()
            If iNumSignatures1 = iNumSignatures2 Then
                SignElement = -3
            Else
                SignElement = 0
            End If
        End If
    End If
Exit Function

Err_SvrSignElement:
    SignElement = -99
    Exit Function
End Function

Public Function SetWindowState(lWindowState As Long) As Long
    fMainForm.WindowState = lWindowState
End Function

Public Function SetWindowLayout(lWindowLayout As Long) As Long
    fMainForm.tvTreeView.Visible = (1 = (lWindowLayout And 1))
    fMainForm.SizeControls fMainForm.imgSplitter.Left
End Function

Public Function SetElementCaption(ix As Integer, strCaption As String) As Long
On Error GoTo Err_SetElementCaption
 Dim strKey As String
 Dim nx As Integer
    If ix < 1 Or ix > gNode.SubNodes.Count Then
        SetElementCaption = -1
    Else
        gNode.SubNodes.Item(ix).Caption = strCaption
        SetElementCaption = 0
        fMainForm.RefreshListe
    End If
Exit Function

Err_SetElementCaption:
    SetElementCaption = -99
    Exit Function
End Function

Public Function EncryptElement(ix As Integer) As Long
On Error GoTo Err_EncryptElement
 Dim iNumSignatures1 As Integer
 Dim iNumSignatures2 As Integer
 Dim strKey As String
 Dim nx As Integer
 Dim hResult As Long
 
    If 0 = ix And 0 = gNode.SubNodes.Count Then
        hResult = -1
    ElseIf ix < 0 Or gNode.SubNodes.Count < ix Then
        hResult = -1
    Else
        If ix = 0 Then
            Set gCurElement = gNode
        Else
            strKey = gNode.SubNodes.Item(ix).UniqueKey
            Set gCurElement = Nothing
            For nx = 1 To fMainForm.tvTreeView.Nodes.Count
                If fMainForm.tvTreeView.Nodes.Item(nx).Key = strKey Then
                    fMainForm.SetSelectedNode fMainForm.tvTreeView.Nodes.Item(nx)
                    Exit For
                End If
            Next nx
        End If
        If gCurElement Is Nothing Then
            hResult = -3
        Else
            If gCurElement.encrypted Then
                hResult = -2
            Else
                hResult = 0
                fMainForm.EncryptElement
            End If
        End If
    End If
    EncryptElement = hResult
Exit Function

Err_EncryptElement:
    EncryptElement = -99
    Exit Function
End Function

