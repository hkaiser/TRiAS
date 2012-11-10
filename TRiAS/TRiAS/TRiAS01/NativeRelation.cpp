// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/26/1998 09:53:03 AM
//
// @doc
// @module NativeRelation.cpp | Relationsfunktionen für TRiAS-Objekte

#include "trias01p.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#include "resource.h"

#include <ActDB.h>
#include <ErrInst.hxx>
#include <NativeObject.h>

#include "syncdb.hxx"
#include "ConnectFilterWrappers.h"

namespace trias_nativeobject {

///////////////////////////////////////////////////////////////////////////////
// Löschen aller Relationen eines Objektes 

/*static*/ 
HRESULT CALLBACK CNativeObject::DeleteRelatedObjectsRelations (INT_PTR lONr, int iRelType, UINT_PTR dwData)
{
CDeleteRelationsCallBack *pData = reinterpret_cast<CDeleteRelationsCallBack *>(dwData);
CNativeObject Obj (pData -> m_hPr, pData -> m_lONr);

	if (!Obj) return E_UNEXPECTED;

	TX_ASSERT(pData -> m_iRelType == iRelType);		// stimmt das so ?
	return Obj.DeleteRelation (lONr, pData -> m_lRCode, iRelType);
}

/*static*/
HRESULT CALLBACK CNativeObject::DeleteRelations (INT_PTR lRCode, int iRelType, UINT_PTR dwData)
{
CDeleteRelationsCallBack *pData = reinterpret_cast<CDeleteRelationsCallBack *>(dwData);

	pData -> m_lRCode = lRCode;
#if defined(_DEBUG)
	pData -> m_iRelType = iRelType;
#endif // _DEBUG

CNativeObject Obj (pData -> m_hPr, pData -> m_lONr);

	if (!Obj) return E_UNEXPECTED;
	return Obj.EnumRelatedObjects (lRCode, DeleteRelatedObjectsRelations, dwData);
}

///////////////////////////////////////////////////////////////////////////////
// sämtliche Relationen löschen
HRESULT CNativeObject::DeleteAllRelations() 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);

	if (::LocGetDBVersion(m_hPr) < NEWDBVERSION)
		return HRESULT_FROM_ERRCODE(E_BADDIRISVERSION);

// Relationen dieses Objektes aufsammeln
CDeleteRelationsCallBack Data;

	Data.m_hPr = m_hPr;
	Data.m_lONr = m_lONr;
	return EnumRelationCodes (DeleteRelations, reinterpret_cast<UINT_PTR>(&Data));
}

///////////////////////////////////////////////////////////////////////////////
// löscht die gegebene ElementarRelation zwischen zwei Objekten 
HRESULT CNativeObject::DeleteRelation (INT_PTR lOSek, INT_PTR lRelCode, int rgRelTyp) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);

// DatenBasisVersion testen
	if (::LocGetDBVersion(m_hPr) < NEWDBVERSION)
		return HRESULT_FROM_ERRCODE(E_BADDIRISVERSION);

// Prüfen, ob Objekte existieren
	RETURN_FAILED_HRESULT(TestOBL (m_hPr, m_lONr, rgRelTyp));
	RETURN_FAILED_HRESULT(TestOBL (m_hPr, lOSek, rgRelTyp ^ (OUREL | BRELAP)));

// wenn Begleitrelation, dann gesondert behandlen
	if (BREL(rgRelTyp)) {
		if (rgRelTyp & BRELA) 
			return DeleteBegleitRelation (m_hPr, m_lONr, lOSek);
		else	
			return DeleteBegleitRelation (m_hPr, lOSek, m_lONr);	// RückRelation auflösen
	}	

// in VORKette entsprechende Sätze löschen, OBLSatz und VRTSatz korrigieren
long lRelSatz;

	if (S_OK != FindRelation (lOSek, lRelCode, rgRelTyp, &lRelSatz))
		return HRESULT_FROM_ERRCODE(W_NORELATION);

	RETURN_FAILED_HRESULT(DeleteVORSatz (m_lONr, rgRelTyp, lRelSatz));
	RETURN_FAILED_HRESULT(DeleteVORSatz (lOSek, rgRelTyp ^ OUREL, lRelSatz));

// RALSatz finden
DB_ADDR dbaRAL(m_hPr);
struct ral RALSatz;
ErrCode RC;

	dbaRAL.file_no = RAL;
	DBASSERTHR(z_keyfind (&dbaRAL, RAT, &lRelCode));
	__ReadHR(dbaRAL, RALSatz);

// VRESatz aus Kette herauslösen
	RETURN_FAILED_HRESULT(DeleteLink (m_hPr, VRE, &RALSatz.zravre, lRelSatz));
	if (0 != RALSatz.zravre) {
		__WriteHR(dbaRAL, RALSatz);
	} else {
		__DisposeHR(dbaRAL, RALSatz);
	}

// RELSatz löschen
DB_ADDR dbaREL(m_hPr);

	dbaREL.file_no = REL;
	dbaREL.rec_no = lRelSatz;
	__DisposeHR(dbaREL, rel());

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob ObjektSatz existiert und eine bestimmte Relation besitzt
/*static*/
HRESULT CNativeObject::TestOBL (HPROJECT hPr, INT_PTR lONr, int rgRMaske) 
{
// ObjektSatz einlesen
ErrInstall EI (EC_INVADDR);
DB_ADDR_OBL dbaOBL(hPr);
struct obl OBLSatz;
ErrCode RC;

	dbaOBL.rec_no = lONr;
	__ReadHR(dbaOBL, OBLSatz);	

// Testen, ob gesuchte Relation überhaupt existiert 
	if (!(OBLSatz.rmaske & rgRMaske))
		return HRESULT_FROM_ERRCODE(W_BADRELTYP);

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Herauslösen des Relationssatzes aus der VORKette 
// korrigieren der RelationsInfo im OBLSatz und VRTSatz
HRESULT CNativeObject::DeleteVORSatz (long lONr, int rgRelTyp, long lRelSatz) 
{
// ObjektSatz einlesen
DB_ADDR_OBL dbaOBL(m_hPr);
struct obl OBLSatz;
ErrCode RC;

	dbaOBL.rec_no = lONr;
	__ReadHR(dbaOBL, OBLSatz);

// zugehörigen VRTSatz lesen
DB_ADDR dbaVRT(m_hPr);
struct reltyp VRTSatz;

	dbaVRT.file_no = RELTYP;
	dbaVRT.rec_no = OBLSatz.zovor;
	__ReadHR(dbaVRT, VRTSatz);

// VORSatz aus entsprechender Kette herauslöschen
	if (HREL(rgRelTyp)) {		// gleichrangige Relation
		RETURN_FAILED_HRESULT(DeleteLink (m_hPr, VOR, &VRTSatz.zhrel, lRelSatz));
		if (0 == VRTSatz.zhrel)	{
		// letzte Relation dieses Typs wurde gelöscht
			OBLSatz.rmaske &= ~GREL;	// Maske korrigieren
			__WriteHR(dbaOBL, OBLSatz);
		}
	} else if (VRELO(rgRelTyp)) {	// Relation nach oben
		RETURN_FAILED_HRESULT(DeleteLink (m_hPr, VOR, &VRTSatz.zvrelo, lRelSatz));
		if (0 == VRTSatz.zvrelo) {
		// letzte Relation dieses Typs wurde gelöscht
			OBLSatz.rmaske &= ~OREL;
			__WriteHR(dbaOBL, OBLSatz);
		}
	} else if (VRELU(rgRelTyp)) {	// Relation nach unten
		RETURN_FAILED_HRESULT(DeleteLink (m_hPr, VOR, &VRTSatz.zvrelu, lRelSatz));
		if (0 == VRTSatz.zvrelu) {
		// letzte Relation dieses Typs wurde gelöscht
			OBLSatz.rmaske &= ~UREL;	// Maske korrigieren
			__WriteHR(dbaOBL, OBLSatz);
		}
	}

// VRTSatz wegschreiben oder auflösen
	if (0 != OBLSatz.rmaske) { 	// noch Relationen vorhanden
		__WriteHR(dbaVRT, VRTSatz);
	} else {			// letzte Relation wurde gelöscht
		__DisposeHR(dbaVRT, VRTSatz);
		OBLSatz.zovor = 0;	// ObjektSatz richten und wegschreiben
		__WriteHR(dbaOBL, OBLSatz);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Löschen einer Begleitrelation 
/*static*/
HRESULT CNativeObject::DeleteBegleitRelation (HPROJECT hPr, INT_PTR lOPrim, INT_PTR lOSek) 
{
DB_ADDR_OBL dbaOBLP(hPr), dbaOBLS(hPr);
struct obl OBLSatzP, OBLSatzS;
ErrCode RC;

// ObjektSätze einlesen
	dbaOBLP.rec_no = lOPrim;
	__ReadHR(dbaOBLP, OBLSatzP);
	dbaOBLS.rec_no = lOSek;
	__ReadHR(dbaOBLS, OBLSatzS);

// wenn noch keine ObjektRelation exitiert
	if (!BREL(OBLSatzP.rmaske) && !BREL(OBLSatzS.rmaske)) 
		return HRESULT_FROM_ERRCODE(W_NOTEXTOBJ);

	{
	DB_ADDR dbaVRTP(hPr), dbaVRTS(hPr);
	struct reltyp VRTSatzP, VRTSatzS;

		dbaVRTP.file_no = dbaVRTS.file_no = RELTYP;

	// RELTYPSatz für PrimärObjekt behandeln
		if (OBLSatzP.zovor != 0) {
		// RELTYPSatz einlesen und BRel neu setzen
			dbaVRTP.rec_no = OBLSatzP.zovor;
			__ReadHR(dbaVRTP, VRTSatzP);

			VRTSatzP.zbrela = 0L;	// Relation löschen
			__WriteHR(dbaVRTP, VRTSatzP);

			if ((OBLSatzP.rmaske &= ~BRELA) == 0) {
				__DisposeHR(dbaVRTP, VRTSatzP);
				OBLSatzP.zovor = 0L;
			}
			__WriteHR(dbaOBLP, OBLSatzP);
		} else
			return HRESULT_FROM_ERRCODE(W_NOTEXTOBJ);

	// RELTYPSatz für SekundärObjekt behandeln
		if (OBLSatzS.zovor != 0) {
		// RELTYPSatz einlesen und BRel neu setzen
			dbaVRTS.rec_no = OBLSatzS.zovor;
			__ReadHR(dbaVRTS, VRTSatzS);

			VRTSatzS.zbrelp = 0L;
			__WriteHR(dbaVRTS, VRTSatzS);

			if ((OBLSatzS.rmaske &= ~BRELP) == 0) {
				__DisposeHR(dbaVRTS, VRTSatzS);
				OBLSatzS.zovor = 0L;
			}
			__WriteHR(dbaOBLS, OBLSatzS);
		} else 
			return HRESULT_FROM_ERRCODE(W_NOTEXTOBJ);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob eine bestimmte Relation existiert 
HRESULT CNativeObject::FindRelation (INT_PTR lONr2, INT_PTR lRelCode, int rgRelTyp, long *plWert) 
{
	if (NULL != plWert) 
		*plWert = 0;

// ObjektSatz lesen
DB_ADDR_OBL dbaOBL(m_hPr);
struct obl OBLSatz;
ErrCode RC;

	dbaOBL.rec_no = m_lONr;
	__ReadHR(dbaOBL, OBLSatz);

// Maske auswerten
	if (!(OBLSatz.rmaske & rgRelTyp)) 
		return S_FALSE;

// VRTSatz lesen
DB_ADDR dbaVRT(m_hPr);
struct reltyp VRTSatz;

	dbaVRT.file_no = RELTYP;
	dbaVRT.rec_no = OBLSatz.zovor;
	__ReadHR(dbaVRT, VRTSatz);

// zugehörigen Relationssatz finden
long lRelSatz = 0;

	if (HREL(OBLSatz.rmaske)) {
	// horizontale Relation prüfen
		RETURN_FAILED_HRESULT(FindRelationsSatz (VRTSatz.zhrel, &lRelSatz, lRelCode, lONr2));
	} else if (VRELO(OBLSatz.rmaske)) {
	// vertikal nach oben prüfen
		RETURN_FAILED_HRESULT(FindRelationsSatz (VRTSatz.zvrelo, &lRelSatz, lRelCode, lONr2));
	} else if (VRELU(OBLSatz.rmaske)) {
	// vertikal nach unten prüfen
		RETURN_FAILED_HRESULT(FindRelationsSatz (VRTSatz.zvrelu, &lRelSatz, lRelCode, lONr2));
	}
	if (0 == lRelSatz) return S_FALSE;

// RELSatzNr liefern
	if (plWert != NULL)
		*plWert = lRelSatz;
	return S_OK;
}

HRESULT CNativeObject::FindRelationsSatz (long lBegin, long *plWert, long lRelCode, long lONr2) 
{
DB_ADDR dbaVOR(m_hPr), dbaREL(m_hPr), dbaRAL(m_hPr);
struct vor VORSatz;
struct rel RELSatz;
struct ral RALSatz;
ErrCode RC;	// FehlerCode
long lNext;

	dbaVOR.file_no = VOR;
	dbaREL.file_no = REL;
	dbaRAL.file_no = RAL;
	lNext = lBegin;
	*plWert = 0;

	while (0 != (dbaVOR.rec_no = lNext)) {
	// VORSatz einlesen
		__ReadHR(dbaVOR, VORSatz);
		lNext = VORSatz.znvor;		// nächster Satz	

	// RELSatz einlesen
		dbaREL.rec_no = VORSatz.zvorel;
		__ReadHR(dbaREL, RELSatz);

	// RALSatz lesen
		dbaRAL.rec_no = RELSatz.zrera;
		__ReadHR(dbaRAL, RALSatz);

	// Vergleichen, ob der gesuchte Satz gefunden wurde
		if (lRelCode == RALSatz.rat && 	// RelationsCode
		    m_lONr == RELSatz.zol1 &&	// PrimärObjekt
		    lONr2 == RELSatz.zol2)		// SekundärObjekt
		{
			*plWert = dbaREL.rec_no;
			break;
		}
	}	
	return (0 != *plWert) ? S_OK : S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// sämtliche Relationen (Codes) des Objektes enumerieren
HRESULT CNativeObject::EnumRelationCodes (
	HRESULT (CALLBACK *pFcn)(INT_PTR, int, UINT_PTR), UINT_PTR dwData, int iMaske)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);

	if (::LocGetDBVersion(m_hPr) < NEWDBVERSION) 
		return HRESULT_FROM_ERRCODE(E_BADDIRISVERSION);

// ObjektSatz einlesen
DB_ADDR_OBL dbaOBL(m_hPr);
struct obl OBLSatz;
ErrCode RC;

	dbaOBL.rec_no = m_lONr;
	__ReadHR(dbaOBL, OBLSatz);

// Maske testen
bool fBFound = false;
HRESULT hr = S_OK;

	if (BREL(iMaske)) {			// Begleitrelation
		hr = EnumBegleitRelationCode (pFcn, dwData);
		if (S_OK != hr) return hr;

		fBFound = true;
	}

	if (!KREL(iMaske)) 
		return S_OK;	// nichts gesucht - nichts gefunden

	if (VREL(iMaske)) {
		if (HREL(iMaske)) {
			if (!HREL(OBLSatz.rmaske) && !VREL(OBLSatz.rmaske)) // beides gesucht aber keine da
				return (fBFound) ? S_OK : HRESULT_FROM_ERRCODE(WC_NOTFOUND);
		} else {
			if (!VREL(OBLSatz.rmaske))	// nur VREL's gesucht aber keine da
				return (fBFound) ? S_OK : HRESULT_FROM_ERRCODE(WC_NOTFOUND);
		}
	} else if (HREL(iMaske) && !HREL(OBLSatz.rmaske)) // nur HREL's gesucht aber keine da
		return (fBFound) ? S_OK : HRESULT_FROM_ERRCODE(WC_NOTFOUND);

// RelationsCodes enumerieren
DB_ADDR dbaVRT(m_hPr);
struct reltyp VRTSatz;

	dbaVRT.file_no = RELTYP;
	dbaVRT.rec_no = OBLSatz.zovor;
	__ReadHR(dbaVRT, VRTSatz);

// Einlesen der RelationsCodes
	if (HREL(iMaske) && HREL(OBLSatz.rmaske)) {
		hr = EnumRelationTypesForCode (VRTSatz.zhrel, pFcn, dwData);
		if (S_OK != hr) return hr;
	}
	if (VREL(iMaske) && VRELU(OBLSatz.rmaske)) {
		hr = EnumRelationTypesForCode (VRTSatz.zvrelu, pFcn, dwData);
		if (S_OK != hr) return hr;
	}
	if (VREL(iMaske) && VRELO(OBLSatz.rmaske)) {
		hr = EnumRelationTypesForCode (VRTSatz.zvrelo, pFcn, dwData);
		if (S_OK != hr) return hr;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Einlesen aller RelationsCodes einer logischen Klasse
HRESULT CNativeObject::EnumRelationTypesForCode (
	long lStart, HRESULT (CALLBACK *pFcn)(INT_PTR, int, UINT_PTR), UINT_PTR dwData) 
{
DB_ADDR dbaVOR(m_hPr), dbaREL(m_hPr), dbaRAL(m_hPr);
struct vor VORSatz;
struct rel RELSatz;
struct ral RALSatz;

// DBAdressen initialisieren
	dbaVOR.file_no = VOR;
	dbaREL.file_no = REL;
	dbaRAL.file_no = RAL;

// für jeden Satz der VOR-Kette
long lNext = lStart;
ErrCode RC;
HRESULT hr = S_OK;

	while (0 != (dbaVOR.rec_no = lNext)) {
	// Verbindungskette lesen
		__ReadHR(dbaVOR, VORSatz);
		lNext = VORSatz.znvor;	// nächster Satz

	// einlesen des RELSatzes
		dbaREL.rec_no = VORSatz.zvorel;
		__ReadHR(dbaREL, RELSatz);

	// einlesen des RALSatzes
		dbaRAL.rec_no = RELSatz.zrera;
		__ReadHR(dbaRAL, RALSatz);

	// enumeration des gefundenen RelationsCodes
		if (RELSatz.zol1 == m_lONr) {
		// Primärobjekt
			hr = pFcn (RALSatz.rat, RALSatz.maske, dwData);
			if (S_OK != hr) return hr;
		} else if (RELSatz.zol2 == m_lONr) {
		// SekundärObjekt
			hr = pFcn (RALSatz.rat, RALSatz.maske ^ OUREL, dwData);
			if (S_OK != hr) return hr;
		} else
		// das sollte nicht passieren
			return HRESULT_FROM_ERRCODE(EC_SYSERROR);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Begleitrelation enumerieren 
HRESULT CNativeObject::EnumBegleitRelationCode (
	HRESULT (CALLBACK *pFcn)(INT_PTR, int, UINT_PTR), UINT_PTR dwData)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);

	if (::LocGetDBVersion(m_hPr) < NEWDBVERSION) 
		return HRESULT_FROM_ERRCODE(E_BADDIRISVERSION);

long lAssocONr = AssociatedObject();
HRESULT hr = S_OK;

// abhängiges Textobjekt ist da
	if (lAssocONr < 0) 
		hr = pFcn (-1L, BRELA, dwData);
	else if (lAssocONr > 0) 
		hr = pFcn (-1L, BRELP, dwData);

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Alle Objekte enumerieren, die eine bestimmte Relation zu diesem Objekt besitzen
HRESULT CNativeObject::EnumRelatedObjects (
	INT_PTR lRCode, HRESULT (CALLBACK *pFcn)(INT_PTR, int, UINT_PTR), UINT_PTR dwData) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);

	if (::LocGetDBVersion(m_hPr) < NEWDBVERSION) 
		return HRESULT_FROM_ERRCODE(E_BADDIRISVERSION);

// wenn Begleitrelation gesucht ist, dann dieses hier tun
	if (-1L == lRCode || 0L == lRCode) 
		return EnumBegleitObject (pFcn, dwData);

// ObjektSatz lesen
DB_ADDR_OBL dbaOBL(m_hPr);
struct obl OBLSatz;
ErrCode RC;

	dbaOBL.rec_no = m_lONr;
	__ReadHR(dbaOBL, OBLSatz);

// Testen, ob überhaupt Relationen existieren
	if (!HREL(OBLSatz.rmaske) && !VREL(OBLSatz.rmaske)) 
		return HRESULT_FROM_ERRCODE(WC_NOTFOUND);

// Finden der gegebenen Relation
DB_ADDR dbaRAL(m_hPr);
struct ral RALSatz;

	dbaRAL.file_no = RAL;
	DBASSERTHR(z_keyfind (&dbaRAL, RAT, &lRCode));
	__ReadHR(dbaRAL, RALSatz);

// Aufsammeln der gesuchten Objekte entlang der VREKette
DB_ADDR dbaVRE(m_hPr);
DB_ADDR dbaREL(m_hPr);
struct vre VRESatz;
struct rel RELSatz;
long lNext = RALSatz.zravre;
HRESULT hr = S_OK;

	dbaVRE.file_no = VRE;
	dbaREL.file_no = REL;
	while (0 != (dbaVRE.rec_no = lNext)) {
	// VRESatz lesen
		__ReadHR(dbaVRE, VRESatz);
		lNext = VRESatz.znvre;		// nächster Satz

	// RELSatz lesen
		dbaREL.rec_no = VRESatz.zvrere;
		__ReadHR(dbaREL, RELSatz);

	// überprüfen, ob gegebenes Objekt dabei ist
		if (RELSatz.zol1 == m_lONr) {
		// Primärobjekt
			hr = trias_connectfilter::EnumObjectsWrapper(m_hPr, RELSatz.zol2, 
				RALSatz.maske, pFcn, dwData);
			if (S_OK != hr) return hr;

		} else if (RELSatz.zol2 == m_lONr) {
		// SekundärObjekt
			hr = trias_connectfilter::EnumObjectsWrapper(m_hPr, RELSatz.zol1, 
				RALSatz.maske ^ OUREL, pFcn, dwData);
			if (S_OK != hr) return hr;
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Auffinden des Objektes einer Begleitrelation 
HRESULT CNativeObject::EnumBegleitObject (
	HRESULT (CALLBACK *pFcn)(INT_PTR, int, UINT_PTR), UINT_PTR dwData)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);

	if (::LocGetDBVersion(m_hPr) < NEWDBVERSION) 
		return HRESULT_FROM_ERRCODE(E_BADDIRISVERSION);

long lAssocONr = AssociatedObject();
HRESULT hr = S_OK;

	if (lAssocONr < 0) {
		hr = trias_connectfilter::EnumObjectsWrapper(m_hPr, -lAssocONr, BRELP, pFcn, dwData);
		if (S_OK != hr) return hr;

	} else if (lAssocONr > 0) {
		hr = trias_connectfilter::EnumObjectsWrapper(m_hPr, lAssocONr, BRELA, pFcn, dwData);
		if (S_OK != hr) return hr;

	} else if (lAssocONr == 0)
		return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
	
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// liefert ein eventuell existierendes Begleitobjekt
INT_PTR CNativeObject::AssociatedObject()
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);

	if (::LocGetDBVersion(m_hPr) < NEWDBVERSION) 
		return HRESULT_FROM_ERRCODE(E_BADDIRISVERSION);

// Objektsatz einlesen
ErrCode RC;
DB_ADDR_OBL dbaOBL(m_hPr);
struct obl OBLSatz;

	dbaOBL.rec_no = m_lONr;
	if (EC_OKAY != (RC = (ErrCode)z_readrec (&dbaOBL, &OBLSatz)))
		return 0L;

	if (OBLSatz.rmaske & (BRELA | BRELP)) {
	// besitzt Begleitobjekt
	DB_ADDR dbaVRT(m_hPr);
	struct reltyp VRTSatz;

		dbaVRT.file_no = RELTYP;
		dbaVRT.rec_no = OBLSatz.zovor;
		if (EC_OKAY != (RC = (ErrCode)z_readrec (&dbaVRT, &VRTSatz)))
			return 0L;
		if (OBLSatz.rmaske & BRELA)
			return -VRTSatz.zbrela;	// abhängiges TextObjekt
		else
			return VRTSatz.zbrelp;	// übergeordnetes Objekt
	}
	return 0L;
}

///////////////////////////////////////////////////////////////////////////////
// Relation aufbauen
HRESULT CNativeObject::PutRelation (INT_PTR lOSek, INT_PTR lRelCode, int rgRelTyp)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

// DatenBasisVersion Testen
CActDB ActDB(m_hPr);

	if (::LocGetDBVersion(m_hPr) < NEWDBVERSION)
		return HRESULT_FROM_ERRCODE(E_BADDIRISVERSION);

	if (BREL(rgRelTyp)) {
	// wenn BegleitRelation aufgebaut werden soll
		RETURN_FAILED_HRESULT(PutBegleitRelation (lOSek));
	} else {
	// RelationsSatz aufbauen
	long lRelSatz = 0;		// Nummer des RELSatzes
	int locRelTyp = rgRelTyp & (OUREL | GREL);

		RETURN_FAILED_HRESULT(EstablishRelation (lOSek, lRelCode, locRelTyp, &lRelSatz));

	// Relation für Primärobjekt verketten
		RETURN_FAILED_HRESULT(ChainRelation (m_lONr, lRelSatz, locRelTyp));

	// Relation für Sekundärobjekt verketten
		RETURN_FAILED_HRESULT(ChainRelation (lOSek, lRelSatz, locRelTyp ^ OUREL));
	}

// RelationsTyp in ObjektSätzen schreiben
	RETURN_FAILED_HRESULT(MaskRelation (m_lONr, rgRelTyp, true));
	RETURN_FAILED_HRESULT(MaskRelation (lOSek, rgRelTyp, false));
	return S_OK;
}

HRESULT CNativeObject::EstablishRelation (INT_PTR lOSek, INT_PTR lRCode, int rgRelTyp, long *plRelSatz)
{
ErrInstall EI (WC_NOTFOUND);	// Fehlermeldung unterdrücken
DB_ADDR dbaRAL(m_hPr);
struct ral RALSatz;
long RC;

// RelCode als Schlüssel suchen und ggf. neuen Schlüsseleintrag machen
	dbaRAL.file_no = RAL;
	if ((RC = z_keyfind (&dbaRAL, RAT, &lRCode)) != EC_OKAY) {

		if (RC == WC_NOTFOUND) {
		// RelCode existiert noch nicht
			RALSatz.rat = lRCode;	// RelationsCode setzen
			RALSatz.maske = rgRelTyp;
			__NewHR(dbaRAL, RALSatz);
		} else 
			return HRESULT_FROM_ERRCODE(RC);	// Fehler
	} else {
	// RelCode existiert bereits, einlesen
		__ReadHR(dbaRAL, RALSatz);

	// prüfen, ob RelTyp übereinstimmt
		if (RALSatz.maske != rgRelTyp)
			return HRESULT_FROM_ERRCODE(W_BADRELTYP);
	}

// Aufbauen des RELSatzes
	if (!FindRelation (lOSek, lRCode, rgRelTyp)) {
	DB_ADDR dbaREL(m_hPr);
	struct rel RELSatz;

		dbaREL.file_no = REL;
		RELSatz.zrera = dbaRAL.rec_no;
		RELSatz.zol1 = m_lONr;
		RELSatz.zol2 = lOSek;

		__NewHR(dbaREL, RELSatz);
		*plRelSatz = dbaREL.rec_no;

	// RALSatz in VerbindungsDatei einketten
		RETURN_FAILED_HRESULT(::CreateLink (m_hPr, VRE, &RALSatz.zravre, *plRelSatz));
		__WriteHR(dbaRAL, RALSatz);
	} else 
		return HRESULT_FROM_ERRCODE(S_DUPLREL);

	return S_OK;
}

// Verketten der Relation in einer der drei Relationsketten -------------------
HRESULT CNativeObject::ChainRelation (INT_PTR lONr, INT_PTR lRelSatz, int rgRelTyp) 
{
DB_ADDR_OBL dbaOBL(m_hPr);
DB_ADDR dbaVRT(m_hPr);
struct obl OBLSatz;
struct reltyp VRTSatz;
long RC;

// ObjektSatz einlesen
	dbaOBL.rec_no = lONr;
	__ReadHR(dbaOBL, OBLSatz);

// verlängerten ObjektSatz lesen/neu bilden
	dbaVRT.file_no = RELTYP;
	if (0 != OBLSatz.zovor) {
	// RELTYPSatz einlesen
		dbaVRT.rec_no = OBLSatz.zovor;
		__ReadHR(dbaVRT, VRTSatz);
	} else {
	// selbigen neu generieren
		__NewHR(dbaVRT, VRTSatz);
		OBLSatz.zovor = dbaVRT.rec_no;
		__WriteHR(dbaOBL, OBLSatz);
	}

// RelTyp-abhängiges einketten
int rgVrel = VREL(rgRelTyp);
int rgHrel = HREL(rgRelTyp);

	if (rgHrel) {
		RETURN_FAILED_HRESULT(::CreateLink (m_hPr, VOR, &VRTSatz.zhrel, lRelSatz));
		__WriteHR(dbaVRT, VRTSatz);
	} else if (rgVrel & UREL) {
		RETURN_FAILED_HRESULT(::CreateLink (m_hPr, VOR, &VRTSatz.zvrelu, lRelSatz));
		__WriteHR(dbaVRT, VRTSatz);
	} else if (rgVrel & OREL) {
		RETURN_FAILED_HRESULT(::CreateLink (m_hPr, VOR, &VRTSatz.zvrelo, lRelSatz));
		__WriteHR(dbaVRT, VRTSatz);
	}
	return S_OK;
}

// Setzen der Relationsmasken 
HRESULT CNativeObject::MaskRelation (INT_PTR lONr, int rgRelTyp, bool fFlag) 
{
int rgHrel = HREL(rgRelTyp);
int rgVrel = VREL(rgRelTyp);
int rgBrel = BREL(rgRelTyp);

DB_ADDR_OBL dbaOBL(m_hPr);
struct obl OBLSatz;
long RC;

// ObjektSatz einlesen
	dbaOBL.rec_no = lONr;
	__ReadHR(dbaOBL, OBLSatz);

// Relationstyp im ObjektSatz korrigieren
	OBLSatz.rmaske |= rgHrel;
	if (fFlag) {
		OBLSatz.rmaske |= rgVrel;
		OBLSatz.rmaske |= rgBrel;
	} else {
		if (0 != rgVrel) 
			OBLSatz.rmaske |= rgVrel ^ OUREL;
		if (0 != rgBrel) 
			OBLSatz.rmaske |= rgBrel ^ BRELAP;
	}
	if (rgVrel || rgHrel || rgBrel) 
		__WriteHR(dbaOBL, OBLSatz);

	return S_OK;
}

HRESULT CNativeObject::PutBegleitRelation (INT_PTR lOSek)
{
DB_ADDR_OBL dbaOBLP(m_hPr), dbaOBLS(m_hPr);
struct obl OBLSatzP, OBLSatzS;
long RC;

// ObjektSätze einlesen
	dbaOBLP.rec_no = m_lONr;
	__ReadHR(dbaOBLP, OBLSatzP);
	dbaOBLS.rec_no = lOSek;
	__ReadHR(dbaOBLS, OBLSatzS);

// wenn Primärobjekt TextObjekt ist, dann Fehler
	if (OBLSatzP.status & SB_TEXTOBJ)
		return HRESULT_FROM_ERRCODE(S_BADPRIMOBJ);

// wenn noch keine ObjektRelation exitiert
	if (!BREL(OBLSatzP.rmaske) && !BREL(OBLSatzS.rmaske)) {
	DB_ADDR dbaVRTP(m_hPr), dbaVRTS(m_hPr);
	struct reltyp VRTSatzP, VRTSatzS;

		dbaVRTP.file_no = dbaVRTS.file_no = RELTYP;

	// RELTYPSatz für PrimärObjekt behandeln
		if (0 == OBLSatzP.zovor) {
		// RELTYPSatz existiert noch nicht
			VRTSatzP.zbrela = lOSek;
			__NewHR(dbaVRTP, VRTSatzP);

		// ObjektSatz korrigieren
			OBLSatzP.zovor = dbaVRTP.rec_no;
			__WriteHR(dbaOBLP, OBLSatzP);
		} else {
		// RELTYPSatz einlesen und BRel neu setzen
			dbaVRTP.rec_no = OBLSatzP.zovor;
			__ReadHR(dbaVRTP, VRTSatzP);

			VRTSatzP.zbrela = lOSek;
			__WriteHR(dbaVRTP, VRTSatzP);
		}

	// RELTYPSatz für SekundärObjekt behandeln
		if (0 == OBLSatzS.zovor) {
		// RELTYPSatz existiert noch nicht
			VRTSatzS.zbrelp = m_lONr;
			__NewHR(dbaVRTS, VRTSatzS);

		// ObjektSatz korrigieren
			OBLSatzS.zovor = dbaVRTS.rec_no;
			__WriteHR(dbaOBLS, OBLSatzS);
		} else {
		// RELTYPSatz einlesen und BRel neu setzen
			dbaVRTS.rec_no = OBLSatzS.zovor;
			__ReadHR(dbaVRTS, VRTSatzS);

			VRTSatzS.zbrelp = m_lONr;
			__WriteHR(dbaVRTS, VRTSatzS);
		}
	} else 
		return HRESULT_FROM_ERRCODE(W_DUPLBREL);

	return S_OK;
}

} // namespace trias_nativeobject 
