Attribute VB_Name = "CSSet2"
Option Explicit
Option Base 0
Const BaseDir As String = "."

Sub TestCSSet2()
    Dim CSSet As New TRiASCSSet
    Dim cs As TRIASCS.TRIASCS

' Bundesweites Bessel
    Set cs = New TRIASCS.TRIASCS: GKBessel cs, "BeGk3_3", "Bessel, Gauß-Krüger (3°/3°)", 6, 1500000: CSSet.Add cs
    cs.SaveToFile BaseDir & "/BeGk3_3.tcf"
    Set cs = New TRIASCS.TRIASCS: GKBessel cs, "BeGk6_3", "Bessel, Gauß-Krüger (6°/3°)", 6, 2500000: CSSet.Add cs
    cs.SaveToFile BaseDir & "/BeGk6_3.tcf"
    Set cs = New TRIASCS.TRIASCS: GKBessel cs, "BeGk9_3", "Bessel, Gauß-Krüger (9°/3°)", 9, 3500000: CSSet.Add cs
    cs.SaveToFile BaseDir & "/BeGk9_3.tcf"
    Set cs = New TRIASCS.TRIASCS: GKBessel cs, "BeGk12_3", "Bessel, Gauß-Krüger (12°/3°)", 12, 4500000: CSSet.Add cs
    cs.SaveToFile BaseDir & "/BeGk12_3.tcf"
    Set cs = New TRIASCS.TRIASCS: GKBessel cs, "BeGk15_3", "Bessel, Gauß-Krüger (15°/3°)", 15, 5500000: CSSet.Add cs
    cs.SaveToFile BaseDir & "/BeGk15_3.tcf"
    Set cs = New TRIASCS.TRIASCS: GKBessel cs, "BeGkAuto3", "Bessel, Gauß-Krüger (Auto/3°)", 0, 0, 3: CSSet.Add cs
    cs.SaveToFile BaseDir & "/BeGkAuto3.tcf"

' DESD (DLK aus Leizen)
    Set cs = New TRIASCS.TRIASCS: GKBessel cs, "BesD", "Bessel, Gauß-Krüger (10.5°/3°) [BesD]", 10.5, 1500000: CSSet.Add cs
    cs.SaveToFile BaseDir & "/BesD.tcf"
    
' Neue Bundesländer (außer Thüringen)
    Set cs = New TRIASCS.TRIASCS: GKBessel cs, "BeGkRd839_3", "Bessel, Gauß-Krüger (9°/3°)", 9, 3500000, 3, tcsGD_DeutscheHauptdreiecksnetzRd83: CSSet.Add cs
    cs.SaveToFile BaseDir & "/BeGkRd839_3.tcf"
    Set cs = New TRIASCS.TRIASCS: GKBessel cs, "BeGkRd8312_3", "Bessel, Gauß-Krüger (12°/3°)", 12, 4500000, 3, tcsGD_DeutscheHauptdreiecksnetzRd83: CSSet.Add cs
    cs.SaveToFile BaseDir & "/BeGkRd8312_3.tcf"
    Set cs = New TRIASCS.TRIASCS: GKBessel cs, "BeGkRd8315_3", "Bessel, Gauß-Krüger (15°/3°)", 15, 5500000, 3, tcsGD_DeutscheHauptdreiecksnetzRd83: CSSet.Add cs
    cs.SaveToFile BaseDir & "/BeGkRd8315_3.tcf"
    Set cs = New TRIASCS.TRIASCS: GKBessel cs, "BeGkRd83Auto_3", "Bessel, Gauß-Krüger (Auto/3°)", 0, 0, 3, tcsGD_DeutscheHauptdreiecksnetzRd83: CSSet.Add cs
    cs.SaveToFile BaseDir & "/BeGkRd83Auto3.tcf"
    
    Set cs = New TRIASCS.TRIASCS: GKKrasso cs, "KrGk3_6", "Krassovsky, Gauß-Krüger (3°/6°)", 3, 1500000: CSSet.Add cs
    cs.SaveToFile BaseDir & "/KrGk3_6.tcf"
    Set cs = New TRIASCS.TRIASCS: GKKrasso cs, "KrGk9_6", "Krassovsky, Gauß-Krüger (9°/6°)", 9, 2500000: CSSet.Add cs
    cs.SaveToFile BaseDir & "/KrGk9_6.tcf"
    Set cs = New TRIASCS.TRIASCS: GKKrasso cs, "KrGk15_6", "Krassovsky, Gauß-Krüger (15°/6°)", 15, 3500000: CSSet.Add cs
    cs.SaveToFile BaseDir & "/KrGk15_6.tcf"
    Set cs = New TRIASCS.TRIASCS: GKKrasso cs, "KrGkAuto6", "Krassovsky, Gauß-Krüger (Auto/6°)", 0, 0, 6: CSSet.Add cs
    cs.SaveToFile BaseDir & "/KrGkAuto6.tcf"
    
    Set cs = New TRIASCS.TRIASCS: GKKrasso cs, "KrGk6_3", "Krassovsky, Gauß-Krüger (6°/3°)", 6, 2500000: CSSet.Add cs
    cs.SaveToFile BaseDir & "/KrGk6_3.tcf"
    Set cs = New TRIASCS.TRIASCS: GKKrasso cs, "KrGk9_3", "Krassovsky, Gauß-Krüger (9°/3°)", 9, 3500000: CSSet.Add cs
    cs.SaveToFile BaseDir & "/KrGk9_3.tcf"
    Set cs = New TRIASCS.TRIASCS: GKKrasso cs, "KrGk12_3", "Krassovsky, Gauß-Krüger (12°/3°)", 12, 4500000: CSSet.Add cs
    cs.SaveToFile BaseDir & "/KrGk12_3.tcf"
    Set cs = New TRIASCS.TRIASCS: GKKrasso cs, "KrGk15_3", "Krassovsky, Gauß-Krüger (15°/3°)", 15, 5500000: CSSet.Add cs
    cs.SaveToFile BaseDir & "/KrGk15_3.tcf"
    Set cs = New TRIASCS.TRIASCS: GKKrasso cs, "KrGkAuto3", "Krassovsky, Gauß-Krüger (Auto/3°)", 0, 0, 3: CSSet.Add cs
    cs.SaveToFile BaseDir & "/KrGkAuto3.tcf"
    
    Set cs = New TRIASCS.TRIASCS: UtmEtrs cs, "EtUtm15_6", "ETRS 89, UTM (15°/6°)", 15, 3500000: CSSet.Add cs
    cs.SaveToFile BaseDir & "/EtUtm15_6.tcf"
    Set cs = New TRIASCS.TRIASCS: UtmEtrs cs, "EtUtm9_6", "ETRS 89, UTM (9°/6°)", 9, 2500000: CSSet.Add cs
    cs.SaveToFile BaseDir & "/EtUtm9_6.tcf"
    Set cs = New TRIASCS.TRIASCS: UtmEtrs cs, "EtUtm3_6", "ETRS 89, UTM (3°/6°)", 3, 1500000: CSSet.Add cs
    cs.SaveToFile BaseDir & "/EtUtm3_6.tcf"
    Set cs = New TRIASCS.TRIASCS: UtmEtrs cs, "EtUtmAuto6", "ETRS 89, UTM (Auto/6°)", 0, 0, 6: CSSet.Add cs
    cs.SaveToFile BaseDir & "/EtUtmAuto6.tcf"
    
'    Set cs = New TRIASCS.TRIASCS: GKBessel cs, "Bessel (12°/3°)", 12, 4500000, _
'        tcsGD_DeutscheHauptdreiecksnetzRd83, tcsDTA_PositionVector7ParamTransformation: CSSet.Add cs
'    cs.SaveToFile BaseDir & "/BeGk12_3_7p.tcf"
'    Set cs = New TRIASCS.TRIASCS: GKKrasso cs, "Krassovsky (12°/3°)", 12, 4500000, _
'        tcsDTA_PositionVector7ParamTransformation: CSSet.Add cs
'    cs.SaveToFile BaseDir & "/KrGk12_3_7p.tcf"
    
    Set cs = New TRIASCS.TRIASCS: Geo cs, "BeGeod", "Bessel, geodätisch (Sekunden)", tcsGD_DeutscheHauptdreiecksnetz, tcsUOA_Second ', 606#, 23#, 413#
    CSSet.Add cs
    cs.SaveToFile BaseDir & "/BeGeod.tcf"
    Set cs = New TRIASCS.TRIASCS: Geo cs, "BeGeodDeg", "Bessel, geodätisch (Grad)", tcsGD_DeutscheHauptdreiecksnetz, tcsUOA_Degree ', 606#, 23#, 413#
    CSSet.Add cs
    cs.SaveToFile BaseDir & "/BeGeodDeg.tcf"
    
    Set cs = New TRIASCS.TRIASCS: Geo cs, "KrGeod", "Krassovsky, geodätisch (Sekunden)", tcsGD_Pulkovo1942, tcsUOA_Second           ' , 28#, -130#, -95#
    CSSet.Add cs
    cs.SaveToFile BaseDir & "/KrGeod.tcf"
    Set cs = New TRIASCS.TRIASCS: Geo cs, "KrGeodDeg", "Krassovsky, geodätisch (Grad)", tcsGD_Pulkovo1942, tcsUOA_Degree           ' , 28#, -130#, -95#
    CSSet.Add cs
    cs.SaveToFile BaseDir & "/KrGeodDeg.tcf"
    
    Set cs = New TRIASCS.TRIASCS: Geo cs, "WgsGeod", "WGS 84, geodätisch (Sekunden)", tcsGD_WorldGeodeticSystem1984, tcsUOA_Second   ' , 0#, 0#, 0#
    CSSet.Add cs
    cs.SaveToFile BaseDir & "/WgsGeod.tcf"
    Set cs = New TRIASCS.TRIASCS: Geo cs, "WgsGeodDeg", "WGS 84, geodätisch (Grad)", tcsGD_WorldGeodeticSystem1984, tcsUOA_Degree   ' , 0#, 0#, 0#
    CSSet.Add cs
    cs.SaveToFile BaseDir & "/WgsGeodDeg.tcf"
    
    Set cs = New TRIASCS.TRIASCS: Affine cs, "User1", "Nutzersystem 1": CSSet.Add cs
    cs.SaveToFile BaseDir & "/User1.tcf"
    
    Set cs = New TRIASCS.TRIASCS
    Soldner cs, "SoldnerBerlin", "Soldner Koordinatensystem (Berlin Müggelturm)", _
        tcsGD_DeutscheHauptdreiecksnetz, 52.41862827, 13.62720366, 40000#, 10000#
    CSSet.Add cs
    cs.SaveToFile BaseDir & "/SoldnerBerlin.tcf"
    
'    CSSet.SaveToRegistry TCS_HKCU, "Software\FEZ\TRiAS\CoordinateSystems"
'    CSSet.SaveToFile BaseDir & "/Coords.tcs"
    
End Sub

Sub GKBessel(cs As TRIASCS.TRIASCS, strName$, strDescr$, Lon#, east#, Optional ZoneWidth#, _
    Optional datum As TRIASCS.TRIASCSGEODETICDATUM, _
    Optional algo As TRIASCS.TRIASCSDTRANSALGORITHM)
    
    If (datum = 0) Then
        datum = tcsGD_DeutscheHauptdreiecksnetz
    End If
    If (algo = 0) Then
        algo = tcsDTA_PositionVector7ParamTransformation
    End If
    
    cs.Name = strName$
    cs.Category = "Gauß-Krüger Koordinatensystem"
    cs.Description = strDescr$
    cs.CoordSystemType = tcsCS_Projected
    
    With cs.GeographicCS
        .GeodeticDatum = datum  ' tcsGD_DeutscheHauptdreiecksnetz
        .UnitOfAngle = tcsUOA_Second
        .PrimeMeridian = tcsPM_Greenwich
    End With
    
    With cs.DatumTransformation
        .GeodeticDatum = datum  ' tcsGD_DeutscheHauptdreiecksnetz
        .TransformationAlgorithm = algo
    End With
    
    With cs.ProjectedCS
        .ProjectionAlgorithm = tcsPA_GaussKrueger
        .ProjectionParameter(tcsPP_GaussKrueger_ScaleFactorAtNaturalOrigin) = 1#
        .ProjectionParameter(tcsPP_GaussKrueger_LatitudeOfNaturalOrigin) = 0#
        .ProjectionParameter(tcsPP_GaussKrueger_LongitudeOfNaturalOrigin) = Lon# * 3600#
        .ProjectionParameter(tcsPP_GaussKrueger_FalseNorthing) = 0#
        .ProjectionParameter(tcsPP_GaussKrueger_FalseEasting) = east#
        .ProjectionParameter(tcsPP_GaussKrueger_ZoneWidth) = ZoneWidth#
    End With
End Sub

Sub GKKrasso(cs As TRIASCS.TRIASCS, strName$, strDescr$, Lon#, east#, Optional ZoneWidth#, _
    Optional algo As TRIASCS.TRIASCSDTRANSALGORITHM)
    
    cs.Name = strName$
    cs.Category = "Gauß-Krüger Koordinatensystem"
    cs.Description = strDescr$
    cs.CoordSystemType = tcsCS_Projected
    
    If (algo = 0) Then
        algo = tcsDTA_PositionVector7ParamTransformation
    End If
    
    With cs.GeographicCS
        .GeodeticDatum = tcsGD_Pulkovo1942
        .UnitOfAngle = tcsUOA_Second
        .PrimeMeridian = tcsPM_Greenwich
    End With
    
    With cs.DatumTransformation
        .GeodeticDatum = tcsGD_Pulkovo1942
        .TransformationAlgorithm = algo
    End With
    
    With cs.ProjectedCS
        .ProjectionAlgorithm = tcsPA_GaussKrueger
        .ProjectionParameter(tcsPP_GaussKrueger_ScaleFactorAtNaturalOrigin) = 1#
        .ProjectionParameter(tcsPP_GaussKrueger_LatitudeOfNaturalOrigin) = 0#
        .ProjectionParameter(tcsPP_GaussKrueger_LongitudeOfNaturalOrigin) = Lon# * 3600#
        .ProjectionParameter(tcsPP_GaussKrueger_FalseNorthing) = 0#
        .ProjectionParameter(tcsPP_GaussKrueger_FalseEasting) = east#
        .ProjectionParameter(tcsPP_GaussKrueger_ZoneWidth) = ZoneWidth#
    End With
End Sub

Sub UtmEtrs(cs As TRIASCS.TRIASCS, strName$, strDescr$, Lon#, east#, Optional ZoneWidth#)

    cs.Name = strName$
    cs.Category = "UTM Koordinatensystem"
    cs.Description = strDescr$
    cs.CoordSystemType = tcsCS_Projected
    
    With cs.GeographicCS
        .GeodeticDatum = tcsGD_WorldGeodeticSystem1984
        .UnitOfAngle = tcsUOA_Second
        .PrimeMeridian = tcsPM_Greenwich
    End With
    
    With cs.DatumTransformation
        .GeodeticDatum = tcsGD_WorldGeodeticSystem1984
        .TransformationAlgorithm = tcsDTA_PositionVector7ParamTransformation
    End With
    
    With cs.ProjectedCS
        .ProjectionAlgorithm = tcsPA_GaussKrueger
        .ProjectionParameter(tcsPP_GaussKrueger_ScaleFactorAtNaturalOrigin) = 0.9996
        .ProjectionParameter(tcsPP_GaussKrueger_LatitudeOfNaturalOrigin) = 0#
        .ProjectionParameter(tcsPP_GaussKrueger_LongitudeOfNaturalOrigin) = Lon# * 3600#
        .ProjectionParameter(tcsPP_GaussKrueger_FalseNorthing) = 0#
        .ProjectionParameter(tcsPP_GaussKrueger_FalseEasting) = east#
        .ProjectionParameter(tcsPP_GaussKrueger_ZoneWidth) = ZoneWidth#
    End With
End Sub

Sub Geo(cs As TRIASCS.TRIASCS, strName$, strDescr$, dat, uoa As TRIASCSUNITOFANGLE)

    cs.Name = strName$
    cs.Category = "Geodätisches Koordinatensystem"
    cs.Description = strDescr$
    cs.CoordSystemType = tcsCS_Geographic
    
    With cs.GeographicCS
        .GeodeticDatum = dat
        .UnitOfAngle = uoa
        .PrimeMeridian = tcsPM_Greenwich
    End With
    
    With cs.DatumTransformation
        .GeodeticDatum = dat
        .TransformationAlgorithm = tcsDTA_PositionVector7ParamTransformation
    End With
    
End Sub

Sub Affine(cs As TRIASCS.TRIASCS, strName$, strDescr$)
    cs.Name = strName$
    cs.Category = "Nutzerkoordinatensystem"
    cs.Description = strDescr$
    cs.CoordSystemType = tcsCS_Projected
    cs.ProjectedCS.ProjectionAlgorithm = tcsPA_AffineTransformation
    cs.ProjectedCS.UnitOfLength = tcsUOL_Metre
End Sub

Sub Soldner(cs As TRIASCS.TRIASCS, strName$, strDescr$, dat, Lat#, Lon#, FalseX#, FalseY#)

    cs.Name = strName$
    cs.Category = "Soldner Koordinatensystem"
    cs.Description = strDescr$
    cs.CoordSystemType = tcsCS_Projected
    
    With cs.GeographicCS
        .GeodeticDatum = dat
        .UnitOfAngle = tcsUOA_Second
        .PrimeMeridian = tcsPM_Greenwich
    End With
    
    With cs.DatumTransformation
        .GeodeticDatum = dat
        .TransformationAlgorithm = tcsDTA_PositionVector7ParamTransformation
    End With

    With cs.ProjectedCS
        .ProjectionAlgorithm = tcsPA_CassiniSoldner
        .ProjectionParameter(tcsPP_CassiniSoldner_LatitudeOfNaturalOrigin) = Lat * 3600
        .ProjectionParameter(tcsPP_CassiniSoldner_LongitudeOfNaturalOrigin) = Lon * 3600
        .ProjectionParameter(tcsPP_CassiniSoldner_FalseEasting) = FalseX
        .ProjectionParameter(tcsPP_CassiniSoldner_FalseNorthing) = FalseY
        .ProjectionParameter(tcsPP_GaussKrueger_ScaleFactorAtNaturalOrigin) = 1#
    End With

End Sub
