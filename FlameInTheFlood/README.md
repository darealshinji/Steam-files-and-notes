AppID: `318600`

To rebind keys copy `Input.ini` into `C:\Users\<USERNAME>\AppData\Local\RiverGame\Saved\Config\WindowsNoEditor`
and edit it accordingly.

The `Input.ini` file contains all the default bindings.
You only need to remap keys that you want to change, for example if you want to bind "toggle inventory"
to the tabulator key, the file's content should be just like this:
``` ini
[/script/engine.inputsettings]
ActionMappings=(ActionName="InventoryToggle",Key=Tab,bShift=False,bCtrl=False,bAlt=False,bCmd=False)
```

Directional movements can also be remapped to support AZERTY keyboard layouts.

PS: keep a backup just in case the game overwrites the content.

