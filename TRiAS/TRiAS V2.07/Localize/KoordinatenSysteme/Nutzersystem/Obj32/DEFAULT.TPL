; Moduldefinitionsdatei für eine Koordinatentransformation

LIBRARY		DEFAULT

DESCRIPTION	'Standardkoordinatentransformation V@A.@B.@C, (C) #@D'

EXPORTS
	COORDTRANSLOAD		= _CoordTransLoad@4		@1
	COORDTRANSUNLOAD	= _CoordTransUnLoad@0		@2
	COORDTRANSDESCRIPTION	= _CoordTransDescription@4	@3
	COORDTRANSASPECTRATIO	= _CoordTransAspectRatio@8	@4
;	COORDTRANSMODE		= _CoordTransMode@4		@5
	TRANSFORM		= _Transform@8			@6
	INVTRANSFORM		= _InvTransform@8		@7
	COORDTRANSDISTANCE	= _CoordTransDistance@8		@8
	COORDTRANSTOSTRING	= _CoordTransToString@20	@9
	COORDTRANSTOVALUE	= _CoordTransToValue@4		@10
	COORDTRANSRECTANGLE	= _CoordTransRectangle@12	@11
	COORDTRANSISMETRIC	= _CoordTransIsMetric@0		@12
	COORDTRANSNATIVE	= _CoordTransNative@8		@13
	COORDTRANSMETRIC	= _CoordTransMetric@8		@14

	COORDTRANSNATIVEEX		= _CoordTransNativeEx@12	@15
	COORDTRANSMETRICEX		= _CoordTransMetricEx@12	@16
	COORDTRANSNATIVEPARAM	= _CoordTransNativeParam@8	@17
	COORDTRANSMETRICPARAM	= _CoordTransMetricParam@8	@18
;
	DllRegisterServer		= _DllRegisterServer@0		@19
	DllUnregisterServer		= _DllUnregisterServer@0	@20
