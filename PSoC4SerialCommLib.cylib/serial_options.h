#if !defined(serial_options_H)
#define serial_options_H

    #if !defined(NO)
        #define NO                          (0u)
    #endif
    #if !defined(YES)
        #define YES                         (1u)
    #endif
    #if !defined(FALSE)
        #define FALSE                          (0u)
    #endif
    #if !defined(TRUE)
        #define TRUE                         (1u)
    #endif


    #if !defined(ENCRYPTION_ENABLED)
        #define ENCRYPTION_ENABLED          (NO)
    #endif

    #if !defined(DO_DEBUG)
        #define DO_DEBUG                    (NO)
    #endif

    #if !defined(NULL)
        #define NULL ((void *)0)
    #endif
    
#endif /* serial_options_H */
