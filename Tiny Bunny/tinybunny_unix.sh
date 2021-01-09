#!/bin/sh
set -e
set -x

gamedir="Tiny Bunny"
sdkver="7.3.5"

if [ "$(printf "$PWD" | tail -c28)" = "/steamapps/common/Tiny Bunny" ]; then
  gamedir="."
fi

if [ -f "$gamedir/game/script_version.txt" ]; then
  sdkver=$(sed 's|,|.|'g "$gamedir/game/script_version.txt" | tr -d -c '0-9.')
fi

mkdir -p "$gamedir/lib"
cd "$gamedir"

#wget https://www.renpy.org/dl/$sdkver/renpy-${sdkver}-sdk.tar.bz2
wget https://archive.org/download/renpy-${sdkver}-sdk/renpy-${sdkver}-sdk.tar.bz2
tar xf renpy-${sdkver}-sdk.tar.bz2

# move files
mv renpy-${sdkver}-sdk/renpy.sh TinyBunny.sh
mv renpy-${sdkver}-sdk/lib/linux-i686 lib/
mv renpy-${sdkver}-sdk/lib/linux-x86_64 lib/
mv renpy-${sdkver}-sdk/lib/darwin-x86_64 lib/

# rename binaries
mv lib/linux-i686/renpy lib/linux-i686/TinyBunny
mv lib/linux-x86_64/renpy lib/linux-x86_64/TinyBunny
mv lib/darwin-x86_64/renpy lib/darwin-x86_64/TinyBunny

# download SteamAPI libraries (taken from https://partner.steamgames.com/)
wget -O lib/linux-i686/libsteam_api.so https://github.com/darealshinji/Steam-files-and-notes/raw/master/libsteam_api.so
wget -O lib/linux-x86_64/libsteam_api.so https://github.com/darealshinji/Steam-files-and-notes/raw/master/libsteam_api64.so
wget -O lib/darwin-x86_64/libsteam_api.dylib https://github.com/darealshinji/Steam-files-and-notes/raw/master/libsteam_api.dylib

# delete
rm renpy-${sdkver}-sdk.tar.bz2
rm -rf renpy-${sdkver}-sdk
