Attribute VB_Name = "GeoZuGau"
Option Explicit
Option Base 0
Const dX = 606.069176231606
Const dY = 22.9985051548215
Const dZ = 413.04801358317

'------------------------------------------------------------
' Transformation von geodätischen zu Gauß-Krüger Koordinaten

Sub TestGeoZuGau()
    Dim CTF As New TRiASCSTransform
    Dim CS1 As New TRiASCS
    Dim CS2 As New TRiASCS
    On Error GoTo errHandler
    
    CS1.CoordSystemType = tcsCS_Geographic
    With CS1.GeographicCS
        .GeodeticDatum = tcsGD_DeutscheHauptdreiecksnetz
        .PrimeMeridian = tcsPM_Greenwich
    End With
    With CS1.ProjectedCS
        .ProjectionAlgorithm = tcsPA_GaussKrueger
        .ProjectionParameter(tcsPP_GaussKrueger_FalseEasting) = 4500000#
        .ProjectionParameter(tcsPP_GaussKrueger_FalseNorthing) = 0#
        .ProjectionParameter(tcsPP_GaussKrueger_LongitudeOfNaturalOrigin) = 12#
        .ProjectionParameter(tcsPP_GaussKrueger_LatitudeOfNaturalOrigin) = 0#
    End With
    With CS1.DatumTransformation
        .TransformationAlgorithm = tcsDTA_GeocentricTranslations
        .Parameter(tcsDTP_GeocentricTranslations_XAxisTranslation) = dX
        .Parameter(tcsDTP_GeocentricTranslations_YAxisTranslation) = dY
        .Parameter(tcsDTP_GeocentricTranslations_ZAxisTranslation) = dZ
    End With
    
    CS2.CoordSystemType = tcsCS_Geographic
    With CS2.GeographicCS
        .GeodeticDatum = tcsGD_WorldGeodeticSystem1984
        .PrimeMeridian = tcsPM_Greenwich
    End With
    With CS2.ProjectedCS
        .ProjectionAlgorithm = tcsPA_GaussKrueger
        .ProjectionParameter(tcsPP_GaussKrueger_FalseEasting) = 4500000#
        .ProjectionParameter(tcsPP_GaussKrueger_FalseNorthing) = 0#
        .ProjectionParameter(tcsPP_GaussKrueger_LongitudeOfNaturalOrigin) = 12#
        .ProjectionParameter(tcsPP_GaussKrueger_LatitudeOfNaturalOrigin) = 0#
    End With
    With CS2.DatumTransformation
        .TransformationAlgorithm = tcsDTA_GeocentricTranslations
        .Parameter(tcsDTP_GeocentricTranslations_XAxisTranslation) = 0
        .Parameter(tcsDTP_GeocentricTranslations_YAxisTranslation) = 0
        .Parameter(tcsDTP_GeocentricTranslations_ZAxisTranslation) = 0
    End With
    
    '/////////////////////////////////////////////////////////////////////////////////////
    '// der Transformator...
    Dim csIn As TRiASCS, csOut As TRiASCS
    Set csIn = CS1
    Set csOut = CS2
    With csIn
        .CoordSystemType = tcsCS_Geographic
        .GeographicCS.UnitOfAngle = tcsUOA_Second
    End With
    With csOut
        .CoordSystemType = tcsCS_Projected
        .GeographicCS.UnitOfAngle = tcsUOA_Degree
        .ProjectedCS.UnitOfLength = tcsUOL_Metre
    End With
    
    CTF.AddInputCS csIn
    CTF.OutputCS = csOut
    CTF.OutputCS.Recompute
    
    '/////////////////////////////////////////////////////////////////////////////////////
    '// die Koordinate
    Dim ptsIn() As Double: ReDim ptsIn(0 To 2)
    ptsIn(0) = 12# * 3600                       '11# * 3600# + 59# * 60# + 54.5128311
    ptsIn(1) = 52# * 3600 + 30# * 60#           '52# * 3600# + 29# * 60# + 54.8759844
    ptsIn(2) = 0
    '/////////////////////////////////////////////////////////////////////////////////////
    '// ...transformieren
    Dim ptsOut As Variant
    ptsOut = CTF.Transform(strguid:=csIn.Guid, inpoints:=ptsIn)
    CTF.ShutDown
    ptsOut(0) = ptsOut(0) - 4499896.48687
    ptsOut(1) = ptsOut(1) - 5818821.21615
errHandler:
End Sub
