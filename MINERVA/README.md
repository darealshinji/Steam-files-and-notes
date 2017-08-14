AppID: `235780`

SourceMod
---------
An installation guide on how to install MINERVA as a sourcemod can be found at http://steamcommunity.com/sharedfiles/filedetails/?id=754991349

Standalone game
---------------
How to install _MINERVA_ as a standalone game on Linux using the _Source SDK Base 2013 Singleplayer_:
``` bash
# download SDK
steamcmd +login USERNAME PASSWORD +force_install_dir $HOME/MINERVA +app_update 243730 validate +quit
# download MINERVA
steamcmd +login USERNAME PASSWORD +@sSteamCmdForcePlatformType windows +force_install_dir $HOME/MINERVA/MINERVA +app_license_request 235780 +app_update 235780 validate +quit

cp -rf metastasis -t $HOME/MINERVA/MINERVA
cp ../libgcrypt.so.11 $HOME/MINERVA/bin
cd $HOME/MINERVA
mv MINERVA/metastasis .
mv sourcetest/bin ep2
rm -rf MINERVA sdktools sourcetest steamapps
```
Start the game with `./hl2.sh -game metastasis`

