// Ausführen des MenuBefehls ID_FEATURE_CLASSIFY ------------------------------
// File: FCLASSFY.CXX

#include "featurep.hxx"
#include "feature.h"		// ResourceKonstanten

#include <propguid.h>

#if _MSC_VER >= 1000
#pragma warning (disable:4786)	// truncation of identifier name in browser database
#endif // _MSC_VER

#include <selidprp.h>		// PropertyActions (descriptions)
#include <clsfyprp.h>
#include <selrlprp.h>
#include <selobwnd.h>
#include <dstobwnd.h>

#include "propseq.hxx"

// Klassifikation von Objekten nach identischer Objekteigenschaft -------------
// Das Ganze ist als ActionPropertySequence implementiert:
//	'CLSPROP_ROOT\Recherche\Objektauswahl nach Identifikator und Typ'
//	'CLSPROP_ROOT\Recherche\Gruppieren von Objekten'
//	'CLSPROP_ROOT\Recherche\Bilden von Objektrelationen'
//	'CLSPROP_ROOT\Recherche\Objekte in Recherchefenster anzeigen'

static LPCSTR s_cbClsfyActs[] = {
	c_cbSelPrpName,
	c_cbClsfyPrpName,
	c_cbGenRelPrpName,
	c_cbDestObjWndName,
};
#define SIZEOF_ACTIONS sizeof(s_cbClsfyActs)/sizeof(s_cbClsfyActs[0])

bool CFeatureExtension :: ClassifyObjects (void)
{
// Generieren der geforderten Sequence
IPropertyActionSequence *pISeq = NULL;
HRESULT hr = InitPropertyActionSequence (m_pXtnSite, s_cbClsfyActs, 
					 SIZEOF_ACTIONS, &pISeq);
	if (FAILED(hr)) return false;

// durchführen der gewünschten Aktion
	hr = pISeq -> DoActions (hWnd(), NULL, NULL, NULL);
	pISeq -> Release();

return SUCCEEDED(hr);
}

// Klassifikation von Objekten nach identischer Objekteigenschaft -------------
// Das Ganze ist als ActionPropertySequence implementiert:
// 	'CLSPROP_ROOT\Recherche\Objektauswahl aus Recherchefenster'
//	'CLSPROP_ROOT\Recherche\Gruppieren von Objekten'
//	'CLSPROP_ROOT\Recherche\Bilden von Objektrelationen'
//	'CLSPROP_ROOT\Recherche\Objekte in Recherchefenster anzeigen'

static LPCSTR s_cbClsfyActsOR[] = {
	c_cbSelObjWndName,
	c_cbClsfyPrpName,
	c_cbGenRelPrpName,
	c_cbDestObjWndName,
};
#define SIZEOF_ACTIONS_OR sizeof(s_cbClsfyActsOR)/sizeof(s_cbClsfyActsOR[0])

bool CFeatureExtension :: ClassifyORObjects (void)
{
// Generieren der geforderten Sequence
IPropertyActionSequence *pISeq = NULL;
HRESULT hr = InitPropertyActionSequence (m_pXtnSite, s_cbClsfyActsOR, 
					 SIZEOF_ACTIONS_OR, &pISeq);
	if (FAILED(hr)) return false;

// durchführen der gewünschten Aktion
	hr = pISeq -> DoActions (hWnd(), NULL, NULL, NULL);
	pISeq -> Release();

return SUCCEEDED(hr);
}

