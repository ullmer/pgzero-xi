#include "enoColormapper.h"
#include <stdio.h>

int main() {
  enoColormapper ecm = enoColormapper();

  char *ecmHelp = ecm.getColorSummaryStr();
  printf("%s", ecmHelp);
  
  printf("------------\n");

  char *ecmYHelp = ecm.getColorYamlStr();
  printf("%s", ecmYHelp);
}

// end //
