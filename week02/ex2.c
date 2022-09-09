#include <stdio.h>
#include <string.h>

#define MAX_SIZE 256
#define PROG int main()
#define BEGIN {
#define END }
#define $ ;
#define ___ ,

PROG BEGIN
    char s[MAX_SIZE]                         $
    fgets(s ___ MAX_SIZE ___ stdin)          $
    char* beforeDot = strtok(s ___ ".")      $
    size_t len = strlen(beforeDot)           $
    fputc('"' ___ stdout)                    $
    for (int i = len-1 $ i >= 0 $ i--) BEGIN $
        fputc(beforeDot[i] ___ stdout)       $
    END                                      $
    fputs("\"\n" ___ stdout)                 $
END
