#include "../include/lexer/lexer.h"
#include "../include/lexer/charcheck.h"
#include "../include/lexer/tokenizer.h"

#define MAX_LENGTH 100


int main()
{
    //example
    lexicalAnalyzer("int main() {int a,b; a=10; return 0;}");
}