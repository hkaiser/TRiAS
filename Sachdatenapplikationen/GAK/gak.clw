; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDaoRecordViewExt
LastTemplate=CRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "gak.h"
LastPage=0

ClassCount=90
Class1=CAbfView
Class2=CAbfallParam
Class3=CAbfallSet
Class4=CAbfArtSet
Class5=CAbfartSet
Class6=CAbfartParams
Class7=CAbfDoc
Class8=CAbfFrame
Class9=CAbfPage
Class10=CAbfSet
Class11=CAbfSetExport
Class12=CAbfSheet
Class13=CAboutDlg
Class14=CAfiDlg
Class15=CAnfallStelle
Class16=CBetreiberPage
Class17=CBgsSet
Class18=CBgsSetRed
Class19=CBrancheParam
Class20=CBranchPage
Class21=CChangeNummerDlg
Class22=CChildFrame
Class23=CColumns
Class24=CCompactDataBase
Class25=CDoAbgleich
Class26=CDocumentExt
Class27=CDoImportPage
Class28=CEditExt
Class29=CEnterNr
Class30=CEntPage
Class31=CEntsorger1
Class32=CEntsPage
Class33=CEntsorgerSet
Class34=CErzeugerSet
Class35=CErzFrame
Class36=CErzInfo
Class37=CErzListeSet
Class38=CErzeugerParam
Class39=CErzeugerSheet
Class40=CExportResultDlg
Class41=CFeldInfos
Class42=CFirmaSet
Class43=CFirmaPage
Class44=CGakApp
Class45=CGakDoc
Class46=CGakSet
Class47=CGakSetRed
Class48=CDaoRecordsetExt
Class49=CGakView
Class50=CGebietParam
Class51=CImportParamPage
Class52=CImportQueryDialog
Class53=CImportResultPage
Class54=CImportDlg
Class55=CImportSumPage
Class56=CInputTablePage
Class57=CKreisSet
Class58=CListBoxExt
Class59=CMainFrame
Class60=CNewQueryDef
Class61=CNumEdit
Class62=CRealEdit
Class63=CErzNrEdit
Class64=COutputSet
Class65=COutputTablePage
Class66=CParameters
Class67=CPartnerPage
Class68=CProgress
Class69=CQueryDialog
Class70=CEnterQueryParam
Class71=CQueryParams
Class72=CQueryResult
Class73=CDaoRecordViewExt
Class74=CReportTable
Class75=CResultDialog
Class76=CResultParam
Class77=CSearchSet
Class78=CSearchResult
Class79=CSelectExportTables
Class80=CSelNumberDlg
Class81=CSelectSet
Class82=CSelTable
Class83=CStatusBarExt
Class84=CStatistikDialog
Class85=CTableNameDlg
Class86=CTranspPage
Class87=CTranspSet
Class88=CUserInfoDlg

ResourceCount=51
Resource1=IDD_ENTSORGER
Resource2=IDD_PARAMS
Resource3=IDD_DOABGLEICH
Resource4=IDD_BETREIBER
Resource5=IDD_QUERY_SELECT
Resource6=IDD_STATISTIK
Resource7=IDD_IMPORT_INPUT
Resource8=IDD_ABFART_PARAMS
Resource9=IDD_FIRMA
Resource10=IDD_IMPORT_RESULT
Resource11=IDD_DO_IMPORT
Resource12=IDD_ANFALLSTELLE
Resource13=IDD_SEL_NUMMER
Resource14=IDD_GEBIET_PARAM
Resource15=IDD_TRANSPORTEUR
Resource16=IDD_ENTSORGER1
Resource17=IDD_ERZEUGER_PARAM
Resource18=IDD_QUERY_RESULT
Resource19=IDD_EXPORT_RESULT
Resource20=IDD_GAK_FORM
Resource21=IDD_AFI
Resource22=IDD_RESULT
Resource23=IDD_BRANCHE
Resource24=IDD_ABFALL_PARAM
Resource25=IDD_REPORT_TABLE
Resource26=IDD_ENTSORGUNG
Resource27=IDD_COMPACT_DATABASE
Resource28=IDD_QUERY_DEF
Resource29=IDD_IMPORT_SUM
Resource30=IDD_INPUT_TABLE_NAME
Resource31=IDD_EXPORT_TABLES
Resource32=IDD_IMPORT_QUERY
Resource33=IDM_POPUP
Resource34=IDD_ANSPRECH
Resource35=IDD_RECHERCHESTATUS
Resource36=IDD_DOKONTROLLE
Resource37=IDD_CHANGE_ERZ_NR
Resource38=IDR_MAINFRAME
Resource39=IDD_QUERY_PARAM
Resource40=IDD_RECORDS_SELECT
Resource41=IDD_USER_NAME
Resource42=IDR_GAKTYPE
Resource43=IDD_SEARCH_RESULT
Resource44=IDD_LOOK_NR
Resource45=IDD_BRANCHE_PARAM
Resource46=IDD_RESULT_PARAM
Resource47=IDD_ERZ_INFO
Resource48=IDD_ABFAELLE
Resource49=IDD_FELDINFO
Resource50=IDD_OUTPUT_TABLE
Class89=CSelNumberDlgUsage
Class90=CTestRS
Resource51=IDD_SELECT_TABLE

[CLS:CAbfView]
Type=0
BaseClass=CDaoRecordViewExt
HeaderFile=ABFVIEW.H
ImplementationFile=_ABFVIEW.CPP

[CLS:CAbfallParam]
Type=0
BaseClass=CPropertyPage
HeaderFile=ABFALLP.H
ImplementationFile=ABFALLP.CPP
LastObject=CAbfallParam

[CLS:CAbfallSet]
Type=0
HeaderFile=ABFALSET.H
ImplementationFile=ABFALSET.CPP
Filter=N

[CLS:CAbfArtSet]
Type=0
HeaderFile=ABFARSET.H
ImplementationFile=ABFARSET.CPP

[CLS:CAbfartSet]
Type=0
HeaderFile=ABFARSETODBC.H
ImplementationFile=ABFARSETODBC.CPP

[CLS:CAbfartParams]
Type=0
BaseClass=CSelNumberDlgUsage
HeaderFile=ABFARTPA.H
ImplementationFile=ABFARTPA.CPP
LastObject=CAbfartParams
Filter=D
VirtualFilter=dWC

[CLS:CAbfDoc]
Type=0
BaseClass=CDocumentExt
HeaderFile=ABFDOC.H
ImplementationFile=ABFDOC.CPP

[CLS:CAbfFrame]
Type=0
BaseClass=CChildFrame
HeaderFile=ABFFRAME.H
ImplementationFile=ABFFRAME.CPP

[CLS:CAbfPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=ABFPAGE.H
ImplementationFile=ABFPAGE.CPP
LastObject=CAbfPage

[CLS:CAbfSet]
Type=0
HeaderFile=ABFSET.H
ImplementationFile=Abfset.cpp
LastObject=CAbfSet

[CLS:CAbfSetExport]
Type=0
HeaderFile=ABFSETEX.H
ImplementationFile=ABFSETEX.CPP

[CLS:CAbfSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=ABFSHEET.H
ImplementationFile=ABFSHEET.CPP

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ABOUT.H
ImplementationFile=ABOUT.CPP

[CLS:CAfiDlg]
Type=0
BaseClass=CDialog
HeaderFile=afidlg.h
ImplementationFile=afidlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_ONLYNOTEXPORTED

[CLS:CAnfallStelle]
Type=0
BaseClass=CPropertyPage
HeaderFile=ANFPAGE.H
ImplementationFile=ANFPAGE.CPP

[CLS:CBetreiberPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=BETRPAGE.H
ImplementationFile=BETRPAGE.CPP

[CLS:CBgsSet]
Type=0
HeaderFile=BGSSET.H
ImplementationFile=BGSSET.CPP

[CLS:CBgsSetRed]
Type=0
HeaderFile=BGSSET.H
ImplementationFile=BGSSET.CPP

[CLS:CBrancheParam]
Type=0
BaseClass=CPropertyPage
HeaderFile=BrancheP.h
ImplementationFile=BrancheP.cpp

[CLS:CBranchPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=BranPage.h
ImplementationFile=BranPage.cpp

[CLS:CChangeNummerDlg]
Type=0
BaseClass=CDialog
HeaderFile=CHANGENR.H
ImplementationFile=CHANGENR.CPP

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=CHILDFRM.H
ImplementationFile=CHILDFRM.CPP

[CLS:CColumns]
Type=0
HeaderFile=COLUMNST.H
ImplementationFile=COLUMNST.CPP

[CLS:CCompactDataBase]
Type=0
BaseClass=CDialog
HeaderFile=COMPACT.H
ImplementationFile=COMPACT.CPP

[CLS:CDoAbgleich]
Type=0
BaseClass=CDialog
HeaderFile=DOABGLEI.H
ImplementationFile=DOABGLEI.CPP
LastObject=IDB_ESCAPE
Filter=D
VirtualFilter=dWC

[CLS:CDocumentExt]
Type=0
BaseClass=CDocument
HeaderFile=DOCUMEXT.H
ImplementationFile=DOCUMEXT.CPP

[CLS:CDoImportPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=DOIMPPGE.H
ImplementationFile=DOIMPPGE.CPP

[CLS:CEditExt]
Type=0
BaseClass=CEdit
HeaderFile=EDITEXT.H
ImplementationFile=EDITEXT.CPP

[CLS:CEnterNr]
Type=0
BaseClass=CDialog
HeaderFile=ENTERNR.H
ImplementationFile=ENTERNR.CPP

[CLS:CEntPage]
Type=0
BaseClass=CEntsorger1
HeaderFile=EntPage.h
ImplementationFile=ENTPAGE.CPP
LastObject=CEntPage
Filter=N

[CLS:CEntsorger1]
Type=0
BaseClass=CBranchPage
HeaderFile=Entsorger1.h
ImplementationFile=Entsorger1.cpp

[CLS:CEntsPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=ENTSPAGE.H
ImplementationFile=ENTSPAGE.CPP

[CLS:CEntsorgerSet]
Type=0
HeaderFile=ENTSSET.H
ImplementationFile=ENTSSET.CPP

[CLS:CErzeugerSet]
Type=0
HeaderFile=ERZEUSET.H
ImplementationFile=ERZEUSET.CPP

[CLS:CErzFrame]
Type=0
BaseClass=CChildFrame
HeaderFile=ERZFRAME.H
ImplementationFile=ERZFRAME.CPP

[CLS:CErzInfo]
Type=0
BaseClass=CDialog
HeaderFile=ERZINFO.H
ImplementationFile=ERZINFO.CPP
Filter=D
VirtualFilter=dWC
LastObject=CErzInfo

[CLS:CErzListeSet]
Type=0
HeaderFile=ERZLISTE.H
ImplementationFile=ERZLISTE.CPP

[CLS:CErzeugerParam]
Type=0
BaseClass=CPropertyPage
HeaderFile=ERZPAR.H
ImplementationFile=ERZPAR.CPP

[CLS:CErzeugerSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=ERZSHEET.H
ImplementationFile=ERZSHEET.CPP

[CLS:CExportResultDlg]
Type=0
BaseClass=CDialog
HeaderFile=EXPORTRE.H
ImplementationFile=EXPORTRE.CPP

[CLS:CFeldInfos]
Type=0
BaseClass=CDialog
HeaderFile=FELDINFO.H
ImplementationFile=FELDINFO.CPP

[CLS:CFirmaSet]
Type=0
HeaderFile=FIRMASET.H
ImplementationFile=FIRMASET.CPP

[CLS:CFirmaPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=FIRMPAGE.H
ImplementationFile=FIRMPAGE.CPP

[CLS:CGakApp]
Type=0
BaseClass=CWinApp
HeaderFile=GAK.H
ImplementationFile=gak.cpp

[CLS:CGakDoc]
Type=0
BaseClass=CDocumentExt
HeaderFile=GAKDOC.H
ImplementationFile=GAKDOC.CPP

[CLS:CGakSet]
Type=0
HeaderFile=GAKSET.H
ImplementationFile=GAKSET.CPP

[CLS:CGakSetRed]
Type=0
HeaderFile=GAKSET.H
ImplementationFile=GAKSET.CPP

[CLS:CDaoRecordsetExt]
Type=0
HeaderFile=GAKSETE.H
ImplementationFile=GAKSETE.CPP

[CLS:CGakView]
Type=0
BaseClass=CDaoRecordViewExt
HeaderFile=gakView.h
ImplementationFile=gakView.cpp
LastObject=CGakView

[CLS:CGebietParam]
Type=0
BaseClass=CPropertyPage
HeaderFile=GEBIETP.H
ImplementationFile=GEBIETP.CPP

[CLS:CImportParamPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=IMPPARPG.H
ImplementationFile=IMPPARPG.CPP

[CLS:CImportQueryDialog]
Type=0
BaseClass=CDialog
HeaderFile=IMPQUERY.H
ImplementationFile=IMPQUERY.CPP

[CLS:CImportResultPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=IMPRESPG.H
ImplementationFile=IMPRESPG.CPP

[CLS:CImportDlg]
Type=0
BaseClass=CPropertySheet
HeaderFile=IMPRTDLG.H
ImplementationFile=IMPRTDLG.CPP

[CLS:CImportSumPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=IMPSUMPG.H
ImplementationFile=IMPSUMPG.CPP

[CLS:CInputTablePage]
Type=0
BaseClass=CPropertyPage
HeaderFile=INTABLPG.H
ImplementationFile=INTABLPG.CPP

[CLS:CKreisSet]
Type=0
HeaderFile=KREISSET.H
ImplementationFile=KREISSET.CPP

[CLS:CListBoxExt]
Type=0
BaseClass=CListBox
HeaderFile=LISTEXT.H
ImplementationFile=LISTEXT.CPP

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=MAINFRM.H
ImplementationFile=Mainfrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=IDM_ODBC_ACESS

[CLS:CNewQueryDef]
Type=0
BaseClass=CDialog
HeaderFile=NEWQUERY.H
ImplementationFile=NEWQUERY.CPP

[CLS:CNumEdit]
Type=0
BaseClass=CEdit
HeaderFile=NUMEDIT.H
ImplementationFile=NUMEDIT.CPP

[CLS:CRealEdit]
Type=0
BaseClass=CNumEdit
HeaderFile=NUMEDIT.H
ImplementationFile=NUMEDIT.CPP

[CLS:CErzNrEdit]
Type=0
BaseClass=CNumEdit
HeaderFile=NUMEDIT.H
ImplementationFile=NUMEDIT.CPP

[CLS:COutputSet]
Type=0
HeaderFile=OUTSET.H
ImplementationFile=OUTSET.CPP

[CLS:COutputTablePage]
Type=0
BaseClass=CPropertyPage
HeaderFile=OUTTBPG.H
ImplementationFile=OUTTBPG.CPP

[CLS:CParameters]
Type=0
BaseClass=CDialog
HeaderFile=PARAMS.H
ImplementationFile=PARAMS.CPP

[CLS:CPartnerPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=PARTPAGE.H
ImplementationFile=PARTPAGE.CPP

[CLS:CProgress]
Type=0
BaseClass=CDialog
HeaderFile=PROGRESS.H
ImplementationFile=PROGRESS.CPP

[CLS:CQueryDialog]
Type=0
BaseClass=CDialog
HeaderFile=QUERYDLG.H
ImplementationFile=Querydlg.cpp

[CLS:CEnterQueryParam]
Type=0
BaseClass=CDialog
HeaderFile=QUERYPAR.H
ImplementationFile=Querypar.cpp

[CLS:CQueryParams]
Type=0
BaseClass=CPropertySheet
HeaderFile=QUERYPAR.H
ImplementationFile=Querypar.cpp

[CLS:CQueryResult]
Type=0
BaseClass=CDialog
HeaderFile=QUERYRES.H
ImplementationFile=Queryres.cpp

[CLS:CDaoRecordViewExt]
Type=0
BaseClass=CDaoRecordView
HeaderFile=recview.h
ImplementationFile=recview.cpp
LastObject=IDB_ABGLEICH
Filter=D
VirtualFilter=XRVWC

[CLS:CReportTable]
Type=0
BaseClass=CDialog
HeaderFile=REPTABLE.H
ImplementationFile=REPTABLE.CPP
Filter=D
VirtualFilter=dWC
LastObject=CReportTable

[CLS:CResultDialog]
Type=0
BaseClass=CDialog
HeaderFile=RESDLG.H
ImplementationFile=RESDLG.CPP
LastObject=IDOK

[CLS:CResultParam]
Type=0
BaseClass=CPropertyPage
HeaderFile=RESULTP.H
ImplementationFile=RESULTP.CPP

[CLS:CSearchSet]
Type=0
HeaderFile=SEARCHSE.H
ImplementationFile=SEARCHSE.CPP

[CLS:CSearchResult]
Type=0
BaseClass=CDialog
HeaderFile=SEARRES.H
ImplementationFile=SEARRES.CPP

[CLS:CSelectExportTables]
Type=0
BaseClass=CDialog
HeaderFile=SELECTEX.H
ImplementationFile=SELECTEX.CPP

[CLS:CSelNumberDlg]
Type=0
BaseClass=CDialog
HeaderFile=SELNUM.H
ImplementationFile=SELNUM.CPP

[CLS:CSelectSet]
Type=0
HeaderFile=SELSET.H
ImplementationFile=SELSET.CPP

[CLS:CSelTable]
Type=0
BaseClass=CDialog
HeaderFile=SELTABLE.H
ImplementationFile=seltable.cpp

[CLS:CStatusBarExt]
Type=0
BaseClass=CStatusBar
HeaderFile=STATBARE.H
ImplementationFile=STATBARE.CPP

[CLS:CStatistikDialog]
Type=0
BaseClass=CDialog
HeaderFile=STATDLG.H
ImplementationFile=STATDLG.CPP

[CLS:CTableNameDlg]
Type=0
BaseClass=CDialog
HeaderFile=Tablndlg.h
ImplementationFile=TablNDlg.cpp

[CLS:CTranspPage]
Type=0
BaseClass=CBranchPage
HeaderFile=TRANSPGE.H
ImplementationFile=TRANSPGE.CPP

[CLS:CTranspSet]
Type=0
HeaderFile=TRANSSET.H
ImplementationFile=TRANSSET.CPP

[CLS:CUserInfoDlg]
Type=0
BaseClass=CDialog
HeaderFile=USERINFO.H
ImplementationFile=USERINFO.CPP

[DB:CAbfallSet]
DB=1

[DB:CAbfArtSet]
DB=1

[DB:CAbfartSet]
DB=1

[DB:CAbfSet]
DB=1

[DB:CAbfSetExport]
DB=1

[DB:CBgsSet]
DB=1

[DB:CBgsSetRed]
DB=1

[DB:CColumns]
DB=1

[DB:CEntsorgerSet]
DB=1

[DB:CErzeugerSet]
DB=1

[DB:CAbgleichCntSet]
DB=1

[DB:CErzListeSet]
DB=1

[DB:CFirmaSet]
DB=1

[DB:CGakSet]
DB=1

[DB:CGakSetRed]
DB=1

[DB:CDaoRecordsetExt]
DB=1

[DB:CKreisSet]
DB=1

[DB:COutputSet]
DB=1

[DB:CSearchSet]
DB=1

[DB:CSelectSet]
DB=1

[DB:CTables]
DB=1

[DB:CTranspSet]
DB=1

[DLG:IDD_ABFALL_PARAM]
Type=1
Class=CAbfallParam
ControlCount=12
Control1=IDB_ONLY_SONDER_ABF,button,1342373891
Control2=IDC_STATIC,button,1342177287
Control3=IDB_ALL_ABF,button,1342373891
Control4=IDC_STATIC,static,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDE_ABFART,edit,1350770816
Control7=IDB_SELECT,button,1342373889
Control8=IDC_STATIC,static,1342308352
Control9=IDE_ABF_BEZ,edit,1352665092
Control10=IDC_STATIC,static,1342177287
Control11=IDC_STATIC,static,1342308354
Control12=IDE_MENGE,edit,1350762624

[DLG:IDD_ABFART_PARAMS]
Type=1
Class=CAbfartParams
ControlCount=39
Control1=IDE_ABFALLART,edit,1484849280
Control2=IDE_ENSN_NR,edit,1350631552
Control3=IDE_MENGE2,edit,1350631552
Control4=IDE_TRANSPORTEUR,edit,1350631552
Control5=IDC_SELECTBEFOERD,button,1342242816
Control6=IDE_ENTSORGER,edit,1350631552
Control7=IDC_SELECTENTSORG,button,1342242816
Control8=IDE_RD_VERFAHREN,edit,1350631552
Control9=IDE_PRIO,edit,1350639744
Control10=IDOK,button,1476591617
Control11=IDCANCEL,button,1342177280
Control12=IDC_STATIC,static,1342308354
Control13=IDC_STATIC,static,1342308354
Control14=IDC_STATIC,static,1342308354
Control15=IDC_STATIC,static,1342308354
Control16=IDC_STATIC,static,1342308354
Control17=IDC_ABFALLBEZ,static,1342312960
Control18=IDC_BEFOERDNAME,static,1342312960
Control19=IDC_BEFOERDORT,static,1342312960
Control20=IDC_BEFOERDSTR,static,1342312960
Control21=IDC_ENTSORGNAME,static,1342312960
Control22=IDC_ENTSORGORT,static,1342312960
Control23=IDC_ENTSORGSTR,static,1342312960
Control24=IDC_STATIC,button,1342177287
Control25=IDC_STATIC,button,1342177287
Control26=IDC_STATIC,static,1342308866
Control27=IDC_STATIC,static,1342308866
Control28=IDC_STATIC,static,1342308866
Control29=IDC_STATIC,static,1342308866
Control30=IDC_STATIC,static,1342308866
Control31=IDC_STATIC,static,1342308866
Control32=IDC_STATIC,static,1342308866
Control33=IDC_STATIC,static,1342308866
Control34=IDC_ENTSORGANLAGE,static,1342312960
Control35=IDC_STATIC,static,1342308866
Control36=IDC_BEFOERDKOMMENTAR,edit,1352730628
Control37=IDC_ENTSORGKOMMENTAR,edit,1352730628
Control38=IDC_STATIC,static,1342308866
Control39=IDC_STATIC,static,1342308866

[DLG:IDD_ABFAELLE]
Type=1
Class=CAbfPage
ControlCount=30
Control1=IDS_ARTEN_INFO,static,1342308352
Control2=IDL_ABFALLART,listbox,1352728835
Control3=IDC_STATIC,static,1342308352
Control4=IDS_SONDER_ABFALL,static,1342177280
Control5=IDB_ARTNEU,button,1342373899
Control6=IDB_ARTDEL,button,1342177291
Control7=IDB_ARTCHA,button,1342177291
Control8=IDC_STATIC,static,1342308352
Control9=IDE_ABFART,edit,1350567940
Control10=IDC_STATIC,static,1342308352
Control11=IDE_INTERNE_BEZ,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDE_EAK_NR,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDE_VERBRINGUNG,edit,1350568064
Control16=IDB_CHANGE,button,1342242817
Control17=IDC_STATIC,static,1342308354
Control18=IDE_NACHWEIS_NR,edit,1350631552
Control19=IDC_STATIC,static,1342177280
Control20=IDE_DICHTE,edit,1350568064
Control21=IDC_STATIC,static,1342308354
Control22=IDE_VERFAHREN,edit,1350568064
Control23=IDB_CHANGE_VERF,button,1342242816
Control24=IDC_STATIC,static,1342308352
Control25=IDE_MENGET,edit,1350631552
Control26=IDC_STATIC,static,1342308354
Control27=IDE_MENGEM,edit,1350631552
Control28=IDB_VORBEHANDLUNG,button,1342242819
Control29=IDC_STATIC,static,1342308352
Control30=IDE_COMMENT,edit,1352728580

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_AFI]
Type=1
Class=CAfiDlg
ControlCount=9
Control1=IDB_AFIS,button,1342177289
Control2=IDC_AFIS,combobox,1344340226
Control3=IDC_STATIC,static,1342177287
Control4=IDB_KREISE,button,1342177289
Control5=IDC_KREISE,combobox,1344340226
Control6=IDB_SONDER_ABF,button,1342242819
Control7=IDOK,button,1476591617
Control8=IDCANCEL,button,1342177280
Control9=IDC_ONLYNOTEXPORTED,button,1342242819

[DLG:IDD_ANFALLSTELLE]
Type=1
Class=CAnfallStelle
ControlCount=19
Control1=IDC_STATIC,static,1342308354
Control2=IDE_ANFALLSTELLE,edit,1350631552
Control3=IDC_STATIC,static,1342308354
Control4=IDE_BETRIEB,edit,1350631552
Control5=IDC_STATIC,static,1342308354
Control6=IDE_STRASSE,edit,1350631552
Control7=IDC_STATIC,static,1342308354
Control8=IDE_HNR,edit,1350631552
Control9=IDC_STATIC,static,1342308354
Control10=IDE_PLZ,edit,1350639744
Control11=IDC_STATIC,static,1342308354
Control12=IDE_ORT,edit,1350568064
Control13=IDB_CHANGE,button,1342242817
Control14=IDC_STATIC,static,1342308354
Control15=IDE_GKZ,edit,1350568064
Control16=IDC_STATIC,static,1342308354
Control17=IDE_KREIS_KUERZEL,edit,1350568072
Control18=IDC_STATIC,static,1342308354
Control19=IDE_COMMENT,edit,1352728580

[DLG:IDD_BETREIBER]
Type=1
Class=CBetreiberPage
ControlCount=4
Control1=IDC_STATIC,static,1342308354
Control2=IDE_NUMMER,edit,1350631552
Control3=IDC_STATIC,static,1342308354
Control4=IDE_NAME,edit,1352728580

[DLG:IDD_BRANCHE_PARAM]
Type=1
Class=CBrancheParam
ControlCount=7
Control1=IDC_STATIC,static,1342308354
Control2=IDE_NUMMER,edit,1350631552
Control3=IDB_CHANGE,button,1342242817
Control4=IDC_STATIC,static,1342308352
Control5=IDE_NAME,edit,1352665092
Control6=IDB_ALLE,button,1342373891
Control7=IDC_STATIC,static,1342177287

[DLG:IDD_BRANCHE]
Type=1
Class=CBranchPage
ControlCount=5
Control1=IDB_CHANGE,button,1342242817
Control2=IDC_STATIC,static,1342308354
Control3=IDE_NUMMER,edit,1350568064
Control4=IDC_STATIC,static,1342308354
Control5=IDE_NAME,edit,1352665092

[DLG:IDD_CHANGE_ERZ_NR]
Type=1
Class=CChangeNummerDlg
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDE_NUMMER,edit,1350631560
Control3=IDS_INFOTEXT,static,1342308352
Control4=IDL_NUMMERN_ERZ,listbox,1352728833
Control5=IDOK,button,1476460545
Control6=IDCANCEL,button,1342177280

[DLG:IDD_COMPACT_DATABASE]
Type=1
Class=CCompactDataBase
ControlCount=11
Control1=IDC_STATIC,button,1342177287
Control2=IDB_FILE_NAME,button,1342242816
Control3=IDE_FILENAME,edit,1350633600
Control4=IDB_AS_NEW,button,1342177283
Control5=IDC_STATIC,button,1342177287
Control6=IDB_VERSION10,button,1342242825
Control7=IDB_VERSION11,button,1342177289
Control8=IDB_VERSION20,button,1342177289
Control9=IDB_VERSION30,button,1342177289
Control10=IDOK,button,1342242817
Control11=IDCANCEL,button,1342177280

[DLG:IDD_DOABGLEICH]
Type=1
Class=CDoAbgleich
ControlCount=21
Control1=IDC_STATIC,static,1342308352
Control2=IDL_ABFALL_VJN,SysListView32,1476493317
Control3=IDC_STATIC,static,1342308352
Control4=IDL_ABFALLN,SysListView32,1476493313
Control5=IDC_STATIC,static,1342308352
Control6=IDL_BGSN,SysListView32,1476493313
Control7=IDT_AKTION,static,1342177280
Control8=IDT_PROGRESS2,msctls_progress32,1350565888
Control9=IDOK,button,1342373889
Control10=IDB_ESCAPE,button,1476395008
Control11=IDB_INLISTE,button,1476395008
Control12=ID_HELP,button,1207959552
Control13=IDB_ERZ_INFO,button,1476395008
Control14=IDCANCEL,button,1342177280
Control15=IDB_WEITER,button,1476395008
Control16=IDC_STATIC,static,1342308864
Control17=IDC_STATIC,static,1342308864
Control18=IDC_STATIC,static,1342308864
Control19=IDC_STATIC,static,1342308864
Control20=IDC_ANFALLSTELLE,static,1342312960
Control21=IDC_BRANCHENNUMMER,static,1342312960

[DLG:IDD_DO_IMPORT]
Type=1
Class=CDoImportPage
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDS_AKTION,static,1342308352
Control4=IDC_PROGRESS,msctls_progress32,1350565888

[DLG:IDD_LOOK_NR]
Type=1
Class=CEnterNr
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDE_NUMBER,edit,1350631560
Control4=IDC_STATIC,button,1342177287
Control5=IDB_LIKE,button,1342242825
Control6=IDB_GR_EQ,button,1342177289
Control7=IDB_GR,button,1342177289
Control8=IDB_EQ,button,1342177289
Control9=IDB_LESS,button,1342177289
Control10=IDB_LESS_EQ,button,1342177289
Control11=IDOK,button,1476460545
Control12=IDCANCEL,button,1342242816

[DLG:IDD_ENTSORGER]
Type=1
Class=CEntPage
ControlCount=26
Control1=IDC_STATIC,static,1342308354
Control2=IDE_NUMMER,edit,1350631552
Control3=IDB_CHANGE,button,1342242817
Control4=IDB_EIGEN,button,1342242819
Control5=IDC_STATIC,static,1342308354
Control6=IDE_NAME,edit,1350567936
Control7=IDC_STATIC,static,1342308354
Control8=IDE_ART,edit,1350568064
Control9=IDC_STATIC,static,1342308354
Control10=IDE_STRASSE,edit,1350568064
Control11=IDC_STATIC,static,1342308354
Control12=IDE_PLZ,edit,1350576256
Control13=IDC_STATIC,static,1342308354
Control14=IDE_ORT,edit,1350568064
Control15=IDC_STATIC,static,1342308354
Control16=IDE_PARTNER,edit,1350762624
Control17=IDC_STATIC,static,1342308354
Control18=IDE_TELEFON,edit,1350631552
Control19=IDC_STATIC,static,1342308354
Control20=IDE_TELEFAX,edit,1350631552
Control21=IDB_FREI,button,1342242819
Control22=IDC_STATIC,static,1342308354
Control23=IDE_FREI_NR,edit,1350631552
Control24=IDC_STATIC,static,1342308354
Control25=IDE_BEMERKUNGEN,edit,1352728580
Control26=IDC_COPYCLIPBOARD,button,1342242816

[DLG:IDD_ENTSORGER1]
Type=1
Class=CEntsorger1
ControlCount=7
Control1=IDE_NUMMER,edit,1350631552
Control2=IDB_CHANGE,button,1342242817
Control3=IDC_STATIC,static,1342308352
Control4=IDE_BEMERKUNGEN,edit,1352728580
Control5=IDC_STATIC,static,1342308352
Control6=IDE_NAME,edit,1216350208
Control7=IDC_COPYCLIPBOARD,button,1342242816

[DLG:IDD_ENTSORGUNG]
Type=1
Class=CEntsPage
ControlCount=11
Control1=IDC_STATIC,static,1342308354
Control2=IDE_BIMSCH_NUMMER,edit,1350631552
Control3=IDC_STATIC,static,1342308354
Control4=IDC_SPALTE,combobox,1344340227
Control5=IDC_STATIC,static,1342308354
Control6=IDE_BIMSCH_NUMMERG,edit,1350631552
Control7=IDC_STATIC,static,1342177287
Control8=IDB_LIEGT_VOR,button,1342373891
Control9=IDC_STATIC,static,1342308354
Control10=IDE_ANUMMER,edit,1350762624
Control11=IDC_STATIC,static,1342308352

[DLG:IDD_ERZ_INFO]
Type=1
Class=CErzInfo
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308354
Control3=IDT_BRANCHE,static,1342312448
Control4=IDC_STATIC,static,1342308354
Control5=IDT_ANF_STELLE,static,1342312448
Control6=IDC_STATIC,static,1342308354
Control7=IDT_ANF_ORT,static,1342312448
Control8=IDC_STATIC,static,1342308354
Control9=IDC_STATIC,static,1342308354
Control10=IDC_STATIC,static,1342308354
Control11=IDT_PARTNER,static,1342312448
Control12=IDT_TEL,static,1342312448
Control13=IDT_FAX,static,1342312448
Control14=IDC_STATIC,static,1342308354
Control15=IDT_FIRMA,static,1342312448
Control16=IDT_STRASSE,static,1342312448
Control17=IDC_STATIC,static,1342308354

[DLG:IDD_ERZEUGER_PARAM]
Type=1
Class=CErzeugerParam
ControlCount=5
Control1=IDC_STATIC,static,1342308354
Control2=IDE_ERZ_NR,edit,1350568064
Control3=IDB_ERZEUGER,button,1342242817
Control4=IDC_STATIC,static,1342308352
Control5=IDE_FIRMA,edit,1352665092

[DLG:IDD_EXPORT_RESULT]
Type=1
Class=CExportResultDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308354
Control3=IDC_STATIC,static,1342308354
Control4=IDC_STATIC,static,1342177287
Control5=IDC_STATIC,static,1342308354
Control6=IDC_ERZ_CNT,static,1342308352
Control7=IDC_ABF_CNT,static,1342308352
Control8=IDC_SUM_CNT,static,1342308352

[DLG:IDD_FELDINFO]
Type=1
Class=CFeldInfos
ControlCount=1
Control1=IDC_FELDINFO,SysListView32,1350631429

[DLG:IDD_FIRMA]
Type=1
Class=CFirmaPage
ControlCount=25
Control1=IDC_STATIC,static,1342308354
Control2=IDE_FIRMA,edit,1350631552
Control3=IDC_STATIC,static,1342308354
Control4=IDE_STRASSE,edit,1350631552
Control5=IDC_STATIC,static,1342308354
Control6=IDE_HNR,edit,1350631552
Control7=IDC_STATIC,static,1342308354
Control8=IDE_PLZ,edit,1350639744
Control9=IDC_STATIC,static,1342308354
Control10=IDE_ORT,edit,1350631552
Control11=IDC_STATIC,static,1342308354
Control12=IDB_GET_ADDRESS,button,1342242817
Control13=IDC_STATIC,static,1342177287
Control14=IDC_STATIC,static,1342308354
Control15=IDE_PARTNER,edit,1350631552
Control16=IDC_STATIC,static,1342308354
Control17=IDE_TELEFON,edit,1350631552
Control18=IDC_STATIC,static,1342308354
Control19=IDE_TELEFAX,edit,1350631552
Control20=IDC_STATIC,static,1342177287
Control21=IDC_STATIC,static,1342308354
Control22=IDE_BETREIBER_NR,edit,1350631552
Control23=IDC_STATIC,static,1342308354
Control24=IDE_BILANZ_NR,edit,1350568064
Control25=IDB_UNTERSCHRIFT,button,1342242819

[DLG:IDD_GEBIET_PARAM]
Type=1
Class=CGebietParam
ControlCount=8
Control1=IDB_ALLE_GEMEINDEN,button,1342373891
Control2=IDC_STATIC,static,1342177287
Control3=IDC_STATIC,static,1342177282
Control4=IDE_GKZ,edit,1350770816
Control5=IDB_GEMEINDE_SEL,button,1342373889
Control6=IDB_KREIS_SEL,button,1342177280
Control7=IDC_STATIC,static,1342308354
Control8=IDT_GEMEINDE,static,1342177280

[DLG:IDD_RECORDS_SELECT]
Type=1
Class=CImportParamPage
ControlCount=8
Control1=IDC_STATIC,button,1342177287
Control2=IDB_ALL_RECORDS,button,1342373897
Control3=IDB_ONLY_REFERENZ,button,1342177289
Control4=IDB_ONLY_NOT_REFERENZ,button,1342177289
Control5=IDC_STATIC,button,1342177287
Control6=IDB_ALWAYS_INDEX,button,1342373897
Control7=IDB_ALWAYS_MOD,button,1342177289
Control8=IDB_NEVER_MOD,button,1342177289

[DLG:IDD_IMPORT_QUERY]
Type=1
Class=CImportQueryDialog
ControlCount=5
Control1=IDC_STATIC,static,1342308352
Control2=IDL_QUERIES,listbox,1353779459
Control3=IDB_SELECT,button,1342242819
Control4=IDOK,button,1476591617
Control5=IDCANCEL,button,1342177280

[DLG:IDD_IMPORT_RESULT]
Type=1
Class=CImportResultPage
ControlCount=15
Control1=IDC_STATIC,static,1342308354
Control2=IDS_ACT_CNT,static,1342308352
Control3=IDC_STATIC,static,1342308354
Control4=IDS_NEW_CNT,static,1342308352
Control5=IDC_STATIC,static,1342308354
Control6=IDS_ACT_ERR_CNT,static,1342308352
Control7=IDC_STATIC,static,1342308354
Control8=IDS_NEW_ERR_CNT,static,1342308352
Control9=IDC_STATIC,static,1342177287
Control10=IDC_STATIC,static,1342308354
Control11=IDS_SUM_CNT,static,1342308352
Control12=IDC_STATIC,static,1342308354
Control13=IDS_SUM_ERR_CNT,static,1342308352
Control14=IDB_ERROR_HELP,button,1342177280
Control15=IDB_SHOW_PROTOKOLL,button,1342242816

[DLG:IDD_IMPORT_SUM]
Type=1
Class=CImportSumPage
ControlCount=14
Control1=IDC_STATIC,static,1342308354
Control2=IDS_TABLE_INFO,static,1342308352
Control3=IDC_STATIC,static,1342308354
Control4=IDS_INPUT_DATABASE,static,1342308352
Control5=IDC_STATIC,static,1342308354
Control6=IDS_INPUT_TABLE,static,1342308352
Control7=IDC_STATIC,static,1342308354
Control8=IDS_OUTPUT_DATABASE,static,1342308352
Control9=IDC_STATIC,static,1342308354
Control10=IDS_OUTPUT_TABLE,static,1342308352
Control11=IDS_SELECTED,static,1342308352
Control12=IDS_ACTUAL,static,1342308352
Control13=IDS_AS_NEW_TABLE,static,1342308352
Control14=IDC_STATIC,static,1342308352

[DLG:IDD_IMPORT_INPUT]
Type=1
Class=CInputTablePage
ControlCount=20
Control1=IDC_STATIC,button,1342177287
Control2=IDB_ABFALL,button,1342373897
Control3=IDB_ERZEUGER,button,1342177289
Control4=IDB_BRANCH,button,1342177289
Control5=IDB_ABFALL_ARTEN,button,1342177289
Control6=IDB_TRANSPORTEURE,button,1342177289
Control7=IDB_ENTSORGER,button,1342177289
Control8=IDB_GEMEINDEN,button,1342177289
Control9=IDB_KREISE,button,1342177289
Control10=IDB_VERBRINGUNG,button,1342177289
Control11=IDB_VERFAHREN,button,1342177289
Control12=IDC_STATIC,button,1342177287
Control13=IDB_MDB_TABLE,button,1342373897
Control14=IDB_OLD_VERSION,button,1342177289
Control15=IDB_FOX_TABLE,button,1342177289
Control16=IDB_OLD_VERSION_FOX,button,1342177289
Control17=IDE_PATH,edit,1350699136
Control18=IDB_CHANGE,button,1342242817
Control19=IDC_STATIC,static,1342308352
Control20=IDL_TABLES,listbox,1352728835

[DLG:IDD_QUERY_DEF]
Type=1
Class=CNewQueryDef
ControlCount=19
Control1=IDC_STATIC,static,1342308352
Control2=IDE_NAME,edit,1350631552
Control3=IDB_QUERY_ART,button,1342242819
Control4=IDC_STATIC,static,1342308352
Control5=IDE_SQL,edit,1353781252
Control6=IDB_CHECK,button,1476395008
Control7=IDB_ED_BACK,button,1476395008
Control8=IDC_TABLES,static,1342308352
Control9=IDL_TABLES,listbox,1353777411
Control10=IDC_FIELDS,static,1342308352
Control11=IDL_FIELDS,listbox,1353777411
Control12=IDC_FUNCTIONS,static,1342308352
Control13=IDL_FUNCTIONS,listbox,1353777409
Control14=IDC_OPERATORS,static,1342308352
Control15=IDL_OPERATORS,listbox,1353777409
Control16=IDOK,button,1342373889
Control17=IDCANCEL,button,1342242816
Control18=IDC_STATIC,static,1342308352
Control19=IDE_DESCRPITION,edit,1352665092

[DLG:IDD_OUTPUT_TABLE]
Type=1
Class=COutputTablePage
ControlCount=6
Control1=IDS_INFO,static,1342308352
Control2=IDL_TABLES,listbox,1352728835
Control3=IDC_STATIC,static,1342308352
Control4=IDE_TABLE_NAME,edit,1350631552
Control5=IDB_CREATE,button,1476460545
Control6=IDB_AS_NEW,button,1342242819

[DLG:IDD_PARAMS]
Type=1
Class=CParameters
ControlCount=34
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_ERZEUGER_TABLE,combobox,1344340227
Control4=IDC_STATIC,static,1342308352
Control5=IDC_ABFALL_TABLE,combobox,1344340227
Control6=IDC_STATIC,static,1342308352
Control7=IDC_VJABFALL_TABLE,combobox,1344340227
Control8=IDC_STATIC,static,1342308352
Control9=IDC_BGS_TABLE,combobox,1344340227
Control10=IDC_STATIC,static,1342308352
Control11=IDE_OUTPUT_DB,edit,1484851328
Control12=IDB_OUTPUT_DB,button,1342242816
Control13=IDC_STATIC,button,1342177287
Control14=IDB_ABGLEICH,button,1342373897
Control15=IDB_KONTROLLE,button,1342185481
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,static,1342308352
Control18=IDB_RD1,button,1342373897
Control19=IDB_RD2,button,1342177289
Control20=IDB_RD3,button,1342177289
Control21=IDC_STATIC,static,1342308352
Control22=IDE_MENGE_REC,edit,1350631552
Control23=IDC_STATIC,static,1342308352
Control24=IDE_MENGE2,edit,1350631552
Control25=IDB_SONDERABFALL,button,1342242819
Control26=IDB_CREATE_ERZLISTE,button,1342242819
Control27=IDT_ERZLISTE,static,1342308352
Control28=IDC_STATIC,button,1342177287
Control29=IDE_ERZ_NUMMER,edit,1350631552
Control30=IDE_ASN,edit,1350639744
Control31=IDB_ERZ_NR,button,1342242819
Control32=IDOK,button,1476591616
Control33=ID_HELP,button,1342177280
Control34=IDCANCEL,button,1342177280

[DLG:IDD_ANSPRECH]
Type=1
Class=CPartnerPage
ControlCount=16
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308354
Control3=IDE_NAME,edit,1350762624
Control4=IDC_STATIC,static,1342308354
Control5=IDE_TELEFON,edit,1350631552
Control6=IDC_STATIC,static,1342308354
Control7=IDE_TELEFAX,edit,1350631552
Control8=IDC_STATIC,static,1342308354
Control9=IDE_FUNKTION,edit,1350631552
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342308354
Control12=IDE_BB_NAME,edit,1350762624
Control13=IDC_STATIC,static,1342308354
Control14=IDE_BB_TELEFON,edit,1350631552
Control15=IDC_STATIC,static,1342308354
Control16=IDE_BB_TELEFAX,edit,1350631552

[DLG:IDD_RECHERCHESTATUS]
Type=1
Class=CProgress
ControlCount=3
Control1=IDT_ACTIONTEXT,static,1342308353
Control2=IDCANCEL,button,1342242817
Control3=IDT_PROGRESS,msctls_progress32,1350565888

[DLG:IDD_QUERY_SELECT]
Type=1
Class=CQueryDialog
ControlCount=13
Control1=IDS_INFO,static,1342308352
Control2=IDC_QUERIES,SysListView32,1350631429
Control3=IDB_STANDARD,button,1342242819
Control4=IDC_STATIC,button,1342177287
Control5=IDB_DATENBLATT,button,1342373897
Control6=IDB_QUERY_LISTE,button,1342177289
Control7=IDS_SELECT_INFO,static,1342308352
Control8=IDB_NEU,button,1342373888
Control9=IDB_AENDERN,button,1342177280
Control10=IDB_DELETE,button,1342177280
Control11=IDB_IMPORT,button,1342177280
Control12=IDOK,button,1342373889
Control13=IDCANCEL,button,1342177280

[DLG:IDD_QUERY_PARAM]
Type=1
Class=CEnterQueryParam
ControlCount=5
Control1=IDS_TYPE,static,1342308352
Control2=IDS_INFOTEXT,static,1342308352
Control3=IDE_PARAM,edit,1350631552
Control4=IDOK,button,1476460545
Control5=IDCANCEL,button,1342242816

[DLG:IDD_QUERY_RESULT]
Type=1
Class=CQueryResult
ControlCount=8
Control1=IDS_FOUND,static,1342308352
Control2=IDC_QUERY_LIST,SysListView32,1350631425
Control3=IDB_ALLE,button,1342373897
Control4=IDB_TABLE,button,1342177289
Control5=IDB_ONLY_SELECTED,button,1342177289
Control6=IDB_FELDNAMEN,button,1342177283
Control7=IDB_COPY,button,1342373888
Control8=IDOK,button,1342242817

[DLG:IDD_REPORT_TABLE]
Type=1
Class=CReportTable
ControlCount=5
Control1=IDC_LIST,SysListView32,1350664197
Control2=IDC_ERZLISTDRUCK,button,1342242816
Control3=IDOK,button,1342242817
Control4=IDC_PLACEHOLDER,static,1073741832
Control5=IDC_ERZLISTDRUCKVOR,button,1208025088

[DLG:IDD_RESULT]
Type=1
Class=CResultDialog
ControlCount=10
Control1=IDC_STATIC,static,1342308354
Control2=IDT_ABGL_CNT,static,1342308352
Control3=IDC_STATIC,static,1342308354
Control4=IDT_UEBERN_CNT,static,1342308352
Control5=IDC_STATIC,static,1342308354
Control6=IDT_ESC_CNT,static,1342308352
Control7=IDT_DELETED_REC,static,1342308354
Control8=IDT_INLISTE_DEL_CNT,static,1342308352
Control9=IDOK,button,1342373889
Control10=IDB_OUTPUT_ERZLISTE,button,1342177280

[DLG:IDD_RESULT_PARAM]
Type=1
Class=CResultParam
ControlCount=2
Control1=IDT_QUERY_NAME,static,1342308352
Control2=IDE_RESULT,edit,1352669316

[DLG:IDD_SEARCH_RESULT]
Type=1
Class=CSearchResult
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDE_FERZNR,edit,1350631560
Control3=IDC_FOUND,static,1342308352
Control4=IDL_NUMMERN,listbox,1352728833
Control5=IDB_STAMM,button,1476460545
Control6=IDB_ABFAELLE,button,1476395008
Control7=IDOK,button,1342177280

[DLG:IDD_EXPORT_TABLES]
Type=1
Class=CSelectExportTables
ControlCount=5
Control1=IDC_STATIC,button,1342177287
Control2=IDB_ABFAELLE,button,1342242819
Control3=IDB_ERZEUGER,button,1342242819
Control4=IDOK,button,1342373889
Control5=IDCANCEL,button,1342177280

[DLG:IDD_SEL_NUMMER]
Type=1
Class=CSelNumberDlg
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDE_SEARCH,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDE_SEARCH_NUMBER,edit,1350631552
Control5=IDC_CNT,static,1342308352
Control6=IDC_SELECT,SysListView32,1350631429
Control7=IDB_STORE_DATA,button,1342242819
Control8=IDOK,button,1342242817
Control9=IDCANCEL,button,1342177280

[DLG:IDD_SELECT_TABLE]
Type=1
Class=CSelTable
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDE_TABLE,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDL_LIST_TABLES,listbox,1353777411
Control5=IDOK,button,1342373889
Control6=IDCANCEL,button,1342177280

[DLG:IDD_STATISTIK]
Type=1
Class=CStatistikDialog
ControlCount=2
Control1=IDT_TABLES,SysTreeView32,1350631479
Control2=IDC_TABLES,SysListView32,1350631425

[DLG:IDD_INPUT_TABLE_NAME]
Type=1
Class=CTableNameDlg
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDE_NAME,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDE_DATABASE,edit,1350568064
Control5=IDB_SELECT_DB,button,1342242816
Control6=IDOK,button,1476460545
Control7=IDCANCEL,button,1342242816

[DLG:IDD_TRANSPORTEUR]
Type=1
Class=CTranspPage
ControlCount=14
Control1=IDC_STATIC,static,1342308354
Control2=IDE_NUMMER,edit,1350631552
Control3=IDB_CHANGE,button,1342242817
Control4=IDB_EIGENTRANSPORT,button,1342242819
Control5=IDC_STATIC,static,1342308354
Control6=IDE_NAME,edit,1352665092
Control7=IDC_STATIC,static,1342308354
Control8=IDE_STRASSE,edit,1350568064
Control9=IDC_STATIC,static,1342308354
Control10=IDE_ORT,edit,1350568064
Control11=IDC_STATIC,static,1342308354
Control12=IDE_PLZ,edit,1350576256
Control13=IDC_STATIC,static,1342308354
Control14=IDE_BEMERKUNGEN,edit,1352728580

[DLG:IDD_USER_NAME]
Type=1
Class=CUserInfoDlg
ControlCount=5
Control1=IDC_STATIC,static,1342308353
Control2=IDC_STATIC,static,1342308353
Control3=IDE_USER_NAME,edit,1350631560
Control4=IDOK,button,1476460545
Control5=IDCANCEL,button,1342242816

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDM_STAMMDATEN
Command2=IDM_ABFALL
Command3=IDM_LOOK_NR
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_RECORD_FIRST
Command9=ID_RECORD_PREV
Command10=ID_RECORD_NEXT
Command11=ID_RECORD_LAST
Command12=IDM_NEW_REKORD
Command13=IDM_DELETE_REKORD
Command14=IDM_CHANGE_KEY
Command15=IDB_ABGLEICH
Command16=ID_APP_ABOUT
Command17=ID_CONTEXT_HELP
Command18=IDM_AKTBILANZ
CommandCount=18

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDM_STAMMDATEN
Command2=IDM_ABFALL
Command3=IDM_LOOK_NR
Command4=IDM_RECHERCHE
Command5=IDM_REPAIR_DATABASE
Command6=IDM_COMPACT_DATABASE
Command7=IDM_STATISTIK
Command8=IDM_IMPORT
Command9=IDM_EXPORT
Command10=ID_FILE_PRINT_SETUP
Command11=ID_APP_EXIT
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=IDM_NEW_ABGLEICH
Command15=IDM_LAST_ABGLEICH
Command16=IDM_DRUCK_ERZLISTE
Command17=IDM_CONFIG_DSN
Command18=IDM_ODBC_ACESS
Command19=IDM_CALL_ADMIN
Command20=ID_HELP_FINDER
Command21=IDM_HELP_DATABSE_ERRORS
Command22=ID_APP_ABOUT
CommandCount=22

[MNU:IDR_GAKTYPE]
Type=1
Class=?
Command1=IDM_STAMMDATEN
Command2=IDM_ABFALL
Command3=IDM_LOOK_NR
Command4=IDM_AKTBILANZ
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_APP_EXIT
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_PASTE
Command12=ID_EDIT_COPY
Command13=ID_RECORD_FIRST
Command14=ID_RECORD_PREV
Command15=ID_RECORD_NEXT
Command16=ID_RECORD_LAST
Command17=IDM_NEW_REKORD
Command18=IDM_DELETE_REKORD
Command19=IDM_CHANGE_KEY
Command20=IDM_SET_BOOKMARK
Command21=IDM_GOTO_BOOKMARK
Command22=ID_VIEW_TOOLBAR
Command23=ID_VIEW_STATUS_BAR
Command24=ID_WINDOW_TILE_HORZ
Command25=ID_WINDOW_TILE_VERT
Command26=ID_WINDOW_CASCADE
Command27=ID_WINDOW_ARRANGE
Command28=IDM_ABGLEICH_AKT
Command29=IDM_ABGLEICH_AKTNEW
Command30=ID_HELP_FINDER
Command31=IDM_HELP_DATABSE_ERRORS
Command32=ID_APP_ABOUT
CommandCount=32

[MNU:IDM_POPUP]
Type=1
Class=?
Command1=IDM_BACK
Command2=IDM_CUT
Command3=IDM_COPY
Command4=IDM_INSERT
Command5=IDM_DELETE
Command6=IDM_SELECT
CommandCount=6

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDM_ABFALL
Command2=IDM_AKTBILANZ
Command3=ID_EDIT_COPY
Command4=IDM_STAMMDATEN
Command5=IDM_LOOK_NR
Command6=ID_FILE_PRINT
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_HELP
Command11=ID_CONTEXT_HELP
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=IDM_RECHERCHE
Command17=ID_EDIT_CUT
Command18=ID_EDIT_UNDO
CommandCount=18

[DLG:IDD_GAK_FORM]
Type=1
Class=CSelNumberDlgUsage
ControlCount=0

[DLG:IDD_DOKONTROLLE]
Type=1
Class=?
ControlCount=21
Control1=IDC_STATIC,static,1342308352
Control2=IDL_ABFALLN,SysListView32,1476493313
Control3=IDC_STATIC,static,1342308352
Control4=IDL_BGSN,SysListView32,1476493313
Control5=IDC_STATIC,static,1342308352
Control6=IDL_ABFALL_VJN,SysListView32,1476493313
Control7=IDT_AKTION,static,1342177280
Control8=IDT_PROGRESS2,msctls_progress32,1350565888
Control9=IDOK,button,1342373889
Control10=IDB_ESCAPE,button,1476395008
Control11=IDB_INLISTE,button,1476395008
Control12=ID_HELP,button,1342177280
Control13=IDB_ERZ_INFO,button,1476395008
Control14=IDCANCEL,button,1342177280
Control15=IDC_STATIC,static,1342308864
Control16=IDC_STATIC,static,1342308864
Control17=IDC_STATIC,static,1342308864
Control18=IDC_STATIC,static,1342308864
Control19=IDC_ANFALLSTELLE,static,1342312960
Control20=IDC_BRANCHENNUMMER,static,1342312960
Control21=IDB_WEITER,button,1208025088

[CLS:CSelNumberDlgUsage]
Type=0
HeaderFile=SelNumberDlgUsage.h
ImplementationFile=SelNumberDlgUsage.cpp
BaseClass=CDialog
Filter=D
LastObject=CSelNumberDlgUsage

[CLS:CTestRS]
Type=0
HeaderFile=TestRS.h
ImplementationFile=TestRS.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CTestRS]
DB=1
DBType=ODBC
ColumnCount=30
Column1=[Prioritaet], 12, 1
Column2=[Bearbeitet], -7, 1
Column3=[Nummer], 12, 10
Column4=[Abfallnummer], 12, 10
Column5=[Transporteurnummer], 12, 10
Column6=[Entsorgernummer], 12, 10
Column7=[Vorbehandlung], 12, 1
Column8=[Menge_t], 8, 8
Column9=[Verbringungscode], 12, 10
Column10=[Abfallbezeichnung], 12, 80
Column11=[Betreibernummer], 12, 10
Column12=[Eigentransport], -7, 1
Column13=[Entsorgungsverfahren], 12, 5
Column14=[Eigenentsorgung], -7, 1
Column15=[Entsorgungspartner], 12, 30
Column16=[Entsorgungstelefon], 12, 20
Column17=[Entsorgungstelefax], 12, 20
Column18=[Entsorgungsfreistellung], -7, 1
Column19=[Freistellungsnummer], 12, 20
Column20=[Betreiberbemerkungen], -1, 1073741824
Column21=[Transporteurbemerkungen], -1, 1073741824
Column22=[Entsorgerbemerkungen], -1, 1073741824
Column23=[Bemerkungen], -1, 1073741824
Column24=[Erfassungsdatum], 11, 16
Column25=[Aenderungsdatum], 11, 16
Column26=[ro], -7, 1
Column27=[user], 12, 20
Column28=[EAKNummer], 12, 10
Column29=[Nachweisnummer], 12, 20
Column30=[Exportiert], 12, 1

