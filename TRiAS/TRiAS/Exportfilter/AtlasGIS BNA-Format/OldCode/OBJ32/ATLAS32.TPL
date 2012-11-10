; ModulDefinitionsFile für Export-DLL ATLAS32

LIBRARY		ATLASBNA

DESCRIPTION	'Export von Daten im Atlas*GIS BNA-Format V@A.@B (Build @C), (C) #@D'

EXPORTS
	ATLASBNAEXPORTBEGIN		= _AtlasBnaExportBegin@16	@10
	ATLASBNAEXPORTCOMMENT		= _AtlasBnaExportComment@8	@11
	ATLASBNAEXPORTHEADER		= _AtlasBnaExportHeader@8	@12
	ATLASBNAEXPORTDESCRIPTION	= _AtlasBnaExportDescription@12	@13
	ATLASBNAEXPORTDATA		= _AtlasBnaExportData@20	@14
	ATLASBNAEXPORTTRAILER		= _AtlasBnaExportTrailer@8	@15
	ATLASBNAEXPORTEND		= _AtlasBnaExportEnd@4		@16
	ATLASBNAGETEXPORTCAPS		= _AtlasBnaGetExportCaps@4	@17
	ATLASBNAEXPORTBREAK		= _AtlasBnaExportBreak@4	@18
