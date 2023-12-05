#include "model.h"
#include "interface.h"
#include <string.h>

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

#define PARENT_CELL(col,row) model[col][row].dependencies //dependencies of the parent cell
#define CHILD_CELL cell->dependencies //dependencies of the child cell
#define cell_col (*parent_loc).col
#define cell_row (*parent_loc).row
#define child_col(cell, c) (cell)->dependencies.children[c]->class.loc.col //column of the child cell
#define child_row(cell, c) (cell)->dependencies.children[c]->class.loc.row //row of the child cell
#define child_text(cell, c) (cell)->dependencies.children[c]->text //text of the child cell
#define checkUnique(cell, p) (cell).dependencies.parents[p]->class.loc.col == (*parent_loc).col && (cell).dependencies.parents[p]->class.loc.row == (*parent_loc).row //check if the child is unique as to not duplicate itself
//check if the child exists in the parent cell using cell location
#define checkExistChild(cell, p, c) (cell)->class.loc.col == (cell)->dependencies.parents[p]->dependencies.children[c]->class.loc.col && (cell)->class.loc.row == (cell)->dependencies.parents[p]->dependencies.children[child]->class.loc.row
//check if the parent exists in the childs cell using cell location
#define checkExistParent(cell, cp, cc) (cell)->class.loc.col == (cell)->dependencies.children[cc]->dependencies.parents[cp]->class.loc.col && (cell)->class.loc.row == (cell)->dependencies.children[cc]->dependencies.parents[cp]->class.loc.row
//checks if the locations of the parent matches the location of the child
#define notEqualLoc (cell->class.loc.col == parent_loc->col && cell->class.loc.col == parent_loc->row)
typedef struct loc_t{ //location of the cell in enum values
    COL col;
    ROW row;
}loc_t;

typedef struct depend{
    struct cell_t **parents; //cells it is dependent on
    struct cell_t **children; //cells dependent on it
    size_t parent_amt; //amount of parents
    size_t children_amt; //amount of children
}depend;

typedef struct class{ //containing useful identifying data
    DATATYPE type; //type means ERROR, FORMULA, TEXT, NUMBER
    loc_t loc; //location
}class;

typedef struct cell_t{
        char *text; //Text display inside the cell
        float eval_value; //Evaluated value
        depend dependencies; //contains an array of the dependency per cell
        class class; //contains arbitrary data such as type and location
    }cell_t;


static cell_t model[NUM_COLS][NUM_ROWS]; //simulated spreadsheet

void model_init() {
    for(size_t col=0;col<NUM_COLS;col++){ //iterate through the entire array and set everything to null as to not leave anything dangling.
        for(size_t row=0;row<NUM_ROWS;row++){
            model[col][row].text = malloc(1);
            model[col][row].text[0] = '\0'; //set text to null character
            model[col][row].eval_value = 0; //if text is written, remove the impact a formula would see
            model[col][row].dependencies.children = malloc(1); //allocate to not make it null
            model[col][row].dependencies.parents = malloc(1); //allocate to not make it null
            model[col][row].dependencies.children_amt = 0;
            model[col][row].dependencies.parent_amt = 0;
            model[col][row].class.type = DNE; //has not been discovered yet
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
        loc[0] = col - 'A'; //uses ASCII math
        loc[1] = strtol(*text+1,NULL,10)-1; //converts to a long
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
void cellSkip(char **text){ //Skips over the cell text i.e. if text is "A1", this function makes it ""
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

    for(size_t parent = 0; parent < (*cell).dependencies.parent_amt; parent++){ //iterate over each parent
        if(checkUnique(*cell, parent)){ //if it is not a unique parent then prevent it from running
            unique = false;
        }
    }

    if(unique){ //if it is a unique parent/child
    
    //Increment amts. by 1
    CHILD_CELL.parent_amt++;
    PARENT_CELL(cell_col,cell_row).children_amt++;

    //Increase memory, I know it is faster to double it
    CHILD_CELL.parents = realloc(CHILD_CELL.parents,sizeof(cell_t)*CHILD_CELL.parent_amt); //realloc based on the new amount of parents
    PARENT_CELL(cell_col,cell_row).children = realloc(PARENT_CELL(cell_col,cell_row).children, sizeof(cell_t)*PARENT_CELL(cell_col,cell_row).children_amt); //realloc based on the new amount of children
    
    //Add to pointer array
    CHILD_CELL.parents[CHILD_CELL.parent_amt-1] = &model[cell_col][cell_row];
    PARENT_CELL(cell_col,cell_row).children[PARENT_CELL(cell_col,cell_row).children_amt-1] = cell;
    }else if(!(parent_loc->col <= 6)){
        cell->class.type = ERROR;
    }
}

 void checkDependencies(cell_t **cell){ //check for cells dependent on the curr. and reevaluate.

    if((*cell)->dependencies.children_amt >= 1){ //if the updated cell has 1 or more children
        for(size_t child = 0; child < (*cell)->dependencies.children_amt; child++){ //for each child
            set_cell_value(child_row(*cell, child), child_col(*cell, child), strdup((*cell)->dependencies.children[child]->text));  //reevaluate each child cell based on the new value
        }
    }
}

float eval_expression(char* cell_value, float *sum, cell_t *cell){ //evaluation function to deal with incoming text
    *sum = 0;
    char first = *cell_value;

    if(!isValid(*cell_value)){ //initial validation check
        (*cell).class.type = TEXT;
        return *sum;
    }else if(isValid(*cell_value) && !isDigit(*cell_value)){ //if it is a valid first formula character '='
        cell_value++;
    }

    while(!isNull(*cell_value)){ //While not null character -> end of str
        if(isDigit(*cell_value)){ //if between 0-9 for the char

            assert(parse_number(&cell_value, sum)); //parse the number
            (*cell).class.type = NUMBER;

        }else if(isCol(*cell_value) && isDigit(*(cell_value+1))){ //if between A to G in ASCII it is a cell reference.

            int* location = malloc(sizeof(int)*2);
            assert(get_cell_reference(*cell_value, &cell_value, location)); //get the cell location
            loc_t parent_loc = {
                .col = location[0],
                .row = location[1]
            };

            if(parent_loc.col == cell->class.loc.col && parent_loc.row == cell->class.loc.row){ //check self-reference
                cell->class.type = ERROR;
                return 0;
            }

            float found = model[location[0]][location[1]].eval_value; //set a value of the found cell reference to it.
             (*cell).class.type = FORMULA;

            updateDependencies(cell, &parent_loc); //update the cells parents property

            if(cell->dependencies.children[0] == &model[parent_loc.col][parent_loc.row] && model[parent_loc.col][parent_loc.row].dependencies.children[0] == (cell_t *)cell){ //if there is a circular dependency
                cell->class.type = ERROR;
                model[parent_loc.col][parent_loc.row].class.type = ERROR;
                return 0;
            }

            free(location);

            //if(!isCol(*(cell_value+2)) || !isOperator(*(cell_value+2))) cell->class.type = ERROR; attempt at fixing errors

            cellSkip(&cell_value); //skip over cell text

            *sum += found;
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

void set_cell_value(ROW row, COL col, char *text) { //sets the value of cell visually and in the data structure
    if(model[col][row].text != NULL) free(model[col][row].text); //make sure text exists
    model[col][row].text = text;
    model[col][row].class.loc.col = col;
    model[col][row].class.loc.row = row;

    float val;

    model[col][row].eval_value = eval_expression(text, &val, &model[col][row]); //evaluate the cell
    cell_t *cell = &model[col][row];
    if(model[col][row].class.type != ERROR && model[col][row].class.type != TEXT) checkDependencies(&cell); //if it is not an error cell

    model[col][row].text = text;
    static char cell_display[CELL_DISPLAY_WIDTH+1]; //how much can fit in the cell
    snprintf(cell_display,CELL_DISPLAY_WIDTH+1, "%.1f",model[col][row].eval_value);


    if(model[col][row].class.type == ERROR){ //set the text to error
        strcpy(cell_display, "ERR:NAN");
    }else if(model[col][row].class.type == TEXT){ //if its text copy it
        strcpy(cell_display, text);
    }


    update_cell_display(row, col, cell_display);
}

void removeDependencies(cell_t **cell){
    //parent remover
    int parent_amt2 = (*cell)->dependencies.parent_amt;
    for(size_t parent = 0; parent < parent_amt2; parent++){ //iterate over each parent of the cell
        for(size_t child = 0; child < (*cell)->dependencies.parents[parent]->dependencies.children_amt;child++){ //iterate over each child of each parent
            if(checkExistChild(*cell, parent, child)){ //if a child exists in the parent
                (*cell)->dependencies.parents[parent]->dependencies.children_amt--; //dec the amt of children
                (*cell)->dependencies.parent_amt--; //dec the amt of parents
            }
        }
    }
    //child remover
    int child_amt2 = (*cell)->dependencies.children_amt;
    for(size_t cell_child; cell_child < child_amt2; cell_child++){ //iterate over each child of the cell
        for(size_t cell_parent; cell_parent < (*cell)->dependencies.children[cell_child]->dependencies.parent_amt; cell_parent++){ //iterate over each parent of each child
            if(checkExistParent(*cell, cell_parent, cell_child)){ //if a parent exists in the child
            (*cell)->dependencies.children[cell_child]->dependencies.parent_amt--; //dec the amt of parents
            (*cell)->dependencies.children_amt--; //dec the amt of children
            }
        }  
    }
}

void clear_cell(ROW row, COL col) {
    if(model[col][row].text != NULL) free(model[col][row].text);
    model[col][row].text = malloc(1);
    model[col][row].text[0] = '\0'; //set back to null character
    model[col][row].eval_value = 0;
    model[col][row].class.type = DNE; //the value no longer exists so we don't know
    cell_t *cell = &model[col][row];
    checkDependencies(&cell);
    removeDependencies(&cell);

    update_cell_display(row, col, "");
}

char *get_textual_value(ROW row, COL col) {
    return strdup(model[col][row].text); //duplicate the str pointer
}
