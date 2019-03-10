/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 */

/*
 * Quick and dirty hack to batch extract Ogg streams from the audio log assets
 * of "The Turing Test", located in "steamapps\common\The Turing Test\TheTuringTest\Content\Audio\VOLogs"
 */

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>


int main(void)
{
  const std::string files[] = {
    "AvaGoingToSleep",
    "ChrisConsidersRemovingHand",
    "ChrisRemovesHand",
    "DanGivingUp",
    "DansApology",
    "DansApologyScratchy",
    "DepartureLanding",
    "DontKnowWhatItIsYet",
    "InsideBaseTheCircularRoom",
    "InsideBaseTheCircularRoomChecked",
    "MikhailThreatensTom",
    "PreparingForDeparture",
    "SarahAndChris",
    "SarahAndMikhail",
    "SarahAndMikhail2",
    "SarahAndTom",
    "TeamMeeting",
    "TheOrganismIsUnwanted",
    "TheyreRightToKeepUsHere",
    "TomAndChris",
    "TomAndTeam",
    "TomAskingAdvice",
    "TomKillsChris",
    "TomTalksToDaniel",
    "TomsCutsOffTheFood",
    "TomsUpset",
    "TuringTest1",
    "TuringTest2",
    "TuringTest3",
    "TuringTest4",
    "WhatIsTheOrganism"
  };

  for (size_t i = 0; i < (sizeof(files)/sizeof(*files)); ++i) {
    std::string in = files[i] + ".uasset";
    std::string out = files[i] + ".ogg";
    size_t szIn, pos, szOut;
    char *data, *p;
    std::string copy;

    std::ifstream ifs(in, std::ios::in|std::ios::binary|std::ios::ate);

    if (!ifs.is_open()) {
      std::cerr << "cannot open file: " << in << std::endl;
      return 1;
    }

    szIn = ifs.tellg();

    if (szIn > 2048*1024 /*2M*/ || szIn < 50*1024 /*50k*/) {
      std::cerr << "incorrect file size: " << in << std::endl;
      ifs.close();
      return 1;
    }

    ifs.seekg(0, std::ios::beg);

    data = new char[szIn];
    ifs.read(data, szIn);

    if (!ifs) {
      std::cerr << "cannot read data from file: " << in << std::endl;
      delete[] data;
      return 1;
    }
    ifs.close();

    if (memcmp("\xC1\x83\x2A\x9E\xFA\xFF\xFF\xFF", data, 8) != 0) {
      std::cerr << "wrong magic bytes: " << in << std::endl;
      delete[] data;
      return 1;
    }

    p = data;
    pos = 0;

    for (size_t j = 0; j < szIn-8; ++j, ++p) {
      if (memcmp("\0OggS\0", p, 6) == 0) {
        pos = j + 1;
        p++;
        break;
      }
    }

    if (pos == 0) {
      std::cerr << "no Ogg data found in file: " << in << std::endl;
      delete[] data;
      return 1;
    }

    szOut = szIn - pos;

    std::ofstream ofs(out, std::ofstream::out|std::ofstream::binary);

    if (!ofs.is_open()) {
      std::cerr << "cannot write to file: " << out << std::endl;
      delete[] data;
      return 1;
    }

    ofs.write(p, szOut);

    if (!ofs) {
      std::cerr << "error writing to file: " << out << std::endl;
      ofs.close();
      delete[] data;
      return 1;
    }
    ofs.close();

    std::cout << "file saved: " << out << std::endl;

    delete[] data;
  }

#ifdef _WIN32
  std::cout << std::endl;
  system("pause");
#endif
  return 0;
}

