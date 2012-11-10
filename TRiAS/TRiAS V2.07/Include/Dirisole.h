// ClassIDs und GUID's für TRIAS ----------------------------------------------
// File: DIRISOLE.H

#if !defined(_DIRISOLE_H)
#define _DIRISOLE_H

#if defined(INITGUIDS)
#include <initguid.h>
#endif

extern "C" {

// {937EEB40-2234-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(CLSID_DirisProject, 0x937EEB40L, 0x2234, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
// {07963822-3123-101C-BB62-00AA0018497C}	
DEFINE_GUID(CLSID_TRiASMetaDocument, 0x07963822L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

// {CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(CLSID_DataTransferObject, 0xCF883AF6L, 0x553F, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);

// ConnectionPoint, der direkt durch TRiAS unterstützt wird -------------------
// 0796385A-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITRiASNotificationSink, 0x0796385AL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 0796386E-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITRiASSysNotificationSink, 0x0796386EL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

// {8DE4E3C0-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(LIBID_TriasLibrary, 0x8DE4E3C0L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
// {89C5F582-4E2B-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(LIBID_TriasAdviseSink, 0x89C5F582L, 0x4E2B, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);

// 07963881-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(CLSID_ViewDropTarget, 0x07963881L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 07963883-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(CLSID_ORWndDropSource, 0x07963883L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 07963884-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(CLSID_ORWndDropTarget, 0x07963884L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

#if !defined(_TriasTLB_H_) && !defined(__Triastlb_h__)
// {8DE4E3C2-4D53-101B-AAE1-E7E7E7E7E7E7}
// DEFINE_GUID(CLSID_Application, 0x8DE4E3C2L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);

// {8DE4E3C3-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_ITriasApp, 0x8DE4E3C3L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
// {8DE4E3C4-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_DTriasApp, 0x8DE4E3C4L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);

// {8DE4E3C5-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_IDocuments, 0x8DE4E3C5L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
// {8DE4E3C6-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_DDocuments, 0x8DE4E3C6L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
// {8DE4E3C7-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_IDocument, 0x8DE4E3C7L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
// {8DE4E3C8-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_DDocument, 0x8DE4E3C8L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);


// {8DE4E3C9-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_IGeoClasses, 0x8DE4E3C9L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
// {8DE4E3CA-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_DGeoClasses, 0x8DE4E3CAL, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
// {8DE4E3CB-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_IGeoClass, 0x8DE4E3CBL, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
// {8DE4E3CC-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_DGeoClass, 0x8DE4E3CCL, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);


//{8DE4E3D1-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_IGeoObjects, 0x8DE4E3D1L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
//{8DE4E3D2-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_DGeoObjects, 0x8DE4E3D2L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
//{8DE4E3D3-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_IGeoObject, 0x8DE4E3D3L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
//{8DE4E3D4-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_DGeoObject, 0x8DE4E3D4L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);


//{8DE4E3D5-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_IGeoFeatures, 0x8DE4E3D5L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
//{8DE4E3D6-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_DGeoFeatures, 0x8DE4E3D6L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
//{8DE4E3D7-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_IGeoFeature, 0x8DE4E3D7L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
//{8DE4E3D8-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_DGeoFeature, 0x8DE4E3D8L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);


// {8DE4E3CD-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_IViews, 0x8DE4E3CDL, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
// DispInterface:	_DViews			{8DE4E3CE-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_DViews, 0x8DE4E3CEL, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
// {8DE4E3CF-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_IView, 0x8DE4E3CFL, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
// {8DE4E3D0-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_DView, 0x8DE4E3D0L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);

// {8DE4E3D9-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_ITRiASCollection, 0x8DE4E3D9L, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
// {8DE4E3DA-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_ITRiASBaseClass, 0x8DE4E3DAL, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);

// {8DE4E3DB-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_IGeoObjectWins, 0x8DE4E3DBL, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
// {8DE4E3DC-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_DGeoObjectWins, 0x8DE4E3DCL, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
// {8DE4E3DB-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_IGeoObjectWin, 0x8DE4E3DDL, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
// {8DE4E3DC-4D53-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_DGeoObjectWin, 0x8DE4E3DEL, 0x4D53, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);

// {89C5F580-4E2B-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_INotificationSink, 0x89C5F580L, 0x4E2B, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
// {89C5F581-4E2B-101B-AAE1-E7E7E7E7E7E7}
DEFINE_GUID(IID_DNotificationSink, 0x89C5F581L, 0x4E2B, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);
#endif // _TriasTLB_H_


// NotificationSink zu TRIAS(R) -----------------------------------------------

}	// extern "C" 

// nützliche Macro's ----------------------------------------------------------
#if !defined(ADDREF)
#define ADDREF(pUnk)	{if (pUnk) pUnk -> AddRef();}
#endif
#if !defined(RELEASE)
#define RELEASE(pUnk)	{if (pUnk) {pUnk -> Release();pUnk = NULL;}}
#endif

// Dispatchfehler enstehen aus ErrCodes durch VT_ERRORFROMERRCODE()
#define VT_ERROR_OFFSET		2000
#define ErrorFromErrCode(iRC)	(MAKE_SCODE(SEVERITY_ERROR,FACILITY_DISPATCH,short(iRC)+VT_ERROR_OFFSET))
#define GetErrCode(iVTError)	(SCODE_CODE(iVTError)-VT_ERROR_OFFSET)

#if !defined(DELETE)
#define DELETE(x)	{if(x){delete(x);(x)=NULL;}}
#if defined(MSCC8) || _MSC_VER >= 800
#define DELETE_VEC(x)	{if(x){delete [] (x); (x)=NULL;}}
#else
#define DELETE_VEC(x,s)	{if(x){delete [(s)] (x); (x)=NULL;}}
#endif
#endif // DELETE

#if !defined(BASED_CODE)
#define BASED_CODE __based(__segname("_CODE"))
#endif

// Types that OLE2.H et. al. leave out ----------------------------------------
#ifndef LPLPVOID
typedef LPVOID FAR * LPLPVOID;
#endif

#ifndef LPPOINTL
typedef POINTL FAR * LPPOINTL;
#endif

// Useful macros. -------------------------------------------------------------
#define SETFormatEtc(fe, cf, asp, td, med, li)   \
    {\
    (fe).cfFormat=cf;\
    (fe).dwAspect=asp;\
    (fe).ptd=td;\
    (fe).tymed=med;\
    (fe).lindex=li;\
    };

#define SETDefFormatEtc(fe, cf, med)   \
    {\
    (fe).cfFormat=cf;\
    (fe).dwAspect=DVASPECT_CONTENT;\
    (fe).ptd=NULL;\
    (fe).tymed=med;\
    (fe).lindex=-1;\
    };


#define SETRECTL(rcl, l, t, r, b) \
    {\
    (rcl).left=l;\
    (rcl).top=t;\
    (rcl).right=r;\
    (rcl).bottom=b;\
    }

#define SETSIZEL(szl, h, v) \
    {\
    (szl).cx=h;\
    (szl).cy=v;\
    }


#define RECTLFROMRECT(rcl, rc)\
    {\
    (rcl).left=(long)(rc).left;\
    (rcl).top=(long)(rc).top;\
    (rcl).right=(long)(rc).right;\
    (rcl).bottom=(long)(rc).bottom;\
    }


#define RECTFROMRECTL(rc, rcl)\
    {\
    (rc).left=(int)(rcl).left;\
    (rc).top=(int)(rcl).top;\
    (rc).right=(int)(rcl).right;\
    (rc).bottom=(int)(rcl).bottom;\
    }


#define POINTLFROMPOINT(ptl, pt) \
    { \
    (ptl).x=(long)(pt).x; \
    (ptl).y=(long)(pt).y; \
    }


#define POINTFROMPOINTL(pt, ptl) \
    { \
    (pt).x=(int)(ptl).x; \
    (pt).y=(int)(ptl).y; \
    }

// Here's one that should be in windows.h
#define SETPOINT(pt, h, v) \
    {\
    (pt).x=h;\
    (pt).y=v;\
    }

#define SETPOINTL(ptl, h, v) \
    {\
    (ptl).x=h;\
    (ptl).y=v;\
    }

///////////////////////////////////////////////////////////////////////////////
// HilfsMacros
#if !defined(TEST_E_POINTER)
#if defined(_DEBUG)
#define TEST_E_POINTER(s,p) \
	do{ \
		if(NULL==(p)) { \
			AtlTrace("%s has bad pointer parameter.",s); return E_POINTER; \
		} \
	}while(0) \

#else
#define TEST_E_POINTER(s,p) \
	do{ \
		if(NULL==(p)) return E_POINTER; \
	}while(0) \

#endif // _DEBUG
#endif // TEST_E_POINTER

#endif // _DIRISOLE_H
