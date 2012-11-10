VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form frmMain 
   Caption         =   "EDBS-Separator"
   ClientHeight    =   7905
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9885
   LinkTopic       =   "Form1"
   ScaleHeight     =   7905
   ScaleWidth      =   9885
   Begin VB.CommandButton K_FilterEDBS 
      Caption         =   "Daten bereitstellen"
      Height          =   375
      Left            =   2400
      TabIndex        =   40
      Top             =   6600
      Width           =   1815
   End
   Begin VB.ListBox lboDateien 
      Height          =   6300
      Left            =   5640
      TabIndex        =   7
      Top             =   240
      Width           =   4095
   End
   Begin MSComDlg.CommonDialog DlgCommon 
      Left            =   120
      Top             =   6600
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Frame FrameDataSelection 
      Caption         =   "Ergebnisdaten"
      Height          =   1335
      Left            =   120
      TabIndex        =   6
      Top             =   5160
      Width           =   5415
      Begin VB.TextBox strDestinationFileExtension 
         Height          =   285
         Left            =   2520
         TabIndex        =   24
         Text            =   "edbs"
         Top             =   960
         Width           =   615
      End
      Begin VB.CommandButton K_DestinationDir 
         Caption         =   "..."
         Height          =   255
         Left            =   4920
         TabIndex        =   23
         Top             =   600
         Width           =   375
      End
      Begin VB.TextBox strDestinationDir 
         Height          =   285
         Left            =   1320
         TabIndex        =   22
         Top             =   600
         Width           =   3615
      End
      Begin VB.CommandButton K_DestinationFile 
         Caption         =   "..."
         Height          =   255
         Left            =   4920
         TabIndex        =   21
         Top             =   240
         Width           =   375
      End
      Begin VB.TextBox strDestinationFile 
         Height          =   285
         Left            =   1320
         TabIndex        =   20
         Top             =   240
         Width           =   3615
      End
      Begin VB.OptionButton bSepDestination 
         Caption         =   "Verzeichnis"
         Height          =   255
         Index           =   2
         Left            =   120
         TabIndex        =   19
         Top             =   600
         Width           =   2295
      End
      Begin VB.OptionButton bSepDestination 
         Caption         =   "Datei"
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   18
         Top             =   240
         Width           =   855
      End
      Begin VB.Label Label2 
         Caption         =   "mit Erweiterung"
         Height          =   255
         Left            =   1320
         TabIndex        =   25
         Top             =   960
         Width           =   1215
      End
   End
   Begin VB.Frame FrameFileSelection 
      Caption         =   "Ausgangsdaten"
      Height          =   3015
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   5415
      Begin VB.ComboBox cboBSZN_Katasteramt 
         Height          =   315
         ItemData        =   "frmMain.frx":0000
         Left            =   1560
         List            =   "frmMain.frx":0002
         TabIndex        =   41
         Top             =   2400
         Width           =   1935
      End
      Begin VB.ComboBox cboBSZN_Ausgabe 
         Height          =   315
         Left            =   1560
         TabIndex        =   38
         Top             =   2040
         Width           =   3735
      End
      Begin VB.OptionButton bSepSource 
         Caption         =   "BSZN-Abgabe"
         Height          =   255
         Index           =   3
         Left            =   120
         TabIndex        =   37
         Top             =   1680
         Width           =   1335
      End
      Begin VB.TextBox strSepSourceBSZN 
         Height          =   285
         Left            =   1560
         TabIndex        =   36
         Top             =   1680
         Width           =   3375
      End
      Begin VB.CommandButton K_SelectSourceBSZN 
         Caption         =   "..."
         Height          =   255
         Left            =   4920
         TabIndex        =   35
         Top             =   1680
         Width           =   375
      End
      Begin VB.Frame Frame1 
         BorderStyle     =   0  'Kein
         Height          =   735
         Left            =   960
         TabIndex        =   26
         Top             =   960
         Width           =   4335
         Begin VB.OptionButton bSepSourceDir 
            Caption         =   "des Bezirks"
            Enabled         =   0   'False
            Height          =   255
            Index           =   2
            Left            =   960
            TabIndex        =   30
            Top             =   360
            Width           =   1335
         End
         Begin VB.ComboBox Bezirke 
            Height          =   315
            ItemData        =   "frmMain.frx":0004
            Left            =   2400
            List            =   "frmMain.frx":0006
            TabIndex        =   29
            Top             =   360
            Width           =   1935
         End
         Begin VB.TextBox strSourceFileExtension 
            Height          =   285
            Left            =   2400
            TabIndex        =   28
            Text            =   "001"
            Top             =   0
            Width           =   615
         End
         Begin VB.OptionButton bSepSourceDir 
            Caption         =   "mit Erweiterung"
            Enabled         =   0   'False
            Height          =   255
            Index           =   1
            Left            =   960
            TabIndex        =   27
            Top             =   0
            Width           =   1455
         End
         Begin VB.Label Label1 
            Caption         =   "alle Dateien"
            Height          =   255
            Left            =   0
            TabIndex        =   31
            Top             =   0
            Width           =   855
         End
      End
      Begin VB.CommandButton K_SelectSourceDir 
         Caption         =   "..."
         Height          =   255
         Left            =   4920
         TabIndex        =   13
         Top             =   600
         Width           =   375
      End
      Begin VB.TextBox strSepSourceDir 
         Height          =   285
         Left            =   1320
         TabIndex        =   12
         Top             =   600
         Width           =   3615
      End
      Begin VB.CommandButton K_SelectSourceFile 
         Caption         =   "..."
         Height          =   255
         Left            =   4920
         TabIndex        =   11
         Top             =   240
         Width           =   375
      End
      Begin VB.TextBox strSepSourceFile 
         Height          =   285
         Left            =   1320
         TabIndex        =   10
         Top             =   240
         Width           =   3615
      End
      Begin VB.OptionButton bSepSource 
         Caption         =   "Datei"
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   4
         Top             =   240
         Width           =   855
      End
      Begin VB.OptionButton bSepSource 
         Caption         =   "Verzeichnis"
         Height          =   255
         Index           =   2
         Left            =   120
         TabIndex        =   3
         Top             =   600
         Width           =   2295
      End
      Begin VB.Label Label4 
         Caption         =   "Katasteramt"
         Height          =   255
         Left            =   360
         TabIndex        =   42
         Top             =   2400
         Width           =   1215
      End
      Begin VB.Label Label3 
         Caption         =   "Ausgabe"
         Height          =   255
         Left            =   360
         TabIndex        =   39
         Top             =   2040
         Width           =   1215
      End
   End
   Begin VB.Frame FrameSepType 
      Caption         =   "Separieren nach"
      Height          =   1815
      Left            =   120
      TabIndex        =   5
      Top             =   3240
      Width           =   5415
      Begin VB.OptionButton bSepList 
         Caption         =   "negativ"
         Enabled         =   0   'False
         Height          =   495
         Index           =   2
         Left            =   2640
         TabIndex        =   34
         Top             =   960
         Width           =   975
      End
      Begin VB.OptionButton bSepList 
         Caption         =   "positiv"
         Enabled         =   0   'False
         Height          =   495
         Index           =   1
         Left            =   1800
         TabIndex        =   33
         Top             =   960
         Width           =   975
      End
      Begin VB.CheckBox xMaskList 
         Caption         =   "Liste"
         Enabled         =   0   'False
         Height          =   375
         Left            =   120
         TabIndex        =   32
         Top             =   960
         Width           =   1215
      End
      Begin VB.TextBox strMaskFolie 
         Height          =   285
         Left            =   1800
         TabIndex        =   17
         Top             =   240
         Width           =   1455
      End
      Begin VB.CheckBox xMaskFolie 
         Caption         =   "Folien"
         Height          =   375
         Left            =   120
         TabIndex        =   16
         Top             =   240
         Width           =   1815
      End
      Begin VB.TextBox strMaskObjectID 
         Height          =   285
         Left            =   1800
         TabIndex        =   15
         Top             =   600
         Width           =   1455
      End
      Begin VB.CheckBox xMaskObjectID 
         Caption         =   "Objektnummer wie"
         Height          =   375
         Left            =   120
         TabIndex        =   14
         Top             =   600
         Width           =   1815
      End
      Begin VB.CheckBox xMaskFLOE 
         Caption         =   "FLOE"
         Enabled         =   0   'False
         Height          =   375
         Left            =   120
         TabIndex        =   9
         Top             =   1320
         Width           =   1815
      End
   End
   Begin ComctlLib.StatusBar StatusBar 
      Align           =   2  'Unten ausrichten
      Height          =   255
      Left            =   0
      TabIndex        =   0
      Top             =   7650
      Width           =   9885
      _ExtentX        =   17436
      _ExtentY        =   450
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   1
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            AutoSize        =   1
            Object.Width           =   16933
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.CommandButton K_Exit 
      Caption         =   "B&eenden"
      Height          =   375
      Left            =   4320
      TabIndex        =   1
      Top             =   6600
      Width           =   1215
   End
   Begin ComctlLib.ProgressBar ProgressBar 
      Height          =   255
      Left            =   120
      TabIndex        =   8
      Top             =   7080
      Width           =   5415
      _ExtentX        =   9551
      _ExtentY        =   450
      _Version        =   327682
      Appearance      =   1
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim strSourceDir As String

Private Sub Bezirke_Click()
On Error GoTo Err_Bezirke_Change
    LadeDateienDirKat
    Me.bSepSourceDir(2) = True
Exit Sub

Err_Bezirke_Change:
    MsgBox Err.Description
    Resume Next
End Sub

Private Sub bSepSource_Click(index As Integer)
    Select Case index
    Case 1
        LadeDateienFile
    Case 2
        LadeDateienDir
    End Select
End Sub

Private Sub bSepSourceDir_Click(index As Integer)
    Select Case index
    Case 1
        LadeDateienDir
    Case 2
        LadeDateienDirKat
    End Select
End Sub

Private Sub cboBSZN_Ausgabe_Change()
    If Me.cboBSZN_Katasteramt.Enabled = False Then
        LadeDateienBSZN
    End If
End Sub

Private Sub cboBSZN_Ausgabe_Click()
    If Me.cboBSZN_Katasteramt.Enabled = False Then
        LadeDateienBSZN
    End If
End Sub

Private Sub cboBSZN_Katasteramt_Change()
    LadeDateienBSZNfürKatasteramt
End Sub

Private Sub cboBSZN_Katasteramt_Click()
    LadeDateienBSZNfürKatasteramt
End Sub

Private Sub Form_Unload(CANCEL As Integer)
On Error Resume Next
 Dim strDirName As String
 Dim strFileName As String
    strDirName = GetTempDirName & "ZEDBS\"
    strFileName = Dir(strDirName & "*.*", vbNormal)
    Do While Len(strFileName) > 0
        Kill strDirName & strFileName
        strFileName = Dir()
    Loop
    RmDir strDirName
End Sub

Private Sub K_DestinationDir_Click()
    Dim fSelDir As frmSelDir
    Set fSelDir = New frmSelDir
    Load fSelDir
    fSelDir.Show vbModal, Me
    If fSelDir.Tag = Chr(13) Then
    Else
        Me.strDestinationDir = fSelDir.Tag
    End If
    Unload fSelDir
    Set fSelDir = Nothing
End Sub

Private Sub K_DestinationFile_Click()
On Error Resume Next
    DlgCommon.CancelError = True
    DlgCommon.DialogTitle = "Ausgabedatei festlegen"
    DlgCommon.InitDir = strSourceDir
    DlgCommon.DefaultExt = "*.001"
    DlgCommon.Filter = "ALK-Dateien (*.001)|*.001"
    DlgCommon.FileName = "EDBS_Sep.001"
    DlgCommon.Flags = cdlOFNCreatePrompt Or cdlOFNHideReadOnly
    DlgCommon.ShowOpen
    If Err = 32755 Then 'Abbrechen gedrückt
        Exit Sub
    ElseIf Err = 0 Then
        Me.strDestinationFile = DlgCommon.FileName
    Else
        MsgBox Err.Description
    End If
End Sub

Private Sub K_Exit_Click()
    Unload Me
End Sub

Private Sub K_FilterEDBS_Click()
    FilterEDBS1
End Sub

Private Function ObjId(strBuffer As String) As String
    If Mid(strBuffer, 66, 4) = "0000" Then
        ObjId = Mid(strBuffer, 88, 7)
    Else
        If Mid(strBuffer, 131, 1) <> " " Then
            ObjId = Mid(strBuffer, 111, 7)
        ElseIf Mid(strBuffer, 132, 1) <> " " Then
            ObjId = Mid(strBuffer, 118, 7)
        Else
            ObjId = ""
        End If
    End If
End Function
Private Function Folie(strBuffer As String) As String
    If Mid(strBuffer, 66, 4) = "0000" Then
        Folie = Mid(strBuffer, 78, 3)
    Else
        Folie = Mid(strBuffer, 104, 3)
    End If
End Function

Sub LadeDateienFile()
 Dim strSourceDir As String
 Dim strSourceFile As String
 Dim strSourceFileExtension As String
 Dim pos As Integer
    strSourceDir = ""
    strSourceFile = Me.strSepSourceFile
    pos = InStr(strSourceFile, "\")
    Do While pos > 0
        strSourceDir = strSourceDir & Mid(strSourceFile, 1, pos)
        strSourceFile = Mid(strSourceFile, pos + 1)
        pos = InStr(strSourceFile, "\")
    Loop
    Me.lboDateien.Clear
    Me.lboDateien.AddItem strSourceFile
End Sub


Sub LadeDateienDir()
 Dim strSourceDir As String
 Dim strSourceFile As String
 Dim strSourceFileExtension As String
 
    strSourceDir = Me.strSepSourceDir
    strSourceFileExtension = Me.strSourceFileExtension
    If Right(strSourceDir, 1) <> "\" Then
        strSourceDir = strSourceDir & "\"
    End If
    Me.lboDateien.Clear
    strSourceFile = Dir(strSourceDir & "*." & strSourceFileExtension)
    Do While Len(strSourceFile) > 0
        Me.lboDateien.AddItem strSourceFile
        strSourceFile = Dir()
    Loop
End Sub

Sub LadeDateienBSZN_Ausgabe(strBSZN_Ausgabe As String)
 Dim strSourceDir As String
 Dim strSourceFile As String
 Dim strSourceFileExtension As String
 
    strSourceDir = Me.strSepSourceDir
'    strSourceFileExtension = Me.strSourceFileExtension
    strSourceFileExtension = "*"
    If Right(Me.strSepSourceBSZN, 1) <> "\" Then
        strSourceDir = Me.strSepSourceBSZN & "\"
    End If
    strSourceFile = Dir(Me.strSepSourceBSZN & strBSZN_Ausgabe & "\*." & strSourceFileExtension)
    Do While Len(strSourceFile) > 0
        If Right(strSourceFile, 4) <> ".mdb" Then
            Me.lboDateien.AddItem strBSZN_Ausgabe & "\" & strSourceFile
        End If
        strSourceFile = Dir()
    Loop
End Sub

Sub LadeDateienDirKat()
On Error GoTo Err_LadeDateienDirKat
 Dim strSourceDir As String
 Dim strSourceFile As String
 Dim strSourceFileExtension As String
 Dim db As Database
 Dim qd As QueryDef
 Dim rs As Recordset
    
    If Me.Bezirke.ListIndex < 0 Then
        Exit Sub
    End If
    
    strSourceDir = Me.strSepSourceDir
    strSourceFileExtension = Me.strSourceFileExtension
    If Right(strSourceDir, 1) <> "\" Then
        strSourceDir = strSourceDir & "\"
    End If
    Me.lboDateien.Clear
    
    Set db = OpenDatabase(strSourceDir & "Katasteramtsdateien.mdb")
On Error Resume Next
    Set qd = db.QueryDefs("tmpAbfrage")
On Error GoTo Err_LadeDateienDirKat
    If qd Is Nothing Then
       Set qd = db.CreateQueryDef("tmpAbfrage", "SELECT * FROM Bezirke")
    End If
    qd.SQL = "SELECT * FROM Bezirke_ALK_Dateien WHERE Bezirk =" & Str(Me.Bezirke.ItemData(Me.Bezirke.ListIndex))
    Set rs = qd.OpenRecordset(dbOpenSnapshot)
    Do Until rs.EOF
        Me.lboDateien.AddItem rs.Fields("Dateiname").Value
        rs.MoveNext
    Loop
    rs.Close
    db.Close
Exit Sub

Err_LadeDateienDirKat:
    MsgBox Err.Description
    Resume Next

End Sub

Sub LadeDateienBSZNfürKatasteramt_Ausgabe(strBSZN_Ausgabe As String)
On Error GoTo Err_LadeDateienBSZN_Ausgabe
 Dim strSourceDir As String
 Dim strSourceFile As String
 Dim strSourceFileExtension As String
 Dim pos As Integer
 Dim db As Database
 Dim qd As QueryDef
 Dim rs As Recordset
    
    If Right(Me.strSepSourceBSZN, 1) <> "\" Then
        Me.strSepSourceBSZN = Me.strSepSourceBSZN & "\"
    End If
    strSourceDir = Me.strSepSourceBSZN & strBSZN_Ausgabe
    strSourceFileExtension = ".zedbs"
    If Right(strSourceDir, 1) <> "\" Then
        strSourceDir = strSourceDir & "\"
    End If
    
On Error Resume Next
    Set db = OpenDatabase(strSourceDir & "Katasteramtsdateien.mdb")
    If Err.Number <> 0 Then
        MsgBox strSourceDir & "Katasteramtsdateien.mdb" & " nicht gefunden!"
        Exit Sub
    End If
    Set qd = db.QueryDefs("tmpAbfrage")
On Error GoTo Err_LadeDateienBSZN_Ausgabe
    If qd Is Nothing Then
       Set qd = db.CreateQueryDef("tmpAbfrage", "SELECT * FROM Bezirke")
    End If
    qd.SQL = "SELECT * FROM Bezirke_ALK_Dateien WHERE Bezirk =" & Str(Me.cboBSZN_Katasteramt.ItemData(Me.cboBSZN_Katasteramt.ListIndex))
    Set rs = qd.OpenRecordset(dbOpenSnapshot)
    Do Until rs.EOF
        strSourceFile = rs.Fields("Dateiname").Value
        pos = InStr(strSourceFile, ".")
        If pos > 0 Then
            strSourceFile = Left(strSourceFile, pos - 1)
        End If
        strSourceFile = strSourceFile & strSourceFileExtension
        Me.lboDateien.AddItem strBSZN_Ausgabe & "\" & strSourceFile
        rs.MoveNext
    Loop
    rs.Close
    db.Close
Exit Sub

Err_LadeDateienBSZN_Ausgabe:
    MsgBox Err.Description
    Resume Next
End Sub

Sub LadeDateienBSZN()
On Error GoTo Err_LadeDateienBSZN
 Dim iAusgabe As Integer
    
    Me.lboDateien.Clear
 
    For iAusgabe = 0 To Me.cboBSZN_Ausgabe.ListIndex
        LadeDateienBSZN_Ausgabe Me.cboBSZN_Ausgabe.List(iAusgabe)
    Next iAusgabe
Exit Sub

Err_LadeDateienBSZN:
    MsgBox Err.Description
    Resume Next
End Sub

Sub LadeDateienBSZNfürKatasteramt()
On Error GoTo Err_LadeDateienBSZN
 Dim iAusgabe As Integer
    
    Me.lboDateien.Clear
 
    For iAusgabe = 0 To Me.cboBSZN_Ausgabe.ListIndex
        LadeDateienBSZNfürKatasteramt_Ausgabe Me.cboBSZN_Ausgabe.List(iAusgabe)
    Next iAusgabe
Exit Sub

Err_LadeDateienBSZN:
    MsgBox Err.Description
    Resume Next
End Sub

Sub LadeKatasteraemterBSZN()
On Error GoTo Err_LadeKatasteraemterBSZN
 Dim strSourceDir As String
 Dim strTemp As String
 Dim pos As Integer
    
    strSourceDir = Me.strSepSourceBSZN
    If Right(strSourceDir, 1) <> "\" Then
        strSourceDir = strSourceDir & "\"
    End If
    
    strTemp = Dir(strSourceDir & "Katasteraemter.mdb")
    If Len(strTemp) > 0 Then
        Dim db As Database
        Dim qd As QueryDef
        Dim rs As Recordset
On Error Resume Next
        Set db = OpenDatabase(strSourceDir & "Katasteraemter.mdb", , True)
        If Err.Number <> 0 Then
            MsgBox strSourceDir & "Katasteraemter.mdb konnte nicht geöffnet werden!"
            Exit Sub
        End If
        Set qd = db.QueryDefs("tmpAbfrage")
On Error GoTo Err_LadeKatasteraemterBSZN
        If qd Is Nothing Then
            Set qd = db.CreateQueryDef("tmpAbfrage", "SELECT * FROM Katasteraemter")
        End If
        qd.SQL = "SELECT * FROM Katasteraemter"
        Set rs = qd.OpenRecordset(dbOpenSnapshot)
        Do Until rs.EOF
            Me.cboBSZN_Katasteramt.AddItem rs.Fields("BZKatasteramt").Value
            Me.cboBSZN_Katasteramt.ItemData(Me.cboBSZN_Katasteramt.ListCount - 1) = rs.Fields("IDKatasteramt").Value
            rs.MoveNext
        Loop
        rs.Close
        Set rs = Nothing
        Set qd = Nothing
        db.Close
        Me.cboBSZN_Katasteramt.Enabled = True
    Else
        Me.cboBSZN_Katasteramt.Enabled = False
        cboBSZN_Ausgabe_Click
    End If
Exit Sub

Err_LadeKatasteraemterBSZN:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next

End Sub

Sub LadeDateienBSZNKat()
On Error GoTo Err_LadeDateienDirKat
 Dim strSourceDir As String
 Dim strSourceFile As String
 Dim strSourceFileExtension As String
 Dim db As Database
 Dim qd As QueryDef
 Dim rs As Recordset
    
    strSourceDir = Me.strSepSourceBSZN
    strSourceFileExtension = Me.strSourceFileExtension
    If Right(strSourceDir, 1) <> "\" Then
        strSourceDir = strSourceDir & "\"
    End If
    Me.lboDateien.Clear
    
    Set db = OpenDatabase(strSourceDir & "Katasteramtsdateien.mdb")
On Error Resume Next
    Set qd = db.QueryDefs("tmpAbfrage")
On Error GoTo Err_LadeDateienDirKat
    If qd Is Nothing Then
       Set qd = db.CreateQueryDef("tmpAbfrage", "SELECT * FROM Bezirke")
    End If
    qd.SQL = "SELECT * FROM Bezirke_ALK_Dateien WHERE Bezirk =" & Str(Me.Bezirke.ItemData(Me.Bezirke.ListIndex))
    Set rs = qd.OpenRecordset(dbOpenSnapshot)
    Do Until rs.EOF
        Me.lboDateien.AddItem rs.Fields("Dateiname").Value
        rs.MoveNext
    Loop
    rs.Close
    db.Close
Exit Sub

Err_LadeDateienDirKat:
    MsgBox Err.Description
    Resume Next

End Sub

Sub LadeFLOEdir(strSourceDir As String, strSourceFile As String, strFLOE As String)
 Dim strTemp As String
 Dim db As Database
 Dim qd As QueryDef
 Dim rs As Recordset
        
On Error Resume Next
    Set db = OpenDatabase(strSourceDir & "FLOE.MDB")
    If Err Then
    Else
        db.QueryDefs.Delete "tmpAbfrage"
'        Set qd = db.CreateQueryDef("tmpAbfrage", "SELECT DLOB2005 FROM FLOE WHERE DLOB0001 ='" & Left(strSourceFile, 8) & "'")
        Set qd = db.CreateQueryDef("tmpAbfrage", "SELECT DLOB2005 FROM FLOE" _
                & " WHERE Filter1 >='" & Mid(strSourceFile, 1, 4) & "'" _
                & " AND Filter1 <='" & Mid(strSourceFile, 5, 4) & "'" _
                & " AND Filter2 >='" & Mid(strSourceFile, 9, 4) & "'" _
                & " AND Filter2 <='" & Mid(strSourceFile, 13, 4) & "'" _
                & " OR Filter1 = '' AND Filter2 = ''" _
                )
        Set rs = qd.OpenRecordset(dbOpenSnapshot)
        Do Until rs.EOF
            strFLOE = strFLOE & rs.Fields("DLOB2005").Value & ";"
            rs.MoveNext
        Loop
        rs.Close
        db.QueryDefs.Delete "tmpAbfrage"
        Set qd = Nothing
        db.Close
        Set db = Nothing
    End If
End Sub

Sub LadeFLOEver(lVersion As Long, strSourceDir As String, strSourceFile As String, strFLOE As String)
On Error GoTo Err_LadeFLOE_BSZN
 Dim iAusgabe As Integer
 Dim pos As Integer
 Dim strFile As String
 
    strFile = strSourceFile
    pos = InStr(strFile, "\")
    Do While pos > 0
        strFile = Mid(strFile, pos + 1)
        pos = InStr(strFile, "\")
    Loop
    
    For iAusgabe = 1 To lVersion
        LadeFLOEdir strSourceDir & Me.cboBSZN_Ausgabe.List(iAusgabe) & "\", strFile, strFLOE
    Next iAusgabe
Exit Sub

Err_LadeFLOE_BSZN:
    MsgBox Err.Description
    Resume Next

End Sub

Sub LadeObjektauswahl(strSourceDir As String, strSourceFile As String, strLIST As String)
 Dim strTemp As String
 Dim db As Database
 Dim qd As QueryDef
 Dim rs As Recordset
        
On Error Resume Next
    strLIST = ""
    Set db = OpenDatabase(strSourceDir & "Objektauswahl.mdb")
    If Err Then
    Else
        db.QueryDefs.Delete "tmpAbfrage"
        Set qd = db.CreateQueryDef("tmpAbfrage", "SELECT Objektnummer FROM Objekte WHERE Dateiname ='" & ExtractName(strSourceFile) & "'")
        Set rs = qd.OpenRecordset(dbOpenSnapshot)
        Do Until rs.EOF
            strLIST = strLIST & rs.Fields("Objektnummer").Value & ";"
            rs.MoveNext
        Loop
        rs.Close
        db.QueryDefs.Delete "tmpAbfrage"
        Set qd = Nothing
        db.Close
        Set db = Nothing
    End If
End Sub

Function ExtractPath(strFullFileName As String) As String
 Dim strPath As String
    
    If InStr(strFullFileName, "\") > 0 Then
        strPath = strFullFileName
        Do Until Right(strPath, 1) = "\"
            strPath = Left(strPath, Len(strPath) - 1)
        Loop
    Else
        ExtractPath = ""
    End If
End Function

Function ExtractName(strFullFileName As String) As String
 Dim strName As String
 Dim pos As Integer
 
    strName = strFullFileName
    pos = InStr(strName, "\")
    Do While pos > 0
        strName = Mid(strName, pos + 1)
        pos = InStr(strName, "\")
    Loop
    If InStr(strName, ".") > 0 Then
        Do
            strName = Left(strName, Len(strName) - 1)
        Loop Until Right(strName, 1) = "."
        strName = Left(strName, Len(strName) - 1)
    End If
    ExtractName = strName
End Function

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

Sub FilterEDBS1()
On Error GoTo Err_FilterEDBS1
 Dim hResult As Long
 Dim db As Database
 Dim qd As QueryDef
 Dim rs As Recordset
Dim strFolie As String
Dim strObjID As String
Dim strOutFile As String
Dim strSourceFileType As String * 2
Dim strTempFileName As String
Dim lFileCnt As Long
Dim lByteCnt As Long
Dim hSourceFile As Long
Dim hDestinationFile As Long
Dim strBuffer As String
Dim pos As Integer
Dim strKennung As String * 10
Dim strGebäudetyp As String * 4
Dim strEDBSID As String * 7
Dim strSourceDir As String
Dim strSourceFile As String
Dim strSourceFileName As String
Dim bFolgesatz As Boolean

Dim bCopy As Boolean
Dim bMaskObjectID As Boolean
Dim bMaskListe As Boolean
Dim bMaskFolie As Boolean
Dim bMaskFLOE As Boolean

Dim strTemp As String
Dim lRecords As Long
Dim strFLOE As String
Dim strLIST As String

'========================================================================
    If Me.bSepDestination(1) Then
        hDestinationFile = FreeFile
        Open Me.strDestinationFile For Output As hDestinationFile
    End If
    
    If Me.bSepSource(3) Then
        strSourceDir = Me.strSepSourceBSZN
    Else
        strSourceDir = Me.strSepSourceDir
    End If
    lFileCnt = 0
    Do While lFileCnt < Me.lboDateien.ListCount
        Me.lboDateien.ListIndex = lFileCnt
        strSourceFile = Me.lboDateien.List(lFileCnt)
        
        If Me.xMaskList Then
            strLIST = ""
            LadeObjektauswahl strSourceDir, strSourceFile, strLIST
        End If
        
'        If Me.xMaskFLOE Then
'            strFLOE = ""
'            If Me.bSepSource(3) Then
'                LadeFLOEver Me.cboBSZN_Ausgabe.ListIndex, strSourceDir, strSourceFile, strFLOE
'            Else
'                LadeFLOEver Me.cboBSZN_Ausgabe.ListCount - 1, strSourceDir, strSourceFile, strFLOE
'            End If
'        End If
        
        If Me.bSepDestination(2) Then
            hDestinationFile = FreeFile
            strOutFile = ExtractName(strSourceFile) & "." & Me.strDestinationFileExtension
            Open Me.strDestinationDir & strOutFile For Append As hDestinationFile
        End If
'--------------------------------------------------------------------
        Me!StatusBar.Panels(1).Text = strSourceDir & strSourceFile
        lFileCnt = lFileCnt + 1
        Me.ProgressBar.Max = FileLen(strSourceDir & strSourceFile) + 1
        
        strTempFileName = ""
        strSourceFileName = ""
        hSourceFile = FreeFile
On Error Resume Next
        Open strSourceDir & strSourceFile For Input As hSourceFile
        If Err Then
            MsgBox "Die Datei " & strSourceDir & strSourceFile & " konnte nicht geöffnet werden!"
            hSourceFile = 0
        End If
On Error GoTo Err_FilterEDBS1
        strSourceFileType = Input(2, #hSourceFile)
        If strSourceFileType = "PK" Then
            Close hSourceFile
            Me!StatusBar.Panels(1).Text = strSourceDir & strSourceFile & " wird entpackt ..."
            hResult = UnzipFileFromFile(strSourceDir & strSourceFile, strSourceFileName)
            Me.ProgressBar.Max = FileLen(strSourceFileName) + 1
            strTempFileName = strSourceFileName
On Error Resume Next
            Open strSourceFileName For Input As hSourceFile
            If Err Then
                MsgBox "Die Datei " & strSourceFileName & " konnte nicht geöffnet werden!"
                hSourceFile = 0
            End If
On Error GoTo Err_FilterEDBS1
        Else
            Seek hSourceFile, 1
        End If
        
        Me!StatusBar.Panels(1).Text = strSourceDir & strSourceFile & " wird verarbeitet ..."
        lByteCnt = 0
        
        If hSourceFile <> 0 Then
            Do Until EOF(hSourceFile)
                lByteCnt = lByteCnt + ReadLine(hSourceFile, strBuffer)
                If lByteCnt = Me.ProgressBar.Value Then
                    Exit Do
                End If
                Me.ProgressBar.Value = lByteCnt
                If bFolgesatz = False Then
                    bCopy = False
                End If
                If Mid(strBuffer, 13, 4) = "FLOE" Then
                    bCopy = False
                ElseIf Mid(strBuffer, 13, 4) = "BKRT" Then
                    bCopy = False
                    If Me.xMaskFLOE Then
                        Dim strFilter As String
                        If Mid(strBuffer, 37, 1) = "+" Then 'SOLDNER-Koordinaten
                            strFilter = Mid(strBuffer, 37, 4) & Mid(strBuffer, 57, 4) _
                                        & Mid(strBuffer, 47, 4) & Mid(strBuffer, 67, 4)
                        Else
                            strFilter = Mid(strBuffer, 37, 2) & Mid(strBuffer, 41, 2) _
                                        & Mid(strBuffer, 57, 2) & Mid(strBuffer, 61, 2) _
                                        & Mid(strBuffer, 39, 2) & Mid(strBuffer, 43, 2) _
                                        & Mid(strBuffer, 59, 2) & Mid(strBuffer, 63, 2)
                        End If

                        strFLOE = ""
                        If Me.bSepSource(3) Then
                            LadeFLOEver Me.cboBSZN_Ausgabe.ListIndex, strSourceDir, strFilter, strFLOE
                        Else
                            LadeFLOEver Me.cboBSZN_Ausgabe.ListCount - 1, strSourceDir, strFilter, strFLOE
                        End If
                    End If
                ElseIf Mid(strBuffer, 13, 4) <> "FEIN" Then
                    bCopy = True
                Else
                    If bFolgesatz = False Then
                        strFolie = Folie(strBuffer)
                        strObjID = ObjId(strBuffer)
                        If Me.xMaskFolie Then
                            bMaskFolie = (0 <> InStr(Me.strMaskFolie, strFolie))
                        Else
                            bMaskFolie = True
                        End If
                        If Me.xMaskObjectID Then
                            bMaskObjectID = strObjID Like Me.strMaskObjectID
                        Else
                            bMaskObjectID = True
                        End If
                        If Me.xMaskList Then
                            If Me.bSepList(1) Then
                                bMaskListe = (0 < InStr(strLIST, strObjID))
                            ElseIf Me.bSepList(2) Then
                                bMaskListe = (0 = InStr(strLIST, strObjID))
                            Else
                                bMaskListe = True
                            End If
                        Else
                            bMaskListe = True
                        End If
                        If Me.xMaskFLOE Then
                            bMaskFLOE = (0 = InStr(strFLOE, strObjID))
                        Else
                            bMaskFLOE = True
                        End If
                        bCopy = bMaskFolie And bMaskObjectID And bMaskListe And bMaskFLOE
                        If Mid(strBuffer, 23, 1) = "A" Then
                            bFolgesatz = True
                        End If
                    Else
                        If Mid(strBuffer, 23, 1) = "E" Then
                            bFolgesatz = False
                        End If
                    End If
                End If
    '            If bCopy And strObjID = "P002TNO" Then
    '                strObjID = strObjID
    '            End If
                If bCopy Then
                    Print #hDestinationFile, strBuffer
                End If
                DoEvents
            Loop
            Close hSourceFile
        End If
        If Me.bSepDestination(2) Then
            Close hDestinationFile
        End If
        If Len(strTempFileName) > 0 Then
            Kill strTempFileName
            strTempFileName = ""
        End If
    Loop
    If Me.bSepDestination(1) Then
        Close hDestinationFile
    End If
    If Me.xMaskFLOE Then
        If Not db Is Nothing Then
            db.Close
        End If
    End If
    Me!StatusBar.Panels(1).Text = ""
    MsgBox Str(lFileCnt) & " Dateien wurden verarbeitet."
    Me.ProgressBar.Value = 0
    Me.K_Exit.SetFocus
Exit Sub

Err_FilterEDBS1:
    MsgBox Err.Description
    Resume Next
End Sub
'Sub FilterEDBS2()
'Dim strOutFile As String
'Dim lFileCnt As Long
'Dim file As Long
'Dim outfile As Long
'Dim strBuffer As String
'Dim strOutBuffer As String
'Dim pos1 As Integer
'Dim pos2 As Integer
'Dim strKennung As String * 10
'Dim strGebäudetyp As String * 4
'Dim strEDBSID As String * 7
'Dim strSourceDir As String
'Dim strSourceFile As String
'Dim bFolgesatz As Boolean
'Dim bCopy As Boolean
'Dim strTemp As String
'Dim xmin, ymin, xmax, ymax
'Dim fxmin, fymin, fxmax, fymax
'Dim x, y
'Dim curObjId
'
'    pos1 = InStr(Me.strMaskKoordinaten, ";")
'    If pos1 > 0 Then
'        If IsNumeric(Mid(Me.strMaskKoordinaten, 1, pos1 - 1)) Then
'            xmin = Val(Mid(Me.strMaskKoordinaten, 1, pos1 - 1))
'        End If
'        pos2 = InStr(pos1 + 1, Me.strMaskKoordinaten, ";")
'        If pos2 > 0 Then
'            If IsNumeric(Mid(Me.strMaskKoordinaten, pos1 + 1, pos2 - 1)) Then
'                ymin = Val(Mid(Me.strMaskKoordinaten, pos1 + 1, pos2 - 1))
'            End If
'            pos1 = pos2
'            pos2 = InStr(pos1 + 1, Me.strMaskKoordinaten, ";")
'            If pos2 > 0 Then
'                If IsNumeric(Mid(Me.strMaskKoordinaten, pos1 + 1, pos2 - 1)) Then
'                    xmax = Val(Mid(Me.strMaskKoordinaten, pos1 + 1, pos2 - 1))
'                End If
'                pos1 = pos2
'                pos2 = InStr(pos1 + 1, Me.strMaskKoordinaten, ";")
'                If pos2 > 0 Then
'                    If IsNumeric(Mid(Me.strMaskKoordinaten, pos1 + 1, pos2 - 1)) Then
'                        ymax = Val(Mid(Me.strMaskKoordinaten, pos1 + 1, pos2 - 1))
'                    End If
'                End If
'            End If
'        End If
'    Else
'        xmin = 22000000
'        ymin = 24000000
'        xmax = 23000000
'        ymax = 25000000
'    End If
'    If Me.bSepSource(2) Then
'        strSourceDir = Me!strSource
'        If Mid(strSourceDir, Len(strSourceDir)) <> "\" Then
'            strSourceDir = strSourceDir & "\"
'        End If
'    Else
'        strSourceDir = ""
'        strTemp = Me.strSource
'        pos1 = InStr(strTemp, "\")
'        Do While pos1 > 0
'            strSourceDir = strSourceDir & Mid(strTemp, 1, pos1)
'            strTemp = Mid(strTemp, pos1 + 1)
'            pos1 = InStr(strTemp, "\")
'        Loop
'    End If
'    If bSepSource(2) Then
'        strSourceFile = Dir(strSourceDir & "*.001")
'    Else
'        strSourceFile = strTemp
'    End If
'    strOutFile = Me.strDestination
'    If InStr(strOutFile, "\") = 0 Then
'        strOutFile = strSourceDir & strOutFile
'    End If
'    lFileCnt = 0
'    outfile = FreeFile
'    strOutBuffer = ""
'    Open strOutFile For Output As outfile
'    Do While Len(strSourceFile) > 0
'        Me!StatusBar.Panels(1).Text = strSourceDir & strSourceFile
'        lFileCnt = lFileCnt + 1
'        file = FreeFile
'        Open strSourceDir & strSourceFile For Input As file
'        fxmin = Null
'        fymin = Null
'        fxmax = Null
'        fymax = Null
'        curObjId = "0000000"
'        Do While EOF(file) = False
'            Line Input #file, strBuffer
'            If Mid(strBuffer, 13, 4) <> "FEIN" Then
'                If Mid(strBuffer, 13, 4) = "BKRT" Then
'                    If Mid(strBuffer, 37, 1) = "+" And Mid(strBuffer, 47, 1) = "+" _
'                        And Mid(strBuffer, 57, 1) = "+" And Mid(strBuffer, 67, 1) = "+" Then
'                        If IsNumeric(Mid(strBuffer, 38, 9)) And IsNumeric(Mid(strBuffer, 48, 9)) _
'                            And IsNumeric(Mid(strBuffer, 58, 9)) And IsNumeric(Mid(strBuffer, 68, 9)) Then
'                            fxmin = Val(Mid(strBuffer, 38, 9))
'                            fymin = Val(Mid(strBuffer, 48, 9))
'                            fxmax = Val(Mid(strBuffer, 58, 9))
'                            fymax = Val(Mid(strBuffer, 68, 9))
'                            If fxmin > xmax Or fxmax < xmin Or fymin > ymax Or fymax < ymin Then
'                                Exit Do
'                            End If
'                        End If
'                    End If
'                Else
'                    bCopy = True
'                End If
'            Else
'                If bFolgesatz = False And curObjId <> ObjId(strBuffer) Then
'                    curObjId = ObjId(strBuffer)
'                    strOutBuffer = ""
'                    bCopy = False
'                End If
'                If bCopy = False Then
'                    pos1 = 1
'                    Do
'                        pos1 = InStr(pos1, strBuffer, "+")
'                        If pos1 > 0 Then
'                            If Mid(strBuffer, pos1 + 10, 1) = "+" Then
'                                If IsNumeric(Mid(strBuffer, pos1 + 1, 9)) And IsNumeric(Mid(strBuffer, pos1 + 11, 9)) Then
'                                    'Koordinate gefunden
'                                    x = Val(Mid(strBuffer, pos1 + 1, 9))
'                                    y = Val(Mid(strBuffer, pos1 + 11, 9))
'                                    If xmin <= x And x <= xmax And ymin <= y And y <= ymax Then
'                                        bCopy = True
'                                        Exit Do
'                                    End If
'                                End If
'                            End If
'                            pos1 = pos1 + 20
'                        Else
'                            Exit Do
'                        End If
'                    Loop
'                End If
'            End If
'            If Mid(strBuffer, 23, 1) = "A" Then
'                bFolgesatz = True
'            ElseIf Mid(strBuffer, 23, 1) = "E" Then
'                bFolgesatz = False
'            End If
'            If bCopy Then
'                If Len(strOutBuffer) > 0 Then
'                    Print #outfile, strOutBuffer
'                    strOutBuffer = ""
'                End If
'                Print #outfile, strBuffer
'            Else
'                If Len(strOutBuffer) = 0 Then
'                    strOutBuffer = strBuffer
'                Else
'                    strOutBuffer = strOutBuffer & Chr(13) & Chr(10) & strBuffer
'                End If
'            End If
'        Loop
'        Close file
''        MsgBox "xmin" & Str(xmin) & " ymin" & Str(ymin) & " xmax" & Str(xmax) & " ymax" & Str(ymax)
'        If bSepSource(2) Then
'            strSourceFile = Dir()
'        Else
'            strSourceFile = ""
'        End If
'    Loop
'    Close outfile
'    Me!StatusBar.Panels(1).Text = ""
'    MsgBox Str(lFileCnt) & " Dateien wurden verarbeitet."
'    Me.K_Exit.SetFocus
'
'End Sub
Private Sub K_SelectSource_Click()
End Sub


Private Sub K_SelectSourceBSZN_Click()
 Dim fSelDir As frmSelDir
 Dim strTemp As String
    Set fSelDir = New frmSelDir
    Load fSelDir
    fSelDir.Show vbModal, Me
    If fSelDir.Tag = Chr(13) Then
    Else
        Me.strSepSourceBSZN = fSelDir.Tag
        Me.bSepSource(3) = True
        LadeKatasteraemterBSZN
        Me.xMaskFLOE.Enabled = True
    
        strTemp = Dir(Me.strSepSourceBSZN & "Objektauswahl.mdb")
        If Len(strTemp) > 0 Then
            Me.xMaskList.Enabled = True
            Me.bSepList(1).Enabled = True
            Me.bSepList(2).Enabled = True
        Else
            Me.xMaskList.Enabled = False
            Me.xMaskList = False
            Me.bSepList(1).Enabled = False
            Me.bSepList(2).Enabled = False
        End If
    
    End If
    Unload fSelDir
    Set fSelDir = Nothing
End Sub

Private Sub K_SelectSourceDir_Click()
    Dim fSelDir As frmSelDir
    Set fSelDir = New frmSelDir
    Load fSelDir
    fSelDir.Show vbModal, Me
    If fSelDir.Tag = Chr(13) Then
    Else
        Me.strSepSourceDir = fSelDir.Tag
        Me.bSepSource(2) = True
        Me.bSepSourceDir(1) = True
        LadeDateienDir
    End If
    Unload fSelDir
    Set fSelDir = Nothing
End Sub

Private Sub K_SelectSourceFile_Click()
On Error Resume Next
    DlgCommon.CancelError = True
    DlgCommon.DialogTitle = "Ausgabedatei festlegen"
    DlgCommon.InitDir = strSourceDir
    DlgCommon.DefaultExt = "*.edbs"
    DlgCommon.Filter = "ALK-Dateien |*.001;*.alk;*.edb;*.edbs;*zedbs"
    DlgCommon.FileName = ""
    DlgCommon.Flags = cdlOFNFileMustExist Or cdlOFNHideReadOnly
    DlgCommon.ShowOpen
    If Err = 32755 Then 'Abbrechen gedrückt
        Exit Sub
    ElseIf Err = 0 Then
        Me.strSepSourceDir = ExtractPath(DlgCommon.FileName)
        Me.strSepSourceFile = DlgCommon.FileName
        LadeDateienFile
        SourceChanged
        Me.bSepSource(1) = True
    Else
        MsgBox Err.Description
    End If

End Sub

Private Sub SourceChanged()
On Error GoTo Err_strSource_Change
 Dim strTemp As String
 Dim pos As Integer
 
    strSourceDir = Me.strSepSourceDir
    If Len(strSourceDir) > 0 Then
        Me.bSepSourceDir(1).Enabled = True
    Else
        Me.bSepSourceDir(1).Enabled = False
    End If
    strTemp = Dir(strSourceDir & "Katasteramtsdateien.mdb")
    If Len(strTemp) > 0 Then
        Dim db As Database
        Dim td As TableDef
        Dim qd As QueryDef
        Dim rs As Recordset
        Set db = OpenDatabase(strSourceDir & "Katasteramtsdateien.mdb")
On Error Resume Next
        Set td = db.TableDefs("Bezirke")
On Error GoTo Err_strSource_Change
        If td Is Nothing Then
            Me.bSepSourceDir(2).Enabled = False
        Else
            Set td = Nothing
On Error Resume Next
            Set qd = db.QueryDefs("tmpAbfrage")
On Error GoTo Err_strSource_Change
            If qd Is Nothing Then
                Set qd = db.CreateQueryDef("tmpAbfrage", "SELECT * FROM Bezirke")
            End If
            qd.SQL = "SELECT * FROM Bezirke"
            Set rs = qd.OpenRecordset(dbOpenSnapshot)
            Do Until rs.EOF
                Me.Bezirke.AddItem rs.Fields("BZBezirk").Value
                Me.Bezirke.ItemData(Me.Bezirke.ListCount - 1) = rs.Fields("IDBezirk").Value
                rs.MoveNext
            Loop
            rs.Close
            Set rs = Nothing
            Set qd = Nothing
            Me.bSepSourceDir(2).Enabled = True
        End If
        db.Close
    Else
        Me.bSepSourceDir(2).Enabled = False
    End If
    strTemp = Dir(strSourceDir & "LIST.MDB")
    If Len(strTemp) > 0 Then
        Me.xMaskList.Enabled = True
        Me.bSepList(1).Enabled = True
        Me.bSepList(2).Enabled = True
    Else
        Me.xMaskList.Enabled = False
        Me.xMaskList = False
        Me.bSepList(1).Enabled = False
        Me.bSepList(2).Enabled = False
    End If
    strTemp = Dir(strSourceDir & "UPDTFLOE.MDB")
    If Len(strTemp) > 0 Then
        Me.xMaskFLOE.Enabled = True
    Else
        Me.xMaskFLOE.Enabled = False
        Me.xMaskFLOE = False
    End If
    strTemp = Dir(strSourceDir & "*.zedbs")
    If Len(strTemp) > 0 Then
        Me.strSourceFileExtension = "zedbs"
    Else
        strTemp = Dir(strSourceDir & "*.001")
        If Len(strTemp) > 0 Then
            Me.strSourceFileExtension = "001"
        Else
        End If
    End If
Exit Sub

Err_strSource_Change:
    MsgBox Err.Description
    Resume Next
End Sub

Private Sub strDestinationDir_Change()
    Me.bSepDestination(2) = True
End Sub

Private Sub strDestinationFile_Change()
    Me.bSepDestination(1) = True
End Sub

Private Sub strSepSourceBSZN_Change()
 Dim strTemp As String
 Dim ix As Integer
    Me.cboBSZN_Ausgabe.Clear
    ix = 0
    strTemp = Dir(strSepSourceBSZN, vbDirectory)
    Do While Len(strTemp) > 0
        If vbDirectory = (GetAttr(strSepSourceBSZN & strTemp) And vbDirectory) Then
            If Left(strTemp, 1) <> "." And Left(strTemp, 1) <> "_" Then
                Me.cboBSZN_Ausgabe.AddItem strTemp
                Me.cboBSZN_Ausgabe.ItemData(Me.cboBSZN_Ausgabe.ListCount - 1) = ix
                ix = ix + 1
            End If
        End If
        strTemp = Dir()
    Loop
    If ix > 0 Then
        Me.cboBSZN_Ausgabe.ListIndex = ix - 1
    End If
End Sub

Private Sub strSepSourceDir_Change()
    SourceChanged
    Me.bSepSource(2) = True
End Sub

Private Sub strSepSourceFile_Change()
    Me.bSepSource(1) = True
End Sub

Private Sub strSourceFileExtension_Change()
    LadeDateienDir
End Sub
