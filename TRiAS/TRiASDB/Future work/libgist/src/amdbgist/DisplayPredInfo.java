// DisplayPredInfo.java
// Copyright (c) 1998, Regents of the University of California
// $Id: DisplayPredInfo.java,v 1.1 1999/06/21 00:33:01 marcel Exp $

/* Structure containing predicate location and index into a color map */
/* indicating preferred color for display                             */

public class DisplayPredInfo {

int node;
int slot;
int level;
int color = 0;

public DisplayPredInfo() {}

public DisplayPredInfo(int node, int slot, int level, int color) {
    this.node = node;
    this.slot = slot;
    this.level = level;
    this.color = color;

}

public void setFields(int node, int slot, int level, int color) {

    this.node = node;
    this.slot = slot;
    this.level = level;
    this.color = color;

}

public void copyFields(DisplayPredInfo pred) {
    
    this.node = pred.node;
    this.slot = pred.slot;
    this.level = pred.level;
    this.color = pred.color;

}

}
