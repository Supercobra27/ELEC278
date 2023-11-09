#include "engine.h"
#include "util.h"
#include <string.h>

bool run_statements(struct context *ctx, const char **input, struct error *err) {
    // Skip the whitespace at the beginning of the input.
    skip_whitespace(input);

    // Check if we are at a valid end of a sequence of statements, in which case, do nothing.
    if (**input == '\0' || **input == '}')
        return true;

    // Otherwise, run a single statement and then the rest of the statements.
    return run_statement(ctx, input, err) && run_statements(ctx, input, err);
}

bool run_statement(struct context *ctx, const char **input, struct error *err) {
    // TODO: Task 2: implement enqueue, assert, and assignment statements.


    //ENQ
    if(starts_with(*input, "ENQ")){ //If statement is ENQ
    *input += 3;
    skip_whitespace(input);
    if(**input != '('){
            err->pos = *input;
            err->desc = "invalid syntax : missing '('";
            return false;
            }
    *input += 1;
        int value; //Create standin
        if(!eval_expression(ctx, input, err, &value)) return false; //Evaluate exp, if false return error
        skip_whitespace(input);
        if(**input != ')'){
            err->pos = *input;
            err->desc = "invalid syntax : missing ')'";
            return false;
            }
        *input += 1;
        skip_whitespace(input);
        if(**input != ';'){
            err->pos = *input;
            err->desc = "invalid syntax : missing ';'";
        }
        *input += 1;
        enqueue(&ctx->q, value); //Otherwise enqueue value;

    //ASSERT
    }else if(starts_with(*input, "ASSERT")){ //If statement is ASSERT
        bool cond; //Create bool
        *input += 6;
        skip_whitespace(input);
    if(**input != '('){
            err->pos = *input;
            err->desc = "invalid syntax : missing '('";
            return false;
            }
    *input += 1;
        if(!eval_condition(ctx, input, err, &cond)) return false; //Check if eval condition failed
        if(!cond){ //If cond failed return error
            err->pos = *input;
            err->desc = "Failed Condition - ASSERT";
            return false;
        }
        skip_whitespace(input);
        if(**input != ')'){
            err->pos = *input;
            err->desc = "invalid syntax : missing ')'";
            return false;
            }
        *input += 1;
        skip_whitespace(input);
        if(**input != ';'){
            err->pos = *input;
            err->desc = "invalid syntax : missing ';'";
        }
        *input += 1;

    //ASSIGNMENT
    }else if(**input == 'x' || **input == 'y'){ //If statement is variable
        char var = **input;
        *input += 1;
        skip_whitespace(input);
        if(**input != '='){
            err->pos = *input;
            err->desc = "Expected '=' - ASSIGNMENT";
        }
        int value = 0;
        *input += 1;
        skip_whitespace(input);
        if(!eval_expression(ctx,input, err, &value)){
            return false;
        }
        if(**input != ';'){
            err->pos = *input;
            err->desc = "invalid syntax : missing ';'";
        }
        *input += 1;
        if(var == 'x'){ ctx->x = value;}
        else if(var == 'y'){ ctx->y = value;}
        else err->pos = *input; err->desc = "Failed variable";

    // TODO: Task 3: implement loops.
    //Use run_statements to run the ones inside the while loop
    }else if(starts_with(*input, "WHILE")){ //If statement is WHILE
        skip_whitespace(input);
        if(**input != '('){
            err->pos = *input;
            err->desc = "Expected '('";
            return false;
        }
        *input += 1;
        bool out, init;
        eval_condition(ctx, input, err, &init);
        if(**input != ')'){
            err->pos = *input;
            err->desc = "Expected ')'";
            return false;
        }
        *input+=1;
        skip_whitespace(input);
        if(**input != '{'){
            err->pos = *input;
            err->desc = "Expected '{'";
            return false;
        }
        skip_whitespace(input);
        while(eval_condition(ctx,input,err,&out) || init == true){
            init == false;
        run_statements(ctx,input,err);
        }
    }
    return true;
}

bool eval_expression(struct context *ctx, const char **input, struct error *err, int *out) {
    // TODO: Task 2: implement variable, constant, and dequeue.
    bool add, has_x = false, has_y = false, has_int = false, is_neg = false;

    //Variable
    if(**input == 'x') {
        *input += 1;
        skip_whitespace(input);
        if(**input == '+'){
            add = true;
            has_x = true;
        }else{
        *out = ctx->x;
        }
    }else if(**input == 'y') {
        *input += 1; 
        skip_whitespace(input);
        if(**input == '+'){
            add = true;
            has_y = true;
        }else{
        *out = ctx->y;
        }

    //Dequeue
    }else if(strncmp(*input, "DEQ", 3) == 0){
        if(!dequeue(&ctx->q,out)){
            err->pos = *input;
            err->desc = "Failed to dequeue";
            return false;
        }
        *input += 3; 

    //Const.
    }else{
        skip_whitespace(input);
        if(**input == '+'){
            *input += 1;
            skip_whitespace(input);
            if(**input == '-'){
                is_neg = true;
            }
            add = true;
            has_int = true;
        }else{
            parse_integer(input,err,out);
        }
        skip_whitespace(input);
    }

    // TODO: Task 3: implement add.
    if(add == true || **input == '+'){
        int neg = 1;
        skip_whitespace(input);
        if(is_neg){*input += 1; neg = -1;}
        if(has_x) *out += ctx->x; has_x = false;
        if(has_y) *out += ctx->y; has_y = false;
        if(has_int){
            int x; 
            parse_integer(input, err, &x); 
            *out += neg*x; 
            has_int = false;
            }
        if(**input != ';'){eval_expression(ctx, input, err, out);}
        *input += 1;
        if(**input != ';'){
            err->pos = *input;
            err->desc = "invalid syntax : missing ';'";
        }
    }

    return true;
}

bool eval_condition(struct context *ctx, const char **input, struct error *err, bool *out) {
    // TODO: Task 2: implement empty, equals, less than.
    skip_whitespace(input);
    //EMPTY
    if(starts_with(*input, "EMPTY")){
        *input += 5;
        *out = queue_empty(&ctx->q); //Check if queue is empty

    //COMPARATORS
    }else{ // will be exp = exp
    skip_whitespace(input);
    if(**input == '!'){
        *input += 1;
        bool cond;
        if(!eval_condition(ctx, input, err, &cond)) return false;
        *out = !cond;
    }
    
    int left, right, operator;
    skip_whitespace(input);

    if(**input == 'x' || **input == 'y' || starts_with(*input,"DEQ")){
        if(starts_with(*input, "DEQ")){
            dequeue(&ctx->q, &left);
            *input += 3;
        }else if(**input == 'x'){
            left = ctx->x;
            *input += 1;
        }else if(**input == 'y'){
            left = ctx->y;
            *input += 1;
        }else{
            parse_integer(input, err, &left);
            *input += 1;
        }
        skip_whitespace(input);
        if(**input == '=') operator=0;
        if(**input == '<') operator=1;
        *input += 1;
        skip_whitespace(input);
        if(starts_with(*input, "DEQ")){
            dequeue(&ctx->q, &right);
        }else if(**input == 'x'){
            right = ctx->x;
        }else if(**input == 'y'){
            right = ctx->y;
        }else{
            parse_integer(input, err, &right);
        }
        switch(operator){
            case 0:
            return *out = left == right;
            case 1:
            return *out = left < right;
            default:
            err->pos = *input;
            err->desc = "Incorrect Operand : use = or <";
            return false;
        }
    }

    //NOT
    }

    // TODO: Task 3: implement not.

    return true;
}

bool parse_integer(const char **input, struct error *err, int *out) {
    // Try to parse an integer at the current position, advancing '*input' to after it.
    const char *before = *input;
    int result = (int) strtol(before, (char **) input, 10);

    // If no characters were used, then the input was invalid.
    if (*input == before) {
        err->pos = before;
        err->desc = "expected an integer";
        return false;
    } else {
        *out = result;
        return true;
    }
}

bool eval_loop(const char **input, struct error *err, bool *out){

}