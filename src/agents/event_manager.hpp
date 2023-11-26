#pragma once
#include <iostream>
#include <vector>
#include "../agents/events.hpp"

using namespace std;

class AI_Character;
class Observer;
class Event;

class EventManager {
public:
  EventManager();
  ~EventManager();
  void addObserver(Observer* observer);
  void removeObserver(Observer* observer);
  void notifyObservers(const AI_Character& sender, const Event& event);

private:
  vector<Observer*> observers;
};
