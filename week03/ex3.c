#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_FILES 256
#define MAX_SUBDIRS 8

typedef struct File {
    // Unique identifier of the file (0-255)
    int id;

    // Name of the file
    // (maximum length is 63 characters)
    char* name;

    // Length of the `data` (including null character)
    size_t size;

    // Content of the file as string
    // (maximum length is 1024 characters)
    char* data;

    // Parent directory of the file
    struct Directory* parent_dir;
} File;

typedef struct Directory {
    // Absolute path to the directory starting with "/"
    // (maximum length is 2048 characters)
    char* path;

    // Number of files
    int nf;

    // Array of files
    File* files[MAX_FILES];

    // Number of sub-directories
    int nd;

    // Array of sub-directories
    struct Directory* directories[MAX_SUBDIRS];
} Directory;

/*
 * Overwrite file data with str.
 */
void add_to_file(File* file, const char* str) {
    size_t len = strlen(str);
    char* new_data = malloc(len + 1);
    strcpy(new_data, str);
    if (file->data != NULL) {
        free(file->data);
    }
    file->data = new_data;
    file->size = len + 1;
}

/*
 * Append str to file data.
 */
void append_to_file(File* file, const char* str) {
    if (file->data == NULL) {
        add_to_file(file, str);
        return;
    }

    size_t len = strlen(str);
    char* new_data = malloc(file->size + len + 1);
    strcpy(new_data, file->data);
    strcpy(new_data + file->size - 1, str);
    free(file->data);
    file->data = new_data;
    file->size += len;
};

/*
 * Print file path to stdout. 
 */
void pwd_file(File* file) {
    printf("%s/%s\n", file->parent_dir->path, file->name);
}

/*
 * Add file to the directory.
 */
void add_file(File* file, Directory* dir) {
    dir->files[dir->nf++] = file;
    file->parent_dir = dir;
};

// Given to you
// Adds the subdirectory dir1 to the directory dir2
void add_dir(Directory *dir1, Directory *dir2){
    if (dir1 && dir2){
        dir2->directories[dir2->nd] = dir1;
        dir2->nd++;
    }
}

// Helper functions
void show_dir(Directory *dir);
void show_file(File *file);
void show_file_detailed(File *file);

int main(){
    Directory home, bin, root;

    home = (Directory) {
        .path = "/home",
        .nf = 0,
        .files = {},
        .nd = 0,
        .directories = {}
    };
    bin = (Directory) {
        .path = "/bin",
        .nf = 0,
        .files = {},
        .nd = 0,
        .directories = {}
    };
    root = (Directory) {
        .path = "/",
        .nf = 0,
        .files = {},
        .nd = 0,
        .directories = {}
    };

    // Add subdirectories
    add_dir(&home, &root);
    add_dir(&bin, &root);

    File bash, ex31, ex32;

    int id_counter = 0;

    bash = (File) {
        .id = id_counter++,
        .name = "bash",
        .size = 0,
        .data = NULL,
        .parent_dir = NULL
    };
    ex31 = (File) {
        .id = id_counter++,
        .name = "ex3_1.c",
        .size = 0,
        .data = NULL,
        .parent_dir = NULL
    };
    ex32 = (File) {
        .id = id_counter++,
        .name = "ex3_2.c",
        .size = 0,
        .data = NULL,
        .parent_dir = NULL
    };

    add_file(&bash, &bin);
    add_file(&ex31, &home);
    add_file(&ex32, &home);

    char content1[] = "int printf(const char * format, ...);";
    char content2[] = "int main(){printf('Hello World');}";
    char content3[] = "//This is a comment in C language";
    char content4[] = "Bourne Again Shell!";

    add_to_file(&ex31, content1);
    add_to_file(&ex32, content3);
    add_to_file(&bash, content4);

    append_to_file(&ex31, content2);

    show_dir(&root);
    show_file_detailed(&bash);
    show_file_detailed(&ex31);
    show_file_detailed(&ex32);

    pwd_file(&bash);
    pwd_file(&ex31);
    pwd_file(&ex32);

    return EXIT_SUCCESS;
}

// Helper functions

// Displays the content of the Directory dir
void show_dir(Directory *dir){
    printf("\nDIRECTORY\n");
    printf(" path: %s\n", dir->path);
    printf(" files:\n");
    printf("    [ ");
    for (int i = 0; i < dir->nf; i++){
        show_file(dir->files[i]);
    }
    printf("]\n");
    printf(" directories:\n");
    printf("    { ");
    
    for (int i = 0; i < dir->nd; i++){
        show_dir(dir->directories[i]);
    }
    printf("}\n");
}

// Prints the name of the File file
void show_file(File *file){
    printf("%s ", file->name);
}

// Shows details of the File file
void show_file_detailed(File *file){
    printf("\nFILE\n");
    printf(" id: %d\n", file->id);
    printf(" name: %s\n", file->name);
    printf(" size: %lu\n", file->size);
    printf(" data:\n");
    printf("    [ %s ]\n", file->data);
}
