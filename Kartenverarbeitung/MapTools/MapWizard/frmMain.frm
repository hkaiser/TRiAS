VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "Tabctl32.ocx"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "Comdlg32.ocx"
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "Mscomctl.ocx"
Begin VB.Form frmMain 
   Caption         =   "TRiAS-MapWizard"
   ClientHeight    =   6165
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8385
   LinkTopic       =   "Form1"
   ScaleHeight     =   6165
   ScaleWidth      =   8385
   StartUpPosition =   3  'Windows-Standard
   Begin VB.CommandButton K_Navigate 
      Caption         =   "Command1"
      Height          =   375
      Index           =   1
      Left            =   7080
      TabIndex        =   2
      Top             =   5520
      Width           =   1215
   End
   Begin VB.CommandButton K_Navigate 
      Caption         =   "Command1"
      Height          =   375
      Index           =   0
      Left            =   5880
      TabIndex        =   1
      Top             =   5520
      Width           =   1215
   End
   Begin TabDlg.SSTab tabPages 
      Height          =   5295
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   8175
      _ExtentX        =   14420
      _ExtentY        =   9340
      _Version        =   393216
      Style           =   1
      Tab             =   1
      TabsPerRow      =   10
      TabHeight       =   176
      TabCaption(0)   =   "Tab 0"
      TabPicture(0)   =   "frmMain.frx":0000
      Tab(0).ControlEnabled=   0   'False
      Tab(0).Control(0)=   "cbExcludeMapWizardDir"
      Tab(0).Control(1)=   "cboMaszstab"
      Tab(0).Control(2)=   "strSourceDir"
      Tab(0).Control(3)=   "K_SelectSourceDir"
      Tab(0).Control(4)=   "cbRecursiv"
      Tab(0).Control(5)=   "cboKartentyp"
      Tab(0).Control(6)=   "cboBildformat"
      Tab(0).Control(7)=   "cboGrundkonfiguration"
      Tab(0).Control(8)=   "Label3"
      Tab(0).Control(9)=   "Label6"
      Tab(0).Control(10)=   "Label5"
      Tab(0).Control(11)=   "Label1"
      Tab(0).Control(12)=   "Label4"
      Tab(0).ControlCount=   13
      TabCaption(1)   =   "Tab 1"
      TabPicture(1)   =   "frmMain.frx":001C
      Tab(1).ControlEnabled=   -1  'True
      Tab(1).Control(0)=   "lblLayer"
      Tab(1).Control(0).Enabled=   0   'False
      Tab(1).Control(1)=   "lblDateien"
      Tab(1).Control(1).Enabled=   0   'False
      Tab(1).Control(2)=   "Label2"
      Tab(1).Control(2).Enabled=   0   'False
      Tab(1).Control(3)=   "lboLayer"
      Tab(1).Control(3).Enabled=   0   'False
      Tab(1).Control(4)=   "txtInfo"
      Tab(1).Control(4).Enabled=   0   'False
      Tab(1).Control(5)=   "lboDateien"
      Tab(1).Control(5).Enabled=   0   'False
      Tab(1).Control(6)=   "K_AlleLayer"
      Tab(1).Control(6).Enabled=   0   'False
      Tab(1).Control(7)=   "K_AlleDateien"
      Tab(1).Control(7).Enabled=   0   'False
      Tab(1).ControlCount=   8
      TabCaption(2)   =   "Tab 2"
      TabPicture(2)   =   "frmMain.frx":0038
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "cbRetainTempFiles"
      Tab(2).Control(1)=   "K_DestinationFile"
      Tab(2).Control(2)=   "strDestinationFile"
      Tab(2).Control(3)=   "cbStoreCmd"
      Tab(2).Control(4)=   "Frame1"
      Tab(2).Control(5)=   "K_SelectDestinationDir"
      Tab(2).Control(6)=   "strDestinationDir"
      Tab(2).Control(7)=   "DlgCommon"
      Tab(2).Control(8)=   "Label7"
      Tab(2).ControlCount=   9
      Begin VB.CheckBox cbExcludeMapWizardDir 
         Caption         =   "ohne *MapWizard*-Unterverzeichnisse"
         Height          =   255
         Left            =   -70440
         TabIndex        =   41
         Top             =   600
         Value           =   1  'Aktiviert
         Width           =   3255
      End
      Begin VB.CheckBox cbRetainTempFiles 
         Caption         =   "temporärer Dateien erhalten"
         Height          =   375
         Left            =   -74760
         TabIndex        =   40
         Top             =   3840
         Width           =   2535
      End
      Begin VB.ComboBox cboMaszstab 
         Enabled         =   0   'False
         Height          =   315
         Left            =   -73320
         TabIndex        =   38
         Top             =   2430
         Width           =   3975
      End
      Begin VB.CommandButton K_AlleDateien 
         Caption         =   "alle Dateien"
         Height          =   255
         Left            =   1680
         TabIndex        =   35
         Top             =   2280
         Width           =   1095
      End
      Begin VB.CommandButton K_AlleLayer 
         Caption         =   "alle Layer"
         Height          =   255
         Left            =   1680
         TabIndex        =   34
         Top             =   120
         Width           =   1095
      End
      Begin VB.CommandButton K_DestinationFile 
         Caption         =   "..."
         Height          =   255
         Left            =   -67680
         TabIndex        =   33
         Top             =   3480
         Width           =   375
      End
      Begin VB.TextBox strDestinationFile 
         Height          =   285
         Left            =   -71880
         TabIndex        =   32
         Top             =   3480
         Width           =   4215
      End
      Begin VB.CheckBox cbStoreCmd 
         Caption         =   "Befehle nur in .BAT-Datei speichern"
         Height          =   255
         Left            =   -74760
         TabIndex        =   31
         Top             =   3480
         Width           =   3015
      End
      Begin VB.Frame Frame1 
         Caption         =   "Verarbeitungsschritte"
         Height          =   2415
         Left            =   -74760
         TabIndex        =   20
         Top             =   240
         Width           =   7455
         Begin VB.CheckBox cbRenameFiles 
            Caption         =   "Nomenklatur aus Begleitdokumenten als Dateiname verwenden (umbenennen oder kopieren)"
            Height          =   255
            Left            =   240
            TabIndex        =   37
            Top             =   240
            Width           =   7095
         End
         Begin VB.CheckBox cbCompress 
            Caption         =   "Komprimieren"
            Height          =   255
            Left            =   240
            TabIndex        =   36
            Top             =   2040
            Width           =   2055
         End
         Begin VB.CheckBox cbConvert 
            Caption         =   "Dateien in TIF-Bildformat konvertieren"
            Height          =   255
            Left            =   240
            TabIndex        =   26
            Top             =   600
            Width           =   3735
         End
         Begin VB.CheckBox cbReduceColor 
            Caption         =   "Farbreduktion"
            Height          =   255
            Left            =   240
            TabIndex        =   25
            Top             =   1320
            Width           =   1815
         End
         Begin VB.CheckBox cbRotate 
            Caption         =   "Drehen"
            Height          =   255
            Left            =   240
            TabIndex        =   24
            Top             =   960
            Width           =   1815
         End
         Begin VB.CheckBox cbReduceSize 
            Caption         =   "Auflösungsstufen berechnen"
            Height          =   255
            Left            =   240
            TabIndex        =   23
            Top             =   1680
            Width           =   2535
         End
         Begin VB.TextBox strHistFile 
            Height          =   285
            Left            =   2880
            TabIndex        =   22
            Top             =   1320
            Width           =   4095
         End
         Begin VB.CommandButton Command1 
            Caption         =   "..."
            Height          =   255
            Left            =   6960
            TabIndex        =   21
            Top             =   1320
            Width           =   375
         End
         Begin VB.Label Label8 
            Caption         =   "Hist-Datei"
            Height          =   255
            Left            =   2040
            TabIndex        =   27
            Top             =   1320
            Width           =   855
         End
      End
      Begin VB.CommandButton K_SelectDestinationDir 
         Caption         =   "..."
         Height          =   255
         Left            =   -70200
         TabIndex        =   19
         Top             =   3000
         Width           =   375
      End
      Begin VB.TextBox strDestinationDir 
         Height          =   285
         Left            =   -74760
         TabIndex        =   18
         Top             =   3000
         Width           =   4575
      End
      Begin VB.ListBox lboDateien 
         Height          =   2205
         Left            =   240
         MultiSelect     =   2  'Erweitert
         TabIndex        =   16
         Top             =   2520
         Width           =   2535
      End
      Begin VB.TextBox txtInfo 
         BackColor       =   &H8000000B&
         Height          =   4575
         Left            =   3000
         Locked          =   -1  'True
         MultiLine       =   -1  'True
         ScrollBars      =   3  'Beides
         TabIndex        =   15
         Top             =   360
         Width           =   4935
      End
      Begin VB.ListBox lboLayer 
         Height          =   1815
         Left            =   240
         MultiSelect     =   2  'Erweitert
         TabIndex        =   14
         Top             =   360
         Width           =   2535
      End
      Begin VB.TextBox strSourceDir 
         Height          =   285
         Left            =   -73320
         TabIndex        =   11
         Top             =   240
         Width           =   6015
      End
      Begin VB.CommandButton K_SelectSourceDir 
         Caption         =   "..."
         Height          =   255
         Left            =   -67320
         TabIndex        =   10
         Top             =   240
         Width           =   375
      End
      Begin VB.CheckBox cbRecursiv 
         Caption         =   "einschließlich Unterverzeichnisse"
         Height          =   255
         Left            =   -73320
         TabIndex        =   9
         Top             =   600
         Width           =   3855
      End
      Begin VB.ComboBox cboKartentyp 
         Height          =   315
         Left            =   -73320
         TabIndex        =   7
         Top             =   1920
         Width           =   3975
      End
      Begin VB.ComboBox cboBildformat 
         Height          =   315
         Left            =   -73320
         TabIndex        =   5
         Top             =   1410
         Width           =   3975
      End
      Begin VB.ComboBox cboGrundkonfiguration 
         Height          =   315
         Left            =   -73320
         TabIndex        =   3
         Top             =   930
         Width           =   3975
      End
      Begin MSComDlg.CommonDialog DlgCommon 
         Left            =   -67320
         Top             =   3360
         _ExtentX        =   847
         _ExtentY        =   847
         _Version        =   393216
      End
      Begin VB.Label Label3 
         Caption         =   "Maßstab"
         Height          =   375
         Left            =   -74760
         TabIndex        =   39
         Top             =   2400
         Width           =   1095
      End
      Begin VB.Label Label2 
         Caption         =   "Eigenschaften"
         Height          =   255
         Left            =   3000
         TabIndex        =   30
         Top             =   120
         Width           =   1215
      End
      Begin VB.Label lblDateien 
         Caption         =   "Dateien"
         Height          =   255
         Left            =   240
         TabIndex        =   29
         Top             =   2280
         Width           =   975
      End
      Begin VB.Label Label7 
         Caption         =   "Ausgabeverzeichnis"
         Height          =   255
         Left            =   -74760
         TabIndex        =   28
         Top             =   2760
         Width           =   1575
      End
      Begin VB.Label lblLayer 
         Caption         =   "Dateien"
         Height          =   255
         Left            =   240
         TabIndex        =   17
         Top             =   120
         Width           =   975
      End
      Begin VB.Label Label6 
         Caption         =   "Kartenverzeichnis"
         Height          =   255
         Left            =   -74760
         TabIndex        =   12
         Top             =   210
         Width           =   1335
      End
      Begin VB.Label Label5 
         Caption         =   "Kartentyp"
         Height          =   375
         Left            =   -74760
         TabIndex        =   8
         Top             =   1890
         Width           =   1095
      End
      Begin VB.Label Label1 
         Caption         =   "Bildformat"
         Height          =   375
         Left            =   -74760
         TabIndex        =   6
         Top             =   1410
         Width           =   1335
      End
      Begin VB.Label Label4 
         Caption         =   "Grundkonfiguration"
         Height          =   375
         Left            =   -74760
         TabIndex        =   4
         Top             =   930
         Width           =   1575
      End
   End
   Begin MSComctlLib.StatusBar StatusBar 
      Align           =   2  'Unten ausrichten
      Height          =   270
      Left            =   0
      TabIndex        =   13
      Top             =   5895
      Width           =   8385
      _ExtentX        =   14790
      _ExtentY        =   476
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   14288
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private gstrWorkDir As String
Private gstrSourceDir As String
Private gstrDestinationDir As String

' KK000704 _ Nomenklatur retten / Protokolldatei / Layer-Info
Private gstrNomenklatur As String
Private gstrLayer As String

Private gstrProtocollDir As String      ' Dir Protokoll.txt
Private gstrProtocollFile As String     ' ...\Protokoll.txt
Private gstrErrorFile As String         ' ....\error.txt
Private gstrTempDir As String           ' Temp-Dir

Private xFile As Long                   ' für Protokoll.txt


Private Declare Function GetTempPath Lib "kernel32" Alias "GetTempPathA" _
        (ByVal nBufferLength As Long, ByVal lpBuffer As String) As Long

Private Sub MakeDir(ByVal strDir As String)
On Error Resume Next
    Dim strTestDir As String
    Dim strCurDir As String
    Dim Pos As Integer
' sicherstellen, daß Zielverzeichnis existiert
    strCurDir = CurDir()
    strTestDir = ""
    Pos = InStr(strDir, "\")
    Do While Pos > 0
        strTestDir = strTestDir & Left(strDir, Pos)
        strDir = Mid(strDir, Pos + 1)
        ChDir strTestDir
        If Err Then
            MkDir strTestDir
            ChDir strTestDir
        End If
        Pos = InStr(strDir, "\")
    Loop
    ChDir strCurDir
End Sub
Private Sub Load_CheckBox(cb As CheckBox, strKey As String)
    Dim strBuffer As String * 255
    Dim strCnt As String
    Dim lCnt As Long
    Dim result As Long
    Dim strCfg As String
    Dim strDefault As String
    
    result = GetPrivateProfileString(ByVal Me.cboGrundkonfiguration, _
            ByVal "X" & strKey, ByVal "?nein", strBuffer, Len(strBuffer), App.Path & "\MapWizard.ini")
    If result > 0 Then
        If Left(strBuffer, 1) = "?" Then
            cb.Enabled = True
        End If
        If Mid(strBuffer, 2, 1) = "j" Then
            cb.Value = 1
        End If
    End If
    
End Sub

Private Sub Load_ComboBox(cbo As ComboBox, strKey As String, strSubkey As String)
    Dim strBuffer As String * 255
    Dim strCnt As String
    Dim lCnt As Long
    Dim result As Long
    Dim strCfg As String
    Dim strDefault As String
    
    cbo.Clear
    
    If Len(strKey) = 0 Then
        Exit Sub
    End If
    result = GetPrivateProfileString(ByVal strKey, _
            ByVal "Default", ByVal "", strBuffer, Len(strBuffer), App.Path & "\MapWizard.ini")
    If result > 0 Then
        strDefault = Left(strBuffer, InStr(strBuffer, Chr$(0)) - 1)
    End If
    
    lCnt = 0
    Do
        lCnt = lCnt + 1
        strCnt = strSubkey & Trim(Str(lCnt))
        result = GetPrivateProfileString(ByVal strKey, _
                ByVal strCnt, ByVal "", strBuffer, Len(strBuffer), App.Path & "\MapWizard.ini")
        If result = 0 Then
            Exit Do
        End If
        strCfg = Left(strBuffer, InStr(strBuffer, Chr$(0)) - 1)
        cbo.AddItem strCfg
        If strDefault = strCfg Then
            cbo.ListIndex = cbo.ListCount - 1
        End If
    Loop
        

End Sub

Private Sub Load_ListBox(lbo As ListBox, strKey As String, strSubkey As String)
    Dim strBuffer As String * 255
    Dim strCnt As String
    Dim lCnt As Long
    Dim result As Long
    Dim strCfg As String
    
    lbo.Clear
    
    lCnt = 0
    Do
        lCnt = lCnt + 1
        strCnt = strSubkey & Trim(Str(lCnt))
        result = GetPrivateProfileString(ByVal strKey, _
                ByVal strCnt, ByVal "", strBuffer, Len(strBuffer), App.Path & "\MapWizard.ini")
        If result = 0 Then
            Exit Do
        End If
        strCfg = Left(strBuffer, InStr(strBuffer, Chr$(0)) - 1)
        lbo.AddItem strCfg
    Loop
End Sub


Private Sub cbCompress_Click()
    
    If Me.cbCompress Then
        Protocoll (" *** Komprimieren Ein")
    Else
        Protocoll (" *** Komprimieren Aus")
    End If
    
End Sub

Private Sub cbConvert_Click()
' KK000705
   If Me.cbReduceSize Then
        Protocoll (" *** Dateien in TIF-Bildformat konvertieren EIN ")
   Else
        Protocoll (" *** Dateien in TIF-Bildformat konvertieren AUS ")
   End If
        
  End Sub

Private Sub cboKartentyp_Change()
    Load_ComboBox Me.cboMaszstab, Me.cboKartentyp, "M"
    If Me.cboMaszstab.ListCount > 0 Then
        Me.cboMaszstab.Enabled = True
    Else
        Me.cboMaszstab.Enabled = False
    End If
End Sub

Private Sub cboKartentyp_Click()
    cboKartentyp_Change
End Sub

Private Sub cbRecursiv_Click()
    strSourceDir_Change
End Sub

Private Sub cbReduceColor_Click()
' KK000705
        If Me.cbReduceSize Then
            Protocoll (" *** Farbreduktion EIN ")
        Else
            Protocoll (" *** Farbreduktion AUS ")
        End If

End Sub

Private Sub cbReduceSize_Click()
' KK000705
        If Me.cbReduceSize Then
            Protocoll (" *** Auflösungsstufe berechnen EIN ")
        Else
             Protocoll (" *** Auflösungsstufe berechnen AUS ")
        End If
        
End Sub

Private Sub cbRenameFiles_Click()
' KK000704
' kein ausblenden !!!
'    If Me.cbRenameFiles Then
'        Me.cbCompress.Enabled = False
'        Me.cbCompress = 0
'        Me.cbConvert.Enabled = False
'        Me.cbConvert = 0
'        Me.cbReduceColor.Enabled = False
'        Me.cbReduceColor = 0
'        Me.cbReduceSize.Enabled = False
'        Me.cbReduceSize = 0
'        Me.cbRotate.Enabled = False
'        Me.cbRotate = 0
'    Else
        Me.cbCompress.Enabled = True
        Me.cbConvert.Enabled = True
        Me.cbReduceColor.Enabled = True
        Me.cbReduceSize.Enabled = True
        Me.cbRotate.Enabled = True
        
        If Me.cbRenameFiles Then
            Protocoll (" *** Nomenklatur aus Begleitdokumenten als Namen verwenden EIN")
        Else
            Protocoll (" *** Nomenklatur aus Begleitdokumenten als Namen verwenden AUS")
        End If
        
'    End If
End Sub

Private Sub cbRotate_Click()
' KK000705
        If Me.cbRotate Then
            Protocoll (" *** Drehen EIN")
        Else
            Protocoll (" *** Drehen AUS")
        End If

End Sub

Private Sub cbStoreCmd_Click()
' KK000705
        If Me.cbStoreCmd Then
            Protocoll (" *** MapWizard.bat - Datei erstellen EIN")
' gilt nur für Drehen und Doc-Datei
            Me.cbCompress.Enabled = False
            Me.cbCompress = 0
            Me.cbReduceSize.Enabled = False
            Me.cbReduceSize = 0
        Else
            Protocoll (" *** MapWizard.bat - Datei erstellen AUS")
            Me.cbCompress.Enabled = True
            Me.cbReduceSize.Enabled = True
       End If

End Sub

Private Sub Command1_Click()
On Error Resume Next
    DlgCommon.CancelError = True
    DlgCommon.DialogTitle = "Hist-Datei festlegen"
    DlgCommon.InitDir = App.Path
    DlgCommon.DefaultExt = "*.mif"
    DlgCommon.Filter = "Hist-Dateien (*.mif)|*.mif"
    DlgCommon.FileName = "Standard.mif"
    DlgCommon.Flags = cdlOFNCreatePrompt Or cdlOFNHideReadOnly
    DlgCommon.ShowOpen
    If Err = 32755 Then 'Abbrechen gedrückt
        Exit Sub
    ElseIf Err = 0 Then
        Me.strHistFile = DlgCommon.FileName
    Else
        MsgBox Err.Description
    End If

End Sub

Private Sub Form_Load()
Dim ix As Integer
' KK000704
    gstrNomenklatur = ""
    gstrLayer = ""
    
   
    Me.K_Navigate(0).Caption = "<< Zurück"
    Me.K_Navigate(1).Caption = "Weiter >>"
    For ix = 0 To Me.tabPages.Tabs - 1
        Me.tabPages.Tab = ix
        Me.tabPages.Caption = ""
    Next ix
    Me.tabPages.TabHeight = 1
    Me.tabPages.Tab = 0
    Load_ComboBox Me.cboGrundkonfiguration, "Grundkonfigurationen", ""
    Load_ComboBox Me.cboBildformat, "Bildformate", ""
    Load_ComboBox Me.cboKartentyp, "Kartentypen", ""
    Me.strHistFile = App.Path & "\Standard.mif"

Dim strTemp As String
On Error Resume Next
    Me.strSourceDir = GetSetting("TRiAS-MapWizard", "Common", "Directory")
    If "yes" = GetSetting("TRiAS-MapWizard", "Common", "recursiv") Then
        Me.cbRecursiv = 1
    Else
        Me.cbRecursiv = 0
    End If
    strSourceDir_Change
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Me.tabPages.TabHeight = 100

End Sub

Private Function CalculateRotation(R() As Double, H() As Double) As Double
    Dim a As Double
    Dim b As Double
    Dim c As Double
    Dim w(1 To 4) As Double
    
    b = R(4) - R(1)
    a = H(4) - H(1)
    w(1) = Atn(b / a) * 180 / 3.141592
    b = H(1) - H(2)
    a = R(2) - R(1)
    w(2) = Atn(b / a) * 180 / 3.141592
    b = R(3) - R(2)
    a = H(3) - H(2)
    w(3) = Atn(b / a) * 180 / 3.141592
    b = H(4) - H(3)
    a = R(3) - R(4)
    w(4) = Atn(b / a) * 180 / 3.141592
    CalculateRotation = (w(1) + w(2) + w(3) + w(4)) / 4
End Function
Private Function Umlaut(strStr As String) As Boolean
    Dim i, j As Long
    i = Len(strStr)
    Umlaut = False
    For j = 0 To i - 1
        If Mid(strStr, j + 1, 1) = "Ü" Or _
            Mid(strStr, j + 1, 1) = "ü" Or _
            Mid(strStr, j + 1, 1) = "Ä" Or _
            Mid(strStr, j + 1, 1) = "ä" Or _
            Mid(strStr, j + 1, 1) = "Ö" Or _
            Mid(strStr, j + 1, 1) = "ö" Or _
            Mid(strStr, j + 1, 1) = "ß" Then
                Umlaut = True
                Exit Function
        End If
    Next j
End Function
Sub DoCmd(strCmd As String, tStoreCmd As Boolean)
On Error GoTo Err_DoCmd
    Dim hFile As Long
    Dim strTestDir As String
    Dim strErr As String
    
    If Umlaut(strCmd) Then
        MsgBox "Umlaute in der Kommandozeile - Abbruch !!!", , "DoCmd"
        Protocoll ("DoCmd-Fehler - Umlaute in der Kommandozeile")
        WizardUnload
    End If
    strErr = "if errorlevel 1 echo Fehler"

    If tStoreCmd Then
        hFile = FreeFile
        If InStr(Me.strDestinationFile, ":") > 0 Then
            Open Me.strDestinationFile For Append As hFile
        Else
            Open Me.strDestinationDir & Me.strDestinationFile For Append As hFile
        End If
        Print #hFile, strCmd
        Close hFile
    Else
        hFile = FreeFile
        
        
        Open App.Path & "\DoCmd.wait" For Output As hFile
        Close hFile
        hFile = FreeFile
        Open App.Path & "\DoCmd.bat" For Output As hFile
        Print #hFile, strCmd
        Print #hFile, strErr
        Print #hFile, "del """ & App.Path & "\DoCmd.wait"""
        Close hFile
        
        Protocoll (strCmd)
        Protocoll (strErr)
        
        Dim strDel As String
        strDel = "del """ & App.Path & "\DoCmd.wait"""
        
        Protocoll (strDel)
        
    ' KK 000522
        Dim Ergebnis As Double
 '       Ergebnis = Shell("""" & App.Path & "\DoCmd.bat""", vbNormalFocus)
         Ergebnis = Shell("""" & App.Path & "\DoCmd.bat""", vbMinimizedNoFocus)
        If 0 = Ergebnis Then
            Exit Sub
        End If
        Do
            strTestDir = Dir(App.Path & "\DoCmd.wait")
            If Len(strTestDir) = 0 Then
                Exit Do
            End If
            DoEvents
        Loop
    End If
Exit Sub

Err_DoCmd:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "DoCmd"
    Protocoll ("DoCmd-Fehler" & Str(Err.Number) & ": " & Err.Description)
'    Resume Next
'    Unload Me
    WizardUnload
End Sub
Sub WizardUnload()

    Dim strDel As String
    strDel = "del """ & gstrTempDir & "~im*.tmp"""
    DoCmd strDel, Me.cbStoreCmd
    Unload Me
End Sub
Sub DoRenameFiles(strInDir As String, strFile As String, strOutDir As String)
On Error GoTo Err_DoRotate
    Dim strInFile As String
    Dim strLayer As String
    Dim strOutFile As String
    Dim strDocInFile As String
    Dim strDocOutFile As String
    Dim strDocInfo As String
    Dim strNomenklatur As String
    Dim strTemp As String
    Dim R(1 To 6) As Double
    Dim H(1 To 6) As Double
    Dim Pos As Integer
    
    strInFile = strInDir & strFile
    strLayer = Layer(strFile)
    strOutFile = gstrDestinationDir & Path(strFile)
    strDocInFile = Mid(strInFile, 1, Len(strInFile) - Len(Me.cboBildformat)) & "doc"
    strDocOutFile = Mid(strInFile, 1, Len(strInFile) - Len(Me.cboBildformat)) & "doc"
    strDocInfo = Read_DocInfo(strInFile, R, H)
    If Len(strDocInfo) > 0 Then
        Pos = InStr(strDocInfo, " ")
    ' KK000713 - Großbuchstaben
        If IsNumeric(Left(strDocInfo, 1)) Then
            strTemp = Trim(Mid(strDocInfo, 1, Pos - 1))
        Else
            strTemp = UCase(Left(strDocInfo, 1))
'        strTemp = Trim(Mid(strDocInfo, 1, pos - 1))
            strTemp = strTemp + Trim(Mid(strDocInfo, 2, Pos - 2))
        End If
    ' ===========================================================
        strNomenklatur = Mid(strTemp, 1, 1) _
                        & "-" & Mid(strTemp, 2, 2) & "-"
        strTemp = Mid(strTemp, 4)
        Do While IsNumeric(Left(strTemp, 1))
            strNomenklatur = strNomenklatur & Left(strTemp, 1)
            strTemp = Mid(strTemp, 2)
        Loop
    ' KK000713 - Großbuchstaben
        If True <> IsNumeric(Left(strTemp, 1)) Then
            Dim strRef As String
            strRef = UCase(Left(strTemp, 1))
            strTemp = strRef + Mid(strTemp, 2, Len(strTemp) - 1)
        End If
        
    ' ============================================================
        strNomenklatur = strNomenklatur _
                        & "-" & Mid(strTemp, 1, 1) _
                        & "-" & Mid(strTemp, 2, 1) _
                        & "-" & Mid(strTemp, 3, 1)
                        
' KK000704 - Nomenklatur sichern
        gstrNomenklatur = "<" & strNomenklatur & ">"
        gstrLayer = strLayer
'        gstrNomenklatur = strNomenklatur
        
        strOutFile = strOutFile & strNomenklatur & strLayer & "." & Me.cboBildformat
        strDocOutFile = Mid(strOutFile, 1, Len(strOutFile) - Len(Me.cboBildformat)) & "doc"
        If gstrSourceDir <> gstrDestinationDir Then
           If Me.cbStoreCmd Then
                 DoCmd "copy """ & strDocInFile & """ """ & strDocOutFile & """", Me.cbStoreCmd
                 DoCmd "copy """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
           Else
                If FileLen(strDocInFile) Then
                     DoCmd "copy """ & strDocInFile & """ """ & strDocOutFile & """", Me.cbStoreCmd
                Else
                    Protocoll (" ERROR : File " & strDocInFile & " existiert nicht !!!")
            '    Unload Me
                    WizardUnload
                End If
            
                If FileLen(strInFile) Then
                    DoCmd "copy """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
                Else
                    Protocoll (" ERROR : File " & strInFile & " existiert nicht !!!")
             '   Unload Me
                    WizardUnload
                End If
            End If
            
        Else
            If Me.cbStoreCmd Then
                DoCmd "rename """ & strDocInFile & """ """ & strDocOutFile & """", Me.cbStoreCmd
                DoCmd "rename """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
            Else
                If FileLen(strDocInFile) Then
                    DoCmd "rename """ & strDocInFile & """ """ & strDocOutFile & """", Me.cbStoreCmd
                Else
                    Protocoll (" ERROR : File " & strDocInFile & " existiert nicht !!!")
            '    Unload Me
                    WizardUnload
                End If
                
                If FileLen(strInFile) Then
                    DoCmd "rename """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
                Else
                    Protocoll (" ERROR : File " & strInFile & " existiert nicht !!!")
            '    Unload Me
                    WizardUnload

                End If
            End If
        End If
    End If
Exit Sub

Err_DoRotate:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "DoRotate"
    Resume Next
End Sub
Sub MakeRenameFiles(ByVal strInDir As String, ByVal strSourceFile As String, ByRef strOutDir As String)
On Error GoTo Err_MakeRenameFiles
    Dim ix As Integer
    Dim strFileName As String
    Dim strTestDir As String
    Dim Pos As Integer
    
    strOutDir = gstrDestinationDir & Path(strSourceFile)
    
    If Right(strSourceFile, 1) = ">" Then
        For ix = 0 To Me.lboLayer.ListCount - 1
            If Me.lboLayer.Selected(ix) Then
                strFileName = strSourceFile
                Pos = InStr(strFileName, "<")
                strFileName = Left(strFileName, Pos - 1) _
                    & Mid(strFileName, Pos + 1, Len(strFileName) - Pos - 1) _
                    & Left(Me.lboLayer.List(ix), InStr(Me.lboLayer.List(ix), ";") - 1) _
                    & "." & Me.cboBildformat
'                strTestDir = Dir(strInDir & File(strFileName))
                strTestDir = Dir(gstrSourceDir & strFileName)
                If Len(strTestDir) > 0 Then
                    DoRenameFiles strInDir, strFileName, strOutDir
                End If
            End If
        Next ix
    Else
        DoRenameFiles strInDir, strSourceFile, strOutDir
    End If
Exit Sub

Err_MakeRenameFiles:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "MakeRenameFiles"
    Resume Next
End Sub

Sub DoRotate(dblRotation As Double, strInDir As String, strFile As String, strOutDir As String)
On Error GoTo Err_DoRotate
    Dim strInFile As String
    Dim strOutFile As String
    Dim strMapInfo As String
    Dim strRotation As String
    Dim Pos1 As Integer
    Dim Pos2 As Integer
    Dim ix As Integer
    
    If strInDir <> gstrSourceDir Then
        strInFile = strInDir & File(strFile)
    Else
        strInFile = strInDir & strFile
    End If
    
    If strOutDir <> gstrDestinationDir Then
        strOutFile = strOutDir & File(strFile)
    Else
' KK000713
'        strOutFile = strOutDir & strFile
        If strOutDir <> strInDir Then
           strOutFile = strOutDir & strFile
        Else
            strOutDir = gstrWorkDir
            strOutFile = gstrWorkDir & strFile
        End If
   End If
    
 ' KK000705
    strMapInfo = Read_MapInfo(strInDir & strFile)
    
'    strMapInfo = Read_MapInfo(gstrSourceDir & strFile)
    Pos1 = InStr(strMapInfo, Chr(10) & "277")
    For ix = 1 To 5
        Pos1 = InStr(Pos1 + 1, strMapInfo, Chr(9))
    Next ix
    Pos2 = InStr(Pos1 + 1, strMapInfo, Chr(10))
    ix = Val(Mid(strMapInfo, Pos1 + 1, Pos2 - Pos1))
'   # 277 => Samples per Pixel => 3 => RGB
    
    strRotation = Format(dblRotation)
    Pos1 = InStr(strRotation, ",")
    If Pos1 > 0 Then
        Mid(strRotation, Pos1, 1) = "."
    End If
    If ix = 3 Then
        If Me.cbStoreCmd Then
            DoCmd """" & App.Path & "\imrotate"" -rotate " & strRotation & " -outcompress ccitt4 """ & strInFile & """ """ & strOutFile & """ 2> """ & gstrErrorFile, Me.cbStoreCmd
            DoCmdError
        Else
            If FileLen(strInFile) Then
                DoCmd """" & App.Path & "\imrotate"" -rotate " & strRotation & " -outcompress ccitt4 """ & strInFile & """ """ & strOutFile & """ 2> """ & gstrErrorFile, Me.cbStoreCmd
                DoCmdError
            Else
                Protocoll (" ERROR : File " & strInFile & " existiert nicht !!!")
        '    Unload Me
                WizardUnload

            End If
        End If
        
    Else
        If Me.cbStoreCmd Then
           DoCmd """" & App.Path & "\imrotate"" -rotate " & strRotation & " -outcompress ccitt4 -outchandepth 1 -outnchan 1 " & " """ & strInFile & """ """ & strOutFile & """ 2> """ & gstrErrorFile, Me.cbStoreCmd
           DoCmdError
        Else
            If FileLen(strInFile) Then
               DoCmd """" & App.Path & "\imrotate"" -rotate " & strRotation & " -outcompress ccitt4 -outchandepth 1 -outnchan 1 " & " """ & strInFile & """ """ & strOutFile & """ 2> """ & gstrErrorFile, Me.cbStoreCmd
               DoCmdError
            Else
                Protocoll (" ERROR : File " & strInFile & " existiert nicht !!!")
        '    Unload Me
                WizardUnload
            End If
        End If
            
    End If
    
    If Not Me.cbRetainTempFiles And strInDir <> gstrSourceDir Then
        DoCmd "del """ & strInFile & """", Me.cbStoreCmd
    End If
    
    If strOutDir = gstrWorkDir Then
        DoCmd "copy """ & strOutFile & """ """ & strInFile & """", Me.cbStoreCmd
    End If
   
Exit Sub

Err_DoRotate:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "DoRotate"
    Resume Next
End Sub
Private Sub DoCmdError()
    If FileLen(gstrErrorFile) Then
        Protocoll (" *** ERROR : Bearbeitungsfehler siehe " & gstrErrorFile)
        WizardUnload
    End If

End Sub
Private Sub MakeRotate(ByVal strInDir As String, ByVal strSourceFile As String, ByRef strOutDir As String)
On Error GoTo Err_MakeRotate
    Dim strFileName As String
    Dim strTestDir As String
    Dim strDocInfo As String
    Dim Pos As Integer
    Dim ix As Integer
    Dim dblaR(1 To 6) As Double
    Dim dblaH(1 To 6) As Double
    Dim dblRotation As Double
    Dim lFileCnt As Long
    
    If Me.cbReduceSize Then
        strOutDir = gstrWorkDir & "Rotate\"
        MakeDir strOutDir
    Else
        strOutDir = gstrDestinationDir & Path(strSourceFile)
    End If
    
    If Right(strSourceFile, 1) = ">" Then
        dblRotation = 0
        If Read_GeoRef(gstrSourceDir & strSourceFile, dblaR, dblaH) Then
            dblRotation = CalculateRotation(dblaR, dblaH)
        Else
            For ix = 0 To Me.lboLayer.ListCount - 1
                If Me.lboLayer.Selected(ix) Then
                    strFileName = strSourceFile
                    
                 ' KK000704 - Nomenklatur ???
                    If Len(gstrNomenklatur) > 0 Then
                        strFileName = gstrNomenklatur
                    End If
                    
                    Pos = InStr(strFileName, "<")
                    
                    If (Pos) Then
                        strFileName = Left(strFileName, Pos - 1) _
                         & Mid(strFileName, Pos + 1, Len(strFileName) - Pos - 1) _
                         & Left(Me.lboLayer.List(ix), InStr(Me.lboLayer.List(ix), ";") - 1) _
                         & "." & Me.cboBildformat
                    Else
                        strFileName = strFileName _
                         & Left(Me.lboLayer.List(ix), InStr(Me.lboLayer.List(ix), ";") - 1) _
                         & "." & Me.cboBildformat
                    End If
                   
                    
                    strTestDir = Dir(strInDir & strFileName)
                    
                    If Len(strTestDir) > 0 Then
                        lFileCnt = lFileCnt + 1
                        If Not Read_GeoRef(gstrSourceDir & strFileName, dblaR, dblaH) Then
                            strDocInfo = Read_DocInfo(gstrSourceDir & strFileName, dblaR, dblaH)
                        End If
                        If Len(strDocInfo) > 0 Then
                            dblRotation = dblRotation + CalculateRotation(dblaR, dblaH)
                        Else
                            dblRotation = 0
                        End If
                    End If
                End If
            Next ix
        End If
        If lFileCnt > 0 Then
            dblRotation = dblRotation / lFileCnt
        End If
        For ix = 0 To Me.lboLayer.ListCount - 1
            If Me.lboLayer.Selected(ix) Then
                strFileName = strSourceFile
                
                ' KK000704 - Nomenklatur ???
                If Len(gstrNomenklatur) > 0 Then
                    strFileName = gstrNomenklatur
                End If
                
                Pos = InStr(strFileName, "<")
                
                If (Pos) Then
                    strFileName = Left(strFileName, Pos - 1) _
                     & Mid(strFileName, Pos + 1, Len(strFileName) - Pos - 1) _
                     & Left(Me.lboLayer.List(ix), InStr(Me.lboLayer.List(ix), ";") - 1) _
                     & "." & Me.cboBildformat
                Else
                     strFileName = strFileName _
                       & Left(Me.lboLayer.List(ix), InStr(Me.lboLayer.List(ix), ";") - 1) _
                       & "." & Me.cboBildformat
                End If

                
'                strTestDir = Dir(strInDir & File(strFileName))
                strTestDir = Dir(gstrSourceDir & strFileName)
                If Len(strTestDir) > 0 Then
                    DoRotate dblRotation, strInDir, strFileName, strOutDir
                End If
            End If
        Next ix
    Else
' KK000705
        Read_DocInfo strInDir & strSourceFile, dblaR, dblaH
'        Read_DocInfo gstrSourceDir & strSourceFile, dblaR, dblaH
        dblRotation = CalculateRotation(dblaR, dblaH)
       ' KK000704 - Nomenklatur ??? - Layer fehlt ???
        If Len(gstrNomenklatur) > 0 Then
                Pos = InStr(gstrNomenklatur, "<")
                If Pos Then
                    strSourceFile = Left(gstrNomenklatur, Pos - 1) _
                     & Mid(gstrNomenklatur, Pos + 1, Len(gstrNomenklatur) - Pos - 1) _
                     & gstrLayer _
                     & "." & Me.cboBildformat
                Else
                     strSourceFile = gstrNomenklatur _
                       & gstrLayer _
                       & "." & Me.cboBildformat
                End If
        End If
       
        DoRotate dblRotation, strInDir, strSourceFile, strOutDir
        
    End If
Exit Sub

Err_MakeRotate:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "MakeRotate"
    Resume Next
End Sub
Function MapInfoLog(strMapInfo As String, strCode As String) As Integer
    Dim Pos1 As Integer
    Dim pos22 As Integer
    Dim Pos2 As Integer
    MapInfoLog = -1
    
    If "" = strMapInfo Then
        Exit Function
    End If
    If "" = strCode Then
        Exit Function
    End If
    
    Pos1 = InStr(strMapInfo, Chr(10) & strCode)
    If 0 = Pos1 Then
        Pos1 = InStr(strMapInfo, Chr(13) & strCode)
    End If
    If 0 = Pos1 Then
         MsgBox "Fehler in MapInfo.log : Code " & strCode & " nicht auffindbar !!!"
        Exit Function
    End If
    Dim ix As Integer
    For ix = 1 To 5
        Pos1 = InStr(Pos1 + 1, strMapInfo, Chr(9))
    Next ix
    Pos2 = InStr(Pos1 + 1, strMapInfo, Chr(10))
    
    pos22 = InStr(Pos1 + 1, strMapInfo, Chr(9))
    If pos22 > Pos1 And pos22 < Pos2 Then
        Pos2 = pos22
    End If
'-----------
    
    ix = Val(Mid(strMapInfo, Pos1 + 1, Pos2 - Pos1))
    
    MapInfoLog = ix
    
End Function
Sub DoReduceColor(strInDir As String, strFile As String, strOutDir As String)
On Error GoTo Err_DoReduceColor
    Dim strInFile As String
    Dim strOutFile As String
    Dim strMapInfo As String
    Dim Pos1 As Integer
    Dim Pos2 As Integer
    Dim ix As Integer
    
    If strInDir <> gstrSourceDir Then
        strInFile = strInDir & File(strFile)
    Else
        strInFile = strInDir & strFile
    End If
    If strOutDir <> gstrDestinationDir Then
        strOutFile = strOutDir & File(strFile)
    Else
        strOutFile = strOutDir & strFile
    End If
    
' KK000712
    strMapInfo = ""
    
    strMapInfo = Read_MapInfo(gstrSourceDir & strFile)
    If "" = strMapInfo Then
 '           Protocoll (" ==========> ERROR : File " & gstrSourceDir & strFile & " existiert nicht !!!")
    '        Unload Me
            WizardUnload
    End If
    
' KK 000523 - Hier lieber eine eine Funktion

'    pos1 = InStr(strMapInfo, Chr(10) & "277")
'    For ix = 1 To 5
'        pos1 = InStr(pos1 + 1, strMapInfo, Chr(9))
'    Next ix
'    pos2 = InStr(pos1 + 1, strMapInfo, Chr(10))
'    ix = Val(Mid(strMapInfo, pos1 + 1, pos2 - pos1))
'   # 277 => Samples per Pixel => 3 => RGB

    ix = MapInfoLog(strMapInfo, "277")
    
    If ix = 3 Then
        If Me.cbStoreCmd Then
            DoCmd """" & App.Path & "\MapRColor"" -p 4 -h """ & Me.strHistFile & """ """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
        Else
            If FileLen(strInFile) Then
                DoCmd """" & App.Path & "\MapRColor"" -p 4 -h """ & Me.strHistFile & """ """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
            Else
                Protocoll (" ERROR : File " & strInFile & " existiert nicht !!!")
        '    Unload Me
                WizardUnload
            End If
        End If
   Else
        If Me.cbStoreCmd Then
            DoCmd "copy """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
        Else
            If FileLen(strInFile) Then
                DoCmd "copy """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
            Else
                Protocoll (" ERROR : File " & strInFile & " existiert nicht !!!")
        '    Unload Me
                WizardUnload
            End If
        End If
    End If
    If Not Me.cbRetainTempFiles And strInDir <> gstrSourceDir Then
        DoCmd "del """ & strInFile & """", Me.cbStoreCmd
    End If
Exit Sub

Err_DoReduceColor:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "DoReduceColor"
    Resume Next
End Sub

Sub MakeReduceColor(ByVal strInDir As String, ByVal strSourceFile As String, ByRef strOutDir As String)
On Error GoTo Err_MakeReduceColor
    Dim ix As Integer
    Dim strFileName As String
    Dim strTestDir As String
    Dim Pos As Integer
    
    If Me.cbCompress Or Me.cbReduceSize Then
        strOutDir = gstrWorkDir & "RColor\"
        MakeDir strOutDir
    Else
        strOutDir = gstrDestinationDir & Path(strSourceFile)
    End If
    
    If Right(strSourceFile, 1) = ">" Then
        For ix = 0 To Me.lboLayer.ListCount - 1
            If Me.lboLayer.Selected(ix) Then
                strFileName = strSourceFile
                Pos = InStr(strFileName, "<")
                strFileName = Left(strFileName, Pos - 1) _
                    & Mid(strFileName, Pos + 1, Len(strFileName) - Pos - 1) _
                    & Left(Me.lboLayer.List(ix), InStr(Me.lboLayer.List(ix), ";") - 1) _
                    & "." & Me.cboBildformat
'                strTestDir = Dir(strInDir & File(strFileName))
                strTestDir = Dir(gstrSourceDir & strFileName)
                If Len(strTestDir) > 0 Then
                    DoReduceColor strInDir, strFileName, strOutDir
                End If
            End If
        Next ix
    Else
        DoReduceColor strInDir, strSourceFile, strOutDir
    End If
Exit Sub

Err_MakeReduceColor:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "MakeReduceColor"
    Resume Next
End Sub

Sub DoCompressFile(strInFile As String, strSourceFile As String, strOutFile As String)
On Error GoTo Err_DoCompressFile
    Dim strMapInfo As String
    Dim Pos1 As Integer
    Dim Pos2 As Integer
' KK000522
    Dim pos22 As Integer
    
    Dim ix As Integer
    Dim t258 As Integer
    Dim t277 As Integer
    Dim strCompressor As String
    
    strMapInfo = Read_MapInfo(strSourceFile)
' KK000712
    If "" = strMapInfo Then
'            Protocoll (" ==========> ERROR : File " & strSourceFile & " existiert nicht !!!")
    '        Unload Me
            WizardUnload
    End If
    
'    Pos1 = InStr(strMapInfo, Chr(10) & "258")
    
'    For ix = 1 To 5
'        Pos1 = InStr(Pos1 + 1, strMapInfo, Chr(9))
'    Next ix
    
'    Pos2 = InStr(Pos1 + 1, strMapInfo, Chr(10))
    
'    t258 = Val(Mid(strMapInfo, Pos1 + 1, Pos2 - Pos1))

' KK000523
    t258 = MapInfoLog(strMapInfo, "258")
    
' Nun Code 277

'    Pos1 = InStr(strMapInfo, Chr(10) & "277")
    
'    For ix = 1 To 5
'        Pos1 = InStr(Pos1 + 1, strMapInfo, Chr(9))
'    Next ix
'    Pos2 = InStr(Pos1 + 1, strMapInfo, Chr(10))
'    t277 = Val(Mid(strMapInfo, Pos1 + 1, Pos2 - Pos1))

    t277 = MapInfoLog(strMapInfo, "277")
    
' KK000522
    If 3 = t277 Then
       strCompressor = "packbits"
    Else
        strCompressor = ""
    End If
'------------------------------
    
    If 1 = t277 And 8 = t258 Then
        strCompressor = "packbits"
    ElseIf 1 = t277 And 1 = t258 Then
        strCompressor = "g4"
'    Else
'        strCompressor = ""
    End If
    
   If Len(strCompressor) > 0 Then
        If Me.cbStoreCmd Then
            DoCmd """" & App.Path & "\tiffcp"" -s -r 32 -c " & strCompressor & " """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
        Else
            If FileLen(strInFile) Then
                DoCmd """" & App.Path & "\tiffcp"" -s -r 32 -c " & strCompressor & " """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
            Else
                Protocoll (" ERROR : File " & strInFile & " existiert nicht !!!")
        '    Unload Me
                WizardUnload
            End If
        End If
    Else
        If Me.cbStoreCmd Then
            DoCmd "copy """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
        Else
            If FileLen(strInFile) Then
                DoCmd "copy """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
            Else
                Protocoll (" ERROR : File " & strInFile & " existiert nicht !!!")
        '    Unload Me
                WizardUnload
            End If
        End If
    End If
    
    If Not Me.cbRetainTempFiles Then
        DoCmd "del """ & strInFile & """", Me.cbStoreCmd
    End If
    
Exit Sub

Err_DoCompressFile:
'    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "DoCompressFile"
     Protocoll ("DoCompressFile-Fehler : " & Str(Err.Number) & ": " & Err.Description)
'    Resume Next
'    Unload Me
    WizardUnload
End Sub

Sub DoCompress(strInDir As String, strFile As String, strOutDir As String)
On Error GoTo Err_DoCompress
    Dim strInFile As String
    Dim strOutFile As String
    Dim strMapInfo As String
    Dim Pos1 As Integer
    Dim Pos2 As Integer
    Dim ix As Integer
    Dim t258 As Integer
    Dim t277 As Integer
    Dim strCompressor As String
    
    If strInDir <> gstrSourceDir Then
        strInFile = strInDir & File(strFile)
    Else
        strInFile = strInDir & strFile
    End If
    If strOutDir <> gstrDestinationDir Then
        strOutFile = strOutDir & File(strFile)
    Else
        strOutFile = strOutDir & strFile
    End If
    
    strMapInfo = Read_MapInfo(gstrSourceDir & strFile)
    Pos1 = InStr(strMapInfo, Chr(10) & "258")
    For ix = 1 To 5
        Pos1 = InStr(Pos1 + 1, strMapInfo, Chr(9))
    Next ix
    Pos2 = InStr(Pos1 + 1, strMapInfo, Chr(10))
    t258 = Val(Mid(strMapInfo, Pos1 + 1, Pos2 - Pos1))
    
    Pos1 = InStr(strMapInfo, Chr(10) & "277")
    For ix = 1 To 5
        Pos1 = InStr(Pos1 + 1, strMapInfo, Chr(9))
    Next ix
    Pos2 = InStr(Pos1 + 1, strMapInfo, Chr(10))
    t277 = Val(Mid(strMapInfo, Pos1 + 1, Pos2 - Pos1))
    
    If 1 = t277 And 8 = t258 Then
        strCompressor = "packbits"
    ElseIf 1 = t277 And 1 = t258 Then
        strCompressor = "g4"
    Else
        strCompressor = ""
    End If
    Protocoll (" =============== DoCompress - tiffcp -Variante =================")
    If Len(strCompressor) > 0 Then
        If Me.cbStoreCmd Then
            DoCmd """" & App.Path & "\tiffcp"" -s -r 32 -c " & strCompressor & " """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
        Else
            If FileLen(strInFile) Then
                DoCmd """" & App.Path & "\tiffcp"" -s -r 32 -c " & strCompressor & " """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
            Else
                Protocoll (" ERROR : File " & strInFile & " existiert nicht !!!")
        '    Unload Me
                WizardUnload
            End If
       End If
    Else
       If Me.cbStoreCmd Then
             DoCmd "copy """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
       Else
             If FileLen(strInFile) Then
                 DoCmd "copy """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
             Else
                 Protocoll (" ERROR : File " & strInFile & " existiert nicht !!!")
        '    Unload Me
                 WizardUnload
             End If
        End If
    End If
    
    If Not Me.cbRetainTempFiles And strInDir <> gstrSourceDir Then
        DoCmd "del """ & strInFile & """", Me.cbStoreCmd
    End If
Exit Sub

Err_DoCompress:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "DoCompress"
    Resume Next

End Sub

Sub MakeCompress(ByVal strInDir As String, ByVal strSourceFile As String, ByRef strOutDir As String)
On Error GoTo Err_MakeCompress
    Dim ix As Integer
    Dim strFileName As String
    Dim strTestDir As String
    Dim Pos As Integer
    
    If Me.cbReduceSize Then
        strOutDir = gstrWorkDir & "Compress\"
        MakeDir strOutDir
    Else
        strOutDir = gstrDestinationDir & Path(strSourceFile)
    End If
    
    If Right(strSourceFile, 1) = ">" Then
        For ix = 0 To Me.lboLayer.ListCount - 1
            If Me.lboLayer.Selected(ix) Then
                strFileName = strSourceFile
                
 ' KK000704 - mit Nomenklatur arbeiten !!!!
                If Len(gstrNomenklatur) > 0 Then
                    strFileName = gstrNomenklatur
                End If
                
                Pos = InStr(strFileName, "<")
                If (Pos) Then
                 strFileName = Left(strFileName, Pos - 1) _
                   & Mid(strFileName, Pos + 1, Len(strFileName) - Pos - 1) _
                   & Left(Me.lboLayer.List(ix), InStr(Me.lboLayer.List(ix), ";") - 1) _
                   & "." & Me.cboBildformat
                Else
                 strFileName = strFileName _
                   & Left(Me.lboLayer.List(ix), InStr(Me.lboLayer.List(ix), ";") - 1) _
                   & "." & Me.cboBildformat
                End If


'                strTestDir = Dir(strInDir & File(strFileName))
                strTestDir = Dir(gstrSourceDir & strFileName)
                If Len(strTestDir) > 0 Then
                    DoCompress strInDir, strFileName, strOutDir
                End If
            End If
        Next ix
    Else
 ' KK000704 - mit Nomenklatur arbeiten !!!! - und Layer ????
        Pos = InStr(gstrNomenklatur, "<")
        If Pos Then
             strSourceFile = Left(gstrNomenklatur, Pos - 1) _
             & Mid(gstrNomenklatur, Pos + 1, Len(gstrNomenklatur) - Pos - 1) _
             & gstrLayer _
             & "." & Me.cboBildformat
        Else
             strSourceFile = gstrNomenklatur _
             & gstrLayer _
             & "." & Me.cboBildformat
        End If
        DoReduceSize strInDir, strSourceFile, strOutDir
    End If
Exit Sub

Err_MakeCompress:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "MakeCompress"
    Resume Next
End Sub

Sub DoReduceSize(ByVal strInDir As String, ByVal strFile As String, strOutDir As String)
On Error GoTo Err_DoReduceSize
    Dim strInFile As String
    Dim strOutFile As String
    Dim strTempFile As String
    Dim Pos As Integer
    Dim ix As Integer
    
    If strInDir <> gstrSourceDir Then
        strInFile = strInDir & File(strFile)
    Else
        strInFile = strInDir & strFile
    End If
        
    If strOutDir <> gstrDestinationDir Or Me.cbCompress Then
        strOutFile = strOutDir & File(strFile)
    Else
        strOutFile = strOutDir & strFile
    End If
    
    If Me.cbCompress Then

    Else
        If Me.cbStoreCmd Then
             DoCmd "copy """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
        Else
             If FileLen(strInFile) Then
                DoCmd "copy """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
             Else
                Protocoll (" DoReduceSize - ERROR : File " & strInFile & " existiert nicht !!!")
        '    Unload Me
                WizardUnload
             End If
        End If
        strInFile = strOutFile
    End If
    
    Pos = InStr(strOutFile, ".")
    
    strOutFile = Mid(strOutFile, 1, Pos - 1) & "a" & Mid(strOutFile, Pos)
    
    For ix = Asc("a") To Asc("e")
    
'        If FileLen(strInFile) Then
 '           DoCmd """" & App.Path & "\MapRSize"" -p 4 """ & strInFile & """ """ & strOutFile & """", Me.cbStoreCmd
 '           DoCmd App.Path & "\MapRSize -p 4 " & strInFile & " " & strOutFile, Me.cbStoreCmd
 '       Else
 '           Protocoll (" ERROR : File " & strInFile & " existiert nicht !!!")
 '           Unload Me
 '       End If
        
        If Me.cbCompress Then
            strTempFile = gstrDestinationDir & Path(strFile) & File(strInFile)
' KK000507
           DoCompressFile strInFile, strInFile, strTempFile
'           DoCompressFile strInFile, strInFile, strTempFile
'            DoCompressFile strInFile, gstrSourceDir & strFile, strTempFile
'            DoCompressFile strTempFile, gstrSourceDir & strFile, strOutFile
'            If Not Me.cbRetainTempFiles And strInFile <> strInDir & strFile Then
'                DoCmd "del """ & strInFile & """", Me.cbStoreCmd
'            End If
        End If
        If Me.cbStoreCmd Then
           DoCmd """" & App.Path & "\MapRSize"" -p 4 """ & strTempFile & """ """ & strOutFile & """", Me.cbStoreCmd
        Else
            If FileLen(strTempFile) Then
               DoCmd """" & App.Path & "\MapRSize"" -p 4 """ & strTempFile & """ """ & strOutFile & """", Me.cbStoreCmd
            Else
                Protocoll (" ERROR : File " & strInFile & " existiert nicht !!!")
'            Unload Me
               WizardUnload
            End If
        End If
        
        strInFile = strOutFile
        Pos = InStr(strInFile, ".")
        strOutFile = Mid(strInFile, 1, Pos - 2) & Chr(ix + 1) & Mid(strInFile, Pos)
    Next ix
    
    If Me.cbCompress Then
        strTempFile = gstrDestinationDir & Path(strFile) & File(strInFile)
' KK000710
        DoCompressFile strInFile, strInFile, strTempFile
'        DoCompressFile strInFile, gstrSourceDir & strFile, strTempFile
'        If Not Me.cbRetainTempFiles And strInFile <> strInDir & strFile Then
'            DoCmd "del """ & strInFile & """", Me.cbStoreCmd
'        End If
    End If

Exit Sub

Err_DoReduceSize:
    Resume Next
'    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "DoReduceSize"
    Protocoll ("Fehler:DoReduceSize = " & Str(Err.Number) & ": " & Err.Description)
'    Resume Next
'    Unload Me
    WizardUnload
End Sub

Sub MakeReduceSize(ByVal strInDir As String, ByVal strSourceFile As String, ByRef strOutDir As String)
On Error GoTo Err_MakeReduceSize
    Dim ix As Integer
    Dim strFileName As String
    Dim strTestDir As String
    Dim Pos As Integer
    
    strOutDir = gstrWorkDir & "RSize\"
    MakeDir strOutDir
    
    If Right(strSourceFile, 1) = ">" Then
        For ix = 0 To Me.lboLayer.ListCount - 1
            If Me.lboLayer.Selected(ix) Then
                strFileName = strSourceFile
                Pos = InStr(strFileName, "<")
                strFileName = Left(strFileName, Pos - 1) _
                    & Mid(strFileName, Pos + 1, Len(strFileName) - Pos - 1) _
                    & Left(Me.lboLayer.List(ix), InStr(Me.lboLayer.List(ix), ";") - 1) _
                    & "." & Me.cboBildformat
' KK000907                   & Left(Me.lboLayer.List(ix), 2) _
'                strTestDir = Dir(strInDir & File(strFileName))
                strTestDir = Dir(gstrSourceDir & strFileName)
                If Len(strTestDir) > 0 Then
                    DoReduceSize strInDir, strFileName, strOutDir
                End If
            End If
        Next ix
    Else
        DoReduceSize strInDir, strSourceFile, strOutDir
    End If
Exit Sub

Err_MakeReduceSize:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "MakeReduceSize"
    Resume Next
End Sub

Private Function MakeAnything() As Boolean
On Error GoTo Err_MakeAnything
    Dim strBuffer As String * 255
    Dim lFileCnt As Long
    Dim strSourceFile As String
    Dim strInDir As String
    Dim strOutDir As String
    Dim strDir As String
    
   
  
    If Me.strSourceDir <> "" Then
        SaveSetting "TRiAS-MapWizard", "Common", "Directory", Me.strSourceDir
        If Me.cbRecursiv <> 0 Then
            SaveSetting "TRiAS-MapWizard", "Common", "recursiv", "yes"
        Else
            SaveSetting "TRiAS-MapWizard", "Common", "recursiv", "no"
        End If
    End If
    
    If Len(Me.strDestinationDir) = 0 Then
        MsgBox "Sie müssen erst ein Ausgabeverzeichnis festlegen!"
        Me.strDestinationDir.SetFocus
        MakeAnything = False
        Exit Function
    End If
    
    If Me.cbStoreCmd <> 0 And Len(Me.strDestinationFile) = 0 Then
        MsgBox "Sie müssen erst eine Ausgabedatei festlegen!"
        Me.strDestinationFile.SetFocus
        MakeAnything = False
        Exit Function
    End If
    
    Me.K_Navigate(0).Enabled = False
    Me.K_Navigate(1).Enabled = False
    
    If Me.cbStoreCmd <> 0 Then
On Error Resume Next
        Kill Me.strDestinationFile
On Error GoTo Err_MakeAnything
    End If
    
    If Right(gstrSourceDir, 1) <> "\" Then
        gstrSourceDir = gstrSourceDir & "\"
    End If
    gstrDestinationDir = Me.strDestinationDir
    If Right(gstrDestinationDir, 1) <> "\" Then
        gstrDestinationDir = gstrDestinationDir & "\"
    End If
    
' KK000905
' Existiert Dir oder muss es angelegt werden
    If Dir(gstrDestinationDir) = "" Then
        MakeDir gstrDestinationDir
    End If

    GetTempPath ByVal Len(strBuffer), ByVal strBuffer
    gstrWorkDir = Left(strBuffer, InStr(strBuffer, Chr$(0)) - 1)
    If Right(gstrWorkDir, 1) <> "\" Then
        gstrWorkDir = gstrWorkDir & "\"
    End If
' KK000713
    gstrTempDir = gstrWorkDir
    gstrWorkDir = gstrWorkDir & "MapWizard\"
    
    lFileCnt = 0
    Do While lFileCnt < Me.lboDateien.ListCount
        If Me.lboDateien.Selected(lFileCnt) Then
            strSourceFile = Me.lboDateien.List(lFileCnt)
            
            Me!StatusBar.Panels(1).Text = strSourceFile
            Me.StatusBar.Refresh
' sicherstellen, daß Zielverzeichnis existiert
            strDir = Me.strDestinationDir & strSourceFile
            MakeDir strDir

' Arbeitsschritte ausführen
            strInDir = gstrSourceDir
            If Me.cbRenameFiles Then
                MakeRenameFiles strInDir, strSourceFile, strOutDir
                strInDir = strOutDir
            End If
 ' Versuch : Nomenklatur
 ' KK000704 - Nomenklatur ??? - und Layer ???
             Dim Pos As Integer
             Pos = InStr(gstrNomenklatur, "<")
             If Pos Then
                  strSourceFile = Left(gstrNomenklatur, Pos - 1) _
                    & Mid(gstrNomenklatur, Pos + 1, Len(gstrNomenklatur) - Pos - 1) _
                    & gstrLayer _
                    & "." & Me.cboBildformat
             End If

            If Me.cbRotate Then
                Protocoll (" *********************** Function < Rotate >")
                MakeRotate strInDir, strSourceFile, strOutDir
                strInDir = strOutDir
            End If
            If Me.cbReduceColor Then
                Protocoll (" *********************** Function < ReduceColor >")
                MakeReduceColor strInDir, strSourceFile, strOutDir
                strInDir = strOutDir
           End If
            If Me.cbReduceSize Then
                Protocoll (" *********************** Function < ReduceSize >")
                MakeReduceSize strInDir, strSourceFile, strOutDir
                strInDir = strOutDir
            End If
            If Me.cbCompress And Not Me.cbReduceSize Then
                Protocoll (" *********************** Function < Compress >")
                MakeCompress strInDir, strSourceFile, strOutDir
                strInDir = strOutDir
           End If
        End If
        DoEvents
        lFileCnt = lFileCnt + 1
    Loop
    Me!StatusBar.Panels(1).Text = ""
    Me.StatusBar.Refresh
   
    If Not Me.cbRetainTempFiles Then
        DoCmd "rmdir /s """ & gstrWorkDir & """", Me.cbStoreCmd
    Else
        DoCmd "rmdir """ & gstrWorkDir & """", Me.cbStoreCmd
    End If
    
    MsgBox "Die Verarbeitung wurde abgeschlossen!"
    Me.K_Navigate(0).Enabled = True
    Me.K_Navigate(1).Enabled = True
    MakeAnything = True
Exit Function

Err_MakeAnything:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "MakeAnything"
    Resume Next
    MakeAnything = False
End Function
Private Function Protocoll(strText As String) As Boolean

On Error GoTo Err_Protocoll
    If "" = gstrProtocollDir Or "" = gstrProtocollFile Then
'        MsgBox " Protocoll - Datei nicht definiert "
        Protocoll = False
        Exit Function
    End If
    xFile = FreeFile
    Open gstrProtocollFile For Append As xFile
    Print #xFile, strText
    Close xFile
    Protocoll = True
    Exit Function
    
Err_Protocoll:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "Protocoll"
    Resume Next
    Protocoll = False
End Function


Private Sub K_AlleDateien_Click()
    Dim ix As Integer
    For ix = 0 To Me.lboDateien.ListCount - 1
        Me.lboDateien.Selected(ix) = True
    Next ix
End Sub

Private Sub K_AlleLayer_Click()
    Dim ix As Integer
    If Me.K_AlleLayer.Caption = "Alle Dateien" Then
        For ix = 0 To Me.lboDateien.ListCount - 1
            Me.lboDateien.Selected(ix) = True
        Next ix
    Else
        For ix = 0 To Me.lboLayer.ListCount - 1
            Me.lboLayer.Selected(ix) = True
        Next ix
    End If
End Sub

Private Sub K_DestinationFile_Click()
On Error Resume Next
    DlgCommon.CancelError = True
    DlgCommon.DialogTitle = "Ausgabedatei festlegen"
    DlgCommon.InitDir = strSourceDir
    DlgCommon.DefaultExt = "*.bat"
    DlgCommon.Filter = "Stapeldateien (*.bat)|*.bat"
    DlgCommon.FileName = "MapWizard.bat"
    DlgCommon.Flags = cdlOFNCreatePrompt Or cdlOFNHideReadOnly
    DlgCommon.ShowOpen
    If Err = 32755 Then 'Abbrechen gedrückt
        Exit Sub
    ElseIf Err = 0 Then
        Me.strDestinationFile = DlgCommon.FileName
        Me.cbStoreCmd = 1
    Else
        MsgBox Err.Description
    End If
End Sub

Private Sub K_Navigate_Click(Index As Integer)
    Dim strDir As String
    

    With Me.tabPages
        Select Case .Tab
        Case 0
            If Index = 1 Then
                Me.K_Navigate(0).Caption = "<< Zurück"
                Me.K_Navigate(0).Enabled = True
                
                gstrSourceDir = Me.strSourceDir
                
                Load_ListBox Me.lboLayer, Me.cboGrundkonfiguration, "L"
                If Me.lboLayer.ListCount > 0 Then
                    Me.lblLayer.Caption = "Layer"
                    Me.K_AlleLayer.Caption = "Alle Layer"
                    K_AlleLayer_Click
                    Me.lboDateien.Height = Me.txtInfo.Top + Me.txtInfo.Height - (Me.lblDateien.Top + Me.lblDateien.Height)
                    Me.lboDateien.Top = Me.lblDateien.Top + Me.lblDateien.Height
                    Me.K_AlleDateien.Visible = True
                    Me.lblDateien.Visible = True
                    Me.lboLayer.Visible = True
                Else
                    Me.lboLayer.Visible = False
                    Me.K_AlleDateien.Visible = False
                    Me.lblDateien.Visible = False
                    Me.K_AlleLayer.Caption = "Alle Dateien"
                    Me.lblLayer.Caption = "Dateien"
                    Me.lboDateien.Top = Me.lboLayer.Top
                    Me.lboDateien.Height = Me.txtInfo.Height
                End If
                Me.K_Navigate(1).Caption = "Weiter >>"
                Me.K_Navigate(1).Enabled = True
                .Tab = 1
            Else
                Me.K_Navigate(0).Caption = "<< Zurück"
                Me.K_Navigate(0).Enabled = False
            End If
    
            Me.txtInfo = ""
            Me.lboDateien.Clear
            strDir = Me.strSourceDir
            If Right(strDir, 1) <> "\" Then
                strDir = strDir & "\"
            End If
            fill_lboDateien strDir, ""
            Me.Refresh
        Case 1
            If Index = 1 Then
                Me.strDestinationDir = Me.strSourceDir
                If Right(Me.strDestinationDir, 1) <> "\" Then
                    Me.strDestinationDir = Me.strDestinationDir & "\"
                End If
                Me.strDestinationDir = Me.strDestinationDir & "MapWizard\"
                
     ' KK000705 -- ProtokollStart -------------------------------------------------
                xFile = FreeFile
                MakeDir Me.strDestinationDir
                gstrProtocollDir = Me.strDestinationDir
                gstrProtocollFile = gstrProtocollDir & "\Protokoll.txt"
                gstrErrorFile = gstrProtocollDir & "\Error.txt"
                On Error Resume Next
                Kill gstrProtocollFile
                On Error Resume Next
                Kill gstrErrorFile
               
                Open gstrProtocollFile For Append As xFile
                Print #xFile, " *** Start MapWizard " & Date & " " & Time & " *** "
                Close xFile
     ' ----------------------------------------------------------------------------
     
                Load_CheckBox Me.cbRotate, "Drehen"
                Me.K_Navigate(1).Caption = "Fertigstellen"
                Me.K_Navigate(1).Enabled = True
                .Tab = 2
            Else
                Me.K_Navigate(0).Caption = "<< Zurück"
                Me.K_Navigate(0).Enabled = False
                .Tab = 0
            End If
        Case 2
            If Index = 1 Then
                Me.K_Navigate(1).Enabled = True
                If MakeAnything Then
             '       Unload Me
                     WizardUnload
                End If
                    
            Else
                .Tab = 1
            End If
        End Select
        If .Tab > 0 Then
            Me.K_Navigate(0).Caption = "<< Zurück"
            Me.K_Navigate(0).Enabled = True
        Else
            Me.K_Navigate(0).Caption = "<< Zurück"
            Me.K_Navigate(0).Enabled = False
        End If
        If .Tab < .Tabs - 1 Then
            Me.K_Navigate(1).Caption = "Weiter >>"
            Me.K_Navigate(1).Enabled = True
        Else
            Me.K_Navigate(1).Caption = "Fertigstellen"
            Me.K_Navigate(1).Enabled = True
        End If
    End With


End Sub

Private Sub K_SelectDestinationDir_Click()
On Error Resume Next
    Dim fSelDir As frmSelDir
    Set fSelDir = New frmSelDir
    fSelDir.Dir1.Path = Me.strDestinationDir
    Load fSelDir
    fSelDir.Show vbModal, Me
    If fSelDir.Tag = Chr(13) Then
    Else
        Me.strDestinationDir = fSelDir.Tag
    End If
    Unload fSelDir
    Set fSelDir = Nothing
End Sub

Private Sub K_SelectSourceDir_Click()
On Error Resume Next
    Dim fSelDir As frmSelDir
    Set fSelDir = New frmSelDir
    fSelDir.Dir1.Path = Me.strSourceDir
    Load fSelDir
    fSelDir.Show vbModal, Me
    If fSelDir.Tag = Chr(13) Then
    Else
        Me.strSourceDir = fSelDir.Tag
    End If
    Unload fSelDir
    Set fSelDir = Nothing

End Sub
Function ReadLine(hSourceFile As Long, strBuffer As String) As Long
    Dim strChar As String
    Dim lByteCnt
    strBuffer = ""
    lByteCnt = 0
    Do While EOF(hSourceFile) = False
        strChar = Input(1, #hSourceFile)
        lByteCnt = lByteCnt + 1
        If Asc(strChar) > 13 Then
            strBuffer = strBuffer & strChar
            Exit Do
        End If
    Loop
    Do While EOF(hSourceFile) = False
        strChar = Input(1, #hSourceFile)
        lByteCnt = lByteCnt + 1
        If Asc(strChar) <= 13 Then
            Exit Do
        End If
        strBuffer = strBuffer & strChar
    Loop
    ReadLine = lByteCnt
End Function

Function Layer(ByVal strFile As String) As String
    Dim strLayer As String
    Dim ix As Integer
    
'    strLayer = LCase(Mid(strFile, InStr(strFile, ".") - 2, 2))
' KK000907
    Dim strLboLayer As String
    Dim Pos As Integer
    
    ix = 0
    Do While ix < Me.lboLayer.ListCount
'   KK000907
        Pos = InStr(Me.lboLayer.List(ix), ";") - 1
        strLboLayer = Left(Me.lboLayer.List(ix), Pos)
        strLayer = LCase(Mid(strFile, InStr(strFile, ".") - Pos, Pos))
        If strLayer = strLboLayer Then
'       If strLayer = Left(Me.lboLayer.List(ix), 2) Then
            Exit Do
        End If
        ix = ix + 1
    Loop
    If ix < Me.lboLayer.ListCount Then
        Layer = strLayer
    Else
        Layer = ""
    End If
End Function

Function File(ByVal strFile As String) As String
    Dim strTemp As String
    
    strTemp = strFile
    Do While InStr(strTemp, "\")
        strTemp = Mid(strTemp, 2)
    Loop
    File = strTemp
End Function

Function Path(strFile As String) As String
    Dim strTemp As String
    
    strTemp = strFile
    Do While Right(strTemp, 1) <> "\" And Len(strTemp) > 0
        strTemp = Left(strTemp, Len(strTemp) - 1)
    Loop
    Path = strTemp
End Function

Function Read_GeoRef(strFileName As String, R() As Double, H() As Double) As Boolean
    Dim strBuffer As String * 255
    Dim strPath As String
    Dim strFile As String
    Dim strGeoRefFile As String
    Dim strGeoRef As String
    Dim strRef As String
    Dim ix As Integer
    Dim Pos As Integer
    
    strPath = Path(strFileName)
    strFile = UCase(Mid(strFileName, Len(strPath) + 1))
    strGeoRefFile = Dir(strPath & "GeoRef.dat")
    If Len(strGeoRefFile) > 0 Then
        ix = GetPrivateProfileString(ByVal "Georeferenzen", _
                ByVal strFile, ByVal "", strBuffer, Len(strBuffer), strPath & strGeoRefFile)
        If ix > 0 Then
            strGeoRef = Trim(Left(strBuffer, InStr(strBuffer, Chr$(0)) - 1)) & ";"
            ix = 1
            Do While Len(strGeoRef) > 0
                Pos = InStr(strGeoRef, " ")
                R(ix) = CDbl(Left(strGeoRef, Pos - 1))
                strGeoRef = Mid(strGeoRef, Pos + 1)
                Pos = InStr(strGeoRef, ";")
                H(ix) = CDbl(Left(strGeoRef, Pos - 1))
                strGeoRef = Mid(strGeoRef, Pos + 1)
                ix = ix + 1
            Loop
            Read_GeoRef = True
        Else
            Read_GeoRef = False
        End If
    Else
        Read_GeoRef = False
    End If
End Function


Function Read_DocInfo(strFileName As String, R() As Double, H() As Double) As String
On Error GoTo Err_Read_DocInfo
'    Dim rex As TRiASSupport.ParseRegularExpression
    Dim strDocFileName As String
    Dim hDocFile As Long
    Dim strBuffer As String
    Dim strInfo As String
    
    strDocFileName = Left(strFileName, Len(strFileName) - Len(Me.cboBildformat)) & "doc"
    hDocFile = FreeFile
    Open strDocFileName For Input As hDocFile

    ReadLine hDocFile, strBuffer
    strInfo = Trim(Left(strBuffer, 49))
    strInfo = strInfo & Chr(13) & Chr(10) & Trim(Mid(strBuffer, 50))
    Do Until EOF(hDocFile)
        ReadLine hDocFile, strBuffer
        If Left(strBuffer, 7) = "   1   " Then
            R(1) = Val(Mid(strBuffer, 10, 13))
            H(1) = Val(Mid(strBuffer, 24, 13))
        ElseIf Left(strBuffer, 7) = "   2   " Then
            R(2) = Val(Mid(strBuffer, 10, 13))
            H(2) = Val(Mid(strBuffer, 24, 13))
        ElseIf Left(strBuffer, 7) = "   3   " Then
            R(3) = Val(Mid(strBuffer, 10, 13))
            H(3) = Val(Mid(strBuffer, 24, 13))
        ElseIf Left(strBuffer, 7) = "   4   " Then
            R(4) = Val(Mid(strBuffer, 10, 13))
            H(4) = Val(Mid(strBuffer, 24, 13))
        ElseIf Left(strBuffer, 7) = "   5   " Then
            R(5) = Val(Mid(strBuffer, 10, 13))
            H(5) = Val(Mid(strBuffer, 24, 13))
        ElseIf Left(strBuffer, 7) = "   6   " Then
            R(6) = Val(Mid(strBuffer, 10, 13))
            H(6) = Val(Mid(strBuffer, 24, 13))
        Else
        End If
    Loop
    Close hDocFile
    
    strInfo = strInfo & Chr(13) & Chr(10) & "1" & Format(R(1), "  0000000.000") & Format(H(1), "  0000000.000")
    strInfo = strInfo & Chr(13) & Chr(10) & "2" & Format(R(2), "  0000000.000") & Format(H(2), "  0000000.000")
    strInfo = strInfo & Chr(13) & Chr(10) & "3" & Format(R(3), "  0000000.000") & Format(H(3), "  0000000.000")
    strInfo = strInfo & Chr(13) & Chr(10) & "4" & Format(R(4), "  0000000.000") & Format(H(4), "  0000000.000")
    strInfo = strInfo & Chr(13) & Chr(10) & "5" & Format(R(5), "  0000000.000") & Format(H(5), "  0000000.000")
    strInfo = strInfo & Chr(13) & Chr(10) & "6" & Format(R(6), "  0000000.000") & Format(H(6), "  0000000.000")
    Read_DocInfo = strInfo
Exit Function

Err_Read_DocInfo:
    If Err.Number = 53 Then     'Datei nicht gefunden
        Read_DocInfo = ""
        Exit Function
    Else
        MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "Read_MapInfo"
        Resume Next
    End If
End Function

Function Read_MapInfo(strFileName As String) As String
On Error GoTo Err_Read_MapInfo
    Dim hFile As Long
    Dim strTestDir As String

On Error Resume Next
 '   Kill App.Path & "\MapInfo.log"
 ' KK000713
    Dim strDel As String
    strDel = "del """ & App.Path & "\MapInfo.log"""
 '   DoCmd strDel, Me.cbStoreCmd
    DoCmd strDel, False
    
On Error GoTo Err_Read_MapInfo
    Dim Flen As Long
    Flen = FileLen(strFileName)
    If Me.cbStoreCmd Then
       DoCmd """" & App.Path & "\MAPINFO.EXE"" """ & strFileName & """ 1> """ & App.Path & "\MapInfo.log""", False
    Else
        If FileLen(strFileName) Then
'        DoCmd """" & App.Path & "\MAPINFO.EXE"" """ & strFileName & """ 1> """ & App.Path & "\MapInfo.log""", False
'         DoCmd """" & App.Path & "\MAPINFO.EXE"" """ & strFileName & """ 1> """ & App.Path & "\MapInfo.log""", False
            DoCmd """" & App.Path & "\MAPINFO.EXE"" """ & strFileName & """ 1> """ & App.Path & "\MapInfo.log""", Me.cbStoreCmd
        Else
            Protocoll (" Read_MapInfo - ERROR : File " & strFileName & " existiert nicht !!!")
    '    Unload Me
            WizardUnload
        End If
    End If
            
On Error Resume Next
    hFile = FreeFile
    Open App.Path & "\MapInfo.log" For Input As hFile
    If Err Then
        Read_MapInfo = ""
        Protocoll (" Read_MapInfo - ERROR : File " & App.Path & "\MapInfo.log" & " existiert nicht !!!")
    Else
        Read_MapInfo = Input(LOF(hFile), hFile)
        Close hFile
    End If
            
On Error Resume Next
'    Kill App.Path & "\MapInfo.log"
' KK000713
    strDel = "del """ & App.Path & "\MapInfo.log"""
    DoCmd strDel, False


On Error GoTo Err_Read_MapInfo

Exit Function

Err_Read_MapInfo:
'    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "Read_MapInfo"
' KK000713
    Protocoll ("Read_MapInfo-Fehler" & Str(Err.Number) & ": " & Err.Description)
'    Resume Next
    WizardUnload
End Function

Private Sub fill_lboDateien(strSourceDir As String, strBaseDir As String)
On Error GoTo Err_fill_lboDateien
    Dim strDir As String
    Dim strSourceFile As String
    Dim strLayer As String
    Dim strTemp1 As String
    Dim strTemp2 As String
    Dim ix As Integer
    
    
    If Me.cbExcludeMapWizardDir And InStr(strBaseDir, "MapWizard") Then
        Exit Sub
    End If
    
    If strSourceDir = "\" Then
        Exit Sub
    End If
    strDir = Me.strSourceDir & strBaseDir & "\"
    
    
    If Me.cbRecursiv Then
        strTemp1 = Dir(strDir, vbDirectory)
        Do While Len(strTemp1) > 0
            If vbDirectory = (GetAttr(strDir & strTemp1) And vbDirectory) Then
                If Left(strTemp1, 1) <> "." Then
                    If Len(strBaseDir) > 0 Then
                        fill_lboDateien strSourceDir, strBaseDir & "\" & strTemp1
                    Else
                        fill_lboDateien strSourceDir, strTemp1
                    End If
                    strTemp2 = Dir(strDir, vbDirectory)
                    Do While strTemp2 <> strTemp1
                        strTemp2 = Dir()
                    Loop
                End If
            End If
            strTemp1 = Dir()
        Loop
    End If
    
    strSourceFile = Dir(strDir & "\*." & Me.cboBildformat)
    Do While Len(strSourceFile) > 0
        If Me.lboLayer.ListCount > 0 Then
            strLayer = Layer(strSourceFile)
            If Len(strLayer) > 0 Then
' KK000907
                strSourceFile = "<" & Left(strSourceFile, InStr(strSourceFile, ".") - Len(strLayer) - 1) & ">"
'                strSourceFile = "<" & Left(strSourceFile, Len(strSourceFile) - Len(Me.cboBildformat) - 3) & ">"
            End If
        End If
        If Len(strBaseDir) > 0 Then
            strSourceFile = strBaseDir & "\" & strSourceFile
        End If
        ix = 0
        Do While ix < Me.lboDateien.ListCount
            If strSourceFile = Me.lboDateien.List(ix) Then
                Exit Do
            End If
            ix = ix + 1
        Loop
        If ix = Me.lboDateien.ListCount Then
            Me.lboDateien.AddItem strSourceFile
        End If
        strSourceFile = Dir()
    Loop
    
Exit Sub

Err_fill_lboDateien:
    If Err.Number = 53 Then
        Exit Sub
    Else
        MsgBox Err.Description
        Resume Next
    End If


End Sub


Private Sub lboDateien_Click()
On Error GoTo Err_lboDateien_Click
    Dim strDir As String
    Dim strFileName As String
    Dim strCmd As String
    Dim R(1 To 6) As Double
    Dim H(1 To 6) As Double
    Dim strTestDir As String
    Dim strDocInfo As String
    Dim strMapInfo As String
    Dim strLayerInfo As String
    Dim Pos As Integer
    Dim ix As Integer
    strDocInfo = ""
    
    If Me.lboDateien.SelCount <> 1 Then
        Me.txtInfo = Me.lboDateien.SelCount & " Dateien ausgewählt"
    Else
        strFileName = Me.lboDateien.List(Me.lboDateien.ListIndex)
        If Right(strFileName, 1) = ">" Then
            strLayerInfo = "Layer:"
            For ix = 0 To Me.lboLayer.ListCount - 1
                strFileName = Me.lboDateien.List(Me.lboDateien.ListIndex)
                Pos = InStr(strFileName, "<")
                strFileName = Left(strFileName, Pos - 1) _
                    & Mid(strFileName, Pos + 1, Len(strFileName) - Pos - 1) _
                    & Left(Me.lboLayer.List(ix), InStr(Me.lboLayer.List(ix), ";") - 1) _
                    & "." & Me.cboBildformat
'                    & Left(Me.lboLayer.List(ix), 2)    KK000907
                strFileName = Dir(Me.strSourceDir & strFileName)
                If Len(strFileName) > 0 Then
                    strLayerInfo = strLayerInfo & Chr(13) & Chr(10) & Me.lboLayer.List(ix)
                End If
            Next ix
            Me.txtInfo = strLayerInfo
        Else
            strDir = strSourceDir & strFileName
            Do While Right(strDir, 1) <> "\"
                strDir = Left(strDir, Len(strDir) - 1)
            Loop
            strDocInfo = Read_DocInfo(gstrSourceDir & strFileName, R, H)
            strMapInfo = Read_MapInfo(gstrSourceDir & strFileName)
            Me.txtInfo = "Dokument:" & Chr(13) & Chr(10) & strDocInfo & Chr(13) & Chr(10) & "Karte:" & Chr(13) & Chr(10) & strMapInfo
        End If
        Me.Refresh

    End If
Exit Sub

Err_lboDateien_Click:
    MsgBox Err.Description
    Resume Next
End Sub

Private Sub strDestinationFile_Change()
    Me.cbStoreCmd = 1
End Sub

Private Sub strSourceDir_Change()
On Error GoTo Err_strSourceDir
    Dim strDir As String
    
    
Exit Sub

Err_strSourceDir:
    If Err.Number = 53 Then
        Exit Sub
    Else
        MsgBox Err.Description
        Exit Sub
    End If
End Sub

