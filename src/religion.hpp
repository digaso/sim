#pragma once
#include <string>

using namespace std;
class God
{
private:
  uint8_t id;
  string name;
  uint8_t religion_id;


public:

  God(/* args */) {};
  God(uint8_t id, string name, uint8_t religion_id) {
    this->name = name;
    this->religion_id = religion_id;
    this->id = id;
  };
  ~God() {};
  uint8_t getId() { return this->id; };
  string get_name() { return this->name; };
  uint8_t get_religion_id() { return this->religion_id; };
};



class Religion
{
private:
  uint8_t id;
  string name;
  uint8_t color_id;
  vector<God> gods;
  bool is_polytheistic;
public:

  Religion(/* args */) {};
  ~Religion() {};
  Religion(uint8_t id, string name, uint8_t color_id, bool is_polytheistic = true) {
    this->name = name;
    this->color_id = color_id;
    this->id = id;
    this->is_polytheistic = is_polytheistic;
  };
  uint8_t getId() { return this->id; };
  string get_name() { return this->name; };
  uint8_t get_color_id() { return this->color_id; };
  void set_name(string name) { this->name = name; };
  void set_color_id(uint8_t color_id) { this->color_id = color_id; };
  void add_god(God g) { this->gods.push_back(g); };
  //print all gods
  string print() {
    string s = "";
    s += "Religion: " + this->name + "\n";
    s += "Color: " + to_string(this->color_id) + "\n";
    s += "Gods: \n";
    for (auto g : this->gods) {
      s += g.get_name() + "\n";
    }
    return s;
  };
};

