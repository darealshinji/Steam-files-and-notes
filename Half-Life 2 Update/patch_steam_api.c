/***
Patch HL2 Update's steam_api.dll by changing 4 bytes
at offset 0x03530:

  0x03530   55 8B EC   83 EC 14 68   F0 85 41 3B E8 B0 F1 FF FF
  0x03530   55 8B EC   32 C0 5D C3   F0 85 41 3B E8 B0 F1 FF FF

This will make the function SteamAPI_IsSteamRunning()
immediately return "false":

  SteamAPI_IsSteamRunning:
      push    ebp         ; 55
      mov     ebp, esp    ; 8B EC
      xor     al, al      ; 32 C0
      pop     ebp         ; 5D
      ret                 ; C3

Note: there's no real file integrity check included.
Only the filesize and the 4 bytes at the offset are checked.

MD5 checksums before and after the patching are:
before -> 69bee18efe39e0bd24b8ac979b560f39
after  -> c6b2cbe8bb59c38d5f54077de86a66ba

***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 4

int main(void)
{
  const long size = 145600L;
  const long offset = 0x03533;
  const unsigned char old[BUFSIZE] = { '\x83', '\xEC', '\x14', '\x68' };
  const unsigned char new[BUFSIZE] = { '\x32', '\xC0', '\x5D', '\xC3' };
  const char *file1 = "bin/steam_api.dll";
  const char *file2 = "steam_api.dll";

  FILE *fp;
  const char *file = file1;
  unsigned char buf[BUFSIZE];
  int rv = 1;


  /* open file */

  fp = fopen(file, "r+b");

  if (!fp)
  {
    file = file2;
    fp = fopen(file, "r+b");
  }

  if (!fp)
  {
    printf("error: cannot open \"%s\" or \"%s\"\n", file1, file2);
    goto exit;
  }

  /* check filesize */

  if (fseek(fp, 0, SEEK_END) == -1)
  {
    printf("error: cannot find end of %s\n", file);
    goto close;
  }

  if (ftell(fp) != size)
  {
    printf("error: wrong filesize: expected %ld bytes\n", size);
    goto close;
  }

  rewind(fp);


  /* go to offset and read bytes */

  if (fseek(fp, offset, SEEK_SET) == -1)
  {
    printf("error: cannot parse %s\n", file);
    goto close;
  }

  if (fread(buf, 1, BUFSIZE, fp) != BUFSIZE)
  {
    printf("error: fread()\n");
    goto close;
  }


  /* compare bytes and patch if necessary */

  if (memcmp(old, buf, BUFSIZE) == 0)
  {
    /* go back to offset */
    if (fseek(fp, -BUFSIZE, SEEK_CUR) == -1)
    {
      printf("error: fseek()\n");
      goto close;
    }

    if (fwrite(new, 1, BUFSIZE, fp) == BUFSIZE)
    {
      printf("%s patched\n", file);
      rv = 0;
    }
    else
    {
      printf("error: could not patch %s\n", file);
    }
  }
  else if (memcmp(new, buf, BUFSIZE) == 0)
  {
    printf("%s already patched\n", file);
    rv = 0;
  }
  else
  {
    printf("error: wrong file\n");
  }


close:
  fclose(fp);
exit:
#ifdef _WIN32
  printf("\n");
  system("pause");
#endif
  return rv;
}

