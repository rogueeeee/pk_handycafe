# <img width="28" src="https://en.touhouwiki.net/images/7/7b/Th135Patchouli.png"> <font size=80> pk for handyCafe </font>
Runtime patching and modification tool for handyCafe

<img src ="https://raw.githubusercontent.com/rogueeeee/pk_handycafe/master/ss.png"/>

## Features
* <b>No logout lockscreen</b> - Disables logout of client both for Client (Logout user, Credit expiration, etc...) and Server (Logout user) side
* <b>No Process clear</b> - Disables the clearing / termination of process on log out
* <b>No Browser on login</b> - Disables the browser pop up on login
* <b>No Remote shutdown</b> - Disables the remote shutdown feature that can be triggered by the server
* <b>Exit handycafe</b> - Executes the exit routine of handycafe
* <b>No foreground query</b> - Disables the Client's foreground query, preventing the server from gathering information regarding the currently focused window
* <b>Authentication Bypass</b> - Bypasses the server side authentication allowing you to login with any credentials
* ~~<b>Spoof Lockscreen</b> - Disables the lockscreen from forcing itself in the foreground and prevents the client from confirming the login on the server and hide/show the lockscreen on key~~

## Supported Versions
* handyCafe 3.3.21 (21/July/2010)
* handyCafe 4.1.16 (10/August/2016)

## Building
<i>Open in Visual Studio through <b>pk_handycafe.vcxproj</b>, setup the build config, and press <b>Ctrl + B</b></i>
* Solution Config: Release
* Solution Platform: x86
* Character set: Multi-byte
* Main file: <b>[pkhandycafe.cpp](https://github.com/rogueeeee/pk_handycafe/blob/master/pkhandycafe.cpp)</b>

## Note

* Support for <u><b>handyCafe version 4.1.16</b> features are <b>intentionally disabled</b></u> and excluded from the repository.

* Patch table for HandyCafe 4.1.16 (latest handyCafe version) is not included
in the repo, define <b>[PKHC_DISABLE_SUPPORT_NEW](https://github.com/rogueeeee/pk_handycafe/blob/master/pkhandycafe.h#L8)</b> in <b>pkhandycafe.h</b>
to prevent errors on compilation. By default, this release uses the <b>patchtable_4116_dummy.h</b>

* [Old repo for MinGW](https://github.com/rogueeeee/pk_handycafe/releases/tag/0.0.2)

* <b>[PKHC_SPOOF_LAZY](https://github.com/rogueeeee/pk_handycafe/blob/master/pkhandycafe.h#L9)</b> macro is defined for disabling the spoof lockscreen feature because I broke it, undefine if you got the patchtable correct

## License
MIT