AppID: `57300`

Linux
-----

If neither the game nor the launcher can be started from the Steam client, try to
set the environment variable `LC_ALL` in your game's launch options to something
available on your system, i.e.: `LC_ALL=en_GB.UTF8 %command%`

You can enter `locale` in a shell to see how they're currently set on your
system or `locale -a` to get a list of all that are alternatively available.
Note that `C`, `C.UTF8` and `POSIX` don't seem to work.

