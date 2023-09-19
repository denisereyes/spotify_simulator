#include "Song.h"
#include <iostream>
#include <stdlib.h>
#include <sstream>

using namespace std;

// Default constructor
Song::Song() {
  title = "";
  listen_count = 0;
}
// Specific constructor
Song::Song(string song_title, int listen_count_val) {
  title = song_title;
  listen_count = listen_count_val;
}

// Operator overloading
bool Song::operator==(const Song& other) {
  return (title == other.title);
}

bool Song::operator<(const Song& other) {
  return (title < other.title);
}

bool Song::operator>(const Song& other) {
  return (title > other.title);
}

ostream& operator<<(ostream& os, const Song& se)
{
  os << se.title << ", " << se.listen_count;
  return os;
}

// Setters & Getters
void Song::set_title(string new_title) {
  this->title = new_title;
}
string Song::get_title() {
  return title;
}

void Song::set_listen_count(int new_listen_count) {
  listen_count = new_listen_count;
}
int Song::get_listen_count() {
  return listen_count;
}