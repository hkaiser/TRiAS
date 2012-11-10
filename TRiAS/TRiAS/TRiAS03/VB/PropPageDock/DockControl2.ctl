VERSION 5.00
Begin VB.UserControl PropPageDockControl 
   Alignable       =   -1  'True
   Appearance      =   0  'Flat
   BackColor       =   &H00C0C0FF&
   ClientHeight    =   735
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   3930
   ControlContainer=   -1  'True
   DrawMode        =   11  'Not Xor Pen
   ScaleHeight     =   735
   ScaleWidth      =   3930
   ToolboxBitmap   =   "DockControl2.ctx":0000
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      Caption         =   "Docking Control"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   24
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   60
      TabIndex        =   0
      Top             =   60
      Width           =   3795
   End
End
Attribute VB_Name = "PropPageDockControl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Implements implDockControl

' Wir sind die Nutzerschnittstelle einer TRiAS-Geokomponente
Implements TRiAS.IGeoComponentUI
Private mUICallback As TRiAS.IGeoComponentUICallback

Private mPropSheet As CommonPropertySheet
Private mModalPageUsage As Boolean

Private m_wndprcNext As Long

Public Event FireCommand(ByVal Command As Variant, MoreData As Variant)
Public Event NextFocus(ByVal Prev As Boolean)
Public Event OnKeyDown(KeyCode As Integer, Shift As Integer)
Public Event DoActivateForm()
Public Event PageActivated()

Public Property Get Enabled() As Boolean
  Enabled = UserControl.Enabled
End Property

Public Property Get ActiveControl() As Object
  On Error Resume Next
  If IsNotNothing(mPropSheet) Then
    Set ActiveControl = mPropSheet.ActiveControl
  End If
End Property


Public Property Get ControlType() As OwnControlTypes
  ControlType = octDock
End Property


Public Property Get ClientSheet() As CommonPropertySheet
  Set ClientSheet = mPropSheet
End Property


Public Property Let Enabled(ByVal NewValue As Boolean)
  UserControl.Enabled = NewValue
End Property


Public Property Let ModalPageUsage(ByVal NewValue As Boolean)
  mModalPageUsage = NewValue
End Property

Public Property Get ModalPageUsage() As Boolean
  ModalPageUsage = mModalPageUsage
End Property

Public Sub MoveWithClient(ByVal x As Long, ByVal Y As Long, _
    ByVal CX As Long, ByVal CY As Long, Optional ByVal AlignMode As Variant, _
    Optional ByVal AlignModeParent As Variant)
    
  If IsNothing(mPropSheet) Then Exit Sub
  On Error Resume Next
  With UserControl
    .ScaleTop = Y
    .ScaleLeft = x
    .Width = CX
    .Height = CY
  End With
  With mPropSheet
    Select Case ResolveParaZahl(dtamStandard, AlignMode)
      Case dtamStretch, dtamStandard
        Call .MovePage(0, 0, CX, CY)
      Case dtamRight
        Call .MovePage(CX - .Width, 0)
      Case dtamCenter
        Call .MovePage((CX - .Width) \ 2, (CY - .Height \ 2))
      Case dtamLeft
        Call .MovePage(0, 0)
    End Select
  End With
End Sub

Public Sub OnActivateControl()
  On Error Resume Next
  If IsNotNothing(mPropSheet) Then
    Call mPropSheet.OnActivatePage
  End If
End Sub



Private Property Get isSubClassed() As Boolean
  isSubClassed = m_wndprcNext <> 0
End Property

Public Sub Refresh()
  UserControl.Refresh
End Sub

Private Sub SubClass()
  If isSubClassed Then Exit Sub
    
  Call SetWindowLong(hwnd, GWL_USERDATA, ObjPtr(Me))
  m_wndprcNext = SetWindowLong(hwnd, GWL_WNDPROC, _
    AddressOf DockCtrlProc)
End Sub
Public Property Get SubControls() As Object
  If IsNothing(mPropSheet) Then
    Set SubControls = Nothing
  Else
    Set SubControls = mPropSheet.Controls
  End If
End Property

Private Property Get TargetHandle() As Long
  If IsNotNothing(mPropSheet) Then
    TargetHandle = mPropSheet.hwnd
  Else
    TargetHandle = 0
  End If
End Property

Friend Function WindowProc(ByVal hwnd As Long, ByVal uMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
    
  If isSubClassed Then
    On Error Resume Next
    Select Case uMsg
      Case WM_SETFOCUS
        WindowProc = CallWindowProc(m_wndprcNext, hwnd, _
          uMsg, wParam, ByVal lParam)
        Call PostMessage(UserControl.hwnd, MSG_SETFOCUSTOCONTROL, 0, 0)
      Case MSG_SETFOCUSTOCONTROL
        Call OnActivateControl
      Case Else
        WindowProc = CallWindowProc(m_wndprcNext, hwnd, _
          uMsg, wParam, ByVal lParam)
    End Select
  End If
End Function

Friend Sub UnSubClass()
  If isSubClassed Then
    On Error Resume Next
    Call SetWindowLong(hwnd, GWL_WNDPROC, m_wndprcNext)
    Call SetWindowLong(hwnd, GWL_USERDATA, 0&)
    m_wndprcNext = 0
  End If
End Sub


Public Property Let BackColor(ByVal RHS As Long)
  UserControl.BackColor = RHS
End Property


Public Property Get BackColor() As Long
  BackColor = UserControl.BackColor
End Property


Public Sub CloseParent()
  On Error Resume Next
  Call UnSubClass
  If IsNotNothing(mPropSheet) Then
    Call mPropSheet.ClosePage
    Set mPropSheet = Nothing
  End If
End Sub
Public Function CreateParent _
    (ByVal AObjekt As Variant, _
    ByVal Callback As SABIS_CLASSES.CommonCallback, _
    ByVal SubPageMode As PropertySheetUsages, _
    ByVal Info As implUserInfo, Optional ByVal MoreData As Variant) As SABIS_CLASSES.CommonPropertySheet
  
  Set CreateParent = Nothing
  On Error GoTo CPErr
  If VarTypeText(AObjekt) Then
    Set mPropSheet = CreateObject(AObjekt)
  Else
    Set mPropSheet = AObjekt
  End If
  If IsNotNothing(mPropSheet) Then
    With mPropSheet
      If .OnInitPage(Me, Callback, SubPageMode, Info, MoreData) Then
        Call SetParent(.hwnd, hwnd)
        Call ShowWindow(.hwnd, vbNormalFocus)
        Call SetAsParent(.hwnd)
        Call SetWindowLong(.hwnd, GWL_STYLE, _
          GetWindowLong(.hwnd, GWL_STYLE) Or DS_CONTROL)
        Call SetWindowLong(.hwnd, GWL_EXSTYLE, _
          GetWindowLong(.hwnd, GWL_EXSTYLE) Or WS_EX_CONTROLPARENT)
        Call SubClass
        Set CreateParent = mPropSheet
      End If
    End With
  End If
  Exit Function
CPErr:
  Err.Raise Err
End Function

Public Sub FireCommand(ByVal Command As Variant, MoreData As Variant)
  On Error Resume Next
  RaiseEvent FireCommand(Command, MoreData)
End Sub

Public Property Get hwnd() As Long
  hwnd = UserControl.hwnd
End Property

Public Sub OnKeyDown(KeyCode As Integer, Shift As Integer)
  On Error Resume Next
  RaiseEvent OnKeyDown(KeyCode, Shift)
End Sub

Public Sub SetNextFocus(ByVal Prev As Boolean)
  On Error Resume Next
  RaiseEvent NextFocus(Prev)
End Sub

Private Sub implDockControl_DoActivateForm()
  On Error Resume Next
  RaiseEvent DoActivateForm
  'UserControl.SetFocus
End Sub

Private Sub implDockControl_FireCommand(ByVal ACommand As Variant, MoreData As Variant)

End Sub


Private Property Get implDockControl_hWnd() As Long
  implDockControl_hWnd = UserControl.hwnd
End Property

Private Sub implDockControl_OnKeyDown(KeyCode As Integer, Shift As Integer)
  On Error Resume Next
  RaiseEvent OnKeyDown(KeyCode, Shift)
End Sub


Private Sub implDockControl_ParentActivated()
  On Error Resume Next
  RaiseEvent PageActivated
End Sub

Private Sub implDockControl_SetNextFocus(ByVal Prev As Boolean)
  On Error Resume Next
  RaiseEvent NextFocus(Prev)
End Sub

Private Sub UserControl_EnterFocus()
  On Error Resume Next
  Call OnActivateControl
End Sub

Private Sub UserControl_GotFocus()
  On Error Resume Next
  Call OnActivateControl
End Sub


Private Sub UserControl_Initialize()
  With UserControl
    Call SetWindowLong(.hwnd, GWL_STYLE, _
      GetWindowLong(.hwnd, GWL_STYLE) Or DS_CONTROL)
    Call SetWindowLong(.hwnd, GWL_EXSTYLE, _
      GetWindowLong(.hwnd, GWL_EXSTYLE) Or WS_EX_CONTROLPARENT)
  End With
  Set mUICallback = Nothing
End Sub

Private Sub UserControl_MouseDown(Button As Integer, Shift As Integer, x As Single, Y As Single)
  On Error Resume Next
  Call OnActivateControl
End Sub

Private Sub UserControl_ReadProperties(PropBag As PropertyBag)
  mModalPageUsage = PropBag.ReadProperty(pcModalPageUsage, False)
End Sub

Private Sub UserControl_Terminate()
  On Error Resume Next
  Set mUICallback = Nothing
  Call UnSubClass
  Set mPropSheet = Nothing
End Sub

Private Sub UserControl_WriteProperties(PropBag As PropertyBag)
  Call PropBag.WriteProperty(pcModalPageUsage, mModalPageUsage, False)
End Sub

' Callback ist wieder die erste Funktion, die gerufen wird und zugleich 
' auch die letzte (RHS = Nothing). Es wird der Rückverweis auf den 
' umschließenden Dialog, der dieses Control enthält übergeben.
Private Property Set IGeoComponentUI_Callback(ByVal RHS As TRiAS.IGeoComponentUICallback)

  Set mUICallback = RHS
End Property

' AllowNextPage wird gerufen, um abzufragen, ob der 'Weiter >' bzw. 'Fertigstellen'
' Button aktiviert werden soll oder nicht.
Private Property Get IGeoComponentUI_AllowNextPage() As Boolean

  IGeoComponentUI_AllowNextPage = True
End Property

' OnActivate wird gerufen: kurz bevor die Assistentenseite angezeigt werden soll
' (Activate = True) und kurz nachdem die Assistentenseite ausgebelndet worden
' ist (Activate = False)
Private Sub IGeoComponentUI_OnActivate(ByVal Activate As Boolean)

' Wenn die Assistentenseite angezeigt werden soll, muß das Nutzerinterface
' den aktuellen Gegebenheiten angepaßt werden. Daher der Aufruf von
' OnStatusChange. Dieser veranlaßt einen Aufruf unserer Funktion AllowNextPage
' und richtet entsprechend die Buttons des Assistenten.
' Im übrigen sollte OnStatusChange immer dann gerufen werden, wenn sich
' der Zustand unserer Assistentenseite geändert hat.
  If (Activate = True) Then
    mUICallback.OnStatusChange
  End If
  
End Sub

' OnBack wird gerufen, wenn die vorhergehende Seite angezeigt werden soll.
' False als Rückgabewert verhindert ein Umschalten.
Private Function IGeoComponentUI_OnBack() As Boolean

  IGeoComponentUI_OnBack = True
End Function

' OnNext wird gerufen, wenn die nächste Seite angezeigt werden soll bzw.
' der 'Fertigstellen' Button betätigt wurde (der Assistent wird geschlossen).
' False als Rückgabewert verhindert ein Umschalten.
Private Function IGeoComponentUI_OnNext() As Boolean

  IGeoComponentUI_OnNext = True
End Function

' Hier kommen alle Messages vorbei, die dieses Fenster betreffen. Am einfachsten
' ist es den Aufruf ungesehen an das Callback-Interface weiterzuleiten :-)
Private Function IGeoComponentUI_TranslateAccelerator(ByVal Wnd As Long, ByVal Msg As Long, _
  ByVal wParam As Long, ByVal lParam As Long, ByVal Time As Long, ByVal PosX As Long, _
  ByVal PosY As Long) As Boolean

  IGeoComponentUI_TranslateAccelerator = _
    mUICallback.TranslateAccelerator(Wnd, Msg, wParam, lParam, Time, PosX, PosY)
End Function

