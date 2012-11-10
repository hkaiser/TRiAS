// KONSTANTENDEFINITIONEN FÅR ERWEITERUNGSRESSOURCEN
// File: GEOSTAT.H

#if !defined(_GEOSTAT_H)
#define _GEOSTAT_H
                              
// MenuKonstanten
#define STATISTEXTENSIONMENU	100
#define STATISTORMENU			101



//MenuPunkte
//TRIAS-Leiste
#define IDM_GEOALLDBINFO	1

#define IDM_SICHTINFO		3
#define IDM_SICHTPART		4
#define IDM_SICHTORWIND		5
#define IDM_SICHTPARAM		6
#define	IDM_ABOUT		7


//ORFenster
#define IDM_DEFORWIND		10
#define IDM_DEFOBJCONT		11
#define IDM_DEFKLASSIFIZ	12
#define IDM_DEFMINMAX		13
#define IDM_DEFMITTELWERT	14
#define IDM_DEFMEDIAN		15
#define IDM_DEFOBJANALYSE	16
#define IDM_DEFOBJTOPOL		17
#define IDM_ORWINOBJTOPOL	18
#define IDM_ORWINOBJTOPOLOG	19

//----DB-Fenster--------------------
#define SHOWDATABASE		500

//----Ident-Anzeige--------------------
#define SHOWIDENTIFIKATOR	550

//---- ObjektKlassen/Objekt-Parameter-Anzeige--------------------
#define SHOWOBJECTCLASS		560

//----Neue ObjektKlassen/Objekt-Anzeige--------------------
#define SHOWOBJECTCLASSVIEW	570

//----Zusammenstellen der Zwischenablage-------------------
#define CLIPBOARDVIEW		600

//---Sortieren der Parameter------------------------------
#define PARAMETERSORT		610

//-----GIClassification---------------
#define GICLASSIFICATION	720

//------Suchen von DatenbankObjekten------------
#define SHOWDATABASEOBJECT	750


//--------------- DB - Header- Schl¸ssel ------------------------------------
#define IDT_HEADAENDATUM	    1551
#define IDT_HEADKOEFF11		    1552
#define IDT_HEADKOEFF12		    1553
#define IDT_HEADKOEFF21		    1554
#define IDT_HEADKOEFF22		    1555
#define IDT_HEADOFFSETX		    1556
#define IDT_HEADOFFSETY		    1557

#define IDT_HEADKOORDTYP	    1016
#define IDT_HEADUNIQUEIDENT	    1017
#define IDT_HEADTPMCODE		    1018
#define IDT_HEADTEXTMCODE	    1019

// Ma·einheiten
#define	IDT_UNITKM		1040
#define	IDT_UNITM 		1041
#define	IDT_UNITQM		1042
#define	IDT_UNITHA		1043
#define	IDT_UNITQKM		1044

// Strings f¸r ObjProp's
#define IDH_HELPAREA		1100
#define IDS_OBJPROPAREA		1101
#define IDH_HELPPOINT		1102
#define IDS_OBJPROPPOINT	1103
#define IDH_HELPBIGRANGE	1105
#define IDS_OBJPROPBIGRANGE	1106
#define IDH_HELPRANGE		1107
#define IDS_OBJPROPRANGE	1108
#define IDH_HELPDIFF		1109
#define IDS_OBJPROPDIFF		1110
#define IDH_HELPLINE		1111
#define IDS_OBJPROPLINE		1112
#define IDH_HELPRPOINTX		1113
#define IDS_OBJPROPRPOINTX	1114
#define IDH_HELPRPOINTY		1115
#define IDS_OBJPROPRPOINTY	1116
#define IDH_HELPRTEXT		1117
#define IDS_OBJPROPRTEXT	1118
#define IDH_HELPAREARADIUS	1119
#define IDS_OBJPROPAREARADIUS	1120

#define IDT_DEXNOTEXT		1121

//----------DB-Fenster--------------------
#define IDT_DBDATABASENAME	1201
#define IDT_DBDATABASEPBD	1202
#define IDT_DBDATABASEDATUM	1203
#define IDS_DBDATABASESIGHT	1204
#define IDS_DBDATABASEOBJCLASS	1205
#define IDS_DBDATABASEMCODE	1206
#define IDS_DBDATABASETPROJECT	1207
#define IDS_DBDATABASEDBASE	1208
#define IDS_DBDATABASEPROJECTS	1209
#define IDS_DBDATABASEPROFEXT	1210
#define IDS_DBDATABASEDBDAT	1211
#define IDS_DBDATABASEPERM	1212
#define IDS_DBDATABASEPERMHCODE	1213
#define IDS_DBDATABASEPERMMCODE	1214

#define IDCB_DBDATABASEINFO	1215

//----------Ident-Anzeige--------------------
#define IDT_SHOWIDENTKEY	1220
#define IDT_SHOWIDENTNUMBER	1221
#define IDG_SHOWSTATUSGAUGE	1222


//-------ObjektKlassen/Objekt-öbersicht--------
#define IDT_OCLPCLASSCOUNT	1250
#define IDLB_OCLPCLASSLIST	1251
#define IDCB_OCLPBEZUGSKLASSE	1252
#define IDC_OCLPBEZUGEINAUS	1253

#define IDT_OCLPCUMULCLASS	1254
#define IDT_OCLPPROZANTEIL	1255

#define IDT_OCLPOBJECTCOUNT	1256
#define IDT_OCLPMINIMUM		1257
#define IDT_OCLPMAXIMUM		1258
#define IDT_OCLPMEDIANWERT	1259
#define IDT_OCLPMITTELWERT	1260

#define IDT_OCLPCLASSSUMME	1261
#define IDT_OCLPALLOBJECTSCOUNT	1262
#define IDT_OCLPBEZMINIMUM	1263
#define IDT_OCLPBEZMAXIMUM	1264
#define IDT_OCLPBEZMEDIANWERT	1265
#define IDT_OCLPBEZMITTELWERT	1266
#define IDT_OCLPBESCHREIBUNG	1267
#define IDB_OCLPCLIPBOARD	1268


//-----------ObjektKlassenInfoFenster-----------
//------------------------------------------
#define IDLB_OCLOBJCLASSLIST              1601
#define IDT_OCLOBJEKTKLASSEN           1602
#define IDC_OCLOBJEKTEIGENSCH	    1605
#define IDCB_OCLMERKMALLIST	    1606
#define IDC_OCLMERKMALANZEIGE	    1607
#define IDC_OCLINVERSMERKMAL	    1608
#define IDC_OCLONLYMERKMAL		    1609

//-----------Container----------------------
#define IDK_OCLLOHOCH		    1610
#define IDK_OCLLORECHTS		    1611
#define IDK_OCLRUHOCH		    1612
#define IDK_OCLRURECHTS		    1613
//-----------Kumulierte Werte----------------
#define IDT_OCLFLINHALT		    1614
#define IDT_OCLFLMASS		    1615
#define IDT_OCLLINLAENGE		    1616
#define IDT_OCLLINMASS		    1617
//----------------------------------------
#define IDT_OCLBESCHREIBUNG	    1618

//----------Zerlegte Objekte-----------------
#define IDT_OCLOBJEKTE		    1620
#define IDT_OCLOBJEKT		    1621
#define IDC_OCLPUNKTE		    1622
#define IDC_OCLPUNKT		    1623
#define IDC_OCLLINIEN		    1624
#define IDC_OCLLINIE		    1625
#define IDC_OCLFLAECHEN		    1626
#define IDC_OCLFLAECHE		    1627
#define IDC_OCLTEXTE		    1628
#define IDC_OCLTEXT		    1629
#define IDC_OCLSONSTIGE	    1630
#define IDC_OCLSONSTIG		    1631

//-------------Buttons--------------------------
#define IDB_OCLPUTCLIPBOARD	    1634
#define IDB_OCLALLEKLASSEN		    1635
#define IDB_OCLANZEIGEN		    1636
#define IDB_OCLDETAILS		    1637

//-------------MessageBox-Texte-------------------
#define IDS_OCLASSRECHERCHE	    1640
#define IDS_OCLCOUNTOBJECTS	    1641
#define IDS_OCLSTOPWORK		    1642



//-------- TextAnzeigen f¸r CheckBoxen  --------
#define IDT_KEINE			    1340
#define IDT_NOOBJEKTE		    1342
#define IDT_KEINIDLANGTEXT	    1343
#define IDT_KEINMKLANGTEXT	    1344


//---------StatShortHelp-------------------------
#define IDH_HELPOBJEIGENSCH	    1345
#define IDH_HELPMKANZEIGE	    1346
#define IDH_HELPOBJTYP		    1347
#define IDH_HELPNOOBJTYP	    1348
#define IDH_HELPALLEKLASSEN	    1349
#define IDH_HELPOKLSUMM		    1350
#define IDH_HELPTEMPOKL		    1351
#define IDH_HELPCLIPBOARD	    1352

#define IDH_LINIENINTERVALL	    1390
#define IDH_FLAECHENINTERVALL	1391 
#define IDH_HELPNOOBJEIGENSCH	1392

#define IDH_HELPMKEXISTIERT	1393
#define IDH_HELPNOMKEXISTIERT	1394
#define IDH_HELPNOMKANZEIGE	1395

#define IDH_HELPBEZLINIENOKL	1396
#define IDH_HELPBEZFLAECHENOKL	1397

//-----------Help-GIClassification----------------
#define IDH_HELPMASSEINHEIT	    1360
#define IDH_HELPEINZELKRITERIUM	    1361
#define IDH_HELPINTERVALLANGABE	    1362
#define IDH_HELPWIDERSPRUCH	    1363
#define IDH_HELPOKLBESCHREIBUNG	    1364
#define IDH_HELPBEZOKLBESCHREIBUNG  1365
#define IDH_HELPMKBESCHREIBUNG	    1366
#define IDH_HELPNOBESCHREIBUNG	    1367

//------------ERROR-MESSAGE-----------------------
#define IDE_ERRNOOKL		    1370
#define IDE_ERRNOMK		    1371
#define IDE_ERRNOPBD		    1372


#define IDS_KEINEANSICHT	    1380
#define IDS_SICHTAUSSCHNITT	    1381

//-----GIClassification-Fenster---------------
#define IDC_LISTOBJCLASS	1410
#define IDC_LISTMASSEINH	1420
#define IDC_BUTTONEINZEL	1430
#define IDC_BUTTONINTERVALL	1440
#define IDT_INTERVALLTEXT	1445
#define IDT_INTERVALLWERT	1450
#define IDT_TEXTELEMENTS	1452
#define IDT_NUMBERELEMENTS	1455
#define IDC_LISTMATHOPONE	1460
#define IDT_OBJEKTKLASSE	1465
#define IDC_LISTMATHOPTWO	1470
#define IDT_VERGLWERTMIN	1480
#define IDT_VERGLWERTMAX	1490
#define IDT_HILFETEXT		1493

//---Geometriklassifikation - MessageTexte
#define IDS_GICLASSIFICATION	1495
#define IDS_GICLASSNOOBJECTS	1496
#define IDS_GICLASSNORECH	1497
#define IDS_GICLASSSTOPWORK	1498
#define IDS_GICLASSCOUNTINTERVALL 1499
//-----------------------------------
#define IDS_GICLASSCREATEINTERVALL	1500
#define IDS_GICLASSOBJEKT	 1501


#define IDS_LINIEN		1510
#define IDS_FLAECHEN		1515

// mathematische Operationen
#define IDS_KLEINER		1520
#define IDS_KLEINERGLEICH	1525
#define IDS_GLEICH		1530
#define IDS_UNGLEICH		1535
#define IDS_GROESSER		1540
#define IDS_GROESSERGLEICH	1545

#define IDT_KEININTERVALLWERT	1550

// Allgemeine Texte MessageBox
#define IDS_CREATEDBOBJECTS	1560
#define IDS_CREATEOBJCLASS	1561
#define IDS_ARITHMITTEL		1562
#define IDS_MEDIANWERT		1563
//-------------------------------------
#define IDS_STARTRECHERCHE	1565
#define IDS_OBJEKTRECHERCHE	1566
#define IDS_GAUGEBOX		1567
#define IDS_NODEFOBJCLASS	1568
#define IDS_NODEFMERKMAL	1569
#define IDS_FLAECHENTEXT	1570
#define IDS_LINIENTEXT		1571
#define IDS_DBUEBERSICHT	1572
#define IDS_ORWINDOWTEXT	1573
#define IDS_FLAECHENKLASSE	1574
#define IDS_LINIENKLASSE	1575
#define IDS_MINIMUMMAXIMUM	1576
#define IDS_TIMERCAPTION	1577
#define IDS_OBJCLASSCAPTION	1578


//Zwischenablage
#define IDLB_CLIPPARMLISTE	1650
#define IDB_CLIPREIHENFOLGE	1651
#define IDS_CLIPBESCHREIBUNG	1652
#define IDC_CLIPUEBERSCHRIFT	1653
#define IDC_CLIPOKLEIGENSCH	1654
#define IDC_CLIPKUMULATIV	1655
#define IDC_CLIPCOUNTEINTRAG	1656
//------Parameter:ClipBoard----------
#define IDS_CLIPOBJCLASSKEY	1660
#define IDS_CLIPOBJCLASSSHORT	1661
#define IDS_CLIPOBJCLASSLONG	1662
#define IDS_CLIPFLAECHENGROESSE	1663
#define IDS_CLIPLINIENLAENGE	1664
#define IDS_CLIPMEDIANWERT	1665
#define IDS_CLIPARITHMITTEL	1666
#define IDS_CLIPCOUNTER		1667
#define IDS_CLIPMINIMUM		1668
#define IDS_CLIPMAXIMUM		1669
//------Hilfe:ClipBoard----------
#define IDH_CLIPOBJCLASSKEY	1670
#define IDH_CLIPOBJCLASSSHORT	1671
#define IDH_CLIPOBJCLASSLONG	1672
#define IDH_CLIPFLAECHENGROESSE	1673
#define IDH_CLIPLINIENLAENGE	1674
#define IDH_CLIPMEDIANWERT	1675
#define IDH_CLIPARITHMITTEL	1676
#define IDH_CLIPCOUNTER		1677
#define IDH_CLIPMINIMUM		1678
#define IDH_CLIPMAXIMUM		1679
//-----------SortierFenster------
#define IDLB_CLIPSORTPARMCLASS	1680
#define IDB_CLIPSORTPLUS	1681
#define IDB_CLIPSORTMINUS	1682
#define IDB_CLIPSORTHILFE	1683
//-----------TextRessourcen ClipBoard-----
#define IDS_CLIPPUNKT		1690
#define IDS_CLIPLINIE		1691
#define IDS_CLIPFLAECHE		1692
#define IDS_CLIPTEXT		1693
//-------------------------------------
//-------------------------------------
//Prozentualer Anteil ergaenzt
#define IDS_CLIPPROZENT		1694
#define IDH_CLIPPROZENT		1695


//-----Nur f¸r uns --------------------
#define IDS_DBOBJECTANZEIGE	1800

//neu
#define IDS_LONGCLASSNAME	2000
#define IDS_OBJPROPCLASSNAME	2100
#endif 	// _GEOSTAT_H
