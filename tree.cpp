#include <iostream>
#include <memory>
#include <functional>
#include <queue>
#include <climits>
#include <algorithm>

enum Colors {WHITE, BLACK, GRAY};

using namespace std;

template <typename T>
struct Node {
    T data;
    shared_ptr<Node> left;
    shared_ptr<Node> right;

    Colors color = WHITE;
    int d = -1; // -1 represents infinity
    int f = 0; // Finish time
    std::shared_ptr<Node> pi = nullptr; // Parent pointer

    Node(T val, std::shared_ptr<Node> l, std::shared_ptr<Node> r) : data(val), left(l), right(r) {}
    Node(int val) : data(val), left(nullptr), right(nullptr) {}    
};

template <typename T>
using nodeptr = shared_ptr<Node<T>>;

template <typename T>
void InOrder(nodeptr<T> root, function<void(nodeptr<T>)>& f) {
    nodeptr x = root;
    if (x != nullptr) {
        InOrder(x->left, f);
        f(x);
        InOrder(x->right, f);
    }
}


template <typename T>
void PreOrder(nodeptr<T> root, function<void(nodeptr<T>)>& f) {
    nodeptr x = root;
    if (x != nullptr) {
        f(x);
        PreOrder(x->left, f);
        PreOrder(x->right, f);
    }
}


template <typename T>
void PostOrder(nodeptr<T> root, function<void(nodeptr<T>)>& f) {
    nodeptr x = root;
    if (x != nullptr) {
        PostOrder(x->left, f);
        PostOrder(x->right, f);
        f(x);
    }
}

template <typename T>
void BFS(nodeptr<T> s) {
    s->color = GRAY;
    s->d = 0;
    s->pi = nullptr;

    queue<nodeptr<T>> Q;
    Q.push(s);

    while (!Q.empty()) {
        nodeptr<T> u = Q.front();
        Q.pop();

        nodeptr<T> neighbours[] = {u->left, u->right};
        for (nodeptr<T> v: neighbours) {
            if (v != nullptr) {
                if (v->color == WHITE) {
                    v->color = GRAY;
                    v->d = u->d + 1;
                    v->pi = u;
                    Q.push(v);
                }
            }
        }
        u->color = BLACK;
        std::cout << "Visited " << u->data << " at distance " << u->d << std::endl;
    }

}

template <typename T>
void DFS_Visit(nodeptr<T> u, int& time) {
    // 1-3: Discover node u
    time = time + 1;
    u->d = time;
    u->color = GRAY;
    cout << "Discovering " << u->data << " at " << u->d << endl;

    // 4-5: Explore neighbors (Left and Right for your tree)
    nodeptr<T> neighbors[] = {u->left, u->right};
    for (nodeptr<T> v : neighbors) {
        if (v != nullptr) {
            // 5-7: If v is WHITE, it's a "Tree Edge"
            if (v->color == WHITE) {
                v->pi = u;
                DFS_Visit(v, time);
            }
        }
    }

    // 8-10: Finish node u
    u->color = BLACK;
    time = time + 1;
    u->f = time;
    cout << "Finishing " << u->data << " at " << u->f << endl;
}

// Wrapper to match DFS(G)
template <typename T>
void DFS(vector<nodeptr<T>>& nodes) {
    int time = 0;
    // Initialization (Step 1-3)
    for (auto& u : nodes) {
        u->color = WHITE;
        u->pi = nullptr;
    }
    // Search (Step 5-7)
    for (auto& u : nodes) {
        if (u->color == WHITE) {
            DFS_Visit(u, time);
        }
    }
}

template <typename T>
vector<T> SolveMazeBFS(nodeptr<T> start, nodeptr<T> end) {
    queue<nodeptr<T>> Q;
    start->color = GRAY;
    start->d = 0;
    Q.push(start);

    while (!Q.empty()) {
        nodeptr<T> u = Q.front();
        Q.pop();

        // Check only left and right since structure is fixed
        nodeptr<T> children[] = {u->left, u->right};
        for (nodeptr<T> v : children) {
            if (v != nullptr && v->color == WHITE) {
                v->color = GRAY;
                v->d = u->d + 1;
                v->pi = u;
                if (v == end) {
                    break; 
                }
                Q.push(v);
            }
        }
        u->color = BLACK;
    }

    // Path reconstruction into a vector
    vector<T> path;
    nodeptr<T> curr = end;
    while (curr != nullptr) {
        path.push_back(curr->data);
        curr = curr->pi; // Move to parent
    }
    
    // Reverse to get Start -> End order
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    vector<nodeptr<char>> nodes(13); 

    for (int i = 0; i < 13; i++) {
        nodes[i] = make_shared<Node<char>>(char('A' + i));
    }

    nodeptr<char> A = nodes[0], B = nodes[1], C = nodes[2], D = nodes[3],
                  E = nodes[4], F = nodes[5], G = nodes[6], H = nodes[7],
                  I = nodes[8], J = nodes[9], K = nodes[10], L = nodes[11],
                  M = nodes[12];

    A->left = B;
    B->left = C;
    C->left = D;
    D->left = E;
    E->left = F;
    F->left = G;

    B->right = H;
    H->left = I;
    I->left = J;
    H->right = K;
    K->right = L;
    L->right = M;

    BFS(A);
    DFS(nodes);

    auto path = SolveMazeBFS(A, J);
    for (auto p: path) {
        cout << p << "->";
    }
    return 0;
}
