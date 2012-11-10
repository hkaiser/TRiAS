Attribute VB_Name = "FileFuncs"
Option Explicit
Option Base 1

Declare Function GetTempPath Lib "kernel32" Alias "GetTempPathA" _
        (ByVal nBufferLength As Long, ByVal lpBuffer As String) As Long

Declare Function GetTempFileName Lib "kernel32" Alias "GetTempFileNameA" _
        (ByVal lpszPath As String, ByVal lpPrefixString As String, _
         ByVal wUnique As Long, ByVal lpTempFileName As String) As Long

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
    Suffix = Right(Path, 4)
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

Public Function GetTempDirName() As String
 Dim hResult As Long, PathBuffSize As Long, PathBuff As String

    PathBuffSize = 255
    PathBuff = Space$(PathBuffSize)
    hResult = GetTempPath(PathBuffSize, PathBuff)
    If 0 = hResult Then
        GetTempDirName = ""
    Else
        GetTempDirName = StripTerminator(PathBuff)
    End If
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

