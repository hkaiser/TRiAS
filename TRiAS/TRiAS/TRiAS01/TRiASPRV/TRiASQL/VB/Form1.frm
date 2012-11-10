VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Small Parser Demo"
   ClientHeight    =   6510
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7650
   LinkTopic       =   "Form1"
   ScaleHeight     =   6510
   ScaleWidth      =   7650
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command2 
      Caption         =   "Register info"
      Height          =   495
      Left            =   6000
      TabIndex        =   4
      Top             =   120
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.TextBox Text2 
      Height          =   4455
      Left            =   240
      MultiLine       =   -1  'True
      TabIndex        =   2
      Text            =   "Form1.frx":0000
      Top             =   1800
      Width           =   6975
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Execute"
      Height          =   495
      Left            =   6000
      TabIndex        =   1
      Top             =   1200
      Width           =   1215
   End
   Begin VB.TextBox Text1 
      Height          =   495
      Left            =   240
      MultiLine       =   -1  'True
      TabIndex        =   0
      Text            =   "Form1.frx":0006
      Top             =   1200
      Width           =   5535
   End
   Begin VB.Label Label1 
      Caption         =   "Demo of Small Parser-Enter the SQL statement and then press execute."
      Height          =   375
      Left            =   240
      TabIndex        =   3
      Top             =   120
      Width           =   5055
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' (C) 1999 Systementor AB     Stefan Holmberg


'Helper function just to add text to the out edit box
Private Sub AddText(sString As String)
    Text2.Text = Text2.Text & sString & vbCrLf
End Sub


' Helper function to convert the expression stack to text
' Expressions are expressed in postfix notation, that is like
' on old HP calculators
' 1 2 +    That means 1+2
' SmallParser converts the query expressions into postfix
' Why? Because they are so easy to evaluate

' Consider: 1+4*6
' In postfix that is: 1 4 6 * +
' To evaluate just go from left to right and when you come to an operand
' just use the two nearest fields on the stack

Private Function ExpressionToString(ByVal oExpression As TRiASOleDB.GenericStack) As String
    Dim o As TRiASOleDB.IExpressionItem
    Dim strText As String
    Dim n As Integer
    For n = 1 To oExpression.Count
        Set o = oExpression.Item(n)
        If strText = "" Then
            strText = "(POSTFIX)"
        End If
        strText = strText & " " & o.AsString
    Next
    If oExpression.AsName <> "" Then
        strText = strText & "  ---- AS " & oExpression.AsName
    End If
    ExpressionToString = strText
End Function


Private Sub DeleteStmt(oParser As TRiASOleDB.Parser)
    Dim oStatement As TRiASOleDB.DeleteStmt
    AddText (" DELETE STATEMENT" & vbCrLf)
    Set oStatement = oParser.DeleteStmt
    
    AddText ("")
    AddText ("***********Source table:")
    AddText (oStatement.TableIdent.Name)
        
    
    AddText ("")
    AddText ("***********Where expression:")
    If Not oStatement.WhereExpressionStack Is Nothing Then
       AddText ExpressionToString(oStatement.WhereExpressionStack)
    End If
End Sub

Private Sub InsertStmt(oParser As TRiASOleDB.Parser)
    Dim oStatement As TRiASOleDB.InsertStmt
    Dim oColIdent As TRiASOleDB.ColumnIdent
    Dim oStack As TRiASOleDB.GenericStack
    
    AddText (" INSERT STATEMENT" & vbCrLf)
    Set oStatement = oParser.InsertStmt
    
    AddText ("")
    AddText ("***********Source table:")
    AddText (oStatement.TableIdent.Name)
        
    AddText ("")
    AddText ("***********Insert columns:")
    For Each oColIdent In oStatement.ColumnIdentList
        AddText (oColIdent.ColumnName)
    Next
    
    AddText ("")
    AddText ("***********Insert expressions:")
    For Each oStack In oStatement.InsertExpressionList
        AddText ExpressionToString(oStack)
    Next
End Sub



Private Sub CreateTableStmt(oParser As TRiASOleDB.Parser)
    Dim oList As TRiASOleDB.CreateTableItemList
    Dim oStatement As TRiASOleDB.CreateTableStmt
    Dim oItem As TRiASOleDB.CreateTableItem
    Dim strText As String
    AddText (" CREATE TABLE STATEMENT" & vbCrLf)
    Set oStatement = oParser.CreateTableStmt
    
    AddText ("")
    AddText ("***********Source table:")
    AddText (oStatement.TableIdent.Name)
        
    
    AddText ("")
    AddText ("***********Column specifications:")
    For Each oItem In oStatement.CreateTableItemList
        strText = oItem.ColName & "   Datatype = "
        Select Case oItem.DataType
            Case PARSER_DATATYPE_INTEGER
                strText = strText & " Integer"
            Case PARSER_DATATYPE_STRING
                strText = strText & " char( " & CStr(oItem.DataLength) & ")"
            Case PARSER_DATATYPE_FLOAT
                strText = strText & " Float"
        End Select
    AddText strText
    Next
End Sub


Private Sub DropTableStmt(oParser As TRiASOleDB.Parser)
    Dim oStatement As TRiASOleDB.DropStmt
    Dim strText As String
    AddText (" DROP TABLE STATEMENT" & vbCrLf)
    Set oStatement = oParser.DropTableStmt
    
    AddText ("")
    AddText ("***********Source table:")
    AddText (oStatement.TableIdent.Name)
        
End Sub


Private Sub SelectStmt(oParser As TRiASOleDB.Parser)
    Dim oStatement As TRiASOleDB.SelectStmt
    Dim strTemp As String
    Dim oOrderByObj As TRiASOleDB.OrderByObj
    Dim oTableIdent As TRiASOleDB.TableIdent
    Dim oStackList As TRiASOleDB.GenericStackList
    
    Text2.Text = Text2.Text & " SELECT STATEMENT" & vbCrLf
    Set oStatement = oParser.SelectStmt
    
    AddText ("")
    AddText ("***********Distinct:")
    If oStatement.Distinct Then
        AddText ("Yes")
    Else
        AddText ("No")
    End If
    
    AddText ("")
    AddText ("***********Select expressions:")
    Set oStackList = oStatement.SelectExpressionList
    For Each oExpr In oStackList
        AddText ExpressionToString(oExpr)
    Next
    
    AddText ("")
    AddText ("***********Source tables:")
    For Each oTableIdent In oStatement.TableIdentList
        AddText (oTableIdent.Name)
    Next
        
    AddText ("")
    AddText ("***********Where expression:")
    If Not oStatement.WhereExpressionStack Is Nothing Then
       AddText ExpressionToString(oStatement.WhereExpressionStack)
    End If
        
        
    AddText ("")
    AddText ("***********Group by:")
    For Each oColIdent In oStatement.GroupByObjList
        AddText oColIdent.TableName & "." & oColIdent.ColumnName
    Next
        
    AddText ("")
    AddText ("***********Having expression:")
    If Not oStatement.HavingExpressionStack Is Nothing Then
        AddText ExpressionToString(oStatement.HavingExpressionStack)
    End If
        
        
    AddText ("")
    AddText ("***********Order by items:")
    For Each oOrderByObj In oStatement.OrderByObjList
            If oOrderByObj.Asc = True Then
                strAsc = " ASC "
            Else
                strAsc = " Desc "
            End If
            AddText (oOrderByObj.ColumnIdent.TableName & "." & oOrderByObj.ColumnIdent.ColumnName & strAsc)
        Next
        
    AddText ("")
    AddText ("***********Where expression:")
    If Not oStatement.WhereExpressionStack Is Nothing Then
       AddText ExpressionToString(oStatement.WhereExpressionStack)
    End If
    
    
    
End Sub

Private Sub UpdateStmt(oParser As TRiASOleDB.Parser)
    Dim oStatement As TRiASOleDB.UpdateStmt
    Dim strTemp As String
    Dim oTableIdent As TRiASOleDB.TableIdent
    Dim oUpdateItem As TRiASOleDB.UpdateItem

    Text2.Text = Text2.Text & " UPDATE STATEMENT" & vbCrLf
    Set oStatement = oParser.UpdateStmt
    
    
    AddText ("")
    AddText ("***********Table:")
    Set oTableIdent = oStatement.TableIdent
    AddText (oTableIdent.Name)


    AddText ("")
    AddText ("***********SET:")
    For Each oUpdateItem In oStatement.UpdateItemList
        strTemp = oUpdateItem.ColumnIdent.TableName & "." & oUpdateItem.ColumnIdent.ColumnName & "=" & ExpressionToString(oUpdateItem.ExpressionStack)
        AddText strTemp
    Next

    AddText ("")
    AddText ("***********Where expression:")
    If Not oStatement.WhereExpressionStack Is Nothing Then
       AddText ExpressionToString(oStatement.WhereExpressionStack)
    End If

End Sub





Private Sub Command1_Click()
    Dim oParser As TRiASOleDB.Parser
    
    On Error GoTo Hell
    
    Text2.Text = ""
    
    Set oParser = New TRiASOleDB.Parser
    oParser.ParseSQL Text1.Text
    Select Case oParser.StatementType
        Case STATEMENT_TYPE_SELECT
            SelectStmt oParser
        Case STATEMENT_TYPE_UPDATE
            UpdateStmt oParser
        Case STATEMENT_TYPE_DELETE
            DeleteStmt oParser
        Case STATEMENT_TYPE_INSERT
            InsertStmt oParser
        Case STATEMENT_TYPE_CREATETABLE
            CreateTableStmt oParser
        Case STATEMENT_TYPE_DROPTABLE
            DropTableStmt oParser
    End Select
    Exit Sub
    
Hell:
    MsgBox Err.Description, , Err.Source
End Sub

Private Sub Command2_Click()
'    Load Form2
'    Form2.Show vbModal
'    Unload Form2
End Sub

Private Sub Form_Load()
'    Load Form2
'    Form2.Show vbModal
'    Unload Form2
End Sub
