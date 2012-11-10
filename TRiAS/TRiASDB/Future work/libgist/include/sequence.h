// sequence.h					-*- c++ -*-
// Copyright (c) 1997, 1998, Regents of the University of California
// $Id: sequence.h,v 1.1 1999/09/27 01:08:53 marcel Exp $

#ifndef SEQUENCE_H
#define SEQUENCE_H

#ifdef __GNUG__
#pragma interface "sequence.h"
#endif


///////////////////////////////////////////////////////////////////////////////
// ScoringMatrix
///////////////////////////////////////////////////////////////////////////////


class ScoringMatrix {
public:

    typedef int Matrix[20][20];
    ScoringMatrix(Matrix m); // copy

    static void init(); // call to initialize 'index'
    int score(char a, char b) const;

    Matrix matrix;

protected:
    static int _index[256]; // map from char to index into 'matrix'
    static bool _initialized;

};

extern ScoringMatrix blosum45, blosum62, blosum80;


///////////////////////////////////////////////////////////////////////////////
// Sequence
///////////////////////////////////////////////////////////////////////////////

class Sequence {
public:

    Sequence(const char* s); // don't copy

    void localAlign(
        const Sequence& s,
	const ScoringMatrix& m,
	int gapPenalty,
	double& score,
	double& prob);

protected:

    const char* seq;
};

#endif // SEQUENCE_H
