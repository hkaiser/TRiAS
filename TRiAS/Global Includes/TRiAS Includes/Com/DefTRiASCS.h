#if !defined(_TRIASCSWRAPPERS_H_2B8D1810_09E3_11d3_9962_0060085FC1CE)
#define _TRIASCSWRAPPERS_H_2B8D1810_09E3_11d3_9962_0060085FC1CE

#if !defined(_SMARTIF_H__F5802CB5_D772_11D1_85F2_00600875138A__INCLUDED_)
#error "You must include com/Smartif.h first
#endif

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

DefineSmartInterface(TRiASCS)
DefineSmartInterface(TRiASCSSet)
DefineSmartInterface(TRiASCSPCS)
DefineSmartInterface(TRiASCSGCS)
DefineSmartInterface(TRiASCSDatumTransformation)
DefineSmartInterface(TRiASCSTransform)
DefineSmartInterface(TRiASCSTransformData)
DefineSmartInterface(TRiASCSValidate)
DefineSmartInterface(TRiASCSTransformInfo)

#endif // _TRIASCSWRAPPERS_H_2B8D1810_09E3_11d3_9962_0060085FC1CE
