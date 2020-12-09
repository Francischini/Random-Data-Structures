/*
	Gabriel Francischini de Souza
	
    This is a Left-Leaning Red Black Tree with functions like insertion, search, deletion, types of printing, successor/predecessor of a node.
	All heap blocks were freed with Valgrind (no memory leaks are possible).

    Input:
    First line contain the number of operations.
    If 1 is given, the program reads a new integer and will insert it on the tree.
    If 2 is given, the program reads a new integer and returns the successor of the given number.
    If 3 is given, the program reads a new integer and returns the predecessor of the given number.
    If 4 is given, returns the maximum value of the tree.
    If 5 is given, returns the minimum value of the tree.
    If 6 is given, prints the tree preOrder.
    If 7 is given, prints the tree inOrder.
    If 8 is given, prints the tree posOrder.
 */



#include <stdio.h>
#include <stdlib.h>
#include "LLRBTree.h"

int main(){
    LLRBTree * root = create_LLRBTree();

    struct Node* aux = NULL;
    struct Node* aux2 = NULL;
    int n, i, x, o;
    int count = 0, empty = 0;
    int johnson = 0;
	int vector[100]; /*Hopefully the user doesn't want to do more than 100 operations in this tree, otherwise we should not use ISO C90 and then fix it with a variable length array*/

    scanf("%d", &n);
    

    for(i = 0; i < n; i++){
        scanf("%d", &o);
        if(o == 1){
            scanf("%d", &x);
            vector[count] = x;
            count++;
            insert_LLRBTree(root, x);
        }
        else if(o == 2){
            scanf("%d", &x);
            aux = searchNode_LLRBTree(root, x);
            inOrderSuccessor(*root, aux);
        }
        else if(o == 3){
            scanf("%d", &x);
            aux2 = searchNode_LLRBTree(root, x);
            inOrderPredecessor(*root, aux2);
        }
        else if(o == 4){
            maxValue_print(*root);
        }
        else if(o == 5){
            minValue_print(*root);
        }
        else if(o == 6){
            preOrder_LLRBTree(root, 0);
            printf("\n");
        }
        else if(o == 7){
            inOrder_LLRBTree(root, 0);
            printf("\n");
        }
        else if(o == 8){
            posOrder_LLRBTree(root, 0);
            printf("\n");
        }else{
            printf("Error\n");
        }
    }

    /*Deallocating Memory*/
    for(i = 0; i < count+1; i++){
        delete_LLRBTree(root,vector[i]);
    }

	free_LLRBTree(root);
    empty = isEmpty_LLRBTree(root);
    printf("Deallocated Memory? %s\n", empty ? "true" : "false");


    return 0;
}

