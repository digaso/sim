#pragma once
#include <string>

using namespace std;
class Religion

{
private:
  uint8_t id;
  string name;
  uint8_t color_id;
public:

  Religion(/* args */) {};
  Religion(string name, uint8_t color_id, uint8_t id) {
    this->name = name;
    this->color_id = color_id;
    this->id = id;
  };
  ~Religion() {};
};

