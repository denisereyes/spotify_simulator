#pragma once
#include <string>
#include <iostream>

class Song {
 public:
  Song();
  Song(std::string song_title, int listen_count_val);

  // Copy & Overloading
  bool operator==(const Song& other);
  bool operator<(const Song& other);
  bool operator>(const Song& other);
  friend std::ostream& operator<<(std::ostream& os, const Song& se);

  void set_title(std::string new_title);
  std::string get_title();

  void set_listen_count(int new_listen_count);
  int get_listen_count();

 private:
  std::string title;
  int listen_count;
};

std::ostream& operator<<(std::ostream& os, const Song& se);