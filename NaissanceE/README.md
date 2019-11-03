AppID: `265690`


Skip Intro
----------

Delete or rename `UDKGame\Movies\UE3_logo.bik`.


Uninstall Entry
---------------

If you want the entry from installed software list to be invisible, go to the registry
path `HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\UDK-XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX`
and create a new DWORD entry with the name `WindowsInstaller` and the value `1`.

The X's in the path are a GUID which can be found in the file `NaissanceE\Binaries\InstallInfo.xml`


Change FOV
----------

The developer console is already enabled by default. It can be displayed with one of the keys near the enter
key (it differs depending on your layout). You can change the FOV with the command `fov <value>`,
for example `fov 100`.
