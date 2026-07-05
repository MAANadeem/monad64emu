#include "base.h"
#include <vector>
constexpr u32 RAM_SIZE = 4 * 1024 * 1024; // 4 MB

struct RAM {
  RAM();
  std::vector<u16> mem_array;
};
