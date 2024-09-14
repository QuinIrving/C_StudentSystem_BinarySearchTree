// Assignment N4: Template file!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define FLUSH stdin=freopen(NULL,"r",stdin)
#define FLUSH freopen(NULL,"r",stdin)
#define RMN(str) str[strcspn(str,"\n")]=0

#define MAX_LEN 50

typedef struct node BST_node;

struct node {
    short ID;
    float gpa;
    BST_node *leftChild;
    BST_node *rightChild;
};

// You must implement all the functions below
BST_node* createBST_node(BST_node* root);   // function to create the BST node
BST_node* createBST();                      // function to create the BST
void displayBST(BST_node* root);            // function to display the BST
void insert_node(BST_node** root, BST_node* node );  // function to insert node into the BST.
void removeBST(BST_node** root);            // function to remove BST
void tree_traversal(BST_node*);             // function used in displayBST() to traverse
BST_node* searchBST(BST_node*, short);      // function to return a node with specific ID
void changeBST (BST_node**);                // function called to change ID in a node in BST
void move_node(BST_node**, short, short);   // function used inside changeBST() to delete node with specific ID and then re-insert it into BST.

// You can declare and implement your own function(s) if needed below:
BST_node* tree_minimum (BST_node*, BST_node**);
BST_node* tree_maximum (BST_node*, BST_node**);
BST_node* getNodeParent(BST_node*, BST_node**, short);
void delete_traversal(BST_node*);
short get_ID(BST_node*, int flag);

// Do NOT modify main() function!
int main() {
    printf("\nCreating List of students:\n\n");

    BST_node* root = createBST();

    displayBST(root);

    if (root!=NULL) {
        putchar('\n');
        changeBST(&root); // Note: comment it out if you don't implement it!
        displayBST(root);
    }

    removeBST(&root);

    return 0;
}


// function to display the BST. No need to change it!
void displayBST(BST_node* root){

    printf("\n------------------\n");
    printf(" ID\t  GPA\n");
    printf("------------------\n");

    if(root == NULL) {
        printf("List of students is empty.\n");
    }
    else  {
        tree_traversal(root);
    }
}



// Functions below are declared so template can compile!
// Check all the function prototypes above main() function!


// function to create the BST
BST_node* createBST() {

    BST_node* root = NULL;
    BST_node* newNode = NULL;
    do {
        newNode = createBST_node(root);
        if (newNode != NULL) {
            insert_node(&root, newNode);
        }
    } while(newNode != NULL);
    return root;
}


// function called to change ID in a node in BST
void changeBST (BST_node** root) {

    short id;
    do {
        // You must implement it!
        printf("\nInput ID you want to change (4 digits): ");
        id = get_ID(*root, 0);

        if (id == -1) {
            printf("Student with id=%d not found!", id);
            continue;
        }

        if (id == -2) {
            return;
        }

        if (searchBST(*root, id) == NULL) {
            printf("Student with id=%d not found!", id);
            id = -1;
        }

    } while(id == -1);

    short newID;
    do {
        printf("Input new ID (4 digits): ");

        newID = get_ID(*root, 1);
        if (newID == -3) {
            continue;
        }

    } while(newID == -1 || newID == -2 || newID == -3);

    move_node(root, id, newID);

}

BST_node* getNodeParent(BST_node* root, BST_node** parent, short id) {
    BST_node* current = root;

    while (current != NULL) {
        if (current->leftChild != NULL && current->leftChild->ID == id) {
            *parent = current;
            return current->leftChild;
        }

        if (current->rightChild != NULL && current->rightChild->ID == id) {
            *parent = current;
            return current->rightChild;
        }

        if (current->ID > id) {
            current = current->leftChild;
        } else {
            current = current->rightChild;
        }
    }

    return root;

}

BST_node* tree_minimum (BST_node* current, BST_node** parent) {

    if (current != NULL) {
        if (current->leftChild != NULL) {
            *parent = current;
            tree_minimum(current->leftChild, parent);
        } else if (current->rightChild != NULL) {
            tree_minimum(current->rightChild, parent);
        }
    }
    return (*parent)->leftChild;
}

BST_node* tree_maximum (BST_node* current, BST_node** parent) {

    if (current != NULL) {
        if (current->rightChild != NULL) {
            *parent = current;
            tree_maximum(current->rightChild, parent);
        } else if (current->leftChild != NULL) {
            tree_maximum(current->leftChild, parent);
        }
    }
    return (*parent)->rightChild;
}

void tree_traversal(BST_node* root) {

    if (root != NULL) {
        tree_traversal(root->leftChild);
        printf("%-4d %7.2f\n",root->ID, root->gpa);
        tree_traversal(root->rightChild);
    }
}

void removeBST(BST_node** root) {

    delete_traversal(*root);
    *root = NULL;
}

void delete_traversal(BST_node* root) {

    if (root != NULL) {
        delete_traversal(root->leftChild);
        delete_traversal(root->rightChild);
    }

}

BST_node* createBST_node(BST_node* root) {

    short id;
    float gpa;


    // allocate memory for input string of gpa
    char* gpaString = (char*) calloc(MAX_LEN, sizeof(char));
    if (gpaString == NULL) {
        perror("Error: Failed to allocate heap memory");
        exit(1);
    }

    do {
        printf("Insert student's ID (4 digits): ");

        id = get_ID(root, 1);

        if (id == -2) {
            return NULL;
        }

        // if name entered was blank (go straight to check, so we can exit loop)
        if(id == -1) {
            printf("Incorrect value! Please try again!\n");
            continue;
        }


        if (id == -3) {
            continue;
        }

        do {
            // ask for gpa input
            printf("Insert student's GPA (0-100): ");

            // get gpa input from user
            fgets(gpaString, sizeof(gpaString), stdin);
            RMN(gpaString);

            // if gpa entered was blank (go straight to check to skip creating a node)
            if (strlen(gpaString) < 1) {
                printf("Incorrect value! Please try again!\n");
                continue;
            }

            // convert string to float for gpa
            gpa = strtof(gpaString, NULL);

            // check if gpa is within valid range, if not then skip creating node
            if (gpa < 0.0 || gpa > 100.0) {
                printf("Incorrect value! Please try again!\n");
                continue;
            }
        } while(strlen(gpaString) < 1 || gpa < 0.0 || gpa > 100.0);
        free(gpaString);
    } while(id == -1 || id == -3);
    // so if strlen is 0 (or blank) it stops loop,
    // or if id is 4 digits it stops loop


    BST_node* newNode = (BST_node*) calloc(1, sizeof(BST_node));
    // if error for allocating
    if (newNode == NULL) {
        perror("Error: Failed to allocate heap memory");
        exit(1);
    }

    newNode->ID = id;
    newNode->gpa = gpa;

    return newNode;
}

short get_ID(BST_node* root, int flag) {
    short id;

    // allocate memory for input string of id
    char* sid = (char*) calloc(MAX_LEN, sizeof(char));
    if (sid == NULL) {
        perror("Error: Failed to allocate heap memory");
        exit(1);
    }

    FLUSH;

    // get id input from user
    fgets(sid, MAX_LEN, stdin);
    RMN(sid);

    if (strlen(sid) == 0) {
        return -2;
    }

    if(strlen(sid) != 4) {
        return -1;
    }

    id = atoi(sid);

    if (flag == 1) {
        if (searchBST(root, id) != NULL) {
            printf("Incorrect value! Record with id=%d already exists!\n", id);
            return -3;
        }
    }

    free(sid);

    return id;

}

void insert_node(BST_node** root, BST_node* node) {

    if (*root == NULL) {
        *root = node;
        return;
    }

    BST_node* current = *root;

    //check for place to insert
    while (current != NULL) {
        if (node->ID < current->ID) {

            // go to left child of current.
            // first check if left child is null, if so then just set it
            if (current->leftChild == NULL) {
                current->leftChild = node;
                return;
            }

            // if not we then move to it
            current = current->leftChild;
        } else {

            if (current->rightChild == NULL) {
                current->rightChild = node;
                return;
            }
            current = current->rightChild;
        }
    }
}

BST_node* searchBST(BST_node* root, short id) {

    BST_node* current = root;
    while (current != NULL) {

        if (id == current->ID) {
            return current;
        }
        else if (id < current->ID) {

            // go to left child of current.
            // first check if left child is null, if so then just set it
            if (current->leftChild == NULL) {
                return NULL;
            }

            // if not we then move to it
            current = current->leftChild;
        } else {
            if (current->rightChild == NULL) {
                return NULL;
            }
            current = current->rightChild;
        }
    }
    return current;

}

void move_node(BST_node** root, short id, short newID) {

    BST_node* moveParent = NULL;
    BST_node* sameIDNode = getNodeParent(*root, &moveParent, id);
    BST_node* replacementParent = NULL;
    BST_node* replacementNode = NULL;


    if (sameIDNode->leftChild != NULL || sameIDNode->rightChild != NULL) {
        replacementParent = NULL;
        if (sameIDNode->ID < (*root)->ID) {
            replacementNode = tree_minimum(sameIDNode, &replacementParent);
        } else if (sameIDNode->ID > (*root)->ID) {
            replacementNode = tree_maximum(sameIDNode, &replacementParent);
        } else {
            replacementNode = NULL;
        }

        if (moveParent->leftChild->ID == sameIDNode->ID) {
            moveParent->leftChild = replacementNode;
        } else {
            moveParent->rightChild = replacementNode;
        }

        if (replacementParent->ID == sameIDNode->ID) {
            // attach nodes already done
        } else {
            if (replacementParent->leftChild->ID == replacementNode->ID) {
                replacementParent->leftChild = replacementNode->rightChild;
            } else {
                replacementParent->rightChild = replacementNode->rightChild;
            }
        }

        if (sameIDNode->leftChild != NULL && sameIDNode->leftChild->ID == replacementNode->ID) {
            replacementNode->rightChild = sameIDNode->rightChild;
        } else if (sameIDNode->rightChild != NULL && sameIDNode->rightChild->ID == replacementNode->ID){
            replacementNode->leftChild = sameIDNode->leftChild;
        } else {
            replacementNode->leftChild = sameIDNode->leftChild;
            replacementNode->rightChild = sameIDNode->rightChild;
        }


    } else {
        if (moveParent->leftChild->ID == sameIDNode->ID) {
            moveParent->leftChild = NULL;
        } else {
            moveParent->rightChild = NULL;
        }

    }

    sameIDNode->leftChild = NULL;
    sameIDNode->rightChild = NULL;

    sameIDNode->ID = newID;
    insert_node(root, sameIDNode);

}