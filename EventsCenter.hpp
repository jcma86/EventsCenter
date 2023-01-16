#ifndef __TOOLS_NOTIFICATION_CENTER__
#define __TOOLS_NOTIFICATION_CENTER__

#include <string.h>
#include <vector>
#include <functional>

#include "Emitter.hpp"

class EventsCenter
{
private:
  int _listenersCount = 0;
  std::vector<Emitter*> _emitters;

  int findEmitterId(const char *emitterId);

  EventsCenter();
  ~EventsCenter();

public:
  static EventsCenter &getEventsCenter()
  {
    static EventsCenter ncInstance;
    return ncInstance;
  }

  EventsCenter(EventsCenter const &) = delete;
  EventsCenter &operator=(const EventsCenter &) = delete;

  Emitter *createEmitter(const char *id);
  int subscribe(const char *emitterId, std::function<void(const char *emitterId, const char *value)> listener);
  void unsubscribe(const char *emitterId, int listenerId);
};

#endif
