#include "../include/tokenizer.h"
#include "../include/charcheck.h"

int lexicalAnalyzer (char* input) {
    int left = 0, right = 0;
    int len = strlen(input);

    while (right <= len && left <= right)
    {
        if(!isDelimiter(input[right])){
            right++;
        }

        if(isDelimiter(input[right]) && left == right){
            if(isOperation(input[right])){
                printf("Token: Operator, value: %c\n", input[right]);
            } 

            right++;
            left = right;
        }
        else if (isDelimiter(input[right]) && left != right || (right == len && left != right)){
            char *sub = getSubstring(input, left, right-1);

            if(isKeyword(sub)){
                printf("Token: Keyword, Value: %s\n", sub);
            }
            else if (isInteger (sub)) {
                printf("Token: Integer, Value: %s\n", sub);
            }
            else if (validIdentitfier(sub) && !isDelimiter(input[right-1])){
                printf ("Token: Identifier, Value: %s\n", sub);
            }
            else if (!validIdentitfier(sub) && !isDelimiter(input[right-1])){
                printf("Token: Unidentified, Value: %s\n", sub);
            }
            left = right;
        }
    }
    return 0;
}