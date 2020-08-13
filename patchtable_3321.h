// Table of info for HandyCafe v3.3.21

#ifndef ___INCGUARD_PATCHTABLE_3321_
#define ___INCGUARD_PATCHTABLE_3321_

#include "patchtable_base.h"

namespace patchtable_3321
{
    extern patchtable_t __NoLockScreen_next_desktop;

    patchtable_t NoLockScreen =
    {
        "\x8B\xEC",
        "\x5D\xC3",
        0x125761,
        2,
        &patchtable_3321::__NoLockScreen_next_desktop
    };

    patchtable_t __NoLockScreen_next_desktop =
    {
        NoLockScreen.byte_old,
        NoLockScreen.byte_new,
        0x158081,
        2
    };

    patchtable_t NoProcClear =
    {
        "\x75\x08",
        "\xEB\x77",
        0x11DDEB,
        2
    };

    patchtable_t NoBrowserOnLogin
    {
        "\x50\x68\x74\xE7\x56\x00\x6A\x00\xE8\x66\x8E\xEE\xFF",
        nullptr,
        0x16E5B5,
        13
    };

    patchtable_t NoRemoteShutdown =
    {
        "\x8B\xF2",
        "\xEB\x7F",
        0x123A59,
        2
    };

    patchtable_t NoForegroundQuery =
    {
        "\x8B\xD8",
        "\x33\xC0",
        0x127C1A,
        2
    };

    patchtable_t __SpoofLockscreen_next_adminalertserver =
    {
        "\xE8\xC8\xE4\xFF\xFF",
        nullptr,
        0x128FE3,
    };

    patchtable_t __SpoofLockscreen_next_servercheckjump =
    {
        "\xEB\x5D",
        nullptr,
        0x156788,
        2,
        &patchtable_3321::__SpoofLockscreen_next_adminalertserver
    };

    patchtable_t __SpoofLockscreen_next_alertserver =
    {
        "\xE8\x41\x28\xFD\xFF",
        nullptr,
        0x1567E2,
        5,
        &patchtable_3321::__SpoofLockscreen_next_servercheckjump
    };

    patchtable_t SpoofLockscreen =
    {
        "\xFF\x53\x38",
        nullptr,
        0x9F693,
        3,
        &patchtable_3321::__SpoofLockscreen_next_alertserver
    };

    namespace ExitHC_v
    {
        pkhc_offset_t offset = 0x164EFC;
    }
}
#endif//___INCGUARD_PATCHTABLE_3321_