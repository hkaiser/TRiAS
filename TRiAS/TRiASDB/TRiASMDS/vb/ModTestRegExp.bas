Attribute VB_Name = "ModTestRegExp"
Option Explicit

Sub testRegExp()
    Dim mdsMap As New TRiASMDSMap
    Dim mdscoll As TRiASMDSStringColl
    Dim v As Variant
    Dim sKey$, sShort$, sLong$
    mdsMap.SetAt "11190", "Hallo", "Das lange Hallo"
    mdsMap.SetAt "11191", "Ballo", "Das lange Ballo"
    mdsMap.SetAt "11192", "knallo", "Das lange Knallo"
    mdsMap.SetAt "11193", "Fallo", "Das lange Fallo"
    Set mdscoll = mdsMap.SearchValues("[BK].*a.*", mdsSM_RegExp + mdsSM_NoCase)
    For Each v In mdscoll
        sKey$ = v
        mdsMap.GetAt sKey$, sShort$, sLong$
    Next
End Sub

