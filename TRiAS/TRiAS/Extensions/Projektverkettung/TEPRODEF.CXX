// File: TEPRODEF.CXX

#include "tprojp.hxx"
#include "tproject.h"
#include "defproj.h"

#include "menukey.hxx"
#include "txtedit.hxx"
#include "teprodef.hxx"
#include "TPROJECT.HXX"

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

TProjectDefine :: TProjectDefine (pWindow pW, uint res, ResourceFile &RF, char *pProject, PROJTree *pPROJ, MMenuTree *pMenu , char * pInput)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _TPDirectory (this,IDS_TPROJECTSDIR),
	       _TProjectKey (this,IDS_TPROJECTKEY),
	       _RF (RF),
	       _TProjects (this,IDLB_TPROJECTS),
	       _TPDefine ( this, IDB_TPROJECTSEARCH),
	       _TPNew ( this, IDC_BUTTONNEW),
	       _TPDelete ( this, IDB_TPROJECTDELETE),
	       _TPStore ( this, IDB_TPROJECTSTORE),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_pW = pW;
//	pW->Disable();
	_pRefTP = NULL;
	_pRefTP = new char [_MAX_PATH];

	_pInput = NULL;
	_isOR = false;

	if ( pInput ) {
		_pInput = new char [_MAX_PATH];
		if ( !_pInput )
			return;
		*_pInput = '\0';

		_isOR = true;		// Ruf aus ORF
	}
	OKButton.Disable();
	_TPStore.Disable();
	_TPDelete.Disable();


	_TPDelete.SetText(ResString ( ResID ( IDS_GLOBALDELETE,&_RF),60));

	_TProjectKey.SetButton ( &_TPStore);
	_TProjectKey.SetProject ( &_TPDirectory);
	_TProjectKey.SetTextLimit ( (uint)MaxKey); 

	_pPROJ = pPROJ;
	_pMenu = pMenu;
	_isNewTree = false;		
	if ( !pPROJ || !pMenu)
		return;
	CTable t ( *_pPROJ );
	if ( !pProject)
		return;
	if (!t.Find( pProject))
		return;

	PROJLock l(t);
	_iLevel = l->Level();
	_pTPRJ = l->pTPRJ();
	
	if ( !_pTPRJ) {
		_pTPRJ = new TPRJTree;
		l->StoreTProjects (_pTPRJ);
		_isNewTree = true;			// Baum neu angelegt
	}

	_pKey = NULL;
	_pLastKey = NULL;
	_pProject = NULL;
	_pLastProject = NULL;
	_isMenu = false;

	if ( !_pLastKey )
		_pLastKey = new char [_MAX_PATH];
	if ( !_pLastProject)
		_pLastProject = new char [_MAX_PATH];

	if ( !_pLastKey || !_pLastProject )  {
		DELETE_OBJ ( _pLastKey );
		DELETE_OBJ ( _pLastProject );
		return;
	}
	*_pLastKey = '\0';
	*_pLastProject = '\0';

	if ( !LoadTProjectList())
		return;

	_pLocDir = new char [_MAX_PATH];
	if ( !_pLocDir )
		return;

	strcpy (_pLocDir,pProject);
	strupr (_pLocDir);

	_TProjects.ChangeCurrentIndex (0);

	char *pBuffer = new char [_MAX_PATH];

	_TProjects.GetCurrentString (pBuffer);

	if (_pRefTP)
		strcpy (_pRefTP,pBuffer);

	// KK010514
		if ( !_pKey ) 
			_pKey = new char [_MAX_PATH];
		if ( _pKey) 
			strcpy ( _pKey, pBuffer);
//////////////////////////////////////////////////////////////////////////////

	CTable k ( *_pMenu);

	if ( k.Find( pBuffer )) {
		TPRJLock f(k);
		_TPDirectory.SetText(f->DBName());
		_TProjectKey.SetText(f->Menu());
	// KK010514
		if ( !_pProject ) 
			_pProject = new char [_MAX_PATH];
		if ( _pKey) 
			strcpy ( _pProject,f->DBName() );
//////////////////////////////////////////////////////////////////////////////

		if ( !_isOR) {
			_TPStore.Disable();
			_TPDelete.Enable();
		}
	} else {
		_TPStore.Disable();
		_TPDelete.Disable();
	}



	DELETE_OBJ(pBuffer);

	_isModified = false;		// Keine Veränderung des Menüs

	// Button Löschen in Entfernen
	if ( _isOR)
		_TPDelete.SetText(ResString(ResID(IDS_LOCALDELETE,&_RF),50));

//Objektzugriff
	if ( pInput && *pInput != '\0' ) {	//ORF mit Link
		strcpy ( _pInput,pInput);
		CTable t ( *_pTPRJ);
		if ( t.Find( _pInput ) ) {
			TPRJLock l(t);
			_TProjectKey.SetText(_pInput);
			char *pProjectName = new char [ _MAX_PATH];
			if ( !pProjectName)
				return;
			*pProjectName = '\0';
			strcat ( pProjectName, l->Drive());
			strcat ( pProjectName, l->Path());								
			strcat ( pProjectName, l->DBName());
			strcat ( pProjectName, l->Ext());
			_TPDirectory.SetText(pProjectName);
			_TProjectKey.SetDelete ( &_TPDelete);
			_TProjectKey.SetKey ( _pInput);
			if ( !_pKey ) 
				_pKey = new char [_MAX_PATH];
			if ( _pKey) 
				strcpy ( _pKey, _pInput);

			if ( !_pProject ) 
				_pProject = new char [_MAX_PATH];
			if ( _pProject) {
				strcpy ( _pProject, pProjectName);
				strupr ( _pProject );
			}
			
			DELETE_OBJ ( pProjectName);
			_TPDelete.Enable();
			_TPStore.Disable();
		}
	}


	return;
}

#pragma warning (default: 4355)


TProjectDefine :: ~TProjectDefine (void)
{
//	_pW->Enable();
	DELETE_OBJ ( _pProject);
	DELETE_OBJ ( _pKey);
	DELETE_OBJ ( _pLocDir);
	DELETE_OBJ ( _pLastKey);
	DELETE_OBJ ( _pLastProject);
	DELETE_OBJ ( _pInput);
	DELETE_OBJ ( _pRefTP);
}
void _XTENSN_EXPORT TProjectDefine :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {

	case IDOK: 
		{
		EndDlg (1);
		}
		break;

	case IDCANCEL:
		{
		if ( _isNewTree ) {	// Baum wieder weg 
			CTable t ( *_pPROJ );
			if (t.Find( _pLocDir)) {
				PROJLock l(t);
				_pTPRJ = NULL;
				l->DeleteTProjects ();
			}
		}
		EndDlg (0);
		}
		break;


	case IDB_TPROJECTSTORE: 
		{
		if ( !_pLastKey ) {
			_pLastKey = new char [_MAX_PATH];
			if ( !_pLastKey)
				return;
		}
		_TProjectKey.GetText ( _pLastKey , _MAX_PATH-1);
		
		if ( !_pLastProject ) {
			_pLastProject = new char [_MAX_PATH];
			if ( !_pLastProject) {
				DELETE_OBJ ( _pLastKey );
				return;
			}
		}
		_TPDirectory.GetText ( _pLastProject , _MAX_PATH-1);
		strupr(_pLastProject);

		if ( *_pLastKey == '\0' ) { 
			HWND hWnd = this->Handle();
			MessageBox ( hWnd ,
			ResString ( ResID ( IDS_TPNOPROJECTKEY,&_RF),60),
			ResString (ResID(IDT_TPCAPTION,&_RF),50),
			 MB_OK|MB_ICONEXCLAMATION);
			return;
		}

// Nur für Einzelobjekt
		if ( _pInput ) {
			if ( _pLastKey ) {
				if ( strcmp ( _pInput, _pLastKey ) != 0 ) {
					strcpy ( _pInput,_pLastKey);
				} else
					*_pInput = '\0';
			}
		}

		if ( StoreNewInformation()) {

			FillTProjectList();
			OKButton.Enable();
		}

		if ( _pInput ) {
			if ( *_pInput != '\0')
				_isModified = true;
			EndDlg(2);
			return;
		}

		}
		break;

	case IDB_TPROJECTDELETE:
		{
		if ( _pInput ) {
//			_TProjectKey.GetText ( _pInput,_MAX_PATH-1);
//			FillTProjectList();
			EndDlg(-1);
			return;
		}
		char * pKey = new char [_MAX_PATH];
//		if ( !pKey)
// KK 010514
		if ( !pKey || !_pKey)
			return;
		_TProjectKey.GetText ( pKey , _MAX_PATH-1);
		if ( strcmp ( pKey, _pKey) != 0 ) {
			FillTProjectList();
			return;
		} 
		if ( _pKey ) {
			CTable t( *_pMenu);
			if ( t.Find ( _pKey )) {
				MMenuLock l(t);
				char * pProject = new char [_MAX_PATH];
				if ( !pProject)
					return;
				_TPDirectory.GetText ( pProject , _MAX_PATH-1);
				strupr(pProject);
				if ( strcmp ( pProject, _pProject) != 0 ) {
					FillTProjectList();
					return;
				} 
				l->ModKZ() = (short)MF_DeleteKey;
				FillTProjectList();
				OKButton.Enable();

			}
		}
		}
		break;

	case IDC_BUTTONNEW:
		{
			char *pTRiNam = ((CProjectExtension *)g_pTE)->TRiASName();
	        char *pList = new char [ _MAX_PATH];
	        if ( !pList && pTRiNam )
	        	return;
	        wsprintf ( pList,ResString(ResID(IDS_TPSEARCHCAPTION,&_RF),50),pTRiNam);

		COpenDialog ODlg ( this , pList);
		ODlg.SetCaption ( ResString(ResID(IDS_TPNEWCAPTION,&_RF),50) );
		ODlg.Show();          
		DELETE_OBJ ( pList);
		if ( ODlg.Result() == 1 ) {	// OK
			int iLen = ODlg.GetFileNameLen();
			char * pProj = new char [_MAX_PATH];
			if ( !pProj)
				return;
			ODlg.GetFileName( pProj , _MAX_PATH);
			pProj = strupr ( pProj );
//----------------------> Vater = Tochter ??? <------------
			if ( strcmp(_pLocDir , pProj ) == 0 ) {
				HWND hWnd = this->Handle();
				MessageBox ( hWnd ,
				ResString ( ResID ( IDS_TPNORELATION,&_RF),60),
				ResString (ResID(IDT_TPCAPTION,&_RF),50),
				 MB_OK|MB_ICONEXCLAMATION);
				return;
			}
			_TPDirectory.SetText(pProj);
			char *pUser = new char [_MAX_PATH];
			if ( pUser ) {
				_splitpath (pProj, NULL, NULL, pUser, NULL);
				_TProjectKey.SetText ( pUser );
				DELETE_OBJ ( pUser);
			}
			_TPStore.Enable();
			DELETE_OBJ ( pProj);
		} else {
			_TProjectKey.SetText ( _pKey );
		}

		}
		break;

		
	case IDB_TPROJECTSEARCH:
		{
			char *pTRiNam = ((CProjectExtension *)g_pTE)->TRiASName();
	        char *pList = new char [ _MAX_PATH];
	        if ( !pList && pTRiNam )
	        	return;
	        wsprintf ( pList,ResString(ResID(IDS_TPSEARCHCAPTION,&_RF),50),pTRiNam);

		COpenDialog ODlg ( this , pList);
//		ODlg.AddFlags( OFN_HIDEREADONLY);
		ODlg.SetCaption ( ResString(ResID(IDT_TPCAPTION,&_RF),50) );
		ODlg.Show();          
		DELETE_OBJ ( pList);
		if ( ODlg.Result() == 1 ) {	// OK
			int iLen = ODlg.GetFileNameLen();
			char * pProj = new char [_MAX_PATH];
			if ( !pProj)
				return;
			ODlg.GetFileName( pProj , _MAX_PATH);
			pProj = strupr ( pProj );
//----------------------> Vater = Tochter ??? <------------
			if ( strcmp(_pLocDir , pProj ) == 0 ) {
				HWND hWnd = this->Handle();
				MessageBox ( hWnd ,
				ResString ( ResID ( IDS_TPNORELATION,&_RF),60),
				ResString (ResID(IDT_TPCAPTION,&_RF),50),
				 MB_OK|MB_ICONEXCLAMATION);
				return;
			}
			_TPDirectory.SetText(pProj);
			char *pUser = new char [_MAX_PATH];
			if ( pUser ) {
				_TProjectKey.GetText ( pUser ,MaxKey);
				if ( *pUser == '\0' ) {
					_splitpath (pProj, NULL, NULL, pUser, NULL);
					_TProjectKey.SetText ( pUser );
				}
				DELETE_OBJ ( pUser);
			}
			_TPStore.Enable();
			DELETE_OBJ ( pProj);
		} else {
			_TProjectKey.SetText ( _pKey );
		}

		}
		break;
	}
	return;
}
//Member
//-------------------------------------------------------------------
//
Bool TProjectDefine :: LoadTProjectList ( void )
{
	if ( !_pTPRJ)
		return false;

	_TProjects.Clear();
	char *pProject = new char [_MAX_PATH];
	if ( !pProject )
		return false;

	_TPDirectory.SetText(NULL);
	_TProjectKey.SetText(NULL);

	CTable t(*_pTPRJ );
	CTable m( *_pMenu);
	short MenuNr = 0;
	short iCount = 0;
	for (t.First(); t.Valid() ; t.Next()  ) {
	
		TPRJLock l(t);
		if ( !_isMenu ) {
			MenuNr++;
			MODMENU MM;
			SetModZero ( &MM);
			MM.iMenuNr = MenuNr;
			MM.pKey = l->Menu();
			*pProject = '\0';
			strcat ( pProject , l->Drive());
			strcat ( pProject , l->Path());
			strcat ( pProject , l->DBName());
			strcat ( pProject , l->Ext());
			MM.pDBName = pProject;  
			char *pMen = l->Menu();

			MMenuCreator MMenuCr ( *_pMenu );
			ContCreate ( MMenuCr, MMenu ) ( pMen, &MM );
		}
		_TProjects.AddString ( l->Menu());
		iCount ++;
	}

	_isMenu = true;

	DELETE_OBJ ( pProject);

	if (0 < iCount )
		_TPStore.Enable();

	return true;

}
//----------------------------------------------------------------------
Bool TProjectDefine :: FillTProjectList ( void )
{

	_TProjects.Clear();

	_TPStore.Disable();
	_TPDelete.Disable();

	CTable t(*_pMenu );

	_TPDirectory.SetText(NULL);
	_TProjectKey.SetText(NULL);

	_isModified = false;
	for (t.First(); t.Valid() ; t.Next()  ) {
	
		MMenuLock l(t);
		short MKZ = l->ModKZ();
		if ( MKZ != (short) MF_DeleteKey &&
		     MKZ != (short) MF_ModKey ) {
			_TProjects.AddString ( l->Menu());
			if ( MKZ == (short) MF_AddKey && l->MenuNr() == 0) {
				_isModified = true;
				OKButton.Enable();
			}
			if ( MKZ == (short) MF_ModProject && l->MenuNr() > 0) {
				_isModified = true;
				OKButton.Enable();
			}
		} else {
			if ( l->MenuNr())
				_isModified = true;
		}

	}

	if ( _pLastKey)
		*_pLastKey = '\0';
	if ( _pLastProject)
		*_pLastProject = '\0';

	return true;
}
//---------------------------------------------------------
void _XTENSN_EXPORT TProjectDefine :: ListBoxSel (ControlEvt e )
{
	switch ((unsigned int)e.GetControlID()) {

	case IDLB_TPROJECTS:
		{
		OKButton.Disable();
		char *pBuffer = new char [_MAX_PATH];
		if ( pBuffer == NULL ) 
			return ;
		_TPStore.Enable();

// Gilt hier bei ORF !! 
//		if ( !_pInput || *_pInput == '\0')
//			_TPStore.Disable();

		if ( !_isOR) 
			_TPStore.Disable();

		int iIndex = _TProjects.GetCurrentIndex();

		if (iIndex != -1) {
			_TProjects.GetCurrentString (pBuffer);
			if ( !_pInput || *_pInput == '\0'){
				OKButton.Enable();
			}
			if (_pRefTP)
				strcpy (_pRefTP,pBuffer);
		} else {
			DELETE_OBJ ( pBuffer);
			return;
		}


		CTable t ( *_pMenu);
		if ( !t.Find( pBuffer )) {
			DELETE_OBJ ( pBuffer);
			return;
		}
		TPRJLock l(t);
		_TPDirectory.SetText(l->DBName());
		_TProjectKey.SetText(l->Menu());

		if ( !_pKey ) 
			_pKey = new char [_MAX_PATH];
		if ( _pKey) 
			strcpy ( _pKey, l->Menu());

		if ( !_pProject ) 
			_pProject = new char [_MAX_PATH];
		if ( _pProject) {
			strcpy ( _pProject, l->DBName());
			strupr ( _pProject );
		}
		
		_TPDelete.Enable();

		if ( _pInput ) {
			if ( strcmp ( _pInput, pBuffer) != 0 )
				_TPDelete.Disable();
		}

		DELETE_OBJ ( pBuffer);

		}
		break;
	}
}
//---------------------------------------------------------
Bool TProjectDefine :: StoreNewInformation ( void )
{
	
	if ( _pMenu == NULL )
		return false;

	

	CTable t ( *_pMenu);

	if ( t.Find( _pLastKey) ) {		// Schlüssel schon gegeben

		if ( _pProject == NULL )
			return true;

		MMenuLock l(t);
		if ( strcmp ( _pProject, _pLastProject ) == 0 ) 	// identisch
			return false;
		if ( l->MenuNr() > 0 )
			l->ModKZ() = (short)MF_ModProject;

		l->StoreReferenz( _pLastProject,_pProject);
	} else {
//	Neues Teilprojekt oder modifizierter Key
//	Achtung - pProject muß nicht definiert sein
		MODMENU MM;
		SetModZero ( &MM);
		MM.pKey = _pLastKey;
		MM.pDBName = _pLastProject;
		if (_pProject ) {
		   if ( strcmp ( _pProject , _pLastProject ) == 0 ) {
			if ( t.Find ( _pKey )) {
				MMenuLock l(t);
				l->ModKZ() = (short) MF_ModKey; 
				l->StoreReferenz( _pLastProject,_pLastKey);
			}
		   }
		}

		MM.iModKZ = (short) MF_AddKey; 		// Neuer Key,neues Project
		MMenuCreator MMenuCr ( *_pMenu );
		ContCreate ( MMenuCr, MMenu ) ( _pLastKey, &MM );
	}
	
	return true;
}
//------------------------TProjectDefine--------------------------------
// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

TProjectMod :: TProjectMod (pWindow pW, uint res, ResourceFile *pResTarget, char *pIni, char *pPfad, char *pKey)
	     : DialogWindow (pW, ResID ( res, pResTarget)),
	       _TPIni (this,IDC_TPPROJECTINI),
	       _TPPfad (this,IDC_TPROJECTPFAD),
		   _TPKey (this, IDS_TPROJECTKEY),
		   _TPDir (this, IDS_TPROJECTSDIR),
	       _TPDefine ( this, IDB_TPROJECTSEARCHMOD),
	       OKButton (this, IDOK),
	       DelButton (this, IDC_DELBUTTON),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte

	_pResTarget = pResTarget;

	_pW = pW;
	_pINI = NULL;
	_pPfad = NULL;
	_pKey = NULL;

	if ( pIni ) {
		_pINI = new char [_MAX_PATH];
		if ( !_pINI )
			return;
		strcpy ( _pINI,pIni);
	}
	if ( pPfad ) {
		_pPfad = new char [_MAX_PATH];
		if ( !_pPfad )
			return;
		strcpy ( _pPfad,pPfad);
	}

	if ( pKey ) {
		_pKey = new char [_MAX_PATH];
		if ( !_pKey )
			return;
		strcpy ( _pKey,pKey);
	}

	OKButton.Disable();
	DelButton.Disable();


	_TPPfad.SetText(pPfad);
	_TPIni.SetText(pIni);
	_TPKey.SetText (pKey);

	return;
}

#pragma warning (default: 4355)


TProjectMod :: ~TProjectMod (void)
{
	DELETE_OBJ ( _pPfad);
	DELETE_OBJ ( _pINI);
	DELETE_OBJ ( _pKey);
}
void _XTENSN_EXPORT TProjectMod :: ButtonClick (ControlEvt e)
{

	switch ((unsigned int)e.GetControlID()) {

	case IDOK: 
		{
		_TPKey.GetText (_pKey, _MAX_PATH);

		if ( !_pPfad) {
			EndDlg(0);
		} else {

			EndDlg(1);
		}
		}
		break;

	case IDCANCEL:
		{
		EndDlg (0);
		}
		break;

	case IDC_DELBUTTON:
		{
		EndDlg (-1);
		}
		break;

	case IDB_TPROJECTSEARCHMOD:
		{

		char *pTRiNam = ((CProjectExtension *)g_pTE)->TRiASName();

        char *pList = new char [ _MAX_PATH];
        if ( pList && pTRiNam) {
	        wsprintf ( pList,ResString(ResID(IDS_TPSEARCHCAPTION,_pResTarget),50),pTRiNam);
		//	        strcpy ( pList,ResString(ResID(IDS_TPSEARCHCAPTION,_pResTarget),50));

			COpenDialog ODlg ( this , pList);
			ODlg.SetCaption ( ResString(ResID(IDT_TPCAPTION,_pResTarget),50) );
			ODlg.SetFileName (_pPfad);
			ODlg.Show();
				
			DELETE_OBJ ( pList);

			if ( ODlg.Result() == 1 ) {	// OK
				int iLen = ODlg.GetFileNameLen();
				ODlg.GetFileName( _pPfad , _MAX_PATH);
				 _pPfad = strupr ( _pPfad );
				_TPDir.SetText(_pPfad);
				OKButton.Enable();
				DelButton.Enable();
			}
		}
		}

		break;


	}

	return;

}
//------------------------TProjectMod--------------------------------
//----------------------TEPRODEF.CXX-------------------------------------
