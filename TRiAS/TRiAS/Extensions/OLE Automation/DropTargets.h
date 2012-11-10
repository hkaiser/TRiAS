///////////////////////////////////////////////////////////////////////////////
// Helperklasse für Drag'n Drop

#if !defined(_DROPTARGETS_H)
#define _DROPTARGETS_H

///////////////////////////////////////////////////////////////////////////////
// benötigte SmartInterfaces
DefineSmartInterface(DropTarget);

class CDropTargets : 
	public map<HWND, WDropTarget, less<HWND> >
{
public:
	HRESULT DragEnter (HWND hWnd, IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
	{
	iterator it = find(hWnd);
	
		if (it == end()) return S_FALSE;	// einfach weitermachen
		return (*it).second -> DragEnter (pDataObj, grfKeyState, pt, pdwEffect);
	}
	HRESULT DragOver (HWND hWnd, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
	{
	iterator it = find(hWnd);
	
		if (it == end()) return S_FALSE;	// einfach weitermachen
		return (*it).second -> DragOver (grfKeyState, pt, pdwEffect);
	}
	HRESULT DragLeave (HWND hWnd)
	{
	iterator it = find(hWnd);
	
		if (it == end()) return S_FALSE;	// einfach weitermachen
		return (*it).second -> DragLeave();
	}
	HRESULT Drop (HWND hWnd, IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
	{
	iterator it = find(hWnd);
	
		if (it == end()) return S_FALSE;	// einfach weitermachen
		return (*it).second -> Drop (pDataObj, grfKeyState, pt, pdwEffect);
	}
};

#endif // _DROPTARGETS_H
