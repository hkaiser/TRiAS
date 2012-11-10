// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/18/1998 09:10:03 PM
//
// @doc
// @module MatchBase.cpp | Description goes here

#include "stdafx.h"

#include "Helper.h"
#include "MatchBase.h"

// DMatchString
IMPLEMENT_PROPERTY_ACCESS(CMatchStringBase, MatchText, BSTR);
IMPLEMENT_PROPERTY_ACCESS(CMatchStringBase, MatchCase, VARIANT_BOOL);
IMPLEMENT_PROPERTY_ACCESS(CMatchStringBase, NegateMatch, VARIANT_BOOL);
