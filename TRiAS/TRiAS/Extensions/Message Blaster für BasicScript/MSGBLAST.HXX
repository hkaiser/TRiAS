// Beispielerweiterung --------------------------------------------------------
// File: MSGBLAST.HXX

#if !defined(_MSGBLAST_HXX)
#define _MSGBLAST_HXX

#include "Msgguid.h"

///////////////////////////////////////////////////////////////////////////////
// benötigte SmartInterfaces
DefineSmartInterface(ExtendBScript);
DefineSmartInterface(MouseAction);

class CMsgBlastExt : 
	public CTriasExtension,
	public CComCoClass<CMsgBlastExt, &CLSID_MsgBlaster>
{
public:
	BEGIN_COM_MAP(CMsgBlastExt)
		COM_INTERFACE_ENTRY(ITriasXtension2)	// immer mit eintragen
		COM_INTERFACE_ENTRY(ITriasXtension)		// immer mit eintragen
	END_COM_MAP()

// Die folgende Zeile einfügen, wenn der alte Mechanismus der
// Registrierung der Erweiterungen intakt bleibt
	DECLARE_NO_REGISTRY();
	DECLARE_NOT_AGGREGATABLE_SINGLE(CMsgBlastExt, g_pTE);

		CMsgBlastExt (void);
		~CMsgBlastExt() {}

	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);

protected:
	bool RegisterBScriptExtension (void);

private:
	WExtendBScript m_Sink;
	WMouseAction m_Mouse;		// globale Instanz des Mouse-Objektes
};

#endif // _MSGBLAST_HXX
