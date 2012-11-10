// Beispielerweiterung --------------------------------------------------------
// File: KOMPOBJ.HXX

#if !defined(_KOMPOBJ_HXX)
#define _KOMPOBJ_HXX

class CRelationExtension : public CTriasExtension {
private:
	
protected:
	bool GenerateObjWnd (long lMCode, long *pObjs, long lCnt, uint uiRes);
		
public:
		CRelationExtension (void);
		~CRelationExtension (void);

	STDMETHOD_(bool, InitExtension) (THIS_ short iMode);
	STDMETHOD_(bool, UnLoadExtension) (THIS);
	STDMETHOD_(bool, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(bool, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
};

#endif // _KOMPOBJ_HXX
