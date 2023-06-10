#pragma once
#include <string>
#include "../province.hpp"

using namespace std;

class Province;

class Good
{
private:
  uint id;
  string name;
  float base_value;
public:
  void (*func) (Province*);
  Good(/* args */);
  Good(uint id, string name, float base_value);
  ~Good();
};

