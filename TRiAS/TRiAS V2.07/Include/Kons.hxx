// KonsistenzTest einzelner Objekte -------------------------------------------
// File: KONS.HXX

#if !defined(_KONS_HXX)
#define _KONS_HXX

/* 
	GeometrieStatus eines Objektes

   Der Zustand der Geometrie wird durch eine TernärZahl characterisiert:
   wobei 0 - kein entsprechender Geometrieverweis im Objektsatz
	 1 - Verweis im Objektsatz, aber keine gültige Struktur
	 2 - Verweis im Objektsatz und gültige Struktur

	FLP
	000
	001
	002	gültiger Punkt
	010
	011
	012
	020	gültige Linie
	021
	022
	100
	101
	102
	110
	111
	112
	120
	121
	122
	200	gültige Fläche
	201
	202
	210
	211
	212
	220
	221
	222

 */

#define	KTKNoGeometrie 		0
#define	KTKisPoint 			1
#define	KTKisValidPoint 	2
#define	KTKisLine 			3
#define	KTKisValidLine 		6
#define	KTKisArea 			9
#define	KTKisValidArea 		18

// TestStatus des Kontextes ---------------------------------------------------
#define KTSHandleObject		IDS_KONSOBJECT
#define KTSHandlePoint		IDS_KONSPOINT
#define KTSHandleLine		IDS_KONSLINE
#define KTSHandleArea		IDS_KONSAREA

#define KTSHandleView		IDS_KONSVIEW
#define KTSHandleIdent		IDS_KONSIDENT

// DiagnoseStatus des Kontextes -----------------------------------------------
#define KTDNothing			0x00		// do nothing
#define KTDDiagnose			0x01
#define KTDRepair			0x02
#define KTDQueryCorrection	0x04
#define KTDProtocol			0x08
#define KTDStatus			0x10

#define KTDDeepDiagnose		0x80

// Funktion, welche für jeden Satz einer Verbindungsliste gerufen wird --------
class CKonsistenzTestKontext;

#include "konssatz.hxx"

typedef ErrCode TESTLINKHANDLER (CKonsistenzTestKontext &, CSatzKontext *);
typedef TESTLINKHANDLER* TESTLINKPROC;

// Funktionen, welche Referenzen auf diverse Informationen in einem 
// Verbindungssatz liefern
typedef long & GETWERTHANDLER (long *);		// liefert 'Wert'
typedef GETWERTHANDLER* GETWERTPROC;

typedef long & GETLINKHANDLER (long *);		// liefert Verkettungszeiger
typedef GETLINKHANDLER* GETLINKPROC;

GETWERTHANDLER DefGetWert;			// StandardRoutinen
GETLINKHANDLER DefGetLink;

// Kontext des Tests ----------------------------------------------------------
class GeoDB;
class CDBDict;
class CProtocol;

class CKonsistenzTestKontext {
protected:
	DWORD m_dwTarget;	// ObjNr, SichtName oder Identifikator
	long m_lRecNo;		// zum Target gehörende RecordNummer
	int m_iTyp;

	short m_iGStatus;	// GeometrieStatus
	short m_iTStatus;	// TestStatus
	short m_iDStatus;	// Diagnose/ReparaturStatus

	CSatzKontext *m_pParent;
	CSatzKontext *m_pBrother;
	CSatzKontext *m_pMe;

	GeoDB &m_rDB;
	CProtocol *m_pPrt;

public:
	GeoDB &DB(void) const { return m_rDB; }

public:
// Konstruktor/Destruktor
		CKonsistenzTestKontext (GeoDB &, long = 0, int iTyp = OBL, 
			short = KTDDiagnose, CProtocol *pPrt = NULL);
		CKonsistenzTestKontext (GeoDB &, const char * = NULL, 
			short = KTDDiagnose, CProtocol *pPrt = NULL);
		CKonsistenzTestKontext (CKonsistenzTestKontext &);
		~CKonsistenzTestKontext (void);

	long ObjNr (void) { return (long)m_dwTarget; }
	const char *View (void) { return (const char *)m_dwTarget; }

	long RecNo (void) { return m_lRecNo; }
	int Typ (void) { return m_iTyp; }

// ZustandsInformation
	void SetGStatus (short GS) { if (GS != KTKNoGeometrie) m_iGStatus += GS; else m_iGStatus = 0; }
	short GStatus (void) { return m_iGStatus; }

	void SetTStatus (short KS) { m_iTStatus = KS; }
	short TStatus (void) { return m_iTStatus; }

	void SetDStatus (short DS) { m_iDStatus = DS; }
	short DStatus (void) { return m_iDStatus; }

	ErrCode TestIdentifikator (COBLKontext &);
	ErrCode TestGeometrie (COBLKontext &);
	ErrCode TestMerkmale (COBLKontext &, long lMCode = 0L);
	ErrCode TestMerkmale (CSICHTKontext &, long lMCode = 0L);
	ErrCode TestMerkmale (CIDLKontext &, long lMCode = 0L);
	ErrCode TestDeletedMerkmal (COBLKontext &, long lMCode);
	ErrCode TestDeletedMerkmal (CSICHTKontext &, long lMCode);
	ErrCode TestDeletedMerkmal (CIDLKontext &, long lMCode);

	ErrCode TestIDL (long &rlFirst, long lONr);

	bool operator ! (void) { return 0 > m_lRecNo; }

friend TESTLINKHANDLER ObjektMerkmalsTest;
friend TESTLINKHANDLER SichtMerkmalsTest;
friend TESTLINKHANDLER IdentMerkmalsTest;

protected:
	ErrCode TestMerkmalsInfo (long &, long);
	ErrCode TestTextMerkmal (long &);
	ErrCode TestIndTextMerkmal (long &);
	ErrCode TestNumericMerkmal (long &);
	ErrCode TestBinaryMerkmal (long &);

	ErrCode TestGeometriePoint (long &);
	ErrCode TestGeometrieLine (long &);
	ErrCode TestGeometrieArea (long &);

	ErrCode TestCoords (long &x, long &y);
	ErrCode TestVGO (long &zVGO);
	ErrCode TestKFK (long &zKFK);
	ErrCode TestLink (short, long &, long = -1,
			  GETWERTPROC = DefGetWert, 
			  GETLINKPROC = DefGetLink,
			  TESTLINKPROC = NULL);

	DWORD Target (void) { return m_dwTarget; }

public:
	void SetParent (CSatzKontext *pP) { m_pParent = pP; m_pBrother = NULL; }
	void SetParent (CSatzKontext *pP, long *pField) 
		{ m_pParent = pP; if (pP) pP -> SetField (pField); 
		  m_pBrother = NULL; }
	void SetBrother (CSatzKontext *pB) { m_pBrother = pB; }
	void SetBrother (void) { m_pBrother = m_pMe; m_pMe = NULL; }
	void SetMe (CSatzKontext *pM) { m_pMe = pM; }
	CSatzKontext *GetParent (void) const { return m_pParent; }
	CSatzKontext *GetBrother (void) const { return m_pBrother; }
	CSatzKontext *GetMe (void) const { return m_pMe; }

	void *GetField (void) { return GetMe() ? GetMe() -> GetField() : NULL; }
	void SetField (long *pData) { if (GetMe()) GetMe() -> SetField(pData); }

	char *ListName (long iRecord, char *pBuffer);	// liefert kompletten RecordNamen
	short RecSize (long iRecNo);	// liefert Satzgröße in long's

	void Out (char *pOut); 
};

// FunktionsPrototypen --------------------------------------------------------
ErrCode BadestRC (ErrCode RC1, ErrCode RC2);
bool KonsErrorWindow (LPCSTR cbOutBuff);


#endif // _KONS_HXX
