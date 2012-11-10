// Verwaltung von Undo/Redo ---------------------------------------------------
// File: UNDOHELP.HXX

#if !defined(_UNDOHELP_HXX)
#define _UNDOHELP_HXX

#if !defined(_DEFINED_UNDOCNT)

const int DEFAULTUNDOCNT = 100;

#define _DEFINED_UNDOCNT
#endif // _DEFINED_UNDOCNT

#define MAXUNDOREDOLISTS	10	// müßte genügen

class CUndoRedoList;

class _TRIAS03_ENTRY CManageUndoRedo {
private:
	CUndoRedoList *m_pUndoList;
	CUndoRedoList *m_pRedoList;

// Stack für komplexe Undo's
	LPUNDOREDOLIST m_rgLists[MAXUNDOREDOLISTS];	
	short m_iCurrPos;

protected:
// Objekte nur über CreateInstance erzeugen
	bool FInit (int iCnt);

		CManageUndoRedo (void);

public:
// Konstruktion/Initialisierung (nur dynamisch)
static CManageUndoRedo *CreateInstance (int iCnt = DEFAULTUNDOCNT);

		~CManageUndoRedo (void);

	HRESULT AddUndo (LPUNKNOWN pIUndo);
	HRESULT BeginUndoLevel (LPCTSTR pDesc);
	HRESULT BeginUndoLevel (LPUNKNOWN pIUndoList);
	HRESULT EndUndoLevel (void);
	HRESULT CancelUndoLevel (bool fUndoExisting = false);

	HRESULT Undo (LONG lCnt = 1L);
	HRESULT Redo (LONG lCnt = 1L);

	HRESULT GetUndoList (LPENUMUNKNOWN *pUndos);
	HRESULT GetRedoList (LPENUMUNKNOWN *pRedos);

	DWORD GetNextUndoDesc (LPTSTR *pDesc);
	DWORD GetNextRedoDesc (LPTSTR *pDesc);

	void EveryDelete (void);
};

#endif // _UNDOHELP_HXX
