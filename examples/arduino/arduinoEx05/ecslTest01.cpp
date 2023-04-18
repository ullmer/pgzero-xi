#include "enoStrLightmapper.h"
#include "enoColormapper.h"
#include <stdio.h>

int main() {
  enoStrLightmapper ecsl = enoStrLightmapper(5);
  enoColormapper ecm = enoColormapper();

  char *ecmHelp = ecm.getColorSummaryStr();
  printf("\ncolormap summary\n");
  printf(  "----------------\n");
  printf("%s", ecmHelp);

  ecsl.setLightByIdx(0, 'r', 10);
  ecsl.showLight();

  printf("\nlightmap summary\n");
  printf(  "----------------\n");
  char *ecslHelp = ecsl.getLightSummaryStr();
  printf("%s", ecslHelp);
}

/// end ///
