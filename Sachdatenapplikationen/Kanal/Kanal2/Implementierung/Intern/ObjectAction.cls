VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "ObjectAction"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

' Interface für Operationen über einem Objekt
Public Function BeginAction() As Long
    
End Function

' muß auch Nullpointer verkraften
Public Function DoAction(obj As DGeoObject) As Long
    
End Function

Public Function EndAction() As Long

End Function



