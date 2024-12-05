/*
Types definition for data structures
*/

#include <stdint.h>
#include "./types.h"




// cast void pointer to specific type, in order to allow inserting value directly into variable
void __type_dispatcher(DSDataTypes type, DSData dest, const DSData src) {
    // first casting to long for avoiding compiler narrowing conversion warning
     switch(type) { 
        case DS_CHAR_T:
            *(char*)dest = (char)(long)src; 
            break;
        case DS_UCHAR_T:
            *(unsigned char*)dest = (unsigned char)(long)src; 
            break;
        case DS_SHORT_T:
            *(short*)dest = (short)(long)src; 
            break;
        case DS_USHORT_T:
            *(unsigned short*)dest = (unsigned short)(long)src; 
            break;
        case DS_INT_T:
            *(int*)dest = (int)(long)src; 
            break;
        case DS_UINT_T:
            *(unsigned int*)dest = (unsigned int)(long)src; 
            break;
        case DS_LONG_T:
            *(long*)dest = (long)src; 
            break;
        case DS_ULONG_T:
            *(unsigned long*)dest = (unsigned long)src; 
            break;
        case DS_LONG_LONG_T:
            *(long long*)dest = (long long)src; 
            break;
        case DS_ULONG_LONG_T:
            *(unsigned long long*)dest = (unsigned long long)src; 
            break;
        // sized integer types
        case DS_INT8_T:
            *(int8_t*)dest = (int8_t)src; 
            break;
        case DS_UINT8_T:
            *(uint8_t*)dest = (uint8_t)src; 
            break;
        case DS_INT16_T:
            *(int16_t*)dest = (int16_t)src; 
            break;
        case DS_UINT16_T:
            *(uint16_t*)dest = (uint16_t)src; 
            break;
        case DS_INT32_T:
            *(int32_t*)dest = (int32_t)src; 
            break;
        case DS_UINT32_T:
            *(uint32_t*)dest = (uint32_t)src; 
            break;
    // if 64bit system, allow 64bit types
    #if SYS_64
        case DS_INT64_T:
            *(int64_t*)dest = (int64_t)src; 
            break;
        case DS_UINT64_T:
            *(uint64_t*)dest = (uint64_t)src; 
            break;
        // custom data type, here elements are pointers, so just copy src to dest
        default:
            *(uint64_t*)dest = src;
    #else
        default:
            *(uint32_t*)dest = src;
    #endif
    } 
}
