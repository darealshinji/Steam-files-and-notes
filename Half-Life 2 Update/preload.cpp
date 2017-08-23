// Compile on Linux: g++ -m32 -Wall -O2 -s -fPIC -shared -o preload.so preload.cpp
// Use launch options: LD_PRELOAD=./preload.so %command%

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/steam/steam_api.h

#define S_API extern "C" __attribute__ ((visibility("default")))
#define S_CALLTYPE

S_API bool S_CALLTYPE SteamAPI_IsSteamRunning()
{
  return false;
}

