// Datenbank-šbersicht ------------------------------------------------------
// File: ATTINFO.HXX

#if !defined(_ATTINFO_HXX)
#define _ATTINFO_HXX

// Anzeigen von Identifikatoren ---------------------
class IdentInformation : public ModeLessDialog {
private:

	bool _fWasInterrupted;

	long _lIdents;	
	long _Number;
	long _Key;
	PushButton CancelButton;
	ResourceFile &_RF;
	pWindow _pW;
	short _iRangeAll;
	short _iCurrVal;
	GaugeBox _Status;
	
protected:
	void _XTENSN_EXPORT ButtonClick (ControlEvt);

public:
		IdentInformation (pWindow pW, uint res, ResourceFile &RF ,pchar pCaption, short iRange);
		~IdentInformation (void);


//Memberfunktionen
	bool Break (void) { 
#if defined(WIN32)
		App :: Exec (ExecWhileEvent);  // bei Windows nachfragen
#else
		CallAppExec (ExecWhileEvent);
#endif // WIN32
		return _fWasInterrupted; 
	}

	void SetPosition (short iCnt) { _Status.SetPosition ( iCnt);}

	void ModifyWindow ( long Ident );
	void SetText ( short iCnt );
	void SetStart ( void );

};

#endif	// ATTINFO.HXX
