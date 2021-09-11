#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int n;

  if(argc < 2){
    fprintf(2, "Usage: sleep [second]...\n");
    exit(1);
  }

  n = atoi(argv[1]);
  fprintf(2, "%d\n", n);
  sleep(n);

  exit(0);
}
