#ifndef __INCGUARD_HASH_
#define __INCGUARD_HASH_

typedef unsigned long long FNV64; // type definition for FNV hash result

namespace utils
{
    // Hashes a string with FNV
    constexpr FNV64 hashfnv(const char* str)
    {
        FNV64 result = 0xcbf29ce484222325ull;
    
        while(*str)
            result = (result * 0x00000100000001B3ull) ^ *str++;
    
        return result;
    }
    
    constexpr FNV64 hashfnv_partial(const char* str, size_t len)
    {
        FNV64 result = 0xcbf29ce484222325ull;
    
        while(*str && len-- > 0)
            result = (result * 0x00000100000001B3ull) ^ *str++;
    
        return result;
    }
}

#endif