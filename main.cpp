#include <iostream>
#include "src/world.hpp"
#include "src/utils/load_files.hpp"

using namespace std;

int main() {
  World w(1, 5, 1234);
  load_files(&w);
  country* c = w.getCountryById(1);
  c->print_provinces();
  c->print_characters();

  return EXIT_SUCCESS;

}