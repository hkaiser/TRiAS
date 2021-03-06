// Definition des Interface f�r die Erweiterung "Objektoperationen"
// File: OperExt.cxx


#include "ObjOperP.hxx"

#include "ObjOperR.h"	// Ressourcekonstanten f�r diese Erweiterung (IDS_BERAB_OBJEKT)
#include "ObjOper.hxx"	// Klasse f�r diese Erweiterung


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



// --------------------------------------------------------------------------------------------
// IExtendObjOper-Methoden
// lONr-Objekt schneidet die Objekte, deren Objektnummern in pEnumIn �bergeben werden;
// die Objektnummern der Ergebnis-Objekte werden in ppEnumOut zur�ckgegeben
STDMETHODIMP_ (HRESULT) ObjektOpExtension::SectionObjObjs_ONr (LONG lONr, IEnumLONG* pEnumIn,
									   DWORD dwLageAusw, SpForm sfSForm, IEnumLONG** ppEnumOut)
{
	if (NULL == ppEnumOut) return E_POINTER;

	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

HPROJECT hPr = 0;	// hier ist sicher noch Handlungsbedarf !!!
bool bFortAnz = false;	// keine Fortschrittsanzeige
WEnumLONG wEnumUsed;	// die wirklich benutzten Originalobjekte (wird hier nicht ausgewertet)

// durch die nachfolgende Zeile wird die Fehlermeldung WC_MESSAGE_OPER abgeschaltet (siehe auch
// DEX_ErrInstall() und DEX_SetError()); wenn weitere Fehlermeldungen abgeschaltet werden
// sollten, m��te f�r diese eine analoge Zeile geschrieben werden; die Variable EI ist dabei
// frei w�hlbar, da im ErrInstall-Konstruktor das Abschalten erfolgt und im ErrInstall-
// Destruktor wieder das Anschalten, also z.B. ErrInstall EI2 (EC_NOGEOANTRIAS);
ErrInstall EI (WC_MESSAGE_OPER);

	return SchnittObjObjekte_ONr (hPr, lONr, pEnumIn, dwLageAusw, sfSForm, bFortAnz,
								  ppEnumOut);
}


// --------------------------------------------------------------------------------------------
// Die pEnumRegard-Objekte schneiden die pEnumTarget-Objekte; die wirklich geschnittenen
// Originalobjekte werden in ppEnumUsed zur�ckgegeben, die neu erzeugten Objekte in ppEnumNew
STDMETHODIMP_ (HRESULT) ObjektOpExtension::ObjectSection (HPROJECT hPr,
				  IEnumLONG* pEnumRegard, IEnumLONG* pEnumTarget, DWORD dwLage, BOOL bCopyFeat,
				  BOOL bFortAnz, IEnumLONG** ppEnumUsed, IEnumLONG** ppEnumNew)
{
	_ASSERTE (0 != pEnumRegard);

	m_OpMode = EINZOBJ;
	bCopyFeat ? (m_bCopyFeat = true) : (m_bCopyFeat = false);

HRESULT hrRet = S_OK;
long lRegONr;			// Objektnummer eines der schneidenden Objekte
SpForm sfSForm = SFORM_PERM;

	for (pEnumRegard->Reset(); S_OK == pEnumRegard->Next (1, &lRegONr, NULL); )
	{
	HRESULT hr = SchnittObjObjekte_ONr (hPr, lRegONr, pEnumTarget, dwLage, sfSForm, bFortAnz,
										ppEnumNew);

		if (FAILED(hr)) hrRet = hr;
	}

	// die wirklich verwendeten Originalobjekte in ppEnumUsed zur�ckgeben
	if (*ppEnumUsed && m_lOrigInd > 0)
		for (long l = 0; l < m_lOrigInd; l++)
			((IEnum<LONG>*)*ppEnumUsed)->AddItem (m_plOrigObjNr[l]);

	return hrRet;
}


// --------------------------------------------------------------------------------------------
// pIOG-Objekt schneidet die Objekte, deren Objektnummern in pEnumIn �bergeben werden
STDMETHODIMP_ (HRESULT) ObjektOpExtension::SectionObjObjs_Geom (IObjektGeometrie* pIOG,
				   IEnumLONG* pEnumIn, DWORD dwLageAusw, SpForm sfSForm, IEnumLONG** ppEnumOut)
{
	if (NULL == ppEnumOut) return E_POINTER;

bool bFortAnz = false;				// keine Fortschrittsanzeige
ErrInstall EI (WC_MESSAGE_OPER);	// keine Anzeige der Fehlermeldung WC_MESSAGE_OPER

	return SchnittObjObjekte_Geom (pIOG, pEnumIn, dwLageAusw, sfSForm, bFortAnz, ppEnumOut);
}


// --------------------------------------------------------------------------------------------
// lONr-Objekt schneidet alle Objekte der ulIdent-Objektklasse
STDMETHODIMP_ (HRESULT) ObjektOpExtension::SectionObjOClass_ONr (LONG lONr, ULONG ulIdent,
									   DWORD dwLageAusw, SpForm sfSForm, IEnumLONG** ppEnumOut)
{
	return E_NOTIMPL;
}


// --------------------------------------------------------------------------------------------
// pIOG-Objekt schneidet alle Objekte der ulIdent-Objektklasse
STDMETHODIMP_ (HRESULT) ObjektOpExtension::SectionObjOClass_Geom (IObjektGeometrie* pIOG,
						ULONG ulIdent, DWORD dwLageAusw, SpForm sfSForm, IEnumLONG** ppEnumOut)
{
	return E_NOTIMPL;
}


// --------------------------------------------------------------------------------------------
// pIOG-Kante schneidet lONr-Objekt
STDMETHODIMP_ (HRESULT) ObjektOpExtension::SectionLineObj_Geom (IObjektGeometrie* pIOG,
															  LONG lONr, IEnumLONG** ppEnumOut)
{
	if (NULL == ppEnumOut) return E_POINTER;

	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

HPROJECT hPr = 0;	// hier ist sicher noch Handlungsbedarf !!!
bool bFortAnz = false;				// keine Fortschrittsanzeige
ErrInstall EI (WC_MESSAGE_OPER);	// keine Anzeige der Fehlermeldung WC_MESSAGE_OPER

	return SchnittKanteObj_Geom (hPr, pIOG, lONr, bFortAnz, ppEnumOut);
}


// --------------------------------------------------------------------------------------------
// pIOG-Kante schneidet alle Objekte der ulIdent-Objektklasse
STDMETHODIMP_ (HRESULT) ObjektOpExtension::SectionLineObjs_Geom (IObjektGeometrie* pIOG,
														  ULONG ulIdent, IEnumLONG** ppEnumOut)
{
	return E_NOTIMPL;
}


// --------------------------------------------------------------------------------------------
// Durchschnitt der Fl�chen, deren Objektnummern in pEnumIn �bergeben werden; weitere Parameter
// sind
// - ulIdent:  Identifikator f�r die Ergebnisfl�chen
// - sfSForm:  Speicherform (permanent, tempor�r)
// - bFortAnz: Fortschrittsanzeige wird eingeblendet (true) bzw. ist nicht sichtbar (false)
// in ppEnumOut werden die Objektnummern der Ergebnisfl�chen zur�ckgegeben
STDMETHODIMP_ (HRESULT) ObjektOpExtension::AndArea (IEnumLONG* pEnumIn, ULONG ulIdent,
													  SpForm sfSForm, IEnumLONG** ppEnumOut)
												
{
	if (NULL == ppEnumOut) return E_POINTER;

HPROJECT hPr = DEX_GetObjectsProject (ulIdent);
bool bCopyFeat = true;				// Merkmale der Ursprungsobjekte vererben
bool bFortAnz = false;				// keine Fortschrittsanzeige
ErrInstall EI (WC_MESSAGE_OPER);	// keine Anzeige der Fehlermeldung WC_MESSAGE_OPER

	return DurchschnittsFlaeche (hPr, pEnumIn, ulIdent, bCopyFeat, sfSForm, bFortAnz,
								 ppEnumOut);
}


// --------------------------------------------------------------------------------------------
// Vereinigung der Fl�chen, deren Objektnummern in pEnumIn �bergeben werden; weitere Parameter
// sind
// - ulIdent:  Identifikator f�r die Ergebnisfl�chen
// - sfSForm:  Speicherform (permanent, tempor�r)
// - bFortAnz: Fortschrittsanzeige wird eingeblendet (true) bzw. ist nicht sichtbar (false)
// in ppEnumOut werden die Objektnummern der Ergebnisfl�chen zur�ckgegeben
STDMETHODIMP_ (HRESULT) ObjektOpExtension::OrArea (IEnumLONG* pEnumIn, ULONG ulIdent,
													 SpForm sfSForm, IEnumLONG** ppEnumOut)
												
{
	if (NULL == ppEnumOut) return E_POINTER;

bool bFortAnz = false;				// keine Fortschrittsanzeige
ErrInstall EI (WC_MESSAGE_OPER);	// keine Anzeige der Fehlermeldung WC_MESSAGE_OPER

	return VereinigungsFlaeche (pEnumIn, ulIdent, sfSForm, bFortAnz, ppEnumOut);
}


// --------------------------------------------------------------------------------------------
// Exklusiv-Oder der lONr-Fl�che mit allen Fl�chen, deren Objektnummern in pEnumIn �bergeben
// werden
STDMETHODIMP_ (HRESULT) ObjektOpExtension::XorArea_ONr (LONG lONr, IEnumLONG* pEnumIn,
														 SpForm sfSForm, IEnumLONG** ppEnumOut)
{
	if (NULL == ppEnumOut) return E_POINTER;

bool bFortAnz = false;				// keine Fortschrittsanzeige
ErrInstall EI (WC_MESSAGE_OPER);	// keine Anzeige der Fehlermeldung WC_MESSAGE_OPER

	return ExklusivFlaeche_ONr (lONr, pEnumIn, sfSForm, bFortAnz, ppEnumOut);
}


// --------------------------------------------------------------------------------------------
// Exklusiv-Oder der pIOG-Fl�che mit allen Fl�chen, deren Objektnummern in pEnumIn �bergeben
// werden
STDMETHODIMP_ (HRESULT) ObjektOpExtension::XorArea_Geom (IObjektGeometrie* pIOG,
									 IEnumLONG* pEnumIn, SpForm sfSForm, IEnumLONG** ppEnumOut)
{
	if (NULL == ppEnumOut) return E_POINTER;

bool bFortAnz = false;				// keine Fortschrittsanzeige
ErrInstall EI (WC_MESSAGE_OPER);	// keine Anzeige der Fehlermeldung WC_MESSAGE_OPER

	return ExklusivFlaeche_Geom (pIOG, pEnumIn, sfSForm, bFortAnz, ppEnumOut);
}


// --------------------------------------------------------------------------------------------
// gemeinsame Konturabschnitte (Kanten) der lONr-Fl�che mit allen pEnumIn-Fl�chen;
// die Auswertung erfolgt f�r dwLageAusw
//  LINN	wenn pEnumIn-Fl�che innerhalb,
//  LAUSS	wenn pEnumIn-Fl�che au�erhalb bzw.
//  LINAU	wenn pEnumIn-Fl�che sowohl innerhalb als auch au�erhalb
// der lONr-Fl�che liegt;
// ulIdent ist der Identifikator f�r die Ergebnisobjekte
STDMETHODIMP_ (HRESULT) ObjektOpExtension::CommonContour_ONr (LONG lONr, ULONG ulIdent,
				   IEnumLONG* pEnumIn, DWORD dwLageAusw, SpForm sfSForm, IEnumLONG** ppEnumOut)
{
	if (NULL == ppEnumOut) return E_POINTER;

bool bFortAnz = false;				// keine Fortschrittsanzeige
ErrInstall EI (WC_MESSAGE_OPER);	// keine Anzeige der Fehlermeldung WC_MESSAGE_OPER

	return GemeinsameKontur_ONr (lONr, ulIdent, pEnumIn, dwLageAusw, sfSForm, bFortAnz,
								 ppEnumOut);
}


// --------------------------------------------------------------------------------------------
// gemeinsame Konturabschnitte (Kanten) der pIOG-Fl�che mit allen pEnumIn-Fl�chen
STDMETHODIMP_ (HRESULT) ObjektOpExtension::CommonContour_Geom (IObjektGeometrie* pIOG,
										   ULONG ulIdent, IEnumLONG* pEnumIn, DWORD dwLageAusw,
										   SpForm sfSForm, IEnumLONG** ppEnumOut)
{
	return E_NOTIMPL;
//	return m_pObjOper->GemeinsameKontur_Geom (pIOG, ulIdent, pEnumIn, dwLageAusw, sfSForm,
//											  bFortAnz, ppEnumOut);
}


// --------------------------------------------------------------------------------------------
// Linienobjekte werden zu m�glichst gemeinsamen Linienobjekten vereinigt;
// evtl. L�cken werden ausgef�llt, wenn sie <= ulFill sind; f�r bAsArea == true werden
// geschlossene Linien in Fl�chenobjekte umgewandelt
STDMETHODIMP_ (HRESULT) ObjektOpExtension::LinesUnion (IEnumLONG* pEnumIn, ULONG ulIdent,
							 ULONG ulFill, BOOL bAsArea, SpForm sfSForm, IEnumLONG** ppEnumOut)
{
	if (! ppEnumOut)
		return E_POINTER;

ErrInstall EI (WC_MESSAGE_OPER);	// keine Anzeige der Fehlermeldung WC_MESSAGE_OPER

	return LinienZusammenfassung (pEnumIn, ulIdent, ulFill, bAsArea, ppEnumOut);
}


// --------------------------------------------------------------------------------------------
// 2 Linienobjekte werden (m�glichst) zu einem gemeinsamen Linienobjekt vereinigt;
// evtl. L�cke wird ausgef�llt, wenn sie <= ulFill ist; ist die Ergebnislinie geschlossen, wird
// sie f�r bAsArea = true in ein Fl�chenobjekte umgewandelt
STDMETHODIMP_ (HRESULT) ObjektOpExtension::LinesUnion_Geom (IObjektGeometrie* pIOGIn1,
										 IObjektGeometrie* pIOGIn2, ULONG ulFill, BOOL bAsArea,
										 ULONG ulIdent, IObjektGeometrie** ppIOGOut)
{
	if (!pIOGIn1 || !pIOGIn2 || !ppIOGOut)
		return E_POINTER;

ErrInstall EI (WC_MESSAGE_OPER);	// keine Anzeige der Fehlermeldung WC_MESSAGE_OPER

	return LinienZusammenfassung (pIOGIn1, pIOGIn2, ulFill, bAsArea, ulIdent, ppIOGOut);
}


// --------------------------------------------------------------------------------------------
// Splitten aller Objekte, deren Objektnummern in pEnumIn �bergeben werden
STDMETHODIMP_ (HRESULT) ObjektOpExtension::Splitting (IEnumLONG* pEnumIn, ULONG ulFuzzyX,
		   ULONG ulFuzzyY, ULONG ulDangle, IEnumLONG** ppEnumOutAtom, IEnumLONG** ppEnumOutMod)

{
	if (NULL == ppEnumOutAtom) return E_POINTER;

ErrInstall EI (WC_MESSAGE_OPER);	// keine Anzeige der Fehlermeldung WC_MESSAGE_OPER

HPROJECT hPr = 0;	// hier ist sicher noch Handlungsbedarf !!!

	return SplittingBase (hPr, pEnumIn, ulFuzzyX, ulFuzzyY, ulDangle, ppEnumOutAtom,
						  ppEnumOutMod);
}


// --------------------------------------------------------------------------------------------
// Verschieben des lONr-Objektes
STDMETHODIMP_ (HRESULT) ObjektOpExtension::LineShifting_ONr (LONG lONr, LONG lXB, LONG lYB,
				  LONG lXA, LONG lYA, LONG lXE, LONG lYE, MoveDir MD, BOOL bVerlA, BOOL bVerlE,
				  LONG lEps, LONG lXMin, LONG lYMin, LONG lXMax, LONG lYMax, LONG* plONr)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

ErrInstall EI (WC_MESSAGE_OPER);	// keine Anzeige der Fehlermeldung WC_MESSAGE_OPER

	return LinienVerschiebung_ONr (lONr, lXB, lYB, lXA, lYA, lXE, lYE, MD, bVerlA, bVerlE,
								   lEps, lXMin, lYMin, lXMax, lYMax, plONr);
}


// --------------------------------------------------------------------------------------------
// Verschieben des pIOG-Objektes
STDMETHODIMP_ (HRESULT) ObjektOpExtension::LineShifting_Geom (IObjektGeometrie* pIOG,
		   LONG lXB, LONG lYB, LONG lXA, LONG lYA, LONG lXE, LONG lYE, MoveDir MD, BOOL bVerlA,
		   BOOL bVerlE, LONG lEps, LONG lXMin, LONG lYMin, LONG lXMax, LONG lYMax, LONG* plONr)
{
	return E_NOTIMPL;
}
