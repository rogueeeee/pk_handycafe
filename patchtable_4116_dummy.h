// Table of info for HandyCafe v4.1.16

#ifndef ___INCGUARD_PATCHTABLE_4116_DUMMY_
#define ___INCGUARD_PATCHTABLE_4116_DUMMY_
#ifdef PKHC_DISABLE_SUPPORT_NEW

#include "patchtable_base.h"
namespace patchtable_4116
{
    patchtable_t NoLockScreen;
    patchtable_t NoProcClear;
    patchtable_t NoBrowserOnLogin;
    patchtable_t NoRemoteShutdown;
    patchtable_t NoForegroundQuery;

    namespace SpoofLockscreen_v
    {
        pkhc_offset_t getforeground_offset  = 0x0;
    }

    namespace ExitHC_v
    {
        pkhc_offset_t offset = 0x0;
    }
}
#endif
#endif//___INCGUARD_PATCHTABLE_4116_DUMMY_