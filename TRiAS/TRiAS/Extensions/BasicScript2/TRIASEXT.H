#ifndef _TRIASEXT_H
#define _TRIASEXT_H

// Registriert diese Erweiterung als PropertySheetExt ----------------------
bool RegisterHandler (REFCLSID rclsid, LPCTSTR pcProgID, UINT uiName, 
					  REFCLSID rTargetId, LPCTSTR pcTargetPropgID);
// DeRegistriert diese Erweiterung --------------------------------------------
inline bool _ExtRegDeleteKeySucceeded(LONG error);

bool UnRegisterHandler (REFCLSID rclsid, LPCTSTR pcProgID, 
						REFCLSID rTargetId, LPCTSTR pcTargetPropgID);

#endif //_TRIASEXT_H