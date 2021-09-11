#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pipefd_p[2];
  int pipefd_c[2];
  char c_buf[256];
  char p_buf[256];

  pipe(pipefd_p);
  pipe(pipefd_c);

  if (fork() != 0) {
    write(pipefd_c[1], "ping", 5);
    read(pipefd_p[0], p_buf, 5);
    printf("%d: received pong\n", getpid());
  } else  {
    read(pipefd_c[0], c_buf, 5);
    printf("%d: received ping\n", getpid());
    write(pipefd_p[1], "pong", 5);
  }  
  exit(0);  
}

