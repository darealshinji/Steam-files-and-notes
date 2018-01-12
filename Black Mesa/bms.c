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
  char self[PATH_MAX] = {0};
  char *argv_copy[argc];
  void *handle;
  char *error;
  bool (*pSteamAPI_IsSteamRunning) (void);
  int (*pLauncherMain) (int, char**);


  /* change the current working directory to the exe's path */

  ssize_t ssize = readlink("/proc/self/exe", self, PATH_MAX);

  if (ssize < 1) {
    fprintf(stderr, "error: readlink() failed; unable to resolve /proc/self/exe\n");
    return 1;
  }

  char *copy = strdup(self);
  char *dir = dirname(copy);

  if (chdir(dir) != 0) {
    fprintf(stderr, "error: chdir() failed; unable to move into the directory `%s'\n", dir);
    free(copy);
    return 1;
  }
  free(copy);


  /* rename bin/libstdc++.so.6 to only use the system C++ library */

  const char *lib = "bin/libstdc++.so.6";
  const char *dest = "bin/libstdc++.so.6.old";

  if (access(lib, F_OK) == 0) {
    printf("renaming `%s' to `%s'\n", lib, dest);
    if (rename(lib, dest) == -1) {
      int errsv = errno;
      fprintf(stderr, "error: moving `%s' failed: %s\n", lib, strerror(errsv));
      //return 1;
    }
  }


  /* check for running Steam instance; starting the game without Steam
   * running will result in a segmentation fault */

  handle = dlopen("./bin/libsteam_api.so", RTLD_LAZY);

  if (!handle) {
    fprintf(stderr, "error: %s\n", dlerror());
    return 1;
  }

  dlerror();
  *(void **) (&pSteamAPI_IsSteamRunning) = dlsym(handle, "SteamAPI_IsSteamRunning");
  error = dlerror();

  if (error) {
    fprintf(stderr, "error: %s\n", error);
    dlclose(handle);
    return 1;
  }

  if (pSteamAPI_IsSteamRunning() == false) {
    fprintf(stderr, "error: SteamAPI_IsSteamRunning() failed; unable to locate a running instance of Steam\n");
    dlclose(handle);
    return 1;
  }

  dlclose(handle);


  /* dlopen() the launcher */

  handle = dlopen("./bin/launcher.so", RTLD_LAZY);

  if (!handle) {
    fprintf(stderr, "error: %s\n", dlerror());
    return 1;
  }

  dlerror();
  *(void **) (&pLauncherMain) = dlsym(handle, "LauncherMain");
  error = dlerror();

  if (error) {
    fprintf(stderr, "error: %s\n", error);
    dlclose(handle);
    return 1;
  }


  /* launch game with argv[0] set to the resolved exe path;
   * otherwise the game's resources won't be loaded correctly
   * when starting the game from another path */

  argv_copy[0] = strdup(self);

  for (int i = 1; i < argc; i++) {
    argv_copy[i] = strdup(argv[i]);
  }
  argv_copy[argc] = '\0';

  int rv = pLauncherMain(argc, argv_copy);
  dlclose(handle);

  for (int i = 0; i < argc; i++) {
    free(argv_copy[i]);
  }

  return rv;
}

