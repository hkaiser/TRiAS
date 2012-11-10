// Klassendeklarationen für lokale Profile-Dateien (BildMerkmale anzeigen)
// File: BILDPROF.HXX

#if !defined(_BILDPROF_HXX)
#define _BILDPROF_HXX

#import "tlb/TRiASDB.tlb"	raw_interfaces_only raw_dispinterfaces no_namespace	named_guids \
	exclude("IPersistStreamInit", "IPersist", "IStream", "ISequentialStream") \
	exclude("_LARGE_INTEGER", "_ULARGE_INTEGER", "tagSTATSTG", "_FILETIME") \
	exclude("IObjectWithSite")

// Verwaltung einer ProfileDatei
class BildProFile 
{
private:
	char *_FullName;	// Pfadname der ProfileDatei
	ResourceFile *_pResTarget;	// evtl. ResourceFile

protected:
	HRESULT GetFeature (INT_PTR lIdent, LPCSTR pcName, ITRiASFeature **ppIFeat);
	HRESULT GetObjectsDef (ULONG ulIdent, ITRiASObjects **ppIObjs);

public:
// Konstruktor/Destruktor
		BildProFile (const char *Project, ResourceFile *pResTarget = NULL);
		~BildProFile (void);

// Memberfunktionen
// Verwalten der Merkmalskodes, die Bildinfo enthalten
	long ReadImageCode (long lIdent);
};

#endif // _BILDPROF_HXX
