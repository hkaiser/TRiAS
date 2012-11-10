// gakSete.h : interface of the CDaoRecordsetExt class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _GAKSET_H
#define _GAKSET_H

enum LockResult { LockFailed = 0, NothingToLock = 1, Locked = 2 };
enum LockType { NotLock = FALSE, Lock = TRUE, Store = 2 };
typedef void (CALLBACK *PFPREPARE)(LPARAM);

class CDaoRecordsetExt: public CDaoRecordset
{
protected:
	UINT m_uiPrimKey;			// PrimaryKey
	BOOL m_bCanUpDate;			// Satz kann editiert werden
	CString m_strDefaultSQL;	// Default SQL-Text
	CDaoTableDef *m_pTableDef;	// realisiert dbOpenTable

	virtual void SetFieldValue(LPCTSTR szName, const COleVariant& varValue);

public:
	// JG ist der Datensatz gültig
	virtual bool IsValid();

	BOOL m_bOutputLockError;	// Semaphor für Ausgabe der LockInfo an Nutzer

	virtual BOOL CanUpdate (void);
	int virtual LockReckord (int iLock = TRUE, CWnd *pWnd = NULL, const char *pNummer = NULL);
	virtual void OutputLockErrorMessage (void);

	virtual BOOL PrepareAddNew (const char *pNummer, PFPREPARE = NULL, LPARAM = 0);
	void LastRecordDeleted (void);	// letzte Satz wurde gelöscht

	BOOL FieldsChanged (void);

	CDaoRecordsetExt(UINT uiPrimKey, const char *pDefaultSQL, CDaoDatabase* pDatabase = NULL);
	~CDaoRecordsetExt (void);
	DECLARE_DYNAMIC(CDaoRecordsetExt)

	// JG nur für AbfSets definiert / sonst leere Implementation
	virtual BOOL SearchNummer(const char *pNummer = NULL , BOOL bOutErrMsg =TRUE);

protected:
	CString	m_user;
	BOOL	m_ro;

public:
// Field/Param Data
	//{{AFX_FIELD(CDaoRecordsetExt, CDaoRecordset)
	CString			m_Nummer;						// Nummerfeld
	COleDateTime	m_Erfassungsdatum;				// Systemfelder
	COleDateTime	m_Aenderungsdatum;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGakSet)
	public:
	virtual CString GetDefaultDBName();		// REVIEW:  Get a comment here
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);	// RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

//	weitere virtuelle Funktionen
	virtual void Open(int nOpenType = AFX_DAO_USE_DEFAULT_TYPE, LPCTSTR lpszSQL = NULL, int nOptions = 0);
	virtual void Delete( );
};

class COutputLockError
{
private:
	CDaoRecordsetExt *m_pSet;
public: 
	COutputLockError (CDaoRecordsetExt *pSet) { m_pSet = pSet; m_pSet -> m_bOutputLockError = FALSE; }
	~COutputLockError (void) { m_pSet -> m_bOutputLockError = TRUE;  m_pSet -> OutputLockErrorMessage (); }
};

#endif		// _GAKSET_H
