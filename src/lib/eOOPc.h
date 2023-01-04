#ifndef EOOPC_MAIN_H
#define EOOPC_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
	
	/**
	* Colours for the console
	*/
		#define  cRED "\x1b[31m"
		#define  cGREEN "\x1b[32m"
		#define  cYELLOW "\x1b[33m"
		#define  cBLUE "\x1b[34m"
		#define  cMAGENTA "\x1b[35m"
		#define  cCYAN "\x1b[36m"
		#define  cRESET "\x1b[0m"
	
	/**
	* Debugging macros originally taken from
	* Learn C the Hard Way: Practical Exercises on the Computational Subjects You Keep Avoiding (Like C)
	* Book by Zed Shaw (Zed's Aesome Debug Macros)
	*/

		#define eERR 1
	
		/**
		* Set up some debugging functions that can be globally turned off with a definition
		*/
			#ifdef eNODEBUG
				#define eDEBUG(msg, ...)
			#else
				#define eDEBUG(msg, ...) fprintf(stderr, "DEBUG %s:%d: " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__)
			#endif
	
		/**
		* Get string version of global errno
		*/
			#define eCLEANERRNO() (errno == 0 ? "None" : strerror(errno))
		
		/**
		* Log an error
		*/
			#define eLOGERROR(msg, ...) fprintf(stderr, cRED "[ERROR] (%s:%d: errno: %s) " msg "\n" cRESET, \
			__FILE__, __LINE__, eCLEANERRNO(), ##__VA_ARGS__)
		
		/**
		* Log a warning
		*/
			#define eLOGWARN(msg, ...) fprintf(stderr, cYELLOW "[WARN] (%s:%d: errno: %s) " msg "\n" cRESET, \
			__FILE__, __LINE__, eCLEANERRNO(), ##__VA_ARGS__)
		
		/**
		* Log some info
		*/
			#define eLOGINFO(msg, ...) fprintf(stderr, cRESET "[INFO] (%s:%d) " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__)
		
		/**
		* Try a test, outputting an error if false, then goto a given error_X marker
		*/
			#define eCHECK(test,err,msg, ...) if(test) { eLOGERROR(msg, ##__VA_ARGS__); errno=0; goto error_##err; } else errno=0
	
		/**
		* Mark a chunk of code that will throw an error. Usage eTRY{ ... }. "return" should be within try block
		*/
			#define eTRY if(1)
		
		/**
		* Throw an error to be "caught" by the appropriate catch marker
		*/
			#define eTHROW(exc,msg, ...) eLOGERROR(msg, ##__VA_ARGS__); goto error_##exc
	
		/**
		* wrap definition of error_x marker
		*/
			#define eCATCH(n) error_##n: if(1)
	
	/**
	* OOP Macros. Read up on OOP here:
	* https://github.com/erbarratt/eoopc
	* Extreme C: Taking you to the limit in Concurrency, OOP, and the most advanced capabilities of C - Kamran Amini
	*/
	
		/**
		* grab an interface definition by calling it's macro.
		* @param i Interface name
		*/
			#define eIMPLEMENTS(i) eINTERFACE_##i()
	
		/**
		* helper macro to denote that this parent is upcastable (this macro must be first element of containing
		* struct for this to be true)
		* @param c Class
		* @param p Property name
		*/
			#define eINHERITS(c,p) struct c p
		
		/**
		* Instantiate an object 'o*' of type 'c' by using function 'c_instatiate()'
		* @param c Struct type
		* @param o Object variable name
		* @param ... any further arguments
		*/
			#define eCONSTRUCT(c, ...) c##_instantiate(__VA_ARGS__)
		
		/**
		* Call allocation method and imediately fire instantiation function for heap object
		* @param c Struct type
		* @param o Object variable name
		* @param ... any further arguments
		*/
			#define eNEW(c) (struct c *)malloc(sizeof(struct c))
		
		/**
		* Cast "self" back into the class type
		* @param c Struct type
		*/
			#define eSELF(c) struct c * self = (struct c*)eOBJ
		
		/**
		* upCast "self" to parent struct type. Parent struct type must be first struct member publically
		* Can only be called from scope where child object is instantiated
		* @param c Struct type
		* @param v Variable name to use
		*/
			#define ePARENT(c, v) struct c * v = (struct c *)self
		

		/**
		* Method call wrapper that passes object as first argument for use of eSELF()
		* @param o Object
		* @param m The method
		* @param ... Other args
		*/
			#define eCALLarg(o, m, ...) (*o->m)(o, __VA_ARGS__)
		
		/**
		* Method call wrapper that passes object as first argument for use of eSELF(), no arguments
		* @param o Object
		* @param m The method
		* @param ... Other args
		*/
			#define eCALL(o,m) (*o->m)(o)
			
		/**
		* Free memory on heap for object
		* @param var o Object variable name
		*/
			#define eDESTROY(o) free(o); o = ((void*)0)
		
#endif //OOP_MAIN_H
