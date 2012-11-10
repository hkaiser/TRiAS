// -*-C++-*- directory.cc
// <!!----------------------------------------------------------------------> 
// <!! Copyright (C) 1998 Dietmar Kuehl, Claas Solutions GmbH > 
// <!!> 
// <!! Permission to use, copy, modify, distribute and sell this > 
// <!! software for any purpose is hereby granted without fee, provided > 
// <!! that the above copyright notice appears in all copies and that > 
// <!! both that copyright notice and this permission notice appear in > 
// <!! supporting documentation. Dietmar Kuehl and Claas Solutions make no > 
// <!! representations about the suitability of this software for any > 
// <!! purpose. It is provided "as is" without express or implied warranty. > 
// <!!----------------------------------------------------------------------> 

// Author: Dietmar Kuehl dietmar.kuehl@claas-solutions.de 
// Title:  Implementation of the directory iterator
// Version: $Name: Release-1-0 $ $Id: directory.cpp,v 1.5 1998/11/11 03:06:16 kuehl Exp $

// -------------------------------------------------------------------------- 

#include "stdafx.h"
#include "directory.h"

// -------------------------------------------------------------------------- 

boost::filesystem::dir_it::dir_it():
	rep(new representation())
{
}

boost::filesystem::dir_it::dir_it(string const &dirname):
	rep(new representation(dirname))
{
}

#if defined(BOOST_WINNT)
boost::filesystem::dir_it::dir_it(string const &dirname, string const &pattern):
	rep(new representation(dirname, pattern))
{
}
#endif // defined(BOOST_WINNT)

boost::filesystem::dir_it::dir_it(boost::filesystem::dir_it const &it):
	rep(it.rep->reference())
{
}

boost::filesystem::dir_it::~dir_it()
{
	delete rep->release();
}

boost::filesystem::dir_it &boost::filesystem::dir_it::operator= (boost::filesystem::dir_it const &it)
{
	it.rep->reference();
	delete rep->release();
	rep = it.rep;
	return *this;
}

// -------------------------------------------------------------------------- 

string boost::filesystem::dir_it::operator* () const
{
	return *(*rep);
}

boost::filesystem::dir_it &boost::filesystem::dir_it::operator++ ()
{
	++(*rep);
	return *this;
}

boost::filesystem::dir_it::proxy boost::filesystem::dir_it::operator++ (int)
{
	string rc(*(*rep));
	++(*rep);
	return rc;
}

// -------------------------------------------------------------------------- 

bool boost::filesystem::dir_it::operator== (boost::filesystem::dir_it const &it) const
{
	return *rep == *(it.rep);
}

bool boost::filesystem::dir_it::operator!= (boost::filesystem::dir_it const &it) const
{
	return !(*rep == *(it.rep));
}
