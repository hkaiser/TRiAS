Attribute VB_Name = "FileFuncs"
Option Explicit
Option Base 1

Declare Function GetTempPath Lib "kernel32" Alias "GetTempPathA" _
        (ByVal nBufferLength As Long, ByVal lpBuffer As String) As Long

Declare Function GetTempFileName Lib "kernel32" Alias "GetTempFileNameA" _
        (ByVal lpszPath As String, ByVal lpPrefixString As String, _
         ByVal wUnique As Long, ByVal lpTempFileName As String) As Long

Public Const TSD_HEADERLEN = 16
'Public Const DT_Anlage = 1
'Public Const DT_Dokument = 2
'Public Const DT_Signatur = 3
'Public Const DT_Seite = 4
Public Const DT_Ende = 255

Public Function StripTerminator(ByVal strString As String) As String
Dim intZeroPos As Integer

    intZeroPos = InStr(strString, Chr$(0))
    If intZeroPos > 0 Then
        StripTerminator = Left$(strString, intZeroPos - 1)
    Else
        StripTerminator = strString
    End If
End Function

Public Sub SplitPath(ByVal Path As String, ByRef Drive As String, _
        ByRef Subdirs As String, ByRef FileName As String, _
        ByRef Suffix As String)

Dim LastBracket As Long
Const BackSlash = "\"

    Drive = Left(Path, 3)
    LastBracket = LastCharacter(Path, BackSlash)
    Subdirs = Mid(Path, 4, LastBracket - 4)
    FileName = Mid(Path, LastBracket, Len(Path) - LastBracket - 3)
    Suffix = right(Path, 4)
    While ("." <> Left(Suffix, 1)) And (Len(Suffix) > 0)
        FileName = FileName & Left(Suffix, 1)
        Suffix = Mid(Suffix, 2)
    Wend
End Sub

Public Function LastCharacter(ByVal SearchString As String, _
                              ByVal SearchFor As String) As Long
Dim curr_pos As Integer, next_pos As Integer

    next_pos = 0
    Do
        curr_pos = next_pos
        next_pos = InStr(curr_pos + 1, SearchString, SearchFor)
    Loop Until next_pos = 0
    LastCharacter = curr_pos + 1
End Function

Public Function GetTempName() As String
Dim ReturnVal As Long, PathBuffSize As Long, PathBuff As String
Dim Prefix As String, FileName As String, result As String

    PathBuffSize = 255
    PathBuff = Space$(PathBuffSize)
    Prefix = "TSD"
    FileName = Space$(255)
    ReturnVal = GetTempPath(PathBuffSize, PathBuff)
    If 0 = ReturnVal Then
        Exit Function
    End If
    PathBuff = StripTerminator(PathBuff)
    ReturnVal = GetTempFileName(PathBuff, Prefix, 0&, FileName)
    If 0 = ReturnVal Then
        Exit Function
    End If
    result = StripTerminator(FileName)
    fMainForm.gTempArray.Add result
    GetTempName = result
End Function

Public Function DateiExist(ByVal Name As String) As Boolean
Dim test As String
On Error GoTo ExistError

    test = Dir(Name)
    DateiExist = (0 <> Len(test))
Exit Function

ExistError:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Function


Private Function Ungleich(a() As Byte, b() As Byte, cnt As Long) As Boolean
Dim result As Boolean, i As Long

    result = False
    For i = 1 To cnt
        If a(i) <> b(i) Then
            result = True
            Exit For
        End If
    Next i
    Ungleich = result
End Function

Private Function Versatz(a() As Byte, b() As Byte, cnt As Long) As Long
Dim result As Long, i As Long

    result = 1
    For i = 2 To cnt
        If a(1) <> b(i) Then
            result = result + 1
        Else
            Exit For
        End If
    Next i
    Versatz = result
End Function

Public Function GetFileVersion(ByVal strFileName As String) As Boolean
Dim result As Boolean, hFile As Long
Dim buff() As Byte

On Error GoTo Err_GetFileVersion

    result = False
    gDokFileVersion = -1
    gDokFileMajor = 0
    gDokFileMinor = 0
    gDokFileRevision = 0
    gHeaderLen = 0

    ReDim buff(16)
    hFile = FreeFile
    Open strFileName For Binary As #hFile
'    Input #hFile, strDokType
'    If "TSD Version 0.0.1" <> strDokType Then
    Get #hFile, , buff
    Close #hFile

    If (buff(1) <> Asc("T")) Or (buff(2) <> Asc("S")) Or _
        (buff(3) <> Asc("D")) Then
        GoTo GFV_Fertig
    End If
    result = True
    If (buff(4) = Asc(" ")) And (buff(5) = Asc("V")) And _
        (buff(6) = Asc("e")) Then
        gDokFileVersion = 0
        GoTo GFV_Fertig
    End If
    gDokFileVersion = buff(4)
    gDokFileMajor = buff(5) * 256 + buff(6)
    gDokFileMinor = buff(7) * 256 + buff(8)
    gDokFileRevision = buff(9) * 256 + buff(10)
    gHeaderLen = buff(11) * 256 + buff(12)


GFV_Fertig:
    GetFileVersion = result
Exit Function

Err_GetFileVersion:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Function

Public Function ReadFH1n(ByVal strFileName As String, nd As cNode) As Long
Dim hResult As Long, hFile As Long
Dim buff() As Byte
Dim nextpos As Long
Dim Level(0 To 100) As cNode
Dim Elements As ccNodes
Dim Element As cNode

On Error GoTo Err_ReadFH1

    hResult = -1
    ReDim buff(gHeaderLen)

    hFile = FreeFile
    Open strFileName For Binary As #hFile
    Get #hFile, , buff
    Close #hFile

    Set Level(0) = nd
    nextpos = TSD_HEADERLEN + 1
    nd.Class = GetString(buff, nextpos + 17)
    nd.FileName = GetString(buff, nextpos + 17 + Len(nd.Class) + 2)
    nd.Caption = GetString(buff, nextpos + 17 + Len(nd.Class) + 2 + Len(nd.FileName) + 2)
    nd.TempFileLen = GetLong(buff, nextpos + 1)
    nd.FileAttributes = GetLong(buff, nextpos + 5)
    nd.FileDate = GetDate(buff, nextpos + 9)
    nd.State = GetLong(buff, nextpos + 13)
    nextpos = nextpos + 17 + Len(nd.Class) + 2 + Len(nd.FileName) + 2 + Len(nd.Caption) + 2
    
    Do While nextpos < gHeaderLen
        Set Elements = Level(buff(nextpos) - 1).SubNodes
        Set Element = Elements.Add(GetString(buff, nextpos + 17))
        Set Level(buff(nextpos)) = Element
        Element.FileName = GetString(buff, nextpos + 17 + Len(Element.Class) + 2)
        Element.Caption = GetString(buff, nextpos + 17 + Len(Element.FileName) + 2 + Len(Element.Class) + 2)
        Element.TempFileLen = GetLong(buff, nextpos + 1)
        Element.FileAttributes = GetLong(buff, nextpos + 5)
        Element.FileDate = GetDate(buff, nextpos + 9)
        Element.State = GetLong(buff, nextpos + 13)
        nextpos = nextpos + 17 + Len(Element.Class) + 2 + Len(Element.FileName) + 2 + Len(Element.Caption) + 2
    Loop
    
    hResult = 0

RFH1_Fertig:
    ReadFH1n = hResult
    Exit Function

Err_ReadFH1:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Function

Public Function ReadFH1(ByVal strFileName As String, nd As cNode) As Long
Dim hResult As Long, hFile As Long
Dim buff() As Byte
Dim nextpos As Long
Dim Level(0 To 100) As cNode
Dim Elements As ccNodes
Dim Element As cNode

On Error GoTo Err_ReadFH1

    hResult = -1
    ReDim buff(gHeaderLen)

    hFile = FreeFile
    Open strFileName For Binary As #hFile
    Get #hFile, , buff
    Close #hFile

    nextpos = TSD_HEADERLEN + 1
    Do While nextpos < gHeaderLen
        If buff(nextpos) = 0 Then
            Set Elements = gNode.SubNodes
        Else
            Set Elements = Level(buff(nextpos) - 1).SubNodes
        End If
        Set Element = Elements.Add(GetString(buff, nextpos + 17))
        Set Level(buff(nextpos)) = Element
        Element.FileName = GetString(buff, nextpos + 17 + Len(Element.Class) + 2)
        Element.Caption = GetString(buff, nextpos + 17 + Len(Element.FileName) + 2 + Len(Element.Class) + 2)
        Element.TempFileLen = GetLong(buff, nextpos + 1)
        Element.FileAttributes = GetLong(buff, nextpos + 5)
        Element.FileDate = GetDate(buff, nextpos + 9)
        Element.State = GetLong(buff, nextpos + 13)
        nextpos = nextpos + 17 + Len(Element.Class) + 2 + Len(Element.FileName) + 2 + Len(Element.Caption) + 2
    Loop
    
    hResult = 0

RFH1_Fertig:
    ReadFH1 = hResult
    Exit Function

Err_ReadFH1:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Function





'Private Function CalculateBuffSize() As Long
' Dim result As Long
' Dim nx As Long
'
'    result = 0
'    For nx = 1 To gNode.SubNodes.Count
'        result = result + gNode.SubNodes.Item(nx).SizeTSDHeader
'    Next nx
'    CalculateBuffSize = result
'End Function


Public Function GetLong(buff() As Byte, ByVal offset As Long) As Long
Dim result As Long

    result = 0
    result = result * 256 + buff(offset)
    result = result * 256 + buff(offset + 1)
    result = result * 256 + buff(offset + 2)
    result = result * 256 + buff(offset + 3)
    GetLong = result
End Function

Public Function SetLong(ByVal wert As Long, buff() As Byte, _
            ByVal offset As Long) As Long
Dim result As Long, n1 As Long, n2 As Long
Dim n3 As Long, n4 As Long, f1 As Double

    result = 0
    n4 = wert Mod 256
    n3 = ((wert - n4) / 256#) Mod 256
    n2 = ((wert - n4 - n3 * 256) / (256# * 256)) Mod 256
    f1 = 256# * 256 * 256
    n1 = ((wert - n4 - n3 * 256 - n2 * 256 * 256) / f1) Mod 256
    buff(offset) = n1
    buff(offset + 1) = n2
    buff(offset + 2) = n3
    buff(offset + 3) = n4
    SetLong = 4
End Function

Public Function SetInt(ByVal wert As Integer, buff() As Byte, _
                ByVal offset As Long) As Long
Dim n As Long

    n = wert Mod 256
    buff(offset + 1) = wert Mod 256
    buff(offset) = ((wert - n) / 256) Mod 256
    SetInt = 2
End Function

Public Function GetDate(buff() As Byte, ByVal offset As Long) As Date
    GetDate = CVDate(Str(buff(offset)) & "." & Str(buff(offset + 1)) & "." & Str(buff(offset + 2) * 256 + buff(offset + 3)))
End Function

Public Function SetDate(ByVal Datum As String, buff() As Byte, _
            ByVal offset As Long) As Integer
    buff(offset) = Day(Datum)
    buff(offset + 1) = Month(Datum)
    buff(offset + 2) = Int(Year(Datum) / 256)
    buff(offset + 3) = Year(Datum) Mod 256
    SetDate = 4
End Function

Public Function GetString(buff() As Byte, ByVal offset As Long) As String
Dim result As String, C As Integer, n As Integer, i As Integer

    n = buff(offset) * 256 + buff(offset + 1)
    result = ""
    For i = 1 To n
        C = buff(offset + i + 1)
        C = C + 37
        If C > 128 Then C = C - 128
        result = result & Chr(C)
    Next i
    GetString = result
End Function

Public Function SetString(ByVal text As String, buff() As Byte, _
                ByVal offset As Long) As Long
Dim result As Long, C As Integer, n As Integer, i As Integer

    n = Len(text)
    buff(offset) = n / 256
    buff(offset + 1) = n Mod 256
    result = 2 + n
    For i = 1 To n
        C = Asc(Mid(text, i, 1))
        C = C - 37
        If C < 0 Then C = C + 128
        buff(offset + i + 1) = C
    Next i
    SetString = result
End Function

Public Sub CopyFileOrDir(oDat As cNode, strPath As String)
Dim strKey As String, oDok As cNode, i As Integer

    strKey = strPath & oDat.Caption
    If "Anlage" = oDat.Class Then
        FileCopy oDat.TempFileName, strKey
    ElseIf "Verzeichnis" = oDat.Class Then
        MkDir strKey
        For i = 1 To oDat.SubNodes.Count
            Set oDok = oDat.SubNodes.Item(i)
            CopyFileOrDir oDok, strKey & "\"
        Next i
    End If
End Sub

' Rekursives Löschen eines Verzeichnisses mit Inhalt
Public Sub DelTree(DirName As String)
Const ATTR_NORMAL = 0
Const ATTR_DIRECTORY = 16

Dim OriginalDir, FileName, NextFileName As String

  OriginalDir = CurDir$
  ChDir DirName
  FileName = Dir$("*.*", ATTR_NORMAL)
  Do While FileName <> ""
      Kill FileName
      FileName = Dir$
  Loop

  Do
    FileName = Dir$("*.*", ATTR_DIRECTORY)
    While FileName = "." Or FileName = ".."
      FileName = Dir$
    Wend

    If FileName = "" Then Exit Do
    DelTree (FileName)
  Loop

  ChDir OriginalDir
  RmDir DirName
End Sub
