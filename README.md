# <img width="28" src="https://en.touhouwiki.net/images/7/7b/Th135Patchouli.png"> <font size=80> pk for handyCafe </font>
Runtime patching and modification tool for handyCafe

## Features
* <b>No logout lockscreen</b> - Disables logout of client both for Client (Logout user, Credit expiration, etc...) and Server (Logout user) side
* <b>No Process clear</b> - Disables the clearing / termination of process on log out
* <b>No Browser on login</b> - Disables the browser pop up on login
* <b>No Remote shutdown</b> - Disables the remote shutdown feature that can be triggered by the server
* <b>Exit handycafe</b> - Executes the exit routine of handycafe
* <b>No foreground query</b> - Disables the Client's foreground query, preventing the server from gathering information regarding the currently focused window
* <b>Spoof Lockscreen</b> - Disables the lockscreen from forcing itself in the foreground and prevents the client from confirming the login on the server ~~and hide/show the lockscreen on key~~
* <b>Authentication Bypass</b> - Bypasses the server side authentication allowing you to login with any credentials

## Supported Versions
* handyCafe 3.3.21 (21/July/2010)
* handyCafe 4.1.16 (10/August/2016)

## Compiling
<i>If you are using VSCode with the C/C++ extension from microsoft, Open the directory on the editor, press <b>Ctrl + Shift + B</b> to build the project</i>
* Compiler: [MinGW (i686)](https://sourceforge.net/projects/mingw-w64/)
* mingw args  (Release standalone build): <i>-static -Ofast -v -mwindows -lpsapi -lversion</i>
* Platform: x86
* Main file: <b>[pkhandycafe.cpp](https://github.com/rogueeeee/pk_handycafe/blob/master/pkhandycafe.cpp)</b>
* Character set: Multi-byte

## Note
* When compiling with VSCode you might need to retarget the path in </b>[task.json](https://github.com/rogueeeee/pk_handycafe/blob/master/.vscode/tasks.json)</b>

* Patch table for HandyCafe 4.1.16 (latest handyCafe version) is not included
in the repo, define <b>[PKHC_DISABLE_SUPPORT_NEW](https://github.com/rogueeeee/pk_handycafe/blob/master/pkhandycafe.h#L4)</b> in <b>pkhandycafe.h</b>
to prevent errors on compilation. By default, this release uses the <b>patchtable_4116_dummy.h</b>

* ~~Patch table for the No authentication feature is not included
in the repo, define <b>[PKHC_DISABLE_AUTHENTICATION_BYPASS](https://github.com/rogueeeee/pk_handycafe/blob/master/pkhandycafe.h#L5)</b> in <b>pkhandycafe.h</b>
to prevent errors on compilation. By default, this release uses the <b>patchtable_noauth_dummy.h~~</b>

* Support for 4.1.16 ~~and No authentication~~ features are intentionally disabled and excluded from the repository.

## License
MIT