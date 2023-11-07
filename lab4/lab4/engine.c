#include "engine.h"
#include "util.h"

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
    skip_whitespace(input);
    //char *exp = strtok(input,"()");
    //char *eval = strtok(*exp, " ");

    if(strncmp(*input,"ENQ",3)==0){
        int value;
        if(!eval_expression(ctx, input, err, &value)) return false;
        enqueue(&ctx->q, value);
    }else if(strncmp(*input, "ASSERT",6)==0){
        bool cond;
        if(!eval_condition(ctx, input, err, &cond)) return false;
        if(!cond){
            err->pos = *input;
            err->desc = "assert failed";
        }
    }else if(**input == 'x' || **input == 'y'){
        char var = **input;
        *input += 1;
        if(**input != '='){
            err->pos = *input;
            err->desc = "Expected '='";
        }
        *input += 1;
        int value;
        if(!eval_expression(ctx,input, err, value)){
            return false;
        }
        if(var == 'x') ctx->x = value;
        if(var == 'y') ctx->y = value;
        else err->pos = *input; err->desc = "Failed variable";
        
    }

    // TODO: Task 3: implement loops.

    return true;
}

bool eval_expression(struct context *ctx, const char **input, struct error *err, int *out) {
    // TODO: Task 2: implement variable, constant, and dequeue.

    // TODO: Task 3: implement add.

    return true;
}

bool eval_condition(struct context *ctx, const char **input, struct error *err, bool *out) {
    // TODO: Task 2: implement empty, equals, less than.

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
