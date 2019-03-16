// gcc -m32 -Wall -O3 hl2_launcher_linux.c -o hl2_linux -ldl -s -Wl,-rpath,'$ORIGIN/bin'
// Linking with RPATH set to '$ORIGIN/bin' is important!

#include <dlfcn.h>
#include <libgen.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef int (*LauncherMain_t)(int, char**);

int main(int argc, char *argv[])
{
  char *self, *dn, *error;
  void *hinstLauncher;
  LauncherMain_t pLauncherMain;
  int resultLauncherMain;

  if ((self = realpath("/proc/self/exe", NULL)) == NULL) {
    perror("realpath()");
    return 1;
  }

  dn = dirname(self);
  free(self);

  if (chdir(dn) != 0) {
    perror("chdir()");
    return 1;
  }

  if ((hinstLauncher = dlopen("./bin/launcher.so", RTLD_LAZY)) == NULL) {
    fprintf(stderr, "error: %s\n", dlerror());
    return 1;
  }

  dlerror();
  pLauncherMain = dlsym(hinstLauncher, "LauncherMain");

  if ((error = dlerror()) != NULL) {
    fprintf(stderr, "error: %s\n", error);
    dlclose(hinstLauncher);
    return 1;
  }

  resultLauncherMain = pLauncherMain(argc, argv);

  if (dlclose(hinstLauncher) != 0) {
    fprintf(stderr, "error: %s\n", dlerror());
    return 1;
  }

  return resultLauncherMain;
}

