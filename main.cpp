#include <iostream>
#include <unistd.h>
#include <ios>
#include <fstream>
#include <string>
#include "src/world.hpp"
#include "src/graphics/raytest.hpp"
#include "src/province.hpp"
#include "src/country.hpp"

#define INITIAL_YEAR 822
#define INITIAL_MONTH 1
#define INITIAL_DAY 1
#define NUM_CHUNKS 7

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