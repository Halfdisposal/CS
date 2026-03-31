#include <iostream>
#include <string>
#include <memory>
#include <stdio.h>



typedef struct Node {
    int key;
    int h;
    std::shared_ptr<Node> l, r, p;
} Node;

using node_ptr = std::shared_ptr<Node>;

int max(int x, int y) {
    return x > y ? x : y;
}


node_ptr create_node(int key, int h = 1) {
    node_ptr n = std::make_shared<Node>();
    n->key = key;
    n->h = h;
    n->l = nullptr;
    n->r = nullptr;
    n->p = nullptr;
    return n;
}


auto printTree = [](auto& self, node_ptr node, std::string indent, bool isLeft) -> void {
    if (node == nullptr) return;
    self(self, node->r, indent + (isLeft ? "|   " : "    "), false);
    std::cout << indent;
    std::cout << (isLeft ? "^- " : "v- ");
    std::cout << node->key << "(" << node->h << ")" << std::endl;
    self(self, node->l, indent + (isLeft ? "    " : "|   "), true);
};

// Height calculation as per Slide 14:
// x.h = 1 + max(x.left.h, x.right.h)
// NIL nodes have height 0
int get_new_h(node_ptr x) {
    if (x == nullptr) return 0;
    int lh = (x->l != nullptr) ? x->l->h : 0;
    int rh = (x->r != nullptr) ? x->r->h : 0;
    return 1 + max(lh, rh);
}

// LEFT-ROTATE(T, x) — Slides 11-15
// Rotates left around x; x's right child y becomes the new subtree root.
// Heights of x and y are recomputed after pointer changes (Slide 14).
// Returns the new subtree root y.
node_ptr left_rotation(node_ptr& root, node_ptr x) {
    node_ptr y = x->r;          // y = x.right  (Slide 11)

    // Reposition beta (Slide 11)
    x->r = y->l;
    if (y->l != nullptr) y->l->p = x;

    // Connect y to x's parent (Slide 12)
    y->p = x->p;
    if (x->p == nullptr) root = y;          // x was root → y becomes root
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
node_ptr right_rotation(node_ptr& root, node_ptr y) {
    node_ptr x = y->l;          // x = y.left

    // Reposition beta
    y->l = x->r;
    if (x->r != nullptr) x->r->p = y;

    // Connect x to y's parent
    x->p = y->p;
    if (y->p == nullptr) root = x;
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
void balance(node_ptr& root, node_ptr y, node_ptr z) {
    int lh = (y->l != nullptr) ? y->l->h : 0;
    int rh = (y->r != nullptr) ? y->r->h : 0;
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
void insert(node_ptr& root, node_ptr z) {
    // Standard BST insertion — find the correct leaf position (Slides 17-20)
    node_ptr y = nullptr;
    node_ptr x = root;
    while (x != nullptr) {
        y = x;
        if (z->key < x->key) x = x->l;
        else x = x->r;
    }
    z->p = y;
    if (y == nullptr) root = z;           // tree was empty
    else if (z->key < y->key) y->l = z;
    else y->r = z;

    // Set z's children to NIL and height to 1 (Slide 21)
    z->l = nullptr;
    z->r = nullptr;
    z->h = 1;

    // Walk up from z's parent, recomputing heights and rebalancing (Slides 22-39)
    node_ptr curr = z->p;
    while (curr != nullptr) {
        // Recompute height (Slide 23)
        curr->h = get_new_h(curr);

        int lh = (curr->l != nullptr) ? curr->l->h : 0;
        int rh = (curr->r != nullptr) ? curr->r->h : 0;
        int bf = lh - rh;

        // If unbalanced (|bf| == 2), call BALANCE (Slides 26-27)
        if (bf == 2 || bf == -2) {
            // Save parent before rotation (balance may change curr's parent pointer)
            node_ptr next = curr->p;
            balance(root, curr, z);
            curr = next;  // continue from the ancestor above the rotated subtree
        } else {
            curr = curr->p;
        }
    }
}

node_ptr search(const node_ptr root, int key) {
    if (root == nullptr) return nullptr;
    node_ptr x = root;
    while (x != nullptr) {
        if (x->key == key) {
            return x;
        } else if (x->key > key) {
            x = x->l;
        } else {
            x = x->r;
        }
    }
    return nullptr;
}


int main() {
    node_ptr root = create_node(20);

    node_ptr nl  = create_node(18);
    node_ptr nr  = create_node(24);
    node_ptr nll = create_node(8);

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
    printTree(printTree, root, "", true);

    node_ptr z = create_node(10);
    insert(root, z);

    printf("\nAfter inserting 10:\n");
    printTree(printTree, root, "", true);

    node_ptr s_z = search(root, 10);
    // Use %p for pointer addresses (shared_ptr stores the managed pointer via .get())
    printf("search(10): found=%p, inserted=%p, match=%s\n",
           (void*)s_z.get(), (void*)z.get(),
           (s_z == z ? "yes" : "no"));
}