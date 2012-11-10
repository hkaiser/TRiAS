VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "cNode"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

Public Parent As cNode
Public Class As String
Public Caption As String
Public FileDate As Date
Public FileName As String
Public FileAttributes As Long

Public TempFileName As String
Public TempFileLen As Long

Public SubNodes As ccNodes
Private Const STATE_SIGNED As Long = 1
Private Const STATE_ENCRYPTED As Long = 2
Public State   As Long

'local variable(s) to hold property value(s)
Private mvarUniqueKey As String 'local copy

Public Property Let signed(ByVal vData As Boolean)
    If vData = True Then
        State = State Or STATE_SIGNED
    Else
        State = State And Not STATE_SIGNED
    End If
End Property

Public Property Get signed() As Boolean
    If (State And STATE_SIGNED) = 0 Then
        signed = False
    Else
        signed = True
    End If
End Property

Public Property Let encrypted(ByVal vData As Boolean)
    If vData = True Then
        State = State Or STATE_ENCRYPTED
    Else
        State = State And Not STATE_ENCRYPTED
    End If
End Property

Public Property Get encrypted() As Boolean
    If (State And STATE_ENCRYPTED) = 0 Then
        encrypted = False
    Else
        encrypted = True
    End If
End Property

Public Property Let UniqueKey(ByVal vData As String)
    mvarUniqueKey = vData
End Property

Public Property Get UniqueKey() As String
    UniqueKey = mvarUniqueKey
End Property

Public Function LoadFromTSD(ByVal strFileName As String) As Long
On Error GoTo Err_LoadFromTSD
 Dim hResult As Long

    If GetFileVersion(strFileName) Then
        Me.SubNodes.Clear
        hResult = Me.LoadHeaderFromTSD(strFileName)
        If hResult = 0 Then
            hResult = Me.LoadDataFromTSD(strFileName, gHeaderLen + 1)
        Else
            LoadFromTSD = -2
        End If
    Else
        LoadFromTSD = -1
    End If
Exit Function

Err_LoadFromTSD:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "LoadFromTSD"
    Resume Next

End Function

Public Function LoadHeaderFromTSD(ByVal strFileName As String) As Long
On Error GoTo Err_LoadHeaderFromTSD
 Dim hResult As Long

    hResult = -1
    If 1 = gDokFileVersion Then
        hResult = ReadFH1n(strFileName, Me)
'    ElseIf 1 = gDokFileVersion Then
'        result = ReadFH1(strFileName)
    Else
        MsgBox "Diese Version des Programmes kann das vorliegende Dateiformat nicht lesen! " & _
                "Installieren Sie bitte eine aktuelle Version des TeleSafe!"
    End If

    LoadHeaderFromTSD = hResult
Exit Function

Err_LoadHeaderFromTSD:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "LoadHeaderFromTSD"
    Resume Next
End Function


Public Function LoadDataFromTSD(ByVal strFileName As String, startPos As Long) As Long
On Error GoTo Err_LoadDataFromTSD
 Dim hResult As Long
 Dim SubNode As cNode
 Dim nx As Integer
 Dim i As Long, Location, curr() As Byte
 Dim j As Long, n As Long, pos As Long

    hResult = 0
    If TempFileLen > 0 Then
        TempFileName = GetTempName
        If 0 = Len(TempFileName) Then
            LoadDataFromTSD = False
            Exit Function
        End If
    
        Open strFileName For Binary As #1
        Open TempFileName For Binary As #2
        Seek 1, startPos
        ReDim curr(1 To 4096)
        pos = 0
        Do While pos < TempFileLen
            n = 4096
            If (n > (Me.TempFileLen - pos)) Then n = Me.TempFileLen - pos
            If n <> 4096 Then ReDim curr(1 To n)
            Get 1, , curr
            Put 2, , curr
            pos = pos + n
        Loop
        Close #2
        Close #1
        startPos = startPos + pos
    End If
    
    For nx = 1 To SubNodes.Count
        hResult = SubNodes.Item(nx).LoadDataFromTSD(strFileName, startPos)
        If 0 <> hResult Then
            Exit For
        End If
    Next nx
    LoadDataFromTSD = hResult
Exit Function

Err_LoadDataFromTSD:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "LoadDataFromTSD"
    Resume Next
End Function


Public Function SaveToTSD(strFileName As String, tNeutral As Boolean) As Long
On Error Resume Next
    Kill strFileName
On Error GoTo Err_SaveToTSD
    Me.SaveHeaderToTSD strFileName, tNeutral
    Me.SaveDataToTSD strFileName
SaveToTSD = 0
Exit Function

Err_SaveToTSD:
    MsgBox "Fehler" & Str(Err.mumber) & ": " & Err.Description, , "SaveToTSD"
    Resume Next
End Function

Public Function SaveHeaderToTSD(strFileName As String, tNeutral As Boolean) As Long
On Error GoTo Err_SaveHeaderToTSD
 Dim hFile As Long, buff() As Byte
 Dim buffsize As Long
 Dim nx As Integer
 Dim nextpos As Long
 
    buffsize = Me.SizeTSDHeader

    ReDim buff(1 To buffsize + TSD_HEADERLEN + 1)
    buff(1) = Asc("T")
    buff(2) = Asc("S")
    buff(3) = Asc("D")
    buff(4) = 1
    If tNeutral Then
        SetInt 0, buff, 5
        SetInt 0, buff, 7
        SetInt 0, buff, 9
    Else
        SetInt App.Major, buff, 5
        SetInt App.Minor, buff, 7
        SetInt App.Revision, buff, 9
    End If
    SetInt TSD_HEADERLEN + buffsize + 1, buff, 11
    
    nextpos = TSD_HEADERLEN + 1
    
    nextpos = Me.WriteFH1ToBuffer(0, buff, nextpos)
    
    buff(nextpos) = DT_Ende
    
    hFile = FreeFile
    Open strFileName For Binary As #hFile
    Put hFile, , buff
    Close #hFile
Exit Function

Err_SaveHeaderToTSD:
    MsgBox "Fehler" & Str(Err.mumber) & ": " & Err.Description, , "SaveHeaderToTSD"
    Resume Next
End Function

Public Function SaveDataToTSD(ByVal strFileName As String) As Boolean
On Error GoTo Err_SaveDataToTSD
 Dim result As Boolean, SubNode As cNode
 Dim nx As Integer
 Dim i As Long, Location, curr() As Byte
 Dim j As Long, n As Long

    result = True
    If TempFileLen > 0 Then
        If 0 = Len(TempFileName) Then
            SaveDataToTSD = False
            Exit Function
        End If
        Open strFileName For Binary As #1
        Open TempFileName For Binary As #2
        Seek 1, LOF(1) + 1
        ReDim curr(1 To 4096)
        Do While Loc(2) < LOF(2)
            n = 4096
            If (n > (LOF(2) - Loc(2))) Then n = LOF(2) - Loc(2)
            If n <> 4096 Then ReDim curr(1 To n)
            Get 2, , curr
            Put 1, , curr
        Loop
        Close #2
        Close #1
    End If

    For nx = 1 To SubNodes.Count
        Set SubNode = SubNodes.Item(nx)
        result = SubNode.SaveDataToTSD(strFileName)
        If Not result Then Exit For
    Next nx
    SaveDataToTSD = result
Exit Function

Err_SaveDataToTSD:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "SaveDataToTSD"
    Resume Next
End Function

Public Function SaveToBuffer(baBuffer() As Byte, lStart As Long) As Long
On Error GoTo Err_SaveToBuffer
 Dim result As Boolean
 Dim hFile As Long
 Dim lFileLength As Long
 Dim nx As Integer
 Dim lNextPos As Long

    result = True
    lNextPos = lStart
    If TempFileLen > 0 Then
        hFile = FreeFile
        Open TempFileName For Binary As hFile
        lFileLength = LOF(hFile)
        Do Until lFileLength = 0
            Get hFile, , baBuffer(lNextPos)
            lNextPos = lNextPos + 1
            lFileLength = lFileLength - 1
        Loop
        Close hFile
    End If
    For nx = 1 To SubNodes.Count
        lNextPos = SubNodes.Item(nx).SaveToBuffer(baBuffer, lNextPos)
    Next nx
    SaveToBuffer = lNextPos
Exit Function

Err_SaveToBuffer:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description, , "SaveToBuffer"
    Resume Next
End Function

Public Function Size() As Long
 Dim lSize As Long
 Dim nx As Integer
 
    lSize = TempFileLen
    For nx = 1 To SubNodes.Count
        lSize = lSize + SubNodes.Item(nx).Size
    Next nx
    Size = lSize
End Function

Public Function SizeTSDHeader()
 Dim lSize As Long
 Dim nx As Integer
 
    lSize = 17 + Len(Class) + 2 + Len(FileName) + 2 + Len(Caption) + 2
    For nx = 1 To SubNodes.Count
        lSize = lSize + SubNodes.Item(nx).SizeTSDHeader
    Next nx
    SizeTSDHeader = lSize
End Function

Public Function SizeTSDData()
 Dim lSize As Long
 Dim nx As Integer
 
    lSize = TempFileLen
    For nx = 1 To SubNodes.Count
        lSize = lSize + SubNodes.Item(nx).SizeTSDData
    Next nx
    SizeTSDData = lSize
End Function


Public Function WriteFH1ToBuffer(ByVal bLevel As Byte, baBuffer() As Byte, ByVal pos As Long)
On Error GoTo Err_WriteTSDHeader
 Dim nx As Integer
 Dim nextpos As Long
    baBuffer(pos) = bLevel
    SetLong TempFileLen, baBuffer, pos + 1
    SetLong FileAttributes, baBuffer, pos + 5
    SetDate FileDate, baBuffer, pos + 9
    SetLong State, baBuffer, pos + 13
    nextpos = pos + 17
    nextpos = nextpos + SetString(Class, baBuffer, nextpos)
    nextpos = nextpos + SetString(FileName, baBuffer, nextpos)
    nextpos = nextpos + SetString(Caption, baBuffer, nextpos)
    For nx = 1 To SubNodes.Count
        nextpos = SubNodes.Item(nx).WriteFH1ToBuffer(bLevel + 1, baBuffer, nextpos)
    Next nx
    WriteFH1ToBuffer = nextpos
Exit Function

Err_WriteTSDHeader:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next

End Function

Public Function LoadFromBuffer(vBuffer As Variant, lStart As Long, lLen As Long) As Boolean
 Dim lx As Long
 Dim hFile As Long
On Error Resume Next
    If TypeName(vBuffer) <> "Byte()" Then
        MsgBox "Ungültiger Varianttyp " & TypeName(vBuffer) & " in Funktion LoadFromBuffer!"
        LoadFromBuffer = False
        Exit Function
    End If
    If Len(TempFileName) > 0 Then
        Kill TempFileName
    End If
On Error GoTo Err_LoadFromBuffer
    FileDate = Now
    FileAttributes = 0
    TempFileLen = lLen
    TempFileName = GetTempName
    hFile = FreeFile
    Open TempFileName For Binary Access Write As hFile
    For lx = lStart To lStart + lLen - 1
        Put #hFile, , vBuffer(lx)
    Next
    Close #hFile
    LoadFromBuffer = True
Exit Function

Err_LoadFromBuffer:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next

End Function

Public Function SetFromFile(ByVal strPfad As String) As Boolean
Dim result As Boolean
Dim Drive As String, Subdirs As String
Dim strFileName As String, Suffix As String

On Error GoTo Err_SetFromFile

    result = True
    
    SplitPath strPfad, Drive, Subdirs, strFileName, Suffix

    Me.FileDate = FileDateTime(strPfad)
    Me.FileAttributes = GetAttr(strPfad)
    Me.FileName = strFileName & Suffix
    Me.TempFileName = strPfad
    Me.TempFileLen = FileLen(strPfad)
    
    SetFromFile = result
Exit Function

Err_SetFromFile:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Function

Public Function LoadFromFile(ByVal strPfad As String) As Boolean
Dim result As Boolean
Dim Drive As String, Subdirs As String
Dim strFileName As String, Suffix As String

On Error GoTo Err_LoadFromFile

    result = True
    FileDate = FileDateTime(strPfad)
    FileAttributes = GetAttr(strPfad)
    TempFileName = GetTempName
    TempFileLen = FileLen(strPfad)
    FileCopy strPfad, TempFileName
    
    SplitPath strPfad, Drive, Subdirs, strFileName, Suffix

    Me.FileName = strFileName & Suffix
        
    LoadFromFile = result
Exit Function

Err_LoadFromFile:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Function

Public Function LoadFromPath(ByVal strPath As String) As Boolean
Dim oElement As cNode, fname As String, dname As String
Dim strSearch As String, strTemp As String

On Error GoTo Err_LoadFromPath
    
    strSearch = strPath & "\*.*"
    dname = Dir(strSearch, vbNormal + vbDirectory)
    While Left(dname, 1) = "."
        dname = Dir
    Wend
    fname = strPath & "\" & dname
    While 0 < Len(dname)
        If vbDirectory = (GetAttr(fname) And vbDirectory) Then
            Set oElement = SubNodes.Add("Verzeichnis")
            If Not oElement Is Nothing Then
                oElement.LoadFromPath fname
                oElement.Caption = dname
                Set oElement = Nothing
            End If
            strTemp = Dir(strSearch, vbNormal + vbDirectory)
            While strTemp <> dname
                strTemp = Dir
            Wend
        Else
            Set oElement = SubNodes.Add("Anlage")
            If Not oElement Is Nothing Then
                oElement.LoadFromFile fname
                oElement.Caption = dname
                Set oElement = Nothing
            End If
        End If
        dname = Dir
        fname = strPath & "\" & dname
    Wend
Exit Function

Err_LoadFromPath:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next

End Function
Public Sub LoadPrinterBitmaps(ByVal pfad As String)
On Error GoTo Err_LoadPrinterBitmaps
 Dim SubNode As cNode, strPfad As String, nCnt As Integer
 Dim strFile As String

    strPfad = pfad
    nCnt = 1
    While DateiExist(strPfad & Format(nCnt, "000"))
        Set SubNode = SubNodes.Add("Seite")
        If Not SubNode Is Nothing Then
            SubNode.Caption = "Seite" & Str(nCnt)
            SubNode.LoadFromFile strPfad & Format(nCnt, "000")
            Kill strPfad & Format(nCnt, "000")
        End If
        nCnt = nCnt + 1
    Wend
Exit Sub

Err_LoadPrinterBitmaps:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next

End Sub

Public Sub LoadPrinterData(ByVal strFileName As String)
On Error GoTo Err_LoadPrinterData
 Dim hResult As Long
 Dim SubNode As cNode, strPfad As String, nCnt As Integer
 Dim strTempFileName As String
 Dim svrTSPrint As New TSPRINTLib.TSPrinter

    hResult = svrTSPrint.LoadPrinterOutput(strFileName)
    nCnt = 0
    strTempFileName = GetTempName
    hResult = svrTSPrint.SavePage(strTempFileName)
    Do While 0 = hResult
        nCnt = nCnt + 1
        Set SubNode = SubNodes.Add("Seite")
        If Not SubNode Is Nothing Then
            SubNode.Caption = "Seite" & Str(nCnt)
            SubNode.SetFromFile strTempFileName
        End If
        strTempFileName = GetTempName
        hResult = svrTSPrint.SavePage(strTempFileName)
    Loop
Exit Sub

Err_LoadPrinterData:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next

End Sub

Private Sub Class_Initialize()
    Set SubNodes = New ccNodes
    Set SubNodes.Owner = Me
    Set Parent = Nothing
    Class = ""
    FileName = ""
    Caption = ""
    FileDate = Now
    FileAttributes = 0
    TempFileName = ""
    TempFileLen = 0
    State = 0
End Sub

Private Sub Class_Terminate()
On Error GoTo Err_Class_Terminate
    
    If (Len(TempFileName) > 0) And DateiExist(TempFileName) Then
        Kill TempFileName
    End If

    Set SubNodes = Nothing
    Set Parent = Nothing
Exit Sub

Err_Class_Terminate:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next

End Sub

Public Function ZahlSeiten() As Integer
 Dim nx As Integer
 Dim px As Integer
    px = 0
    For nx = 1 To SubNodes.Count
        If SubNodes.Item(nx).Class = "Seite" Then
            px = px + 1
        End If
    Next nx
    ZahlSeiten = px
End Function

Public Function ZahlSignaturen() As Integer
 Dim nx As Integer
 Dim sx As Integer
    sx = 0
    For nx = 1 To SubNodes.Count
        If SubNodes.Item(nx).Class = "Unterschrift" Then
            sx = sx + 1
        End If
    Next nx
    ZahlSignaturen = sx
End Function

Public Function Page(ByVal pix As Integer) As cNode
 Dim SubNode As cNode
 Dim nx As Integer
 Dim px As Integer
    px = 0
    For nx = 1 To SubNodes.Count
        If SubNodes.Item(nx).Class = "Seite" Then
            px = px + 1
        End If
        If px = pix Then
            Set Page = SubNodes.Item(nx)
            Exit Function
        End If
    Next nx
    Page = Nothing
End Function

Public Function Visualisation(vix As Integer) As cNode
 Dim SubNode As cNode
 Dim nx As Integer
 Dim vx As Integer
    vx = 0
    For nx = 1 To SubNodes.Count
        If SubNodes.Item(nx).Class = "Visualisierung" Then
            vx = vx + 1
        End If
        If vx = vix Then
            Set Visualisation = SubNodes.Item(nx)
            Exit Function
        End If
    Next nx
    Visualisation = Nothing
End Function

Public Function Signature(six As Integer) As cNode
 Dim SubNode As cNode
 Dim nx As Integer
 Dim sx As Integer
    sx = 0
    For nx = 1 To SubNodes.Count
        If SubNodes.Item(nx).Class = "Unterschrift" Then
            sx = sx + 1
        End If
        If sx = six Then
            Set Signature = SubNodes.Item(nx)
            Exit Function
        End If
    Next nx
    Signature = Nothing
End Function


Public Function FillListView(lv As ListView) As Boolean
Dim itmX As ListItem, i As Integer

    lv.ListItems.Clear
    Select Case Me.Class
    Case "Visualisierung"
        For i = 1 To Me.SubNodes.Count
            Set itmX = lv.ListItems.Add(, Me.SubNodes.Item(i).UniqueKey, _
                        Me.SubNodes.Item(i).Caption)
            itmX.SubItems(1) = Me.SubNodes.Item(i).Size
            itmX.SubItems(2) = Me.SubNodes.Item(i).ClassName
            itmX.SubItems(3) = Me.SubNodes.Item(i).FileDate
        Next i
        Set itmX = Nothing
    
    Case "Verzeichnis"
        For i = 1 To Me.SubNodes.Count
            Set itmX = lv.ListItems.Add(, Me.SubNodes.Item(i).UniqueKey, _
                        Me.SubNodes.Item(i).Caption)
            itmX.SubItems(1) = Me.SubNodes.Item(i).Size
            itmX.SubItems(2) = Me.SubNodes.Item(i).ClassName
            itmX.SubItems(3) = Me.SubNodes.Item(i).FileDate
        Next i
        Set itmX = Nothing
    
    Case "Dokument"
        For i = 1 To Me.SubNodes.Count
            Set itmX = lv.ListItems.Add(, Me.SubNodes.Item(i).UniqueKey, _
                        Me.SubNodes.Item(i).Caption)
            itmX.SubItems(1) = Me.SubNodes.Item(i).Size
            itmX.SubItems(2) = Me.SubNodes.Item(i).ClassName
            itmX.SubItems(3) = Me.SubNodes.Item(i).FileDate
        Next i
        Set itmX = Nothing
    
    End Select
End Function

Public Function ClassName() As String

    ClassName = Class
End Function
