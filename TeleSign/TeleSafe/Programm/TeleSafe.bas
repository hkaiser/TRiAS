Attribute VB_Name = "modMain"
Option Explicit

Global Const LISTVIEW_BUTTON = 11
Private lLastUniqueKey As Long
Public fMainForm As frmMain
'Public svrCryptoSeal As New TeleSign.CryptoSeal
Public svrTSCrypt As TSCryptSvr

Public gNode As cNode
Public gCurElement As cNode
Public gPrvElement As cNode

'Public gAktDok As cNode
'Public gAktPage As cNode
'Public gAktSign As cNode
Public gCurEnclosure As cNode
Public gZahlSeiten As Integer
Public gAktSeite As Integer
'Private gEnableDroping As Boolean
'Private gTempFileName As String
'Private gDokFileName As String
Public gDokFileVersion As Integer
Public gDokFileMajor As Long
Public gDokFileMinor As Long
Public gDokFileRevision As Long
Public gHeaderLen As Long
Public gExecutionMode As Long

Public gRecipients As String




Sub Main()
On Error GoTo Err_Main
 Dim hResult As Long
 Dim i As Integer, j As Integer, l As Integer
 Dim X As Double, bStartDirekt As Boolean
 Dim args
 Dim lDefaultExecutionMode As Long
 gRecipients = ""
    args = GetCommandLine
    gExecutionMode = RegGetDWORD(HKEY_LOCAL_MACHINE, "Software\FEZ Potsdam GmbH\TeleSafe\Printer", "ShellExecuteMode", 0)
    lDefaultExecutionMode = RegGetDWORD(HKEY_LOCAL_MACHINE, "Software\FEZ Potsdam GmbH\TeleSafe\Printer", "ShellExecuteDefaultMode", 0)
    RegSetDWORD HKEY_LOCAL_MACHINE, "Software\FEZ Potsdam GmbH\TeleSafe\Printer", "ShellExecuteMode", lDefaultExecutionMode
    
    If IsArray(args) And UBound(args) > 0 Then
        bStartDirekt = True
    End If

On Error Resume Next
'    Kill "C:\TEMP\TSD*.tmp"
On Error GoTo Err_Main
    If Not bStartDirekt Then
        frmSplash.Show
        frmSplash.Refresh

        For i = 1 To 300
            For j = 1 To 100
                For l = 1 To 100
                    X = 32 * 32
                Next l
            Next j
        Next i
    End If

    lLastUniqueKey = 0

    Set fMainForm = New frmMain
    Load fMainForm
    
    fMainForm.Show
    
    Unload frmSplash
Exit Sub

Err_Main:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Sub

Public Function GetPassword()
 Dim fPassword As frmPassword
    Set fPassword = New frmPassword
    Load fPassword
    fPassword.Show vbModal
    If fPassword.Tag = Chr(13) Then
        GetPassword = ""
    Else
        GetPassword = fPassword.Tag
    End If
    Unload fPassword
    Set fPassword = Nothing
End Function

Sub LoadResStrings(frm As Form)
    On Error Resume Next


    Dim ctl As Control
    Dim obj As Object
    Dim fnt As Object
    Dim sCtlType As String
    Dim nVal As Integer


    'set the form's caption
    frm.Caption = LoadResString(CInt(frm.Tag))
    

    'set the font
    Set fnt = frm.Font
    fnt.Name = LoadResString(20)
    fnt.Size = CInt(LoadResString(21))
    

    'set the controls' captions using the caption
    'property for menu items and the Tag property
    'for all other controls
    For Each ctl In frm.Controls
        Set ctl.Font = fnt
        sCtlType = TypeName(ctl)
        If sCtlType = "Label" Then
            ctl.Caption = LoadResString(CInt(ctl.Tag))
        ElseIf sCtlType = "Menu" Then
            ctl.Caption = LoadResString(CInt(ctl.Caption))
        ElseIf sCtlType = "TabStrip" Then
            For Each obj In ctl.Tabs
                obj.Caption = LoadResString(CInt(obj.Tag))
                obj.ToolTipText = LoadResString(CInt(obj.ToolTipText))
            Next
        ElseIf sCtlType = "Toolbar" Then
            For Each obj In ctl.Buttons
                obj.ToolTipText = LoadResString(CInt(obj.ToolTipText))
            Next
        ElseIf sCtlType = "ListView" Then
            For Each obj In ctl.ColumnHeaders
                obj.text = LoadResString(CInt(obj.Tag))
            Next
        Else
            nVal = 0
            nVal = Val(ctl.Tag)
            If nVal > 0 Then ctl.Caption = LoadResString(nVal)
            nVal = 0
            nVal = Val(ctl.ToolTipText)
            If nVal > 0 Then ctl.ToolTipText = LoadResString(nVal)
        End If
    Next
End Sub

Public Function GetUniqueKey() As String
    lLastUniqueKey = lLastUniqueKey + 1
    GetUniqueKey = "E" & Format(lLastUniqueKey, "000000")
End Function

Public Function GetCommandLine(Optional MaxArgs)
    'Declare variables.
    Dim C, CmdLine, CmdLnLen, InArg, i, NumArgs
    'See if MaxArgs was provided.
    If IsMissing(MaxArgs) Then MaxArgs = 10
    'Make array of the correct size.
    ReDim ArgArray(MaxArgs)
    NumArgs = 0: InArg = False
    'Get command line arguments.
    CmdLine = Command()
'    CmdLine = "D:\Programme\TeleSign\TSDBMP.DAT"
    CmdLnLen = Len(CmdLine)
    'Go thru command line one character
    'at a time.
    For i = 1 To CmdLnLen
        C = Mid(CmdLine, i, 1)
        'Test for space or tab.
        If (C <> " " And C <> vbTab) Then
            'Neither space nor tab.
            'Test if already in argument.
            If Not InArg Then
            'New argument begins.
            'Test for too many arguments.
                If NumArgs = MaxArgs Then Exit For
                NumArgs = NumArgs + 1
                InArg = True
            End If
            'Concatenate character to current argument.
            ArgArray(NumArgs) = ArgArray(NumArgs) & C
        Else
            'Found a space or tab.
            'Set InArg flag to False.
            InArg = False
        End If
    Next i
    'Resize array just enough to hold arguments.
    ReDim Preserve ArgArray(NumArgs)
    'Return Array in Function name.
    GetCommandLine = ArgArray()
End Function

