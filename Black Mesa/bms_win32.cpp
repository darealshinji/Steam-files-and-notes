// windres bms.res bms_res.o
// g++ -m32 -Wall -O3 -mwindows bms_win32.cpp -o bms.exe bms_res.o -lshlwapi -s

// cl /Ox /EHsc /GS /guard:cf bms_win32.cpp /link /out:bms.exe bms.res user32.lib advapi32.lib shlwapi.lib

#include <windows.h>
#include <shlwapi.h>
#include <stdlib.h>
#include <string.h>
#include <string>


std::string get_steam_path(std::string rootdir)
{
  HKEY hKey;
  DWORD size;
  char data[1024] = {0};
  char *s;
  std::string str = "";

  if (RegOpenKeyExA(HKEY_CLASSES_ROOT, "steam\\Shell\\Open\\Command", 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
    goto check_rootdir;
  }

  if (RegQueryValueExA(hKey, NULL, NULL, NULL, (LPBYTE)data, &size) != ERROR_SUCCESS) {
    RegCloseKey(hKey);
    goto check_rootdir;
  }

  if (data[0] == '"') {
    s = strtok(data + 1, "\"");
    if (s != NULL) {
      str = std::string(s);
    }
  }

  RegCloseKey(hKey);

  if (str != "" && PathFileExists(str.c_str())) {
    //MessageBox(0, "Path to Steam.exe found in registry", "Info", MB_OK);
    return str;
  }

check_rootdir:

  str = rootdir + "\\..\\..\\..\\Steam.exe";
  if (PathFileExists(str.c_str())) {
    return str;
  }

  str = "C:\\Program Files (x86)\\Steam\\Steam.exe";
  if (PathFileExists(str.c_str())) {
    return str;
  }

  str = "C:\\Program Files\\Steam\\Steam.exe";
  if (PathFileExists(str.c_str())) {
    return str;
  }

  str = "C:\\Steam\\Steam.exe";
  if (PathFileExists(str.c_str())) {
    return str;
  }

  return "";
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  const char *title = "Error";
  UINT type = MB_ICONERROR | MB_OK;
  char moduleName[MAX_PATH];
  char moduleRootDrive[_MAX_DRIVE];
  char moduleRootDir[_MAX_DIR];
  std::string dirname, path, dll;
  HINSTANCE hinstLauncher;
  int resultLauncherMain;

  typedef bool (*SteamAPI_IsSteamRunning_t)(void);
  typedef int (*LauncherMain_t)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
  SteamAPI_IsSteamRunning_t pSteamAPI_IsSteamRunning;
  LauncherMain_t pLauncherMain;


  if (!GetModuleFileName(hInstance, moduleName, MAX_PATH)) {
    MessageBox(0, "Failed calling GetModuleFileName()", title, type);
    return 1;
  }

  if (_splitpath_s(moduleName, moduleRootDrive, _MAX_DRIVE, moduleRootDir, _MAX_DIR, NULL, 0, NULL, 0) != 0) {
    MessageBox(0, "Failed calling _splitpath_s()", title, type);
    return 1;
  }

  dirname = std::string(moduleRootDrive) + "\\" + std::string(moduleRootDir);

  path = "PATH=" + dirname + "\\bin;" + std::string(getenv("PATH"));
  _putenv(path.c_str());


  /* check for a running instance of Steam
   * and try to launch Steam if needed */

  dll = dirname + "\\bin\\steam_api.dll";
  hinstLauncher = LoadLibraryEx(dll.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

  if (!hinstLauncher) {
    char *errmsg;

    if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                      NULL,
                      GetLastError(),
                      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                      (LPSTR) &errmsg,
                      0,
                      NULL))
    {
      std::string msg = "Failed to load steam_api.dll:\n\n" + std::string(errmsg);
      MessageBox(0, msg.c_str(), title, type);
      LocalFree(errmsg);
    }

    return 1;
  }

  pSteamAPI_IsSteamRunning = (SteamAPI_IsSteamRunning_t) GetProcAddress(hinstLauncher, "SteamAPI_IsSteamRunning");

  if (!pSteamAPI_IsSteamRunning()) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD dwret;
    std::string steam_path, command;
    const char *errmsg;

    FreeLibrary(hinstLauncher);

    steam_path = get_steam_path(dirname);

    if (steam_path == "") {
      MessageBox(0, "Unable to find a running instance of Steam.", title, type);
      return 1;
    }

    command = steam_path + " -applaunch 362890";

    if (strlen(lpCmdLine) > 0) {
      command += " " + std::string(lpCmdLine);
    }

    SecureZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    SecureZeroMemory(&pi, sizeof(pi));

    errmsg = "Cannot launch Black Mesa through Steam.";

    if (!CreateProcess(NULL, (LPSTR) command.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
      MessageBox(0, errmsg, title, type);
      return 1;
    }

    dwret = WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (dwret == WAIT_ABANDONED || dwret == WAIT_TIMEOUT || dwret == WAIT_FAILED) {
      MessageBox(0, errmsg, title, type);
      return 1;
    }

    return 0;
  }


  /* load launcher.dll */

  FreeLibrary(hinstLauncher);
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

    FreeLibrary(hinstLauncher);
    return 1;
  }

  pLauncherMain = (LauncherMain_t) GetProcAddress(hinstLauncher, "LauncherMain");
  resultLauncherMain = pLauncherMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

  FreeLibrary(hinstLauncher);
  return resultLauncherMain;
}

