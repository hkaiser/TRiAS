VERSION 5.00
Begin VB.Form Main 
   Caption         =   "Test des StdComDlg's"
   ClientHeight    =   1785
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4305
   LinkTopic       =   "Form1"
   ScaleHeight     =   1785
   ScaleWidth      =   4305
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton ShowDialog 
      Caption         =   "Show StdComDlg"
      Height          =   615
      Left            =   960
      TabIndex        =   0
      Top             =   480
      Width           =   2415
   End
End
Attribute VB_Name = "Main"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub ShowDialog_Click()
Dim Dlg As New TRIASUI.TRiASOptionDlg
Dim R As Boolean

    R = Dlg.Show(SHOWCOMMAND_Show)
End Sub
