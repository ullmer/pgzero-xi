#include "enoColormapper.h"
#include <stdio.h>

main() {
  enoColormapper ecm = enoColormapper();

  char *ecmHelp = ecm.getColorSummaryStr();
  printf(ecmHelp);
  
  //printf("------------\n");
  printf("%0*c\n", 20, '-');

  char *ecmYHelp = ecm.getColorYamlStr();
  printf(ecmYHelp);
}

// end //
