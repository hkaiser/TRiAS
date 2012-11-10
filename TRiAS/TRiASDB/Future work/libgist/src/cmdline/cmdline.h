// cmdline.h
// Copyright (c) 1998, Regents of the University of California
// $Id: cmdline.h,v 1.4 1998/12/13 00:01:29 marcel Exp $

#ifndef CMDLINE_H
#define CMDLINE_H

extern void cmdCreate(const char* table, const char* extname);
extern void cmdLoad(const char* table, const char* extname, const char* filename,
    float fillFactor);
extern void cmdWriteLoadfile(const char* table, const char* filename);
extern void cmdOpen(const char* table);
extern void cmdClose(const char* table);
extern void cmdCheck(const char* table);
extern void cmdSelect(const char* table, const char* qstr, int k, int io);
extern void cmdInsert(const char* table, const char* kstr, const char* dstr);
extern void cmdDelete(const char* table, const char* qstr);
extern void cmdQuit();
extern void cmdDump(const char* table, shpid_t pgno);
extern void cmdSplit(const char* table, shpid_t pgno);
extern void cmdSetEcho(int state);
extern void cmdSetStruct(const char* table, int state);
extern void cmdCreateAnl(const char* analysis, const char* index, const char* scriptfile,
    int numRandomRuns, float targetUtil);
extern void cmdOpenAnl(const char* analysis);
extern void cmdCloseAnl(const char* analysis);
extern void cmdSplitStats(const char* analysis, const char* option);
extern void cmdPenaltyStats(const char* analysis, const char* loadfile, const char* option);
extern void cmdWkldStats(const char* analysis);
extern void cmdHelp();
extern void cmdPrompt();
extern void cmdAnlInfo(const char* anl);
extern void cmdPredInfo(const char* index, int subtreeRoot, int levels);

#endif // CMDLINE_H
