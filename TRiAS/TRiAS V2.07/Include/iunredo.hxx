// Undo/Redo Interface --------------------------------------------------------
// File: IUNREDO.HXX

#if !defined(_IUNREDO_HXX)
#define _IUNREDO_HXX

///////////////////////////////////////////////////////////////////////////////
// Interface für Einzel-Undo/Redo ---------------------------------------------
//
#undef INTERFACE
#define INTERFACE IUndoRedo

// 07963808-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IUndoRedo, 0x07963808L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

DECLARE_INTERFACE_(IUndoRedo, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IUndoRedo methods
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc) PURE;
	STDMETHOD(Undo)(THIS) PURE;
	STDMETHOD(Redo)(THIS) PURE;
};
typedef IUndoRedo *LPUNDOREDO;

// Flags, die von Capabilities geliefert werden können ------------------------
typedef enum tagUNDOREDOCAPS {
// Gruppen der Flags zusammenfassen
	UNDOREDOCAPS_NOFLAGS = 0x00,
	UNDOREDOCAPS_ANDFLAGS = 0x03,
	UNDOREDOCAPS_ORFLAGS = 0x0300,

// Flags, die mit '&' (AND) zusammengefaßt werden müssen
	UNDOREDOCAPS_CANUNDO = 0x01,		// kann Undo
	UNDOREDOCAPS_CANREDO = 0x02,		// kann auch Redo

// Flags, die mit '|' (OR) zusammengefaßt werden müssen
	UNDOREDOCAPS_REPAINT = 0x0100,		// nach abgeschlossener Aktion neu zeichnen
	UNDOREDOCAPS_MULTILEVEL = 0x0200,	// enthält selbst mehrere UndoRedo's
} UNDOREDOCAPS;


///////////////////////////////////////////////////////////////////////////////
// Interface für Undo/Redo-Liste ----------------------------------------------
//
#undef INTERFACE
#define INTERFACE IUndoRedoList

// 07963809-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IUndoRedoList, 0x07963809L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

DECLARE_INTERFACE_(IUndoRedoList, IUndoRedo)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IUndoRedo methods
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc) PURE;
	STDMETHOD(Undo)(THIS) PURE;
	STDMETHOD(Redo)(THIS) PURE;

// *** IUndoRedoList methods ***
	STDMETHOD_(ULONG, Count)(THIS) PURE;
	STDMETHOD(AddUndoRedo)(THIS_ LPUNDOREDO pIUndoRedo) PURE;
	STDMETHOD_(DWORD, Undo)(THIS_ LONG lNum, IUndoRedoList *pIRedoList) PURE;
	STDMETHOD_(DWORD, Redo)(THIS_ LONG lNum, IUndoRedoList *pIUndoList) PURE;
};
typedef IUndoRedoList *LPUNDOREDOLIST;

///////////////////////////////////////////////////////////////////////////////
// Interface's für diverse Undo/Redo-Objekte ----------------------------------
//
// Alle diese Interface's müssen nach ihrer Instanziierung über die betreffende
// Funktion 'Init' für den konkreten Fall parametrisiert werden. Erfolgt diese
// Initialisierung nicht, so liefern die Funktionen des IUndoRedo-Interface's
// immer einen FehlerStatus (S_FALSE --> nicht mit FAILED() abtesten!).

// Merkmal löschen, erzeugen oder modifizieren --------------------------------
#undef INTERFACE
#define INTERFACE IUndoRedoObjectFeature

// B16261A2-856C-11CE-8CC3-444553540000	
// DEFINE_GUID(IID_IUndoRedoObjectFeature, 0xB16261A2L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

DECLARE_INTERFACE_(IUndoRedoObjectFeature, IUndoRedo)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IUndoRedo methods *** 
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc) PURE;
	STDMETHOD(Undo)(THIS) PURE;
	STDMETHOD(Redo)(THIS) PURE;

// *** IUndoRedoObjectFeature ***
	STDMETHOD(Init)(THIS_ LONG lONr, ULONG ulMCode, 
			LPCTSTR pNew, LPCTSTR pOld /* = NULL */) PURE;
};
typedef IUndoRedoObjectFeature *LPUNDOREDOOBJECTFEATURE;

// Relation löschen -----------------------------------------------------------
#undef INTERFACE
#define INTERFACE IUndoRedoDeleteObjectRelation

// B16261A3-856C-11CE-8CC3-444553540000	
// DEFINE_GUID(IID_IUndoRedoDeleteObjectRelation, 0xB16261A3L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

DECLARE_INTERFACE_(IUndoRedoDeleteObjectRelation, IUndoRedo)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IUndoRedo methods *** 
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc) PURE;
	STDMETHOD(Undo)(THIS) PURE;
	STDMETHOD(Redo)(THIS) PURE;

// *** IUndoRedoDeleteObjectRelation ***
	STDMETHOD(Init)(THIS_ LONG lONr, LONG lSecONr, 
			ULONG ulRCode, short iRTyp) PURE;
};
typedef IUndoRedoDeleteObjectRelation *LPUNDOREDODELETEOBJECTRELATION;

// Relation erzeugen ----------------------------------------------------------
#undef INTERFACE
#define INTERFACE IUndoRedoCreateRelation

// B16261A5-856C-11CE-8CC3-444553540000	
// DEFINE_GUID(IID_IUndoRedoCreateObjectRelation, 0xB16261A5L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

DECLARE_INTERFACE_(IUndoRedoCreateObjectRelation, IUndoRedo)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IUndoRedo methods *** 
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc) PURE;
	STDMETHOD(Undo)(THIS) PURE;
	STDMETHOD(Redo)(THIS) PURE;

// *** IUndoRedoCreateRelation ***
	STDMETHOD(Init)(THIS_ LONG lONr, LONG lSecONr, 
			ULONG ulRCode, short iRTyp) PURE;
};
typedef IUndoRedoCreateObjectRelation *LPUNDOREDOCREATEOBJECTRELATION;

// Textobjekt löschen ---------------------------------------------------------
#undef INTERFACE
#define INTERFACE IUndoRedoDeleteText

// B16261A5-856C-11CE-8CC3-444553540000	
// DEFINE_GUID(IID_IUndoRedoDeleteText, 0xB16261A5L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

DECLARE_INTERFACE_(IUndoRedoDeleteText, IUndoRedo)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IUndoRedo methods *** 
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc) PURE;
	STDMETHOD(Undo)(THIS) PURE;
	STDMETHOD(Redo)(THIS) PURE;

// *** IUndoRedoDeleteText ***
	STDMETHOD(Init)(THIS_ LONG lONr, LPCRECT prc /* = NULL */) PURE;
};
typedef IUndoRedoDeleteText *LPUNDOREDODELETETEXT;

// Textobjekt erzeugen --------------------------------------------------------
#undef INTERFACE
#define INTERFACE IUndoRedoCreateText

// B16261A6-856C-11CE-8CC3-444553540000	
// DEFINE_GUID(IID_IUndoRedoCreateText, 0xB16261A6L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

DECLARE_INTERFACE_(IUndoRedoCreateText, IUndoRedo)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IUndoRedo methods *** 
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc) PURE;
	STDMETHOD(Undo)(THIS) PURE;
	STDMETHOD(Redo)(THIS) PURE;

// *** IUndoRedoCreateText ***
	STDMETHOD(Init)(THIS_ LONG lONr) PURE;
};
typedef IUndoRedoCreateText *LPUNDOREDOCREATETEXT;

// Objekt aus OR-Fenster entfernen --------------------------------------------
#undef INTERFACE
#define INTERFACE IUndoRedoDeleteObjectWnd

// B16261A7-856C-11CE-8CC3-444553540000	
// DEFINE_GUID(IID_IUndoRedoDeleteObjectWnd, 0xB16261A7L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

DECLARE_INTERFACE_(IUndoRedoDeleteObjectWnd, IUndoRedo)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IUndoRedo methods *** 
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc) PURE;
	STDMETHOD(Undo)(THIS) PURE;
	STDMETHOD(Redo)(THIS) PURE;

// *** IUndoRedoDeleteObjectWnd ***
	STDMETHOD(Init)(THIS_ HWND hWnd, LONG lONr) PURE;
};
typedef IUndoRedoDeleteObjectWnd *LPUNDOREDODELETEOBJECTWND;

// Objekt in OR-Fenster austauschen -------------------------------------------
#undef INTERFACE
#define INTERFACE IUndoRedoReplaceObjectWnd

// B16261AE-856C-11CE-8CC3-444553540000	
// DEFINE_GUID(IID_IUndoRedoReplaceObjectWnd, 0xB16261A7L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

DECLARE_INTERFACE_(IUndoRedoReplaceObjectWnd, IUndoRedo)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IUndoRedo methods *** 
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc) PURE;
	STDMETHOD(Undo)(THIS) PURE;
	STDMETHOD(Redo)(THIS) PURE;

// *** IUndoRedoDeleteObjectWnd ***
	STDMETHOD(Init)(THIS_ HWND hWnd, LONG lONr, LONG lNewONr) PURE;
};
typedef IUndoRedoReplaceObjectWnd *LPUNDOREDOREPLACEOBJECTWND;

// Objekt zu OR-Fenster huinzufügen -------------------------------------------
#undef INTERFACE
#define INTERFACE IUndoRedoAddToObjectWnd

// B16261AF-856C-11CE-8CC3-444553540000	
// DEFINE_GUID(IID_IUndoRedoAddToObjectWnd, 0xB16261A7L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

DECLARE_INTERFACE_(IUndoRedoAddToObjectWnd, IUndoRedo)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IUndoRedo methods *** 
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc) PURE;
	STDMETHOD(Undo)(THIS) PURE;
	STDMETHOD(Redo)(THIS) PURE;

// *** IUndoRedoDeleteObjectWnd ***
	STDMETHOD(Init)(THIS_ HWND hWnd, LONG lONr) PURE;
};
typedef IUndoRedoAddToObjectWnd *LPUNDOREDOADDTOOBJECTWND;

// Normales Objekt löschen ----------------------------------------------------
#undef INTERFACE
#define INTERFACE IUndoRedoDeleteObject

// B16261A8-856C-11CE-8CC3-444553540000	
// DEFINE_GUID(IID_IUndoRedoDeleteObject, 0xB16261A8L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

DECLARE_INTERFACE_(IUndoRedoDeleteObject, IUndoRedo)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IUndoRedo methods *** 
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc) PURE;
	STDMETHOD(Undo)(THIS) PURE;
	STDMETHOD(Redo)(THIS) PURE;

// *** IUndoRedoDeleteObject ***
	STDMETHOD(Init)(THIS_ LONG lONr, LPCRECT prc /* = NULL */) PURE;
};
typedef IUndoRedoDeleteObject *LPUNDOREDODELETEOBJECT;

// Normales Objekt modifizieren -----------------------------------------------
#undef INTERFACE
#define INTERFACE IUndoRedoModifyObject

// B16261A9-856C-11CE-8CC3-444553540000	
// DEFINE_GUID(IID_IUndoRedoModifyObject, 0xB16261A9L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

DECLARE_INTERFACE_(IUndoRedoModifyObject, IUndoRedo)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IUndoRedo methods *** 
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc) PURE;
	STDMETHOD(Undo)(THIS) PURE;
	STDMETHOD(Redo)(THIS) PURE;

// *** IUndoRedoModifyObject ***
	STDMETHOD(Init)(THIS_ LONG lONr, const OBJGEOMETRIE *pOGNew, LPCRECT prc /* = NULL */) PURE;
};
typedef IUndoRedoModifyObject *LPUNDOREDOMODIFYOBJECT;

// Normales Objekt löschen ----------------------------------------------------
#undef INTERFACE
#define INTERFACE IUndoRedoCreateObject

// B16261AD-856C-11CE-8CC3-444553540000	
// DEFINE_GUID(IID_IUndoRedoCreateObject, 0xB16261ADL, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DECLARE_INTERFACE_(IUndoRedoCreateObject, IUndoRedo)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IUndoRedo methods *** 
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc) PURE;
	STDMETHOD(Undo)(THIS) PURE;
	STDMETHOD(Redo)(THIS) PURE;

// *** IUndoRedoCreateObject ***
	STDMETHOD(Init)(THIS_ LONG lONr, const OBJGEOMETRIE *pOGNew, LPCRECT prc /* = NULL */) PURE;
};
typedef IUndoRedoCreateObject *LPUNDOREDOCREATEOBJECT;

// PBD-Eintrag löschen, erzeugen, modifizieren --------------------------------
#undef INTERFACE
#define INTERFACE IUndoRedoPBDData

// B16261AA-856C-11CE-8CC3-444553540000	
// DEFINE_GUID(IID_IUndoRedoPBDData, 0xB16261A8L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

typedef enum tagPBDDATATYPE {
	PBDDATATYPE_UNKNOWN = 0,        // ???
	PBDDATATYPE_IDENT = 1,          // PBD-Eintrag f³r Identifikator
	PBDDATATYPE_FEATURE = 2,        // PBD-Eintrag f³r Merkmal
	PBDDATATYPE_RELATION = 3,       // PBD-Eintrag f³r Relation
	PBDDATATYPE_MAXEXTRIES = 4,
} PBDDATATYPE;

DECLARE_INTERFACE_(IUndoRedoPBDData, IUndoRedo)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IUndoRedo methods *** 
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc) PURE;
	STDMETHOD(Undo)(THIS) PURE;
	STDMETHOD(Redo)(THIS) PURE;

// *** IUndoRedoPBDData ***
	STDMETHOD(InitModify)(THIS_ const PBDDATA *pNewData, const PBDDATA *pOldData /* = NULL */) PURE;
	STDMETHOD(InitDelete)(THIS_ PBDDATATYPE rgType, ULONG ulTarget) PURE;
};
typedef IUndoRedoPBDData *LPUNDOREDOPBDDATA;

// Visualisierung modifizieren ------------------------------------------------
#undef INTERFACE
#define INTERFACE IUndoRedoVisInfo

// B16261AB-856C-11CE-8CC3-444553540000	
// DEFINE_GUID(IID_IUndoRedoVisInfo, 0xB16261ABL, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

DECLARE_INTERFACE_(IUndoRedoVisInfo, IUndoRedo)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IUndoRedo methods *** 
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc) PURE;
	STDMETHOD(Undo)(THIS) PURE;
	STDMETHOD(Redo)(THIS) PURE;

// *** IUndoRedoVisInfo ***
	STDMETHOD(Init)(THIS_ const HANDLEVISINFO *pNewData, const HANDLEVISINFO *pOldData /* = NULL */) PURE;
};
typedef IUndoRedoVisInfo *LPUNDOREDOVISINFO;

// Identifikator eines Objektes modifizieren ----------------------------------
#undef INTERFACE
#define INTERFACE IUndoRedoModIdent

// B16261AC-856C-11CE-8CC3-444553540000	
// DEFINE_GUID(IID_IUndoRedoModIdent, 0xB16261ACL, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

DECLARE_INTERFACE_(IUndoRedoModIdent, IUndoRedo)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IUndoRedo methods *** 
	STDMETHOD_(DWORD, Capabilities)(THIS_ LPTSTR *pDesc) PURE;
	STDMETHOD(Undo)(THIS) PURE;
	STDMETHOD(Redo)(THIS) PURE;

// *** IUndoRedoModIdent ***
	STDMETHOD(Init)(THIS_ LONG lONr, ULONG ulNewIdent, 
					ULONG ulOldIdent/* = 0L */, int iMode/* = 0 */) PURE;
};
typedef IUndoRedoModIdent *LPUNDOREDOMODIDENT;

#endif // _IUNREDO_HXX
