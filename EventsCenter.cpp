#include "EventsCenter.hpp"

EventsCenter::EventsCenter() {}

EventsCenter::~EventsCenter()
{
  size_t t = _emitters.size() - 1;
  for (size_t i = 0; i <= t; i += 1)
  {
    _emitters[t - i]->clear();
    delete _emitters[t - i];
    _emitters.erase(_emitters.begin() + (t - i));
  }

  _emitters.clear();
}

int EventsCenter::findEmitterId(const char *emitterId)
{
  for (int i = 0; i < _emitters.size(); i += 1)
    if (strcmp(_emitters[i]->id(), emitterId) == 0)
      return i;

  return -1;
}

Emitter *EventsCenter::createEmitter(const char *id)
{
  int i = findEmitterId(id);
  if (i != -1)
    return _emitters[i];

  Emitter *em = new Emitter();
  em->setId(id);
  _emitters.push_back(em);

  return em;
}

int EventsCenter::subscribe(const char *emitterId, std::function<void(const char *emitterId, const char *value)> listener)
{
  int i = findEmitterId(emitterId);
  if (i == -1)
    return -1;

  listener_struct l;
  l.id = _listenersCount;
  l.listener = listener;
  _emitters[i]->addListener(l);

  _listenersCount += 1;

  return l.id;
}

void EventsCenter::unsubscribe(const char *emitterId, int listenerId)
{
  int i = findEmitterId(emitterId);
  if (i == -1)
    return;

  _emitters[i]->removeListener(listenerId);
}