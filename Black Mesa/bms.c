// gcc -m32 -Wall -Wextra -O3 bms.c -o bms_linux_new -ldl -s -Wl,-rpath,'$ORIGIN/bin'
// setting the RPATH to '$ORIGIN/bin' makes it possible to start the game without "bms.sh"

#include <dlfcn.h>
#include <errno.h>
#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef __cplusplus
typedef char bool;
#define false 0
#define true  1
#endif

int main(int argc, char **argv)
{
  char *argv_copy[argc], *self, *copy, *dir, *error;
  const char *lib, *dest;
  void *handle = NULL;
  int rv = 1;

  bool (*pSteamAPI_IsSteamRunning) (void);
  int (*pLauncherMain) (int, char**);


  /* change the current working directory to the exe's path */

  self = realpath("/proc/self/exe", NULL);

  if (!self) {
    fprintf(stderr, "error: realpath() failed; unable to resolve /proc/self/exe\n");
    return 1;
  }

  copy = strdup(self);
  dir = dirname(copy);

  if (chdir(dir) != 0) {
    fprintf(stderr, "error: chdir() failed; unable to move into the directory `%s'\n", dir);
    free(copy);
    goto close;
  }
  free(copy);


  /* rename bin/libstdc++.so.6 to only use the system C++ library */

  lib = "bin/libstdc++.so.6";
  dest = "bin/libstdc++.so.6.old";

  if (access(lib, F_OK) == 0) {
    printf("renaming `%s' to `%s'\n", lib, dest);
    if (rename(lib, dest) == -1) {
      int errsv = errno;
      fprintf(stderr, "error: moving `%s' failed: %s\n", lib, strerror(errsv));
      //goto close;
    }
  }


  /* check for running Steam instance; starting the game without Steam
   * running will result in a segmentation fault */

  handle = dlopen("./bin/libsteam_api.so", RTLD_LAZY);

  if (!handle) {
    fprintf(stderr, "error: %s\n", dlerror());
    goto close;
  }

  dlerror();
  *(void **) (&pSteamAPI_IsSteamRunning) = dlsym(handle, "SteamAPI_IsSteamRunning");
  error = dlerror();

  if (error) {
    fprintf(stderr, "error: %s\n", error);
    goto close;
  }

  if (pSteamAPI_IsSteamRunning() == false) {
    fprintf(stderr, "error: SteamAPI_IsSteamRunning() failed; unable to locate a running instance of Steam\n");
    goto close;
  }

  dlclose(handle);


  /* dlopen() the launcher */

  handle = dlopen("./bin/launcher.so", RTLD_LAZY);

  if (!handle) {
    fprintf(stderr, "error: %s\n", dlerror());
    goto close;
  }

  dlerror();
  *(void **) (&pLauncherMain) = dlsym(handle, "LauncherMain");
  error = dlerror();

  if (error) {
    fprintf(stderr, "error: %s\n", error);
    goto close;
  }
  printf("launcher.so successfully loaded\n");


  /* launch game with argv[0] set to the resolved exe path;
   * otherwise the game's resources won't be loaded correctly
   * when starting the game from another path */

  for (int i = 1; i < argc; i++) {
    argv_copy[i] = argv[i];
  }
  argv_copy[0] = self;
  argv_copy[argc] = '\0';

  rv = pLauncherMain(argc, argv_copy);

close:
  if (handle) {
    dlclose(handle);
  }
  if (self) {
    free(self);
  }
  return rv;
}

