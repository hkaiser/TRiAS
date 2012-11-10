VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form frmMain 
   Caption         =   "EDBS-Komprimierung"
   ClientHeight    =   3615
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6960
   LinkTopic       =   "Form1"
   ScaleHeight     =   3615
   ScaleWidth      =   6960
   StartUpPosition =   3  'Windows-Standard
   Begin VB.ListBox lboDateien 
      Height          =   2205
      Left            =   1080
      TabIndex        =   8
      Top             =   960
      Width           =   4095
   End
   Begin VB.ComboBox cboBSZN_Ausgabe 
      Height          =   315
      Left            =   1080
      TabIndex        =   6
      Top             =   480
      Width           =   4095
   End
   Begin VB.TextBox strSourceDir 
      Height          =   285
      Left            =   1080
      TabIndex        =   4
      Top             =   120
      Width           =   5415
   End
   Begin VB.CommandButton K_SelectSourceDir 
      Caption         =   "..."
      Height          =   255
      Left            =   6480
      TabIndex        =   3
      Top             =   120
      Width           =   375
   End
   Begin ComctlLib.StatusBar StatusBar 
      Align           =   2  'Unten ausrichten
      Height          =   375
      Left            =   0
      TabIndex        =   2
      Top             =   3240
      Width           =   6960
      _ExtentX        =   12277
      _ExtentY        =   661
      Style           =   1
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   1
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.CommandButton K_ZIP 
      Caption         =   "&Zippen"
      Height          =   495
      Left            =   5280
      TabIndex        =   1
      Top             =   480
      Width           =   1575
   End
   Begin VB.CommandButton K_Exit 
      Caption         =   "&Beenden"
      Height          =   495
      Left            =   5280
      TabIndex        =   0
      Top             =   1080
      Width           =   1575
   End
   Begin VB.Label Label2 
      Caption         =   "Dateien"
      Height          =   375
      Left            =   0
      TabIndex        =   9
      Top             =   960
      Width           =   975
   End
   Begin VB.Label Label3 
      Caption         =   "Ausgabe"
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   480
      Width           =   855
   End
   Begin VB.Label Label1 
      Caption         =   "Verzeichnis"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   120
      Width           =   855
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cboBSZN_Ausgabe_Click()
    Dim strBaseDir As String
    Dim strSourceDir As String
    Dim strSourceFile As String
        
    strBaseDir = Me.strSourceDir
    If right(strBaseDir, 1) <> "\" Then
        strBaseDir = strBaseDir & "\"
    End If
    strSourceDir = Me.cboBSZN_Ausgabe.List(Me.cboBSZN_Ausgabe.ListIndex)
    
    Me.lboDateien.Clear
    strSourceFile = Dir(strBaseDir & strSourceDir & "\*.*")
    Do While Len(strSourceFile) > 0
        If right(strSourceFile, 2) <> "db" Then
            Me.lboDateien.AddItem strSourceFile
        End If
        strSourceFile = Dir()
    Loop
    Me.Refresh
End Sub

Private Sub Form_Load()
    Me.strSourceDir = GetSetting("EDBS", "BSZN", "Basisverzeichnis")
End Sub

Private Sub K_Exit_Click()
    If Me.strSourceDir <> "" Then
        SaveSetting "EDBS", "BSZN", "Basisverzeichnis", Me.strSourceDir
    End If
    Unload Me
End Sub

Private Sub K_SelectSourceDir_Click()
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

Private Sub K_ZIP_Click()
On Error GoTo Err_K_ZIP
    Dim hResult As Long
    Dim strBaseDir As String
    Dim strSourceDir As String
    Dim strSourceFile As String
    Dim strSourceFileExtension As String
    Dim strDestinationDir As String
    Dim strDestinationFile As String
    Dim strDestinationFileExtension As String
    Dim lFileCnt As Long
    
    strBaseDir = Me.strSourceDir
    If right(strBaseDir, 1) <> "\" Then
        strBaseDir = strBaseDir & "\"
    End If
    strSourceDir = Me.cboBSZN_Ausgabe.List(Me.cboBSZN_Ausgabe.ListIndex)
    
    lFileCnt = 0
    Do While lFileCnt < Me.lboDateien.ListCount
        Me.lboDateien.ListIndex = lFileCnt
        strSourceFile = Me.lboDateien.List(lFileCnt)
        lFileCnt = lFileCnt + 1
        Me!StatusBar.Panels(1).Text = strSourceFile
        Me.StatusBar.Refresh
        DoEvents
        
        SetAttr strBaseDir & strSourceDir & "\" & strSourceFile, vbNormal
        strDestinationFile = strSourceFile
        Do While InStr(strDestinationFile, ".")
            strDestinationFile = Left(strDestinationFile, Len(strDestinationFile) - 1)
        Loop
        strDestinationFile = strDestinationFile & ".zedbs"
        hResult = zipFileToFile(strBaseDir & strSourceDir & "\" & strSourceFile, strBaseDir & strSourceDir & "\" & strDestinationFile)
        If 0 = hResult Then
            Kill strBaseDir & strSourceDir & "\" & strSourceFile
        End If
    Loop
    Me.StatusBar.Panels(1).Text = ""
    MsgBox Str(lFileCnt) & " wurden Dateien komprimiert!"
Exit Sub

Err_K_ZIP:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Sub

Private Sub strSourceDir_Change()
 Dim strTemp As String
 Dim ix As Integer
    Me.cboBSZN_Ausgabe.Clear
    ix = 0
    strTemp = Dir(strSourceDir, vbDirectory)
    Do While Len(strTemp) > 0
        If vbDirectory = (GetAttr(strSourceDir & strTemp) And vbDirectory) Then
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
