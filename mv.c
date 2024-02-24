#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUF_SIZE 512

int
main(int argc, char *argv[])
{
    int fd_src, fd_dest, n;
    char buf[BUF_SIZE];

    if(argc != 3){
        printf(2, "Usage: mv source destination\n");
        exit();
    }

    if((fd_src = open(argv[1], O_RDONLY)) < 0){
        printf(2, "mv: cannot open %s\n", argv[1]);
        exit();
    }

    if((fd_dest = open(argv[2], O_WRONLY | O_CREATE)) < 0){
        printf(2, "mv: cannot create %s\n", argv[2]);
        close(fd_src);
        exit();
    }

    while((n = read(fd_src, buf, sizeof(buf))) > 0){
        if(write(fd_dest, buf, n) != n){
            printf(2, "mv: write error\n");
            close(fd_src);
            close(fd_dest);
            exit();
        }
    }

    close(fd_src);
    close(fd_dest);

    if(unlink(argv[1]) < 0){
        printf(2, "mv: cannot delete %s\n", argv[1]);
        exit();
    }

    exit();
}
