#pragma once
#include <string>

using namespace std;

class CultureTrait
{
private:
  /* data */
public:
  CultureTrait(/* args */) {};
  ~CultureTrait() {};
};

class Culture
{
private:
  string name;
  uint id;
  //vector<CultureTrait> traits;

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

