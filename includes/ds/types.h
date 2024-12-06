// HEADER FILE CONTAINING DS COMMON TYPES
#pragma once



#define SYS_64 __SIZE_OF_POINTER__ == 8

// generic type for a ds item
typedef void *DSData;


// types for ds
typedef enum _types {
    // fundamental types
    DS_SHORT_T=0,
    DS_USHORT_T,
    DS_INT_T,
    DS_UINT_T,
    DS_CHAR_T,
    DS_UCHAR_T,
    DS_LONG_T,
    DS_ULONG_T,
    DS_LONG_LONG_T,
    DS_ULONG_LONG_T,
    DS_FLOAT_T,
    DS_DOUBLE_T,
    DS_LONG_DOUBLE_T,
    // sized integer types
    DS_INT8_T,
    DS_UINT8_T,
    DS_INT16_T,
    DS_UINT16_T,
    DS_INT32_T,
    DS_UINT32_T,
#if SYS_64
    DS_INT64_T,
    DS_UINT64_T,
#endif
    // custom data type
    DS_CUSTOM_T
} DSDataTypes;


void __type_dispatcher(DSDataTypes type, DSData dest, const DSData src);







/*
 
   THIS LIBRARY MEETS ERRNO PHILOSOFY, ALL FUNCTIONS RETURN NULL OR -1 IN CASE OF ERROR(AND ERRNO IS SET), VALID POINTER OR 1 IN CASE OF SUCCESS 
*/

