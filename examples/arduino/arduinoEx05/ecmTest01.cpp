#include "enoColormapper.h"
#include <stdio.h>

main() {
  enoColormapper ecm = enoColormapper();
  char *ecmHelp = ecm.getColorSummaryStr();
  printf(ecmHelp);
}

// end //
