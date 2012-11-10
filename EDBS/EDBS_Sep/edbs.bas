Attribute VB_Name = "edbs"
Option Explicit

Dim bAnwendungsbereich As Byte
Const edbs As Byte = 0
Const ALK As Byte = 1
Const Atkis_DLM As Byte = 2
Const Atkis_DKM As Byte = 3

Dim strFileName As String
Dim strBuffer As String
Dim strSearchBuffer As String
Dim strLogBuffer As String
Dim rsEDBS As Recordset
Dim rsEDBS_Fehler As Recordset

Dim strObjFolie As String
Dim strObjObjjektart As String
Dim strObjObjektnummer As String

Dim rsFLOE As Recordset

Dim rsAuftragskennsatz As Recordset
Dim IDAuftragskennsatz As Long

Dim rsAnfangspunktDerLinie As Recordset
Dim IDAnfangspunktDerLinie As Long

Dim rsEndpunktDerLinie As Recordset
Dim IDEndpunktDerLinie As Long

Dim rsFunktionDerLinie As Recordset
Dim IDFunktionDerLinie As Long

Dim rsFachparameter As Recordset
Dim IDFachparameter As Long

Dim rsLageparameter As Recordset
Dim IDLageparameter As Long

Dim rsFunktionDesObjekts As Recordset
Dim IDFunktionDesObjekts As Long

Dim rsBesondereInformation As Recordset
Dim IDBesondereInformation As Long

Dim rsGeometrieangabe As Recordset
Dim IDGeometrieangabe As Long

Sub readEDBS()
On Error Resume Next
Dim strReadBuffer As String
Dim infile As Long
Dim inchar As String
Dim iSatzlaenge As Integer
Dim iSuchkriterienAnfang As Integer
Dim lBytes As Long
Dim strIN As String * 8
Dim strZugehörigkeitsschlüssel As String * 2


'    Set rsEDBS = CurrentDb.OpenRecordset("EDBS", dbOpenDynaset)
'    Set rsEDBS_Fehler = CurrentDb.OpenRecordset("EDBS_Fehler", dbOpenDynaset)
'    Set rsFLOE = CurrentDb.OpenRecordset("FLOE", dbOpenDynaset)
'    Set rsAuftragskennsatz = CurrentDb.OpenRecordset("Auftragskennsatz", dbOpenDynaset)
'    Set rsAnfangspunktDerLinie = CurrentDb.OpenRecordset("AnfangspunktDerLinie", dbOpenDynaset)
'    Set rsEndpunktDerLinie = CurrentDb.OpenRecordset("EndpunktDerLinie", dbOpenDynaset)
'    Set rsFunktionDerLinie = CurrentDb.OpenRecordset("FunktionDerLinie", dbOpenDynaset)
'    Set rsFachparameter = CurrentDb.OpenRecordset("Fachparameter", dbOpenDynaset)
'    Set rsLageparameter = CurrentDb.OpenRecordset("Lageparameter", dbOpenDynaset)
'    Set rsFunktionDesObjekts = CurrentDb.OpenRecordset("FunktionDesObjekts", dbOpenDynaset)
'    Set rsBesondereInformation = CurrentDb.OpenRecordset("BesondereInformation", dbOpenDynaset)
'    Set rsGeometrieangabe = CurrentDb.OpenRecordset("Geometrieangabe", dbOpenDynaset)
    
'    Me.ProgressBar.Min = 0
'    Me.ProgressBar.Max = FileLen(strFileName)
    lBytes = 0
    strBuffer = ""
    infile = FreeFile
    Open strFileName For Input As infile
    
    Do Until EOF(infile)
        Line Input #infile, strReadBuffer
        lBytes = lBytes + Len(strReadBuffer)
'        Me.ProgressBar.Value = lBytes
        If Mid(strReadBuffer, 1, 4) <> "EDBS" Then
            MsgBox "Syntaxfehler, Zeile beginnt nicht mit EDBS!"
        Else
'           rsEDBS.AddNew
'           rsEDBS!SA = Mid(strReadBuffer, 1, 4)
'           rsEDBS!SL = Mid(strReadBuffer, 5, 8)
            iSatzlaenge = Val(Mid(strReadBuffer, 5, 4))
            If iSatzlaenge <> Len(strReadBuffer) - 12 Then
                MsgBox "Fehlerhafte Satzlänge" & Str(iSatzlaenge) & " bei" & Str(Len(strReadBuffer) - 12) & " Byte"
            End If
'           rsEDBS!Satzlaenge = iSatzlaenge
            iSuchkriterienAnfang = Val(Mid(strReadBuffer, 9, 4))
'           rsEDBS!SuchkriterienAnfang = iSuchkriterienAnfang
            If iSuchkriterienAnfang <> 0 Then
'                rsEDBS!Suchkriterien = Mid(strReadBuffer, iSuchkriterienAnfang)
                strSearchBuffer = Mid(strReadBuffer, 12 + iSuchkriterienAnfang)
                strReadBuffer = Left(strReadBuffer, 12 + iSuchkriterienAnfang - 1)
            End If
'            rsEDBS!OP = Mid(strReadBuffer, 13, 4)
'            rsEDBS!QU = Mid(strReadBuffer, 17, 12)
'            rsEDBS!Satznummer = Mid(strReadBuffer, 17, 6)
            strZugehörigkeitsschlüssel = Mid(strReadBuffer, 23, 2)
'            rsEDBS!Zugehörigkeitsschlüssel = Mid(strReadBuffer, 23, 2)
'            rsEDBS!Quittungsschlüssel = Mid(strReadBuffer, 25, 4)
            strIN = Mid(strReadBuffer, 29, 8)
'            rsEDBS!IN = Mid(strReadBuffer, 29, 8)
'            rsEDBS!Namenstyp = Mid(strReadBuffer, 29, 1)
'            rsEDBS!Hauptdatei = Mid(strReadBuffer, 30, 1)
'            rsEDBS!Unterdatei = Mid(strReadBuffer, 31, 1)
            
            strReadBuffer = Mid(strReadBuffer, 37)
            strBuffer = strBuffer & strReadBuffer
            DoEvents
            If strZugehörigkeitsschlüssel <> "A " And strZugehörigkeitsschlüssel <> "F " Then
                strLogBuffer = strBuffer
'                rsEDBS!Daten = strBuffer
                Select Case strIN
                Case "ULQA0000"
                    readULQA0000
                Case "ULOBNN  "
                    bAnwendungsbereich = edbs
                    readULO
                Case "ULO8ALK "
                    bAnwendungsbereich = ALK
                    readULO
                Case "DLOB2005"
                    readDLOB2005
                End Select
                strBuffer = ""
            End If
'            rsEDBS.Update
        End If
    Loop
    Close infile
    
    
'    rsAuftragskennsatz.Close
'    rsGeometrieangabe.Close
'    rsBesondereInformation.Close
'    rsFunktionDesObjekts.Close
'    rsLageparameter.Close
'    rsFachparameter.Close
'    rsFunktionDerLinie.Close
'    rsEndpunktDerLinie.Close
'    rsAnfangspunktDerLinie.Close
'    rsEDBS_Fehler.Close
'    rsEDBS.Close
    
End Sub

Function UnFormatKoordinate(Koordinate As String) As String
    If Left(Koordinate, 2) = "TT" Then
        UnFormatKoordinate = "TT          " & Format(Val(Mid(Koordinate, 3)), "0000000000")
    ElseIf Left(Koordinate, 1) = "+" Then
        UnFormatKoordinate = Right(Koordinate, 10) & Left(Koordinate, 10)
    Else
        UnFormatKoordinate = Mid(Koordinate, 1, 2) & Mid(Koordinate, 5, 2) & Mid(Koordinate, 9, 6) & Mid(Koordinate, 3, 2) & Mid(Koordinate, 7, 2) & Mid(Koordinate, 15, 6)
    End If
End Function

Sub readDLOB2005()
    rsFLOE.AddNew
    rsFLOE!DLOB0001 = Mid(strSearchBuffer, 13, 8)
    rsFLOE!DLOB0002 = Mid(strSearchBuffer, 33, 12)
    rsFLOE!DLOB0003 = Mid(strSearchBuffer, 57, 1)
    rsFLOE!DLOB2003 = Mid(strSearchBuffer, 70, 2)
    rsFLOE!DLOB2005 = Mid(strSearchBuffer, 84, 7)
    rsFLOE.Update
End Sub

Function GetWHF() As Integer
    If Len(strBuffer) < 4 Then
        LogError "GetWHF Len(strBuffer) < 4"
        GetWHF = -1
    Else
        GetWHF = Val(Left(strBuffer, 4))
        If Val(Left(strBuffer, 4)) <> 0 Then
            If Len(strBuffer) <= 4 Then
                LogError "GetWHF WHF <> 0 And Len(strBuffer) <= 4"
                GetWHF = -1
            End If
        End If
        strBuffer = Mid(strBuffer, 5)
    End If
End Function

Sub readULQA0000()
On Error GoTo Err_readULQA0000
 Dim iWHF1 As Integer
    iWHF1 = GetWHF()
    If iWHF1 = 0 Then
        MsgBox "Auftragskennsatz mit Wiederholungsfaktor = 0"
        rsAuftragskennsatz.AddNew
        IDAuftragskennsatz = rsAuftragskennsatz!IDAuftragskennsatz
        rsAuftragskennsatz.Update
    ElseIf iWHF1 = 1 Then
        rsAuftragskennsatz.AddNew
        IDAuftragskennsatz = rsAuftragskennsatz!IDAuftragskennsatz
        rsAuftragskennsatz!Dateiname = strFileName
        rsAuftragskennsatz!AuftragskennzeichenDienststelle = Mid(strBuffer, 1, 14)
        rsAuftragskennsatz!AuftragskennzeichenAuftragsnummer = Mid(strBuffer, 15, 5)
        rsAuftragskennsatz!AuftragskennzeichenWeitereGliederung = Mid(strBuffer, 20, 1)
        rsAuftragskennsatz!Prüfzeichen = Mid(strBuffer, 21, 1)
        rsAuftragskennsatz!Auftragsart = Mid(strBuffer, 22, 1)
        rsAuftragskennsatz!AktualitätDesAuftrags = Mid(strBuffer, 23, 2)
        rsAuftragskennsatz!Integrationshinweis = Mid(strBuffer, 25, 1)
        rsAuftragskennsatz!Bezirksgrundstücksdatenbank = Mid(strBuffer, 26, 2)
        rsAuftragskennsatz!Antragshinweis = Mid(strBuffer, 28, 11)
        rsAuftragskennsatz!VerarbeitungssteuerungAuftragskennung = Mid(strBuffer, 39, 1)
        rsAuftragskennsatz!VerarbeitungssteuerungBenutzungsart = Mid(strBuffer, 40, 8)
        rsAuftragskennsatz!VerarbeitungssteuerungTextFürAusgabe = Mid(strBuffer, 48, 32)
        rsAuftragskennsatz!VerarbeitungssteuerungVerarbeitungsmodus = Mid(strBuffer, 80, 2)
        rsAuftragskennsatz!VerarbeitungssteuerungAnzahlDerAusfertigungen = Mid(strBuffer, 82, 2)
        rsAuftragskennsatz!AuftragsinhaltPunktdatenkennung = Mid(strBuffer, 84, 2)
        rsAuftragskennsatz!AuftragsinhaltDatenkennungALK = Mid(strBuffer, 86, 2)
        rsAuftragskennsatz!AuftragsinhaltMessungselementekennung = Mid(strBuffer, 88, 2)
        rsAuftragskennsatz!AuftragsinhaltDatenkennungDLM = Mid(strBuffer, 90, 2)
        rsAuftragskennsatz!AuftragsinhaltDatenkennungDKM = Mid(strBuffer, 92, 2)
        rsAuftragskennsatz!AuftragsinhaltUnbelegt = Mid(strBuffer, 94, 50)
        rsAuftragskennsatz!Meridianstreifensystem = Mid(strBuffer, 144, 1)
        rsAuftragskennsatz!Verarbeitungsstop = Mid(strBuffer, 145, 1)
        rsAuftragskennsatz!VerarbeitungsstatusAusgabe = Mid(strBuffer, 146, 1)
        rsAuftragskennsatz!VerarbeitungsstatusErgebnisDesVerarbeitungsschrittes = Mid(strBuffer, 147, 1)
        rsAuftragskennsatz!VerarbeitungsstatusArtDesVerarbeitungsschrittes = Mid(strBuffer, 148, 1)
        rsAuftragskennsatz!HöchsteEDBSSatznummerBeiEingabe = Mid(strBuffer, 149, 6)
        rsAuftragskennsatz!AnzahlWeitererEDBSSätzeBeiAusgabe = Mid(strBuffer, 155, 6)
        rsAuftragskennsatz!DatumErsteintragAuftragsbuch = Mid(strBuffer, 161, 6)
        rsAuftragskennsatz!DatumLetzteVerarbeitung = Mid(strBuffer, 167, 6)
        rsAuftragskennsatz!DatumAusgabeDesErledigtenAuftrages = Mid(strBuffer, 173, 6)
        rsAuftragskennsatz!ZuständigeStellePunktnummer = Mid(strBuffer, 179, 14)
        rsAuftragskennsatz!Plausibilitätssteuerung = Mid(strBuffer, 192, 12)
        rsAuftragskennsatz!HinweisFürGeometriebehandlung = Mid(strBuffer, 204, 1)
        rsAuftragskennsatz!FolgeverarbeitungTerminalErgebnisdaten = Mid(strBuffer, 205, 8)
        rsAuftragskennsatz!FolgeverarbeitungFolgeprogrammErgebnisdaten = Mid(strBuffer, 213, 8)
        rsAuftragskennsatz!FolgeverarbeitungTerminalnameVerarbeitungsprotokoll = Mid(strBuffer, 221, 8)
        rsAuftragskennsatz!FolgeverarbeitungFolgeprogrammVerarbeitungsprotokoll = Mid(strBuffer, 229, 8)
        rsAuftragskennsatz!Prioritätssteurung = Mid(strBuffer, 237, 1)
        rsAuftragskennsatz!Auftragssteuerung = Mid(strBuffer, 238, 10)
        rsAuftragskennsatz!Antragsnummer = Mid(strBuffer, 248, 10)
        rsAuftragskennsatz.Update
    Else
        MsgBox "Auftragskennsatz mit Wiederholungsfaktor > 1"
    End If
Exit Sub

Err_readULQA0000:
    LogError Err.Description
    Resume Next
End Sub

Sub readULO()
 Dim iWHF1 As Integer
    iWHF1 = GetWHF()
    If iWHF1 < 0 Then
        Exit Sub
    End If
    Do While iWHF1 > 0
        iWHF1 = iWHF1 - 1
        If GetAnfangspunktDerLinie() = False Then
            Exit Do
        End If
    Loop
End Sub

Function GetAnfangspunktDerLinie()
On Error GoTo Err_GetAnfangspunktDerLinie
 Dim strRH As String
 Dim iWHF1 As Integer
 Dim iWHF2 As Integer
    iWHF1 = GetWHF()
    If iWHF1 < 0 Then
        GetAnfangspunktDerLinie = False
        Exit Function
    End If
    Do While iWHF1 > 0
        DoEvents
        iWHF1 = iWHF1 - 1
        rsAnfangspunktDerLinie.AddNew
        rsAnfangspunktDerLinie!IDAuftragskennsatz = IDAuftragskennsatz
        IDAnfangspunktDerLinie = rsAnfangspunktDerLinie!IDAnfangspunktDerLinie
        strRH = UnFormatKoordinate(Left(strBuffer, 20))
        rsAnfangspunktDerLinie!AnfangspunktDerLinieH = Left(strRH, 10)
        rsAnfangspunktDerLinie!AnfangspunktDerLinieR = Right(strRH, 10)
        rsAnfangspunktDerLinie!Prüfzeichen = Mid(strBuffer, 21, 1)
        strBuffer = Mid(strBuffer, 22)
        iWHF2 = GetWHF()
        If iWHF2 < 0 Then
            GetAnfangspunktDerLinie = False
            Exit Function
        End If
        rsAnfangspunktDerLinie!WHFEndpunktDerLinie = iWHF2
        Do While iWHF2 > 0
            iWHF2 = iWHF2 - 1
            If GetEndpunktDerLinie() = False Then
                 GetAnfangspunktDerLinie = False
                Exit Function
            End If
        Loop
        iWHF2 = GetWHF()
        If iWHF2 < 0 Then
            GetAnfangspunktDerLinie = False
            Exit Function
        End If
        rsAnfangspunktDerLinie!WHFFunktionDesObjekts = iWHF2
        Do While iWHF2 > 0
            iWHF2 = iWHF2 - 1
            If GetFunktionDesObjekts() = False Then
                GetAnfangspunktDerLinie = False
                Exit Function
            End If
        Loop
        rsAnfangspunktDerLinie.Update
    Loop
    GetAnfangspunktDerLinie = True
Exit Function

Err_GetAnfangspunktDerLinie:
    LogError Err.Description
    GetAnfangspunktDerLinie = False
    Exit Function
End Function

Function GetEndpunktDerLinie()
On Error GoTo Err_GetEndpunktDerLinie
 Dim strRH As String
 Dim iWHF1 As Integer
 Dim iWHF2 As Integer
    iWHF1 = GetWHF()
    If iWHF1 < 0 Then
        GetEndpunktDerLinie = False
        Exit Function
    End If
    Do While iWHF1 > 0
        DoEvents
        iWHF1 = iWHF1 - 1
        rsEndpunktDerLinie.AddNew
        rsEndpunktDerLinie!IDAnfangspunktDerLinie = IDAnfangspunktDerLinie
        IDEndpunktDerLinie = rsEndpunktDerLinie!IDEndpunktDerLinie
        strRH = UnFormatKoordinate(Left(strBuffer, 20))
        rsEndpunktDerLinie!EndpunktDerLinieR = Left(strRH, 10)
        rsEndpunktDerLinie!EndpunktDerLinieH = Right(strRH, 10)
        rsEndpunktDerLinie!ArtDerLiniengeometrie = Mid(strBuffer, 21, 2)
        rsEndpunktDerLinie.Update
        strBuffer = Mid(strBuffer, 23)
        If bAnwendungsbereich <> ALK Then
            iWHF2 = GetWHF()
            If iWHF2 < 0 Then
                GetEndpunktDerLinie = False
                Exit Function
            End If
        Else
            iWHF2 = 1
            'Funktion der Linie ist nicht weiter untergliedert, es gibt also keinen WHF für Struktur
        End If
        Do While iWHF2 > 0
            iWHF2 = iWHF2 - 1
            If GetFunktionDerLinie() = False Then
                GetEndpunktDerLinie = False
                Exit Function
            End If
        Loop
        iWHF2 = GetWHF()
        If iWHF2 < 0 Then
            GetEndpunktDerLinie = False
            Exit Function
        End If
        Do While iWHF2 > 0
            iWHF2 = iWHF2 - 1
            If GetLageparameter() = False Then
                GetEndpunktDerLinie = False
                Exit Function
            End If
        Loop
    Loop
    GetEndpunktDerLinie = True
Exit Function

Err_GetEndpunktDerLinie:
    LogError Err.Description
    GetEndpunktDerLinie = False
    Exit Function
End Function

Function GetFunktionDerLinie()
On Error GoTo Err_GetFunktionDerLinie
 Dim iWHF1 As Integer
 Dim iWHF2 As Integer
 Dim iPos As Integer
    iWHF1 = GetWHF()
    If iWHF1 < 0 Then
        GetFunktionDerLinie = False
        Exit Function
    End If
    Do While iWHF1 > 0
        DoEvents
        iWHF1 = iWHF1 - 1
        rsFunktionDerLinie.AddNew
        rsFunktionDerLinie!IDEndpunktDerLinie = IDEndpunktDerLinie
        IDFunktionDerLinie = rsFunktionDerLinie!IDFunktionDerLinie
        rsFunktionDerLinie!Folie = Mid(strBuffer, 1, 3)
        rsFunktionDerLinie!Linienart = Mid(strBuffer, 4, 4)
        rsFunktionDerLinie!Objektnummer1R = Mid(strBuffer, 8, 7)
        rsFunktionDerLinie!Objektnummer2L = Mid(strBuffer, 15, 7)
        iPos = 22
        If bAnwendungsbereich <> ALK Then
            rsFunktionDerLinie!Objektteilnummer1R = Mid(strBuffer, iPos, 3)
            iPos = iPos + 3
            rsFunktionDerLinie!Objektteilnummer2L = Mid(strBuffer, 25, 3)
            iPos = iPos + 3
        End If
        rsFunktionDerLinie!Linienteilung1R = Mid(strBuffer, iPos, 1)
        iPos = iPos + 1
        rsFunktionDerLinie!linienteilung2L = Mid(strBuffer, iPos, 1)
        iPos = iPos + 1
        rsFunktionDerLinie.Update
        
        strBuffer = Mid(strBuffer, iPos)
        
        If bAnwendungsbereich <> ALK Then
            iWHF2 = GetWHF()
            If iWHF2 < 0 Then
                GetFunktionDerLinie = False
                Exit Function
            End If
            Do While iWHF2 > 0
                iWHF2 = iWHF2 - 1
                If GetFachparameter() = False Then
                    GetFunktionDerLinie = False
                    Exit Function
                End If
            Loop
        End If
    Loop
    GetFunktionDerLinie = True
Exit Function

Err_GetFunktionDerLinie:
    LogError Err.Description
    GetFunktionDerLinie = False
    Exit Function
End Function

Function GetLageparameter()
On Error GoTo Err_GetLageparameter
    rsLageparameter.AddNew
    rsLageparameter!IDEndpunktDerLinie = IDEndpunktDerLinie
    IDLageparameter = rsLageparameter!IDLageparameter
    rsLageparameter!Lageparameter = Left(strBuffer, 20)
    rsLageparameter.Update
    
    strBuffer = Mid(strBuffer, 21)
    
    GetLageparameter = True
Exit Function

Err_GetLageparameter:
    LogError Err.Description
    GetLageparameter = False
    Exit Function
End Function

Function GetFachparameter()
On Error GoTo Err_GetFachparameter
    rsFachparameter.AddNew
    rsFachparameter!IDFunktionDerLinie = IDFunktionDerLinie
    IDFachparameter = rsFachparameter!IDFachparameter
    rsFachparameter!ArtDesFachparameters = Mid(strBuffer, 1, 1)
    rsFachparameter!KennungDesFachparameters = Mid(strBuffer, 2, 1)
    rsFachparameter!WertDesFachparameters = Mid(strBuffer, 3, 7)
    rsFachparameter.Update
    
    strBuffer = Mid(strBuffer, 9)
    
    GetFachparameter = True
Exit Function

Err_GetFachparameter:
    LogError Err.Description
    GetFachparameter = False
    Exit Function
End Function

Function GetFunktionDesObjekts()
On Error GoTo Err_GetFunktionDesObjekts
 Dim iWHF1 As Integer
 Dim iWHF2 As Integer
 Dim iPos As Integer
    iWHF1 = GetWHF()
    If iWHF1 < 0 Then
        GetFunktionDesObjekts = False
        Exit Function
    End If
    Do While iWHF1 > 0
        DoEvents
        iWHF1 = iWHF1 - 1
        rsFunktionDesObjekts.AddNew
        rsFunktionDesObjekts!IDAuftragskennsatz = IDAuftragskennsatz
        rsFunktionDesObjekts!IDAnfangspunktDerLinie = IDAnfangspunktDerLinie
        IDFunktionDesObjekts = rsFunktionDesObjekts!IDFunktionDesObjekts
        rsFunktionDesObjekts!Folie = Mid(strBuffer, 1, 3)
        rsFunktionDesObjekts!Objektart = Mid(strBuffer, 4, 4)
        rsFunktionDesObjekts!AktualitätDesObjekts = Mid(strBuffer, 8, 2)
        rsFunktionDesObjekts!Objekttyp = Mid(strBuffer, 10, 1)
        rsFunktionDesObjekts!Objektnummer = Mid(strBuffer, 11, 7)
        iPos = 18
        If bAnwendungsbereich <> ALK Then
            rsFunktionDesObjekts!Modelltyp = Mid(strBuffer, iPos, 2)
            iPos = iPos + 2
        End If
        rsFunktionDesObjekts!Entstehungsdatum = Mid(strBuffer, iPos, 6)
        iPos = iPos + 6
        If bAnwendungsbereich <> ALK Then
            rsFunktionDesObjekts!Veränderungskennung = Mid(strBuffer, 26, 1)
            iPos = iPos + 1
        End If
        strBuffer = Mid(strBuffer, iPos)
        
        iWHF2 = GetWHF()
        If iWHF2 < 0 Then
            GetFunktionDesObjekts = False
            Exit Function
        End If
        rsFunktionDesObjekts!WHFBesondereInformation = iWHF2
        rsFunktionDesObjekts.Update
        Do While iWHF2 > 0
            iWHF2 = iWHF2 - 1
            If GetBesondereInformation() = False Then
                GetFunktionDesObjekts = False
                Exit Function
            End If
        Loop
    Loop
    GetFunktionDesObjekts = True
Exit Function

Err_GetFunktionDesObjekts:
    LogError Err.Description
    GetFunktionDesObjekts = False
    Exit Function
End Function

Function GetBesondereInformation()
On Error GoTo Err_GetBesondereInformation
 Dim iWHF1 As Integer
 Dim iWHF2 As Integer
 Dim iPos As Integer
    iWHF1 = GetWHF()
    If iWHF1 < 0 Then
        GetBesondereInformation = False
        Exit Function
    End If
    Do While iWHF1 > 0
        DoEvents
        iWHF1 = iWHF1 - 1
        rsBesondereInformation.AddNew
        rsBesondereInformation!IDAnfangspunktDerLinie = IDAnfangspunktDerLinie
        rsBesondereInformation!IDFunktionDesObjekts = IDFunktionDesObjekts
        IDBesondereInformation = rsBesondereInformation!IDBesondereInformation
        rsBesondereInformation!ArtDerInformation = Mid(strBuffer, 1, 2)
        rsBesondereInformation!Kartentyp = Mid(strBuffer, 3, 2)
        rsBesondereInformation!Darstellungsart = Mid(strBuffer, 5, 6)
        rsBesondereInformation!Textdaten = Mid(strBuffer, 11, 33)
        rsBesondereInformation!ArtDerGeometrieangabe = Mid(strBuffer, 44, 2)
        iPos = 46
        If bAnwendungsbereich <> ALK Then
            rsBesondereInformation!Objektteilnummer = Mid(strBuffer, iPos, 3)
            iPos = iPos + 3
        End If
        rsBesondereInformation.Update
        strBuffer = Mid(strBuffer, iPos)
        iWHF2 = GetWHF()
        If iWHF2 < 0 Then
            GetBesondereInformation = False
            Exit Function
        End If
        Do While iWHF2 > 0
            iWHF2 = iWHF2 - 1
            If GetGeometrieangaben() = False Then
                GetBesondereInformation = False
                Exit Function
            End If
        Loop
    Loop
    GetBesondereInformation = True
Exit Function

Err_GetBesondereInformation:
    LogError Err.Description
    GetBesondereInformation = False
    Exit Function
End Function

Function GetGeometrieangaben()
On Error GoTo Err_GetGeometrieangaben
 Dim strRH As String
    rsGeometrieangabe.AddNew
    rsGeometrieangabe!IDBesondereInformation = IDBesondereInformation
    IDGeometrieangabe = rsGeometrieangabe!IDGeometrieangabe
    strRH = UnFormatKoordinate(Left(strBuffer, 20))
    rsGeometrieangabe!GeometrieangabeR = Left(strRH, 10)
    rsGeometrieangabe!GeometrieangabeH = Right(strRH, 10)
    rsGeometrieangabe.Update
    
    strBuffer = Mid(strBuffer, 21)
    
    GetGeometrieangaben = True
Exit Function

Err_GetGeometrieangaben:
    LogError Err.Description
    GetGeometrieangaben = False
    Exit Function
End Function

Sub LogError(strErrorDescription As String)
    rsEDBS_Fehler.AddNew
    rsEDBS_Fehler!strErrorDescription = strErrorDescription
    rsEDBS_Fehler!strFileName = strFileName
    rsEDBS_Fehler!IDAuftragskennsatz = IDAuftragskennsatz
    rsEDBS_Fehler!IDAnfangspunktDerLinie = IDAnfangspunktDerLinie
    rsEDBS_Fehler!IDEndpunktDerLinie = IDEndpunktDerLinie
    rsEDBS_Fehler!IDFunktionDerLinie = IDFunktionDerLinie
    rsEDBS_Fehler!IDFachparameter = IDFachparameter
    rsEDBS_Fehler!IDLageparameter = IDLageparameter
    rsEDBS_Fehler!IDFunktionDesObjekts = IDFunktionDesObjekts
    rsEDBS_Fehler!IDBesondereInformation = IDBesondereInformation
    rsEDBS_Fehler!IDGeometrieangabe = IDGeometrieangabe
    rsEDBS_Fehler!strBuffer = strLogBuffer
    rsEDBS_Fehler.Update
End Sub

