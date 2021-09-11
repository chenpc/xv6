#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p_pid;
  int pipefd[2];  
  char c_buf[256];
  char p_buf[256];

  pipe(pipefd);

  p_pid = getpid();
  fork();

  if (getpid() == p_pid) {
    write(pipefd[0], "ping", 5);
    read(pipefd[0], p_buf, 5);
    printf("%d: received pong\n", getpid());
  } else  {
    read(pipefd[1], c_buf, 5);
    printf("%d: received ping\n", getpid());
    write(pipefd[1], "pong", 5);    
  }
  exit(0);  
}

