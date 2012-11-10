VERSION 5.00
Begin VB.Form frmSplash 
   BorderStyle     =   3  'Fester Dialog
   ClientHeight    =   4710
   ClientLeft      =   45
   ClientTop       =   45
   ClientWidth     =   7455
   ControlBox      =   0   'False
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4710
   ScaleWidth      =   7455
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'Bildschirmmitte
   Tag             =   "1049"
   Visible         =   0   'False
   Begin VB.Timer Timer1 
      Left            =   6840
      Top             =   4080
   End
   Begin VB.Frame fraMainFrame 
      Height          =   4590
      Left            =   0
      TabIndex        =   0
      Tag             =   "1050"
      Top             =   0
      Width           =   7380
      Begin VB.PictureBox picLogo 
         AutoSize        =   -1  'True
         Height          =   1800
         Left            =   120
         Picture         =   "frmSplash.frx":0000
         ScaleHeight     =   1740
         ScaleWidth      =   4245
         TabIndex        =   2
         Top             =   720
         Width           =   4305
      End
      Begin VB.Label lblWarning 
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   435
         Left            =   5040
         TabIndex        =   11
         Tag             =   "1053"
         Top             =   840
         Width           =   1935
      End
      Begin VB.Label lblVersionCryptoSeal 
         AutoSize        =   -1  'True
         Caption         =   "Version 0.9.5.0"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   240
         Left            =   180
         TabIndex        =   10
         Tag             =   "1054"
         Top             =   4080
         Width           =   1380
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "Visualisierer für digital signierte Dokumente"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   240
         Left            =   180
         TabIndex        =   9
         Top             =   3360
         Width           =   4185
      End
      Begin VB.Label lblLicenseTo 
         Alignment       =   1  'Rechts
         Caption         =   "Lizensiert für: TeleSign GmbH "
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   120
         TabIndex        =   1
         Tag             =   "1058"
         Top             =   300
         Width           =   6855
      End
      Begin VB.Label lblProductName 
         AutoSize        =   -1  'True
         Caption         =   "Visualisierer"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   32.25
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   765
         Left            =   180
         TabIndex        =   8
         Tag             =   "1057"
         Top             =   2640
         Width           =   3855
      End
      Begin VB.Label lblCompanyProduct 
         AutoSize        =   -1  'True
         Caption         =   "CompanyProduct"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   18
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   435
         Left            =   4320
         TabIndex        =   7
         Tag             =   "1056"
         Top             =   1440
         Visible         =   0   'False
         Width           =   3000
      End
      Begin VB.Label lblPlatform 
         Alignment       =   1  'Rechts
         AutoSize        =   -1  'True
         Caption         =   "Platform"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   15.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   360
         Left            =   5760
         TabIndex        =   6
         Tag             =   "1055"
         Top             =   1920
         Visible         =   0   'False
         Width           =   1275
      End
      Begin VB.Label lblVersionTeleSafe 
         AutoSize        =   -1  'True
         Caption         =   "Version 0.01"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   9.75
            Charset         =   0
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   240
         Left            =   180
         TabIndex        =   5
         Tag             =   "1054"
         Top             =   3720
         Width           =   1155
      End
      Begin VB.Label lblCompany 
         Caption         =   "TeleSign GmbH"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   4710
         TabIndex        =   4
         Tag             =   "1052"
         Top             =   2970
         Width           =   2415
      End
      Begin VB.Label lblCopyright 
         Caption         =   "Copyright © 1999"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   4710
         TabIndex        =   3
         Tag             =   "1051"
         Top             =   2760
         Width           =   2415
      End
   End
End
Attribute VB_Name = "frmSplash"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
    
'    LoadResStrings Me
    lblVersionTeleSafe.Caption = "TeleSafe Version " & App.Major & "." & App.Minor & "." & App.Revision
'    lblVersionCryptoSeal.Caption = "CryptoSeal Version " & svrCryptoSeal.Major & "." & svrCryptoSeal.Minor & "." & svrCryptoSeal.Revision
    lblProductName.Caption = App.Title
    Timer1.Interval = 5000
    Timer1.Enabled = True
End Sub

Private Sub Timer1_Timer()
    Unload Me
End Sub
