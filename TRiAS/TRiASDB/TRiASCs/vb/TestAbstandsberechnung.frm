VERSION 5.00
Object = "{C932BA88-4374-101B-A56C-00AA003668DC}#1.1#0"; "msmask32.ocx"
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Begin VB.Form TestAbstandsberechnung 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Test Abstandsberechnung (Geo-Toolbox)"
   ClientHeight    =   8175
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   6900
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   8175
   ScaleWidth      =   6900
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox CalcCount 
      BeginProperty DataFormat 
         Type            =   1
         Format          =   "0"
         HaveTrueFalseNull=   0
         FirstDayOfWeek  =   0
         FirstWeekOfYear =   0
         LCID            =   1031
         SubFormatType   =   1
      EndProperty
      Height          =   285
      Left            =   2520
      TabIndex        =   30
      Top             =   3840
      Width           =   735
   End
   Begin VB.CommandButton CalcDistances 
      Caption         =   "Abstände berechnen"
      Height          =   375
      Left            =   4200
      TabIndex        =   7
      Top             =   3840
      Width           =   2535
   End
   Begin VB.CommandButton SampleCoordSys 
      Caption         =   "&Beispieldaten "
      Height          =   375
      Left            =   4200
      TabIndex        =   2
      Top             =   240
      Width           =   2535
   End
   Begin VB.Frame Frame3 
      Height          =   30
      Left            =   1800
      TabIndex        =   22
      Top             =   840
      Width           =   4935
   End
   Begin VB.CommandButton SelectCoordSys 
      Caption         =   "&Koordinatensystem auswählen"
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Top             =   240
      Width           =   2655
   End
   Begin MSComDlg.CommonDialog FileDialog 
      Left            =   120
      Top             =   1440
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
      DefaultExt      =   "tcf"
      DialogTitle     =   "Koordinatensystem auswählen"
      Filter          =   "TRiAS Koordinatensystemdateien (*.tsf);*.tsf"
   End
   Begin MSMask.MaskEdBox HochEnd 
      Height          =   375
      Left            =   3360
      TabIndex        =   6
      Top             =   2880
      Width           =   1935
      _ExtentX        =   3413
      _ExtentY        =   661
      _Version        =   393216
      AutoTab         =   -1  'True
      MaxLength       =   32
      Format          =   "##°##'##.#####"""
      Mask            =   "##°##'##.#####"""
      PromptChar      =   "_"
   End
   Begin MSMask.MaskEdBox HochStart 
      Height          =   375
      Left            =   3360
      TabIndex        =   4
      Top             =   2400
      Width           =   1935
      _ExtentX        =   3413
      _ExtentY        =   661
      _Version        =   393216
      AllowPrompt     =   -1  'True
      AutoTab         =   -1  'True
      MaxLength       =   15
      Format          =   "##°##'##.#####"""
      Mask            =   "##°##'##.#####"""
      PromptChar      =   "_"
   End
   Begin MSMask.MaskEdBox RechtsEnd 
      Height          =   375
      Left            =   1200
      TabIndex        =   5
      Top             =   2880
      Width           =   1935
      _ExtentX        =   3413
      _ExtentY        =   661
      _Version        =   393216
      AllowPrompt     =   -1  'True
      AutoTab         =   -1  'True
      MaxLength       =   15
      Format          =   "##°##'##.#####"""
      Mask            =   "##°##'##.#####"""
      PromptChar      =   "_"
   End
   Begin MSMask.MaskEdBox RechtsStart 
      Height          =   375
      Left            =   1200
      TabIndex        =   3
      Top             =   2400
      Width           =   1935
      _ExtentX        =   3413
      _ExtentY        =   661
      _Version        =   393216
      AllowPrompt     =   -1  'True
      AutoTab         =   -1  'True
      MaxLength       =   15
      Format          =   "##°##'##.#####"""
      Mask            =   "##°##'##.#####"""
      PromptChar      =   "_"
   End
   Begin VB.Frame Frame1 
      Height          =   30
      Left            =   1200
      TabIndex        =   9
      Top             =   2040
      Width           =   5535
   End
   Begin VB.Frame Frame2 
      Height          =   30
      Left            =   4320
      TabIndex        =   15
      Top             =   3600
      Width           =   2415
   End
   Begin MSFlexGridLib.MSFlexGrid DistResults 
      Height          =   2655
      Left            =   120
      TabIndex        =   8
      Top             =   5280
      Width           =   6615
      _ExtentX        =   11668
      _ExtentY        =   4683
      _Version        =   393216
      Rows            =   11
      Cols            =   3
      AllowBigSelection=   0   'False
      ScrollBars      =   0
      SelectionMode   =   1
      Appearance      =   0
   End
   Begin VB.Label Label5 
      Caption         =   "Anzahl der Berechnungen:"
      Height          =   255
      Left            =   360
      TabIndex        =   29
      Top             =   3840
      Width           =   1935
   End
   Begin VB.Label Label4 
      Caption         =   "... oder ..."
      Height          =   255
      Left            =   3120
      TabIndex        =   28
      Top             =   360
      Width           =   855
   End
   Begin VB.Label Label3 
      Caption         =   "Koordinatensystem "
      Height          =   255
      Left            =   120
      TabIndex        =   27
      Top             =   720
      Width           =   1455
   End
   Begin VB.Label CoordSysCategory 
      Height          =   255
      Left            =   3000
      TabIndex        =   26
      Top             =   1080
      Width           =   3735
      WordWrap        =   -1  'True
   End
   Begin VB.Label CategoryLabel 
      Caption         =   "Kategorie:"
      Height          =   255
      Left            =   1920
      TabIndex        =   25
      Top             =   1080
      Width           =   855
   End
   Begin VB.Label DescLabel 
      Caption         =   "Beschreibung:"
      Height          =   255
      Left            =   1920
      TabIndex        =   24
      Top             =   1440
      Width           =   1095
   End
   Begin VB.Label CoordSysDesc 
      Height          =   255
      Left            =   3000
      TabIndex        =   23
      Top             =   1440
      Width           =   3735
   End
   Begin VB.Label StartLabel 
      Caption         =   "&Startwert:"
      Height          =   255
      Left            =   210
      TabIndex        =   12
      Top             =   2460
      Width           =   945
   End
   Begin VB.Label Koordinaten 
      Caption         =   "Koordinaten"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   1920
      Width           =   975
   End
   Begin VB.Label HochEndOut 
      Height          =   255
      Left            =   3360
      TabIndex        =   21
      Top             =   4800
      Width           =   1935
   End
   Begin VB.Label RechtsEndOut 
      Height          =   255
      Left            =   1200
      TabIndex        =   20
      Top             =   4800
      Width           =   1935
   End
   Begin VB.Label Label2 
      Caption         =   "Endwert:"
      Height          =   255
      Left            =   240
      TabIndex        =   19
      Top             =   4800
      Width           =   735
   End
   Begin VB.Label HochStartOut 
      Height          =   255
      Left            =   3360
      TabIndex        =   18
      Top             =   4440
      Width           =   1935
   End
   Begin VB.Label RechtsStartOut 
      Height          =   255
      Left            =   1200
      TabIndex        =   17
      Top             =   4440
      Width           =   1935
   End
   Begin VB.Label Label1 
      Caption         =   "Startwert:"
      Height          =   255
      Left            =   240
      TabIndex        =   16
      Top             =   4440
      Width           =   735
   End
   Begin VB.Label ResultLabel 
      Caption         =   "Nach unterschiedlichen Verfahren berechnete Abstände:"
      Height          =   255
      Left            =   120
      TabIndex        =   14
      Top             =   3480
      Width           =   4095
   End
   Begin VB.Label HochEndLabel 
      Caption         =   "Hochwert:"
      Height          =   255
      Left            =   3360
      TabIndex        =   11
      Top             =   2160
      Width           =   855
   End
   Begin VB.Label RechtsEndLabel 
      Caption         =   "Rechtswert:"
      Height          =   255
      Left            =   1200
      TabIndex        =   10
      Top             =   2160
      Width           =   975
   End
   Begin VB.Label EndLabel 
      Caption         =   "&Endwert:"
      Height          =   255
      Left            =   210
      TabIndex        =   13
      Top             =   2940
      Width           =   855
   End
End
Attribute VB_Name = "TestAbstandsberechnung"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Option Base 0

' Anzahl der Zeilen im FlexGrid
Const iRows As Integer = 10

' Eingegebenen Koordinaten
Dim dRechtsStart As Double          ' Koordinate 1
Dim dHochStart As Double

Dim dRechtsEnd As Double            ' Koordinate 2
Dim dHochEnd As Double

' Anzahl der Berechnungen
Dim iCount As Integer

' Koordinatensysteme
Dim CTF As TRiASCSTransform         ' Transformationsobjekt
Dim csOut As TRIASCS.TRIASCS                ' Koordinatensystem, in dem gerechnet wird
Dim csIn As TRIASCS.TRIASCS                 ' Koordinatensystem der Eingabekoordinaten

Dim UIService As TRiASCSUIService   ' Serviceobjekt für Formatierung, Konvertierung etc.

Private Sub InitCoords(ptStart() As Double, ptEnd() As Double)
    
    ptStart(0) = dRechtsStart
    ptStart(1) = dHochStart
    ptStart(2) = 0
    ptEnd(0) = dRechtsEnd
    ptEnd(1) = dHochEnd
    ptEnd(2) = 0

End Sub

Private Sub CalculateDistance( _
    DistService As TRiASCSDistanceService, _
    acc As DIST_ACCURACY, Col As Integer)

' Koordinatenfelder
Dim ptStart() As Double: ReDim ptStart(0 To 2)
Dim ptEnd() As Double: ReDim ptEnd(0 To 2)

' Zeitmessung
Dim i As Integer
Dim dMeanTime As Double

    dMeanTime = 0
    For i = 0 To iCount
    ' Koordinatenfelder initialisieren (unbedingt jedesmal machen!)
        InitCoords ptStart, ptEnd
        
    ' geforderte genauigkeit voreinstellen
        DistService.Accuracy = acc
        
    ' Berechnung durchführen und resultat anzeigen
    Dim dDist As Double

        dDist = DistService.GetDistance(csIn, ptStart, csIn, ptEnd)
        DistResults.TextMatrix(Col, 1) = Str$(dDist)
    
    ' Zeit der letzten Berechnung
        dMeanTime = dMeanTime + DistService.LastTime
    Next i
    
    DistResults.TextMatrix(Col, 2) = Str$(dMeanTime / iCount)
    DoEvents
    
End Sub

Private Sub CalculateDistances()
' Fehlerbehandlung
    On Error GoTo errorLabel
    
' Berechnungen nur, wenn alle Koordinaten gegeben sind
    If (dRechtsStart = 0 Or dRechtsEnd = 0 Or dHochStart = 0 Or dHochEnd = 0) Then
        Exit Sub
    End If

' Koordinatensystem muß gegeben sein
    If (csIn Is Nothing Or csOut Is Nothing) Then
        Exit Sub
    End If

' FlexGrid leeren
Dim i As Integer

    For i = 1 To iRows
        DistResults.TextMatrix(i, 1) = ""
        DistResults.TextMatrix(i, 2) = ""
    Next i
    
' Feststellen, wie oft Berechnent werden soll
    iCount = CInt(CalcCount.Text)
    If (iCount <= 1) Then
        iCount = 500
        CalcCount.Text = Str$(iCount)
    End If
    
' Abstandsberechnungen durchführen
Dim DistService As New TRiASCSDistanceService

    Set DistService.TransformPipe = CTF

    Me.MousePointer = 11
    Call CalculateDistance(DistService, ACCURACY_Planar, 1)
    Call CalculateDistance(DistService, ACCURACY_SphericMajorAxis, 2)
    Call CalculateDistance(DistService, ACCURACY_SphericArithMean, 3)
    Call CalculateDistance(DistService, ACCURACY_SphericGeomMean, 4)
    Call CalculateDistance(DistService, ACCURACY_SphericHarmMean, 5)
    Call CalculateDistance(DistService, ACCURACY_SphericVolume, 6)
    Call CalculateDistance(DistService, ACCURACY_SphericArea, 7)
    Call CalculateDistance(DistService, ACCURACY_SphericGeomMeanCurvatureRadii, 8)
    Call CalculateDistance(DistService, ACCURACY_Ellipsoidal1, 9)
    Call CalculateDistance(DistService, ACCURACY_Ellipsoidal2, 10)

errorLabel:
    Set DistService.TransformPipe = Nothing
    Me.MousePointer = 0

End Sub

Private Sub CalcDistances_Click()
    Call CalculateDistances
End Sub

Private Sub SampleCoordSys_Click()
' bisheriges Koordinatensystem freigeben
    Set csOut = Nothing
    Set csIn = Nothing

' Koordinatensystem voreinstellen
    On Error GoTo errorLabel
    Set csOut = New TRIASCS
    Set csIn = New TRIASCS

    csOut.LoadFromFile ("BeGk12_3.tcf")     ' throws Err on bad file
    CTF.OutputCS = csOut

    csIn.LoadFromFile ("BeGk12_3.tcf")      ' throws Err on bad file
    
' Beschreibung des neuen Koordinatensystems anzeigen
    CoordSysCategory.Caption = csIn.Category
    CoordSysDesc.Caption = csIn.Description
    
' Eingabemasken setzen
Dim Mask As String

    Mask = UIService.InputMask(csIn, COORDELEMENT_X)
    RechtsStart.Mask = Mask
    RechtsStart.Format = Mask
    RechtsStart.Text = "4511711"
    RechtsEnd.Mask = Mask
    RechtsEnd.Format = Mask
    RechtsEnd.Text = "4544446"
    
    Mask = UIService.InputMask(csIn, COORDELEMENT_Y)
    HochStart.Mask = Mask
    HochStart.Format = Mask
    HochStart.Text = "5832672"
    HochEnd.Mask = Mask
    HochEnd.Format = Mask
    HochEnd.Text = "5831982"
    
    Exit Sub
    
errorLabel:
    MsgBox "Die Datei 'BeGk12_3.tsf' konnte nicht geöffnet werden oder enthält kein TRiAS Koordinatensystem!", _
        vbOKOnly Or vbExclamation, "Beispieldaten"
    Exit Sub

End Sub

Private Sub SelectCoordSys_Click()
' bisheriges Koordinatensystem freigeben
    Set csOut = Nothing
    Set csIn = Nothing
    
' Datei Öffnen Dialog anzeigen
    On Error GoTo labelNoFile
    
    FileDialog.DialogTitle = "Koordinatensystem auswählen"
    FileDialog.Filter = "TRiAS Koordinatensystemdateien (*.tcf)"
    FileDialog.FilterIndex = 0
    FileDialog.DefaultExt = "tcf"
    FileDialog.FileName = "*.tcf"
    FileDialog.CancelError = True
    FileDialog.ShowOpen

' Laden der Datei/ des Koordinatensystems
    On Error GoTo errorLabel
    
    Set csOut = New TRIASCS
    Set csIn = New TRIASCS
    
    csOut.LoadFromFile (FileDialog.FileName)    ' throws Err on bad file
    CTF.OutputCS = csOut

    csIn.LoadFromFile (FileDialog.FileName)     ' throws Err on bad file
    
' Beschreibung des neuen Koordinatensystems anzeigen
    CoordSysCategory.Caption = csIn.Category
    CoordSysDesc.Caption = csIn.Description
    
' Eingabemasken setzen
Dim Mask As String

    Mask = UIService.InputMask(csIn, COORDELEMENT_X)
    RechtsStart.Mask = Mask
    RechtsStart.Format = Mask
    RechtsEnd.Mask = Mask
    RechtsEnd.Format = Mask
    
    Mask = UIService.InputMask(csIn, COORDELEMENT_Y)
    HochStart.Mask = Mask
    HochStart.Format = Mask
    HochEnd.Mask = Mask
    HochEnd.Format = Mask

    Exit Sub
    
errorLabel:
    MsgBox "Die ausgewählte Datei ist kein TRiAS Koordinatensystem!", _
        vbOKOnly Or vbExclamation, "Koordinatensystem auswählen"
    Exit Sub
    
labelNoFile:
    Exit Sub        ' abgebrochen
    
End Sub

Private Sub Form_Load()
' Spalten im Flexgrid auf richtige Größe bringen
    DistResults.ColWidth(0) = 2 * DistResults.Width / 5
    DistResults.ColWidth(1) = (DistResults.Width - DistResults.ColWidth(0)) / 2
    DistResults.ColWidth(2) = DistResults.ColWidth(1)
    
' Höhe richten
Dim iHeight As Integer
Dim i As Integer

    iHeight = 0
    For i = 0 To iRows
        iHeight = iHeight + DistResults.RowHeight(i)
    Next i
    DistResults.Height = iHeight% + iHeight% / 100
    
' Überschriften setzen
    DistResults.TextMatrix(0, 0) = "Berechnungsalgorithmus"
    DistResults.TextMatrix(0, 1) = "Berechneter Abstand"
    DistResults.TextMatrix(0, 2) = "Benötigte Zeit [ms]"
    
' Algorithmen setzen
    DistResults.TextMatrix(1, 0) = "Planar (Pythagoras)"
    DistResults.TextMatrix(2, 0) = "Kugel (Hauptachse)"
    DistResults.TextMatrix(3, 0) = "Kugel (arithm. Mittelwert)"
    DistResults.TextMatrix(4, 0) = "Kugel (geom. Mittelwert)"
    DistResults.TextMatrix(5, 0) = "Kugel (harm. Mittelwert)"
    DistResults.TextMatrix(6, 0) = "Kugel (Volumen wie Ellipsoid)"
    DistResults.TextMatrix(7, 0) = "Kugel (Oberfläche wie Ellipsoid)"
    DistResults.TextMatrix(8, 0) = "Kugel (Mittel der Krümmungsradien)"
    DistResults.TextMatrix(9, 0) = "Ellipsoid (Algorithmus 1)"
    DistResults.TextMatrix(10, 0) = "Ellipsoid (Algorithmus 2)"
    
' Variablen initialisieren
    dRechtsStart = 0
    dRechtsEnd = 0
    dHochStart = 0
    dHochEnd = 0
    iCount = 500
    CalcCount.Text = Str$(iCount)
    
' Koordinatensystem
    Set CTF = New TRiASCSTransform

' UIService instantiieren
    Set UIService = New TRiASCSUIService
    
' MaskEdits
    RechtsStart.Mask = ""
    RechtsStart.Format = ""
    RechtsStart.Text = ""
    HochStart.Mask = ""
    HochStart.Format = ""
    HochStart.Text = ""
    RechtsEnd.Mask = ""
    RechtsEnd.Format = ""
    RechtsEnd.Text = ""
    HochEnd.Mask = ""
    HochEnd.Format = ""
    HochEnd.Text = ""
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    CTF.ShutDown
    Set CTF = Nothing
    Set UIService = Nothing
End Sub

' wenn ein Koordinatenfeld modifiziert wurde, dann den neuen Koordinatenwert
' auf seine Gültigkeit prüfen und zum Test wieder ausgeben
Private Sub RechtsStart_Change()
    If (Not csIn Is Nothing) Then
        dRechtsStart = UIService.Convert(csIn, COORDELEMENT_X, RechtsStart.Text)
        RechtsStartOut.Caption = UIService.Format(csIn, COORDELEMENT_X, dRechtsStart)
    End If
End Sub

Private Sub HochStart_Change()
    If (Not csIn Is Nothing) Then
        dHochStart = UIService.Convert(csIn, COORDELEMENT_Y, HochStart.Text)
        HochStartOut.Caption = UIService.Format(csIn, COORDELEMENT_Y, dHochStart)
    End If
End Sub

Private Sub RechtsEnd_Change()
    If (Not csIn Is Nothing) Then
        dRechtsEnd = UIService.Convert(csIn, COORDELEMENT_X, RechtsEnd.Text)
        RechtsEndOut.Caption = UIService.Format(csIn, COORDELEMENT_X, dRechtsEnd)
    End If
End Sub

Private Sub HochEnd_Change()
    If (Not csIn Is Nothing) Then
        dHochEnd = UIService.Convert(csIn, COORDELEMENT_Y, HochEnd.Text)
        HochEndOut.Caption = UIService.Format(csIn, COORDELEMENT_Y, dHochEnd)
    End If
End Sub

