Attribute VB_Name = "DYNAZIP"
Option Explicit
'Additional flag bit for Encrypted Attribute
Global Const ATTR_ENCRYPT = &H8000&
Global Const ATTR_LFNAME = &H10000

' Multi-Volume Control FLAG definitions
'Global Const MV_FORMAT = &H1
'Global Const MV_LOWDENSE = &H2
'
'Global Const MV_WIPE = &H100
'Global Const MV_SUBDIR = &H200
'Global Const MV_SYSHIDE = &H400
'
'Global Const MV_CDFIRST = &H1000
'Global Const MV_USEMULTI = &H8000
'
'Global Const ZSO_RELATIVEPATHFLAG = &H1
'Global Const ZSO_MINORCANCEL = &H2
'Global Const ZSO_EXTERNALPROG = &H4
'Global Const ZSO_EXTPROGCANCEL = &H8
'Global Const ZSO_IGNORELONGNAMES = &H10
'Global Const ZSO_MANGLELONGNAMES = &H20
'Global Const ZSO_SKIPLOCKEDFILES = &H40
'Global Const ZSO_FORCEREMOVEABLE = &H80
'Global Const ZSO_LOGZIPRESULTS = &H100
'Global Const ZSO_JUST_ARCHIVED = &H200
'Global Const ZSO_RESET_ARCHIVED = &H400
'
'Global Const USO_OVERWRITE_RO = &H1
'Global Const USO_MINORCANCEL = &H2
'Global Const USO_EXTERNALPROG = &H4
'Global Const USO_EXTPROGCANCEL = &H8
'Global Const USO_IGNORELONGNAMES = &H10
'Global Const USO_MANGLELONGNAMES = &H20
'Global Const USO_FORCEREMOVEABLE = &H80
'Global Const USO_LOGZIPRESULTS = &H100

' Declarations used to gain access to Windows Functions

Declare Function SendMessage Lib "user32" Alias "SendMessageA" (ByVal hWnd As Long, ByVal wMsg As Long, ByVal wParam As Long, lParam As Long) As Long
Declare Function GetSystemMetrics Lib "user32" (ByVal nIndex As Long) As Long
Declare Function ShellExecute Lib "shell32.dll" Alias "ShellExecuteA" (ByVal hWnd As Long, ByVal lpOperation As String, ByVal lpFile As String, ByVal lpParameters As String, ByVal lpDirectory As String, ByVal nShowCmd As Long) As Long
Declare Function UpdateWindow Lib "user32" (ByVal hWnd As Long) As Long
' User Profile Routines
' NOTE: The lpKeyName argument for GetProfileString, WriteProfileString,
'       GetPrivateProfileString, and WritePrivateProfileString can be either
'       a string or NULL.  This is why the argument is defined as "As Any".
'          For example, to pass a string specify   ByVal "wallpaper"
'          To pass NULL specify                    ByVal 0&
'       You can also pass NULL for the lpString argument for WriteProfileString
'       and WritePrivateProfileString
Declare Function GetProfileInt Lib "kernel32" Alias "GetProfileIntA" (ByVal lpAppName As String, ByVal lpKeyName As String, ByVal nDefault As Long) As Long

Declare Function GetProfileString Lib "kernel32" Alias "GetProfileStringA" (ByVal lpAppName As String, ByVal lpKeyName As String, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long) As Long

Declare Function WriteProfileString Lib "kernel32" Alias "WriteProfileStringA" (ByVal lpszSection As String, ByVal lpszKeyName As String, ByVal lpszString As String) As Long


'------ Types needed for DynaZIP -------------------------------------------------------
Type VBSTATBLK
  hMinorStat As Long       'hWnd for the Minor Status Display
  hMajorStat As Long       'hWnd for the Major Status Display
  hResv1 As Long           'Reserved set to 0
  hResv2 As Long           'Reserved set to 0
End Type


Type ZIPINFO
  index As Integer
  oSize As Long
  cSize As Long
  cMethod As Integer
  cOption As Integer
  cPathType As Integer
  crc_32 As Long
  szDateTime As String * 18
  szFileName As String * 260
  attr As Long
  lziResv1 As Long
  lziResv2 As Long
End Type


Type VBDZIPBLOCK
  szZIPFile As String * 260
  szItemList As String * 5120
  szTempPath As String * 260
  szComment As String * 2048
  szDate As String * 7
  szIncludeFollowing As String * 2048
  szExcludeFollowing As String * 2048
  szStoreSuffixes As String * 1024
  szEncryptCode As String * 66
  'Added for Rev 3
  szExtProgTitle As String * 260

End Type

Type VBDUNZIPBLOCK
  szZIPFile  As String * 260
  szFileSpec  As String * 5120
  szDestination  As String * 260
  szReturnString  As String * 2048
  szDecryptCode As String * 66
  'Added for Rev 3
  szExtProgTitle As String * 260
End Type

Type ZIPCMDSTRUCT
  zipStructSize As Long                     'INT in "C"
  function As Long                          'INT in "C"
  lpszZIPFile As Long                       'LPSTR in "C"
  lpszItemList As Long                      'LPSTR in "C"
  lpMajorStatus As Long                     'FARPROC in "C"
  lpMajorUserData As Long                   'void far * in "C"
  lpMinorStatus As Long                     'FARPROC in "C"
  lpMinorUserData As Long                   'void far * in "C"
  dosifyFlag As Long                        'BOOL in "C"
  recurseFlag As Long                       'BOOL in "C"
  compFactor As Long                        'INT in "C"
  quietFlag As Long                         'BOOL in "C"
  pathForTempFlag As Long                   'BOOL in "C"
  lpszTempPath As Long                      'LPSTR in "C"
  FixFlag As Long                           'BOOL in "C"
  fixHarderFlag As Long                     'BOOL in "C"
  includeVolumeFlag As Long                 'BOOL in "C"
  deleteOriginalFlag As Long                'BOOL in "C"
  growExistingFlag As Long                  'BOOL in "C"
  noDirectoryNamesFlag As Long              'BOOL in "C"
  convertLFtoCRLFFlag As Long               'BOOL in "C"
  addCommentFlag As Long                    'BOOL in "C"
  lpszComment As Long                       'LPSTR in "C"
  afterDateFlag As Long                     'BOOL in "C"
  lpszDate As Long                          'LPSTR in "C"
  oldAsLatestFlag As Long                   'BOOL in "C"
  includeOnlyFollowingFlag As Long          'BOOL in "C"
  lpszIncludeFollowing As Long              'LPSTR in "C"
  excludeFollowingFlag As Long              'BOOL in "C"
  lpszExcludeFollowing As Long              'LPSTR in "C"
  noDirectoryEntriesFlag As Long            'BOOL in "C"
  includeSysHiddenFlag As Long              'BOOL in "C"
  dontCompressTheseSuffixesFlag As Long     'BOOL in "C"
  lpszStoreSuffixes As Long                 'LPSTR in "C"
  bDiagnostic As Long                       'BOOL in "C"
  encryptFlag As Long                       'BOOL in "C"
  lpszEncryptCode As Long                   'LPSTR in "C"
  lpMessageDisplay As Long                  'FARPROC in "C"
  lpMessageDisplayData As Long              'void far * in "C"
  wMultiVolControl As Integer               'WORD in "C"
  wZipSubOptions As Integer                 'WORD in "C"

  ' added for rev 3.00
  lResv1 As Long                            ' LONG in "C"
  lResv2 As Long                            ' LONG in "C"
  lpRenameProc As Long                      ' FARPROC in "C"
  lpRenameUserData As Long                  ' void far * in "C"
  lpszExtProgTitle As Long                  ' LPSTR in "C"
  lpMemBlock As Long                        ' void far * in "C"
  lMemBlockSize As Long                     ' LONG in "C"

End Type
Type UNZIPCMDSTRUCT
  unzipStructSize As Long        ' INT in "C"
  function As Long               ' INT in "C"
  lpszZIPFile As Long            ' LPSTR in "C"
  zInfo As Long                  ' ZIPINFO far * in "C"
  lpszFilespec As Long           ' LPSTR in "C"
  index  As Long                 ' INT in "C"
  lpszDestination As Long        ' LPSTR in "C"
  freshenFlag As Long            ' BOOL in "C"
  updateFlag As Long             ' BOOL in "C"
  overWriteFlag As Long          ' BOOL in "C"
  quietFlag As Long              ' BOOL in "C"
  testFlag As Long               ' BOOL in "C"
  noDirectoryNamesFlag As Long   ' BOOL in "C"
  recurseFlag As Long            ' BOOL in "C"
  noDirectoryItemsFlag As Long   ' BOOL in "C"
  lpMinorStatus As Long          ' FARPROC in "C"
  lpMinorUserData As Long        ' void far * in "C"
  lpMajorStatus As Long          ' FARPROC in "C"
  lpMajorUserData As Long        ' void far * in "C"
  returnCount As Long            ' INT in "C"
  lpszReturnString As Long       ' LPSTR in "C"
  bDiagnostic As Long            ' BOOL in "C"
  bLF2CRLFFlag As Long           ' BOOL in "C"
  decryptFlag As Long            ' BOOL in "C"
  lpszDecryptCode As Long        ' LPSTR in "C"
  lpMessageDisplay As Long       ' FARPROC in "C"
  lpMessageDisplayData As Long   ' void far * in "C"
  wUnzipSubOptions As Integer    ' WORD in "C"

  ' added for rev 3.00
  lResv1 As Long                 ' LONG in "C"
  lResv2 As Long                 ' LONG in "C"
  lpRenameProc As Long           ' FARPROC in "C"
  lpRenameUserData As Long       ' void far * in "C"
  lpszExtProgTitle As Long       ' LPSTR in "C"
  lpMemBlock As Long             ' void far * in "C"
  lMemBlockSize As Long          ' LONG in "C"
  lStartingOffset As Long        ' LONG in "C"

End Type


' the "function"s that are supported for unzipping
Global Const UNZIP_COUNTALLZIPMEMBERS = 1
Global Const UNZIP_GETNEXTZIPINFO = 2
Global Const UNZIP_COUNTNAMEDZIPMEMBERS = 3
Global Const UNZIP_GETNEXTNAMEDZIPINFO = 4
Global Const UNZIP_GETCOMMENTSIZE = 5
Global Const UNZIP_GETCOMMENT = 6
Global Const UNZIP_GETINDEXEDZIPINFO = 7
Global Const UNZIP_EXTRACT = 8
Global Const UNZIP_FILETOMEM = 9

'error codes returned for unzipping
Global Const UE_OK = 0                ' success
Global Const UE_EOF = 2               ' unexpected end of zip file
Global Const UE_STRUCT = 3            ' structure error in zip file
Global Const UE_MEM1 = 4              ' out of memory
Global Const UE_MEM2 = 5              ' out of memory
Global Const UE_NOFILE = 9            ' file not found error
Global Const UE_BORED = 11            ' nothing to do
Global Const UE_SAMEVOL = 12          ' same volume
Global Const UE_INDEX = 25            ' index out of bounds
Global Const UE_OUTPUT = 28           ' error creating output file
Global Const UE_OPEN = 29             ' error opening output file
Global Const UE_BADCRC = 39           ' crc error
Global Const UE_ABORT = 40            ' Application canceled operation
Global Const UE_ENCRYPT = 41          ' file skipped, encrypted
Global Const UE_UNKNOWN = 42          ' unknown compression method
Global Const UE_BADKEY = 44           ' Bad or missing decrypt code
Global Const UE_BUSY = 45         ' Busy, can't enter now
Global Const UE_NOVOL = 46            ' can't unzip a volume item
Global Const UE_CMDERR = 47           ' bad command structure
Global Const UE_CANCEL = 48           ' user cancelled this operation
Global Const UE_SKIP = 49             ' user skipped this operation
Global Const UE_DISKFULL = 50         ' disk full


' the "function"s that are supported for zipping
Global Const ZIP_FRESHEN = 1
Global Const ZIP_DELETE = 2
Global Const ZIP_UPDATE = 3
Global Const ZIP_ADD = 4
Global Const ZIP_MEMTOFILE = 5

' Error return values for zipping.  The values 0..4 and 12..18 follow the conventions
'   of PKZIP.   The values 4..10 are all assigned to "insufficient memory"
'   by PKZIP, so the codes 5..10 are used here for other purposes.

Global Const ZE_MISS = -1             'used by procname(), zipbare()
Global Const ZE_OK = 0                'success
Global Const ZE_EOF = 2               'unexpected end of zip file
Global Const ZE_FORM = 3              'zip file structure error
Global Const ZE_MEM = 4               'out of memory
Global Const ZE_LOGIC = 5             'internal logic error
Global Const ZE_BIG = 6               'entry too large to split
Global Const ZE_NOTE = 7              'invalid comment format
Global Const ZE_TEST = 8              'zip test (-T) failed or out of memory
Global Const ZE_ABORT = 9             'user interrupt or termination
Global Const ZE_TEMP = 10             'error using a temp file
Global Const ZE_READ = 11             'read or seek error
Global Const ZE_NONE = 12             'nothing to do
Global Const ZE_NAME = 13             'missing or empty zip file
Global Const ZE_WRITE = 14            'error writing to a file
Global Const ZE_CREAT = 15            'couldn't open to write
Global Const ZE_PARMS = 16            'bad command line
Global Const ZE_INCOMPLETE = 17       'Could Not Complete Operation
Global Const ZE_OPEN = 18             'could not open a specified file to read
Global Const ZE_MEDIA = 19            'Media error or HW failure
Global Const ZE_MVPARMS = 20          'Invalid combination of control parameters
Global Const ZE_MVUSAGE = 21          'Improper use of a Multi-Volume Zip file

Global zi As ZIPINFO
Global zcs As ZIPCMDSTRUCT
Global ucs As UNZIPCMDSTRUCT
Global vbdzBlk As VBDZIPBLOCK
Global vbduzBlk As VBDUNZIPBLOCK
Global statusBlk As VBSTATBLK
Global UNZIPerrors(51) As String
Global ZIPerrors(51) As String

' The following variables are used to display ZIPPING and UNZIPPING status
Global szStatus1 As String
Global szStatus2 As String

'The following variables are used to keep track of current conditions
'Global szGlobalDest As String
'Global szTempDir As String
'Global szDefaultViewer As String
'Global szInitialDir As String
'Global szDefaultZIPDir As String
'Global szDefaultSourceDir As String
'Global szLastInputFileDir As String
'Global szINITemp As String * 260

'The following variables are used to record the options selected by the user
Global bOverwriteWarn As Integer     'BOOL in "C" Code
Global bDeleteWarn As Integer        'BOOL in "C" Code
Global bOverwriteRO As Integer       'BOOL in "C" Code
Global bSavePaths As Integer         'BOOL in "C" Code
Global bUseTempDir As Integer        'BOOL in "C" Code
Global bAppendPaths As Integer       'BOOL in "C" Code
Global iZIPCompLevel As Integer      'INT  in "C" Code
Global bDeleteAfterZIP As Integer    'BOOL in "C" Code
Global bLF2CRLF As Integer           'BOOL in "C" Code
Global winPosUpLeftX As Integer      'INT in "C"
Global winPosUpLeftY As Integer      'INT in "C"
Global bENCRYPT As Integer           'INT in "C"
Global bIncludeSysHide As Integer    'BOOL in 'C'
Global bFormatVolume As Integer      'BOOL in 'C'
Global bLowDensity As Integer        'BOOL in 'C'
Global bPlaceCDFirst As Integer      'BOOL in 'C'
Global bWipeVolume As Integer        'BOOL in 'C'
Global bWipeSubDirs As Integer       'BOOL in 'C'
Global bWipeSysHidden As Integer     'BOOL in 'C'


'The following declaration describes the Visual Basic DLL Function that
'fills in the ucs structure with the appropriate far pointers and far references
'that are required by the "C" version interface in the DynaZip UNZIP DLL
'INPUTS:
'  ucs          FAR PTR to an UNZIPCMDSTRUCT structure that will be used by the DLL
'  vbduzBlk       FAR PTR to a VBDUNZIPBLOCK structure containing properly initialized data
'  ZI           FAR PTR to a ZIPINFO structure that will be used by the DLL
'  StatBlk      FAR PTR to a ZIP Status Structure containing handles for the Minor and major status
'
'OUTPUTS:
'  ucs          Structure members filled in with return information from the DLL side
'
'RETURNS:
'  A Long Value with an error code
'
'ASSUMPTIONS:
'  All Strings must be fixed length and can NOT be moved in memory during the Status CALLBACKS
'  All Data Items must not be moved during the Status CALLBACKS
'
Declare Function dunzipVB Lib "dunzip32.dll" (ucs As UNZIPCMDSTRUCT, vbduzBlk As VBDUNZIPBLOCK, zi As ZIPINFO, statBlk As VBSTATBLK) As Integer
'--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
'The following declaration describes the Visual Basic DLL Function that
'fills in the zcs structure with the appropriate far pointers and far references
'that are required by the "C" version interface in the DynaZip ZIP DLL
'INPUTS:
'  zcs          FAR PTR to an ZIPCMDSTRUCT structure that will be used by the DLL
'  vbdzBlk      FAR PTR to a VBDZIPBLOCK structure containing properly initialized data
'  StatBlk      FAR PTR to a ZIP Status Structure containing handles for the Minor and major status
'
'OUTPUTS:
'  ucs          Structure members filled in with return information from the DLL side
'
'RETURNS:
'  A Long Value with an error code
'
'ASSUMPTIONS:
'  All Strings must be fixed length and can NOT be moved in memory during the Status CALLBACKS
'  All Data Items must not be moved during the Status CALLBACKS
'
'Declare Function dzipVB Lib "dzip32.dll" (zcs As ZIPCMDSTRUCT, vbdzBlk As VBDZIPBLOCK, statBlk As VBSTATBLK) As Integer
Declare Function dzipVB Lib "dzip32.dll" (zcs As Any, vbdzBlk As Any, statBlk As Any) As Integer
'--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Function zipFileToFile(strSourceFileName As String, strDestinationFileName As String) As Long
On Error GoTo Err_zipFile
 Dim hResult As Long
 Dim zi As ZIPINFO
 Dim zcs As ZIPCMDSTRUCT
 Static vbdzBlk As VBDZIPBLOCK
 Dim statusBlk As VBSTATBLK
    Call initZIPCmdStruct(zcs)

    zcs.compFactor = 9
    zcs.function = ZIP_ADD
'    zcs.wZipSubOptions = USO_EXTERNALPROG               'Statusmonitor
    
    vbdzBlk.szZIPFile = strDestinationFileName
    vbdzBlk.szItemList = strSourceFileName
'    vbdzBlk.szExtProgTitle = "EDBS_ZIP Status"
    hResult = dzipVB(zcs, vbdzBlk, statusBlk)
  
    If hResult <> ZE_OK Then
        InitErrorStrings
        MsgBox "ZIP error: " & ZIPerrors(hResult), vbOK + vbInformation, "EDBS_ZIP-Warnung"
    End If
    zipFileToFile = hResult
Exit Function

Err_zipFile:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
End Function

Function UnzipFileFromFile(strSourceFileName As String, strDestinationFileName As String) As Long
On Error GoTo Err_unzipFileFromFile
Dim hResult As Long
Static vbduzBlk As VBDUNZIPBLOCK
Static zi As ZIPINFO
Static ucs As UNZIPCMDSTRUCT
    Call initUNZIPCmdStruct(ucs)
    vbduzBlk.szZIPFile = strSourceFileName
    ucs.function = UNZIP_COUNTALLZIPMEMBERS
    statusBlk.hMinorStat = 0
    statusBlk.hMajorStat = 0
    hResult = dunzipVB(ucs, vbduzBlk, zi, statusBlk)
    If (hResult <> 0) Then
      MsgBox vbduzBlk.szZIPFile & "is an invalid Zip file, operation aborted!", vbExclamation, "Dynazip Alert"
      hResult = -1
    End If
'    ElseIf 1 <> ucs.returnCount Then
'        hResult = -1
    If hResult = 0 Then
        Do
            ucs.function = UNZIP_GETNEXTZIPINFO
            statusBlk.hMinorStat = 0
            statusBlk.hMajorStat = 0
            hResult = dunzipVB(ucs, vbduzBlk, zi, statusBlk)
        Loop Until (hResult <> 0) Or (0 = (zi.attr And &H10))
        If hResult = 0 Then
                
            Call initUNZIPCmdStruct(ucs)
            ucs.function = UNZIP_EXTRACT       'EXTRACT files from the ZIP file
            ucs.noDirectoryItemsFlag = True
            ucs.noDirectoryNamesFlag = True
'           ucs.wUnzipSubOptions = USO_EXTERNALPROG
            ucs.overWriteFlag = True

            vbduzBlk.szZIPFile = strSourceFileName
            vbduzBlk.szFileSpec = StripTerminator(zi.szFileName)
            If zi.cPathType = 1 Then
                Do Until InStr(vbduzBlk.szFileSpec, "/") = 0
                    vbduzBlk.szFileSpec = Mid(vbduzBlk.szFileSpec, 2)
                Loop
            End If
            vbduzBlk.szDestination = GetTempDirName & "ZEDBS\"
'           vbduzBlk.szExtProgTitle = "Unzip Status"
            strDestinationFileName = Trim(vbduzBlk.szDestination) & Trim(vbduzBlk.szFileSpec)
            hResult = dunzipVB(ucs, vbduzBlk, zi, statusBlk)
        End If
    End If
    UnzipFileFromFile = hResult
Exit Function

Err_unzipFileFromFile:
    MsgBox "Fehler" & Str(Err.Number) & ": " & Err.Description
    Resume Next
  
End Function

'Sub addNewFiles()
'  Dim zcs As ZIPCMDSTRUCT
'  Dim Response As Integer
'  Dim bufflen As Long
'  Dim szFileToZip As String
'  Dim szFileList As String, szItemList As String
'  Dim addedCount As Integer
'  Dim szNew1 As String, szNew2 As String
'  Dim szTemp As String
'  Dim bMultiFile As Boolean
'  Dim itemCount As Integer
'  Dim pos As Integer
'  Dim pos1 As Integer
'  Dim szPath As String
'  bufflen = 5119&
'
'  'Initialize the command structure
'  Call initZIPCmdStruct(zcs)
''  vbdzBlk.szZIPFile = DYNAZIPFORM1!IDE_ZIPFILENAME.Text
'  Response = ZE_OK
'
''  i = getMultiFileName(DYNAZIPFORM1.hWnd, szFileList, bufflen)
'  addedCount = 0
'  If Len(szFileList) = 0 Then
'    Exit Sub
'  End If
'
'  If bDeleteAfterZIP Then
'
'    szTemp = "You are about to delete the selected file<s> after zipping.  Is this what you want to do?"
'    Response = MsgBox(szTemp, MB_ICONQUESTION + MB_OKCANCEL, "DynaZIP Alert")
'
'    If Response = 0 Then
'      Exit Sub
'    End If
'
'  End If
'
'
'  ' check to see whether it's one or multiple files
'  bMultiFile = False
'  If InStr(szFileList, " ") <> 0 Then
'    bMultiFile = 1
'  End If
'
'  preserveStatusBars
'
'    If bMultiFile Then
'        ' we're doing more than one file
'        ' how many items in the list
'        itemCount = 0
'        pos = 1
'        Do While pos <> 0
'            pos = InStr(pos, szFileList, " ")
'            If pos <> 0 Then
'                itemCount = itemCount + 1
'                pos = pos + 1
'            End If
'        Loop
'
'        ' we have a string now in the form "path file1 file2 ... file(n)"
'        ' get a copy of the path
''???????        lpszTemp = lpszLargeFileList
'        szPath = Left$(szFileList, InStr(1, szFileList, " ") - 1)
'        If right$(szPath, 1) <> "\" Then
'            szPath = szPath & "\"
'        End If
'
'
'        ' now, prepare the item list for the selected files, one at a time
'        pos = 1
'        Do While pos <> 0
'            'go till all of the filenames have been used
'
'            'pos and pos1 bracket the filename part to be used
'            pos = InStr(pos, szFileList, " ")
'
'            ' See if we have a file to ZIP
'            If pos <> 0 Then
'                pos = pos + 1
'                pos1 = InStr(pos, szFileList, " ")
'                If pos1 = 0 Then
'                    pos1 = Len(szFileList) + 1
'                End If
'                'get the path if any
'                szFileToZip = szPath
'                szTemp = Mid$(szFileList, pos, pos1 - pos)
'                ' get the file name portion
'                szFileToZip = szFileToZip & szTemp
'                If Len(szTemp) <> 0 Then
'                    ' presuming we do have a file to zip
'                    szFileToZip = UCase$(szFileToZip)
'                    If (StrComp(vbdzBlk.szZIPFile, szFileToZip) = 0) Then
'                        szNew1 = "You are trying to add " & szFileToZip & " to itself, which is not permitted.  Skipping this item..."
'                        MsgBox szNew1, MB_ICONEXCLAMATION + MB_OK, "Dynazip Alert"
'                    Else
'                        If Len(szItemList) <> 0 Then
'                            szItemList = szItemList & " "
'                        End If
'
'                        szItemList = szItemList & szFileToZip
'                        addedCount = addedCount + 1
'                    End If
'                End If
'            End If
'        Loop
'
'    Else
'        'we're doing only one file
'        addedCount = 0
'        szNew2 = "Adding 1 item"
'        Call SetStatus(2, 0, szNew2)
'        szFileList = UCase$(szFileList)
'        If (StrComp(vbdzBlk.szZIPFile, szFileList) = 0) Then
'            szNew1 = "You are trying to add " & szFileToZip & " to itself, which is not permitted.  Skipping this item..."
'            MsgBox szNew1, MB_ICONEXCLAMATION + MB_OK, "Dynazip Alert"
'        Else
'            szItemList = szFileList
'            addedCount = addedCount + 1
'        End If
'    End If
'    If addedCount <> 0 Then
'        'now we're ready to zip the group
'        zcs.noDirectoryNamesFlag = Not bSavePaths
'        zcs.deleteOriginalFlag = bDeleteAfterZIP
'        zcs.compFactor = iZIPCompLevel
'        zcs.function = ZIP_ADD
'        If bUseTempDir Then
'            zcs.pathForTempFlag = 1
'            vbdzBlk.szTempPath = szTempDir
'            ' let's check if the directory exists, if not, create it
'            szTempDir = LCase$(szTempDir)
'On Error Resume Next
'            ChDrive szTempDir
'            ChDir szTempDir
'            If (LCase$(CurDir$) <> szTempDir) Then
'                'We could not change to the temporary directory
'                szTemp = "The currently set temporary directory <" & szTempDir & "> does not exist.  Do you want to create it?"
'                Response = MsgBox(szTemp, MB_YESNO + MB_ICONQUESTION, "DynaZIP Alert")
'                If Response = IDNO Then
'                    'User decided to not make a new directory
'                    Exit Sub
'                Else
'                    'User wants to make the directory
'                    MkDir szTempDir
'                    ChDir szTempDir
'                    ChDrive szTempDir
'                    If LCase$(CurDir$) <> szTempDir Then
'                    szTemp = "Could not create Temporary Directory <" & szTempDir & ">. Operation cancelled."
'                    MsgBox szTemp, MB_OK, "DynaZIP Alert"
'                    Exit Sub
'                End If
'            End If
'        End If
'On Error GoTo 0
'    End If
'    szNew2 = "Adding " & Format$(addedCount) & "Item(s)"
'    Call SetStatus(2, 0, szNew2)
''    DYNAZIPFORM1!IDE_ZIPFILENAME.Text = vbdzBlk.szZIPFile
''    UpdateWindow (DYNAZIPFORM1!IDE_ZIPFILENAME.hWnd)
'    zcs.convertLFtoCRLFFlag = bLF2CRLF
'    ' here's where the actual zipping takes place
'    vbdzBlk.szItemList = szItemList
'    statusBlk.hMinorStat = 0
'    statusBlk.hMajorStat = 0
'    zcs.encryptFlag = bENCRYPT
'    If bENCRYPT Then
''      vbdzBlk.szEncryptCode = DYNAZIPFORM1!IDC_ENCRYPTCODE.Text
'    End If
'    Call initZCSMultiVol(zcs)
'    Response = dzipVB(zcs, vbdzBlk, statusBlk)
'  End If
'
'  If Response <> ZE_OK Then
'    szTemp = "ZIP error: " & ZIPerrors(Response)
'    MsgBox szTemp, MB_OK + MB_ICONINFORMATION, "DynaZIP Alert"
'  End If
'  restoreStatusBars
'  If addedCount <> 0 Then
'    'something was added, we need to update the item list
'    pos = fillInZIPInfo()
'  End If
'End Sub
'
'Sub ClearStatus1()
''  DYNAZIPFORM1!Status1.Text = ""
'End Sub
'
'Sub ClearStatus2()
''  DYNAZIPFORM1!Status2.Text = ""
'
'End Sub
'
'Sub createNewZIP()
'  Dim szTemp As String
'  szTemp = ""
'On Error GoTo ErrOpen
'  CMDSAVE!CMDSaveAsFile.Filter = "ZIP Files (*.ZIP)|*.ZIP|All Files (*.*)|*.*"
'  CMDSAVE!CMDSaveAsFile.FilterIndex = 0
'  CMDSAVE!CMDSaveAsFile.Action = 2
'  vbdzBlk.szZIPFile = CMDSAVE!CMDSaveAsFile.FileName
'  DYNAZIPFORM1!IDE_ZIPFILENAME.Text = CMDSAVE!CMDSaveAsFile.FileName
'  DYNAZIPFORM1!IDC_FILELIST.Clear
'  addNewFiles
'  If DYNAZIPFORM1!IDC_FILELIST.ListCount = 0 Then
'    vbdzBlk.szZIPFile = ""
'    i = fillInZIPInfo()
'    DYNAZIPFORM1!IDB_ADDFILES.Enabled = False
'    ClearStatus1
'    ClearStatus2
'  Else
'    DYNAZIPFORM1!IDB_ADDFILES.Enabled = True
'  End If
'  Exit Sub
'
'ErrOpen:
'  Exit Sub
'
'End Sub
'
'Sub deleteSelectedFiles()
'  Static szLargeFileList As String
'  Static selcount As Integer
'  Static i As Integer
'  Static totalItems As Integer
'  Static pos As Integer
'  Static szNew1 As String
'  Static szNew2 As String
'  Static attrib As Integer
'  Static Response As Integer
'  Static deletedCount As Integer
'  Static szTemp As String
'
'  ' initialize the ZIP and UNZIP command structures
'  Call initZIPCmdStruct(zcs)
'  Call initUNZIPCmdStruct(ucs)
'
'  ' set up for the output file name
'  vbdzBlk.szZIPFile = DYNAZIPFORM1!IDE_ZIPFILENAME.Text
'
'  selcount = GetLBSelCount(DYNAZIPFORM1!IDC_FILELIST)
'  totalItems = DYNAZIPFORM1!IDC_FILELIST.ListCount
'  deletedCount = 0   ' nothing's been deleted yet
'
'  If (selcount = 0) Or (totalItems = 0) Then
'    ' There's something amiss
'    Exit Sub
'  End If
'  vbduzBlk.szZIPFile = DYNAZIPFORM1!IDE_ZIPFILENAME.Text
'  ucs.function = UNZIP_COUNTALLZIPMEMBERS
'  Response = dunzipVB(ucs, vbduzBlk, zi, statusBlk)
'  If Response <> ZE_OK Then
'    szTemp = "ZIP error: " & ZIPerrors(Response)
'    MsgBox szTemp, MB_OK + MB_ICONINFORMATION, "DynaZIP Alert"
'    Exit Sub
'  End If
'  If selcount = ucs.returnCount Then
'    szNew1 = "You have selected all of the items in ZIP File " & DYNAZIPFORM1!IDE_ZIPFILENAME.Text & ". Do you want to delete this ZIP file from your disk?"
'    Response = MsgBox(szNew1, MB_ICONQUESTION + MB_YESNOCANCEL, "DynaZIP Alert")
'    If Response = IDCANCEL Then
'      Exit Sub
'    Else
'      If Response = IDYES Then
'  On Error GoTo FileErrorHandler
'  Kill DYNAZIPFORM1!IDE_ZIPFILENAME.Text
'  On Error GoTo 0
'
'  DYNAZIPFORM1!IDE_ZIPFILENAME.Text = ""
'  i = fillInZIPInfo()
'  DYNAZIPFORM1!IDB_ADDFILES.Enabled = False
'  Exit Sub
'      End If
'    End If
'  End If
'  preserveStatusBars
'  ' build the string to be used for the delete operation
'  szLargeFileList = ""
'  For i = 0 To totalItems - 1 Step 1
'    If DYNAZIPFORM1!IDC_FILELIST.Selected(i) Then
'      ucs.function = UNZIP_GETINDEXEDZIPINFO
'      vbduzBlk.szZIPFile = DYNAZIPFORM1!IDE_ZIPFILENAME.Text
'      ucs.index = i
'      If dunzipVB(ucs, vbduzBlk, zi, statusBlk) = UE_OK Then
'  'check for valid item
'  Response = IDYES
'  If bDeleteWarn Then
'    szNew1 = "You are about to delete " & zi.szFileName & " from ZIP File " & vbduzBlk.szZIPFile & ". Is this what you want to do?"
'    Response = MsgBox(szNew1, MB_ICONQUESTION + MB_YESNOCANCEL, "DynaZIP Alert")
'  End If
'  If Response = IDCANCEL Then
'    Exit For
'  Else
'    If Response = IDYES Then
'      szTemp = Left$(zi.szFileName, InStr(zi.szFileName, Chr$(0)) - 1)
'      szLargeFileList = szLargeFileList & Chr$(34) & szTemp & Chr$(34) & " "
'      deletedCount = deleteCount + 1
'    End If
'  End If
'      End If
'    End If
'  Next i
'  If deletedCount <> 0 Then
'    ' now we're ready to delete the group
'    ' get rid of the ' ' at the end of the list (if any)
'    szLargeFileList = Left$(szLargeFileList, Len(szLargeFileList) - 1)
'    ' get handles to the two status bar controls
'    statusBlk.hMinorStat = 0
'    statusBlk.hMajorStat = 0
'    vbdzBlk.szItemList = szLargeFileList
'    szNew2 = "Deleting " & Format$(deletedCount) & " item(s)"
'    Call SetStatus(2, 0, szNew2)
'    DYNAZIPFORM1!IDE_ZIPFILENAME.Text = vbdzBlk.szZIPFile
'    UpdateWindow (DYNAZIPFORM1!IDE_ZIPFILENAME.hWnd)
'    zcs.function = ZIP_DELETE
'    ' here's where the actual deleting takes place
'    Call initZCSMultiVol(zcs)
'    Response = dzipVB(zcs, vbdzBlk, statusBlk)
'
'  End If
'  If Response <> ZE_OK Then
'    szTemp = "ZIP error: " & ZIPerrors(Response)
'    MsgBox szTemp, MB_OK + MB_ICONINFORMATION, "DynaZIP Alert"
'  End If
'
'  ' Make sure the user sees 100%
'  szTemp = DYNAZIPFORM1!Status2.Text
'  Call SetStatus(2, 100, szTemp)
'
'  restoreStatusBars
'  If deletedCount <> 0 Then
'    ' something was deleted, we need to update the item list
'    i = fillInZIPInfo()
'  End If
'  Exit Sub
'
'FileErrorHandler:
'  szNew1 = "File " & DYNAZIPFORM1!IDE_ZIPFILENAME.Text & " could not be deleted!"
'  MsgBox szNew1, MB_ICONASTERISK + MB_OK, "Dynazip Alert"
'  Exit Sub
'
'End Sub
'
'Sub executeFile()
'  Dim selcount As Integer, cursel As Integer
'  Dim szExeName As String
'  Dim szTemp As String
'  Dim j As Integer, errorval As Integer, Response As Integer
'  Dim ucs As UNZIPCMDSTRUCT
'
'  selcount = GetLBSelCount(DYNAZIPFORM1!IDC_FILELIST)
'
'  If selcount <> 1 Then
'    Exit Sub
'  End If
'  If Len(szTempDir) <= 2 Then
'    'Append a backslash to the probable drive and colon
'    szTempDir = szTempDir & "\"
'  End If
'  szTempDir = LCase$(szTempDir)
'  On Error Resume Next
'  ChDrive szTempDir
'  ChDir szTempDir
'  If (LCase$(CurDir$) <> szTempDir) Then
'    'We could not change to the temporary directory
'    szTemp = "The currently set temporary directory <" & szTempDir & "> does not exist.  Do you want to create it?"
'    Response = MsgBox(szTemp, MB_YESNO + MB_ICONQUESTION, "DynaZIP Alert")
'    If Response = IDNO Then
'      'User decided to not make a new directory
'      Exit Sub
'    Else
'      'User wants to make the directory
'      MkDir szTempDir
'      ChDir szTempDir
'      ChDrive szTempDir
'      If LCase$(CurDir$) <> szTempDir Then
'  szTemp = "Could not create Temporary Directory <" & szTempDir & ">. Operation cancelled."
'  MsgBox szTemp, MB_OK, "DynaZIP Alert"
'  Exit Sub
'      End If
'    End If
'  End If
'  cursel = DYNAZIPFORM1!IDC_FILELIST.ListIndex
'  Call initUNZIPCmdStruct(ucs)
'  vbduzBlk.szZIPFile = DYNAZIPFORM1!IDE_ZIPFILENAME.Text
'  vbduzBlk.szDestination = szTempDir
'  ucs.index = cursel
'  statusBlk.hMinorStat = 0
'  statusBlk.hMajorStat = 0
'  ucs.function = UNZIP_GETINDEXEDZIPINFO
'  If dunzipVB(ucs, vbduzBlk, zi, statusBlk) = UE_OK Then
'    szTempDir = SlashesToBackSlashes(szTempDir)
'    szExeName = szTempDir
'    If right$(szExeName, 1) <> "\" Then
'      szExeName = szExeName & "\"
'    End If
'    szTemp = ExtractFileName(zi.szFileName)
'    szExeName = szExeName & szTemp
'    Call initUNZIPCmdStruct(ucs)
'    vbduzBlk.szZIPFile = DYNAZIPFORM1!IDE_ZIPFILENAME.Text
'    vbduzBlk.szDestination = szTempDir
'    ucs.index = cursel
'    ucs.overWriteFlag = 1
'    ucs.quietFlag = 1
'    ucs.function = UNZIP_EXTRACT
'    ucs.bLF2CRLFFlag = bLF2CRLF
'    ucs.decryptFlag = bENCRYPT
'    If bENCRYPT Then
'      vbduzBlk.szDecryptCode = DYNAZIPFORM1!IDC_ENCRYPTCODE.Text
'    End If
'    statusBlk.hMinorStat = 0
'    statusBlk.hMajorStat = 0
'    errorval = dunzipVB(ucs, vbduzBlk, zi, statusBlk)
'    If errorval = 0 Then
'      If ShellExecute(DYNAZIPFORM1.hWnd, ByVal "open", szExeName, 0&, szTempDir, SW_SHOW) < 32 Then
'  Response = MsgBox("This file can not be executed, and has no program associated with it.  Do you want to run the default viewer to display it?", MB_OKCANCEL + MBICONQUESTION, "DynaZIP Alert")
'  If Response = IDOK Then
'    Response = ShellExecute(DYNAZIPFORM1.hWnd, ByVal "open", szDefaultViewer, szExeName, szTempDir, SW_SHOW)
'  End If
'      End If
'    Else
'      Response = MsgBox("UNZIP error, could not extract item (may be encrypted).", MB_OK + MB_ICONEXCLAMATION, "DynaZIP Alert")
'      UpdateWindow (DYNAZIPFORM1.hWnd)
'    End If
'  End If
'End Sub
'
'Function ExtractFileName(szString As String) As String
'  Dim szTemp As String
'  Dim pos As Integer, newpos As Integer
'
'  szTemp = SlashesToBackSlashes(szString)
'  pos = InStr(szString, "\")
'  newpos = -1
'  Do While (pos <> 0) And (newpos <> 0)
'    newpos = InStr(pos + 1, szString, "\")
'    If (newpos > pos) Then
'      pos = newpos
'    End If
'  Loop
'  If pos <> 0 Then
'    pos = pos + 1
'  Else
'    pos = 1
'  End If
'  ExtractFileName = Mid$(szString, pos)
'End Function
'
'Sub extractSelectedFiles()
'  Dim selcount As Integer, i As Integer, totalItems As Integer
'  Dim szMemberSpec As String
'  Dim szNew1 As String, szNew2 As String, szTemp As String
'  Dim errorx As Integer
'  Dim attrib As Integer
'  Dim szLargeItemList As String
'  Dim ExtractedCount As Integer
'
'  'initialize the UNZIP command structure
'  Call initUNZIPCmdStruct(ucs)
'
'  vbduzBlk.szZIPFile = DYNAZIPFORM1!IDE_ZIPFILENAME.Text
'  If bAppendPaths Then
'    ucs.noDirectoryNamesFlag = 0
'  Else
'    ucs.noDirectoryNamesFlag = 1
'  End If
'
'  If bOverwriteWarn Then
'    ucs.overWriteFlag = 0
'  Else
'    ucs.overWriteFlag = 1
'  End If
'
'  ucs.bLF2CRLFFlag = bLF2CRLF
'  ' retrieve the extract-to path
'  szMemberSpec = DYNAZIPFORM1!IDE_EXTRACTTO.Text
'  vbduzBlk.szDestination = szMemberSpec
'
'  selcount = GetLBSelCount(DYNAZIPFORM1!IDC_FILELIST)
'  totalItems = DYNAZIPFORM1!IDC_FILELIST.ListCount
'
'  If ((selcount = 0) Or (totalItems = 0)) Then
'    'There's something amiss
'    Exit Sub
'  End If
'
'  preserveStatusBars
'
'  statusBlk.hMinorStat = 0
'  statusBlk.hMajorStat = 0
'
'  szNew2 = "Extracting " & Format$(selcount) & " item(s)"
'  Call SetStatus(2, 0, szNew2)
'  szLargeItemList = ""
'  ExtractedCount = selcount
'  For i = 0 To totalItems - 1 Step 1
'    If DYNAZIPFORM1!IDC_FILELIST.Selected(i) Then
'      If selcount > 1 Then
'        szNew2 = "Item " & Format$(i + 1) & " of " & Format$(selcount)
'        Call SetStatus(2, (100 * (i + 1)) / selcount, szNew2)
'      End If
'
'      ucs.function = UNZIP_GETINDEXEDZIPINFO
'      vbduzBlk.szZIPFile = DYNAZIPFORM1!IDE_ZIPFILENAME.Text
'      ucs.index = i
'      If dunzipVB(ucs, vbduzBlk, zi, statusBlk) = UE_OK Then
'        'check for valid item
'
'        ' finally ready to unzip something
'        ClearStatus1
'
'        ' inform us for each item extracted
'        statusBlk.hMinorStat = 0
'
'        ' here's where the actual unzipping occurs
'        If ((Len(szLargeItemList) + Len(zi.szFileName) + 3) >= 5000&) Then
'          'Can't fit another item in the list
'          'go ahead and UNZIP what we have in the list so far
'          ucs.index = -1
'          ' get rid of the ' ' at the end of the list (if any)
'          szLargeItemList = Left$(szLargeItemList, Len(szLargeItemList) - 1)
'          vbduzBlk.szFileSpec = szLargeItemList
'          ucs.function = UNZIP_EXTRACT
'          ucs.decryptFlag = bENCRYPT
'          If bENCRYPT Then
'            vbduzBlk.szDecryptCode = DYNAZIPFORM1!IDC_ENCRYPTCODE.Text
'          End If
'          errorx = dunzipVB(ucs, vbduzBlk, zi, statusBlk)
'          szLargeItemList = ""
'        Else
'          ' append another item to the list use double quotes and a
'          ' trailing space to delimit the item
'          szTemp = Left$(zi.szFileName, InStr(zi.szFileName, Chr$(0)) - 1)
'
'          szLargeItemList = szLargeItemList & Chr$(34) & szTemp & Chr$(34) & " "
'          ExtractedCount = ExtractedCount - 1
'          If (ExtractedCount <= 0) Then
'            ' this is the last item go aheah and UNZIP anyway
'            ucs.index = -1
'            ' get rid of the ' ' at the end of the list (if any)
'            szLargeItemList = Left$(szLargeItemList, Len(szLargeItemList) - 1)
'            ucs.function = UNZIP_EXTRACT
'            ucs.decryptFlag = bENCRYPT
'            If bENCRYPT Then
'              vbduzBlk.szDecryptCode = DYNAZIPFORM1!IDC_ENCRYPTCODE.Text
'            End If
'            vbduzBlk.szFileSpec = szLargeItemList
'            errorx = dunzipVB(ucs, vbduzBlk, zi, statusBlk)
'            szLargeItemList = ""
'          End If
'
'        End If
'
'
'        If errorx = UE_SKIP Then
'          errorx = 0
'
'        Else
'          If errorx = UE_CANCEL Then
'            Exit For
'          End If
'        End If
'
'        If errorx <> 0 Then
'          szNew1 = "UNZIP error: " & UNZIPerrors(errorx)
'          MsgBox szNew1, MB_ICONEXCLAMATION + MB_OK, "Dynazip Alert"
'          Exit For
'        End If
'      End If
'    End If
'  Next i
'
'  ' Make sure the user sees 100%
'  szNew1 = DYNAZIPFORM1!Status2.Text
'  Call SetStatus(2, 100, szNew1)
'
'  ' restore the state of both status bars
'  restoreStatusBars
'End Sub
'
'Sub ExtractWorkingDir(szDest As String, szSrc As String)
'  Dim pos As Integer, newpos As Integer
'  Dim szTemp As String
'
'  szTemp = SlashesToBackSlashes(szSrc)
'  pos = InStr(szSrc, "\")
'  newpos = -1
'  Do While (pos <> 0) And (newpos <> 0)
'    If pos < Len(szSrc) Then
'      pos = pos + 1
'    End If
'    newpos = InStr(pos, szSrc, "\")
'    If (newpos > pos) Then
'      pos = newpos
'    End If
'  Loop
'  If pos = 0 Then
'    szDest = Left$(szSrc, 2) & "\"
'  Else
'    szDest = Left$(szSrc, pos - 1)
'    If right$(szDest, 1) = "\" Then
'      szDest = Left$(szDest, Len(szDest) - 1)
'    End If
'  End If
'
'End Sub
'
'---------------------------------------------------------------------------
' Returns TRUE if filled in OK, FALSE i there's some problem with the
' ZIP file as specified.
'Function fillInZIPInfo() As Integer
'  Dim Response As Long, i As Integer, j As Integer
'  Dim szTemp As String, szTemp2  As String, szTemp3 As String
'  Dim szMethod As String
'  Dim szPerc As String
'  Dim perc As Long
'  Dim wLongest As Integer, ThisWidth As Integer
'  Dim lBytesTotal As Long
'  Dim szAttributes As String
'  Dim X As Long
'  Dim hwnd1 As Integer, sbWidth As Integer
'  Const SM_CXVSCROLL = 2
'  Const LB_SETHORIZONTALEXTENT = &H400 + 21
'  Const NUL = &H0
'
'  Call initUNZIPCmdStruct(ucs)
'
'  vbduzBlk.szZIPFile = DYNAZIPFORM1!IDE_ZIPFILENAME.Text
'  If (StrComp(DYNAZIPFORM1!IDE_ZIPFILENAME.Text, "") = 0) Or (StrComp(DYNAZIPFORM1!IDE_ZIPFILENAME.Text, "No ZIP File Selected") = 0) Then
'  ' there is no name recorded (yet)
'    DYNAZIPFORM1!IDE_ZIPFILENAME.Text = "No ZIP File Selected"
'    DYNAZIPFORM1!IDC_FILELIST.Clear
'    DYNAZIPFORM1!IDB_EXTRACTFILES.Enabled = False
'    DYNAZIPFORM1!IDB_DELETEFILES.Enabled = False
'    DYNAZIPFORM1!IDB_EXECUTE.Enabled = False
'    DYNAZIPFORM1!IDC_SELECTALL.Enabled = False
'    ClearStatus1
'    ClearStatus2
'    fillInZIPInfo = False
'    Exit Function
'  Else
'    ' there is a name, get the info
'    DYNAZIPFORM1!IDE_ZIPFILENAME.Text = Left$(vbduzBlk.szZIPFile, InStr(vbduzBlk.szZIPFile, " ") - 1)
'    ucs.function = UNZIP_COUNTALLZIPMEMBERS
'    statusBlk.hMinorStat = 0
'    statusBlk.hMajorStat = 0
'    zi.index = 100
'    zi.oSize = 256
'    zi.cSize = 512
'    zi.cMethod = 15
'    zi.cOption = 32
'    zi.cPathType = 64
'    zi.crc_32 = 1024
'    zi.szDateTime = "01/01/99 09:09"
'    zi.szFileName = "This is a filename"
'    zi.attr = 0
'    zi.lziResv1 = 10
'    zi.lziResv2 = 11
'    j = Len(zi)
'    Response = dunzipVB(ucs, vbduzBlk, zi, statusBlk)
'    j = ucs.returnCount
'    If (Response <> UE_OK) Then
'      szTemp = vbduzBlk.szZIPFile
'      szTemp = szTemp & "is an invalid Zip file, operation aborted!"
'      MsgBox szTemp, MB_ICONEXCLAMATION, "Dynazip Alert"
'      vbduzBlk.szZIPFile = String$(Len(vbduzBlk.szZIPFile), 0)
'      fillInZIPInfo = False
'      Exit Function
'    End If
'    DYNAZIPFORM1!IDC_FILELIST.Clear
'    'Need to setup Horizontal scrolling for IDC_FILELIST here
'    lBytesTotal = 0
'    szTemp = "Reading "
'    szTemp = szTemp & szZIPFile
'    ClearStatus1
'    ClearStatus2
'    i = 0
'    Do
'      ucs.function = UNZIP_GETNEXTZIPINFO
'      statusBlk.hMinorStat = 0
'      statusBlk.hMajorStat = 0
'      If (dunzipVB(ucs, vbduzBlk, zi, statusBlk) <> UE_OK) Then
'        ClearStatus1
'        ClearStatus2
'        fillInZIPInfo = False
'        Exit Function
'      End If
'      Select Case zi.cMethod
'  Case 0
'    szMethod = "Stored"
'  Case 1
'    szMethod = "Shrunk"
'  Case 2
'    szMethod = "Reduced1"
'  Case 3
'    szMethod = "Reduced2"
'  Case 4
'    szMethod = "Reduced3"
'  Case 5
'    szMethod = "Reduced4"
'  Case 6
'    szMethod = "Imploded"
'  Case 7
'    szMethod = "Tokenized"
'  Case 8
'    szMethod = "Deflated"
'  Case Else
'    szMethod = "Unknown"
'      End Select
'      If zi.oSize = 0 Then
'  perc = 0
'      Else
'  perc = (100& * (zi.oSize - zi.cSize)) / zi.oSize
'      End If
'      If perc < 0 Then
'  perc = 0
'      End If
'      szPerc = Format$(perc)
'      If zi.attr And ATTR_ARCHIVE Then
'  szAttributes = "a"
'      Else
'  szAttributes = "-"
'      End If
'      If zi.attr And ATTR_DIRECTORY Then
'  szAttributes = szAttributes & "d"
'      Else
'  szAttributes = szAttributes & "-"
'      End If
'      If zi.attr And ATTR_VOLUME Then
'  szAttributes = szAttributes & "v"
'      Else
'  szAttributes = szAttributes & "-"
'      End If
'      If zi.attr And ATTR_SYSTEM Then
'  szAttributes = szAttributes & "s"
'      Else
'  szAttributes = szAttributes & "-"
'      End If
'      If zi.attr And ATTR_HIDDEN Then
'  szAttributes = szAttributes & "h"
'      Else
'  szAttributes = szAttributes & "-"
'      End If
'      If zi.attr And ATTR_READONLY Then
'  szAttributes = szAttributes & "r"
'      Else
'  szAttributes = szAttributes & "-"
'      End If
'      If zi.attr And ATTR_ENCRYPT Then
'  szAttributes = szAttributes & "*"
'      Else
'  szAttributes = szAttributes & " "
'      End If
'      If zi.attr And ATTR_LFNAME Then
'  szAttributes = szAttributes & "L"
'      Else
'  szAttributes = szAttributes & " "
'      End If
'      szTemp2 = Left$(zi.szFileName, InStr(zi.szFileName, Chr$(0)) - 1)
'      szTemp2 = LCase$(szTemp2)
'      szTemp = Left$(zi.szDateTime, 15) & Chr$(9) & Format$(zi.cSize) & Chr$(9) & Format$(zi.oSize) & Chr$(9) & szPerc & Chr$(9) & szMethod & Chr$(9) & Space$(3) & szAttributes & Chr$(9) & Space$(2) & szTemp2
'      lBytesTotal = lBytesTotal + zi.oSize
'      DYNAZIPFORM1!IDC_FILELIST.AddItem szTemp
'      ThisWidth = (DYNAZIPFORM1.TextWidth(szTemp) / Screen.TwipsPerPixelX) + sbWidth
'      If ThisWidth > Longest Then
'        Longest = ThisWidth
'      End If
'
'      If j > 20 Then
'        Call SetStatus(1, (i * 100&) / j, "")
'      End If
'      i = i + 1
'    Loop While i < j
'    hwnd1 = DYNAZIPFORM1!IDC_FILELIST.hWnd
'    X = SendMessage(hwnd1, LB_SETHORIZONTALEXTENT, Longest, NUL)
'    szTemp = Format$(j) & " Total Items, " & Format$(lBytesTotal, "#,#") & " Bytes Total"
'    Call SetStatus(1, 0, szTemp)
'    Call SetStatus(2, 0, "0 Item(s) Selected")
'    DYNAZIPFORM1!IDB_EXTRACTFILES.Enabled = False
'    DYNAZIPFORM1!IDB_DELETEFILES.Enabled = False
'    DYNAZIPFORM1!IDB_EXECUTE.Enabled = False
'    If j <> 0 Then
'      DYNAZIPFORM1!IDC_SELECTALL.Enabled = True
'    End If
'    fillInZIPInfo = True
'  End If
'End Function

'Sub GetDestDirectory(ByVal h1 As Integer, szTemp As String, szTitle As String)
'  Dim szDrive As String, szPath As String
'
'  Load DIRBROWSER
'  On Error GoTo GDD_ERROR
'  DIRBROWSER.Caption = szTitle
'  If (Len(szTemp) <> 0) Then
'    szDrive = Left$(szTemp, 1) & ":\"
'    szPath = szTemp
'  Else
'    szDrive = CurDir$
'    szPath = szDrive
'  End If
'
'  DIRBROWSER!Drive1.Drive = szDrive
'  DIRBROWSER!Dir1.Path = szPath
'  DIRBROWSER!ID_FROMSPEC.Text = szTemp
'  DIRBROWSER!ID_TOSPEC.Text = DIRBROWSER!Dir1.Path
'  DIRBROWSER.Show 1
'  szTemp = DIRBROWSER!ID_TOSPEC.Text
'  Unload DIRBROWSER
'  Exit Sub
'
'GDD_ERROR:
'  Unload DIRBROWSER
'  MsgBox "Invalid Path or Drive!", MB_OK + MB_ICONEXCLAMATION, "DynaZIP Alert"
'  Exit Sub
'End Sub
'
'Function getExeFileName(szFile As String) As Integer
'  Dim szExt As String
'  Dim szFileName As String
'
'  On Error GoTo ERR_OPENEXEFILENAME
'
'  szLastInputFileDir = szDefaultZIPDir
'  ' Prompt user for name of file to use for input
'  CMDOFFRM!CMDOpenFile.DialogTitle = "DynaZIP - GetProgram Name"
'  CMDOFFRM!CMDOpenFile.Filter = "Programs etc.|*.EXE;*.PIF;*.BAT;*.COM|All Files|*.*"
'  CMDOFFRM!CMDOpenFile.InitDir = szLastInputFileDir
'  szExt = ""
'  CMDOFFRM!CMDOpenFile.DefaultExt = szExt
'  CMDOFFRM!CMDOpenFile.FilterIndex = 1
'  CMDOFFRM!CMDOpenFile.FileName = szFile
'  CMDOFFRM!CMDOpenFile.MaxFileSize = 128
'  CMDOFFRM!CMDOpenFile.Flags = OFN_FILEMUSTEXIST + OFN_HIDEREADONLY
'
'  CMDOFFRM!CMDOpenFile.Action = 1
'  szFile = CMDOFFRM!CMDOpenFile.FileName
'  If Len(szFile) <> 0 Then
'    Call ExtractWorkingDir(szDefaultSourceDir, szFile)
'    getExeFileName = True
'  Else
'    szFile = ""
'    getExeFileName = False
'  End If
'  Exit Function
'
'ERR_OPENEXEFILENAME:
'  szFile = ""
'  getExeFileName = False
'  Exit Function
'
'End Function
'
'Function GetLBSelCount(LB As Control) As Integer
'  Dim i As Integer, selcount As Integer
'
'  selcount = 0
'  For i = 0 To LB.ListCount - 1 Step 1
'    If LB.Selected(i) Then selcount = selcount + 1
'  Next i
'  GetLBSelCount = selcount
'End Function
'
''This is called when (possibly) more than one input filenames are needed
''
''
'Function getMultiFileName(ByVal h1 As Integer, szFile As String, bufflen As Long) As Integer
'
'  Dim szExt As String
'  Dim szFileName As String
'
'  On Error GoTo ERR_OPEN
'
'  szLastInputFileDir = szDefaultSourceDir
'  ' Prompt user for name of file to use for input
'  CMDOFFRM!CMDOpenFile.DialogTitle = "DynaZIP - Select Items To Add"
'  CMDOFFRM!CMDOpenFile.Filter = "All Files (*.*)|*.*"
'  CMDOFFRM!CMDOpenFile.InitDir = szLastInputFileDir
'  CMDOFFRM!CMDOpenFile.DefaultExt = "*.zip"
'  CMDOFFRM!CMDOpenFile.FilterIndex = 1
'  CMDOFFRM!CMDOpenFile.FileName = szFile
'  CMDOFFRM!CMDOpenFile.MaxFileSize = bufflen
'  CMDOFFRM!CMDOpenFile.Flags = OFN_FILEMUSTEXIST + OFN_HIDEREADONLY + OFN_ALLOWMULTISELECT
'
'  CMDOFFRM!CMDOpenFile.Action = 1
'  szFile = CMDOFFRM!CMDOpenFile.FileName
'  If Len(szFile) <> 0 Then
'    If InStr(szFile, " ") <> 0 Then
'      szDefaultSourceDir = Left$(szFile, InStr(szFile, " "))
'    Else
'      Call ExtractWorkingDir(szDefaultSourceDir, szFile)
'    End If
'    getMultiFileName = True
'  Else
'    szFile = ""
'    getMultiFileName = False
'  End If
'  Exit Function
'
'ERR_OPEN:
'  szFile = ""
'  getMultiFileName = False
'  Exit Function
'End Function

Sub InitErrorStrings()
'
'Error message equivalences for dunzip.dll
UNZIPerrors(0) = ""
UNZIPerrors(1) = ""
UNZIPerrors(2) = "Unexpected end of zip file"
UNZIPerrors(3) = "Zip file structure invalid"
UNZIPerrors(4) = "Out of memory"
UNZIPerrors(5) = "Out of memory"
UNZIPerrors(6) = ""
UNZIPerrors(7) = ""
UNZIPerrors(8) = ""
UNZIPerrors(9) = "File not found"
UNZIPerrors(10) = ""
UNZIPerrors(11) = "No files to test, UNZIP_EXTRACT, etc."
UNZIPerrors(12) = ""
UNZIPerrors(13) = ""
UNZIPerrors(14) = ""
UNZIPerrors(15) = ""
UNZIPerrors(16) = ""
UNZIPerrors(17) = ""
UNZIPerrors(18) = ""
UNZIPerrors(19) = ""
UNZIPerrors(20) = ""
UNZIPerrors(21) = ""
UNZIPerrors(22) = ""
UNZIPerrors(23) = ""
UNZIPerrors(24) = ""
UNZIPerrors(25) = "Index out of bounds"
UNZIPerrors(26) = ""
UNZIPerrors(27) = ""
UNZIPerrors(28) = "Error creating output file"
UNZIPerrors(29) = "Error opening archive"
UNZIPerrors(30) = ""
UNZIPerrors(31) = ""
UNZIPerrors(32) = ""
UNZIPerrors(33) = ""
UNZIPerrors(34) = ""
UNZIPerrors(35) = ""
UNZIPerrors(36) = ""
UNZIPerrors(37) = ""
UNZIPerrors(38) = ""
UNZIPerrors(39) = "Bad CRC"
UNZIPerrors(40) = "Application cancelled operation"
UNZIPerrors(41) = "File skipped, encrypted"
UNZIPerrors(42) = "File skipped, unknown compression method"
UNZIPerrors(43) = ""
UNZIPerrors(44) = "Bad or missing decrypt code"
UNZIPerrors(45) = "Busy, can't enter now"
UNZIPerrors(46) = "Can't UNZIP_EXTRACT a Volume ID item"
UNZIPerrors(47) = "Command syntax error"
UNZIPerrors(48) = "Operation cancelled"
UNZIPerrors(49) = "Operation skipped"
UNZIPerrors(50) = "Disk full"

'Error message equivalences for dzip.dll
ZIPerrors(0) = ""
ZIPerrors(1) = "Busy, can't enter now"
ZIPerrors(2) = "Unexpected end of zip file"
ZIPerrors(3) = "Zip file structure invalid"
ZIPerrors(4) = "Out of memory"
ZIPerrors(5) = "Internal logic error"
ZIPerrors(6) = "Entry too big to split"
ZIPerrors(7) = "Invalid comment format"
ZIPerrors(8) = "Zip file invalid or insufficient memory"
ZIPerrors(9) = "Application cancelled operation"
ZIPerrors(10) = "Temporary file failure"
ZIPerrors(11) = "Input file read failure"
ZIPerrors(12) = "Nothing to do!"
ZIPerrors(13) = "Missing or empty zip file"
ZIPerrors(14) = "Output file write failure, possible disk full"
ZIPerrors(15) = "Could not create output file"
ZIPerrors(16) = "Invalid control parameters"
ZIPerrors(17) = "Could not complete operation"
ZIPerrors(18) = "File not found or no read permission"
ZIPerrors(19) = "Media Error"
ZIPerrors(20) = "Invalid Multi-Volume control parameters"
ZIPerrors(21) = "Improper usage of Multi-Volume Zip file"
End Sub

'
' **************************************************************************************
'
'  Procedure:  initUNZIPCmdStruct()
'
'  Purpose:  make the inputted UNZIP command structure "plain vanilla"
'
' **************************************************************************************
Sub initUNZIPCmdStruct(ucs As UNZIPCMDSTRUCT)
  ucs.unzipStructSize = Len(ucs)
  ucs.function = 9                ' Intentionally out of range
  ucs.lpszZIPFile = 0             'NULL
  ucs.zInfo = 0                   'NULL
  ucs.lpszFilespec = 0            'NULL
  ucs.index = -1
  ucs.lpszDestination = 0         'NULL
  ucs.freshenFlag = 0             'False
  ucs.updateFlag = 0              'False
  ucs.overWriteFlag = 0           'False
  ucs.quietFlag = 0               'False
  ucs.testFlag = 0                'False
  ucs.noDirectoryNamesFlag = 1 'True
  ucs.recurseFlag = 1          'True
  ucs.lpMinorStatus = 0           'NULL
  ucs.lpMinorUserData = 0         'NULL
  ucs.lpMajorStatus = 0           'NULL
  ucs.lpMajorUserData = 0         'NULL
  ucs.returnCount = 0
  ucs.lpszReturnString = 0        'NULL
  ucs.bDiagnostic = 0             'False
  ucs.bLF2CRLFFlag = 0            'False
  ucs.decryptFlag = 0             'False
  ucs.lpszDecryptCode = 0         'NULL
  ucs.lpMessageDisplay = 0        'NULL
  ucs.lpMessageDisplayData = 0    'NULL
  ucs.wUnzipSubOptions = 2
'  ucs.wUnzipSubOptions = USO_MINORCANCEL
'  If (bOverwriteRO = True) Then
'    ucs.wUnzipSubOptions = ucs.wUnzipSubOptions + USO_OVERWRITE_RO
'  End If
  
  ' Added for Rev 3
  ucs.lResv1 = 0
  ucs.lResv2 = 0
  ucs.lpRenameProc = 0
  ucs.lpRenameUserData = 0
  ucs.lpszExtProgTitle = 0
  ucs.lpMemBlock = 0
  ucs.lMemBlockSize = 0
  ucs.lStartingOffset = 0
  
  statusBlk.hMinorStat = 0
  statusBlk.hMajorStat = 0
  statusBlk.hResv1 = 0
  statusBlk.hResv2 = 0

  vbduzBlk.szZIPFile = ""
  vbduzBlk.szFileSpec = ""
  vbduzBlk.szDestination = ""
  vbduzBlk.szReturnString = ""
  vbduzBlk.szDecryptCode = ""

  ' added for rev 3.00

  vbduzBlk.szExtProgTitle = "DynaZIP UnZIP Status"

  ucs.lResv1 = 0
  ucs.lResv2 = 0
  ucs.lpRenameProc = 0
  ucs.lpRenameUserData = 0
  ucs.lpszExtProgTitle = 0
  ucs.lpMemBlock = 0
  ucs.lMemBlockSize = 0
  ucs.lStartingOffset = 0

  'Here is where we determine if a Progress display is needed and
  'if Cancelling is allowed.
  'You can also set the title that will appear on the external progress
  'window's title bar
  'ucs.wUnzipSubOptions = ucs.wUnzipSubOptions + USO_EXTERNALPROG + USO_EXTPROGCANCEL

End Sub

'Sub initZCSMultiVol(zcs As ZIPCMDSTRUCT)
'  zcs.wMultiVolControl = 0
'  If (DYNAZIPFORM1!IDC_USEMULTIVOLUME.Value) Then
'    zcs.wMultiVolControl = zcs.wMultiVolControl + MV_USEMULTI
'    If bFormatVolume Then
'      zcs.wMultiVolControl = zcs.wMultiVolControl + MV_FORMAT
'    End If
'    If bLowDensity Then
'      zcs.wMultiVolControl = zcs.wMultiVolControl + MV_LOWDENSE
'    End If
'    If bWipeVolume Then
'      zcs.wMultiVolControl = zcs.wMultiVolControl + MV_WIPE
'    End If
'    If bWipeSubDirs Then
'      zcs.wMultiVolControl = zcs.wMultiVolControl + MV_SUBDIR
'    End If
'    If bWipeSysHidden Then
'      zcs.wMultiVolControl = zcs.wMultiVolControl + MV_SYSHIDE
'    End If
'    If bPlaceCDFirst Then
'      zcs.wMultiVolControl = zcs.wMultiVolControl + MV_CDFIRST
'    End If
'  End If
'
'End Sub

' **************************************************************************************
'
'  Procedure:  initZIPCmdStruct()
'
'  Purpose:  make the inputted ZIP command structure "plain vanilla"
'
' **************************************************************************************
Sub initZIPCmdStruct(zcs As ZIPCMDSTRUCT)
  zcs.zipStructSize = Len(zcs)
  zcs.function = 0                        'intentionally out of range
  zcs.bDiagnostic = 0                     'False
  zcs.lpszZIPFile = 0                     'NULL
  zcs.lpszItemList = 0                    'NULL
  zcs.lpMajorStatus = 0                   'NULL
  zcs.lpMajorUserData = 0                 'NULL
  zcs.lpMinorStatus = 0                   'NULL
  zcs.lpMinorUserData = 0                 'NULL
  zcs.dosifyFlag = 0                      'False
  zcs.recurseFlag = 0                     'False
  zcs.compFactor = 5
  zcs.quietFlag = 0                       'False
  zcs.pathForTempFlag = 0                 'False
  zcs.lpszTempPath = 0                    'NULL
  zcs.dontCompressTheseSuffixesFlag = 0   'False
  zcs.lpszStoreSuffixes = 0               'NULL
  zcs.FixFlag = 0                         'False
  zcs.fixHarderFlag = 0                   'False
  zcs.includeVolumeFlag = 0               'False
  zcs.deleteOriginalFlag = 0              'False
  zcs.growExistingFlag = 0                'False
  zcs.noDirectoryNamesFlag = 0            'False
  zcs.convertLFtoCRLFFlag = 0             'False
  zcs.addCommentFlag = 0                  'False
  zcs.lpszComment = 0                     'NULL
  zcs.afterDateFlag = 0                   'False
  zcs.lpszDate = 0                        'False
  zcs.oldAsLatestFlag = 0                 'NULL
  zcs.includeOnlyFollowingFlag = 0        'False
  zcs.lpszIncludeFollowing = 0            'NULL
  zcs.noDirectoryEntriesFlag = 0          'False
  zcs.includeSysHiddenFlag = 0            'False
  zcs.excludeFollowingFlag = 0            'False
  zcs.lpszExcludeFollowing = 0            'NULL
  zcs.encryptFlag = 0                     'False
  zcs.lpszEncryptCode = 0                 'NULL
  zcs.lpMessageDisplay = 0                'NULL
  zcs.lpMessageDisplayData = 0            'NULL
  zcs.wMultiVolControl = 0                'NO Multi-Volume
  zcs.wZipSubOptions = 0
  
  ' Added for Rev 3
  zcs.lResv1 = 0
  zcs.lResv2 = 0
  zcs.lpRenameProc = 0
  zcs.lpRenameUserData = 0
  zcs.lpszExtProgTitle = 0
  zcs.lpMemBlock = 0
  zcs.lMemBlockSize = 0
  
  statusBlk.hMinorStat = 0
  statusBlk.hMajorStat = 0
  statusBlk.hResv1 = 0
  statusBlk.hResv2 = 0


  vbdzBlk.szZIPFile = ""
  vbdzBlk.szItemList = ""
  vbdzBlk.szTempPath = ""
  vbdzBlk.szComment = ""
  vbdzBlk.szDate = ""
  vbdzBlk.szIncludeFollowing = ""
  vbdzBlk.szExcludeFollowing = ""
  vbdzBlk.szStoreSuffixes = ""
  vbdzBlk.szEncryptCode = ""

  ' added for rev 3.00

  vbdzBlk.szExtProgTitle = "EDBS_ZIP Status"

  zcs.lResv1 = 0
  zcs.lResv2 = 0
  zcs.lpRenameProc = 0
  zcs.lpRenameUserData = 0
  zcs.lpszExtProgTitle = 0
  zcs.lpMemBlock = 0
  zcs.lMemBlockSize = 0
  'Here is where we determine if a Progress display is needed and
  'if Cancelling is allowed.
  'You can also set the title that will appear on the external progress
  'window's title bar
  'zcs.wZipSubOptions = zcs.wZipSubOptions + ZSO_EXTERNALPROG + ZSO_EXTPROGCANCEL


End Sub

Function MajorStatus(szItem As Long, Percent As Long, userData As Long) As Integer
  MajorStatus = 0
End Function

Function MinorStatus(szItem As Long, Percent As Long, userData As Long) As Integer
  MinorStatus = 0
End Function

'Sub preserveStatusBars()
'  szStatus1 = DYNAZIPFORM1!Status1.Text
'  szStatus2 = DYNAZIPFORM1!Status2.Text
'End Sub

'Sub readIniFile()
'  Dim Response As Integer
'
'  Response = GetProfileString(ByVal "DynaZIPVB5", ByVal "Initial Save Directory", ByVal "C:\", szINITemp, Len(szINITemp))
'  szInitialDir = Left$(szINITemp, InStr(szINITemp, Chr$(0)) - 1)
'  If Response = 0 Then
'    szInitialDir = CurDir$
'  End If
'
'  Response = GetProfileString(ByVal "DynaZIPVB5", ByVal "Default ZIP Directory", ByVal "C:\", szINITemp, Len(szINITemp))
'  szDefaultZIPDir = Left$(szINITemp, InStr(szINITemp, Chr$(0)) - 1)
'  If Response = 0 Then
'    szDefaultZIPDir = CurDir$
'  End If
'
'  Response = GetProfileString(ByVal "DynaZIPVB5", ByVal "Default Source Directory", ByVal "C:\", szINITemp, Len(szINITemp))
'  szDefaultSourceDir = Left$(szINITemp, InStr(szINITemp, Chr$(0)) - 1)
'  If Response = 0 Then
'    szDefaultSourceDir = CurDir$
'  End If
'
'  Response = GetProfileString(ByVal "DynaZIPVB5", ByVal "Default Viewer", ByVal "Notepad.exe", szINITemp, Len(szINITemp))
'  szDefaultViewer = Left$(szINITemp, InStr(szINITemp, Chr$(0)) - 1)
'
'  Response = GetProfileString(ByVal "DynaZIPVB5", ByVal "Temporary Directory", ByVal "C:\tempdir", szINITemp, Len(szINITemp))
'  szTempDir = Left$(szINITemp, InStr(szINITemp, Chr$(0)) - 1)
'
'  bOverwriteWarn = GetProfileInt(ByVal "DynaZIPVB5", ByVal "Overwrite Warn", 1)
'  bDeleteWarn = GetProfileInt(ByVal "DynaZIPVB5", ByVal "Delete Warn", 0)
'  bOverwriteRO = GetProfileInt(ByVal "DynaZIPVB5", ByVal "Overwrite Read Only", 1)
'  bSavePaths = GetProfileInt(ByVal "DynaZIPVB5", ByVal "Save With Path", 0)
'  bAppendPaths = GetProfileInt(ByVal "DynaZIPVB5", ByVal "Restore With Path", 0)
'  bDeleteAfterZIP = GetProfileInt(ByVal "DynaZIPVB5", ByVal "Delete After ZIP", 0)
'  bUseTempDir = GetProfileInt(ByVal "DynaZIPVB5", ByVal "Use Temp Dir", 0)
'  bLF2CRLF = GetProfileInt(ByVal "DynaZIPVB5", ByVal "Line Feed to Carriage Return", 0)
'  iZIPCompLevel = GetProfileInt(ByVal "DynaZIPVB5", ByVal "ZIP Compression Level", 5)
'
'  bFormatVolume = GetProfileInt(ByVal "DynaZIPVB5", ByVal "Format Volume", 0)
'  bLowDensity = GetProfileInt(ByVal "DynaZIPVB5", ByVal "Use Low Density", 0)
'  bWipeVolume = GetProfileInt(ByVal "DynaZIPVB5", ByVal "Place CD First", 0)
'  bWipeSubDirs = GetProfileInt(ByVal "DynaZIPVB5", ByVal "Wipe Volume", 0)
'  bWipeSysHidden = GetProfileInt(ByVal "DynaZIPVB5", ByVal "Wipe Sub Directories", 0)
'  bPlaceCDFirst = GetProfileInt(ByVal "DynaZIPVB5", ByVal "Wipe Sys Hidden", 0)
'
'  winPosUpLeftX = GetProfileInt(ByVal "DynaZIPVB5", ByVal "Window Upper Left X", 10)
'  winPosUpLeftY = GetProfileInt(ByVal "DynaZIPVB5", ByVal "Window Upper Left Y", 10)
'
'End Sub

'Sub restoreStatusBars()
'  DYNAZIPFORM1!Status1.Text = szStatus1
'  DYNAZIPFORM1!Status2.Text = szStatus2
'End Sub

'Sub saveIniFile()
'  Dim i As Integer
'
'  i = WriteProfileString(ByVal "DynaZIPVB5", ByVal "Initial Save Directory", ByVal szInitialDir)
'  i = WriteProfileString(ByVal "DynaZIPVB5", ByVal "Default ZIP Directory", ByVal szDefaultZIPDir)
'  i = WriteProfileString(ByVal "DynaZIPVB5", ByVal "Default Source Directory", ByVal szDefaultSourceDir)
'  i = WriteProfileString(ByVal "DynaZIPVB5", ByVal "Default Viewer", ByVal szDefaultViewer)
'  i = WriteProfileString(ByVal "DynaZIPVB5", ByVal "Temporary Directory", ByVal szTempDir)
'  If bOverwriteWarn Then
'    bOverwriteWarn = 1
'  End If
'  i = WriteProfileInt("DynaZIPVB5", "Overwrite Warn", bOverwriteWarn)
'  If bDeleteWarn Then
'    bDeleteWarn = 1
'  End If
'  i = WriteProfileInt("DynaZIPVB5", "Delete Warn", bDeleteWarn)
'  If bOverwriteRO Then
'    bOverwriteRO = 1
'  End If
'  i = WriteProfileInt("DynaZIPVB5", "Overwrite Read Only", bOverwriteRO)
'  If bSavePaths Then
'    bSavePaths = 1
'  End If
'  i = WriteProfileInt("DynaZIPVB5", "Save With Path", bSavePaths)
'  If bAppendPaths Then
'    bAppendPaths = 1
'  End If
'  i = WriteProfileInt("DynaZIPVB5", "Restore With Path", bAppendPaths)
'  If bDeleteAfterZIP Then
'    bDeleteAfterZIP = 1
'  End If
'  i = WriteProfileInt("DynaZIPVB5", "Delete After ZIP", bDeleteAfterZIP)
'  If bUseTempDir Then
'    bUseTempDir = 1
'  End If
'  i = WriteProfileInt("DynaZIPVB5", "Use Temp Dir", bUseTempDir)
'  If bLF2CRLF Then
'    bLF2CRLF = 1
'  End If
'  i = WriteProfileInt("DynaZIPVB5", "Line Feed to Carriage Return", bLF2CRLF)
'  i = WriteProfileInt("DynaZIPVB5", "ZIP Compression Level", iZIPCompLevel)
'  i = WriteProfileInt("DynaZIPVB5", "Window Upper Left X", winPosUpLeftX)
'  i = WriteProfileInt("DynaZIPVB5", "Window Upper Left Y", winPosUpLeftY)
'
'  If bFormatVolume Then
'    bFormatVolume = 1
'  End If
'  i = WriteProfileInt("DynaZIPVB5", "Format Volume", bFormatVolume)
'  If bLowDensity Then
'    bLowDensity = 1
'  End If
'  i = WriteProfileInt("DynaZIPVB5", "Use Low Density", bLowDensity)
'  If bWipeVolume Then
'    bWipeVolume = 1
'  End If
'  i = WriteProfileInt("DynaZIPVB5", "Wipe Volume", bWipeVolume)
'  If bWipeSubDirs Then
'    bWipeSubDirs = 1
'  End If
'  i = WriteProfileInt("DynaZIPVB5", "Wipe Sub Directories", bWipeSubDirs)
'  If bWipeSysHidden Then
'    bWipeSysHidden = 1
'  End If
'  i = WriteProfileInt("DynaZIPVB5", "Wipe Sys Hidden", bWipeSysHidden)
'  If bPlaceCDFirst Then
'    bPlaceCDFirst = 1
'  End If
'  i = WriteProfileInt("DynaZIPVB5", "Place CD First", bPlaceCDFirst)
'
'End Sub

'Sub SetDefaultValues()
'Dim rc1 As Rect
'
''The following variables are used to keep track of current conditions
'  szGlobalDest = ""
'  szTempDir = "c:\tempdir"
'  szDefaultViewer = "notepad.exe"
'  szInitialDir = ""
'  szDefaultZIPDir = ""
'  szDefaultSourceDir = ""
'  szLastInputFileDir = ""
'
''The following variables are used to record the options selected by the user
'  bOverwriteWarn = 1
'  bDeleteWarn = 0
'  bOverwriteRO = 0
'  bSavePaths = 0
'  bUseTempDir = 0
'  bAppendPaths = 0
'  iZIPCompLevel = 5
'  bDeleteAfterZIP = 0
'  bLF2CRLF = 0
'  bENCRYPT = 0
'
'  bFormatVolume = 0
'  bLowDensity = 0
'  bWipeVolume = 0
'  bWipeSubDirs = 0
'  bWipeSysHidden = 0
'  bPlaceCDFirst = 0
'
'  winPosUpLeftX = 0
'  winPosUpLeftY = 0
'
''Retrieve the command line that was used when the program was executed
'  szCommandLine = Command$
'
''Set up initial controls values
'  DYNAZIPFORM1!IDE_ZIPFILENAME.Text = ""
'  DYNAZIPFORM1!IDE_EXTRACTTO.Text = ""
'
''Now read the associated "INI" file
'  readIniFile
'
''Now set the correct position for any new instances
'  If App.PrevInstance <> 0 Then
'    ' Offset new instance from any previous instance by 15 pixels
'    rc1.Left = 0
'    rc1.Top = 0
'    DYNAZIPFORM1.Left = (rc1.Left) * Screen.TwipsPerPixelX
'    DYNAZIPFORM1.Top = (rc1.Top) * Screen.TwipsPerPixelX
'  Else
'    DYNAZIPFORM1.Left = 0
'    DYNAZIPFORM1.Top = 0
'
'  End If
'
'
'End Sub
'
'Sub SetStatus(stat As Integer, statvalue As Integer, szText As String)
'  Select Case stat
'  Case 1
'    If StrComp(DYNAZIPFORM1!Status1.Text, szText) <> 0 Then
'      DYNAZIPFORM1!Status1.Text = szText
'    End If
'
'  Case 2
'    If StrComp(DYNAZIPFORM1!Status2.Text, szText) <> 0 Then
'      DYNAZIPFORM1!Status2.Text = szText
'    End If
'
'  Case Else
'    If StrComp(DYNAZIPFORM1!Status1.Text, szText) <> 0 Then
'      DYNAZIPFORM1!Status1.Text = szText
'    End If
'
'  End Select
'End Sub
'
'Function SlashesToBackSlashes(szString As String) As String
'Dim pos As Integer
'  pos = InStr(szString, "/")
'  Do While (pos <> 0)
'    Mid$(szString, pos, 1) = Chr$(92) 'Replace slash with backslash
'    pos = InStr(pos, szString, "/")
'  Loop
'  pos = InStr(szString, Chr$(0))
'  'Set remainder of string to all nulls
'  Do While (pos <> 0) And (pos <= Len(szString))
'    Mid$(szString, pos, 1) = Chr$(0)
'    pos = pos + 1
'  Loop
'
'  SlashesToBackSlashes = szString
'End Function

Function validZIPFile(szTestFile As String) As Integer
  Dim Response As Integer
  Dim ucs As UNZIPCMDSTRUCT
  Call initUNZIPCmdStruct(ucs)
  vbduzBlk.szZIPFile = szTestFile
  ucs.function = UNZIP_COUNTALLZIPMEMBERS
  Response = dunzipVB(ucs, vbduzBlk, zi, statusBlk)
  If Response = UE_OK Then
    validZIPFile = True
  Else
    validZIPFile = False
  End If
End Function

Function WriteProfileInt(szHeading As String, szSubCat As String, myValue As Integer) As Integer
  Dim szIntAsString As String
  Dim i As Integer

  szIntAsString = Format$(myValue)
  i = WriteProfileString(ByVal szHeading, ByVal szSubCat, ByVal szIntAsString)
End Function

