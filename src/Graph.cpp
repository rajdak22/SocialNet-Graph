#include "../include/Graph.hpp"
#include <queue>
#include <iostream>

SocialNetGraph::SocialNetGraph() {}

// Utility Functions

string SocialNetGraph::lower_caseify(const string& username) {
    string lowered = username;

    for(char& c : lowered) {
        if(c - 'A' < 26 && c - 'A' >= 0) c = (char) c + 'a' - 'A';
    }

    return lowered;
}

int SocialNetGraph::getID(const string& username_temp) {
    string username = lower_caseify(username_temp);

    if (usernameToID.find(username) == usernameToID.end()) {
        return -1; 
    }
    return usernameToID[username];
}

// Social Network Operations 

bool SocialNetGraph::addUser(const string& username) {
    int old_id = getID(username);
    
    if (old_id != -1) {
        return false;
    }

    int newID = adjList.size();                                         // The next available index
    adjList.emplace_back();                                             // Adds a new, empty list (vector) for the new user
    usernameToID[username] = newID;                                     // Updates map of username to ID
    allUsers.push_back({username, AVL_Tree_Post()}); // Store original username & new AVL Tree
    
    return true;
}

int SocialNetGraph::degreesOfSeparation(const string& u1, const string& u2) {
    int id1 = getID(u1);
    int id2 = getID(u2);

    if (id1 == -1 || id2 == -1) return -2;

    queue<pair<int, int>> q; // {current_id, distance}
    vector<bool> visited(adjList.size(), false);

    // performing BFS to find shortest distance
    q.push({id1, 0});
    visited[id1] = true;

    while (!q.empty()) {
        auto [currentID, distance] = q.front();
        q.pop();

        if (currentID == id2) {
            return distance; // Found the shortest path length 
        }

        // Iterate through neighbors
        for (int neighborID : adjList[currentID]) {
            if (!visited[neighborID]) {
                visited[neighborID] = true;
                q.push({neighborID, distance + 1});
            }
        }
    }

    return -1; 
}

int SocialNetGraph::addFriend(const string& u1, const string& u2) {
    int id1 = getID(u1);
    int id2 = getID(u2);

    if (id1 == -1 || id2 == -1) return -1;

    if(find(adjList[id1].begin(), adjList[id1].end(), id2) != adjList[id1].end()) return 0;

    adjList[id1].push_back(id2);
    adjList[id2].push_back(id1);
    string u1_copy = u1;
    string u2_copy = u2;
    // allUsers[id1].friendsTree.insertFriend(u2_copy);
    // allUsers[id2].friendsTree.insertFriend(u1_copy);
    return 1;
}

void SocialNetGraph::listFriends(const string& username) {
    int id = getID(username);

    if(id == -1) cout<<"Invalid Username\n";
    else {
        vector<string> friends;
        for(int uid : adjList[id]) {
            friends.push_back(allUsers[uid].username);
        }
        sort(friends.begin(), friends.end());
        for(auto f : friends) {
            cout<<f<<endl;
        }
    }
}

// INCOMPLETE, COMPLETE THE IMPLEMENTATION
vector<string> SocialNetGraph::suggestFriends(const string& username, int N) {
    int id = getID(username);

    if(id == -1) return {"Invalid Username"};

    vector<int> friends = adjList[id];
    unordered_map<int, int> mutualCount;

    for (int friendID : friends) {
        for (int fof : adjList[friendID]) {
            mutualCount[fof]++;
        }
    }
    mutualCount[id] = 0;
    for (int friendID : friends) {
        mutualCount[friendID] = 0;
    }

    vector<pair<int, int>> candidates; // (userID, mutualCount)

    for (auto [user_id, count] : mutualCount) {
        if(count > 0) candidates.emplace_back(user_id, count);
    }

    // Custom sorting using comparator for candidates; Sorting by 
    // number of mutuals, followed by alphabetical order

    sort(candidates.begin(), candidates.end(), [&](const auto& a, const auto& b) {
        if (a.second != b.second)
            return a.second > b.second;
        return allUsers[a.first].username < allUsers[b.first].username;
    });

    vector<string> mutuals;

    N = (N == -1)? (int) candidates.size() : N;

    for(int i = 0; i < min(N, (int) candidates.size()); i++) {
        mutuals.push_back(allUsers[candidates[i].first].username);
    }

    return mutuals;
}

// User Content Operations

bool SocialNetGraph::addPost(const string& username, const string& content) {
    int id = getID(username);
    if (id == -1) return false;
    
    allUsers[id].postTree.insertPost(content);
    return true;
}

void SocialNetGraph::outputPosts(const string& username, int N) {
    int id = getID(username);
    if (id == -1) return;
    
    queue<Node_Post*> latest = allUsers[id].postTree.output_posts(N);

    int count = 1;

    while(!latest.empty()) {
        Node_Post* post = latest.front();
        latest.pop();
        cout<<"Post Number ";
        cout<<count<<":"<<endl;
        cout<<post->post_content<<endl;
        count++;
    }
}
