AppID: `12130`

There are several patches available to make the game work correctly on modern
Windows systems and to fix other issues.

These are the ones that I use:

* Re-linking `manhunt.exe` (extract files and run `Manhunt Fix.bat`):
https://www.dropbox.com/s/hqzb2y7t3kfpueg/Manhunt%20Fix.zip?dl=1

* Widescreen fix:
https://thirteenag.github.io/wfp#manhunt<br>
Note: user files will now be stored in `steamapps/common/Manhunt/0/`

* Using DirectX 9 (d3d8.dll pseudo-driver):
https://github.com/crosire/d3d8to9/releases

* Looping sound issues:
delete or rename `audio\PC\SCRIPTED\CRAPPER\CRAPPER.RIB` and `audio\PC\SCRIPTED\PORN\PORN.RIB`

