// MenuKonstanten ------------------------------------------------------------
// File: MENUITEM.H

#if !defined(_MENUITEM_H)
#define _MENUITEM_H

// Projektverwaltung
#define IDM_OPEN        	101
#define IDM_CLOSE       	102
#define IDM_EXIT        	103
#define IDM_EDITHEADER  	104
#define IDM_OPENOLD1    	105
#define IDM_OPENOLD2    	106
#define IDM_OPENOLD3    	107
#define IDM_OPENOLD4    	108
#define IDM_PASSWORD    	109
#define IDM_PRINT       	110
#define IDM_SELPRINT    	111
#define IDM_SAVEDB		112
#define IDM_NEWDB		113

// Anzeigenverwaltung
#define IDM_GEOGRAPH    	201
#define IDM_WORLD       	202
#define IDM_GITTER      	203
#define IDM_DRAW        	204
#define IDM_SELOBJ      	205
#define IDM_SELRECH     	206
#define IDM_LEGENDE		207
#define IDM_DQLEDIT		208
#define IDM_SELAUSSCHNITT	209
#define IDM_PREVSELAUSSCHNITT	210
#define IDM_SELSICHTCONT	211
#define IDM_DELSICHTCONT	212
#define IDM_REECHRESULTS	213
#define IDM_DELETEVIEWS		214
#define IDM_OVERVIEW		215
#define IDM_ZOOMOUT		216
#define IDM_ZOOMIN		217
#define IDM_SELECTIDENTS	218
#define IDM_DELETEIDENTS	219
#define IDM_MODIFYIDENTS	220
#define IDM_SHOWLEGENDE		222
#define IDM_SHOWOVERVIEW	223

// Hilfe-/Info-Menu
#define IDM_INDEX       	301
#define IDM_KEYBOARD    	302
#define IDM_IMAGE       	303
#define IDM_HELP        	304
#define IDM_ABOUT       	305
#define IDM_MOUSE       	307
#define IDM_GLOSSAR     	306

// Debugging
#define IDM_PROFILE     	499

// Optionen
#define IDM_TOOLS       	501
#define IDM_TEXTSEARCH  	502
#define IDM_TEXTPARAMS  	503
#define IDM_COORDS      	504
#define IDM_10000       	507
#define IDM_25000       	505
#define IDM_50000       	506
#define IDM_SCHRANK		508
#define IDM_COPYTOCLIPBOARD	509
#define IDM_MASSTAB		510

// Werkzeuge
#define IDM_SELTOOLS		600
#define IDM_ARROW       	601
#define IDM_ZOOM		602
#define IDM_LUPE        	603
#define IDM_SCHERE      	604
#define IDM_LINEAL      	605
#define IDM_TEXT		606

// Darstellungsparameter
#define IDM_SYMBOLPARS		700
#define IDM_PRIORITYSELECT	701
#define IDM_BACKGRNDCOLOR	702
#define IDM_VISTEXTOBJ		703
#define IDM_CHANGEVISINFO	704

#define IDM_IMPORT		800
#define IDM_EXPORT		801
#define IDM_BUFFERING		802
#define IDM_MKSEARCH		803
#define IDM_MKPARAMS		804

#define IDM_LOADEXTENSION_CUST	819
#define IDM_LOADEXTENSION	820
#define IDM_UNLOADEXTENSION	821
#define IDM_SAVEOPT		822
#define IDM_RECHRESULTS		823
#define IDM_EXECUTE_SEQUENCE	824

#define IDM_AUTOSAVEDB		900

// allgemeiner AbbruchKode
#define IDM_CANCEL      	1000

// MenuCodes für Ansichten, die definiert wurden
#define IDM_SIGHTS      	1010

// Einträge im Systemmenu der ObjektInfoDlg's
#define IDM_ATTRIBUTE   	2000
#define IDM_TOPOLOGIE   	2001
#define IDM_THEMATIK    	2002
#define IDM_OBJHELP     	2003
#define IDM_BILDINFO    	2004
#define IDM_DBASEINFO		2005
#define IDM_OBJAREA		2006
#define IDM_OBJCENTRE		2007
#define IDM_OBJBUFFERING	2008
#define IDM_OBJCOLOR		2009
#define IDM_OBJPRIORITY		2010
#define IDM_OBJSICHT		2011
#define IDM_OBJBUFFPARS		2012
#define IDM_OBJDELETE		2013
#define IDM_MODIDENT		2014
#define IDM_MODALLIDENTS	2015
#define IDM_CREATEKO		2016
#define IDM_DUMMY		2017
#define IDM_OBJPROPS		2018
#define IDM_ZOOMOBJECTS		2019
#define IDM_TOGGLEROLLUP	2020

#define EXTINSERTMENUPOS	6

#define IDM_CREATETEXTOBJ	3000
#define IDM_DELETETEXTOBJ	3001
#define IDM_EDITTEXTOBJ		3002
#define IDM_MODIDTEXTOBJ	3003
#define IDM_CREATEBREL		3004
#define IDM_DELETEBREL		3005

#define VISTYPEMENU		4000
#define IDM_VISTYPEPUNKT	4001
#define IDM_VISTYPELINIE	4002
#define IDM_VISTYPEFLAECHE	4003
#define IDM_VISTYPETEXT		4004

#define IDM_REMOVEORWNDS	5001
#define IDM_MINIMIZEORWNDS	5002
#define IDM_MAXIMIZEORWNDS	5003

// HilfeItems für Bildschirmbereiche
#define IDW_CANVAS		520
#define IDW_CAPTION		521

#define IDM_FITLEGENDENTRIES	530
#define IDM_LEGENDHELP		531
#define IDM_LEGENDSELFONT	532

#define IDM_LEGENDVISENTRY	540
#define IDM_LEGENDVISSCALE	541

#endif // _MENUITEM_H
