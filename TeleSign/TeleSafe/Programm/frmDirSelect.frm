VERSION 5.00
Begin VB.Form frmDirSelect 
   BorderStyle     =   3  'Fester Dialog
   Caption         =   "Verzeichnis auswählen"
   ClientHeight    =   3195
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5880
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3195
   ScaleWidth      =   5880
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows-Standard
   Begin VB.DriveListBox Drive1 
      Height          =   315
      Left            =   120
      TabIndex        =   3
      Top             =   2640
      Width           =   3975
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Abbrechen"
      Height          =   345
      Left            =   4440
      TabIndex        =   2
      Tag             =   "1069"
      Top             =   600
      Width           =   1260
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   345
      Left            =   4440
      TabIndex        =   1
      Tag             =   "1069"
      Top             =   120
      Width           =   1260
   End
   Begin VB.DirListBox Dir1 
      Height          =   2115
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   3975
   End
End
Attribute VB_Name = "frmDirSelect"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public strPfad As String

Private Sub cmdCancel_Click()
    strPfad = ""
    Me.Hide
End Sub

Private Sub cmdOK_Click()
    strPfad = Me.Dir1.Path
    Me.Hide
End Sub

Private Sub Drive1_Change()

    Me.Dir1.Path = Me.Drive1.Drive
    Me.Dir1.Refresh
End Sub
