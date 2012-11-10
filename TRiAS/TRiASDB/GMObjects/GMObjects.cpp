#define __BUILD_HEADERS__F1946A90_CE1B_11d1_8F28_0060085FC1CE
#define	__BUILD_CONSTANTS__B8DDC940_0057_11d2_8F56_0060085FC1CE
#include "GMObjects/GMObjects.h"
#include "GMObjBuild.h"

#define	__IMPLEMENTATION_EXCLUDES__			\
	exclude("_IGCollection" )				\
	exclude("_IGDynaCollection" )			\
	exclude("_DGMStyleBase")				\
	rename("_DGMLegends", "DGMLegends")		\
	rename("_DGMLegend", "DGMLegend")

#import "GMObjects/tlb/PCSS.tlb"	\
	__IMPLEMENTATION_EXCLUDES__		\
	no_namespace					\
	raw_native_types				\
	named_guids						\
	implementation_only

#import "GMObjects/tlb/Mapview.tlb"	\
	__IMPLEMENTATION_EXCLUDES__		\
	no_namespace					\
	raw_native_types				\
	named_guids						\
	implementation_only

#import "GMObjects/tlb/DefCoordSystem.tlb"	\
	__IMPLEMENTATION_EXCLUDES__		\
	no_namespace					\
	raw_native_types				\
	named_guids						\
	implementation_only

