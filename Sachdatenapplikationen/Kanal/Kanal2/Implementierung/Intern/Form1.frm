VERSION 5.00
Object = "{05589FA0-C356-11CE-BF01-00AA0055595A}#2.0#0"; "msdxm.ocx"
Begin VB.Form frmTestProg 
   Caption         =   "Testprogramm (Kanalkopplung)"
   ClientHeight    =   6660
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8175
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   Picture         =   "Form1.frx":08CA
   ScaleHeight     =   6660
   ScaleWidth      =   8175
   Begin VB.CommandButton cmdClear 
      Appearance      =   0  'Flat
      Height          =   375
      Left            =   0
      Picture         =   "Form1.frx":87B6
      Style           =   1  'Graphical
      TabIndex        =   3
      Top             =   6240
      Width           =   375
   End
   Begin VB.CheckBox chkAusgabeCheck 
      Caption         =   "Check1"
      Height          =   255
      Left            =   0
      TabIndex        =   2
      Top             =   5280
      Value           =   1  'Checked
      Width           =   255
   End
   Begin VB.TextBox txtAusgabe 
      BorderStyle     =   0  'None
      Height          =   1335
      Left            =   480
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   1
      Top             =   5280
      Width           =   7695
   End
   Begin VB.CommandButton btStart 
      Caption         =   "Start"
      Height          =   375
      Left            =   6840
      TabIndex        =   0
      Top             =   240
      Width           =   1335
   End
   Begin AMovieCtl.ActiveMovie ActiveMovie1 
      Height          =   3255
      Left            =   2280
      TabIndex        =   4
      Top             =   1800
      Width           =   5775
      Appearance      =   0
      AutoStart       =   -1  'True
      AllowChangeDisplayMode=   -1  'True
      AllowHideDisplay=   0   'False
      AllowHideControls=   -1  'True
      AutoRewind      =   -1  'True
      Balance         =   0
      CurrentPosition =   0
      DisplayBackColor=   0
      DisplayForeColor=   16777215
      DisplayMode     =   0
      Enabled         =   -1  'True
      EnableContextMenu=   -1  'True
      EnablePositionControls=   -1  'True
      EnableSelectionControls=   0   'False
      EnableTracker   =   -1  'True
      Filename        =   "D:\Daten\Pics\avi\destiny3.mpg"
      FullScreenMode  =   0   'False
      MovieWindowSize =   0
      PlayCount       =   0
      Rate            =   1
      SelectionStart  =   -1
      SelectionEnd    =   -1
      ShowControls    =   -1  'True
      ShowDisplay     =   -1  'True
      ShowPositionControls=   0   'False
      ShowTracker     =   -1  'True
      Volume          =   -600
   End
   Begin VB.Line Line2 
      BorderColor     =   &H80000010&
      X1              =   0
      X2              =   8160
      Y1              =   5160
      Y2              =   5160
   End
   Begin VB.Line Line1 
      BorderColor     =   &H80000014&
      X1              =   0
      X2              =   8160
      Y1              =   5140
      Y2              =   5140
   End
End
Attribute VB_Name = "frmTestProg"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim kopplung As Koppelmodul

Const x1 = 2554124
Const y1 = 6108681
Const x2 = 3053178
Const y2 = 5290544

Dim xmitte As Double
Dim ymitte As Double
Dim radius As Double
Dim geometrieinited As Boolean

Dim outtext As String
Const cstKlasse = "klasse"
Const cstLinie = "Linie"
Const cstText = "Text"
Const cstKreis = "Kreis"

Private Sub btStart_Click()
    Starttest
    creationtest
    testeVisualisation
    CloseTest
End Sub

Private Sub testeVisualisation()
    output ("Teste Visualisierung")
    Dim testinterface As Darstellung
    Set testinterface = kopplung
    
    If testinterface Is Nothing Then
        output ("QI failed")
        Exit Sub
    End If
    
    Dim klasses() As String
    ReDim klasses(0)
    klasses(0) = cstKlasse
    
    Dim objids() As String
    ReDim objids(0)
    objids(0) = "Linie" & 1
        
    If (0 <> testinterface.Auswaehlen(objids, klasses)) Then
        output ("Fehler in Routine auswählen")
    End If
    
    MsgBox ("kann's weiter gehen")
End Sub

Private Function min(val1 As Double, val2 As Double) As Double
    min = val1
    If (val2 < val1) Then
        min = val2
    End If
End Function

Private Sub GenerateBaseGeometrie()
    If geometrieinited = False Then
        xmitte = (x1 + x2) / 2
        ymitte = (y1 + y2) / 2
        radius = min(Abs(x2 - x1), Abs(y2 - y1)) / 2
    End If
End Sub

Private Sub GenerateLine(number As Long, ByRef x() As Double, ByRef y() As Double)
    GenerateBaseGeometrie   ' Basisgeometrien initialisieren
    
    ' Größe setzen
    ReDim x(1)
    ReDim y(1)
    
    Dim dx As Double
    dx = Sin(number * 0.01) * radius
    
    Dim dy As Double
    dy = Cos(number * 0.01) * radius
    
    x(0) = xmitte + dx
    x(1) = xmitte - dx
    y(0) = ymitte + dy
    y(1) = ymitte - dy
End Sub

Private Sub GenerateText(number As Long, ByRef x As Double, ByRef y As Double, ByRef drehwinkel As Double, ByRef text As String, ByRef textalignment As KANAL_TextBezugspunkt)
    GenerateBaseGeometrie       ' Basisgeometrien initialisieren
    
    x = xmitte + number * 100   ' immer etwas versetzen
    y = ymitte + number * 100   ' immer etwas versetzen
    drehwinkel = number * 10   ' in 10° Schritten drehen
    
    text = "TextObjekt " & number
    textalignment = number Mod 3
End Sub

Private Sub GenerateKreis(number As Long, ByRef x As Double, ByRef y As Double, ByRef durchmesser As Double)
    GenerateBaseGeometrie       ' Basisgeometrien initialisieren
    
    x = xmitte + number * 100   ' immer etwas versetzen
    y = ymitte + number * 100   ' immer etwas versetzen
    durchmesser = number * 10   ' in 10m Schritten vergrößern
End Sub

Private Sub creationtest()
    Const testklasse = "Klasse"
    Const testID = 0
    Dim x() As Double   ' für Punktarrays
    Dim y() As Double
    Dim sx As Double    ' für einzelne Punkte
    Dim sy As Double
    Dim drehwinkel As Double
    Dim textalignment As KANAL_TextBezugspunkt
    Dim vistext As String
    Dim durchmesser As Double
    
    Dim testinterface As Geometrie
    Set testinterface = kopplung
    
    If testinterface Is Nothing Then
        output ("QI failed")
        Exit Sub
    End If
    
    Dim objId As String
    Dim i As Long
    
    For i = 1 To 10
        ' eine Geometrie generieren
        GenerateLine i, x, y
        
        ' einen ObjID generieren
        objId = cstLinie & i
        
        ' jetzt das Object erzeugen
        output ("Erzeuge das LinienObjekt " & objId & " der Klasse " & cstKlasse)
        If (testinterface.ErzeugeLinie(x, y, objId, cstKlasse) <> 0) Then
            output ("Test failed")
        End If
        
        ' Jetzt noch ein paar Texte
        GenerateText i, sx, sy, drehwinkel, vistext, textalignment
        objId = cstText & i
        ' jetzt das Object erzeugen
        output ("Erzeuge das TextObjekt " & objId & " der Klasse " & cstKlasse)
        If (testinterface.ErzeugeText(sx, sy, textalignment, drehwinkel, vistext, objId, cstKlasse) <> 0) Then
            output ("Test failed")
        End If
        
        ' Jetzt noch ein Kreischen
        GenerateKreis i, sx, sy, durchmesser
        objId = cstKreis & i
        ' jetzt das Object erzeugen
        output ("Erzeuge das KreisObjekt " & objId & " der Klasse " & cstKlasse)
        If (testinterface.ErzeugeKreis(sx, sy, durchmesser, objId, cstKlasse) <> 0) Then
            output ("Test failed")
        End If
        
        
    Next
End Sub

Private Sub output(str As String)
     outtext = outtext & vbCrLf & str
     If (chkAusgabeCheck.Value = 1) Then
        txtAusgabe.text = outtext
     End If
End Sub

Private Sub Starttest()
    output ("")
    output ("ErzeugeKoppelmodul")
    Set kopplung = New Koppelmodul
    Dim test As kopplung
    Set test = kopplung
    
    If test Is Nothing Then
        output ("QI failed")
        Exit Sub
    End If
        
    output ("")
    output ("Starte TRiAS ")
    If test.StarteKopplung <> 0 Then
        output ("StarteKoplung failed")
        Exit Sub
    End If
End Sub

Private Sub CloseTest()
    Dim test As kopplung
    Set test = kopplung

    output ("Beende TRiAS ")
    If test.BeendeKopplung <> 0 Then
        output ("BeendeKopplung failed")
        Exit Sub
    End If
    
    Set kopplung = Nothing
End Sub

' Test des ID Mappings
Private Sub IDMappingTest()
    Dim test As New KanalID2TRiaSID
    Const constObjID = "0815"
    Dim objId As String
    objId = constObjID
    
    Const constClassid = "Klasse"
    Dim classid As String
    classid = constClassid
    
    output ("")
    output ("Hinwandlung")
    output (objId & "  " & classid)
    Dim triasid As String
    triasid = test.GetTRiASIDfromKanalID(objId, classid)
    output ("Ergebnis : " & triasid)
    output ("")
    output ("Und wieder zurück")
    test.GetKANALIDFromTRiASID triasid, objId, classid
    output (objId & "  " & classid)
    output ("")
    If (constObjID = objId) And (constClassid = classid) Then
        output ("Korrekt")
    Else
        output ("InKorrekt")
    End If
    
    output ("")
    output ("Ein Test mit falschen IDs")
    Dim testval As String
    testval = "CLASSE_bla_02719"
    output (testval)
    test.GetKANALIDFromTRiASID testval, objId, classid
    output (objId & "  " & classid)
    
    testval = "KANAL_bla02719"
    output (testval)
    test.GetKANALIDFromTRiASID testval, objId, classid
    output (objId & "  " & classid)
    
    testval = "KANAL_bla_"
    output (testval)
    test.GetKANALIDFromTRiASID testval, objId, classid
    output (objId & "  " & classid)
    
    testval = "KANAL__bla_0815"
    output (testval)
    test.GetKANALIDFromTRiASID testval, objId, classid
    output (objId & "  " & classid)
End Sub

Private Sub cmdClear_Click()
    outtext = vbEmpty
    output ("")
End Sub

Private Sub Form_Load()
    geometrieinited = False
End Sub

Private Sub Form_Resize()
    vsElastic.Width = Me.Width
    vsElastic.Height = Me.Height
End Sub
