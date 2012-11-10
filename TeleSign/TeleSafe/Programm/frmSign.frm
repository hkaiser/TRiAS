VERSION 5.00
Begin VB.Form frmSign 
   BorderStyle     =   3  'Fester Dialog
   Caption         =   "Unterschreiben"
   ClientHeight    =   2490
   ClientLeft      =   2835
   ClientTop       =   3480
   ClientWidth     =   5325
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1471.174
   ScaleMode       =   0  'Benutzer
   ScaleWidth      =   4999.887
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'Bildschirmmitte
   Begin VB.Frame Frame1 
      Caption         =   "Zertifikat"
      Height          =   1095
      Left            =   120
      TabIndex        =   4
      Top             =   120
      Width           =   5055
      Begin VB.TextBox IssuerCommonName 
         BackColor       =   &H8000000A&
         BorderStyle     =   0  'Kein
         Height          =   285
         Left            =   1320
         Locked          =   -1  'True
         TabIndex        =   8
         Text            =   "Text1"
         Top             =   480
         Width           =   3615
      End
      Begin VB.TextBox OwnerCommonName 
         Appearance      =   0  '2D
         BackColor       =   &H8000000A&
         BorderStyle     =   0  'Kein
         Height          =   285
         Left            =   1320
         Locked          =   -1  'True
         TabIndex        =   7
         Text            =   "Text1"
         Top             =   240
         Width           =   3615
      End
      Begin VB.Label Label3 
         Caption         =   "Ausgestellt von"
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   480
         Width           =   1335
      End
      Begin VB.Label Label2 
         Caption         =   "Ausgestellt für"
         Height          =   255
         Left            =   120
         TabIndex        =   5
         Top             =   240
         Width           =   1335
      End
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "Unterschreiben"
      Default         =   -1  'True
      Height          =   390
      Left            =   3960
      TabIndex        =   1
      Top             =   2040
      Width           =   1260
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "&Abbrechen"
      Height          =   390
      Left            =   240
      TabIndex        =   2
      Top             =   2040
      Width           =   1260
   End
   Begin VB.TextBox strPassword 
      Height          =   345
      IMEMode         =   3  'DISABLE
      Left            =   960
      PasswordChar    =   "*"
      TabIndex        =   0
      Top             =   1320
      Width           =   1725
   End
   Begin VB.Label Label1 
      Caption         =   "Passwort:"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   1320
      Width           =   855
   End
End
Attribute VB_Name = "frmSign"
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

Private Sub Form_Load()
 Dim strCommonName As String
 Dim cx As Integer
 Dim pCertificate As Long
 Dim hResult As Long

    Me.OwnerCommonName = ""
    Me.IssuerCommonName = ""
    If svrTSCrypt Is Nothing Then
        Me.OwnerCommonName = ""
        Me.IssuerCommonName = ""
    Else
        cx = 0
        hResult = svrTSCrypt.GetFirstCertificate(pCertificate)
        Do While hResult = 0
            cx = cx + 1
            hResult = svrTSCrypt.ExportCertificate(App.Path & "\TSCurUsr.der", pCertificate)
            hResult = svrTSCrypt.GetOwnerCommonName(pCertificate, strCommonName)
            If hResult = 0 Then
                Me.OwnerCommonName = strCommonName
            End If
            hResult = svrTSCrypt.GetIssuerCommonName(pCertificate, strCommonName)
            If hResult = 0 Then
                Me.IssuerCommonName = strCommonName
            End If
            hResult = svrTSCrypt.GetNextCertificate(pCertificate)
        Loop
    End If
End Sub
