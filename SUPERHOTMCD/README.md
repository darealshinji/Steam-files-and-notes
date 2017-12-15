AppID: `690040`

Linux
-----
You can download and install `SUPERHOT: MIND CONTROL DELETE` the following way on Linux:
``` sh
# install steamcmd
sudo apt install steamcmd

# download SUPERHOTMCD for Windows:
# USERNAME = Steam username; PASSWORD = Steam password
steamcmd +login USERNAME PASSWORD +@sSteamCmdForcePlatformType windows +force_install_dir /tmp/SUPERHOTMCD +app_update 690040 validate +quit
mv /tmp/SUPERHOTMCD .
cd SUPERHOTMCD

# download and install Linux binaries to run the game
name="UnitySetup-Linux-Support-for-Editor-5.6.2p1"
wget https://beta.unity3d.com/download/8a29de46e0a0/TargetSupportInstaller/${name}.exe
7z x ${name}.exe -o$name
cp -rv $name/*/Variations/linux64_headless_development_mono/Data/Mono/x86_64 SHMCD_Data/Mono/
cp -rv $name/*/Variations/linux64_withgfx_development_mono/Data/Plugins/x86_64 SHMCD_Data/Plugins/
cp -v $name/*/Variations/linux64_withgfx_nondevelopment_mono/LinuxPlayer SHMCD.x86_64
chmod a+x SHMCD.x86_64
rm -rf $name ${name}.exe

# if you want a picture for the screen selector window
wget http://cdn.edgecast.steamstatic.com/steam/apps/690040/header.jpg
convert header.jpg SHMCD_Data/ScreenSelector.png

# start the game
./SHMCD.x86_64 -show-screen-selector
```
