#include "province.hpp"

using namespace std;

string Province::get_name()
{
  return this->name;
}

country* Province::get_country()
{
  return this->country_owner;
}

void Province::set_country(country* country_owner)
{
  this->country_owner = country_owner;
}

uint Province::get_id()
{
  return this->id;
}

uint Province::get_population()
{
  return this->population_size;
}

float Province::get_y()
{
  return this->y;
}

type_province Province::get_type()
{
  return this->type;
}

float Province::get_x()
{
  return this->x;
}

float Province::get_height()
{
  return this->height;
}

float Province::get_moisture()
{
  return this->moisture;
}

void Province::add_goods(uint_fast8_t good_id)
{
  this->goods.push_back(good_id);
}

float Province::get_migration_atraction()
{
  return this->migration_atraction;
}

float Province::get_tax_control()
{
  return this->tax_control;
}

void Province::set_migration_atraction(float migration_atraction)
{
  this->migration_atraction = migration_atraction;
}

void Province::set_tax_control(float tax_control)
{
  this->tax_control = tax_control;
}

string Province::type_province_to_string(type_province type)
{
  switch (type)
  {
  case deep_sea:
    return "Deep Sea";
    break;
  case sea:
    return "Sea";
    break;
  case coastal_sea:
    return "Coastal Sea";
    break;
  case coast:
    return "Coast";
    break;
  case grassland:
    return "Grassland";
    break;
  case desert:
    return "Desert";
    break;
  case tundra:
    return "Tundra";
    break;
  case taiga:
    return "Taiga";
    break;
  case bare:
    return "Bare";
    break;
  case mountain:
    return "Mountain";
    break;
  case hill:
    return "Hill";
    break;
  case tropical:
    return "Tropical";
    break;
  case tropical_forest:
    return "Tropical Forest";
    break;
  case temperate_desert:
    return "Temperate Desert";
    break;
  case forest:
    return "Forest";
    break;
  case coastal_desert:
    return "Coastal Desert";
    break;
  default:
    break;
  }
  return "None";
}

ostream& operator<<(ostream& os, const Province& p)
{
  os << "Province: " << p.name << " Population: " << p.population_size << " Country: " << p.country_owner->get_name() << " Latitude: " << p.y << " Longitude: " << p.x;
  return os;
}
