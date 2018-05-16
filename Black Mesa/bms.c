// gcc -m32 -Wall -Wextra -O3 bms.c -o bms_linux_new -ldl -s -Wl,-rpath,'$ORIGIN/bin'
// setting the RPATH to '$ORIGIN/bin' makes it possible to start the game without "bms.sh"

#include <dlfcn.h>
#include <errno.h>
#include <inttypes.h>
#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef char bool;
#define true 1
#define false 0

#define STRINGIFY(x)  #x
#define GETPROCADDR(handle,type,func,param) \
  typedef type (*func##_t) param; \
  func##_t func = (func##_t) dlsym(handle, STRINGIFY(func));


void print_error(const char *message)
{
  void *sdl = NULL;

  fprintf(stderr, "error: %s\n", message);

  if ((sdl = dlopen("libSDL2-2.0.so.0", RTLD_LAZY)) == NULL) {
    return;
  }

#define DLSYM(type,func,param) \
  GETPROCADDR(sdl,type,func,param) \
  if (dlerror()) { \
    dlclose(sdl); \
    return; \
  }

  DLSYM(int, SDL_Init, (uint32_t))
  DLSYM(int, SDL_ShowSimpleMessageBox, (uint32_t, const char *, const char *, void *))
  DLSYM(void, SDL_Quit, (void))

#undef DLSYM

  if (SDL_Init(32) == 0) {
    SDL_ShowSimpleMessageBox(16, "Error", message, NULL);
    SDL_Quit();
  }

  dlclose(sdl);
}


int main(int argc, char **argv)
{
  char *argv_copy[argc + 2], *self, *copy, *dir, *error;
  void *handle = NULL;
  int rv = 1;


  /* change the current working directory to the exe's path */

  if ((self = realpath("/proc/self/exe", NULL)) == NULL) {
    print_error("realpath() failed: unable to resolve /proc/self/exe\nAre you using an ancient Linux system?");
    return 1;
  }

  copy = strdup(self);
  dir = dirname(copy);

  if (chdir(dir) != 0) {
    const char *format = "chdir() failed: unable to move into the directory `%s'";
    error = malloc(strlen(format) - 1 + strlen(dir));
    sprintf(error, format, dir);
    print_error(error);
    free(error);
    free(copy);
    goto close;
  }
  free(copy);



  /* remove bin/libstdc++.so.6 if it still exists */
  unlink("bin/libstdc++.so.6");



  /* check for running Steam instance; starting the game without Steam
   * running will result in a segmentation fault */

  if ((handle = dlopen("./bin/libsteam_api.so", RTLD_LAZY)) == NULL) {
    print_error("cannot open ./bin/libsteam_api.so");
    goto close;
  }

#define DLSYM(type,func,param) \
  GETPROCADDR(handle,type,func,param) \
  if ((error = dlerror()) != NULL) { \
    print_error(error); \
    goto close; \
  }

  dlerror();
  DLSYM(bool, SteamAPI_IsSteamRunning, (void))

  if (SteamAPI_IsSteamRunning() == false) {
    argv_copy[0] = argv[0];
    argv_copy[1] = "-applaunch";
    argv_copy[2] = "362890";  /* Black Mesa AppID */
    for (int i = 1; i < argc; i++) {
      argv_copy[i + 2] = argv[i];
    }
    argv_copy[argc + 2] = '\0';

    execvp("steam", argv_copy);
    print_error("unable to launch Steam");

    dlclose(handle);
    if (self) {
      free(self);
    }
    _exit(127);
  }

  dlclose(handle);



  /* dlopen() the launcher */

  if ((handle = dlopen("./bin/launcher.so", RTLD_LAZY)) == NULL) {
    print_error("cannot open ./bin/launcher.so");
    goto close;
  }

  dlerror();
  DLSYM(int, LauncherMain, (int, char**))
  printf("launcher.so successfully loaded\n");



  /* launch game with argv[0] set to the resolved exe path;
   * otherwise the game's resources won't be loaded correctly
   * when starting the game from another path */

  for (int i = 1; i < argc; i++) {
    argv_copy[i] = argv[i];
  }
  argv_copy[0] = self;
  argv_copy[argc] = argv_copy[argc + 1] = argv_copy[argc + 2] = '\0';

  rv = LauncherMain(argc, argv_copy);


close:
  if (handle) {
    dlclose(handle);
  }
  if (self) {
    free(self);
  }
  return rv;
}

