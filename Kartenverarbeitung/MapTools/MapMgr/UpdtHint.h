#define	ON_UPDATE_FILENEW		1

#define	ON_UPDATE_PRELOADING	11
#define	ON_UPDATE_PRESAVING		12
#define	ON_UPDATE_POSTLOADING	13
#define	ON_UPDATE_POSTSAVING	14

#define	ON_UPDATE_ADDPICTNAME	21
#define	ON_UPDATE_DELPICTNAME	22
#define	ON_UPDATE_CHGPICTNAME	23

#define ON_UPDATE_PICTSIZE		31
#define ON_UPDATE_REFCORNER		32

typedef struct tagMAPINFO {
	LPCTSTR				m_lpszMapIdent;
	LPCTSTR				m_lpszMapName;
	union {
		void				*vPtr;
		CArray<POINT,POINT>	*pPoints;
		CSize				*pSize;
	} ptr;
	tagMAPINFO();
} MAPINFO, FAR* LPMAPINFO;

class CUpdateHint : public CObject
{
	DECLARE_DYNAMIC(CUpdateHint);
public:
	CUpdateHint(LPMAPINFO pInfo = NULL);
	WPARAM	m_wParam;
	LPMAPINFO	pInfo;
};
