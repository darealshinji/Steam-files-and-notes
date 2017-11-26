AppID: `290930`

If _Half-Life 2: Update_ is censored start the game without Steam running in background.
Run `Half-Life 2 Update/hl2.exe` or `Half-Life 2 Update/hl2.sh` to start the game.

Alternatively you can put `preload.so` into the `Half-Life 2 Update` directory and set
the game's launch options to `LD_PRELOAD=./preload.so %command%`.
This will disable SteamAPI features but the game is uncut even if Steam is running.

On Windows you can run `patch_steam_api.exe` inside the `Half-Life 2 Update` directory
to patch `steam_api.dll` (make sure to keep a backup of the original file).
