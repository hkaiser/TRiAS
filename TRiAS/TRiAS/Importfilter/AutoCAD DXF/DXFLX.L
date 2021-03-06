%{
#include "yytab.h"          		// Yacc-Defines und YYSTYPE

//	globale Variablen
const short LexBufferSize = 257; // eine AutoCAD-Zeile hat max. 256 Zeichen
char CommentBuffer [LexBufferSize] = "";

short GetComment (char *pVal);
short FindToken (char *pToken, pKeyList pKL);
short FindAnf (char *pVal);
short FindEndSec (char *pVal);
short SetSectionTable (char *pVal);
short SetHeaderElemTable (char *pVal);
short SetEntityElemTable (char *pVal);
short CreateCoordX (char *pVal);
short CreateCoordY (char *pVal);
short CreateCoordZ (char *pVal);
short CreateWinkel0 (char *pVal);
short CreateWinkel1 (char *pVal);	
short GetText (char *pVal);
short GetLayerName (char *pVal);
short GetName (char *pVal);
short CreateFloat (char *pVal);
short CreateFloat1 (char *pVal);
short CreateFloat2 (char *pVal);
short CreateFloat4 (char *pVal);
short CreateFloat5 (char *pVal);
short CreateFlag0 (char *pVal);
short CreateFlag1 (char *pVal);
short GetVertexCount (char *pVal);

short SetTable (char *pToken, pExtKeyList pList);
void yyerror (short ResourceId);

short GetWinkel (char *pVal);
short GetTextHoehe (char *pVal);

// DXF-Datei-Rahmen
TableInfo FileTable [] = 
{
	{ 0, 			FindAnf 		},
	{ 2, 			SetSectionTable	},
	{ IGNORE_REC, 	NULL 			},
};

//	warte auf Token ENDSEC
TableInfo EndSecTable [] = 
{
	{ 0, 			FindEndSec 		},
	{ IGNORE_REC, 	NULL 			},
};

//	Tabelle f�r die Behandlung der Header-S�tze
TableInfo HeaderTable [] = 
{
	{ 0,			SetHeaderElemTable	},
	{ 9, 			SetHeaderElemTable	},
	{ IGNORE_REC, 	NULL 				},
};

//	Versions-Tabelle
TableInfo VersionTable [] = 
{
	{ 0,			SetHeaderElemTable	},	
	{ 1,			GetText				},
	{ 9,			SetHeaderElemTable	},
	{ IGNORE_REC, 	NULL 				},
};

//	Extension-Tabelle
TableInfo ExtensionTable [] = 
{
	{ 0,			SetHeaderElemTable	},	
	{ 9,			SetHeaderElemTable	},
	{ 10,			CreateCoordX		},
	{ 20,			CreateCoordY		},
	{ 30,			CreateCoordZ		},
	{ IGNORE_REC, 	NULL 				},
};

//	LastEdit-Tabelle
TableInfo LastEditTable [] = 
{
	{ 0,			SetHeaderElemTable	},	
	{ 9,			SetHeaderElemTable	},
	{ 40,			CreateFloat			},
	{ IGNORE_REC, 	NULL 				},
};

ExtKeyList HeaderElemTable [] =
{
	{ "$ACADVER",	VERSION,	VersionTable 	},
	{ "$EXTMIN",	EXT_MIN,	ExtensionTable	},
	{ "$EXTMAX",	EXT_MAX,	ExtensionTable	},
	{ "$LIMMIN",	LIM_MIN,	ExtensionTable	},
	{ "$LIMMAX",	LIM_MAX,	ExtensionTable	},
	{ "$TDUPDATE",	LAST_EDIT,	LastEditTable	},
	{ "ENDSEC",		END_SECT,	FileTable		},		
	{ NULL,			IGNORE_REC,	HeaderTable		},  // unbekannte Variablen sicher
};													// filtern !

//	Tabelle f�r die Behandlung der Entity-S�tze
TableInfo EntityTable [] = 
{
	{ 0,			SetEntityElemTable	},
	{ IGNORE_REC, 	NULL 				},
};

//	Block-Tabelle
TableInfo BlockTable [] = 
{
	{ 0,			SetEntityElemTable	},
	{ 2,			GetName				},
	{ 8,			GetLayerName 		},
	{ 10, 			CreateCoordX		},
	{ 20, 			CreateCoordY		},
	{ 30, 			CreateCoordZ		},
	{ 70,			CreateFlag0			},
	{ IGNORE_REC, 	NULL 				},
};

//	Linien-Tabelle
TableInfo LineTable [] = 
{
	{ 0,			SetEntityElemTable	},
	{ 8,			GetLayerName 		},
	{ 10, 			CreateCoordX		},
	{ 11,			CreateCoordX		},
	{ 20, 			CreateCoordY		},
	{ 21, 			CreateCoordY		},
	{ 30, 			CreateCoordZ		},
	{ 31, 			CreateCoordZ		},
	{ 999,			GetComment			},
	{ IGNORE_REC, 	NULL 				},
};

//	PolyLinien-Table
TableInfo PolyLineTable [] = 
{
	{ 0,			SetEntityElemTable	},
	{ 8,			GetLayerName 		},
	{ 70,			CreateFlag0			},
	{ 999,			GetComment			},
	{ IGNORE_REC, 	NULL 				},
};

//	LWPolyLinien-Table
TableInfo LWPolyLineTable [] = 
{
	{ 0,			SetEntityElemTable	},
	{ 8,			GetLayerName 		},
	{ 10, 			CreateCoordX		},
	{ 20, 			CreateCoordY		},
	{ 70,			CreateFlag0			},
	{ 90,			GetVertexCount		},
	{ 999,			GetComment			},
	{ IGNORE_REC, 	NULL 				},
};

//	Point-Table
TableInfo PointTable [] = 
{
	{ 0,			SetEntityElemTable	},
	{ 8,			GetLayerName 		},
	{ 10, 			CreateCoordX		},
	{ 20, 			CreateCoordY		},
	{ 30, 			CreateCoordZ		},
	{ 999,			GetComment			},
	{ IGNORE_REC, 	NULL 				},
};

//	Vertex-Table
TableInfo VertexTable [] = 
{
	{ 0,			SetEntityElemTable	},
	{ 8,			GetLayerName 		},
	{ 10, 			CreateCoordX		},
	{ 20, 			CreateCoordY		},
	{ 30, 			CreateCoordZ		},
	{ 42,			CreateFloat2		},
	{ 70,			CreateFlag0		    },
	{ IGNORE_REC, 	NULL 				},
};

//	Solid-Table
TableInfo SolidTable [] = 
{
	{ 0,			SetEntityElemTable	},
	{ 8,			GetLayerName 		},
	{ 10, 			CreateCoordX		},
	{ 11,			CreateCoordX		},
	{ 12, 			CreateCoordX		},
	{ 13, 			CreateCoordX		},
	{ 20, 			CreateCoordY		},
	{ 21, 			CreateCoordY		},
	{ 22, 			CreateCoordY		},
	{ 23, 			CreateCoordY		},
	{ 30, 			CreateCoordZ		},
	{ 31, 			CreateCoordZ		},
	{ 32, 			CreateCoordZ		},
	{ 33, 			CreateCoordZ		},
	{ 999,			GetComment			},
	{ IGNORE_REC, 	NULL 				},
};

//	Circle-Table
TableInfo CircleTable [] = 
{
	{ 0,			SetEntityElemTable	},
	{ 8,			GetLayerName 		},
	{ 10, 			CreateCoordX		},
	{ 20, 			CreateCoordY		},
	{ 30, 			CreateCoordZ		},
	{ 40,			CreateFloat			},
	{ 999,			GetComment			},
	{ IGNORE_REC, 	NULL 				},
};

//	Arc-Table
TableInfo ArcTable [] = 
{
	{ 0,			SetEntityElemTable	},
	{ 8,			GetLayerName 		},
	{ 10, 			CreateCoordX		},
	{ 20, 			CreateCoordY		},
	{ 30, 			CreateCoordZ		},
	{ 40,			CreateFloat			},
	{ 50,			CreateWinkel0		},
	{ 51,			CreateWinkel1		},
	{ 999,			GetComment			},
	{ IGNORE_REC, 	NULL 				},
};

TableInfo SeqendTable [] = 
{
	{ 0,			SetEntityElemTable	},
	{ 8,			GetLayerName 		},
	{ IGNORE_REC, 	NULL 				},
};

//	Textelement-Table
TableInfo TextElemTable [] = 
{
	{ 0,			SetEntityElemTable	},
	{ 1,			GetText				},
	{ 8,			GetLayerName 		},
	{ 10, 			CreateCoordX		},
	{ 20, 			CreateCoordY		},
	{ 30, 			CreateCoordZ		},
	{ 40,			GetTextHoehe		},
	{ 50,			CreateWinkel0		},
	{ 999,			GetComment			},
	{ IGNORE_REC, 	NULL 				},
};

//	Insert-Table
TableInfo InsertTable [] = 
{
	{ 0,			SetEntityElemTable	},
	{ 2,			GetName				},
	{ 8,			GetLayerName 		},
	{ 10, 			CreateCoordX		},
	{ 20, 			CreateCoordY		},
	{ 30, 			CreateCoordZ		},
	{ 41,			CreateFloat1		},
	{ 42,			CreateFloat2		},
	{ 44,			CreateFloat4		},
	{ 45,			CreateFloat5		},
	{ 50,			CreateWinkel0		},
	{ 70,			CreateFlag0			},	
	{ 71,			CreateFlag1			},
	{ IGNORE_REC, 	NULL 				},
};

//	Shape-Table
TableInfo ShapeTable [] = 
{
	{ 0,			SetEntityElemTable	},
	{ 2,			GetName				},
	{ 8,			GetLayerName 		},
	{ 10, 			CreateCoordX		},
	{ 20, 			CreateCoordY		},
	{ 30, 			CreateCoordZ		},
	{ IGNORE_REC, 	NULL 				},
};

//	Attrib-Table
TableInfo AttribTable [] = 
{
	{ 0,			SetEntityElemTable	},
	{ 1,			GetText				},
	{ 2,			GetName				},
	{ 8,			GetLayerName 		},
	{ 10, 			CreateCoordX		},
	{ 20, 			CreateCoordY		},
	{ 30, 			CreateCoordZ		},
	{ IGNORE_REC, 	NULL 				},
};

ExtKeyList EntityElemList [] =
{
	{ "BLOCK",		BLOCK,		BlockTable		},
	{ "LINE",		LINE, 		LineTable		},
	{ "POLYLINE",	POLY_LINE,	PolyLineTable	},
	{ "LWPOLYLINE",	LWPOLY_LINE,	LWPolyLineTable	},
	{ "VERTEX",		VERTEX,		VertexTable		},
	{ "SEQEND",		SEQEND,		SeqendTable 	},
	{ "CIRCLE",		CIRCLE,		CircleTable		},
	{ "ARC",		ARC,		ArcTable		},
	{ "TEXT",		TEXT_ELEM,	TextElemTable	},	
	{ "POINT",		POINT,		PointTable		},		
	{ "INSERT",		INSERT,		InsertTable		},
	{ "TRACE",		TRACE_ELEM,	SolidTable		},		// g�ltige Token sind identisch !
	{ "SOLID",		SOLID,		SolidTable		},
	{ "SHAPE",		SHAPE,		ShapeTable		},	
	{ "3DFACE",		SOLID,		SolidTable		},		// g�ltige Token sind identisch ! wird wie Solid behandelt
	{ "3DLINE",		LINE,		LineTable		},		// g�ltige Token sind identisch ! ab Version 12 nicht vorh. --> wird wie Line beh.
	{ "ATTRIB",		ATTRIB,		AttribTable		},		
	{ "ENDBLK",		ENDBLK,		EntityTable		},
	{ "ENDSEC", 	END_SECT,	FileTable		},
	{ NULL,			IGNORE_REC, EntityTable		},		// unbekannte Entities	
};														// sicher filtern !			

ExtKeyList SectionTable [] =
{
	{ "ENTITIES", 	ENTITIES,	EntityTable },		// diese Section werden 
	{ "HEADER", 	HEADER,		HeaderTable },		// interpretiert,
	{ "BLOCKS",		BLOCKS,		EntityTable	},		
	{ "TABLES",		TABLES,		EndSecTable	},		// unbekannte Section 
	{ NULL,			IGNORE_REC, EndSecTable	},		// sicher filtern !
};													

// 	Schl�sselwortlisten
KeyList AnfList [] =
{
	{ "SECTION", 	SECTION			},
	{ "ENDSEC", 	END_SECT		},
	{ "EOF", 		END_OF_FILE		},
	{ NULL,			IGNORE_REC		},
}; 

// weitere Variablen
long lLineNr = 0;							// Zeilen-Nummer
TableInfo* pActTable = &FileTable [0];		// Zeiger auf File-Table
char LexBuffer [LexBufferSize] = "";		// eine AutoCAD-Zeile hat max. 256 Zeichen

// Prototypen der Schl�ssel/Suchfunktionen:	
// lese bis zum akt. Zeilende u. die dann folgende Zeile
// Zeilenz�hler entspr. erh�hen
BOOL ReadNextLine (char *Buffer = LexBuffer, short sLen = sizeof (LexBuffer) - 1);

// lese den akt. Record
short ReadRecord (short sRecHeader, pTableInfo = pActTable);
%}

/* expression */
sign        [+-]
dezimal     [0-9]
integer     ({sign}?{dezimal}+)
real        ({integer}"."{dezimal}+)
realexp     ({real}"E"{integer})
nl          \n

%%
[ \t]+		;
{nl}        {	lLineNr++; }

{integer}   { 	short sRet = ReadRecord (atoi (yytext)); 
				if (sRet != IGNORE_REC)
					return sRet;
			}
%%

// lese bis zum akt. Zeilende u. die dann folgende Zeile
// Zeilenz�hler entspr. erh�hen
BOOL ReadNextLine (char* Buffer, short Max) 
{							
	register short i = 0, ch = 0;
    
	while (!Error && input () != '\n');			// akt. Zeilende lesen
	if (Error)
		return FALSE;
    lLineNr++;   

//	ggf. nur einlesen u. nicht kopieren
	if (!Buffer)
	{
		while (!Error && input () != '\n');		// akt. Zeilende lesen
		if (Error)
			return FALSE;
		lLineNr++;   
		return TRUE;
	}
		
    while (!Error && (i < Max) &&         		//  maximal Puffergr. lesen 
	  	  ((ch = input ()) != '\n')) 
	{
	  Buffer [i] = (char) ch;
	  i++;
    }
    Buffer [i] = '\0';  				// Textende setzen 
	lLineNr++;							// Zeilenz�hler erh�hen

	return Error ? FALSE : TRUE;	
}

// lese akt. Satz
short ReadRecord (short sRecHead, pTableInfo pInfo)
{
	if (! pInfo)		// das sollte nicht passieren
	{
		yyerror (IDS_SYSERROR);
		return LEX_ERROR;
	}

//	suche Tabellen-Eintrag
	while ((pInfo -> sRecVar != IGNORE_REC) && (pInfo -> sRecVar != sRecHead))
		pInfo++;

	HandleValFct pFct = pInfo -> pHandleValFct;
	if (pFct)
	{
		if (!Error && ReadNextLine (LexBuffer))
			return pFct (LexBuffer);
		else
			return LEX_ERROR;
	}
	else
	{
		ReadNextLine (NULL, 0);	// Zeile nur lesen	
		return IGNORE_REC;		// Satz wurde nicht gefunden
	}	
}

// suche best. Token in �bergebener Liste	
short FindToken (char *pToken, pKeyList pKL)
{
//	pr�fe Parameter
	if (!pToken || !pKL)
	{
		yyerror (IDS_SYSERROR);
		return LEX_ERROR;
	}

//	Token suchen
	while (pKL -> pKeyWord)
	{
		if (strcmp (pKL -> pKeyWord, pToken) == 0)
			return pKL -> sRetVal;
		pKL++;			 
	} 	

	return IGNORE_REC;
}

//	finde Anfangs-Token
short FindAnf (char *pToken) 
{
	return FindToken (pToken, &AnfList [0]);
}

//	warte auf ENDSEC-Token
short FindEndSec (char *pToken)
{
	if (!pToken)
	{
		yyerror (IDS_SYSERROR);
		return LEX_ERROR;
	}	

//	Token gefunden
	if (strcmp (pToken, "ENDSEC") == 0)
	{
		pActTable = &FileTable [0];		// jetzt sollte eine neue 
		return END_SECT;				// Section oder EOF folgen
	}

	return IGNORE_REC;
}

// 	erzeuge Koordinate 
short CreateCoord (char *pKoordText)
{
//	pr�fe Parameter
	if (!pKoordText)
	{
		yyerror (IDS_SYSERROR);
		return LEX_ERROR;
	}

	yylval.real = atof (pKoordText);
	
	return KOORD;	
}

//	erzeuge X-Koordinate
short CreateCoordX (char *pVal)
{
	return CreateCoord (pVal) == KOORD ? KOORD_X : LEX_ERROR;	
}

//	erzeuge Y-Koordinate
short CreateCoordY (char *pVal)
{
	return CreateCoord (pVal) == KOORD ? KOORD_Y : LEX_ERROR;	
}

//	erzeuge Z-Koordinate
short CreateCoordZ (char *pVal)
{
	return CreateCoord (pVal) == KOORD ? KOORD_Z : LEX_ERROR;	
}

// erzeuge Float-Value
short CreateFloat (char *pVal)
{
	return CreateCoord (pVal) == KOORD ? FLOAT : LEX_ERROR;
}

// erzeuge Float1-Value
short CreateFloat1 (char *pVal)
{
	return CreateCoord (pVal) == KOORD ? FLOAT1 : LEX_ERROR;
}

// erzeuge Float2-Value
short CreateFloat2 (char *pVal)
{
	return CreateCoord (pVal) == KOORD ? FLOAT2 : LEX_ERROR;
}

// erzeuge Float4-Value
short CreateFloat4 (char *pVal)
{
	return CreateCoord (pVal) == KOORD ? FLOAT4 : LEX_ERROR;
}

// erzeuge Float5-Value
short CreateFloat5 (char *pVal)
{
	return CreateCoord (pVal) == KOORD ? FLOAT5 : LEX_ERROR;
}

// erzeuge Flag0-Value
short CreateFlag0 (char *pVal)
{
//	pr�fe Parameter
	if (!pVal)
	{
		yyerror (IDS_SYSERROR);
		return LEX_ERROR;
	}

	yylval.integer = atoi (pVal);
	return FLAG0;	
}

// erzeuge Flag1-Value
short CreateFlag1 (char *pVal)
{
//	pr�fe Parameter
	if (!pVal)
	{
		yyerror (IDS_SYSERROR);
		return LEX_ERROR;
	}

	yylval.integer = atoi (pVal);
	return FLAG1;	
}

//	erzeuge Winel "0"
short CreateWinkel0 (char *pVal)
{
	return CreateCoord (pVal) == KOORD ? WINKEL0 : LEX_ERROR;
}

//	erzeuge Winel "1"
short CreateWinkel1 (char *pVal)
{
	return CreateCoord (pVal) == KOORD ? WINKEL1 : LEX_ERROR;
}

//	lese und kopiere Text
short GetText (char *pText)
{
//	pr�fe Parameter
	if (!pText)
	{
		yyerror (IDS_SYSERROR);
		return LEX_ERROR;
	}

	char *pT = new char [strlen (pText) + 1];
	if (pT)
	{
		strcpy (pT, pText);
		yylval.str_ptr = pT;				// Zeiger speichern
	}
	else
	{
		yylval.str_ptr = NULL;
		yyerror (IDS_NOMEMORY);
		return LEX_ERROR;
	}

	return TEXT0;
}

// lese Layername 
short GetLayerName (char *pText)
{
	return GetText(pText) == TEXT0 ? LAYER_NAME : LEX_ERROR;	
}

// lese VertexCOunt 
short GetVertexCount (char *pVal)
{
//	pr�fe Parameter
	if (!pVal)
	{
		yyerror (IDS_SYSERROR);
		return LEX_ERROR;
	}
	yylval.integer = atoi (pVal);
	return VERTEX_COUNT;
}

// lese Name
short GetName (char *pText)
{
	return GetText (pText) == TEXT0 ? NAME : LEX_ERROR;	
}

//	setze neue Tabelle
short SetTable (char *pToken, pExtKeyList pList)
{
//	pr�fe Parameter
	if (!pToken || !pList)
	{
		yyerror (IDS_SYSERROR);
		return LEX_ERROR;
	}

//	Token suchen
	while (pList -> pKeyWord)
	{
		if (strcmp (pList -> pKeyWord, pToken) == 0)
		{
			pActTable = pList -> pTI;	// akt. Tabelle setzen
			return pList -> sRetVal;
		}
		pList++;			 
	} 	
	
//	ggf. default-Tabelle einstellen
	if (pList -> pTI)
		pActTable = pList -> pTI;		// default setzen		

	return pList -> sRetVal;		
}

// aktviere Section-Table
short SetSectionTable (char *pToken) 
{
	return SetTable (pToken, &SectionTable [0]);
}

//	Header-Elemente-Tabelle aktivieren
short SetHeaderElemTable (char *pToken)
{
	return SetTable (pToken, &HeaderElemTable [0]);
}

//	aktiviere Elemente-Tabelle
short SetEntityElemTable (char *pToken)
{
	return SetTable (pToken, &EntityElemList [0]);
}

// Lex init
void yyinit_lex (void)
{
	yy_init = 1;
}

///////////////////////////////////////////////////////////////////////////////
//	lese und kopiere Text
short GetWinkel (char *pText)
{
//	pr�fe Parameter
	if (!pText)
	{
		yyerror (IDS_SYSERROR);
		return LEX_ERROR;
	}

	char *pT = new char [strlen (pText) + 1];
	if (pT)
	{
		strcpy (pT, pText);
		yylval.str_ptr = pT;				// Zeiger speichern
	}
	else
	{
		yylval.str_ptr = NULL;
		yyerror (IDS_NOMEMORY);
		return LEX_ERROR;
	}

	return WINKEL;
}

short GetTextHoehe (char *pText)
{
//	pr�fe Parameter
	if (!pText)
	{
		yyerror (IDS_SYSERROR);
		return LEX_ERROR;
	}

	char *pT = new char [strlen (pText) + 1];
	if (pT)
	{
		strcpy (pT, pText);
		yylval.str_ptr = pT;				// Zeiger speichern
	}
	else
	{
		yylval.str_ptr = NULL;
		yyerror (IDS_NOMEMORY);
		return LEX_ERROR;
	}

	return TEXT_HOEHE;
}

short GetComment (char *pVal)
{
//	pr�fe Parameter
	if (!pVal)
	{
		yyerror (IDS_SYSERROR);
		return LEX_ERROR;
	}

//	Kommentar ggf. einlesen
	if (*pVal)
		strcpy (CommentBuffer, pVal);
	else
		CommentBuffer [0] = '\0';

	return IGNORE_REC;
}

