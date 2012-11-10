VERSION 5.00
Begin VB.Form Form2 
   Caption         =   "Form2"
   ClientHeight    =   2910
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7365
   LinkTopic       =   "Form2"
   ScaleHeight     =   2910
   ScaleWidth      =   7365
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Cancel          =   -1  'True
      Caption         =   "OK"
      Height          =   495
      Left            =   2880
      TabIndex        =   2
      Top             =   2040
      Width           =   1215
   End
   Begin VB.Label Label2 
      Caption         =   $"Form2.frx":0000
      Height          =   735
      Left            =   480
      TabIndex        =   1
      Top             =   1080
      Width           =   6495
   End
   Begin VB.Label Label1 
      Caption         =   "The component SmallParser.dll is under the bin-directory. You may need to reference it to get this program to work."
      Height          =   495
      Left            =   480
      TabIndex        =   0
      Top             =   360
      Width           =   6375
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit


Private Sub Command1_Click()
    Hide
End Sub
