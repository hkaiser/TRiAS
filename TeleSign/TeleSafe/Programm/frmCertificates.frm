VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form frmCertificates 
   Caption         =   "Zertifikate"
   ClientHeight    =   4245
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7830
   LinkTopic       =   "Form1"
   ScaleHeight     =   4245
   ScaleWidth      =   7830
   StartUpPosition =   3  'Windows-Standard
   Begin VB.CommandButton K_Exit 
      Caption         =   "&Schließen"
      Height          =   375
      Left            =   6480
      TabIndex        =   9
      Top             =   3840
      Width           =   1335
   End
   Begin VB.CommandButton K_User 
      Caption         =   "Empfänger hinzufügen"
      Height          =   375
      Left            =   2880
      TabIndex        =   8
      Top             =   3360
      Width           =   2295
   End
   Begin VB.CommandButton K_Show 
      Caption         =   "&Anzeigen..."
      Height          =   375
      Left            =   6480
      TabIndex        =   6
      Top             =   3360
      Width           =   1335
   End
   Begin VB.CommandButton K_Export 
      Caption         =   "E&xportieren..."
      Height          =   375
      Left            =   1440
      TabIndex        =   5
      Top             =   3360
      Width           =   1335
   End
   Begin MSComDlg.CommonDialog dlgCommon 
      Left            =   5760
      Top             =   3360
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.CommandButton K_Import 
      Caption         =   "&Importieren..."
      Height          =   375
      Left            =   0
      TabIndex        =   4
      Top             =   3360
      Width           =   1335
   End
   Begin TabDlg.SSTab tabCertificates 
      Height          =   3255
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   7815
      _ExtentX        =   13785
      _ExtentY        =   5741
      _Version        =   393216
      Tab             =   2
      TabHeight       =   520
      TabCaption(0)   =   "Eigene Zertifikate"
      TabPicture(0)   =   "frmCertificates.frx":0000
      Tab(0).ControlEnabled=   0   'False
      Tab(0).Control(0)=   "lstOwnCertificates"
      Tab(0).ControlCount=   1
      TabCaption(1)   =   "Andere Personen"
      TabPicture(1)   =   "frmCertificates.frx":001C
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "lstOtherCertificates"
      Tab(1).ControlCount=   1
      TabCaption(2)   =   "Empfängerliste"
      TabPicture(2)   =   "frmCertificates.frx":0038
      Tab(2).ControlEnabled=   -1  'True
      Tab(2).Control(0)=   "lstUserCertificates"
      Tab(2).Control(0).Enabled=   0   'False
      Tab(2).ControlCount=   1
      Begin ComctlLib.ListView lstOwnCertificates 
         Height          =   2775
         Left            =   -74880
         TabIndex        =   2
         Top             =   360
         Width           =   7575
         _ExtentX        =   13361
         _ExtentY        =   4895
         View            =   2
         LabelWrap       =   -1  'True
         HideSelection   =   0   'False
         _Version        =   327682
         ForeColor       =   -2147483640
         BackColor       =   -2147483643
         BorderStyle     =   1
         Appearance      =   1
         NumItems        =   0
      End
      Begin ComctlLib.ListView lstOtherCertificates 
         Height          =   2775
         Left            =   -74880
         TabIndex        =   3
         Top             =   360
         Width           =   7575
         _ExtentX        =   13361
         _ExtentY        =   4895
         View            =   2
         LabelWrap       =   -1  'True
         HideSelection   =   -1  'True
         _Version        =   327682
         ForeColor       =   -2147483640
         BackColor       =   -2147483643
         BorderStyle     =   1
         Appearance      =   1
         NumItems        =   0
      End
      Begin ComctlLib.ListView lstUserCertificates 
         Height          =   2775
         Left            =   120
         TabIndex        =   7
         Top             =   360
         Width           =   7575
         _ExtentX        =   13361
         _ExtentY        =   4895
         View            =   2
         LabelWrap       =   -1  'True
         HideSelection   =   -1  'True
         _Version        =   327682
         ForeColor       =   -2147483640
         BackColor       =   -2147483643
         BorderStyle     =   1
         Appearance      =   1
         NumItems        =   0
      End
   End
   Begin VB.CommandButton K_Cancel 
      Caption         =   "Abbre&chen"
      Height          =   375
      Left            =   5040
      TabIndex        =   0
      Top             =   3840
      Visible         =   0   'False
      Width           =   1335
   End
End
Attribute VB_Name = "frmCertificates"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Sub GetCertificates()
On Error GoTo Err_GetCertificates
 Dim cx As Integer
 Dim itmX As ListItem
 Dim itmU As ListItem
 Dim pCertificate As Long
 Dim strVal As String
 Dim strErrorDescription As String
 Dim tOwnCertificate As Boolean
 
    Me.lstOwnCertificates.ListItems.Clear
    Me.lstOtherCertificates.ListItems.Clear
        
        cx = 0
        hResult = svrTSCrypt.GetFirstCertificate(pCertificate)
        Do While hResult = 0
            cx = cx + 1
            hResult = svrTSCrypt.IsOwnCertificate(pCertificate)
            If hResult = 1 Then
                Set itmX = lstOwnCertificates.ListItems.Add(, "C" & Format(cx, "000"))
                tOwnCertificate = True
            ElseIf hReesult = 0 Then
                Set itmX = lstOtherCertificates.ListItems.Add(, "C" & Format(cx, "000"))
                tOwnCertificate = False
            Else
                hResult = svrTSCrypt.GetErrorDescription(hResult, strErrorDescription)
                MsgBox strErrorDescription
                hResult = -1
                Exit Do
            End If
            itmX.Tag = Str(pCertificate)
            hResult = svrTSCrypt.GetOwnerCommonName(pCertificate, strVal)
            If hResult = 0 Then
                itmX.text = strVal
            End If
            hResult = svrTSCrypt.GetIssuerCommonName(pCertificate, strVal)
            If hResult = 0 Then
                itmX.SubItems(1) = strVal
            End If
            hResult = svrTSCrypt.GetNotAfter(pCertificate, strVal)
            If hResult = 0 Then
                If Len(strVal) = 13 Then
                    If Val(Left(strVal, 2)) > 50 Then
                        strVal = Mid(strVal, 5, 2) & "." & Mid(strVal, 3, 2) & "." & "19" & Left(strVal, 2)
                    Else
                        strVal = Mid(strVal, 5, 2) & "." & Mid(strVal, 3, 2) & "." & "20" & Left(strVal, 2)
                    End If
                ElseIf Len(strVal) = 15 Then
                    strVal = Mid(strVal, 7, 2) & "." & Mid(strVal, 5, 2) & "." & Left(strVal, 4)
                Else
                    strVal = "unbekanntes Format"
                End If
                itmX.SubItems(2) = strVal
            End If
            hResult = svrTSCrypt.GetLabel(pCertificate, strVal)
            If hResult = 0 Then
                itmX.SubItems(3) = strVal
            End If
            If tOwnCertificate And Me.lstUserCertificates.ListItems.Count = 0 _
                And itmX.text <> itmX.SubItems(1) Then
                Set itmU = lstUserCertificates.ListItems.Add(, itmX.Key)
                itmU.text = itmX.text
                itmU.Tag = itmX.Tag
                itmU.SubItems(1) = itmX.SubItems(1)
                itmU.SubItems(2) = itmX.SubItems(2)
                itmU.SubItems(3) = itmX.SubItems(3)
                Set itmU = Nothing
            End If
            Set itmX = Nothing
            hResult = svrTSCrypt.GetNextCertificate(pCertificate)
        Loop

Exit Sub

Err_GetCertificates:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Sub
Private Sub Form_Load()
On Error GoTo Err_Form_Load
 Dim strErrorDescription As String
 Dim clmX As ColumnHeader
 Dim lst As ListView
 
    Me.tabCertificates.Tab = 0
    Me.tabCertificates.TabVisible(2) = False
    Me.K_User.Visible = False
    
    Set svrTSCrypt = New TSCRYPTLib.TSCryptSvr
    If svrTSCrypt Is Nothing Then
        MsgBox "Der Kryptographiemodul konnte nicht geladen werden!"
    Else
        With Me.lstOwnCertificates
            .ListItems.Clear
            .View = lvwReport
            .ColumnHeaders.Clear
            Set clmX = .ColumnHeaders.Add(, , "Ausgestellt für", Int(Me.lstOwnCertificates.Width / 5))
            Set clmX = .ColumnHeaders.Add(, , "Ausgestellt von", Int(Me.lstOwnCertificates.Width / 5))
            Set clmX = .ColumnHeaders.Add(, , "Gültig bis", Int(Me.lstOwnCertificates.Width / 5))
            Set clmX = .ColumnHeaders.Add(, , "Angezeigter Name", Int(Me.lstOwnCertificates.Width / 5))
        End With
        
        With Me.lstOtherCertificates
            .ListItems.Clear
            .View = lvwReport
            .ColumnHeaders.Clear
            Set clmX = .ColumnHeaders.Add(, , "Ausgestellt für", Int(Me.lstOwnCertificates.Width / 5))
            Set clmX = .ColumnHeaders.Add(, , "Ausgestellt von", Int(Me.lstOwnCertificates.Width / 5))
            Set clmX = .ColumnHeaders.Add(, , "Gültig bis", Int(Me.lstOwnCertificates.Width / 5))
            Set clmX = .ColumnHeaders.Add(, , "Angezeigter Name", Int(Me.lstOwnCertificates.Width / 5))
        End With
        
        With Me.lstUserCertificates
            .ListItems.Clear
            .View = lvwReport
            .ColumnHeaders.Clear
            Set clmX = .ColumnHeaders.Add(, , "Ausgestellt für", Int(Me.lstOwnCertificates.Width / 5))
            Set clmX = .ColumnHeaders.Add(, , "Ausgestellt von", Int(Me.lstOwnCertificates.Width / 5))
            Set clmX = .ColumnHeaders.Add(, , "Gültig bis", Int(Me.lstOwnCertificates.Width / 5))
            Set clmX = .ColumnHeaders.Add(, , "Angezeigter Name", Int(Me.lstOwnCertificates.Width / 5))
        End With
        hResult = svrTSCrypt.SetDatabase(App.Path)
        hResult = svrTSCrypt.SetPassword(GetPassword())
        hResult = svrTSCrypt.Open()
        If hResult <> 0 Then
           hResult = svrTSCrypt.GetErrorDescription(hResult, strErrorDescription)
           MsgBox strErrorDescription
        End If
        GetCertificates
    End If
Exit Sub

Err_Form_Load:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Sub

Private Sub Form_Unload(CANCEL As Integer)
On Error GoTo Err_Form_unload
 Dim svrSpezial As New TSPrinter
    If Not svrTSCrypt Is Nothing Then
        hResult = svrTSCrypt.Close()
        Set svrTSCrypt = Nothing
    End If
    svrSpezial.spezial1
Exit Sub
Err_Form_unload:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Sub

Private Sub K_Cancel_Click()
    Me.Tag = Chr(13)
    Me.Hide
End Sub

Private Sub K_Exit_Click()
    If Me.tabCertificates.TabVisible(2) And Me.lstUserCertificates.ListItems.Count = 0 Then
        MsgBox "Sie müssen erst der Empfängerliste einen Empfänger hinzufügen!"
    Else
        Me.Tag = ""
        Me.Hide
    End If
End Sub

Private Sub K_Export_Click()
On Error GoTo Err_K_Export
 Dim itmX As ListItem
 Dim hResult As Long
 Dim strErrorDescription As String
    
    If Me.tabCertificates.Tab = 0 Then
        Set itmX = Me.lstOwnCertificates.SelectedItem
    ElseIf Me.tabCertificates.Tab = 1 Then
        Set itmX = Me.lstOtherCertificates.SelectedItem
    ElseIf Me.tabCertificates.Tab = 2 Then
        Set itmX = Me.lstUserCertificates.SelectedItem
    End If

    If itmX Is Nothing Then
        MsgBox "Sie müssen erst ein Zertifikat auswählen!"
    Else
        With Me.dlgCommon
            .Filter = "Zertifikate (*.DER)|*.DER|Alle Dateien (*.*)|*.*"
            .Flags = cdlOFNHideReadOnly
            .ShowOpen
            If Len(.FileName) = 0 Then
                Exit Sub
            End If
            hResult = svrTSCrypt.ExportCertificate(.FileName, itmX.Tag)
            If hResult <> 0 Then
                hResult = svrTSCrypt.GetErrorDescription(hResult, strErrorDescription)
                MsgBox strErrorDescription
            End If
        End With
    End If

Exit Sub

Err_K_Export:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Sub

Private Sub K_Import_Click()
On Error GoTo Err_K_Import
 Dim strErrorDescription As String
 Dim hFile As Long

    With Me.dlgCommon
        .Filter = "Zertifikate (*.DER)|*.DER|Alle Dateien (*.*)|*.*"
        .Flags = cdlOFNHideReadOnly
        .ShowOpen
        If Len(.FileName) = 0 Then
            Exit Sub
        End If
        hResult = svrTSCrypt.ImportCertificates(.FileName)
        If hResult <> 0 Then
           hResult = svrTSCrypt.GetErrorDescription(hResult, strErrorDescription)
           MsgBox strErrorDescription
        Else
            GetCertificates
        End If
    End With
Exit Sub

Err_K_Import:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next

End Sub

Private Sub K_Show_Click()
On Error GoTo Err_K_Show
 Dim itmX As ListItem
 Dim hResult As Long
 Dim strErrorDescription As String
 Dim strCommand As String
    If Me.tabCertificates.Tab = 0 Then
        Set itmX = Me.lstOwnCertificates.SelectedItem
    ElseIf Me.tabCertificates.Tab = 1 Then
        Set itmX = Me.lstOtherCertificates.SelectedItem
    ElseIf Me.tabCertificates.Tab = 2 Then
        Set itmX = Me.lstUserCertificates.SelectedItem
    End If

    If itmX Is Nothing Then
        MsgBox "Sie müssen erst ein Zertifikat auswählen!"
    Else
        hResult = svrTSCrypt.ExportCertificate(App.Path & "\TSCert.der", itmX.Tag)
        If hResult <> 0 Then
            hResult = svrTSCrypt.GetErrorDescription(hResult, strErrorDescription)
            MsgBox strErrorDescription
            MsgBox "Das Zertifikat konnte nicht angezeigt werden!"
        Else
            strCommand = RegGetCommandDER
            strCommand = Mid(strCommand, 1, InStr(strCommand, "%1") - 1) & App.Path & "\TSCert.der" & Mid(strCommand, InStr(strCommand, "%1") + 2)
            If Len(strCommand) > 0 Then
                Shell strCommand, vbNormalFocus
            Else
                MsgBox "Auf diesem Rechner ist kein Programm zum Anzeigen von Zertifikaten installiert!"
            End If
        End If
    End If
Exit Sub

Err_K_Show:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next

End Sub

Private Sub K_User_Click()
 Dim itmX As ListItem
 Dim itmU As ListItem
 
    If Me.tabCertificates.Tab = 2 Then  ' Empfänger entfernen
        Set itmX = Me.lstUserCertificates.SelectedItem
        If itmX Is Nothing Then
            MsgBox "Sie müssen erst ein Zertifikat auswählen!"
        Else
            Me.lstUserCertificates.ListItems.Remove itmX.Key
        End If
    Else                                ' Empfänger hinzufügen
        If Me.tabCertificates.Tab = 0 Then
            Set itmX = Me.lstOwnCertificates.SelectedItem
        ElseIf Me.tabCertificates.Tab = 1 Then
            Set itmX = Me.lstOtherCertificates.SelectedItem
        End If
            
        If itmX Is Nothing Then
            MsgBox "Sie müssen erst ein Zertifikat auswählen!"
        Else
            Set itmU = Me.lstUserCertificates.FindItem(itmX.Tag, lvwTag, , lvwWholeWord)
            If itmU Is Nothing Then
                Set itmU = lstUserCertificates.ListItems.Add(, itmX.Key)
                itmU.text = itmX.text
                itmU.Tag = itmX.Tag
                itmU.SubItems(1) = itmX.SubItems(1)
                itmU.SubItems(2) = itmX.SubItems(2)
                itmU.SubItems(3) = itmX.SubItems(3)
                Set itmU = Nothing
            Else
                MsgBox "Dieses Zertifikat wurde der Empfängerliste bereits hinzugefügt!"
            End If
            Set itmX = Nothing
        End If
    End If
    
End Sub

Private Sub tabCertificates_Click(PreviousTab As Integer)
    If Me.tabCertificates.Tab = 2 Then
        Me.K_User.Caption = "Empfänger entfernen"
    Else
        Me.K_User.Caption = "Empfänger hinzufügen"
    End If
End Sub

