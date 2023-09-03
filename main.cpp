#include <iostream>
#include <unistd.h>
#include <ios>
#include <fstream>
#include <string>
#include "src/world.hpp"
//#include "src/graphics/window.hpp"
#include "src/graphics/raytest.hpp"
#define NUM_CHUNKS 5
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

  int cols = NUM_CHUNKS * CHUNKSIZE;
  int rows = NUM_CHUNKS / 1.5 * CHUNKSIZE;
  World w(1, 1, 1166, cols, rows);
  run(&w);

  print_memory_usage();

  return EXIT_SUCCESS;

}