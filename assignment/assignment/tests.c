#include <string.h>

#include "model.h"
#include "testrunner.h"
#include "tests.h"
#include <stdio.h>
#define CELL_EDIT_WIDTH 1000
#include "interface.h"

void run_tests() {
    set_cell_value(ROW_2, COL_A, strdup("1.4"));
    assert_display_text(ROW_2, COL_A, strdup("1.4"));
    set_cell_value(ROW_2, COL_B, strdup("2.9"));
    assert_display_text(ROW_2, COL_B, strdup("2.9"));
    set_cell_value(ROW_2, COL_C, strdup("=A2+B2+0.4"));
    assert_edit_text(ROW_2, COL_C, strdup("=A2+B2+0.4"));
    assert_display_text(ROW_2, COL_C, strdup("4.7"));
    set_cell_value(ROW_2, COL_B, strdup("3.1"));
    assert_display_text(ROW_2, COL_C, strdup("4.9"));
    set_cell_value(ROW_1, COL_A, strdup("1"));
    // populate the first row a formula that references all the cells before it. This is the worst case scenario for updating cells. this is the most dependencies a cell and all of it's descendants can have without circular dependencies.
    char formula[CELL_EDIT_WIDTH + 1] = "=0", prev_cell[5] = "+A1";
    for (int i = 1; i < NUM_ROWS * NUM_COLS; i++)
    {
        ROW r = i / NUM_COLS, prev_r = (i - 1) / NUM_COLS;
        COL c = i % NUM_COLS, prev_c = (i - 1) % NUM_COLS;
        prev_cell[1] = prev_c + 'A';
        snprintf(prev_cell + 2, 3, "%d", prev_r + 1); // +1 since row=0 is row_1.

        strcat(formula, prev_cell);
        set_cell_value(r, c, strdup(formula));
    }
    // Check that all the cells have the correct values.
    assert_display_text(ROW_1, COL_A, strdup("1.0"));
    float num = 1;
    for (int i = 1; i < NUM_ROWS * NUM_COLS/2; i++)
    {
        ROW r = i / NUM_COLS;
        COL c = i % NUM_COLS;
        char expected[CELL_DISPLAY_WIDTH + 1];
        snprintf(expected, CELL_DISPLAY_WIDTH + 1, "%.1f", num);
        assert_display_text(r, c, strdup(expected));
        num *= 2;
    }
    printf("first");
    // Perform an update on cell A1 and check that all the cells have the correct values.
    set_cell_value(ROW_1, COL_A, strdup("2.5"));
    assert_display_text(ROW_1, COL_A, strdup("2.5"));
    num = 2.5;
    for (int i = 1; i < NUM_ROWS * NUM_COLS/2; i++)
    {
        ROW r = i / NUM_COLS;
        COL c = i % NUM_COLS;
        char expected[CELL_DISPLAY_WIDTH + 1];
        snprintf(expected, CELL_DISPLAY_WIDTH + 1, "%.1f", num);
        assert_display_text(r, c, strdup(expected));
        num *= 2;
    }

    printf("died");
    getc(stdin);
}
