// MetafileSupport innerhalb von CommonVU -------------------------------------
// File: METAFILE.HXX

#if !defined(_METAFILE_HXX)
#define _METAFILE_HXX

class MetaFileExposeEvt : public Event {
public:
	Rectangle GetExposedArea (void);
};

// Diese Klasse kann dazu verwendet Werden ein neues Metafile zu erzeugen
// oder ein bestehendes Metafile zu lesen und anzuzeigen
class MetaFile : public Window {
protected:
	HANDLE _hMF;		// MetaFileHandle
	HANDLE _hMetaDC;	// DC des Metafiles
	char *_Name;		// MetaFileName

virtual void MetaFileExpose (MetaFileExposeEvt) = 0;

public:
// Konstruktor/Destruktor
		MetaFile (char *Name = NULL);
		~MetaFile (void);

// Memberfunktionen
	HANDLE GetHandle (void) { return _hMF; }	// holt MetaFileHandle
	HANDLE GetDC (void) { return _hMetaDC; }	// holt DC
	void Generate (void);		// MetaFile generieren
};

#endif // _METAFILE_HXX
