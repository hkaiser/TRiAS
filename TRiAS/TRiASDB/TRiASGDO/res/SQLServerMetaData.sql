-- $Header: $
-- Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
-- Created: 17.11.2002 21:28:12 
--
-- @doc
-- @module SQLServerMetaData.sql | Create SQL-Server metadata for new database

-- Create the  GAliasTable
IF EXISTS(SELECT * FROM sysobjects WHERE id = object_id('GAliasTable'))
DROP TABLE GAliasTable
SET ANSI_PADDING ON
CREATE TABLE  GAliasTable(
	TableType VARCHAR(255) PRIMARY KEY,
	TableName VARCHAR(255) NOT NULL)
GO
-- Create the  GFeatures
IF EXISTS(SELECT * FROM sysobjects WHERE id = object_id('GFeatures'))
DROP TABLE GFeatures
SET ANSI_PADDING ON
CREATE TABLE  GFeatures(
	FeatureName VARCHAR(255) PRIMARY KEY,
	GeometryType INT NULL,
	PrimaryGeometryFieldName VARCHAR(255),
	FeatureDescription VARCHAR(255))
GO
-- Create the  FieldLookup
IF EXISTS(SELECT * FROM sysobjects WHERE id = object_id('FieldLookup'))
DROP TABLE FieldLookup
SET ANSI_PADDING ON
CREATE TABLE  FieldLookup(
	IndexID INT PRIMARY KEY IDENTITY,
	FeatureName VARCHAR(255) NOT NULL,
	FieldName   VARCHAR(255) NOT NULL)
GO
-- Create the  AttributeProperties
IF EXISTS(SELECT * FROM sysobjects WHERE id = object_id('AttributeProperties'))
DROP TABLE AttributeProperties
SET ANSI_PADDING ON
CREATE TABLE  AttributeProperties(
	IndexID INT PRIMARY KEY,
	IsKeyField BIT,
	FieldDescription VARCHAR(255), 
	FieldFormat VARCHAR(255),
	FieldType SMALLINT,
	IsFieldDisplayable BIT,
	FieldPrecision SMALLINT) 
GO
-- Create the  GeometryProperties
IF EXISTS(SELECT * FROM sysobjects WHERE id = object_id('GeometryProperties'))
DROP TABLE GeometryProperties
SET ANSI_PADDING ON
CREATE TABLE  GeometryProperties(
	IndexID INT PRIMARY KEY,
	PrimaryGeometryFlag BIT,
	GeometryType INT,
	GCoordSystemGUID VARCHAR(39) ,
	FieldDescription VARCHAR(255))
GO
-- Create the  GCoordSystem
IF EXISTS(SELECT * FROM sysobjects WHERE id = object_id('GCoordSystem'))
DROP TABLE GCoordSystem
SET ANSI_PADDING ON
CREATE TABLE  GCoordSystem(
	CSGUID VARCHAR(39) PRIMARY KEY,
	CSGUIDTYPE INT,
	Name VARCHAR(255),
	Description VARCHAR(255),
	BaseStorageType TINYINT,
	Stor2CompMatrix1 FLOAT,
	Stor2CompMatrix2 FLOAT,
	Stor2CompMatrix3 FLOAT,
	Stor2CompMatrix4 FLOAT,
	Stor2CompMatrix5 FLOAT,
	Stor2CompMatrix6 FLOAT,
	Stor2CompMatrix7 FLOAT,
	Stor2CompMatrix8 FLOAT,
	Stor2CompMatrix9 FLOAT,
	Stor2CompMatrix10 FLOAT,
	Stor2CompMatrix11 FLOAT,
	Stor2CompMatrix12 FLOAT,
	Stor2CompMatrix13 FLOAT,
	Stor2CompMatrix14 FLOAT,
	Stor2CompMatrix15 FLOAT,
	Stor2CompMatrix16 FLOAT,
	HeightStorageType TINYINT,
	LonNormStorageOpt TINYINT,
	GeodeticDatum SMALLINT,
	Ellipsoid SMALLINT,
	EquatorialRadius FLOAT,
	InverseFlattening FLOAT,
	ProjAlgorithm SMALLINT,
	AzimuthAngle FLOAT,
	FalseX FLOAT,
	FalseY FLOAT,
	Hemisphere TINYINT,
	LatOfOrigin FLOAT,
	LatOfTrueScale FLOAT,
	LonOfOrigin FLOAT,
	RadOfStandCircle FLOAT,
	ScaleReductFact FLOAT,
	StandPar1 FLOAT,
	StandPar2 FLOAT,
	Zone SMALLINT,
	PathNumber SMALLINT,
	RowNumber SMALLINT,
	Satellite SMALLINT,
	XAzDefOpt TINYINT,
	GeomHeightOfOrig FLOAT,
	GeomHeightOfPoint1 FLOAT,
	GeomHeightOfPoint2 FLOAT,
	LatOfPoint1 FLOAT,
	LatOfPoint2 FLOAT,
	LonOfPoint1 FLOAT,
	LonOfPoint2 FLOAT,
	ArgumentOfPerigee FLOAT,
	EarthRotPeriod FLOAT,
	FourierExpansionDegree TINYINT,
	NodesInSimpsonIntegration TINYINT,
	OrbEarthRotPeriodRatio FLOAT,
	OrbEcc FLOAT,
	OrbInclination FLOAT,
	OrbOff FLOAT,
	OrbPeriod FLOAT,
	OrbSemimajAxis FLOAT,
	OblMercDefMode TINYINT,
	LatOfMapCenter FLOAT,
	OblLamConfConDefMode TINYINT,
	RotNorthPoleLat FLOAT,
	RotNorthPoleLon FLOAT,
	GaussianLat FLOAT,
	SpherModel TINYINT,
	SpherRadius FLOAT,
	LatOfBasisPointA FLOAT,
	LatOfBasisPointB FLOAT,
	LatOfBasisPointC FLOAT,
	LonOfBasisPointA FLOAT,
	LonOfBasisPointB FLOAT,
	LonOfBasisPointC FLOAT,
	ChamTriOriginDefMode TINYINT,
	AngOrientationProjPlaneDefMode TINYINT,
	AzOfUpwardTilt FLOAT,
	FocalLength FLOAT,
	HeightAboveEllipAtNadir FLOAT,
	HeightOrigOfLocalHorizSys FLOAT,
	LatOrigOfLocalHorizSys FLOAT,
	LocationOfProjPlaneDefMode TINYINT,
	LonOrigOfLocalHorizSys FLOAT,
	PerspCenterGeocX FLOAT,
	PerspCenterGeocY FLOAT,
	PerspCenterGeocZ FLOAT,
	PerspCenterHeight FLOAT,
	PerspCenterLat FLOAT,
	PerspCenterLon FLOAT,
	PerspCenterXEast FLOAT,
	PerspCenterYNorth FLOAT,
	PerspCenterZUp FLOAT,
	RefCoordSysDefMode TINYINT,
	RotAboutXAxis FLOAT,
	RotAboutYAxis FLOAT,
	RotAboutZAxis FLOAT,
	SwingAng FLOAT,
	TiltAng FLOAT,
	ExtendProjMatrix1 FLOAT,
	ExtendProjMatrix2 FLOAT,
	ExtendProjMatrix3 FLOAT,
	ExtendProjMatrix4 FLOAT,
	ExtendProjMatrix5 FLOAT,
	ExtendProjMatrix6 FLOAT,
	ExtendProjMatrix7 FLOAT,
	ExtendProjMatrix8 FLOAT,
	ExtendProjMatrix9 FLOAT,
	ExtendProjMatrix10 FLOAT,
	ExtendProjMatrix11 FLOAT,
	ExtendProjMatrix12 FLOAT,
	ExtendProjMatrix13 FLOAT,
	ExtendProjMatrix14 FLOAT,
	ExtendProjMatrix15 FLOAT,
	ExtendProjMatrix16 FLOAT,
	VerticalDatum SMALLINT,
	UndulationModel SMALLINT,
	AverageUndulation FLOAT)
GO
-- Create the  ModificationLog
IF EXISTS(SELECT  * FROM sysobjects WHERE id = object_id('ModificationLog'))
DROP TABLE ModificationLog
SET ANSI_PADDING ON
CREATE TABLE  ModificationLog(
	ModificationNumber INT PRIMARY KEY IDENTITY,
	Type TINYINT, 
	ModifiedTableID INT, 
	KeyValue1 VARCHAR(255),
	KeyValue2 VARCHAR(255),
	KeyValue3 VARCHAR(255),
	KeyValue4 VARCHAR(255),
	KeyValue5 VARCHAR(255),
	KeyValue6 VARCHAR(255),
	KeyValue7 VARCHAR(255),
	KeyValue8 VARCHAR(255),
	KeyValue9 VARCHAR(255),
	KeyValue10 VARCHAR(255),
	SESSIONID INT)
GO
-- Create the  ModifiedTables
IF EXISTS(SELECT  * FROM sysobjects WHERE id = object_id('ModifiedTables'))
DROP TABLE ModifiedTables
SET ANSI_PADDING ON
CREATE TABLE  ModifiedTables(
	ModifiedTableID INT PRIMARY KEY IDENTITY,
	TableName VARCHAR(255), 
	KeyField1 VARCHAR(255), 
	KeyField2 VARCHAR(255), 
	KeyField3 VARCHAR(255), 
	KeyField4 VARCHAR(255), 
	KeyField5 VARCHAR(255), 
	KeyField6 VARCHAR(255), 
	KeyField7 VARCHAR(255), 
	KeyField8 VARCHAR(255), 
	KeyField9 VARCHAR(255), 
	KeyField10 VARCHAR(255))
GO
-- Create the  GParameters
IF EXISTS(SELECT  * FROM sysobjects WHERE id = object_id('GParameters'))
DROP TABLE GParameters
SET ANSI_PADDING ON
CREATE TABLE  GParameters(
	GPARAMETER VARCHAR(255) PRIMARY KEY,
	GVALUE VARCHAR(255) NOT NULL)
GO
-- Create the  GFieldMapping
IF EXISTS(SELECT  * FROM sysobjects WHERE id = object_id('GFieldMapping'))
DROP TABLE GFieldMapping
SET ANSI_PADDING ON
CREATE TABLE GFieldMapping(
	TABLE_NAME VARCHAR(255) NOT NULL,
	COLUMN_NAME VARCHAR(255) NOT NULL,
	DATA_TYPE INT,
	DATA_SUBTYPE INT,
	CSGUID VARCHAR(39)  NULL,
	AUTOINCREMENT BIT, 
	primary key(TABLE_NAME, COLUMN_NAME))
GO
-- Insert the required info into the newly created tables
INSERT INTO GAliasTable VALUES('INGRFeatures','GFeatures')
INSERT INTO GAliasTable VALUES('INGRFieldLookup','FieldLookup')
INSERT INTO GAliasTable VALUES('INGRAttributeProperties','AttributeProperties')
INSERT INTO GAliasTable VALUES('INGRGeometryProperties','GeometryProperties')
INSERT INTO GAliasTable VALUES('GCoordSystemTable','GCoordSystem')
INSERT INTO GAliasTable VALUES('GModifications','ModificationLog')
INSERT INTO GAliasTable VALUES('GModifiedTables','ModifiedTables')
INSERT INTO GAliasTable VALUES('GParameters','GParameters')
INSERT INTO GAliasTable VALUES('GADOFieldMapping','GFieldMapping')
INSERT INTO GAliasTable VALUES('INGRDictionaryProperties','GDictionaryProperties')
GO
INSERT INTO GParameters VALUES('ADOTypeForBinaryStorage','205')
INSERT INTO GParameters VALUES('ADOTypeForGeometryStorage','205')
INSERT INTO GParameters VALUES('ADOTypeForDateStorage','135')
GO
