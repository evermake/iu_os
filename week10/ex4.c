#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define DIR_TO_SCAN "tmp"

typedef struct {
    char*     name;
    ino_t     i_node_number;
    nlink_t   hard_links_count;
} FileInfo;

FileInfo* get_entries_info(char* path, int* n) {
    DIR *d;
    d = opendir(path);
    if (!d) {
        exit(EXIT_FAILURE);
    }
    chdir(path);

    struct dirent *entry;
    FileInfo* infos = malloc(sizeof(FileInfo)*64);
    int i = 0;
    while ((entry = readdir(d)) != NULL) {
        if (strcmp(entry->d_name, ".")  == 0) continue;
        if (strcmp(entry->d_name, "..") == 0) continue;

        FileInfo f;
        struct stat s;
        stat(entry->d_name, &s);
        f.name             = entry->d_name;
        f.i_node_number    = s.st_ino;
        f.hard_links_count = s.st_nlink;
        infos[i] = f;
        i++;
    }
    *n = i;
    closedir(d);
    return infos;
}

int main() {
    int read_count;
    FileInfo* entries_info = get_entries_info(DIR_TO_SCAN, &read_count);
    printf("File — Hard Links\n");
    for (int i = 0; i < read_count; i++) {
        FileInfo a = entries_info[i];
        if (a.hard_links_count < 2) {
            continue;
        }
        printf("%s — ", a.name);
        int is_first = 1;
        for (int j = 0; j < read_count; j++) {
            FileInfo b = entries_info[j];
            if (a.i_node_number == b.i_node_number) {
                if (is_first) {
                    printf("%s", b.name);
                    is_first = 0;
                }
                else {
                    printf(", %s", b.name);
                }
            }
        }
        printf("\n");
    }
    if (entries_info != NULL) {
        free(entries_info);
    }
    return EXIT_SUCCESS;
}

