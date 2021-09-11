#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"


int getline(char *buf, int size)
{
    char c;
    int ret;
    int i;
    char *tmp = buf;

    
    for (i=0;i<size;i++) {
        ret = read(0, &c, 1);
        
        if (ret < 0)
            return -1;               
        if (c == '\n' || c == 0) {
            *tmp++ = 0;
            break;
        }
        *tmp++ = c;

    }
    
    return strlen(buf);
}

int
main(int argc, char *argv[])
{
    int i;
    char *tmp_argv[MAXARG];    
    char buf[256];
    int wstat;        

    if (argc < 2) {
        printf("arg < 2\n");
        exit(0);
    }
    memset(tmp_argv, 0, sizeof(tmp_argv));
    // exec("grep", argv);
    
    tmp_argv[0] = argv[1];

    for (i=1;i<argc-1;i++) {
        tmp_argv[i] = argv[i+1];
        // printf("[%d]: %s\n", i, argv[i+1]);
    }
    
    while(getline(buf, 256) > 0) {
        int tmp = i;
        tmp_argv[tmp++] = buf;
        tmp_argv[tmp++] = 0;
        // printf("[%d] {%s} %s %s %s %s\n", i, tmp_argv[0], tmp_argv[0], tmp_argv[1], tmp_argv[2], tmp_argv[3]);
        if (fork() == 0)
            exec(tmp_argv[0], tmp_argv);            
        else
            wait(&wstat);
    }

    

    exit(0);
}
