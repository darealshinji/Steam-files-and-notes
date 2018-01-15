AppID: `622650`

Bug fixes on Linux
------------------
Add `-screen-fullscreen 0` to the launch options to fix the fullscreen bug (black screen after start).

To prevent further creashes, download the missing `libCSteamworks.so` and `libsteam_api.so` files  by
running the following commands in a terminal (requires `unzip` and `wget` to be installed):
``` sh
wget https://partner.steamgames.com/downloads/steamworks_sdk_142.zip
wget https://github.com/rlabrecque/CSteamworks/releases/download/v1.30-1.40/CSteamworks-v1.30-1.40.zip
mkdir -p BATIM_Data/Plugins/x86 BATIM_Data/Plugins/x86_64
unzip -j steamworks_sdk_142.zip sdk/redistributable_bin/linux32/libsteam_api.so -d BATIM_Data/Plugins/x86/
unzip -j steamworks_sdk_142.zip sdk/redistributable_bin/linux64/libsteam_api.so -d BATIM_Data/Plugins/x86_64/
unzip -j CSteamworks-v1.30-1.40.zip x86/libCSteamworks.so -d BATIM_Data/Plugins/x86/
unzip -j CSteamworks-v1.30-1.40.zip x86_64/libCSteamworks.so -d BATIM_Data/Plugins/x86_64/
```
Then copy or move the created `BATIM_Data` directory into the `Bendy and the Ink Machine` game directory.

