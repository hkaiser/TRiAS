// Importty.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "importty.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	spezielle Begin/End-Import-Funktionen
BOOL OpenAbfallArtenSet (CImportParams* pParams)
{
	ASSERT (NULL != pParams);
	ASSERT (pParams -> m_SourceDatabase.IsOpen ());

	pParams -> m_pParamSet = new CDaoRecordset (&pParams -> m_SourceDatabase);
	CString strSQL;
	VERIFY (strSQL.LoadString (IDS_SELECT_DICHTEART));
	pParams -> m_pParamSet -> Open (dbOpenSnapshot, strSQL, dbReadOnly);

	return TRUE;
}

//	spezielle Konvertierungsfunktionen
BOOL DoNothing (CImportParams*)			{ return TRUE; }

//	Abfallmengen übernehmen bzw. entsprechend der Dichte berechnen
BOOL HandleAbfallMengen (CImportParams* pParams)
{ 
	ASSERT (NULL != pParams);
	ASSERT (pParams -> m_SourceSet.IsOpen ());
	ASSERT (pParams -> m_DestSet.IsOpen ());

//	Eingabe-Menge lesen
	double dMengeT = 0.0;
	COleVariant vars (pParams -> m_SourceSet.GetFieldValue (_T("menge_t")));
	ASSERT (VT_R8 == vars.vt);
	dMengeT = vars.dblVal;

//	wenn Menge nicht gegeben: Menge über Voulumen und Dichte berechnen
	if (dMengeT <= 0)
	{
		double dMengeV = 0.0;
		vars = pParams -> m_SourceSet.GetFieldValue (_T("menge_cbm"));
		ASSERT (VT_R8 == vars.vt);
		dMengeV = vars.dblVal;

	//	nur bei gültigem Wert Dichte lesen
		if (dMengeV > 0.0)
		{
			ASSERT (NULL != pParams -> m_pParamSet);
			ASSERT (pParams -> m_pParamSet -> IsOpen ());
			double dDichte = 0.0;

		//	lese Abfallart
			char SearchField [] = _T("nrabfart");
			COleVariant vara (pParams -> m_SourceSet.GetFieldValue (SearchField));
			if (VT_EMPTY != vara.vt)
			{
				char *pVal = (char *) vara.pbVal;
				if (pVal && *pVal)
				//	jetzt Dichte lesen
				{
					CString strWhere;
					AfxFormatString2 (strWhere, IDS_FIND_DICHTE, SearchField, pVal);
					if (pParams -> m_pParamSet -> FindFirst (strWhere))
					{
						vara = pParams -> m_pParamSet -> GetFieldValue (_T("Dichte"));
						dDichte = vara.dblVal;
					}
				}
			}

		//	Menge in Tonnen berechnen
			if (dDichte > 0.0)
				dMengeT = dDichte * dMengeV;
		}
	}

//	Wert ausgeben
	vars.dblVal = dMengeT;	
	pParams -> m_DestSet.SetFieldValue (_T("Menge_t"), vars);

	return TRUE; 
}

//	Typ-Umwandlung der Dichte bei Abfallarten durchführen, wenn Input Foxpro-Datei
BOOL HandleDichte (CImportParams* pParams)		
{ 
	ASSERT (NULL != pParams);
	ASSERT (pParams -> m_SourceSet.IsOpen ());
	ASSERT (pParams -> m_DestSet.IsOpen ());

	COleVariant vars (pParams -> m_SourceSet.GetFieldValue (_T("Dichte")));
	ASSERT (VT_R8 == vars.vt);
	COleVariant vard;		
	vard.ChangeType (VT_R4, vars);
	pParams -> m_DestSet.SetFieldValue (_T("Dichte"), vard);	
	return TRUE; 
}		

//	Plz auf 5 Zeichen verkürzen
BOOL HandlePlz (CImportParams* pParams, char *pInFieldName)		
{ 
	ASSERT (NULL != pParams);
	ASSERT (pParams -> m_SourceSet.IsOpen ());
	ASSERT (pParams -> m_DestSet.IsOpen ());
	ASSERT (NULL != pInFieldName && AfxIsValidString (pInFieldName));

	char OutFieldName [] = _T("Postleitzahl");

//	lese FoxPro-Plz
	COleVariant vars (pParams -> m_SourceSet.GetFieldValue (pInFieldName));
	if (VT_NULL == vars.vt)
	{
		pParams -> m_DestSet.SetFieldValueNull (OutFieldName);
		return TRUE;
	}

//	left trim vornehmen
	char *pVal = (char *) vars.pbVal;
	while (pVal && *pVal && *pVal == ' ')
		pVal++;
	if (!pVal || !*pVal)
		pParams -> m_DestSet.SetFieldValueNull (OutFieldName);								
	else
	{
	//	Länge ggf. begrenzen
		char PlzBuffer [PlzLaenge + 5] = "";
		if (strlen (pVal) > PlzLaenge)
		{
			strncpy (PlzBuffer, pVal, PlzLaenge);
			pVal = PlzBuffer;
		}			

		if (pVal != (char *)vars.pbVal)
		{
			COleVariant vard (pVal, VT_BSTRT);
			pParams -> m_DestSet.SetFieldValue (OutFieldName, vard);
		}
		else
			pParams -> m_DestSet.SetFieldValue (OutFieldName, vars);							
	}
	return TRUE; 
}	

BOOL HandleTransEntsPlz (CImportParams* pParams)		
{
	return HandlePlz (pParams, _T("Plz"));	
}

BOOL HandleGemeindePlz (CImportParams* pParams)		
{
	return HandlePlz (pParams, _T("Postleit"));
}

//	Gemeinde-Nummer: dbDouble in Text10 umwandeln
BOOL HandleGemeindeNr (CImportParams* pParams)		
{
	ASSERT (NULL != pParams);
	ASSERT (pParams -> m_SourceSet.IsOpen ());
	ASSERT (pParams -> m_DestSet.IsOpen ());

	char OutFieldName [] = _T("Nummer");

	COleVariant vars (pParams -> m_SourceSet.GetFieldValue (_T("Schl_sseln")));
	if (VT_NULL == vars.vt)
	{
		pParams -> m_DestSet.SetFieldValueNull (OutFieldName);
		return TRUE;
	}
	ASSERT (VT_R8 == vars.vt);			// Typ ok ?

//	Konvertierung vornehmen
	char Buffer [NummerLaenge + 10] = "";
	itoa ((int)vars.dblVal, Buffer, 10);
	if (strlen (Buffer) > NummerLaenge)
		Buffer [NummerLaenge - 1] = '\0';
	COleVariant vard (Buffer, VT_BSTRT);

	pParams -> m_DestSet.SetFieldValue (OutFieldName, vard);

	return TRUE;
}

// Text in Boolsches Feld umwandeln
BOOL HandleEntsZur 	(CImportParams* pParams)		
{
	ASSERT (NULL != pParams);
	ASSERT (pParams -> m_SourceSet.IsOpen ());
	ASSERT (pParams -> m_DestSet.IsOpen ());

	char OutFieldName [] = _T("Zurueck");
	COleVariant vard;
	vard.ChangeType (VT_BOOL);
	vard.bVal = FALSE;	

//	lese FoxPro-Feld
	COleVariant vars (pParams -> m_SourceSet.GetFieldValue (_T("Zur_ck")));
	if (VT_NULL == vars.vt)
	{
		pParams -> m_DestSet.SetFieldValue (OutFieldName, vard);
		return TRUE;
	}

//	prüfe Feldinhalt
	char *pVal = (char *)vars.pbVal;
	if (pVal && *pVal == 'x' || *pVal == 'X')
		vard.bVal = TRUE;
	
	pParams -> m_DestSet.SetFieldValue (OutFieldName, vard);
	return TRUE;
}

BOOL HandleBesBegruendung (CImportParams* pParams)
{
	ASSERT (NULL != pParams);
	ASSERT (pParams -> m_SourceSet.IsOpen ());
	ASSERT (pParams -> m_DestSet.IsOpen ());

	char OutFieldName [] = _T("Bemerkungen");
	COleVariant vard ("");
	
//	lese FoxPro-Feld
	COleVariant vars (pParams -> m_SourceSet.GetFieldValue (_T("Begruend")));
	if (VT_NULL != vars.vt)
		pParams -> m_DestSet.SetFieldValue (OutFieldName, vard);
	else
		pParams -> m_DestSet.SetFieldValueNull (OutFieldName);

	return TRUE;
}

BOOL HandleEntsorgerBem (CImportParams* pParams)
{
	ASSERT (NULL != pParams);
	ASSERT (pParams -> m_SourceSet.IsOpen ());
	ASSERT (pParams -> m_DestSet.IsOpen ());

	char OutFieldName [] = _T("Entsorgerbemerkungen");
	COleVariant vard ("");
	
//	lese FoxPro-Feld
	COleVariant vars (pParams -> m_SourceSet.GetFieldValue (_T("Bemerk")));
	if (VT_NULL != vars.vt)
		pParams -> m_DestSet.SetFieldValue (OutFieldName, vard);
	else
		pParams -> m_DestSet.SetFieldValueNull (OutFieldName);

	return TRUE;
}

FieldKonvert AbfallFieldKonvertFoxPro [] = 
{
	{ _T("registrnum"),	dbText,		10,		NULL},					// C10
	{ _T("nrabfart"),	dbText,		10,		NULL},					// C10
	{ _T("menge_t"),	dbDouble,	-1,		HandleAbfallMengen},	// F10/3
	{ _T("vorbehandl"), dbText,		1,		NULL},					// C1 
	{ _T("transporte"), dbText,		10,		NULL},					// C10
	{ _T("entsorgnr"),	dbText,		10,		NULL},					// C10
	{ _T("evn_e"),		dbText,		10,		DoNothing},
	{ _T("eingabedat"), dbDate,		-1,		NULL},					// D8
	{ _T("aendergdat"), dbDate,		-1,		NULL},					// D8
	{ _T("Verwertpru"),	dbText,		80,		DoNothing},
	{ _T("evn_e"),		dbText,		10,		DoNothing},
	NULL		
};

//	neue Felder für Abfälle: #JB970603
FieldKonvert AbfallFieldKonvertFoxProNew [] = 
{
	{ _T("Abfcode"),	dbText,		5,		NULL},
	{ _T("Freistell"),	dbText,		20,		NULL},
	{ _T("Verfahren"),	dbText,		3,		NULL},
	{ _T("Eigenents"),	dbBoolean,	-1,		NULL},
	{ _T("Bemerk"),		dbText,		128,	HandleEntsorgerBem},
	{ _T("Begruend"),	dbText,		128,	HandleBesBegruendung},
	NULL
};

FieldKonvert AbfallFieldKonvertMdb [] =
{
	{ _T("Nummer"),					dbText,		10,		NULL},			// T10
	{ _T("Abfallnummer"),			dbText,		10,		NULL},			// T10
	{ _T("Menge_t"),				dbDouble,	-1,		NULL},			// DF3
	{ _T("Vorbehandlung"),			dbText,		1,		NULL},			// T1
	{ _T("Transporteurnummer"),		dbText,		10,		NULL},			// T10
	{ _T("Entsorgernummer"),		dbText,		10,		NULL},			// T10
	{ _T("Entsorgerbemerkungen"),	dbMemo,		-1,		NULL},			// Memo
	{ _T("Erfassungsdatum"),		dbDate,		-1,		NULL},			// Date
	{ _T("Aenderungsdatum"),		dbDate,		-1,		NULL},			// Date
	{ _T("Bemerkungen"),			dbMemo,		-1,		NULL},			// Memo
	{ _T("Transporteurbemerkungen"),dbMemo,		-1,		NULL},			// Memo
	NULL
};

//	neue Felder für Abfälle: #JB970603
FieldKonvert AbfallFieldKonvertMdbNew [] =
{
	{ _T("Verbringungscode"),		dbText,		10,		NULL},	
	{ _T("Freistellungsnummer"),	dbText,		20,		NULL},
	{ _T("Entsorgungsverfahren"),	dbText,		5,		NULL},
	{ _T("Eigenentsorgung"),		dbBoolean,	-1,		NULL},
	{ _T("Abfallbezeichnung"),		dbText,		80,		NULL},		
	{ _T("Betreibernummer"),		dbText,		10,		NULL},
	{ _T("Entsorgungspartner"),		dbText,		30,		NULL},
	{ _T("Entsorgungstelefon"),		dbText,		20,		NULL},
	{ _T("Entsorgungstelefax"),		dbText,		20,		NULL},
	{ _T("Entsorgungsfreistellung"),dbBoolean,	-1,		NULL},
	{ _T("Betreiberbemerkungen"),	dbMemo,		-1,		NULL},
	{ _T("Eigentransport"),			dbBoolean,	-1,		NULL},
	{ _T("EAKNummer"),				dbText,		10,		NULL},
	{ _T("Nachweisnummer"),			dbText,		20,		NULL},
	{ _T("Exportiert"),				dbText,		 1,		NULL},
	NULL
};

//	Indizes für Abfälle, die zu erzeugen sind
IndexFieldInfo AbfallIndexField [] =
{
	{ _T("Nummer")				,TRUE	},	// NULL ist nicht erlaubt 
	{ _T("Abfallnummer")		,TRUE	},	
	{ _T("Transporteurnummer")	,FALSE	},	
	{ _T("Entsorgernummer")		,FALSE	},
	{ _T("Betreibernummer")		,FALSE	},	
	{ _T("Nachweisnummer")		,FALSE	},	
	NULL
};

//	FoxPro-Erzeuger-Felder
FieldKonvert ErzeugerFieldKonvertFoxPro [] =
{
	{ _T("erznr"),		dbText,		9,		NULL},			// C9
	{ _T("bezanfal"),	dbText,		30,		NULL},			// C30
	{ _T("betr_anl"),	dbText,		30,		NULL},			// C30
	{ _T("stranfal"),	dbText,		30,		NULL},			// C30
	{ _T("hausnran"),	dbText,		4,		NULL},			// C4
	{ _T("plzanfal"),	dbText,		5,		NULL},			// C5
	{ _T("ortanfal"),	dbText,		30,		NULL},			// C30
	{ _T("gkz"),		dbText,		10,		NULL},			// C10
	{ _T("anspr"),		dbText,		30,		NULL},			// C30
	{ _T("telanspr"),	dbText,		20,		NULL},			// C20
	{ _T("faxanspr"),	dbText,		20,		NULL},			// C20
	{ _T("brnace"),		dbText,		10,		NULL},			// C10
	{ _T("firma"),		dbText,		40,		NULL},			// C40
	{ _T("strfa"),		dbText,		30,		NULL},			// C30
	{ _T("hnrfa"),		dbText,		4,		NULL},			// C4
	{ _T("plzfa"),		dbText,		5,		NULL},			// C5
	{ _T("ortfa"),		dbText,		30,		NULL},			// C30
//	{ _T("betrenan"),	dbText,		9,		NULL},			// C9
//	{ _T("artents"),	dbText,		30,		NULL},			// C30
	{ _T("datverz"),	dbDate,		-1,		NULL},			// D8
	{ _T("datkor"),		dbDate,		-1,		NULL},			// D8
	{ _T("bemerkung"),	dbText,     80,     NULL},			// C80
	NULL
};

	//	FoxPro-Erzeuger-Felder (neue Version): #970505
FieldKonvert ErzeugerFieldKonvertFoxProNew [] =
{
	{ _T("telfa"),		dbText,		20,		NULL},			// C20
	{ _T("faxfa"),		dbText,		20,		NULL},			// C20
	{ _T("ansprfa"),	dbText,		30,		NULL},			// C30
	{ _T("funkanspr"),	dbText,		30,		NULL},			// C30
	{ _T("bimschnr"),	dbText,		5,		NULL},			// C5
	{ _T("bimschsp"),	dbText,		1,		NULL},			// C1
	{ _T("Exportiert"),	dbText,		1,		NULL},
	{ _T("EDV"),		dbText,		3,		NULL},
	{ _T("EDVsonstige"),dbText,		40,		NULL},
	{ _T("Unterschrift"),dbBoolean,	-1,		NULL},
	NULL
};

//	Indizes für Erzeuger
IndexFieldInfo ErzeugerIndexField [] =
{
	{ _T("Ortsname")			,FALSE	},	// NULL ist erlaubt 
	{ _T("Gemeindekennzahl")	,FALSE	},	// bei allen Feldern
	{ _T("Branchennummer")		,FALSE	},
	NULL
};

//	MDB-GAK-Format
FieldKonvert ErzeugerFieldKonvertMdb [] =
{
	{ _T("Nummer"),							dbText,		10,		NULL},			// T10
	{ _T("Anfallstelle"),					dbText,		80,		NULL},			// T80
	{ _T("Betriebsstaette"),				dbText,		80,		NULL},			// T80
	{ _T("Strasse"),						dbText,		80,		NULL},			// T80
	{ _T("Hausnummer"),						dbText,		10,		NULL},			// T10
	{ _T("Postleitzahl"),					dbText,		5,		NULL},			// T5
	{ _T("Ortsname"),						dbText,		50,		NULL},			// T50
	{ _T("Gemeindekennzahl"),				dbText,		10,		NULL},			// T10
	{ _T("Ansprechpartner"),				dbText,		30,		NULL},			// T30
	{ _T("Partnertelefon"),					dbText,		20,		NULL},			// T20
	{ _T("Partnertelefax"),					dbText,		20,		NULL},			// T20
	{ _T("Branchennummer"),					dbText,		10,		NULL},			// T10
	{ _T("Firmenname"),						dbText,		80,		NULL},			// T80
	{ _T("Firmenstrasse"),					dbText,		80,		NULL},			// T80
	{ _T("Firmenhausnummer"),				dbText,		10,		NULL},			// T10
	{ _T("Firmenpostleitzahl"),				dbText,		5,		NULL},			// T5
	{ _T("Firmenortsname"),					dbText,		50,		NULL},			// T50
//	{ _T("Entsorgungsnummer"),				dbText,		10,		NULL},			// T10
//	{ _T("Entsorgungsart"),					dbText,		80,		NULL},			// T80
	{ _T("Erfassungsdatum"),				dbDate,		-1,		NULL},			// Datum/Zeit
	{ _T("Aenderungsdatum"),				dbDate,		-1,		NULL},			// Datum/Zeit
	{ _T("Bemerkungen"),					dbMemo,		-1,		NULL},			// Memo	
	NULL
};

//	neue Felder: #JB970505
FieldKonvert ErzeugerFieldKonvertMdbNew [] =
{
	{ _T("Firmentelefon"),					dbText,		20,		NULL},			// T20
	{ _T("Firmentelefax"),					dbText,		20,		NULL},			// T20
	{ _T("Firmenansprechpartner"),			dbText,		30,		NULL},			// T30
	{ _T("Partnerfunktion"),				dbText,		30,		NULL},			// T30
	{ _T("Bimschnummer"),					dbText,		5,		NULL},			// T5
	{ _T("Bimschspalte"),					dbText,		1,		NULL},			// T1
	{ _T("Betreibernummer"),				dbText,		20,		NULL},			// ff. Felder ex. 
	{ _T("Bimschgenehmigungsnummer"),		dbText,		30,		NULL},			// nicht in FoxPro oder	
	{ _T("Anzeigenachweisverordnung"),		dbBoolean,	-1,		NULL},			// alten Version	
	{ _T("Antragsnummer"),					dbText,		20,		NULL},
	{ _T("Betriebsbeauftragter"),			dbText,		30,		NULL},
	{ _T("Betriebsbeauftragtennummer"),		dbLong,		-1,		NULL},
	{ _T("Betriebsbeauftragtentelefon"),	dbText,		20,		NULL},
	{ _T("Betriebsbeauftragtentelefax"),	dbText,		20,		NULL},
	{ _T("Bilanznummer"),					dbText,		20,		NULL},
	{ _T("Exportiert"),						dbText,		1,		NULL},
	{ _T("EDV"),							dbText,		3,		NULL},
	{ _T("EDVsonstige"),					dbText,		40,		NULL},
	{ _T("Unterschrift"),					dbBoolean,	-1,		NULL},
	NULL
};


//	MDB-Arsys-Format
/*
FieldKonvert ErzeugerFieldKonvertMdbArsys [] =
{
	{ _T("EZSCHL"),							dbText,		9,		NULL},			// T9
	{ _T("FIRMA1"),							dbText,		30,		NULL},			// T30
	{ _T("FIRMA2"),							dbText,		30,		NULL},			// T30
	{ _T("BEZ1"),							dbText,		30,		NULL},			// T30
	{ _T("BEZ2"),							dbText,		30,		NULL},			// T30
	{ _T("Strasse"),						dbText,		80,		NULL},			// T80
	{ _T("Hausnummer"),						dbText,		10,		NULL},			// T10
	{ _T("Postleitzahl"),					dbText,		5,		NULL},			// T5
	{ _T("Ortsname"),						dbText,		50,		NULL},			// T50
	{ _T("Gemeindekennzahl"),				dbText,		10,		NULL},			// T10
	{ _T("Ansprechpartner"),				dbText,		30,		NULL},			// T30
	{ _T("Partnertelefon"),					dbText,		20,		NULL},			// T20
	{ _T("Partnertelefax"),					dbText,		20,		NULL},			// T20
	{ _T("Branchennummer"),					dbText,		10,		NULL},			// T10
	{ _T("Firmenname"),						dbText,		80,		NULL},			// T80
	{ _T("Firmenstrasse"),					dbText,		80,		NULL},			// T80
	{ _T("Firmenhausnummer"),				dbText,		10,		NULL},			// T10
	{ _T("Firmenpostleitzahl"),				dbText,		5,		NULL},			// T5
	{ _T("Firmenortsname"),					dbText,		50,		NULL},			// T50
//	{ _T("Entsorgungsnummer"),				dbText,		10,		NULL},			// T10
//	{ _T("Entsorgungsart"),					dbText,		80,		NULL},			// T80
	{ _T("Erfassungsdatum"),				dbDate,		-1,		NULL},			// Datum/Zeit
	{ _T("Aenderungsdatum"),				dbDate,		-1,		NULL},			// Datum/Zeit
	{ _T("Bemerkungen"),					dbMemo,		-1,		NULL},			// Memo	
	{ _T("Firmentelefon"),					dbText,		20,		NULL},			// T20
	{ _T("Firmentelefax"),					dbText,		20,		NULL},			// T20
	{ _T("Firmenansprechpartner"),			dbText,		30,		NULL},			// T30
	{ _T("Partnerfunktion"),				dbText,		30,		NULL},			// T30
	{ _T("Bimschnummer"),					dbText,		5,		NULL},			// T5
	{ _T("Bimschspalte"),					dbText,		1,		NULL},			// T1
	{ _T("Betreibernummer"),				dbText,		20,		NULL},			// ff. Felder ex. 
	{ _T("Bimschgenehmigungsnummer"),		dbText,		30,		NULL},			// nicht in FoxPro oder	
	{ _T("Anzeigenachweisverordnung"),		dbBoolean,	-1,		NULL},			// alten Version	
	{ _T("Antragsnummer"),					dbText,		20,		NULL},
	{ _T("Betriebsbeauftragter"),			dbText,		30,		NULL},
	{ _T("Betriebsbeauftragtennummer"),		dbLong,		-1,		NULL},
	{ _T("Betriebsbeauftragtentelefon"),	dbText,		20,		NULL},
	{ _T("Betriebsbeauftragtentelefax"),	dbText,		20,		NULL},
	{ _T("Bilanznummer"),					dbText,		20,		NULL},
	NULL
};
*/

FieldKonvert GemeindenFieldKonvertMdb [] =
{
	{ _T("Name"),					dbText,		50,		NULL},		// T50
	{ _T("Nummer"),					dbText,		10,		NULL},		// T10
	{ _T("Amtsnummer"),				dbText,		10,		NULL},		// T10
	{ _T("Postleitzahl"),			dbText,		5,		NULL},		// T5
	{ _T("Bevölkerungsanzahl"),		dbDouble,	-1,		NULL},		// Double
	{ _T("Bevölkerungsdichte"),		dbDouble,	-1,		NULL},		// Double
	{ _T("Fläche"),					dbDouble,	-1,		NULL},		// Double
	NULL
};

FieldKonvert GemeindenFieldKonvertFoxPro [] =
{
	{ _T("Gemeinde"),				dbText,		29,		NULL},		// C29
	{ _T("Schl_sseln"),				dbDouble,	-1,		HandleGemeindeNr},		// N10 --> in Text 10 konv.
	//{ _T("Amtnr"),					dbText,		6,		NULL},		// C6
	//{ _T("Postleit"),					dbText,		7,		HandleGemeindePlz},		// C7 --> in Text 5 konv.
	//{ _T("BevÍlkerun"),				dbDouble,	-1,		NULL},		// N10
	//{ _T("BevÍlkdich"),				dbDouble,	-1,		NULL},		// N11/1
	//{ _T("Fl-che"),					dbDouble,	-1,		NULL},		// N10/2
	NULL
};

FieldKonvert BranchenFieldKonvertMdb [] =
{
	{ _T("Nummer"),					dbText,		10,		NULL},		// T10
	{ _T("Name"),					dbText,		140,	NULL},		// T140
	NULL
};

FieldKonvert BranchenFieldKonvertFoxPro [] =
{
	{ _T("Branchennr"),				dbText,		10,		NULL},		// C10
	{ _T("Branchenbz"),				dbText,		140,	NULL},		// C140
	NULL
};

FieldKonvert VerfahrenFieldKonvertMdb [] =
{
	{ _T("Nummer"),					dbText,		5,		NULL},		// T5
	{ _T("Name"),					dbText,		80,		NULL},		// T80
	{ _T("Bemerkungen"),			dbText,		255,	NULL},		// T255
	NULL
};

FieldKonvert VerfahrenFieldKonvertFoxPro [] =
{
	{ _T("Nummer"),					dbText,		5,		NULL},		// T5
	{ _T("Name"),					dbText,		80,		NULL},		// T80
	{ _T("Bemerkung"),				dbText,		255,	NULL},		// T255
	NULL
};

FieldKonvert KreisFieldKonvertMdb [] =
{
	{ _T("Nummer"),					dbText,		10,		NULL},		
	{ _T("Name"),					dbText,		50,		NULL},	
	{ _T("Kuerzel"),				dbText,		5,		NULL},
	NULL
};

FieldKonvert VerbringungFieldKonvertMdb [] =
{
	{ _T("Nummer"),					dbText,		10,		NULL},		
	{ _T("Name"),					dbText,		255,	NULL},	
	NULL
};

FieldKonvert AbfallArtenFieldKonvertMdb [] =
{
	{ _T("Nummer"),					dbText,		10,		NULL},		// T10
	{ _T("Name"),					dbText,		128,	NULL},		// T128
//	{ _T("Herkunft"),				dbText,		128,	NULL},		// T128
	{ _T("Sonderabfall"),			dbBoolean,	-1,		NULL},		// BOOLEAN
//	{ _T("Labfgmass"),				dbBoolean,	-1,		NULL},		// BOOLEAN
	{ _T("Dichte"),					dbSingle,	-1,		NULL},		// Single:F2
//	{ _T("Cpb"),					dbText,		1,		NULL},		// T1
//	{ _T("Hmv"),					dbText,		1,		NULL},		// T1
//	{ _T("Sav"),					dbText,		1,		NULL},		// T1
//	{ _T("Hmd"),					dbText,		1,		NULL},		// T1
//	{ _T("Sad"),					dbText,		1,		NULL},		// T1
//	{ _T("Utd"),					dbText,		1,		NULL},		// T1
//	{ _T("Bemerkungen"),			dbText,		80,		NULL},		// T80
	NULL
};

FieldKonvert AbfallArtenFieldKonvertFoxPro [] =
{
	{ _T("Nrabfart"),				dbText,		10,		NULL},		// C10
	{ _T("Abfall_art"),				dbText,		100,	NULL},		// C100
//	{ _T("Herkunft"),				dbText,		110,	NULL},		// C110
	{ _T("Ueabfbestv"),				dbBoolean,	-1,		NULL},		// BOOLEAN
//	{ _T("Labfgmass"),				dbBoolean,	-1,		NULL},		// BOOLEAN
	{ _T("Dichte"),					dbDouble,	-1,		HandleDichte}, // N4/2
//	{ _T("Cpb"),					dbText,		1,		NULL},		// C1
//	{ _T("Hmv"),					dbText,		1,		NULL},		// C1
//	{ _T("Sav"),					dbText,		1,		NULL},		// C1
//	{ _T("Hmd"),					dbText,		1,		NULL},		// C1
//	{ _T("Sad"),					dbText,		1,		NULL},		// C1
//	{ _T("Utd"),					dbText,		1,		NULL},		// C1
//	{ _T("Sonstiges"),				dbText,		20,		NULL},		// C20
	NULL
};

FieldKonvert TransporteureFieldKonvertMdb [] =
{
	{ _T("Nummer"),					dbText,		10,		NULL},		// T10
	{ _T("Name"),					dbText,		80,		NULL},		// T80
	{ _T("Strasse"),				dbText,		80,		NULL},		// T80
	{ _T("Ortsname"),				dbText,		50,		NULL},		// T50
	{ _T("Postleitzahl"),			dbText,		5,		NULL},		// T5
	{ _T("Telefon"),				dbText,		20,		NULL},		// T20
	{ _T("Erteilt"),				dbDate,		-1,		NULL},		// Date
	{ _T("Befristet"),				dbDate,		-1,		NULL},		// Date	
	NULL
};

FieldKonvert TransporteureFieldKonvertFoxPro [] =
{
	{ _T("Befnr"),					dbText,		9,		NULL},		// C9
	{ _T("Abfbef"),					dbText,		40,		NULL},		// C40
	{ _T("Str"),					dbText,		25,		NULL},		// C25
	{ _T("Ort"),					dbText,		30,		NULL},		// C30
	{ _T("Plz"),					dbText,		6,		HandleTransEntsPlz},	// C6 in Text 5 umwandeln
	{ _T("Telefonnr"),				dbText,		12,		NULL},		// C12
	{ _T("Erteilt"),				dbDate,		-1,		NULL},		// Date
	{ _T("Befristet"),				dbDate,		-1,		NULL},		// Date
	NULL
};

FieldKonvert EntsorgerFieldKonvertMdb [] =
{
	{ _T("Nummer"),					dbText,		10,		NULL},		// T10
	{ _T("Name"),					dbText,		80,		NULL},		// T80
	{ _T("Anlage"),					dbText,		80,		NULL},		// T80
	{ _T("Anlagenart"),				dbText,		30,		NULL},		// T30
	{ _T("Strasse"),				dbText,		80,		NULL},		// T80
	{ _T("Ortsname"),				dbText,		50,		NULL},		// T50
	{ _T("Postleitzahl"),			dbText,		5,		NULL},		// T5
	{ _T("Erteilt"),				dbDate,		-1,		NULL},		// Date
	{ _T("Zurueck"),				dbBoolean,	-1,		NULL},		// BOOLEAN
	NULL
};

FieldKonvert EntsorgerFieldKonvertFoxPro [] =
{
	{ _T("Entsnr"),					dbText,		9,		NULL},		// C9
	{ _T("Abfents"),				dbText,		60,		NULL},		// C60
	{ _T("Entsanl"),				dbText,		70,		NULL},		// C70
	{ _T("Entsart"),				dbText,		20,		NULL},		// C20
	{ _T("Str"),					dbText,		35,		NULL},		// C35
	{ _T("Ort"),					dbText,		25,		NULL},		// C25
	{ _T("Plz"),					dbText,		6,		HandleTransEntsPlz},		// C6 in Text5 umwandeln
	{ _T("Erteilt"),				dbDate,		-1,		NULL},		// Date
	{ _T("Zur_ck"),					dbText,		1,		HandleEntsZur},		// C1
	NULL
};

/////////////////////////////////////////////////////////////////////////////
// CImportParams
CImportParams::CImportParams() // ohne try/catch
{
	m_lUpdateCnt = m_lAppendCnt = m_lUpdateErrCnt = m_lAppendErrCnt = 0;
	m_tImportType = MdbTable;
	m_tTableType = Abfall;
	m_pTableInfo = NULL;
	m_bAsNewTable = TRUE;		// als neue Tabelle

	m_pParamSet = NULL;

	m_DestDatabase.Open (((CGakApp *)AfxGetApp ())->DatabaseName());
}

CImportParams::~CImportParams()
{
//	alles schließen
	if (NULL != m_pParamSet)
	{
		if (m_pParamSet -> IsOpen ())
			m_pParamSet -> Close ();
		DELETE_OBJ (m_pParamSet);
	}

	if (m_SourceSet.IsOpen ())
		m_SourceSet.Close ();
	if (m_DestSet.IsOpen ())
		m_DestSet.Close ();
	if (m_SourceDatabase.IsOpen ())
		m_SourceDatabase.Close ();
	if (m_DestDatabase.IsOpen ())
		m_DestDatabase.Close ();

	if (NULL != m_ReportFile.m_pStream)
		m_ReportFile.Close ();

	DELETE_OBJ (m_pTableInfo);
}

// CTableInfo -------------------------------------------
CTableInfo:: CTableInfo (FieldKonvert *pInput, FieldKonvert *pOutput,
						 DatensatzMenge tMenge, DatensatzActual tActual,
						 UINT uiRecordSelectFlag, UINT uiRecordActFlag, 
						 UINT uiTableName, UINT uiDDL, 
						 BOOL bCreateNumberIndex /*FALSE*/, IndexFieldInfo *pInfo/*NULL*/)
{
	m_pFieldKonvertOutput = m_pFieldKonvertInput = NULL;
	pfBeginImport = pfEndImport = NULL;
	m_uiDDL = uiDDL;
	m_pIndexFieldInfo = pInfo;
	m_tMenge = tMenge;
	m_tActual = tActual;
	
	ASSERT (NULL != pInput);
	ASSERT (NULL != pOutput);

//	Werte übernehmen
	m_pFieldKonvertInput = pInput;
	m_pFieldKonvertOutput = pOutput;

	m_uiRecordSelect = uiRecordSelectFlag;
	m_uiRecordActual = uiRecordActFlag;

	VERIFY (m_strTableName.LoadString (uiTableName));
	VERIFY (m_strKeyOutName1.LoadString (IDS_NUMMER));	// Standardschlüssel
	m_strPrimaryKey = m_strKeyOutName1;			// Suchschlüssel
	m_strKeyInpName1 = m_strKeyOutName1;		// für MDB
	m_bCreateNumberIndex = bCreateNumberIndex;
}	

// CAbfallTableInfo --------------------------------------
CAbfallTableInfo::CAbfallTableInfo(ImportType tKonvertType)
				 :CTableInfo (AbfallFieldKonvertMdb, AbfallFieldKonvertMdb, 
							  AllRecords, Never, AllRecords, Never, 
							  IDS_ABF_TABLE_NAME_DESCR, IDS_ABFALL_DDL,
							  FALSE, AbfallIndexField)
{
	m_pFieldKonvertInputDyn = m_pFieldKonvertOutputDyn = NULL;

//	Ausgaben-Tabellen-Info muß immer erzeugt werden: und immer alle Felder
	m_pFieldKonvertOutputDyn = ConcatFields (AbfallFieldKonvertMdb, 
										  sizeof (AbfallFieldKonvertMdb) / sizeof (FieldKonvert),
										  AbfallFieldKonvertMdbNew, 
										  sizeof (AbfallFieldKonvertMdbNew) / sizeof (FieldKonvert)
										  );
	if (!m_pFieldKonvertOutput)
		AfxThrowMemoryException ();
	m_pFieldKonvertOutput = m_pFieldKonvertOutputDyn;

//	Eingabefeld bestimmen
	if ((FoxProTable == tKonvertType) || (FoxProTableOld == tKonvertType))
	{
		pfBeginImport = OpenAbfallArtenSet;

		if (FoxProTableOld == tKonvertType)
			m_pFieldKonvertInput = AbfallFieldKonvertFoxPro;				
		else
		{//	neuen Felder anhängen
			m_pFieldKonvertInputDyn = ConcatFields (AbfallFieldKonvertFoxPro, 
												 sizeof (AbfallFieldKonvertFoxPro) / sizeof (FieldKonvert),
												 AbfallFieldKonvertFoxProNew, 
												 sizeof (AbfallFieldKonvertFoxProNew) / sizeof (FieldKonvert)
												 );
			if (!m_pFieldKonvertInputDyn)
				AfxThrowMemoryException ();
			m_pFieldKonvertInput = m_pFieldKonvertInputDyn;
		}
	}
	else 
	{	// MdbTable
		if (MdbTableOld == tKonvertType)
			m_pFieldKonvertInput = AbfallFieldKonvertMdb;				
		else
		{
		//	bei neuem MDB-Format doppelten Import verhindern
			m_pFieldKonvertInput = m_pFieldKonvertOutput;
			m_uiRecordSelect |= CheckImportFlag;	
		}
	}		

	m_strKeyInpName1.Empty ();
	m_strKeyInpName2.Empty ();
	m_strKeyOutName1.Empty ();		// kein eindeutiger Schlüssel definierbar
	m_strKeyOutName2.Empty ();	
	m_strPrimaryKey.Empty ();
}

CAbfallTableInfo :: ~CAbfallTableInfo (void)
{
	DELETE_VEC (m_pFieldKonvertInputDyn);
	DELETE_VEC (m_pFieldKonvertOutputDyn);
}

// CErzeugerTableInfo --------------------------------------
CErzeugerTableInfo::CErzeugerTableInfo(ImportType tKonvertType)
				   :CTableInfo (ErzeugerFieldKonvertMdb, ErzeugerFieldKonvertMdb, 
								AllRecords, Index,
							    AllRecords|OnlyRefRecords|OnlyNotRefRecords, Always|Never|Index,
								IDS_ERZ_TABLE_NAME, IDS_ERZEUGER_DDL, FALSE, ErzeugerIndexField)
{
	m_pFieldKonvertInputDyn = m_pFieldKonvertOutputDyn = NULL;

//	Ausgaben-Tabellen-Info muß immer erzeugt werden: und immer alle Felder
	m_pFieldKonvertOutputDyn = ConcatFields (ErzeugerFieldKonvertMdb, 
										  sizeof (ErzeugerFieldKonvertMdb) / sizeof (FieldKonvert),
										  ErzeugerFieldKonvertMdbNew, 
										  sizeof (ErzeugerFieldKonvertMdbNew) / sizeof (FieldKonvert)
										  );
	if (!m_pFieldKonvertOutput)
		AfxThrowMemoryException ();
	m_pFieldKonvertOutput = m_pFieldKonvertOutputDyn;
	
	if ((FoxProTable == tKonvertType) || (FoxProTableOld == tKonvertType))
	{
		if (FoxProTableOld == tKonvertType)
			m_pFieldKonvertInput = ErzeugerFieldKonvertFoxPro;				
		else
		{//	neuen Felder anhängen
			m_pFieldKonvertInputDyn = ConcatFields (ErzeugerFieldKonvertFoxPro, 
												 sizeof (ErzeugerFieldKonvertFoxPro) / sizeof (FieldKonvert),
												 ErzeugerFieldKonvertFoxProNew, 
												 sizeof (ErzeugerFieldKonvertFoxProNew) / sizeof (FieldKonvert)
												 );
			if (!m_pFieldKonvertInputDyn)
				AfxThrowMemoryException ();
			m_pFieldKonvertInput = m_pFieldKonvertInputDyn;
		}
		m_strKeyInpName1 = _T("Erznr");
		m_tActual = Always;
		m_uiRecordActual &= ~Index;
	}
	else 
	{	// MdbTable
		if (MdbTableOld == tKonvertType)
			m_pFieldKonvertInput = ErzeugerFieldKonvertMdb;				
		else
		{
		//	bei neuem MDB-Format auch doppelten Import verhindern
			m_pFieldKonvertInput = m_pFieldKonvertOutput;
			m_uiRecordSelect |= CheckImportFlag;	
		}
	}		
}

CErzeugerTableInfo :: ~CErzeugerTableInfo (void)
{
	DELETE_VEC (m_pFieldKonvertInputDyn);
	DELETE_VEC (m_pFieldKonvertOutputDyn);
}

// CGemeindenTableInfo --------------------------------------
CGemeindenTableInfo::CGemeindenTableInfo(ImportType tKonvertType)
				    :CTableInfo (GemeindenFieldKonvertMdb, GemeindenFieldKonvertMdb, 
								 AllRecords, Index,
							     AllRecords|OnlyRefRecords|OnlyNotRefRecords, Always|Never|Index,
								 IDS_GEM_TABLE_NAME, IDS_GEMEINDEN_DDL)
{
	VERIFY (m_strKeyOutName2.LoadString (IDS_NAME));

	if ((FoxProTable == tKonvertType) || (FoxProTableOld == tKonvertType))
	{
		m_pFieldKonvertInput = GemeindenFieldKonvertFoxPro;				
		m_strKeyInpName1 = _T("Gemeinde");
		m_strKeyInpName2 = _T("Schlüsseln");	
		m_tActual = Always;
		m_uiRecordActual &= ~Index;
	}
	else
		m_strKeyInpName2 = m_strKeyOutName2;		// für MDB
}

// CBranchenTableInfo --------------------------------------
CBranchenTableInfo::CBranchenTableInfo(ImportType tKonvertType)
				   :CTableInfo (BranchenFieldKonvertMdb, BranchenFieldKonvertMdb, 
								AllRecords, Index,
							    AllRecords|OnlyRefRecords|OnlyNotRefRecords, Always|Never|Index,
								IDS_BR_TABLE_NAME, IDS_BRANCHEN_DDL)
{
	if ((FoxProTable == tKonvertType) || (FoxProTableOld == tKonvertType))
	{
		m_pFieldKonvertInput = BranchenFieldKonvertFoxPro;				
		m_strKeyInpName1 = _T("Branchennr");
		m_tActual = Always;
		m_uiRecordActual &= ~Index;
	}
}

// CKreisTableInfo --------------------------------------
CKreisTableInfo::CKreisTableInfo(ImportType tKonvertType)
				:CTableInfo (KreisFieldKonvertMdb, KreisFieldKonvertMdb, 
							 AllRecords, Index,
							 AllRecords|OnlyRefRecords|OnlyNotRefRecords, Always|Never|Index,
							 IDS_KREISE_TABLE_NAME, IDS_KREISE_DDL)
{
	if ((FoxProTable == tKonvertType) || (FoxProTableOld == tKonvertType))
	{
		m_tActual = Always;
		m_uiRecordActual &= ~Index;
	}
}

// CVerfahrenTableInfo --------------------------------------
CVerfahrenTableInfo::CVerfahrenTableInfo(ImportType tKonvertType)
					:CTableInfo (VerfahrenFieldKonvertMdb, VerfahrenFieldKonvertMdb, 
								AllRecords, Index,
								AllRecords|OnlyRefRecords|OnlyNotRefRecords, Always|Never|Index,
								IDS_VERFAHREN_TABLE_NAME, IDS_VERFAHREN_DDL)
{
	if ((FoxProTable == tKonvertType) || (FoxProTableOld == tKonvertType))
	{
		m_pFieldKonvertInput = VerfahrenFieldKonvertFoxPro;
		m_tActual = Always;
		m_uiRecordActual &= ~Index;
	}
}

// CVerbringungTableInfo --------------------------------------
CVerbringungTableInfo::CVerbringungTableInfo(ImportType tKonvertType)
					  :CTableInfo (VerbringungFieldKonvertMdb, VerbringungFieldKonvertMdb, 
							       AllRecords, Index,
							       AllRecords|OnlyRefRecords|OnlyNotRefRecords, Always|Never|Index,
							       IDS_VERBR_TABLE_NAME, IDS_VERBRINGUNG_DDL)
{
	if ((FoxProTable == tKonvertType) || (FoxProTableOld == tKonvertType))
	{
		m_tActual = Always;
		m_uiRecordActual &= ~Index;
	}
}

// CAbfallArtenTableInfo --------------------------------------
CAbfallArtenTableInfo::CAbfallArtenTableInfo(ImportType tKonvertType)
					  :CTableInfo (AbfallArtenFieldKonvertMdb, AbfallArtenFieldKonvertMdb, 
								   AllRecords, Index,
								   AllRecords|OnlyRefRecords|OnlyNotRefRecords, Always|Never|Index,
								   IDS_ABFART_TABLE_NAME, IDS_ABFALLARTEN_DDL)
{
	if ((FoxProTable == tKonvertType) || (FoxProTableOld == tKonvertType))
	{
		m_pFieldKonvertInput = AbfallArtenFieldKonvertFoxPro;				
		m_strKeyInpName1 = _T("Nrabfart");
		m_tActual = Always;
		m_uiRecordActual &= ~Index;
	}
}

// CEntsorgerTableInfo --------------------------------------
CEntsorgerTableInfo::CEntsorgerTableInfo(ImportType tKonvertType)
					:CTableInfo (EntsorgerFieldKonvertMdb, EntsorgerFieldKonvertMdb, 
								 AllRecords, Index,
								 AllRecords|OnlyRefRecords|OnlyNotRefRecords, Always|Never|Index,
								 IDS_ENTS_TABLE_NAME, IDS_ENTSORGER_DDL)
{
	if ((FoxProTable == tKonvertType) || (FoxProTableOld == tKonvertType))
	{
		m_pFieldKonvertInput = EntsorgerFieldKonvertFoxPro;				
		m_strKeyInpName1 = _T("Entsnr");
		m_tActual = Always;
		m_uiRecordActual &= ~Index;
	}
}

// CTransporteureTableInfo --------------------------------------
CTransporteureTableInfo::CTransporteureTableInfo(ImportType tKonvertType)
					    :CTableInfo (TransporteureFieldKonvertMdb, TransporteureFieldKonvertMdb, 
									 AllRecords, Index,
									 AllRecords|OnlyRefRecords|OnlyNotRefRecords, Always|Never|Index,
									 IDS_TR_TABLE_NAME, IDS_TRANSPORTEURE_DDL)
{
	if ((FoxProTable == tKonvertType) || (FoxProTableOld == tKonvertType))
	{
		m_pFieldKonvertInput = TransporteureFieldKonvertFoxPro;				
		m_strKeyInpName1 = _T("Befnr");
		m_tActual = Always;
		m_uiRecordActual &= ~Index;
	}
}

//	Felder zusammenfügen
FieldKonvert *ConcatFields (FieldKonvert *pFieldKonvert1, int iLen1,
							FieldKonvert *pFieldKonvert2, int iLen2)
{
	ASSERT (NULL != pFieldKonvert1);
	ASSERT (NULL != pFieldKonvert2);
	ASSERT ((iLen1 > 0) && (iLen2 > 0));

	int iCnt =  iLen1 + iLen2;

	FieldKonvert *pFields = NULL;
	FieldKonvert *pFieldsRet = pFields;
	try
	{
		pFields = new FieldKonvert [iCnt + 1];		
		pFieldsRet = pFields;
		memset (pFields, 0, (iCnt + 1) * (sizeof (FieldKonvert)));

	//	kopiere Feld1
		for (int i = 0; i < iLen1; i++)
		{
			if (pFieldKonvert1 -> pFieldName && *pFieldKonvert1 -> pFieldName)
				pFields -> pFieldName = pFieldKonvert1 -> pFieldName;
			else
				break;		//	Terminator angetroffen
			pFields -> sType = pFieldKonvert1 -> sType;
			pFields -> sLen = pFieldKonvert1 -> sLen;

			if (pFieldKonvert1 -> pfFieldKonvert)
				pFields -> pfFieldKonvert = pFieldKonvert1 -> pfFieldKonvert;
			else
				NULL;

			pFields++;
			pFieldKonvert1++;
		}

	//	kopiere Feld2
		for (i = 0; i < iLen2; i++)
		{
			if (pFieldKonvert2 -> pFieldName && *pFieldKonvert2 -> pFieldName)
				pFields -> pFieldName = pFieldKonvert2 -> pFieldName;
			else
				break;		//	Terminator angetroffen
			pFields -> sType = pFieldKonvert2 -> sType;
			pFields -> sLen = pFieldKonvert2 -> sLen;

			if (pFieldKonvert2 -> pfFieldKonvert)
				pFields -> pfFieldKonvert = pFieldKonvert2 -> pfFieldKonvert;
			else
				NULL;

			pFields++;
			pFieldKonvert2++;
		}
	}
	catch (CMemoryException *me)
	{
		me -> ReportError ();			// Fehler ausgeben
		me -> Delete ();
	}

	return pFieldsRet;
}

