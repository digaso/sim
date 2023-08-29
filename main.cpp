#include <iostream>
#include <unistd.h>
#include <ios>
#include <fstream>
#include <string>
#include "src/world.hpp"
//#include "src/graphics/window.hpp"
#include "src/graphics/raytest.hpp"
#define NUM_CHUNKS 10
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

  World w(1, 1, 1166);
  int cols_and_rows = NUM_CHUNKS * CHUNKSIZE;
  cout << "cols_and_rows: " << cols_and_rows << endl;
  w.set_num_cols(cols_and_rows);
  w.set_num_rows(cols_and_rows);
  run(&w);

  print_memory_usage();

  return EXIT_SUCCESS;

}