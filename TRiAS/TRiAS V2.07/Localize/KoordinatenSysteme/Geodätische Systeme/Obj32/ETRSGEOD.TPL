; Moduldefinitionsdatei für eine Koordinatentransformation

LIBRARY		ETRSGEOD

DESCRIPTION	'Koordinatentransformation Geodätisch (ETRS89) V@A.@B (Build @C), (C) #@D'

EXPORTS
	COORDTRANSLOAD			= _CoordTransLoad@4			@1
	COORDTRANSUNLOAD		= _CoordTransUnLoad@0		@2
	COORDTRANSDESCRIPTION	= _CoordTransDescription@4	@3
	COORDTRANSASPECTRATIO	= _CoordTransAspectRatio@8	@4
	COORDTRANSMODE			= _CoordTransMode@4			@5
	TRANSFORM				= _Transform@8				@6
	INVTRANSFORM			= _InvTransform@8			@7
	COORDTRANSDISTANCE		= _CoordTransDistance@8		@8
	COORDTRANSTOSTRING		= _CoordTransToString@20	@9
	COORDTRANSTOVALUE		= _CoordTransToValue@4		@10
	COORDTRANSRECTANGLE		= _CoordTransRectangle@12	@11
	COORDTRANSISMETRIC		= _CoordTransIsMetric@0		@12
	COORDTRANSNATIVE		= _CoordTransNative@8		@13
	COORDTRANSMETRIC		= _CoordTransMetric@8		@14
	COORDTRANSTOSTRINGEX	= _CoordTransToStringEx@16	@15
	COORDTRANSTOVALUEEX		= _CoordTransToValueEx@12	@16
	COORDTRANSDISTANCEEX	= _CoordTransDistanceEx@12	@17
	COORDTRANSNATIVEEX		= _CoordTransNativeEx@12	@18
	COORDTRANSMETRICEX		= _CoordTransMetricEx@12	@19
	COORDTRANSNATIVEPARAM	= _CoordTransNativeParam@8	@20
	COORDTRANSMETRICPARAM	= _CoordTransMetricParam@8	@21
	TRANSFORMEX				= _TransformEx@12			@22
	INVTRANSFORMEX			= _InvTransformEx@12		@23
;
	DllGetClassObject		= _DllGetClassObject@12		@24
	DllCanUnloadNow			= _DllCanUnloadNow@0		@25
	DllRegisterServer		= _DllRegisterServer@0		@26
	DllUnregisterServer		= _DllUnregisterServer@0	@27
