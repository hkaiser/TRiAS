// PaintScale.java
// Copyright (c) 1998, Regents of the University of California
// $Id: PaintScale.java,v 1.1 1999/06/21 00:34:25 marcel Exp $

import java.awt.*;

public class PaintScale {

private static float truncate(float d, int digits)
{
    float p = (float) Math.pow(10.0, (double) digits);
    return ((float) ((int) (d * p))/p);
}

public static int vertical(Graphics g, int xmin, int ymin,
    int ymax, float min, float max, int numTicks, int rightalign) {

    // its actually faster if you give us the fontmetrics ... but if it
    // isn't possible ... or too hard to change for now ... call this method.

    return vertical(g, g.getFontMetrics(), xmin, ymin, ymax, min, max,
	numTicks, rightalign);
	
}

public static int vertical(Graphics g, FontMetrics fm, int xmin, int ymin, 
    int ymax, float min, float max, int numTicks, int rightalign) {

    int h = ymax - ymin;
    
    float range = max - min;

    int i;

    float d  = (float) h / (float) numTicks;

    float dv = (float) range / (float) numTicks;

    float value;

    // float mintrunc = truncate(min,3);

    int pos;

    int strh;

    int strw = 0;
    int maxstrw = 0;
    
    strh = fm.getHeight() - fm.getDescent() - 1;

    g.setColor(Color.black);

    // Find maximum string width ...
    for (i = 0; i <= numTicks; i++) {

	value = truncate(( ((float) i) * dv ) + min , 3);
	
	strw = fm.stringWidth(Float.toString(value));
	if (strw > maxstrw)
	    maxstrw = strw;

    }

    String valstr;

    for (i = 0; i <= numTicks; i++) {

	pos = h - (int) Math.floor(i*d); // make it go backwarks ...
	value = truncate(( ((float) i) * dv ) + min , 3 );

	valstr = Float.toString(value);
	strw = fm.stringWidth(valstr);

	if (rightalign == 0) {

	    g.drawString(valstr, xmin + 6, ymin + pos + strh / 2);
	    g.drawLine( xmin, ymin + pos, xmin + 4, ymin + pos);

	} else {
	    
	    // if (value > 100)
	    // 		System.out.println(valstr + " " + xmin + " " + strw + " " +
	    // 		    maxstrw + " " + (xmin - strw + maxstrw));
	    g.drawString(valstr, xmin + maxstrw - strw, ymin + pos + strh / 2);
	    g.drawLine( xmin + maxstrw + 2, ymin + pos, xmin + maxstrw + 6,
		ymin + pos );

	}

	// g.drawString(valstr, xmin + 6, ymin + pos + strh / 2);
	
	// g.drawLine( xmin, ymin + pos, xmin + 4, ymin + pos);
    }
    
//     pos = ymin; // make it go backwards ...
    
//     g.drawLine( xmin, pos, xmin + 4, pos);

//     max = (float) (Math.rint(i*dv*100) / 100.0) + min;
    
//     strw = fm.stringWidth(Float.toString(max));
//     if (strw > maxstrw)
// 	maxstrw = strw;
//     g.drawString(Float.toString(max),
// 	xmin + 6, pos + strh / 2);

    return maxstrw + 6;
}


// returns width excess to the right ...

public static int horizontal(Graphics g, int ymin, int xmin,
    int xmax, float min, float max, int numTicks) {

    // its actually faster if you give us the fontmetrics ... but if it
    // isn't possible ... or too hard to change for now ... call this method.

    return horizontal(g, g.getFontMetrics(), ymin, xmin, xmax, min, max,
	numTicks);
	
}

public static int horizontal(Graphics g, FontMetrics fm, int ymin, int xmin, 
    int xmax, float min, float max, int numTicks) {

    float value =  truncate(max, 3);

    // ((float) ((int)Math.rint(max*(float)1000)) / (float) 1000);
    int strw = fm.stringWidth(Float.toString(value));
    
    strw -= strw / 2;
    
    int w = xmax - strw - xmin;

    if ( w < 0 )
	return w;
    
    float range = max - min;

    // float mintrunc = (float)((int)Math.rint(min*(float)1000))/(float)1000;

    int i;

    float d  = (float) w / (float) numTicks;

    float dv = (float) range / (float) numTicks;

    int pos;

    int strh;
    
    strh = fm.getHeight() - fm.getDescent();

    g.setColor(Color.black);

    // Find maximum string width ... .. what for over here? ...
//     for (i = 0; i < numTicks; i++) {

// 	value = (float) (Math.rint(i*dv*1000) / 1000.0) + min;	
// 	strw = fm.stringWidth(Float.toString(value));
// 	if (strw > maxstrw)
// 	    maxstrw = strw;

//     }

    String valstr;

    for (i = 0; i <= numTicks; i++) {
	
	pos = (int) Math.floor(i*d); // goes forewords ... 
	// value = (float)((int) Math.rint((float)i*dv*(float)1000) /(float)1000) + 
	// mintrunc;

	value = truncate(( ((float) i) * dv ) + min, 3);

	valstr = Float.toString(value);
	strw = fm.stringWidth(valstr);
	
	g.drawLine(xmin + pos, ymin, xmin + pos, ymin + 4);
	g.drawString(valstr, xmin + pos - strw / 2, ymin + 4 + strh);

    }

    // return strw - (strw / 2);

    return w;
}

}
