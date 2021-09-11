#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int i;
    int pipefd[2];
    int first_p;
    int n;
    int l_fd;
    int ret;
    int wstat;
    // int forked = 0;
    pipe(pipefd);

    for (i=2;i<35;i++) {        
        write(pipefd[1], &i, 4);        
    }
    close(pipefd[1]);    

   
fork_here:
    l_fd = pipefd[0];
    ret = read(l_fd, &first_p, 4);
    pipe(pipefd); 
    if (!ret)
        goto out;

    printf("prime %d\n", first_p);
    while(read(l_fd, &n ,4) != 0) {
        if (n%first_p)
            write(pipefd[1], &n, 4);
    }
    close(l_fd);
    close(pipefd[1]);
    
    if (fork() == 0) {
        goto fork_here;
    }

    wait(&wstat);

out:
    exit(0);
}

