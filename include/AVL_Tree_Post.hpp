#ifndef AVL_TREE_POST_HPP
#define AVL_TREE_POST_HPP

#include <ctime>
#include <string>
#include <stack>
#include <queue>

using namespace std;

struct Node_Post {
    string post_content;
    time_t time_of_posting;
    Node_Post* left;
    Node_Post* right;
    int height;

    Node_Post(string post_content);
};

class AVL_Tree_Post {
private:
    Node_Post* root;

    // Utility functions
    int height(Node_Post* N) const;
    int getBalance(Node_Post* N) const;
    void updateNode(Node_Post* N);

    // Rotations
    Node_Post* rightRotate(Node_Post* y);
    Node_Post* leftRotate(Node_Post* y);

    // Core operations
    Node_Post* insertHelper(Node_Post* node, const string& post_content, const time_t& post_time);
    Node_Post* deleteNodeHelper(Node_Post* root, time_t post_time);
    Node_Post* minValueNode(Node_Post* node);

    // Helper to delete entire tree
    void deleteTree(Node_Post* node);

public:
    AVL_Tree_Post();
    ~AVL_Tree_Post();

    // Public API
    void insertPost(const string& post_content);
    void deletePost(time_t post_time);
    int getRootBalanceFactor() const;
    queue<Node_Post*> output_posts(int N) const;
};

#endif // AVL_TREE_HPP
