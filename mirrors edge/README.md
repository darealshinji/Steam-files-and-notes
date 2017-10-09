AppID: `17410`

Disable intro movie
-------------------
Simply remove `TdGame/Movies/StartupMovie.bik` from the game directory.

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
