VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "ccNodes"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

'local variable to hold collection
Private mCol As Collection
Public Owner As cNode

Public Function Add(Class As String) As cNode
Dim objNewMember As cNode
    
    Set objNewMember = New cNode

    Set objNewMember.Parent = Owner
    objNewMember.Class = Class
    objNewMember.UniqueKey = GetUniqueKey

    mCol.Add objNewMember, objNewMember.UniqueKey

    Set Add = objNewMember
    Set objNewMember = Nothing

End Function

Public Property Get Item(vntIndexKey As Variant) As cNode
    Set Item = mCol(vntIndexKey)
End Property

Public Property Get Count() As Long
    Count = mCol.Count
End Property

Public Sub Clear()
    While Count() > 0
        Remove Count()
    Wend
End Sub

Public Sub Remove(vntIndexKey As Variant)
    mCol.Remove vntIndexKey
End Sub

Public Property Get NewEnum() As IUnknown
    'this property allows you to enumerate
    'this collection with the For...Each syntax
    Set NewEnum = mCol.[_NewEnum]
End Property

Private Sub Class_Initialize()
    Set mCol = New Collection
    Set Owner = Nothing
End Sub

Private Sub Class_Terminate()
    Set mCol = Nothing
    Set Owner = Nothing
End Sub

Public Function Exists(Key As String) As Boolean
On Error GoTo Err_Exists
 Dim nd As cNode
    Set nd = Find(Key)
    If nd Is Nothing Then
        Exists = False
    Else
        Exists = True
        Set nd = Nothing
    End If
Exit Function

Err_Exists:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Function

Public Function Find(Key As String) As cNode
On Error GoTo Err_Find
 Dim nd As cNode
 Dim nx As Integer

    Set nd = Nothing
    For nx = 1 To Count
        If Item(nx).UniqueKey = Key Then
            Set nd = Item(nx)
        Else
            Set nd = Item(nx).SubNodes.Find(Key)
        End If
        If Not nd Is Nothing Then
            Set Find = nd
            Set nd = Nothing
            Exit Function
        End If
    Next nx
    Set Find = Nothing
Exit Function

Err_Find:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Function

Public Function RemoveSubnode(Key As String) As Boolean
On Error GoTo Err_RemoveSubnode
 Dim result As Boolean
 Dim nx As Integer

    result = False
    For nx = 1 To Count
        If Item(nx).UniqueKey = Key Then
            Remove Key
            result = True
        Else
            result = Item(nx).SubNodes.RemoveSubnode(Key)
        End If
        If result Then Exit Function
    Next nx
    RemoveSubnode = result
Exit Function

Err_RemoveSubnode:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Function

Sub BuildTreeView(tvTreeView As TreeView, ndParent As Node)
On Error GoTo Err_BuildTreeView
Dim Element As cNode
Dim nd As Node
Dim nx As Integer
Dim strIcon As String

    For nx = 1 To Count
        Set Element = Item(nx)
        Select Case Element.Class
        Case "Encrypted"
            If Element.encrypted Then
                strIcon = "TSOrdnerZu"
            Else
                strIcon = "Ordner"
            End If
        Case "Dokument"
            If Element.encrypted Then
                strIcon = "TSOrdnerZu"
            Else
                strIcon = "TSOrdner"
            End If
        Case "Visualisierung"
            strIcon = "Seiten"
        Case "Verzeichnis"
            If Element.encrypted Then
                strIcon = "TSOrdnerZu"
            Else
                strIcon = "Ordner"
            End If
        Case "Anlage"
            If Element.encrypted Then
                strIcon = "AnlageZu"
            Else
                strIcon = "Anlage"
            End If
        Case "Seite"
            strIcon = "Blatt"
        Case "Unterschrift"
            If Element.encrypted Then
                strIcon = "Schloss1"
            Else
                strIcon = "Sign1"
            End If
        Case "Zertifikat"
            strIcon = "Zerti"
        End Select
        If ndParent Is Nothing Then
            Set nd = tvTreeView.Nodes.Add(, , Element.UniqueKey, Element.Caption, strIcon)
        Else
            Set nd = tvTreeView.Nodes.Add(ndParent, tvwChild, Element.UniqueKey, Element.Caption, strIcon)
        End If
        Element.SubNodes.BuildTreeView tvTreeView, nd
    Next nx
Exit Sub

Err_BuildTreeView:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next

End Sub

