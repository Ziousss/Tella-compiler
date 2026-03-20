int main(){
    bool found = false;
    int j = 0;
    if(found == true){
        for(int i = 0; i < 5; i = i + 1){
            j++;
        }
        return j;
    } else {
        while(j < 42){
            j+= 1;
        }   
        return j;
    }
}

/*
returns the right value when changing both values
echo $?
5

Cherry on top, ++ and +=1 work
-- and -= work as well but carefull the compiler does not have negatives right now. Loops around to 255 when -1.
*/
