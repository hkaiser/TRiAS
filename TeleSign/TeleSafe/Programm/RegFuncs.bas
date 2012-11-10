Attribute VB_Name = "RegFuncs"
Option Explicit

Public Const HKEY_CLASSES_ROOT = &H80000000
Public Const HKEY_CURRENT_USER = &H80000001
Public Const HKEY_LOCAL_MACHINE = &H80000002
Public Const HKEY_USERS = &H80000003
Public Const HKEY_PERFORMANCE_DATA = &H80000004
Public Const HKEY_CURRENT_CONFIG = &H80000005
Public Const HKEY_DYN_DATA = &H80000006

Const ERROR_SUCCESS = 0&

Const REG_SZ = 1
Const REG_DWORD = 4

Private Declare Function RegCreateKey Lib "advapi32.dll" Alias "RegCreateKeyA" (ByVal hKey As Long, ByVal lpSubKey As String, phkResult As Long) As Long
Private Declare Function RegSetValue Lib "advapi32.dll" Alias "RegSetValueA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal dwType As Long, ByVal lpData As String, ByVal cbData As Long) As Long
Private Declare Function RegSetValueEx Lib "advapi32.dll" Alias "RegSetValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal Reserved As Long, ByVal dwType As Long, ByRef lpData As Any, ByVal cbData As Long) As Long
Private Declare Function RegQueryValue Lib "advapi32.dll" Alias "RegQueryValueA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal lpValue As String, ByVal lpcbValue As Long) As Long
Private Declare Function RegQueryValueEx Lib "advapi32.dll" Alias "RegQueryValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal lpReserved As Long, lpType As Long, lpData As Any, lpcbData As Long) As Long
Private Declare Function RegCloseKey Lib "advapi32.dll" (ByVal hKey As Long) As Long
Private Declare Function RegDeleteKey Lib "advapi32.dll" Alias "RegDeleteKeyA" (ByVal hKey As Long, ByVal lpSubKey As String) As Long
Private Declare Function RegDeleteValue Lib "advapi32.dll" Alias "RegDeleteValueA" (ByVal hKey As Long, ByVal lpValueName As String) As Long

'Private Declare Function GetWindowsDirectory Lib "kernel32" Alias "GetWindowsDirectoryA" (ByVal lpBuffer As String, ByVal nSize As Long) As Long

Public Function RegGetCommandDER() As String
 Dim regDER As String
    regDER = RegGetSTRING(HKEY_CLASSES_ROOT, ".DER", "", "")
    If Len(regDER) > 0 Then
        RegGetCommandDER = RegGetSTRING(HKEY_CLASSES_ROOT, regDER & "\shell\open\command", "", "")
    Else
        RegGetCommandDER = regDER
    End If
End Function
Public Function RegGetDWORD(lKey As Long, szKey As String, szValue As String, dwDefault As Long)
On Error GoTo Err_RegGetDWORD
Dim hKey As Long
Dim lpdwValue As Long
Dim lpcbValue As Long
    If ERROR_SUCCESS <> RegCreateKey(lKey, szKey, hKey) Then
        MsgBox "Unable to load registry entries!"
    Else
        lpcbValue = 4
        If ERROR_SUCCESS <> RegQueryValueEx(hKey, szValue, 0, REG_DWORD, lpdwValue, lpcbValue) Then
            RegGetDWORD = dwDefault
        Else
            RegGetDWORD = lpdwValue
        End If
        RegCloseKey hKey
    End If
Exit Function

Err_RegGetDWORD:
    MsgBox Err.Description
    Resume Next
End Function

Public Function RegGetSTRING(lKey As Long, szKey As String, szValue As String, szDefault As String)
On Error GoTo Err_RegGetSTRING
Dim hKey As Long
Dim lpszValue As String * 255
Dim lpcbValue As Long
    If ERROR_SUCCESS <> RegCreateKey(lKey, szKey, hKey) Then
        MsgBox "Unable to load registry entries!"
    Else
        lpcbValue = 255
        If ERROR_SUCCESS <> RegQueryValueEx(hKey, szValue, 0, REG_SZ, ByVal lpszValue, lpcbValue) Then
            RegGetSTRING = szDefault
        Else
            RegGetSTRING = Mid(lpszValue, 1, lpcbValue - 1)
        End If
        RegCloseKey hKey
    End If
Exit Function

Err_RegGetSTRING:
    MsgBox Err.Description
    Resume Next
End Function

Public Sub RegSetDWORD(lKey As Long, szKey As String, szValue As String, lpValue As Long)
On Error GoTo Err_RegSetDWORD
Dim hKey As Long
Dim lpcbValue As Long
    If ERROR_SUCCESS <> RegCreateKey(lKey, szKey, hKey) Then
        MsgBox "Unable to load registry entries!"
    Else
        lpcbValue = 4
        If ERROR_SUCCESS <> RegSetValueEx(hKey, szValue, 0, REG_DWORD, lpValue, lpcbValue) Then
            MsgBox "SetValueDWORD"
        End If
        RegCloseKey hKey
    End If
Exit Sub

Err_RegSetDWORD:
    MsgBox Err.Description
    Resume Next
End Sub

Public Sub RegSetSTRING(lKey As Long, szKey As String, szValue As String, lpValue As String)
On Error GoTo Err_RegSetSTRING
Dim hKey As Long
Dim lpcbValue As Long
    If ERROR_SUCCESS <> RegCreateKey(lKey, szKey, hKey) Then
        MsgBox "Unable to load registry entries!"
    Else
        lpcbValue = Len(lpValue)
        If ERROR_SUCCESS <> RegSetValueEx(hKey, szValue, 0, REG_SZ, ByVal lpValue, lpcbValue) Then
            MsgBox "SetValueSTRING"
        End If
        RegCloseKey hKey
    End If
Exit Sub

Err_RegSetSTRING:
    MsgBox Err.Description
    Resume Next
End Sub

