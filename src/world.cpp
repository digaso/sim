#include "world.hpp"
#include <algorithm>
#include <unordered_map>
#include <cfloat>

struct Node {
  Province* province;
  float cost;

  bool operator>(const Node& other) const {
    return cost > other.cost;
  }
};

World::World(uint8_t day, uint8_t month, uint year, uint cols, uint rows)
{
  this->world_date = date(day, month, year);
  provinces = new Province[ cols * rows ];
  this->num_cols = cols;
  this->num_rows = rows;
  Good good;
  good.set_goods(this);
  //organize goods
  for (Good g : getGoods()) {
    switch (g.get_class()) {
    case class_good::basic_need:
      this->basic_needs.push_back(g.get_id());
      break;
    case class_good::luxury:
      this->luxury_needs.push_back(g.get_id());
      break;
    case class_good::military:
      this->military_needs.push_back(g.get_id());
      break;
    case class_good::raw_material:
      this->raw_materials.push_back(g.get_id());
      break;
    default:
      break;
    }
  }
  //print goods 
  cout << "Basic needs: " << endl;
  for (uint id : this->basic_needs) {
    cout << id << " ";
    cout << getGoodById(id)->get_name() << endl;
  }
  cout << "Luxury needs: " << endl;
  for (uint id : this->luxury_needs) {
    cout << getGoodById(id)->get_name() << endl;
  }
  cout << "Military needs: " << endl;
  for (uint id : this->military_needs) {
    cout << getGoodById(id)->get_name() << endl;
  }
  cout << "Raw materials: " << endl;
  for (uint id : this->raw_materials) {
    cout << getGoodById(id)->get_name() << endl;
  }

}

World::~World()
{
}

Country* World::getCountryById(uint id) {
  if (id < countries.size()) {
    return &countries.at(id);
  }
  return nullptr;
};

Character* World::getCharacterById(uint id) {
  if (id < characters.size()) {
    return &characters.at(id);
  }
  return nullptr;
};

void World::addAIAgent(AI_Character aic) {

  this->agents.push_back(aic);
}

void World::addBuilding(Building b) {
  this->buildings.push_back(b);
}

const string World::to_string() const
{
  ostringstream os;
  os << "World date: " << this->world_date.day() << "-" << world_date.month() << "-" << world_date.year();
  return os.str();
}
const date World::getDate() const
{
  return this->world_date;
}

Good* World::getGoodById(uint id)
{
  if (id < goods.size()) {
    return &goods.at(id);
  }
  return nullptr;
}

uint World::get_characters_size() {

  return this->characters.size();
}

Province* World::getProvinceByCoords(uint x, uint y)
{

  return &provinces[ (y * this->num_cols) + x ];
}

Province* World::getProvinceById(uint id)
{

  return &provinces[ id ];
}

string World::getDateString()
{
  ostringstream os;
  os << this->world_date.day() << "-" << world_date.month() << "-" << world_date.year();
  return os.str();
}

void World::setDate(date d)
{
  this->world_date = d;
}

void World::addProvince(Province p, uint x, uint y)
{
  this->provinces[ (y * this->num_cols) + x ] = p;
}

void World::addCountry(Country c)
{
  this->countries.push_back(c);
}

Province* World::getProvinces()
{
  return this->provinces;
}

void World::addRegion(Region r)
{
  this->regions.push_back(r);
}

void World::addReligion(Religion r)
{
  this->religions.push_back(r);
}

vector<Province*> World::get_land_neighbours(Province* p)
{
  vector<Province*> neighbours;
  int x = p->get_x();
  int y = p->get_y();
  //check cardinal directions
  if (x < this->num_cols - 1 && this->getProvinceByCoords(x + 1, y)->get_type() != type_province::sea && this->getProvinceByCoords(x + 1, y)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x + 1, y)->get_type() != type_province::deep_sea) {
    neighbours.push_back(this->getProvinceByCoords(x + 1, y));
  }
  if (y > 0 && this->getProvinceByCoords(x, y - 1)->get_type() != type_province::sea && this->getProvinceByCoords(x, y - 1)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x, y - 1)->get_type() != type_province::deep_sea) {
    neighbours.push_back(this->getProvinceByCoords(x, y - 1));
  }
  if (x > 0 && this->getProvinceByCoords(x - 1, y)->get_type() != type_province::sea && this->getProvinceByCoords(x - 1, y)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x - 1, y)->get_type() != type_province::deep_sea) {
    neighbours.push_back(this->getProvinceByCoords(x - 1, y));
  }
  if (y < this->num_rows - 1 && this->getProvinceByCoords(x, y + 1)->get_type() != type_province::sea && this->getProvinceByCoords(x, y + 1)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x, y + 1)->get_type() != type_province::deep_sea) {
    neighbours.push_back(this->getProvinceByCoords(x, y + 1));
  }

  return neighbours;
}

Region World::getRegionById(int id)
{
  if (id != -1) return regions.at(id);
  return Region();
}

vector<Province*> World::get_land_neighbours_diagonal(Province* p)
{
  vector<Province*> neighbours;
  int x = p->get_x();
  int y = p->get_y();
  //check cardinal directions
  if (x < this->num_cols - 1 && this->getProvinceByCoords(x + 1, y)->get_type() != type_province::sea && this->getProvinceByCoords(x + 1, y)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x + 1, y)->get_type() != type_province::deep_sea) {
    neighbours.push_back(this->getProvinceByCoords(x + 1, y));
  }
  if (y > 0 && this->getProvinceByCoords(x, y - 1)->get_type() != type_province::sea && this->getProvinceByCoords(x, y - 1)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x, y - 1)->get_type() != type_province::deep_sea) {
    neighbours.push_back(this->getProvinceByCoords(x, y - 1));
  }
  if (x > 0 && this->getProvinceByCoords(x - 1, y)->get_type() != type_province::sea && this->getProvinceByCoords(x - 1, y)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x - 1, y)->get_type() != type_province::deep_sea) {
    neighbours.push_back(this->getProvinceByCoords(x - 1, y));
  }
  if (y < this->num_rows - 1 && this->getProvinceByCoords(x, y + 1)->get_type() != type_province::sea && this->getProvinceByCoords(x, y + 1)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x, y + 1)->get_type() != type_province::deep_sea) {
    neighbours.push_back(this->getProvinceByCoords(x, y + 1));
  }
  //check diagonal directions
  if (x < this->num_cols - 1 && y > 0 && this->getProvinceByCoords(x + 1, y - 1)->get_type() != type_province::sea && this->getProvinceByCoords(x + 1, y - 1)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x + 1, y - 1)->get_type() != type_province::deep_sea) {
    neighbours.push_back(this->getProvinceByCoords(x + 1, y - 1));
  }
  if (x > 0 && y > 0 && this->getProvinceByCoords(x - 1, y - 1)->get_type() != type_province::sea && this->getProvinceByCoords(x - 1, y - 1)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x - 1, y - 1)->get_type() != type_province::deep_sea) {
    neighbours.push_back(this->getProvinceByCoords(x - 1, y - 1));
  }
  if (x > 0 && y < this->num_rows - 1 && this->getProvinceByCoords(x - 1, y + 1)->get_type() != type_province::sea && this->getProvinceByCoords(x - 1, y + 1)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x - 1, y + 1)->get_type() != type_province::deep_sea) {
    neighbours.push_back(this->getProvinceByCoords(x - 1, y + 1));
  }
  if (x < this->num_cols - 1 && y < this->num_rows - 1 && this->getProvinceByCoords(x + 1, y + 1)->get_type() != type_province::sea && this->getProvinceByCoords(x + 1, y + 1)->get_type() != type_province::coastal_sea && this->getProvinceByCoords(x + 1, y + 1)->get_type() != type_province::deep_sea) {
    neighbours.push_back(this->getProvinceByCoords(x + 1, y + 1));
  }

  return neighbours;
}

const vector<Country> World::getCountries() const
{
  return this->countries;
}

void World::printCountries() {
  for (auto row : this->countries) {
    cout << row.print() << endl;
  }
}

void World::addCharacter(Character c) {
  this->characters.push_back(c);
}

void World::addCulture(Culture c) {
  this->cultures.push_back(c);
}

bool World::ProvConnectedLand(Province* p1, Province* p2) {
  if (p1->get_region_id() == p2->get_region_id()) return true;
  return false;
}

float calculate_cost_based_on_type(type_province provinceType) {
  // Customize the cost calculation based on province type
  switch (provinceType) {
  case type_province::coastal_desert:
    return 1.7;
  case type_province::desert:
    return 2.0;
  case type_province::grassland:
  case type_province::coast:
    return 1.0;
  case type_province::hill:
    return 2.0;
  case type_province::mountain:
    return 4.0;
  case type_province::forest:
    return 1.5;
  case type_province::tropical_forest:
    return 2.0;
  case type_province::taiga:
    return 1.5;
  case type_province::tundra:
    return 1.8;
  case type_province::bare:
    return 4.0;
  case type_province::temperate_desert:
    return 1.5;
  default:
    return 5;  // Default cost for unknown types
  }
}

vector<Province*> World::get_path_between_provinces(uint start_id, uint end_id) {
  Province* start = getProvinceById(start_id);
  Province* end = getProvinceById(end_id);

  if ((!start || !end)) return {};
  if (start->get_region_id() != end->get_region_id()) return {};

  priority_queue<Node, vector<Node>, greater<Node>> pq;
  unordered_map<Province*, float> distance;
  unordered_map<Province*, Province*> parent;

  // Initialize distances
  for (size_t i = 0; i < num_cols * num_rows; ++i) {
    distance[ &provinces[ i ] ] = FLT_MAX;
  }
  distance[ start ] = 0;

  pq.push({ start, 0 });

  while (!pq.empty()) {
    Province* current = pq.top().province;
    float cost = pq.top().cost;
    pq.pop();

    if (current == end) {
      // Reached the destination, reconstruct the path
      vector<Province*> path;
      while (current) {
        path.push_back(current);
        current = parent[ current ];
      }
      reverse(path.begin(), path.end());
      return path;
    }

    vector<Province*> neighbours = get_neighbours_without_diagonal(current);
    for (auto& neighbour : neighbours) {
      float new_cost = cost + calculate_cost_based_on_type(neighbour->get_type());
      if (new_cost < distance[ neighbour ]) {
        distance[ neighbour ] = new_cost;
        parent[ neighbour ] = current;
        pq.push({ neighbour, new_cost });
      }
    }
  }

  // No path found
  return {};
}

Religion* World::getReligionById(uint id) {
  if (id < religions.size()) {
    return &religions.at(id);
  }
  return nullptr;
}

void World::printReligions() {
  for (auto row : this->religions) {
    cout << row.print() << endl;
  }
}

void World::addGood(Good g) {
  this->goods.push_back(g);
}

vector<Province*> World::get_neighbours(Province* p) {
  vector<Province*> neighbours;
  int x = p->get_x();
  int y = p->get_y();
  //check cardinal directions
  if (x < this->num_cols - 1) {
    neighbours.push_back(this->getProvinceByCoords(x + 1, y));
  }
  if (y > 0) {
    neighbours.push_back(this->getProvinceByCoords(x, y - 1));
  }
  if (x > 0) {
    neighbours.push_back(this->getProvinceByCoords(x - 1, y));
  }
  if (y < this->num_rows - 1) {
    neighbours.push_back(this->getProvinceByCoords(x, y + 1));
  }
  //check diagonal directions
  if (x < this->num_cols - 1 && y > 0) {
    neighbours.push_back(this->getProvinceByCoords(x + 1, y - 1));
  }
  if (x > 0 && y > 0) {
    neighbours.push_back(this->getProvinceByCoords(x - 1, y - 1));
  }
  if (x > 0 && y < this->num_rows - 1) {
    neighbours.push_back(this->getProvinceByCoords(x - 1, y + 1));
  }
  if (x < this->num_cols - 1 && y < this->num_rows - 1) {
    neighbours.push_back(this->getProvinceByCoords(x + 1, y + 1));
  }


  return neighbours;

}

vector<Province*> World::get_neighbours_without_diagonal(Province* p) {

  vector<Province*> neighbours;
  int x = p->get_x();
  int y = p->get_y();
  //check cardinal directions
  if (x < this->num_cols - 1) {
    neighbours.push_back(this->getProvinceByCoords(x + 1, y));
  }
  if (y > 0) {
    neighbours.push_back(this->getProvinceByCoords(x, y - 1));
  }
  if (x > 0) {
    neighbours.push_back(this->getProvinceByCoords(x - 1, y));
  }
  if (y < this->num_rows - 1) {
    neighbours.push_back(this->getProvinceByCoords(x, y + 1));
  }



  return neighbours;

}

bool World::advanceDate() {
  int month = this->world_date.month();
  this->world_date++;
  if (month != this->world_date.month()) {
    return true;
  }
  return false;
}

void World::updateAgents() {
  for (AI_Character agent : this->agents) {
    agent.update(this);
  }
}

void  World::updateWorld() {
  advanceDate();
  updateAgents();
}

Culture* World::getCultureById(uint id) {
  if (id < cultures.size()) {
    return &cultures.at(id);
  }
  return nullptr;
}