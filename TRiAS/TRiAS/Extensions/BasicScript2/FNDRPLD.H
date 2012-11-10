
#if !defined(_FNDRPLD_H)
#define _FNDRPLD_H

class CFindReplaceDlg : public CFindReplaceDialog {
private:
public:
		CFindReplaceDlg (void);
		~CFindReplaceDlg (void);
		
static CFindReplaceDlg *CreateInstance ();
	BOOL FInit ();

};


#endif //_FNDRPLD_H
