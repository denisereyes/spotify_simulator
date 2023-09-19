#include <vector>
#include <map>
#include "Song.h"
#include "User.h"
#include "BST.h"
#include "GraphNode.h"


class System {
  public:
    System();
    ~System();

    void show_menu();
    
    void add_songs(std::string filename);
    void add_song();

    void add_users(std::string filename);
    void add_user();

    void show_songs(std::string flag);
    void show_users();
    void show_friends(std::string u);

    void add_friendship(std::string a, std::string b);
    void break_friendship(std::string a, std::string b);

    void set_efn(int k);
    void listen(std::string user, int n, std::string title);
    void recommend(int k);

    bool in_primary(Song s);

    // Heap functions
    void max_heapify(int i, int n);
    Song extract_max(int n);
    void increase_key(int i);

    // Graph functions
    void update_efn();
  private:
    int system_count, primary_count, user_count, efn;

    // BST and Graph for songs and users
    BST<Song> *songs;
    BST<Song> *primary_library;
    BST<GraphNode> *users;
    std::vector<std:: string> user_list;

    // Heap for songs
    std::vector<Song> songs_heap;

    // Map for heap indexes
    std::map<std::string, int> index;
};