
// File: ATTRIBUT.CXX

#include "attribp.hxx"


#include <oleguid.h>
#include <dirisole.h>

#include <triashelper.h>
#include <triashelper_i.c>

#include <eonrguid.h>

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>


#include <xtsnaux.hxx>
#include <xtsnguid.h>
#include <initguid.h>
#include <istatus.h>
#include <igeometr.hxx>

//---GUIDS---------------------
#include <trelguid.h>
#include "attrguid.h" 

#include "version.h"

#include "attribut.h" 
#include "about.h"
#include "define.h"

#include "about.hxx"
#include "idkey.hxx"    
#include "objkey.hxx"
#include "clstree.hxx"
#include "stohwnd.hxx"
#include "attinfo.hxx"
#include "erben.hxx"
#include "bilden.hxx"
#include "auswahl.hxx" 
#include "txtedit.hxx"
#include "mwerte.hxx"
#include "attribut.hxx"

// Die folgende Funktion muá vom Nutzer bereitgestellt werden und lediglich
// ein Objekt vom konkreten ErweiterungTyp anlegen. Diese Funktion ist notwendig,
// da keine virtuellen Konstruktoren erlaubt sind.
CTriasExtension *NewExtension (void)
{
	return new AttributExtension ();
}

//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
//
bool GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
	memcpy (&rClsID, &CLSID_Sachdaten, sizeof (GUID));
	return true;
}

// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll.
//
// ACHTUNG: Im VersionsRC-File (*.rcv) nicht den Eintrag "TRiASSelfRegister" 
// vergessen. Ohne diesen EIntrag wird die Funktion UpdateRegistry nie gerufen.
bool UpdateRegistry (bool fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
	bool fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_Sachdaten, 
				TEXT("TRiAS.Attributverarbeitung.1"), IDS_LONGCLASSNAME,
				ATTRIBUT_MAJORVERSION, ATTRIBUT_MINORVERSION,
				EFUnLoadable|EFVisible);
		return fSuccess;
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_Sachdaten, 
				TEXT("TRiAS.Attributverarbeitung.1"));
	}

return true;	// alles ok

}


// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muá von der Klasse 'TriasExtension'
// abgeleitet sein, welche wiederum als einzigen Parameter den ResID des
// im Hauptfenster einzuh„ngeneden Menu's bergeben bekommt.
AttributExtension :: AttributExtension (void)
		  : CTriasExtension (ATTRIBUTEXTENSIONMENU,ATTRIBUTORMENU)
{

	m_pIDM = NULL;		//	ID-Verzeichnis
	m_pOBJ = NULL;		//	Obj-Verzeichnis
	m_pClass = NULL;	//	MK-ID-ZuOrdnung
	m_pMVergl = NULL;	//	MK-Vergleich
	m_pHWNDTree = NULL;
	m_isORHwnd = 0;
	m_iFct = 0;
	m_iLenCLS = 0;
	m_lIntervall = 0L;
	m_pMKM = NULL;		//	MK-Verzeichnis
	m_pMCode = NULL;
	m_pInfo = NULL;
	m_pW = NULL;
	m_pMText = NULL;
	HideORHwnd();
// Interface

	m_pDoc = NULL;
	m_pScript = NULL;
	m_pTop = NULL;


}

// Destruktor -----------------------------------------------------------------
AttributExtension :: ~AttributExtension (void) 
{

		DELETE ( m_pIDM );

		DELETE ( m_pOBJ );

		DELETE ( m_pClass );

		DELETE ( m_pMVergl );

		DELETE ( m_pHWNDTree );

		DELETE ( m_pMKM);

		DELETE ( m_pMCode);

		DELETE ( m_pMText);

		DELETE ( m_pInfo);

		ReleaseInterface();

}
// ----------------------------------------------------------------------------

// Diese Funktion wird (einmalig) gerufen, wenn die Erweiterung vollst„ndig
// installiert ist
STDMETHODIMP_(bool) AttributExtension :: InitExtension ( short iMode)
{



	if (!CTriasExtension :: InitExtension (iMode))
		return false;
// Notifikation anfordern, die bei ObjektSelektieren/-deselektieren ausgelöst
// wird


// hier zusätzlichen MenuPunkt anhängen

	RegisterNotification (DEX_PROJECTOPEN);	
	RegisterNotification (DEX_PROJECTCLOSE);
	RegisterNotification (DEX_CREATEOBJEKTINFO);
	RegisterNotification (DEX_OBJWNDCLOSED);


	return TRUE;

}

// Diese Funktion wird gerufen, bevor die Erweiterung freigeben werden soll
STDMETHODIMP_(bool) AttributExtension :: UnLoadExtension (void)
{
// Notifikationen wieder abmelden
	UnRegisterNotification (DEX_PROJECTOPEN);	
	UnRegisterNotification (DEX_PROJECTCLOSE);
	UnRegisterNotification (DEX_CREATEOBJEKTINFO);
	UnRegisterNotification (DEX_OBJWNDCLOSED);

	return CTriasExtension :: UnLoadExtension();		// kein Fehler
}


// Diese Funktion initialisiert das Menu --------------------------------------
STDMETHODIMP_(bool) AttributExtension :: MenuInit (HMENU hMenu , LPARAM, HWND hWnd )
{


// Mein Menu ???
	if (hWnd == NULL && hMenu != MenuHandle()) return FALSE;
	if (hWnd != NULL && hMenu != ORMenuHandle()) return FALSE;

	if ( hWnd != 0 && hMenu == ORMenuHandle()) {
		if ( m_pHWNDTree == NULL ) 
			m_pHWNDTree = new SHWNDTree;
		bool Flag = false;
		{
		CTable t(*m_pHWNDTree);
		if ( (!t.Find ( (void *)&hWnd ))) {
			SHWNDCreator SHWNDCr ( *m_pHWNDTree );
			ContCreate (SHWNDCr, SHWND) ( hWnd );
			Flag = true;
		}
		}
		if ( Flag)
			AddORHwnd();

		m_hWnd = hWnd;

		UINT iMenuID = IDM_ORWINCOPYATTRIBUT + MenuOffset();

		OBJSTATISTIK OS;
	   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
		OS.dwSize = sizeof(OBJSTATISTIK);
		OS.lONr =  DEX_GetActiveObject ( hWnd );

		if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
			EnableMenuItem (hMenu, iMenuID, MF_BYCOMMAND|MF_ENABLED);
		}
		
		if (m_pHWNDTree->Count() == 2 )
			return TRUE;		

		EnableMenuItem (hMenu, iMenuID, MF_BYCOMMAND|MF_GRAYED);

	}

	return TRUE;
}


// Diese Funktion dient der Behandlung der MenuKommandos vom nutzereigenen
// Menu der Erweiterung
STDMETHODIMP_(bool) AttributExtension :: MenuCommand (WPARAM MenuItemID, HWND hWnd)
{

	switch (MenuItemID) {	

//-----------------ABOUT-Fenster-----------------------------------------
		case IDM_ABOUT:		// AboutBox
		{
		AboutBox AB (MWind(), ResID (ATTRIBUTABOUT, &RF()));

		AB.Show();
		}
		break; 

//-----------------Sichtinformation-----------------------------------------
//	ganze Sicht
		case IDM_SICHTATTRIBUT:
   		{    
		m_hWnd = hWnd;
		m_pW = MWind();
		SetTreeInformation();
		LadeObjektKlasse ( );

		{
		ObjClassAuswahl OCA ( m_pW,AUSWAHLMODUS, RF(), m_pIDM);
		OCA.Show();  
		m_iFct = OCA.Result();
		if ( OCA.Result() == 0 )
			return FALSE;

		m_pMCode = OCA.MCode();
		}

		VerdichteObjektKlasse();
		short MFlag;
//		if ( m_iFct == 1 ) 
		if ( m_iFct == 1 || m_iFct == -3 ) 
			MFlag = MerkmalsZuordnung();
		short Typ = (short)MISicht;

		if ( m_iFct != -2 ) 
			ErfassenObjekte( Typ );

		short Number = 0;	// MVergleich !!!!!

		if ( m_iFct == -1 ) {	//LOE
			LoescheMerkmal();
		} else {
			if ( m_iFct == 1 ) {	//Recherche
				if ( MFlag )
					MerkmalsTest();
				else
					return FALSE;
			}
			if ( m_iFct == -2 ) {	//Mod
				if ( FindeKriterium()) {
					ErfassenObjekte(Typ);
					SuchePartner(Typ);
					TauscheMerkmal();
				} else
					return FALSE;
			}
			if ( m_iFct == -3 ) {	//Vergleiche
				if ( MFlag ) {
					MerkmalsTest();
//---------------------------Nur fr Sorge-----------------------------
					Number = MerkmalVergleich();
				} else
					return FALSE;
			}
		}
		if ( m_iFct == -3 ) {
			ZeigeAlleFenster();
		} else {
			ObjektKontrolle();
		}
		}
		break;

//	ganze Sicht-Merkmale bilden-Carola
		case IDM_CREATESICHTATTRIBUT:

   		{    
		m_hWnd = hWnd;
		m_pW = MVWind();
		SetTreeInformation();
		LadeObjektKlasse ( );

		{
		CreateFeature CF ( m_pW,OBJECTATTRIBUTBILDUNG, RF(), m_pIDM);
		CF.Show();  
		m_iFct = CF.Result();
		if ( CF.Result() == 0 )
			return FALSE;

		m_pMCode = CF.MCode();
		char *pText = CF.MText();
		m_isVorn = CF.isVorsatz();
		if ( pText && *pText != '\0') {
			if ( !m_pMText)
				m_pMText = new char [_MAX_PATH];
			if ( m_pMText )
				strncpy ( m_pMText, pText, _MAX_PATH -1);
		}
		}
		VerdichteObjektKlasse();

		short Typ = (short)MISicht;

		ErfassenObjekte( Typ );

		if ( m_iFct == 1 ) {	//Bilden neuen MWert
			Text_Und_Merkmal();
		}
		ObjektKontrolle();

		}
		break;
////////////////////////////////////////////////////////////////////////

//	ganze Sicht-Merkmale aus Top bilden
		case IDM_CREATETOPATTRIBUT:
   		{    
		m_hWnd = hWnd;
		m_pW = MVWind();
		SetTreeInformation();
		LadeObjektKlasse ( );

		{
		CreateFeature CF ( m_pW,OBJECTATTRIBUTBILDUNG, RF(), m_pIDM);
		CF.Show();  

		m_iFct = CF.Result();
		if ( CF.Result() == 0 )
			return FALSE;

		m_pMCode = CF.MCode();
		
		}

		VerdichteObjektKlasse();

		short Typ = (short)MISicht;

		ErfassenObjekte( Typ );

		if ( m_iFct == 1 ) {	//Bilden neuen MWert
			Text_Und_Merkmal();
		}

		ObjektKontrolle();

		}
		break;

////////////////////////////////////////////////////////////////////////
//	Sichtausschnitt
		case IDM_CONTATTRIBUT:
		{

		CEierUhr Wait ( MWind());
		m_hWnd = hWnd;
		SetTreeInformation();
		m_pW = MWind();

		long Cont[4];
		if ( !DEX_GetActiveSelection ( Cont ))
			DEX_GetActiveSightContainer ( Cont );

		ENUMRECHGEOMETRIE ERGI;
		memset (&ERGI, '\0', sizeof(ENUMRECHGEOMETRIE));
		ERGI.dwSize = sizeof(ENUMRECHGEOMETRIE);
		ERGI.lCont = &Cont[0];
		ERGI.iMode = ERGActSight;
		//	Objekte zählen
		ERGI.eFcn = (RECHGEOMETRIEPROC) EnumObjectsWithStatus;
		ERGI.pData = m_pIDM;
		DEX_EnumRechGeometrie( ERGI );

		{
		ObjClassAuswahl OCA ( MWind(),AUSWAHLMODUS, RF(), m_pIDM);
		OCA.Show();  
		m_iFct = OCA.Result();
		if ( OCA.Result() == 0 )
			return FALSE;

		m_pMCode = OCA.MCode();
		}

		VerdichteObjektKlasse();

		short MFlag;
		if ( m_iFct == 1 ) 
			MFlag = MerkmalsZuordnung();
		short Typ = (short)MISegment;

		if ( m_iFct != -2 ) 
			ErfassenObjekte( Typ );

		if ( m_iFct == -1 ) {	//LOE
			LoescheMerkmal();
		} else { 
			if ( m_iFct == 1 ) {
				if ( MFlag )
					MerkmalsTest();
				else
					return FALSE;
			}
			if ( m_iFct == -2 ) {
				if ( FindeKriterium()) {
					ErfassenObjekte(Typ);
					SuchePartner(Typ);
					TauscheMerkmal();
				} else
					return FALSE;
			}
		}
		ObjektKontrolle();
		}     
		break;

//	Sichtausschnitt-Merkmale bilden-Carola
		case IDM_CREATECONTATTRIBUT:
   		{    

		CEierUhr Wait ( MVWind());
		m_hWnd = hWnd;
		SetTreeInformation();
		m_pW = MVWind();

		long Cont[4];
		if ( !DEX_GetActiveSelection ( Cont ))
			DEX_GetActiveSightContainer ( Cont );

		ENUMRECHGEOMETRIE ERGI;
		memset (&ERGI, '\0', sizeof(ENUMRECHGEOMETRIE));
		ERGI.dwSize = sizeof(ENUMRECHGEOMETRIE);
		ERGI.lCont = &Cont[0];
		ERGI.iMode = ERGActSight;
		//	Objekte zählen
		ERGI.eFcn = (RECHGEOMETRIEPROC) EnumObjectsWithStatus;
		ERGI.pData = m_pIDM;
		DEX_EnumRechGeometrie( ERGI );

		{
		CreateFeature CF ( m_pW,OBJECTATTRIBUTBILDUNG, RF(), m_pIDM);
		CF.Show();  
		m_iFct = CF.Result();
		if ( CF.Result() == 0 )
			return FALSE;

		m_pMCode = CF.MCode();
		char *pText = CF.MText();
		m_isVorn = CF.isVorsatz();

		if ( pText && *pText != '\0') {
			if ( !m_pMText)
				m_pMText = new char [_MAX_PATH];
			if ( m_pMText )
				strncpy ( m_pMText, pText, _MAX_PATH -1);
		}
		}
		VerdichteObjektKlasse();

		short Typ = (short)MISegment;

		ErfassenObjekte( Typ );

		if ( m_iFct == 1 ) {	//Bilden neuen MWert
			Text_Und_Merkmal();
		}
		ObjektKontrolle();

		}
		break;

//--------------------Umklassifizieren---------------------------
		case IDM_ATTRIBUTCLASSIFY:

		{
		CEierUhr Wait ( MWind());
				
		m_hWnd = hWnd;
		m_pW = MWind();

		if ( m_pClass )
			DELETE (m_pClass);

		m_pClass = new CLSTree;
		if ( !m_pClass)
			return true;

		LoadClassList();
		if ( m_pClass && m_pClass->Count() > 0 ) {
			m_pClass->Optimize();
			long lCount = m_pClass->Count();

			Klassifiziere ();
		}
		}
		break;

//---------------Fenster-------------------------------------------
		case IDM_ORWINATTRIBUT:
		{

		CEierUhr Wait ( MWind());
		if ( !IdentInFenster(hWnd))
			return FALSE;
		m_hWnd = hWnd;
		m_pW = ORWind(hWnd);

		{
		ObjClassAuswahl OCA ( m_pW,AUSWAHLMODUS, RF(), m_pIDM);
		OCA.Show();  
		m_iFct = OCA.Result();
		if ( OCA.Result() == 0 )
			return FALSE;

		m_pMCode = OCA.MCode();
		}

		VerdichteObjektKlasse();
		short MFlag;
		if ( m_iFct == 1 ) 
			MFlag = MerkmalsZuordnung();
		short Typ = (short)MIFenster;

		if ( m_iFct != -2 ) 
			ErfassenObjekte( Typ );

		if ( m_iFct == -1 ) {	//LOE
			LoescheMerkmal();
		} else { 
			if ( m_iFct == 1 ) {
				if ( MFlag )
					MerkmalsTest();
				else
					return FALSE;
			}
			if ( m_iFct == -2 ) {
				if ( FindeKriterium()) {
					ErfassenObjekte(Typ);
					SuchePartner(Typ);
					TauscheMerkmal();
				}
			}
		}
		ObjektKontrolle();
		}
		break;

		case IDM_CREATEORWINATTRIBUT :
		{

		CEierUhr Wait ( MWind());
		if ( !IdentInFenster(hWnd))
			return FALSE;
		m_hWnd = hWnd;
		m_pW = ORWind(hWnd);

		{
		CreateFeature CF ( m_pW,OBJECTATTRIBUTBILDUNG, RF(), m_pIDM);
		CF.Show();  
		m_iFct = CF.Result();
		if ( CF.Result() == 0 )
			return FALSE;

		m_pMCode = CF.MCode();
		char *pText = CF.MText();
		m_isVorn = CF.isVorsatz();

		if ( pText && *pText != '\0') {
			if ( !m_pMText)
				m_pMText = new char [_MAX_PATH];
			if ( m_pMText )
				strncpy ( m_pMText, pText, _MAX_PATH -1);
		}
		}
		VerdichteObjektKlasse();

		short Typ = (short)MIFenster;

		ErfassenObjekte( Typ );

		if ( m_iFct == 1 ) {	//Bilden neuen MWert
			Text_Und_Merkmal();
		}
		ObjektKontrolle();


		}
		break;
//-------------------SORGE------------------------------------------
//------------------------------------------------------------------
		case IDM_ORWINMEINESORGE:
		{

		CEierUhr Wait ( MWind());
		if ( !IdentInFenster(hWnd))
			return FALSE;
		m_hWnd = hWnd;
		m_pW = ORWind(hWnd);

		short Typ = (short)MIFenster;

		ErfassenObjekte( Typ );

		SorgesAblage();

		}
		break;

//------------------------------------------------------------------
//-----------------2 Fenster -----------------------------------------

		case IDM_ORWINCOPYATTRIBUT:		
		{
		if ( !Pruefe_2_ORHwnd() )
			return FALSE;
		m_hWnd = hWnd;
		m_pW = ORWind(hWnd);
		m_RootObject =  DEX_GetActiveObject ( m_hWnd);

		{
		DefineCopyInformation DCI ( m_pW,OBJECTATTRIBUTAUSWAHL, RF(), m_RootObject);
		DCI.Show();
		m_iFct = DCI.Result();
		if ( DCI.Result() == 1 ) {
			m_pMCode = DCI.MCode();
		} else
			return FALSE;
		}
		short Typ = (short)MI2Fenster;

 		CEierUhr Wait ( MVWind());

		ErfassenObjekte( Typ );

		SuchePartner(Typ);
		TauscheMerkmal();
		ObjektKontrolle();

		} 
		break;

//---------------------default-------------------------------------
		default:
		return FALSE;

	} // SWITCH
	return FALSE;
}

STDMETHODIMP_(LRESULT) AttributExtension :: Notification (WPARAM iMsg, LPARAM p)
{

	switch (iMsg) {

	case DEX_QUERYRECHOBJECT:
	{
	
	}
	break;


	case DEX_PROJECTOPEN:
	break;

	case DEX_PROJECTCLOSE:
	{
		HideORHwnd();
		DELETE (m_pHWNDTree);
		ReleaseInterface();

	}
	break;

	case DEX_OBJWNDCLOSED:
	// Objektfenster wird geschlossen
	{
	if ( m_pHWNDTree != NULL && m_pHWNDTree->Count() > 0 ) {

		CTable t(*m_pHWNDTree); 
		HWND Rmich = HWND ( p );
		if ( (t.Find ( (void *)&Rmich ))) {
			t.Delete();
			DeleteORHwnd();
		}
		if ( isORHwnd() ) { 
			  t.First();
			 SHWNDLock l(t);
			Rmich = l->Shwnd();
			 SetFocus ( Rmich );
		}
	}
	}
	break;

	case DEX_CREATEOBJEKTINFO:
	// ein Fenster wurde aufgezogen
//-------------- Handle in Baum -----------------------------------------------
	{

	if ( m_pHWNDTree == NULL ) 
		m_pHWNDTree = new SHWNDTree;

	{
	CTable t(*m_pHWNDTree);
	m_hWnd = HWND ( p );

	SHWNDCreator SHWNDCr ( *m_pHWNDTree );
	ContCreate (SHWNDCr, SHWND) ( (HWND) p );
	}
	AddORHwnd();

	}
//---------------------------------------------------------------------------
	break;

	default:
	break;

	}	//Switch

//	return FALSE;
	return CTriasExtension :: Notification( iMsg,p);		// kein Fehler

}

// Memberfunktionen
//-------------------------------------------------------------------------
void AttributExtension :: LoadClassList ( void )
{
	if ( !m_pClass)
		return;
	char *pList = new char [ _MAX_PATH];
        if ( !pList )
        	return;

        strcpy ( pList,"TRiAS(R) Zuordn.Tab (*.cls);(*.txt)|*.cls;*.txt ");

        {
	COpenDialog ODlg ( MVWind() , pList);
//	ODlg.AddFlags( OFN_HIDEREADONLY);
	ODlg.SetCaption ( "Zuordung Merkmal <=> Identifikator" );
	ODlg.Show();
	*pList = '\0';
	if ( ODlg.Result() == 1 ) {	// OK
		int iLen = ODlg.GetFileNameLen();
		ODlg.GetFileName( pList , _MAX_PATH);
	} else {
		DELETE ( pList);
		return;
	}
	}

	OFSTRUCT of;
	if ( OpenFile (pList, &of, OF_EXIST) < 0 ) {
		DELETE ( pList);
		return ;
	}

	HFILE hf = OpenFile (pList, &of, OF_READ);
	if ( hf < 0 ) {
		DELETE (pList);
		return;
	}
	DELETE ( pList);

	_llseek ( hf, 0L,0);
	long Len = _llseek ( hf, 0L,2);
	_llseek ( hf, 0L,0);
	if ( Len <= 0 ) {
		_lclose(hf);
		return;
	}

	char *pASCField = new char [Len+1];
	if ( pASCField ) {
		*pASCField = '\0';
		_lread ( hf, (void __huge *)pASCField, (UINT)Len);
		*(pASCField+Len ) = '\0';
	}

	_lclose(hf);

	m_iLenCLS = 0;
	CEierUhr Wait (MVWind());

	CTable t( *m_pClass);

	char *ptr;
	char *pStart = pASCField;
	char *pMerkmal,*pText;
	char *pIdent = new char [_MAX_PATH];
	if ( !pIdent)
		return;
	int iLen = 0;
	while ( (ptr = ReadRecord (pStart,&iLen)) != NULL ) {
//		int Len = strlen ( ptr);
		pStart = ptr + iLen;
// Aenderungen fuer Netti
		if ( *ptr == '"')
			ptr++;
//---------------------
		pMerkmal = strtok ( ptr,",;\t");
//		pIdent = strtok ( NULL, ",;\t");
		pText = strtok ( NULL, ",;\t");
		long Ident = 0L;

// Aenderungen fuer Netti
		if ( !pMerkmal) {
			DELETE (pASCField);
			DELETE (pIdent);
			return;
		}
		char *eptr = strchr(pMerkmal,'"');
		if ( eptr)
			*eptr = '\0';
		if ( pText) {
			strcpy ( pIdent,pText);
			*(pIdent+3) = '\0';
			strcat ( pIdent, "00000");
		}
//-----------------------
		if ( pIdent) {
			ulong uIdent = (ulong) Ident;
			IdentFromClassX ( pIdent,&uIdent);
			Ident = (long) uIdent;
/*-----Korr23.1.97
			if ( DEX_GetIdBase() == 16 ) {
				Ident = strtoul ( pIdent,NULL,16);
			} else {
				Ident = atol ( pIdent);
			}
------------*/

		}
		if ( pMerkmal ) {
			if ( !t.Find (pMerkmal)) {
				if ( m_iLenCLS < (short) strlen(pMerkmal) )
					m_iLenCLS = (short) strlen(pMerkmal);
				CLSCreator CLSCr ( *m_pClass );
				ContCreate ( CLSCr, CLS ) ( pMerkmal, Ident,pText );
			}
		}
	}
	DELETE (pASCField);
	DELETE ( pIdent);
	return;
}
//------------------------------------------------------------------------
void AttributExtension :: Klassifiziere ( void )
{
	SetTreeInformation();
	LadeObjektKlasse ( );

	{
	CreateFeature CF ( m_pW,OBJECTATTRIBUTBILDUNG, RF(), m_pIDM);
	CF.Show();  
	m_iFct = CF.Result();
	if ( CF.Result() == 0 )
		return;
	m_pMCode = CF.MCode();
	char *pText = CF.MText();
	m_isVorn = CF.isVorsatz();
	if ( pText && *pText != '\0') {
		if ( !m_pMText)
			m_pMText = new char [_MAX_PATH];
		if ( m_pMText )
			strncpy ( m_pMText, pText, _MAX_PATH -1);
	}

	}

	VerdichteObjektKlasse();

	short Typ = (short)MISicht;

	ErfassenObjekte( Typ );

	KlassifiziereObjekt ();

	ObjektKontrolle();

}
//---------------------------------------------------------------------------
char *AttributExtension :: ReadRecord ( char *pStart, int *Len )
{
	if ( !pStart || *pStart == '\0' )
		return NULL;

	if (*pStart == '\n')
		pStart++;
	if (*pStart == '\r')
		pStart++;
	if (*pStart == ' ')
		pStart++;

	if ( *pStart == '\0')
		return NULL;

	char *aptr = pStart;	//Beginn

	char *ptr = strchr ( pStart, '\r');	//SatzEnde

	if ( ptr ) {
		*ptr = '\0';
		if ( *(ptr+1) = '\n') {
			ptr++;
			*ptr = '\0';
		}
		pStart = ptr+1;
	} else {
		ptr = strchr ( pStart, '\n');	//SatzEnde
		if ( ptr) {
			*ptr = '\0';
			pStart = ptr+1;
		}
	}
	*Len = pStart - aptr;
	return aptr;
}
//-----------------------------------------------------------------------
//------Selektierte MKodes Merkmalswerte erfassen ----------
void AttributExtension :: KlassifiziereObjekt ( void ) 
{
	if ( !m_pClass)
		return;
	if ( !m_pMCode )
		return;
	if ( !m_pOBJ)
		return;
	short iRange= ( short ) m_pOBJ->Count();  

	if ( m_pInfo)
		DELETE ( m_pInfo);
	m_pInfo = new IdentInformation ( m_pW, ATTGAUGEBOX, RF(),"Merkmalsanalyse",iRange);
	m_pInfo->Show();
	m_pInfo->Update();
	iRange = 0;

	CTable t (*m_pOBJ);
	for ( t.First(); t.Valid(); t.Next() ) {
		OBJLock l(t);
		long ONr = l->Object();	
			if ( BearbeiteObjekt ( ONr))
				l->SetFlag();
		iRange++;
		if ( m_pInfo->Break() ) {
			HWND hwnd = m_pInfo->Handle();
			MessageBox ( hwnd ,
			 "Recherche wurde abgebrochen !!!", 
			 "Merkmalsanalyse", 
			 MB_OK|MB_ICONEXCLAMATION);
			DELETE ( m_pInfo );
			return;
		}
		m_pInfo->SetText ( iRange);

	}
	DELETE ( m_pInfo);
	return;
}
//--------------------------------------------------------------------------
bool AttributExtension :: BearbeiteObjekt ( long ONr)
{
	if ( !m_pClass || m_pClass->Count() == 0)
		return false;

	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return false;

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = ONr;		// ObjektNummer
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuffer;		// Puffer= Identifikator
	tm.iTTyp = TT_Objekt;

	tm.lMCode = *(m_pMCode+1);		// MerkmalsCode
	long lTextCode = 0L;
	if ( m_pMText && *m_pMText != '\0')
		lTextCode = atol(m_pMText);		// 2.MKode

	if( !DEX_GetTextMerkmal ( tm ) || *pBuffer == '\0') {
		DELETE ( pBuffer);
		return false;
	}
/*----------------- fuer Netti nicht noetig
	char *eptr;
	bool flag;
	if ( (short) strlen (pBuffer) > m_iLenCLS)
		eptr = pBuffer + m_iLenCLS;
	else
		eptr = pBuffer + strlen(pBuffer);
		
	*eptr = '\0';
----------------------------------------------*/

	CTable t(*m_pClass);
	short myFlag = true;

	if ( t.Find(pBuffer)) {

/*----------------- fuer Netti nicht noetig
	while ( strlen(pBuffer) > 0 ) {

		if ( !t.Find(pBuffer)) {
			eptr--;
			eptr = '\0';
			flag = false;
		} else {
			*pBuffer = '\0';
			flag = true;
		}
	}

	DELETE ( pBuffer);
	if ( !flag)
		return false;
----------------------------------------------*/

		CLSLock l(t);

		if ( l->KurzText() && lTextCode != 0L)
			SetMerkmal ( ONr,lTextCode,l->KurzText());
		long Ident = l->Ident();


//-Umklassifizieren
		MODOBJIDENT id;
		id.dwSize = sizeof(MODOBJIDENT);
		id.lONr = ONr;
		id.lNewIdent = Ident;
		if ( DEX_GetObjectType(ONr) == OGPunkt )
			id.iMode = MODIDENT_PUNKT;
		if ( DEX_GetObjectType(ONr) == OGLinie )
			id.iMode = MODIDENT_LINIE;
		if ( DEX_GetObjectType(ONr) == OGFlaeche )
			id.iMode = MODIDENT_FLAECHE;

		if ( !DEX_ModObjectIdent ( id)) 
			myFlag = false;
		else
			myFlag = true;
	} else
		myFlag = false;

	DELETE ( pBuffer);
	return myFlag;
}
// ------------------------------------------------------------------------
void AttributExtension :: SetMerkmal  ( long lONr, long lMCode, char *pText ) 
{
	if ( lONr <= 0L || lMCode <= 0L)
		return;
	if (!pText || *pText == '\0')
		return;


	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// ObjektNummer
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pText;		// Puffer= Identifikator
	tm.iTTyp = TT_Objekt;

	tm.lMCode = lMCode;		// MerkmalsCode

	DEX_ModTextMerkmal ( tm );

}
//-------------------------------------------------------------------------
void AttributExtension :: ErfassenObjekte ( short Typ ) 
{

	if ( m_pOBJ )
		DELETE ( m_pOBJ);

	m_pOBJ = new OBJTree;	
	if ( !m_pOBJ)
		return;

	CEierUhr Wait (MVWind());

	if ( Typ == (short) MISicht ) {

	   CTable t( *m_pIDM );
	   ENUMLONGKEYEX ELK;
	   memset (&ELK,'\0',sizeof(ENUMLONGKEYEX) );
	   ELK.eFcn = ( ENUMLONGKEYEXPROC) SearchObjects;
	   for ( t.First(); t.Valid(); t.Next()) {
		IDMLock l(t);
		long Ident = l->Ident();
		ELK.eKey = Ident;
		ELK.eData = (DWORD) l->RefTyp();
		ELK.ePtr = m_pOBJ;
		DEX_EnumIdentObjectsEx(ELK);
	   }
	}

	if ( Typ == (short) MISegment ) {
		long Cont[4];
		if ( !DEX_GetActiveSelection ( Cont ))
			DEX_GetActiveSightContainer ( Cont );

		ENUMRECHGEOMETRIE ERGI;
		memset (&ERGI, '\0', sizeof(ENUMRECHGEOMETRIE));
		ERGI.dwSize = sizeof(ENUMRECHGEOMETRIE);
		ERGI.lCont = &Cont[0];
		ERGI.iMode = ERGActSight;
		//	Objekte zählen
		ERGI.eFcn = (RECHGEOMETRIEPROC) SearchIdentObjects;
		OBJPOINT OP;
		OP.pOBJ = m_pOBJ;
		OP.pIdent = m_pIDM;
		ERGI.pData = &OP;
		DEX_EnumRechGeometrie( ERGI );
	}

	if ( Typ == ( short ) MIFenster ) {
		ENUMLONGKEY ENL;
		ENL.eFcn = ( ENUMLONGKEYPROC ) SearchIdentObjects;
		ENL.eKey = (long ) (void *)m_hWnd;
		OBJPOINT OP;
		OP.pOBJ = m_pOBJ;
		OP.pIdent = m_pIDM;
		ENL.ePtr = &OP;
		DEX_EnumSelectedObjects (ENL);
	}

	if ( Typ == ( short ) MI2Fenster ) {
		ENUMLONGKEY ENL;
		ENL.eFcn = ( ENUMLONGKEYPROC ) SearchIdentObjects;
		ENL.eKey = (long ) (void *)m_hWndSec;
		OBJPOINT OP;
		OP.pOBJ = m_pOBJ;
		OP.pIdent = NULL;
		ENL.ePtr = &OP;
		DEX_EnumSelectedObjects (ENL);
	}

	return;
}
//--------------------------------------------------------------------------

void AttributExtension :: SuchePartner ( short Typ) 
{
	if ( !m_pOBJ)
		return;
	CTable t (*m_pOBJ);

	if ( Typ == ( short ) MI2Fenster ) {
		for ( t.First(); t.Valid(); t.Next() ) {
			OBJLock l(t);
			long ONr = l->Object();	
			l->SetPartner ( m_RootObject );
		}
	} else {
		if ( m_isCont ) {	// Container
			long Cont[4];
			long Data[2];
			Data[0] = 0L;
			Data[1] = m_lIdent2;
			ENUMRECHGEOMETRIE ERGI;
			memset (&ERGI, '\0', sizeof(ENUMRECHGEOMETRIE));
			ERGI.dwSize = sizeof(ENUMRECHGEOMETRIE);
			ERGI.iMode = ERGActSight;
			ERGI.eFcn = (RECHGEOMETRIEPROC) FindePartner;
			for ( t.First(); t.Valid(); t.Next() ) {
				OBJLock l(t);
				long ONr = l->Object();	
				DEX_GetObjContainer(ONr,Cont[0]);
				if ( m_lIntervall > 0L ) {
					long RDiff = ( Cont[1] - Cont[0] ) * m_lIntervall / 2L;
					long HDiff = ( Cont[3] - Cont[2] ) * m_lIntervall / 2L;
					double RWert = (double) RDiff * 0.01;
					double HWert = (double) HDiff * 0.01;
					Cont[0] = Cont[0] - (long) RWert;
					Cont[1] = Cont[1] + (long) RWert;
					Cont[2] = Cont[2] - (long) HWert;
					Cont[3] = Cont[3] + (long) HWert;
				}
				ERGI.lCont = &Cont[0];
			//	Objekte zählen
				ERGI.pData = &Data;
				DEX_EnumRechGeometrie( ERGI );
				l->SetPartner ( Data[0] );
			}
		} else {	// Merkmal
			MCVERGLEICH MCV;
			MCV.lObj = 0L;
			MCV.lMCode = m_lMCode;
			MCV.iTyp = m_iTyp;
			ENUMLONGKEY ENL;
			ENL.eFcn = ( ENUMLONGKEYPROC ) SucheMKPartner;
			ENL.eKey = m_lIdent2;
			for ( t.First(); t.Valid(); t.Next() ) {
				OBJLock l(t);
				char *pBuffer = FindeVergleichsText(l->Object(),m_lMCode);
				if ( !pBuffer)
					return;
				MCV.pVText = pBuffer;
				ENL.ePtr = &MCV;
				DEX_EnumIdentObjects (ENL);
				l->SetPartner ( MCV.lObj );
				DELETE ( pBuffer);
			}
		}
	}
	return;
}
//-----------------------------------------------------------------
char * AttributExtension :: FindeVergleichsText ( long ONr, long MCode) 
{
	if ( ONr == 0L || MCode == 0L )
		return NULL;
	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return NULL;

	TARGETMERKMAL TM;
	memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
	TM.lTarget = ONr;
	TM.imaxLen = _MAX_PATH-1;
	TM.iTTyp = TT_Objekt;
	TM.pMText = pBuffer;
	TM.lMCode = MCode;

	if( DEX_GetTextMerkmal ( TM )) 	// Merkmal gefunden
		return pBuffer;
		
	DELETE ( pBuffer);
	return NULL;
}
//-----------------------------------------------------------------
void AttributExtension :: TauscheMerkmal (void) 
{
	if ( !m_pMCode )
		return;
	if ( !m_pOBJ)
		return;
	CTable t (*m_pOBJ);
	for ( t.First(); t.Valid(); t.Next() ) {
		OBJLock l(t);
		long ONr = l->Object();	
		long Partner = l->Partner();
		if ( Partner > 0L ) {
			if ( Partner_hat_Merkmal(Partner)) {
				if ( Speichern_Merkmal ( ONr,Partner))
					l->SetFlag();
			}
		}
	}
	return;
}
//-----------------------------------------------------------------
void AttributExtension :: BildeMerkmal (void) 
{
	if ( !m_pMCode)
		return;
	if ( !m_pOBJ)
		return;
	CTable t (*m_pOBJ);
	for ( t.First(); t.Valid(); t.Next() ) {
		OBJLock l(t);
		long ONr = l->Object();	
		if ( Objekt_hat_Merkmal(ONr)) {
			if ( Zusammenstellen_Merkmal ( ONr))
				l->SetFlag();
		}
	}
	return;
}
//-----------------------------------------------------------------
void AttributExtension :: LoescheMerkmal (void) 
{
	if ( !m_pMCode )
		return;
	if ( !m_pOBJ)
		return;

	ulong Count = m_pOBJ->Count();
	short iRange= ( short ) Count;  

	if ( m_pInfo)
		DELETE ( m_pInfo);
	m_pInfo = new IdentInformation ( m_pW, ATTGAUGEBOX, RF(),"Löschen von Merkmalen",iRange);
	m_pInfo->Show();
	m_pInfo->Update();
	iRange = 0;

	CTable t (*m_pOBJ);
	for ( t.First(); t.Valid(); t.Next() ) {
		OBJLock l(t);
		long ONr = l->Object();	

		if ( Loeschen_Merkmal ( ONr))
			l->SetFlag();

		iRange++;
		if ( m_pInfo->Break() ) {
			HWND hwnd = m_pInfo->Handle();
			MessageBox ( hwnd ,
			 "Recherche wurde abgebrochen !!!", 
			 "Löschen von Merkmalen", 
			 MB_OK|MB_ICONEXCLAMATION);
			DELETE ( m_pInfo );
			return;
		}
		m_pInfo->SetText ( iRange);

	}
	DELETE ( m_pInfo);
	return;
}
//-----------------------------------------------------------------
void AttributExtension :: ObjektKontrolle (void) 
{
	if ( !m_pOBJ)
		return;
	CEierUhr Wait( MWind());
	CTable t (*m_pOBJ);
	ulong Count = m_pOBJ->Count();
	long *pPos = new long [ Count + 1 ];
	long *pNeg = new long [ Count + 1 ];
	if ( pPos == NULL || pNeg == NULL ) {
		DELETE ( pPos);
		DELETE ( pNeg);
	}
	*pPos = 0L;
	*pNeg = 0L;
	long Neg = 0L;
	long Pos = 0L;
	for ( t.First(); t.Valid(); t.Next() ) {
		OBJLock l(t);
		long ONr = l->Object();	
		if ( l->ObjFlag()) {
			Pos++;
			*( pPos + Pos ) = ONr;
		} else {
			Neg++;
			*( pNeg + Neg ) = ONr;
		}
	}
	short Flag = ROSortObjNr;
	if ( Pos > 0L ) {
		*pPos = Pos;
		CreateORWindow ( Flag, 100, 100, pPos, "Verarbeitung positiv", 0, 255, 255);
	}
	if ( Neg > 0L ) {
		*pNeg = Neg;
		CreateORWindow ( Flag, 500, 100, pNeg, "Verarbeitung negativ", 255, 255, 0);
	}

	DELETE ( pPos);
	DELETE ( pNeg);	
}
//-----------------------------------------------------------------
void AttributExtension :: ZeigeAlleFenster (void) 
{
	if ( !m_pMVergl)
		return;
	CEierUhr Wait( MWind());
	CTable t (*m_pMVergl);
	short L = 50;
	short B = 100; 
	for ( t.First(); t.Valid(); t.Next() ) {
		VClassLock l(t);
		OBJTree *pObj = l->Obj();
		if ( !pObj)
			continue;
		long Count = (long) pObj->Count();

		long *pPos = new long [ Count + 1 ];
		if ( !pPos ) {
			continue;
		}
		*pPos = 0L;
		long Number = 0L;

		CTable d ( *pObj);
		for ( d.First(); d.Valid(); d.Next() ) {
			OBJLock e(d);
			Number++;
			*(pPos+Number) = e->Object();
		}
		short Flag = ROSortObjNr;
		if ( Number > 0L ) {
			*pPos = Number;
			L = L + 50;
			CreateORWindow ( Flag, L, B, pPos, l->Merkmal(), 0, 255, 255);
		}
		DELETE ( pPos);
	}

}
//--------------------------------------------------------------------------
Bool AttributExtension :: HideORHwnd (void) 
{

	if ( m_pHWNDTree != NULL && m_pHWNDTree->Count() > 0 ) {
		CTable t(*m_pHWNDTree);
		for ( t.First();t.Valid();t.Next())
			t.Delete();
	}

	m_isORHwnd = 0;

	return TRUE;
}

//------------------------------------------------------------------
void AttributExtension :: AddORHwnd (void) 
{
	if ( m_pHWNDTree == NULL )
		m_isORHwnd = 0;
	else {
		if ( m_pHWNDTree->Count() == 0 )
			m_isORHwnd = 0;
		else
			m_isORHwnd++;
	}

return;
}

void AttributExtension :: DeleteORHwnd (void) 
{
	if ( m_pHWNDTree == NULL )
		m_isORHwnd = 0;
	else {
		if ( m_pHWNDTree->Count() == 0 )
			m_isORHwnd = 0;
		else
			m_isORHwnd--;
	}

	if ( m_isORHwnd <= 0 ) {
		HideORHwnd( );
	}
		
return;
}

//------------------------------------------------------------------
Bool AttributExtension :: Pruefe_2_ORHwnd ( void ) 
{
	if ( m_pHWNDTree == NULL )
		return FALSE;

	CTable t(*m_pHWNDTree); 
	if ( m_pHWNDTree->Count() != 2 )
		return FALSE;

	t.First();
	SHWNDLock l(t);
	if ( m_hWnd == l->Shwnd()) {
		t.Next();
		SHWNDLock l(t);
		m_hWndSec = l->Shwnd();
	} else {
		m_hWndSec = l->Shwnd();
	}

	return TRUE;
}

//	ORFenster erstellen-----------------------------------------
void AttributExtension :: CreateORWindow ( short Flag, short PX, short PY, long *pObjL, char *pCaption, short RF, short GF, short BF)
{
	if ( *pObjL <= 0 )
		return;

	POINT PNT;
	PNT.x = PX;
	PNT.y = PY;


	CREATEOBJEKTINFOEX COI;
	memset ( &COI, '\0', sizeof (COI) );
	COI.dwSize = sizeof(COI);
	COI.lpCaption = pCaption;
	COI.plObjs = pObjL+1;
	COI.iNumObjs = short( *pObjL);
	COI.cMColor = RGB(RF,GF,BF);
	COI.pntPos = PNT;
	COI.m_iFlags = Flag;

	RegisterNotification (DEX_QUERYRECHOBJECT);
	DEX_CreateObjektInfo( COI );
	UnRegisterNotification (DEX_QUERYRECHOBJECT);

}
//--------------------------------------------------------------------------
//------Merkmal eines Objektes vorhanden/nicht vorhanden----------

Bool AttributExtension :: Objekt_hat_Merkmal (long ONr )
{
	if( !m_pMCode)
		return FALSE;

	long NR = *m_pMCode;


	TARGETMERKMAL TM;
	memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
	TM.lTarget = ONr;
	TM.imaxLen = NULL;
	TM.iTTyp = TT_Objekt;
	TM.pMText = NULL;
    
	for ( long i = 0; i < NR; i++ ) {

		TM.lMCode = *(m_pMCode+i+1);

		if( !DEX_GetTextMerkmal ( TM )) 	// Merkmal gefunden
			return FALSE;
		
	}
	return TRUE;		//Frage:Mk in Objekt

}
//--------------------------------------------------------------------------

Bool AttributExtension :: Partner_hat_Merkmal (long ONr )
{
	if( !m_pMCode)
		return FALSE;

	long NR = *m_pMCode;


	TARGETMERKMAL TM;
	memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
	TM.lTarget = ONr;
	TM.imaxLen = NULL;
	TM.iTTyp = TT_Objekt;
	TM.pMText = NULL;
    
	for ( long i = 0; i < NR; i++ ) {

		TM.lMCode = *(m_pMCode+2*i+2);	// PartnerCode

		if( !DEX_GetTextMerkmal ( TM )) 	// Merkmal gefunden
			return FALSE;
		
	}
	return TRUE;		//Frage:Mk in Objekt

}
//--------------------------------------------------------------------------
//------Merkmal eines Objektes anderem Objekt bergeben----------
Bool AttributExtension :: Speichern_Merkmal (long Wohin, long Woher )
{
	if( !m_pMCode)
		return FALSE;
	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return FALSE;

	// MerkmalsWert holen
	TARGETMERKMAL tm;

	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = Woher;		// ObjektNummer
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuffer;		// Puffer
	tm.iTTyp = TT_Objekt;

	long NR = *m_pMCode;
	for ( long i = 0; i < NR; i++ ) {

		tm.lMCode = *(m_pMCode+2*i+2);		// MerkmalsCode

		if( !DEX_GetTextMerkmal ( tm )) {
			DELETE ( pBuffer);
			return FALSE;
		}

		tm.lTarget = Wohin;		// ObjektNummer
		tm.lMCode = *(m_pMCode+2*i+1);		// neuer MerkmalsCode

		if ( DEX_ModTextMerkmal (tm) != EC_OKAY ) {
			DELETE ( pBuffer);
			return FALSE;
		}
	}
	DELETE ( pBuffer);
	return TRUE;

}
//------Merkmal eines Objektes l”schen----------
Bool AttributExtension :: Loeschen_Merkmal (long ONr )
{
	if( !m_pMCode)
		return FALSE;

	// MerkmalsWert holen
	TARGETMERKMAL tm;

	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = ONr;		// ObjektNummer
	tm.imaxLen = NULL;
	tm.pMText = NULL;		// Puffer
	tm.iTTyp = TT_Objekt;
	long NR = *m_pMCode;
	for ( long i = 0; i < NR; i++) {
		tm.lMCode = *(m_pMCode+i+1);		// MerkmalsCode

		if( DEX_GetTextMerkmal ( tm )) {
			if ( DEX_ModTextMerkmal (tm) != EC_OKAY ) {
				return FALSE;
			}
		}

	}
	return TRUE;

}
//------Merkmale eines Objektes aus MKode zusammenstellen----------
Bool AttributExtension :: Zusammenstellen_Merkmal (long ONr )
{
	if( !m_pMCode)
		return FALSE;
	char *pBuffer = new char [_MAX_PATH];

	if ( !pBuffer)
		return FALSE;

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	long lMCode = *(m_pMCode+1);
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = ONr;		// ObjektNummer
	tm.lMCode = lMCode;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuffer;		// Puffer
	tm.iTTyp = TT_Objekt;

	if( !DEX_GetTextMerkmal ( tm )) {
		DELETE ( pBuffer);
		return FALSE;
	}

//---------------------Zusammensetzen----------------------
	if ( *pBuffer == '\0') {
		DELETE ( pBuffer);
		return FALSE;
	}
	if ( strlen (pBuffer ) < 9 ) {
		DELETE ( pBuffer);
		return FALSE;
	}

	long MKode = lMCode;
// Nummer 1
	MKode++;
	if ( !Konstruiere_Merkmal(ONr,MKode,pBuffer,0,1)) {
		DELETE (pBuffer);
		return FALSE;
	}

// Nummer 2
	MKode++;
	if ( !Konstruiere_Merkmal(ONr,MKode,pBuffer,1,1)) {
		DELETE (pBuffer);
		return FALSE;
	}
// Nummer 3
	MKode++;
	if ( !Konstruiere_Merkmal(ONr,MKode,pBuffer,2,3)) {
		DELETE (pBuffer);
		return FALSE;
	}
// Nummer 4
	MKode++;
	if ( !Konstruiere_Merkmal(ONr,MKode,pBuffer,5,1)) {
		DELETE (pBuffer);
		return FALSE;
	}
// Nummer 5
	MKode++;
	if ( !Konstruiere_Merkmal(ONr,MKode,pBuffer,6,1)) {
		DELETE (pBuffer);
		return FALSE;
	}
// Nummer 6
	MKode++;
	if ( !Konstruiere_Merkmal(ONr,MKode,pBuffer,7,1)) {
		DELETE (pBuffer);
		return FALSE;
	}
// Nummer 7
	MKode++;
	if ( !Konstruiere_Merkmal(ONr,MKode,pBuffer,8,1)) {
		DELETE (pBuffer);
		return FALSE;
	}

//----------------------------------------------------------------

	DELETE ( pBuffer);
	return TRUE;

}
//---------------------------------------------------------------------------
//------Merkmale eines Objektes aus MKode zusammenstellen----------
Bool AttributExtension :: Konstruiere_Merkmal (long ONr, long MKode, char *pBuffer,unsigned int p, unsigned int l) 
{
	if( MKode == 0L || ONr <= 0L )
		return FALSE;
	if (!pBuffer || *pBuffer == '\0')
		return FALSE;

	char *pBuf = new char [_MAX_PATH];

	if ( !pBuf)
		return FALSE;
	*pBuf = '\0';
	strncpy (pBuf,pBuffer+p,l);
	*(pBuf+l) = '\0';

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = ONr;		// ObjektNummer
	tm.lMCode = MKode;		// MerkmalsCode
	tm.imaxLen = (short) l;
	tm.pMText =pBuf;		// Puffer
	tm.iTTyp = TT_Objekt;
	if ( DEX_ModTextMerkmal (tm) == EC_OKAY ) {
		DELETE ( pBuf);
		return TRUE;
	} 
	DELETE ( pBuf);
	return FALSE;
}
//--------------------------------------------------------------------------
//------Selektierte MKodes Merkmalswerte zuordnen ----------
Bool AttributExtension :: MerkmalsZuordnung ( void ) 
{
	if ( !m_pMCode)
		return FALSE;
	if ( !m_pIDM )
		return FALSE;

	if ( m_pMKM )
		DELETE ( m_pMKM);
	m_pMKM = new IDMTree;

	CTable t ( *m_pMKM);
	short Typ = 0;
	for ( long i = 0; i < *m_pMCode; i++ ) {
		IDMCreator IDMCr ( *m_pMKM );
		ContCreate ( IDMCr, IDM ) ( *(m_pMCode+i+1) , Typ);
	}

	DefineMerkmalsWert DMW ( MWind(),ATTRIBUTZUORDNUNG, RF(), m_pMKM);
	DMW.Show();
	if ( DMW.Result() == 0 )
		return FALSE;
	return TRUE;
}
//-----------------------------------------------------------------------
//------Selektierte MKodes Merkmalswerte zuordnen ----------
void AttributExtension :: MerkmalsTest ( void ) 
{

	if ( !m_pMCode )
		return;
	if ( !m_pOBJ)
		return;
	if ( !m_pMKM )
		return;
	ulong Count = m_pOBJ->Count();
	short iRange= ( short ) Count;  

	if ( m_pInfo)
		DELETE ( m_pInfo);
	m_pInfo = new IdentInformation ( m_pW, ATTGAUGEBOX, RF(),"Merkmalsanalyse",iRange);
	m_pInfo->Show();
	m_pInfo->Update();
	iRange = 0;

	CTable t (*m_pOBJ);
	for ( t.First(); t.Valid(); t.Next() ) {
		OBJLock l(t);
		long ONr = l->Object();	
		if ( Testen_Merkmal ( ONr))
			l->SetFlag();
		iRange++;
		if ( m_pInfo->Break() ) {
			HWND hwnd = m_pInfo->Handle();
			MessageBox ( hwnd ,
			 "Recherche wurde abgebrochen !!!", 
			 "Merkmalsanalyse", 
			 MB_OK|MB_ICONEXCLAMATION);
			DELETE ( m_pInfo );
			return;
		}
		m_pInfo->SetText ( iRange);

	}
	DELETE ( m_pInfo);
	return;
}
//--------------------------------------------------------------------------
Bool AttributExtension :: Testen_Merkmal (long ONr )
{
	if ( !m_pMKM)
		return FALSE;

	CTable t(*m_pMKM);
	char *pBuff1 = new char [_MAX_PATH];
	char *pBuff2 = new char [_MAX_PATH];
	if ( !pBuff1 || !pBuff2 ) {
		DELETE ( pBuff1);
		DELETE ( pBuff2);
		return FALSE;
	}

	// MerkmalsWert holen
	TARGETMERKMAL tm;

	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = ONr;		// ObjektNummer
	tm.iTTyp = TT_Objekt;

	for ( t.First(); t.Valid(); t.Next() ) {
		IDMLock l(t);
		tm.lMCode = l->Ident();		// MerkmalsCode
		short iModus = l->Modus();	
		tm.imaxLen = _MAX_PATH;
		tm.pMText = pBuff2;		// Puffer

		if ( !DEX_GetTextMerkmal (tm) ) {
			DELETE ( pBuff1);
			DELETE ( pBuff2);
			if ( iModus != (short) MIExistiertNicht )
				return FALSE;
		} else {

			if ( iModus == (short) MIExistiertNicht )
				return FALSE;
			if ( l->Text()) {   
			   strcpy ( pBuff1, l->Text() );
		
			   if ( *pBuff1 != '\0') {
				if ( !Vergleiche_Merkmal(iModus,pBuff1,pBuff2) ) {
					DELETE ( pBuff1);
					DELETE ( pBuff2);
					return FALSE;
				}
			   }
			} else {
				if ( iModus != (short)MIExistiert && iModus != (short)MIExistiertNicht) {
					DELETE ( pBuff1);
					DELETE ( pBuff2);
					return FALSE;
				}
			}
		}
	}
	DELETE ( pBuff1);
	DELETE ( pBuff2);

	return TRUE;
}
//--------------------------------------------------------------------------

//------Merkmal eines Objektes vergleichen/abtesten----------
Bool AttributExtension :: Vergleiche_Merkmal (short iModus, char *pIst, char *pHaben )
{

	if ( iModus == (short) MIExistiert || iModus == (short) MIExistiertNicht)
		return TRUE;

	if ( !pIst || !pHaben)
		return FALSE;

	if ( *pIst == '\0' || *pHaben == '\0' )
		return FALSE;

// Verschiedene Modi
// Modi von MerkmalRecherchen
//	MIExistiert		0	//Merkmal vorhanden.
//	MIExistiertNicht	1	//Merkmal nicht vorhanden.
//	MIExakt			2	//Merkmal vollst.
//	MITeilMenge		3	//Teilmenge
//	MINichtVorhanden	4	//inverse Recherche
//	MIWertAnfang		5	//Zeichen am Anfang
//	MIWertEnde		6	//Zeichen am Ende
//	MIWertLaenge		7	//ZeichenLaenge

	
	if ( iModus == (short) MIExakt ) {
		int LenH = strlen ( pHaben );
		int LenI = strlen ( pIst );	//Suchtext
		if ( LenI != LenH )
			return false;	
		if ( strcmp ( pIst,pHaben) == 0 ) 
			return TRUE;
		else 
			return FALSE;
	}

	if ( iModus == (short) MITeilMenge ) {	// TeilString
		int LenH = strlen ( pHaben );
		int LenI = strlen ( pIst );	//Suchtext
		if ( LenI > LenH )
			return false;	
		if ( LenI == LenH ) {
			if ( strcmp ( pIst,pHaben) == 0 )
				return TRUE;
			else
				return FALSE;
		}	

		for ( int i = 0; i < LenH-LenI; i++) {
			if ( *(pHaben+i) == *(pIst) ) {
				if ( strncmp ( pIst,pHaben+i,LenI) == 0 )
					return TRUE;
			}
		}
		return FALSE;
	}

	if ( iModus == (short) MINichtVorhanden ) {	// TeilString
		int LenH = strlen ( pHaben );
		int LenI = strlen ( pIst );		// Suchstring
		if ( LenI > LenH )
			return true;
		
		if ( LenI == LenH ) {
			if ( strcmp ( pIst,pHaben) == 0 )
				return false;
			else
				return true;
		}

		for ( int i = 0; i < LenH-LenI; i++) {
			if ( *(pHaben+i) == *(pIst) ) {
				if ( strncmp ( pIst,pHaben+i,LenI) == 0 )
					return FALSE;
			}
		}
		return TRUE;
	}


	if ( iModus == (short) MIWertAnfang ) {	// TeilString am Anfang
		int LenH = strlen ( pHaben );
		int LenI = strlen ( pIst );
		if ( LenI > LenH )
			return FALSE;
		if ( strncmp ( pIst,pHaben,LenI) == 0 )
			return TRUE;
		else
			return FALSE;
	}

	if ( iModus == (short) MIWertEnde ) {	// TeilString am Ende
		int LenH = strlen ( pHaben );
		int LenI = strlen ( pIst );
		if ( LenI > LenH )
			return FALSE;
		int Len = LenH - LenI;
		if ( strncmp ( pIst,pHaben+Len,LenI) == 0 )
			return TRUE;
		else
			return FALSE;
	}

	if ( iModus == (short) MIWertLaenge ) {	// Zeichenlaenge
		int LenH = strlen ( pHaben );
		unsigned char c;
		char *pTst = new char [_MAX_PATH];
		int MaxI,MinI;
		MaxI = -1;
		MinI = -1;
		if ( pTst ) {
			*pTst = '\0';
			int LenI = strlen ( pIst);
			int j = 0;
			for ( int i = 0; i < LenI ; i++ ) {
				c = *(pIst +i);
				if ( isdigit(c)) {
					*(pTst+j) = c;
					j++;
				} else {
					if ( j > 0 ) {
						*(pTst+j) = '\0';
						if ( MinI == -1 )
							MinI = atoi ( pTst);
						else {
							if ( MaxI == -1 )
								MaxI = atoi ( pTst);
						}
						*pTst = '\0';
						j = 0;		
					}
				}
			}
			if ( j > 0 ) {
				*(pTst+j) = '\0';
				if ( MinI == -1 )
						MinI = atoi ( pTst);
				else  {
					if ( MaxI == -1 )
						MaxI = atoi ( pTst);
				}	
			}
			
			
			if ( MinI == -1 && MaxI == -1 )
				return FALSE;
			if ( MaxI == -1 )
				MaxI = MinI;
			if ( MinI > MaxI ) {
				LenI = MinI;
				MinI = MaxI;
				MaxI = LenI;
			}
//------------------Minimum--------------------------
			if ( MinI > LenH )
				return FALSE;
//------------------Maximum----------------------------
			if ( MaxI < LenH )
				return FALSE;
			else
				return TRUE;

			DELETE ( pTst);
		}
	}

	return FALSE;
}
//------Identifikatoren von selektierten Objekten in Fenster ----------
Bool AttributExtension :: IdentInFenster ( HWND hWnd )
{

	if ( m_pIDM )
		DELETE ( m_pIDM );
	m_pIDM = new IDMTree;
	if ( !m_pIDM)
		return FALSE;
	short Typ = 0;
	Typ = OTPunkt | OTLinie | OTFlaeche | OTText;
	ENUMNOKEYLONGEX ELK;
	memset (&ELK,'\0',sizeof(ENUMNOKEYLONGEX) );
	ELK.eFcn = ( ENUMNOKEYLONGEXPROC) AufbauIDListe;
	ELK.eData = (DWORD) Typ;
	ELK.ePtr = m_pIDM;
	DEXOR_EnumIdentsSelectedEx(hWnd,ELK);
	return TRUE;
}

//-------------------------------------------------------------------------
void AttributExtension :: SetTreeInformation ( void )
{
	if ( m_pIDM != NULL )
		DELETE ( m_pIDM);
	m_pIDM = new IDMTree;

	if ( m_pOBJ != NULL )
		DELETE ( m_pOBJ);
	m_pOBJ = new OBJTree;

	if ( m_pMKM != NULL )
		DELETE ( m_pMKM);
	m_pMKM = new IDMTree;

	return;
}
//-------------------------------------------------------------------------
void AttributExtension :: LadeObjektKlasse ( void )
{
	if ( !m_pIDM)
		return;

	CEierUhr Wait ( MWind());

	short Typ = OTText | OTLinie | OTFlaeche | OTPunkt ;

	ENUMTEXTKEYEX ENTex;
	ENTex.eKey = NULL;		// NULL = aktuelle Sicht
	ENTex.eFcn = ( ENUMTEXTKEYEXPROC) StoreIdentWithTyp;
	ENTex.ePtr = m_pIDM;
	ENTex.eData = ( DWORD ) Typ;	
	DEX_EnumSightIdentsEx(ENTex);

	return;
}
//-------------------------------------------------------------------------
void AttributExtension :: VerdichteObjektKlasse ( void )
{
	if ( !m_pIDM)
		return;

	{
	CTable t ( *m_pIDM);
	short RefGi;
	
	for (t.First(); t.Valid(); t.Next() ) {
		RefGi = 0;
		{
		IDMLock l(t);
		if ( l) {
			RefGi = l->RefTyp();
		}
		}
		
		if ( !RefGi )
			t.Delete();
	}
	m_pIDM->Optimize();
	}

	return;
}
//-------------------------------------------------------------------------
Bool AttributExtension :: FindeKriterium ( void )
{
	if ( !m_pIDM)
		return false;

	if ( !m_pMCode)
		return false;

	{
	DefineObjClassErbe DOE ( m_pW,ATTRIBUTAUSWAHL, RF(), m_pIDM, m_pMCode);
	DOE.Show();
	short iFct = DOE.Result();
	if ( DOE.Result() == 1 ) {
		m_lIdent2 = DOE.Ident2();
		m_iTyp = DOE.GiTyp();
		DELETE ( m_pMCode);
		m_pMCode = DOE.MCode();
		m_lIntervall = DOE.Intervall();
		m_lMCode = DOE.MkIdent();
		m_isCont = DOE.isContainer();
	} else {
		return false;
	}
	}

	VerdichteObjektKlasse();

	return true;

}
//--------------------------------------------------------------------------
//------Selektierten MKode neue Merkmalswerte zuordnen ----------
void AttributExtension :: Text_Und_Merkmal ( void ) 
{
	if ( !m_pOBJ)
		return;
	if ( !m_pMText || *m_pMText == '\0')
		return;
	ulong Count = m_pOBJ->Count();
	short iRange= ( short ) Count;  

	if ( m_pInfo)
		DELETE ( m_pInfo);
	m_pInfo = new IdentInformation ( m_pW, ATTGAUGEBOX, RF(),"Merkmalsanalyse",iRange);
	m_pInfo->Show();
	m_pInfo->Update();
	iRange = 0;

	CTable t (*m_pOBJ);
	for ( t.First(); t.Valid(); t.Next() ) {
		OBJLock l(t);
		long ONr = l->Object();	
		if ( SetzeText ( ONr))
			l->SetFlag();
		iRange++;
		if ( m_pInfo->Break() ) {
			HWND hwnd = m_pInfo->Handle();
			MessageBox ( hwnd ,
			 "Recherche wurde abgebrochen !!!", 
			 "Merkmalsanalyse", 
			 MB_OK|MB_ICONEXCLAMATION);
			DELETE ( m_pInfo );
			return;
		}
		m_pInfo->SetText ( iRange);

	}
	DELETE ( m_pInfo);
	return;
}
//--------------------------------------------------------------------------
//------Text vor Merkmal setzen ----------
Bool AttributExtension :: SetzeText ( long ONr ) 
{

	if ( *(m_pMCode+1) == 0L || !m_pMText || *m_pMText == '\0') {
		return false;
	}
	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return false;

	char *pBuff = new char [_MAX_PATH];
	if ( !pBuff) {
		DELETE ( pBuffer);
		return false;
	}
	char *pMText = new char [_MAX_PATH];
	if ( !pMText) {
		DELETE ( pBuffer);
		DELETE ( pBuff);
		return false;
	}

	// MerkmalsWert holen
	TARGETMERKMAL tm;

	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = ONr;		// ObjektNummer
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuffer;		// Puffer
	tm.iTTyp = TT_Objekt;

	tm.lMCode = *(m_pMCode+1);		// MerkmalsCode

	if( !DEX_GetTextMerkmal ( tm )) {	// MK nicht da -> neuanlegen
		*pBuffer = '\0';
		tm.imaxLen = _MAX_PATH;
	}

//------Umklassifizieren

	if ( strcmp(m_pMText, "ID=")) {
		ModId ( ONr, m_pMText);
		DELETE ( pBuffer);
		DELETE ( pBuff);
		DELETE ( pMText);
		return true;
	}



// Text oder nicht Text, Dass ist hier die Frage 
	char *pNewText;

	if ( strcmp(m_pMText, "substr("))
		pNewText = Substring ( ONr, m_pMText );

	if ( pNewText ) {
		strcpy (pMText, pNewText);
//		strcpy (pBuff, pNewText);
		DELETE ( pNewText);
	} else {
		DELETE ( pBuffer);
		DELETE ( pBuff);
		DELETE ( pMText);
		return false;
	}

	if ( m_isVorn ) {
		strcpy ( pBuff, pMText);
		strcat ( pBuff, pBuffer);
	} else {
		strcpy ( pBuff, pBuffer);
		strcat ( pBuff, pMText);
	}


	tm.pMText = pBuff;	

	if ( DEX_ModTextMerkmal (tm) != EC_OKAY ) {
		DELETE ( pBuffer);
		DELETE ( pBuff);
		DELETE ( pMText);
		return false;
	}

	DELETE ( pBuffer);
	DELETE ( pBuff);
	DELETE ( pMText);

	return true; 

}
//------Text vor Merkmal setzen ----------
char * AttributExtension :: Substring ( long ONr, char *pOText ) 
{

	char *ptr = strchr ( pOText, '(');
	if (! ptr ) 
		return NULL;
	int Len = strlen ( pOText);

	char *pText = new char [Len];
	if ( !pText )
		return NULL;

	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return NULL;

	strcpy ( pText,ptr+1);
	ptr = pText;

	char *pMCode,*pStart,*pLaenge;
	int iPos,iLaenge;

	short iBase = DEX_GetMkBase();

	pMCode = strtok(ptr,",");
	pStart = strtok(NULL,",");
	pLaenge = strtok (NULL,",");
	iPos = atoi(pStart);
	iLaenge = atoi ( pLaenge);
	
	long lMCode = 0L;

	if ( iBase == 16 ) {
		lMCode = strtoul ( pMCode,NULL,16);
	} else {
		lMCode = atol ( pMCode);
	}

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = ONr;		// ObjektNummer
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuffer;		// Puffer
	tm.iTTyp = TT_Objekt;

	tm.lMCode = lMCode;		// MerkmalsCode

	if( !DEX_GetTextMerkmal ( tm )) {
		DELETE ( pBuffer);
		DELETE ( pText);
		return NULL;
	}
	char *pExp = new char [_MAX_PATH];
	if ( !pExp) {
		DELETE ( pBuffer);
		DELETE (pText);
		return NULL;
	}
	*pExp = '\0';
	ptr = pBuffer+iPos-1;
	*(ptr+iLaenge) = '\0';
	strcpy ( pExp, ptr);
	DELETE ( pBuffer);
	DELETE ( pText);
	return pExp;
		
}
//---------------------------------------------------------------------------
//------Umklassifizieren ----------
void AttributExtension :: ModId ( long ONr, char *pOText ) 
{

	char *ptr = strchr ( pOText, '=');
	if (! ptr ) 
		return ;

	ptr++;
	short iBase = DEX_GetMkBase();
	long lMCode = 0L;

	if ( iBase == 16 ) {
		lMCode = strtoul ( ptr,NULL,16);
	} else {
		lMCode = atol ( ptr);
	}

	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return ;

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = ONr;		// ObjektNummer
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuffer;		// Puffer= Identifikator
	tm.iTTyp = TT_Objekt;

	tm.lMCode = lMCode;		// MerkmalsCode

	if( !DEX_GetTextMerkmal ( tm )) {
		DELETE ( pBuffer);
		return ;
	}

	long lIDCode = 0L;

	iBase = DEX_GetIdBase();

	ulong uIdent = (ulong) lIDCode;
	IdentFromClassX ( pBuffer, &uIdent);
	lIDCode = (long) uIdent;
/*-----------------23.1.97
	if ( iBase == 16 ) {
		lIDCode = strtoul ( pBuffer,NULL,16);
	} else {
		lIDCode = atol ( pBuffer);
	}
-----------------*/

//-Umklassifizieren
	MODOBJIDENT id;
	id.dwSize = sizeof(MODOBJIDENT);
	id.lONr = ONr;
	id.lNewIdent = lIDCode;
	if ( DEX_GetObjectType(ONr) == OGPunkt )
		id.iMode = MODIDENT_PUNKT;
	if ( DEX_GetObjectType(ONr) == OGLinie )
		id.iMode = MODIDENT_LINIE;
	if ( DEX_GetObjectType(ONr) == OGFlaeche )
		id.iMode = MODIDENT_FLAECHE;

	DEX_ModObjectIdent ( id);

	DELETE ( pBuffer);
	return;
		
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT SearchObjects ( long ONr, DWORD GTyp , void *pData)
  {

	short Type = DEX_GetObjectType(ONr);
//	Nur Linien und Flaechen
//	if ( Type == OGLinie || Type == OGFlaeche ) {
	   CTable t(*( OBJTree * )pData);
	   if ( !t.Find (&ONr) ) {
		OBJECTTYP ObjStr;
		ObjStr.lIdent = DEX_GetObjIdent ( ONr );
		if ( Type == OGLinie )
			ObjStr.iGITyp =OTLinie;
		if ( Type == OGFlaeche )
			ObjStr.iGITyp =OTFlaeche;
		if ( Type == OGPunkt )
			ObjStr.iGITyp =OTPunkt;
		if ( Type == OGText )
			ObjStr.iGITyp =OTText;
		if ( GTyp & ObjStr.iGITyp ) {
			OBJCreator OBJCr ( * (OBJTree * )pData );
			ContCreate ( OBJCr, OBJ ) ( ONr, &ObjStr );
		}
	   }
//	}
	return TRUE;
  }

//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT SearchIdentObjects ( long ONr, Bool , void *pData)
  {
	long Ident = DEX_GetObjIdent(ONr);
   	IDMTree *pVgl = ((OBJPOINT *)pData)->pIdent;	
	short GiTyp = 0;
	if ( pVgl ) { 
		CTable d ( *pVgl);
		if ( !d.Find (&Ident))
			return TRUE;
		IDMLock m(d);
		GiTyp = m->RefTyp();
	}

	short Type = DEX_GetObjectType(ONr);  
	OBJECTTYP ObjStr;	
	ObjStr.iGITyp = 0;

	if ( Type == OGLinie )
		ObjStr.iGITyp =OTLinie;
	if ( Type == OGFlaeche )
		ObjStr.iGITyp =OTFlaeche;
	if ( Type == OGPunkt )
		ObjStr.iGITyp =OTPunkt;
	if ( Type == OGText )
		ObjStr.iGITyp =OTText;

	if ( GiTyp & ObjStr.iGITyp == 0 )
			return TRUE;

	CTable t( * ((OBJPOINT * ) pData)->pOBJ );

	if ( !t.Find (&ONr) ) {
		OBJCreator OBJCr ( * ((OBJPOINT * )pData)->pOBJ );
		ContCreate ( OBJCr, OBJ ) ( ONr, &ObjStr );
	}

	return TRUE;
  }

//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT EnumObjectsWithStatus ( long ONr, Bool , void *pData)
  {

	short Typ = DEX_GetObjectType(ONr);  
	long Ident = DEX_GetObjIdent(ONr);
    short Type;
    
	if ( Typ == OGLinie )
		Type =OTLinie;
	if ( Typ == OGFlaeche )
		Type =OTFlaeche;
	if ( Typ == OGPunkt )
		Type =OTPunkt;
	if ( Typ == OGText )
		Type =OTText;

	CTable t(*( IDMTree * )pData);
	if ( !t.Find (&Ident) ) {
		IDMCreator IDMCr ( * (IDMTree * )pData );
		ContCreate ( IDMCr, IDM ) ( Ident , Type);
	} else {
		IDMLock l(t);
		l->SetGiTyp(Type) ;
	}

	return TRUE;
  }

//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT FindePartner ( long ONr, Bool , void *pData)
 {
	(* ( long *) pData ) = 0L;
	long Ident = DEX_GetObjIdent(ONr);
	long Vgl = *((long *) pData+1);
	if ( Ident != Vgl )
		return TRUE;
	(* ( long *) pData ) = ONr;
		return FALSE;
 }
//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheMKPartner ( long ONr, Bool , void *pData)
 {
	char *pVText = ((MCVERGLEICH *)pData)->pVText;	
	long MCode = ((MCVERGLEICH *)pData)->lMCode;
	((MCVERGLEICH *)pData)->lObj = 0L;
	short iTyp = ((MCVERGLEICH *)pData)->iTyp;	
	short iOTyp = DEX_GetObjectType ( ONr );
	short iVTyp;


//	FestStellen des GI-Typs--------------------------	

	if ( iOTyp == OGPunkt )
		iVTyp = OTPunkt;
	if ( iOTyp == OGLinie )
		iVTyp = OTLinie;
	if ( iOTyp == OGFlaeche )
		iVTyp = OTFlaeche;
	if ( iOTyp == OGText )
		iVTyp = OTText;

	if ( iVTyp != iTyp ) 
		return true;


	char *pBuffer = new char [_MAX_PATH];
	if ( !pBuffer)
		return TRUE;

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = ONr;		// ObjektNummer
	tm.lMCode = MCode;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH - 1;
	tm.pMText =pBuffer;		// Puffer
	tm.iTTyp = TT_Objekt;

	if( !DEX_GetTextMerkmal ( tm )) {
		DELETE ( pBuffer);
		return TRUE;
	}
	if ( strcmp ( pBuffer, pVText) == 0 ) {
		((MCVERGLEICH *)pData)->lObj = ONr;
		DELETE ( pBuffer);
		return FALSE;
	}
	DELETE ( pBuffer);
	return TRUE;

 }
//--------------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT AufbauIDListe ( long Ident, DWORD Typ , void *pData)
 {
	CTable t(*( IDMTree * )pData);
	if ( !t.Find (&Ident) ) {
		short Type = (short) Typ;
		IDMCreator IDMCr ( * (IDMTree * )pData );
		ContCreate ( IDMCr, IDM ) ( Ident , Type);
	}
	return TRUE;
 }
//--------------------------------------------------------------------------------
//-----------ATTRIBUT.CXX
