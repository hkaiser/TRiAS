// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 28.06.2002 15:52:02 
//
// @doc
// @module MediaPlayer.cpp | Definition of the <c CMediaPlayer> class

#include "stdafx.h"
#include "VidCtrl.h"

#include <Com/ComBool.h>

#include "MediaPlayer.h"

//////////////////////////////////////////////////////////////////////////
// CMediaPlayer

HRESULT CMediaPlayer::Attach (HWND hWnd)
{
// Control dranhängen
	CAxWindow::Attach(hWnd);
	RETURN_FAILED_HRESULT(this->QueryControl(m_spPlayer.ppu()));

// Control Initialisieren
	RETURN_FAILED_HRESULT(m_spPlayer->put_SendMouseClickEvents(VARIANT_TRUE));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Properties
HRESULT CMediaPlayer::SendMouseClickEvents(bool fSendEvents)
{
	_ASSERTE(m_spPlayer.IsValid());
	return m_spPlayer->put_SendMouseClickEvents(CComBool(fSendEvents));
}

