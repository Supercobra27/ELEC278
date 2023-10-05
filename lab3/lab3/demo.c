#include "demo.h"
#include "stack.h"
#include <string.h>

bool matchBrackets(char c1, char c2){
    if (c1 == '(' && c2 == ')')
        return true;
    else if (c1 == '{' && c2 == '}')
        return true;
    else if (c1 == '[' && c2 == ']')
        return true;
    else
        return false;
}

bool check_brackets(const char *str) {
    stack_ptr s = stack_new();
    int i=0;
    char out;
    int len=0;
    bool good = true;
    while(str[i]){
        if(str[i]=='{'|| str[i]=='(' || str[i]=='['){
            stack_push(s, str[i]);
            len++;
        }
        if(str[i]== '}' || str[i]== ')' || str[i]== ']'){
            bool worked = stack_pop(s, &out);
            if(matchBrackets(out, str[i]) && len!=0){
                good = true;
            }else{
                return false;
            }
            len--;
        }
        i++;
    }

    if(len == 0){
        return true;
    }

    if(!stack_pop(s,&out)) return false;
    stack_free(s);
    return false;
}
