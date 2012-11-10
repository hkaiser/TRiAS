Attribute VB_Name = "FormatStrings"
Option Explicit

' Auseinandernehmen der eingegebenen Zeichenkette
Function RetrieveCoord(Text As String) As Double

    RetrieveCoord = 0
    On Error GoTo errorLabel
    
' zuerst alle offenen Stellen entfernen
Dim Result As String
Dim cNextChar As String
Dim iLen As Integer
Dim iLoop As Integer

    iLoop = 1
    iLen = Len(Text)
    Do
        cNextChar = Mid(Text, iLoop, 1)
        If (cNextChar <> "_") Then
            Result = Result + cNextChar
        End If
        iLoop = iLoop + 1
    Loop While (iLoop <= iLen)
    
' jetzt Konvertierung vornehmen
Dim dDeg As Long
Dim dMin As Long
Dim dSec As Double
Dim dVal As Long

    dDeg = 0
    dMin = 0
    dSec = 0
    dVal = 0

    iLoop = 1
    iLen = Len(Result)
    Do
        cNextChar = Mid(Result, iLoop, 1)
        Select Case cNextChar
        Case "°"        ' Minuten
            dDeg = dVal
            dVal = 0
            
        Case "'"        ' Minuten
            dMin = dVal
            If (Len(Result) - (iLoop + 1) - 1 > 0) Then
                dSec = CDbl(Mid(Result, iLoop + 1, Len(Result) - (iLoop + 1))) ' der Rest sind die Sekunden
            Else
                dSec = 0
            End If
            Exit Do
            
        Case "0" To "9"
            dVal = dVal * 10 + CLng(cNextChar)
        End Select
        
        iLoop = iLoop + 1
    Loop While (iLoop <= iLen)
    
' Ergebnis in Sekunden liefern
    RetrieveCoord = dDeg * 3600 + dMin * 60 + dSec
    Exit Function
    
errorLabel:
    RetrieveCoord = 0
    Exit Function
End Function

Function FormatCoord(dCoord As Double) As String
Dim dDeg As Long
Dim dMin As Long
Dim dSec As Double
Dim dVal As Long

    dDeg = (dCoord - 1800) / 3600
    dCoord = dCoord - dDeg * 3600
    
    dMin = (dCoord - 30) / 60
    While (dMin >= 60)
        dDeg = dDeg + 1
        dMin = dMin - 60
        dCoord = dCoord - 3600
    Wend
    dCoord = dCoord - dMin * 60
    
    dSec = dCoord
  
    While (dSec >= 60)
        dMin = dMin + 1
        dSec = dSec - 60
        While (dMin >= 60)
            dDeg = dDeg + 1
            dMin = dMin - 60
            dCoord = dCoord - 60
        Wend
    Wend

Dim strT As String

    strT = Format(dDeg) + "° "
    If (dMin <> 0 Or dSec <> 0) Then
        strT = strT + Format(dMin) + "' "
        If (dSec <> 0) Then
            strT = strT + Format(dSec, "#0.0####") + """"
        End If
    End If
    FormatCoord = strT
        
End Function

Function FormatCoordWithMask(dCoord As Double) As String

End Function
