int foo(int param){
    return param+5;
}

int main(){
    int j = 4;
    int i = foo(4);

    return 5;
}

/*
echo $?
13
works
*/