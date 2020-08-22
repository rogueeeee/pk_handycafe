// Table of info for HandyCafe v3.3.21

#ifndef ___INCGUARD_PATCHTABLE_3321_
#define ___INCGUARD_PATCHTABLE_3321_

#include "patchtable_base.h"

namespace patchtable_3321
{
    extern patchtable_t __NoLockScreen_next_desktop;

    patchtable_t NoLockScreen =
    {
        "nls",
        "\x8B\xEC",
        "\x5D\xC3",
        0x125761,
        2,
        &patchtable_3321::__NoLockScreen_next_desktop
    };

    patchtable_t __NoLockScreen_next_desktop =
    {
        "nls_2",
        NoLockScreen.byte_old,
        NoLockScreen.byte_new,
        0x158081,
        2
    };

    patchtable_t NoProcClear =
    {
        "npc",
        "\x75\x08",
        "\xEB\x77",
        0x11DDEB,
        2
    };

    patchtable_t NoBrowserOnLogin
    {
        "nbol",
        "\x50\x68\x74\xE7\x56\x00\x6A\x00\xE8\x66\x8E\xEE\xFF",
        nullptr,
        0x16E5B5,
        13
    };

    patchtable_t NoRemoteShutdown =
    {
        "nrs",
        "\x8B\xF2",
        "\xEB\x7F",
        0x123A59,
        2
    };

    patchtable_t NoForegroundQuery =
    {
        "nfq",
        "\x8B\xD8",
        "\x33\xC0",
        0x127C1A,
        2
    };
#ifndef PKHC_SPOOF_LAZY
    patchtable_t __SpoofLockscreen_next_setupdesktop =
    {
        "sl_7",
        "\xE8\xFB\x31\xFF\xFF",
        nullptr,
        0x164E80
    };

    patchtable_t __SpoofLockscreen_next_hidetaskbar =
    {
        "sl_6",
        "\xE8\x7D\x2B\xEE\xFF",
        nullptr,
        0x1257C6,
        5
    };

    patchtable_t __SpoofLockscreen_next_hidesidepanel =
    {
        "sl_5",
        "\xE8\x93\x2B\xEE\xFF",
        nullptr,
        0x1257B0,
        5,
        &patchtable_3321::__SpoofLockscreen_next_hidetaskbar
    };

    patchtable_t __SpoofLockscreen_next_adminalertserver =
    {
        "sl_4",
        "\xE8\xC8\xE4\xFF\xFF",
        nullptr,
        0x128FE3,
        5,
        &patchtable_3321::__SpoofLockscreen_next_hidesidepanel
    };

    patchtable_t __SpoofLockscreen_next_servercheckjump =
    {
        "sl_3",
        "\xEB\x5D",
        nullptr,
        0x156788,
        2,
        &patchtable_3321::__SpoofLockscreen_next_adminalertserver
    };

    patchtable_t SpoofLockscreen =
    {
        "sl_2",
        "\xE8\x41\x28\xFD\xFF",
        nullptr,
        0x1567E2,
        5,
        &patchtable_3321::__SpoofLockscreen_next_servercheckjump
    };

    patchtable_t SpoofLockscreen_event_getforeground =
    {
        "sl",
        "\xFF\x53\x38",
        nullptr,
        0x9F693,
        3,
    };
#endif
    patchtable_t NoAuthentication =
    {
        "na",
        "\x74\x14",
        nullptr,
        0x156774,
        2
    };

    namespace ExitHC_v
    {
        pkhc_offset_cx offset = 0x164EFC;
    }
}
#endif//___INCGUARD_PATCHTABLE_3321_