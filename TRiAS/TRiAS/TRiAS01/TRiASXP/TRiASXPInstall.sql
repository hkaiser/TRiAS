-- $Header: $
-- Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
-- Created: 12.08.2001 17:59:11 
--
-- @doc
-- @module TRiASXPInstall.sql | Install OGC extended stored procedures etc.

-------------------------------------------------------------------------------
-- Install extended stored procedures

USE master	-- should be installed to master db

-- xp_AsText
IF EXISTS (SELECT * FROM sysobjects WHERE id = object_id(N'[master].[dbo].[xp_AsText]') and xtype = N'X')
	EXEC sp_dropextendedproc N'xp_AsText'
GO

EXEC sp_addextendedproc N'xp_AsText', 'TRiASXP.dll'
GO

GRANT EXEC ON [master].[dbo].[xp_AsText] TO PUBLIC 
GO

-------------------------------------------------------------------------------
-- Install user defined functions

USE testdb	-- should be installed to local db

-- AsText()
IF EXISTS (SELECT * FROM sysobjects WHERE id = object_id(N'[dbo].[AsText]') and xtype in (N'FN', N'IF', N'TF'))
	DROP FUNCTION [dbo].[AsText]
GO

CREATE FUNCTION  [dbo].[AsText] (@geometry AS IMAGE) 
RETURNS VARCHAR(8000)
AS
BEGIN
DECLARE @retval AS VARCHAR(8000)

	EXEC [master].[dbo].[xp_AsText] @geometry, @retval OUTPUT
	RETURN  CAST(@retval AS VARCHAR(8000))
END
GO

