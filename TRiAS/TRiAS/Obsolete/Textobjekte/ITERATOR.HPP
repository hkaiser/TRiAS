
class CLBIterator 
{
private:
	CListBox &m_rlb;// Liste , wird im Konstruktor übergeben
	short m_iCnt;   // Zähler durch Liste
	short m_iCntItems; // Anzahl der Listenmitglieder
	short m_iIdBase;
	char* m_pItem;
	CString m_sItem;
public:
	CLBIterator (CListBox &m_rlb);  // Konstruktor , der den Zähler an den Beginn der Liste setzt 
	~CLBIterator(); 
	BOOL GetNextItem (long &rlItem, char* pcGeo);// Gibt selektierten Wert in der Liste	
	void Reset (void); // besorgt eigentliches Zurücksetzen
	char FindObjGeo (char* pItem);// stellt fest , ob Obj. T,F oder L
};


