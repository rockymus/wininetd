#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <string.h>

int main(void) 
{
    FILE *file;
    char filename[200];
    char *newline;   

    if (fgets(filename, sizeof(filename), stdin) == NULL)
        return -1; // Input error / EOF
    newline = strchr(filename, '\n');
    if (newline) // ? is a newline present?
        *newline = '\0';
    printf("**%s**\n", filename); // ** will help checking for
                                  //    the presence of white spaces.

    file = fopen(filename, "r");
    if (file) {
        int chr;
        while ((chr = fgetc(file)) != EOF)
            fputc(chr, stdout);
        fclose(file);
    } else {
        printf("File not found.");
    }
    printf("\n");

    return 0;
}