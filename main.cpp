#include <iostream>
#include <thread>
#include <unistd.h>
#include <ios>
#include <fstream>
#include <string>
#include "src/configs.h"
#include "src/world.hpp"
#include "src/province.hpp"
#include "src/country.hpp"
#include "src/graphics/game.hpp"

using namespace std;

void print_memory_usage() {
  ifstream proc("/proc/self/status");
  string s;
  while (getline(proc, s), !proc.fail()) {
    if (s.substr(0, 6) == "VmSize") {
      cout << s << endl;
    }
  }
}

int main() {
  uint cols = NUM_CHUNKS * CHUNKSIZE;
  uint rows = (NUM_CHUNKS * CHUNKSIZE) * 0.7;
  World w(INITIAL_DAY, INITIAL_MONTH, INITIAL_YEAR, cols, rows);
  run(&w);


  print_memory_usage();

  return EXIT_SUCCESS;

}