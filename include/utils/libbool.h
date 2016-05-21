/*
    * Created by Thibault PIANA on 20/05/16.
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ONLYOS_UTILS_LIBBOOL_H
#define ONLYOS_UTILS_LIBBOOL_H
    #define bool char

    #ifndef true
        #define true 1
    #endif

    #ifndef false
        #define false 0
    #endif

    /* Convenant symbols */
    #define	__bool_true_false_are_defined	1
#endif //ONLYOS_LIBBOOL_H

#ifdef __cplusplus
}
#endif