#include <iostream> 
#include <sstream> 
#include "movie.h"
#include "util.h"
#include <string> 
#include <set>
#include <list>
#include <map> 

using namespace std; 

set<string> Movie::keywords()
{
  set<string> words; 
  words = parseStringToWords(name_); 
  words.insert(to_string(price_));
  words.insert(to_string(qty_)); 
  words.insert(genre_);
  words.insert(rating_);
  return words;
}

string Movie::displayString() const
{
  stringstream ss; 
  ss << name_ << " " <<  price_ << " " << qty_ << " " << genre_ << " " << rating_ << endl; 
  return ss.str(); 
}

void Movie::dump(ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

Movie::Movie(string category, string name, double price, int qty, string genre, string rating) : Product(category_, name_, price_, qty_)
{
  //category_ = category; 
  //name_ = name; 
  //price_ = price; 
  //qty_ = qty; 
  genre_ = genre; 
  rating_ = rating; 
}