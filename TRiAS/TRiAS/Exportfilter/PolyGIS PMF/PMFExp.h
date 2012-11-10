// PMFStructur-Definitionen -------------------------------------------------------
// File: PMFExp.H

#if !defined(_PMFEXP_H)
#define _PMFEXP_H
//---------------------------------------------------------------------------------
#define PMFPunkt		0
#define PMFStrecke		1
#define PMFKreis		2
#define PMFText			3
#define PMFMass			4
#define PMFPolyLinie		5
#define PMFFlaeche		6

#define BNAKEYLEN	80		//Max. Länge einer Attributbezeichnung ( Kurztext)
#define PMFKEYCOUNT 8		// Anzahl auszugebender Attribute 

#define POLYGISKEYLEN	28	//Max. Länge Polygis-Merkmal-Feld

double dMaxCont = 9999999.99;
double dMinCont = 0.0;
//---------------------------------------------------------------------------------

// Schlüssel für PMF-Export -------------------------------------------------
char *dTab = "  ";
char *dEnd = "end";

// Projekt
char *dProjektKopf = "object %s: tProject";
//char *dProjekt0 = "  Version = 8.41";
char *dProjekt1 = "  Coords = %s,%s,%s,%s";
/*
char *dProjekt2 = "  ANr =";
char *dProjekt3 = "  Key1 =";
char *dProjekt4 = "  Key2 = ";


// Datei
char *dDateiKopf = "object %s: tRegisterRecNew";
char *dDatei0 = "  0=1@1@111";
char *dDatei1 = "  1=1@2@";
*/

// Datentypen
char *dTypenKopf = "object %s: tDataAccess";
char *dTypen0 = "  LayerTyp = %d";
/*
char *dTypen1 = "  TableName =";
char *dTypen2 = "  GisDbIdent = 00";
char *dTypen3 = "  ObjDbName =";
char *dTypen4 = "  ObjDbIndex =";
char *dTypen5 = "  DbName =";
char *dTypen6 = "  UpdateTable = off";
char *dTypen7 = "  DoRegister = off";
char *dTypen8 = "  wwwHide = off";
*/
char *dTypenKey = "  Key-%.2d = on"; 
char *dTypenAlias = "  Alias-%.2d ="; 
char *dTypenShort = "  ShortName-%.2d =";
//Später - Merkmale statt Key
char *dTypenAliasEx = "  Alias-%.2d = %s"; 
char *dTypenShortEx = "  ShortName-%.2d = %s";

char *dTypenFld = "  FldTyp-%.2d = S"; 


// Entity
char *dEntityKopf = "object %s: tEntity";
char *dEntity0 = "  DbName = %s"; 
//char *dEntity1 = "  DataPath =";
 

// Group
char *dGroupKopf = "object %s: tGroup";
char *dGroup0 = "  Entity = %s"; 


// Layer
char *dLayerKopfN = "object %s: tLayer";
char *dLayerKopf = "object %s_%s: tLayer";
char *dLayer0 = "  Type = %d";
char *dLayer1 = "  Entity = %s";
char *dLayer2 = "  Group = %s";
char *dLayer3 = "  DataAccess = %s";				// Hier nicht nur Standard - auch über def. Gruppen (Color-Template)
/*
char *dLayer4 = "  ResetAttr = on"; 
char *dLayer5 = "  LegendName ="; 
char *dLayer6 = "  LegendBem1 ="; 
char *dLayer7 = "  LegendBem2 ="; 


// UserLayer
char *dUserLayerKopfN = "object %s: tUserLayerProperty";
char *dUserLayerKopf = "object %s_%s: tUserLayerProperty";
char *dUserLayer0 = "  Type = %d";

char *dUserLayer1 = "  User = 000";
char *dUserLayer2 = "  Visible = on";
char *dUserLayer3 = "  Available = on";
char *dUserLayer4 = "  Priority = 1000";
char *dUserLayer5 = "  CADPri = 1000";
//char *dUserLayer6 = "  AttrDef = %s";
*/

// Objekt
//char *dObjektKopf = "object %ld: tSeg";
char *dObjektKopf = "object %ld: %s";
/*
char *dObjektrsp = "  rSP = 0.000";
char *dObjekthsp = "  hSP = 0.000";
char *dObjektAlpa = "  alphaSP = 0";
char *dObjektSigB = "  SigBegin = 0";
char *dObjektSigE = "  SigEnd = 0";
char *dObjektAlpaFS = "  alphaFS = 0.000";
char *dObjektOptions = "  options = 0";
*/
char *dObjektCount = "  ObjCount = %d";

// Koordinaten
char *dKoordinatenKopf = "object -1: tGeoObj";
char *dKoordinatenR = "  r = %s";
char *dKoordinatenH = "  h = %s";

// Merkmale
char *dMerkmalsKopf = "Layer = %s";
char *dMerkmalsKopf0 = "Layer = %s_%s";
char *dMerkmalsKopf1 = "object Keys: tKeys";
char *dMerkmal = "  Key-%.2d = %s";

///////////////////////////////////////////////////////////////////////////////////////
#endif // _PMFEXP_H

