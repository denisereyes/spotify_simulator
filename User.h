#pragma once
#include <string>
#include <iostream>
#include <vector>

/* TO-DO:
    Use a stl::map to map usernames with userids. O(log n).
*/
class User {
 public:
  User();
  User(std::string user_name);

  // Setters and Getters
  std::vector<std::string> get_friends();
  void set_username(std::string new_username);
  std::string get_username();

  // Copy & Overloading
  bool operator==(const User& other);
  bool operator<(const User& other) const;
  bool operator>(const User& other) const;
  friend std::ostream& operator<<(std::ostream& os, const User& se);

  void add_friend(std::string new_friend);
  void remove_friend(std::string s);
  void show_friends();

 private:
  std::string username;
  std::vector<std::string> friends;
};

std::ostream& operator<<(std::ostream& os, const User& se);