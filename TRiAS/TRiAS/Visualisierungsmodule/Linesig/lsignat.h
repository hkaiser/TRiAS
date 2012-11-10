#ifndef	__LINESIGNATURE_H__
#define	__LINESIGNATURE_H__

#include	<limits.h>
#include	"metafile.h"

#define	DEFAULT_GENERALIZE	5
#define	MIN_GENERALIZE		3

#define	MIN_WIDTH			500
#define	MAX_WIDTH			SHRT_MAX
#define	DEFAULT_WIDTH		10000

#define	MIN_HEIGHT			10
#define	MAX_HEIGHT			SHRT_MAX
#define	DEFAULT_HEIGHT		10000

#define	MIN_XOFFSET			0
#define	MAX_XOFFSET			100
#define	DEFAULT_XOFFSET		0

#define	MIN_YOFFSET			-3000
#define	MAX_YOFFSET			3000
#define	DEFAULT_YOFFSET		0

#define	minmax( val, min, max )	(((val) < (max)) && ((val) > (min)) ? (val) :	\
									(val) > (max) ? (max) :						\
									(val) < (min) ? (min) :						\
									(val))

class CLineResource : public CObject {
	DECLARE_DYNAMIC( CLineResource )

	UINT	m_nResrcID;
	UINT	m_nDefaultWidth;
public:
	CLineResource( UINT nResrcID, UINT nDefaultWidth );

	UINT	GetResrcID( )		{ return m_nResrcID; }
	UINT	GetDefaultWidth( )	{ return m_nDefaultWidth; }
};

typedef map<CString, CMetaFile*, less<CString> > MetafileMap;

class CLineSigCtrl : public CTriasVMD {
	DECLARE_DYNCREATE( CLineSigCtrl )

// Constructor
public:
	CLineSigCtrl( );

// Persistence
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// Implementation
protected:
	MetafileMap			m_mapOfSignatures;
	BOOL				LoadSignatures( );
	short				m_maxCoords;
	long				*m_R;					// Koordinatenpuffer für Rechtswerte
	long				*m_H;					// Koordinatenpuffer für Hochwerte
	long				m_scale;
	long				m_arc;
	BOOL				m_bClipExtended;
	BOOL				m_bMarkSegments;

// Overrides
public:
	virtual	~CLineSigCtrl( );
	virtual	void	DeleteContents( );

protected:
	BOOL	ParseVisInfoString( LPCTSTR pszString, CString& sigName, long& rDX, long& rDY, CDRect& rcDst, BOOL &swapX, BOOL &swapY );
	BOOL	ParseVisInfoString( LPCTSTR pszString, CString& sigName, long& rDX, long& rDY, long& width, long& height, long& xOff, long& yOff, BOOL &swapX, BOOL &swapY );
	BOOL	GetCoordBuffers( short coordCount );

public:
	DECLARE_OLECREATE_EX(CLineSigCtrl)			// Class factory and guid
	DECLARE_PROPPAGEIDS(CLineSigCtrl)			// Property page IDs
	DECLARE_OLECTLTYPE(CLineSigCtrl)			// Type name and misc status

	virtual LPCTSTR GetProgIdent();				// liefert ProgIdent "TRiAS.VM...."

	virtual	BOOL	OnProjectOpen( LPCTSTR pszNewProject );
	virtual	void	OnProjectClose( );
	virtual	BOOL	OnViewOpen( LPCTSTR pszView );
	virtual	void	OnViewClose( );

	virtual	BOOL	OnChangePalette( CDC *pDC, HPALETTE hPal );

	virtual	BOOL	OnQueryParameters(
						CWnd *pParentWnd,
						const DWORD lONr, 
						class VisInfo * pVI, 
						LPCTSTR pszVisStr, 
						LPSTR pBuffer, 
						short iLen,
						short * piOTypes);
	virtual	BOOL	OnDrawObject(
						CDC *pDC,
						CDC *pTarget,
						const DWORD lObjNr, 
						class VisInfo * pVI, 
						LPCTSTR pszVisString, 
						short& fDrawFlags );

// Message maps
	//{{AFX_MSG(CLineSigCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CLineSigCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CLineSigCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

	DECLARE_OLETYPELIB(CLineSigCtrl)      // GetTypeInfo
	DECLARE_INTERFACE_MAP()
	DECLARE_VISMOD_INTERFACE()

	// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CLineSigCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
};

const CDSize GetDotsPerMM( CDC* pDC );
const CString StrToASCII( LPCTSTR lpszString );

#endif	// __LINESIGNATURE_H__
