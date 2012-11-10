VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "GeometryTransaction"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

' dieses Modul generiert eine (Pseudo) Transaction
' im Klartext : kein Undo
' im Moment wird einfach das neuzeichnen unterbunden

Private counter As Long
Private intrans As Boolean

Public Sub starttrans(redraweach As Long)
    intrans = True
    counter = 0
End Sub

Public Sub endtrans()
    intrans = False
    counter = 0
End Sub

Public Sub count()
    
End Sub

Private Sub Class_Initialize()
    counter = 0
    intrans = False
End Sub

Private Sub Class_Terminate()
    If intrans Then
        endtrans
    End If
End Sub
