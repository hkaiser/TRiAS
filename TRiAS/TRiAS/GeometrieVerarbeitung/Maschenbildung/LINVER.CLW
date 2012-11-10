; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CParamDialog
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "linver.h"
LastPage=0

ClassCount=4

ResourceCount=4
Class1=CParamDialog
Resource1=IDD_LINVERFOLGUNG
Resource2=IDM_UNITINGMENU
Class2=CObjStatDlg
Class3=CVerschnittDialog
Class4=CVerschnittPage
Resource3=IDD_VERSCHNITT_PAGE
Resource4=IDD_OBJEKT_STATISTIK

[DLG:IDD_LINVERFOLGUNG]
Type=1
Class=CParamDialog
ControlCount=15
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342177296
Control3=IDC_STATIC,static,1342308352
Control4=IDE_FUZZY,edit,1350762624
Control5=IDB_FUZZY,msctls_updown32,1342177461
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342177296
Control8=IDB_MASCHEN_UNION,button,1342373891
Control9=IDB_LINES_UNION,button,1342242819
Control10=IDB_OUTPUT_MERKMAL,button,1342252035
Control11=IDB_DELETE_LINES,button,1342373891
Control12=IDC_MARK_OBJECTS,button,1342242819
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342177296
Control15=IDT_DESCRIPTION,static,1342308352

[CLS:CParamDialog]
Type=0
HeaderFile=paramdlg.hpp
ImplementationFile=paramdlg.cpp
BaseClass=CPropertyPage
LastObject=IDB_OUTPUT_MERKMAL
Filter=D
VirtualFilter=idWC

[DLG:IDD_OBJEKT_STATISTIK]
Type=1
Class=CObjStatDlg
ControlCount=13
Control1=IDC_STATIC,static,1342177282
Control2=IDC_STATIC,static,1342177282
Control3=IDC_STATIC,static,1342177282
Control4=IDC_STATIC,static,1342177282
Control5=IDT_TEXTCNT,static,1342177280
Control6=IDT_PKTCNT,static,1342177280
Control7=IDT_LINCNT,static,1342177280
Control8=IDT_FLCNT,static,1342177280
Control9=IDC_STATIC,static,1342177296
Control10=IDC_STATIC,static,1342308354
Control11=IDT_SUMME,static,1342177280
Control12=IDC_STATIC,static,1342308354
Control13=IDT_GEO_ERROR,static,1342308352

[CLS:CObjStatDlg]
Type=0
HeaderFile=objstat.hpp
ImplementationFile=objstat.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CObjStatDlg

[CLS:CVerschnittDialog]
Type=0
HeaderFile=Verschnt.hpp
ImplementationFile=Verschnt.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CVerschnittDialog

[CLS:CVerschnittPage]
Type=0
HeaderFile=Verparam.hpp
ImplementationFile=Verparam.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDC_MARK_OBJECTS

[DLG:IDD_VERSCHNITT_PAGE]
Type=1
Class=CVerschnittPage
ControlCount=15
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342177296
Control3=IDC_STATIC,static,1342308352
Control4=IDE_FUZZY,edit,1350762624
Control5=IDB_FUZZY,msctls_updown32,1342177461
Control6=IDC_STATIC,static,1342308352
Control7=IDE_DANGLE_LEN,edit,1350762624
Control8=IDB_DANGLE_LEN,msctls_updown32,1342177461
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342177296
Control11=IDB_DELETE_LINES,button,1342242819
Control12=IDC_MARK_OBJECTS,button,1342242819
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342177296
Control15=IDT_DESCRIPTION,static,1342308352

[MNU:IDM_UNITINGMENU]
Type=1
Command1=IDM_LINESPLITTING
Command2=IDM_LINEUNITING
Command3=IDM_AREAFORMING
CommandCount=3

