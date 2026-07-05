
#include <format>
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
    std::cout << argc << std::endl;
    if (argc < 3) {
        std::cout << "not enough arguments" << std::endl;
        return 1;
    }
    char *pif_file_name = argv[1];
    char *game_file_name = argv[2];

    std::vector<u8> pif_file = ReadFileAsBinary(pif_file_name);
    std::vector<u8> game_file = ReadFileAsBinary(game_file_name);

    N64 n64(pif_file, game_file);
    n64.Run();
    return 0;
}
