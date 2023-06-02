#include <iostream>
#include <unistd.h>
#include <ios>
#include <fstream>
#include <string>
#include "src/world.hpp"
#include "src/utils/load_files.hpp"
#include "src/graphics/window.hpp"

using namespace sf;
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
  World w(1, 5, 1208);

  run();
  print_memory_usage();

  return EXIT_SUCCESS;

}