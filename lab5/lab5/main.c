#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct bst_node *bst;

struct bst_node {
    int value;
    bst left, right;
};

void bst_print_elements(bst tree) {
    if (tree != NULL) {
        bst_print_elements(tree->left);
        printf("%d, ", tree->value);
        bst_print_elements(tree->right);
    }
}

void bst_print(bst tree) {
    printf("{");
    bst_print_elements(tree);
    printf("}\n");
}

bool bst_insert(bst *tree, int value) {
    // TODO: Task 1: insert 'value' into 'tree'.
    struct bst_node *newNode = malloc(sizeof(struct bst_node));
    if(newNode == NULL) return false; //mem failed
    
    //Set node
    newNode->value = value;
    newNode->right = newNode->left = NULL;


    if(*tree == NULL){
        *tree = newNode; //tree points at newNode
        return true;
    }else if((*tree)->value > value){ //Insert right
        return bst_insert(&((*tree)->left), value);
    }else if((*tree)->value < value){ //Insert left
        return bst_insert(&((*tree)->right), value);
    }

    free(newNode); //free if could not insert
    return false;
}

bst min(bst tree){
    while(tree->left != NULL){ //while not at min value
         tree = tree->left;   
        }
    return tree;
}

bool bst_remove(bst *tree, int value) {
    // TODO: Task 2: remove 'value' from 'tree'.
    if(*tree == NULL){
        return false;
    }
    
    if((*tree)->value > value){ //traverse left
        return bst_remove(&((*tree)->left), value);
    }else if((*tree)->value < value){ //traverse right
        return bst_remove(&((*tree)->right), value);
    }else{
        if((*tree)->left == NULL){ //If left is NULL
            bst temp = *tree;
            *tree = (*tree)->right;
            free(temp);
        }else if((*tree)->right == NULL){ //If right is NULL
            bst temp = *tree;
            *tree = (*tree)->left;
            free(temp);
        }else{
            bst temp = min((*tree)->right); //find min value
            (*tree)->value = temp->value; //set temp

            bst_remove(&((*tree)->right), temp->value); //recurse
        }
        return true;
    }

    return false;
}

bst postOrderInsert(bst tree, bst result){ //traverse postorder and insert at beginning
    if(tree != NULL){
    bst_insert(&result, tree->value); //insert curr
    postOrderInsert(tree->left, result); //go left as far
    postOrderInsert(tree->right, result); //go right as far
    }
    return result;
}

bst bst_union(bst tree1, bst tree2){
    bst result = NULL; //null tree
    result = postOrderInsert(tree1, result); //add tree1
    result = postOrderInsert(tree2, result); //add tree2
    return result;
}

bst postOrderIntersect(bst tree1, bst tree2, bst *result) {
    if (tree1 != NULL) {
        postOrderIntersect(tree1->left, tree2, result);
        postOrderIntersect(tree1->right, tree2, result); //postOrder traversal of the bst

        if (bst_remove(&tree2, tree1->value)) { //If successfully removes, means it exists, therefore add to resultant tree
            bst_insert(result, tree1->value);
        }
    }
    return *result;
}

bst bst_intersection(bst tree1, bst tree2) {
    bst result = NULL; // Initialize an empty tree for the intersection
    result = postOrderIntersect(tree1, tree2, &result);
    return result;
}

int main() {
    // Initialize two trees.
    bst tree1 = NULL, tree2 = NULL;

    assert(bst_insert(&tree1, 1));
    assert(bst_insert(&tree1, 9));
    assert(bst_insert(&tree1, 2));
    assert(bst_insert(&tree1, 7));
    assert(bst_insert(&tree1, 0));
    assert(bst_insert(&tree1, 3));
    assert(bst_insert(&tree1, 13));
    assert(bst_insert(&tree1, 5));
    assert(!bst_insert(&tree1, 3));

    // Should print: {0, 1, 2, 3, 5, 7, 9, 13, }
    bst_print(tree1);

    assert(bst_insert(&tree2, 12));
    assert(bst_insert(&tree2, 13));
    assert(bst_insert(&tree2, 1));
    assert(bst_insert(&tree2, 0));
    assert(bst_insert(&tree2, 19));
    assert(bst_insert(&tree2, 7));
    assert(!bst_insert(&tree2, 13));
    assert(bst_insert(&tree2, 5));

    // Should print: {0, 1, 5, 7, 12, 13, }
    bst_print(tree2);

    // Should print: {0, 1, 2, 3, 5, 7, 9, 12, 13, 19, }
    bst union_1_2 = bst_union(tree1, tree2);
    bst_print(union_1_2);

    // Should print: {0, 1, 5, 7, 13, }
    bst intersection_1_2 = bst_intersection(tree1, tree2);
    bst_print(intersection_1_2);

    return 0;
}
