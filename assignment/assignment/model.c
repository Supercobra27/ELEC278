#include "model.h"
#include "interface.h"
#include <string.h>

#include <stddef.h>
#include <stdlib.h>

typedef enum{
    FLOAT,
    INT
}DT;

typedef struct cell_t{
        char *value; //textual representation
        long eval_value; //evaluated value
        struct cell_t **parents; //it is dependent on
        struct cell_t **children; //other cells that are dependent on it
    }cell_t;

cell_t model[7][10];


void model_init() {
    // TODO: implement this.
    for(int i=0;i<NUM_COLS;i++){ //iterate through the entire array and set everything to null as to not leave anything dangling.
        for(int j=0;j<NUM_ROWS;j++){
            model[i][j].value = malloc(1);
            strcpy(model[i][j].value, "");
            model[i][j].eval_value = 0;
            model[i][j].children = NULL;
            model[i][j].parents = NULL;
        }
    }
}

int* get_cell_reference(char row, char col){
    int row_convert = row - '0';
    int col_convert = col - 'A';
    int loc[2] = {row_convert, col_convert};
    return loc;
}

long eval_expression(char* cell_value, long sum){

    if(*cell_value != '=' && *cell_value != '+'){
        return 0;
    }else if(*cell_value == '+' || *cell_value == '='){
        cell_value++;
    }else{
        return 0;
    }

    while(*cell_value != '\0'){ //While not null character -> end of str
        if(*cell_value >= '0' && *cell_value <= '9'){ //if between 0-9 for the char
        long dec = 0;
            if(*(++cell_value) == '.'){
                cell_value++;
                dec = (*cell_value - '0')/10; //find decimal point
            }
            long whole = *cell_value - '0';
            sum += whole+dec; //convert from ASCII back to int

        }else if(*cell_value >= 'A' && *cell_value <= 'G'){ //if between A to G in ASCII it is a cell reference
            int* loc = malloc(sizeof(int)*2);
            loc = get_cell_reference(*cell_value, *(cell_value+1));
            cell_value--;
            int found = model[loc[0]][loc[1]].eval_value; //set a value of the found cell reference to it.
            free(loc);
            sum += found;
        }else if(*cell_value == '+'){//if it sees an operator
                sum += eval_expression(cell_value, sum);
        }
        cell_value++; //continue through the string
    }
    return 0;
}

long val;

void set_cell_value(ROW row, COL col, char *text) {
    // TODO: implement this.
    model[row][col].value = malloc(strlen(text)+1);
    strcpy(model[row][col].value, text);

    val = eval_expression(get_textual_value(row,col), val);
    model[row][col].eval_value = val;


    // This just displays the text without saving it in any data structure. You will need to change this.
    update_cell_display(row, col, text);
    free(text);
}

void clear_cell(ROW row, COL col) {
    // TODO: implement this.
    strcpy(model[row][col].value, "");
    model[row][col].eval_value = 0;

    // This just clears the display without updating any data structure. You will need to change this.
    update_cell_display(row, col, "");
}

char *get_textual_value(ROW row, COL col) {
    // TODO: implement this.
    return model[row][col].value;
}
