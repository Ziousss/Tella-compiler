size_t myStrlen(char *string){
    size_t count = 0;
    while(string[count] != '\0'){
        count++;
    }

    char *hello = "Hi";
    if(hello == "Hello"){
        return 5;
    }

    return count;
}