#include <stdio.h>
#include <stdlib.h>
#include "LLRBTree.h"

#define RED 1
#define BLACK 0

struct Node{
    int info;
    struct Node *left;
    struct Node *right;
    int color;
};


LLRBTree* create_LLRBTree(){
    LLRBTree* root = (LLRBTree*) malloc(sizeof(LLRBTree));
    if(root != NULL){
        *root = NULL;
    }
    return root;
}

void free_node(struct Node* no){
    if(no == NULL)
        return;
    free_node(no->left);
    free_node(no->right);
    free(no);
    no = NULL;
}

void free_LLRBTree(LLRBTree* root){
    if(root == NULL)
        return;
    free_node(*root);
    free(root);
}

int search_LLRBTree(LLRBTree *root, int value){
    struct Node* current = *root;
    if(root == NULL)
        return 0;

    while(current != NULL){
        if(value == current->info){
            return 1;
        }
        if(value > current->info)
            current = current->right;
        else
            current = current->left;
    }
    return 0;
}

struct Node* left_rotation(struct Node* A){
    struct Node* B = A->right;
    A->right = B->left;
    B->left = A;
    B->color = A->color;
    A->color = RED;
    return B;
}

struct Node* right_rotation(struct Node* A){
    struct Node* B = A->left;
    A->left = B->right;
    B->right = A;
    B->color = A->color;
    A->color = RED;
    return B;
}

int color(struct Node* H){
    if(H == NULL)
        return BLACK;
    else
        return H->color;
}

void change_color(struct Node* H){
    H->color = !H->color;
    if(H->left != NULL)
        H->left->color = !H->left->color;
    if(H->right != NULL)
        H->right->color = !H->right->color;
}


/*struct Node* insert_node(struct Node* H, int value, int *resp){
    if(H == NULL){
        struct Node *novo;
        novo = (struct Node*)malloc(sizeof(struct Node));
        if(novo == NULL){
            *resp = 0;
            return NULL;
        }

        novo->info = value;
        novo->color = RED;
        novo->right = NULL;
        novo->left = NULL;
        *resp = 1;
        return novo;
    }

    if(value == H->info)
        *resp = 0;
    else{
        if(value < H->info)
            H->left = insert_node(H->left,value,resp);
        else
            H->right = insert_node(H->right,value,resp);
    }


    if(color(H->right) == RED && color(H->left) == BLACK)
        H = left_rotation(H);


    if(color(H->left) == RED && color(H->left->left) == RED)
        H = right_rotation(H);


    if(color(H->left) == RED && color(H->right) == RED)
        change_color(H);

    return H;
}
*/
int insert_LLRBTree(LLRBTree* root, int value){

    *root = insertion(*root,value);
    if((*root) != NULL)
        (*root)->color = BLACK;

    return 1;
}

struct Node* balance(struct Node* H){

    if(color(H->right) == RED)
        H = left_rotation(H);


    if(H->left != NULL && color(H->right) == RED && color(H->left->left) == RED)
        H = right_rotation(H);

    if(color(H->left) == RED && color(H->right) == RED)
        change_color(H);

    return H;
}

struct Node* move_redNode_to_left(struct Node* H){
    change_color(H);
    if(color(H->right->left) == RED){
        H->right = right_rotation(H->right);
        H = left_rotation(H);
        change_color(H);
    }
    return H;
}

struct Node* move_redNode_to_right(struct Node* H){
    change_color(H);
    if(color(H->left->left) == RED){
        H = right_rotation(H);
        change_color(H);
    }
    return H;
}

struct Node* delete_smaller(struct Node* H){
    if(H->left == NULL){
        free_node(H);
        return NULL;
    }
    if(color(H->left) == BLACK && color(H->left->left) == BLACK)
        H = move_redNode_to_left(H);

    H->left = delete_smaller(H->left);
    return balance(H);
}


struct Node* search_smaller(struct Node* current){
    struct Node *no1 = current;
    struct Node *no2 = current->left;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->left;
    }
    return no1;
}

struct Node* delete_node(struct Node* H, int value){
    if(value < H->info){
        if(color(H->left) == BLACK && color(H->left->left) == BLACK)
            H = move_redNode_to_left(H);

        H->left = delete_node(H->left, value);
    }else{
        if(color(H->left) == RED)
            H = right_rotation(H);

        if(value == H->info && (H->right == NULL)){
            free(H);
            return NULL;
        }

        if(color(H->right) == BLACK && color(H->right->left) == BLACK)
            H = move_redNode_to_right(H);

        if(value == H->info){
            struct Node* x = search_smaller(H->right);
            H->info = x->info;
            H->right = delete_smaller(H->right);
        }else
            H->right = delete_node(H->right, value);
    }
    return balance(H);
}

int delete_LLRBTree(LLRBTree *root, int value){
    if(search_LLRBTree(root,value)){
        struct Node* h = *root;
        *root = delete_node(h,value);
		/*free_node(h);*/
        if(*root != NULL)
            (*root)->color = BLACK;
        return 1;
    }else
        return 0;
}

int isEmpty_LLRBTree(LLRBTree *root){
    if(root == NULL)
        return 1;
    if(*root == NULL)
        return 1;
    return 0;
}


/*int totalNodes_LLRBTree(LLRBTree *root){
    int alt_left;
    int alt_right;
    if (root == NULL)
        return 0;
    if (*root == NULL)
        return 0;

    alt_left = totalNodes_LLRBTree(&((*root)->left));
    alt_right = totalNodes_LLRBTree(&((*root)->right));
    return (alt_left + alt_right + 1);
}*/

/*int height_LLRBTree(LLRBTree *root){
    int alt_left;
    int alt_right;
    if (root == NULL)
        return 0;
    if (*root == NULL)
        return 0;
    alt_left = height_LLRBTree(&((*root)->left));
    alt_right = height_LLRBTree(&((*root)->right));
    if (alt_left > alt_right)
        return (alt_left + 1);
    else
        return(alt_right + 1);
}*/

void  posOrder_LLRBTree(LLRBTree *root, int H){
    if(root == NULL)
        return;

    if(*root != NULL){
        posOrder_LLRBTree(&((*root)->left),H+1);
        posOrder_LLRBTree(&((*root)->right),H+1);

        if((*root)->color == RED)
            printf("%d ",(*root)->info);
        else
            printf("%d ",(*root)->info);

    }
}

void inOrder_LLRBTree(LLRBTree *root, int H){
    if(root == NULL)
        return;

    if(*root != NULL){
        inOrder_LLRBTree(&((*root)->left),H+1);

        if((*root)->color == RED)
            printf("%d ",(*root)->info);
        else
            printf("%d ",(*root)->info);

        inOrder_LLRBTree(&((*root)->right),H+1);
    }
}

void preOrder_LLRBTree(LLRBTree *root,int H){
    if(root == NULL)
        return;

    if(*root != NULL){
        if((*root)->color == RED)
            printf("%d ",(*root)->info);
        else
            printf("%d ",(*root)->info);

        preOrder_LLRBTree(&((*root)->left),H+1);
        preOrder_LLRBTree(&((*root)->right),H+1);
    }
}


struct Node* searchNode_LLRBTree(LLRBTree *root, int value){
	struct Node* current = *root;
    	int i = 0;
	if(root == NULL)
        return 0;

    while(current != NULL){
        if(value == current->info){
            return current;
        }
        if(value > current->info)
            current = current->right;
        else
            current = current->left;
        i++;

    }
    printf("erro\n");
    return current;
}

struct Node * minValue(struct Node* node){
    struct Node* current = node;


    while(current->left != NULL){
        current = current->left;
    }
    return current;
}

struct Node* inOrderSuccessor(struct Node *root, struct Node *n){

    struct Node *succ = NULL;
    if(n->right != NULL){
        struct Node *teste = minValue(n->right);
        printf("%d\n", teste->info);
        return minValue(n->right);
    }




    while(root != NULL){
        if(n->info < root->info){
            succ = root;
            root = root->left;
        }
        else if(n->info > root->info)
            root = root->right;
        else
           break;
    }
    if(succ != NULL){
        printf("%d\n", succ->info);
    }else{
        printf("erro\n");
    }

    return succ;
}

struct Node* maxValue(struct Node* node){
    struct Node* n = node;
    while(n->right != NULL)
        n = n->right;
    return n;
}

struct Node* inOrderPredecessor(struct Node* root, struct Node* x){

    struct Node *predecessor = NULL;
    if(x->left != NULL){
        struct Node *teste2 = maxValue(x->left);
        printf("%d\n", teste2->info);
        return maxValue(x->left);
    }



    while (root != NULL){
        if (x->info > root->info){
            predecessor = root;
            root = root->right;
        }
        else if (x->info < root->info)
            root = root->left;
        else
           break;
    }
    if(predecessor != NULL){
        printf("%d\n", predecessor->info);
    }else{
        printf("erro\n");
    }
    return predecessor;
}

void maxValue_print(struct Node* node){
    struct Node* n = node;
    while(n->right != NULL)
        n = n->right;

    printf("%d\n", n->info);
}

void minValue_print(struct Node* node){
    struct Node* current = node;


    while(current->left != NULL){
        current = current->left;
    }
    printf("%d\n", current->info);
}

int resolve_color(struct Node *tree){
  return tree ? tree->color : BLACK;
}


struct Node * left_rotate(struct Node *x){
  struct Node *y = x->right;
  x->right = y->left;
  y->left = x;

  return y;
}

struct Node * right_rotate(struct Node *x){
  struct Node *y = x->left;
  x->left = y->right;
  y->right = x;

  return y;
}

struct Node * new_leaf(int value){
  struct Node *leaf = (struct Node *) malloc(sizeof(struct Node));
  leaf->info = value;
  leaf->color = 1;
  leaf->left = NULL;
  leaf->right = NULL;

  return leaf;
}

struct Node * insertion(struct Node *tree, int value){
    if(tree == NULL)
    return new_leaf(value);

  if (value < tree->info) {
    tree->left = insertion(tree->left, value);
    if (resolve_color(tree->left) == RED) {
      if (resolve_color(tree->right) == RED) {
        if (resolve_color(tree->left->left) == RED || resolve_color(tree->left->right) == RED){
          tree->left->color = BLACK;
          tree->right->color = BLACK;
          tree->color = RED;
        }
      }
      else {
        if (resolve_color(tree->left->right) == RED) {
          tree->left = left_rotate(tree->left);
        }
        if (resolve_color(tree->left->left) == RED) {
          tree = right_rotate(tree);
          tree->color = BLACK;
          tree->right->color = RED;
        }
      }
    }
  }
  else {
    tree->right = insertion(tree->right, value);
    if (resolve_color(tree->right) == RED) {
      if (resolve_color(tree->left) == RED) {
        if (resolve_color(tree->right->right) == RED || resolve_color(tree->right->left) == RED) {
          tree->right->color = BLACK;
          tree->left->color = BLACK;
          tree->color = RED;
        }
      }
      else {
        if (resolve_color(tree->right->left) == RED) {
          tree->right = right_rotate(tree->right);
        }
        if (resolve_color(tree->right->right) == RED) {
          tree = left_rotate(tree);
          tree->color = BLACK;
          tree->left->color = RED;
        }
      }
    }
  }

  return tree;
}

int ret_root(LLRBTree *root){
    struct Node* current = *root;
    if(root != NULL){
      return current->info;
    }else{
        return 0;
    }
}


