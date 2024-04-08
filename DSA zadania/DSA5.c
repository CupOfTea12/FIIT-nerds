/*
Code made by CupOfTea12
@2024
*/

//---LIBRARIES---//
#include <stdio.h>
#include <stdlib.h>
#define COUNT 10

//---STRUCTS---//
//human struct
typedef struct {
    int id;
    char name[13];
    char lastname[13];
    char dob[16];
} Hooman;

//tree nodes
typedef struct NodeTree {
    Hooman data;
    struct NodeTree *left;
    struct NodeTree *right;
    int height;
} NodeTree;

//---METHODS---//

//create node
NodeTree *createNode(Hooman data) {
    NodeTree *newNode = (NodeTree *)malloc(sizeof(NodeTree));
    if (newNode == NULL) {
        printf("Memory issue.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}
//max
int max(int a, int b) {
    return (a > b) ? a : b;
}
//height
int height(NodeTree *node) {
    if (node == NULL)
        return 0;
    return node->height;
}
//get balance
int getBalance(NodeTree *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}
//right rotation
NodeTree *rightRotate(NodeTree *y) {
    NodeTree *x = y->left;
    NodeTree *T2 = x->right;
    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}
//left rotate
NodeTree *leftRotate(NodeTree *x) {
    NodeTree *y = x->right;
    NodeTree *T2 = y->left;
    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}
//insert function
NodeTree *insert(NodeTree *root, Hooman data) {
    if (root == NULL)
        return createNode(data);

    if (data.id < root->data.id)
        root->left = insert(root->left, data);
    else if (data.id > root->data.id)
        root->right = insert(root->right, data);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && data.id < root->left->data.id)
        return rightRotate(root);
    if (balance < -1 && data.id > root->right->data.id)
        return leftRotate(root);
    if (balance > 1 && data.id > root->left->data.id) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && data.id < root->right->data.id) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
//search
void search(NodeTree *root, int id, int *first) {
    if (root == NULL) {
        return;
    }

    NodeTree *result = NULL;
    while (root != NULL) {
        if (root->data.id == id) {
            result = root;
            if (*first == 0) {
                printf("%d %s %s %s", result->data.id, result->data.name, result->data.lastname, result->data.dob);
                ++(*first);
            } else
                printf("\n%d %s %s %s", result->data.id, result->data.name, result->data.lastname, result->data.dob);
            return;
        } else if (root->data.id < id) {
            root = root->right;
        } else {
            root = root->left;
        }
    }
}
//search interval
void searchInterval(NodeTree *root, int id1, int id2, int *first) {
    if (root == NULL) {
        return;
    }

    if (id1 > id2) {
        int temp = id1;
        id1 = id2;
        id2 = temp;
    }

    if (root->data.id >= id1 && root->data.id <= id2) {
        searchInterval(root->left, id1, id2, first);

        if (*first == 0) {
            printf("%d %s %s %s", root->data.id, root->data.name, root->data.lastname, root->data.dob);
            ++(*first);
        } else {
            printf("\n%d %s %s %s", root->data.id, root->data.name, root->data.lastname, root->data.dob);
        }

        searchInterval(root->right, id1, id2, first);
    } else if (root->data.id < id1) {
        searchInterval(root->right, id1, id2, first);
    } else {
        searchInterval(root->left, id1, id2, first);
    }
}
//minimal value node
NodeTree *minValueNode(NodeTree *node) {
    NodeTree *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}
//delete node
NodeTree *deleteNode(NodeTree *root, int id) {
    if (root == NULL)
        return root;

    if (id < root->data.id)
        root->left = deleteNode(root->left, id);
    else if (id > root->data.id)
        root->right = deleteNode(root->right, id);
    else {
        if (root->left == NULL) {
            NodeTree *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            NodeTree *temp = root->left;
            free(root);
            return temp;
        }

        NodeTree *temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data.id);
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
//print tree
void printTree(NodeTree *root, int level) {
    if (root != NULL) {
        printTree(root->right, level + 1);
        for (int i = 0; i < level; i++)
            printf("    ");
        printf("%d %s %s %s\n", root->data.id, root->data.name, root->data.lastname, root->data.dob);
        printTree(root->left, level + 1);
    }
}

void print2DUtil(NodeTree *root, int space) {
    if (root == NULL)
        return;

    space += COUNT;
    print2DUtil(root->right, space);

    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d %s %s %s\n", root->data.id, root->data.name, root->data.lastname, root->data.dob);

    print2DUtil(root->left, space);
}

void print2D(struct NodeTree *root) {
    print2DUtil(root, 0);
}

int main() {
    NodeTree *root = NULL;
    char operation;
    int id, first = 0;
    Hooman hooman;

    while (scanf(" %c", &operation) == 1) {
        switch (operation) {
            case 'i':
                while (scanf("%d %12s %12s %15s", &hooman.id, hooman.name, hooman.lastname, hooman.dob) == 4) {
                    root = insert(root, hooman);
                }
                break;

            case 's':
                ;
                int id1, id2;
                while (scanf("%d", &id1) == 1) {
                    if (scanf("%d", &id2) == 1)
                        searchInterval(root, id1, id2, &first);
                    else {
                        search(root, id1, &first);
                        break;
                    }
                }
                break;

            case 'd':
                if (scanf("%d", &id) != 1) {
                    continue;
                }
                root = deleteNode(root, id);
                break;

            case 'p':
                print2D(root);
                break;

            default:
                break;
        }
    }

    return 0;
}