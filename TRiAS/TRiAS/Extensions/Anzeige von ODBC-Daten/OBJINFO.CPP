/*
        Die Klasse beinhaltet Infos für TRiAS-Enum-Funtkionen.

        Erarbeitet: J. Benkenstein                      Stand vom: 30.11.95
*/

#include "pheader.h"

#include <errinstx.hxx> // ErrInstall
#include <hpp/objinfo.hpp>		// zugeh. Header

// externe Variablen
extern int g_sMkBase;						// und Merkmale

//	KurzText zu einem Id oder Merkmal lesen
char* __export GetKurzText (ulong ulKode, short sType, char *pBuffer, short sBufferSize)
{
//	prüfe Parameter
	ASSERT (ulKode > 0);
	ASSERT (sType == 'i' || sType == 'm');
	ASSERT (pBuffer != NULL && sBufferSize > 0);

PBDDATA pbdData;						// PBD-Struktur

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = sType;
	pbdData.pbdCode = ulKode;
	pbdData.pbdKText = pBuffer;
	pbdData.pbdKTextLen = sBufferSize;

//	keine Fehlermeldung durch TRIAS
ErrInstall E1 (sType == 'i' ? WC_NOIDENT : WC_NOMERKMAL);

	return DEX_GetPBDData (pbdData) == EC_OKAY ? pBuffer : NULL;
}

// ListBox mit allen Identifikatoren/Merkmalen der PBD füllen
BOOL __export FAR PASCAL FillObjMerkmalList (ulong Ident, BOOL, void* pData)
{                 

	ObjMerkmalInfo *pInfo = (ObjMerkmalInfo *) pData;
	if ( 'i' != pInfo -> m_lType ) 
		return TRUE;


	char KText[KurzTextLen] = "";

	ErrInstall E1 ( WC_NOIDENT );
	char outBuff[KurzTextLen + 20] = "";

	ErrCode EC;

	PBDDATA pbdData;            
	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = (short) pInfo -> m_lType;
	pbdData.pbdCode = Ident;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = KurzTextLen - 1;
	EC = DEX_GetPBDData (pbdData);

	if ( EC != EC_OKAY && EC != WC_RETURN)
		return TRUE;

	if (FAILED(ClassFromIdentX (Ident, outBuff, sizeof(outBuff))) || (!*outBuff))
		return FALSE;

	strcat (outBuff, ":");
	strcat (outBuff, pbdData.pbdKText);

	// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen 
	// in Klammern hintendran hängen
	if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
		HPROJECT hPr = DEX_GetObjectsProject(Ident);

		ASSERT(NULL != hPr);
		if (NULL != DEX_GetDataSourceShortName (hPr, KText)) {
			strcat (outBuff, " (");
			strcat (outBuff, KText);
			strcat (outBuff, ")");
		}
	}


	if (pInfo -> m_pCComboBox) {
		int iIndex = pInfo -> m_pCComboBox -> AddString (outBuff);

		if (CB_ERR != iIndex)
			pInfo -> m_pCComboBox -> SetItemData (iIndex, Ident);
		return (CB_ERR != iIndex) ? TRUE : FALSE;
	}

	if (pInfo -> m_pCListBox) {
		int iIndex = pInfo -> m_pCListBox -> AddString (outBuff);
	
		if (CB_ERR != iIndex)
			pInfo -> m_pCListBox -> SetItemData (iIndex, Ident);
		return (iIndex != LB_ERR) ? TRUE : FALSE;	 
	}

	ASSERT(NULL != pInfo -> m_pCComboBox || NULL != pInfo -> m_pCListBox);
	return FALSE;	
}

//---------------------------------------------------------------------------------
// ListBox mit allen Merkmalen des ID füllen
BOOL __export FAR PASCAL FillObjFeatureList (ulong Ident, DWORD dw, void* pData)
{                 

	ObjMerkmalInfo *pInfo = (ObjMerkmalInfo *) pData;
	if ( 'm' != pInfo -> m_lType)
		return TRUE;
	if ( 0 == pInfo -> m_lIdent)
		return TRUE;

	if (dw & MPSystemFeatures)
		return TRUE;

	char KText[KurzTextLen] = "";

	ErrInstall E1 ( WC_NOMERKMAL);
	char outBuff[KurzTextLen + 20] = "";

	ErrCode EC;

	PBDMERKMALEX pbdData;            
	INITSTRUCT(pbdData, PBDMERKMALEX);
	pbdData.pbdTyp = (short) pInfo -> m_lType;
	pbdData.pbdCode = Ident;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = KurzTextLen - 1;
	pbdData.lIdent = pInfo -> m_lIdent;
	HPROJECT hPr = DEX_GetObjectsProject(pInfo -> m_lIdent);
	EC = DEX_GetPBDDataEx (hPr,pbdData);

	if ( EC != EC_OKAY ) // Nur definierte OE !!
		return TRUE;

	// Merkmal
	ASSERT('m' == pbdData.pbdTyp);
	if ( pbdData.ipbdMTyp != 'a' )					// nur ObjectFeature
		return TRUE;	// KK000411

	if ( 0 == strncmp (pbdData.pbdKText,"__",2))	// HK - intern : alle OE mit __ raus
		return TRUE;	// KK000411

// KK000427 - mappen der MCodes !!!
long lMIdent = DEX_MapHandleToMCode(Ident);

	if (pInfo -> m_pCComboBox) {
	int iIndex = pInfo -> m_pCComboBox -> AddString (pbdData.pbdKText);

		if (CB_ERR != iIndex) {
			pInfo -> m_pCComboBox -> SetItemData(iIndex, lMIdent);
			return TRUE;
		}
		return FALSE;
	}

//	if (pInfo -> m_pCListBox) {
//		if (g_sMkBase == 10)    
//			wsprintf (outBuff, "%08ld:%s", lMIdent, pbdData.pbdKText);
//		else
//			wsprintf (outBuff, "%08lx:%s", lMIdent, pbdData.pbdKText);
//
//	int iIndex = pInfo -> m_pCListBox -> AddString (outBuff);
//	
//		return (iIndex != LB_ERR) ? TRUE : FALSE;	 
//	}

	ASSERT(NULL != pInfo -> m_pCComboBox/* || NULL != pInfo -> m_pCListBox*/);
	return FALSE;	
}

//---------------------------------------------------------------------------------
#ifdef WIN32
// CListCtrl mit allen Identifikatoren/Merkmalen der PBD füllen
BOOL __export FAR PASCAL FillObjMerkmalListView (ulong ulKode, BOOL, void* pData)
{                 
ObjMerkmalInfo *pInfo = (ObjMerkmalInfo *) pData;
PBDDATA pbdData;            
char KText [KurzTextLen] = "";

//	ASSERT(pInfo -> m_lType == 'i');

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = ulKode;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = KurzTextLen - 1;

ErrInstall E1 (/*WC_NOIDENT*/pInfo -> m_lType == 'i' ? WC_NOIDENT : WC_NOMERKMAL);
char outBuff [KurzTextLen + 20] = "";
	DEX_GetPBDData (pbdData);
    if (pbdData.pbdTyp == 'i')
    {
		if (FAILED(ClassFromIdentX (ulKode, outBuff, sizeof(outBuff))) || (!*outBuff))
			return FALSE;
    }
    else
    {//     Merkmal       
            if (g_sMkBase == 10)
                    wsprintf (outBuff, "%08ld", ulKode);
            else
                    wsprintf (outBuff, "%08lx", ulKode);
    }

CObjektInfo *pOjektInfo = NULL;

	TRY {
	//	wenn Zeiger auf Control vorhanden
		if (pInfo -> m_pCListCtrl) {
			if (pInfo -> m_pCListCtrl -> InsertItem (pInfo -> m_iIndex, pbdData.pbdKText) != pInfo -> m_iIndex)
				AfxThrowUserException ();

			pOjektInfo = new CObjektInfo;
			pOjektInfo -> m_ulKode = ulKode;
			pOjektInfo -> m_strDescr = pbdData.pbdKText;
			if (! pInfo -> m_pCListCtrl ->  SetItemData (pInfo -> m_iIndex, (DWORD) pOjektInfo))
				AfxThrowUserException ();
			pInfo -> m_iMaxFirstLen = max (pInfo -> m_iMaxFirstLen, lstrlen (pbdData.pbdKText)); 		
			
			if (!pInfo -> m_pCListCtrl -> SetItemText (pInfo -> m_iIndex, 1, outBuff)) 
				AfxThrowUserException ();
			pInfo -> m_iMaxSecLen = max (pInfo -> m_iMaxSecLen, lstrlen (outBuff));	// max. Länge setzen

			if ('i' == pbdData.pbdTyp && DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
			HPROJECT hPr = DEX_GetObjectsProject(ulKode);

				ASSERT(NULL != hPr);
				if (NULL != DEX_GetDataSourceShortName (hPr, outBuff)) {
					if (!pInfo -> m_pCListCtrl -> SetItemText (pInfo -> m_iIndex, 2, outBuff)) 
						AfxThrowUserException ();
				}					
			}

			pInfo -> m_iIndex++;	// ZeilenIndex weiter setzen	
			return TRUE;			// alles OK
		}

	} CATCH (CMemoryException, me) {
		DEX_Error (RC_CommonODBC, EC_NOMEMORY);
	} AND_CATCH (CUserException, me) {
		DEX_Error (RC_CommonODBC, EC_SYSERROR);
	} END_CATCH

//	Speicher ggf. freigeben
	DELETE_OBJ (pOjektInfo);		

	return FALSE;	
}
#endif
