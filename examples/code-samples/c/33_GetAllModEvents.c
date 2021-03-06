#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>
#include <time.h>

void onGetAllEvents(void *object, ModioResponse response, ModioModEvent *events_array, u32 events_array_size)
{
  bool *wait = object;
  printf("On get mod events response: %i\n", response.code);

  // Just like the event listener, it returns an array of events
  for (u32 i = 0; i < events_array_size; i++)
  {
    printf("Event found!\n");
    printf("Id: %i\n", (int)events_array[i].id);
    printf("Mod id: %i\n", (int)events_array[i].mod_id);
    printf("User id: %i\n", (int)events_array[i].user_id);
    printf("Date added: %s\n", ctime((const time_t *)&events_array[i].date_added));
    printf("Event type: ");
    switch (events_array[i].event_type)
    {
    case MODIO_EVENT_UNDEFINED:
      printf("Undefined\n");
      break;
    case MODIO_EVENT_MODFILE_CHANGED:
      printf("Modfile changed\n");
      break;
    case MODIO_EVENT_MOD_AVAILABLE:
      printf("Mod available\n");
      break;
    case MODIO_EVENT_MOD_UNAVAILABLE:
      printf("Mod unavailable\n");
      break;
    case MODIO_EVENT_MOD_EDITED:
      printf("Mod edited\n");
      break;
    }
    printf("\n");
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, false, true, "e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  time_t current_time;
  time(&current_time);
  char current_time_str[12];
  sprintf(current_time_str, "%d", (int)current_time);

  ModioFilterCreator filter;
  modioInitFilter(&filter);
  modioSetFilterLimit(&filter, 10);
  // Let's filter from january first 2018 to the current date
  modioAddFilterMinField(&filter, "date_added", "1514780160");
  modioAddFilterMaxField(&filter, "date_added", current_time_str);

  printf("Getting mod events...\n");

  // Everything is setup up, let's retreive the events now
  modioGetAllEvents(&wait, filter, &onGetAllEvents);

  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
