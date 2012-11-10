VERSION 5.00
Begin VB.Form frmTestProg 
   Caption         =   "Testprogramm (Kanalkopplung)"
   ClientHeight    =   6675
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8175
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   6675
   ScaleWidth      =   8175
   Begin VB.VScrollBar VScroll1 
      Height          =   4215
      Left            =   7920
      Max             =   1000
      Min             =   1
      TabIndex        =   4
      Top             =   720
      Value           =   10
      Width           =   255
   End
   Begin VB.CommandButton cmdClear 
      Appearance      =   0  'Flat
      Height          =   375
      Left            =   0
      Picture         =   "Form1.frx":08CA
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
   Begin VB.Label lblCount 
      Alignment       =   1  'Right Justify
      Caption         =   "1"
      Enabled         =   0   'False
      Height          =   375
      Left            =   6960
      TabIndex        =   5
      Top             =   720
      Width           =   855
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

Dim WithEvents kopplung As Koppelmodul
Attribute kopplung.VB_VarHelpID = -1

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
Const cstSymbol = "Symbol"

Private Sub btStart_Click()
    Starttest
    creationtest
    
    testeVisualisation
End Sub

Private Sub testeVisualisation()
    output ("Teste Visualisierung")
    Dim testinterface As Darstellung
'    Set testinterface = kopplung
    
    Dim maxindex As Long
    maxindex = 0
    
    Dim klasses() As String
    ReDim klasses(maxindex)
    Dim objids() As String
    ReDim objids(maxindex)
    
    Dim i As Long
    For i = 0 To maxindex
        klasses(i) = cstKlasse
        objids(i) = cstLinie & (i + 1)
    Next
    
    If (0 <> kopplung.Auswaehlen(objids, klasses)) Then
        output ("Fehler in Routine auswählen")
    End If
    
'    If (0 <> kopplung.Zoomen(objids, klasses)) Then
'        output ("Fehler in Routine zoomen")
'    End If
    
'    MsgBox ("kann's weiter gehen")
End Sub

Private Function min(val1 As Double, val2 As Double) As Double
    min = val1
    If (val2 < val1) Then
        min = val2
    End If
End Function

Private Sub SetFontByNumber(number As Long)
    Dim strFont As String
    Select Case number Mod 3
    Case 0: strFont = "Wingdings"
    Case 1: strFont = "Webdings"
    Case 2: strFont = "Courier"
    End Select
    
    kopplung.SetzeSymbolFont (strFont)
End Sub

Private Sub GenerateBaseGeometrie()
    If geometrieinited = False Then
        xmitte = (x1 + x2) / 2
        ymitte = (y1 + y2) / 2
        radius = min(Abs(x2 - x1), Abs(y2 - y1)) / 2
    End If
End Sub

Private Sub GenerateLine(ByVal number As Long, ByRef x() As Double, ByRef y() As Double)
    GenerateBaseGeometrie   ' Basisgeometrien initialisieren
    
    ' Größe setzen
    ReDim x(1)
    ReDim y(1)
    
'    number = number Mod 30
    
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
    drehwinkel = (number * 10) Mod 360   ' in 10° Schritten drehen
    
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
    Dim z() As Double
    Dim sx As Double    ' für einzelne Punkte
    Dim sy As Double
    Dim sz As Double
    Dim drehwinkel As Double
    Dim textalignment As KANAL_TextBezugspunkt
    Dim vistext As String
    Dim durchmesser As Double
    
 
    Dim ObjID As String
    Dim i As Long
    
    kopplung.StartGeometryTransaction 10
    Dim maxindex As Long
    maxindex = lblCount.Caption
    For i = 1 To maxindex
        ' eine Geometrie generieren
        GenerateLine i, x, y
        
        ' einen ObjID generieren
        ObjID = cstLinie & i
        
        ' jetzt das Object erzeugen
        If 92 = i Then
            output ("Enter critical section ;-)")
        End If
        
        output ("Erzeuge das LinienObjekt " & ObjID & " der Klasse " & cstKlasse)
        If (kopplung.ErzeugeLinie(x, y, z, ObjID, cstKlasse) <> 0) Then
            output ("Test failed")
        End If
        
        ' Jetzt noch ein paar Texte
        GenerateText i, sx, sy, drehwinkel, vistext, textalignment
        ObjID = cstText & i
        ' jetzt das Object erzeugen
        output ("Erzeuge das TextObjekt " & ObjID & " der Klasse " & cstKlasse)
        If (kopplung.ErzeugeText(sx, sy, sz, textalignment, drehwinkel, vistext, ObjID, cstKlasse) <> 0) Then
            output ("Test failed")
        End If
        
        If (kopplung.Loesche(ObjID, cstKlasse) <> 0) Then
            output ("Delete failed")
        End If
        

        ObjID = cstSymbol & i
        ' jetzt das Object erzeugen
        output ("Erzeuge das Symbol" & ObjID & " der Klasse " & cstKlasse)
        SetFontByNumber i
        If (kopplung.ErzeugeSymbol(sx, sy, sz, "A", 20, drehwinkel, ObjID, cstKlasse) <> 0) Then
            output ("Test failed")
        End If

        ' Jetzt noch ein Kreischen
        GenerateKreis i, sx, sy, durchmesser
        ObjID = cstKreis & i
        ' jetzt das Object erzeugen
        output ("Erzeuge das KreisObjekt " & ObjID & " der Klasse " & cstKlasse)
        If (kopplung.ErzeugeKreis(sx, sy, sz, durchmesser, ObjID, cstKlasse) <> 0) Then
            output ("Test failed")
        End If
        
        VScroll1.Value = maxindex + 1 - i
    Next
    
    kopplung.EndGeometryTransaction
End Sub

Private Sub output(str As String)
     outtext = outtext & vbCrLf & str
     If (chkAusgabeCheck.Value = 1) Then
        txtAusgabe.text = outtext
     End If
End Sub

Private Sub Starttest()
    ' wenn schn was da ist dann das benutzen
    If Not kopplung Is Nothing Then
        Exit Sub
    End If
    
    output ("")
    output ("ErzeugeKoppelmodul")
    Set kopplung = New Koppelmodul
    
    output ("")
    output ("Starte TRiAS ")
    If kopplung.StarteKopplung <> 0 Then
        output ("StarteKoplung failed")
        Exit Sub
    End If
    
    kopplung.ZeigeTRiAS True
End Sub

Private Sub CloseTest()
    ' ist doch gar nicht auf
    If kopplung Is Nothing Then
        Exit Sub
    End If
    
    output ("Beende TRiAS ")
    If kopplung.BeendeKopplung <> 0 Then
        output ("BeendeKopplung failed")
        Exit Sub
    End If
    
    Set kopplung = Nothing
End Sub

' Test des ID Mappings
Private Sub IDMappingTest()
    Dim test As New KanalID2TRiaSID
    Const constObjID = "0815"
    Dim ObjID As String
    ObjID = constObjID
    
    Const constClassid = "Klasse"
    Dim classid As String
    classid = constClassid
    
    output ("")
    output ("Hinwandlung")
    output (ObjID & "  " & classid)
    Dim triasid As String
    triasid = test.GetTRiASIDfromKanalID(ObjID, classid)
    output ("Ergebnis : " & triasid)
    output ("")
    output ("Und wieder zurück")
    test.GetKANALIDFromTRiASID triasid, ObjID, classid
    output (ObjID & "  " & classid)
    output ("")
    If (constObjID = ObjID) And (constClassid = classid) Then
        output ("Korrekt")
    Else
        output ("InKorrekt")
    End If
    
    output ("")
    output ("Ein Test mit falschen IDs")
    Dim testval As String
    testval = "CLASSE_bla_02719"
    output (testval)
    test.GetKANALIDFromTRiASID testval, ObjID, classid
    output (ObjID & "  " & classid)
    
    testval = "KANAL_bla02719"
    output (testval)
    test.GetKANALIDFromTRiASID testval, ObjID, classid
    output (ObjID & "  " & classid)
    
    testval = "KANAL_bla_"
    output (testval)
    test.GetKANALIDFromTRiASID testval, ObjID, classid
    output (ObjID & "  " & classid)
    
    testval = "KANAL__bla_0815"
    output (testval)
    test.GetKANALIDFromTRiASID testval, ObjID, classid
    output (ObjID & "  " & classid)
End Sub

Private Sub cmdClear_Click()
    outtext = vbEmpty
    output ("")
End Sub

Private Sub Form_Load()
    geometrieinited = False
    VScroll1.min = 1
    VScroll1.Max = 1000
End Sub

Private Sub Form_Unload(Cancel As Integer)
    CloseTest
End Sub

Private Sub kopplung_OnToDelete(ObjID As String, klasse As String, retval As Boolean)
    retval = False
End Sub

Private Sub kopplung_OnToShow(ObjID As String, klasse As String, retval As Boolean)
    
End Sub

Private Sub txtAusgabe_Change()
'    txtAusgabe
End Sub

Private Sub VScroll1_Change()
    lblCount.Caption = VScroll1.Value
End Sub
