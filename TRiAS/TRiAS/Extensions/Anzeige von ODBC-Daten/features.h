#ifndef __FEATURES_H__FILE
#define __FEATURES_H__FILE

//
// feature name<->code handling
//
// feature.h
//


/*/
// forwards
//

struct ITRiASFeature;
struct ITRiASObjects;
*/
HRESULT GetFeatureHandle (INT_PTR lIdent, LPCSTR pcName, INT_PTR *phFeat);
HRESULT GetFeature (INT_PTR lIdent, LPCSTR pcName, ITRiASFeature **ppIFeat);
HRESULT GetObjectsDef (ULONG ulIdent, ITRiASObjects **ppIObjs);
HRESULT GetFeatureName (INT_PTR hFeat, LPSTR pBuffer, int iLen);

#endif //__FEATURES_H__FILE