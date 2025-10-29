#include "../include/AVL_Tree_Post.hpp"
#include <algorithm> // for max() function

// Node Implementation

Node_Post::Node_Post(string post_content) {
    this->post_content = post_content;
    time_of_posting = time(nullptr);
    left = nullptr;
    right = nullptr;
    height = 0;
}

// AVL_Tree Implementation

AVL_Tree_Post::AVL_Tree_Post() : root(nullptr) {}

AVL_Tree_Post::~AVL_Tree_Post() {
    deleteTree(root);
}

// Auxilliary Functions
int AVL_Tree_Post::height(Node_Post* N) const {
    return (N == nullptr) ? -1 : N->height;
}

int AVL_Tree_Post::getBalance(Node_Post* N) const {
    return (N == nullptr) ? 0 : height(N->left) - height(N->right);
}

void AVL_Tree_Post::updateNode(Node_Post* N) {
    if (N == nullptr) return;
    N->height = 1 + max(height(N->left), height(N->right));
}

// Rotations
Node_Post* AVL_Tree_Post::rightRotate(Node_Post* y) {
    Node_Post* x = y->left;
    Node_Post* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateNode(y);
    updateNode(x);

    return x;
}

Node_Post* AVL_Tree_Post::leftRotate(Node_Post* y) {
    Node_Post* x = y->right;
    Node_Post* T2 = x->left;

    // Perform Rotation
    x->left = y;
    y->right = T2;

    // Update Heights
    updateNode(y);
    updateNode(x);

    return x;
}

// Insertion
Node_Post* AVL_Tree_Post::insertHelper(Node_Post* node, const string& post_content, const time_t& post_time) {
    if (node == nullptr)
        return new Node_Post(post_content);

    if (post_time < node->time_of_posting)
        node->left = insertHelper(node->left, post_content, post_time);
    else if (post_time > node->time_of_posting)
        node->right = insertHelper(node->right, post_content, post_time);
    else
        return node; // duplicate timestamp, ignore

    updateNode(node);

    int balance = getBalance(node);

    // Balancing
    if (balance > 1 && post_time < node->left->time_of_posting)
        return rightRotate(node);

    if (balance < -1 && post_time > node->right->time_of_posting)
        return leftRotate(node);

    if (balance > 1 && post_time > node->left->time_of_posting) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && post_time < node->right->time_of_posting) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Finding min node for successor finding
Node_Post* AVL_Tree_Post::minValueNode(Node_Post* node) {
    Node_Post* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

// Deletion
Node_Post* AVL_Tree_Post::deleteNodeHelper(Node_Post* root, time_t post_time) {
    if (root == nullptr) return root;

    if (post_time < root->time_of_posting)
        root->left = deleteNodeHelper(root->left, post_time);
    else if (post_time > root->time_of_posting)
        root->right = deleteNodeHelper(root->right, post_time);
    else {
        // Node found
        if (root->left == nullptr || root->right == nullptr) {
            Node_Post* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                delete root;
                return nullptr;
            } else {
                *root = *temp;
                delete temp;
            }
        } else {
            Node_Post* temp = minValueNode(root->right);
            root->post_content = temp->post_content;
            root->time_of_posting = temp->time_of_posting;
            root->right = deleteNodeHelper(root->right, temp->time_of_posting);
        }
    }

    updateNode(root);

    int balance = getBalance(root);

    // Balancing
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

// Destructor Helper
void AVL_Tree_Post::deleteTree(Node_Post* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

// Public Functions
void AVL_Tree_Post::insertPost(const string& post_content) {
    time_t now = time(nullptr);
    root = insertHelper(root, post_content, now);
}

void AVL_Tree_Post::deletePost(time_t post_time) {
    root = deleteNodeHelper(root, post_time);
}

int AVL_Tree_Post::getRootBalanceFactor() const {
    if (root == nullptr)
        return 0;
    return getBalance(root);
}

queue<Node_Post*> AVL_Tree_Post::output_posts(int N) const {
    queue<Node_Post*> result;
    if (root == nullptr || N == 0)
        return result;

    stack<Node_Post*> st;
    Node_Post* curr = root;

    int count = 0;
    bool fetchAll = (N == -1);

    while ((!st.empty() || curr != nullptr) && (fetchAll || count < N)) {
        while (curr != nullptr) {
            st.push(curr);
            curr = curr->right;
        }

        curr = st.top();
        st.pop();

        result.push(curr);
        count++;

        curr = curr->left;
    }

    return result;
}
