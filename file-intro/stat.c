#include <sys/stat.h>
#include <stdlib.h> 
#include <stdio.h>

int main(int argc, char *argv[]) {
        struct stat status_file;
        
        if (argc != 2) {
            printf("Enter a file\n");
            exit(1);
        }

        const char *filename = argv[1];;

        if (stat(filename, &status_file)) {
            printf("Error opening stat");
            exit(1);
        }

        printf("File type:                ");
        switch (status_file.st_mode & S_IFMT) {
        case S_IFBLK:
            printf("block device\n");
            break;
        case S_IFCHR:
            printf("character device\n");
            break;
        case S_IFDIR:
            printf("directory\n");
            break;
        case S_IFIFO:
            printf("FIFO/pipe\n");
            break;
        case S_IFLNK:
            printf("symbolic link\n");
            break;
        case S_IFREG:
            printf("regular file\n");
            break;
        case S_IFSOCK:
            printf("socket\n");
            break;
        default:
            printf("unknown?");
            break;
        }


        printf("\nFile st_uid %d \n",status_file.st_uid);
        printf("\nFile st_blksize %ld \n",status_file.st_blksize);
        printf("\nFile st_gid %d \n",status_file.st_gid);
        printf("\nFile st_blocks %ld \n",status_file.st_blocks);
        printf("\nFile st_size %ld \n",status_file.st_size);
        printf("\nFile st_nlink %u \n",(unsigned int)status_file.st_nlink);
        printf("\nFile Permissions User\n");
        printf((status_file.st_mode & S_IRUSR)? "r":"-");
        printf((status_file.st_mode & S_IWUSR)? "w":"-");
        printf((status_file.st_mode & S_IXUSR)? "x":"-");
        printf("\n");
        printf("\nFile Permissions Group\n");
        printf((status_file.st_mode & S_IRGRP)? "r":"-");
        printf((status_file.st_mode & S_IWGRP)? "w":"-");
        printf((status_file.st_mode & S_IXGRP)? "x":"-");
        printf("\n");
        printf("\nFile Permissions Other\n");
        printf((status_file.st_mode & S_IROTH)? "r":"-");
        printf((status_file.st_mode & S_IWOTH)? "w":"-");
        printf((status_file.st_mode & S_IXOTH)? "x":"-");
        printf("\n");
}