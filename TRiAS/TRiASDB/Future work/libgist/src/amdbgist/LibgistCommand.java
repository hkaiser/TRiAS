// LibgistCommand.java
// Copyright (c) 1998, Regents of the University of California
// $Id: LibgistCommand.java,v 1.1 1999/06/21 00:33:05 marcel Exp $

import java.io.File;
import java.lang.StringBuffer;

/*
 * LibgistCommand.java - 
 * encapsulates single command taken from script
 */

class LibgistCommand 
{

// constants for cmdType
static final int INVALID = -1;
static final int INSERT = 0;
static final int REMOVE = INSERT + 1;
static final int FETCH = INSERT + 2;
static final int CREATE = INSERT + 3;
static final int OPEN = INSERT + 4;
static final int CLOSE = INSERT + 5;
static final int FLUSH = INSERT + 6;
static final int OPENANL = INSERT + 7;
static final int CLOSEANL = INSERT + 8;
static final int CREATEANL = INSERT + 9;
static final int WKLDSTATS = INSERT + 10;
static final int SPLITSTATS = INSERT + 11;
static final int PENALTYSTATS = INSERT + 12;
static final int SCRIPT = INSERT + 13;

int cmdType;
int fetchLimit;
StringBuffer qual; // query qualification (used by fetch and delete)
StringBuffer key; // used by insert
StringBuffer data; // used by insert
StringBuffer indexName; // used by create, createanl
StringBuffer extension; // used by create
float fillFactor; // used by create, createanl
StringBuffer loadFile; // used by create
StringBuffer scriptFile; // used by createanl
File analysisFile; // used by openanl, createanl
int numRandomRuns; // used by createanl

LibgistCommand()
{
    qual = new StringBuffer();
    key = new StringBuffer();
    data = new StringBuffer();
    indexName = new StringBuffer();
    extension = new StringBuffer();
    loadFile = new StringBuffer();
    scriptFile = new StringBuffer();
    analysisFile = null;
}

void
reset()
{
    cmdType = INVALID;
    fetchLimit = 0;
    qual.setLength(0);
    key.setLength(0);
    data.setLength(0);
    indexName.setLength(0);
    extension.setLength(0);
    fillFactor = 0.0f;
    loadFile.setLength(0);
    scriptFile.setLength(0);
    analysisFile = null;
}

}
