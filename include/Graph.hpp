#include <string>
#include <vector>           // for efficient addition of users
#include <unordered_map>    // mapping user_names to numbers
#include <ctime>            // for timestamps

// AVL Tree header
#include "../include/AVL_Tree_Post.hpp"


using namespace std;

// struct to hold user-specific data (username and posts)
struct UserData {
    string username;
    AVL_Tree_Post postTree;         // The AVL Tree for the user's posts
    // AVL_Tree_People friendsTree;    // The AVL Tree for the user's friends
};

class SocialNetGraph {
private:

    vector<vector<int>> adjList; 
    unordered_map<string, int> usernameToID;
    vector<UserData> allUsers;
    string lower_caseify(const string& username);

public:

    SocialNetGraph();
    
    // Social Network Operations
    bool addUser(const string& username);                                  // ADD_USER 
    int addFriend(const string& u1, const string& u2);                     // ADD_FRIEND 
    void listFriends(const string& username);                              // LIST_FRIENDS 
    vector<string> suggestFriends(const string& username, int N);     // SUGGEST_FRIENDS 
    int degreesOfSeparation(const string& u1, const string& u2);           // DEGREES_OF_SEPARATION 
    
    // User Content Operations
    bool addPost(const string& username, const string& content);           // ADD_POST 
    void outputPosts(const string& username, int N);                       // OUTPUT_POSTS
    
    // Utility
    int getID(const string& username);                                           // GETS_ID
};