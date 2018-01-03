AppID: `210770`

Native Runtime
--------------
To play with disabled steam-runtime, copy `libSDL2-2.0.so.0` from
the amd64 steam-runtime (`~/.steam/steam/ubuntu12_32/steam-runtime/amd64`)
into `Binaries/linux-amd64`:
``` sh
cp -vf "$HOME/.steam/steam/ubuntu12_32/steam-runtime/amd64/usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0" Binaries/linux-amd64
```
