Attribute VB_Name = "TestErrTrk"
Option Explicit
Option Base 0

Sub TestErrTrk()
    Dim triasCTF As New TRiASCSTransform
    Dim trCS1 As New TRiASCS
    Dim trCSOut As New TRiASCS
    On Error GoTo DumpErrors

GoTo DoTransform

    trCS1.CoordSystemType = tcsCS_Geographic
    trCS1.GeographicCS.GeodeticDatum = tcsGD_DeutscheHauptdreiecksnetz
    trCS1.GeographicCS.PrimeMeridian = tcsPM_Greenwich
    trCS1.GeographicCS.UnitOfAngle = tcsUOA_Degree
    
    trCS1.DatumTransformation.TransformationAlgorithm = tcsDTA_GeocentricTranslations
    trCS1.DatumTransformation.Parameter(tcsDTP_GeocentricTranslations_XAxisTranslation) = 0
    trCS1.DatumTransformation.Parameter(tcsDTP_GeocentricTranslations_YAxisTranslation) = 0
    trCS1.DatumTransformation.Parameter(tcsDTP_GeocentricTranslations_ZAxisTranslation) = 0
    
    trCSOut.CoordSystemType = tcsCS_Projected
    trCSOut.GeographicCS.GeodeticDatum = tcsGD_DeutscheHauptdreiecksnetz
    trCSOut.GeographicCS.PrimeMeridian = tcsPM_Greenwich
    trCSOut.GeographicCS.UnitOfAngle = tcsUOA_Degree
    
    trCSOut.DatumTransformation.TransformationAlgorithm = tcsDTA_GeocentricTranslations
    trCSOut.DatumTransformation.Parameter(tcsDTP_GeocentricTranslations_XAxisTranslation) = 0
    trCSOut.DatumTransformation.Parameter(tcsDTP_GeocentricTranslations_YAxisTranslation) = 0
    trCSOut.DatumTransformation.Parameter(tcsDTP_GeocentricTranslations_ZAxisTranslation) = 0
    
    trCSOut.ProjectedCS.ProjectionAlgorithm = tcsPA_GaussKrueger
    trCSOut.ProjectedCS.UnitOfLength = tcsUOL_Metre
    trCSOut.ProjectedCS.ProjectionParameter(tcsPP_GaussKrueger_FalseEasting) = 5500000#
    trCSOut.ProjectedCS.ProjectionParameter(tcsPP_GaussKrueger_FalseNorthing) = 0#
    trCSOut.ProjectedCS.ProjectionParameter(tcsPP_GaussKrueger_LongitudeOfNaturalOrigin) = 15#
    trCSOut.ProjectedCS.ProjectionParameter(tcsPP_GaussKrueger_LatitudeOfNaturalOrigin) = 0#
DoTransform:
    trCS1.GeographicCS.GeodeticDatum = tcsGD_UserDefined
    trCS1.GeographicCS.Ellipsoid = tcsEL_UserDefined
    trCS1.GeographicCS.SemiMajorAxis = 0
    trCS1.GeographicCS.Flattening = 0
    triasCTF.OutputCS = trCSOut
    triasCTF.AddInputCS trCS1
    trCSOut.Recompute

    Dim ptsIn() As Double: ReDim ptsIn(0 To 2)
    ptsIn(0) = 13#
    ptsIn(1) = 52#
    ptsIn(2) = 0
    
    Dim ptsOut As Variant
    ptsOut = triasCTF.Transform(strguid:=trCS1.Guid, inpoints:=ptsIn)
    Exit Sub
DumpErrors:
    Dim errTrk As New ErrorStack, eItem As ErrorItem
    For Each eItem In errTrk
        MsgBox eItem.Description, vbOKOnly, "Err " & eItem.Source
    Next
End Sub
