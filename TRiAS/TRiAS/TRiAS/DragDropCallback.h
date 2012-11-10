// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 23.09.2000 21:49:27 
//
// @doc
// @module DragDropCallback.h | Declaration of the <c CDragDropCallback> class

#if !defined(_DRAGDROPCALLBACK_H__BBD6517D_1E0B_4F6B_A137_8C9DCBC4D58D__INCLUDED_)
#define _DRAGDROPCALLBACK_H__BBD6517D_1E0B_4F6B_A137_8C9DCBC4D58D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// dient als abstrakte Basisklasse für das Targetobjekt einer D&D Operation
class CDragDropCallback
{
public:
	virtual HRESULT DragEnter(IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect) = 0;
	virtual HRESULT DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect) = 0;
	virtual HRESULT DragLeave(void) = 0;
	virtual HRESULT Drop(IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect) = 0;
	virtual bool FQueryPasteFromData(IDataObject *pIDataObject) = 0;
	virtual bool FPasteFromData(IDataObject *pIDataObject) = 0;
	virtual UINT TestDroppablePoint(POINTL *pPt) = 0;
	virtual void GiveFeedBack(POINTL *pPt, bool fRemove = false, bool fDraw = true) = 0;
	virtual bool IsDropSourceInst (void) = 0;
};

#endif // !defined(_DRAGDROPCALLBACK_H__BBD6517D_1E0B_4F6B_A137_8C9DCBC4D58D__INCLUDED_)
