// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.01.2001 11:22:29 
//
// @doc
// @module StatistValues.cpp | Definition of several statistics classes

#include "StdAfx.h"

#include <Atl/Ciid.h>

#include "StatistApp.h"
#include "StatistValue.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASStatistCount, CStatistCount)
RT_OBJECT_ENTRY(CLSID_TRiASStatistCountNotNull, CStatistCountNotNull)
RT_OBJECT_ENTRY(CLSID_TRiASStatistSum, CStatistSum)
RT_OBJECT_ENTRY(CLSID_TRiASStatistArithmeticAverage, CStatistArithAverage)
RT_OBJECT_ENTRY(CLSID_TRiASStatistGeometricAverage, CStatistGeomAverage)
RT_OBJECT_ENTRY(CLSID_TRiASStatistMedian, CStatistMedian)
RT_OBJECT_ENTRY(CLSID_TRiASStatistMinValue, CStatistMinValue)
RT_OBJECT_ENTRY(CLSID_TRiASStatistMaxValue, CStatistMaxValue)
RT_OBJECT_ENTRY(CLSID_TRiASStatistRange, CStatistRange)
RT_OBJECT_ENTRY(CLSID_TRiASStatistStandardDeviation, CStatistStandardDeviation)
RT_OBJECT_ENTRY(CLSID_TRiASStatistVariance, CStatistVariance)
