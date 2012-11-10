// CommonDialog Wrapper für ColorDlg ------------------------------------------
// File: COLR31IM.CXX

#include "tfrmpre.hxx"

#include <commdlg.h>
#include <win31imp.hxx>

CStdColorDlg_Win31 :: CStdColorDlg_Win31 (HWND hW, Color *c)
{
	flags = 0;
	hwnd = hW;
	DefColor = *((long*)c);

HDC hDC = GetDC(hwnd);

	CustomColors[1]=GetBkColor(hDC);
	ReleaseDC(hwnd, hDC);
	CustomColors[0] = DefColor;
	for (short count = 2; count <= 15; count++)
		CustomColors[count] = CustomColors[1];
}

CStdColorDlg_Win31 :: ~CStdColorDlg_Win31 (void)
{
}

void CStdColorDlg_Win31 :: GetColor (Color *retval)
{
	*((long*)retval) = DefColor ; 
}

bool CStdColorDlg_Win31 :: Show (void)
{
CHOOSECOLOR cc;
Bool ret_value;

	cc.lStructSize    = sizeof(CHOOSECOLOR);  
	cc.hwndOwner      = hwnd;
	cc.hInstance      = NULL;
	cc.rgbResult      = DefColor;
	cc.lpCustColors   = (unsigned long*)CustomColors;
	cc.Flags          = flags;
	cc.lCustData      = 0;
	cc.lpfnHook       = 0;
	cc.lpTemplateName = 0;

	if (ret_value = ChooseColor( &cc))
		DefColor = cc.rgbResult;

return ( ret_value);
}

