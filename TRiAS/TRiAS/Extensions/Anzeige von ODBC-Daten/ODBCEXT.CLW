; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAutoListComboBox
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "odbcext.h"
VbxHeaderFile=odbcext.h
VbxImplementationFile=odbcext.cpp
LastPage=0

ClassCount=26

ResourceCount=31
Resource1=IDD_ABGL_RESULT (_DEBUG)
Resource2=IDM_ODBCBACKUP
Resource3=IDD_ABGLEICH (_DEBUG)
Resource4=IDD_INPUT_WHERE_PAGE1
Resource5=IDD_FIELDINFO
Resource6=IDD_CREATE_WHERE
Resource7=IDD_RELATIONS
Class1=CImportParamDialog
Resource8=IDD_INPUT_WHERE_PAGE2
Resource9=IDD_LONGVAR
Class2=CTriasPage
Class3=CAbgleichPage
Class4=CImportSheet
Resource10=IDD_FILE_DSN
Resource11=IDD_FREE_REL
Class5=CDsnPage
Class6=CFeldPage
Resource12=IDD_FILTER
Class7=CFilterPage
Class8=CFeldInfoDialog
Resource13=IDD_USER_DSN
Class9=CResultPage
Resource14=IDR_ACCELERATOR1
Class10=CImportResult2
Resource15=IDD_VIEW_FRAME
Class11=CDoAbgleich
Class12=CConnect
Resource16=IDD_IMP_DOABGLEICH (_DEBUG)
Resource17=IDD_FIELD_CONTENT
Class13=CUserDsnPage
Class14=CFileDsnPage
Class15=CFreeRelDlg
Class16=CFreeRelDialog
Class17=CDataSourceNameSheet
Class18=CUserDlg
Class19=CFileDlg
Resource18=IDR_VIEW_FRAMEBACKUP
Resource19=IDD_CONNECTIONS
Resource20=IDD_RECH_STATUS
Class20=CWherePage
Resource21=IDM_VIEW_FRAMEBACKUP
Class21=CFieldContentsDlg
Class22=CToolTipButton
Resource22=IDD_INPUT_WHERE_PAGE
Resource23=IDD_FILE_DSN_MEDIUM
Resource24=IDD_USER_DSN_MEDIUM
Class23=CRechStat
Class24=CWhereSet
Class25=CAutoListComboBox
Resource25=IDM_ODBC
Class26=CDerivedGrid
Resource26=IDD_DATENQUELLE
Resource27=IDM_VIEW_FRAME
Resource28=IDR_VIEW_FRAME
Resource29=IDD_TRIAS (_DEBUG)
Resource30=IDD_FELDER
Resource31=IDD_IMP_ABGL_RES2 (_DEBUG)

[DB:CColumns]
DB=1

[DB:CRecSet]
DB=1

[DB:CTables]
DB=1

[DLG:IDR_VIEW_FRAME]
Type=1
Class=?
ControlCount=2
Control1=IDL_ROWLIST,listbox,1353777537
Control2=IDC_GRID,GXWND,1350631424

[DLG:IDD_LONGVAR]
Type=1
Class=?
ControlCount=1
Control1=IDE_LONGVAR,edit,1352730628

[DLG:IDD_FIELDINFO]
Type=1
Class=CFeldInfoDialog
ControlCount=1
Control1=IDL_FIELDINFO,SysListView32,1350631429

[DLG:IDD_RELATIONS]
Type=1
Class=?
ControlCount=11
Control1=65535,static,1342308352
Control2=IDL_DELETESLAVE,listbox,1353779459
Control3=IDB_ADDREL,button,1208156171
Control4=IDB_REMREL,button,1207959563
Control5=65535,static,1208090624
Control6=IDL_ADDSLAVE,listbox,1219561731
Control7=IDOK,button,1342242816
Control8=IDCANCEL,button,1342177280
Control9=IDB_RELHELP,button,1476395008
Control10=IDB_FREEREL,button,1342242816
Control11=IDB_DELREL,button,1476460544

[DLG:IDD_CONNECTIONS]
Type=1
Class=CConnect
ControlCount=28
Control1=IDC_STATIC1,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_OBJKLASSEN,combobox,1344471299
Control4=IDC_STATIC,static,1342308352
Control5=IDB_LASTENTRY,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDE_ALIASNAME,edit,1350631552
Control8=IDB_RELATIONEN,button,1476460544
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308352
Control11=IDC_TAB_DSN,SysTabControl32,1342242816
Control12=IDC_STATIC,static,1342177280
Control13=IDC_TABLES,combobox,1478689027
Control14=IDC_STATIC,button,1342177287
Control15=IDB_MERKMALSKODE,button,1342177289
Control16=IDC_MERKMALSKODES,combobox,1344471299
Control17=IDC_STATIC,static,1342177280
Control18=IDC_KOPPELFELD,combobox,1478557955
Control19=IDC_STATIC,static,1342177296
Control20=IDB_SELECTWHERE,button,1342177289
Control21=IDE_WHEREKLAUSEL,edit,1350764672
Control22=IDB_CREATEWHERE,button,1342177280
Control23=IDC_STATIC,button,1342177287
Control24=IDT_CONNECTDESCR,edit,1352665092
Control25=IDB_STORECONNECT,button,1476591617
Control26=IDB_BEENDEN,button,1342177280
Control27=IDB_CONNECTHELP,button,1476395008
Control28=IDB_STANDARD_DSN,button,1476460547

[DLG:IDD_CREATE_WHERE]
Type=1
Class=?
ControlCount=18
Control1=65535,static,1342308352
Control2=IDE_WHERE,edit,1350631808
Control3=65535,static,1342177280
Control4=IDL_OBJ_MERKMALE,listbox,1353777411
Control5=IDB_AS_TEXT,button,1342242825
Control6=IDB_AS_NUM,button,1342177289
Control7=IDB_AS_DATE,button,1342177289
Control8=65535,static,1342308352
Control9=IDL_TABLE_FIELDS,listbox,1353777411
Control10=65535,static,1342308352
Control11=IDL_SCALE_FUNCTIONS,listbox,1352728833
Control12=65535,static,1342308352
Control13=IDL_OPERATORS,listbox,1352728833
Control14=IDB_CHECK_WHERE,button,1476460544
Control15=IDOK,button,1476460545
Control16=IDCANCEL,button,1342177280
Control17=65535,button,1342177287
Control18=IDT_WHERE_DESCR,edit,1352665092

[MNU:IDR_VIEW_FRAME]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_REDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=IDD_ASC
Command7=IDD_DESC
Command8=IDM_FIELDINFO
Command9=ID_FILE_SAVE_AS
CommandCount=9

[CLS:CImportParamDialog]
Type=0
HeaderFile=importpa.hpp
ImplementationFile=importpa.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[DB:CImportParamDialog]
DB=1
ColumnCount=-1
LastClass=CImportParamDialog

[MNU:IDM_ODBC]
Type=1
Class=?
Command1=IDM_ODBCENTRY
Command2=IDM_CALL_ADMIN
CommandCount=2

[CLS:CTriasPage]
Type=0
HeaderFile=triaspge.hpp
ImplementationFile=triaspge.cpp
Filter=D
LastObject=CTriasPage
BaseClass=CPropertyPage
VirtualFilter=idWC

[CLS:CAbgleichPage]
Type=0
HeaderFile=abglpge.hpp
ImplementationFile=abglpge.cpp
Filter=D
LastObject=CAbgleichPage
BaseClass=CPropertyPage
VirtualFilter=idWC

[CLS:CImportSheet]
Type=0
HeaderFile=importsh.hpp
ImplementationFile=importsh.cpp
Filter=W
LastObject=CImportSheet
BaseClass=CPropertySheet
VirtualFilter=hWC

[DLG:IDD_DATENQUELLE]
Type=1
Class=CDsnPage
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_DSN_TAB,SysTabControl32,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDL_DSN_TABLE,listbox,1352728835
Control5=IDB_DSN_ON_TRIAS,button,1342373897
Control6=IDB_DSN_ON_TABLE,button,1342177289
Control7=IDB_IMP_IMP_NOTEXISTS,button,1342242819
Control8=IDB_IMP_DEL_NOTEXISTS,button,1342242819

[CLS:CDsnPage]
Type=0
HeaderFile=dsnpage.hpp
ImplementationFile=dsnpage.cpp
Filter=D
LastObject=CDsnPage
BaseClass=CPropertyPage
VirtualFilter=idWC

[DLG:IDD_FELDER]
Type=1
Class=CFeldPage
ControlCount=9
Control1=65535,static,1342308352
Control2=IDL_FELD_KOPPEL,SysListView32,1350631429
Control3=65535,static,1342308352
Control4=IDL_FELD_RECHTSW,SysListView32,1350631429
Control5=65535,static,1342308352
Control6=IDL_FELD_HOCHW,SysListView32,1350631429
Control7=65535,static,1342308352
Control8=65535,static,1342308352
Control9=65535,static,1342308352

[CLS:CFeldPage]
Type=0
HeaderFile=feldpage.hpp
ImplementationFile=feldpage.cpp
Filter=D
LastObject=CFeldPage
BaseClass=CPropertyPage
VirtualFilter=idWC

[DLG:IDD_FILTER]
Type=1
Class=CFilterPage
ControlCount=11
Control1=65535,static,1342308352
Control2=IDE_FILTER_KLAUSEL,edit,1350631552
Control3=65535,static,1342308352
Control4=IDL_FILTER_FELD,SysListView32,1350631429
Control5=65535,static,1342308352
Control6=IDL_FILTER_FUNKT,listbox,1352728833
Control7=65535,static,1342308352
Control8=IDL_FILTER_OPERA,listbox,1352728833
Control9=IDB_FILTER_CHECK,button,1476460545
Control10=IDT_IMP_FILTER_DESCR,edit,1352665092
Control11=65535,button,1342177287

[CLS:CFilterPage]
Type=0
HeaderFile=filtrpge.hpp
ImplementationFile=filtrpge.cpp
Filter=D
LastObject=CFilterPage
BaseClass=CPropertyPage
VirtualFilter=idWC

[CLS:CFeldInfoDialog]
Type=0
HeaderFile=feldin32.hpp
ImplementationFile=feldin32.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDL_FIELDINFO

[CLS:CResultPage]
Type=0
HeaderFile=rsltpge.hpp
ImplementationFile=rsltpge.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CResultPage

[CLS:CImportResult2]
Type=0
HeaderFile=ImpRslt2.hpp
ImplementationFile=ImpRslt2.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CImportResult2

[CLS:CDoAbgleich]
Type=0
HeaderFile=Abgleich.hpp
ImplementationFile=Abgleich.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CDoAbgleich

[CLS:CConnect]
Type=0
HeaderFile=connect.hpp
ImplementationFile=connect.cpp
BaseClass=CDialog
LastObject=CConnect
Filter=W
VirtualFilter=dWC

[CLS:CUserDsnPage]
Type=0
HeaderFile=UDsnPage.h
ImplementationFile=UDsnPage.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CUserDsnPage

[CLS:CFileDsnPage]
Type=0
HeaderFile=FDsnPage.h
ImplementationFile=FDsnPage.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CFileDsnPage

[CLS:CFreeRelDlg]
Type=0
HeaderFile=FreeRelD.h
ImplementationFile=FreeRel.cpp
BaseClass=CDialog
Filter=D
LastObject=CFreeRelDlg
VirtualFilter=dWC

[DLG:IDD_FREE_REL]
Type=1
Class=CFreeRelDialog
ControlCount=12
Control1=IDC_DSN_TAB,SysTabControl32,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_TABLENAME,combobox,1478557955
Control4=IDC_STATIC,static,1342308352
Control5=IDE_ALIASNAME,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_KOPPELFIELD,combobox,1478557955
Control8=IDC_STATIC,button,1342177287
Control9=IDT_DESCRIPTION,edit,1352665092
Control10=IDOK,button,1476460545
Control11=IDCANCEL,button,1342177280
Control12=IDB_FRHELP,button,1476395008

[CLS:CFreeRelDialog]
Type=0
HeaderFile=FreeRelD.hpp
ImplementationFile=FreeRelD.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[CLS:CDataSourceNameSheet]
Type=0
HeaderFile=dsnsheet.h
ImplementationFile=dsnsheet.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=CDataSourceNameSheet

[DLG:IDD_USER_DSN]
Type=1
Class=CUserDlg
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_DSN,combobox,1344340227
Control3=IDB_CREATE,button,1342373889
Control4=IDB_CHANGE,button,1342177280

[CLS:CUserDlg]
Type=0
HeaderFile=UserDlg.h
ImplementationFile=UserDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_DSN
VirtualFilter=dWC

[DLG:IDD_FILE_DSN]
Type=1
Class=CFileDlg
ControlCount=5
Control1=IDE_DSN,edit,1350568064
Control2=IDB_SELECT,button,1342242817
Control3=IDC_STATIC,static,1342308352
Control4=IDB_CREATE,button,1342373889
Control5=IDB_CHANGE,button,1476395008

[CLS:CFileDlg]
Type=0
HeaderFile=FileDlg.h
ImplementationFile=FileDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDB_SELECT
VirtualFilter=dWC

[DLG:IDD_FILE_DSN_MEDIUM]
Type=1
Class=?
ControlCount=5
Control1=IDE_DSN,edit,1350568064
Control2=IDB_SELECT,button,1342242817
Control3=IDC_STATIC,static,1342308352
Control4=IDB_CREATE,button,1342373889
Control5=IDB_CHANGE,button,1342177280

[DLG:IDD_USER_DSN_MEDIUM]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_DSN,combobox,1344340227
Control3=IDB_CREATE,button,1342373889
Control4=IDB_CHANGE,button,1342177280

[DLG:IDD_INPUT_WHERE_PAGE]
Type=1
Class=CWherePage
ControlCount=16
Control1=IDC_STATIC,static,1342308352
Control2=IDC_TAB_DSN,SysTabControl32,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDL_FILTER_TABLES,combobox,1478557954
Control5=IDC_STATIC,static,1342308352
Control6=IDL_FILTER_FELD,combobox,1478557954
Control7=IDB_CONTENTS,button,1476460544
Control8=IDC_STATIC,static,1342308352
Control9=IDL_FILTER_FUNKT,combobox,1478557698
Control10=IDC_STATIC,static,1342308352
Control11=IDL_FILTER_OPERA,combobox,1478557698
Control12=IDC_STATIC,static,1342308352
Control13=IDT_IMP_FILTER_DESCR,edit,1352665092
Control14=IDC_STATIC,static,1342308352
Control15=IDE_FILTER_KLAUSEL,edit,1486946372
Control16=IDB_FILTER_CHECK,button,1476460545

[CLS:CWherePage]
Type=0
HeaderFile=WherePge.h
ImplementationFile=WherePge.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CWherePage

[DLG:IDD_FIELD_CONTENT]
Type=1
Class=CFieldContentsDlg
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDT_FELDNAME,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDT_FELD_TYP,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDL_FELD_CONTENTS,listbox,1353777409
Control7=IDOK,button,1476591617
Control8=IDCANCEL,button,1342177280

[CLS:CFieldContentsDlg]
Type=0
HeaderFile=FContDlg.h
ImplementationFile=FContDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CFieldContentsDlg

[CLS:CToolTipButton]
Type=0
HeaderFile=\Triasdev\inc.hpp\tooltipb.h
ImplementationFile=tooltipb.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=CToolTipButton

[DLG:IDD_INPUT_WHERE_PAGE1]
Type=1
Class=?
ControlCount=16
Control1=IDC_STATIC,static,1342308352
Control2=IDC_TAB_DSN,SysTabControl32,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDL_FILTER_TABLES,combobox,1478557954
Control5=IDC_STATIC,static,1342308352
Control6=IDL_FILTER_FELD,combobox,1478557954
Control7=IDB_CONTENTS,button,1476460544
Control8=IDC_STATIC,static,1342308352
Control9=IDL_FILTER_FUNKT,combobox,1478557698
Control10=IDC_STATIC,static,1342308352
Control11=IDL_FILTER_OPERA,combobox,1478557698
Control12=IDC_STATIC,static,1342308352
Control13=IDT_IMP_FILTER_DESCR,edit,1352665092
Control14=IDC_STATIC,static,1342308352
Control15=IDE_FILTER_KLAUSEL,edit,1486946372
Control16=IDB_FILTER_CHECK,button,1476460545

[DLG:IDD_INPUT_WHERE_PAGE2]
Type=1
Class=CWherePage
ControlCount=16
Control1=IDC_STATIC,static,1342308352
Control2=IDC_TAB_DSN,SysTabControl32,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDL_FILTER_TABLES,combobox,1478557954
Control5=IDC_STATIC,static,1342308352
Control6=IDL_FILTER_FELD,combobox,1478557954
Control7=IDB_CONTENTS,button,1476460544
Control8=IDC_STATIC,static,1342308352
Control9=IDL_FILTER_FUNKT,combobox,1478557698
Control10=IDC_STATIC,static,1342308352
Control11=IDL_FILTER_OPERA,combobox,1478557698
Control12=IDC_STATIC,static,1342308352
Control13=IDT_IMP_FILTER_DESCR,edit,1352665092
Control14=IDC_STATIC,static,1342308352
Control15=IDE_FILTER_KLAUSEL,edit,1486946372
Control16=IDB_FILTER_CHECK,button,1476460545

[DLG:IDD_RECH_STATUS]
Type=1
Class=CRechStat
ControlCount=3
Control1=IDC_STATIC,static,1342308354
Control2=IDT_RECORD_NUMBER,static,1342308352
Control3=IDCANCEL,button,1342242817

[CLS:CRechStat]
Type=0
HeaderFile=RechStat.h
ImplementationFile=RechStat.cpp
BaseClass=CDialog
Filter=D
LastObject=CRechStat
VirtualFilter=dWC

[CLS:CWhereSet]
Type=0
HeaderFile=WhereSet.h
ImplementationFile=WhereSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CWhereSet

[DB:CWhereSet]
DB=1
DBType=ODBC
ColumnCount=10
Column1=[Tabelle1].[Ident], 12, 10
Column2=[Tabelle1].[Objektnummer], 12, 10
Column3=[Tabelle1].[NumAttrInt], 5, 2
Column4=[Tabelle1].[NumAttrFloat], 8, 8
Column5=[Tabelle1].[Flaeche], 8, 8
Column6=[Tabelle2].[Ident], 12, 10
Column7=[Tabelle2].[Objektnummer], 12, 10
Column8=[Tabelle2].[NumAttrInt], 5, 2
Column9=[Tabelle2].[NumAttrFloat], 8, 8
Column10=[Tabelle2].[Flaeche], 8, 8

[CLS:CAutoListComboBox]
Type=0
HeaderFile=AutoListComboBox.h
ImplementationFile=AutoListComboBox.cpp
BaseClass=CComboBox
Filter=W
VirtualFilter=cWC
LastObject=65535

[ACL:IDR_ACCELERATOR1]
Type=1
Class=?
Command1=IDM_COPY
CommandCount=1

[CLS:CDerivedGrid]
Type=0
HeaderFile=DerivedGrid.h
ImplementationFile=DerivedGrid.cpp
BaseClass=generic CWnd
Filter=W
LastObject=CDerivedGrid

[MNU:IDM_ODBCBACKUP]
Type=1
Class=?
Command1=IDM_ODBCENTRY
Command2=IDM_CALL_ADMIN
Command3=IDM_IMPORT_PARAM
Command4=IDM_OPTIMIZE
CommandCount=4

[MNU:IDR_VIEW_FRAMEBACKUP]
Type=1
Class=?
Command1=IDM_FIRSTFIELD
Command2=IDM_LASTFIELD
Command3=IDM_FIRSTRECORD
Command4=IDM_PREVRECORD
Command5=IDM_NEXTRECORD
Command6=IDM_LASTRECORD
Command7=IDM_COPY
Command8=IDM_FIELDINFO
Command9=ID_FILE_SAVE_AS
CommandCount=9

[MNU:IDM_VIEW_FRAME]
Type=1
Class=?
Command1=ID_EDIT_UNDO
Command2=ID_EDIT_REDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=IDD_ASC
Command7=IDD_DESC
Command8=IDM_FIELDINFO
Command9=ID_FILE_SAVE_AS
CommandCount=9

[DLG:IDD_VIEW_FRAME]
Type=1
Class=?
ControlCount=2
Control1=IDL_ROWLIST,listbox,1353777537
Control2=IDC_GRID,GXWND,1350631424

[MNU:IDM_VIEW_FRAMEBACKUP]
Type=1
Class=?
Command1=IDM_FIRSTFIELD
Command2=IDM_LASTFIELD
Command3=IDM_FIRSTRECORD
Command4=IDM_PREVRECORD
Command5=IDM_NEXTRECORD
Command6=IDM_LASTRECORD
Command7=IDM_COPY
Command8=IDM_FIELDINFO
Command9=ID_FILE_SAVE_AS
CommandCount=9

[DLG:IDD_ABGL_RESULT (_DEBUG)]
Type=1
Class=CResultPage
ControlCount=23
Control1=IDC_STATIC,static,1342308354
Control2=IDC_STATIC,static,1342308354
Control3=IDC_STATIC,static,1342308354
Control4=IDC_STATIC,static,1342308354
Control5=IDC_STATIC,static,1342308354
Control6=IDC_STATIC,static,1342308354
Control7=IDC_STATIC,static,1342308354
Control8=IDC_STATIC,static,1342308354
Control9=IDC_STATIC,static,1342308354
Control10=IDE_IMP_RES_OBJKL,edit,1352665092
Control11=IDC_IMP_RES_DEF,static,1342308352
Control12=IDC_IMP_RES_OBJMERKM,static,1342308352
Control13=IDC_IMP_RES_DSN,static,1342308352
Control14=IDC_IMP_RES_TABLE,static,1342308352
Control15=IDC_IMP_RES_KOPPELF,static,1342308352
Control16=IDC_IMP_RES_RECHTSW,static,1342308352
Control17=IDC_IMP_RES_HOCHW,static,1342308352
Control18=IDC_IMP_RES_FILTER,static,1342308352
Control19=IDC_STATIC,static,1342308354
Control20=IDC_IMP_RES_NOTEXISTS,static,1342308352
Control21=IDC_IMP_RES_ADD,static,1342308352
Control22=IDC_IMP_RES_AKTION,static,1342308352
Control23=IDC_STATIC,static,1342308352

[DLG:IDD_ABGLEICH (_DEBUG)]
Type=1
Class=CAbgleichPage
ControlCount=3
Control1=65535,static,1342308352
Control2=IDL_ABGLEICH,listbox,1352728835
Control3=IDE_ABGLEICH,edit,1350631552

[DLG:IDD_IMP_DOABGLEICH (_DEBUG)]
Type=1
Class=CDoAbgleich
ControlCount=4
Control1=IDT_IMP_ABGLEICH_INFO,static,1342308352
Control2=IDC_IMP_PROGRESS,msctls_progress32,1342177280
Control3=65535,static,1342308352
Control4=65535,static,1342308352

[DLG:IDD_TRIAS (_DEBUG)]
Type=1
Class=CTriasPage
ControlCount=6
Control1=65535,static,1342308352
Control2=65535,static,1342308352
Control3=IDL_IMP_OBJ_KLASSEN,SysListView32,1350631425
Control4=65535,static,1342308352
Control5=65535,static,1342308352
Control6=IDL_OBJ_MERKM_LIST,SysListView32,1350631429

[DLG:IDD_IMP_ABGL_RES2 (_DEBUG)]
Type=1
Class=CImportResult2
ControlCount=13
Control1=IDT_IMP_RES_ABGL,static,1342308354
Control2=IDT_IMP_RES_ERR,static,1342308354
Control3=IDT_IMP_RES_DOPP_TRIAS,static,1342308354
Control4=IDT_IMP_RES_NEW,static,1342308354
Control5=IDB_IMP_RES_PROT,button,1342242816
Control6=IDT_IMP_RES_DEL,static,1342308354
Control7=IDT_IMP_RES_VABGL,static,1342308352
Control8=IDT_IMP_RES_VNEW,static,1342308352
Control9=IDT_IMP_RES_VDEL,static,1342308352
Control10=IDT_IMP_RES_VERR,static,1342308352
Control11=IDT_IMP_RES_VDOPP_TRIAS,static,1342308352
Control12=IDT_IMP_RES_VDOPP_TABLE,static,1342308352
Control13=IDT_IMP_RES_DOPP_TABLE,static,1342308354

