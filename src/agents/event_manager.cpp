#include "event_manager.hpp"

EventManager::EventManager() {}
EventManager::~EventManager() {}

void EventManager::addObserver(Observer* observer) {
  observers.push_back(observer);
}

void EventManager::notifyObservers(const AI_Character& sender, const Event& event) {
  for (Observer* observer : observers) {
    observer->notify(sender, event);
  }
}