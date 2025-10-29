# SocialNet

This project implements a **C++-based social networking platform simulation** built using **custom AVL trees** for managing posts and friendships efficiently.  
It allows users to connect, post, and interact in a structured, data-driven environment with near-real-time query performance.

Unlike typical STL-based solutions, this project provides **custom implementations** of:

- **AVL_Tree_Post** → manages user posts chronologically (latest first)
- **AVL_Tree_People** → manages friend relationships in a balanced, sorted tree
- **SocialNetGraph** → maintains user relationships using adjacency lists and provides friend suggestions, degree calculations, etc.

---

## Prerequisites

To build and run this project, you need:

- **C++20** (or newer)
- A C++ compiler (`g++` or `clang++`)
- A working shell environment (`bash`)
- The following folder structure:

include/
AVL_Tree_People.hpp
AVL_Tree_Post.hpp
Graph.hpp
src/
AVL_Tree_People.cpp
AVL_Tree_Post.cpp
Graph.cpp
main.cpp
compile/
compile.sh


---

## Setup and Execution

Before first use, grant execution permission to the shell script:

chmod +x compile/compile.sh

Then run the following command to compile and execute:

./compile/compile.sh

This script:
1. Compiles all `.cpp` files using `g++ -std=c++20 -Wall -Wextra -O2`
2. Creates an executable called `main`
3. Runs the program automatically

---

## Key Terms

- **UserData** → Each user in the system with:
  - `username` (case-insensitive)
  - `postTree` (AVL_Tree_Post)
  - `friendsTree` (AVL_Tree_People)
- **Post Tree** → AVL tree maintaining posts sorted by posting time.
- **Friends Tree** → AVL tree maintaining friend usernames sorted alphabetically.
- **SocialNetGraph** → Core graph structure that manages all users, friendships, and cross-user operations.

---

## Commands

You interact with the system by typing commands in the terminal after launching the program.

|              Command                 |                                     Description                                              |
|--------------------------------------|----------------------------------------------------------------------------------------------|
| `add_user <username>`                | Adds a new user to SocialNet.                                                                |
| `add_friend <user1> <user2>`         | Connects two users as friends (bidirectional).                                               |
| `list_friends <username>`            | Lists all friends of the given user (one per line).                                          |
| `suggest_friends <username> <N>`     | Suggests up to `N` new friends based on mutual friends count. Use `-1` for all suggestions.  |
| `degrees_of_separation <u1> <u2>`    | Displays the minimum degrees of separation between two users.                                |
| `add_post <username> <post_content>` | Adds a post for a user. The post content can contain spaces.                               |
| `output_posts <username> <N>`        | Displays the latest `N` posts by that user (or all if `N == -1`).                            |
| `EXIT`                               | Exits the program safely.                                                                    |

---

## Notes

- **Usernames are case-insensitive** (e.g., `Alice` and `alice` are treated the same).
- **Usernames cannot have spaces**.
- Each printed entry (friends, posts, etc.) appears on a **new line**.
- Invalid argument counts display `"Arguments Mismatch"`.
- Invalid numbers or conversions display `"Arguments Mismatch : Enter a valid number"`.

---

## Example

Welcome to SocialNet! Get started

> add_user Alice
alice is now a part of SocialNet

> add_user Bob
bob is now a part of SocialNet

> add_user Charlie
charlie is now a part of SocialNet

> add_friend Alice Bob
alice befriended bob !

> add_friend Alice Charlie
alice befriended charlie !

> add_friend Bob Charlie
bob befriended charlie !

> suggest_friends Alice 5
# (no new suggestions since Alice already knows both)

> degrees_of_separation Alice Charlie
1 degrees apart

> add_post Alice I love data structures!
alice has posted successfully

> add_post Alice AVL trees are cool!
alice has posted successfully

> output_posts Alice 2
The latest posts are:
AVL trees are cool!
I love data structures!

> list_friends Bob
alice
charlie

> EXIT
Exiting...

---

## Design Highlights

- **Balanced AVL Trees** → Ensure `O(log n)` complexity for insertion, deletion, and lookups.
- **Graph-based Friendships** → Enable mutual friend analysis and degree computation efficiently.
- **Chronological Post Management** → Ensures the most recent posts are fetched first.
- **Automated Build Script** → `compile.sh` compiles and runs the program in a single step.

---

## Author

Developed as part of **COL106: Data Structures and Algorithms — Long Assignment 2**.  
Project Name: **SocialNet**
