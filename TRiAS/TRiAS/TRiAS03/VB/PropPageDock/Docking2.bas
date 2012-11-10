Attribute VB_Name = "SpeziellDocking2"
Option Explicit

Public Const G_COPYRIGHTYEAR = "2000 - 2002"

Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" _
  (pDest As Any, pSource As Any, ByVal ByteLen As Long)

Declare Function CallWindowProc Lib "user32" Alias _
  "CallWindowProcA" (ByVal wndrpcPrev As Long, ByVal hwnd As Long, _
  ByVal uMsg As Long, ByVal wParam As Long, lParam As Any) As Long

Public Const GWL_USERDATA = (-21)
Public Const GWL_WNDPROC = -4

Public Const GWL_STYLE = (-16)
Public Const GWL_EXSTYLE = (-20)

Public Const DS_CONTROL = &H400
Public Const WS_EX_CONTROLPARENT = &H10000

Public Const WM_USER = &H400
Public Const WM_SETFOCUS = 7

Public Const MSG_SETFOCUSTOCONTROL = WM_USER + 100

Declare Function SetFocusAPI Lib "user32" Alias "SetFocus" _
  (ByVal hwnd As Long) As Long

Declare Function SetParent Lib "user32" (ByVal hWndChild As Long, _
  ByVal hWndNewParent As Long) As Long

Declare Function ShowWindow Lib "user32" (ByVal hwnd As Long, _
  ByVal cmdShow As Long) As Long

Public Declare Function SetForegroundWindow Lib "user32" _
  (ByVal hwnd As Long) As Long

Declare Function SetWindowLong Lib "user32" Alias _
  "SetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long, _
  ByVal dwNewLong As Long) As Long
  
Declare Function GetWindowLong Lib "user32" Alias _
  "GetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long) As Long

Declare Function PostMessage Lib "user32" Alias "PostMessageA" _
  (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, _
  lParam As Long) As Long

Public Const pcModalPageUsage = "ModalPageUsage"
Public Const CStrValid = "1"
Public Sub SetAsParent(ByVal hwnd As Long)
  Call SetWindowLong(hwnd, GWL_STYLE, _
    GetWindowLong(hwnd, GWL_STYLE) Or DS_CONTROL)
End Sub

Public Property Get IsNothing(ByVal Objekt As Object) As Boolean
  IsNothing = Objekt Is Nothing
End Property
Public Property Get IsNotNothing(ByVal Objekt As Object) As Boolean
  IsNotNothing = Not (Objekt Is Nothing)
End Property

Function ResolveParaZahl(ByVal Standard As Long, _
    Optional ByVal NewLong As Variant, Optional ByVal NullStandard As Variant) As Long
  Dim Info As Long
  
  Info = Standard
  If Not IsMissing(NewLong) Then
    If Len(NewLong) > 0 Then 'vbnullstring!!
      If VarTypeZahl(NewLong) Then
        Info = NewLong
      End If
    End If
  End If
  If ResolveParaBoolean(False, NullStandard) And Info = 0 Then
    Info = Standard
  End If
  ResolveParaZahl = Info
End Function

Function ResolveParaBoolean(ByVal Standard As Boolean, Optional ByVal NewBool As Variant) As Boolean
  Dim Info As Boolean
  
  Info = Standard
  If Not IsMissing(NewBool) Then
    If Not VarTypeObj(NewBool) Then
      If Len(NewBool) > 0 Then 'vbnullstring!!
        If VarType(NewBool) = vbBoolean Then
          Info = NewBool
        Else
          If VarTypeZahl(NewBool) Then
            Info = CBool(NewBool)
          ElseIf VarType(NewBool) = vbString Then
            Info = NewBool = CStrValid
          End If
        End If
      End If
    End If
  End If
  ResolveParaBoolean = Info
End Function

Public Property Get VarTypeObj(NewObject As Variant) As Boolean
  VarTypeObj = (VarType(NewObject) = vbObject) Or (VarType(NewObject) = vbDataObject)
End Property

Public Property Get VarTypeZahl(ByVal Zahl As Variant) As Boolean
  Dim DerTyp As Long
  
  DerTyp = VarType(Zahl)
  VarTypeZahl = DerTyp = vbInteger Or DerTyp = vbLong Or _
    DerTyp = vbByte Or DerTyp = vbDouble Or DerTyp = vbSingle
End Property

Public Property Get VarTypeText(ByVal AText As Variant) As Boolean
  VarTypeText = VarType(AText) = vbString
End Property

Private Function DockCtrlFromhWnd(hwnd As Long) As PropPageDockControl
  Dim Form1 As PropPageDockControl
  Dim pObj As Long
  
  On Error Resume Next
  pObj = GetWindowLong(hwnd, GWL_USERDATA)
  CopyMemory Form1, pObj, 4
  Set DockCtrlFromhWnd = Form1
  CopyMemory Form1, 0&, 4
End Function

Public Function DockCtrlProc(ByVal hwnd As Long, ByVal uMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
  'Use a helper function to make sure that we actually hold
  'a reference count on the form until WindowProc returns.
  Dim ADock As PropPageDockControl
  
  On Error Resume Next
  
  If hwnd > 0 Then
    Set ADock = DockCtrlFromhWnd(hwnd)
    If IsNotNothing(ADock) Then
      DockCtrlProc = ADock.WindowProc(hwnd, uMsg, wParam, lParam)
    End If
  End If
End Function

