/*
Program that lists the contents of the root directory "/".
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#define DIRNAME "/"

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(DIRNAME)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            printf("%s ", ent->d_name);
        }
        closedir(dir);
    } else {
        /* could not open directory */
        printf("failed to open directory");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
