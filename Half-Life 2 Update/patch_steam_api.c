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
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE        4
#define FILESIZE       145600
#define BYTES_OFFSET   0x03533
#define CRC_UNPATCHED  "9FC8E082"
#define CRC_PATCHED    "FC036437"
#define NEW_BYTES      '\x32','\xC0','\x5D','\xC3'

// https://github.com/nothings/stb
 
typedef unsigned int stb_uint;

stb_uint stb_crc32_block(stb_uint crc, unsigned char *buffer, stb_uint len)
{
   static stb_uint crc_table[256];
   stb_uint i,j,s;
   crc = ~crc;

   if (crc_table[1] == 0)
      for(i=0; i < 256; i++) {
         for (s=i, j=0; j < 8; ++j)
            s = (s >> 1) ^ (s & 1 ? 0xedb88320 : 0);
         crc_table[i] = s;
      }
   for (i=0; i < len; ++i)
      crc = (crc >> 8) ^ crc_table[buffer[i] ^ (crc & 0xff)];
   return ~crc;
}

stb_uint stb_crc32(unsigned char *buffer, stb_uint len)
{
   return stb_crc32_block(0, buffer, len);
}

int main(void)
{
  const long size = FILESIZE;
  const unsigned char new_bytes[BUFSIZE] = { NEW_BYTES };
  const char *file1 = "bin/steam_api.dll";
  const char *file2 = "steam_api.dll";

  FILE *fp;
  const char *file = file1;
  unsigned char buf[BUFSIZE];
  unsigned char filebuf[FILESIZE];
  char crc[9] = {0};
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


  /* check CRC and patch file */

  if (fread(filebuf, 1, FILESIZE, fp) != FILESIZE)
  {
    printf("error: fread()\n");
    goto close;
  }

  snprintf(crc, 9, "%.8X", stb_crc32(filebuf, FILESIZE));

  if (strcmp(crc, CRC_PATCHED) == 0)
  {
    printf("%s already patched\n", file);
    rv = 0;
    goto close;
  }
  else if (strcmp(crc, CRC_UNPATCHED) == 0)
  {
    /* go to offset and read bytes */

    if (fseek(fp, BYTES_OFFSET, SEEK_SET) == -1)
    {
      printf("error: cannot parse %s\n", file);
      goto close;
    }

    if (fread(buf, 1, BUFSIZE, fp) != BUFSIZE)
    {
      printf("error: fread()\n");
      goto close;
    }

    if (fseek(fp, -BUFSIZE, SEEK_CUR) == -1)
    {
      printf("error: fseek()\n");
      goto close;
    }

    /* patch file */

    if (fwrite(new_bytes, 1, BUFSIZE, fp) == BUFSIZE)
    {
      printf("%s now patched\n", file);
      rv = 0;
    }
    else
    {
      printf("error: could not patch %s\n", file);
    }
  }
  else
  {
    printf("error: wrong file (CRC mismatch)\n");
    goto close;
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

