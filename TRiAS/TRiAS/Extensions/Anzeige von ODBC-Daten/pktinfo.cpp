/*
DATEI: PKTINFO.CPP

Der Container verwaltet Objekt-Informationen von vorgegebenen Objektklassen.

Erarbeitet: J. Benkenstein					Stand vom: 17.1.1996
*/

#include "pheader.h"		// vorübersetzter Header
#include "odbcext.hr"	

#include <hpp/getodbci.hpp>		// COdbcInfos
#include "importpa.hpp"		// CImportParams
#ifndef WIN32
#include <progress.hpp>				// CProgressCtrl
#endif                                               
#include "pktinfo.hpp"		// zugeh. Header

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//	Konstanten
const short sMaxMerkmalSize = 256;		// max. Größe eines Textmerkmals
const short sMaxValSize = 30;			// max. Koord-Größe

// externe Variablen
extern CPunktInfoTree *g_pCPunktInfoTree;  
extern CImportParams *g_pCParams;
extern CStdioFile *g_pFile;				// Protokoll-Datei

// globale Funktionen ---------------------------------------------------------
void* __export GetPunktInfo (void *pObj)
{
	return (void *) (const char *)(((CPunktInfo *) pObj) -> m_strMerkmal);
}

BOOL __export PASCAL EnumObjektMerkmale (long lObjNr, DWORD dwData, void *pData)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	TRY
	{
		CString strBuffer;
		TARGETMERKMAL tm;
		memset (&tm, 0, sizeof (tm));		// init.
		tm.dwSize = sizeof (tm);			// Größe der Struktur
		tm.lTarget = (LPARAM) lObjNr;		// Objektnummer
		tm.lMCode = *(long *) pData;		// Merkmalskode
		tm.iTTyp = TT_Objekt;				// Objektmerkmal
		tm.imaxLen = sMaxMerkmalSize;		// max. Größe setzen
		tm.pMText = strBuffer.GetBuffer (sMaxMerkmalSize);	// Puffer setzen

	//	Merkmal lesen: auch die mit leerem Inhalt, um sie ggf. zu löschen
		DEX_GetTextMerkmal (tm);		

	//	Geometrie lesen
		double dKoordX, dKoordY;
		dKoordX = dKoordY = 0.0;
		OBJGEOMETRIE og;
		memset (&og, 0, sizeof (og));			// init.
		og.dwSize = sizeof (og);				// Größe der Struktur
		og.lONr = lObjNr;						// ObjektNummer
		og.pdblX = &dKoordX;
		og.pdblY = &dKoordY;
		og.iObjTyp = OGPunkt;
		og.lCnt = 1;							// 1 Koordinate
		og.iFlags = (short) (OGConverted |		// double Koordinaten
							 OGIgnoreIdent);	// Id ignorieren

		if (!DEX_GetObjGeometrie (og))
		{
			DEX_Error (RC_OdbcImport, EC_BadGeometrie);
			AfxThrowUserException ();
		}

	//	Merkmal ggf. speichern
		ASSERT (g_pCPunktInfoTree != NULL);
		return g_pCPunktInfoTree -> StoreObjektInfo (lObjNr, dKoordX, dKoordY, tm.pMText);
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
	}
	AND_CATCH (CUserException, ue)
	{
	}		
	END_CATCH

	return FALSE;
}

//	CPunktInfo ----------------------------------------------------------------
CPunktInfo :: CPunktInfo (long lObjNr, const char *pMerkmal, double X, double Y,
						  short sIsModified)
{
	TRY
	{
		m_lObjNr = lObjNr;
		m_strMerkmal = pMerkmal;
		m_sIsModified = sIsModified;
		m_dX = X;
		m_dY = Y;
	}
	CATCH (CMemoryException, me)
	{
		THROW_LAST ();
	}
	END_CATCH
}

// CPunktInfoTree -----------------------------------------------------------
CPunktInfoTree :: CPunktInfoTree (BOOL bDeleteDoppelte)
				: CTree (GetPunktInfo)
{
	m_bDelDopp = bDeleteDoppelte;		// doppelt vorhandene Objekte löschen
}

CPunktInfoTree :: ~ CPunktInfoTree (void)
{
	EveryDelete ();
}

void __export CPunktInfoTree :: UserDelete (void *pObj)
{
	((CPunktInfo *) pObj) -> ~CPunktInfo ();	
}

//	speichern der für die angegebenen Objektklassen zugeh. CPunktInfo
BOOL CPunktInfoTree :: GetPunktInfos (ulong *pulObjKl, ulong ulMK)
{
//	prüfe Parameter
	ASSERT (pulObjKl != NULL);
	ASSERT (ulMK > 0 && *pulObjKl > 0);

//	alten Infos löschen
	EveryDelete ();

//	Schlüssel init.
	ENUMLONGKEYEX key;
	memset (&key, 0, sizeof (key));		// init.
	key.eFcn = (ENUMLONGKEYEXPROC) EnumObjektMerkmale;		// Enum-Funktion
	key.eData = OTPunkt;				// nur Punktinfos abgl.
	key.ePtr = (void *) &ulMK;			// Merkmalskode bleibt konstant

//	enum. alle Punkt-Objekte
	for (; *pulObjKl; pulObjKl++)
	{
		key.eKey = *pulObjKl;			// akt. ID setzen
		if (!DEX_EnumIdentObjectsEx (key))
			AfxThrowUserException ();
	}

	return TRUE;
}

//	neue ObjektInfo speichern
BOOL CPunktInfoTree :: StoreObjektInfo (long lObjNr, double X, double Y,
										const char *pMerkmal, short sIsMod)
{
//	prüfe Parameter
	ASSERT (lObjNr > 0);
	ASSERT (pMerkmal != NULL && AfxIsValidString (pMerkmal));
	ASSERT (g_pCParams != NULL);

	TRY
	{
		if (!*pMerkmal)
		{
		//	ggf. Objekt löschen
			if (m_bDelDopp && DEX_DeleteObject (lObjNr))
			{
				g_pCParams -> m_lDelCnt++;		// auch diesen Zähler erhöhen
				OutputError (IDS_ERR_EMPTY_MERKMAL, lObjNr, (long)X, (long)Y, "");				
			}
			return TRUE;
		}

		CTable tb(*this);
		if (tb.Find ((void *)pMerkmal))
		{
		//	TRIAS-doppelte mitzählen
			g_pCParams -> m_lDoppTriasCnt++;		

		//	Fehlermeldung ausgeben
			OutputError (IDS_ERR_DOPP_PUNKT, lObjNr, (long)X, (long)Y, pMerkmal);

		//	ggf. Objekt löschen
			if (m_bDelDopp && DEX_DeleteObject (lObjNr))
			{
				g_pCParams -> m_lDelCnt++;		// auch diesen Zähler erhöhen
				OutputError (IDS_ERR_DOPP_DEL, lObjNr, (long)X, (long)Y, pMerkmal);				
			}
			return TRUE;
		}
	
	//	Objekt speichern
		CPunktInfoCreator Cr (*this);  
		return ContCreate (Cr, CPunktInfo) (lObjNr, pMerkmal, (long)X, (long)Y, sIsMod) ? TRUE : FALSE;
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
	}
	AND_CATCH (CFileException, fe)
	{
		// DEX_Error (RC_OdbcImport, EC_NOSPACE);
		fe -> ReportError ();
	}
	AND_CATCH (CUserException, ue)
	{
		DEX_Error (RC_OdbcImport, EC_SYSERROR);
	}
	END_CATCH

	return FALSE;
}

//	nicht referenzierte Objekte löschen
BOOL CPunktInfoTree :: DeleteNotRefObj (CProgressCtrl &stProgress, CStatic &stInfo,
										void (*pWasInterrupted) (void))
{
	ASSERT (pWasInterrupted != NULL);

	TRY
	{
	//	Status-Info ausgeben
		CString strInfo;
		if (!strInfo.LoadString (IDS_IMP_DEL_NOTEXIST))
			AfxThrowResourceException ();
		stInfo.SetWindowText (strInfo);	

	//	Progress-Controll init.
		stProgress.SetRange (0, (int)Count ());
		stProgress.SetPos (0);
		
	//	Zähler akt.
		long lActCnt = 1;

		CTable tb (*this);
		for (tb.First (); tb.Valid (); tb.Next (), lActCnt++)
		{
		//	Abbruch ?
			pWasInterrupted ();			// Abbruch mit Exception 
			
			stProgress.SetPos ((int)lActCnt);	// Progress akt.

			CPunktInfoLock pL (tb);		
			if (! pL)						// interner Fehler
				AfxThrowUserException ();
			else
			{//	wenn Objekt nicht modifiziert wurde --> löschen
				if ((pL -> m_sIsModified == NotModified) &&
					 DEX_DeleteObject (pL -> m_lObjNr))
				{
					g_pCParams -> m_lDelCnt++;
					pL -> m_sIsModified = IsDeleted;		// Löschflag setzen
					OutputError (IDS_ERR_NREF_DEL, pL -> m_lObjNr, 
								 (long)pL -> m_dX, (long)pL -> m_dY, pL -> m_strMerkmal);				
				}
			}
		}
		return TRUE;
	}
	CATCH (CUserException, ue)
	{
		DEX_Error (RC_OdbcImport, EC_LOCKERROR);
	}
	AND_CATCH (CResourceException, re)
	{
		DEX_Error (RC_OdbcImport, EC_NORESOURCE);
	}
	AND_CATCH_ALL (e)
	{
		THROW_LAST ();		// nur weitereichen: z.B. Abbruch
	}
	END_CATCH_ALL

	return FALSE;
}

//	Fehlermeldung ausgeben
void CPunktInfoTree :: OutputError (uint uiResID, long lObjNr, 
								    long X, long Y, const char*pMerkmal)
{
	ASSERT (lObjNr > 0);
	ASSERT (pMerkmal != NULL && AfxIsValidString (pMerkmal));
	ASSERT (g_pFile != NULL);

	CString strError, strFormat;
	if (!strFormat.LoadString (uiResID))
		AfxThrowResourceException ();
	char *pBuffer = strError.GetBuffer (strFormat.GetLength () +
									    strlen (pMerkmal) + (3 * sMaxValSize));
	if (*pMerkmal)
		wsprintf (pBuffer, strFormat, lObjNr, pMerkmal, X, Y);
	else
		wsprintf (pBuffer, strFormat, lObjNr, X, Y);
	g_pFile -> WriteString (pBuffer);
}

//	SatzInfo speichern
BOOL CPunktInfoTree :: StoreRecordInfo (long lObjNr, const char *pMerkmal,
										double dX, double dY, short sMod)
{
	ASSERT (lObjNr > 0);
	ASSERT (pMerkmal != NULL && AfxIsValidString (pMerkmal));

	CPunktInfoCreator Cr (*this);  
	return ContCreate (Cr, CPunktInfo) (lObjNr, pMerkmal, dX, dY, sMod) ? TRUE : FALSE;
}	

