//-< EXCEPTION.H >---------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:     3-Oct-99 Sebastiano Suraci  * / [] \ *
//                          Last update: 5-Oct-99 K.A. Knizhnik      * GARRET *
//-------------------------------------------------------------------*--------*
// Database exception 
//-------------------------------------------------------------------*--------*

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

class dbException
{
   protected:
     int   err_code;
     char* msg;	
     int   arg;

   public:
     dbException(int p_err_code, const char* p_msg = NULL, int p_arg = 0)
     : err_code (p_err_code),
       msg (NULL),
       arg (p_arg)
     { 
         if (p_msg != NULL) { 
	     msg = new char[strlen(p_msg)+1]; 
	     strcpy(msg, p_msg);
	 }
     }

     ~dbException() { 
         delete[] msg;
     }

     int   getErrCode() const { return err_code; }
     char* getMsg()     const { return msg; }
     long  getArg()     const { return arg; }
};

#endif
