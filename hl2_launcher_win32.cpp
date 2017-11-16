/* HL2 launcher for Windows (hl2.exe) */

// windres hl2.res hl2_res.o
// g++ -m32 -Wall -O3 -mwindows hl2_launcher_win32.cpp -o hl2.exe hl2_res.o -s

// cl /Ox /EHsc /GS /guard:cf hl2_launcher_win32.cpp /link /out:hl2.exe hl2.res user32.lib

#include <windows.h>
#include <stdlib.h>
#include <string>

typedef int (*LauncherMain_t)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  LPCTSTR title = "Launcher Error";
  UINT type = MB_ICONERROR | MB_OK;

  char moduleName[MAX_PATH];
  char moduleRootDrive[_MAX_DRIVE];
  char moduleRootDir[_MAX_DIR];
  std::string dirname, path, dll;

  HINSTANCE hinstLauncher;
  LauncherMain_t pLauncherMain;
  int resultLauncherMain;

  if (!GetModuleFileName(hInstance, moduleName, MAX_PATH))
  {
    MessageBox(0, "Failed calling GetModuleFileName()", title, type);
    return 1;
  }

  if (_splitpath_s(moduleName, moduleRootDrive, _MAX_DRIVE, moduleRootDir, _MAX_DIR, NULL, 0, NULL, 0) != 0)
  {
    MessageBox(0, "Failed calling _splitpath_s()", title, type);
    return 1;
  }

  dirname = std::string(moduleRootDrive) + "\\" + std::string(moduleRootDir);

  path = "PATH=" + dirname + "\\bin;" + std::string(getenv("PATH"));
  _putenv(path.c_str());

  dll = dirname + "\\bin\\launcher.dll";
  hinstLauncher = LoadLibraryEx(dll.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

  if (!hinstLauncher)
  {
    char *errmsg;

    if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                      NULL,
                      GetLastError(),
                      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                      (LPSTR) &errmsg,
                      0,
                      NULL))
    {
      std::string msg = "Failed to load launcher.dll:\n\n" + std::string(errmsg);
      MessageBox(0, msg.c_str(), title, type);
      LocalFree(errmsg);
    }

    return 1;
  }

  pLauncherMain = (LauncherMain_t) GetProcAddress(hinstLauncher, "LauncherMain");
  resultLauncherMain = pLauncherMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

  FreeLibrary(hinstLauncher);
  return resultLauncherMain;
}

