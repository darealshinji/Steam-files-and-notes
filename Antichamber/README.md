AppID: `219890`


Skip Intro
----------

Delete or rename `UDKGame\Movies\UE3_logo.bik`.


Windows
-------

You can change the entry name in the installed software list to "Antichamber" manually in the registry by editing
the `DisplayName` entry in `HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\UDK-XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX`.

The X's in the path are a GUID which can be found in the file `Antichamber\Binaries\InstallInfo.xml`

If you want the entry to be invisible, create a new DWORD entry with the name `WindowsInstaller` and the value `1`.

