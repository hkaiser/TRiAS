/************************************************************************
**	D B D A O . C P P													*
**																		*
*************************************************************************
** Copyright (C) 1996 by Microsoft Corporation		 					*
**		   All Rights Reserved					 						*
************************************************************************/
/*
	DBDAO.CPP

	Source code for DBDAO C++ classes
*/

#include "stdafx.h"
#include "resource.h"

#define _DB_NOFORCE_LIBS
#include <DBDAO.h>



/*****************************************************************************
* CdbException
*/
CONSTRUCTOR			CdbException::CdbException(
	HRESULT	hr)
	{
	m_hr = hr;
	}

/*****************************************************************************
* CdbBookmark
*/
CONSTRUCTOR			CdbBookmark::CdbBookmark() //default
	{
	vt		= 0;
	parray	= NULL;
	}


CONSTRUCTOR			CdbBookmark::CdbBookmark(
	LPSAFEARRAY psa)
	{
	vt		= VT_ARRAY|VT_UI1;
	parray	= psa;
	}

CONSTRUCTOR			CdbBookmark::CdbBookmark(
	const CdbBookmark &o)
	{
	VariantInit(this);
	DAOMFC_CALL(VariantCopy(this, (LPVARIANT)&o));
	}

CdbBookmark &			CdbBookmark::operator =(
	const CdbBookmark &o)
	{
	DAOMFC_CALL(VariantCopy(this, (LPVARIANT)&o));
	return *this;
	}

					CdbBookmark::operator LPSAFEARRAY(
	VOID)
	{
	return (vt&VT_ARRAY?parray:NULL);
	}

/*****************************************************************************
* CdbOleObject
*/
CONSTRUCTOR			CdbOleObject::CdbOleObject(
	VOID)
	{
	m_punkInterface = NULL;
	}

CdbOleObject &		CdbOleObject::operator =(
	CdbOleObject &o)
	{
	SetInterface(o.m_punkInterface, TRUE);
	return *this;
	}

DESTRUCTOR			CdbOleObject::~CdbOleObject(
	VOID)
	{

	if (m_punkInterface)
		m_punkInterface->Release();
	}

BOOL				CdbOleObject::StartOLE(
	)
	{
	HRESULT	hr;

	DAOMFC_CALL(hr=CoInitialize(NULL));

	return SUCCEEDED(hr);
	}

VOID				CdbOleObject::SetInterface(
	LPUNKNOWN	punk,
	BOOL		bAddRef)	// = FALSE
	{
	// Get rid of existing interface, if we have one
	if (m_punkInterface)
		m_punkInterface->Release();

	// Addref new interface so we have a valid reference
	if (bAddRef && punk)
		punk->AddRef();

	m_punkInterface = punk;
	OnInterfaceChange();
	}

VOID				CdbOleObject::SetInterface(
	REFIID	riidClass,
	REFIID	riidInterface)
	{
	LPUNKNOWN	punk;

	if (!StartOLE())
		return;

	DAOMFC_CALL(CoCreateInstance(riidClass, NULL, CLSCTX_INPROC_SERVER, riidInterface, (LPVOID *)&punk));

	SetInterface(punk);
	}

VOID				CdbOleObject::SetInterfaceLic(
	REFIID	riidClass,
	REFIID	riidInterface)
	{
	LPUNKNOWN	punk;
	BSTR		m_bstrKey = NULL;
	LPCLASSFACTORY2 pClassFactory2 = NULL;

	if (!StartOLE())
		return;

#if _MSC_VER >= 1000
    m_bstrKey = SysAllocString(CdbWide((LPSTR)szKEY));
#else
	m_bstrKey = SysAllocString(_T(szKEY));
#endif

	DAOMFC_CALL(CoGetClassObject(riidClass, CLSCTX_INPROC_SERVER, NULL, IID_IClassFactory2, (void**)&pClassFactory2));
	
	ASSERT(pClassFactory2 != NULL);

	DAOMFC_CALL(pClassFactory2->CreateInstanceLic(NULL, NULL, riidInterface, m_bstrKey,(LPVOID *)&punk));
	    
	if (NULL!=m_bstrKey)
        SysFreeString(m_bstrKey);

	SetInterface(punk);

	DAOMFC_CALL(pClassFactory2->Release());
	}


LPUNKNOWN			CdbOleObject::GetInterface(
	BOOL	bAddRef,				// = FALSE
	BOOL	bThrowException) const	// = TRUE
	{
	if (!m_punkInterface)
		{
		// Oops! The OLE interface has not been set yet a request is
		// being made to access the interface!

		if (bThrowException)
			{
			// First: Set the rich error info.
			#if _MSC_VER >= 1000
			SetRichErrorInfo(L"DBDAO", L"Object OLE interface not set.", NULL, 0L);
			#endif
			// Second: Throw an exception.
			DAOMFC_CALL(E_FAIL);
			}
		else
			return NULL;
		}

	if (bAddRef)
		m_punkInterface->AddRef();

	return m_punkInterface;
	}

VOID				CdbOleObject::OnInterfaceChange(
	VOID)
	{
	// By default do nothing on interface change
	}

VOID				CdbOleObject::SetRichErrorInfo(
	LPOLESTR	pstrSource,
	LPOLESTR	pstrDescription,
	LPOLESTR	pstrHelpFile,
	ULONG		ulHelpID) const
	{
	ICreateErrorInfo *	pcei;
	IErrorInfo *		pei;

	if (FAILED(CreateErrorInfo(&pcei)))
		return;

	if (FAILED(pcei->QueryInterface(IID_IErrorInfo, (LPVOID *)&pei)))
		{
		pcei->Release();
		return;
		}

	pcei->SetGUID(IID_NULL);

	if (pstrSource)
		pcei->SetSource(pstrSource);
	if (pstrDescription)
		pcei->SetDescription(pstrDescription);
	if (pstrHelpFile)
		pcei->SetHelpFile(pstrHelpFile);

	pcei->SetHelpContext(ulHelpID);

	SetErrorInfo((DWORD)0, pei);

	pei->Release();
	pcei->Release();
	}


/*****************************************************************************
* CdbObject
*/
CONSTRUCTOR			CdbObject::CdbObject(
	VOID)
	{
	}

CONSTRUCTOR			CdbObject::CdbObject(
	LPUNKNOWN	punk,
	BOOL		bAddRef)	// = FALSE
	{
	SetInterface(punk, bAddRef);
	}

CString				CdbObject::GetName(
	VOID)
	{
 	#if _MSC_VER >= 1000
 	SetRichErrorInfo(L"DBDAO", L"Method not supported", NULL, 0);
	#endif
	DAOMFC_CALL(E_FAIL);
	return (LPCTSTR)NULL;
	}

VOID				CdbObject::SetName(
	LPCTSTR pstr)
	{
	UNREFERENCED_PARAMETER(pstr);
	#if _MSC_VER >= 1000
	SetRichErrorInfo(L"DBDAO", L"Method not supported", NULL, 0);
	#endif
	DAOMFC_CALL(E_FAIL);
	}

/*****************************************************************************
* CdbStaticCollection
*/
// Methods
CdbObject		CdbStaticCollection::ObItem(
	LONG i)
	{
	DAOMFCSCollection *	pcol = (DAOMFCSCollection *)GetInterface();
	LPUNKNOWN			pint = NULL;

	if (!pcol)
		return (LPUNKNOWN)NULL;

	DAOMFC_CALL(pcol->get_Item(LTV(i), &pint));

	return pint;
	}

CdbObject		CdbStaticCollection::ObItem(
	LPCTSTR pstr)
	{
	DAOMFCSCollection *	pcol = (DAOMFCSCollection *)GetInterface();
	LPUNKNOWN			pint = NULL;

	if (!pcol)
		return (LPUNKNOWN)NULL;

	DAOMFC_CALL(pcol->get_Item(STV(pstr), &pint));

	return pint;
	}

LONG			CdbStaticCollection::GetCount(
	VOID)
	{
	DAOMFCSCollection *	pcol = (DAOMFCSCollection *)GetInterface();
	SHORT				s		= 0;

	if (!pcol)
		return 0;

	DAOMFC_CALL(pcol->get_Count(&s));

	return (LONG)s;
	}

VOID			CdbStaticCollection::ObAppend(
	CdbObject &o)
	{
	UNREFERENCED_PARAMETER(o);
	}

VOID			CdbStaticCollection::Delete(
	LPCTSTR pstr)
	{
	UNREFERENCED_PARAMETER(pstr);
	}

VOID			CdbStaticCollection::Refresh(
	VOID)
	{
	DAOMFCSCollection *	pcol	= (DAOMFCSCollection *)GetInterface();

	DAOMFC_CALL(pcol->Refresh());
	}

/*****************************************************************************
* CdbDynamicCollection
*/
// Methods
CdbObject		CdbDynamicCollection::ObItem(
	LONG i)
	{
	DAOMFCDCollection *	pcol = (DAOMFCDCollection *)GetInterface();
	LPUNKNOWN			pint = NULL;

	if (!pcol)
		return (LPUNKNOWN)NULL;

	DAOMFC_CALL(pcol->get_Item(LTV(i), &pint));

	return pint;
	}

CdbObject		CdbDynamicCollection::ObItem(
	LPCTSTR pstr)
	{
	DAOMFCDCollection *	pcol = (DAOMFCDCollection *)GetInterface();
	LPUNKNOWN			pint = NULL;

	if (!pcol)
		return (LPUNKNOWN)NULL;

	DAOMFC_CALL(pcol->get_Item(STV(pstr), &pint));

	return pint;
	}

LONG			CdbDynamicCollection::GetCount(
	VOID)
	{
	DAOMFCDCollection *	pcol = (DAOMFCDCollection *)GetInterface();
	SHORT				s		= 0;

	if (!pcol)
		return 0;

	DAOMFC_CALL(pcol->get_Count(&s));

	return (LONG)s;
	}

VOID			CdbDynamicCollection::ObAppend(
	CdbObject &o)
	{
	DAOMFCDCollection *	pcol	= (DAOMFCDCollection *)GetInterface();
	LPDISPATCH	pdisp			= (LPDISPATCH)o.GetInterface();

	if (!pdisp)
		return;

	DAOMFC_CALL(pcol->Append(pdisp));
	}

VOID			CdbDynamicCollection::Delete(
	LPCTSTR pstr)
	{
	DAOMFCDCollection *	pcol	= (DAOMFCDCollection *)GetInterface();

	DAOMFC_CALL(pcol->Delete(STB(pstr)));
	}

VOID			CdbDynamicCollection::Refresh(
	VOID)
	{
	DAOMFCDCollection *	pcol	= (DAOMFCDCollection *)GetInterface();

	DAOMFC_CALL(pcol->Refresh());
	}


/*****************************************************************************
* Collection implementations
*/
DAOMFC_STATIC_COLLECTION_IMPL(CdbErrors, CdbError, DAOErrors, DAOError)
DAOMFC_STATIC_COLLECTION_IMPL(CdbDatabases, CdbDatabase, DAODatabases, DAODatabase)
DAOMFC_STATIC_COLLECTION_IMPL(CdbRecordsets, CdbRecordset, DAORecordsets, DAORecordset)
DAOMFC_STATIC_COLLECTION_IMPL(CdbParameters, CdbParameter, DAOParameters, DAOParameter)
DAOMFC_STATIC_COLLECTION_IMPL(CdbDocuments, CdbDocument, DAODocuments, DAODocument)
DAOMFC_STATIC_COLLECTION_IMPL(CdbContainers, CdbContainer, DAOContainers, DAOContainer)

DAOMFC_DYNAMIC_COLLECTION_IMPL(CdbProperties, CdbProperty, DAOProperties, DAOProperty)
DAOMFC_DYNAMIC_COLLECTION_IMPL(CdbFields, CdbField, DAOFields, DAOField)
DAOMFC_DYNAMIC_COLLECTION_IMPL(CdbQueryDefs, CdbQueryDef, DAOQueryDefs, DAOQueryDef)
DAOMFC_DYNAMIC_COLLECTION_IMPL(CdbTableDefs, CdbTableDef, DAOTableDefs, DAOTableDef)
DAOMFC_DYNAMIC_COLLECTION_IMPL(CdbIndexes, CdbIndex, DAOIndexes, DAOIndex)
DAOMFC_DYNAMIC_COLLECTION_IMPL(CdbRelations, CdbRelation, DAORelations, DAORelation)
DAOMFC_DYNAMIC_COLLECTION_IMPL(CdbUsers, CdbUser, DAOUsers, DAOUser)
DAOMFC_DYNAMIC_COLLECTION_IMPL(CdbGroups, CdbGroup, DAOGroups, DAOGroup)

//The Workspaces collection may not have it's interface until the client decides between JET and ODBC
//(because DAO will load Jet or ODBC as soon as the collection is accessed)so until an individual item 
//in the workspaces collection is addressed, keep the interface NULL

CdbWorkspace		CdbWorkspaces::Item				(LONG i) 		{GetDelayedInterface(); return (DAOWorkspace *)(ObItem(i).GetInterface(TRUE)); }
CdbWorkspace		CdbWorkspaces::Item				(LPCTSTR pstr)	{GetDelayedInterface(); return (DAOWorkspace *)(ObItem(pstr).GetInterface(TRUE)); }
VOID				CdbWorkspaces::Append			(CdbWorkspace &o)	{GetDelayedInterface(); ObAppend(o); }
CdbWorkspace		CdbWorkspaces::operator[]		(LONG i)		{GetDelayedInterface(); return (DAOWorkspace *)(Item(i).GetInterface(TRUE)); }
CdbWorkspace		CdbWorkspaces::operator[]		(LPCTSTR pstr)	{GetDelayedInterface(); return (DAOWorkspace *)(Item(pstr).GetInterface(TRUE)); }

VOID			CdbWorkspaces::GetDelayedInterface()
	{
	DAOWorkspaces *		pwrks	= NULL;

	// If we have the Engine interface and this interface hasn't been set yet
	// we can try to get it now (Unless the user created DBEngine with an
	// explicit "DONT START"
	if (!m_punkInterface && pDBEng && !m_bDontStart)
		{
		DAOMFC_CALL(pDBEng->get_Workspaces(&pwrks));
		SetInterface(pwrks);
		}
	}

//The Connections interface is special cased because it can exist in an unconnected state if the 
//Workspace is a Jet workspace. This implementation makes sure the error info gets
//generated properly from DAO
CdbConnection		CdbConnections::Item			(LONG i) 		{CheckInterface(); return (DAOConnection *)(ObItem(i).GetInterface(TRUE)); }
CdbConnection		CdbConnections::Item			(LPCTSTR pstr)	{CheckInterface(); return (DAOConnection *)(ObItem(pstr).GetInterface(TRUE)); }
CdbConnection		CdbConnections::operator[]		(LONG i)		{CheckInterface(); return (DAOConnection *)(Item(i).GetInterface(TRUE)); }
CdbConnection		CdbConnections::operator[]		(LPCTSTR pstr)	{CheckInterface(); return (DAOConnection *)(Item(pstr).GetInterface(TRUE)); }
LONG				CdbConnections::GetCount		(
	VOID)
	{
	DAOMFCSCollection *	pcol;
	SHORT				s		= 0;
	CheckInterface(); 
	
	pcol = (DAOMFCSCollection *)GetInterface();

	if (!pcol)
		return 0;

	DAOMFC_CALL(pcol->get_Count(&s));

	return (LONG)s;
	}

VOID                CdbConnections::Refresh(
	VOID)
	{
	DAOMFCSCollection *	pcol;
	CheckInterface();
	pcol	= (DAOMFCSCollection *)GetInterface();

	DAOMFC_CALL(pcol->Refresh());

	}


//Force DAO to throw an exception if the interface is missing. This is an indirect way of doing this
//by checking for a missing interface and then asking the DAO workspace to return it. If the Connections
//interface throws an exception it's most likely because this is a Jet workspace
VOID				CdbConnections::CheckInterface()
	{
	DAOConnections *	pconn	= NULL;

	if(!m_punkInterface)
		if(pwrk)
			DAOMFC_CALL(pwrk->get_Connections(&pconn));
	}

CONSTRUCTOR		CdbConnections::CdbConnections(
	CdbConnections &Connections)
	{
	DAOConnections *	pconn	= NULL;

	//Try to trap the user from getting a Connections copy if this is a Jet workspace
	if(Connections.pwrk)
		DAOMFC_CALL(Connections.pwrk->get_Connections(&pconn));

	SetInterface(Connections.m_punkInterface, TRUE);
	}


CdbConnections &	CdbConnections::operator =(
	CdbConnections &Connections)
	{
	DAOConnections *	pconn	= NULL;

	//Try to trap the user from getting a Connections copy if this is a Jet workspace
	if(Connections.pwrk)
		DAOMFC_CALL(Connections.pwrk->get_Connections(&pconn));

	SetInterface(Connections.m_punkInterface, TRUE);
	return *this;
	}

/*****************************************************************************
* CdbLastOLEError
*
* NOTE:	This object is meant to be used inside of exception handlers so
*		exceptions should not be raised by these member functions.
*/
CONSTRUCTOR				CdbLastOLEError::CdbLastOLEError(
	VOID)
	{
	IErrorInfo *	pei = NULL;

	GetErrorInfo(0L, &pei);

	CdbOleObject::SetInterface((LPUNKNOWN)pei);
	}

CString					CdbLastOLEError::GetSource(
	VOID)
	{
	IErrorInfo *	pei = (IErrorInfo *)GetInterface(FALSE, FALSE);
	CdbBSTR			bstr;

	if (!pei)
		return (LPOLESTR)NULL;

	pei->GetSource(bstr);

	return *((BSTR *)bstr);
	}

CString					CdbLastOLEError::GetDescription(
	VOID)
	{
	IErrorInfo *	pei = (IErrorInfo *)GetInterface(FALSE, FALSE);
	CdbBSTR			bstr;

	if (!pei)
		return (LPOLESTR)NULL;

	pei->GetDescription(bstr);

	return *((BSTR *)bstr);
	}

CString					CdbLastOLEError::GetHelpFile(
	VOID)
	{
	IErrorInfo *	pei = (IErrorInfo *)GetInterface(FALSE, FALSE);
	CdbBSTR			bstr;

	if (!pei)
		return (LPOLESTR)NULL;

	pei->GetHelpFile(bstr);

	return *((BSTR *)bstr);
	}

DWORD					CdbLastOLEError::GetHelpContext(
	VOID)
	{
	IErrorInfo *	pei = (IErrorInfo *)GetInterface(FALSE, FALSE);
	DWORD			dw	= 0;

	if (!pei)
		return 0;

	pei->GetHelpContext(&dw);

	return dw;
	}

/*****************************************************************************
* CdbDBEngine
*/
// Administration
CONSTRUCTOR			CdbDBEngine::CdbDBEngine(
	DAODBEngine *	peng,
	BOOL			bAddRef)	// = FALSE
	{

	m_bStarted = TRUE;
	Workspaces.m_bDontStart = FALSE;
	CdbOleObject::SetInterface((LPUNKNOWN)peng, bAddRef);
	}


CONSTRUCTOR			CdbDBEngine::CdbDBEngine(
	BOOL	bPrivate,		// = FALSE
	BOOL	bStart,			// = TRUE
	LPCTSTR pstrIniPath,	// = NULL
	LPCTSTR pstrDefUser,	// = NULL
	LPCTSTR pstrDefPW,		// = NULL
	LONG	lType)			// = dbUseJet
	{
	m_bStarted = FALSE;

	CdbOleObject::SetInterfaceLic(bPrivate?CLSID_CDAOPrivDBEngine:CLSID_CDAODBEngine,dbIID_IDAODBEngine);
																                  
	if (pstrIniPath)
		SetIniPath(pstrIniPath);
	if (pstrDefUser)
		SetDefaultUser(pstrDefUser);
	if (pstrDefPW)
		SetDefaultPassword(pstrDefPW);
	
	//Jet or ODBC?
	SetDefaultType(lType);	
	
	if (bStart)
		{
		Start();
		Workspaces.m_bDontStart = FALSE;
		}
	else
		{
		//User explicitly asked us NOT to start the engine, so set a flag 
		//so we don't "help" by starting it later to get the workspaces collection
		Workspaces.m_bDontStart = TRUE;
		}

	}

CONSTRUCTOR			CdbDBEngine::CdbDBEngine(
	const CdbDBEngine &o)
	{
	Workspaces.m_bDontStart = FALSE;
	SetInterface(o.GetInterface(TRUE));
	//Workspaces collection may be delayed.
	Workspaces.SetDBEngine((DAODBEngine *)GetInterface());
	}

CdbDBEngine &		CdbDBEngine::operator =(
	const CdbDBEngine &o)
	{
	SetInterface(o.GetInterface(TRUE));
	return *this;
	}

VOID				CdbDBEngine::OnInterfaceChange(
	VOID)
	{
	DAODBEngine	*		peng	= (DAODBEngine *)GetInterface();
	DAOProperties *		pprps	= NULL;
	DAOWorkspaces *		pwrks	= NULL;
	DAOErrors *			perrs	= NULL;

	if (peng && m_bStarted)
		{
		peng->get_Properties(&pprps);

		//Delay this so we can start in either Jet or ODBC - 3.5
		//peng->get_Workspaces(&pwrks);
		peng->get_Errors(&perrs);
		}

	Properties.SetInterface(pprps);
	Workspaces.SetDBEngine(peng);
	Errors.SetInterface(perrs);
	}

VOID				CdbDBEngine::Start(
	VOID)
	{
	// If not started then start and setup collections
	if (!m_bStarted)
		{
		m_bStarted = TRUE;
		Workspaces.m_bDontStart = FALSE;
		OnInterfaceChange();
		}
	}

VOID				CdbDBEngine::SetOption(
	long lOption,
	LPVARIANT pvValue)
	{
	DAODBEngine	*	peng	= (DAODBEngine *)GetInterface();

	DAOMFC_CALL(peng->SetOption(lOption, *pvValue));

	}
// Properties
VOID				CdbDBEngine::SetDefaultPassword(
	LPCTSTR	pstr)
	{
	SPROPSET(DAODBEngine, put_DefaultPassword, pstr);	
	}

VOID				CdbDBEngine::SetDefaultUser(
	LPCTSTR	pstr)
	{
	SPROPSET(DAODBEngine, put_DefaultUser, pstr);
	}

VOID				CdbDBEngine::SetIniPath(
	LPCTSTR	pstr)
	{
	SPROPSET(DAODBEngine, put_IniPath, pstr);
	}

CString				CdbDBEngine::GetIniPath(
	VOID)
	{
	SPROPGET(DAODBEngine, get_IniPath);
	}

VOID				CdbDBEngine::SetDefaultType(
	LONG	l)
	{
	LPROPSET(DAODBEngine, put_DefaultType, l);
	}

LONG				CdbDBEngine::GetDefaultType(
	VOID)
	{
	LPROPGET(DAODBEngine, get_DefaultType);
	}

VOID				CdbDBEngine::SetLoginTimeout(
	SHORT	s)
	{
	WPROPSET(DAODBEngine, put_LoginTimeout, s);
	}

SHORT				CdbDBEngine::GetLoginTimeout(
	VOID)
	{
	WPROPGET(DAODBEngine, get_LoginTimeout);
	}

CString				CdbDBEngine::GetVersion(
	VOID)
	{
	SPROPGET(DAODBEngine, get_Version);
	}

CString				CdbDBEngine::GetSystemDB(
	VOID)
	{
	SPROPGET(DAODBEngine, get_SystemDB);
	}

VOID				CdbDBEngine::SetSystemDB(
	LPCTSTR	pstr)
	{
	SPROPSET(DAODBEngine, put_SystemDB, pstr);	
	}

// Methods
CdbWorkspace 		CdbDBEngine::CreateWorkspace(
	LPCTSTR	pstrName,
	LPCTSTR	pstrUser,
	LPCTSTR	pstrPassword,
	LONG	lDefaultType) //=dbUseJet
	{
	DAODBEngine	*	peng	= (DAODBEngine *)GetInterface();
	DAOWorkspace *	pwrk	= NULL;

	if (!peng)
		return (DAOWorkspace *)NULL;

	DAOMFC_CALL(peng->CreateWorkspace(STB(pstrName), STB(pstrUser), STB(pstrPassword), OLTV(lDefaultType), &pwrk));

	return pwrk;
	}

VOID				CdbDBEngine::CompactDatabase(
	LPCTSTR	pstrOldDatabase,
	LPCTSTR	pstrNewDatabase,
	LPCTSTR pstrDstConnect, // = NULL
	LONG	lOptions, // = -1
	LPCTSTR pstrSrcConnect)// = NULL
	{
	DAODBEngine	*	peng	= (DAODBEngine *)GetInterface();
	TCHAR		szEmpty[] = {_T("")};

	//The DstConnect is an optional argument to DAO, BUT if it isn't
	//supplied DAO ignores the lOptions. So, always supply a DstConnect
	if (!pstrDstConnect) pstrDstConnect = (LPCTSTR)&szEmpty;

	DAOMFC_CALL(peng->CompactDatabase(STB(pstrOldDatabase), 
		STB(pstrNewDatabase), 
		STV(pstrDstConnect),
		OLTV(lOptions),
		STV(pstrSrcConnect)));
	}

VOID				CdbDBEngine::RepairDatabase(
	LPCTSTR pstrDatabase)
	{
	DAODBEngine	*	peng	= (DAODBEngine *)GetInterface();

	DAOMFC_CALL(peng->RepairDatabase(STB(pstrDatabase)));
	}

VOID				CdbDBEngine::RegisterDatabase(
	LPCTSTR	pstrDatabase,
	LPCTSTR	pstrDriver,
	BOOL	bSilent,
	LPCTSTR	pstrAttributes)
	{
	DAODBEngine	*	peng	= (DAODBEngine *)GetInterface();

	DAOMFC_CALL(peng->RegisterDatabase(STB(pstrDatabase), STB(pstrDriver), BTB(bSilent), STB(pstrAttributes)));
	}

VOID				CdbDBEngine::Idle(
	LONG lOptions)	// = -1
	{
	DAODBEngine	*	peng	= (DAODBEngine *)GetInterface();

	DAOMFC_CALL(peng->Idle(OLTV(lOptions)));
	}

CdbDatabase			CdbDBEngine::OpenDatabase(
	LPCTSTR		pstrName,
	BOOL		bExclusive, 		// 
	BOOL		bReadOnly,			// = FALSE
	LPCTSTR		pstrConnect)		// = NULL
	{
	DAODBEngine	*	peng	= (DAODBEngine *)GetInterface();
	DAODatabase *	pdb		= NULL;

	if (!peng)
		return FALSE;

	DAOMFC_CALL(peng->OpenDatabase(STB(pstrName), BTV(bExclusive), BTV(bReadOnly), STV(pstrConnect), &pdb));

	return pdb;
	}

CdbDatabase			CdbDBEngine::OpenDatabase(
	LPCTSTR		pstrName,
	LONG		lOptions,	 		// = 0L
	BOOL		bReadOnly,			// = FALSE
	LPCTSTR		pstrConnect)		// = NULL
	{
	DAODBEngine	*	peng	= (DAODBEngine *)GetInterface();
	DAODatabase *	pdb		= NULL;

	if (!peng)
		return FALSE;

	DAOMFC_CALL(peng->OpenDatabase(STB(pstrName), OLTV(lOptions), BTV(bReadOnly), STV(pstrConnect), &pdb));

	return pdb;
	}

CdbConnection			CdbDBEngine::OpenConnection(
	LPCTSTR		pstrName,
	LONG		lOption,		// = -1
	BOOL		bReadOnly,		// = FALSE
	LPCTSTR		pstrConnect)	// = NULL
	{
	DAODBEngine	*	peng	= (DAODBEngine *)GetInterface();
	DAOConnection *	pconn	= NULL;

	if (!peng)
		return FALSE;

	DAOMFC_CALL(peng->OpenConnection(STB(pstrName), OLTV(lOption), BTV(bReadOnly), STV(pstrConnect), &pconn));

	return pconn;
	}

/*****************************************************************************
* CdbError
*/
// Administration
CONSTRUCTOR			CdbError::CdbError(
	VOID)
	{
	}

CONSTRUCTOR			CdbError::CdbError(
	DAOError *	perr,
	BOOL		bAddRef)	// = FALSE
	{
	CdbOleObject::SetInterface((LPUNKNOWN)perr, bAddRef);
	}

CONSTRUCTOR			CdbError::CdbError(
	const CdbError &o)
	{
	SetInterface(o.GetInterface(TRUE));
	}

CdbError &			CdbError::operator =(
	const CdbError &o)
	{
	SetInterface(o.GetInterface(TRUE));
	return *this;
	}

VOID				CdbError::OnInterfaceChange(
	VOID)
	{
	}

// Properties
LONG				CdbError::GetNumber(
	VOID)
	{
	LPROPGET(DAOError, get_Number);
	}

CString				CdbError::GetSource(
	VOID)
	{
	SPROPGET(DAOError, get_Source);
	}

CString				CdbError::GetDescription(
	VOID)
	{
	SPROPGET(DAOError, get_Description);
	}

CString				CdbError::GetHelpFile(
	VOID)
	{
	SPROPGET(DAOError, get_HelpFile);
	}

LONG				CdbError::GetHelpContext(
	VOID)
	{
	LPROPGET(DAOError, get_HelpContext);
	}

/*****************************************************************************
* CdbWorkspace
*/
// Administration
CONSTRUCTOR			CdbWorkspace::CdbWorkspace(
	VOID)
	{
	}

CONSTRUCTOR			CdbWorkspace::CdbWorkspace(
	DAOWorkspace *	pwrk,
	BOOL			bAddRef)	// = FALSE
	{
	CdbOleObject::SetInterface((LPUNKNOWN)pwrk, bAddRef);
	}

CONSTRUCTOR			CdbWorkspace::CdbWorkspace(
	const CdbWorkspace &o)
	{
	CdbOleObject::SetInterface(o.GetInterface(TRUE));
	}

CdbWorkspace &		CdbWorkspace::operator =(
	const CdbWorkspace &o)
	{
	CdbOleObject::SetInterface(o.GetInterface(TRUE));
	return *this;
	}

VOID				CdbWorkspace::OnInterfaceChange(
	VOID)
	{
	DAOWorkspace *		pwrk 	= (DAOWorkspace *)GetInterface();
	DAOProperties *		pprps	= NULL;
	DAOUsers *			pusrs	= NULL;
	DAOGroups *			pgrps	= NULL;
	DAODatabases *		pdbs	= NULL;
	DAOConnections *	pconn	= NULL;

	if (pwrk)
		{
		pwrk->get_Properties(&pprps);
		pwrk->get_Databases(&pdbs);
		pwrk->get_Connections(&pconn);
		pwrk->get_Users(&pusrs);
		pwrk->get_Groups(&pgrps);
		}

	Properties.SetInterface(pprps);
	Databases.SetInterface(pdbs);
	Connections.SetInterface(pconn);
	if(pwrk)
		Connections.SetWorkspace(pwrk);
	Users.SetInterface(pusrs);
	Groups.SetInterface(pgrps);
	}

// Properties
CString				CdbWorkspace::GetName(
	VOID)
	{
	SPROPGET(DAOWorkspace, get_Name);
	}

VOID				CdbWorkspace::SetName(
	LPCTSTR pstr)
	{
	SPROPSET(DAOWorkspace, put_Name, pstr);
	}

CString				CdbWorkspace::GetUserName(
	VOID)
	{
	SPROPGET(DAOWorkspace, get_UserName);
	}

BOOL				CdbWorkspace::GetIsolateODBCTrans(
	VOID)
	{
	BPROPGET(DAOWorkspace, get_IsolateODBCTrans);
	}

VOID				CdbWorkspace::SetIsolateODBCTrans(
	BOOL b)
	{
	BPROPSET(DAOWorkspace, put_IsolateODBCTrans, b);
	}

LONG				CdbWorkspace::GetType(
	VOID)
	{
	LPROPGET(DAOWorkspace, get_Type);
	}

LONG				CdbWorkspace::GetDefaultCursorDriver(
	VOID)
	{
	LPROPGET(DAOWorkspace, get_DefaultCursorDriver);
	}

VOID				CdbWorkspace::SetDefaultCursorDriver(
	LONG l)
	{
	LPROPSET(DAOWorkspace, put_DefaultCursorDriver, l);
	}

LONG				CdbWorkspace::GetLoginTimeout(
	VOID)
	{
	LPROPGET(DAOWorkspace, get_LoginTimeout);
	}

VOID				CdbWorkspace::SetLoginTimeout(
	LONG l)
	{
	LPROPSET(DAOWorkspace, put_LoginTimeout, l);
	}

// Methods
VOID				CdbWorkspace::BeginTrans(
	VOID)
	{
	DAOWorkspace *		pwrk	= (DAOWorkspace *)GetInterface();

	DAOMFC_CALL(pwrk->BeginTrans());
	}

VOID				CdbWorkspace::CommitTrans(
	long lOptions)			// = -1
	{
	DAOWorkspace *		pwrk	= (DAOWorkspace *)GetInterface();

	//DAO SDK functions default to -1 for longs, but since
	// this function is a strongly-typed optional, 0 is the
	// default. We need to convert this from -1 to 0
	if (lOptions == -1)
		lOptions = 0;
	DAOMFC_CALL(pwrk->CommitTrans(lOptions));
	}

VOID				CdbWorkspace::Close(
	VOID)
	{
	DAOWorkspace *		pwrk	= (DAOWorkspace *)GetInterface();

	DAOMFC_CALL(pwrk->Close());
	}

VOID				CdbWorkspace::Rollback(
	VOID)
	{
	DAOWorkspace *		pwrk	= (DAOWorkspace *)GetInterface();

	DAOMFC_CALL(pwrk->Rollback());
	}

CdbDatabase			CdbWorkspace::OpenDatabase(
	LPCTSTR	pstrName,
	BOOL	bExclusive,		// = FALSE
	BOOL	bReadOnly,		// = FALSE
	LPCTSTR	pstrConnect)	// = NULL
	{
	DAOWorkspace *		pwrk	= (DAOWorkspace *)GetInterface();
	DAODatabase *		pdb		= NULL;

	if (!pwrk)
		return (DAODatabase *)NULL;

	DAOMFC_CALL(pwrk->OpenDatabase(STB(pstrName), BTV(bExclusive), BTV(bReadOnly), STV(pstrConnect), &pdb));

	return pdb;
	}

CdbDatabase			CdbWorkspace::OpenDatabase(
	LPCTSTR		pstrName,
	LONG		lOptions,	 		// = -1L
	BOOL		bReadOnly,			// = FALSE
	LPCTSTR		pstrConnect)		// = NULL
	{
	DAOWorkspace *	pwrk	= (DAOWorkspace *)GetInterface();
	DAODatabase *	pdb		= NULL;

	if (!pwrk)
		return FALSE;

	DAOMFC_CALL(pwrk->OpenDatabase(STB(pstrName), OLTV(lOptions), BTV(bReadOnly), STV(pstrConnect), &pdb));

	return pdb;
	}

CdbConnection			CdbWorkspace::OpenConnection(
	LPCTSTR		pstrName,
	LONG		lOption,		// = -1
	BOOL		bReadOnly,		// = FALSE
	LPCTSTR		pstrConnect)	// = NULL
	{
	DAOWorkspace *	pwrk	= (DAOWorkspace *)GetInterface();
	DAOConnection *	pconn	= NULL;

	if (!pwrk)
		return FALSE;

	DAOMFC_CALL(pwrk->OpenConnection(STB(pstrName), OLTV(lOption), BTV(bReadOnly), STV(pstrConnect), &pconn));

	return pconn;
	}


CdbDatabase			CdbWorkspace::CreateDatabase(
	LPCTSTR	pstrName,
	LPCTSTR	pstrConnect,
	LONG	lOption)	// = -1
	{
	DAOWorkspace *		pwrk	= (DAOWorkspace *)GetInterface();
	DAODatabase *		pdb		= NULL;

	if (!pwrk)
		return (DAODatabase *)NULL;

	DAOMFC_CALL(pwrk->CreateDatabase(STB(pstrName), STB(pstrConnect), OLTV(lOption), &pdb));

	return pdb;
	}

CdbUser				CdbWorkspace::CreateUser(
	LPCTSTR pstrName,		// = NULL
	LPCTSTR pstrPID,		// = NULL
	LPCTSTR pstrPassword)	// = NULL
	{
	DAOWorkspace *		pwrk	= (DAOWorkspace *)GetInterface();
	DAOUser *			pusr	= NULL;

	if (!pwrk)
		return (DAOUser *)NULL;

	DAOMFC_CALL(pwrk->CreateUser(STV(pstrName), STV(pstrPID), STV(pstrPassword), &pusr));

	return pusr;
	}

CdbGroup			CdbWorkspace::CreateGroup(
	LPCTSTR pstrName,	// = NULL
	LPCTSTR pstrPID)	// = NULL
	{
	DAOWorkspace *		pwrk	= (DAOWorkspace *)GetInterface();
	DAOGroup *			pgrp	= NULL;

	if (!pwrk)
		return (DAOGroup *)NULL;

	DAOMFC_CALL(pwrk->CreateGroup(STV(pstrName), STV(pstrPID), &pgrp));

	return pgrp;
	}

/*****************************************************************************
* CdbDatabase
*/
// Administration
CONSTRUCTOR			CdbDatabase::CdbDatabase(
	VOID)
	{
	}

CONSTRUCTOR			CdbDatabase::CdbDatabase(
	DAODatabase *	pdb,
	BOOL			bAddRef)	// = FALSE
	{
	CdbOleObject::SetInterface((LPUNKNOWN)pdb, bAddRef);
	}

CONSTRUCTOR			CdbDatabase::CdbDatabase(
	const CdbDatabase &o)
	{
	SetInterface(o.GetInterface(TRUE));
	}

CdbDatabase &		CdbDatabase::operator =(
	const CdbDatabase &o)
	{
	SetInterface(o.GetInterface(TRUE));
	return *this;
	}

VOID				CdbDatabase::OnInterfaceChange(
	VOID)
	{
	DAODatabase *	pdb		= (DAODatabase *)GetInterface();
	DAOProperties *	pprps	= NULL;
	DAOTableDefs *	ptds	= NULL;
	DAOQueryDefs *	pqds	= NULL;
	DAORelations *	prls	= NULL;
	DAOContainers *	pcts	= NULL;
	DAORecordsets *	prss	= NULL;

	if (pdb)
		{
		pdb->get_Properties(&pprps);
		pdb->get_TableDefs(&ptds);
		pdb->get_QueryDefs(&pqds);
		pdb->get_Relations(&prls);
		pdb->get_Containers(&pcts);
		pdb->get_Recordsets(&prss);
		}

	Properties.SetInterface(pprps);
	TableDefs.SetInterface(ptds);
	QueryDefs.SetInterface(pqds);
	Relations.SetInterface(prls);
	Containers.SetInterface(pcts);
	Recordsets.SetInterface(prss);
	}

// Properties
LONG				CdbDatabase::GetCollatingOrder(
	VOID)
	{
	LPROPGET(DAODatabase, get_CollatingOrder);
	}

CString				CdbDatabase::GetConnect(
	VOID)
	{
	SPROPGET(DAODatabase, get_Connect);
	}

VOID				CdbDatabase::SetConnect(
	LPCTSTR	pstr)
	{
	SPROPSET(DAODatabase, put_Connect, pstr);
	}

CString				CdbDatabase::GetName(
	VOID)
	{
	SPROPGET(DAODatabase, get_Name);
	}

SHORT				CdbDatabase::GetQueryTimeout(
	VOID)
	{
	WPROPGET(DAODatabase, get_QueryTimeout);
	}

VOID				CdbDatabase::SetQueryTimeout(
	SHORT s)
	{
	WPROPSET(DAODatabase, put_QueryTimeout, s);
	}

BOOL				CdbDatabase::GetTransactions(
	VOID)
	{
	BPROPGET(DAODatabase, get_Transactions);
	}

BOOL				CdbDatabase::GetUpdatable(
	VOID)
	{
	BPROPGET(DAODatabase, get_Updatable);
	}

CString				CdbDatabase::GetVersion(
	VOID)
	{
	SPROPGET(DAODatabase, get_Version);
	}

LONG				CdbDatabase::GetRecordsAffected(
	VOID)
	{
	LPROPGET(DAODatabase, get_RecordsAffected);
	}

CdbConnection		CdbDatabase::GetConnection(
	VOID)
	{
	DAODatabase *	pdb		= (DAODatabase *)GetInterface();
	DAOConnection *	pconn	= NULL;

	if (!pdb)
		return FALSE;

	DAOMFC_CALL(pdb->get_Connection(&pconn));

	return pconn;
	}
CString				CdbDatabase::GetReplicaID(
	VOID)
	{
	SPROPGET(DAODatabase, get_ReplicaID);
	}

CString				CdbDatabase::GetDesignMasterID(
	VOID)
	{
	SPROPGET(DAODatabase, get_DesignMasterID);
	}

VOID				CdbDatabase::SetDesignMasterID(
	LPCTSTR	pstr)
	{
	SPROPSET(DAODatabase, put_DesignMasterID, pstr);
	}

// Methods
VOID				CdbDatabase::Close(
	VOID)
	{
	DAODatabase *	pdb		= (DAODatabase *)GetInterface();

	DAOMFC_CALL(pdb->Close());
	}

VOID				CdbDatabase::Execute(
	LPCTSTR	pstrQuery,
	LONG	lOption)	// = -1
	{
	DAODatabase *	pdb		= (DAODatabase *)GetInterface();

	DAOMFC_CALL(pdb->Execute(STB(pstrQuery), OLTV(lOption)));
	}

CdbRecordset		CdbDatabase::OpenRecordset(
	LPCTSTR	pstrName,
	LONG	lType,		// = -1
	LONG	lOptions,   // = -1
	LONG	lLockEdit)	// = -1
	{
	DAODatabase *	pdb		= (DAODatabase *)GetInterface();
	DAORecordset *	prs		= NULL;

	if (!pdb)
		return (DAORecordset *)NULL;

	DAOMFC_CALL(pdb->OpenRecordset(STB(pstrName), OLTV(lType), OLTV(lOptions), OLTV(lLockEdit), &prs));

	return prs;
	}

CdbProperty			CdbDatabase::CreateProperty(
	LPCTSTR		pstrName,	// = NULL
	LONG		lType,		// = -1
	LPVARIANT	pvValue,	// = NULL
	BOOL		bDDL)		// = FALSE
	{
	DAODatabase *	pdb		= (DAODatabase *)GetInterface();
	DAOProperty *	pprp	= NULL;

	if (!pdb)
		return (DAOProperty *)NULL;

	DAOMFC_CALL(pdb->CreateProperty(STV(pstrName), OLTV(lType), VTV(pvValue), BTV(bDDL), &pprp));

	return pprp;
	}

CdbRelation			CdbDatabase::CreateRelation(
	LPCTSTR	pstrName,		// = NULL
	LPCTSTR	pstrTable,		// = NULL
	LPCTSTR	pstrForiegn,	// = NULL
	LONG	lAttributes)	// = -1
	{
	DAODatabase *	pdb		= (DAODatabase *)GetInterface();
	DAORelation *	prl		= NULL;

	if (!pdb)
		return (DAORelation *)NULL;

	DAOMFC_CALL(pdb->CreateRelation(STV(pstrName), STV(pstrTable), STV(pstrForiegn), OLTV(lAttributes), &prl));

	return prl;
	}

CdbTableDef			CdbDatabase::CreateTableDef(
	LPCTSTR	pstrName,		// = NULL
	LONG	lAttributes,	// = -1
	LPCTSTR	pstrSource,		// = NULL
	LPCTSTR	pstrConnect)	// = NULL
	{
	DAODatabase *	pdb		= (DAODatabase *)GetInterface();
	DAOTableDef *	ptd		= NULL;

	if (!pdb)
		return (DAOTableDef *)NULL;

	DAOMFC_CALL(pdb->CreateTableDef(STV(pstrName), OLTV(lAttributes), STV(pstrSource), STV(pstrConnect), &ptd));

	return ptd;
	}

CdbQueryDef			CdbDatabase::CreateQueryDef(
	LPCTSTR pstrName,	// = NULL
	LPCTSTR pstrSQL)	// = NULL
	{
	DAODatabase *	pdb		= (DAODatabase *)GetInterface();
	DAOQueryDef *	pqd		= NULL;

	if (!pdb)
		return (DAOQueryDef *)NULL;

	DAOMFC_CALL(pdb->CreateQueryDef(STV(pstrName), STV(pstrSQL), &pqd));

	return pqd;
	}

VOID				CdbDatabase::NewPassword(
	LPCTSTR pstrOld, 
	LPCTSTR pstrNew)
	{
	DAODatabase *	pdb		= (DAODatabase *)GetInterface();

	if (!pdb)
		return;

	DAOMFC_CALL(pdb->NewPassword(STB(pstrOld), STB(pstrNew)));
	}

VOID				CdbDatabase::Synchronize(
	LPCTSTR pstrReplica, 
	LONG lType) 		// = -1
	{
	DAODatabase *	pdb		= (DAODatabase *)GetInterface();

	if (!pdb)
		return;

	DAOMFC_CALL(pdb->Synchronize(STB(pstrReplica), OLTV(lType)));
	}

VOID				CdbDatabase::MakeReplica(
	LPCTSTR pstrPath, 
	LPCTSTR pstrDescription, 
	LONG lOptions)			// = -1
	{
	DAODatabase *	pdb		= (DAODatabase *)GetInterface();

	if (!pdb)
		return;

	DAOMFC_CALL(pdb->MakeReplica(STB(pstrPath), STB(pstrDescription), OLTV(lOptions)));
	}

VOID				CdbDatabase::PopulatePartial(
	LPCTSTR pstrDbPathName)
	{
	DAODatabase *	pdb		= (DAODatabase *)GetInterface();

	if (!pdb)
		return;

	DAOMFC_CALL(pdb->PopulatePartial(STB(pstrDbPathName)));
	}


/*****************************************************************************
* CdbConnection
*/
// Administration
CONSTRUCTOR			CdbConnection::CdbConnection(
	VOID)
	{
	}

CONSTRUCTOR			CdbConnection::CdbConnection(
	DAOConnection *	pconn,
	BOOL			bAddRef)	// = FALSE
	{
	CdbOleObject::SetInterface((LPUNKNOWN)pconn, bAddRef);
	}

CONSTRUCTOR			CdbConnection::CdbConnection(
	const CdbConnection &o)
	{
	SetInterface(o.GetInterface(TRUE));
	}

CdbConnection &		CdbConnection::operator =(
	const CdbConnection &o)
	{
	SetInterface(o.GetInterface(TRUE));
	return *this;
	}

VOID				CdbConnection::OnInterfaceChange(
	VOID)
	{
	DAOConnection *	pconn		= (DAOConnection *)GetInterface();
	DAOQueryDefs *	pqds	= NULL;
	DAORecordsets *	prss	= NULL;

	if (pconn)
		{
		pconn->get_QueryDefs(&pqds);
		pconn->get_Recordsets(&prss);
		}

	QueryDefs.SetInterface(pqds);
	Recordsets.SetInterface(prss);
	}

// Properties
CString				CdbConnection::GetConnect(
	VOID)
	{
	SPROPGET(DAOConnection, get_Connect);
	}

CString				CdbConnection::GetName(
	VOID)
	{
	SPROPGET(DAOConnection, get_Name);
	}

CdbDatabase			CdbConnection::GetDatabase(
	VOID)
	{
	DAOConnection *	pconn		= (DAOConnection *)GetInterface();
	DAODatabase *	pdb		= NULL;

	if (!pconn)
		return (DAODatabase *)NULL;

	DAOMFC_CALL(pconn->get_Database(&pdb));

	return pdb;
	}

SHORT				CdbConnection::GetQueryTimeout(
	VOID)
	{
	WPROPGET(DAOConnection, get_QueryTimeout);
	}

VOID				CdbConnection::SetQueryTimeout(
	SHORT s)
	{
	WPROPSET(DAOConnection, put_QueryTimeout, s);
	}

BOOL				CdbConnection::GetUpdatable(
	VOID)
	{
	BPROPGET(DAOConnection, get_Updatable);
	}


LONG				CdbConnection::GetRecordsAffected(
	VOID)
	{
	LPROPGET(DAOConnection, get_RecordsAffected);
	}

BOOL				CdbConnection::GetStillExecuting(
	VOID)
	{
	BPROPGET(DAOConnection, get_StillExecuting);
	}

BOOL				CdbConnection::GetTransactions(
	VOID)
	{
	BPROPGET(DAOConnection, get_Transactions);
	}


// Methods
VOID				CdbConnection::Cancel(
	VOID)
	{
	DAOConnection *	pconn		= (DAOConnection *)GetInterface();

	DAOMFC_CALL(pconn->Cancel());
	}

VOID				CdbConnection::Close(
	VOID)
	{
	DAOConnection *	pconn		= (DAOConnection *)GetInterface();

	DAOMFC_CALL(pconn->Close());
	}

VOID				CdbConnection::Execute(
	LPCTSTR	pstrQuery,
	LONG	lOption)	// = -1
	{
	DAOConnection *	pconn		= (DAOConnection *)GetInterface();

	DAOMFC_CALL(pconn->Execute(STB(pstrQuery), OLTV(lOption)));
	}

CdbRecordset		CdbConnection::OpenRecordset(
	LPCTSTR	pstrName,
	LONG	lType,		// = -1
	LONG	lOptions,	// = -1
	LONG	lLockEdit)  // = -1
	{
	DAOConnection *	pconn		= (DAOConnection *)GetInterface();
	DAORecordset *	prs		= NULL;

	if (!pconn)
		return (DAORecordset *)NULL;

	DAOMFC_CALL(pconn->OpenRecordset(STB(pstrName), OLTV(lType), OLTV(lOptions), OLTV(lLockEdit), &prs));

	return prs;
	}

CdbQueryDef			CdbConnection::CreateQueryDef(
	LPCTSTR pstrName,	// = NULL
	LPCTSTR pstrSQL)	// = NULL
	{
	DAOConnection *	pconn		= (DAOConnection *)GetInterface();
	DAOQueryDef *	pqd		= NULL;

	if (!pconn)
		return (DAOQueryDef *)NULL;

	DAOMFC_CALL(pconn->CreateQueryDef(STV(pstrName), STV(pstrSQL), &pqd));

	return pqd;
	}

/*****************************************************************************
* CdbRecordset
*/
// Administration
CONSTRUCTOR			CdbRecordset::CdbRecordset(
	VOID)
	{
	}

CONSTRUCTOR			CdbRecordset::CdbRecordset(
	DAORecordset *	prs,
	BOOL 			bAddRef)	// = FALSE
	{
	CdbOleObject::SetInterface((LPUNKNOWN)prs, bAddRef);
	}

CONSTRUCTOR			CdbRecordset::CdbRecordset(
	const CdbRecordset &o)
	{
	SetInterface(o.GetInterface(TRUE));
	}

CdbRecordset &		CdbRecordset::operator =(
	const CdbRecordset &o)
	{
	SetInterface(o.GetInterface(TRUE));
	return *this;
	}

VOID				CdbRecordset::OnInterfaceChange(
	VOID)
	{
	DAORecordset *		prs		= (DAORecordset *)GetInterface();
	DAOProperties *		pprps	= NULL;
	DAOFields *			pflds	= NULL;
	if (prs)
		{
		prs->get_Properties(&pprps);
		prs->get_Fields(&pflds);
		}

	Properties.SetInterface(pprps);
	Fields.SetInterface(pflds);
	}

VOID				CdbRecordset::SetGetRowsExInt(
	VOID)
	{
	DAORecordset *		prs		= (DAORecordset *)GetInterface();
	ICDAORecordset *	pGetRows = NULL;
	if (prs)
		{
		prs->QueryInterface(IID_ICDAORecordset, (void **)&pGetRows);
		}
	m_GetRowsInt.SetInterface(pGetRows);
	}

// Properties
BOOL				CdbRecordset::GetBOF(
	VOID)
	{
	BPROPGET(DAORecordset, get_BOF);
	}

CdbBookmark			CdbRecordset::GetBookmark(
	VOID)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();
	LPSAFEARRAY		psa = NULL;

	if (!prs)
		return (LPSAFEARRAY)NULL;

	DAOMFC_CALL(prs->get_Bookmark(&psa));

	return psa;
	}

VOID				CdbRecordset::SetBookmark(
	class CdbBookmark cbm)
	{
	LPSAFEARRAY		psa = (LPSAFEARRAY)cbm;
	DAORecordset *	prs = (DAORecordset *)GetInterface();

	DAOMFC_CALL(prs->put_Bookmark(&psa));
	}

BOOL				CdbRecordset::GetBookmarkable(
	VOID)
	{
	BPROPGET(DAORecordset, get_Bookmarkable);
	}

COleDateTime			CdbRecordset::GetDateCreated(
	VOID)
	{
	DPROPGET(DAORecordset, get_DateCreated);
	}

COleDateTime			CdbRecordset::GetLastUpdated(
	VOID)
	{
	DPROPGET(DAORecordset, get_LastUpdated);
	}

BOOL				CdbRecordset::GetEOF(
	VOID)
	{
	BPROPGET(DAORecordset, get_EOF);
	}


CString				CdbRecordset::GetFilter(
	VOID)
	{
	SPROPGET(DAORecordset, get_Filter);
	}

VOID				CdbRecordset::SetFilter(
	LPCTSTR pstr)
	{
	SPROPSET(DAORecordset, put_Filter, pstr);
	}

CString				CdbRecordset::GetIndex(
	VOID)
	{
	SPROPGET(DAORecordset, get_Index);
	}

VOID				CdbRecordset::SetIndex(
	LPCTSTR pstr)
	{
	SPROPSET(DAORecordset, put_Index, pstr);
	}

CdbBookmark			CdbRecordset::GetLastModified(
	VOID)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();
	LPSAFEARRAY		psa;

	if (!prs)
		return (LPSAFEARRAY)NULL;

	DAOMFC_CALL(prs->get_LastModified(&psa));

	return psa;
	}

BOOL				CdbRecordset::GetLockEdits(
	VOID)
	{
	BPROPGET(DAORecordset, get_LockEdits);
	}

VOID				CdbRecordset::SetLockEdits(
	BOOL b)
	{
	BPROPSET(DAORecordset, put_LockEdits, b);
	}

CString				CdbRecordset::GetName(
	VOID)
	{
	SPROPGET(DAORecordset, get_Name);
	}

BOOL				CdbRecordset::GetNoMatch(
	VOID)
	{
	BPROPGET(DAORecordset, get_NoMatch);
	}

CString				CdbRecordset::GetSort(
	VOID)
	{
	SPROPGET(DAORecordset, get_Sort);
	}

VOID				CdbRecordset::SetSort(
	LPCTSTR pstr)
	{
	SPROPSET(DAORecordset, put_Sort, pstr);
	}

BOOL				CdbRecordset::GetTransactions(
	VOID)
	{
	BPROPGET(DAORecordset, get_Transactions);
	}

SHORT				CdbRecordset::GetType(
	VOID)
	{
	WPROPGET(DAORecordset, get_Type);
	}

LONG				CdbRecordset::GetRecordCount(
	VOID)
	{
	LPROPGET(DAORecordset, get_RecordCount);
	}

BOOL				CdbRecordset::GetUpdatable(
	VOID)
	{
	BPROPGET(DAORecordset, get_Updatable);
	}

BOOL				CdbRecordset::GetRestartable(
	VOID)
	{
	BPROPGET(DAORecordset, get_Restartable);
	}

CString				CdbRecordset::GetValidationText(
	VOID)
	{
	SPROPGET(DAORecordset, get_ValidationText);
	}

CString				CdbRecordset::GetValidationRule(
	VOID)
	{
	SPROPGET(DAORecordset, get_ValidationRule);
	}

CdbBookmark			CdbRecordset::GetCacheStart(
	VOID)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();
	LPSAFEARRAY		psa;

	if (!prs)
		return (LPSAFEARRAY)NULL;

	DAOMFC_CALL(prs->get_CacheStart(&psa));

	return psa;
	}

VOID				CdbRecordset::SetCacheStart(
	CdbBookmark &bm)
	{
	LPSAFEARRAY		psa = (LPSAFEARRAY)bm;
	DAORecordset *	prs = (DAORecordset *)GetInterface();

	DAOMFC_CALL(prs->put_CacheStart(&psa));
	}

LONG				CdbRecordset::GetCacheSize(
	VOID)
	{
	LPROPGET(DAORecordset, get_CacheSize);
	}

VOID				CdbRecordset::SetCacheSize(
	LONG l)
	{
	LPROPSET(DAORecordset, put_CacheSize, l);
	}

FLOAT				CdbRecordset::GetPercentPosition(
	VOID)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();
	FLOAT			f	= (FLOAT)0.0;

	if (!prs)
		return (FLOAT)0.0;

	DAOMFC_CALL(prs->get_PercentPosition(&f));

	return f;
	}

VOID				CdbRecordset::SetPercentPosition(
	FLOAT f)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();

	DAOMFC_CALL(prs->put_PercentPosition(f));
	}

LONG				CdbRecordset::GetAbsolutePosition(
	VOID)
	{
	LPROPGET(DAORecordset, get_AbsolutePosition);
	}
	
VOID				CdbRecordset::SetAbsolutePosition(
	LONG l)
	{
	LPROPSET(DAORecordset, put_AbsolutePosition, l);
	}

SHORT				CdbRecordset::GetEditMode(
	VOID)
	{
	WPROPGET(DAORecordset, get_EditMode);
	}
	
LONG				CdbRecordset::GetUpdateOptions(
	VOID)
	{
	LPROPGET(DAORecordset, get_UpdateOptions);
	}

VOID				CdbRecordset::SetUpdateOptions(
	LONG l)
	{
	LPROPSET(DAORecordset, put_UpdateOptions, l);
	}

SHORT 				CdbRecordset::GetRecordStatus(
	VOID)
	{
	WPROPGET(DAORecordset, get_RecordStatus);
	}
	
BOOL				CdbRecordset::GetStillExecuting(
	VOID)
	{
	BPROPGET(DAORecordset, get_StillExecuting);
	}

LONG				CdbRecordset::GetBatchSize(
	VOID)
	{
	LPROPGET(DAORecordset, get_BatchSize);
	}

VOID				CdbRecordset::SetBatchSize(
	LONG l)
	{
	LPROPSET(DAORecordset, put_BatchSize, l);
	}

LONG				CdbRecordset::GetBatchCollisionCount(
	VOID)
	{
	LPROPGET(DAORecordset, get_BatchCollisionCount);
	}

COleVariant			CdbRecordset::GetBatchCollisions(
	VOID)
	{
	VPROPGET(DAORecordset, get_BatchCollisions);
	}

CdbConnection		CdbRecordset::GetConnection(
	VOID)
	{
	DAORecordset *	prs		= (DAORecordset *)GetInterface();
	DAOConnection *	pconn	= NULL;

	if (!prs)
		return FALSE;

	DAOMFC_CALL(prs->get_Connection(&pconn));

	return pconn;
	}

// Methods
VOID				CdbRecordset::CancelUpdate(
	short sType) //dbUpdateRegular)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();

	DAOMFC_CALL(prs->CancelUpdate(sType));
	}

VOID				CdbRecordset::AddNew(
	VOID)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();

	DAOMFC_CALL(prs->AddNew());
	}

VOID				CdbRecordset::Close(
	VOID)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();

	DAOMFC_CALL(prs->Close());
	}

CdbRecordset		CdbRecordset::OpenRecordset(
	LONG	lType,		// = -1
	LONG 	lOption)	// = -1
	{
	DAORecordset *	prs		= (DAORecordset *)GetInterface();
	DAORecordset *	prsNew	= NULL;

	if (!prs)
		return (DAORecordset *)NULL;

	DAOMFC_CALL(prs->OpenRecordset(SHTV(lType), OLTV(lOption), &prsNew));

	return prsNew;
	}

VOID				CdbRecordset::Delete(
	VOID)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();

	DAOMFC_CALL(prs->Delete());
	}

VOID				CdbRecordset::Edit(
	VOID)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();

	DAOMFC_CALL(prs->Edit());
	}

VOID				CdbRecordset::FindFirst(
	LPCTSTR pstrCriteria)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();

	DAOMFC_CALL(prs->FindFirst(STB(pstrCriteria)));
	}

VOID				CdbRecordset::FindLast(
	LPCTSTR pstrCriteria)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();

	DAOMFC_CALL(prs->FindLast(STB(pstrCriteria)));
	}

VOID				CdbRecordset::FindNext(
	LPCTSTR pstrCriteria)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();

	DAOMFC_CALL(prs->FindNext(STB(pstrCriteria)));
	}

VOID				CdbRecordset::FindPrevious(
	LPCTSTR pstrCriteria)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();

	DAOMFC_CALL(prs->FindPrevious(STB(pstrCriteria)));
	}

VOID				CdbRecordset::MoveFirst(
	VOID)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();

	DAOMFC_CALL(prs->MoveFirst());
	}

VOID				CdbRecordset::MoveLast(
	LONG lOptions) // = -1
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();

	//DAO SDK functions default to -1 for longs, but since
	// this function is a strongly-typed optional, 0 is the
	// default. We need to convert this from -1 to 0
	if (lOptions == -1)
		lOptions = 0;
	DAOMFC_CALL(prs->MoveLast(lOptions));
	}

VOID				CdbRecordset::MoveNext(
	VOID)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();

	DAOMFC_CALL(prs->MoveNext());
	}

VOID				CdbRecordset::MovePrevious(
	VOID)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();

	DAOMFC_CALL(prs->MovePrevious());
	}


VOID				CdbRecordset::Seek(
	LPCTSTR	pstrComparison,
	LONG lNumFields,
	COleVariant	cKey,
	...)
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();
	COleVariant *	lpV;
	va_list			valist;
	CdbVariant		v[13];
	LONG			lIndex;

	ASSERT(lNumFields <= DAO_MAXSEEKFIELDS && lNumFields > 0);

	lpV = &cKey;
	va_start(valist, cKey);

	v[0] = *lpV;
	for(lIndex = 1; lIndex < lNumFields && (lpV = &(va_arg(valist, COleVariant))) != 0; lIndex++ )
		{
		v[lIndex] = *lpV;
		}

	va_end(valist);

	DAOMFC_CALL(prs->Seek(STB(pstrComparison), v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9], v[10], v[11], v[12]));
	}

VOID				CdbRecordset::Update(
	short			sType,	// = dbUpdateRegular
	VARIANT_BOOL	bForce) // = FALSE
	{
	DAORecordset *	prs = (DAORecordset *)GetInterface();

	DAOMFC_CALL(prs->Update(sType, bForce));
	}

CdbRecordset		CdbRecordset::Clone(
	VOID)
	{
	DAORecordset *	prs 	= (DAORecordset *)GetInterface();
	DAORecordset *	prsNew	= NULL;

	if (!prs)
		return FALSE;

	DAOMFC_CALL(prs->Clone(&prsNew));

	return prsNew;
	}

VOID				CdbRecordset::Requery(
	CdbQueryDef *pq)	// = NULL
	{
	DAORecordset *	prs 	= (DAORecordset *)GetInterface();
	COleVariant		Var;

	//Manually load the Query Def as a dispatch
	if (!pq)
		{
		Var.vt			= VT_ERROR;
		Var.scode		= DISP_E_PARAMNOTFOUND;
		}
	else
		{
		Var.vt			= VT_DISPATCH;
		Var.pdispVal	= (LPDISPATCH)pq->GetInterface();
		}

	DAOMFC_CALL(prs->Requery(Var));
	}

VOID				CdbRecordset::Move(
	LONG 			lRows,
	CdbBookmark 	*pbm)	// = NULL
	{
	LPSAFEARRAY		psa = NULL;
	COleVariant		Var;

	if(pbm)
		{
		SafeArrayCopy((LPSAFEARRAY)(*pbm), &psa);
		}

	DAORecordset *	prs 	= (DAORecordset *)GetInterface();

	//Load the safe array into the COleVariant
	ATV(psa, Var);

	DAOMFC_CALL(prs->Move(lRows, Var));
	}

VOID				CdbRecordset::FillCache(
	LONG 			lRows,	// = -1
	CdbBookmark *	pbm)	// = NULL
	{
	DAORecordset *	prs 	= (DAORecordset *)GetInterface();
	COleVariant		Var;

	//Load the safe array into the COleVariant
	ATV((pbm ? pbm->parray:NULL), Var);
		
	DAOMFC_CALL(prs->FillCache(OLTV(lRows), Var));
	}

CdbQueryDef			CdbRecordset::CopyQueryDef(
	VOID)
	{
	DAORecordset *	prs 	= (DAORecordset *)GetInterface();
	DAOQueryDef *	pqd		= NULL;

	if (!prs)
		return (DAOQueryDef *)NULL;

	DAOMFC_CALL(prs->CopyQueryDef(&pqd));

	return pqd;
	}

COleVariant			CdbRecordset::GetRows(
	LONG lRows)		// = -1
	{
	DAORecordset *	prs 	= (DAORecordset *)GetInterface();
	VARIANT			v;

	if (!prs)
		return (LPVARIANT)NULL;

	VariantInit(&v);
	DAOMFC_CALL(prs->GetRows(OLTV(lRows), &v));

	return v;
	}

LONG				CdbRecordset::GetRowsEx(
	LPVOID				pvBuffer,
	LONG				cbRow,
	LPDAORSETBINDING 	prb,
	LONG 				cBinding,
	LPVOID				pvVarBuffer, //= NULL
	LONG				cbVarBuffer, // = 0
	LONG				lRows)		// = -1
	{
	ICDAORecordset *	prs;
	DAOFETCHROWS		fetch;
	HRESULT				hresult;
	LONG				iBinding;
	
	ASSERT(cBinding > 0);
	ASSERT(prb != 0);

	//Clear flags
	fetch.dwFlags = 0;

	//The GetRowsEx interface isn't set until the first time this function
	//is called
	if(!m_GetRowsInt.Exists())
		SetGetRowsExInt();

	prs	= (ICDAORecordset *)m_GetRowsInt.GetInterface();

	if (!prs)
		return 0L;

	LPDAOCOLUMNBINDING 	pColumnBind = new DAOCOLUMNBINDING [cBinding];

	for(iBinding=0;iBinding<cBinding;iBinding++)
		{
		if(prb[iBinding].dwBindIndexType == dbBindIndexINT)
			{
			pColumnBind[iBinding].columnID.dwKind = DAOCOLKIND_IND;
			pColumnBind[iBinding].columnID.ind = prb[iBinding].i;
			}
		else
			{
#ifdef _UNICODE
			pColumnBind[iBinding].columnID.dwKind = DAOCOLKIND_WSTR;
			pColumnBind[iBinding].columnID.lpwstr = prb[iBinding].pstr;
#else
			pColumnBind[iBinding].columnID.dwKind = DAOCOLKIND_STR;
			pColumnBind[iBinding].columnID.lpstr = prb[iBinding].pstr;
#endif

			}
		pColumnBind[iBinding].cbDataOffset	= prb[iBinding].dwOffset;
		pColumnBind[iBinding].cbMaxLen		= prb[iBinding].cb;
		pColumnBind[iBinding].cbInfoOffset	= DAO_NOINDICATOR;
		
		//Variants bound differently
		if(prb[iBinding].dwType != dbBindVARIANT)
			{
			pColumnBind[iBinding].dwBinding		= DAOBINDING_DIRECT;
			}
		else
			{
			pColumnBind[iBinding].dwBinding		= DAOBINDING_VARIANT;
			}
		pColumnBind[iBinding].dwDataType	= prb[iBinding].dwType;
		pColumnBind[iBinding].dwUser		= 0;
		}

	fetch.cRowsRequested = lRows;
	fetch.pData = pvBuffer;
	fetch.pVarData = pvVarBuffer;
	fetch.cbVarData = cbVarBuffer;

	hresult = prs->GetRows(0, cBinding, (LPDAOCOLUMNBINDING)&pColumnBind[0], cbRow, (LPDAOFETCHROWS)&fetch);

	/* Since the DAO GetRowsEx interface will only deliver ANSI string data inside of
	   variants, we'll convert them here to UNICODE */

#ifdef UNICODE
	{
	LPVARIANT	lpV;
	LONG		lcb;
	BSTR		bstrNew;

	for(LONG iBinding=0;iBinding<cBinding;iBinding++)
		{
		if(pColumnBind[iBinding].dwBinding == DAOBINDING_VARIANT)
			{
			lpV = (LPVARIANT)(((char *)pvBuffer) + pColumnBind[iBinding].cbDataOffset);
			for(UINT i = 0; i < fetch.cRowsReturned; i++)
				{
				//If it's a string, convert it to UNICODE
				if(lpV->vt == VT_BSTR)
					{
					lcb = SysStringByteLen(lpV->bstrVal);
					if (!(bstrNew = SysAllocStringLen(NULL, lcb)))
						{
						hresult = ResultFromScode(E_OUTOFMEMORY);
						break;
						}
	
					// Convert from ANSI to WIDE
					if (lcb && !(lcb = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (LPSTR)lpV->bstrVal,
						lcb, (LPWSTR)bstrNew, lcb)))
						{
						SysFreeString(bstrNew);
						hresult = ResultFromScode(E_OUTOFMEMORY);
						break;
						}

					// Make sure it's NULL terminated
					((LPWSTR)(bstrNew))[lcb] = L'\0';

					SysFreeString(lpV->bstrVal);
					lpV->bstrVal = bstrNew;
					}
				lpV = (LPVARIANT)(((char *)lpV) + cbRow);
				}
			}
		}
	}
#endif

	delete [] pColumnBind;

	//Check return code
	signed long lErr;

	switch (GetScode(hresult))
		{
		case E_ROWTOOSHORT:
			lErr = errVtoRowLenTooSmall;
			break;

		case E_BADBINDINFO:
			lErr = errVtoBadBindInfo;
			break;

		case E_COLUMNUNAVAILABLE:
			lErr = errVtoColumnMissing;
			break;
			
		default:			
			lErr = 0L;
			}

	if(lErr)
		{
		prs->AddGetRowsErr(lErr);
		}

	if(FAILED(hresult)) 
		{
		TRACE0("\nGetRowsEX Call Failed.\n\t"); 
		TRACE2("\nIn file %s on line %d\n", _T("DBDAO.CPP"), __LINE__); \
		TRACE1("hResult = %X\n", hresult);
		if (GetScode(hresult) == E_OUTOFMEMORY)
			{
			AfxThrowMemoryException();
			}
		else
			{
			throw CdbException(hresult);
			}
	
		}

	return fetch.cRowsReturned;
	}

COleVariant			CdbRecordset::GetField(
	COleVariant &Index)
	{
	COleVariant vValue;

	GetFieldV(Index, vValue);
      
	return vValue;
	}

COleVariant			CdbRecordset::GetField(
	LPCTSTR pstrIndex)
	{
	COleVariant vValue;

	GetFieldV(STV(pstrIndex), vValue);
      
	return vValue;
	}

COleVariant			CdbRecordset::GetField(
	LONG lIndex)
	{
	COleVariant vValue;
	     
	GetFieldV(LTV(lIndex), vValue);
      
	return vValue;
	}

VOID			CdbRecordset::SetField(
	LPCTSTR pstrIndex,
	LPVARIANT pv)
	{
	SetFieldV(STV(pstrIndex), pv);
	}

VOID			CdbRecordset::SetField(
	COleVariant &Index,
	LPVARIANT pv)
	{
	SetFieldV(Index, pv);
	}

VOID			CdbRecordset::SetField(
	LONG lIndex,
	LPVARIANT pv)
	{
	SetFieldV(LTV(lIndex), pv);
	}

VOID			CdbRecordset::Cancel(
	VOID)
	{
	DAORecordset *	prs 	= (DAORecordset *)GetInterface();

	if (!prs)
		return;

	DAOMFC_CALL(prs->Cancel());
	}

BOOL			CdbRecordset::NextRecordset(
	VOID)
	{
	BPROPGET(DAORecordset, NextRecordset);
	}

/*****************************************************************************
* CdbGetRowsEx
*/
// Administration
CONSTRUCTOR			CdbGetRowsEx::CdbGetRowsEx(
	VOID)
	{
	}

CONSTRUCTOR			CdbGetRowsEx::CdbGetRowsEx(
	ICDAORecordset *	pGetRows,
	BOOL 		bAddRef)	// = FALSE
	{
	CdbOleObject::SetInterface((LPUNKNOWN)pGetRows, bAddRef);
	}

CONSTRUCTOR			CdbGetRowsEx::CdbGetRowsEx(
	const CdbGetRowsEx &o)
	{
	SetInterface(o.GetInterface(TRUE));
	}

CdbGetRowsEx &			CdbGetRowsEx::operator =(
	const CdbGetRowsEx &o)
	{
	SetInterface(o.GetInterface(TRUE));
	return *this;
	}


VOID			CdbGetRowsEx::OnInterfaceChange(
	VOID)
	{
	ICDAORecordset * pGetRows 	= (ICDAORecordset *)GetInterface();

	}


/*****************************************************************************
* CdbField
*/
// Administration
CONSTRUCTOR			CdbField::CdbField(
	VOID)
	{
	}

CONSTRUCTOR			CdbField::CdbField(
	DAOField *	pfld,
	BOOL 		bAddRef)	// = FALSE
	{
	CdbOleObject::SetInterface((LPUNKNOWN)pfld, bAddRef);
	}

CONSTRUCTOR			CdbField::CdbField(
	const CdbField &o)
	{
	SetInterface(o.GetInterface(TRUE));
	}

CdbField &			CdbField::operator =(
	const CdbField &o)
	{
	SetInterface(o.GetInterface(TRUE));
	return *this;
	}

VOID				CdbField::OnInterfaceChange(
	VOID)
	{
	DAOField *		pfld	= (DAOField *)GetInterface();
	DAOProperties *	pprps	= NULL;

	if (pfld)
		{
		pfld->get_Properties(&pprps);
		}

	Properties.SetInterface(pprps);
	}

// Properties
LONG				CdbField::GetCollatingOrder(
	VOID)
	{
	LPROPGET(DAOField, get_CollatingOrder);
	}

SHORT				CdbField::GetType(
	VOID)
	{
	WPROPGET(DAOField, get_Type);
	}

VOID				CdbField::SetType(
	SHORT s)
	{
	WPROPSET(DAOField, put_Type, s);
	}

CString				CdbField::GetName(
	VOID)
	{
	SPROPGET(DAOField, get_Name);
	}

VOID				CdbField::SetName(
	LPCTSTR pstr)
	{
	SPROPSET(DAOField, put_Name, pstr);
	}

LONG				CdbField::GetSize(
	VOID)
	{
	LPROPGET(DAOField, get_Size);
	}

VOID				CdbField::SetSize(
	LONG l)
	{
	LPROPSET(DAOField, put_Size, l);
	}

CString				CdbField::GetSourceField(
	VOID)
	{
	SPROPGET(DAOField, get_SourceField);
	}

CString				CdbField::GetSourceTable(
	VOID)
	{
	SPROPGET(DAOField, get_SourceTable);
	}

COleVariant			CdbField::GetValue(
	VOID)
	{
	VPROPGET(DAOField, get_Value);
	}


VOID				CdbField::SetValue(
	LPVARIANT pv)
	{
	VPROPSET(DAOField, put_Value, pv);
	}

LONG				CdbField::GetAttributes(
	VOID)
	{
	LPROPGET(DAOField, get_Attributes);
	}

VOID				CdbField::SetAttributes(
	LONG l)
	{
	LPROPSET(DAOField, put_Attributes, l);
	}

SHORT				CdbField::GetOrdinalPosition(
	VOID)
	{
	WPROPGET(DAOField, get_OrdinalPosition);
	}

VOID				CdbField::SetOrdinalPosition(
	SHORT s)
	{
	WPROPSET(DAOField, put_OrdinalPosition, s);
	}

CString				CdbField::GetValidationText(
	VOID)
	{
	SPROPGET(DAOField, get_ValidationText);
	}

VOID				CdbField::SetValidationText(
	LPCTSTR pstr)
	{
	SPROPSET(DAOField, put_ValidationText, pstr);
	}

BOOL				CdbField::GetValidateOnSet(
	VOID)
	{
	BPROPGET(DAOField, get_ValidateOnSet);
	}

VOID				CdbField::SetValidateOnSet(
	BOOL b)
	{
	BPROPSET(DAOField, put_ValidateOnSet, b);
	}

CString				CdbField::GetValidationRule(
	VOID)
	{
	SPROPGET(DAOField, get_ValidationRule);
	}

VOID				CdbField::SetValidationRule(
	LPCTSTR pstr)
	{
	SPROPSET(DAOField, put_ValidationRule, pstr);
	}

VOID				CdbField::SetDefaultValue(
	LPCTSTR pstr)
	{
	VPROPSET(DAOField, put_DefaultValue, STV(pstr));
	}

CString				CdbField::GetDefaultValue(
	VOID)
	{
	DAOField *		pfld	= (DAOField *)GetInterface();
	VARIANT			vDAO;

	if (!pfld)
		return (LPCSTR)NULL;

	VariantInit(&vDAO);
	DAOMFC_CALL(pfld->get_DefaultValue(&vDAO));

	//User is expecting a CString so force this variant into one.
	if(GetScode((VariantChangeType(&vDAO, &vDAO, 0, VT_BSTR))) != S_OK)
		{
		return (LPCTSTR)NULL;
		}

	return((LPCTSTR)vDAO.bstrVal);
	}

VOID				CdbField::SetDefaultValue(
	LPVARIANT pv)
	{
	VPROPSET(DAOField, put_DefaultValue, pv);
	}

BOOL				CdbField::GetRequired(
	VOID)
	{
	BPROPGET(DAOField, get_Required);
	}

VOID				CdbField::SetRequired(
	BOOL b)
	{
	BPROPSET(DAOField, put_Required, b);
	}

BOOL				CdbField::GetAllowZeroLength(
	VOID)
	{
	BPROPGET(DAOField, get_AllowZeroLength);
	}

VOID				CdbField::SetAllowZeroLength(
	BOOL b)
	{
	BPROPSET(DAOField, put_AllowZeroLength, b);
	}

BOOL				CdbField::GetDataUpdatable(
	VOID)
	{
	BPROPGET(DAOField, get_DataUpdatable);
	}

CString				CdbField::GetForeignName(
	VOID)
	{
	SPROPGET(DAOField, get_ForeignName);
	}

VOID				CdbField::SetForeignName(
	LPCTSTR pstr)
	{
	SPROPSET(DAOField, put_ForeignName, pstr);
	}

COleVariant			CdbField::GetOriginalValue(
	VOID)
	{
	VPROPGET(DAOField, get_OriginalValue);
	}

COleVariant			CdbField::GetVisibleValue(
	VOID)
	{
	VPROPGET(DAOField, get_VisibleValue);
	}

// Methods
VOID				CdbField::AppendChunk(
	LPVARIANT pv)
	{
	DAOField *		pfld	= (DAOField *)GetInterface();

	DAOMFC_CALL(pfld->AppendChunk(*pv));
	}

COleVariant			CdbField::GetChunk(
	LONG lOffset,
	LONG lBytes)
	{
	DAOField *		pfld	= (DAOField *)GetInterface();
	COleVariant		v;

	if (!pfld)
		return (LPVARIANT)NULL;

	VariantInit(&v);
	DAOMFC_CALL(pfld->GetChunk(lOffset, lBytes, &v));

	return &v;
	}

LONG				CdbField::FieldSize(
	VOID)
	{
	DAOField *		pfld	= (DAOField *)GetInterface();
	LONG			l		= 0;

	if (!pfld)
		return 0;

	DAOMFC_CALL(pfld->get_FieldSize(&l));

	return l;
	}

CdbProperty			CdbField::CreateProperty(
	LPCTSTR		pstrName,	// = NULL
	LONG		lType,		// = -1
	LPVARIANT	pvValue,	// = NULL
	BOOL		bDDL)		// = FALSE
	{
	DAOField *	pfld		= (DAOField *)GetInterface();
	DAOProperty *	pprp	= NULL;

	if (!pfld)
		return (DAOProperty *)NULL;

	DAOMFC_CALL(pfld->CreateProperty(STV(pstrName), OLTV(lType), VTV(pvValue), BTV(bDDL), &pprp));

	return pprp;
	}

/*****************************************************************************
* CdbQueryDef
*/
// Administration
CONSTRUCTOR			CdbQueryDef::CdbQueryDef(
	VOID)
	{
	}

CONSTRUCTOR			CdbQueryDef::CdbQueryDef(
	DAOQueryDef *	pqd,
	BOOL 			bAddRef)	// FALSE
	{
	CdbOleObject::SetInterface((LPUNKNOWN)pqd, bAddRef);
	}

CONSTRUCTOR			CdbQueryDef::CdbQueryDef(
	const CdbQueryDef &o)
	{
	SetInterface(o.GetInterface(TRUE));
	}

CdbQueryDef &		CdbQueryDef::operator =(
	const CdbQueryDef &o)
	{
	SetInterface(o.GetInterface(TRUE));
	return *this;
	}

VOID				CdbQueryDef::OnInterfaceChange(
	VOID)
	{
	DAOQueryDef *	pqd		= (DAOQueryDef *)GetInterface();
	DAOProperties *	pprps	= NULL;
	DAOFields *		pflds	= NULL;
	DAOParameters *	pprms	= NULL;

	if (pqd)
		{
		pqd->get_Properties(&pprps);
		pqd->get_Fields(&pflds);
		pqd->get_Parameters(&pprms);
		}

	Properties.SetInterface(pprps);
	Fields.SetInterface(pflds);
	Parameters.SetInterface(pprms);
	}

// Properties
COleDateTime			CdbQueryDef::GetDateCreated(
	VOID)
	{
	DPROPGET(DAOQueryDef, get_DateCreated);
	}

COleDateTime			CdbQueryDef::GetLastUpdated(
	VOID)
	{
	DPROPGET(DAOQueryDef, get_LastUpdated);
	}

CString				CdbQueryDef::GetName(
	VOID)
	{
	SPROPGET(DAOQueryDef, get_Name);
	}

VOID				CdbQueryDef::SetName(
	LPCTSTR pstr)
	{
	SPROPSET(DAOQueryDef, put_Name, pstr);
	}

SHORT				CdbQueryDef::GetODBCTimeout(
	VOID)
	{
	WPROPGET(DAOQueryDef, get_ODBCTimeout);
	}

VOID				CdbQueryDef::SetODBCTimeout(
	SHORT s)
	{
	WPROPSET(DAOQueryDef, put_ODBCTimeout, s);
	}

SHORT				CdbQueryDef::GetType(
	VOID)
	{
	WPROPGET(DAOQueryDef, get_Type);
	}

CString				CdbQueryDef::GetSQL(
	VOID)
	{
	SPROPGET(DAOQueryDef, get_SQL);
	}

VOID				CdbQueryDef::SetSQL(
	LPCTSTR pstr)
	{
	SPROPSET(DAOQueryDef, put_SQL, pstr);
	}

BOOL				CdbQueryDef::GetUpdatable(
	VOID)
	{
	BPROPGET(DAOQueryDef, get_Updatable);
	}

CString				CdbQueryDef::GetConnect(
	VOID)
	{
	SPROPGET(DAOQueryDef, get_Connect);
	}

VOID				CdbQueryDef::SetConnect(
	LPCTSTR pstr)
	{
	SPROPSET(DAOQueryDef, put_Connect, pstr);
	}

BOOL				CdbQueryDef::GetReturnsRecords(
	VOID)
	{
	BPROPGET(DAOQueryDef, get_ReturnsRecords);
	}

VOID				CdbQueryDef::SetReturnsRecords(
	BOOL b)
	{
	BPROPSET(DAOQueryDef, put_ReturnsRecords, b);
	}

LONG				CdbQueryDef::GetRecordsAffected(
	VOID)
	{
	LPROPGET(DAOQueryDef, get_RecordsAffected);
	}

LONG				CdbQueryDef::GetMaxRecords(
	VOID)
	{
	LPROPGET(DAOQueryDef, get_MaxRecords);
	}

VOID				CdbQueryDef::SetMaxRecords(
	LONG l)
	{
	LPROPSET(DAOQueryDef, put_MaxRecords, l);
	}

BOOL				CdbQueryDef::GetStillExecuting(
	VOID)
	{
	BPROPGET(DAOQueryDef, get_StillExecuting);
	}

LONG				CdbQueryDef::GetCacheSize(
	VOID)
	{
	LPROPGET(DAOQueryDef, get_CacheSize);
	}

VOID				CdbQueryDef::SetCacheSize(
	LONG l)
	{
	LPROPSET(DAOQueryDef, put_CacheSize, l);
	}

COleVariant			CdbQueryDef::GetPrepare(
	VOID)
	{
	VPROPGET(DAOQueryDef, get_Prepare);
	}

VOID				CdbQueryDef::SetPrepare(
	LPVARIANT pv)
	{
	DAOQueryDef *	pqd	= (DAOQueryDef *)GetInterface();

	DAOMFC_CALL(pqd->put_Prepare(*pv));
	}

// Methods
CdbRecordset		CdbQueryDef::OpenRecordset(
	LONG lType,		// = -1
	LONG lOption,	// = -1
	LONG lLockEdit) // = -1
	{
	DAOQueryDef *	pqd = (DAOQueryDef *)GetInterface();
	DAORecordset *	prs	= NULL;

	if (!pqd)
		return (DAORecordset *)NULL;

	DAOMFC_CALL(pqd->OpenRecordset(OLTV(lType), OLTV(lOption), OLTV(lLockEdit), &prs));

	return prs;
	}

VOID				CdbQueryDef::Execute(
	LONG lOption)	// = -1
	{
	DAOQueryDef *	pqd = (DAOQueryDef *)GetInterface();

	DAOMFC_CALL(pqd->Execute(OLTV(lOption)));
	}

CdbProperty			CdbQueryDef::CreateProperty(
	LPCTSTR		pstrName,	// = NULL
	LONG		lType,		// = -1
	LPVARIANT	pvValue,	// = NULL
	BOOL		bDDL)		// = FALSE
	{
	DAOQueryDef *	pqd		= (DAOQueryDef *)GetInterface();
	DAOProperty *	pprp	= NULL;

	if (!pqd)
		return (DAOProperty *)NULL;

	DAOMFC_CALL(pqd->CreateProperty(STV(pstrName), OLTV(lType), VTV(pvValue), BTV(bDDL), &pprp));

	return pprp;
	}

VOID				CdbQueryDef::Close(
	VOID)
	{
	DAOQueryDef *	pqd = (DAOQueryDef *)GetInterface();

	if (!pqd)
		return;

	DAOMFC_CALL(pqd->Close());
	}

VOID				CdbQueryDef::Cancel(
	VOID)
	{
	DAOQueryDef *	pqd = (DAOQueryDef *)GetInterface();

	if (!pqd)
		return;

	DAOMFC_CALL(pqd->Cancel());
	}

/*****************************************************************************
* CdbTableDef
*/
// Administration
CONSTRUCTOR			CdbTableDef::CdbTableDef(
	VOID)
	{
	}

CONSTRUCTOR			CdbTableDef::CdbTableDef(
	DAOTableDef *	ptd,
	BOOL 			bAddRef)	// = FALSE
	{
	CdbOleObject::SetInterface((LPUNKNOWN)ptd, bAddRef);
	}

CONSTRUCTOR			CdbTableDef::CdbTableDef(
	const CdbTableDef &o)
	{
	SetInterface(o.GetInterface(TRUE));
	}

CdbTableDef &		CdbTableDef::operator =(
	const CdbTableDef &o)
	{
	SetInterface(o.GetInterface(TRUE));
	return *this;
	}

VOID				CdbTableDef::OnInterfaceChange(
	VOID)
	{
	DAOTableDef *	ptd		= (DAOTableDef *)GetInterface();
	DAOProperties *	pprps	= NULL;
	DAOFields *		pflds	= NULL;
	DAOIndexes *	pidxs	= NULL;

	if (ptd)
		{
		ptd->get_Properties(&pprps);
		ptd->get_Fields(&pflds);
		ptd->get_Indexes(&pidxs);
		}

	Properties.SetInterface(pprps);
	Fields.SetInterface(pflds);
	Indexes.SetInterface(pidxs);
	}

// Properties
LONG				CdbTableDef::GetAttributes(
	VOID)
	{
	LPROPGET(DAOTableDef, get_Attributes);
	}

VOID				CdbTableDef::SetAttributes(
	LONG l)
	{
	LPROPSET(DAOTableDef, put_Attributes, l);
	}

CString				CdbTableDef::GetConnect(
	VOID)
	{
	SPROPGET(DAOTableDef, get_Connect);
	}

VOID				CdbTableDef::SetConnect(
	LPCTSTR pstr)
	{
	SPROPSET(DAOTableDef, put_Connect, pstr);
	}

COleDateTime			CdbTableDef::GetDateCreated(
	VOID)
	{
	DPROPGET(DAOTableDef, get_DateCreated);
	}

COleDateTime			CdbTableDef::GetLastUpdated(
	VOID)
	{
	DPROPGET(DAOTableDef, get_LastUpdated);
	}

CString				CdbTableDef::GetName(
	VOID)
	{
	SPROPGET(DAOTableDef, get_Name);
	}

VOID				CdbTableDef::SetName(
	LPCTSTR pstr)
	{
	SPROPSET(DAOTableDef, put_Name, pstr);
	}

CString				CdbTableDef::GetSourceTableName(
	VOID)
	{
	SPROPGET(DAOTableDef, get_SourceTableName);
	}

VOID				CdbTableDef::SetSourceTableName(
	LPCTSTR pstr)
	{
	SPROPSET(DAOTableDef, put_SourceTableName, pstr);
	}

BOOL				CdbTableDef::GetUpdatable(
	VOID)
	{
	BPROPGET(DAOTableDef, get_Updatable);
	}

CString				CdbTableDef::GetValidationText(
	VOID)
	{
	SPROPGET(DAOTableDef, get_ValidationText);
	}

VOID				CdbTableDef::SetValidationText(
	LPCTSTR pstr)
	{
	SPROPSET(DAOTableDef, put_ValidationText, pstr);
	}

CString				CdbTableDef::GetValidationRule(
	VOID)
	{
	SPROPGET(DAOTableDef, get_ValidationRule);
	}

VOID				CdbTableDef::SetValidationRule(
	LPCTSTR pstr)
	{
	SPROPSET(DAOTableDef, put_ValidationRule, pstr);
	}

LONG				CdbTableDef::GetRecordCount(
	VOID)
	{
	LPROPGET(DAOTableDef, get_RecordCount);
	}

CString				CdbTableDef::GetConflictTable(
	VOID)
	{
	SPROPGET(DAOTableDef, get_ConflictTable);
	}

COleVariant			CdbTableDef::GetReplicaFilter(
	VOID)
	{
	VPROPGET(DAOTableDef, get_ReplicaFilter);
	}

VOID				CdbTableDef::SetReplicaFilter(
	LPVARIANT pv)
	{
	VPROPSET(DAOTableDef, put_ReplicaFilter, pv);
	}


// Methods
CdbRecordset		CdbTableDef::OpenRecordset(
	LONG lType,		// = -1
	LONG lOption)	// = -1
	{
	DAOTableDef *	ptd		= (DAOTableDef *)GetInterface();
	DAORecordset *	prs		= NULL;

	if (!ptd)
		return (DAORecordset *)NULL;

	DAOMFC_CALL(ptd->OpenRecordset(OLTV(lType), OLTV(lOption), &prs));

	return prs;
	}

VOID				CdbTableDef::RefreshLink(
	VOID)
	{
	DAOTableDef *	ptd		= (DAOTableDef *)GetInterface();

	DAOMFC_CALL(ptd->RefreshLink());
	}

CdbField			CdbTableDef::CreateField(
	LPCTSTR	pstrName,	// = NULL
	LONG	lType,		// = -1
	LONG	lSize)		// = -1
	{
	DAOTableDef *	ptd		= (DAOTableDef *)GetInterface();
	DAOField *		pfld	= NULL;

	if (!ptd)
		return (DAOField *)NULL;

	DAOMFC_CALL(ptd->CreateField(STV(pstrName), OLTV(lType), OLTV(lSize), &pfld));

	return pfld;
	}

CdbIndex			CdbTableDef::CreateIndex(
	LPCTSTR pstrName)	// = NULL
	{
	DAOTableDef *	ptd		= (DAOTableDef *)GetInterface();
	DAOIndex *		pidx	= NULL;

	if (!ptd)
		return (DAOIndex *)NULL;

	DAOMFC_CALL(ptd->CreateIndex(STV(pstrName), &pidx));

	return pidx;
	}

CdbProperty			CdbTableDef::CreateProperty(
	LPCTSTR		pstrName,	// = NULL
	LONG		lType,		// = -1
	LPVARIANT	pvValue,	// = NULL
	BOOL		bDDL)		// = FALSE
	{
	DAOTableDef *	ptd		= (DAOTableDef *)GetInterface();
	DAOProperty *	pprp	= NULL;

	if (!ptd)
		return (DAOProperty *)NULL;

	DAOMFC_CALL(ptd->CreateProperty(STV(pstrName), OLTV(lType), VTV(pvValue), BTV(bDDL), &pprp));

	return pprp;
	}

/*****************************************************************************
* CdbIndex
*/
// Administration
CONSTRUCTOR			CdbIndex::CdbIndex(
	VOID)
	{
	}

CONSTRUCTOR			CdbIndex::CdbIndex(
	DAOIndex *	pidx,
	BOOL 		bAddRef)	// = FALSE
	{
	CdbOleObject::SetInterface((LPUNKNOWN)pidx, bAddRef);
	}

CONSTRUCTOR			CdbIndex::CdbIndex(
	const CdbIndex &o)
	{
	SetInterface(o.GetInterface(TRUE));
	}

CdbIndex &			CdbIndex::operator =(
	const CdbIndex &o)
	{
	SetInterface(o.GetInterface(TRUE));
	return *this;
	}

VOID				CdbIndex::OnInterfaceChange(
	VOID)
	{
	DAOIndex *		pidx	= (DAOIndex *)GetInterface();
	DAOProperties *	pprps	= NULL;
	DAOFields *		pflds	= NULL;

	if (pidx)
		{
		VARIANT	v;

		VariantInit(&v);

		pidx->get_Properties(&pprps);
		pidx->get_Fields(&v);

		v.pdispVal->QueryInterface(dbIID_IDAOIndexFields, (LPVOID *)&pflds);
		v.pdispVal->Release();
		}

	Properties.SetInterface(pprps);
	Fields.SetInterface(pflds);
	}

// Properties
CString				CdbIndex::GetName(
	VOID)
	{
	SPROPGET(DAOIndex, get_Name);
	}

VOID				CdbIndex::SetName(
	LPCTSTR pstr)
	{
	SPROPSET(DAOIndex, put_Name, pstr);
	}

BOOL				CdbIndex::GetForeign(
	VOID)
	{
	BPROPGET(DAOIndex, get_Foreign);
	}

BOOL				CdbIndex::GetUnique(
	VOID)
	{
	BPROPGET(DAOIndex, get_Unique);
	}

VOID				CdbIndex::SetUnique(
	BOOL b)
	{
	BPROPSET(DAOIndex, put_Unique, b);
	}

BOOL				CdbIndex::GetClustered(
	VOID)
	{
	BPROPGET(DAOIndex, get_Clustered);
	}

VOID				CdbIndex::SetClustered(
	BOOL b)
	{
	BPROPSET(DAOIndex, put_Clustered, b);
	}

BOOL				CdbIndex::GetRequired(
	VOID)
	{
	BPROPGET(DAOIndex, get_Required);
	}

VOID				CdbIndex::SetRequired(
	BOOL b)
	{
	BPROPSET(DAOIndex, put_Required, b);
	}

BOOL				CdbIndex::GetIgnoreNulls(
	VOID)
	{
	BPROPGET(DAOIndex, get_IgnoreNulls);
	}

VOID				CdbIndex::SetIgnoreNulls(
	BOOL b)
	{
	BPROPSET(DAOIndex, put_IgnoreNulls, b);
	}

BOOL				CdbIndex::GetPrimary(
	VOID)
	{
	BPROPGET(DAOIndex, get_Primary);
	}

VOID				CdbIndex::SetPrimary(
	BOOL b)
	{
	BPROPSET(DAOIndex, put_Primary, b);
	}

LONG				CdbIndex::GetDistinctCount(
	VOID)
	{
	LPROPGET(DAOIndex, get_DistinctCount);
	}


// Methods
CdbField			CdbIndex::CreateField(
	LPCTSTR	pstrName,	// = NULL
	LONG	lType,		// = -1
	LONG	lSize)		// = -1
	{
	DAOIndex *		pidx	= (DAOIndex *)GetInterface();
	DAOField *		pfld	= NULL;

	if (!pidx)
		return (DAOField *)NULL;

	DAOMFC_CALL(pidx->CreateField(STV(pstrName), OLTV(lType), OLTV(lSize), &pfld));

	return pfld;
	}

CdbProperty			CdbIndex::CreateProperty(
	LPCTSTR		pstrName,	// = NULL
	LONG		lType,		// = -1
	LPVARIANT	pvValue,	// = NULL
	BOOL		bDDL)		// = FALSE
	{
	DAOIndex *		pidx	= (DAOIndex *)GetInterface();
	DAOProperty *	pprp	= NULL;

	if (!pidx)
		return (DAOProperty *)NULL;

	DAOMFC_CALL(pidx->CreateProperty(STV(pstrName), OLTV(lType), VTV(pvValue), BTV(bDDL), &pprp));

	return pprp;
	}


/*****************************************************************************
* CdbProperty
*/
// Administration
CONSTRUCTOR			CdbProperty::CdbProperty(
	VOID)
	{
	}

CONSTRUCTOR			CdbProperty::CdbProperty(
	DAOProperty *	pprp,
	BOOL			bAddRef)	// = FALSE
	{
	SetInterface((LPUNKNOWN)pprp, bAddRef);
	}

CONSTRUCTOR			CdbProperty::CdbProperty(
	const CdbProperty &o)
	{
	SetInterface(o.GetInterface(TRUE));
	}

CdbProperty &		CdbProperty::operator =(
	const CdbProperty &o)
	{
	SetInterface(o.GetInterface(TRUE));
	return *this;
	}

// Properties
COleVariant			CdbProperty::GetValue(
	VOID)
	{
	DAOProperty *	pprp = (DAOProperty *)GetInterface();
	COleVariant		v;

	if (!pprp)
		return v;

	DAOMFC_CALL(pprp->get_Value((LPVARIANT)v));

	return v;
	}

VOID				CdbProperty::SetValue(
	LPVARIANT pv)
	{
	DAOProperty *	pprp = (DAOProperty *)GetInterface();

	DAOMFC_CALL(pprp->put_Value(*pv));
	}

CString				CdbProperty::GetName(
	VOID)
	{
	DAOProperty *	pprp = (DAOProperty *)GetInterface();
	CdbBSTR			bstr;

	if (!pprp)
		return (LPCTSTR)NULL;

	DAOMFC_CALL(pprp->get_Name(bstr));

	return bstr;
	}

VOID				CdbProperty::SetName(
	LPCTSTR pstrName)
	{
	DAOProperty *	pprp = (DAOProperty *)GetInterface();

	DAOMFC_CALL(pprp->put_Name(STB(pstrName)));
	}

SHORT				CdbProperty::GetType(
	VOID)
	{
	DAOProperty *	pprp 	= (DAOProperty *)GetInterface();
	SHORT			s		= 0;

	if (!pprp)
		return 0;

	DAOMFC_CALL(pprp->get_Type(&s));

	return s;
	}

VOID				CdbProperty::SetType(
	SHORT sType)
	{
	DAOProperty *	pprp = (DAOProperty *)GetInterface();

	DAOMFC_CALL(pprp->put_Type(sType));
	}

BOOL				CdbProperty::GetInherited(
	VOID)
	{
	DAOProperty *	pprp	= (DAOProperty *)GetInterface();
	VARIANT_BOOL	vb		= 0;

	if (!pprp)
		return FALSE;

	DAOMFC_CALL(pprp->get_Inherited(&vb));

	return (BOOL)vb;
	}


/*****************************************************************************
* CdbParameter
*/
// Administration
CONSTRUCTOR			CdbParameter::CdbParameter(
	VOID)
	{
	}

CONSTRUCTOR			CdbParameter::CdbParameter(
	DAOParameter *	pprm,
	BOOL 			bAddRef)	// = FALSE
	{
	CdbOleObject::SetInterface((LPUNKNOWN)pprm, bAddRef);
	}

CONSTRUCTOR			CdbParameter::CdbParameter(
	const CdbParameter &o)
	{
	SetInterface(o.GetInterface(TRUE));
	}

CdbParameter &		CdbParameter::operator =(
	const CdbParameter &o)
	{
	SetInterface(o.GetInterface(TRUE));
	return *this;
	}

VOID				CdbParameter::OnInterfaceChange(
	VOID)
	{
	DAOParameter *	pprm	= (DAOParameter *)GetInterface();
	DAOProperties *	pprps	= NULL;

	if (pprm)
		pprm->get_Properties(&pprps);

	Properties.SetInterface(pprps);
	}

// Properties
CString				CdbParameter::GetName(
	VOID)
	{
	SPROPGET(DAOParameter, get_Name);
	}

COleVariant			CdbParameter::GetValue(
	VOID)
	{
	VPROPGET(DAOParameter, get_Value);
	}

VOID				CdbParameter::SetValue(
	LPVARIANT pv)
	{
	VPROPSET(DAOParameter, put_Value, pv);
	}

SHORT				CdbParameter::GetType(
	VOID)
	{
	WPROPGET(DAOParameter, get_Type);
	}

VOID				CdbParameter::SetType(
	SHORT i)
	{
	WPROPSET(DAOParameter, put_Type, i);
	}

SHORT				CdbParameter::GetDirection(
	VOID)
	{
	WPROPGET(DAOParameter, get_Direction);
	}

VOID				CdbParameter::SetDirection(
	SHORT i)
	{
	WPROPSET(DAOParameter, put_Direction, i);
	}

/*****************************************************************************
* CdbRelation
*/
// Administration
CONSTRUCTOR			CdbRelation::CdbRelation(
	VOID)
	{
	}

CONSTRUCTOR			CdbRelation::CdbRelation(
	DAORelation *	prl,
	BOOL 			bAddRef)	// = FALSE
	{
	CdbOleObject::SetInterface((LPUNKNOWN)prl, bAddRef);
	}

CONSTRUCTOR			CdbRelation::CdbRelation(
	const CdbRelation &o)
	{
	SetInterface(o.GetInterface(TRUE));
	}

CdbRelation &		CdbRelation::operator =(
	const CdbRelation &o)
	{
	SetInterface(o.GetInterface(TRUE));
	return *this;
	}

VOID				CdbRelation::OnInterfaceChange(
	VOID)
	{
	DAORelation *	prl		= (DAORelation *)GetInterface();
	DAOProperties *	pprps	= NULL;
	DAOFields *		pflds	= NULL;

	if (prl)
		{
		prl->get_Properties(&pprps);
		prl->get_Fields(&pflds);
		}

	Properties.SetInterface(pprps);
	Fields.SetInterface(pflds);
	}

// Properties
CString				CdbRelation::GetName(
	VOID)
	{
	SPROPGET(DAORelation, get_Name);
	}

VOID				CdbRelation::SetName(
	LPCTSTR pstr)
	{
	SPROPSET(DAORelation, put_Name, pstr);
	}

CString				CdbRelation::GetTable(
	VOID)
	{
	SPROPGET(DAORelation, get_Table);
	}

VOID				CdbRelation::SetTable(
	LPCTSTR pstr)
	{
	SPROPSET(DAORelation, put_Table, pstr);
	}

CString				CdbRelation::GetForeignTable(
	VOID)
	{
	SPROPGET(DAORelation, get_ForeignTable);
	}

VOID				CdbRelation::SetForeignTable(
	LPCTSTR pstr)
	{
	SPROPSET(DAORelation, put_ForeignTable, pstr);
	}

LONG				CdbRelation::GetAttributes(
	VOID)
	{
	LPROPGET(DAORelation, get_Attributes);
	}

VOID				CdbRelation::SetAttributes(
	LONG l)
	{
	LPROPSET(DAORelation, put_Attributes, l);
	}

BOOL				CdbRelation::GetPartialReplica(
	VOID)
	{
	BPROPGET(DAORelation, get_PartialReplica);
	}

VOID				CdbRelation::SetPartialReplica(
	BOOL b)
	{
	BPROPSET(DAORelation, put_PartialReplica, b);
	}

// Methods
CdbField			CdbRelation::CreateField(
	LPCTSTR	pstrName,	// = NULL
	LONG	lType,		// = -1
	LONG	lSize)		// = -1
	{
	DAORelation *	prl		= (DAORelation *)GetInterface();
	DAOField *		pfld	= NULL;

	if (!prl)
		return (DAOField *)NULL;

	DAOMFC_CALL(prl->CreateField(STV(pstrName), OLTV(lType), OLTV(lSize), &pfld));

	return pfld;
	}


/*****************************************************************************
* CdbUser
*/
// Administration
CONSTRUCTOR			CdbUser::CdbUser(
	VOID)
	{
	}

CONSTRUCTOR			CdbUser::CdbUser(
	DAOUser *	pusr,
	BOOL 		bAddRef)	// = FALSE
	{
	CdbOleObject::SetInterface((LPUNKNOWN)pusr, bAddRef);
	}

CONSTRUCTOR			CdbUser::CdbUser(
	const CdbUser &o)
	{
	SetInterface(o.GetInterface(TRUE));
	}

CdbUser &			CdbUser::operator =(
	const CdbUser &o)
	{
	SetInterface(o.GetInterface(TRUE));
	return *this;
	}

VOID				CdbUser::OnInterfaceChange(
	VOID)
	{
	DAOUser *		pusr 	= (DAOUser *)GetInterface();
	DAOProperties *	pprps	= NULL;
	DAOGroups *		pgrps	= NULL;

	if (pusr)
		{
		pusr->get_Properties(&pprps);
		pusr->get_Groups(&pgrps);
		}

	Properties.SetInterface(pprps);
	Groups.SetInterface(pgrps);
	}

// Properties
CString				CdbUser::GetName(
	VOID)
	{
	SPROPGET(DAOUser, get_Name);
	}

VOID				CdbUser::SetName(
	LPCTSTR pstr)
	{
	SPROPSET(DAOUser, put_Name, pstr);
	}

VOID				CdbUser::SetPID(
	LPCTSTR pstr)
	{
	SPROPSET(DAOUser, put_PID, pstr);
	}

VOID				CdbUser::SetPassword(
	LPCTSTR pstr)
	{
	SPROPSET(DAOUser, put_Password, pstr);
	}

// Methods
VOID				CdbUser::NewPassword(
	LPCTSTR	pstrOld,
	LPCTSTR	pstrNew)
	{
	DAOUser *		pusr 	= (DAOUser *)GetInterface();

	DAOMFC_CALL(pusr->NewPassword(STB(pstrOld), STB(pstrNew)));
	}

CdbGroup			CdbUser::CreateGroup(
	LPCTSTR pstrName,	// = NULL
	LPCTSTR pstrPID)	// = NULL
	{
	DAOUser *		pusr 	= (DAOUser *)GetInterface();
	DAOGroup *		pgrp	= NULL;

	if (!pusr)
		return FALSE;

	DAOMFC_CALL(pusr->CreateGroup(STV(pstrName), STV(pstrPID), &pgrp));

	return pgrp;
	}

/*****************************************************************************
* CdbGroup
*/
// Administration
CONSTRUCTOR			CdbGroup::CdbGroup(
	VOID)
	{
	}

CONSTRUCTOR			CdbGroup::CdbGroup(
	DAOGroup *	pgrp,
	BOOL 		bAddRef)	// = FALSE
	{
	CdbOleObject::SetInterface((LPUNKNOWN)pgrp, bAddRef);
	}

CONSTRUCTOR			CdbGroup::CdbGroup(
	const CdbGroup &o)
	{
	SetInterface(o.GetInterface(TRUE));
	}

CdbGroup &			CdbGroup::operator =(
	const CdbGroup &o)
	{
	SetInterface(o.GetInterface(TRUE));
	return *this;
	}

VOID				CdbGroup::OnInterfaceChange(
	VOID)
	{
	DAOGroup *		pgrp 	= (DAOGroup *)GetInterface();
	DAOProperties *	pprps	= NULL;
	DAOUsers *		pusrs	= NULL;

	if (pgrp)
		{
		pgrp->get_Properties(&pprps);
		pgrp->get_Users(&pusrs);
		}

	Properties.SetInterface(pprps);
	Users.SetInterface(pusrs);
	}

// Properties
CString				CdbGroup::GetName(
	VOID)
	{
	SPROPGET(DAOGroup, get_Name);
	}

VOID				CdbGroup::SetName(
	LPCTSTR pstr)
	{
	SPROPSET(DAOGroup, put_Name, pstr);
	}

VOID				CdbGroup::SetPID(
	LPCTSTR pstr)
	{
	SPROPSET(DAOGroup, put_PID, pstr);
	}

// Methods
CdbUser				CdbGroup::CreateUser(
	LPCTSTR pstrName,		// = NULL
	LPCTSTR pstrPID,		// = NULL
	LPCTSTR	pstrPassword)	// = NULL
	{
	DAOGroup *		pgrp 	= (DAOGroup *)GetInterface();
	DAOUser *		pusr	= NULL;

	if (!pgrp)
		return FALSE;

	DAOMFC_CALL(pgrp->CreateUser(STV(pstrName), STV(pstrPID), STV(pstrPassword), &pusr));

	return pusr;
	}


/*****************************************************************************
* CdbDocument
*/
// Administration
CONSTRUCTOR			CdbDocument::CdbDocument(
	VOID)
	{
	}

CONSTRUCTOR			CdbDocument::CdbDocument(
	DAODocument *	pdoc,
	BOOL 			bAddRef)	// = FALSE
	{
	CdbOleObject::SetInterface((LPUNKNOWN)pdoc, bAddRef);
	}

CONSTRUCTOR			CdbDocument::CdbDocument(
	const CdbDocument &o)
	{
	SetInterface(o.GetInterface(TRUE));
	}

CdbDocument &		CdbDocument::operator =(
	const CdbDocument &o)
	{
	SetInterface(o.GetInterface(TRUE));
	return *this;
	}

VOID				CdbDocument::OnInterfaceChange(
	VOID)
	{
	DAODocument *	pdoc	= (DAODocument *)GetInterface();
	DAOProperties *	pprps	= NULL;

	if (pdoc)
		{
		pdoc->get_Properties(&pprps);
		}

	Properties.SetInterface(pprps);
	}

// Properties
CString				CdbDocument::GetName(
	VOID)
	{
	SPROPGET(DAODocument, get_Name);
	}

CString				CdbDocument::GetOwner(
	VOID)
	{
	SPROPGET(DAODocument, get_Owner);
	}

VOID				CdbDocument::SetOwner(
	LPCTSTR pstr)
	{
	SPROPSET(DAODocument, put_Owner, pstr);
	}

CString				CdbDocument::GetContainer(
	VOID)
	{
	SPROPGET(DAODocument, get_Container);
	}

CString				CdbDocument::GetUserName(
	VOID)
	{
	SPROPGET(DAODocument, get_UserName);
	}

VOID				CdbDocument::SetUserName(
	LPCTSTR pstr)
	{
	SPROPSET(DAODocument, put_UserName, pstr);
	}

LONG				CdbDocument::GetPermissions(
	VOID)
	{
	LPROPGET(DAODocument, get_Permissions);
	}

VOID				CdbDocument::SetPermissions(
	LONG l)
	{
	LPROPSET(DAODocument, put_Permissions, l);
	}

COleDateTime			CdbDocument::GetDateCreated(
	VOID)
	{
	DPROPGET(DAODocument, get_DateCreated);
	}

COleDateTime			CdbDocument::GetLastUpdated(
	VOID)
	{
	DPROPGET(DAODocument, get_LastUpdated);
	}

LONG			CdbDocument::GetAllPermissions(
	VOID)
	{
	LPROPGET(DAODocument, get_AllPermissions);
	}

//Methods
CdbProperty			CdbDocument::CreateProperty(
	LPCTSTR		pstrName,	// = NULL
	LONG		lType,		// = -1
	LPVARIANT	pvValue,	// = NULL
	BOOL		bDDL)		// = FALSE
	{
	DAODocument *	pdoc	= (DAODocument *)GetInterface();
	DAOProperty *	pprp	= NULL;

	if (!pdoc)
		return (DAOProperty *)NULL;

	DAOMFC_CALL(pdoc->CreateProperty(STV(pstrName), OLTV(lType), VTV(pvValue), BTV(bDDL), &pprp));

	return pprp;
	}


/*****************************************************************************
* CdbContainer
*/
// Administration
CONSTRUCTOR			CdbContainer::CdbContainer(
	VOID)
	{
	}

CONSTRUCTOR			CdbContainer::CdbContainer(
	DAOContainer *	pctn,
	BOOL			bAddRef)	// = FALSE
	{
	CdbOleObject::SetInterface((LPUNKNOWN)pctn, bAddRef);
	}

CONSTRUCTOR			CdbContainer::CdbContainer(
	const CdbContainer &o)
	{
	SetInterface(o.GetInterface(TRUE));
	}

CdbContainer &		CdbContainer::operator =(
	const CdbContainer &o)
	{
	SetInterface(o.GetInterface(TRUE));
	return *this;
	}

VOID				CdbContainer::OnInterfaceChange(
	VOID)
	{
	DAOContainer *	pctn	= (DAOContainer *)GetInterface();
	DAOProperties *	pprps	= NULL;
	DAODocuments *	pdocs	= NULL;

	if (pctn)
		{
		pctn->get_Properties(&pprps);
		pctn->get_Documents(&pdocs);
		}

	Properties.SetInterface(pprps);
	Documents.SetInterface(pdocs);
	}

// Properties
CString				CdbContainer::GetName(
	VOID)
	{
	SPROPGET(DAOContainer, get_Name);
	}

CString				CdbContainer::GetOwner(
	VOID)
	{
	SPROPGET(DAOContainer, get_Owner);
	}

VOID				CdbContainer::SetOwner(
	LPCTSTR pstr)
	{
	SPROPSET(DAOContainer, put_Owner, pstr);
	}

CString				CdbContainer::GetUserName(
	VOID)
	{
	SPROPGET(DAOContainer, get_UserName);
	}

VOID				CdbContainer::SetUserName(
	LPCTSTR pstr)
	{
	SPROPSET(DAOContainer, put_UserName, pstr);
	}

LONG				CdbContainer::GetPermissions(
	VOID)
	{
	LPROPGET(DAOContainer, get_Permissions);
	}

VOID				CdbContainer::SetPermissions(
	LONG l)
	{
	LPROPSET(DAOContainer, put_Permissions, l);
	}

BOOL				CdbContainer::GetInherit(
	VOID)
	{
	BPROPGET(DAOContainer, get_Inherit);
	}

VOID				CdbContainer::SetInherit(
	BOOL b)
	{
	BPROPSET(DAOContainer, put_Inherit, b);
	}

LONG			CdbContainer::GetAllPermissions(
	VOID)
	{
	LPROPGET(DAOContainer, get_AllPermissions);
	}

/*****************************************************************************
* CdbIndexFields (special case for index fields)
*/
CdbField			CdbIndexFields::Item(
	LPCTSTR pstr)
	{
	DAOIndexFields *	pflds	= (DAOIndexFields *)GetInterface();
	VARIANT				v;
	DAOField *			pfld	= NULL;

	if (!pflds)
		return (DAOField *)NULL;

	VariantInit(&v);
	DAOMFC_CALL(pflds->get_Item(STV(pstr), &v));

	if (v.vt == VT_DISPATCH)
		{
		v.pdispVal->QueryInterface(dbIID_IDAOField, (LPVOID *)&pfld);
		v.pdispVal->Release();
		}

	return pfld;
	}

CdbField			CdbIndexFields::Item(
	LONG i)
	{
	DAOIndexFields *	pflds	= (DAOIndexFields *)GetInterface();
	VARIANT				v;
	DAOField *			pfld	= NULL;

	if (!pflds)
		return (DAOField *)NULL;

	VariantInit(&v);
	DAOMFC_CALL(pflds->get_Item(LTV(i), &v));

	if (v.vt == VT_DISPATCH)
		{
		v.pdispVal->QueryInterface(dbIID_IDAOField, (LPVOID *)&pfld);
		v.pdispVal->Release();
		}

	return pfld;
	}

CdbObject			CdbIndexFields::ObItem(
	LPCTSTR pstr)
	{
	DAOIndexFields *	pflds	= (DAOIndexFields *)GetInterface();
	VARIANT				v;
	DAOField *			pfld	= NULL;

	if (!pflds)
		return (DAOFields *)NULL;

	VariantInit(&v);
	DAOMFC_CALL(pflds->get_Item(STV(pstr), &v));

	if (v.vt == VT_DISPATCH)
		{
		v.pdispVal->QueryInterface(dbIID_IDAOField, (LPVOID *)&pfld);
		v.pdispVal->Release();
		}

	return (LPUNKNOWN)pfld;
	}

CdbObject			CdbIndexFields::ObItem(
	LONG i)
	{
	DAOIndexFields *	pflds	= (DAOIndexFields *)GetInterface();
	VARIANT				v;
	DAOField *			pfld	= NULL;

	if (!pflds)
		return (DAOFields *)NULL;

	VariantInit(&v);
	DAOMFC_CALL(pflds->get_Item(LTV(i), &v));

	if (v.vt == VT_DISPATCH)
		{
		v.pdispVal->QueryInterface(dbIID_IDAOField, (LPVOID *)&pfld);
		v.pdispVal->Release();
		}

	return (LPUNKNOWN)pfld;
	}



/*****************************************************************************
* CdbBSTR
*/
CONSTRUCTOR			CdbBSTR::CdbBSTR(
	BSTR	b)	// = NULL
	{
	m_bstr = b;
	}

DESTRUCTOR			CdbBSTR::~CdbBSTR(
	VOID)
	{
	if (m_bstr)
		SysFreeString(m_bstr);
	}

					CdbBSTR::operator BSTR *(
	VOID)
	{
	return &m_bstr;
	}

					CdbBSTR::operator LPCTSTR(
	VOID)
	{
	return (LPCTSTR)m_bstr;
	}

HRESULT						CdbWideFromAnsi(
	LPSTR			pstr,
	unsigned int	cb,
	BSTR *			pbstr)
	{
	BSTR			bstrNew;

	if (!(bstrNew = SysAllocStringLen(NULL, cb)))
		return ResultFromScode(E_OUTOFMEMORY);
	
	// Convert from ANSI to WIDE if char.s exist
	if (cb && !(cb = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pstr,
		cb, (LPWSTR)bstrNew, cb)))
		{
		SysFreeString(bstrNew);
		return ResultFromScode(E_OUTOFMEMORY);
		}

	// Make sure it's NULL terminated
	((LPWSTR)(bstrNew))[cb] = L'\0';

	*pbstr = bstrNew;

	return NOERROR;
	}
