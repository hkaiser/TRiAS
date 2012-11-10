// Aus PRINTER.HXX herausgelöster Header --------------------------------------
// File: PRNTPARS.HXX

#if !defined(_PRNTPARS_HXX)
#define _PRNTPARS_HXX

class PrinterPars : 
	public PrintingDevice 
{	/// DruckerInformationen
private:
	DVTARGETDEVICE *m_ptd;

protected:
	void Tidy (void) { if (NULL != m_ptd) CoTaskMemFree (m_ptd); }

public:
		PrinterPars (void) : m_ptd(NULL) {}
		~PrinterPars (void) { Tidy(); }

#if !defined(__TRIAS02DLL__)		// Abfragefunktionen
_TRIAS03_ENTRY Point EXPORT03 GetAspectRatio (void);
_TRIAS03_ENTRY DoublePair EXPORT03 GetDotsPerMM (void);
_TRIAS03_ENTRY Dimension EXPORT03 GetPageSize (void);
_TRIAS03_ENTRY bool InitFromDefaultPrinter (void);
_TRIAS03_ENTRY bool InitFromData (DVTARGETDEVICE *pdvt);
_TRIAS03_ENTRY bool SetUp (void);
_TRIAS03_ENTRY DVTARGETDEVICE *GetTargetDevice (void) const { return m_ptd; }
#endif
};

// repräsentiert den aktuell ausgewählten Drucker -----------------------------
class ActPrinterPars : public PrinterPars {
public:
	_TRIAS03_ENTRY EXPORT03 ActPrinterPars (void) {}
};

#endif // _PRNTPARS_HXX
