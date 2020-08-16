#ifndef ___INCGUARD_PATCHTABLE_BASE_
#define ___INCGUARD_PATCHTABLE_BASE_

#include <Windows.h>
#include <Psapi.h>

typedef const char* pkhc_byte_t;
typedef unsigned long long pkhc_offset_t;
typedef unsigned long long pkhc_size_t;

#define pkhc_offset_cx constexpr unsigned long long
#define pkhc_size_cx constexpr unsigned long long

struct patchtable_t
{
    const char*   id       = "?";     // CSTR ID
    pkhc_byte_t   byte_old = nullptr; // Original byte array 
    pkhc_byte_t   byte_new = nullptr; // Patched byte array
    pkhc_offset_t offset   = 0;       // Offset from base
    pkhc_size_t   size     = 0;       // Size of byte array
    patchtable_t* next     = nullptr; // Pointer to the next patchtable

    constexpr pkhc_size_t size_auto()
    {
        if (!byte_old)
            return 0;

        pkhc_byte_t data = byte_old;
        pkhc_size_t sz   = 0;

        while (*data)
        {
            data++;
            sz++;
        }

        return sz - 1;
    }
};

enum HCASMSTATUS : unsigned char
{
    HC_ASM_INVALID,
    HC_ASM_ORIGIN,
    HC_ASM_PATCHED,
};

#endif//___INCGUARD_PATCHTABLE_BASE_