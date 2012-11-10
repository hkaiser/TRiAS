Attribute VB_Name = "CSSet"
Option Explicit
Option Base 0

Sub TestCSSet()
    Dim csSet1 As New TRiASCSSet
    Dim csSet2 As New TRiASCSSet
    Dim csSet3 As New TRiASCSSet
    
    Dim cs As TRiASCS, cs2 As TRiASCS, i%, s$
    
    For i% = 0 To 10
        Set cs = New TRiASCS
        If 8 = i% Then Set cs2 = cs
        If 0 = i Mod 3 Then
            cs.CoordSystemType = tcsCS_Projected
            cs.Category = "Gauß-Krüger Koordinatensysteme"
        End If
        If 1 = i Mod 3 Then
            cs.CoordSystemType = tcsCS_Geographic
            cs.Category = "Geodätische Koordinatensysteme"
        End If
        If 2 = i Mod 3 Then
            cs.CoordSystemType = tcsCS_Projected
            cs.Category = "Allgemeine Koordinatensysteme"
        End If
        cs.Description = "Koordinatensystem " & i%
        csSet1.Add cs
    Next
    For Each cs In csSet1
        s$ = cs.Description
    Next
    i% = csSet1.Count
    Set cs = csSet1.Find(5)
    Set cs = csSet1.Find("CS 7")
    Set cs = csSet1.Find(cs2)
    csSet1.Remove ("CS 3")
    Set cs = csSet1.Find(5)
    csSet1.SaveToFile ("c:\tmp\csset.dat")
    csSet1.SaveToRegistry TCS_HKCU, "Software\FEZ\TRiAS\CoordinateSystems"
    
    csSet2.LoadFromFile ("c:\tmp\csset.dat")
    csSet2.LoadFromRegistry TCS_HKCU, "Software\FEZ\TRiAS\CoordinateSystems"
    csSet2.SaveToFile ("c:\tmp\csset2.dat")
End Sub
