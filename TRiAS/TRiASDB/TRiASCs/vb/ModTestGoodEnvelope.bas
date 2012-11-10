Attribute VB_Name = "ModTestGoodEnvelope"
Option Explicit

Sub TestGoodEnvelope()
    Dim csOut As New TRiASCS, csTrans As New TRiASCSTransform
    Dim x0#, y0#, x1#, y1#
    '----------------------------------------------------------------
    ' OutputSystem muﬂ gegeben sein; csOut ist per Default als
    ' WGS84/Cyl-Equi initialisiert
    csTrans.OutputCS = csOut
    csTrans.GetGoodEnvelope x0, y0, x1, y1
    
    csOut.CoordSystemType = tcsCS_Geographic
    csOut.GeographicCS.UnitOfAngle = tcsUOA_Degree
    csOut.Recompute
    csTrans.GetGoodEnvelope x0, y0, x1, y1
    csTrans.ShutDown
End Sub
