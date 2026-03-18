int foo(int param){
    return param+5;
}

int main(){
    int j = 4;
    int i = j + foo(j);

    return i;
}

/*
echo $?
13
works
*/