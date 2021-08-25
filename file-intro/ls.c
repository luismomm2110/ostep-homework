#include <string.h>
#include <sys/stat.h>
#include <stdlib.h> 
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <dirent.h>

void stat_file(struct stat status_file) {
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

int main (int argc, char *argv[]) {
    DIR *d;
    struct dirent *dir;
    struct stat status_file;
    char working_directory[255];
    
    if ((argc == 2) && (strcmp(argv[1], "-l") != 0)) {
        strcpy(working_directory, argv[1]);
    } else if (argc == 3) {
        strcpy(working_directory, argv[2]);
    } else {
        strcpy(working_directory, ".");
    }

    d = opendir(working_directory);
    
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
            if (strcmp(argv[1], "-l") == 0 ) {
                if (argc == 2) {
                    if (getcwd(working_directory, sizeof(working_directory)) == NULL)
                        perror("getworking_directory() error");
                    else {
                        printf("current working directory is: %s\n", working_directory);
                    }
                }
                    strcat(working_directory, dir->d_name);
                    if (stat(working_directory, &status_file) == -1) {
                        stat_file(status_file);
                    }
            } 
        }


    } else {
        printf("Error opening directory");
        exit(1);
    }




   closedir(d);
   return 0;
}