#include "../include/preprocess/preprocess.h"

char *preprocess(char *source){
    size_t sourceSize = strlen(source);
    size_t capacity = 16;
    size_t outputIndex = 0;
    char *output = malloc(capacity);
    if(output == NULL){
        printf("Malloc failed for output in the preprocess.\n");
        return NULL;
    }
    
    char *fileName = NULL;
    char *fileContent = NULL;
    char *tmp = NULL;

    size_t index = 0;
    while(index < sourceSize){
        if(source[index] != '#'){
            if(outputIndex >= capacity){
                capacity *= 2;
                tmp = realloc(output, capacity);
                if(tmp == NULL){
                    printf("Realloc failed for output in preprocess.\n");
                    free(output);
                    return NULL;
                }
                output = tmp;
            }

            output[outputIndex] = source[index];
            outputIndex++;
            index++;
            continue;
        }

        index++;
        while(index < sourceSize && source[index] == ' '){
            index++;
        }

        char *includeStart = source + index;
        size_t includeLen = 0;
        size_t start = index;

        while (index < sourceSize && source[index] != ' ' && source[index] != '\n' && source[index] != '\"') {
            index++;
            includeLen++;
        }

        if (includeLen != 7 || strncmp(includeStart, "include", 7) != 0) {
            index = start;
            index++;
            continue;
        }

        //Account for space(s)
        while(index < sourceSize && source[index] == ' '){
            index++;
        }

        if(source[index] != '\"'){
            printf("Only local files are implemented for now and they require \"fileName\" usage.\n");
            free(output);
            return NULL;
        } index++;

        size_t fileNameSize = 16;
        tmp = malloc(fileNameSize);
        if(tmp == NULL){
            printf("Malloc failed for fileName in preprocess.\n");
            free(output);
            return NULL;
        }
        fileName = tmp;

        size_t countChar = 0;
        start = index;
        while(index < sourceSize && source[index] != '\"'){
            if(fileNameSize >= index - start){
                fileNameSize *= 2;
                tmp = realloc(fileName, fileNameSize);
                if(tmp == NULL){
                    printf("Realloc failed for fileName in preprocess.\n");
                    free(output);
                    return NULL;
                }
                fileName = tmp;
            }
            fileName[countChar] = source[index];
            countChar++;
            index++;
        }
        fileName[countChar] = '\x00';
        index++;
        //Skip last " and so end of include statementprocessed

        fileContent = readFile(fileName);
        if(fileContent == NULL){
            free(output);
            free(fileName);
            return NULL;
        }
        free(fileName);

        char *processed = preprocess(fileContent);
        free(fileContent);
        if(processed == NULL){
            free(output);
            return NULL;
        }
        fileContent = processed;


        size_t fileContentSize = strlen(fileContent);
        while(capacity < fileContentSize + outputIndex + 1){
            capacity *= 2;
        }

        tmp = realloc(output, capacity);
        if(tmp == NULL){
            printf("Realloc failed for output after fileContentSize in preprocess.\n");
            free(output);
            return NULL;
        }
        output = tmp;

        for(size_t j = 0; j < fileContentSize; j++){
            output[outputIndex + j] = fileContent[j];
        }
        outputIndex += fileContentSize;
    }

    output[outputIndex] = '\0';
    return output;
}