#!/bin/bash
# This script was written to be used on a 32 bit Ubuntu 14.04 system.

function write_script() {
  cat <<EOF> $1
#!/bin/sh -e
cd "\$(dirname "\$0")"
export LD_LIBRARY_PATH="\$PWD:\$LD_LIBRARY_PATH"
export PATH="\$PWD:\$PATH"
cd ../gameroot/
dosbox -conf dosbox_swarrior.conf -conf $2
EOF
  chmod a+x $1
}

set -e
set -x

sudo apt-get install --no-install-recommends wget rpm2cpio subversion \
  build-essential pkg-config autoconf automake \
  libasound2-dev libglu1-mesa-dev libsdl1.2-dev libsdl-net1.2-dev libvorbis-dev

mkdir build
cd build

BUILD="$PWD"
JOBS=4

# build from source - less dependencies
wget -c "http://archive.ubuntu.com/ubuntu/pool/universe/s/sdl-sound1.2/sdl-sound1.2_1.0.3.orig.tar.gz"
tar xf sdl-sound1.2_1.0.3.orig.tar.gz
cd SDL_sound-1.0.3/
./configure --prefix="$BUILD/usr"
make -j$JOBS
make install
cd ..

svn checkout "https://svn.code.sf.net/p/dosbox/code-0/dosbox/trunk" dosbox-svn
cd dosbox-svn
autoreconf -if
CPPFLAGS="-I$BUILD/usr/include/SDL" \
CFLAGS="-O2 -I$BUILD/usr/include/SDL" \
LDFLAGS="-L$BUILD/usr/lib" \
  ./configure
make -j$JOBS
cd ..

# old rpm releases with less dependencies
wget -c "https://www.libsdl.org/release/SDL-1.2.15-1.i386.rpm"
rpm2cpio SDL-1.2.15-1.i386.rpm | cpio -idm
wget -c "https://www.libsdl.org/projects/SDL_net/release/SDL_net-1.2.8-1.i386.rpm"
rpm2cpio SDL_net-1.2.8-1.i386.rpm | cpio -idm

mkdir bin-linux-i386
cd bin-linux-i386
cp ../dosbox-svn/src/dosbox .
# use readelf, objdump or ldd to track dependencies
cp ../usr/lib/libSDL-1.2.so.0 .
cp ../usr/lib/libSDL_net-1.2.so.0 .
cp ../usr/lib/libSDL_sound-1.0.so.1 .
cp /usr/lib/i386-linux-gnu/libvorbis.so.0 .
cp /usr/lib/i386-linux-gnu/libvorbisfile.so.3 .
cp /usr/lib/i386-linux-gnu/libogg.so.0 .
cp /lib/i386-linux-gnu/libpng12.so.0 .
cp /lib/i386-linux-gnu/libz.so.1 .

strip *

cd ../dosbox-svn
LANG=C svn info | grep -v '^Working Copy Root Path:' > SVN_INFO
make distclean
rm -rf .svn autom4te.cache
cd ..
tar cvfJ dosbox-svn.tar.xz dosbox-svn
mv dosbox-svn.tar.xz bin-linux-i386

cd bin-linux-i386
echo "Move this directory to \"steamapps/common/Shadow Warrior Original\"" > INSTALL
cp "$BUILD/../$(basename "$0")" .
chmod a-x "$(basename "$0")"

# write start-up scripts
write_script run_betas.sh dosbox_swarrior_client_betas.conf
write_script run_single_player.sh dosbox_swarrior_single.conf

