// DumpBuffer.CPP

// Author: Dr. Carlo Pescio
// Eptacom Consulting
// Via Bernardo Forte 2-3
// 17100 Savona - ITALY
// Fax +39-19-854761
// email pescio@programmers.net


#include "StdAfx.h"

#include <stdio.h>
#include <stdarg.h>
#include "DumpBuffer.h"


DumpBuffer :: DumpBuffer()
{
	Clear();
}


void DumpBuffer :: Clear()
{
	current = buffer;
	static_current = static_buffer;
}

void DumpBuffer::Printf (const char* format, ...)
{
// protect against obvious buffer overflow
	if (current - buffer < BUFFER_SIZE) {
	va_list argPtr;
	
		va_start (argPtr, format);

	int count = vsprintf (current, format, argPtr);

		va_end (argPtr);
		current += count;
	}
}

void DumpBuffer::StaticPrintf (const char* format, ...)
{
// protect against obvious buffer overflow
	if (static_current - static_buffer < STATIC_BUFFER_SIZE) {
	va_list argPtr;
	
		va_start (argPtr, format);
	
	int count = vsprintf (static_current, format, argPtr);

		va_end (argPtr);
		static_current += count;
	}
}

void DumpBuffer :: SetWindowText( HWND hWnd ) const
{
	SendMessage (hWnd, WM_SETTEXT, 0, (LPARAM)buffer);
}

void DumpBuffer :: StaticSetWindowText( HWND hWnd ) const
{
	SendMessage (hWnd, WM_SETTEXT, 0, (LPARAM)static_buffer);
}

