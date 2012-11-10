Attribute VB_Name = "ModTestMDSKey"
Option Explicit

Sub testSplitOKS()
    Dim mdsKey As New TRiASMDSKey, strOKS$, strShort$
    '------------------------------------------------------
    ' strOKS$ <== "999AB000"
    strOKS$ = mdsKey.SplitOKS("[999AB000]")
    '------------------------------------------------------
    ' strOKS$ <== "999AB000"
    strOKS$ = mdsKey.SplitOKS("[999ab000]")
    '------------------------------------------------------
    ' strOKS$ <== "999AB000"
    ' strShort$ <== "Haus mitDach"
    strOKS$ = mdsKey.SplitOKS("999ab000:Haus mitDach", strShort$)
    '------------------------------------------------------
    ' strOKS$ <== "999AB000"
    ' strShort$ <== "Haus mitDach"
    strOKS$ = mdsKey.SplitOKS("[999ab000]Haus mitDach", strShort$)
    '------------------------------------------------------
    ' Fehler
    strOKS$ = mdsKey.SplitOKS("Foo2000")
End Sub
