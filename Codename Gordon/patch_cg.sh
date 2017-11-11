#!/bin/bash
set -e
set -x

sudo apt install dos2unix patch unzip wget dmg2img p7zip-full steamcmd:i386 openjdk-8-jre-headless

set +x

cgdir="/tmp/cg"
ffdec="java -jar ffdec.jar"

read -p "Steam username: " username
read -s -p "Steam password: " password
echo ""
echo "steamcmd +login $username \$password +@sSteamCmdForcePlatformType windows +force_install_dir $cgdir +app_license_request 92 +app_update 92 validate +quit"

rm -rf $cgdir
steamcmd +login $username $password +@sSteamCmdForcePlatformType windows +force_install_dir $cgdir +app_license_request 92 +app_update 92 validate +quit

set -x

mkdir codename_gordon
cd codename_gordon

wget -c "https://www.free-decompiler.com/flash/download/ffdec_10.0.0.zip"
unzip ffdec_10.0.0.zip -d ffdec
cd ffdec

$ffdec -cli -extract $cgdir/cg.exe -o cg.swf biggest
$ffdec -cli -swf2xml cg.swf cg.xml
cp ../../data/swf.xml.diff .
dos2unix cg.xml swf.xml.diff
patch -p2 cg.xml swf.xml.diff
$ffdec -cli -xml2swf cg.xml ../cg.swf
$ffdec -cli -xml2swf ../../data/cg_version.swf.xml ../cg_version.swf

cd ..
rm -rf ffdec ffdec_10.0.0.zip
cp -r ../data .

cd data
mv ../*.swf .
mv cg.bat cg.sh ..
cp $cgdir/*.xml .
rm cg_victims.xml

for lang in English French German Italian Japanese Korean SChinese Spanish TChinese; do
  mv dialogs_${lang,,}.xml dialogs_${lang}.xml
done

url="https://fpdownload.macromedia.com/pub/flashplayer/updaters/27"
wget -c "$url/flash_player_sa_linux.x86_64.tar.gz"
wget -c "$url/flashplayer_27_sa.exe"
wget -c "$url/flashplayer_27_sa.dmg"

mv flashplayer_27_sa.exe flashplayer.exe
tar xf flash_player_sa_linux.x86_64.tar.gz
mv flashplayer flashplayer_linux
dmg2img -i flashplayer_27_sa.dmg -o flashplayer.img
7z x flashplayer.img
mv "Flash Player/Flash Player.app/Contents/MacOS/Flash Player" flashplayer_mac
rm -rf flash_player_sa_linux.x86_64.tar.gz flashplayer_27_sa.dmg flashplayer.img "Flash Player"

chmod a+x flashplayer_linux flashplayer_mac ../cg.sh


