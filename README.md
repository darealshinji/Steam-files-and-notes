A collection of notes, configurations and other files for my Steam games.

Linux
=====

auto login issues
-----------------
If auto-login doesn't work on Linux, delete or rename all directories or symlinks in your home directory
that contain the name `steam` (case-insensitive). If you have changed the access rights of `~/.steam` you
can delete this directory. Normally it contains basically only symbolic links and should be recreated
on the next launch of Steam.

libsteam_api.so
---------------
In rare cases a game might be missing libsteam_api.so.
Note that the correct soname of `libsteam_api64.so` is `libsteam_api.so`.
libCSteamworks binaries can be downloaded at https://github.com/rlabrecque/CSteamworks/releases

Steam or one of the games won't start
-------------------------------------
Some of libraries from the Steam Runtime can cause imcompatibility issues, resulting in a game or even the Steam client not starting.
Run the following command to find and delete those libraries:
``` sh
find ~/.steam/ \( -name "libgcc_s.so*" -o -name "libstdc++.so*" -o -name "libxcb.so*" -o -name "libgpg-error.so*" \) -print -delete
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


Windows
=======

remove-uninstall-links.bat
--------------------------
Removes uninstall entries of Steam games from _Programs and Features_.

