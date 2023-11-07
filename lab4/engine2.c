//#include "engine.h"
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
    skip_whitespace(input);
    if (strncmp(*input, "ENQ", 3) == 0) {
        *input += 3;
        int value;
        if (!eval_expression(ctx, input, err, &value))
            return false;
        enqueue(&ctx->q, value);
    } else if (strncmp(*input, "ASSERT", 6) == 0) {
        *input += 6;
        bool condition;
        if (!eval_condition(ctx, input, err, &condition))
            return false;
        if (!condition) {
            err->pos = *input;
            err->desc = "assertion failed";
            return false;
        }
    } else if (**input == 'x' || **input == 'y') {
        char var = **input;
        *input += 1;
        if (**input != '=') {
            err->pos = *input;
            err->desc = "expected '='";
            return false;
        }
        *input += 1;
        int value;
        if (!eval_expression(ctx, input, err, &value))
            return false;
        if (var == 'x')
            ctx->x = value;
        else
            ctx->y = value;
    } else if (strncmp(*input, "WHILE", 5) == 0) {
        *input += 5;
        bool condition;
        if (!eval_condition(ctx, input, err, &condition))
            return false;
        while (condition) {
            if (!run_statements(ctx, input, err))
                return false;
            if (!eval_condition(ctx, input, err, &condition))
                return false;
        }
    } else {
        err->pos = *input;
        err->desc = "unknown statement";
        return false;
    }
    return true;
    // TODO: Task 2: implement enqueue, assert, and assignment statements.
    // TODO: Task 3: implement loops.
}
bool eval_expression(struct context *ctx, const char **input, struct error *err, int *out) {
    skip_whitespace(input);
    if (**input == 'x') {
        *input += 1;
        *out = ctx->x;
    } else if (**input == 'y') {
        *input += 1;
        *out = ctx->y;
    } else if (strncmp(*input, "DEQ", 3) == 0) {
        *input += 3;
        if (!dequeue(&ctx->q, out)) {
            err->pos = *input;
            err->desc = "dequeue from empty queue";
            return false;
        }
    } else if (**input == '+') {
        *input += 1;
        int value1, value2;
        if (!eval_expression(ctx, input, err, &value1))
            return false;
        if (!eval_expression(ctx, input, err, &value2))
            return false;
        *out = value1 + value2;
    } else {
        return parse_integer(input, err, out);
    }
    return true;
}

bool eval_condition(struct context *ctx, const char **input, struct error *err, bool *out) {
    // TODO: Task 2: implement empty, equals, less than.
    // TODO: Task 3: implement not.
    skip_whitespace(input);
    if (strncmp(*input, "EMPTY", 5) == 0) {
        *input += 5;
        *out = queue_empty(&ctx->q);
    } else if (**input == '=') {
        *input += 1;
        int value1, value2;
        if (!eval_expression(ctx, input, err, &value1))
            return false;
        if (!eval_expression(ctx, input, err, &value2))
            return false;
        *out = value1 == value2;
    } else if (**input == '<') {
        *input += 1;
        int value1, value2;
        if (!eval_expression(ctx, input, err, &value1))
            return false;
        if (!eval_expression(ctx, input, err, &value2))
            return false;
        *out = value1 < value2;
    } else if (**input == '!') {
        *input += 1;
        bool condition;
        if (!eval_condition(ctx, input, err, &condition))
            return false;
        *out = !condition;
    } else {
        err->pos = *input;
        err->desc = "unknown condition";
        return false;
    }
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