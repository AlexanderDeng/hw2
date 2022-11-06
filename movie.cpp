#include <iostream> 
#include <iomanip> 
#include <sstream> 
#include "movie.h"
#include "util.h"
#include <string> 
#include <set>
#include <list>
#include <map> 

using namespace std; 

set<string> Movie::keywords() const
{
  set<string> words; 
  set<string> genre;
  set<string>::iterator genreIt; 
  words = parseStringToWords(name_); 
  genre = parseStringToWords(genre_); 
  for (genreIt = genre.begin(); genreIt != genre.end(); ++genreIt)
  {
    words.insert(*genreIt); 
  }
  words.insert(to_string(price_));
  words.insert(to_string(qty_)); 
  words.insert(rating_);
  return words; 
}

string Movie::displayString() const
{
  stringstream ss; 
  ss << name_ << "\n" << "Genre: " << genre_ <<" "<< "Rating: " << rating_ << "\n" << setprecision(2) << fixed << price_ << " " << qty_ << " " << "left." << "\n" << endl; 
  return ss.str(); 
}

void Movie::dump(ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

Movie::Movie(const string category, const string name, double price, int qty, string genre, string rating) : Product(category, name, price, qty)
{
  //category_ = category; 
  //name_ = name; 
  //price_ = price; 
  //qty_ = qty; 
  genre_ = genre; 
  rating_ = rating; 
}