#include "User.h"
#include <iostream>
#include <stdlib.h>
#include <sstream>

using namespace std;

// Default constructor
User::User() {
  username = "";
}
// Specific constructor
User::User(string user_name) {
  username = user_name;
}

bool User::operator==(const User& other) {
  return (username == other.username);
}
bool User::operator<(const User& other) const {
  return (username < other.username);
}
bool User::operator>(const User& other) const {
  return (username > other.username);
}

ostream& operator<<(ostream& os, const User& se)
{
  os << se.username;
  return os;
}

// Setters & Getters
vector<string> User::get_friends() {
  return friends;
}

void User::set_username(string new_username) {
  this->username = new_username;
}
string User::get_username() {
  return username;
}

// Add new friend to the vector
void User::add_friend(string new_friend) {
  friends.push_back(new_friend);
}

// Remove friend from the vector
void User::remove_friend(string s) {
  int index = 0;
  for (string f : friends) {
    if (f == s) {
      break;
    }
    index++;
  }
  friends.erase(friends.begin() + index);
}

// Show all friends
void User::show_friends() {
  for (string f : friends) {
    cout << f << ", ";
  }
  cout << endl;
}