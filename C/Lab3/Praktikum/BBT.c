/* Bukan Budokai Tenkaichi
https://www.hackerrank.com/contests/sdd-m3/challenges/bukan-budokai-tenkaichi
Tournament
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct AVLNode {
    int id, ap, height, BF;
    struct AVLNode *left, *right;
} AVLNode;

typedef struct AVLTree {
    AVLNode *root;
    unsigned int size;
} AVLTree;

typedef struct List {
    int id, ap;
    struct List *next;  
} List;

// BASE FUNCTION
void init(AVLTree *tree);
AVLNode *createNode(int id, int ap);
void insert(AVLTree *tree, int id, int ap);

// UTILITY FUNCTION
bool find(AVLNode *node, int id);
int findMin(AVLNode *node);
int findMax(AVLNode *node);
AVLNode *leftRotation(AVLNode *node);
AVLNode *rightRotation(AVLNode *node);
void inorder(AVLNode *node);

// HELPER FUNCTION
int Max(int a, int b);
AVLNode *_insert(AVLNode *node, int id, int ap);
void update(AVLNode *node);
AVLNode *balance(AVLNode *node);
AVLNode *leftLeftCase(AVLNode *node);
AVLNode *leftRightCase(AVLNode *node);
AVLNode *rightRightCase(AVLNode *node);
AVLNode *rightLeftCase(AVLNode *node);

// Custom
void printWinner(int id);
void printCharacter(int id);
void make_EmptyBattlefield(AVLTree *tree, int banyak);
void assign_BattleField(AVLNode *node, List **in);
void changeId(AVLNode *node);

// List
List *createLNode(int id, int ap);
void pushFront(List **head, int id, int ap);
void pushBack(List **head, int id, int ap);
void popFront(List **head);
void fight(AVLNode *root);

int ronde = 1;

int main(void) {
    AVLTree tree;
    init(&tree);

    // Get banyak pemain
    int loop;
    scanf("%d", &loop);

    List *in = NULL;
    for (int i = 0; i < loop; i++) {
        int id, ap;
        scanf("%d %d", &id, &ap); // Get player's id and ap
        pushBack(&in, id, ap);
    }

    make_EmptyBattlefield(&tree, loop);

    assign_BattleField(tree.root, &in);

    fight(tree.root);

    return 0;
}

// Custom
void fight(AVLNode *root) {
    if (!root || root->id != 0) {
        return;
    }
    fight(root->left);
    fight(root->right);

    // Compare ap
    if (root->left->ap >= root->right->ap) {
        root->id = root->left->id;
        root->ap = root->left->ap - root->right->ap;
    }
    else {
        root->id = root->right->id;
        root->ap = root->right->ap - root->left->ap;
    }
    if (root->ap == 0) {
        root->id = -1;
    }
    printWinner(root->id);
}

void assign_BattleField(AVLNode *node, List **in) {
	if (!node || node->id != 0) return;
	
	// Insert new node in every leaf
        if (!node->left) {
		AVLNode *new = createNode((*in)->id, (*in)->ap);
		popFront(in);
		node->left = new;
	}
	if (!node->right) {
		AVLNode *new = createNode((*in)->id, (*in)->ap);
		popFront(in);
		node->right = new;
	}

	assign_BattleField(node->left, in);
	assign_BattleField(node->right, in);
}

void make_EmptyBattlefield(AVLTree *tree, int banyak) {
    for (int i = 1; i < banyak; i++) {
        insert(tree, i, 0); // id = i, ap = 0
    }
    changeId(tree->root); // id = 0
}

void changeId(AVLNode *node) {
    if (node) {
        changeId(node->left);
        node->id = 0;
        changeId(node->right);
    }
}

void printWinner(int id) {
    printf("Pemenang pertarungan ke-%d: ", ronde++);
    // printf("(%d)", id);
    printCharacter(id);
}

// List
void popFront(List **head) {
    if (*head) {
        List *temp = *head;
        *head = temp->next;
        temp->next = NULL;
        free(temp);
    }
}

void pushBack(List **head, int id, int ap) {

    if (!(*head)) {
        pushFront(head, id, ap);
        return;
    }
    else {
        List *n = createLNode(id, ap);
        List *trav = *head;
        while (trav->next) {
            trav = trav->next;
        }
        trav->next = n;
    }
}

void pushFront(List **head, int id, int ap) {
    
    // Make new node
    List *n = createLNode(id, ap);

    n->next = *head;
    *head = n;
    return;
}

List *createLNode(int id, int ap) {
    List *n = malloc(sizeof(List));
    n->id = id;
    n->ap = ap;
    n->next = NULL;
    return n;
}

// BASE FUNCTION
void init(AVLTree *tree) {
    tree->root = NULL;
    tree->size = 0u;
}

AVLNode *createNode(int id, int ap) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->id = id;
    newNode->ap = ap;
    newNode->height = newNode->BF = 0;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insert(AVLTree *tree, int id, int ap) {
    tree->root = _insert(tree->root, id, ap);
    tree->size++;
}

AVLNode *_insert(AVLNode *node, int id, int ap) {
    if (!node)
        return createNode(id, ap);

    else if (id < node->id) {
        node->left = _insert(node->left, id, ap);
    }

    else if (id > node->id) {
        node->right = _insert(node->right, id, ap);
    }
    update(node);
    return balance(node);
}


// UTILITY FUNCTION
bool find(AVLNode *node, int id) {
    AVLNode *trav = node;

    while (trav) {
        if (id < trav->id)
            trav = trav->left;

        else if (id > trav->id)
            trav = trav->right;

        else
            return true;
    }
    return false;
}

int findMin(AVLNode *node) {
    while (node->left) {
        node = node->left;
    }
    return node->id;
}

int findMax(AVLNode *node) {
    while (node->right) {
        node = node->right;
    }
    return node->id;
}

void inorder(AVLNode *node) {
    if (node) {
        inorder(node->left);
        printf("%d ", node->id);
        inorder(node->right);
    }
}

AVLNode *leftRotation(AVLNode *node) {
    AVLNode* newParent = node->right;
    node->right = newParent->left;
    newParent->left = node;
    update(node);
    update(newParent);
    return newParent;
}

AVLNode *rightRotation(AVLNode* node) {
    AVLNode* newParent = node->left;
    node->left = newParent->right;
    newParent->right = node;
    update(node);
    update(newParent);
    return newParent;
}


// HELPER FUNCTION
int Max(int a, int b) {
    return (a > b)? a : b;
}

void update(AVLNode *node)  {
    int leftNodeHeight = (!node->left)? -1 : node->left->height;
    int rightNodeHeight = (!node->right)? -1 : node->right->height;

    node->height = 1 + Max(leftNodeHeight, rightNodeHeight);

    node->BF = rightNodeHeight - leftNodeHeight;
}

AVLNode *balance(AVLNode *node) {
    // Left heavy subtree
    if (node->BF == -2) {
        if (node->left->BF <= 0) { 
            return leftLeftCase(node);
        }
        else {
            return leftRightCase(node);
        }
    }
    // Right heavy subtree
    else if (node->BF == 2) {
        if (node->right->BF >= 0) {
            return rightRightCase(node);
        }
        else { 
            return rightLeftCase(node);
        }
    }
    // Node either has a balance factor of 0, +1 or -1 which is fine
    return node;
}

AVLNode *leftLeftCase(AVLNode *node) {
    return rightRotation(node);
}

AVLNode *leftRightCase(AVLNode *node) {
    node->left  = leftRotation(node->left);
    return leftLeftCase(node);
}

AVLNode *rightRightCase(AVLNode *node) {
    return leftRotation(node);
}

AVLNode *rightLeftCase(AVLNode *node) {
    node->right = rightRotation(node->right);
    return rightRightCase(node);
}

void printCharacter(int id) {
    if(id == -1){
        printf("Tidak ada pemenang\n");
        return;
    }
    switch(id){
        case 1: printf("Elpis\n");
                break;
        case 2: printf("Leonard\n");
                break;
        case 3: printf("Haza\n");
                break;
        case 4: printf("Pupuro\n");
                break;
        case 5: printf("Horus\n");
                break;
        case 6: printf("Xiwangmu\n");
                break;
        case 7: printf("Nuwa\n");
                break;
        case 8: printf("Yog\n");
                break;
        case 9: printf("Giemsa\n");
                break;
        case 10: printf("Reimu\n");
                break;
        case 11: printf("Cang Bi\n");
                break;
        case 12: printf("Radha\n");
                break;
        case 13: printf("Aurora\n");
                break;
        case 14: printf("Astrid\n");
                break;
        case 15: printf("Ralph\n");
                break;
        case 16: printf("Shamash\n");
                break;
        case 17: printf("Enlil\n");
                break;
        case 18: printf("Marduk\n");
                break;
        case 19: printf("Veronica\n");
                break;
        case 20: printf("Marisa\n");
                break;
        case 21: printf("Spencer\n");
                break;
        case 22: printf("Diamond\n");
                break;
        case 23: printf("Amber\n");
                break;
        case 24: printf("Jade\n");
                break;
        case 25: printf("Sapphire\n");
                break;
        case 26: printf("Ruby\n");
                break;
        case 27: printf("Lyndis\n");
                break;
        case 28: printf("Florina\n");
                break;
        case 29: printf("Fiora\n");
                break;
        case 30: printf("Sakuya\n");
                break;
        case 31: printf("Farina\n");
                break;
        case 32: printf("Nino\n");
                break;
        case 33: printf("Renault\n");
                break;
        case 34: printf("Eirika\n");
                break;
        case 35: printf("Vanessa\n");
                break;
        case 36: printf("Tana\n");
                break;
        case 37: printf("Syrene\n");
                break;
        case 38: printf("Amelia\n");
                break;
        case 39: printf("Joshua\n");
                break;
        case 40: printf("Alice\n");
                break;
        case 41: printf("Hansekyo\n");
                break;
        case 42: printf("Dwuaykicong\n");
                break;
        case 43: printf("NETral\n");
                break;
        case 44: printf("iNSANiTY\n");
                break;
        case 45: printf("Vinseks\n");
                break;
        case 46: printf("Aiedail\n");
                break;
        case 47: printf("Heisser\n");
                break;
        case 48: printf("MAXiMUSE\n");
                break;
        case 49: printf("p03tato\n");
                break;
        case 50: printf("Youmu\n");
                break;
        case 51: printf("Ikta\n");
                break;
        case 52: printf("Franz\n");
                break;
        case 53: printf("Zephiel\n");
                break;
        case 54: printf("Idunn\n");
                break;
        case 55: printf("Shanna\n");
                break;
        case 56: printf("thea\n");
                break;
        case 57: printf("Juno\n");
                break;
        case 58: printf("Yaisyeky\n");
                break;
        case 59: printf("Gerik\n");
                break;
        case 60: printf("Mayumi\n");
                break;
        case 61: printf("Cecilia\n");
                break;
        case 62: printf("Sophia\n");
                break;
        case 63: printf("Douglas\n");
                break;
        case 64: printf("Duessel\n");
                break;
    }
}
