#include "TErrTrk.h"
#include "resource.h"

DefineSmartInterface(ErrorItem)

// {104FA1B0-9425-11d2-98B0-0060085FC1CE}
extern "C" const IID __declspec(selectany) IID_IEnumErrorItem =
	{ 0x104fa1b0, 0x9425, 0x11d2, { 0x98, 0xb0, 0x0, 0x60, 0x8, 0x5f, 0xc1, 0xce } };

DefineEnumerator2(WErrorItem, IID_IEnumErrorItem )	// NEnumWErrorItem
DefineSmartEnumerator2(WErrorItem, IID_IEnumErrorItem)					// WEnumWErrorItem

#include <MakeEnumVariant.h>