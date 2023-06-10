#include <string>

using namespace std;

enum type_regiment {
  militia,
  artillery,
  archers,
  light_infantry,
  light_cavalry,
  heavy_infantry,
  heavy_cavalry,
};

class Regiment {
  uint id;
  uint size = 100;
  string name;
  uint morale = 100;
  uint discipline = 100;
  uint drill = 0;
  uint experience = 0;
  type_regiment type;
  uint num_soldiers;
};