// Anzeige und Recherche von Sachinformationen
// File: ATTRIBUT.HXX

#if !defined(_ATTRIBUT_HXX)
#define _ATTRIBUT_HXX


#include <itriasap.h>
#include <triastlb.h>


class AttributExtension : public CTriasExtension {
private:

//-----------Basic-----------------------------
	IExtendBScript *m_pScript;
//-------------------------------------------
	_DDocument *m_pDoc;
	
	IExtendTopRel2 *m_pTop;


	IDMTree *m_pMKM;		//	MK-Baum
	IDMTree *m_pIDM;			// 	ID-Baum
 	OBJTree *m_pOBJ;		//	Objectbaum
 	CLSTree *m_pClass;		//	Baum ID-Zuordnung
 	VClassTree *m_pMVergl;		//	Baum M-Vergleich
	SHWNDTree *m_pHWNDTree;		// 	HWND-Baum ( OR-Fenster)

	class IdentInformation *m_pInfo;	// StatusFenster
	HWND m_hWnd;
	HWND m_hWndSec;
	pWindow m_pW;

	short m_isBreak;
	short m_isORHwnd;
	short m_isCont;
	short m_iFct;
	short m_iTyp;
	short m_isVorn;
	short m_iLenCLS;	// max. LÑnge des MWertes zur Zuordnung CLS

	long m_lIdent2;
	long m_lMCode;
	long *m_pMCode;
	long m_lIntervall;
	long m_RootObject;
	char *m_pMText;
	
protected:
// ¸berladene virtuelle Funktion(en)

	STDMETHOD_(bool, InitExtension) (THIS_ short iMode);
	STDMETHOD_(bool, UnLoadExtension) (THIS);
	STDMETHOD_(bool, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(bool, MenuCommand) (THIS_ UINT uiMenuID, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);

public:
// Konstruktor / Destruktor
		AttributExtension (void);
		~AttributExtension (void);


// Memberfunktionen
// Interface-STATIFCE
	void ReleaseInterface(void);
	bool GetGeoObjectFromONr ( long, _DGeoObject **);
	bool LadeBasicScript(void);
	bool LadeBasicDocument(void);
	bool LadeTopRel(void);

// Memberfunktionen
	void AddORHwnd (void);
	void DeleteORHwnd (void);
	Bool HideORHwnd (void);
	Bool Pruefe_2_ORHwnd (void);
	short isORHwnd (void) { return m_isORHwnd;};
	void CreateORWindow ( short, short, short,long *, char *, short, short, short);
	void ErfassenObjekte(short);
	void SuchePartner( short);
	void TauscheMerkmal( void);
	void BildeMerkmal( void);
	void LoescheMerkmal( void);
	void ObjektKontrolle( void);
	Bool Objekt_hat_Merkmal(long);
	Bool Partner_hat_Merkmal(long);
	Bool Speichern_Merkmal(long,long);
	Bool Loeschen_Merkmal(long);
	Bool Zusammenstellen_Merkmal( long);
	Bool Konstruiere_Merkmal( long,long,char *,unsigned int,unsigned int);
	Bool MerkmalsZuordnung ( void);
	void MerkmalsTest ( void);
	Bool Testen_Merkmal ( long );
	Bool Vergleiche_Merkmal ( short, char *, char * );
	Bool IdentInFenster ( HWND );
	void LadeObjektKlasse(void);
	void VerdichteObjektKlasse(void);
	void SetTreeInformation( void);
	Bool FindeKriterium ( void );
	char *FindeVergleichsText ( long, long);
	void Text_Und_Merkmal ( void );
	Bool SetzeText( long );
	void ModId ( long, char *);
	char *Substring ( long, char *);
	void LoadClassList ( void);
	char *ReadRecord ( char*, int *);
	void Klassifiziere ( void );
	void KlassifiziereObjekt ( void );
	bool BearbeiteObjekt ( long );
//------Nur fÅr Sorge ----------------------------------
	short MerkmalVergleich ( void );
	void BildeMerkmalBaum ( long ONr );
	bool LadeMerkmalBaum ( char * );
	void ZeigeAlleFenster ( void );
	void SorgesAblage ( void );
	void BildeTPBaum ( long, OBJTree * );
	void DruckBild ( OBJTree * , char *, char *, char *);
	short AusgabeClip ( short, char * , OBJTree * , char *, char *, char *);
	void Nomenklatur ( long, char *);
	void KreisName ( long, char *, char *);
	void SetMerkmal(long,long,char *);
};

#endif 	// _ATTRIBUT_HXX
