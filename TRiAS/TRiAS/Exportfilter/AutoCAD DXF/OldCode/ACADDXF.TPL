; ModulDefinitionsFile für Export-DLL ACADDXF

LIBRARY         ACADDXF

DESCRIPTION     'Export von Daten im AutoCad-DXF-Format V@A.@B (Build @C), (C) #@D'

EXPORTS
        ACADDXFEXPORTBEGIN             	= AcadDxfExportBegin       			@10
        ACADDXFEXPORTCOMMENT           	= AcadDxfExportComment      		@11
        ACADDXFEXPORTHEADER            	= AcadDxfExportHeader       		@12
        ACADDXFEXPORTDESCRIPTION       	= AcadDxfExportDescription 			@13
        ACADDXFEXPORTDATA              	= AcadDxfExportData        			@14
        ACADDXFEXPORTTRAILER           	= AcadDxfExportTrailer      		@15
        ACADDXFEXPORTEND               	= AcadDxfExportEnd          		@16
        ACADDXFGETEXPORTCAPS           	= AcadDxfGetExportCaps      		@17
        ACADDXFEXPORTBREAK             	= AcadDxfExportBreak        		@18
		ACADDXFEXPORTIDENTDESCRIPTION  	= AcadDxfExportIdentDescription 	@19
		ACADDXFEXPORTMERKMALDESCRIPTION = AcadDxfExportMerkmalDescription	@20





