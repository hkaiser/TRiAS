ABOUTBOX DIALOG 23, 53, 168, 103
STYLE DS_MODALFRAME | WS_CAPTION | WS_SYSMENU
CAPTION "Info über TriasED"
FONT 8, "MS Sans Serif"
BEGIN
    CTEXT           "Copyright© 1991-1998", -1, 0, 52, 168, 9
    LTEXT           "TriasED", -1, 51, 14, 31, 10
    LTEXT           "Version @A.@B.@C #@D", -1, 50, 27, 106, 10
    DEFPUSHBUTTON   "OK", IDOK, 58, 83, 55, 14, WS_GROUP
    ICON            "TriasEDIcon", -1, 13, 16, 16, 16
    CTEXT           "@E", -1, 0, 66, 168, 8
END
