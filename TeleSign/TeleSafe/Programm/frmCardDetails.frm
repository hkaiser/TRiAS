VERSION 5.00
Begin VB.Form frmCardDetails 
   Caption         =   "Kartendeatails"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows-Standard
   Begin VB.CommandButton K_Exit 
      Caption         =   "&OK"
      Height          =   495
      Left            =   2880
      TabIndex        =   2
      Top             =   2520
      Width           =   1695
   End
   Begin VB.Label lblOwnerCommonName 
      Height          =   255
      Left            =   1560
      TabIndex        =   1
      Top             =   120
      Width           =   2895
   End
   Begin VB.Label Label1 
      Caption         =   "Inhaber"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1335
   End
End
Attribute VB_Name = "frmCardDetails"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()
On Error GoTo Err_Form_Load
 Dim svrSpezial As New TSPrinter
 Dim hResult As Long
 Dim strOwnerCommonName As String
 Dim strErrorDescription As String
 
    Set svrTSCrypt = New TSCRYPTLib.TSCryptSvr
    If svrTSCrypt Is Nothing Then
        MsgBox "Der Kryptographiemodul konnte nicht geladen werden!"
    Else
'        frmPassword.Show vbModal, Me
        If frmPassword.Tag <> Chr(13) Then
            hResult = svrTSCrypt.SetDatabase(App.Path)
'            hResult = svrTSCrypt.SetPassword_CS(frmPassword.Tag)
            hResult = svrTSCrypt.Open()
            If hResult <> 0 Then
                hResult = svrTSCrypt.GetErrorDescription(hResult, strErrorDescription)
                MsgBox strErrorDescription
            End If
'            hResult = svrTSCrypt.ImportCertificate_CS(App.Path & "\TeleSign.crt")
            hResult = svrTSCrypt.GetSCardOwnerCommonName_CS(strOwnerCommonName)
            Me.lblOwnerCommonName.Caption = strOwnerCommonName
            hResult = svrTSCrypt.Close()
'            Unload frmPassword
            Set svrTSCrypt = Nothing
            svrSpezial.spezial1
        Else
            Unload frmPassword
            Set svrTSCrypt = Nothing
            Unload Me
        End If
    End If
Exit Sub

Err_Form_Load:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Sub

Private Sub K_Exit_Click()
On Error GoTo Err_K_Exit
    Unload Me
Exit Sub

Err_K_Exit:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Sub
