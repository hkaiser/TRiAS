// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/16/1998 12:49:39 PM
//
// @doc
// @module Lambda.h | Trickkiste für lokale Predikate

#if !defined(_LAMBDA_H__F45F28D6_7D2F_11D2_9EF6_006008447800__INCLUDED_)
#define _LAMBDA_H__F45F28D6_7D2F_11D2_9EF6_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define __XY__(X,Y) X##Y
#define __MakeNameXY__(FX,LINE) __XY__(FX,LINE)
#define __MakeName__(FX) __MakeNameXY__(FX,__LINE__)

#define Lambda(args,ret_type,body) \
class __MakeName__(__Lambda___) { \
public: ret_type operator() args { body; } }

#endif // !defined(_LAMBDA_H__F45F28D6_7D2F_11D2_9EF6_006008447800__INCLUDED_)
