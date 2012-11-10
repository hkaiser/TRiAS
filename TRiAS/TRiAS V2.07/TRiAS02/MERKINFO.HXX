// Strukturdefinition fuer GetMerkInfo 
// File: MERKINFO.HXX

#if !defined(_MERKINFO_HXX)
#define _MERKINFO_HXX

// Funktionsprototypen --------------------------------------------------------
class MerkInfo;		// deklarieren
_TRIAS02_ENTRY extern "C" 
ErrCode EXPORT02 GetMerkInfo (HPROJECT hPr, long ONr, short iTyp, MerkInfo ***, short *);
			// Merkmale eines Objektes lesen

// Datentypen -----------------------------------------------------------------
class MerkInfo {
public:
// Typ der MerkmalsInformation
	enum MerkInfoTyp {
		MI_Unknown,
		MI_Text,
		MI_Long,
		MI_Double,
	};

private:
	long miMCode;		// MerkmalsCode
	MerkInfoTyp miTyp;	// MerkmalsTyp

protected:
	short miLen;		// Wiederholungsfaktor

// abstract class: Konstruktor/Destruktor
		MerkInfo (long MCode, MerkInfoTyp Typ, short Len);

public:
		~MerkInfo (void) {}

	MerkInfoTyp isA (void) { return miTyp; }
	long MCode (void) { return miMCode; }
	short MLen (void) { return miLen; }	
};

class TextMerkInfo : public MerkInfo {
private:
	char *miText;		// MerkmalsText

public:
// Konstruktor/Destruktor
		TextMerkInfo (long MCode, char *Text);
		~TextMerkInfo (void);

	char *Text (char *Buffer = NULL, short iLen = 0);
};

class LongMerkInfo : public MerkInfo {
private:
	long *miLong;		// MerkmalsWerte

public:
// Konstruktor/Destruktor
		LongMerkInfo (long MCode, long *Werte, long Len);
		~LongMerkInfo (void);

	long *LongWerte (long *LongFeld = NULL, short iLen = 0);
};

class DoubleMerkInfo : public MerkInfo {
private:
	double *miDouble;		// MerkmalsWerte

public:
// Konstruktor/Destruktor
		DoubleMerkInfo (long MCode, double *Werte, long Len);
		~DoubleMerkInfo (void);

	double *DoubleWerte (double *DoubleFeld = NULL, short iLen = 0);
};


#endif
