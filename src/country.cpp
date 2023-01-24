#include "country.hpp"

using namespace std;


void country::add_province(province* p) {
  this->provinces[ this->num_provinces ] = p;
  this->num_provinces++;
}

void country::add_character(character c) {
  this->characters.push_back(c);
}



const int get_countryId_byAbrev(string abrev, vector<country> countries)
{
  for (int i = 0; i < countries.size(); i++)
  {
    if (countries.at(i).get_abrev() == abrev)
      return i;
  }
  return -1;
}

string country::get_name() {
  return this->name;
}
void country::set_name(string name) {
  this->name = name;
}
string country::get_abrev() {
  return this->abrev;
}

string country::print() {
  return this->name + " (" + this->abrev + ")";
}

uint country::get_id() {
  return this->id;
}
province** country::get_provinces() {
  return this->provinces;
}

vector<character> country::get_characters() {
  return this->characters;
}

void country::print_characters() {
  if (this->characters.size() == 0) {
    cout << "No characters" << endl;
    return;
  }
  for (auto row : this->characters) {
    cout << row.get_name() << endl;
  }
}

void country::print_provinces() {
  if (this->num_provinces == 0) {
    cout << "No provinces" << endl;
    return;
  }
  //print the provinces

  for (int i = 0; i < this->num_provinces; i++) {
    cout << this->provinces[ i ]->get_name() << endl;
  }

}


ostream& operator<<(ostream& os, const country& c) {
  os << c.name << " (" << c.abrev << ")";
  return os;
}