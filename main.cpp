#include <iostream>
#include <unistd.h>
#include <ios>
#include <fstream>
#include <string>
#include "src/world.hpp"
#include "src/utils/load_files.hpp"

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
  World w(1, 5, 1268);
  load_files(&w);
  province* porto = w.getProvinceById(173);
  province* lisboa = w.getProvinceById(174);
  province* braga = w.getProvinceById(175);
  province* vila_real = w.getProvinceById(176);
  province* coimbra = w.getProvinceById(178);
  province* viseu = w.getProvinceById(180);
  province* evora = w.getProvinceById(181);
  province* faro = w.getProvinceById(179);
  province* setubal = w.getProvinceById(183);
  province* aveiro = w.getProvinceById(210);
  viseu->add_neighbour(2, coimbra);
  viseu->add_neighbour(3, porto);
  viseu->add_neighbour(3, vila_real);
  viseu->add_neighbour(3, aveiro);
  vila_real->add_neighbour(3, braga);
  vila_real->add_neighbour(3, porto);
  porto->add_neighbour(2, braga);
  porto->add_neighbour(2, aveiro);
  coimbra->add_neighbour(2, aveiro);
  coimbra->add_neighbour(2, lisboa);
  lisboa->add_neighbour(3, evora);
  lisboa->add_neighbour(1, setubal);
  evora->add_neighbour(2, faro);
  evora->add_neighbour(2, setubal);

  evora->print_neighbours();
  cout << "----------------" << endl;

  vector<province*> provinces = w.get_path_between_provinces(176, 179);

  print_memory_usage();

  return EXIT_SUCCESS;

}