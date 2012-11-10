Attribute VB_Name = "ModTestFormatOKS"
Option Explicit

Sub testFormatOKS()
    Dim mdsKey As New TRiASMDSKey, strOKS$
    '------------------------------------------------------
    ' strOKS$ <== "[999AB000]"
    strOKS$ = mdsKey.FormatOKS(&H999AB000)
    '------------------------------------------------------
    ' strOKS$ <== "[999AB000]"
    strOKS$ = mdsKey.FormatOKS("999AB000")
    '------------------------------------------------------
    ' strOKS$ <== "[999AB000]:Haus mit Dach"
    strOKS$ = mdsKey.FormatOKS("[999AB000]", "Haus mit Dach")
End Sub
