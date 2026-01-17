char main(int i, int j, char h){
    i = 4;
    return 'g';
}

void foo(){
    int i = 5;
    int j =7;
    char f = main(i,j, 'g');
    i = 5;
}
