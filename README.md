A collection of notes, configurations and other files for my Steam games.

Linux
=====
You can download the Windows version of a game on Linux using steamcmd (install it using your package manager):
``` sh
steamcmd +login USERNAME [PASSWORD] +@sSteamCmdForcePlatformType windows +force_install_dir DESTINATION +app_license_request APPID +app_update APPID validate +quit
```
You can omit the `+app_license_request APPID` for a game that you already own.
Use `+@sSteamCmdForcePlatformType macos` to download the macOS version of a game.

 * USERNAME PASSWORD: your username and password (password needs to be added only once)
 * DESTINATION: full destination path without spaces in names, i.e. `$HOME/Half-Life_2_(Windows)`
 * APPID: the AppID of the game, i.e. 220 for Half-Life²

Steam or one of the games won't start
-------------------------------------
Some of libraries from the Steam Runtime can cause imcompatibility issues, resulting in a game or even the Steam client not starting.
Run the following command to find and delete those libraries:
``` sh
find ~/.steam/root/ \( -name "libgcc_s.so*" -o -name "libstdc++.so*" -o -name "libxcb.so*" -o -name "libgpg-error.so*" \) -print -delete
```

Useful environment variables
----------------------------
``` sh
# disable steam-runtime
export STEAM_RUNTIME=0

# Workaround for dbus fatal termination related coredumps (SIGABRT)
# https://github.com/ValveSoftware/steam-for-linux/issues/4464
export DBUS_FATAL_WARNINGS=0

# force minimizing on close; temporary workaround for trayicon issues
# https://github.com/ValveSoftware/steam-for-linux/issues/4812
export STEAM_FRAME_FORCE_CLOSE=0
```

Native Runtime
--------------
On Debian/Ubuntu you can build a package with a "native runtime launcher" like this:
``` sh
git clone https://github.com/darealshinji/debian-packaging
cd debian-packaging/games/steam-native
make PBUILDER=0
```

libgcrypt.so.11
---------------
Add `libgcrypt.so.11` to the _bin_ directory of Source/Goldsource engine games to play with Steam Runtime disabled.

libsteam_api.so
---------------
In rare cases a game might be missing libsteam_api.so.
Note that the correct soname of `libsteam_api64.so` is `libsteam_api.so`.
libCSteamworks binaries can be downloaded at https://github.com/rlabrecque/CSteamworks/releases

registry.vdf
------------
If auto-login doesn't work on Linux, set correct username, language and sourcemod path in `registry.vdf`,
replace the original file in `~/.steam/` and mark the file as read-only.

Windows
=======

remove-uninstall-links.bat
--------------------------
Removes uninstall entries of Steam games from _Programs and Features_.

