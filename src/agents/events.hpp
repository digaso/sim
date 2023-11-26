#pragma once
#include <iostream>
#include <vector>
#include "../agents/ai_character.hpp"

using namespace std;


enum class EventType {
  DecisionMade,
  ResourceAcquired,
  ConflictOccurred,
  // Add more event types as needed
};

class Event {
  EventType type;
public:
  virtual ~Event() = default;
};

class ConflictOccurredEvent : public Event {
public:
  std::string location;

  ConflictOccurredEvent(const std::string& loc);
};
