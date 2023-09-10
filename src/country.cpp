#include "country.hpp"

using namespace std;


void Country::add_province(Province* p) {
  this->provinces.push_back(p->get_id());
  this->num_provinces++;
}


string Country::get_name() {
  return this->name;
}
void Country::set_name(string name) {
  this->name = name;
}

string Country::print() {
  return this->name;
}

uint Country::get_id() {
  return this->id;
}

void Country::set_player(bool is_player) {
  this->is_player = is_player;
}

bool Country::player() {
  return this->is_player;
}

void Country::set_capital_id(uint id) {
  this->capital_id = id;
}

uint Country::get_capital_id() {
  return this->capital_id;
}

void Country::set_color_id(uint id) {
  this->color_id = id;
}

uint Country::get_color_id() {
  return this->color_id;
}

uint Country::get_num_provinces() {
  return this->num_provinces;
}

void Country::set_king_id(uint id) {
  this->king_id = id;
}

uint Country::get_king_id() {
  return this->king_id;
}

void Country::set_money(float money) {
  this->money = money;
}

float Country::get_money() {
  return this->money;
}

uint8_t Country::get_religion_id() {
  return this->religion_id;
}

vector<uint> Country::get_provinces() {
  return this->provinces;
}

void Country::print_characters() {

}

void Country::print_provinces() {
  if (this->num_provinces == 0) {
    cout << "No provinces" << endl;
    return;
  }

  for (uint i = 0; i < this->num_provinces; i++) {
    cout << this->provinces[ i ] << endl;
  }

}

ostream& operator<<(ostream& os, const Country& c) {
  os << c.name;
  return os;
}