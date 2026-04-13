#include "../include/preprocess/preprocess.h"
#include <string.h>

PreResult preprocess(char *source, char *fileName){
    size_t cap = 64;
    size_t size = 0;
    SourceChar *out = malloc(sizeof(SourceChar) * cap);
    SourceChar *tmp = out;
    size_t line = 1;

    for (size_t i = 0; source[i]; i++){
        if (source[i] == '\n')
            line++;

        if (source[i] != '#'){
            if (size >= cap){
                cap *= 2;
                tmp = realloc(out, sizeof(SourceChar) * cap);
                if(tmp == NULL){
                    printf("Tmp1 realloc failed in preprocess\n");
                    free(out);
                    return (PreResult){NULL, 0};
                }
                out = tmp;
            }

            out[size].c = source[i];
            out[size].line = line;
            out[size].fileName = strdup(fileName);

            size++;
            continue;
        }
        i++;
        while (source[i] == ' ') i++;

        if (strncmp(&source[i], "include", 7) != 0) continue;
        i += 7;

        while (source[i] == ' ') i++;

        if (source[i] != '"') continue;
        i++;

        char buffer[256];
        size_t f = 0;

        while (source[i] && source[i] != '"' && f < 255) 
            buffer[f++] = source[i++];

        buffer[f] = '\0';
        char *fileContent = readFile(buffer);

        char *fname = strdup(buffer);
        PreResult inc = preprocess(fileContent, fname);
        free(fileContent);

        for (size_t j = 0; j < inc.size; j++){
            if (size >= cap){
                cap *= 2;
                tmp = realloc(out, sizeof(SourceChar) * cap);
                if(tmp == NULL){
                    printf("Tmp1 realloc failed in preprocess\n");
                    free(out);
                    return (PreResult){NULL, 0};
                }
                out = tmp;
            }

            out[size].c = inc.data[j].c;
            out[size].line = inc.data[j].line;

            out[size].fileName = strdup(inc.data[j].fileName);

            size++;
        }
        free(inc.data);
    }

    return (PreResult){out, size};
}