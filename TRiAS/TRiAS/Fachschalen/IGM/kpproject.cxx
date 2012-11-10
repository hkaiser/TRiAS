//-----------KOMPAKT-MEMBER : Datenquellen----------
// File: KPPROJECT.CXX


#include "kompp.hxx"
#include "version.h"
#include "kompaktr.h"

#include <shellapi.h>

#include <triashelper.h>

#include <oleguid.h>
#include <dirisole.h>
#include <eonrguid.h>

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include <igeometr.hxx>

#include "triasdec.h"
#include "triasdef.h"
#include "kompdef.h"

#include <trelguid.h>
#include <operguid.h>

#include "kpstatus.hxx"
#include "kompdll.hxx" 
#include "komphead.hxx"
#include "gewbaum.hxx"

#include "cobjtree.hxx"
#include "ctopobj.hxx"
#include "kompcls.hxx"
#include "kpproject.hxx"
#include "vobjprop.hxx"
#include "kompias.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32


// --------------------------------------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------------
//Member

#if _MSC_VER >= 1100

BOOL CKompiasExtension :: Datenquelle ( )
{

	HPROJECT hPr = NULL;
	char cbBuffer[_MAX_PATH];
	 
	{
			TRiASDatenQuelle TDQ ( MVWind(),IDD_DATENQUELLE,RF());
			if ( TDQ.GetProjectCount() <= 1 ) {
				hPr = TDQ.GetProjectHandle();
				if (hPr != m_hPr) 
					m_hPr = hPr;
				if (NULL != DEX_GetDataSourceName (m_hPr, cbBuffer)) {
					if (m_pLocDir)
						strcpy ( m_pLocDir,cbBuffer);
					SetzeKompaktDatenPfad ( m_pLocDir);
				}
				return true;

			} else {

// falls Gewässerkataster vorhanden, nur dieses
				hPr = TDQ.GetGewaesserKatasterHandle();
				if ( 0 != hPr ) {		// Kataster bereits angelegt
					if (hPr != m_hPr) 
						m_hPr = hPr;
					if (NULL != DEX_GetDataSourceName (m_hPr, cbBuffer)) {
						if (m_pLocDir)
							strcpy ( m_pLocDir,cbBuffer);
						SetzeKompaktDatenPfad ( m_pLocDir);
					}
					
					return true;
				}

				TDQ.Show(Centre);
				if ( TDQ.Result() == 1 ) {
					hPr = TDQ.GetProjectHandle();
					if (hPr != m_hPr) 
						m_hPr = hPr;
					if (NULL != DEX_GetDataSourceName (hPr, cbBuffer)) {
						if (m_pLocDir)
							strcpy ( m_pLocDir,cbBuffer);


				// KK010906

						HPROJECT hP = DEX_MakeDataSourceActive(m_hPr);
						SetzeKompaktDatenPfad ( cbBuffer);
					}
					return true;
					
				}
			}
	}

	return false;

}

#endif
//----------------------------------------------------------------------
#if _MSC_VER >= 1100
bool CKompiasExtension :: DatenQuelleWechseln (void )
{
	//	Datenquelle wechseln ??
		
	if (Datenquelle()) {

		if ( m_pKH) {
			DELETE_OBJ(m_pKH);
			m_pKH = NULL;
		}
		if (m_pGewAlle)
			DELETE_OBJ(m_pGewAlle);
		return true;
	}
	return false;
}
#endif

//----------------------------------------------------------------------
//---------------------------------------------------------------------------
//--------------------------------------------------------------------------
//-------------------------TRiASDatenQuelle------------------------------
//--------------------------------------------------------------------------

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)


TRiASDatenQuelle :: TRiASDatenQuelle ( pWindow pW, uint res, ResourceFile &RF )
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
	       _DataClass( this, IDC_DATENQUELLCOMBO),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_isValid = false;
	_pW = pW;
	_pData = NULL;
	_iCount = 0;

	_hPr = 0;
	_hGewKatPr = 0;

	OKButton.Disable();

	FillDataClassList();

	return;

}

#pragma warning (default: 4355)
//---------------------------------------------------------------------

TRiASDatenQuelle :: ~TRiASDatenQuelle (void)
{

	DELETE_OBJ(_pData);
}
//----------------------------------------------------------------------
void _XTENSN_EXPORT TRiASDatenQuelle :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

		case IDOK: 
		{
			EndDlg(1);

		}
		
		break;

		case IDCANCEL:
		{
		EndDlg (0);
		}
		break;

	}
	return;
}
//___________________________________________________________________________
//---------------------------------------------------------

void _XTENSN_EXPORT TRiASDatenQuelle :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

	case IDC_DATENQUELLCOMBO:

		{

		char *pBuffer = new char [_MAX_PATH];

		if ( !pBuffer) 
			return;

		int iIndex = _DataClass.GetCurrentIndex();

		if (iIndex != -1) {
			_DataClass.GetCurrentString (pBuffer);

		}

#if _MSC_VER >= 1100

//		_hPr = DEX_GetDataSourceHandleEx (pBuffer);

		CRing r(*_pData);

		for (r.First(); r.Valid() ; r.Next()  ) {
	
		   DATACLLock l(r);

		   if ( l ) {
			   char *pShort = &l->DATAShort();
			   if (strcmp(pBuffer,pShort) == 0) {
					_hPr = l->DATAhPr();
				}
		   }

		}
#endif

		OKButton.Enable();

		DELETE_OBJ(pBuffer);
		}

		break;

	}

}
//----------------------------------------------------------------------------

BOOL TRiASDatenQuelle :: FillDataClassList(void)

{

	ENUMNOKEY EN;
//	Bestimmen der Anzahl der Datenquellen

	_DataClass.Clear();

	_pData = new DATACLList ;
	short iCount = 0;

	KOMPAKTQUELLEN KQ;

	KQ.pC = &_DataClass;
	KQ.pD = _pData;
	KQ.iCount = iCount;

	EN.eFcn = ( ENUMNOKEYPROC) SucheDatenQuellen;
	EN.ePtr = &KQ;
	DEX_EnumDataSources(EN);

	_iCount = KQ.iCount;

	CRing r(*_pData);

	for ( r.First(); r.Valid(); r.Next()) {
//	r.First();
	
		DATACLLock l(r);

		if ( l ) {

			_hPr = l->DATAhPr();

	// Testen , ob Gew.Kataster schon eingerichtet !!
			if ( isGewaesserKatasterHandle(_hPr))
				_hGewKatPr = _hPr;
		}
	}

	return true;
}
//----------------------------------------------------------------------
BOOL TRiASDatenQuelle :: isGewaesserKatasterHandle( HPROJECT hPr)

{
	GEODBHDRENTRY hdrEntry;
	hdrEntry.dwSize = sizeof(GEODBHDRENTRY);

	strncpy (hdrEntry.hdrKey, ResString (ResID(IDS_HEADERKEYIDENT,&_RF),17),16);
	hdrEntry.lphdrText = new char [_MAX_PATH];
	hdrEntry.hdrTextLen = _MAX_PATH-1;

	BOOL iFlag = FALSE;

	if ( 0 != hPr) {
		if (DEX_ReadGeoDBHdrEntryEx (hPr,hdrEntry) == EC_OKAY) 
			iFlag = TRUE;
		// HeaderEintrag existiert
	
	}

	DELETE_OBJ (hdrEntry.lphdrText);

	return iFlag;	

}

//---------------------------------------------------------------------

extern "C"  BOOL PASCAL _XTENSN_EXPORT SucheDatenQuellen (char *pName, Bool , void *pData)
{


	// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen in
	// Klammern hinten anhängen
	

	ListBox *pC = (( KOMPAKTQUELLEN *) pData)->pC;
	DATACLList *pD = (( KOMPAKTQUELLEN *) pData)->pD;

	short iCount = (( KOMPAKTQUELLEN *) pData)->iCount;

	CRing r( *pD);

	char cbBuffer[_MAX_PATH];

#if _MSC_VER >= 1100

	HPROJECT hPr = DEX_GetDataSourceHandleEx(pName);

	TX_ASSERT(NULL != hPr);

	if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {

		int iIndex = pC->AddString (cbBuffer);

		DATACLCreator DATACLCr ( *pD );
		ContCreate ( DATACLCr, DATACL ) ( iCount, pName, cbBuffer, hPr );

	}

	(( KOMPAKTQUELLEN *) pData)->iCount++;


#endif

	return TRUE;

}

//---------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
//----------KPPROJECT.CXX
