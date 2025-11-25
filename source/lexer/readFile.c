#include "../include/lexer/readFile.h"


char *readFile(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp){
        perror("File could not open");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char *content = malloc(size+1);
    if (!content) {
        perror("Memory allocation failed");
        fclose(fp);
        return NULL;
    }

    if (fread(content, 1, size, fp) != size) {
        perror("Failed to read file");
        free(content);
        fclose(fp);
        return NULL;
    }
    content[size] = '\0';

    fclose(fp);
    return content;
}