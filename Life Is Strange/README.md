AppID: `290930`

Native Runtime
--------------
To play with disabled steam-runtime, copy the following 64-bit libraries from
the amd64 steam-runtime (`~/.steam/steam/ubuntu12_32/steam-runtime/amd64`)
into `lib/x86_64` or install them through your package manager, if available:
```
libcrypto.so.1.0.0
libgcrypt.so.11
libgnutls.so.26
librtmp.so.0
libSDL2-2.0.so.0
libSDL2_image-2.0.so.0
libSDL2_ttf-2.0.so.0
libssl.so.1.0.0
libtasn1.so.3
```

You can also paste the following into a terminal to copy these files all at once:
``` sh
for lib in libcrypto.so.1.0.0 libgcrypt.so.11 libgnutls.so.26 librtmp.so.0 libSDL2-2.0.so.0 libSDL2_image-2.0.so.0 libSDL2_ttf-2.0.so.0 libssl.so.1.0.0 libtasn1.so.3 ; do \
 find "$HOME/.steam/steam/ubuntu12_32/steam-runtime/amd64" -name $lib -exec cp -v -t "$HOME/.steam/steam/steamapps/common/Life Is Strange/lib/x86_64" '{}' \; ; \
done
```
