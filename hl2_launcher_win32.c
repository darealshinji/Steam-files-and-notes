/* HL2 launcher for Windows (hl2.exe) */

// windres hl2.res hl2_res.o
// gcc -m32 -Wall -O3 -mwindows hl2_launcher_win32.c -o hl2.exe hl2_res.o -s

// cl /Ox /EHsc /GS /guard:cf hl2_launcher_win32.c /link /out:hl2.exe hl2.res user32.lib

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 4096
#define LONG_MAX_PATH 32767

typedef int (*LauncherMain_t)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

static void show_error_message(int errCode, const char *title, const char *str)
{
  int rv;
  char buf[BUFSIZE];
  char err[BUFSIZE];

  rv = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
                      NULL,
                      errCode,
                      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                      buf,
                      sizeof(buf),
                      NULL);

  if (rv == 0) {
    _snprintf_s(err, sizeof(err), _TRUNCATE, "%s\n\nerror code %ld", str, errCode);
  } else {
    _snprintf_s(err, sizeof(err), _TRUNCATE, "%s\n\n%s", str, buf);
  }

  MessageBoxA(NULL, err, title, MB_ICONERROR|MB_OK);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  const char *title = "Launcher Error";
  char modulePath[LONG_MAX_PATH];
  char *p, *env, *path;
  size_t len, modulePathLen;
  HINSTANCE hinstLauncher;
  LauncherMain_t pLauncherMain;
  int resultLauncherMain;

  // get exe path
  if (!GetModuleFileNameA(hInstance, modulePath, sizeof(modulePath))) {
    show_error_message(GetLastError(), title, "Failed calling GetModuleFileName():");
    return 1;
  }

  // get dirname
  p = strrchr(modulePath, '\\');
  if (!p) {
    MessageBoxA(NULL, "Cannot get executable path!", title, MB_ICONERROR|MB_OK);
    return 1;
  }
  *p = 0;
  modulePathLen = strlen(modulePath);

  // add .\bin to PATH
  env = getenv("PATH");
  len = modulePathLen + strlen(env) + 6;
  path = malloc(len);
  _snprintf_s(path, len, _TRUNCATE, "%s\\bin;%s", modulePath, env);
  _putenv_s("PATH", path);

  // load launcher.dll
  len = strlen(modulePath) + 18;
  path = realloc(path, len);
  _snprintf_s(path, len, _TRUNCATE, "%s\\bin\\launcher.dll", modulePath);

  hinstLauncher = LoadLibraryExA(path, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
  free(path);

  if (!hinstLauncher) {
    show_error_message(GetLastError(), title, "Failed to load launcher.dll:");
    return 1;
  }

  // call LauncherMain()
  pLauncherMain = (LauncherMain_t) GetProcAddress(hinstLauncher, "LauncherMain");
  resultLauncherMain = pLauncherMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

  if (FreeLibrary(hinstLauncher) == 0) {
    show_error_message(GetLastError(), title, "Failed to free launcher.dll:");
    return 1;
  }

  return resultLauncherMain;
}

