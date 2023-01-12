AppID: `17410`

Skip Intro
----------
Delete or rename `mirrors edge/TdGame/Movies/StartupMovie.bik` or use the settings
from the provided config files.

Disable NVidia PhysX installation
---------------------------------
Copy `17410_install.vdf` into the game directory or remove the following lines from the original file:
``` json
		"PhysX Version"
		{
			"HasRunKey"		"HKEY_LOCAL_MACHINE\\SOFTWARE\\AGEIA Technologies"
			"process 1"		"%INSTALLDIR%\\PhysX\\PhysX_SystemSoftware.exe"
			"NoCleanUp"		"1"
			"MinimumHasRunValue"		"81017"
		}
```

Use latest system PhysX
-----------------------
- inside `mirrors edge/Binaries` delete the `PhysXLocal` directory and the files `PhysXCore.dll` and `PhysXDevice.dll`
- enable to always use PhysX through video card in NVidia settings

Change FOV
----------
In `C:\Users\<user>\Documents\EA Games\Mirror's Edge\TdGame\Config\TdInput.ini`
add the following below the line `bEnableMouseSmoothing=true`
``` ini
Bindings=(Name="ONE",Command="FOV 90",Control=False,Shift=False,Alt=False)
Bindings=(Name="TWO",Command="FOV 95",Control=False,Shift=False,Alt=False)
Bindings=(Name="THREE",Command="FOV 100",Control=False,Shift=False,Alt=False)
Bindings=(Name="FOUR",Command="FOV 105",Control=False,Shift=False,Alt=False)
Bindings=(Name="FIVE",Command="FOV 110",Control=False,Shift=False,Alt=False)
```
