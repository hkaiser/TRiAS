

#ifndef _regexpr_h_ /* Sun Sep 08 09:46:58 1996 */
#define _regexpr_h_


/*
 *
 *          Copyright (C) 1996, M. A. Sridhar
 *  
 *
 *     This software is Copyright M. A. Sridhar, 1996. You are free
 *     to copy, modify or distribute this software  as you see fit,
 *     and to use  it  for  any  purpose, provided   this copyright
 *     notice and the following   disclaimer are included  with all
 *     copies.
 *
 *                        DISCLAIMER
 *
 *     The author makes no warranties, either expressed or implied,
 *     with respect  to  this  software, its  quality, performance,
 *     merchantability, or fitness for any particular purpose. This
 *     software is distributed  AS IS.  The  user of this  software
 *     assumes all risks  as to its quality  and performance. In no
 *     event shall the author be liable for any direct, indirect or
 *     consequential damages, even if the  author has been  advised
 *     as to the possibility of such damages.
 *
 */

// RegExpr represents a regular expression in the Unix egrep style. It offers
// the ability to construct a regular expression and to determine, given a
// string of characters the range of characters (if any) in the string that
// match the regular expression.
// 
// The implementation is a straightforward modification of copyrighted
// public-domain code by Henry Spencer of the University of Toronto.
//
// REGULAR EXPRESSION SYNTAX:
//
// The following is a direct excerpt from Henry Spencer's documentation:
//
// A regular expression is zero or more \fIbranches\fR, separated by `|'.
// It matches anything that matches one of the branches.
// 
// A branch is zero or more {\it pieces}, concatenated.
// It matches a match for the first, followed by a match for the second, etc.
// 
// A piece is an {\it atom\/} possibly followed by `*', `+', or `?'.
// An atom followed by `*' matches a sequence of 0 or more matches of the atom.
// An atom followed by `+' matches a sequence of 1 or more matches of the atom.
// An atom followed by `?' matches a match of the atom, or the null string.
// 
// An atom is a regular expression in parentheses (matching a match for the
// regular expression), a {\it range\/} (see below), `.'
// (matching any single character), `^' (matching the null string at the
// beginning of the input string), `$' (matching the null string at the
// end of the input string), a `\e' followed by a single character (matching
// that character), or a single character with no other significance
// (matching that character).
// 
// A {\it range\/} is a sequence of characters enclosed in `[]'.
// It normally matches any single character from the sequence.
// If the sequence begins with `^',
// it matches any single character {\it not\/} from the rest of the sequence.
// If two characters in the sequence are separated by `-', this is shorthand
// for the full list of ASCII characters between them
// (e.g. `[0-9]' matches any decimal digit).
// To include a literal `]' in the sequence, make it the first character
// (following a possible `^').
// To include a literal `-', make it the first or last character.


#include "base/string.h"

struct         CL_RegExpStruct;

class YACL_BASE CL_RegExpr {

public:
    CL_RegExpr (const char* regExp);
    // Build a regular expression from the given string. This ``compiles''
    // the regular expression into an automaton representation.

    CL_RegExpr (const CL_RegExpr& r);
    // Copy constructor.
    
    ~CL_RegExpr ();
    // Destructor.

    CL_RegExpr& operator= (const char* regExp);
    // Assignment. This method destroys the currently stored compiled
    // automaton, and recompiles it from {\tt regExp}.

    CL_RegExpr& operator= (const CL_RegExpr& regExp);
    // Assignment.

    long IndexIn (const char* string, long beginFrom = 0);
    // Return the index of the first occurrence of this regular expression
    // in {\tt string}. The search begins at position {\tt beginFrom}. If
    // there is no match, this method returns -1.

    long Match (const char* string, long& length, long beginFrom = 0);
    // Return the index of the first occurrence of this regular expression
    // in {\tt string}. The search begins at position {\tt beginFrom}. The
    // length of the matched string is returned in {\tt length}. If there
    // is no match, this method returns -1.

    enum { MAX_PAIRS = 10 };
    struct IntPair {
        long position;
        long length;
    };
    
    long Match (const char* string, IntPair segs[MAX_PAIRS],
                long beginFrom = 0);
    // Match this regular expression against {\tt string}. For each pair of
    // matched parentheses in this regular expression, return the position
    // and length of the corresponding match in segs. The position-length
    // pairs are ordered according to the order of occurrence of the left
    // parentheses; i.e., if we pretend that the left parentheses in the
    // regular expression are numbered 1, 2, ..., then segs[i] will contain
    // the position and length of the substring matched by the parenthesis
    // pair whose left parenthesis is numbered i.. Also: segs[0] contains
    // the position and length of the match of the whole regular expression.
    // For example, if this regular expression were {\tt ab(aba(.*)c)d}, the
    // call
    //
    //       Match ("annababaxxcd", segs, 0)
    //
    // would yield the following:
    //
    //       segs[0] = {3, 9}
    //       segs[0] = {5, 6}
    //       segs[0] = {8, 2}
    //
    // The better way to design this signature would have been to use a
    // CL_Sequence of pairs. But that would entail another template
    // instantiation.
    
    
    CL_String LastError () const {return _lastError;};
    // Return the most recent error that occurred in regular expression
    // processing. If this method returns the empty string, then there is
    // no error.

protected:

    CL_RegExpStruct* _regcomp (char* exp);
    int              _regexec (CL_RegExpStruct* prog, char* string);
    void             _regsub (CL_RegExpStruct *prog, char *source, char *dest);

    void  regerror (char*);
    char* reg (int paren, int* flagp);
    char* regbranch (int* flagp);
    char* regpiece (int* flagp);
    char* regatom (int* flagp);
    char* regnode (char op);
    void regc (char b);
    void reginsert (char op, char* opnd);
    void regtail (char *p, char *val);
    void regoptail (char *p, char *val);

    int regexec (register CL_RegExpStruct *prog,
                  register char *string);
    int regtry (CL_RegExpStruct *prog, char *string);
    
    int regmatch (char *prog);
    int regrepeat (char *p);
    char*  regnext (register char *p);
    
    CL_RegExpStruct*  _regExp;
    CL_String         _regExpString;
    CL_String         _lastError;
    

    char* regparse;		/* Input-scan pointer. */
    int   regnpar;		/* () count. */
    char  regdummy;
    char* regcode;		/* Code-emit pointer; &regdummy = don't. */
    long  regsize;		/* Code size. */

    char *reginput;		/* String-input pointer. */
    char *regbol;		/* Beginning of input, for ^ check. */
    char **regstartp;	        /* Pointer to startp array. */
    char **regendp;		/* Ditto for endp. */
    
};


#endif /* _regexpr_h_ */


