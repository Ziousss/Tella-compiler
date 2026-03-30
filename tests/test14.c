#include "myLibc/myLibc.c"

int main(){
    size_t number = 0;

    char *name = "This is my name";
    number = myStrlen(name);

    return number;
}

/*
echo $?
15
works
*/
