
typedef struct Node* LLRBTree;
LLRBTree* create_LLRBTree();
void free_LLRBTree(LLRBTree* root);
int insert_LLRBTree(LLRBTree* root,int value);
int delete_LLRBTree(LLRBTree* root, int value);
int isEmpty_LLRBTree(LLRBTree* root);
int totalNodes_LLRBTree(LLRBTree* root);
int height_LLRBTree(LLRBTree* root);
int search_LLRBTree(LLRBTree* root, int value);
void preOrder_LLRBTree(LLRBTree* root, int H);
void inOrder_LLRBTree(LLRBTree* root, int H);
void posOrder_LLRBTree(LLRBTree* root, int H);
struct Node* searchNode_LLRBTree(LLRBTree* root, int value);
struct Node * minValue(struct Node* node);
struct Node* inOrderSuccessor(struct Node* root, struct Node *n);
struct Node* maxValue(struct Node* node);
struct Node* inOrderPredecessor(struct Node* root, struct Node* x);
void maxValue_print(struct Node* node);
void minValue_print(struct Node* node);

int color(struct Node *tree);
struct Node* left_rotate(struct Node* x);
struct Node* right_rotate(struct Node* x);
struct Node* new_leaf(int value);
struct Node* insertion(struct Node* tree, int value);
int ret_root(LLRBTree *root);



