int foo(int param){
    return param * 2;
}

int main(){
    int x = 6;
    x = foo(x);
    return x;
}

/*
echo $?
12
works
*/