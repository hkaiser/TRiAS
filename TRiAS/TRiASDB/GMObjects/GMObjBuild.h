#define	__IMPLEMENTATION_EXCLUDES__			\
	exclude("_IGCollection" )				\
	exclude("_IGDynaCollection" )			\
	exclude("_DGMStyleBase")				\
	rename("_DGMLegends", "DGMLegends")		\
	rename("_DGMLegend", "DGMLegend")

#define	STD_IMPORT					\
	__IMPLEMENTATION_EXCLUDES__		\
	no_namespace					\
	raw_native_types				\
	named_guids						\
	no_implementation

#define	RAW_IMPORT		STD_IMPORT raw_interfaces_only

#import "GMObjects/tlb/PClient.tlb"					RAW_IMPORT
#import "GMObjects/tlb/PCSS.tlb"					STD_IMPORT
#import "GMObjects/tlb/PView.tlb"					RAW_IMPORT
#import "GMObjects/tlb/Mapview.tlb"					STD_IMPORT
#import "GMObjects/tlb/PBasic.tlb"					RAW_IMPORT	\
	rename("point","GMPoint")							\
	rename("Vector","Vector")							\
	rename("Matrix","Matrix")							\
	rename("Points","Points")							\
	rename("PointGeometry","PointGeometry")			\
	rename("LineGeometry","LineGeometry")				\
	rename("PolylineGeometry","PolylineGeometry")		\
	rename("PolygonGeometry","PolygonGeometry")		\
	rename("BoundaryGeometry","BoundaryGeometry")		\
	rename("RectangleGeometry","RectangleGeometry")	\
	rename("OrientedPointGeometry","OrientedPointGeometry")	\
	rename("TextPointGeometry","TextPointGeometry")			\
	rename("ArcGeometry","ArcGeometry")						\
	rename("CompositePolylineGeometry","CompositePolylineGeometry")	\
	rename("CompositePolygonGeometry","CompositePolygonGeometry")		\
	rename("EventServer","EventServer")								\
	rename("SmartLocateService","SmartLocateService")
#import "GMObjects/tlb/PService.dll"				RAW_IMPORT
#import "GMObjects/tlb/GeoMedia.tlb"				RAW_IMPORT	\
			rename("Application","GMApplication")
#import "GMObjects/tlb/PDBPipe.tlb"					RAW_IMPORT	\
			exclude("GDatabase")							\
			exclude("GRecordsets","GRecordset")				\
			exclude("ExtendedPropertySet")					\
			exclude("GFields","GField")						\
			exclude("GErrors","GError")						\
			exclude("GIndexes","GIndex")					\
			exclude("GTableDefs","GTableDef")				\
			exclude("Notification")							\
			exclude("OriginatingPipe")						\
			exclude("RecordsetListener")					\
			exclude("EqualityExtension")
#import "GMObjects/tlb/DefCoordSystem.tlb"			STD_IMPORT
