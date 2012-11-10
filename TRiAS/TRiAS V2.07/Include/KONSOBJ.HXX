// Prototypen für KonsistenzTest ----------------------------------------------
// File: KONSOBJ.HXX

#if !defined(_KONSOBJ_HXX)
#define _KONSOBJ_HXX

#if defined(_DEBUG)

#if defined(WIN32)

#include "kons.hxx"

class CProtocol;

_TRIAS02_ENTRY ErrCode TestObjekt (GeoDB &rDB, long lONr, short toDo = KTDDiagnose, CProtocol *pPrt = NULL);
_TRIAS02_ENTRY ErrCode TestObjektIdent (GeoDB &rDB, long lONr, short toDo = KTDDiagnose, CProtocol *pPrt = NULL);
_TRIAS02_ENTRY ErrCode TestObjektGeometrie (GeoDB &rDB, long lONr, short toDo = KTDDiagnose, CProtocol *pPrt = NULL);

_TRIAS02_ENTRY ErrCode TestObjektMerkmale (GeoDB &rDB, long lONr, short toDo = KTDDiagnose, CProtocol *pPrt = NULL);
_TRIAS02_ENTRY ErrCode TestObjektMerkmal (GeoDB &rDB, long lONr, long lMCode, short toDo = KTDDiagnose, CProtocol *pPrt = NULL);
_TRIAS02_ENTRY ErrCode TestObjektMerkmalDeleted (GeoDB &rDB, long lONr, long lMCode, short toDo = KTDDiagnose, CProtocol *pPrt = NULL);

_TRIAS02_ENTRY ErrCode TestSichtMerkmale (GeoDB &rDB, const char *pView, short toDo = KTDDiagnose, CProtocol *pPrt = NULL);
_TRIAS02_ENTRY ErrCode TestSichtMerkmal (GeoDB &rDB, const char *pView, long lMCode, short toDo = KTDDiagnose, CProtocol *pPrt = NULL);
_TRIAS02_ENTRY ErrCode TestSichtMerkmalDeleted (GeoDB &rDB, const char *pView, long lMCode, short toDo = KTDDiagnose, CProtocol *pPrt = NULL);

_TRIAS02_ENTRY ErrCode TestIdentMerkmale (GeoDB &rDB, long lIdent, short toDo = KTDDiagnose, CProtocol *pPrt = NULL);
_TRIAS02_ENTRY ErrCode TestIdentMerkmal (GeoDB &rDB, long lIdent, long lMCode, short toDo = KTDDiagnose, CProtocol *pPrt = NULL);
_TRIAS02_ENTRY ErrCode TestIdentMerkmalDeleted (GeoDB &rDB, long lIdent, long lMCode, short toDo = KTDDiagnose, CProtocol *pPrt = NULL);

#else

inline ErrCode TestObjekt (GeoDB &rDB, long lONr, ...) { return EC_OKAY; }
inline ErrCode TestObjektIdent (GeoDB &rDB, long lONr, ...) { return EC_OKAY; }
inline ErrCode TestObjektGeometrie (GeoDB &rDB, long lONr, ...) { return EC_OKAY; }

inline ErrCode TestObjektMerkmale (GeoDB &rDB, long lONr, ...) { return EC_OKAY; }
inline ErrCode TestObjektMerkmal (GeoDB &rDB, long lONr, long lMCode, ...) { return EC_OKAY; }
inline ErrCode TestObjektMerkmalDeleted (GeoDB &rDB, long lONr, long lMCode, ...) { return EC_OKAY; }

inline ErrCode TestSichtMerkmale (GeoDB &rDB, const char *pView, ...) { return EC_OKAY; }
inline ErrCode TestSichtMerkmal (GeoDB &rDB, const char *pView, long lMCode, ...) { return EC_OKAY; }
inline ErrCode TestSichtMerkmalDeleted (GeoDB &rDB, const char *pView, long lMCode, ...) { return EC_OKAY; }

inline ErrCode TestIdentMerkmale (GeoDB &rDB, long lIdent, ...) { return EC_OKAY; }
inline ErrCode TestIdentMerkmal (GeoDB &rDB, long lIdent, long lMCode, ...) { return EC_OKAY; }
inline ErrCode TestIdentMerkmalDeleted (GeoDB &rDB, long lIdent, long lMCode, ...) { return EC_OKAY; }

#endif // WIN32

#endif // _DEBUG

#endif // _KONSOBJ_HXX
