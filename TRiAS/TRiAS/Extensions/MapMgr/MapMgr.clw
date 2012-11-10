; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCoordSystemTree
LastTemplate=CTreeCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mapmgr.h"
LastPage=0
CDK=Y

ClassCount=20
Class1=CModifyButton
Class2=CGetFileNameDialog
Class3=CGetFilenameControl
Class4=CModifyButtonFolder
Class5=CGetFolderControl
Class6=CFileDirDialog
Class7=CMapImportDlg
Class8=CPpgBase
Class9=CPpgImportFile
Class10=CPpgIntergraph
Class11=CPpgMapInfo
Class12=CPpgNomenclatur
Class13=CPpgRefPoints
Class14=CPpgSelAddFile
Class15=CPpgSelDataSource
Class16=CPpgSelDocFile
Class17=CPpgSelFilesOrDirs
Class18=CPpgSelMapType

ResourceCount=12
Resource1=IDD_PPGNOMENCLATUR
Resource2=IDD_PPGSELFILES
Resource3=IDD_PPGREFPOINTS
Resource4=1536
Resource5=IDD_PPGIMPORTFILE
Resource6=IDD_PPGINTERGRAPH
Resource7=IDD_PPGMAPINFO
Resource8=IDD_PPGSELDATASOURCE
Resource9=IDD_PPGSELMAPTYPE
Resource10=IDD_PPGSELDOCFILE (_DEBUG)
Resource11=IDD_PPGSELADDFILE
Class19=CSelectCoordSys
Class20=CCoordSystemTree
Resource12=IDD_SELECT_COORDSYS

[CLS:CModifyButton]
Type=0
BaseClass=CButton
HeaderFile=DDXGetFile.h
ImplementationFile=DDXGetFile.cpp

[CLS:CGetFileNameDialog]
Type=0
BaseClass=CFileDialog
HeaderFile=DDXGetFile.h
ImplementationFile=DDXGetFile.cpp

[CLS:CGetFilenameControl]
Type=0
BaseClass=CStatic
HeaderFile=DDXGetFile.h
ImplementationFile=DDXGetFile.cpp

[CLS:CModifyButtonFolder]
Type=0
BaseClass=CButton
HeaderFile=DDXGetFolder.h
ImplementationFile=DDXGetFolder.cpp

[CLS:CGetFolderControl]
Type=0
BaseClass=CStatic
HeaderFile=DDXGetFolder.h
ImplementationFile=DDXGetFolder.cpp

[CLS:CFileDirDialog]
Type=0
BaseClass=CFileDialog
HeaderFile=Dlgdir.h
ImplementationFile=Dlgdir.cpp
LastObject=CFileDirDialog

[CLS:CMapImportDlg]
Type=0
BaseClass=CPropertySheet
HeaderFile=ImportDlg.h
ImplementationFile=ImportDlg.cpp

[CLS:CPpgBase]
Type=0
BaseClass=CPropertyPage
HeaderFile=PpgBase.h
ImplementationFile=PpgBase.cpp

[CLS:CPpgImportFile]
Type=0
BaseClass=CPropertyPage
HeaderFile=PpgImportFile.h
ImplementationFile=PpgImportFile.cpp

[CLS:CPpgIntergraph]
Type=0
BaseClass=CPropertyPage
HeaderFile=ppgintergraph.h
ImplementationFile=PpgIntergraph.cpp

[CLS:CPpgMapInfo]
Type=0
BaseClass=CPropertyPage
HeaderFile=PpgMapInfo.h
ImplementationFile=PpgMapInfo.cpp

[CLS:CPpgNomenclatur]
Type=0
BaseClass=CPropertyPage
HeaderFile=PpgNomenclatur.h
ImplementationFile=PpgNomenclatur.cpp

[CLS:CPpgRefPoints]
Type=0
BaseClass=CPropertyPage
HeaderFile=PpgRefPoints.h
ImplementationFile=PpgRefPoints.cpp

[CLS:CPpgSelAddFile]
Type=0
BaseClass=CPropertyPage
HeaderFile=PpgSelAddFile.h
ImplementationFile=PpgSelAddFile.cpp

[CLS:CPpgSelDataSource]
Type=0
BaseClass=CPropertyPage
HeaderFile=PpgSelDataSource.h
ImplementationFile=PpgSelDataSource.cpp

[CLS:CPpgSelDocFile]
Type=0
BaseClass=CPropertyPage
HeaderFile=PpgSelDocFile.h
ImplementationFile=PpgSelDocFile.cpp

[CLS:CPpgSelFilesOrDirs]
Type=0
BaseClass=CPropertyPage
HeaderFile=PpgSelFilesOrDirs.h
ImplementationFile=PpgSelFilesOrDirs.cpp
Filter=D
VirtualFilter=idWC
LastObject=CPpgSelFilesOrDirs

[CLS:CPpgSelMapType]
Type=0
BaseClass=CPropertyPage
HeaderFile=PpgSelMapType.h
ImplementationFile=PpgSelMapType.cpp

[DLG:IDS_MAPIMPORTCAPTION]
Type=1
Class=CMapImportDlg

[DLG:IDD_PPGIMPORTFILE]
Type=1
Class=CPpgImportFile
ControlCount=8
Control1=IDC_STATIC,static,1350565902
Control2=IDC_PROGRESSMESSAGE,static,1350696960
Control3=IDC_PROGRESSCHUNK,msctls_progress32,1342177280
Control4=IDC_PROGRESSIMPORT,msctls_progress32,1342177280
Control5=IDC_BUTTONSTART,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDITDIR,edit,1350633600
Control8=IDC_BUTTONSELDIR,button,1342242816

[DLG:IDD_PPGINTERGRAPH]
Type=1
Class=CPpgIntergraph
ControlCount=12
Control1=IDC_STATIC,static,1350565902
Control2=IDC_STATIC,static,1342308352
Control3=IDC_TRANSFORMMATRIX,SysListView32,1350666249
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1350696960
Control6=IDC_ORIGX,{51BB3DDF-0C38-11D2-8F6B-0060085FC1CE},1342242816
Control7=IDC_STATIC,static,1350696960
Control8=IDC_ORIGY,{51BB3DDF-0C38-11D2-8F6B-0060085FC1CE},1342242816
Control9=IDC_STATIC,static,1350696960
Control10=IDC_ORIGZ,{51BB3DDF-0C38-11D2-8F6B-0060085FC1CE},1342242816
Control11=IDC_STATIC,static,1342308352
Control12=IDC_COMBO_SCALE,combobox,1344339971

[DLG:IDD_PPGMAPINFO]
Type=1
Class=CPpgMapInfo
ControlCount=3
Control1=IDC_STATIC,static,1350565902
Control2=IDC_LISTGCPS,SysListView32,1350664205
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_PPGNOMENCLATUR]
Type=1
Class=CPpgNomenclatur
ControlCount=3
Control1=IDC_STATIC,static,1350565902
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDITSRCMAP,edit,1350635648

[DLG:IDD_PPGREFPOINTS]
Type=1
Class=CPpgRefPoints
ControlCount=14
Control1=IDC_STATIC,static,1350565902
Control2=IDC_STATIC,button,1342177287
Control3=IDC_TRIASCSUI1,{AE998A04-1127-11D2-8F75-0060085FC1CE},1342242816
Control4=IDC_BUTTONDEFCS,button,1073807360
Control5=IDC_STATIC,button,1342177287
Control6=IDC_COMBOPOINTSCHEMA,combobox,1344339971
Control7=IDC_STATIC,static,1350696960
Control8=IDC_P0X,{51BB3DDF-0C38-11D2-8F6B-0060085FC1CE},1342242816
Control9=IDC_STATIC,static,1350696960
Control10=IDC_P0Y,{51BB3DDF-0C38-11D2-8F6B-0060085FC1CE},1342242816
Control11=IDC_STATIC,static,1350696960
Control12=IDC_P1X,{51BB3DDF-0C38-11D2-8F6B-0060085FC1CE},1342242816
Control13=IDC_STATIC,static,1350696960
Control14=IDC_P1Y,{51BB3DDF-0C38-11D2-8F6B-0060085FC1CE},1342242816

[DLG:IDD_PPGSELADDFILE]
Type=1
Class=CPpgSelAddFile
ControlCount=5
Control1=IDC_STATIC,static,1350565902
Control2=IDC_DESCRIPTION,edit,1350633600
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDITNAME,edit,1350633600
Control5=IDC_BUTTONNAME,button,1342242816

[DLG:IDD_PPGSELDATASOURCE]
Type=1
Class=CPpgSelDataSource
ControlCount=3
Control1=IDC_STATIC,static,1350565902
Control2=IDC_STATIC,static,1342308352
Control3=IDC_SELECTDATASOURCE,ComboBoxEx32,1344340227

[DLG:IDD_PPGSELDOCFILE]
Type=1
Class=CPpgSelDocFile

[DLG:IDD_PPGSELFILES]
Type=1
Class=CPpgSelFilesOrDirs
ControlCount=7
Control1=IDC_STATIC,static,1350565902
Control2=IDC_STATIC_FILESORDIR,static,1342308352
Control3=IDC_SELSOURCE,edit,1350633600
Control4=IDC_STATIC_DESTINATION,static,1342308352
Control5=IDC_SELDESTINATION,edit,1350633600
Control6=IDC_STATIC_ALTFILES,static,1342308352
Control7=IDC_SELREFFILES,edit,1350633600

[DLG:IDD_PPGSELMAPTYPE]
Type=1
Class=CPpgSelMapType
ControlCount=4
Control1=IDC_STATIC,static,1350565902
Control2=IDC_STATIC,static,1342308352
Control3=IDC_TREEOFENGINES,SysTreeView32,1350631463
Control4=IDC_DESCRIPTION,static,1342308352

[DLG:IDD_PPGSELDOCFILE (_DEBUG)]
Type=1
Class=?
ControlCount=3
Control1=IDC_STATIC,static,1350565902
Control2=IDC_FILEDESCRIPTION,static,1342312448
Control3=IDC_CHECKASCIIFILE,button,1342242819

[DLG:1536]
Type=1
Class=?
ControlCount=14
Control1=1090,static,1342308352
Control2=1152,edit,1350632576
Control3=1120,listbox,1352732755
Control4=65535,static,1342308352
Control5=1088,static,1342308480
Control6=1121,listbox,1352732755
Control7=1089,static,1342308352
Control8=1136,combobox,1352728643
Control9=1091,static,1342308352
Control10=1137,combobox,1352729427
Control11=IDOK,button,1342373889
Control12=IDCANCEL,button,1342373888
Control13=1038,button,1342373888
Control14=1040,button,1342373891

[DLG:IDD_SELECT_COORDSYS]
Type=1
Class=CSelectCoordSys
ControlCount=4
Control1=IDC_DESCTEXT,static,1342308352
Control2=IDC_COORDSYSTEMS,SysTreeView32,1350631479
Control3=IDC_COORDDESCRIPTION,static,1342308352
Control4=IDC_STATIC,static,1350565902

[CLS:CSelectCoordSys]
Type=0
HeaderFile=SelectCoordSys.h
ImplementationFile=SelectCoordSys.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CSelectCoordSys

[CLS:CCoordSystemTree]
Type=0
HeaderFile=CoordSystemTree.h
ImplementationFile=CoordSystemTree.cpp
BaseClass=CTreeCtrl
Filter=W

