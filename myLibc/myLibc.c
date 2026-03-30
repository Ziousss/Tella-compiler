int myStrlen(char *string){
    int count = 0;
    while(string[count] != '\0'){
        count++;
    }

    return count;
}