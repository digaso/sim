#pragma once
#include <string>

using namespace std;


enum type_good {
  plantable,
  catchable,
  mineral,
  manufactured,
};

enum class_good {
  basic_need,
  raw_material,
  luxury,
  military
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
  class_good good_class;
  bool maritime = false;
  uint initial_amoount;
  bool* map;
public:
  void static set_goods(World* world);
  Good(/* args */);
  Good(uint id, string name, float base_value, type_good type, class_good good_class);
  ~Good();
  uint getId();
  type_good get_type();
  class_good get_class();
  bool is_maritime();
  void set_map(bool* map);

  bool* get_map();
  uint get_initial_amount();
  void set_initial_amount(uint initial_amount);
  void set_maritime(bool maritime);

  float get_base_value();

  string get_name();
  friend ostream& operator<<(ostream& os, const Good& g);
};
