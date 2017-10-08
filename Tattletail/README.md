AppID: `568090`

Linux
=====

Here are instructions how to install and play Tattletail natively on Linux.
You need `steamcmd` and `wget` (install them with your package manager).

First download the macOS version (the Windows version won't work):
``` sh
steamcmd +login USERNAME PASSWORD +@sSteamCmdForcePlatformType macos +force_install_dir $HOME/Tattletail-tmp +app_update 568090 validate +quit
```
Replace `USERNAME` and `PASSWORD` with your __Steam__ account name and password.
The installation directory (`$HOME/Tattletail-tmp` in this case) has to be an absolute path and mustn't contain any spaces!

Move to the new directory and create a Linux version from the game files:
``` sh
cd $HOME/Tattletail-tmp
wget https://github.com/darealshinji/UnityEngine2deb/archive/master.tar.gz -O- | tar xfz -
./UnityEngine2deb-master/copyunityengine -y tattletailMac.app
cd -
cp -vf UnityPlayer.png $HOME/Tattletail-tmp/Tattletail-Linux/Tattletail_Data/Resources
```

Note: it seems like changes in the settings are only saved after you've started a level.

prefs
-----
Copy `prefs` into the directory `~/.config/unity3d/Waygetter Electronics/Tattletail` to
unlock all eggs, level selection and some other things.


Windows
=======

tattletail.reg
--------------
Windows registry file to unlock all eggs, level selection and other things.
Values were taken from [reddit](https://www.reddit.com/r/Tattletail/comments/5sbk9o/recently_made_a_discovery_on_the_save_game/).

