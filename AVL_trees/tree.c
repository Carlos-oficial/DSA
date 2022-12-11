#include <stdio.h>
#include <stdlib.h>
#define COUNT 2

#define max(a, b) (a > b ? a : b)
//height of Null is 0
#define height(tree) (tree ? (tree->height) : 0)

typedef struct _AVL AVLTree;
struct _AVL
{
    int content;
    unsigned int height;
    AVLTree *left;
    AVLTree *right;
};

void in_order_aux(AVLTree *root)
{
    if (root == NULL)
        printf("*");
    else
    {
        printf("(");
        in_order_aux(root->left);
        printf("<-%d->", root->content);
        in_order_aux(root->right);
        printf(")");
    }
}

void in_order(AVLTree *root)
{
    printf("height: %d",root->height);
    in_order_aux(root);
    printf("\n");
}

void print2DUtil(AVLTree* root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->content);
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(AVLTree* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

AVLTree *new(int n)
{
    AVLTree *new = malloc(sizeof(AVLTree));
    new->content = n;
    new->height = 0;
    new->left = NULL;
    new->right = NULL;
    return new;
}

void swap(void *a, void *b)
{
    void *c = a;
    a = b;
    b = c;
}

AVLTree *rotate_left(AVLTree *root)
{
    if (root->right == NULL) // impssible to rotate
        return root;
    AVLTree *A = root;
    AVLTree *B = root->left;
    AVLTree *C = root->right;
    A->right = C->left;
    C->left = A;

    A->height = 1 + max(height(A->left), height(A->right));
    C->height = 1 + max(height(C->left), height(C->right));
    return C;
}

AVLTree *rotate_right(AVLTree *root)
{
    if (root->left == NULL) // impssible to rotate
        return root;
    AVLTree *A = root;
    AVLTree *B = root->left;
    AVLTree *C = root->right;
    A->left = B->right;
    B->right = A;

    // updating height
    A->height = 1 + max(height(A->left), height(A->right));
    B->height = 1 + max(height(B->left), height(B->right));
    return B;
}

int tilted(AVLTree *tree)
{
    return height(tree->right) - height(tree->left);
}

AVLTree *insert(AVLTree *root, int n)
{
    if (root == NULL)
        return new (n);
    if (n < root->content)
        root->left = insert(root->left, n);
    else
        root->right = insert(root->right, n);

    // updating height
    root->height = 1 + max(height(root->left), height(root->right));

    // balancing the tree
    int tilt = tilted(root);
    if (tilt > 1)
        root = rotate_left(root);
    if (tilt < -1)
        root = rotate_right(root);
    return root;
}

int main()
{

    int arr[] = {4, 64, 31, 17, 10, 29, 12, 58, 88, 34, 46, 3, 97, 96};
    AVLTree *tree = NULL;
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        tree = insert(tree, arr[i]);
    }
    print2D(tree);
    return 0;
}