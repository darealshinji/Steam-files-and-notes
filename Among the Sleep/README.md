AppID: `250620`

Skip intro
----------

To remove the intro sequence from the game, replace `Among The Sleep_Data/sharedassets1.resource`
from the game directory with `Windows/sharedassets1.resource` or `Linux/sharedassets1.resource`.

The Linux file was created like this:
``` sh
mv sharedassets1.resource sharedassets1.resource.orig
mkvmerge --output sharedassets1.resource --webm --no-audio sharedassets1.resource.orig --split duration:200ms --split-max-files 1
mv sharedassets1-001.resource sharedassets1.resource
rm sharedassets1-002.resource
```

The Windows file was created like this:
``` sh
mv sharedassets1.resource sharedassets1.resource.orig
MP4Box -splits 1s sharedassets1.resource.orig -out /tmp/
<crtl + c>
mv /tmp/sharedassets1.resource_001.orig sharedassets1.resource
```

Linux
-----

To launch the 64 bit version of the game, set the following launch options: `"./Among The Sleep.x86_64" #%command%`

If you already have some profile data and want to keep it, you will have to copy it for the 64 bit game.
Launch the 64 bit game once and close it. Then copy `profile.json` from `~/.config/unity3d/Krillbite Studio/Among The Sleep/Default/`
into `~/.config/unity3d/Krillbite Studio/Among The Sleep/<SOME_ID_HERE>/`, replacing the existing file.

