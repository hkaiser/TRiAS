//	CPrintHandler
//
//	Führt den Druck der Anlagen laut Liste aus

class CPrintHandler : public CObject
{
public:
	CStringArray*	m_pPrintListe;

	CPrintHandler();
	~CPrintHandler();

	void	Print();
protected:
	void RenderGeoDB( CDC* pDC );
	CString Identisch( const char*, const char* );
	CString m_strEqIDE;
	CPrintAnlage1* m_pPA;
	void OnPrint( CDC* pDC, CPrintInfo* pInfo );
	void OnPrepareDC( CDC* pDC, CPrintInfo* pInfo = NULL );
	void OnEndPrinting( CDC* pDC, CPrintInfo* pInfo );
	void OnBeginPrinting( CDC* pDC, CPrintInfo* pInfo );
	BOOL OnPreparePrinting( CPrintInfo* pInfo );
};
