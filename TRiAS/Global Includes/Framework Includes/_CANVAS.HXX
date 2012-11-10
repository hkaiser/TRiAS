//  Copyright (c) 1992 Trischford Limited 
//  ( A wholly owned subsidary of Computer Associates International, Inc)
//  All Rights Reserved
//
//	Version 3.1			Nov 1992

class SimpleCanvas {
protected:
	HANDLE hDC;

public:

	SimpleCanvas( HANDLE dc) 	{ hDC = dc; }
	~SimpleCanvas()				{ hDC = 0; }

	ChangeSize( Dimension);

	Dimension GetSize(); 
}


