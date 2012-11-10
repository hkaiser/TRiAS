VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "VBExtension"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Implements TRiAS.DTRiASExtension

Private TabWnd As SABiS_CLASSES.CommonChildWindow2    ' TabChildWindow

Private Sub DTRiASExtension_LoadExtension(ByVal pIApp As TRiAS.DApplication, Optional ByVal vDocDisp As Variant)
  
  Set TabWnd = CreateObject("TRiAS.SabisTabChildWindow:{2}TestWindow")   ' ProgId + Name der Tablasche
  
  'TabWnd.Icon = ...        ' unbedingt for erstem .Visible = True!
  'TabWnd.BackColor = ...   ' darf vorher kommen, aber auch hinterher
  'TabWnd.Tag = ...         ' funktioniert ebenfalls immer
  
  TabWnd.Caption = "SABiSTabWnd"
  TabWnd.Visible = True     ' erzeugt das Fenster (Tablasche)
  
' jetzt kann mit TabWnd.hWnd das Fensterhandle des als direkten Parent zu verwendenden Fensters
' abgefragt werden

  'TabWnd.Enabled = ...     ' ist erst nach dem ersten .Visible = True möglich
  
  'TabWnd.WindowState bringt in diesem Kontext keinen Sinn
  'TabWnd.Top, .Bottom, .Left, .Right, .Height und .Width sind noch nicht implementiert

End Sub

Private Sub DTRiASExtension_UnloadExtension()
  Set TabWnd = Nothing      ' zerlegt das Fenster und die Tablasche
End Sub

Private Function DTRiASExtension_UnloadingExtension(ByVal fMayDeny As Boolean) As Boolean
  TabWnd.Visible = False    ' blendet Tablasche mit diesem Fenster aus
  DTRiASExtension_UnloadingExtension = True
End Function
