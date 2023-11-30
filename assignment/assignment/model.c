#include "model.h"
#include "interface.h"
#include <string.h>

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

//Gotta make my defs better robustness
#define PARENT_CELL(col,row) model[col][row].dependencies
#define CHILD_CELL cell->dependencies
#define cell_col (*parent_loc).col
#define cell_row (*parent_loc).row
#define child_col(cell, c) (cell)->dependencies.children[c]->class.loc.col
#define child_row(cell, c) (cell)->dependencies.children[c]->class.loc.row
#define child_text(cell, c) (cell)->dependencies.children[c]->text
#define checkUnique(cell, p) (cell).dependencies.parents[p]->class.loc.col == (*parent_loc).col && (cell).dependencies.parents[p]->class.loc.row == (*parent_loc).row
#define checkExistChild(cell, p, c) (cell)->class.loc.col == (cell)->dependencies.parents[p]->dependencies.children[c]->class.loc.col && (cell)->class.loc.row == (cell)->dependencies.parents[p]->dependencies.children[child]->class.loc.row
#define checkExistParent(cell, cp, cc) (cell)->class.loc.col == (cell)->dependencies.children[cc]->dependencies.parents[cp]->class.loc.col && (cell)->class.loc.row == (cell)->dependencies.children[cc]->dependencies.parents[cp]->class.loc.row

//TODO: need to add error, dependencies (fix big ones and circular), implement subtraction

typedef struct loc_t{ //location of the cell in enum values
    COL col;
    ROW row;
}loc_t;

typedef struct depend{
    struct cell_t **parents; //cells it is dependent on
    struct cell_t **children; //cells dependent on it
    size_t parent_amt; //amt
    size_t children_amt; //amt
}depend;

typedef struct class{ //add more to this
    DATATYPE type;
    loc_t loc;
}class;

typedef struct cell_t{
        char *text; //Text display inside the cell
        float eval_value; //Evaluated value
        depend dependencies; //contains an array of the dependency per cell
        class class; //contains arbitrary data such as type and location
    }cell_t;

static cell_t model[NUM_COLS][NUM_ROWS];


void model_init() {
    for(size_t col=0;col<NUM_COLS;col++){ //iterate through the entire array and set everything to null as to not leave anything dangling.
        for(size_t row=0;row<NUM_ROWS;row++){
            model[col][row].text = malloc(1);
            model[col][row].text[0] = '\0';
            model[col][row].eval_value = 0;
            model[col][row].dependencies.children = malloc(1);
            model[col][row].dependencies.parents = malloc(1);
            model[col][row].dependencies.children_amt = 0;
            model[col][row].dependencies.parent_amt = 0;
            model[col][row].class.type = DNE;
        }
    }
}

bool parse_number(char** text, float *out){ //parses a string to a number
    char *before = *text; //collect the pre-parsed string.
    *out += strtof(before, text);
    return true; //Parse the string and return 'text' as the continuation.
}

bool get_cell_reference(char col, char** text, int* loc) { //gets the cell reference in comparison to the array
    if(loc == NULL) return false;
        loc[0] = col - 'A';
        loc[1] = strtol(*text+1,NULL,10)-1;
        return true;
}

bool isDigit(char num){ //Checks if the current character is a single digit
    return num >= '0' && num <= '9';
}
bool isCol(char col){ //Checks if the character is within the column restrictions
    return col >= 'A' && col <= 'G';
}

bool isValid(char first){ //Checks if the first character of the input is valid by formula rules
    if(first != '=' && first != '+' && ((first <= '0' || first >= '9') || (first <= '0' && first >= '9'))){
        return false;
    }else if(first == '+' || first == '='){
        return true;
    }
    return true;
}
bool isNull(char null){ //Checks for a null character
    return null == '\0';
}

bool isOperator(char op){ //checks for an operator
    return op == '+';
}

void cellSkip(char **text){ //Skips over the cell text
    if(strlen(*text)>=3){
        *text += 3;
        if(isCol(**text) || isDigit(**text)){
            *text -= 1;
        }
    }else{
        *text += 2;
    }
}

void updateDependencies(cell_t *cell, loc_t *parent_loc){ //When a formula is entered, update the parents and children of respective cells
    bool unique = true;

    //Increase amount of dependencies for each cell involved. should change realloc to double instead.
    for(size_t parent; parent < (*cell).dependencies.parent_amt; parent++){
        if(checkUnique(*cell, parent)){
            unique = false;
        }
    }

#define notEqualLoc (cell->class.loc.col == parent_loc->col && cell->class.loc.col == parent_loc->row)

    if(unique){ //if it is a unique parent/child
    //Increment amts. by 1
    CHILD_CELL.parent_amt++;
    PARENT_CELL(cell_col,cell_row).children_amt++;
    

    //Increase memory
    CHILD_CELL.parents = realloc(CHILD_CELL.parents,sizeof(cell_t)*CHILD_CELL.parent_amt);
    PARENT_CELL(cell_col,cell_row).children = realloc(PARENT_CELL(cell_col,cell_row).children, sizeof(cell_t)*PARENT_CELL(cell_col,cell_row).children_amt);
    
    //Add to pointer array
    CHILD_CELL.parents[CHILD_CELL.parent_amt-1] = &model[cell_col][cell_row];
    PARENT_CELL(cell_col,cell_row).children[PARENT_CELL(cell_col,cell_row).children_amt-1] = cell;
    }else if(!isCol(parent_loc->col)){
        cell->class.type = ERROR;
    }
}

 void checkDependencies(cell_t **cell){ //check for cells dependent on the curr. and reevaluate.

    if((*cell)->dependencies.children_amt >= 1){
        for(size_t child = 0; child < (*cell)->dependencies.children_amt; child++){
            set_cell_value(child_row(*cell, child), child_col(*cell, child), strdup((*cell)->dependencies.children[child]->text));  
        }
    }
}

float eval_expression(char* cell_value, float *sum, cell_t *cell){ //evaluation function to deal with incoming text
    *sum = 0;
    char first = *cell_value;

    if(!isValid(*cell_value)){
        (*cell).class.type = TEXT;
        return 0;
    }else if(isValid(*cell_value) && !isDigit(*cell_value)){
        cell_value++;
    }

    while(!isNull(*cell_value)){ //While not null character -> end of str
        if(isDigit(*cell_value)){ //if between 0-9 for the char

            parse_number(&cell_value, sum); //parse the number
            (*cell).class.type = NUMBER;

        }else if(isCol(*cell_value) && isDigit(*(cell_value+1))){ //if between A to G in ASCII it is a cell reference.

            int* location = malloc(sizeof(int)*2);
            get_cell_reference(*cell_value, &cell_value, location);
            loc_t parent_loc = {
                .col = location[0],
                .row = location[1]
            };

            float found = model[location[0]][location[1]].eval_value; //set a value of the found cell reference to it.

            updateDependencies(cell, &parent_loc);

            free(location);

            cellSkip(&cell_value);

            *sum += found;
            (*cell).class.type = FORMULA;
        }else if(isOperator(*cell_value)){//if it sees an operator
                *sum += eval_expression(cell_value, sum, cell);
        }

        if(isNull(*cell_value)){
            continue;
        }else if(isOperator(*cell_value)){
            cell_value++; //continue through the string
        }else{
            (*cell).class.type = ERROR;
            return *sum;
        }
        
    }


    return *sum;
}

void set_cell_value(ROW row, COL col, char *text) {
    free(model[col][row].text);
    model[col][row].text = text;
    model[col][row].class.loc.col = col;
    model[col][row].class.loc.row = row;

    float val;
    
    model[col][row].eval_value = eval_expression(text, &val, &model[col][row]);
    cell_t *cell = &model[col][row];
    checkDependencies(&cell);
    model[col][row].text = text;
    static char cell_display[CELL_DISPLAY_WIDTH+1];
    snprintf(cell_display,CELL_DISPLAY_WIDTH+1, "%.1f",model[col][row].eval_value);


    if(model[col][row].class.type == ERROR){
        strcpy(cell_display, "ERR:NAN");
    }else if(model[col][row].class.type == TEXT){
        strcpy(cell_display, text);
    }


    update_cell_display(row, col, cell_display);
}

void removeDependencies(cell_t **cell){
    //parent remover
    int parent_amt = (*cell)->dependencies.parent_amt;
    for(size_t parent = 0; parent < parent_amt; parent++){
        for(size_t child = 0; child < (*cell)->dependencies.parents[parent]->dependencies.children_amt;child++){
            if(checkExistChild(*cell, parent, child)){
                (*cell)->dependencies.parents[parent]->dependencies.children_amt--;
                (*cell)->dependencies.parent_amt--;
                //free((*cell)->dependencies.parents[parent]->dependencies.children[child]);
            }
        }
    }
    //child remover
    int child_amt = (*cell)->dependencies.children_amt;
    for(size_t cell_child; cell_child < child_amt; cell_child++){
        for(size_t cell_parent; cell_parent < (*cell)->dependencies.children[cell_child]->dependencies.parent_amt; cell_parent++){
            if(checkExistParent(*cell, cell_parent, cell_child)){
            (*cell)->dependencies.children[cell_child]->dependencies.parent_amt--;
            (*cell)->dependencies.children_amt--;
            //free((*cell)->dependencies.parents[cell_child]->dependencies.children[cell_parent]);
            }
        }  
    }
}

void clear_cell(ROW row, COL col) {
    free(model[col][row].text);
    model[col][row].text[0] = '\0';
    model[col][row].eval_value = 0;
    model[col][row].class.type = DNE;
    cell_t *cell = &model[col][row];
    removeDependencies(&cell); //still breaking on big ones

    update_cell_display(row, col, "");
}

char *get_textual_value(ROW row, COL col) {
    return strdup(model[col][row].text);
}
