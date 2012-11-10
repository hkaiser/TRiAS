Attribute VB_Name = "StringArrayOps"
Option Explicit

' Bestimmen ob beide Arrays die gleiche Dimension haben
Public Function TesteDimensions(a1() As String, a2() As String) As Boolean
    If (UBound(a1) = UBound(a2)) And (LBound(a1) = LBound(a2)) Then
        TesteDimensions = True
    Else
        TesteDimensions = False
    End If
End Function

' Bestimmen der Dimension eines Arrays
Public Function GetDim(ByRef a() As String) As Long
    GetDim = UBound(a) - LBound(a)
End Function


