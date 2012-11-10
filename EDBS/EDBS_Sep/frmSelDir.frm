VERSION 5.00
Begin VB.Form frmSelDir 
   Caption         =   "Verzeichnis auswählen"
   ClientHeight    =   3975
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4095
   LinkTopic       =   "Form1"
   ScaleHeight     =   3975
   ScaleWidth      =   4095
   StartUpPosition =   1  'Fenstermitte
   Begin VB.CommandButton K_Cancel 
      Cancel          =   -1  'True
      Caption         =   "Abbre&chen"
      Height          =   375
      Left            =   1200
      TabIndex        =   3
      Top             =   3600
      Width           =   1335
   End
   Begin VB.CommandButton K_Exit 
      Caption         =   "&OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   2640
      TabIndex        =   2
      Top             =   3600
      Width           =   1335
   End
   Begin VB.DirListBox Dir1 
      Height          =   3015
      Left            =   120
      TabIndex        =   1
      Top             =   480
      Width           =   3855
   End
   Begin VB.DriveListBox Drive1 
      Height          =   315
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3855
   End
End
Attribute VB_Name = "frmSelDir"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Drive1_Change()
On Error Resume Next
    Dir1.Path = Drive1.Drive    ' When drive changes, set directory path.
End Sub

Private Sub K_Cancel_Click()
    Me.Tag = Chr(13)
    Me.Hide
End Sub

Private Sub K_Exit_Click()
    If Right(Dir1.Path, 1) = "\" Then
        Me.Tag = Dir1.Path
    Else
        Me.Tag = Dir1.Path & "\"
    End If
    Me.Hide
End Sub
