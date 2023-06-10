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
public:
  void static set_goods(World* world);
  Good(/* args */);
  Good(uint id, string name, float base_value, type_good type);
  ~Good();
  uint get_id() { return this->id; };
  friend ostream& operator<<(ostream& os, const Good& g);
};
