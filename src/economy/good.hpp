#pragma once
#include <string>

using namespace std;


enum type_good {
  plantable,
  catchable,
  mineral,
  manufactured,
};

class Province;
class World;

class Good
{
private:
  uint id;
  string name;
  float base_value;
  type_good type;
  bool maritime = false;
  bool* map;
public:
  void static set_goods(World* world);
  Good(/* args */);
  Good(uint id, string name, float base_value, type_good type);
  ~Good();
  uint get_id();
  type_good get_type();
  bool is_maritime() {
    return maritime;
  }

  void set_map(bool* map) {
    this->map = map;
  }

  bool* get_map() {
    return map;
  }

  void set_maritime(bool maritime) {
    this->maritime = maritime;
  }

  float get_base_value();

  string get_name() {
    return name;
  }
  friend ostream& operator<<(ostream& os, const Good& g);
};
