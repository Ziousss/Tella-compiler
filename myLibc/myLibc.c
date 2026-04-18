size_t myStrlen(char *string){
    size_t count = 0;
    while(string[count] != '\0'){
        count++;
    }

    return count;
}

int foo(){
    return 5;
}