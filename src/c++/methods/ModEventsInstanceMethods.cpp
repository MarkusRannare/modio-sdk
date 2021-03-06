#include "c++/ModIOInstance.h"
#include "ModioUtility.h"
#include "c++/methods/callbacks/ModEventsInstanceCallbacks.h"
#include "c++/creators/FilterCreator.h"

namespace modio
{
void Instance::getEvents(u32 mod_id, modio::FilterCreator &filter, const std::function<void(const modio::Response &, const std::vector<modio::ModEvent> &events)> &callback)
{
  struct GetEventsCall *get_events_call = new GetEventsCall{callback};
  get_events_calls[current_call_id] = get_events_call;

  modioGetEvents((void*)((uintptr_t)current_call_id), mod_id, *filter.getFilter(), &onGetEvents);

  current_call_id++;
}

void Instance::getAllEvents(modio::FilterCreator &filter, const std::function<void(const modio::Response &, const std::vector<modio::ModEvent> &events)> &callback)
{
  struct GetAllEventsCall *get_all_events_call = new GetAllEventsCall{callback};
  get_all_events_calls[current_call_id] = get_all_events_call;

  modioGetAllEvents((void*)((uintptr_t)current_call_id), *filter.getFilter(), &onGetAllEvents);

  current_call_id++;
}

void Instance::setEventListener(const std::function<void(const modio::Response &, const std::vector<modio::ModEvent> &events)> &callback)
{
  set_event_listener_call = new SetEventListenerCall{callback};
  modioSetEventListener(&onSetEventListener);
}
} // namespace modio
