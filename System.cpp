#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include "System.h"
#include "Parser.h"


using namespace std;

// Constructor
System::System() {
    system_count = 0;
    primary_count = 0;
    user_count = 0;
    efn = 0;
    songs = new BST<Song>();
    primary_library = new BST<Song>();
    users = new BST<GraphNode>();
}

// Destructor 
System::~System() {
    delete songs;
    delete primary_library;
    delete users;
}


void System::show_menu() {
  while (true) {
    cout << "\nPlease choose an option from the following menu: \n" <<
            "\t\"add song\" to add song from the terminal\n" <<
            "\t\"add songs <filename>\" to add songs from a file\n" <<
            "\t\"add user\" to add user from the terminal\n" <<
            "\t\"add users <filename>\" to add users from a file\n" <<
            "\t\"show songs\" to show all songs\n" <<
            "\t\"show users\" to show all users\n" <<
            "\t\"show friends <user>\" to show friends of user\n" <<
            "\t\"add friendship <user1> <user2>\" to add friendship between user1 and user2\n" <<
            "\t\"break friendship <user1> <user2>\" to break friendship between user1 and user2\n" <<
            "\t\"exit\" to exit the program\n";
            

    
    // Parse input
    string line;
    getline(cin, line);
    Parser parser(line);
    
    string operation = parser.getOperation();
    string arg1 = parser.getArg1();
    string arg2 = parser.getArg2();

    // Call functions according to input
    if (operation == "add") {
        if (arg1 == "songs") {
            add_songs(arg2);
        }
        if (arg1 == "song") {
            add_song();
        }
        
        if (arg1 == "users") {
            add_users(arg2);
        }
        if (arg1 == "user") {
            add_user();
        }
    }

    if (operation == "show") {
        if (arg1 == "songs") {
            show_songs(arg2);
        }
        if (arg1 == "users") {
            show_users();
        }
        if (arg1 == "friends") {
            show_friends(arg2);
        }
    }

    if (operation == "add") {
        if (arg1 == "friendship") {
            Parser parser2(arg2);
            add_friendship(parser2.getOperation(), parser2.getArg1());
        }
    }

    if (operation == "break") {
        if (arg1 == "friendship") {
            Parser parser3(arg2);
            break_friendship(parser3.getOperation(), parser3.getArg1());
        }
    }

    if (operation == "set" && arg1 == "efn") {
        set_efn(stoi(arg2));
    }

    if (operation == "listen" && arg1 == "song") {
        Parser parser4(arg2);
        string user = parser4.getOperation();
        int listen_count = stoi(parser4.getArg1());
        string song = parser4.getArg2();
        listen(user, listen_count, song);
    }

    if (operation == "recommend") {
        recommend(stoi(arg1));
    }

    if (operation == "exit") {
        break;
    }
  }
}

// Add songs from file
void System::add_songs(string filename) {
    ifstream songfile(filename + ".txt");

    //  Throw error if file doesn't exist
    if (!songfile.good()) {
        cout << "Error: Song file not found!\n";
        return;
    }

    // Variables to hold information from the file
    string title;

    while (getline(songfile, title)) {
        // Extract information from the file
        if (title == "") {
            getline(songfile, title);
        }
        // Create Song objects
        Song new_song(title, 0);
        songs -> insert(new_song);
        songs_heap.push_back(new_song);
        index[title] = songs_heap.size() - 1;
        system_count++;
    }

    // Close files
    songfile.close();
}

// Add song from terminal
void System::add_song() {
    string title;

    cout << "Enter song title: \n";
    getline(cin, title);

    Song new_song(title, 0);
    songs -> insert(new_song);
    songs_heap.push_back(new_song);
    index[title] = songs_heap.size() - 1;
    system_count++;
}

// Add users from a file
void System::add_users(string filename) {
    ifstream userfile(filename + ".txt");

    //  Throw error if file doesn't exist
    if (!userfile.good()) {
        cout << "Error: User file not found!\n";
        return;
    }

    // Variables to hold information from the file
    string username;

    while (getline(userfile, username)) {
        // Extract information from the file
        if (username == "") {
            getline(userfile, username);
        }
        
        // Create User objects
        User new_user(username);
        GraphNode new_node(new_user);
        users -> insert(new_node);
        user_list.push_back(username);
        user_count++;
    }

    // Close files
    userfile.close();
}

// Add user from the terminal
void System::add_user() {
    string username;

    cout << "Enter user name: \n";
    getline(cin, username);

    User new_user(username);
    GraphNode new_node(new_user);
    users -> insert(new_node);
    user_list.push_back(username);
    user_count++;
}

// Show songs
void System::show_songs(string flag) {
    if (flag == "") {
        songs -> print();
    }

    else if (flag == "-h") {
        int index = 0;
        for (Song song : songs_heap) {
            cout << index << ": " << song << endl;
            index++;
        }
    }

    else if (flag == "-p") {
        primary_library -> print();
    }
}

// Show users
void System::show_users() {
    users -> print();
}

// Show friends
void System::show_friends(string u) {
    User temp_user(u);
    User* user = users -> get(temp_user) -> get_value();
    
    if (!user) {
        cout << "User not found!\n";
        return;
    }

    cout << "Friends of " + u + ": ";
    user -> show_friends();
}

// Add friendship
void System::add_friendship(string a, string b) {
    User user_1(a);
    User user_2(b);


    User* user_1_node = users -> get(user_1) -> get_value();
    User* user_2_node = users -> get(user_2) -> get_value();

    if (!user_1_node) {
        cout << "User 1 not found!\n";
        return;
    }

    if (!user_1_node) {
        cout << "User 2 not found!\n";
        return;
    }

    user_1_node -> add_friend(b);
    user_2_node -> add_friend(a);  
    update_efn();
}

// Break friendship
void System::break_friendship(string a, string b) {
    User temp1(a);
    User temp2(b);

    User* user1 = users -> get(temp1) -> get_value();
    User* user2 = users -> get(temp2) -> get_value();

    if (!user1) {
        cout << "User 1 not found!\n";
        return;
    }
    if (!user2) {
        cout << "User 2 not found!\n";
        return;
    }
    user1 -> remove_friend(a);
    user2 -> remove_friend(b);
    update_efn();
}

// Check if a song is in primary user's library
bool System::in_primary(Song s) {
    Song* song = primary_library -> get(s);
    if (song) {
        return true;
    }
    return false;
}

// Listen to a song
void System::listen(string user, int n, string title) {
    // If efn 0
    if (efn == 0) {
        cout << "Efn is 0!\n";
        return;
    }

    // If user is primary
    if (user == "Primary") {
        cout << "Error: Primary User can't listen to a song!\n";
        return;
    }

    // If user not in efn
    User u_temp(user);
    GraphNode g_temp(u_temp);
    GraphNode* u = users -> get(g_temp);
    if (u -> get_d() <= 0 || u -> get_d() > efn) {
        cout << "User not in efn!\n";
        return;
    }

    // If song already in primary user's library
    Song temp(title, 0);
    if (in_primary(temp) == true) {
        cout << "Song already in primary user's library!\n";
        return;
    }

    // Inc listen count if all conditions good
    Song* song = songs -> get(temp);
    song -> set_listen_count(song -> get_listen_count() + n);
    songs_heap[index[title]].set_listen_count(song -> get_listen_count());
    increase_key(index[title]);
}

// Max-heapify
void System::max_heapify(int i, int n) {
    int l = (2 * i) + 1;
    int r = (2 * i) + 2;
    int largest = i;

    if (l < n && songs_heap[l].get_listen_count() > songs_heap[largest].get_listen_count()) {
        largest = l;
    }

    if (r < n && songs_heap[r].get_listen_count() > songs_heap[largest].get_listen_count()) {
        largest = r;
    }

    if (largest != i) {
        index[songs_heap[i].get_title()] = largest;
        index[songs_heap[largest].get_title()] = i;
        swap(songs_heap[i] , songs_heap[largest]);
        max_heapify(largest, n);
    }
}

// Extract max
Song System::extract_max(int n) {
    if (n < 1) {
        cout << "Error: Heap underflow!\n";
    }
    Song max = songs_heap[0];
    songs_heap[0] = songs_heap[n - 1];
    index[songs_heap[0].get_title()] = 0;
    songs_heap.pop_back();
    n = n - 1;
    max_heapify(0, n);
    return max;
}

// Increase key
void System::increase_key(int i) {
    while (i > 0 && songs_heap[(i - 1) / 2].get_listen_count() < songs_heap[i].get_listen_count()) {
        index[songs_heap[(i - 1) / 2].get_title()] = i;
        index[songs_heap[i].get_title()] = (i - 1) / 2;
        swap(songs_heap[(i - 1) / 2], songs_heap[i]);
        i = (i - 1) / 2;
    }
}

// Set efn
void System::set_efn(int k) {
    efn = k;
}

// Update efn
void System::update_efn() {
    for (string user : user_list) {
        User usr(user);
        GraphNode temp_node(usr);
        GraphNode* node = users -> get(temp_node);
        node -> set_color("white");
        node -> set_d(0);
        node -> set_pred("null");
    }
    User pusr(user_list[0]);
    GraphNode temp(pusr);
    GraphNode* primary = users -> get(temp);
    primary -> set_color("gray");
    primary -> set_d(0);
    primary -> set_pred("null");
    
    queue<GraphNode*> fq;
    fq.push(primary);
    while (fq.size() > 0) {
        GraphNode* u = fq.front();
        fq.pop();
        for (string fname : u -> get_value() -> get_friends()) {
            User tempusr(fname);
            GraphNode temp(tempusr);
            GraphNode* curr = users -> get(temp);
            if (curr -> get_color() == "white") {
                curr -> set_color("gray");
                curr -> set_d(u -> get_d() + 1);
                fq.push(curr);
            }
        }
        u -> set_color("black");
    }
}

// Recommend songs
void System::recommend(int k) {
    int count = 0;
    while (count < k) {
        Song song = extract_max(songs_heap.size());
        song.set_listen_count(0);
        primary_library -> insert(song);
        primary_count++;
        system_count--;
        count++;
    }
}