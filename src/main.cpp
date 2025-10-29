#include "../include/Graph.hpp"
#include <sstream>
#include <iostream>

void append(string& s_main, string& s_other)
{
    if(s_main != "") s_main.push_back(' ');
    for(char c : s_other) s_main.push_back(c);
}

string recreate(vector<string>& commands, int start)
{
    string text = "";
    for(int i = start; i < (int) commands.size(); i++) append(text, commands[i]);
    return text;
}

void string_to_int(string& s, int& n, bool& successful)
{
    successful = true;
    try
    {
        n = stoi(s);
    }
    catch(const invalid_argument&)
    {
        cout<<"Arguments Mismatch : Enter a valid number"<<endl;
        successful = false;

    }
}

int main()
{
    cout<<"Welcome to SocialNet! Get started"<<endl;
    string input = "";
    string helper = "";
    SocialNetGraph sng;
    while(input != "EXIT")
    {
        getline(cin, input);
        stringstream ss(input);
        vector<string> commands;
        while(ss >> helper)
        {
            commands.push_back(helper);
        }
        string command = commands[0];
        for(char& c : command) c = tolower((unsigned char) c);
        int size = commands.size();

        if(command == "add_user")
        {
            if(size != 2) cout<<"Arguments Mismatch"<<endl;
            else
            {
                string username = commands[1];
                bool added = sng.addUser(username);
                if(!added) cout<<"username "<<username<<" already in use"<<endl;
                else cout<<username<<" is now a part of SocialNet"<<endl;
            }
        }
        else if(command == "add_friend")
        {
            if(size != 3) cout<<"Arguments Mismatch"<<endl;
            else
            {
                string u1 = commands[1], u2 = commands[2];
                int status = sng.addFriend(u1, u2);
                if(status == -1)
                {
                    cout<<"Either user is not in SocialNet"<<endl;
                }
                else if (status == 0) 
                {
                    cout<<u1<<" and "<<u2<<" are already friends"<<endl;
                }
                else 
                {
                    cout<<u1<<" befriended "<<u2<<" !"<<endl;
                }
            }
        }
        else if(command == "list_friends")
        {
            if(size != 2) cout<<"Arguments Mismatch"<<endl;
            else
            {
                string username = commands[1];
                sng.listFriends(username);
            }
        }
        else if(command == "suggest_friends")
        {
            if(size != 3) cout<<"Arguments Mismatch"<<endl;
            else
            {
                string username = commands[1];
                bool valid_number = true;
                int N = -1;
                string_to_int(commands[2], N, valid_number);
                if(valid_number)
                {
                    vector<string> mutuals = sng.suggestFriends(username, N);
                    for(string fof : mutuals) cout<<fof<<endl;
                }
            }
        }
        else if(command == "degrees_of_separation")
        {
            if(size != 3) cout<<"Arguments Mismatch"<<endl;
            else
            {
                string u1 = commands[1], u2 = commands[2];
                int distance = sng.degreesOfSeparation(u1, u2);
                if(distance == -2)
                {
                    cout<<"Either user is not in SocialNet"<<endl;
                }
                else
                {
                    cout<<distance<<" degrees apart"<<endl;
                }
            }
        }
        else if(command == "add_post")
        {
            if(size < 3) cout<<"Arguments Mismatch"<<endl;
            else
            {
                string username = commands[1];
                string post_content = recreate(commands, 2);
                bool added = sng.addPost(username, post_content);
                if(!added)
                {
                    cout<<"Invalid username"<<endl;
                }
                else
                {
                    cout<<username<<" has posted successfully"<<endl;
                }
            }
        }
        else if(command == "output_posts")
        {
            if(size != 3) cout<<"Arguments Mismatch"<<endl;
            else
            {
                string username = commands[1];
                bool valid_number = true;
                int N = -1;
                string_to_int(commands[2], N, valid_number);
                if(valid_number)
                {
                    cout<<"The latest posts are: "<<endl; 
                    sng.outputPosts(username, N);
                }
            }
        }
        else if(command == "exit") input = "EXIT";
        else cout<<"Invalid command"<<endl;
    }
    cout<<"Exiting...\n";
    return 0;
}