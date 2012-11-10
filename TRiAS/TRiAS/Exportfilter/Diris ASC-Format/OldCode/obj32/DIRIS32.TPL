; ModulDefinitionsFile für Export-DLL DIRIS32

LIBRARY		DIRISASC

DESCRIPTION	'Export von Daten im DIRIS-Austauschformat V@A.@B (Build @C), (C) #@D'

EXPORTS
	DIRISASCEXPORTBEGIN		= _DirisAscExportBegin@16	@10
	DIRISASCEXPORTCOMMENT		= _DirisAscExportComment@8	@11
	DIRISASCEXPORTHEADER		= _DirisAscExportHeader@8	@12
	DIRISASCEXPORTDESCRIPTION	= _DirisAscExportDescription@12	@13
	DIRISASCEXPORTDATA		= _DirisAscExportData@20	@14
	DIRISASCEXPORTTRAILER		= _DirisAscExportTrailer@8	@15
	DIRISASCEXPORTEND		= _DirisAscExportEnd@4		@16
	DIRISASCGETEXPORTCAPS		= _DirisAscGetExportCaps@4	@17
	DIRISASCEXPORTBREAK		= _DirisAscExportBreak@4	@18
	DIRISASCEXPORTDESCRIPTIONEX	= _DirisAscExportDescriptionEx@16	@19
