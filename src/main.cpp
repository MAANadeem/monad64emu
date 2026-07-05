
#include <fstream>
#include <iostream>
#include <vector>

#include "N64.h"

std::vector<u8> ReadFileAsBinary(char *Filename) {
  std::ifstream Binary;
  Binary.open(Filename);
  std::vector<u8> ByteDump;
  char Byte;
  while (Binary.get(Byte)) {
    if (Binary) {
      ByteDump.push_back((u8)Byte);
    }
  }
  return ByteDump;
}

int main(int argc, char *argv[]) {
  char *GameFileName = argv[1];

  std::vector<u8> GameBinary = ReadFileAsBinary(GameFileName);
    N64 n64;
    n64.Run();
  return 0;
}
