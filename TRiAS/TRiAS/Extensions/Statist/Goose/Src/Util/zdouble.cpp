// This is -*- C++ -*-
// $Id: zdouble.cpp,v 1.4 1999/07/07 05:05:24 trow Exp $

/* 
 * zdouble.cpp
 *
 * Copyright (C) 1999 EMC Capital Management, Inc.
 *
 * Developed by Jon Trowbridge <trow@emccta.com>.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#include <config.h>
#include "Exception.h"
#include "zdouble.h"

const int encoding_basis = 63;
static bool know_endianness = false;
static bool little_endian = false;

// Lifted from GSL, who credit Harbison & Steele
static void
determine_endianness()
{
  union {
    long l;
    char c[sizeof(long)];
  } u;
  u.l = 1;
  know_endianness = true;
  little_endian = (u.c[sizeof(long)-1] == 1);
}

// Take an IEEE 8-byte double and expand it into 11 "XML-safe" characters.
void
encode_double(double x, char* buffer)
{
  char pool[11];
  unsigned char* byte = (unsigned char*)&x;

  if (!know_endianness)
    determine_endianness();
  if (little_endian) {
    // Convert to a big-endian representation
    unsigned char t;
   t = byte[0]; byte[0] = byte[7]; byte[7] = t;
   t = byte[1]; byte[1] = byte[6]; byte[6] = t;
   t = byte[2]; byte[2] = byte[5]; byte[5] = t;
   t = byte[3]; byte[3] = byte[4]; byte[4] = t;
  }

  // Calculate a gratuitous checksum
  unsigned char cs = byte[0] ^ byte[1] ^ byte[2] ^ byte[3] ^
    byte[4] ^ byte[5] ^ byte[6] ^ byte[7];
  int bit_1 = (cs >> 2) & 7;
  int bit_2 = (cs >> 5) & 7;
  cs = (cs & 3) ^ ((cs >> bit_1) & 1) ^ (((cs >> bit_2) << 1) & 2);

  pool[0] = byte[0] & 63;
  pool[1] = byte[1] & 63;
  pool[2] = byte[2] & 63;
  pool[3] = byte[3] & 63;
  pool[4] = byte[4] & 63;
  pool[5] = byte[5] & 63;
  pool[6] = byte[6] & 63;
  pool[7] = byte[7] & 63;

  pool[8] = ((byte[0] & 192) >> 6) | ((byte[1] & 192) >> 4) |
    ((byte[2] & 192) >> 2);
  pool[9] = ((byte[3] & 192) >> 6) | ((byte[4] & 192) >> 4) |
    ((byte[5] & 192) >> 2);
  pool[10] = ((byte[6] & 192) >> 6) | ((byte[7] & 192) >> 4) | (cs << 4);

  for(int i=0; i<11; ++i)
    buffer[i] = pool[i] + encoding_basis;
}

double
decode_double(const char*& buffer)
{
  int pool[11];
  double x;
  unsigned char* byte = (unsigned char*)&x;

  for(int i=0; i<11; ++i) {
    pool[i] = (int)buffer[i] - encoding_basis;
    if (pool[i] < 0 || pool[i] > 63) 
      throw Exception("decode_double(): illegal character");
  }

  byte[0] = pool[0] | (pool[8] << 6);
  byte[1] = pool[1] | ((pool[8] << 4) & 192);
  byte[2] = pool[2] | ((pool[8] << 2) & 192);
  byte[3] = pool[3] | (pool[9] << 6);
  byte[4] = pool[4] | ((pool[9] << 4) & 192);
  byte[5] = pool[5] | ((pool[9] << 2) & 192);
  byte[6] = pool[6] | (pool[10] << 6);
  byte[7] = pool[7] | ((pool[10] << 4) & 192);
  
  int embedded_cs = pool[10] >> 4;

  // Calculate a gratuitous checksum (copied from above)
  unsigned char cs = byte[0] ^ byte[1] ^ byte[2] ^ byte[3] ^
    byte[4] ^ byte[5] ^ byte[6] ^ byte[7];
  int bit_1 = (cs >> 2) & 7;
  int bit_2 = (cs >> 5) & 7;
  cs = (cs & 3) ^ ((cs >> bit_1) & 1) ^ (((cs >> bit_2) << 1) & 2);

  if (cs != embedded_cs) 
    throw Exception("decode_double(): checksum failed");
  
  if (!know_endianness)
    determine_endianness();

  if (little_endian) {
    // Convert from a big-endian representation
    unsigned char t;
   t = byte[0]; byte[0] = byte[7]; byte[7] = t;
   t = byte[1]; byte[1] = byte[6]; byte[6] = t;
   t = byte[2]; byte[2] = byte[5]; byte[5] = t;
   t = byte[3]; byte[3] = byte[4]; byte[4] = t;
  }

  buffer += 11;
  return x;
}

string
encode_double(double x)
{
  char buffer[12];
  buffer[11] = '\0';
  encode_double(x, buffer);
  return string(buffer);
}

double
decode_double(const string& s)
{
  const char* p = s.c_str();
  return decode_double(p);
}


// $Id: zdouble.cpp,v 1.4 1999/07/07 05:05:24 trow Exp $
