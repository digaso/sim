#include <iostream>
#include "world.hpp"
#include "utils/load_files.hpp"

using namespace std;



int main() {
  World w(1, 5, 1234);
  load_files(&w);
  country* c = w.getCountryById(0);
  c->print_provinces();

}