// Manually edited resources
//

//////////////////////////////////////////////////////////////////////////////
//
// String Table
//

STRINGTABLE DISCARDABLE 
BEGIN
    IDS_VERSION          "V@A.@B.@C"
    IDS_COPYRIGHT        "#@D"
END

IDD_ABOUTBOX DIALOG DISCARDABLE  0, 0, 235, 54
STYLE DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "Zusammenstellen von Dateien der DLK"
FONT 8, "MS Sans Serif"
BEGIN
    ICON            IDR_MAINFRAME,IDC_STATIC,9,14,21,20
    LTEXT           "CopyDLK V@A.@B.@C",IDC_VERSION,40,10,128,8,SS_NOPREFIX
    LTEXT           "Copyright © @I 1991 - 2002, #@D",
                    IDC_STATIC,40,23,128,18
    DEFPUSHBUTTON   "OK",IDOK,176,4,55,14,WS_GROUP
END

