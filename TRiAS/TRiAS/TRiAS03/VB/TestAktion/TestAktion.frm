VERSION 5.00
Object = "{EF55FEE7-2EB7-4BB5-86B9-966FF997D772}#1.0#0"; "PropPageDock.ocx"
Begin VB.Form frmTestAktion 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Test zum Erzeugen einer Karteikarte"
   ClientHeight    =   2895
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4500
   Icon            =   "TestAktion.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2895
   ScaleWidth      =   4500
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin PropPageDock.PropPageDockControl PropPageDockControl1 
      Height          =   2295
      Left            =   120
      TabIndex        =   2
      Top             =   480
      Width           =   4215
      _ExtentX        =   7435
      _ExtentY        =   4048
   End
   Begin VB.CommandButton CloseButt 
      Caption         =   "&Schlieﬂen"
      Height          =   315
      Left            =   3210
      TabIndex        =   1
      Top             =   60
      Width           =   1155
   End
   Begin VB.CommandButton CreateButt 
      Caption         =   "&Erzeugen"
      Height          =   315
      Left            =   150
      TabIndex        =   0
      Top             =   60
      Width           =   1155
   End
End
Attribute VB_Name = "frmTestAktion"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub CloseButt_Click()
  Call PropPageDockControl1.CloseParent
End Sub

Private Sub CreateButt_Click()
  Call PropPageDockControl1.CreateParent _
    ("Aktion.karteikarte", Nothing, psuCustom, Nothing)
End Sub


Private Sub Form_Unload(Cancel As Integer)
  Call PropPageDockControl1.CloseParent
End Sub


