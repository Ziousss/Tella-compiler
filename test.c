char * foo(){
    char *name = "Name";
    return name;
}

char *main(){
    int i = 5;
    int j = i + 4;

    char *name = foo();
    return name;
}