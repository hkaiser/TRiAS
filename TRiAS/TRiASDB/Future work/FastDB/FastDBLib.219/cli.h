/*-< CLI.H >---------------------------------------------------------*--------*
 * FastDB                    Version 1.0         (c) 1999  GARRET    *     ?  *
 * (Main Memory Database Management System)                          *   /\|  *
 *                                                                   *  /  \  *
 *                          Created:     13-Jan-2000 K.A. Knizhnik   * / [] \ *
 *                          Last update: 13-Jan-2000 K.A. Knizhnik   * GARRET *
 *-------------------------------------------------------------------*--------*
 * Call level interface to FastDB server
 *-------------------------------------------------------------------*--------*/

#ifndef __CLI_H__
#define __CLI_H__

#ifdef __cplusplus
extern "C" { 
#endif

enum cli_result_code { 
    cli_ok = 0,
    cli_bad_address = -1,
    cli_connection_refused = -2,
    cli_database_not_found = -3, 
    cli_bad_statement = -4,
    cli_parameter_not_found = -5,
    cli_unbound_parameter = -6,
    cli_column_not_found = -7,
    cli_incompatible_type = -8,
    cli_network_error = -9,
    cli_runtime_error = -10,
    cli_bad_descriptor = -11,
    cli_unsupported_type = -12,
    cli_not_found        = -13,
    cli_not_update_mode  = -14,
    cli_table_not_found  = -15,
    cli_not_all_columns_specified = -16, 
    cli_not_fetched = -17
};
    
enum cli_var_type { 
    cli_oid,
    cli_bool, 
    cli_int1, 
    cli_int2,
    cli_int4,
    cli_int8,
    cli_real4,
    cli_real8,
    cli_asciiz,  /* zero terminated string */
    cli_pasciiz, /* pointer to zero terminated string */
    cli_array_of_oid,
    cli_array_of_bool, 
    cli_array_of_int1, 
    cli_array_of_int2,
    cli_array_of_int4,
    cli_array_of_int8,
    cli_array_of_real4,
    cli_array_of_real8
};

typedef char         cli_bool_t;
typedef signed char  cli_int1_t;
typedef signed short cli_int2_t;
typedef signed int   cli_int4_t;
typedef float        cli_real4_t;
typedef double       cli_real8_t;
    
#if defined(_WIN32)
typedef __int64      cli_int8_t;
#else
#if defined(__osf__ )
typedef signed long  cli_int8_t;
#else
#if defined(__GNUC__) || defined(__SUNPRO_CC)
typedef signed long long cli_int8_t;
#else
#error "integer 8 byte type is not defined" 
#endif
#endif
#endif

#ifndef CLI_OID_DEFINED
typedef long cli_oid_t;
#endif

/*********************************************************************
 * cli_open
 *     Establish connection with the server 
 * Parameters:
 *     server_url - zero terminated string with server address and port, 
 *                  for example "localhost:5101", "195.239.208.240:6100",...
 *     max_connect_attempts  - number of attempts to establish connection
 *     reconnect_timeout_sec - timeput in seconds between connection attempts
 * Returns:
 *     >= 0 - connectiondescriptor to be used in all other cli calls
 *     <  0 - error code as described in cli_result_code enum
 */
int cli_open(char const* server_url, 
	     int         max_connect_attempts,
	     int         reconnect_timeout_sec);

/*********************************************************************
 * cli_close
 *     Close session
 * Parameters:
 *     session - session descriptor returned by cli_open
 * Returns:
 *     result code as described in cli_result_code enum
 */
int cli_close(int session);

/*********************************************************************
 * cli_statement
 *     Specify SunSQL statement to be executed at server
 *     Binding to the parameters and columns can be established       
 * Parameters:
 *     session - session descriptor returned by cli_open
 *     stmt    - zero terminated string with SubSQL statement  
 * Returns:
 *     >= 0 - statement descriptor
 *     <  0 - error code as described in cli_result_code enum
 */
int cli_statement(int session, char const* stmt);

/*********************************************************************
 * cli_parameter
 *     Bind parameter to the statement
 * Parameters:
 *     statement  - statememt descriptor returned by cli_statement
 *     param_name - zero terminated string with parameter name  
 *                  Paramter name should start with '%'
 *     var_type   - type of variable as described in cli_var_type enum.
 *                  Only scalar and zero terminated string types are supported.
 *     var_ptr    - pointer to the variable
 * Returns:
 *     result code as described in cli_result_code enum
 */
int cli_parameter(int         statement,
		  char const* param_name, 
		  int         var_type,
		  void*       var_ptr);

/*********************************************************************
 * cli_column
 *     Bind extracted column of select or insert statement
 * Parameters:
 *     statement   - statememt descriptor returned by cli_statement
 *     column_name - zero terminated string with column name  
 *     var_type    - type of variable as described in cli_var_type enum
 *     var_len     - pointer to the variable to hold length of array variable.
 *                   This variable should be assigned the maximal length
 *                   of the array/string buffer, pointed by var_ptr.
 *                   After the execution of the statement it is assigned the 
 *                   real length of the fetched array/string. If it is large 
 *                   than length of the buffer, then only part of the array
 *                   will be placed in the buffer, but var_len still will 
 *                   contain the actual array length. 
 *     var_ptr     - pointer to the variable
 * Returns:
 *     result code as described in cli_result_code enum
 */
int cli_column(int         statement,
	       char const* column_name, 
	       int         var_type, 
	       int*        var_len, 
	       void*       var_ptr);


typedef void* (*cli_column_set)(int var_type, void* var_ptr, int len);
typedef void* (*cli_column_get)(int var_type, void* var_ptr, int* len);

/*********************************************************************
 * cli_array_column
 *     Specify get/set functions for the array column
 * Parameters:
 *     statement   - statememt descriptor returned by cli_statement
 *     column_name - zero terminated string with column name  
 *     var_type    - type of variable as described in cli_var_type enum
 *     var_ptr     - pointer to the variable
 *     set         - function which will be called to construct fetched 
 *                   field. It receives pointer to the variable, 
 *                   length of the fetched array and returns pointer to th 
 *                   array's elements
 *     get         - function which will be called to update the field in the 
 *                   database. Given pointer to the variable, it should return 
 *                   pointer to the array elements and store length of the
 *                   array to the variable pointer by len parameter
 * Returns:
 *     result code as described in cli_result_code enum
 */
int cli_array_column(int            statement,
		     char const*    column_name, 
		     int            var_type,
		     void*          var_ptr,
		     cli_column_set set,
		     cli_column_get get);
    
enum { 
    cli_view_only, 
    cli_for_update
};

/*********************************************************************
 * cli_fetch
 *     Execute select statement.
 * Parameters:
 *     statement  - statememt descriptor returned by cli_statement
 *     for_update - not zero if fetched rows will be updated 
 * Returns:
 *     >= 0 - success, for select statements number of fetched rows is returned
 *     <  0 - error code as described in cli_result_code enum
 */
int cli_fetch(int statement, int for_update);

/*********************************************************************
 * cli_insert
 *     Execute insert statement.
 * Parameters:
 *     statement  - statememt descriptor returned by cli_statement
 *     oid        - object identifier of created record. 
 * Returns:
 *     status code as described in cli_result_code enum
 */
int cli_insert(int statement, cli_oid_t* oid);

/*********************************************************************
 * cli_get_first
 *     Get first row of the selection.
 * Parameters:
 *     statement  - statememt descriptor returned by cli_statement
 * Returns:
 *     result code as described in cli_result_code enum
 */
int cli_get_first(int statement);

/*********************************************************************
 * cli_get_last
 *     Get last row of the selection.
 * Parameters:
 *     statement  - statememt descriptor returned by cli_statement
 * Returns:
 *     result code as described in cli_result_code enum
 */
int cli_get_last(int statement);

/*********************************************************************
 * cli_get_next
 *     Get next row of the selection. If get_next records is called
 *     exactly after cli_fetch function call, is will fetch the first record
 *     in selection.
 * Parameters:
 *     statement  - statememt descriptor returned by cli_statement
 * Returns:
 *     result code as described in cli_result_code enum
 */
int cli_get_next(int statement);

/*********************************************************************
 * cli_get_prev
 *     Get previous row of the selection. If get_next records is called
 *     exactly after cli_fetch function call, is will fetch the last record
 *     in selection.
 * Parameters:
 *     statement  - statememt descriptor returned by cli_statement
 * Returns:
 *     result code as described in cli_result_code enum
 */
int cli_get_prev(int statement);

/*********************************************************************
 * cli_get_oid
 *     Get object identifier of the current record
 * Parameters:
 *     statement  - statememt descriptor returned by cli_statement
 * Returns:
 *     object identifier or 0 if no object is seleected
 */
cli_oid_t cli_get_oid(int statement);

/*********************************************************************
 * cli_update
 *     Update the current row in the selection. You have to set
 *     for_update parameter of cli_fetch to 1 in order to be able 
 *     to perform updates. Updated value of row fields will be taken
 *     from bound column variables. 
 * Parameters:
 *     statement   - statememt descriptor returned by cli_statement
 * Returns:
 *     result code as described in cli_result_code enum
 */
int cli_update(int statement);

/*********************************************************************
 * cli_remove
 *     Remove all selected records. You have to set
 *     for_update parameter of cli_fetch to 1 in order to be able 
 *     to remove records. 
 * Parameters:
 *     statement   - statememt descriptor returned by cli_statement
 * Returns:
 *     result code as described in cli_result_code enum
 */
int cli_remove(int statement);

/*********************************************************************
 * cli_free
 *     Deallocate statement and all associated data
 * Parameters:
 *     statement   - statememt descriptor returned by cli_statement
 * Returns:
 *     result code as described in cli_result_code enum
 */
int cli_free(int statement);

/*********************************************************************
 * cli_commit
 *     Commit current database transaction
 * Parameters:
 *     session - session descriptor as returned by cli_open
 * Returns:
 *     result code as described in cli_result_code enum
 */
int cli_commit(int session);

/*********************************************************************
 * cli_abort
 *     Abort current database transaction
 * Parameters:
 *     session - session descriptor as returned by cli_open
 * Returns:
 *     result code as described in cli_result_code enum
 */
int cli_abort(int session);


#ifdef __cplusplus
}
#endif

#endif


