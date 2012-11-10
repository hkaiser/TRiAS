
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 1990-98, Compiler Resources, Inc.
//
//  FILENAME:             yy_cmd.h
//  
//  FILE DESCRIPTION:     insert file with declarations for 
//                        command line processing
//  
//  MODIFICATION HISTORY:
//  
//    02/27/98   bz       merged -I option that was in the DEC version.
//    12/11/93   bz/cc    changed names of yy_err_obj and yy_inp_obj to
//                        avoid naming conflicts with type definitions.
//    04/10/93   bz       added object parameters to yy_cmd_line().  
//                        also moved yy_cmd_file_suffixes and 
//                        yy_cmd_switch_chars const variables to .cpp.
//    08/07/92   bz       removed macros and #ifdefs in C++ only version.
//    03/30/90   bz/cc    coding and final review completed.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef yy_cmd_h_
#define yy_cmd_h_

#include "yy_errst.h"
#include "yy_inpfi.h"
#include "yy_stdio.h"


//////////////////////////////////////////////////////////////////////////////
//
//  POINTER TYPE DECLARATIONS:
//
//  yy_cmd_ptr          is a typedef which defines a pointer to a command
//                      line processing object.  (This references the 
//                      abstract base class).
// 
//  yy_cmd_dflt_ptr     is a typedef which defines a pointer to a command
//                      line processing object using the default 
//                      implementation.
//
//////////////////////////////////////////////////////////////////////////////

typedef class yy_export yy_cmd_obj            *yy_cmd_ptr;
typedef class yy_export yy_cmd_dflt_obj       *yy_cmd_dflt_ptr;

//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_cmd_obj
//
//  The yy_cmd_obj is the abstract base class for the command line processing
//  object.  It represents the interface of the entire command line processor.
//  If you are replacing the command line processing at the most fundamental
//  level, this class provides the minimal interface which you must support.
//  
//  PUBLIC FUNCTIONS:
//
//  ~yy_cmd_obj()        destructor for a command line object.
//
//  yy_cmd_line()        processes the command line arguments.
//
//  yy_cmd_valid_obj()   supports yy_cmd_valid_ptr(cmd_ptr) by returning 
//                       TRUE for a valid command line processing object.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_cmd_obj : public yy_loc_obj {

 public:

    virtual ~yy_cmd_obj() {}

    virtual void yy_cmd_line(
        int     yy_new_argc,
        char    *yy_new_argv[]) = 0;
 
    virtual yy_boolean yy_cmd_valid_obj() 
        { return(yy_true); }

    };  // yy_cmd_obj

    
//////////////////////////////////////////////////////////////////////////////
//
//  FUNCTION:   yy_boolean yy_cmd_valid_ptr(yy_this_cmd)
//
//  yy_cmd_valid_ptr checks the validity of a pointer to a yy_cmd_obj.
//  Before calling the virtual function in the command line processing object
//  which performs the check, it checks here for NULL (to avoid unexpected 
//  crashes).
//
//////////////////////////////////////////////////////////////////////////////

inline yy_boolean yy_cmd_valid_ptr(yy_cmd_ptr  yy_this_cmd)
{
    if (yy_this_cmd != NULL) {
      return(yy_this_cmd->yy_cmd_valid_obj());
      }
   else {
      return(yy_false);
      }
   
}  // yy_cmd_valid_ptr


//////////////////////////////////////////////////////////////////////////////
//
//  CLASS:  yy_cmd_dflt_obj
//
//  The yy_cmd_dflt_obj is the default implementation class for the Yacc++
//  command line processing object.  It represents an entire command line
//  processor.
//
//  A yy_cmd_dflt_obj is the command line processing object the Language 
//  Objects Library provides as its default.  It is derived from the abstract 
//  base command line processing object. 
//
//  PUBLIC FUNCTIONS:
//
//  yy_cmd_dflt_obj()       constructors for the default implementation
//                          of a command line object.
//                                  
//  ~yy_cmd_dflt_obj()      destructor for a default command line object.
//                                  
//  yy_cmd_filename([char *])
//                          gets (or sets with an argument) the current
//                          file name.  Note that this is informational
//                          only.  It does not cause a new file to be opened.
//
//  yy_cmd_line()           processes the command line arguments.
//
//  yy_loc_print_self()     for errors on the command line, displays the
//                          argument number and text.
//
//  INTERNAL STATE:  
//
//  yy_argc                 the number of command line arguments.
//
//  yy_argv                 the command line arguments.
//
//  yy_arg_num              the number of the argument being processed.  
//
//  yy_this_err_obj         pointer to the error object which may be
//                          configured by command line options such as
//                          -errorfile for an alternate errorfile, 
//                          -min_display, -max_warnings, etc.
//
//  yy_filename             is the filename which was opened for processing.  
//                          This filename is the one found after the suffix 
//                          search was applied to the filename specified on 
//                          the command line.
//
//  yy_paths		    is the list of directories to search for when
//			    opening nested input files.  This list is extended
//			    by the -Include options on the command line.
//
//  yy_this_inp_obj         pointer to the input object for the file
//                          being read in from the command line.
//
//////////////////////////////////////////////////////////////////////////////

class yy_export yy_cmd_dflt_obj : public yy_cmd_obj {

 public:

    yy_cmd_dflt_obj();

    yy_cmd_dflt_obj(
        yy_inp_file_ptr     yy_new_inp,
        yy_err_dflt_ptr     yy_new_err = NULL
        );
        
    virtual ~yy_cmd_dflt_obj();

    inline const char *yy_cmd_filename();
    
    inline const char *yy_cmd_filename(const char *yy_new_filename);

    inline const char *const *yy_cmd_paths();

    inline const char *const *yy_cmd_paths(const char *const *yy_new_paths);

    inline const char *const *yy_cmd_paths_extend(const char *yy_new_path);

    virtual void yy_cmd_line(
        int     yy_new_argc,
        char    *yy_new_argv[]
        );

    virtual yy_boolean yy_loc_print_self(yy_err_ptr);

 protected:
    
        int                 yy_argc; 
        int                 yy_arg_num; 
        char                **yy_argv;
        char 		    **yy_paths;
        char		    *yy_filename;
        yy_err_dflt_ptr     yy_this_err_obj;
        yy_inp_file_ptr     yy_this_inp_obj;

    };  // yy_cmd_dflt_obj


//////////////////////////////////////////////////////////////////////////////
//
//  INLINE FUNCTIONS:
//
//  These are the INLINE functions for the command line default object, 
//  defined above.
//
//////////////////////////////////////////////////////////////////////////////

inline const char *yy_cmd_dflt_obj::yy_cmd_filename()
    { return(yy_filename); }

inline const char *yy_cmd_dflt_obj::yy_cmd_filename(
        const char *yy_new_filename)
    { 

        if (yy_filename != NULL) {
            delete [] yy_filename;
            }

        if (yy_new_filename != NULL) {
            yy_filename = new char[strlen(yy_new_filename) + 1];
	    if (yy_filename == NULL) {
		yy_err_report(406);
		yy_assert_fail("space unavailable from new", __FILE__, 
			       __LINE__);
		return(yy_filename);
		}
            strcpy(yy_filename, yy_new_filename);
            }
        else {
            yy_filename = NULL;
            }
 
        return(yy_filename); 
    }

inline const char *const *yy_cmd_dflt_obj::yy_cmd_paths()
 { return((const char *const *)yy_paths); }

inline const char *const *yy_cmd_dflt_obj::yy_cmd_paths(
        const char *const *yy_new_paths)
    { 
        int	len;

        if (yy_paths != NULL) {
	    for (len = 0; yy_paths[len] != NULL; ++len) {
		delete [] yy_paths[len];
		}
            delete [] yy_paths;
            }

        if (yy_new_paths != NULL) {
	    for (len = 0; yy_new_paths[len] != NULL; ++len) {
		}
            yy_paths = new char *[len+1];
	    if (yy_paths == NULL) {
		yy_err_report(406);
		yy_assert_fail("space unavailable from new", __FILE__, 
			       __LINE__);
		return((const char *const *)yy_paths);
		}
	    yy_paths[len] = 0;
	    for (; len != 0; --len) {
		yy_paths[len] = new char [strlen(yy_new_paths[len]) + 1];
		if (yy_paths[len] == NULL) {
		    yy_err_report(406);
		    yy_assert_fail("space unavailable from new", __FILE__, 
				   __LINE__);
		    return((const char *const *)yy_paths);
		    }
		strcpy(yy_paths[len], yy_new_paths[len]);
		}
            }
        else {
            yy_paths = NULL;
            }
 
        return((const char *const *)yy_paths); 
    }


inline const char *const *yy_cmd_dflt_obj::yy_cmd_paths_extend(
        const char *yy_new_path)
    { 
        int	len;
        char	**yy_temp_paths;
    
	if (yy_new_path == NULL) return((const char *const *)yy_paths); 

        if (yy_paths == NULL) {
	    yy_paths = new char*[2];
	    yy_paths[1] = NULL;
	    yy_paths[0] = new char[strlen(yy_new_path) + 1];
	    if (yy_paths == NULL) {
		yy_err_report(406);
		yy_assert_fail("space unavailable from new", __FILE__, 
			       __LINE__);
		return((const char *const *)yy_paths);
		}
	    strcpy(yy_paths[0], yy_new_path);
	    }
	else {
	    for (len = 0; yy_paths[len] != NULL; ++len) {
		}
            yy_temp_paths = new char *[len+2];
	    if (yy_temp_paths == NULL) {
		yy_err_report(406);
		yy_assert_fail("space unavailable from new", __FILE__, 
			       __LINE__);
		return((const char *const *)yy_paths);
		}
	    yy_temp_paths[len+1] = 0;
	    yy_temp_paths[len] = new char [strlen(yy_new_path) + 1];
	    if (yy_temp_paths[len] == NULL) {
		yy_err_report(406);
		yy_assert_fail("space unavailable from new", __FILE__, 
			       __LINE__);
		return((const char *const *)yy_paths);
		}
	    strcpy(yy_temp_paths[len], yy_new_path);
	    for (; len != 0; --len) {
		yy_temp_paths[len] = yy_paths[len];
		}
            delete [] yy_paths;
	    yy_paths = yy_temp_paths;
            }
 
        return((const char *const *)yy_paths); 
    }


#endif /* yy_cmd_h_ */
