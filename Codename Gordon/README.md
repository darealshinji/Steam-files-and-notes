AppID: `92`

Codename Gordon can still be installed for free using the Steam URL `steam://install/92` or `steamcmd`.

Linux
-----

The embedded SWF file can be extracted with `cat cg.exe | tail -c+1198770 > cg.swf`.
MD5 checksum of cg.swf is `f3930ac0e48d5ad38e612f5acff04f3f`.

You can get a stand-alone Flash player (Flash Player Projector) directly from [Adobe](http://www.adobe.com/support/flashplayer/debug_downloads.html).

To enable dialogs you must replace the content of `cg_languages.xml` with:
``` XML
<languages>
<language>mylanguage</language>
</languages>
```
`mylanguage` must be the language code used in the `dialogs_*.xml` filename, i.e. `tchinese` or `english` (lowercase!).

![Codename Gordon on Linux](screenshot.jpg)

