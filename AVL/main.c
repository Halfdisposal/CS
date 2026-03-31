#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>



typedef struct Node {
    int key;
    int h;
    struct Node *l, *r, *p;
} Node;


int max(int x, int y) {
    return x > y ? x : y;
}

void printTree(Node* node, char* indent, bool isLeft) {
    if (node == NULL) {
        return;
    }

    char newIndent[256];

    strcpy(newIndent, indent);
    strcat(newIndent, isLeft ? "|    " : "    ");
    printTree(node->r, newIndent, false);

    // Print Current Node
    printf("%s", indent);
    printf("%s", isLeft ? "^- " : "v- ");
    printf("%d(%d)\n", node->key, node->h);

    // Process Left Child
    strcpy(newIndent, indent);
    strcat(newIndent, isLeft ? "    " : "|    ");
    printTree(node->l, newIndent, true);
}

Node* create_node(int key) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->h = 0;
    n->l = NULL;
    n->r = NULL;
    n->p = NULL;
    return n;
}



// Height calculation as per Slide 14:
// x.h = 1 + max(x.left.h, x.right.h)
// NIL nodes have height 0
int get_new_h(Node* x) {
    if (x == NULL) return 0;
    int lh = (x->l != NULL) ? x->l->h : 0;
    int rh = (x->r != NULL) ? x->r->h : 0;
    return 1 + max(lh, rh);
}

// LEFT-ROTATE(T, x) — Slides 11-15
// Rotates left around x; x's right child y becomes the new subtree root.
// Heights of x and y are recomputed after pointer changes (Slide 14).
// Returns the new subtree root y.
Node* left_rotation(Node** root, Node* x) {
    Node* y = x->r;          // y = x.right  (Slide 11)

    // Reposition beta (Slide 11)
    x->r = y->l;
    if (y->l != NULL) y->l->p = x;

    // Connect y to x's parent (Slide 12)
    y->p = x->p;
    if (x->p == NULL) *root = y;          // x was root → y becomes root
    else if (x == x->p->l) x->p->l = y;    // x was left child
    else x->p->r = y;                       // x was right child

    // Reconnect x and y (Slide 13)
    y->l = x;
    x->p = y;

    // Recompute heights — x first (it is now lower), then y (Slide 14)
    x->h = get_new_h(x);
    y->h = get_new_h(y);

    return y;  // return new subtree root (Slide 15)
}

// RIGHT-ROTATE(T, y) — symmetric to LEFT-ROTATE (Slide 16)
// Returns the new subtree root x.
Node* right_rotation(Node** root, Node* y) {
    Node* x = y->l;          // x = y.left

    // Reposition beta
    y->l = x->r;
    if (x->r != NULL) x->r->p = y;

    // Connect x to y's parent
    x->p = y->p;
    if (y->p == NULL) *root = x;
    else if (y == y->p->r) y->p->r = x;
    else y->p->l = x;

    // Reconnect x and y
    x->r = y;
    y->p = x;

    // Recompute heights — y first (now lower), then x
    y->h = get_new_h(y);
    x->h = get_new_h(x);

    return x;  // return new subtree root
}

// BALANCE(T, y, z) — Slide 28
// Called when |y.left.h - y.right.h| == 2.
// z is the originally inserted node; its key identifies which of the four
// imbalance cases (LL, RR, LR, RL) applies.
void balance(Node** root, Node* y, Node* z) {
    int lh = (y->l != NULL) ? y->l->h : 0;
    int rh = (y->r != NULL) ? y->r->h : 0;
    int bf = lh - rh;  // balance factor

    // LL case: imbalance due to insertion into y's left child's LEFT subtree
    if (bf == 2 && z->key < y->l->key) {
        right_rotation(root, y);
    }
    // RR case: imbalance due to insertion into y's right child's RIGHT subtree
    else if (bf == -2 && z->key > y->r->key) {
        left_rotation(root, y);
    }
    // LR case: imbalance due to insertion into y's left child's RIGHT subtree
    else if (bf == 2 && z->key > y->l->key) {
        y->l = left_rotation(root, y->l);
        right_rotation(root, y);
    }
    // RL case: imbalance due to insertion into y's right child's LEFT subtree
    else if (bf == -2 && z->key < y->r->key) {
        y->r = right_rotation(root, y->r);
        left_rotation(root, y);
    }
}

// AVL-INSERT(T, z) — Slides 17-39
void insert(Node** root, Node* z) {
    // Standard BST insertion — find the correct leaf position (Slides 17-20)
    Node* y = NULL;
    Node* x = *root;
    while (x != NULL) {
        y = x;
        if (z->key < x->key) x = x->l;
        else x = x->r;
    }
    z->p = y;
    if (y == NULL) *root = z;           // tree was empty
    else if (z->key < y->key) y->l = z;
    else y->r = z;

    // Set z's children to NIL and height to 1 (Slide 21)
    z->l = NULL;
    z->r = NULL;
    z->h = 1;

    // Walk up from z's parent, recomputing heights and rebalancing (Slides 22-39)
    Node* curr = z->p;
    while (curr != NULL) {
        // Recompute height (Slide 23)
        curr->h = get_new_h(curr);

        int lh = (curr->l != NULL) ? curr->l->h : 0;
        int rh = (curr->r != NULL) ? curr->r->h : 0;
        int bf = lh - rh;

        // If unbalanced (|bf| == 2), call BALANCE (Slides 26-27)
        if (bf == 2 || bf == -2) {
            // Save parent before rotation (balance may change curr's parent pointer)
            Node* next = curr->p;
            balance(root, curr, z);
            curr = next;  // continue from the ancestor above the rotated subtree
        } else {
            curr = curr->p;
        }
    }
}

Node* search(Node* root, int key) {
    if (root == NULL) return NULL;
    Node* x = root;
    while (x != NULL) {
        if (x->key == key) {
            return x;
        } else if (x->key > key) {
            x = x->l;
        } else {
            x = x->r;
        }
    }
    return NULL;
}

void free_tree(Node* root) {
    if (root != NULL) {
        free_tree((root)->l);
        free_tree((root)->r);
        free(root);
        root = NULL;
    }
}

int main() {
    Node* root = create_node(20);

    Node* nl  = create_node(18);
    Node* nr  = create_node(24);
    Node* nll = create_node(8);

    // Wire up the tree correctly — including the missing nll->p link
    root->l = nl;  root->r = nr;
    nl->p = root;  nr->p = root;
    nl->l = nll;
    nll->p = nl;   // BUG FIX: parent pointer was missing in original code

    // Set heights bottom-up
    nll->h = 1;
    nl->h  = 2;
    nr->h  = 1;
    root->h = 3;

    printf("Before insertion:\n");
    printTree(root, "", true);

    Node* z = create_node(10);
    insert(&root, z);

    printf("\nAfter inserting 10:\n");
    printTree(root, "", true);

    Node* s_z = search(root, 10);
    printf("search(10): found=%p, inserted=%p, match=%s\n", s_z, z, (s_z == z ? "yes" : "no"));
    
    free_tree(root);
}