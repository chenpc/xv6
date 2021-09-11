#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


void find(char *path, char *name)
{
    int fd;
    struct dirent de;
    struct stat st;
    char buf[256];
    char *p;    

    if((fd = open(path, 0)) < 0){
        fprintf(2, "ls: cannot open %s/%s\n", path, name);
        return;
    }
    if(fstat(fd, &st) < 0){
        fprintf(2, "ls: cannot stat %s/%s\n", path, name);
        close(fd);
        return;
    }    

    if (st.type == T_DIR) {
        strcpy(buf, path);
        p = buf+strlen(buf);
        *p++ = '/';
        

        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(de.inum == 0)
                continue;
            strcpy(p, de.name);                     
            if (strcmp(name, de.name) == 0)
                printf("%s\n", buf);
            else if (strcmp(de.name, ".") == 0)
                continue;
            else if (strcmp(de.name, "..") == 0)
                continue;
            find(buf, name);
            
        }

    }
    close(fd);    
    
}

int
main(int argc, char *argv[])
{
  if(argc < 3){
    printf("find [path] [name]\n");
    exit(0);
  }
  
  find(argv[1], argv[2]);
  exit(0);
}