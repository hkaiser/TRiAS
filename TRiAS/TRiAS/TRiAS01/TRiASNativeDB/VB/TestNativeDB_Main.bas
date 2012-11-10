Attribute VB_Name = "TestNativeDB_Main"
Sub Main()
Dim DSService As TRiASNativeDataSource

    Set DSService = New TRiASNativeDataSource

Dim hPr As Long

    hPr = DSService.Open("D:\My Documents\TRiAS\TRiAS\Projekte\rath1.ris", False)
    DSService.Close (hPr)
    
End Sub
