AppID: `361990`

Linux
=====

Here are instructions how to install and play Lakeview Cabin Collection natively on Linux.
You need `steamcmd` and `wget` (install them with your package manager).

First download the macOS version (the Windows version won't work):
``` sh
steamcmd +login USERNAME PASSWORD +@sSteamCmdForcePlatformType macos +force_install_dir $HOME/LVC-tmp +app_update 361990 validate +quit
```
Replace `USERNAME` and `PASSWORD` with your __Steam__ account name and password.
The installation directory (`$HOME/LVC-tmp` in this case) has to be an absolute path and mustn't contain any spaces!

Move to the new directory and create a Linux version from the game files:
``` sh
cd $HOME/LVC-tmp
wget https://github.com/darealshinji/UnityEngine2deb/archive/master.tar.gz -O- | tar xfz -
./UnityEngine2deb-master/copyunityengine -y LakeviewCabinCollection.app
cd -
cp -vf UnityPlayer.png "$HOME/LVC-tmp/LvC Collection-Linux/LvC Collection_Data/Resources"
cp -vf ScreenSelector.png "$HOME/LVC-tmp/LvC Collection-Linux/LvC Collection_Data"
echo "361990" > "$HOME/LVC-tmp/LvC Collection-Linux/steam_appid.txt"
```

Note: the game sometimes crashes on start.


Windows
=======

To get a banner image for the screen selector copy `ScreenSelector.bmp` into `steamapps/common/Lakeview Cabin Collection/Lakeview Cabin Collection_Data`.

