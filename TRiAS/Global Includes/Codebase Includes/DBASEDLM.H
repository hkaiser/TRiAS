// File: dbasedlm.h

#ifndef _DBASEDLM_H
#define _DBASEDLM_H

#ifdef WIN32
	#ifdef __DLL__
		#define E4EXPORT __declspec(dllexport) 
	#else
		#define E4EXPORT __declspec(dllimport) 
	#endif
	#define FN_EXP
	#define D4DLL_EXP
#else   // WIN16
    #define E4EXPORT 
	#define FN_EXP __export                  
    #define D4DLL_EXP __export                  
#endif 	// WIN32

#define E4EXPORT_FCT E4EXPORT

#ifndef D4DLLS
	#define D4DLLS
#endif

#ifndef _Windows
	#define _Windows	
#endif

#ifndef WINDOWS
	#define WINDOWS				
#endif

#ifndef ERROR_HANDLING
	#define ERROR_HANDLING		
#endif

#endif 		// _DBASEDLM_H

