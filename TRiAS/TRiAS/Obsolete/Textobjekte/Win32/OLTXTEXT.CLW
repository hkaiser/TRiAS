; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTxtReDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "oltxtext.h"
VbxHeaderFile=oltxtext.h
VbxImplementationFile=oltxtext.cpp
LastPage=0

ClassCount=3
Class1=CDlgAbh
Class2=CTextDlg
Class3=CTxtReDlg

ResourceCount=5
Resource1=IDD_DIALOG3
Resource2=IDR_HMENU
Resource3=IDD_DIALOG1
Resource4=IDR_ORMENU
Resource5=IDD_DIALOG2

[CLS:CDlgAbh]
Type=0
HeaderFile=..\dlgabh.h
ImplementationFile=..\dlgabh.cpp
LastObject=CDlgAbh

[CLS:CTextDlg]
Type=0
HeaderFile=..\textdlg.h
ImplementationFile=..\textdlg1.cpp
LastObject=IDC_POSPOINTTEXTS
Filter=D
VirtualFilter=dWC

[CLS:CTxtReDlg]
Type=0
HeaderFile=..\txtredlg.h
ImplementationFile=..\txtrdlg1.cpp
LastObject=IDC_POSPOINTTEXTS
Filter=D
VirtualFilter=dWC

[DLG:IDD_DIALOG3]
Type=1
Class=CDlgAbh
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_LIST1,listbox,1352730883
Control3=IDC_CLOESCH,button,1342242819
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_ALLID,button,1342242816

[DLG:IDD_DIALOG1]
Type=1
Class=CTextDlg
ControlCount=20
Control1=IDC_STATIC,static,1342308352
Control2=IDC_LIST1,listbox,1352730883
Control3=IDC_ALLID,button,1342373888
Control4=IDC_STSPFORM,button,1342308359
Control5=IDC_RADIO3,button,1342242825
Control6=IDC_RADIO4,button,1342177289
Control7=IDC_STATIC,button,1342308359
Control8=IDC_RADIO2,button,1342373897
Control9=IDC_COMBO1,combobox,1344340227
Control10=IDC_RADIO1,button,1342373897
Control11=IDC_EDIT1,edit,1350631552
Control12=IDC_STATIC,button,1342308359
Control13=IDC_CHECK1,button,1342373891
Control14=IDC_RLOESCH,button,1342373897
Control15=IDC_RRENAME,button,1342177289
Control16=IDC_PUTOBCL,button,1342373891
Control17=IDC_ComboPutOCl,combobox,1344340227
Control18=IDOK,button,1342373889
Control19=IDCANCEL,button,1342242816
Control20=IDC_POSPOINTTEXTS,button,1342242819

[DLG:IDD_DIALOG2]
Type=1
Class=CTxtReDlg
ControlCount=17
Control1=IDC_STSPFORM,button,1342308359
Control2=IDC_RADIO2,button,1342242825
Control3=IDC_RADIO3,button,1342177289
Control4=IDC_STATIC,button,1342308359
Control5=IDC_RADIO1,button,1342242825
Control6=IDC_COMBO3,combobox,1344471299
Control7=IDC_RADIO4,button,1342177289
Control8=IDC_EDIT2,edit,1350631552
Control9=IDC_STATIC,button,1342308359
Control10=IDC_CHECK1,button,1342373891
Control11=IDC_LOESCH,button,1342373897
Control12=IDC_RENAME,button,1342177289
Control13=IDC_PUTOBCL,button,1342373891
Control14=IDC_COMBOPUTOBCL,combobox,1344340227
Control15=IDOK,button,1342373889
Control16=IDCANCEL,button,1342242816
Control17=IDC_POSPOINTTEXTS,button,1342242819

[MNU:IDR_HMENU]
Type=1
Class=?
Command1=IDM_CHOICE
Command2=IDM_OBABH
CommandCount=2

[MNU:IDR_ORMENU]
Type=1
Class=?
Command1=IDM_OBRECH
Command2=IDM_OBREABH
Command3=IDM_ORLOESCH
CommandCount=3

