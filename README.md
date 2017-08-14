A collection of notes, configurations and other files for my Steam games.

Linux
-----
You can download the Windows version of a game on Linux using steamcmd (install it using your package manager):
```
steamcmd +login USERNAME PASSWORD +@sSteamCmdForcePlatformType windows +force_install_dir DESTINATION +app_license_request APPID +app_update APPID validate +quit
```

 * USERNAME PASSWORD: your username and password
 * DESTINATION: full destination path without spaces in names, i.e. `$HOME/Half-Life_2_(Windows)`
 * APPID: the AppID of the game, i.e. 220 for Half-Life 2

libgcrypt.so.11
---------------
Add libgcrypt.so.11 to the _bin_ directory of Source/Goldsource engine games to play with Steam Runtime disabled.

registry.vdf
------------
If auto-login doesn't work on Linux, set correct username, language and sourcemod path in `registry.vdf`,
replace the original file in `~/.steam/` and mark the file as read-only.

remove-uninstall-links.bat
--------------------------
Removes uninstall entries of Steam games from _Programs and Features_.

