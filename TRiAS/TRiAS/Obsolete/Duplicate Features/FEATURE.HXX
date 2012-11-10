// Beispielerweiterung --------------------------------------------------------
// File: FEATURE.HXX

#if !defined(_FEATURE_HXX)
#define _FEATURE_HXX

class CUIdentObjects;

class CFeatureExtension : public CTriasExtension {
private:
	long m_lMCode;			// MCode der doppelten Merkmale
	CUIdentObjects m_DupObjs;	// Baum für doppelte Merkmale
	HWND m_hORWnd;			// ORFenster mit doppelten Objekten
	
protected:
	bool FindDupFeatures (void);
	bool ScanTreeForDupObjects (bool &fError);
	
public:
		CFeatureExtension (void);
		~CFeatureExtension (void);

	STDMETHOD_(bool, InitExtension) (THIS_ short iMode);
	STDMETHOD_(bool, UnLoadExtension) (THIS);
	STDMETHOD_(bool, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(bool, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
};

bool FillTrees (long lIdent, short iOTyp, long lMCode, CUIdentObjects &rAllObjs, CUIdentObjects &rDupObjs);
bool ReadTextMerkmal (short iTTyp, DWORD lTarget, long lMCode, char *pText, short iLen);

bool CompareObjs (ULONG lONr1, ULONG lONr2);
bool GetObjectGeometrie (OBJGEOMETRIE &rOG);
void FreeObjGeometrie (OBJGEOMETRIE &rOG);

#endif // _FEATURE_HXX
