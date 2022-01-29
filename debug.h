/* File name: debug.h */
#ifndef __DEBUG_H__
#define __DEBUG_H__
#define __trap() (assert(false), 0)

#if !defined(NDEBUG)
#	if defined(__GNUC__) // Are we compiling for host testing ?

#	elif defined(__IAR__SYSTEMS_ICC__) // Are we compiling for embedded S32K ?
#		include "devassert.h"

#		ifdef assert
#			error "assert is not expected to be defined in that case"
#		endif
#			define assert DEV_ASSERT

#	else
#	error "Unexpected environement"

#	endif //
	
/* Target debug call */
#	ifdef UNIT_TEST
#	include <stdio.h>
#	endif

#	ifdef UNIT_TEST
	extern void Debug_InitOutputFile(FILE *pOutputFile);
#	endif

#	define dbgValidAddr(p) (p!= NULL ? true : false)
#	define dbgCheckValidAddr(p) dbgAssert(dbgValidAddr(p))
#	define dbgptr(p,t) ( dbgValidAddr(p) ? ( ((t*)p)->__debug__magic == DEBUG_MAGIC_NAME(t) ? ((t*)p): __trap()) : __trap() )

#	define dbgCheckPtr(p) dbgAssert(dbgValidAddr(p))
#	define dbgAssert(c)	assert(c)

#	define DEBUG_MAGIC_NAME(t) t##__MAGIC
#	define DEBUG_MAGIC_SET(p,t) ( ((*t)(p))->__debug__magic= DEBUG_MAGIC_NAME(t) )
#	define DEBUG_MAGIC_RESET(p,t) ((p)->__debug__magic= 0x1234AABB)
#	define DEBUG_MAGIC_FIELD unsigned long __debug__magic;

#else // no code for trap an assertion

#	define dbgValidAddr(p) (p!=NULL ? TRUE : FALSE)
#	define dbgCheckValidAddr(p) ((void)p)
#	define dbgPtr(p,t) ((t*)p)

#	define dbgCheckPtr(p) ((void)p)
#	define dbgAssert(c)	((void)c)

#	define DEBUG_MAGIC_SET(p,t) ((void)NULL)
#	define DEBUG_MAGIC_RESET(p,t) ((void)NULL)

#	define DEBUG_MAGIC_FIELD

#endif //!defined(NDEBUG


#endif // __DEBUG_H__