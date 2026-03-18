int main(){
    //i++, i+=1 not implemented yet;
    int j = 0;
    for(int i = 0; i < 10; i = i + 1){
        j = j + 1;
    }

    return j;
}

/*
echo $?
10
works
*/