// If you want a example of a complete flow how authentication should go, please check out 55_SteamAuth.cpp
#include <stdbool.h>
#include "c/ModioC.h"
#include <stdio.h>

void onGalaxyAuth(void *object, ModioResponse response)
{
  bool *wait = object;
  if (response.code == 200)
  {
    printf("Successful Galaxy authentication\n");
  }
  else
  {
    printf("Error while trying to authenticating to Galaxy\n");
  }
  *wait = false;
}

int main(void)
{
  modioInit(MODIO_ENVIRONMENT_TEST, 7, false, true, "e91c01b8882f4affeddd56c96111977b", NULL);

  bool wait = true;

  // Auth works by providing the Appdata param given by the Galaxy SDK
  char *appdata = "GALAXY APPDATA HERE";
  // @todonow: Update example
  modioGalaxyAuth(&wait, appdata, false, &onGalaxyAuth);
  
  while (wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
