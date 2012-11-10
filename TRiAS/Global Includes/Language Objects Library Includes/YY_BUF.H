
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1993-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_buf.h
//  
//  FILE DESCRIPTION:     header file with buffer class declarations
//  
//  CLASS HIERARCHY:
//
//    +------------------+                      +-----------------+
//    |   buffer class   |  <----------------   |   input class   |    
//    +------------------+   is referenced by   +-----------------+
//             | derives
//    +------------------+
//    |   lexer class    |
//    +------------------+
//
//  The buffer class is closely associated with both the lexer and
//  input object.  
//
//  The lexer class is derived from the buffer class.  All the data members
//  and member functions of the buffer class are present in the lexer class.
//  The buffer in the lexer is the input source currently being lexed.
//  The lexer buffer is the input source associated with the input object 
//  on the top of the input object stack.  If input sources are changed,
//  for example, processing a nested include file for input, the pointers
//  of the buffer in that input object are copied into the lexer buffer. 
//  By always having the current buffer in the lexer object itself, we avoid
//  one level of dereferencing for optimal performance.
//
//  If there is more than one input object on the stack, they will each 
//  contain a reference to a buffer object which encapsulates the lexer
//  state at the time lexing was switched to the nested input object.
//  As mentioned above, the top input object has its buffer in the lexer
//  object itself.  The other input objects, if any, each contain a reference
//  to their own buffer.  When the top input is exhausted, the buffer in 
//  the previous input object is copied to the lexer object and lexing
//  continues.
//
//  Users do not explicitly create buffer objects.  They are used internally
//  in the Language Objects Library by the lexer and input classes.
//
//  NOTE:  it is generally not advisable to modify the buffer class unless
//         you have a very thorough knowledge of the inner workings of 
//         Yacc++ and the Language Objects Library.
//
//  MODIFICATION HISTORY:
//  
//    04/08/98   bz       Moved constants to yy_const.h to avoid problems 
//                        with constants not defined early enough.
//    01/28/98   bz       Changed variable name yy_read to yy_read_ptr.  This
//                        avoids a naming conflict with the yy_stdio.h yy_read 
//                        redefinition needed for prefixing file functions 
//                        for PC compilers.
//    03/25/96   bz/cc    changed yy_buf_extend to try harder to extend
//                        the buffer and to not fail unless the buffer
//                        was full and it could not extend it.
//    04/05/94   bz/cc    changed to use yy_memmove to solve memcpy/memmove
//                        platform incompatibilities.
//    01/12/94   bz       changed all buffer sizes to size_t to maximize
//                        token size when using 16 bit compilers.
//    12/10/93   bz/cc    moved yy_lex_char, yy_lex_len, and yy_lex_token
//                        from the lexer class as the fields they access
//                        were previously moved to the buffer class.
//    05/03/93   bz       initial coding.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_buf_h_
#define yy_buf_h_

#include "yy_ansi.h"
#include "yy_asrt.h"
#include "yy_bool.h"
#include "yy_const.h"
#include "yy_err.h"
#include "yy_stdio.h"
#include "yy_strng.h"


//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_buf_ptr      is a typedef which defines a pointer to a buffer object.
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_buf_obj        *yy_buf_ptr;


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_buf_obj
//
//  The yy_buf_obj is the class for the buffer object.  It represents
//  the input being lexed and is contained in lexer objects and referenced
//  from input objects.
//
//  CONFIGURATION CONSTANTS:
//
//  yy_buf_lhead_state_not_read_
//                      is the value of yy_lhead_state when no lookahead 
//                      character has been read and no lexer non-terminal
//                      has been reduced without being shifted.
//
//  yy_buf_lhead_state_read_
//                      is the value of yy_lhead_state when a lookahead
//                      character has been read and no lexer non-terminal
//                      has been reduced without being shifted.
//
//  yy_buf_lhead_state_nterm_only_
//                      is the value of yy_lhead_state when no lookahead
//                      character has been read and a lexer non-terminal
//                      has been reduced without being shifted.
//
//  yy_buf_lhead_state_read_nterm_
//                      is the value of yy_lhead_state when a lookahead
//                      character has been read and a lexer non-terminal
//                      has been reduced without being shifted.
//
//  yy_buf_grow_by_     controls the size of chunks which are added to the 
//                      input buffer when making it larger.
//
//  yy_buf_dflt_size_   is a manifest constant which controls the
//                      initial size of the input buffer.
//
//                 ===> yy_input_dflt_obj uses unbuffered input.  
//                      For unbuffered input (read calls) the size of the 
//                      input buffer determines the default block size for
//                      reading from input.  A bigger block size will result
//                      in fewer calls to read blocks from the input.
//                      However, each input object which is stacked requires 
//                      a new buffer of this fixed minimal block size.  Also
//                      note that each time a token larger than half the 
//                      current block size is read such that it crosses a 
//                      block boundary, the lexer will automatically double
//                      the block size for that input object.
//
//                 ===> yy_input_getc_obj uses buffered input.  
//                      For buffered input (getc calls) the size of the 
//                      input buffer determines the size of the largest 
//                      token.  Again, if the buffer is too small, the 
//                      lexer will double the size of the buffer for that 
//                      input until the token fits.
//
//  PUBLIC FUNCTIONS:
//
//  yy_buf_obj()        default constructor for a buffer object.
//
//  yy_buf_obj(const yy_buf_obj &yy_copy_from_buf)
//                      copy constructor for a buffer object.
//
//  operator=(const yy_buf_obj &yy_copy_from_buf)
//                      assignment operator for a buffer object.
//
//  ~yy_buf_obj()       destructor for a buffer object.
//
//  yy_buf_dmp()        dumps the contents of a buffer object.
//
//  yy_buf_end([char *])
//                      gets (or sets with an argument) the pointer to the
//                      end of the buffer.
//
//  yy_buf_eof_read([yy_boolean])
//                      gets (or sets with an argument) whether the 
//                      end-of-file has been read.
//
//  yy_buf_extend([int])
//                      extends the buffer by default or amount specified
//                      by argument.  (buffer is made larger).
//
//  yy_buf_init()       initializes the buffer fields once the buffer start
//                      has been set.
//
//  yy_buf_ins()        inserts a set of characters into the buffer.
//
//  yy_buf_lhead_char([int])
//                      gets (or sets with an argument) the lookahead 
//                      character.  No change to the state is made.
//
//  yy_buf_lhead_to_read()
//                      returns true if there are characters read into the 
//                      buffer, but not yet lexed.
//
//  yy_buf_lhead_unread()
//                      returns true if the buffer needs to get a new 
//                      lookahead character.
//
//  yy_buf_lineno()     returns the line number of the current position in
//                      the buffer.
//
//  yy_buf_mark_lhead_read()
//                      marks the lookahead character as having been consumed.
//
//  yy_buf_mark_nterm_lhead()
//                      marks the lookahead character as coming from a
//                      lexer non-terminal.
//
//  yy_buf_mark_nterm_read()
//                      marks the lookahead character as having consumed a
//                      lexer non-terminal.
//
//  yy_buf_read([char *])
//                      gets (or sets with an argument) the pointer to 
//                      the portion of the buffer which is read, but
//                      not yet lexed.                      
//
//  yy_buf_read_eof_lhead() 
//                      reads the EOF lookahead character and marks it as
//                      having been read.
//
//  yy_buf_read_lhead() reads the next lookahead character and marks it as
//                      having been read.
//
//  yy_buf_reset()      repositions all of the pointers into a buffer after 
//                      an extension or wrap.
//
//  yy_buf_set_eof()    marks buffer object as having read the end-of-file.
//
//  yy_buf_size([int])  gets (or sets with an argument) the size of the
//                      buffer.
//
//  yy_buf_start([char *])
//                      gets (or sets with an argument) the pointer to the
//                      start of the buffer.
//
//  yy_buf_start_tkn    marks the start of a new token in the buffer.
//
//  yy_buf_tkn_end([char *])
//                      gets (or sets with an argument) the pointer to the
//                      end of the current token in the buffer.
//
//  yy_buf_tkn_start([char *])
//                      gets (or sets with an argument) the pointer to the
//                      start of the current token in the buffer.
//
//  yy_buf_unread_len() returns the number of characters allocated in the
//                      buffer but not read into.
//
//  yy_buf_wrap()       repositions the characters in the buffer and the 
//                      pointers such that the first character of the 
//                      current token is the first character in the buffer.
//
//  INTERNAL STATE:  
//
//  yy_start         is the beginning of buffer currently allocated for 
//                   this input.
//
//  yy_read_ptr      is the start of buffer which is read but unlexed for 
//                   this input.
//
//  yy_end           is the end of buffer which is read for this input.
//
//  yy_tkn_start     is the beginning of the current token in a Yacc++ lexer.
//
//  yy_tkn_end       is the end of the current token in a Yacc++ lexer.
//
//  yy_grow_by       is the size of chunks this buffer is to grow by.
//
//  yy_lhead_state   indicates whether the lookahead character has been read
//                   or not.
//
//  yy_lhead_char    is the lexer input character or the type of the last 
//                   lexical non-terminal.  The state and the input character 
//                   determine what actions the lexer will take.
//
//  yy_lineno        line number of the current position in the buffer.  
//                   Note that action code in the lexer or parser is 
//                   responsible for keeping this field updated!
//                      
//  yy_size          is the size of buffer currently allocated for this input.
//                   See yy_buf_dflt_size_ for the default size.
//
//  yy_eof_read      is true if the last character in the buffer is the
//                   last character in this input.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_buf_obj : public yy_const {

 public:

    yy_buf_obj();

    yy_buf_obj(const yy_buf_obj &yy_copy_from_buf);
    
    yy_buf_obj &operator=(const yy_buf_obj &yy_copy_from_buf);
    
    virtual ~yy_buf_obj();

    void yy_buf_dmp(
        yy_err_ptr   yy_this_err_obj, 
        const char   *yy_dmp_title);

    inline char *yy_buf_end();

    inline char *yy_buf_end(char *yy_new_end);

    inline yy_boolean yy_buf_eof_read();

    inline yy_boolean yy_buf_eof_read(yy_boolean yy_new_eof_read);  

    inline void yy_buf_extend();

    inline void yy_buf_extend(
        size_t  yy_extend_buf_by);

    inline void yy_buf_ins(
        char    *yy_new_array_to_insert,
        size_t  yy_new_array_length);

    inline void yy_buf_init();
    
    inline int yy_buf_lhead_char();

    inline int yy_buf_lhead_char(int i);

    inline yy_boolean yy_buf_lhead_to_read();

    inline yy_boolean yy_buf_lhead_unread();

    inline int &yy_buf_lineno();

    inline void yy_buf_mark_lhead_read();

    inline void yy_buf_mark_nterm_lhead();

    inline void yy_buf_mark_nterm_read();
        
    inline char *yy_buf_read();

    inline char *yy_buf_read(char *yy_new_read);  

    inline void yy_buf_read_eof_lhead();

    inline void yy_buf_read_lhead();

    inline void yy_buf_reset();

    inline void yy_buf_set_eof();

    inline size_t yy_buf_size();
        
    inline size_t yy_buf_size(size_t yy_new_size);

    inline char *yy_buf_start();

    inline char *yy_buf_start(char *yy_new_start);

    inline void yy_buf_start_tkn();

    inline char *yy_buf_tkn_end();
    
    inline char *yy_buf_tkn_end(char *yy_new_tkn_end);  

    inline char *yy_buf_tkn_start();
    
    inline char *yy_buf_tkn_start(char *yy_new_tkn_start);  

    inline long yy_buf_unread_len();

    inline void yy_buf_wrap();        

    inline char &yy_lex_char(size_t i);

    inline size_t yy_lex_len();

    inline char *&yy_lex_token();

 protected:
 
    char                *yy_start;
    char                *yy_read_ptr;  
    char                *yy_end;  
    char                *yy_tkn_start;
    char                *yy_tkn_end;
    size_t              yy_size;  
    size_t              yy_grow_by;  
    int                 yy_lhead_state;
    int                 yy_lhead_char;
    int                 yy_lineno;
    yy_boolean          yy_eof_read;

    };  // yy_buf_obj


//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the INLINE functions for the buffer object, defined above.
//
//////////////////////////////////////////////////////////////////////////////

inline char *yy_buf_obj::yy_buf_end()
    { return(yy_end); }

inline char *yy_buf_obj::yy_buf_end(char *yy_new_end)
    { return(yy_end = yy_new_end); }

inline yy_boolean yy_buf_obj::yy_buf_eof_read() 
    { return(yy_eof_read); }

inline yy_boolean yy_buf_obj::yy_buf_eof_read(
    yy_boolean yy_new_eof_read
    ) 
    { return(yy_eof_read = yy_new_eof_read); }

inline void yy_buf_obj::yy_buf_extend() 
    { 
    yy_buf_extend(yy_size);
    }

inline void yy_buf_obj::yy_buf_extend(size_t yy_extend_buf_by) 
    { 
    char *yy_temp_buf;
    size_t yy_new_size;
    
//  determine the new buffer size.  First, try the larger of the size 
//  passed in and the grow_by size, and then the smaller of the to
//  quantities.  Note, when using the size passed in, round it up to
//  a multiple of the grow_by size.
//
//  If neither works, try adding just one more character.  And, finally,
//  see if any space is left in the current buffer without growing it.  
//  If all of the above fails, the buffer is full and cannot be grown, 
//  the application must be terminated.
//
//  Note, in the default case, the size passed in is the current buffer
//  size.  (See the no argument version of the function above.)  This
//  means that each call attempts to double the buffer size.

    if (yy_extend_buf_by < yy_grow_by) {
	if (yy_size < yy_size + yy_grow_by) {
	    yy_new_size = yy_size + yy_grow_by;
	    }
	else if (yy_size < yy_size + yy_extend_buf_by) {
	    yy_new_size = yy_size + yy_extend_buf_by;
	    }
	else if (yy_size < yy_size + 1) {
	    yy_new_size = yy_size + 1;
	    }
	else if (yy_start != yy_tkn_start) {
	    yy_buf_wrap();  // some space is left in the old buffer, use it
	    return;
	    }
	else { 
	    yy_err_report(406);
	    yy_assert_fail("unable to extend buffer", __FILE__, __LINE__);
	    return;
	    }
        }
    else {
	if (yy_extend_buf_by % yy_grow_by)  {
	    yy_extend_buf_by += yy_grow_by - 1 - (yy_extend_buf_by - 1) %
		yy_grow_by;
	    }
	if (yy_size < yy_size + yy_extend_buf_by) {
	    yy_new_size = yy_size + yy_extend_buf_by;
	    }
	else if (yy_size < yy_size + yy_grow_by) {
	    yy_new_size = yy_size + yy_grow_by;
	    }
	else if (yy_size < yy_size + 1) {
	    yy_new_size = yy_size + 1;
	    }
	else if (yy_start != yy_tkn_start) {
	    yy_buf_wrap();  // some space is left in the old buffer, use it
	    return;
	    }
	else { 
	    yy_err_report(406);
	    yy_assert_fail("unable to extend buffer", __FILE__, __LINE__);
	    return;
	    }
        }

//  attempt to allocate a larger buffer, starting with the requested size
//  and decreasing the size of the request until the request would not
//  result in a larger buffer.  In that case, try to see if there is any
//  space left in the current buffer without growing it, and if not
//  terminating the application.

    assert(0 < yy_new_size);
    yy_temp_buf = yy_start;

    yy_start = new char[yy_new_size+1];
    if (yy_start == NULL) {  // new() failure
	for (;;) {
	    --yy_new_size;
	    if (yy_size == yy_new_size) {
		yy_start = yy_temp_buf;
		if (yy_start != yy_tkn_start) {
		    yy_buf_wrap();  // some space is left in the old buffer, use it
		    return;
		    }
		else { 
		    yy_err_report(406);
		    yy_assert_fail("space unavailable from new", __FILE__, __LINE__);
		    return;
		    }
		}
	    yy_start = new char[yy_new_size+1];
	    if (yy_start != NULL) break; // new() succeeded;
	    }
        }

//  a larger buffer was allocated, move the text to the new buffer

    yy_size = yy_new_size;
    yy_read_ptr = (size_t)(yy_read_ptr - yy_temp_buf) + yy_start;
    yy_buf_wrap();  // copy all the characters to the bigger buffer
    delete [] yy_temp_buf;
    }

inline void yy_buf_obj::yy_buf_ins(
    char           *yy_buf_array_to_insert,
    size_t         yy_buf_array_length) 
    {
    if (yy_buf_array_to_insert != yy_read_ptr) {
        yy_buf_wrap();
        yy_buf_reset();
        if ((size_t)(yy_size-yy_buf_array_length) < 
            (size_t)(yy_end-yy_start)) {
            yy_buf_extend(yy_buf_array_length);
            yy_buf_reset();
            }
        // yy_memmove becomes memcpy on systems like the Sparc which ensure
        // overlapping memory moves are ok.  Otherwise uses memmove.
        yy_memmove(yy_end, yy_buf_array_to_insert, yy_buf_array_length);
        yy_end += yy_buf_array_length;
        }
    }

inline void yy_buf_obj::yy_buf_init()
    {

//  initialize the buffer pointers based on the start pointer

    yy_read_ptr = yy_start;
    yy_end = yy_start;
    yy_tkn_start = yy_start;
    yy_tkn_end = yy_start;

//  until we attempt to read from the buffer, we cannot have seen eof
//  and we don't have a lookahead character waiting

    yy_eof_read = yy_false;
    yy_lhead_state = yy_buf_lhead_state_not_read_;

    }

inline int yy_buf_obj::yy_buf_lhead_char()  
    { return(yy_lhead_char); }

inline int yy_buf_obj::yy_buf_lhead_char(int yy_new_lhead_char) 
    {
    return(yy_lhead_char = yy_new_lhead_char);
    }

inline yy_boolean yy_buf_obj::yy_buf_lhead_to_read() 
    { 
    assert(yy_tkn_start <= yy_tkn_end && yy_tkn_end <= yy_end + 1 || 
        yy_tkn_end == NULL || yy_end == NULL);
    return((yy_end != NULL) && (yy_tkn_end < yy_end)); 
    }

inline yy_boolean yy_buf_obj::yy_buf_lhead_unread() 
    { return(yy_lhead_state == yy_buf_lhead_state_not_read_); }

inline int &yy_buf_obj::yy_buf_lineno()
    { return(yy_lineno); }
        
inline void yy_buf_obj::yy_buf_mark_lhead_read() 
    {
    yy_lhead_state = yy_buf_lhead_state_not_read_;
    }

inline void yy_buf_obj::yy_buf_mark_nterm_lhead() 
    {
    yy_lhead_state |= yy_buf_lhead_state_nterm_only_;
    }

inline void yy_buf_obj::yy_buf_mark_nterm_read() 
    {
    yy_lhead_state &= ~yy_buf_lhead_state_nterm_only_;
    }

inline char *yy_buf_obj::yy_buf_read()    
    { 
    assert(yy_tkn_start <= yy_read_ptr && yy_read_ptr <= yy_end + 1 || 
        yy_read_ptr == NULL);
    return(yy_read_ptr); 
    }
    
inline char *yy_buf_obj::yy_buf_read(
    char *yy_new_read)    
    { 
    return(yy_read_ptr = yy_new_read); 
    }   

inline void yy_buf_obj::yy_buf_read_eof_lhead() 
    {
    ++yy_tkn_end; 
    yy_lhead_char = (int)EOF;
    yy_lhead_state = yy_buf_lhead_state_read_; 
    }

inline void yy_buf_obj::yy_buf_read_lhead() 
    {
    assert(yy_tkn_start <= yy_tkn_end && yy_tkn_end <= yy_end);
    yy_lhead_char = (int) ((unsigned char) *yy_tkn_end);
    ++yy_tkn_end; 
    yy_lhead_state = yy_buf_lhead_state_read_; 
    }

inline void yy_buf_obj::yy_buf_reset() 
    {
    yy_tkn_end = (size_t)(yy_tkn_end - yy_tkn_start) + yy_start;
    yy_end = (size_t)(yy_end - yy_tkn_start) + yy_start;
    yy_tkn_start = yy_start; 
    }

inline void yy_buf_obj::yy_buf_set_eof() 
    {
    yy_tkn_start = yy_tkn_end = yy_end = yy_read_ptr = yy_start;
    yy_eof_read = yy_true;
    }

inline size_t yy_buf_obj::yy_buf_size()
    { return(yy_size); }

inline size_t yy_buf_obj::yy_buf_size(size_t yy_new_size)
    { return(yy_size = yy_new_size); }

inline char *yy_buf_obj::yy_buf_start()
    { return(yy_start); }

inline char *yy_buf_obj::yy_buf_start(char *yy_new_start)
    { 

//  prevent the real buffer from being deleted when 
//  we are moving the buffer to a different object

        if (yy_new_start != NULL) {
            delete [] yy_start;
            }

        return(yy_start = yy_new_start); 
    }

inline void yy_buf_obj::yy_buf_start_tkn() 
    {
    assert(yy_tkn_start <= yy_tkn_end && yy_tkn_end <= yy_end + 1 || 
        yy_tkn_end == NULL);
    if ((yy_lhead_state & yy_buf_lhead_state_read_) && 
        (yy_tkn_end != yy_start)) {
        yy_tkn_start = yy_tkn_end - 1;
        }
    else {
        yy_tkn_start = yy_tkn_end;
        }
    }

inline char *yy_buf_obj::yy_buf_tkn_end()
    { return(yy_tkn_end); }

inline char *yy_buf_obj::yy_buf_tkn_end(char *yy_new_tkn_end)
    { return(yy_tkn_end = yy_new_tkn_end); }

inline char *yy_buf_obj::yy_buf_tkn_start()
    { return(yy_tkn_start); }

inline char *yy_buf_obj::yy_buf_tkn_start(char *yy_new_tkn_start)
    { return(yy_tkn_start = yy_new_tkn_start); }

inline long yy_buf_obj::yy_buf_unread_len()    
    { 
    assert(yy_start <= yy_read_ptr && yy_read_ptr <= yy_start + yy_size + 1 || 
        yy_read_ptr == NULL);
    assert(yy_start <= yy_end && yy_end <= 
           yy_start + yy_size + 1 || yy_end == NULL);
    assert(yy_read_ptr <= yy_end || yy_read_ptr == NULL || 
           yy_end == NULL);
    return((long)(yy_end - yy_read_ptr)); 
    }

inline void yy_buf_obj::yy_buf_wrap() 
    {
    // yy_memmove becomes memcpy on systems like the Sparc which ensure
    // overlapping memory moves are ok.  Otherwise uses memmove.
    yy_memmove(yy_start, yy_tkn_start, (size_t)(yy_end - yy_tkn_start));
    }

inline char &yy_buf_obj::yy_lex_char(size_t i)
    { return(yy_tkn_start[(i)]); }

inline size_t yy_buf_obj::yy_lex_len()
    { 
    return(yy_lhead_state == yy_buf_lhead_state_not_read_ ?
           (size_t)(yy_tkn_end - yy_tkn_start) :
           (size_t)(yy_tkn_end - yy_tkn_start - 1)); 
    }

inline char *&yy_buf_obj::yy_lex_token()
    { return(yy_tkn_start); }


//////////////////////////////////////////////////////////////////////////////
//
//  COMPATIBILITY MACROS:
//
//  For backward compatibility, the following macros preserve the old names.
//
//  yy_cur_lineno       ==> calls yy_buf_lineno
//
//////////////////////////////////////////////////////////////////////////////

#define yy_cur_lineno   yy_buf_lineno


#endif /* yy_buf_h_ */
