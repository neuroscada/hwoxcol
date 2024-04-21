#ifndef DEPRECATE_H
#define DEPRECATE_H
// This file is intended to contain all macros and other definitions to mark functions as deprecated.  Every instance of a
// method or symbol deprecation at a global level, should be defined here.  This file is intended to be included by defs.h.

// Use the following line to control whether deprecated functions and symbols are an error (i.e. build failure) or a warning.
//#pragma warning(error : 4996)  // Make use of __declspec(deprecated) functions an error
//#pragma warning(error : 4995)  // Make use of #pragma deprecated(symbol) symbols an error

// Macro: COMPATIBLE_DEPRECATED(text)
// Summary: A macro to call __declspec(deprecated()), that will downgrade as needed by the Microsoft compiler version
#ifndef _MSC_VER // If not on a Microsoft C compiler assume no deprecation support
    #define COMPATIBLE_DEPRECATED(text)
#else
    #if _MSC_VER < 1310 // If on VCC version that doesn't support deprecation, e.g. < VS2003
        #define COMPATIBLE_DEPRECATED(text)
    #else
        #if _MSC_VER >= 1400  // If on VCC version that supports deprecation with custom text, e.g. >= VS2005
            #define COMPATIBLE_DEPRECATED(text) __declspec(deprecated(text))
        #else
            #define COMPATIBLE_DEPRECATED(text) __declspec(deprecated)
        #endif
    #endif
#endif

//
// Define deprecation specifiers with custom messages.  A different specifier should be used for each reason for deprecation.
//

// Deprecation strings to be used with "__declspec(deprecated(MY_TEXT))".  These messages are only shown to developers, 
// so should not require i18n processing.
#define PNT16_DEPRECATION_TEXT "Function is deprecated because it uses 16 bit point numbers."
#define NAPI_DEPRECATION_TEXT  "Function is deprecated and may be removed in a future release."
#define SEC_UNSAFE_DEPRECATION_TEXT  "Function is deprecated because it is unsafe, please use _s version instead."

// Macro: PNT16_DEPRECATED(text)
// Summary: Used to mark methods which rely on 16 bit point numbers as deprecated
//          To disable these deprecation warnings, define PNT16_NO_DEPRECATE
#ifdef PNT16_NO_DEPRECATE  // If deprecation of 16 bit point usage has been switched off, replace with nothing
    #define PNT16_DEPRECATED
#else
    #define PNT16_DEPRECATED COMPATIBLE_DEPRECATED(PNT16_DEPRECATION_TEXT)
#endif

// Macro: NAPI_DEPRECATED(text)
// Summary: Used to mark methods that are part of the Network API as deprecated.  This is a general deprecation 
//          to be used when we don't or can't provide users with the underlying reason.
//          To disable these deprecation warnings, define NAPI_NO_DEPRECATE
#ifdef NAPI_NO_DEPRECATE  // If deprecation of Network API functions has been switched off, replace with nothing
    #define NAPI_DEPRECATED
#else
    #define NAPI_DEPRECATED COMPATIBLE_DEPRECATED(NAPI_DEPRECATION_TEXT)
#endif

// Macro: SEC_UNSAFE_DEPRECATED(text)
// Summary: Used to mark methods that are part of the Server internal API that are not safe.  Many functions
//          in the server take an input buffer as a parameter, but no buffer sizing is provided, this makes it
//          inherently unsafe for the function to operatoe on it, as it has no clues as to when it might overrun
//          the buffer leading to a potential security whole.
//
//          All such functions should either be updated to include buffer sizing, or create a new version with 
//          buffer sizing and mark existing version as deprecated (see conf_nt.h for example usage). Typically
//          you would take the latter path only if the number of places to update is large, this way compiler
//          warnings should be raised alerting subsystem owners to correct, and preventing new usage of these
//          functions.
//
//          Where updating a function please ensure all memory buffer operations are updated to use the MS _s versions
//          eg use strncpy_s instead of strcpy or strncpy, _snprintf_s instead of snprintf or sprintf, etc... these 
//          allow for specification of buffer size as well as _TRUNCATE allows for the string to be neatly truncated 
//          rather than an exception thrown if buffer is too small.
//
//          To disable these deprecation warnings, define SEC_UNSAFE_NO_DEPRECATE
#ifdef SEC_UNSAFE_NO_DEPRECATE  // If deprecation of unsafe functions has been switched off, replace with nothing
    #define SEC_UNSAFE_DEPRECATED
#else
    #define SEC_UNSAFE_DEPRECATED COMPATIBLE_DEPRECATED(SEC_UNSAFE_DEPRECATION_TEXT)
#endif


#endif //DEPRECATE_H
