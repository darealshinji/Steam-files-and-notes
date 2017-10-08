// gcc -m32 -Wall -O3 hl2_launcher_linux.c -o hl2_linux -ldl -s -Wl,-rpath,'$ORIGIN/bin'
// Linking with RPATH set to '$ORIGIN/bin' is important!

#include <dlfcn.h>
#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

void printError(char *msg)
{
  fprintf(stderr, "error: %s\n", msg);
}

int main(int argc, char **argv)
{
  char buf[PATH_MAX + 1] = {0};
  ssize_t ssize;
  void *handle;
  char *error;
  int rv, rv_dlclose;
  int (*pLauncherMain) (int, char**);

  ssize = readlink("/proc/self/exe", buf, PATH_MAX);

  if (ssize < 1)
  {
    printError("readlink()");
    return 1;
  }

  buf[PATH_MAX] = '\0';

  if (chdir(dirname(buf)) != 0)
  {
    printError("chdir()");
    return 1;
  }

  handle = dlopen("./bin/launcher.so", RTLD_LAZY);

  if (!handle)
  {
    printError(dlerror());
    return 1;
  }

  dlerror();
  *(void **) (&pLauncherMain) = dlsym(handle, "LauncherMain");
  error = dlerror();

  if (error)
  {
    printError(error);
    dlclose(handle);
    return 1;
  }

  rv = (*pLauncherMain)(argc, argv);
  rv_dlclose = dlclose(handle);

  if (rv_dlclose != 0)
  {
    printError(dlerror());
    rv = rv_dlclose;
  }

  return rv;
}

