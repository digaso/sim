#pragma once
#include <string>

using namespace std;
class culture
{
private:
  string name;

public:

  culture(/* args */) {};
  culture(string name) {
    this->name = name;
  };
  ~culture() {};
};

