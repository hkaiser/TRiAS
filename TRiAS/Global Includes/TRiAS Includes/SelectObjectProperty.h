// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.09.2000 12:11:06 
//
// @doc
// @module SelectObjectProperty.h | Declaration of the <c CSelectObjectProperty> class

#if !defined(_SELECTOBJECTPROPERTY_H__C76411E0_B7A8_4A6A_8AC4_F948EDDBB30D__INCLUDED_)
#define _SELECTOBJECTPROPERTY_H__C76411E0_B7A8_4A6A_8AC4_F948EDDBB30D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <bmpbtn.hxx>
#include <SelObjPropDlg.h>
#include <DataHelp.h>

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(ObjectProps);
DefineSmartInterface(EnumObjProps);

///////////////////////////////////////////////////////////////////////////////
// 
class CSelectObjectProperty
{
public:
	CSelectObjectProperty(
			DialogWindow *pParent, UINT uiResEdit, UINT uiResBttn, INCLUDEOBJPROP pFcn = IncludeObjProp)
		: m_sleObjProp(pParent, uiResEdit), m_SelObjProp(pParent, uiResBttn)
	{
		m_pParent = pParent;
		m_pFcn = pFcn;
	}
	~CSelectObjectProperty() {}

	BOOL FInit()
	{
		m_sleObjProp.FInit();
		m_SelObjProp.FInit();
		if (m_SelObjProp.LoadBitmaps (IDB_ARROW_DOWN, IDB_ARROW_DOWN_SEL, IDB_ARROW_DOWN_FOCUS, IDB_ARROW_DOWN_DISABLED))
			m_SelObjProp.SizeToContent(); 

	// Liste der Objekteigenschaften initialisieren
	BOOL fMustReInit = DEX_GetObjectProps (m_Props.ppi());

		if (m_Props.IsValid()) {
		// evtl. alle ObjProps installieren
			if (fMustReInit) {
				m_Props -> OnNewReferenceObject (-1L);	// alles bisherige löschen
				if (FAILED(m_Props -> OnNewReferenceObject (0L))) 
					return FALSE;
				DEX_SetMustInitOPFs(FALSE);
			}
		}
		return TRUE;
	}
	void SetFocus() { m_sleObjProp.SetFocus(); }
	
// Tree anzeigen
	bool ShowObjPropDlg (void)
	{
	// Objekteigenschaften lediglich einmal initialisieren
		TX_ASSERT(m_Props.IsValid());
		if (!m_Props) return false;

	CSelObjPropsDlg SelObjProps (m_pParent, m_Props, m_pFcn);
	char cbBuffer[64];

		m_sleObjProp.GetText (cbBuffer, sizeof(cbBuffer)-1);
		m_ObjProp.Release();		// vorhergehende freigeben

		if (SelObjProps.FInit (cbBuffer)) {
		// Fenstergröße an übergeordnete Controls anpassen
		Point ptEdit (m_sleObjProp.GetPosition());
		Dimension dimEdit (m_sleObjProp.GetSize());
		Point ptBttn (m_SelObjProp.GetPosition());
		Dimension dimBttn (m_SelObjProp.GetSize());

		Point pt (SelObjProps.GetPosition());
		Dimension dim (SelObjProps.GetSize());

			dim = Dimension(ptBttn.X()-ptEdit.X()+dimBttn.Width(), dim.Height());

		// Fensterposition so richten, daß es nicht aus dem Bildschirm raushängt
			pt.X() = ptEdit.X() - 1;
			pt.Y() = ptEdit.Y() - dim.Height() - 1;

		Point ptScreen (pt.X(), dim.Height() - ptEdit.Y() - dimEdit.Height() + m_pParent->GetSize().Height() +1);

			ClientToScreen(m_pParent -> Handle(API_WINDOW_HWND), (POINT *)&ptScreen);
			if (ptScreen.Y() > GetSystemMetrics (SM_CYFULLSCREEN)) 
				pt.Y() = ptEdit.Y() + dimEdit.Height() + 1;

			SelObjProps.ChangePosition (pt);
			SelObjProps.ChangeSize(dim);

		// jetzt anzeigen		
			SelObjProps.Show((ShowState)(Normal | NoParentDisabling));
			if (SelObjProps.Result()) {
			string str ("");

				SelObjProps.GetSelectedObjProp (str);
				if (SUCCEEDED(RetrieveObjProp (str.c_str(), m_ObjProp.ppi())))
				{
					m_sleObjProp.SetText (str.c_str());
					return true;
				}
			}
		}
		return false;
	}

// auf bestimmte Objekteigenschaft vorinitialisieren
	bool InitFromData (LPCSTR pcObjProp)
	{
	DWORD dwFlags = 0L;

		if (SUCCEEDED(RetrieveObjProp (pcObjProp, m_ObjProp.ppi())) &&
			SUCCEEDED(m_ObjProp -> GetPropInfo (NULL, 0, &dwFlags)) &&
			m_pFcn(dwFlags))
		{
			m_sleObjProp.SetText (pcObjProp);
			return true;
		}
		m_ObjProp.Release();
		return false;
	}
	void ResetSelection()
	{
		m_ObjProp.Release();
		m_sleObjProp.SetText("");
	}

// Ergebnis abfragen
	bool SaveData (os_string &rName)
	{
	char cbBuffer[_MAX_PATH];

		m_sleObjProp.GetText (cbBuffer, sizeof(cbBuffer)-1);
		if (strlen(cbBuffer) > 0) {
			rName = cbBuffer;
			return true;
		}
		return false;
	}
	bool hasSelection() { os_string str; return SaveData (str);	}
	HRESULT GetObjProps(IObjectProps **ppIProps)
	{
		if (NULL == ppIProps || !m_Props) 
			return E_POINTER;

		((*ppIProps) = m_Props) -> AddRef();
		return S_OK;
	}

// Persistenz
	static HRESULT Load (IStream *pStm, os_string &rName)
	{
		return LoadString(pStm, rName);
	}
	static HRESULT Save (IStream *pStm, os_string &rName)
	{
		return SaveString (pStm, rName);
	}
	static __int64 GetSizeMax(os_string &rName)
	{
		return ::GetSizeMax(rName);
	}

// Liefert die selektierte Objekteigenschaft
	HRESULT GetSelectedObjProp (IObjectProperty **ppIOP)
	{
		if (m_ObjProp.IsValid()) 
			return LPUNKNOWN(*ppIOP = m_ObjProp) -> AddRef(), S_OK;
		return E_FAIL;
	}

protected:
// Finden einer bestimmten Objekteigenschaft
	HRESULT RetrieveObjProp (LPCSTR pcName, IObjectProperty **ppIOP)
	{
	WEnumObjProps EnumProps;
	HRESULT hr = m_Props -> EnumObjectProps (EnumProps.ppi());

		if (FAILED(hr)) return hr;
		return EnumProps -> FindByName (pcName, ppIOP);
	}

private:
	SingleLineEdit m_sleObjProp;	// Objekteigenschaft
	CBmpButton m_SelObjProp;		// Button für Objekteigenschaft

	WObjectProps m_Props;			// sämtliche Objekteigenschaften
	WObjectProperty m_ObjProp;		// die ausgewählte Objekteigenschaft

	DialogWindow *m_pParent;
	INCLUDEOBJPROP m_pFcn;
};

#endif // !defined(_SELECTOBJECTPROPERTY_H__C76411E0_B7A8_4A6A_8AC4_F948EDDBB30D__INCLUDED_)
