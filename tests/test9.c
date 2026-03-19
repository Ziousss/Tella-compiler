int main(){
    bool found = true;
    int j = 0;
    if(found == true){
        for(int i = 0; i < 5; i = i + 1){
            j = j + 1;
        }
        return j;
    } else {
        while(j < 42){
            j = j + 1;
        }   
        return j;
    }
}

/*
returns the right value when changing both values
echo $?
5
*/
