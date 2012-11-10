IDD_ABOUTBOX DIALOG DISCARDABLE  0, 0, 217, 124
STYLE DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "Info über GAK"
FONT 8, "MS Sans Serif"
BEGIN
    ICON            IDR_MAINFRAME,IDC_STATIC,16,78,18,20
    CTEXT           "Copyright © 1996-1998 @D @E",IDC_STATIC,0,35,217,8
    DEFPUSHBUTTON   "&OK",IDOK,80,104,55,14,WS_GROUP
    CTEXT           "Gewerbeabfallkataster (GAK), Version @A.@B.@C",IDC_STATIC,0,
                    10,217,8
    CTEXT           "f\374r das Land Brandenburg",IDS_FUER,0,20,217,8
    CONTROL         "",IDC_STATIC,"Static",SS_BLACKFRAME,0,60,217,1
    LTEXT           "Das Programm ist lizensiert f\374r:",IDC_STATIC,55,70,147,
                    8
    LTEXT           "Version f\374r den Vertrieb.",IDS_LIZENS,55,80,
                    155,8
    RTEXT           "Nutzername:",IDC_STATIC,55,90,50,8
    LTEXT           "",IDC_USER_NAME,110,90,95,8
END


