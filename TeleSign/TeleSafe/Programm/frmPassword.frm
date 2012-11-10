VERSION 5.00
Begin VB.Form frmPassword 
   BorderStyle     =   3  'Fester Dialog
   Caption         =   "Passwort"
   ClientHeight    =   1155
   ClientLeft      =   2835
   ClientTop       =   3480
   ClientWidth     =   2700
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   682.412
   ScaleMode       =   0  'Benutzer
   ScaleWidth      =   2535.154
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'Bildschirmmitte
   Begin VB.CommandButton cmdOK 
      Caption         =   "&OK"
      Default         =   -1  'True
      Height          =   390
      Left            =   1440
      TabIndex        =   1
      Top             =   600
      Width           =   1140
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "&Abbrechen"
      Height          =   390
      Left            =   240
      TabIndex        =   2
      Top             =   600
      Width           =   1140
   End
   Begin VB.TextBox strPassword 
      Height          =   345
      IMEMode         =   3  'DISABLE
      Left            =   240
      PasswordChar    =   "*"
      TabIndex        =   0
      Top             =   120
      Width           =   2325
   End
End
Attribute VB_Name = "frmPassword"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Sub cmdCancel_Click()
    Me.Tag = Chr(13)
    Me.Hide
End Sub

Private Sub cmdOK_Click()
    Me.Tag = Me.strPassword
    Me.Hide
End Sub
