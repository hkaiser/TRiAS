Attribute VB_Name = "TestTRiASCFG"
Sub Main()
    Call TestTRiASCFG
End Sub

Sub TestTRiASCFG()
Dim XmlService As New LoadXmlService
Dim Doc As IXMLDOMDocument

    Set Doc = XmlService.LoadXmlFromResource("SearchAndReplaceOKS.xml")
    Doc.save "d:\temp\out.xml"
    
End Sub
