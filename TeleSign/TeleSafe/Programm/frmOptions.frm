VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form frmOptions 
   BorderStyle     =   3  'Fester Dialog
   Caption         =   "Options"
   ClientHeight    =   4860
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   6135
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4860
   ScaleWidth      =   6135
   ShowInTaskbar   =   0   'False
   StartUpPosition =   1  'Fenstermitte
   Tag             =   "1059"
   Begin TabDlg.SSTab SSTab1 
      Height          =   4215
      Left            =   120
      TabIndex        =   7
      Top             =   120
      Width           =   5895
      _ExtentX        =   10398
      _ExtentY        =   7435
      _Version        =   393216
      Tabs            =   1
      TabHeight       =   520
      TabCaption(0)   =   "Ansicht"
      TabPicture(0)   =   "frmOptions.frx":0000
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "Label1"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "Combo1"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "Check1"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).ControlCount=   3
      Begin VB.CheckBox Check1 
         Caption         =   "an Fenster angepasst"
         Height          =   375
         Left            =   3120
         TabIndex        =   10
         Top             =   840
         Width           =   1935
      End
      Begin VB.ComboBox Combo1 
         Height          =   315
         Left            =   3120
         TabIndex        =   8
         Text            =   "Combo1"
         Top             =   480
         Width           =   1695
      End
      Begin VB.Label Label1 
         Caption         =   "Darstellungsfaktor der Visualisierungen:"
         Height          =   255
         Left            =   120
         TabIndex        =   9
         Top             =   480
         Width           =   2895
      End
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Height          =   375
      Left            =   2490
      TabIndex        =   0
      Tag             =   "1066"
      Top             =   4455
      Width           =   1095
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3720
      TabIndex        =   1
      Tag             =   "1065"
      Top             =   4455
      Width           =   1095
   End
   Begin VB.CommandButton cmdApply 
      Caption         =   "Apply"
      Height          =   375
      Left            =   4920
      TabIndex        =   2
      Tag             =   "1064"
      Top             =   4455
      Width           =   1095
   End
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'Kein
      Height          =   3780
      Index           =   3
      Left            =   -20000
      ScaleHeight     =   3840.968
      ScaleMode       =   0  'Benutzer
      ScaleWidth      =   5745.64
      TabIndex        =   3
      TabStop         =   0   'False
      Top             =   480
      Width           =   5685
      Begin VB.Frame fraSample4 
         Caption         =   "Sample 4"
         Height          =   2022
         Left            =   505
         TabIndex        =   6
         Tag             =   "1063"
         Top             =   502
         Width           =   2033
      End
   End
   Begin VB.PictureBox picOptions 
      BorderStyle     =   0  'Kein
      Height          =   3780
      Index           =   2
      Left            =   -20000
      ScaleHeight     =   3840.968
      ScaleMode       =   0  'Benutzer
      ScaleWidth      =   5745.64
      TabIndex        =   4
      TabStop         =   0   'False
      Top             =   480
      Width           =   5685
      Begin VB.Frame fraSample3 
         Caption         =   "Sample 3"
         Height          =   2022
         Left            =   406
         TabIndex        =   5
         Tag             =   "1062"
         Top             =   403
         Width           =   2033
      End
   End
End
Attribute VB_Name = "frmOptions"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Public mFaktor As Double



Private Sub Check1_Click()
    If Me.Check1.Value = 1 Then
        Me.Combo1.Enabled = False
    Else
        Me.Combo1.Enabled = True
    End If
End Sub

Private Sub Form_Load()
    LoadResStrings Me

    Me.Combo1.AddItem ("3 - fach")
    Me.Combo1.AddItem ("2 - fach")
    Me.Combo1.AddItem ("Original")
    Me.Combo1.AddItem ("50 %")
    Me.Combo1.AddItem ("33 %")
    Me.Combo1.AddItem ("25 %")
    Me.Combo1.AddItem ("10 %")
    UpdateData False
End Sub

Private Sub cmdApply_Click()
    UpdateData True
    fMainForm.gPictZoomFaktor = mFaktor
    fMainForm.RefreshView
End Sub

Private Sub cmdCancel_Click()
    Unload Me
End Sub

Private Sub cmdOK_Click()
    UpdateData True
    fMainForm.gPictZoomFaktor = mFaktor
    fMainForm.RefreshView
    Unload Me
End Sub

Private Sub UpdateData(bSaveAndValidate As Boolean)
Dim i As Integer

    If bSaveAndValidate Then
        If Me.Check1.Value = 1 Then
            mFaktor = 0
        Else
            i = Me.Combo1.ListIndex
            Select Case i
            Case 0
                mFaktor = 3
            Case 1
                mFaktor = 2
            Case 2
                mFaktor = 1
            Case 3
                mFaktor = 0.5
            Case 4
                mFaktor = 0.33
            Case 5
                mFaktor = 0.25
            Case 6
                mFaktor = 0.1
    '        Else
    '            mFaktor = 0.1
            End Select
        End If
    Else
        Me.Check1.Value = 0
        If mFaktor >= 3 Then
            Me.Combo1.ListIndex = 0
        ElseIf mFaktor >= 2 Then
            Me.Combo1.ListIndex = 1
        ElseIf mFaktor >= 1 Then
            Me.Combo1.ListIndex = 2
        ElseIf mFaktor >= 0.5 Then
            Me.Combo1.ListIndex = 3
        ElseIf mFaktor >= 0.33 Then
            Me.Combo1.ListIndex = 4
        ElseIf mFaktor >= 0.25 Then
            Me.Combo1.ListIndex = 5
        ElseIf mFaktor >= 0.1 Then
            Me.Combo1.ListIndex = 6
        Else
            Me.Combo1.ListIndex = 2
            Me.Check1.Value = 1
        End If
        If Me.Check1.Value = 1 Then
            Me.Combo1.Enabled = False
        Else
            Me.Combo1.Enabled = True
        End If
    End If
End Sub
