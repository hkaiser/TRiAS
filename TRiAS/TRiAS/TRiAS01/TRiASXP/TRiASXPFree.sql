-- $Header: $
-- Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
-- Created: 16.08.2001 21:56:50 
--
-- @doc
-- @module TRiASXPFree.sql | Uninstall OGC extended stored procedures etc.

-------------------------------------------------------------------------------
-- remove extended stored procedures

USE master	-- should be installed to master db

-- xp_AsText
IF EXISTS (SELECT * FROM sysobjects WHERE id = object_id(N'[master].[dbo].[xp_AsText]') and xtype = N'X')
	EXEC sp_dropextendedproc N'xp_AsText'
GO

-------------------------------------------------------------------------------
-- Remove user defined functions

USE testdb	-- should be installed to local db

-- AsText()
IF EXISTS (SELECT * FROM sysobjects WHERE id = object_id(N'[dbo].[AsText]') and xtype in (N'FN', N'IF', N'TF'))
	DROP FUNCTION [dbo].[AsText]
GO

-------------------------------------------------------------------------------
-- free XP dll
DBCC TRiASXP(FREE)
GO

