#pragma once
#include <string>
#include "date.hpp"

class character
{
private:
  uint id;
  std::string name;
  date birth_date;
public:
  character();
  ~character();
};

character::character(/* args */)
{
}

character::~character()
{
}
