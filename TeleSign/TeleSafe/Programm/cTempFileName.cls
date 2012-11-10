VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "cTempFileName"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit

'lokale Variable(n) zum Zuweisen der Eigenschaft(en)
Private mvarstrName As String 'lokale Kopie

Public Property Get strName() As String
'wird beim Ermitteln eines Eigenschaftswertes auf der rechten Seite einer Zuweisung verwendet.
'Syntax: Debug.Print X.strName
    strName = mvarstrName
End Property

Public Property Let strName(vData As String)
    If Len(mvarstrName) = 0 Then
        mvarstrName = vData
    End If
End Property

Private Sub Class_Terminate()
On Error GoTo TerminationError

    If (0 < Len(strName)) Then
        If vbDirectory = (GetAttr(strName) And vbDirectory) Then
            DelTree strName
        ElseIf vbNormal = (GetAttr(strName) And vbNormal) Then
            Kill strName
        End If
    End If

TerminationError:
    mvarstrName = ""
End Sub
