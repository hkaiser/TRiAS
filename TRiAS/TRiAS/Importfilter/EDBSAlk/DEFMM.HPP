///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			defmm.hpp
//
//	Stand:			18.05.1995
//	Beschreibung:	Elemente zur Editierung einer Liste aus Identi-
//					fikator und Bezeichnung
//
//	Entwicklung:	18.05.95	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#ifndef _DEFMM_HPP_
#define _DEFMM_HPP_

#if defined(_USE_CONFIG_DIALOGS)

class CDefMMList
{
	CComboBox			*pCB;
	CEdit				*pED;
	CButton				*pMod;
	CButton				*pDel;
	CMapStringToString	*pMap;
	CString				m_strMerk;
	BOOL				m_MMKgeaendert;
	BOOL				m_MMBgeaendert;
	BOOL				m_bListeGeaendert;

public:
	enum				tTestModus
						{	TestMode8,
							TestMode8x,
							TestMode4,
							TestModeA3
						};

private:
	tTestModus			m_Mode;

	BOOL				EingabeOK();
	
public:
						CDefMMList();
						~CDefMMList();
	void				SetElements( CComboBox *pC, CEdit *pE,
									 CButton *pM, CButton *pD,
									 CMapStringToString *pL, tTestModus m );
	void				Reset();
	void				OnClickedDel();
	void				OnClickedMod();
	void				OnEditKode();
	void				OnEditBez();
	void				OnAuswahlKode();

	void				KodeGeaendert() { m_MMKgeaendert = TRUE; }
	BOOL				NotSavedEdit()	{ return ( m_MMKgeaendert || m_MMBgeaendert ); }
	BOOL				Modified()		{ return m_bListeGeaendert; }
};

#endif // defined(_USE_CONFIG_DIALOGS)

#endif	// _DEFMM_HPP_
