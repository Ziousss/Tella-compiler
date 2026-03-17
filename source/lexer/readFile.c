#include "../include/lexer/readFile.h"

char *readFile(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp){
        printf("File could not open\n");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char *content = malloc(size+1);
    if (!content) {
        printf("Memory allocation failed\n");
        fclose(fp);
        return NULL;
    }

    if (fread(content, 1, size, fp) != size) {
        printf("Failed to read file\n");
        free(content);
        fclose(fp);
        return NULL;
    }
    content[size] = '\0';

    fclose(fp);
    return content;
}