; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CClsfyByCodeDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "linetools.h"
LastPage=0

ClassCount=4
Class1=CCodeCheckDlg

ResourceCount=5
Resource1=IDD_CLSFYBYCODE_OPTIONS
Resource2=IDR_MENU1
Class2=CCCodeStatDlg
Resource3=IDD_CODELINE_OPTIONS
Class3=CCodeLineDlg
Resource4=IDD_CCODESTAT_OPTIONS
Class4=CClsfyByCodeDlg
Resource5=IDR_MENU2

[CLS:CCodeCheckDlg]
Type=0
BaseClass=CPropertyPage
HeaderFile=CodeCheckDlg.h
ImplementationFile=CodeCheckDlg.cpp
LastObject=CCodeCheckDlg
Filter=D
VirtualFilter=idWC

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=IDM_CODECHECK
Command2=IDM_CODECHECKMULTI
Command3=IDM_CHECKGEOMETRIE
Command4=IDM_LINECHECK
Command5=IDM_CLASSIFY
Command6=IDM_CLASSIFYWINDOW
CommandCount=6

[MNU:IDR_MENU2]
Type=1
Class=?
Command1=IDM_CODECHECK
Command2=IDM_CODECHECKMULTI
Command3=IDM_CHECKGEOMETRIE
Command4=IDM_LINECHECK
Command5=IDM_CLASSIFY
Command6=IDM_CLASSIFYWINDOW
CommandCount=6

[CLS:CCCodeStatDlg]
Type=0
HeaderFile=CCodeStatDlg.h
ImplementationFile=CCodeStatDlg.cpp
BaseClass=CPropertyPage
LastObject=CCCodeStatDlg
Filter=D
VirtualFilter=idWC

[DLG:IDD_CCODESTAT_OPTIONS]
Type=1
Class=CCodeCheckDlg
ControlCount=19
Control1=IDC_STATIC,button,1342177287
Control2=IDC_NOKEY,button,1342242819
Control3=IDC_SYNTAXERROR,button,1342242819
Control4=IDC_DUPLICATEKEY,button,1342242819
Control5=IDC_OTHERFEATURE,button,1342242819
Control6=IDC_MULTIGEOMETRY,button,1476460547
Control7=IDC_STATIC,static,1342308352
Control8=IDC_CONTROLCODE,edit,1350633600
Control9=IDC_CONTROLERROR,edit,1350633600
Control10=IDC_STATIC,static,1342308352
Control11=IDC_DUPLGEOMETRY,button,1342242819
Control12=IDC_UNDVERKNUEPFUNG,button,1342177289
Control13=IDC_ODERVERKNUEPFUNG,button,1342177289
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,button,1342177287
Control16=IDC_ERRBESCHREIBUNG,edit,1342244996
Control17=IDC_CONTROLORIGINAL,edit,1350633600
Control18=IDC_STATIC,static,1342308352
Control19=IDC_ERRORSTATIST,button,1476460547

[DLG:IDD_CODELINE_OPTIONS]
Type=1
Class=CCodeLineDlg
ControlCount=7
Control1=IDC_STATIC,button,1342177287
Control2=IDC_CHECKFIRSTCTRL,button,1342242819
Control3=IDC_CHECKFEATURE,button,1342242819
Control4=IDC_CHECKINTERN,button,1342242819
Control5=IDC_LINEDESCRIPTION,edit,1342244932
Control6=IDC_STATIC,static,1342308352
Control7=IDC_LINEGCSCONTROL,edit,1350633600

[CLS:CCodeLineDlg]
Type=0
HeaderFile=CodeLineDlg.h
ImplementationFile=CodeLineDlg.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDM_CHECKGEOMETRIE

[DLG:IDD_CLSFYBYCODE_OPTIONS]
Type=1
Class=CClsfyByCodeDlg
ControlCount=6
Control1=IDC_SELECTCAPTION,button,1342177287
Control2=IDC_AREACONSTRUCTION,button,1342177289
Control3=IDC_LINECONSTRUCTION,button,1342177289
Control4=IDC_HELPCONSTRUCTION,edit,1342245060
Control5=IDC_STATIC,static,1342308352
Control6=IDC_GCOIDENT,edit,1350633600

[CLS:CClsfyByCodeDlg]
Type=0
HeaderFile=ClsfyByCodeDlg.h
ImplementationFile=ClsfyByCodeDlg.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDC_LINECONSTRUCTIOMN

