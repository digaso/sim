#pragma once
#include <string>

using namespace std;
class Culture
{
private:
  string name;
  uint id;

public:

  Culture(/* args */) {};
  Culture(string name, uint id) {
    this->name = name;
    this->id = id;
  };
  string get_name() {
    return this->name;
  }
  uint get_id() {
    return this->id;
  }
  ~Culture() {};
};

