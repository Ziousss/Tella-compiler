#include "tests/includeTest.c"

int main(){
    return foo() + cool();
}

/*
echo $?
14
works
*/