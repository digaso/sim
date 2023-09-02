#include "country.hpp"

using namespace std;


void Country::add_province(Province* p) {
  this->provinces[ this->num_provinces ] = p;
  this->num_provinces++;
}

void Country::add_character(character c) {
  this->characters.push_back(c);
}



const int get_countryId_byAbrev(string abrev, vector<Country> countries)
{
  for (uint i = 0; i < countries.size(); i++)
  {
    if (countries.at(i).get_abrev() == abrev)
      return i;
  }
  return -1;
}

string Country::get_name() {
  return this->name;
}
void Country::set_name(string name) {
  this->name = name;
}
string Country::get_abrev() {
  return this->abrev;
}

string Country::print() {
  return this->name + " (" + this->abrev + ")";
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

Province** Country::get_provinces() {
  return this->provinces;
}

vector<character> Country::get_characters() {
  return this->characters;
}

void Country::print_characters() {
  if (this->characters.size() == 0) {
    cout << "No characters" << endl;
    return;
  }
  for (auto row : this->characters) {
    cout << row.get_name() << endl;
  }
}

void Country::print_provinces() {
  if (this->num_provinces == 0) {
    cout << "No provinces" << endl;
    return;
  }
  //print the provinces

  for (uint i = 0; i < this->num_provinces; i++) {
    cout << this->provinces[ i ]->get_name() << endl;
  }

}


ostream& operator<<(ostream& os, const Country& c) {
  os << c.name << " (" << c.abrev << ")";
  return os;
}