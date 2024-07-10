#include "player.hpp"

Player::Player(World* w, uint country_id) {
  this->w = w;
  this->country_player = w->getCountryById(country_id);
  this->country_player->set_player(true);
}
