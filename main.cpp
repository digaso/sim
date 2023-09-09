#include <iostream>
#include <unistd.h>
#include <ios>
#include <fstream>
#include <string>
#include "src/world.hpp"
//#include "src/graphics/window.hpp"
#include "src/graphics/raytest.hpp"
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
  World w(1, 1, 1166, cols, rows);
  cout << w.get_num_rows() << endl;
  cout << w.get_num_cols() << endl;
  run(&w);

  print_memory_usage();

  return EXIT_SUCCESS;

}