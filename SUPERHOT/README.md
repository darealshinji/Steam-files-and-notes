AppID: `322500`

Configure resolution/fullscreen
-------------------------------
Change resolution or fullscreen in `~/.config/unity3d/SUPERHOT_Team/SUPERHOT/prefs`
or use the launch options `-screen-width 1920 -screen-height 1080 -screen-fullscreen 1`

Replay recording
----------------
Enable video recording on Linux in two steps:

1. Get a static ffmpeg build from [here](https://www.johnvansickle.com/ffmpeg/) and save the ffmpeg binary as `SH_Data/FFMPEGEncoding/ffmpeg.exe`

2. Replace `SH_Data/Managed/Assembly-CSharp.dll` and `SH_Data/Managed/Assembly-CSharp-firstpass.dll` with their counterparts from the Windows build

The videos will be saved in `$HOME/.config/unity3d/SUPERHOT_Team/SUPERHOT/Screenshots/Replays`

Launcher
--------
A launcher application like the one used on Windows can be found here: https://github.com/darealshinji/superhot-linux-launcher

