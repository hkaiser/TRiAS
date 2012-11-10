// Beispielerweiterung --------------------------------------------------------
// File: FEATURE.HXX

#if !defined(_FEATURE_HXX)
#define _FEATURE_HXX

// Funktion, die gerufen wird, wenn zwei Objekte identisch sind. Wenn von dieser
// Funktion true geliefert wird, dann soll das 2. Objekt aus der Liste gelöscht
// werden.
typedef bool (* DUPOBJPROC)(class CGObject &O1, class CGObject &O2, DWORD dwData);

class CFeatureExtension : public CTriasExtension {
private:
	long m_lMCode;			// MCode der doppelten Merkmale
	CUIdentObjects m_DupObjs;	// Baum für doppelte Merkmale
	HWND m_hORWnd;			// ORFenster mit doppelten Objekten
	
protected:
	bool FindDupFeatures (void);
	bool ScanTreeForDupObjects (DUPOBJPROC, DWORD);

	bool ClassifyFeatures (void);
		
public:
		CFeatureExtension (void);
		~CFeatureExtension (void);

	STDMETHOD_(bool, InitExtension) (THIS_ short iMode);
	STDMETHOD_(bool, UnLoadExtension) (THIS);
	STDMETHOD_(bool, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(bool, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);

inline	void SetMCode (long lMCode) { m_lMCode = lMCode; }
inline	void ResetMCode (void) { m_lMCode = 0L; }

	bool GenerateObjWnd (long lMCode, long *pObjs, long lCnt, uint uiRes);

friend bool DeleteDupObj (CGObject &O1, CGObject &O2, DWORD dwData);
};

bool FillTrees (long lIdent, short iOTyp, long lMCode, CUIdentObjects &rAllObjs, CUIdentObjects &rDupObjs);
bool ReadTextMerkmal (short iTTyp, DWORD lTarget, long lMCode, char *pText, short iLen);

#endif // _FEATURE_HXX
