#ifndef _CLIPBRD_HXX
#define _CLIPBRD_HXX


class CClipBoard_Imp;	// declaration only

class _TF_ENTRY32 CClipboard
{
private:
	class CClipBoard_Imp *cb_imp;

public:
	enum Format	{ FmtText, FmtBitmap };

	CClipboard (void);

void   	Clear (void);	
void	Insert (const char *txt);
void	Insert (const pBitmap);
long	GetItemSize (Format);
BOOL	Retrieve (char *, int len = -1);
BOOL	Retrieve (pBitmap);

 	~CClipboard (void);
};
#endif

