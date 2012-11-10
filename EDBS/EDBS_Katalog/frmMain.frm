VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmMain 
   Caption         =   "EDBS-Katalog"
   ClientHeight    =   3645
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7170
   LinkTopic       =   "Form1"
   ScaleHeight     =   3645
   ScaleWidth      =   7170
   StartUpPosition =   3  'Windows-Standard
   Begin MSComctlLib.StatusBar StatusBar 
      Align           =   2  'Unten ausrichten
      Height          =   375
      Left            =   0
      TabIndex        =   9
      Top             =   3270
      Width           =   7170
      _ExtentX        =   12647
      _ExtentY        =   661
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   1
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   12144
         EndProperty
      EndProperty
   End
   Begin VB.ListBox lboDateien 
      Height          =   2205
      Left            =   1200
      TabIndex        =   7
      Top             =   960
      Width           =   4095
   End
   Begin VB.CommandButton K_Katalog 
      Caption         =   "Katalogisieren"
      Height          =   495
      Left            =   5520
      TabIndex        =   6
      Top             =   480
      Width           =   1575
   End
   Begin VB.CommandButton K_Exit 
      Caption         =   "&Beenden"
      Height          =   495
      Left            =   5520
      TabIndex        =   5
      Top             =   1080
      Width           =   1575
   End
   Begin VB.ComboBox cboBSZN_Ausgabe 
      Height          =   315
      Left            =   1200
      TabIndex        =   3
      Top             =   480
      Width           =   4095
   End
   Begin VB.TextBox strSourceDir 
      Height          =   285
      Left            =   1200
      TabIndex        =   1
      Top             =   120
      Width           =   5535
   End
   Begin VB.CommandButton K_SelectSourceDir 
      Caption         =   "..."
      Height          =   255
      Left            =   6720
      TabIndex        =   0
      Top             =   120
      Width           =   375
   End
   Begin VB.Label Label2 
      Caption         =   "Dateien"
      Height          =   375
      Left            =   120
      TabIndex        =   8
      Top             =   960
      Width           =   975
   End
   Begin VB.Label Label3 
      Caption         =   "Ausgabe"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   480
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "Verzeichnis"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   120
      Width           =   975
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub cboBSZN_Ausgabe_Click()
    Dim strBaseDir As String
    Dim strSourceDir As String
    Dim strSourceFile As String
        
    strBaseDir = Me.strSourceDir
    If Right(strBaseDir, 1) <> "\" Then
        strBaseDir = strBaseDir & "\"
    End If
    strSourceDir = Me.cboBSZN_Ausgabe.List(Me.cboBSZN_Ausgabe.ListIndex)
    
    Me.lboDateien.Clear
    strSourceFile = Dir(strBaseDir & strSourceDir & "\*.*")
    Do While Len(strSourceFile) > 0
        If Right(strSourceFile, 2) <> "db" Then
            Me.lboDateien.AddItem strSourceFile
        End If
        strSourceFile = Dir()
    Loop
    Me.Refresh
End Sub

Private Sub Form_Load()
    Me.strSourceDir = GetSetting("EDBS", "BSZN", "Basisverzeichnis")
End Sub

Private Sub K_Exit_Click()
    If Me.strSourceDir <> "" Then
        SaveSetting "EDBS", "BSZN", "Basisverzeichnis", Me.strSourceDir
    End If
    Unload Me
End Sub

Function ReadLine(hSourceFile As Long, strBuffer As String) As Long
    Dim strChar As String
    Dim lByteCnt
    strBuffer = ""
    lByteCnt = 0
    Do While EOF(hSourceFile) = False
        strChar = Input(1, #hSourceFile)
        lByteCnt = lByteCnt + 1
        If Asc(strChar) > 13 Then
            strBuffer = strBuffer & strChar
            Exit Do
        End If
    Loop
    Do While EOF(hSourceFile) = False
        strChar = Input(1, #hSourceFile)
        lByteCnt = lByteCnt + 1
        If Asc(strChar) <= 13 Then
            Exit Do
        End If
        strBuffer = strBuffer & strChar
    Loop
    ReadLine = lByteCnt
End Function

Private Sub K_Katalog_Click()
On Error GoTo Err_Katalog
    Dim strBaseDir As String
    Dim strSourceDir As String
    Dim lFileCnt As Long
    Dim lID_Datei As Long
    Dim strSourceFile As String
    Dim strSourceFileExtension As String
    Dim dbKatalog As Database
    Dim strBuffer As String
    Dim rs As Recordset
        
    Dim hSourceFile As Long
    Dim strSourceFileType As String * 2
    Dim strSourceFileName As String
    Dim strTempFileName As String
    Dim lByteCnt As Long
    Dim lBytesLast As Long
    
    Dim parser As TRiAS_EDBS.parser
    Dim objsEDBS As TRiAS_EDBS.EDBS_Objekte
    Dim objEDBS As TRiAS_EDBS.EDBS_Objekt
    Dim objsBI As TRiAS_EDBS.EDBS_BesondereInformationen
    Dim objBI As TRiAS_EDBS.EDBS_BesondereInformation
    Dim lx As Long
    Dim cntObjects As Long
    Dim lResult As Long
    Dim strKennzeichen As String
    
    strBaseDir = Me.strSourceDir
    If Right(strBaseDir, 1) <> "\" Then
        strBaseDir = strBaseDir & "\"
    End If
    strSourceDir = Me.cboBSZN_Ausgabe.List(Me.cboBSZN_Ausgabe.ListIndex)

    Set parser = New TRiAS_EDBS.parser
    
    Set dbKatalog = DBEngine.OpenDatabase(strBaseDir & "\_Katalog\Katalog.mdb")
    dbKatalog.Execute ("DELETE FROM Dateien WHERE Verzeichnis >= '" & strSourceDir & "'")
    
    lFileCnt = 0
    Do While lFileCnt < Me.lboDateien.ListCount
        Me.lboDateien.ListIndex = lFileCnt
        strSourceFile = Me.lboDateien.List(lFileCnt)
        lFileCnt = lFileCnt + 1
        Me!StatusBar.Panels(1).Text = strSourceFile
        Me.StatusBar.Refresh
        DoEvents

        Set rs = dbKatalog.OpenRecordset("SELECT Max(ID_Datei) as IDMAX FROM Dateien")
        If IsNull(rs.Fields("IDMAX").Value) Then
            lID_Datei = 1
        Else
            lID_Datei = rs.Fields("IDMAX").Value + 1
        End If
        rs.Close
        
        
        strTempFileName = ""
        strSourceFileName = ""
        hSourceFile = FreeFile
On Error Resume Next
        Open strBaseDir & strSourceDir & "\" & strSourceFile For Input As hSourceFile
        If Err Then
            MsgBox "Die Datei " & strBaseDir & strSourceDir & "\" & strSourceFile & " konnte nicht geöffnet werden!"
            hSourceFile = 0
        End If
On Error GoTo Err_Katalog
        Input #hSourceFile, strSourceFileType
        If strSourceFileType = "PK" Then
            Close hSourceFile
            Me.StatusBar.Panels(1).Text = strSourceFile & " wird entpackt ..."
            lResult = UnzipFileFromFile(strBaseDir & strSourceDir & "\" & strSourceFile, strSourceFileName)
            strTempFileName = strSourceFileName
        Else
            Close hSourceFile
            strSourceFileName = strBaseDir & strSourceDir & "\" & strSourceFile
        End If
        
        Me!StatusBar.Panels(1).Text = strSourceFile & " wird verarbeitet ..."
        
        dbKatalog.Execute ("INSERT INTO Dateien Values(" & Str(lID_Datei) & ", '" & strSourceDir & "', '" & ParsePath(strSourceFileName, 4) & "')")

'        Me.ProgressBar.Min = 0
'        Me.ProgressBar.Max = FileLen(strFileName)
        
'        lByteCnt = 0
'        lBytesLast = 0
'        hSourceFile = FreeFile
'        Open strSourceFileName For Input As hSourceFile
'
'        Do Until EOF(hSourceFile)
'            lByteCnt = lByteCnt + ReadLine(hSourceFile, strBuffer)
'            If lByteCnt = lBytesLast Then
'                 Exit Do
'            End If
'            lBytesLast = lByteCnt
''            Me.ProgressBar.Value = lBytes
''            strReadBuffer = Mid(strReadBuffer, 37)
'            DoEvents
'            If Mid(strBuffer, 29, 8) = "DLOB2005" Then
'                dbKatalog.Execute ("UPDATE Objekte SET FLOE =" & Str(lID_Datei) & " WHERE Objektnummer ='" & Mid(strBuffer, 120, 7) & "' AND AktualitätDesObjekts = '" & Mid(strBuffer, 106, 2) & "'")
'            End If
'        Loop
'        Close hSourceFile

        parser.SourceFileName = strSourceFileName
        parser.Modus = 0
        lResult = parser.LoadObjects()
        If lResult < 0 Then
            MsgBox "Fehler" & Str(lResult) & " beim Laden der Objekte!"
        Else
            Set objsEDBS = parser.Objekte
            For Each objEDBS In objsEDBS
                DoEvents
                If objEDBS.FLOE <> 0 Then
                    dbKatalog.Execute ("UPDATE Objekte SET FLOE =" & Str(lID_Datei) & " WHERE Objektnummer ='" & objEDBS.Objektnummer & "' AND AktualitätDesObjekts = '" & objEDBS.Aktualitaet & "'")
                Else
                    dbKatalog.Execute ("INSERT INTO Objekte(ID_Datei,Objektnummer,Folie,Objektart,AktualitätDesObjekts,Entstehungsdatum,Objekttyp,GrundpunktR,GrundpunktH) VALUES(" _
                        & Str(lID_Datei) _
                        & ", '" & objEDBS.Objektnummer _
                        & "', '" & Format(objEDBS.Folie, "000") _
                        & "', '" & Format(objEDBS.Objektart, "0000") _
                        & "', '" & objEDBS.Aktualitaet _
                        & "', '" & objEDBS.Entstehungsdatum _
                        & "', '" & objEDBS.Objekttyp _
                        & "', " & Str(objEDBS.GrundpunktR) _
                        & ", " & Str(objEDBS.GrundpunktH) _
                        & ")")
                    Set objsBI = objEDBS.BesondereInformationen
                    If Not objsBI Is Nothing Then
                        For Each objBI In objsBI
    '                        strKennzeichen = Left(objBI.Textdaten, 2)
    '                        If 0 < Len(strKennzeichen) And 0 < InStr("FS;HA;SB;FL", strKennzeichen) Then
    '                        If 0 < Len(objBI.Textdaten) And 0 < InStr("11;12;13;14;15;16;17", Format(objBI.Informationsart, "00")) Then
                            If 0 < Len(objBI.Textdaten) And 11 <= objBI.Informationsart And objBI.Informationsart <= 17 Then    'Objektnamen
    '                            dbKatalog.Execute "UPDATE ObjekteMitKennzeichen"
                                dbKatalog.Execute "INSERT INTO Objektnamen(ID_Datei,Objektnummer,AktualitätDesObjekts,Objektart,Informationsart,Textdaten) VALUES(" _
                                & Str(lID_Datei) _
                                & ", '" & objEDBS.Objektnummer _
                                & "', '" & objEDBS.Aktualitaet _
                                & "', '" & Format(objBI.Objektart, "0000") _
                                & "', '" & Format(objBI.Informationsart, "00") _
                                & "', '" & objBI.Textdaten _
                                & "')"
                            End If
                            Set objBI = Nothing
                        Next objBI
                    End If
                    Set objsBI = Nothing
                End If
                Set objEDBS = Nothing
            Next objEDBS
            Set objsEDBS = Nothing
        End If
        If Len(strTempFileName) > 0 Then
            Kill strTempFileName
            strTempFileName = ""
        End If
    Loop
    dbKatalog.Close
    Set parser = Nothing
    MsgBox "Die Dateien wurden katalogisiert!"
Exit Sub

Err_Katalog:
    MsgBox Err.Description
    Resume Next
End Sub

Private Sub K_SelectSourceDir_Click()
On Error Resume Next
    Dim fSelDir As frmSelDir
    Set fSelDir = New frmSelDir
    fSelDir.Dir1.Path = Me.strSourceDir
    Load fSelDir
    fSelDir.Show vbModal, Me
    If fSelDir.Tag = Chr(13) Then
    Else
        Me.strSourceDir = fSelDir.Tag
    End If
    Unload fSelDir
    Set fSelDir = Nothing
End Sub

Private Sub strSourceDir_Change()
On Error GoTo Err_strSourceDir
 Dim strTemp As String
 Dim ix As Integer
    Me.cboBSZN_Ausgabe.Clear
    Me.lboDateien.Clear
    ix = 0
    strTemp = Dir(strSourceDir, vbDirectory)
    Do While Len(strTemp) > 0
        If vbDirectory = (GetAttr(strSourceDir & strTemp) And vbDirectory) Then
            If Left(strTemp, 1) <> "." And Left(strTemp, 1) <> "_" Then
                Me.cboBSZN_Ausgabe.AddItem strTemp
                Me.cboBSZN_Ausgabe.ItemData(Me.cboBSZN_Ausgabe.ListCount - 1) = ix
                ix = ix + 1
            End If
        End If
        strTemp = Dir()
    Loop
    If ix > 0 Then
        Me.cboBSZN_Ausgabe.ListIndex = ix - 1
    End If
Exit Sub

Err_strSourceDir:
    If Err.Number = 53 Then
        Exit Sub
    Else
        MsgBox Err.Description
        Exit Sub
    End If
End Sub

