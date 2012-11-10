VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{20C62CAE-15DA-101B-B9A8-444553540000}#1.1#0"; "MSMAPI32.OCX"
Begin VB.Form frmMain 
   Caption         =   "TRiAS-Signature"
   ClientHeight    =   5505
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   8955
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5505
   ScaleWidth      =   8955
   StartUpPosition =   3  'Windows-Standard
   Begin ComctlLib.Toolbar tbToolBar 
      Align           =   1  'Oben ausrichten
      Height          =   390
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   8955
      _ExtentX        =   15796
      _ExtentY        =   688
      ButtonWidth     =   635
      ButtonHeight    =   582
      _Version        =   327682
   End
   Begin MSMAPI.MAPIMessages MAPIMessages1 
      Left            =   6720
      Top             =   720
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      AddressEditFieldCount=   1
      AddressModifiable=   0   'False
      AddressResolveUI=   0   'False
      FetchSorted     =   0   'False
      FetchUnreadOnly =   0   'False
   End
   Begin MSMAPI.MAPISession MAPISession1 
      Left            =   6120
      Top             =   720
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DownloadMail    =   -1  'True
      LogonUI         =   -1  'True
      NewSession      =   0   'False
   End
   Begin VB.PictureBox picCurPage 
      Height          =   1215
      Left            =   5640
      ScaleHeight     =   1155
      ScaleWidth      =   1155
      TabIndex        =   15
      Top             =   1320
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.VScrollBar VScroll1 
      Height          =   1215
      Left            =   7080
      TabIndex        =   14
      Top             =   2280
      Visible         =   0   'False
      Width           =   255
   End
   Begin VB.HScrollBar HScroll1 
      Height          =   255
      Left            =   5880
      TabIndex        =   13
      Top             =   3480
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.PictureBox picRahmen 
      Height          =   3495
      Left            =   7680
      ScaleHeight     =   3435
      ScaleWidth      =   1155
      TabIndex        =   12
      Top             =   720
      Visible         =   0   'False
      Width           =   1215
      Begin VB.Image detPicture 
         BorderStyle     =   1  'Fest Einfach
         Height          =   540
         Index           =   0
         Left            =   240
         Stretch         =   -1  'True
         Top             =   240
         Visible         =   0   'False
         Width           =   720
      End
   End
   Begin VB.PictureBox tbSeiten 
      Height          =   495
      Left            =   5520
      ScaleHeight     =   435
      ScaleWidth      =   3195
      TabIndex        =   9
      Top             =   4440
      Visible         =   0   'False
      Width           =   3255
      Begin VB.CommandButton btnNext 
         Caption         =   "nächste Seite"
         Height          =   375
         Left            =   1560
         TabIndex        =   11
         Top             =   40
         Width           =   1455
      End
      Begin VB.CommandButton btnPrev 
         Caption         =   "vorherige Seite"
         Height          =   375
         Left            =   0
         TabIndex        =   10
         Top             =   40
         Width           =   1455
      End
   End
   Begin VB.PictureBox picSplitter 
      BackColor       =   &H00808080&
      BorderStyle     =   0  'Kein
      FillColor       =   &H00808080&
      Height          =   4800
      Left            =   5400
      ScaleHeight     =   2090.126
      ScaleMode       =   0  'Benutzerdefiniert
      ScaleWidth      =   780
      TabIndex        =   7
      Top             =   705
      Visible         =   0   'False
      Width           =   72
   End
   Begin ComctlLib.TreeView tvTreeView 
      Height          =   4800
      Left            =   0
      TabIndex        =   6
      Top             =   720
      Width           =   3810
      _ExtentX        =   6720
      _ExtentY        =   8467
      _Version        =   327682
      HideSelection   =   0   'False
      Indentation     =   353
      LineStyle       =   1
      Style           =   7
      Appearance      =   1
      OLEDragMode     =   1
      OLEDropMode     =   1
   End
   Begin ComctlLib.ListView lvListView 
      Height          =   4800
      Left            =   3840
      TabIndex        =   5
      Top             =   720
      Width           =   1410
      _ExtentX        =   2487
      _ExtentY        =   8467
      View            =   3
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      OLEDragMode     =   1
      _Version        =   327682
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      OLEDragMode     =   1
      NumItems        =   0
   End
   Begin VB.PictureBox picTitles 
      Align           =   1  'Oben ausrichten
      Appearance      =   0  '2D
      BorderStyle     =   0  'Kein
      ForeColor       =   &H80000008&
      Height          =   300
      Left            =   0
      ScaleHeight     =   300
      ScaleWidth      =   8955
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   390
      Width           =   8955
      Begin VB.Label lblTitle 
         BorderStyle     =   1  'Fest Einfach
         Caption         =   " ListView:"
         Height          =   270
         Index           =   1
         Left            =   3885
         TabIndex        =   4
         Tag             =   "1048"
         Top             =   15
         Width           =   1410
      End
      Begin VB.Label lblTitle 
         BorderStyle     =   1  'Fest Einfach
         Caption         =   " TreeView:"
         Height          =   270
         Index           =   0
         Left            =   0
         TabIndex        =   3
         Tag             =   "1047"
         Top             =   0
         Width           =   3810
      End
   End
   Begin ComctlLib.StatusBar sbStatusBar 
      Align           =   2  'Unten ausrichten
      Height          =   270
      Left            =   0
      TabIndex        =   0
      Top             =   5235
      Width           =   8955
      _ExtentX        =   15796
      _ExtentY        =   476
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   3
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            AutoSize        =   1
            Object.Width           =   10160
            Text            =   "Status"
            TextSave        =   "Status"
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel2 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Style           =   6
            AutoSize        =   2
            TextSave        =   "21.02.00"
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel3 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Style           =   5
            AutoSize        =   2
            TextSave        =   "09:19"
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
   End
   Begin MSComDlg.CommonDialog dlgCommonDialog 
      Left            =   5640
      Top             =   720
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin ComctlLib.ImageList imlIcons 
      Left            =   5880
      Top             =   1320
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   11
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":030A
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":085C
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":0DAE
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":1300
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":1852
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":1DA4
            Key             =   ""
         EndProperty
         BeginProperty ListImage7 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":22F6
            Key             =   ""
         EndProperty
         BeginProperty ListImage8 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":2848
            Key             =   ""
         EndProperty
         BeginProperty ListImage9 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":2D9A
            Key             =   ""
         EndProperty
         BeginProperty ListImage10 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":32EC
            Key             =   ""
         EndProperty
         BeginProperty ListImage11 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "frmMain.frx":383E
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Label txtWeitere 
      Caption         =   "... weitere Seiten"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   5640
      TabIndex        =   8
      Top             =   3840
      Width           =   1815
   End
   Begin ComctlLib.ImageList imlButtonSymbols 
      Left            =   5880
      Top             =   1920
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   327682
   End
   Begin VB.Image imgSplitter 
      Height          =   4785
      Left            =   3720
      MousePointer    =   9  'Größenänderung W O
      Top             =   705
      Width           =   150
   End
   Begin VB.Menu mnuFile 
      Caption         =   "1000"
      Begin VB.Menu mnuFileOpen 
         Caption         =   "1001"
      End
      Begin VB.Menu mnuFileBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileSave 
         Caption         =   "1002"
      End
      Begin VB.Menu mnuFileSaveAs 
         Caption         =   "1003"
      End
      Begin VB.Menu mnuFileSend 
         Caption         =   "1008"
      End
      Begin VB.Menu mnuFileBar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFilePrinterSetup 
         Caption         =   "1005"
         Enabled         =   0   'False
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFilePrint 
         Caption         =   "1004"
      End
      Begin VB.Menu mnuFileBar3 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileDelete 
         Caption         =   "1006"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFileProperties 
         Caption         =   "1007"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFileBar4 
         Caption         =   "-"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuFileClose 
         Caption         =   "1009"
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "2000"
      Begin VB.Menu mnuEditKeyPool 
         Caption         =   "2100"
      End
      Begin VB.Menu mnuEditSign 
         Caption         =   "2210"
      End
      Begin VB.Menu mnuEditVerify 
         Caption         =   "2220"
      End
      Begin VB.Menu mnuEditEncrypt 
         Caption         =   "2230"
      End
      Begin VB.Menu mnuEditEncryptAll 
         Caption         =   "2231"
      End
      Begin VB.Menu mnuEditDecrypt 
         Caption         =   "2240"
      End
      Begin VB.Menu mnuEditBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditWriteFile 
         Caption         =   "1014"
      End
      Begin VB.Menu mnuEditNewVisu 
         Caption         =   "1015"
         Visible         =   0   'False
      End
      Begin VB.Menu mnuEditAddFile 
         Caption         =   "1016"
      End
      Begin VB.Menu mnuEditBar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditShowDetails 
         Caption         =   "1017"
      End
   End
   Begin VB.Menu mnuView 
      Caption         =   "1018"
      Begin VB.Menu mnuViewToolbar 
         Caption         =   "1019"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuViewStatusBar 
         Caption         =   "1020"
         Checked         =   -1  'True
      End
      Begin VB.Menu mnuViewBar2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuViewOptions 
         Caption         =   "1031"
      End
      Begin VB.Menu mnuViewBrowser 
         Caption         =   "1081"
         Visible         =   0   'False
      End
   End
   Begin VB.Menu mnuKarte 
      Caption         =   "1082"
      Begin VB.Menu mnuKarteDetails 
         Caption         =   "1083"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "1032"
      Visible         =   0   'False
      Begin VB.Menu mnuHelpContents 
         Caption         =   "1033"
      End
      Begin VB.Menu mnuHelpSearch 
         Caption         =   "1034"
      End
      Begin VB.Menu mnuHelpBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "1035"
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Option Base 1

Const ELEMENT_DUMMY = "                                                                "
Const ELEMENT_BEGIN = "FEZ#Potsdam#GmbH"
Const ELEMENT_END = "HbmG#madstoP#ZEF"
Const ELEMENT_BEGIN2 = "FEZ§Potsdam§GmbH"
Const ELEMENT_END2 = "HbmG§madstoP§ZEF"
Const NAME_COLUMN = 0
Const TYPE_COLUMN = 1
Const SIZE_COLUMN = 2
Const DATE_COLUMN = 3

Private Declare Function OSWinHelp% Lib "user32" Alias "WinHelpA" (ByVal hWnd&, ByVal HelpFile$, ByVal wCommand%, dwData As Any)

'Public gColDokumente As gColNodes
'Private gAktDok As cNode
'Private gAktPage As cSeite
'Private gAktSign As cSignatur
'Private gZahlSeiten As Integer
'Private gAktSeite As Integer
'Public gColDateien As ccDateien
'Public gDokFileVersion As Integer
'Public gDokFileMajor As Long
'Public gDokFileMinor As Long
'Public gDokFileRevision As Long
'Public gHeaderLen As Long

Private gEnableDroping As Boolean
'Private gTempFileName As String
Private gDokFileName As String

Public gPictZoomFaktor As Double
Public gPictInfo As New cPictInfo

Private nViewMode As Integer
Dim mbMoving As Boolean
Private gbDisableResize As Boolean

Public gTempArray As ccTempFileArray

Const sglSplitLimit = 500

Sub DisplayErrordescription(hResult As Long)
Dim strErrorDescription As String
    If hResult <> 0 Then
        If svrTSCrypt Is Nothing Then
        Else
            svrTSCrypt.GetErrorDescription hResult, strErrorDescription
            MsgBox "Fehler " & Hex(hResult) & ": " & strErrorDescription
        End If
    End If
End Sub

Sub LoadPage(ixPage As Integer)
On Error GoTo Err_LoadPage
 Dim Page As cNode
    detPicture(0).Visible = False
    If gCurElement.Class = "Visualisierung" Then
        If 0 < ixPage And ixPage <= gCurElement.SubNodes.Count Then
            Set Page = gCurElement.SubNodes.Item(ixPage)
            lblTitle(1).Caption = Page.Caption
            detPicture(0).Stretch = False
            detPicture(0).Picture = LoadPicture(Page.TempFileName)
            detPicture(0).Refresh
            gPictInfo.Key = Page.UniqueKey
            gPictInfo.xSize = detPicture(0).Width
            gPictInfo.ySize = detPicture(0).Height
            detPicture(0).Stretch = True
        End If
    ElseIf gCurElement.Class = "Seite" Then
        lblTitle(1).Caption = gCurElement.Caption
        detPicture(0).Stretch = False
        detPicture(0).Picture = LoadPicture(gCurElement.TempFileName)
        detPicture(0).Refresh
        gPictInfo.Key = gCurElement.UniqueKey
        gPictInfo.xSize = detPicture(0).Width
        gPictInfo.ySize = detPicture(0).Height
        detPicture(0).Stretch = True
    End If
Exit Sub

Err_LoadPage:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "LoadPage"
    Resume Next
End Sub
Sub ConfigToolBar()
    If gCurElement Is Nothing Then
        tbToolBar.Buttons("ViewDet").Visible = False
        tbToolBar.Buttons("PreviousPage").Visible = False
        tbToolBar.Buttons("NextPage").Visible = False
    Else
        If gCurElement.Class = "Visualisierung" Then
            tbToolBar.Buttons("ViewDet").Visible = True
            tbToolBar.Buttons("PreviousPage").Visible = True
            tbToolBar.Buttons("NextPage").Visible = True
            tbToolBar.Buttons("PreviousPage").Enabled = (1 < gAktSeite)
            tbToolBar.Buttons("NextPage").Enabled = (gZahlSeiten > 1) And (gCurElement.SubNodes.Count > gAktSeite)
        ElseIf gCurElement.Class = "Seite" Then
            tbToolBar.Buttons("ViewDet").Visible = True
            tbToolBar.Buttons("PreviousPage").Visible = True
            tbToolBar.Buttons("NextPage").Visible = True
            tbToolBar.Buttons("PreviousPage").Enabled = (1 < gAktSeite)
            tbToolBar.Buttons("NextPage").Enabled = (gZahlSeiten > 1) And (gCurElement.Parent.SubNodes.Count > gAktSeite)
        Else
            tbToolBar.Buttons("ViewDet").Visible = False
            tbToolBar.Buttons("PreviousPage").Visible = False
            tbToolBar.Buttons("NextPage").Visible = False
        End If
    End If
End Sub

Sub gotoPreviousPage()
Dim Key As String, i As Integer

    gbDisableResize = True
    detPicture(0).Visible = False
    If "Seite" = gCurElement.Class Then
        Key = gCurElement.Parent.SubNodes.Item(gAktSeite - 1).UniqueKey
        For i = 1 To tvTreeView.Nodes.Count
            If tvTreeView.Nodes.Item(i).Key = Key Then
                SetSelectedNode tvTreeView.Nodes.Item(i)
                Exit For
            End If
        Next i
    Else
        gAktSeite = gAktSeite - 1
        LoadPage gAktSeite
    End If
    ConfigToolBar
'    detPicture(0).Visible = True
    HScroll1_Change
    VScroll1_Change
    gbDisableResize = False
    SizeControls imgSplitter.Left

End Sub
Sub gotoNextPage()
Dim Key As String, i As Integer
    gbDisableResize = True
    detPicture(0).Visible = False
    If "Seite" = gCurElement.Class Then
        Key = gCurElement.Parent.SubNodes.Item(gAktSeite + 1).UniqueKey
        For i = 1 To tvTreeView.Nodes.Count
            If tvTreeView.Nodes.Item(i).Key = Key Then
                SetSelectedNode tvTreeView.Nodes.Item(i)
                Exit For
            End If
        Next i
        LoadPage gAktSeite
    ElseIf gCurElement.Class = "Visualisierung" Then
        gAktSeite = gAktSeite + 1
        LoadPage gAktSeite
    End If
    ConfigToolBar
    HScroll1_Change
    VScroll1_Change
    gbDisableResize = False
    SizeControls imgSplitter.Left
End Sub

'Public Sub SetElementDummy(baBuffer() As Byte, lPos As Long)
'    Dim lx As Long
'    For lx = 0 To Len(ELEMENT_DUMMY) - 1
'        baBuffer(lPos + lx) = Asc(Mid(ELEMENT_DUMMY, lx + 1, 1))
'    Next
'End Sub
'
'Public Sub SetElementBegin(baBuffer() As Byte, lPos As Long)
'    Dim lx As Long
'    For lx = 0 To Len(ELEMENT_BEGIN) - 1
'        baBuffer(lPos + lx) = Asc(Mid(ELEMENT_BEGIN, lx + 1, 1))
'    Next
'End Sub
'
'Public Sub SetElementEnd(baBuffer() As Byte, lPos As Long)
'    Dim lx As Long
'    For lx = 0 To Len(ELEMENT_END) - 1
'        baBuffer(lPos + lx) = Asc(Mid(ELEMENT_END, lx + 1, 1))
'    Next
'End Sub
'
'Public Sub SetElementBegin2(baBuffer() As Byte, lPos As Long)
'    Dim lx As Long
'    For lx = 0 To Len(ELEMENT_BEGIN2) - 1
'        baBuffer(lPos + lx) = Asc(Mid(ELEMENT_BEGIN2, lx + 1, 1))
'    Next
'End Sub
'
'Public Sub SetElementEnd2(baBuffer() As Byte, lPos As Long)
'    Dim lx As Long
'    For lx = 0 To Len(ELEMENT_END2) - 1
'        baBuffer(lPos + lx) = Asc(Mid(ELEMENT_END2, lx + 1, 1))
'    Next
'End Sub
'
'Public Sub SetElementFromFile(hFile As Long, baBuffer() As Byte, lPos As Long, lLen As Long)
'    Dim lx As Long
'    For lx = 0 To lLen - 1
'        baBuffer(lPos + lx) = InputB(1, #hFile)
'    Next
'End Sub
'
'Public Sub SetElementFromBuffer(baSource() As Byte, lSourcePos As Long, baBuffer() As Byte, lPos As Long, lLen As Long)
'    Dim lx As Long
'    For lx = 0 To lLen - 1
'        baBuffer(lPos + lx) = baSource(lSourcePos + lx)
'    Next
'End Sub
'
'Public Function FindElementBegin(baBuffer As Variant, lStartPos As Long) As Long
' Dim lx As Long
'    If TypeName(baBuffer) <> "Byte()" Then
'        MsgBox "Ungültiger Varianttyp " & TypeName(baBuffer) & " in Funktion FindElementBegin!"
'        FindElementBegin = 1
'        Exit Function
'    End If
'    For lx = lStartPos To UBound(baBuffer) - 15
'        If baBuffer(lx) = Asc(Mid(ELEMENT_BEGIN, 1, 1)) Then
'         If baBuffer(lx + 1) = Asc(Mid(ELEMENT_BEGIN, 2, 1)) Then
'          If baBuffer(lx + 2) = Asc(Mid(ELEMENT_BEGIN, 3, 1)) Then
'           If baBuffer(lx + 3) = Asc(Mid(ELEMENT_BEGIN, 4, 1)) Then
'            If baBuffer(lx + 4) = Asc(Mid(ELEMENT_BEGIN, 5, 1)) Then
'             If baBuffer(lx + 5) = Asc(Mid(ELEMENT_BEGIN, 6, 1)) Then
'              If baBuffer(lx + 6) = Asc(Mid(ELEMENT_BEGIN, 7, 1)) Then
'               If baBuffer(lx + 7) = Asc(Mid(ELEMENT_BEGIN, 8, 1)) Then
'                If baBuffer(lx + 8) = Asc(Mid(ELEMENT_BEGIN, 9, 1)) Then
'                 If baBuffer(lx + 9) = Asc(Mid(ELEMENT_BEGIN, 10, 1)) Then
'                  If baBuffer(lx + 10) = Asc(Mid(ELEMENT_BEGIN, 11, 1)) Then
'                   If baBuffer(lx + 11) = Asc(Mid(ELEMENT_BEGIN, 12, 1)) Then
'                    If baBuffer(lx + 12) = Asc(Mid(ELEMENT_BEGIN, 13, 1)) Then
'                     If baBuffer(lx + 13) = Asc(Mid(ELEMENT_BEGIN, 14, 1)) Then
'                      If baBuffer(lx + 14) = Asc(Mid(ELEMENT_BEGIN, 15, 1)) Then
'                       If baBuffer(lx + 15) = Asc(Mid(ELEMENT_BEGIN, 16, 1)) Then
'                           FindElementBegin = lx
'                           Exit Function
'                       End If
'                      End If
'                     End If
'                    End If
'                   End If
'                  End If
'                 End If
'                End If
'               End If
'              End If
'             End If
'            End If
'           End If
'          End If
'         End If
'        End If
'    Next
'    FindElementBegin = -1
'End Function
'
'Public Function FindElementEnd(baBuffer As Variant, lStartPos As Long) As Long
' Dim lx As Long
'    If TypeName(baBuffer) <> "Byte()" Then
'        MsgBox "Ungültiger Varianttyp " & TypeName(baBuffer) & " in Funktion FindElementEnd!"
'        FindElementEnd = 1
'        Exit Function
'    End If
'    For lx = UBound(baBuffer) - 15 To lStartPos Step -1
'        If baBuffer(lx) = Asc(Mid(ELEMENT_END, 1, 1)) Then
'         If baBuffer(lx + 1) = Asc(Mid(ELEMENT_END, 2, 1)) Then
'          If baBuffer(lx + 2) = Asc(Mid(ELEMENT_END, 3, 1)) Then
'           If baBuffer(lx + 3) = Asc(Mid(ELEMENT_END, 4, 1)) Then
'            If baBuffer(lx + 4) = Asc(Mid(ELEMENT_END, 5, 1)) Then
'             If baBuffer(lx + 5) = Asc(Mid(ELEMENT_END, 6, 1)) Then
'              If baBuffer(lx + 6) = Asc(Mid(ELEMENT_END, 7, 1)) Then
'               If baBuffer(lx + 7) = Asc(Mid(ELEMENT_END, 8, 1)) Then
'                If baBuffer(lx + 8) = Asc(Mid(ELEMENT_END, 9, 1)) Then
'                 If baBuffer(lx + 9) = Asc(Mid(ELEMENT_END, 10, 1)) Then
'                  If baBuffer(lx + 10) = Asc(Mid(ELEMENT_END, 11, 1)) Then
'                   If baBuffer(lx + 11) = Asc(Mid(ELEMENT_END, 12, 1)) Then
'                    If baBuffer(lx + 12) = Asc(Mid(ELEMENT_END, 13, 1)) Then
'                     If baBuffer(lx + 13) = Asc(Mid(ELEMENT_END, 14, 1)) Then
'                      If baBuffer(lx + 14) = Asc(Mid(ELEMENT_END, 15, 1)) Then
'                       If baBuffer(lx + 15) = Asc(Mid(ELEMENT_END, 16, 1)) Then
'                           FindElementEnd = lx
'                           Exit Function
'                       End If
'                      End If
'                     End If
'                    End If
'                   End If
'                  End If
'                 End If
'                End If
'               End If
'              End If
'             End If
'            End If
'           End If
'          End If
'         End If
'        End If
'    Next
'    FindElementEnd = -1
'End Function
'Public Function FindElementBegin2(baBuffer() As Byte, lStartPos As Long) As Long
'    Dim lx As Long
'    For lx = lStartPos To UBound(baBuffer) - 15
'        If baBuffer(lx) = Asc(Mid(ELEMENT_BEGIN2, 1, 1)) Then
'         If baBuffer(lx + 1) = Asc(Mid(ELEMENT_BEGIN2, 2, 1)) Then
'          If baBuffer(lx + 2) = Asc(Mid(ELEMENT_BEGIN2, 3, 1)) Then
'           If baBuffer(lx + 3) = Asc(Mid(ELEMENT_BEGIN2, 4, 1)) Then
'            If baBuffer(lx + 4) = Asc(Mid(ELEMENT_BEGIN2, 5, 1)) Then
'             If baBuffer(lx + 5) = Asc(Mid(ELEMENT_BEGIN2, 6, 1)) Then
'              If baBuffer(lx + 6) = Asc(Mid(ELEMENT_BEGIN2, 7, 1)) Then
'               If baBuffer(lx + 7) = Asc(Mid(ELEMENT_BEGIN2, 8, 1)) Then
'                If baBuffer(lx + 8) = Asc(Mid(ELEMENT_BEGIN2, 9, 1)) Then
'                 If baBuffer(lx + 9) = Asc(Mid(ELEMENT_BEGIN2, 10, 1)) Then
'                  If baBuffer(lx + 10) = Asc(Mid(ELEMENT_BEGIN2, 11, 1)) Then
'                   If baBuffer(lx + 11) = Asc(Mid(ELEMENT_BEGIN2, 12, 1)) Then
'                    If baBuffer(lx + 12) = Asc(Mid(ELEMENT_BEGIN2, 13, 1)) Then
'                     If baBuffer(lx + 13) = Asc(Mid(ELEMENT_BEGIN2, 14, 1)) Then
'                      If baBuffer(lx + 14) = Asc(Mid(ELEMENT_BEGIN2, 15, 1)) Then
'                       If baBuffer(lx + 15) = Asc(Mid(ELEMENT_BEGIN2, 16, 1)) Then
'                           FindElementBegin2 = lx
'                           Exit Function
'                       End If
'                      End If
'                     End If
'                    End If
'                   End If
'                  End If
'                 End If
'                End If
'               End If
'              End If
'             End If
'            End If
'           End If
'          End If
'         End If
'        End If
'    Next
'    FindElementBegin2 = -1
'End Function
'
'Public Function FindElementEnd2(baBuffer() As Byte, lStartPos As Long) As Long
'    Dim lx As Long
'    For lx = lStartPos To UBound(baBuffer) - 15
'        If baBuffer(lx) = Asc(Mid(ELEMENT_END2, 1, 1)) Then
'         If baBuffer(lx + 1) = Asc(Mid(ELEMENT_END2, 2, 1)) Then
'          If baBuffer(lx + 2) = Asc(Mid(ELEMENT_END2, 3, 1)) Then
'           If baBuffer(lx + 3) = Asc(Mid(ELEMENT_END2, 4, 1)) Then
'            If baBuffer(lx + 4) = Asc(Mid(ELEMENT_END2, 5, 1)) Then
'             If baBuffer(lx + 5) = Asc(Mid(ELEMENT_END2, 6, 1)) Then
'              If baBuffer(lx + 6) = Asc(Mid(ELEMENT_END2, 7, 1)) Then
'               If baBuffer(lx + 7) = Asc(Mid(ELEMENT_END2, 8, 1)) Then
'                If baBuffer(lx + 8) = Asc(Mid(ELEMENT_END2, 9, 1)) Then
'                 If baBuffer(lx + 9) = Asc(Mid(ELEMENT_END2, 10, 1)) Then
'                  If baBuffer(lx + 10) = Asc(Mid(ELEMENT_END2, 11, 1)) Then
'                   If baBuffer(lx + 11) = Asc(Mid(ELEMENT_END2, 12, 1)) Then
'                    If baBuffer(lx + 12) = Asc(Mid(ELEMENT_END2, 13, 1)) Then
'                     If baBuffer(lx + 13) = Asc(Mid(ELEMENT_END2, 14, 1)) Then
'                      If baBuffer(lx + 14) = Asc(Mid(ELEMENT_END2, 15, 1)) Then
'                       If baBuffer(lx + 15) = Asc(Mid(ELEMENT_END2, 16, 1)) Then
'                           FindElementEnd2 = lx
'                           Exit Function
'                       End If
'                      End If
'                     End If
'                    End If
'                   End If
'                  End If
'                 End If
'                End If
'               End If
'              End If
'             End If
'            End If
'           End If
'          End If
'         End If
'        End If
'    Next
'    FindElementEnd2 = -1
'End Function

Public Sub RefreshListe()
On Error GoTo Err_RefreshListe
 Dim nd As Node, dat As cNode, dok As cNode
 Dim nx As Integer, j As Integer, np As Node
 Dim seite As cNode, sign As cNode

    gZahlSeiten = 0
    gAktSeite = 1
    If Not gCurElement Is Nothing Then
        If gCurElement.Class = "Visualisierung" Then
            gZahlSeiten = gCurElement.SubNodes.Count
        End If
        If gCurElement.Class = "Seite" Then
            gZahlSeiten = gCurElement.Parent.SubNodes.Count
        End If
    End If
    ConfigToolBar
    
    tvTreeView.Visible = False
    Refresh
    tvTreeView.Nodes.Clear
    gNode.SubNodes.BuildTreeView tvTreeView, Nothing
    
    tvTreeView.Visible = True
    If tvTreeView.Nodes.Count > 0 Then
        Set tvTreeView.SelectedItem = tvTreeView.Nodes.Item(1)
        tvTreeView_Click
    End If
Exit Sub

Err_RefreshListe:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "RefreshList"
    Resume Next
End Sub

Private Sub detPicture_DblClick(index As Integer)
   If nViewMode = 1 Then
        gAktSeite = index
        nViewMode = 2
'        ZeigeDetails , gAktDok '#FJE
        ConfigToolBar
    End If
End Sub

Private Sub Form_Unload(CANCEL As Integer)
 Dim hResult As Long
 Dim i As Integer
    
'    hResult = svrTSCrypt.Logoff(fMainForm.hWnd)
    
    Set gCurElement = Nothing
    Set gPrvElement = Nothing
    Set gNode = Nothing
    Set gTempArray = Nothing
    
End Sub

Private Sub HScroll1_Change()
'    detPicture(gAktSeite).Left = -HScroll1.Value
    detPicture(0).Left = -HScroll1.Value
'    If HScroll1.Value = 0 Then
'        detPicture(gAktSeite).Left = 10
'    ElseIf HScroll1.Value = HScroll1.Max Then
'        detPicture(gAktSeite).Left = detPicture(gAktSeite).Width - picRahmen.Width
'    Else
'        detPicture(gAktSeite).Left = -(HScroll1.Value * picRahmen.Width)
'    End If
End Sub

Private Sub HScroll1_KeyDown(KeyCode As Integer, Shift As Integer)
    If KeyCode = vbKeyPageDown Then
        MsgBox "Hallo"
        KeyCode = 0
    End If
End Sub

Private Sub mnuEditAddFile_Click()
On Error GoTo Err_mnuEditAddFile
Dim oFile As cNode
Dim sFile As String

    With dlgCommonDialog
        .Filter = "Alle Dateien (*.*)|*.*"
        .DialogTitle = "Anlage hinzufügen"
        .Flags = cdlOFNHideReadOnly
        .ShowOpen
        If Len(.FileName) = 0 Then
            Exit Sub
        End If
            
        Set oFile = gNode.SubNodes.Add("Anlage")
        If oFile.LoadFromFile(.FileName) = False Then
            MsgBox "Die Datei " & .FileName & " konnte nicht geladen werden!"
        Else
            oFile.Caption = oFile.FileName
        End If
        Set oFile = Nothing
        
        RefreshListe
    End With
Exit Sub

Err_mnuEditAddFile:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next

End Sub
Private Sub mnuEditSign_Click()
On Error GoTo Err_mnuEditSign
 Dim svrSpezial As New TSPrinter
 Dim hResult As Long
 Dim tSigned As Boolean
 Dim oSignature As cNode
 Dim oCertificate As cNode
 Dim strOwnerCommonName As String
 Dim hSignerUser As Long
 Dim hSignerCertificate As Long
 Dim strContentFileName As String
 Dim strSignerCertificateFileName As String
 Dim strSignerInfoFileName As String
    
    If gNode.SubNodes.Count = 0 Then
        Exit Sub
    End If
    If gCurElement Is Nothing Then
        MsgBox "Sie müssen erst eine Visualisierung auswählen!"
        Exit Sub
    End If
    If gCurElement.Class <> "Visualisierung" Then
        MsgBox "Sie müssen erst eine Visualisierung auswählen!"
        Exit Sub
    End If
    If gCurElement.ZahlSeiten = 0 Then
        MsgBox "Die ausgewählte Visualisierung ist leer!"
        Exit Sub
    End If
 
    fMainForm.sbStatusBar.Panels(1).text = "Dokument wird vorbereitet..."
    strContentFileName = GetTempName
    hResult = gCurElement.SaveToTSD(strContentFileName, True)
    tSigned = False
'======================================================================
    Set svrTSCrypt = New TSCRYPTLib.TSCryptSvr
    If svrTSCrypt Is Nothing Then
        MsgBox "Der Kryptographiemodul konnte nicht geladen werden!"
    Else
        hResult = svrTSCrypt.SetDatabase(App.Path)
        DisplayErrordescription hResult
        hResult = svrTSCrypt.Open()
        DisplayErrordescription hResult
        frmSign.Show vbModal, Me
        If frmSign.Tag <> Chr(13) Then
            hResult = svrTSCrypt.SetPassword(frmSign.Tag)
            DisplayErrordescription hResult
            hResult = svrTSCrypt.Open()
            DisplayErrordescription hResult
            fMainForm.sbStatusBar.Panels(1).text = "Dokument wird übergeben..."
            fMainForm.sbStatusBar.Refresh
            hResult = svrTSCrypt.LoadContent(strContentFileName)
            DisplayErrordescription hResult
            fMainForm.sbStatusBar.Panels(1).text = "Dokument wird unterschrieben..."
            hResult = svrTSCrypt.Sign_CS()
            If hResult <> 0 Then
                MsgBox "Während des Unterschreibens sind Fehler aufgetreten!" & Chr(13) & "Die Visualisierung wurde nicht unterschrieben!", vbApplicationModal Or vbOKOnly Or vbCritical
            Else
                hResult = svrTSCrypt.GetUser(0, hSignerUser)
                If hResult <> 0 Then
                Else
                    hResult = svrTSCrypt.GetUserCertificate(hSignerUser, hSignerCertificate)
                    If hResult <> 0 Then
                    Else
                    End If
                End If
                tSigned = True
                If tSigned Then
                    fMainForm.sbStatusBar.Panels(1).text = "Unterschrift und Zertifikat werden übernommen..."
                    gCurElement.Parent.signed = True
                    Set oSignature = gCurElement.Parent.SubNodes.Add("Unterschrift")
                    hResult = svrTSCrypt.GetOwnerCommonName(hSignerCertificate, strOwnerCommonName)
                    oSignature.Caption = "Unterschrift " & strOwnerCommonName
                    strSignerInfoFileName = GetTempName
                    hResult = svrTSCrypt.SaveSignerInfo(hSignerUser, strSignerInfoFileName)
                    If hResult <> 0 Then
                    Else
                        oSignature.SetFromFile strSignerInfoFileName
                    End If
                   
                    Set oCertificate = oSignature.SubNodes.Add("Zertifikat")
                    strSignerCertificateFileName = GetTempName
                    hResult = svrTSCrypt.ExportCertificate(strSignerCertificateFileName, hSignerCertificate)
                    oCertificate.SetFromFile strSignerCertificateFileName
                    oCertificate.Caption = "Zertifikat " & strOwnerCommonName
                    RefreshListe
                    tSigned = False
                    MsgBox "Die Visualisierung wurde unterschrieben!", vbApplicationModal Or vbOKOnly Or vbInformation
                End If
            End If
        End If
        hResult = svrTSCrypt.Close()
        Unload frmSign
        Set svrTSCrypt = Nothing
        svrSpezial.spezial1
    End If
    fMainForm.sbStatusBar.Panels(1).text = ""
On Error Resume Next
    Kill strContentFileName
Exit Sub

Err_mnuEditSign:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next

End Sub

Private Sub mnuEditVerify_Click()
On Error GoTo Err_mnuEditVerify
 Dim hResult As Long
 Dim sx As Integer
 Dim hSignerUser As Long
 Dim hSignerCertificate As Long
 Dim strContentFileName As String
    If gNode.SubNodes.Count = 0 Then
        Exit Sub
    End If
    If gCurElement Is Nothing Then
        MsgBox "Sie müssen erst ein Dokument oder eine Unterschrift auswählen!"
        Exit Sub
    End If
    If gCurElement.Class <> "Dokument" And gCurElement.Class <> "Unterschrift" Then
        MsgBox "Sie müssen erst ein Dokument oder eine Unterschrift auswählen!"
        Exit Sub
    End If
    If gCurElement.Class = "Dokument" And gCurElement.ZahlSignaturen = 0 Then
        MsgBox "Das ausgewählte Dokument ist nicht unterschrieben!"
        Exit Sub
    End If

 

    fMainForm.sbStatusBar.Panels(1).text = "Dokument wird vorbereitet..."
    strContentFileName = GetTempName
    If gCurElement.Class = "Unterschrift" Then
        hResult = gCurElement.Parent.Visualisation(1).SaveToTSD(strContentFileName, True)
    ElseIf gCurElement.Class = "Dokument" Then
        hResult = gCurElement.Visualisation(1).SaveToTSD(strContentFileName, True)
    End If
    Set svrTSCrypt = New TSCRYPTLib.TSCryptSvr
    If svrTSCrypt Is Nothing Then
        MsgBox "Der Kryptographiemodul konnte nicht geladen werden!"
    Else
        hResult = svrTSCrypt.SetDatabase(App.Path)
        DisplayErrordescription hResult
        hResult = svrTSCrypt.SetPassword("")
        DisplayErrordescription hResult
        hResult = svrTSCrypt.Open()
        DisplayErrordescription hResult
        fMainForm.sbStatusBar.Panels(1).text = "Dokument wird übergeben..."
        fMainForm.sbStatusBar.Refresh
        hResult = svrTSCrypt.LoadContent(strContentFileName)
        
        If gCurElement.Class = "Unterschrift" Then
            fMainForm.sbStatusBar.Panels(1).text = "Unterschrift wird übergeben..."
            hResult = svrTSCrypt.ImportCertificates(gCurElement.SubNodes.Item(1).TempFileName)
            DisplayErrordescription hResult
            hResult = svrTSCrypt.AddUserBySignerInfoFile(gCurElement.TempFileName)
            DisplayErrordescription hResult
        ElseIf gCurElement.Class = "Dokument" Then
            fMainForm.sbStatusBar.Panels(1).text = "Unterschriften werden übergeben..."
            For sx = 1 To gCurElement.ZahlSignaturen
                hResult = svrTSCrypt.ImportCertificates(gCurElement.Signature(sx).SubNodes.Item(1).TempFileName)
                DisplayErrordescription hResult
                hResult = svrTSCrypt.AddUserBySignerInfoFile(gCurElement.Signature(1).TempFileName)
                DisplayErrordescription hResult
            Next sx
        End If
        
Dim lUserCount As Long
Dim hUser As Long
Dim strUserCommonName As String
Dim hCertificate As Long
Dim ux As Long
Dim svrSpezial As New TSPrinter

        fMainForm.sbStatusBar.Panels(1).text = "Unterschriften werden geprüft..."
        hResult = svrTSCrypt.GetUserCount(lUserCount)
        DisplayErrordescription hResult
        For ux = 0 To lUserCount - 1
            hResult = svrTSCrypt.GetUser(ux, hUser)
            DisplayErrordescription hResult
            hResult = svrTSCrypt.GetUserCertificate(hUser, hCertificate)
            DisplayErrordescription hResult
            hResult = svrTSCrypt.GetOwnerCommonName(hCertificate, strUserCommonName)
            DisplayErrordescription hResult
            hResult = svrTSCrypt.ValidateSignature(hUser)
            If hResult = 0 Then
                MsgBox "Die Unterschrift von " & strUserCommonName & " ist gültig!", vbInformation
            Else
                DisplayErrordescription hResult
                MsgBox "Die Unterschrift von " & strUserCommonName & " ist nicht gültig!", vbCritical
            End If
        Next ux
        hResult = svrTSCrypt.Close()
        DisplayErrordescription hResult
        Set svrTSCrypt = Nothing
        svrSpezial.spezial1
    End If
    fMainForm.sbStatusBar.Panels(1).text = ""
On Error Resume Next
    Kill strContentFileName
Exit Sub

Err_mnuEditVerify:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Sub
Private Sub mnuEditEncrypt_Click()
On Error GoTo Err_mnuEditEncrypt
 Dim hResult As Long
 Dim strContentFileName As String
 Dim strDocumentFileName As String
 Dim fCertificates As frmCertificates
 Dim ux As Integer
    
    If gCurElement Is Nothing Then
        MsgBox "Sie müssen erst ein Element auswählen!"
        Exit Sub
    End If
    
    fMainForm.sbStatusBar.Panels(1).text = "Daten werden vorbereitet..."
    strContentFileName = GetTempName()
    hResult = gCurElement.SaveToTSD(strContentFileName, False)
    
    fMainForm.sbStatusBar.Panels(1).text = "Zertifikate werden geladen..."
    Set fCertificates = New frmCertificates
    Load fCertificates
    fCertificates.Controls("tabCertificates").TabVisible(2) = True
    fCertificates.Controls("K_User").Visible = True
    fCertificates.Controls("K_Cancel").Visible = True
    fCertificates.Controls("K_Exit").Caption = "&Weiter >>"
    fCertificates.Show vbModal

'======================================================================
    If svrTSCrypt Is Nothing Then
        MsgBox "Der Kryptographiemodul konnte nicht geladen werden!"
    Else
        If fCertificates.Tag <> Chr(13) Then
            fMainForm.sbStatusBar.Panels(1).text = "Daten werden übergeben..."
            hResult = svrTSCrypt.LoadContent(strContentFileName)
            If hResult <> 0 Then
                MsgBox "Laden des Inhalts schiefgegangen!"
            Else
                strDocumentFileName = GetTempName()
                hResult = svrTSCrypt.SetEncryptionType(1)
                fMainForm.sbStatusBar.Panels(1).text = "Zertifikate werden übergeben..."
                For ux = 1 To fCertificates.Controls("lstUserCertificates").ListItems.Count
                    hResult = svrTSCrypt.AddUser(CLng(fCertificates.Controls("lstUserCertificates").ListItems(ux).Tag))
                Next ux
                fMainForm.sbStatusBar.Panels(1).text = "Verschlüsselte Daten werden übernommen..."
                hResult = svrTSCrypt.SaveDocument(strDocumentFileName)
                If hResult = 0 Then
                    gCurElement.SubNodes.Clear
                    gCurElement.SetFromFile strDocumentFileName
                    gCurElement.encrypted = True
                    gCurElement.Caption = "verschlüsselt"
                    RefreshListe
                Else
                    MsgBox "Die Daten konnten nicht vershlüsselt werden!"
                End If
            End If
        End If
    End If
    Unload fCertificates
    Set fCertificates = Nothing
    fMainForm.sbStatusBar.Panels(1).text = ""
On Error Resume Next
    Kill strContentFileName
Exit Sub

Err_mnuEditEncrypt:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Sub

Private Sub mnuEditEncryptAll_Click()
On Error GoTo Err_mnuEditEncryptAll
 Dim hResult As Long
 Dim strContentFileName As String
 Dim strDocumentFileName As String
 Dim strVal As String
 Dim fCertificates As frmCertificates
 Dim hCertificate As Long
 Dim ux As Integer
    If gNode.SubNodes.Count = 0 Then
        MsgBox "Diese Datei enthält keine Elemente, die verschlüsselt werden können!"
        Exit Sub
    End If

    Set gCurElement = gNode
    
    fMainForm.sbStatusBar.Panels(1).text = "Daten werden vorbereitet..."
    strContentFileName = GetTempName()
    hResult = gCurElement.SaveToTSD(strContentFileName, False)
    
    fMainForm.sbStatusBar.Panels(1).text = "Zertifikate werden geladen..."
    Set fCertificates = New frmCertificates
    Load fCertificates
    fCertificates.Controls("tabCertificates").TabVisible(2) = True
    fCertificates.Controls("K_User").Visible = True
    fCertificates.Controls("K_Cancel").Visible = True
    fCertificates.Controls("K_Exit").Caption = "&Weiter >>"
    fCertificates.Show vbModal

'======================================================================
    If svrTSCrypt Is Nothing Then
        MsgBox "Der Kryptographiemodul konnte nicht geladen werden!"
    Else
        If fCertificates.Tag <> Chr(13) Then
            fMainForm.sbStatusBar.Panels(1).text = "Daten werden übergeben..."
            hResult = svrTSCrypt.LoadContent(strContentFileName)
            If hResult <> 0 Then
                MsgBox "Laden des Inhalts schiefgegangen!"
            Else
                strDocumentFileName = GetTempName()
                hResult = svrTSCrypt.SetEncryptionType(1)
                fMainForm.sbStatusBar.Panels(1).text = "Zertifikate werden übergeben..."
                gRecipients = ""
                For ux = 1 To fCertificates.Controls("lstUserCertificates").ListItems.Count
                    hCertificate = CLng(fCertificates.Controls("lstUserCertificates").ListItems(ux).Tag)
                    hResult = svrTSCrypt.IsOwnCertificate(hCertificate)
                    If hResult = 0 Then
                        hResult = svrTSCrypt.GetOwnerCommonName(hCertificate, strVal)
                        gRecipients = gRecipients & strVal & ";"
                        hResult = svrTSCrypt.GetOwnerEmailAddress(hCertificate, strVal)
                        gRecipients = gRecipients & strVal & ";"
                    End If
                    hResult = svrTSCrypt.AddUser(CLng(fCertificates.Controls("lstUserCertificates").ListItems(ux).Tag))
                Next ux
                fMainForm.sbStatusBar.Panels(1).text = "Verschlüsselte Daten werden übernommen..."
                hResult = svrTSCrypt.SaveDocument(strDocumentFileName)
                If hResult = 0 Then
                    gCurElement.SubNodes.Clear
                    gCurElement.SetFromFile strDocumentFileName
                    gCurElement.encrypted = True
                    gCurElement.Caption = "verschlüsselt"
                    Set gCurElement = gNode.SubNodes.Add("Encrypted")
                    gCurElement.encrypted = True
                    gCurElement.Caption = "verschlüsselt"
                    RefreshListe
                Else
                    MsgBox "Die Daten konnten nicht vershlüsselt werden!"
                End If
            End If
        End If
    End If
    Unload fCertificates
    Set fCertificates = Nothing
    fMainForm.sbStatusBar.Panels(1).text = ""
On Error Resume Next
    Kill strContentFileName
Exit Sub

Err_mnuEditEncryptAll:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next

End Sub

Private Sub mnuEditDecrypt_Click()
On Error GoTo Err_mnuEditDecrypt
 Dim strErrorDescription As String
 Dim hResult As Long
 Dim strFileNameC As String
 Dim svrSpezial As New TSPrinter
 Dim ux As Integer
    
    If gCurElement Is Nothing Then
        MsgBox "Sie müssen erst ein Element auswählen!"
        Exit Sub
    End If
    If gCurElement.encrypted = False Then
        MsgBox "Das ausgewählte Element ist nicht verschlüsselt!"
        Exit Sub
    End If
    
'======================================================================
    Set svrTSCrypt = New TSCryptSvr
    If svrTSCrypt Is Nothing Then
        MsgBox "Der Kryptographiemodul konnte nicht geladen werden!"
    Else
        hResult = svrTSCrypt.SetDatabase(App.Path)
        hResult = svrTSCrypt.SetPassword(GetPassword())
        hResult = svrTSCrypt.Open()
        If hResult <> 0 Then
           hResult = svrTSCrypt.GetErrorDescription(hResult, strErrorDescription)
           MsgBox strErrorDescription
        End If
        fMainForm.sbStatusBar.Panels(1).text = "Verschlüsselte Daten werden übergeben..."
        If gCurElement.Class = "Encrypted" Then
            hResult = svrTSCrypt.LoadDocument(gNode.TempFileName)
        Else
            hResult = svrTSCrypt.LoadDocument(gCurElement.TempFileName)
        End If
        If hResult = 0 Then
            strFileNameC = GetTempName()
            fMainForm.sbStatusBar.Panels(1).text = "Entschlüsselte Daten werden übernommen..."
            hResult = svrTSCrypt.SaveContent(strFileNameC)
            If gCurElement.Class = "Encrypted" Then
                Set gCurElement = Nothing
                hResult = gNode.LoadFromTSD(strFileNameC)
            Else
                hResult = gCurElement.LoadFromTSD(strFileNameC)
            End If
            RefreshListe
        Else
            MsgBox "Die Daten konnten nicht entschlüsselt werden!"
        End If
        svrTSCrypt.Close
        Set svrTSCrypt = Nothing
        svrSpezial.spezial1
    End If
    fMainForm.sbStatusBar.Panels(1).text = ""
' Dim hResult As Long
' Dim strSigFileName As String
' Dim oSign As cSignatur
' Dim strCertificateName As String
' Dim lFileLenD As Long
' Dim lFileLenC As Long
' Dim lFileLenS As Long
' Dim hFile As Long
' Dim baDecryptedContent() As Byte
' Dim baDocument() As Byte
' Dim lEBPos As Long
' Dim lEEPos As Long
' Dim lx As Long
' Dim ixp As Integer
' Dim ixs As Integer
' Dim objSeite As cNode
' Dim strObjectName As String
' Dim strObjectDispName As String
'
' '   Set svrCryptoSeal = New TeleSign.CryptoSeal
' '   If svrCryptoSeal Is Nothing Then
' '       MsgBox "Der Zugriff auf die Schlüsselverwaltung ist fehlgeschlagen!"
' '       Exit Sub
' '   End If
'
'    If Not gCurEnclosure Is Nothing Then
'        If gCurEnclosure.encrypted = True Then
'            hFile = FreeFile
'            Open gCurEnclosure.TempFileName For Binary Access Read As hFile
'            lFileLenD = LOF(hFile)
'            ReDim baDocument(0 To lFileLenD - 1)
'            Get #hFile, , baDocument
'            Close hFile
'
'            hFile = FreeFile
'            Open "C:\TEMP\TSDENCT.TMP" For Binary Access Write As hFile
'            Put #hFile, , baDocument
'            Close hFile
'
'            hResult = svrCryptoSeal.SetDocument(baDocument)
'            hResult = svrCryptoSeal.TSDecrypt()
'            hResult = svrCryptoSeal.GetContent(baDecryptedContent)
'
'            If hResult = 0 Then
'                Open "C:\TEMP\TSDCNTDEC.TMP" For Binary Access Write As hFile
'                Put #hFile, , baDecryptedContent
'                Close hFile
'
'                lEBPos = FindElementBegin(baDecryptedContent, 0)
'                lEEPos = FindElementEnd(baDecryptedContent, lEBPos + Len(ELEMENT_BEGIN))
'                strObjectName = gCurEnclosure.Name
'                strObjectDispName = gCurEnclosure.Caption
'                gCurEnclosure.LoadFromBuffer baDecryptedContent, lEBPos + Len(ELEMENT_BEGIN), lEEPos - lEBPos - Len(ELEMENT_BEGIN)
'                gCurEnclosure.encrypted = False
'                gCurEnclosure.Name = strObjectName
'                gCurEnclosure.Caption = strObjectDispName
'                RefreshListe
'            Else
'                MsgBox "Das Dokument konnte nicht entschlüsselt werden!"
'            End If
'        Else
'            MsgBox "Die ausgewählte Anlage ist nicht verschlüsselt!"
'        End If
'        Exit Sub
'    End If
'
'    If gNode.SubNodes.Count = 0 Then
'        Exit Sub
'    End If
'    If gAktDok Is Nothing Then
'        MsgBox "Sie müssen erst ein Dokument auswählen!"
'        Exit Sub
'    End If
'    If gAktDok.signs.Count = 0 Then
'        MsgBox "Das ausgewählte Dokument ist nicht verschlüsselt!"
'        Exit Sub
'    End If
'    If gAktDok.signs(1).encrypted = False Then
'        MsgBox "Das ausgewählte Dokument nur unterschrieben!"
'        Exit Sub
'    End If
'
'    hFile = FreeFile
'    Open gAktDok.signs(1).TempFileName For Binary Access Read As hFile
'    lFileLenD = LOF(hFile)
'    ReDim baDocument(0 To lFileLenD - 1)
'    Get #hFile, , baDocument
'    Close hFile
'
'    hResult = svrCryptoSeal.SetDocument(baDocument)
'    hResult = svrCryptoSeal.TSDecrypt()
'    hResult = svrCryptoSeal.GetContent(baDecryptedContent)
'    If hResult = 0 Then
'        hFile = FreeFile
'        Open "C:\TEMP\TSDCONDECRYPTED.TMP" For Binary Access Write As hFile
'        Put #hFile, , baDecryptedContent
'        Close hFile
'
'        gAktDok.SubNodes.Clear
'        gAktDok.signs.Clear
'        ixp = 0
'        ixs = 0
'        lx = 0
'        lEBPos = FindElementBegin2(baDecryptedContent, 0)
'        Do Until lx < 0
'            lEEPos = FindElementBegin2(baDecryptedContent, lEBPos + Len(ELEMENT_BEGIN2))
'            If lEEPos < 0 Then
'                lEEPos = FindElementEnd2(baDecryptedContent, lEBPos + Len(ELEMENT_BEGIN2))
'                lx = -1
'            End If
'            If baDecryptedContent(lEBPos + Len(ELEMENT_BEGIN2)) = Asc("B") Then
'                ixp = ixp + 1
'                Set objSeite = gAktDok.SubNodes.Add("Seite")
'                objSeite.LoadFromBuffer baDecryptedContent, lEBPos + Len(ELEMENT_BEGIN2), lEEPos - lEBPos - Len(ELEMENT_BEGIN2)
'                objSeite.Caption = "Seite" & Str(ixp)
'            Else
'                ixs = ixs + 1
'                Set oSign = gAktDok.signs.Add("Unterschrift" & Str(ixs))
'                oSign.LoadFromBuffer baDecryptedContent, lEBPos + Len(ELEMENT_BEGIN2), lEEPos - lEBPos - Len(ELEMENT_BEGIN2)
'                oSign.Name = "Unterschrift" & Str(ixs)
'                oSign.Caption = "Unterschrift" & Str(ixs)
'            End If
'            lEBPos = lEEPos
'        Loop
'        gAktDok.encrypted = False
'        If ixs > 0 Then
'            gAktDok.signed = True
'        End If
'        RefreshListe
'    Else
'        MsgBox "Das Dokument konnte nicht entschlüsselt werden!"
'    End If
''    Set svrCryptoSeal = Nothing
    
Exit Sub

Err_mnuEditDecrypt:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "EditDecrypt"
    Resume Next
End Sub

Private Sub mnuEditKeyPool_Click()
On Error GoTo Err_mnuEditKeyPool
 Dim fCertificates As frmCertificates
    Set fCertificates = New frmCertificates
    Load fCertificates
    fCertificates.Show vbModal
    Unload fCertificates
    Set fCertificates = Nothing
'    Set svrCryptoSeal = New TeleSign.CryptoSeal
'    If svrCryptoSeal Is Nothing Then
'        MsgBox "Der Zugriff auf die Schlüsselverwaltung ist fehlgeschlagen!"
'    Else
'        svrCryptoSeal.ManageCertificates
'    End If
'    Set svrCryptoSeal = Nothing
Exit Sub

Err_mnuEditKeyPool:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "mnuEditKeyPool"
    Resume Next

End Sub

Private Sub mnuEditWriteFile_Click()
Dim oDat As cNode, strKey As String, Item As Node
Dim oDok As cNode
Dim Drive As String, Subdirs As String
Dim FileName As String, Suffix As String
Dim i As Integer, msgtext As String
Dim bIgnoreExist As Boolean, retVal As VbMsgBoxResult

On Error GoTo EditWriteFile_Error

    Set Item = tvTreeView.SelectedItem
    If Item Is Nothing Then Exit Sub

    bIgnoreExist = False
    If gNode.SubNodes.Exists(Item.Key) Then
        Set oDat = gNode.SubNodes.Find(Item.Key)
        If oDat.Class = "Anlage" Then
            
            SplitPath oDat.TempFileName, Drive, Subdirs, FileName, Suffix
            strKey = Drive & Subdirs & oDat.Caption
    
            With dlgCommonDialog
                .Filter = "Alle Dateien (*.*)|*.*"
                If gCurElement Is Nothing Then
                    .DialogTitle = "Anlage speichern"
                Else
                    .DialogTitle = gCurElement.Class & " speichern"
                End If
                .FileName = oDat.Caption
                .ShowSave
                If Len(.FileName) = 0 Then
                    Exit Sub
                End If
    
                FileCopy oDat.TempFileName, .FileName
    
            End With
        ElseIf oDat.Class = "Verzeichnis" Then
            
            frmDirSelect.Show vbModal, Me
            If Len(frmDirSelect.strPfad) > 0 Then
                strKey = frmDirSelect.strPfad
                If (right(strKey, 1) <> "\") And _
                    (right(strKey, 1) <> "/") Then strKey = strKey & "\"
                strKey = strKey & oDat.Caption
                MkDir strKey
                For i = 1 To oDat.SubNodes.Count
                    Set oDok = oDat.SubNodes.Item(i)
                    CopyFileOrDir oDok, strKey & "\"
                Next i
            End If
            Unload frmDirSelect
        End If
    End If
    Exit Sub

EditWriteFile_Error:
    If Err.Number = 75 Then
        If Not bIgnoreExist Then
            If Not oDat Is Nothing Then
                If oDat.Class = "Anlage" Then
                    msgtext = "Die Datei '" & oDat.Caption & _
                            "' existiert bereits! Soll sie ersetzt werden!"
                ElseIf oDat.Class = "Verzeichnis" Then
                    If Not oDok Is Nothing Then
                        msgtext = "Das Verzeichnis '" & oDok.Caption & _
                                "' existiert bereits! Soll es überschrieben werden!"
                    Else
                        msgtext = "Das Verzeichnis '" & oDat.Caption & _
                                "' existiert bereits! Soll es überschrieben werden!"
                    End If
                End If
                If Len(msgtext) > 0 Then
                    retVal = MsgBox(msgtext, vbYesNo)
                End If
                If retVal = vbYes Then
                    Resume Next
                Else
                    Exit Sub
                End If
            Else
                MsgBox "Fehler " & Str(Err.Number) & ": " & Err.Description, , "tvTreeView_BeforeLabelEdit"
            End If
        End If
    Else
        MsgBox "Fehler " & Str(Err.Number) & ": " & Err.Description, , "tvTreeView_BeforeLabelEdit"
    End If
    Resume Next
End Sub

Private Sub mnuFileSend_Click()
On Error GoTo Err_mnuFileSend
 Dim MAPISessionID
 Dim strTempFileName As String
 Dim ixRecipients As Integer
    
    fMainForm.sbStatusBar.Panels(1).text = "Kopie des Dokuments wird gespeichert..."
    strTempFileName = GetTempName
    gNode.SaveToTSD strTempFileName, False

    fMainForm.sbStatusBar.Panels(1).text = "eMail-System wird gestartet..."
    Me.MAPISession1.DownLoadMail = False
    Me.MAPISession1.LogonUI = False
    Me.MAPISession1.NewSession = False
    Me.MAPISession1.UserName = ""
    Me.MAPISession1.Password = ""
On Error Resume Next
    Me.MAPISession1.SignOn
    If Err.Number <> 0 Then
        MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description & vbCrLf & vbCrLf & "Das eMail-System konnte nicht gestartet werden!", , Err.Source
    Else
        With Me.MAPIMessages1
            .SessionID = Me.MAPISession1.SessionID
            .Compose
            .MsgNoteText = "TeleSign Dokument"
            .MsgSubject = "TeleSign Dokument"
            .AttachmentPathName = strTempFileName
            .AttachmentName = "TeleSign Dokument"
            ixRecipients = 0
            Do While Len(gRecipients) > 0
                .RecipIndex = ixRecipients
                ixRecipients = ixRecipients + 1
                .RecipDisplayName = Mid(gRecipients, 1, InStr(gRecipients, ";") - 1)
                gRecipients = Mid(gRecipients, InStr(gRecipients, ";") + 1)
                .RecipAddress = Mid(gRecipients, 1, InStr(gRecipients, ";") - 1)
                gRecipients = Mid(gRecipients, InStr(gRecipients, ";") + 1)
            Loop
            .Send True
        End With
        Me.MAPISession1.SignOff
    End If
    fMainForm.sbStatusBar.Panels(1).text = ""
On Error Resume Next
    Kill strTempFileName
Exit Sub

Err_mnuFileSend:
    If Err.Number <> 32001 Then 'Benutzer hat Vorgang abgebrochen
        MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "mnuFileSend"
    End If
    Resume Next
End Sub

Private Sub mnuKarteDetails_Click()
On Error Resume Next
    Shell "GSTools.exe", vbNormalFocus
'    frmCardDetails.Show

End Sub



Private Sub tvTreeView_BeforeLabelEdit(CANCEL As Integer)
On Error GoTo Err_tvTreeView_BeforeLabelEdit
    
    If gCurElement Is Nothing Or gPrvElement Is Nothing Then
        CANCEL = 1
    Else
        If gCurElement.Class = "Unterschrift" Then
            CANCEL = 1
        End If
        If gCurElement.Class = "Visualisierung" Then
            CANCEL = 1
        End If
        If gCurElement.UniqueKey <> gPrvElement.UniqueKey Then
            CANCEL = 1
        End If
    End If
Exit Sub

Err_tvTreeView_BeforeLabelEdit:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "tvTreeView_BeforeLabelEdit"
    Resume Next
End Sub

Private Sub tvTreeView_DblClick()
On Error GoTo Err_tvTreeView_DblClick
 Dim strCommand As String
    Select Case gCurElement.Class
    Case "Zertifikat"
        strCommand = RegGetCommandDER
        strCommand = Mid(strCommand, 1, InStr(strCommand, "%1") - 1) & gCurElement.TempFileName & Mid(strCommand, InStr(strCommand, "%1") + 2)
        If Len(strCommand) > 0 Then
            Shell strCommand, vbNormalFocus
        Else
            MsgBox "Auf diesem Rechner ist kein Programm zum Anzeigen von Zertifikaten installiert!"
        End If
    End Select
Exit Sub

Err_tvTreeView_DblClick:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "tvTreeView_DblClick"
    Resume Next
End Sub

Private Sub tvTreeView_OLESetData(Data As ComctlLib.DataObject, DataFormat As Integer)
On Error GoTo Err_tvTreeView_OLESetData
 Dim oDat As cNode, strKey As String, Item As Node
 Dim oDok As cNode, i As Integer
 Dim Drive As String, Subdirs As String
 Dim FileName As String, Suffix As String

    Set Item = tvTreeView.SelectedItem
    If Item Is Nothing Then Exit Sub
    
    If gNode.SubNodes.Exists(Item.Key) Then
        Set oDat = gNode.SubNodes.Find(Item.Key)
        If oDat.Class = "Anlage" Then
            SplitPath oDat.TempFileName, Drive, Subdirs, FileName, Suffix
            strKey = Drive & Subdirs & oDat.Caption

            FileCopy oDat.TempFileName, strKey
'            gTempFileName = strKey

'            Data.SetData , vbCFFiles
            Data.Files.Add strKey
'            AllowedEffects = 1

            gEnableDroping = False
        ElseIf oDat.Class = "Verzeichnis" Then
'            gTempFileName = GetTempName
            strKey = GetTempName
'            SplitPath strKey, Drive, Subdirs, FileName, Suffix
'            strKey = Drive & Subdirs & oDat.Caption
            If DateiExist(strKey) Then Kill strKey
            MkDir strKey
            strKey = strKey & "\" & oDat.Caption
            MkDir strKey
'            gTempFileName = strKey

            For i = 1 To oDat.SubNodes.Count
                Set oDok = oDat.SubNodes.Item(i)
                CopyFileOrDir oDok, strKey & "\"
            Next i
            
'            Data.SetData , vbCFFiles
            Data.Files.Add strKey
'            AllowedEffects = 2

            gEnableDroping = False
        End If
    End If
Exit Sub

Err_tvTreeView_OLESetData:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "tvTreeView_OLEStartDrag"
    Resume Next

End Sub

Private Sub lvListView_OLESetData(Data As ComctlLib.DataObject, DataFormat As Integer)
On Error GoTo Err_lvListView_OLESetData
 Dim oDat As cNode, strKey As String, Item As ListItem
 Dim oDok As cNode, i As Integer
 Dim Drive As String, Subdirs As String
 Dim FileName As String, Suffix As String

    Set Item = lvListView.SelectedItem
    If Item Is Nothing Then Exit Sub
    
    If gNode.SubNodes.Exists(Item.Key) Then
        Set oDat = gNode.SubNodes.Find(Item.Key)
        If oDat.Class = "Anlage" Then
            SplitPath oDat.TempFileName, Drive, Subdirs, FileName, Suffix
            strKey = Drive & Subdirs & oDat.Caption

            FileCopy oDat.TempFileName, strKey
            Data.Files.Add strKey

            gEnableDroping = False
        ElseIf oDat.Class = "Verzeichnis" Then
            strKey = GetTempName
            If DateiExist(strKey) Then Kill strKey
            MkDir strKey
            strKey = strKey & "\" & oDat.Caption
            MkDir strKey

            For i = 1 To oDat.SubNodes.Count
                Set oDok = oDat.SubNodes.Item(i)
                CopyFileOrDir oDok, strKey & "\"
            Next i
            
            Data.Files.Add strKey

            gEnableDroping = False
        End If
    End If
Exit Sub

Err_lvListView_OLESetData:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "lvListView_OLEStartDrag"
    Resume Next

End Sub

Private Sub VScroll1_Change()
'    detPicture(gAktSeite).Top = -VScroll1.Value
    detPicture(0).Top = -VScroll1.Value
'    detPicture(gAktSeite).Top = -VScroll1.Value * picRahmen.Height
End Sub

Private Sub lvListView_BeforeLabelEdit(CANCEL As Integer)
    CANCEL = 1
End Sub

Private Sub mnuEditShowDetails_Click()
    If nViewMode = 0 Then
        ZeigeDetailBild "Details"
    Else
        ZeigeDetailBild "Liste"
    End If
End Sub

Private Sub mnuFileDelete_Click()
Dim Key As String, ans, text As String
Dim dat As cNode, dok As cNode

    If tvTreeView.SelectedItem Is Nothing Then
        Exit Sub
    End If

    Key = tvTreeView.SelectedItem.Key

    If gNode.SubNodes.Exists(Key) Then
        Set dok = gNode.SubNodes.Find(Key)
        ' Hier sollte noch festgelegt werden, welche Knoten gelöscht werden dürfen!
        text = "Sind Sie sicher, daß Sie das Element einschließlich aller Teilelemente aus dem Dokument entfernen wollen?"
        ans = MsgBox(text, vbYesNo)
        If ans = 6 Then
            gNode.SubNodes.RemoveSubnode Key
        End If
    End If
    
    ShowDetails
    RefreshListe
End Sub

Private Sub mnuFilePrint_Click()
On Error GoTo Err_mnuFilePrint
 Dim nx As Integer
    If gCurElement Is Nothing Then
        Exit Sub
    End If
    If Printer.PaperSize <> vbPRPSA4 Then
        MsgBox "Es wird nur der Druck auf A4-Format unterstützt!"
        Exit Sub
    End If
    If gCurElement.Class = "Seite" Then
        fMainForm.sbStatusBar.Panels(1).text = "Seite wird gedruckt..."
        Me.picCurPage.Picture = LoadPicture(gCurElement.TempFileName)
        Printer.PaintPicture Me.picCurPage.Picture, 0, 0, Printer.Width, Me.picCurPage.Picture.Height * (Printer.Width / Me.picCurPage.Picture.Width)
        Printer.EndDoc
    ElseIf gCurElement.Class = "Visualisierung" Then
        For nx = 1 To gCurElement.SubNodes.Count
            If gCurElement.SubNodes.Item(nx).Class = "Seite" Then
                fMainForm.sbStatusBar.Panels(1).text = "Seite" & Str(nx) & " wird gedruckt..."
                If nx > 1 Then
                    Printer.NewPage
                End If
                Me.picCurPage.Picture = LoadPicture(gCurElement.SubNodes.Item(nx).TempFileName)
                Printer.PaintPicture Me.picCurPage.Picture, 0, 0, Printer.Width, Me.picCurPage.Picture.Height * (Printer.Width / Me.picCurPage.Picture.Width)
            End If
        Next nx
        Printer.EndDoc
    End If
    fMainForm.sbStatusBar.Panels(1).text = ""
Exit Sub

Err_mnuFilePrint:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next

End Sub

Private Sub mnuFileSave_Click()
Dim i As Integer

    If 0 = Len(gDokFileName) Then
        mnuFileSaveAs_Click
    Else
        fMainForm.sbStatusBar.Panels(1).text = "Dokument wird gespeichert..."
        gNode.SaveToTSD gDokFileName, False
        fMainForm.sbStatusBar.Panels(1).text = ""
    End If
    
End Sub

Private Sub mnuFileSaveAs_Click()

    With dlgCommonDialog
        .Filter = "TSD-Dokumente (*.TSD)|*.TSD|Alle Dateien (*.*)|*.*"
        .ShowSave
        If Len(.FileName) = 0 Then
            Exit Sub
        End If
        gDokFileName = .FileName
    End With
    
    fMainForm.sbStatusBar.Panels(1).text = "Dokument wird gespeichert..."
    gNode.SaveToTSD gDokFileName, False
    fMainForm.sbStatusBar.Panels(1).text = ""
End Sub

'Private Sub mnuViewBrowser_Click()
'On Error GoTo Err_mnuViewBrowser
'Dim frmB As New frmBrowser
'
'    frmB.StartingAddress = "http://www.TeleSign.de"
'    frmB.Show
'Exit Sub
'
'Err_mnuViewBrowser:
'    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
'    Resume Next
'End Sub

Private Sub mnuHelpAbout_Click()
'    frmAbout.Show vbModal, Me
    frmSplash.Show
End Sub

Private Sub mnuViewOptions_Click()
    frmOptions.mFaktor = Me.gPictZoomFaktor
    frmOptions.Show vbModal, Me
    Unload frmOptions
End Sub

Private Sub mnuViewStatusBar_Click()

    If mnuViewStatusBar.CHECKED Then
        sbStatusBar.Visible = False
        mnuViewStatusBar.CHECKED = False
    Else
        sbStatusBar.Visible = True
        mnuViewStatusBar.CHECKED = True
    End If
    SizeControls imgSplitter.Left
End Sub

Private Sub mnuViewToolbar_Click()
    If mnuViewToolbar.CHECKED Then
        tbToolBar.Visible = False
        mnuViewToolbar.CHECKED = False
    Else
        tbToolBar.Visible = True
        mnuViewToolbar.CHECKED = True
    End If
    SizeControls imgSplitter.Left
End Sub

Private Sub Form_Load()
On Error GoTo Err_Form_Load
 Dim dok As cNode
 Dim pages As cNode
 Dim args, SaveTitle$
 Dim hResult As Long, text As String
 Dim i As Integer

    args = GetCommandLine
    
    LoadResStrings Me

    Caption = "TRiAS-Signature"
    App.Title = Caption

    Set gNode = New cNode
    gNode.UniqueKey = GetUniqueKey()
    gNode.Class = "Root"
    
'    If DateiExist("C:\Ts.1") Then
'        Set dok = gNode.SubNodes.Add("Neues Dokument")
'        If Not dok Is Nothing Then
'            dok.LadeDrucker
'        End If
'    End If
    Set gTempArray = New ccTempFileArray
    
    LoadToolbarPictures
    
    gEnableDroping = True
    
    nViewMode = 0
    gbDisableResize = False

    Set tvTreeView.ImageList = imlIcons
    Set tbToolBar.ImageList = imlButtonSymbols

Dim tbb As Button
    Set tbb = tbToolBar.Buttons.Add(, "Open", , tbrDefault, "Open")
    tbb.ToolTipText = "Öffnen"
    Set tbb = tbToolBar.Buttons.Add(, "Save", , tbrDefault, "Save")
    tbb.ToolTipText = "Speichern"
    Set tbb = tbToolBar.Buttons.Add(, "Print", , tbrDefault, "Print")
    tbb.ToolTipText = "Drucken"
    Set tbb = tbToolBar.Buttons.Add(, "Send", , tbrDefault, "Send")
    tbb.ToolTipText = "Senden"
'    Set tbb = tbToolBar.Buttons.Add(, "Delete", , tbrDefault, "Delete")
'    tbb.ToolTipText = "Löschen"
    Set tbb = tbToolBar.Buttons.Add(, "Space1", , tbrSeparator)
    Set tbb = tbToolBar.Buttons.Add(, "Sign", , tbrDefault, "Sign")
    tbb.ToolTipText = "Unterschreiben"
    Set tbb = tbToolBar.Buttons.Add(, "Verify", , tbrDefault, "Verify")
    tbb.ToolTipText = "Prüfen"
    Set tbb = tbToolBar.Buttons.Add(, "KeyPool", , tbrDefault, "KeyPool")
    tbb.ToolTipText = "Schlüsselverwaltung"
    Set tbb = tbToolBar.Buttons.Add(, "EncryptAll", , tbrDefault, "Encrypt")
    tbb.ToolTipText = "Alles Verschlüsseln"
    Set tbb = tbToolBar.Buttons.Add(, "Decrypt", , tbrDefault, "Decrypt")
    tbb.ToolTipText = "Entschlüsseln"
    Set tbb = tbToolBar.Buttons.Add(, "Space2", , tbrSeparator)
    Set tbb = tbToolBar.Buttons.Add(, "Layout", , tbrDefault, "Layout2")
    tbb.ToolTipText = "TreeView ausblenden"
    Set tbb = tbToolBar.Buttons.Add(, "ViewDet", , tbrDefault, "ViewDet")
    tbb.ToolTipText = "Details zeigen"
    Set tbb = tbToolBar.Buttons.Add(, "Space3", , tbrSeparator)
    Set tbb = tbToolBar.Buttons.Add(, "PreviousPage", , tbrDefault, "PreviousPage")
    tbb.ToolTipText = "vorherige Seite"
    Set tbb = tbToolBar.Buttons.Add(, "NextPage", , tbrDefault, "NextPage")
    tbb.ToolTipText = "nächste Seite"

    lvListView.ColumnHeaders.Add , , "Name", 2000
    lvListView.ColumnHeaders.Add , , "Größe", 600
    lvListView.ColumnHeaders.Add , , "Typ", 1500
    lvListView.ColumnHeaders.Add , , "Erstellt", 1600

'    Load frmCryptoSealDlg
    mnuEditShowDetails.Enabled = False
    ConfigToolBar
    
    If IsArray(args) And UBound(args) > 0 Then
'        If App.PrevInstance Then
'            SaveTitle$ = App.Title
'            App.Title = "... Kopie."
'            Me.Caption = "... Kopie."
'            AppActivate SaveTitle$ ', True
'            SendKeys "(% )W" ', True
'            End
'        End If

        If Left(args(1), 1) = """" Then
            args(1) = Mid$(args(1), 2, Len(args(1)) - 2)
        End If
        
        If DateiExist(args(1)) And ("TSD" = UCase(right(args(1), 3))) Then
            gDokFileName = args(1)
            ReadDokument gDokFileName
        ElseIf DateiExist(args(1)) And ("DAT" = UCase(right(args(1), 3))) Then
            Set dok = gNode.SubNodes.Add("Dokument")
            If Not dok Is Nothing Then
                dok.Caption = "Neues Dokument"
                Set pages = dok.SubNodes.Add("Visualisierung")
                pages.Caption = "Visualisierung"
                pages.LoadPrinterData args(1)
            End If
            Kill args(1)
        ElseIf right(args(1), 1) = "." Then
            text = args(1) & "001"
            If DateiExist(args(1) & "001") Then
                Set dok = gNode.SubNodes.Add("Dokument")
                If Not dok Is Nothing Then
                    dok.Caption = "Neues Dokument"
                    Set pages = dok.SubNodes.Add("Visualisierung")
                    pages.Caption = "Visualisierung"
                    pages.LoadPrinterBitmaps args(1)
                End If
            End If
        End If
    End If
    
    RefreshListe
    
'    hResult = svrTSCrypt.Logon(fMainForm.hWnd)
'    If hResult <> 0 Then
'        MsgBox "Logon schiefgegangen!"
'    Else
'        hResult = svrTSCrypt.GetPassword(fMainForm.hWnd)
'    End If
    Form_Resize
    Refresh
    
Exit Sub

Err_Form_Load:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Sub

Private Sub LoadToolbarPictures()
Dim imgX As ListImage
    
'Load pictures for the toolbar buttons into the ImageList control.
    Set imgX = imlIcons.ListImages.Add(, "Schloss2", LoadResPicture(2000, 0))
    Set imgX = imlIcons.ListImages.Add(, "Schloss1", LoadResPicture(2001, 0))
    Set imgX = imlIcons.ListImages.Add(, "Schl1", LoadResPicture(2002, 0))
    Set imgX = imlIcons.ListImages.Add(, "Schl2", LoadResPicture(2003, 0))
    Set imgX = imlIcons.ListImages.Add(, "Sign1", LoadResPicture(2004, 0))
    Set imgX = imlIcons.ListImages.Add(, "Dok1", LoadResPicture(2005, 0))
'    Set imgX = imlIcons.ListImages.Add(, "Anlage", LoadResPicture(2006, 0))
    Set imgX = imlIcons.ListImages.Add(, "Zerti", LoadResPicture(2007, 0))
    Set imgX = imlIcons.ListImages.Add(, "Blatt", LoadResPicture(2008, 0))
    
    Set imgX = imlIcons.ListImages.Add(, "TSOrdner", LoadResPicture(5001, 0))
    Set imgX = imlIcons.ListImages.Add(, "TSOrdnerAuf", LoadResPicture(5002, 0))
    Set imgX = imlIcons.ListImages.Add(, "TSOrdnerZu", LoadResPicture(5003, 0))
    Set imgX = imlIcons.ListImages.Add(, "Anlage", LoadResPicture(5004, 0))
    Set imgX = imlIcons.ListImages.Add(, "AnlageZu", LoadResPicture(5006, 0))
    Set imgX = imlIcons.ListImages.Add(, "Seiten", LoadResPicture(5007, 0))
    Set imgX = imlIcons.ListImages.Add(, "Ordner", LoadResPicture(5008, 0))

    Set imgX = imlButtonSymbols.ListImages.Add(, "Open", LoadResPicture(4000, 0))
    Set imgX = imlButtonSymbols.ListImages.Add(, "Print", LoadResPicture(4001, 0))
    Set imgX = imlButtonSymbols.ListImages.Add(, "Save", LoadResPicture(4002, 0))
    Set imgX = imlButtonSymbols.ListImages.Add(, "Decrypt", LoadResPicture(4003, 0))
    Set imgX = imlButtonSymbols.ListImages.Add(, "Encrypt", LoadResPicture(4004, 0))
    Set imgX = imlButtonSymbols.ListImages.Add(, "KeyPool", LoadResPicture(4005, 0))
    Set imgX = imlButtonSymbols.ListImages.Add(, "ViewDet", LoadResPicture(4006, 0))
    Set imgX = imlButtonSymbols.ListImages.Add(, "Sign", LoadResPicture(4007, 0))
    Set imgX = imlIcons.ListImages(6)
    Set imgX = imlButtonSymbols.ListImages.Add(, "Delete", imgX.Picture)
    Set imgX = imlButtonSymbols.ListImages.Add(, "Verify", LoadResPicture(4008, 0))
    Set imgX = imlButtonSymbols.ListImages.Add(, "PreviousPage", LoadResPicture(4009, 0))
    Set imgX = imlButtonSymbols.ListImages.Add(, "NextPage", LoadResPicture(4010, 0))
    Set imgX = imlButtonSymbols.ListImages.Add(, "Send", LoadResPicture(4011, 0))
    Set imgX = imlButtonSymbols.ListImages.Add(, "Layout1", LoadResPicture(4012, 0))
    Set imgX = imlButtonSymbols.ListImages.Add(, "Layout2", LoadResPicture(4013, 0))

End Sub

Private Sub Form_Resize()
    On Error Resume Next
    If Me.Width < 3000 Then Me.Width = 3000
    SizeControls imgSplitter.Left
End Sub

Private Sub imgSplitter_MouseDown(Button As Integer, Shift As Integer, X As Single, y As Single)
    With imgSplitter
        picSplitter.Move .Left, .Top, .Width \ 2, .Height - 20
    End With
    picSplitter.Visible = True
    mbMoving = True
End Sub

Private Sub imgSplitter_MouseMove(Button As Integer, Shift As Integer, X As Single, y As Single)
    Dim sglPos As Single

    If mbMoving Then
        sglPos = X + imgSplitter.Left
        If sglPos < sglSplitLimit Then
            picSplitter.Left = sglSplitLimit
        ElseIf sglPos > Me.Width - sglSplitLimit Then
            picSplitter.Left = Me.Width - sglSplitLimit
        Else
            picSplitter.Left = sglPos
        End If
    End If
End Sub

Private Sub imgSplitter_MouseUp(Button As Integer, Shift As Integer, X As Single, y As Single)
    SizeControls picSplitter.Left
    picSplitter.Visible = False
    mbMoving = False
End Sub

Sub SizeControls(X As Single)
    On Error Resume Next

    If gbDisableResize Then Exit Sub
    gbDisableResize = True
    
    'set the width
    If X < 1500 Then X = 1500
    If X > (Me.Width - 1500) Then X = Me.Width - 1500
    
    If Me.tvTreeView.Visible Then
        tvTreeView.Width = X
        lblTitle(0).Visible = True
        lblTitle(0).Width = tvTreeView.Width
        imgSplitter.Visible = True
        imgSplitter.Left = X
        lvListView.Left = X + 40
        picRahmen.Left = X + 40
'       detPicture(0).Left = x + 40
        lvListView.Width = Me.Width - (tvTreeView.Width + 140)
        picRahmen.Width = Me.Width - (tvTreeView.Width + 140)
    Else
        lblTitle(0).Visible = False
        imgSplitter.Visible = False
        lvListView.Left = 0
        picRahmen.Left = 0
        lvListView.Width = Me.Width - 140
        picRahmen.Width = Me.Width - 140
    End If
'    detPicture(0).Width = lvListView.Width / 6
    detPicture(0).Width = lvListView.Width
    lblTitle(1).Left = lvListView.Left + 20
    lblTitle(1).Width = lvListView.Width - 40

    'set the top
    If tbToolBar.Visible Then
        tbToolBar.Refresh
        tvTreeView.Top = tbToolBar.Height + picTitles.Height
    Else
        tvTreeView.Top = picTitles.Height
    End If
    lvListView.Top = tvTreeView.Top
    picRahmen.Top = tvTreeView.Top
    
'    detPicture(0).Left = 40
'    detPicture(0).Top = 40

    'set the height
    If sbStatusBar.Visible Then
        tvTreeView.Height = Me.ScaleHeight - (picTitles.Top + picTitles.Height + sbStatusBar.Height)
    Else
        tvTreeView.Height = Me.ScaleHeight - (picTitles.Top + picTitles.Height)
    End If

    lvListView.Height = tvTreeView.Height
    picRahmen.Height = tvTreeView.Height
    
'    detPicture(0).Height = (detPicture(0).Width * 295) / 210
    
    imgSplitter.Top = tvTreeView.Top
    imgSplitter.Height = tvTreeView.Height

Dim i As Integer, y As Integer
Dim xSize As Single, ySize As Single
Dim xPos As Integer, yPos As Integer
Dim visu As cNode

'detPicture
'    For i = 1 To 19
'        detPicture(i).Height = detPicture(0).Height
'        detPicture(i).Width = detPicture(0).Width
'        detPicture(i).Top = detPicture(0).Top
'        detPicture(i).Left = detPicture(0).Left
'    Next i
''    For i = 0 To 4
''        detPicture(i).Height = detPicture(0).Height
''        detPicture(i).Width = detPicture(0).Width
''        detPicture(i).Top = detPicture(0).Top
''        detPicture(i).Left = detPicture(i - 1).Left + detPicture(i - 1).Width + _
''                            (detPicture(0).Width - 40) / 4
''    Next i
''    detPicture(5).Top = detPicture(0).Top + detPicture(0).Height + _
''                        (detPicture(0).Width - 40) / 4
''    detPicture(5).Left = detPicture(0).Left
''    For i = 6 To 9
''        detPicture(i).Height = detPicture(5).Height
''        detPicture(i).Width = detPicture(5).Width
''        detPicture(i).Top = detPicture(5).Top
''        detPicture(i).Left = detPicture(i - 1).Left + detPicture(i - 1).Width + _
''                            (detPicture(5).Width - 40) / 4
''    Next i
''    detPicture(10).Top = detPicture(5).Top + detPicture(5).Height + _
''                        (detPicture(5).Width - 40) / 4
''    detPicture(10).Left = detPicture(5).Left
''    For i = 11 To 14
''        detPicture(i).Height = detPicture(10).Height
''        detPicture(i).Width = detPicture(10).Width
''        detPicture(i).Top = detPicture(10).Top
''        detPicture(i).Left = detPicture(i - 1).Left + detPicture(i - 1).Width + _
''                            (detPicture(10).Width - 40) / 4
''    Next i
''    detPicture(15).Top = detPicture(11).Top + detPicture(11).Height + _
''                        (detPicture(11).Width - 40) / 4
''    detPicture(15).Left = detPicture(11).Left
''    For i = 16 To 19
''        detPicture(i).Height = detPicture(15).Height
''        detPicture(i).Width = detPicture(15).Width
''        detPicture(i).Top = detPicture(15).Top
''        detPicture(i).Left = detPicture(i - 1).Left + detPicture(i - 1).Width + _
''                            (detPicture(15).Width - 40) / 4
''    Next i
'    txtWeitere.Top = detPicture(15).Top + picRahmen.Top
'    txtWeitere.Left = detPicture(0).Left
'    txtWeitere.Left = picRahmen.Left
    
'    tbSeiten.Top = detPicture(0).Top
'    tbSeiten.Top = picRahmen.Top
'    tbSeiten.Left = lblTitle(1).Left
'    tbSeiten.Width = lblTitle(1).Width

'    txtWeitere.Visible = False
'    tbSeiten.Visible = False
    picRahmen.Visible = False
    VScroll1.Visible = False
    HScroll1.Visible = False
'detPicture
'    For i = 0 To 19
'        detPicture(i).Visible = False
'    Next i
    If nViewMode = 0 Then
        lvListView.Visible = True
    ElseIf nViewMode = 1 Then
'        For i = 0 To gZahlSeiten - 1
''        For i = 0 To gCurElement.ZahlSeiten - 1
'            detPicture(i).Stretch = True
'            y = detPicture(i).Top + 1.4 * detPicture(i).Height
'            If y < Me.Height Then
'                picRahmen.Visible = True
'                detPicture(i).Visible = True
'            Else
'                detPicture(i).Visible = False
'                If txtWeitere.Top > detPicture(i).Top Then
'                    txtWeitere.Top = detPicture(i).Top
'                End If
'                txtWeitere.Visible = True
'            End If
'        Next i
    ElseIf nViewMode = 2 Then
'        tbSeiten.Visible = False
        picRahmen.Visible = False
        detPicture(0).Visible = False
'        y = lvListView.Top + tbSeiten.Height + 40
        y = lvListView.Top + 40
        picRahmen.Top = y
'        picRahmen.Height = lvListView.Height - tbSeiten.Height - 40
        picRahmen.Height = lvListView.Height - 40
        
'        Set visu = Nothing
'        Select Case gCurElement.Class
'        Case "Visualisierung"
'            If (gAktSeite >= 0) And (gAktSeite < gCurElement.SubNodes.Count()) Then
'                Set visu = gCurElement.SubNodes.Item(gAktSeite + 1)
'            End If
'        Case "Seite"
'            Set visu = gCurElement
'        End Select
'        For i = 0 To gZahlSeiten - 1
'            detPicture(i).Stretch = False
'            detPicture(i).Top = -VScroll1.Value
'            detPicture(i).Left = -HScroll1.Value
'        Next i
'        Set visu = Nothing
        
        VScroll1.Top = picRahmen.Top
        VScroll1.Height = picRahmen.Height
        VScroll1.Left = picRahmen.Left + picRahmen.Width - VScroll1.Width
        HScroll1.Left = picRahmen.Left
        HScroll1.Width = picRahmen.Width
        HScroll1.Top = picRahmen.Top + picRahmen.Height - HScroll1.Height
        Dim dFaktor1 As Double
        Dim dFaktor2 As Double
'        For i = 0 To gZahlSeiten - 1
'            detPicture(i).Stretch = True
'            If 0 < gPictZoomFaktor Then
'                detPicture(i).Width = gPictInfo(i).xSize * gPictZoomFaktor
'                detPicture(i).Height = gPictInfo(i).ySize * gPictZoomFaktor
'            Else
'                dFaktor1 = picRahmen.Width / gPictInfo(i).xSize
'                dFaktor2 = picRahmen.Height / gPictInfo(i).ySize
'                If dFaktor1 < dFaktor2 Then
'                    detPicture(i).Width = gPictInfo(i).xSize * dFaktor1
'                    detPicture(i).Height = gPictInfo(i).ySize * dFaktor1
'                Else
'                    detPicture(i).Width = gPictInfo(i).xSize * dFaktor2
'                    detPicture(i).Height = gPictInfo(i).ySize * dFaktor2
'                End If
'            End If
'            If i = gAktSeite Then
'                xSize = detPicture(i).Width
'                ySize = detPicture(i).Height
'            End If
'        Next i
        detPicture(0).Stretch = True
        If 0 < gPictZoomFaktor Then
            detPicture(0).Width = gPictInfo.xSize * gPictZoomFaktor
            detPicture(0).Height = gPictInfo.ySize * gPictZoomFaktor
        Else
            dFaktor1 = picRahmen.Width / gPictInfo.xSize
            dFaktor2 = picRahmen.Height / gPictInfo.ySize
            If dFaktor1 < dFaktor2 Then
                detPicture(0).Width = gPictInfo.xSize * dFaktor1
                detPicture(0).Height = gPictInfo.ySize * dFaktor1
            Else
                detPicture(0).Width = gPictInfo.xSize * dFaktor2
                detPicture(0).Height = gPictInfo.ySize * dFaktor2
            End If
        End If
        xSize = detPicture(0).Width
        ySize = detPicture(0).Height
'        xSize = detPicture(gAktSeite).Width * gPictZoomFaktor
'        ySize = detPicture(gAktSeite).Height * gPictZoomFaktor
'        detPicture(gAktSeite).Stretch = True
'        detPicture(gAktSeite).Width = xSize
'        detPicture(gAktSeite).Height = ySize
        If ySize > picRahmen.Height Then
            picRahmen.Width = picRahmen.Width - VScroll1.Width
            yPos = VScroll1.Value
            VScroll1.Min = 0
'            VScroll1.Max = ySize - picRahmen.Height + 400
'            VScroll1.Max = Int(ySize / picRahmen.Height) '+ 1
            VScroll1.Max = ySize - picRahmen.Height + HScroll1.Height * 2
'            VScroll1.LargeChange = VScroll1.Max / 10
            VScroll1.LargeChange = VScroll1.Max / 10
'            VScroll1.SmallChange = VScroll1.Max / 100
            VScroll1.SmallChange = VScroll1.Max / 100
            If yPos > 0 Then
                If yPos < VScroll1.Max Then
                    VScroll1.Value = yPos
                Else
                    VScroll1.Value = VScroll1.Max
                End If
            Else
                VScroll1.Value = 0
            End If
            VScroll1.Visible = True
        Else
'            VScroll1.Visible = True '#fje
            VScroll1.Visible = False
            VScroll1.Value = 0
        End If
        If VScroll1.Value > VScroll1.Max Then
            VScroll1.Value = 0
        End If
        If HScroll1.Value > HScroll1.Max Then
            HScroll1.Value = 0
        End If
        
        If xSize > picRahmen.Width Then
            picRahmen.Height = picRahmen.Height - HScroll1.Height
            xPos = HScroll1.Value
            HScroll1.Min = 0
'            HScroll1.Max = xSize - picRahmen.Width + 100
'            HScroll1.Max = Int(xSize / picRahmen.Width) '+1
            HScroll1.Max = xSize - picRahmen.Width + VScroll1.Width
'            HScroll1.LargeChange = HScroll1.Max / 10
            HScroll1.LargeChange = HScroll1.Max / 10
'            HScroll1.SmallChange = HScroll1.Max / 100
            HScroll1.SmallChange = HScroll1.Max / 100
            If xPos > 0 Then
                If xPos < HScroll1.Max Then
                    HScroll1.Value = xPos
                Else
                    HScroll1.Value = HScroll1.Max
                End If
            Else
                HScroll1.Value = 0
            End If
            HScroll1.Visible = True
        Else
'            HScroll1.Visible = True '#fje
            HScroll1.Visible = False
            HScroll1.Value = 0
        End If
'        detPicture(gAktSeite).Top = -VScroll1.Value * picRahmen.Height
'        detPicture(gAktSeite).Left = -HScroll1.Value * picRahmen.Width
        VScroll1_Change
        HScroll1_Change

        If (xSize > picRahmen.Width) And _
           (ySize > picRahmen.Height) Then
            VScroll1.Height = VScroll1.Height - HScroll1.Height
            HScroll1.Width = HScroll1.Width - VScroll1.Width
        End If
        
        picRahmen.Visible = True
        detPicture(0).Visible = True
        
        ConfigToolBar

'        tbSeiten.Visible = True
    End If
    gbDisableResize = False
End Sub

'Private Sub TreeView1_DragDrop(Source As Control, x As Single, y As Single)
'    If Source = imgSplitter Then
'        SizeControls x
'    End If
'End Sub

Private Sub tbToolBar_ButtonClick(ByVal Button As ComctlLib.Button)

    Select Case Button.Key
        Case "Open"
            mnuFileOpen_Click

        Case "Save"
            mnuFileSave_Click

        Case "Print"
            mnuFilePrint_Click

        Case "Send"
            mnuFileSend_Click

        Case "Delete"
            mnuFileDelete_Click

        Case "Sign"
            mnuEditSign_Click

        Case "Verify"
            mnuEditVerify_Click

        Case "KeyPool"
            mnuEditKeyPool_Click

        Case "EncryptAll"
            mnuEditEncryptAll_Click

        Case "Decrypt"
            mnuEditDecrypt_Click

        Case "Layout"
            If Me.tvTreeView.Visible Then
                Me.tvTreeView.Visible = False
                tbToolBar.Buttons("Layout").ToolTipText = "TreeView einblenden"
                tbToolBar.Buttons("Layout").Image = "Layout1"
            Else
                Me.tvTreeView.Visible = True
                tbToolBar.Buttons("Layout").ToolTipText = "TreeView ausblenden"
                tbToolBar.Buttons("Layout").Image = "Layout2"
            End If
            SizeControls Me.imgSplitter.Left
            
        
        Case "ViewDet"
            mnuEditShowDetails_Click
        
        Case "PreviousPage"
            gotoPreviousPage
        
        Case "NextPage"
            gotoNextPage

    End Select
End Sub

Private Sub mnuHelpContents_Click()
Dim nRet As Integer


    'if there is no helpfile for this project display a message to the user
    'you can set the HelpFile for your application in the
    'Project Properties dialog
    If Len(App.HelpFile) = 0 Then
        MsgBox "Unable to display Help Contents. There is no Help associated with this project.", vbInformation, Me.Caption
    Else
        On Error Resume Next
        nRet = OSWinHelp(Me.hWnd, App.HelpFile, 3, 0)
        If Err Then
            MsgBox Err.Description
        End If
    End If
End Sub

Private Sub mnuHelpSearch_Click()
Dim nRet As Integer


    'if there is no helpfile for this project display a message to the user
    'you can set the HelpFile for your application in the
    'Project Properties dialog
    If Len(App.HelpFile) = 0 Then
        MsgBox "Unable to display Help Contents. There is no Help associated with this project.", vbInformation, Me.Caption
    Else
        On Error Resume Next
        nRet = OSWinHelp(Me.hWnd, App.HelpFile, 261, 0)
        If Err Then
            MsgBox Err.Description
        End If
    End If
End Sub

Private Sub mnuFileOpen_Click()
    Dim sFile As String
    Dim hFile As Long

    With dlgCommonDialog
        .Filter = "TSD-Dokumente (*.TSD)|*.TSD|Alle Dateien (*.*)|*.*"
        .Flags = cdlOFNHideReadOnly
        .ShowOpen
        If Len(.FileName) = 0 Then
            Exit Sub
        End If
        gDokFileName = .FileName
    End With
    
    gRecipients = ""
    
    fMainForm.sbStatusBar.Panels(1).text = "Dokument wird geöffnet..."
    ReadDokument gDokFileName
    RefreshListe
    fMainForm.sbStatusBar.Panels(1).text = ""

End Sub


Public Sub SignElement()
    mnuEditSign_Click
End Sub

Public Sub EncryptElement()
    mnuEditEncrypt_Click
End Sub

Public Sub SetSelectedNode(nd As Node)
    Set tvTreeView.SelectedItem = nd
    tvTreeView_Click
'    Me.Refresh
End Sub

Public Sub ReadDokument(strFileName As String)
On Error GoTo Err_ReadDocument
 Dim hResult As Long
 Dim startPos As Long, i As Integer

    HScroll1.Value = 0
    VScroll1.Value = 0
    gPictZoomFaktor = 1
    
    hResult = gNode.LoadFromTSD(strFileName)
    If hResult = -1 Then
        MsgBox "Unbekannte Dateiversion! Lesen abgebrochen!"
    ElseIf hResult = -2 Then
        MsgBox "Fehler beim Lesen des Inhaltsverzeichnisses! Lesen abgebrochen!"
    End If

'    If Not GetFileVersion(strFileName) Then
'        MsgBox "Unbekannte Dateiversion! Lesen abgebrochen!"
'        Exit Sub
'    End If
'
'    Set gNode = Nothing
'    Set gNode = New cNode
'
'    If ReadFileHeader(strFileName) Then
'        gNode.LoadFromTSD strFileName, gHeaderLen + 1
'        For i = 1 To gNode.SubNodes.Count
'            gNode.SubNodes.Item(i).LoadFromTSD strFileName, startPos
'        Next i
'    End If
Exit Sub

Err_ReadDocument:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "ReadDocument"
    Resume Next
End Sub

Private Sub mnuFileProperties_Click()
    'To Do
    MsgBox "Properties Code goes here!"
End Sub

Private Sub mnuFileClose_Click()
    'unload the form
    Unload Me
End Sub

Private Sub tvTreeView_AfterLabelEdit(CANCEL As Integer, NewString As String)
On Error GoTo Err_tvTreeView_AfterLabelEdit
    If Not gCurElement Is Nothing Then
        gCurElement.Caption = NewString
    End If
    tvTreeView_Click
Exit Sub

Err_tvTreeView_AfterLabelEdit:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "tvTreeView_AfterLabelEdit"
    Resume Next
End Sub

Public Sub RefreshView()
    tvTreeView_Click
End Sub

Private Sub tvTreeView_NodeClick(ByVal Node As ComctlLib.Node)
    tvTreeView_Click
End Sub

Private Sub tvTreeView_Click()
Dim i As Integer, n As Integer
Dim Parent As cNode

On Error GoTo Err_tvTreeView_Click

    If tvTreeView.SelectedItem Is Nothing Then
        Exit Sub
    End If

    gbDisableResize = True
    mnuEditShowDetails.Enabled = False
    ConfigToolBar
    gZahlSeiten = 0
    gAktSeite = 1
    Set gPrvElement = gCurElement
    Set gCurElement = gNode.SubNodes.Find(tvTreeView.SelectedItem.Key)
    
    If gCurElement Is Nothing Then
        gbDisableResize = False
        Exit Sub
    Else
        If ("Seite" = gCurElement.Class) Or ("Visualisierung" = gCurElement.Class) Then
            mnuEditShowDetails.Enabled = True
            If ("Seite" = gCurElement.Class) Then
                Set Parent = gCurElement.Parent
                gZahlSeiten = Parent.SubNodes.Count
                For i = 1 To Parent.SubNodes.Count
                    If Parent.SubNodes.Item(i).UniqueKey = gCurElement.UniqueKey Then
                        gAktSeite = i
                        Exit For
                    End If
                Next i
                Set Parent = Nothing
                LoadPage 0
            Else
                gZahlSeiten = gCurElement.SubNodes.Count
                gAktSeite = 1
                LoadPage gAktSeite
            End If
            ConfigToolBar
        Else
            nViewMode = 0
        End If
    End If
'    ZeigeDetails dat, dok
    ShowDetails
    gbDisableResize = False
    SizeControls imgSplitter.Left

Exit Sub

Err_tvTreeView_Click:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "tvTreeView_Click"
    Resume Next
    
End Sub

Public Sub ShowDetails()
On Error GoTo Err_ShowDetails
Dim itmX As ListItem, i As Integer
Dim strViewMode As String
Dim seite As cNode
Dim dFaktor1 As Double
Dim dFaktor2 As Double

    picRahmen.Visible = False
    VScroll1.Visible = False
    HScroll1.Visible = False
'    For i = 0 To 19
'        detPicture(i).Visible = False
'    Next i
    lvListView.Visible = True
    lvListView.View = lvwReport
    lvListView.ListItems.Clear
'    tbSeiten.Visible = False
    
    ConfigToolBar

    strViewMode = "Liste"
    Select Case gCurElement.Class
    Case "Visualisierung"
        gCurElement.FillListView lvListView
'        For i = 1 To gZahlSeiten
'            Set seite = gCurElement.SubNodes.Item(i)
'            If seite.UniqueKey <> gPictInfo(i - 1).Key Then
'                detPicture(i - 1).Stretch = False
'                detPicture(i - 1).Picture = LoadPicture(seite.TempFileName)
'                detPicture(i - 1).Refresh
'                gPictInfo(i - 1).Key = seite.UniqueKey
'                gPictInfo(i - 1).xSize = detPicture(i - 1).Width
'                gPictInfo(i - 1).ySize = detPicture(i - 1).Height
'                detPicture(i - 1).Stretch = True

'                If 0 < gPictZoomFaktor Then
'                    detPicture(i - 1).Width = gPictInfo(i - 1).xSize * gPictZoomFaktor
'                    detPicture(i - 1).Height = gPictInfo(i - 1).ySize * gPictZoomFaktor
'                Else
'                    dFaktor1 = picRahmen.Width / gPictInfo(i - 1).xSize
'                    dFaktor2 = picRahmen.Height / gPictInfo(i - 1).ySize
'                    If dFaktor1 < dFaktor2 Then
'                        detPicture(i - 1).Width = gPictInfo(i - 1).xSize * dFaktor1
'                        detPicture(i - 1).Height = gPictInfo(i - 1).ySize * dFaktor1
'                    Else
'                        detPicture(i - 1).Width = gPictInfo(i - 1).xSize * dFaktor2
'                        detPicture(i - 1).Height = gPictInfo(i - 1).ySize * dFaktor2
'                    End If
'                End If
'                detPicture(i - 1).Width = gPictInfo(i - 1).xSize * gPictZoomFaktor
'                detPicture(i - 1).Height = gPictInfo(i - 1).ySize * gPictZoomFaktor
'            End If
'        Next i
        SizeControls imgSplitter.Left
        If Not gPrvElement Is Nothing Then
            If ("Seite" = gPrvElement.Class) Or ("Visualisierung" = gPrvElement.Class) Then
                strViewMode = ""
            End If
        End If

    Case "Dokument"
        gCurElement.FillListView lvListView
    Case "Verzeichnis"
        gCurElement.FillListView lvListView
    Case "Anlage"
'        Set itmX = lvListView.ListItems.Add(, , gCurElement.Caption)
        Set itmX = lvListView.ListItems.Add(, gCurElement.UniqueKey, _
                    gCurElement.Caption)
        itmX.SubItems(1) = gCurElement.Size
        itmX.SubItems(2) = "Anlage"
        itmX.SubItems(3) = gCurElement.FileDate
    
    Case "Seite"
'        Set itmX = lvListView.ListItems.Add(, , gCurElement.Caption)
        Set itmX = lvListView.ListItems.Add(, gCurElement.UniqueKey, _
                    gCurElement.Caption)
        itmX.SubItems(1) = gCurElement.Size
        itmX.SubItems(2) = "Seite"
        itmX.SubItems(3) = gCurElement.FileDate

'        For i = 1 To gZahlSeiten
'            Set seite = gCurElement.Parent.SubNodes.Item(i)
'            If seite.UniqueKey <> gPictInfo(i - 1).Key Then
'                detPicture(i - 1).Stretch = False
'                detPicture(i - 1).Picture = LoadPicture(seite.TempFileName)
'                detPicture(i - 1).Refresh
'                gPictInfo(i - 1).Key = seite.UniqueKey
'                gPictInfo(i - 1).xSize = detPicture(i - 1).Width
'                gPictInfo(i - 1).ySize = detPicture(i - 1).Height
'                detPicture(i - 1).Stretch = True
'            End If
'        Next i
        SizeControls imgSplitter.Left
        If Not gPrvElement Is Nothing Then
            If ("Seite" = gPrvElement.Class) Or ("Visualisierung" = gPrvElement.Class) Then
                strViewMode = ""
            End If
        End If
    
    Case "Unterschrift"
'        Set itmX = lvListView.ListItems.Add(, , gCurElement.Caption)
        Set itmX = lvListView.ListItems.Add(, gCurElement.UniqueKey, _
                    gCurElement.Caption)
        itmX.SubItems(1) = gCurElement.Size
        itmX.SubItems(2) = "Unterschrift"
        itmX.SubItems(3) = gCurElement.FileDate
    End Select
    
    ZeigeDetailBild strViewMode
Exit Sub

Err_ShowDetails:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "ShowDetails"
    Resume Next
End Sub

'Private Sub ZeigeDetails(Optional dat As cDatei, Optional dok As cNode)
'Dim itmX As ListItem, i As Integer
'
'    picRahmen.Visible = False
'    VScroll1.Visible = False
'    HScroll1.Visible = False
'    For i = 0 To 19
'        detPicture(i).Visible = False
'    Next i
'    lvListView.Visible = True
'    lvListView.View = lvwReport
'    lvListView.ListItems.Clear
'    tbSeiten.Visible = False
'
'    If Not dok Is Nothing Then
'        Set itmX = lvListView.ListItems.Add(, , dok.Caption)
'        itmX.SubItems(1) = dok.Size
'        itmX.SubItems(2) = "Dokument"
'        itmX.SubItems(3) = dok.FileDate
'
'        For i = 0 To gAktDok.ZahlSeiten - 1
'            detPicture(i).Picture = LoadPicture(gAktDok.Page(i + 1).TempFileName)
'            detPicture(i).Refresh
'        Next i
'    End If
'
'    If Not dat Is Nothing Then
'        Set itmX = lvListView.ListItems.Add(, , dat.Name)
'        itmX.SubItems(1) = dat.Size
'        itmX.SubItems(2) = "Anlage"
'        itmX.SubItems(3) = dat.Datum
'    End If
'
'    If Not gAktPage Is Nothing Then
'        Set itmX = lvListView.ListItems.Add(, , gAktPage.Caption)
'        itmX.SubItems(1) = gAktPage.Size
'        itmX.SubItems(2) = "Seite"
'        itmX.SubItems(3) = gAktPage.FileDate
'
'        detPicture(0).Picture = LoadPicture(gAktPage.TempFileName)
'        detPicture(0).Refresh
'    End If
'
'    If Not gAktSign Is Nothing Then
'        Set itmX = lvListView.ListItems.Add(, , gAktSign.Caption)
'        itmX.SubItems(1) = gAktSign.Size
'        itmX.SubItems(2) = "Unterschrift"
'        itmX.SubItems(3) = gAktSign.Datum
'    End If
'
'    If dok Is Nothing And gAktPage Is Nothing Then
'        nViewMode = -1
'    Else
'        nViewMode = nViewMode - 1   ' Trick (ohne Änderung)
'    End If
'    ZeigeDetailBild "xxx"
'End Sub

Private Sub ZeigeDetailListe(Key As String)
On Error GoTo Err_ZeigeDetailListe
 Dim itmX As ListItem, i As Integer

    lblTitle(1).Caption = "Details"
    picRahmen.Visible = False
    VScroll1.Visible = False
    HScroll1.Visible = False
    lvListView.Visible = True
    lvListView.View = lvwReport
    lvListView.ListItems.Clear

Exit Sub

Err_ZeigeDetailListe:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "ZeigeDetailListe"
    Resume Next
End Sub

Public Sub ZeigeDetailBild(Key As String)
On Error GoTo Err_ZeigeDetailBild
 Dim i As Integer, y As Integer
 Dim seite As cNode

    Select Case gCurElement.Class
    Case "Seite"
'        nViewMode = nViewMode + 1
'        If nViewMode = 0 Then
        If Len(Key) > 0 Then
            If "Details" = Key Then
                nViewMode = 2
            Else
                nViewMode = 0
            End If
        End If
        lvListView.Visible = False
    
    Case "Visualisierung"
        If Len(Key) > 0 Then
            If "Details" = Key Then
                nViewMode = 2
            Else
                nViewMode = 0
            End If
        End If
        picRahmen.Visible = False
        VScroll1.Visible = False
        HScroll1.Visible = False
        lvListView.Visible = False
        If (gAktSeite > 0) And (gAktSeite <= gCurElement.SubNodes.Count) Then
            Set seite = gCurElement.SubNodes.Item(gAktSeite)
            detPicture(0).Stretch = False
            detPicture(0).Picture = LoadPicture(seite.TempFileName)
            detPicture(0).Refresh
            gPictInfo.Key = seite.UniqueKey
            gPictInfo.xSize = detPicture(0).Width
            gPictInfo.ySize = detPicture(0).Height
            detPicture(0).Stretch = True
            detPicture(0).Visible = True
        Else
            picRahmen.Visible = False
            VScroll1.Visible = False
            HScroll1.Visible = False
            lvListView.Visible = True
            nViewMode = 0
        End If
    
    Case Else
        picRahmen.Visible = False
        VScroll1.Visible = False
        HScroll1.Visible = False
'        For i = 0 To 19
'            detPicture(i).Visible = False
'        Next i
        lvListView.Visible = True
        nViewMode = 0
    End Select
    
'    nViewMode = nViewMode + 1
'    If (1 = nViewMode) And ("Seite" = gCurElement.Class) Then
'        nViewMode = 2
'    End If
'    If nViewMode > 2 Then
'        nViewMode = 0
'        lvListView.Visible = True
'    End If
    Form_Resize
'    For i = 0 To gZahlSeiten
'        y = detPicture(i).Top + detPicture(i).Height
'        If y < Me.Height Then
'            detPicture(i).Visible = True
'        Else
'            detPicture(i).Visible = False
'        End If
'    Next i
Exit Sub

Err_ZeigeDetailBild:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "ZeigeDetailBild"
    Resume Next
End Sub

Private Sub tvTreeView_OLECompleteDrag(Effect As Long)
On Error GoTo Err_tvTreeView_OLECompleteDrag
    
    If Not gEnableDroping Then
        gEnableDroping = True
    End If
Exit Sub

Err_tvTreeView_OLECompleteDrag:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "tvTreeView_OLECompleteDrag"
    Resume Next
End Sub

Private Sub lvListView_OLECompleteDrag(Effect As Long)
    tvTreeView_OLECompleteDrag Effect
End Sub

Private Sub tvTreeView_OLEDragDrop(Data As ComctlLib.DataObject, Effect As Long, Button As Integer, Shift As Integer, X As Single, y As Single)
On Error GoTo Err_tvTreeView_OLEDragDrop
 Dim oElement As cNode
 Dim i As Integer

    Set tvTreeView.DropHighlight = Nothing
    For i = 1 To Data.Files.Count
        If vbDirectory = (GetAttr(Data.Files.Item(i)) And vbDirectory) Then
            Set oElement = gNode.SubNodes.Add("Verzeichnis")
            If Not oElement Is Nothing Then
                oElement.LoadFromPath Data.Files.Item(i)
                oElement.Caption = Data.Files.Item(i)
                Do While InStr(oElement.Caption, "\") > 0
                    oElement.Caption = Mid(oElement.Caption, InStr(oElement.Caption, "\") + 1)
                Loop
                Set oElement = Nothing
            End If
        Else
            Set oElement = gNode.SubNodes.Add("Anlage")
            If Not oElement Is Nothing Then
                oElement.LoadFromFile Data.Files.Item(i)
                oElement.Caption = oElement.FileName
                Set oElement = Nothing
            End If
        End If
    Next i
    RefreshListe
Exit Sub

Err_tvTreeView_OLEDragDrop:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "tvTreeView_OLEDragDrop"
    Resume Next
End Sub

Private Sub LadeVerzeichnis(ByVal pfad As String)
Dim oFile As cNode, fname As String, dname As String
Dim strSearch As String, strTemp As String

    strSearch = pfad & "\*.*"
    dname = Dir(strSearch, vbNormal + vbDirectory)
    While Left(dname, 1) = "."
        dname = Dir
    Wend
    fname = pfad & "\" & dname
    While 0 < Len(dname)
        If vbDirectory = (GetAttr(fname) And vbDirectory) Then
            LadeVerzeichnis fname
            strTemp = Dir(strSearch, vbNormal + vbDirectory)
            While strTemp <> dname
                strTemp = Dir
            Wend
        Else
            Set oFile = gNode.SubNodes.Add("Anlage")
            If Not oFile Is Nothing Then
                oFile.Caption = "Anlage"
                oFile.LoadFromFile fname
                Set oFile = Nothing
            End If
        End If
        dname = Dir
        fname = pfad & "\" & dname
    Wend
End Sub

Private Sub tvTreeView_OLEDragOver(Data As ComctlLib.DataObject, Effect As Long, Button As Integer, Shift As Integer, X As Single, y As Single, State As Integer)
On Error GoTo Err_tvTreeView_OLEDragOver
    If gEnableDroping Then
        Effect = 1
        Set tvTreeView.DropHighlight = tvTreeView.HitTest(X, y)
    Else
        Effect = 0
    End If
Exit Sub

Err_tvTreeView_OLEDragOver:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "tvTreeView_OLEDragOver"
    Resume Next
End Sub

Private Sub tvTreeView_OLEStartDrag(Data As ComctlLib.DataObject, AllowedEffects As Long)

    Data.SetData , vbCFFiles
    AllowedEffects = 1
    gEnableDroping = False
End Sub

Private Sub lvListView_OLEStartDrag(Data As ComctlLib.DataObject, AllowedEffects As Long)

    Data.SetData , vbCFFiles
    AllowedEffects = 1
    gEnableDroping = False
End Sub

